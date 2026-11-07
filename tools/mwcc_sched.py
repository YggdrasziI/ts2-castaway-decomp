#!/usr/bin/env python3
"""Trace mwccarm's instruction scheduler on one function.

mwccarm 2.0/sp1p5 schedules each basic block twice: once before register coloring
(virtual registers, with a register pressure mode) and once after it. Both passes
are a list scheduler like the GameCube compiler's Scheduler.c (notes/COMPILER.md).
This script compiles a source file with its own build command under the debugger
of tools/mwcc_blocks.py (Windows only) and prints, for each scheduled block of one
function:

  - its pcodes in code generation order: index, opcode number, flags, operands
    (r<N> register, "=" written, "+" read and written, #<imm>, symbols by name);
  - the order the scheduler chose, as indices of that list;
  - with --select, each cycle of the first pass: the ready nodes with their
    earliest cycle (e), deadline (l), successors they would uncover (u), height (h)
    and rank (r), "PRESSURE" when the register pressure mode is on, and the pick.

Opcode numbers are the compiler's own; no names are given for them. The compiler is
not modified and the object written under build/mwcc_blocks/ is identical to the
build's.

Usage:
  python tools/mwcc_sched.py <src/...cpp> --list
  python tools/mwcc_sched.py <src/...cpp> <symbol> [--select] [--version eur]

Every function whose name is <symbol> is traced (a constructor's C1 and C2 have
different names). Blocks are numbered from 0 in each pass.
"""

import argparse
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mwcc_blocks as mb  # noqa: E402

# Addresses in mwccarm 2.0/sp1p5 (mwcc_blocks.COMPILER_SHA1), found by disassembly.
BP_SCHEDULE1 = 0x471C4F     # back end: call of scheduleinstructions before coloring
BP_BLOCK = 0x4FF750         # scheduleblock(PCodeBlock *) entry
BP_BLOCK_END = 0x4FF896     # scheduleblock: after the issue loop
BP_SELECT = 0x4FF590        # selectinstruction(DGNode *head, u16 counter) entry
BP_PRESSURE = 0x4FF645      # selectinstruction: al = register pressure mode
SELECT_RETURNS = {0x4FF638: "Eax", 0x4FF6A0: "Esi", 0x4FF701: "Esi"}  # register holding the pick
COLORING = 0x63A364         # nonzero during the first pass
LIVE, LIMIT = 0x616680, 0x61667C  # live registers and limit (first register class)
PROC_NAME = 0x30            # Object *: HashNameNode *name; its text at +0xA
# PCode after code generation: the opcode at +0x28 is an s16 here (values above
# 0xFF; the machine model reads it with movsx word), not the u8 of mwcc_blocks
PCODE_FLAGS, PCODE_OP, PCODE_ARGC, PCODE_ARGS, ARG_SIZE = 0xC, 0x28, 0x2C, 0x2E, 0xE
NODE_INSTR, NODE_SUCC, NODE_FIELDS = 0xC, 0x8, 0x10  # DGNode; successor: next, node


def text(dbg, addr, limit=256):
    """A NUL-terminated string, read in small pieces so that the end of a page
    does not fail the read; "?" when nothing is readable."""
    out = b""
    while len(out) < limit:
        try:
            piece = dbg.read(addr + len(out), 16)
        except OSError:
            break
        out += piece
        if b"\0" in piece:
            break
    return out.split(b"\0")[0].decode("latin-1") or "?"


def operand(dbg, raw):
    kind, rclass = raw[0], struct.unpack_from("b", raw, 1)[0]
    if kind == 0:
        effect, reg = struct.unpack_from("<Hh", raw, 2)
        prefix = "r" if rclass == 0 else "c%d:r" % rclass
        return "%s%d%s" % (prefix, reg, {1: "", 2: "=", 3: "+"}.get(effect & 3, "?"))
    if kind == 2:
        return "#%d" % struct.unpack_from("<i", raw, 2)[0]
    if kind == 4:
        obj = struct.unpack_from("<I", raw, 6)[0]
        try:
            name = text(dbg, dbg.u32(obj + PROC_NAME) + 0xA)
        except OSError:
            name = "?"
        if name != "?":
            return "@" + name
    return "k%d:%s" % (kind, raw[2:].hex())


def addresses(dbg, block):
    out, p = [], dbg.u32(block + mb.BLOCK_FIRST)
    while p:
        out.append(p)
        p = dbg.u32(p)
    return out


def pcodes(dbg, block):
    out, p = [], dbg.u32(block + mb.BLOCK_FIRST)
    while p:
        argc = dbg.s16(p + PCODE_ARGC)
        raw = dbg.read(p + PCODE_ARGS, ARG_SIZE * argc) if argc > 0 else b""
        args = [operand(dbg, raw[i * ARG_SIZE:(i + 1) * ARG_SIZE]) for i in range(argc)]
        out.append((p, "op%03x f%06x %s" % (dbg.s16(p + PCODE_OP), dbg.u32(p + PCODE_FLAGS), " ".join(args))))
        p = dbg.u32(p)
    return out


def trace(cmd, symbol, select):
    names, state = [], {"name": None}

    def on_schedule1(dbg, ctx):
        # esi: the function (Object *) being compiled
        state["name"] = text(dbg, dbg.u32(ctx.Esi + PROC_NAME) + 0xA)
        state.pop("numbers", None)
        names.append(state["name"])

    def active():
        return symbol is not None and state["name"] == symbol

    def on_block(dbg, ctx):
        if not active():
            return
        block = dbg.u32(ctx.Esp + 4)
        state["block"] = block
        state["before"] = pcodes(dbg, block)
        state["index"] = {p: i for i, (p, _) in enumerate(state["before"])}
        state["first"] = dbg.u32(COLORING) != 0
        numbers = state.setdefault("numbers", {})  # per pass: blocks numbered from 0
        number = numbers.get(state["first"], 0)
        numbers[state["first"]] = number + 1
        print("== block %d, %s coloring" % (number, "before" if state["first"] else "after"))
        for i, (_, s) in enumerate(state["before"]):
            print("  %3d %s" % (i, s))

    def on_block_end(dbg, ctx):
        if not active() or "before" not in state:
            return
        flush()
        order = [state["index"].get(p, "?") for p in addresses(dbg, state["block"])]
        print("  order: %s" % " ".join(map(str, order)))
        del state["before"]

    def flush():
        # a pick whose return was not traced is shown, never dropped
        if "line" in state:
            print(state.pop("line") + " -> ?")

    def on_select(dbg, ctx):
        if not active() or not state.get("first") or "before" not in state:
            return
        flush()
        counter = dbg.u32(ctx.Esp + 8) & 0xFFFF
        ready, node = [], dbg.u32(ctx.Esp + 4)
        while node:
            latency, rank, earliest, latest, height, preds = struct.unpack(
                "<HHHHHh", dbg.read(node + NODE_FIELDS, 12))
            if preds == 0:
                uncovers, succ = 0, dbg.u32(node + NODE_SUCC)
                while succ:
                    if dbg.s16(dbg.u32(succ + 4) + NODE_FIELDS + 10) == 1:
                        uncovers += 1
                    succ = dbg.u32(succ)
                ready.append("%s(e%d l%d u%d h%d r%d)" % (
                    state["index"].get(dbg.u32(node + NODE_INSTR), "?"),
                    earliest, latest, uncovers, height, rank))
            node = dbg.u32(node)
        state["line"] = "  t%-3d live %d/%d ready %s" % (
            counter, dbg.u32(LIVE), dbg.u32(LIMIT), " ".join(ready))

    def on_pressure(dbg, ctx):
        if "line" in state and ctx.Eax & 0xFF:
            state["line"] += " PRESSURE"

    def on_select_return(dbg, ctx, register):
        if "line" not in state:
            return
        node = getattr(ctx, register)
        pick = state["index"].get(dbg.u32(node + NODE_INSTR), "?") if node else "none"
        print(state.pop("line") + " -> %s" % pick)

    dbg = mb.Debugger(cmd, mb.ROOT)
    dbg.add_breakpoint(BP_SCHEDULE1, on_schedule1)
    if symbol is not None:
        dbg.add_breakpoint(BP_BLOCK, on_block)
        dbg.add_breakpoint(BP_BLOCK_END, on_block_end)
        if select:
            dbg.add_breakpoint(BP_SELECT, on_select)
            dbg.add_breakpoint(BP_PRESSURE, on_pressure)
            for addr, register in SELECT_RETURNS.items():
                dbg.add_breakpoint(addr, lambda dbg, ctx, r=register: on_select_return(dbg, ctx, r))
    dbg.run()
    if dbg.exit_code:
        sys.exit("mwcc_sched: the compiler failed (exit code %d); run ninja to see why" % dbg.exit_code)
    return names


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("source")
    ap.add_argument("symbol", nargs="?", help="mangled name of the function to trace")
    ap.add_argument("--list", action="store_true", help="list the functions in schedule order")
    ap.add_argument("--select", action="store_true", help="trace each pick of the first pass")
    ap.add_argument("--version", default="eur")
    a = ap.parse_args()
    if (a.symbol is None) == (not a.list) or (a.list and a.select):
        ap.error("give either a symbol (with or without --select) or --list")
    if os.name != "nt":
        sys.exit("mwcc_sched: Windows only (Win32 debugging API)")
    if struct.calcsize("P") != 8:
        sys.exit("mwcc_sched: needs a 64-bit Python (DEBUG_EVENT layout)")
    mb.load_kernel32()
    names = trace(mb.build_command(a.source, a.version)[1], None if a.list else a.symbol, a.select)
    if a.list:
        print("\n".join(names))
    elif a.symbol not in names:
        sys.exit("mwcc_sched: %s not scheduled (see --list)" % a.symbol)


if __name__ == "__main__":
    main()
