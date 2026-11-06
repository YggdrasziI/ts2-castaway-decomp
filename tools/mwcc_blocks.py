#!/usr/bin/env python3
"""Trace where mwccarm splits straight-line code into basic blocks.

At the start of each statement, mwccarm's code generator ends the current basic
block when it already holds more than 100 pcodes (newstatement, as in the GameCube
compiler's CodeGen.c). A C++ expression statement is often several such statements
(one per call or temporary), so a block can start in the middle of a source line.
Register choices that look random in long runs of identical statements (the r0 / r1
truncation flip, notes/MATCHING.md) follow these block starts.

This script compiles a source file with its own build command under a minimal
Win32 debugger (Windows only; the 32-bit compiler runs under WOW64) and prints, for
each function in code generation order, the pcode count of the current block at
each statement start, and "|N|" where a block is split (N = calls already emitted in
the function). The compiler is not modified and the object is written under
build/mwcc_blocks/; it is identical to the build's.

Usage:
  python tools/mwcc_blocks.py <src/...cpp> [--func N] [--version eur]

Functions are numbered in the order the back end colors them; a function colored
again after spilling counts once. C1 / C2 constructors and D0 / D1 / D2 destructors
are each generated, so a constructor shows up twice.
"""

import argparse
import ctypes
import ctypes.wintypes as W
import hashlib
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mwcc_irdump import compile_command  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WORK = os.path.join(ROOT, "build", "mwcc_blocks")

# Addresses in mwccarm 2.0/sp1p5 (SHA-1 below), found by disassembly.
COMPILER_SHA1 = {"2.0/sp1p5": "6153c610734690650e563e03c5bbf45c9a060ee6"}
PCLASTBLOCK = 0x63A224    # current PCodeBlock *
PCBASICBLOCKS = 0x63A828  # first PCodeBlock * of the function
BLOCK_COUNT = 0x28        # PCodeBlock: s16 pcode count
BLOCK_FIRST = 0x14        # PCodeBlock: first PCode *; PCode +0: next PCode *
PCODE_OP = 0x28           # PCode: u8 opcode during code generation
OP_CALL = 6               # opcode of a call (3 per statement of 3 calls)
BP_STATEMENT = 0x4FFCCD   # newstatement: "cmp word ptr [edx+0x28], 0x64"
BP_SPLIT = 0x4FFCE0       # newstatement: "call branch_label(makepclabel())"
BP_COLORED = 0x513A85     # end of the register coloring of a function

k32 = None  # kernel32, loaded by load_kernel32() (Windows only)


def load_kernel32():
    global k32
    k32 = ctypes.WinDLL("kernel32", use_last_error=True)
    k32.OpenThread.restype = W.HANDLE
    k32.CreateProcessW.argtypes = [W.LPCWSTR, W.LPWSTR, ctypes.c_void_p, ctypes.c_void_p, W.BOOL,
                                   W.DWORD, ctypes.c_void_p, W.LPCWSTR, ctypes.c_void_p, ctypes.c_void_p]
    for f in (k32.ReadProcessMemory, k32.WriteProcessMemory):
        f.argtypes = [W.HANDLE, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t,
                      ctypes.POINTER(ctypes.c_size_t)]
    k32.FlushInstructionCache.argtypes = [W.HANDLE, ctypes.c_void_p, ctypes.c_size_t]
    k32.CloseHandle.argtypes = [W.HANDLE]

DEBUG_ONLY_THIS_PROCESS = 2
CREATE_NO_WINDOW = 0x08000000
DBG_CONTINUE = 0x10002
DBG_EXCEPTION_NOT_HANDLED = 0x80010001
EXCEPTION_DEBUG_EVENT, CREATE_PROCESS_DEBUG_EVENT, EXIT_PROCESS_DEBUG_EVENT = 1, 3, 5
LOAD_DLL_DEBUG_EVENT = 6
BREAKPOINT = (0x80000003, 0x4000001F)  # native, WOW64
SINGLE_STEP = (0x80000004, 0x4000001E)
WOW64_CONTEXT_ALL = 0x0001003F


class STARTUPINFO(ctypes.Structure):
    _fields_ = [("cb", W.DWORD), ("lpReserved", W.LPWSTR), ("lpDesktop", W.LPWSTR),
                ("lpTitle", W.LPWSTR), ("dwX", W.DWORD), ("dwY", W.DWORD),
                ("dwXSize", W.DWORD), ("dwYSize", W.DWORD), ("dwXCountChars", W.DWORD),
                ("dwYCountChars", W.DWORD), ("dwFillAttribute", W.DWORD), ("dwFlags", W.DWORD),
                ("wShowWindow", W.WORD), ("cbReserved2", W.WORD), ("lpReserved2", ctypes.c_void_p),
                ("hStdInput", W.HANDLE), ("hStdOutput", W.HANDLE), ("hStdError", W.HANDLE)]


class PROCESS_INFORMATION(ctypes.Structure):
    _fields_ = [("hProcess", W.HANDLE), ("hThread", W.HANDLE), ("dwProcessId", W.DWORD),
                ("dwThreadId", W.DWORD)]


class DEBUG_EVENT(ctypes.Structure):
    # the union is 8-aligned in a 64-bit debugger: it starts at offset 16
    _fields_ = [("dwDebugEventCode", W.DWORD), ("dwProcessId", W.DWORD),
                ("dwThreadId", W.DWORD), ("pad", W.DWORD), ("u", ctypes.c_ubyte * 168)]


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("ContextFlags", W.DWORD), ("Dr", W.DWORD * 6), ("FloatSave", ctypes.c_ubyte * 112),
                ("SegGs", W.DWORD), ("SegFs", W.DWORD), ("SegEs", W.DWORD), ("SegDs", W.DWORD),
                ("Edi", W.DWORD), ("Esi", W.DWORD), ("Ebx", W.DWORD), ("Edx", W.DWORD),
                ("Ecx", W.DWORD), ("Eax", W.DWORD), ("Ebp", W.DWORD), ("Eip", W.DWORD),
                ("SegCs", W.DWORD), ("EFlags", W.DWORD), ("Esp", W.DWORD), ("SegSs", W.DWORD),
                ("ExtendedRegisters", ctypes.c_ubyte * 512)]


class Debugger:
    """Runs one process; int3 breakpoints, each re-armed after a single step."""

    def __init__(self, args, cwd):
        cmdline = subprocess.list2cmdline(args)
        si = STARTUPINFO()
        si.cb = ctypes.sizeof(si)
        self.pi = PROCESS_INFORMATION()
        if not k32.CreateProcessW(None, ctypes.create_unicode_buffer(cmdline), None, None, False,
                                  DEBUG_ONLY_THIS_PROCESS | CREATE_NO_WINDOW, None, cwd,
                                  ctypes.byref(si), ctypes.byref(self.pi)):
            raise OSError("CreateProcess failed: %d" % ctypes.get_last_error())
        self.process = self.pi.hProcess
        k32.CloseHandle(self.pi.hThread)
        self.breakpoints = {}
        self.exit_code = None

    def read(self, addr, size):
        buf = ctypes.create_string_buffer(size)
        got = ctypes.c_size_t()
        if not k32.ReadProcessMemory(self.process, ctypes.c_void_p(addr), buf, size, ctypes.byref(got)):
            raise OSError("cannot read 0x%x" % addr)
        return buf.raw

    def write(self, addr, data):
        got = ctypes.c_size_t()
        if not k32.WriteProcessMemory(self.process, ctypes.c_void_p(addr), data, len(data), ctypes.byref(got)):
            raise OSError("cannot write 0x%x" % addr)
        k32.FlushInstructionCache(self.process, ctypes.c_void_p(addr), len(data))

    def u32(self, addr):
        return struct.unpack("<I", self.read(addr, 4))[0]

    def s16(self, addr):
        return struct.unpack("<h", self.read(addr, 2))[0]

    def add_breakpoint(self, addr, callback):
        self.breakpoints[addr] = [None, callback]

    def run(self):
        ev = DEBUG_EVENT()
        rearm = None
        while True:
            k32.WaitForDebugEvent(ctypes.byref(ev), 0xFFFFFFFF)
            status = DBG_CONTINUE
            code = ev.dwDebugEventCode
            if code == EXIT_PROCESS_DEBUG_EVENT:
                self.exit_code = struct.unpack_from("<I", bytes(ev.u), 0)[0]
                k32.ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, status)
                k32.CloseHandle(self.process)
                return
            if code in (CREATE_PROCESS_DEBUG_EVENT, LOAD_DLL_DEBUG_EVENT):
                handle = struct.unpack_from("<Q", bytes(ev.u), 0)[0]  # hFile of both events
                if handle:
                    k32.CloseHandle(W.HANDLE(handle))
            if code == CREATE_PROCESS_DEBUG_EVENT:
                for addr, bp in self.breakpoints.items():
                    bp[0] = self.read(addr, 1)
                    self.write(addr, b"\xcc")
            elif code == EXCEPTION_DEBUG_EVENT:
                exc = struct.unpack_from("<I", bytes(ev.u), 0)[0]
                addr = struct.unpack_from("<Q", bytes(ev.u), 16)[0]
                if exc in BREAKPOINT and addr in self.breakpoints:
                    thread = k32.OpenThread(0x1FFFFF, False, ev.dwThreadId)
                    ctx = WOW64_CONTEXT()
                    ctx.ContextFlags = WOW64_CONTEXT_ALL
                    if not thread or not k32.Wow64GetThreadContext(thread, ctypes.byref(ctx)):
                        k32.TerminateProcess(self.process, 1)
                        raise OSError("cannot read the compiler's thread context: %d" % ctypes.get_last_error())
                    original, callback = self.breakpoints[addr]
                    callback(self)
                    self.write(addr, original)
                    ctx.Eip = addr
                    ctx.EFlags |= 0x100  # trap flag: step the original instruction
                    ok = k32.Wow64SetThreadContext(thread, ctypes.byref(ctx))
                    k32.CloseHandle(thread)
                    if not ok:
                        k32.TerminateProcess(self.process, 1)
                        raise OSError("cannot set the compiler's thread context: %d" % ctypes.get_last_error())
                    rearm = addr
                elif exc in SINGLE_STEP and rearm is not None:
                    self.write(rearm, b"\xcc")
                    rearm = None
                elif exc not in BREAKPOINT:
                    status = DBG_EXCEPTION_NOT_HANDLED
            k32.ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, status)


def calls_emitted(dbg, done):
    """Calls in the function's blocks so far. A block before the current one is
    finished: its count is kept in `done` (block address -> calls)."""
    n = 0
    last = dbg.u32(PCLASTBLOCK)
    block = dbg.u32(PCBASICBLOCKS)
    while block:
        if block in done:
            n += done[block]
        else:
            calls = 0
            pcode = dbg.u32(block + BLOCK_FIRST)
            while pcode:
                if dbg.read(pcode + PCODE_OP, 1)[0] == OP_CALL:
                    calls += 1
                pcode = dbg.u32(pcode)
            if block != last:
                done[block] = calls
            n += calls
        block = dbg.u32(block)
    return n


def trace(source, version):
    source = os.path.normpath(os.path.relpath(os.path.abspath(source), ROOT))
    args = compile_command(source, version)
    compiler = os.path.join(ROOT, args[0])
    rel = os.path.relpath(os.path.dirname(compiler), os.path.join(ROOT, "tools", "mwccarm"))
    with open(compiler, "rb") as f:
        sha1 = hashlib.sha1(f.read()).hexdigest()
    if sha1 != COMPILER_SHA1.get(rel.replace(os.sep, "/")):
        sys.exit("mwcc_blocks: only mwccarm %s is supported (got %s)" % (", ".join(COMPILER_SHA1), rel))
    out_dir = os.path.join(WORK, os.path.dirname(source))
    os.makedirs(out_dir, exist_ok=True)
    cmd, i = [compiler], 1
    while i < len(args):
        if args[i] == "-MD":
            pass
        elif args[i] == "-o":
            cmd += ["-o", out_dir]
            i += 1
        else:
            cmd.append(args[i])
        i += 1

    functions, current, done = [], [], {}

    def on_statement(dbg):
        current.append(str(dbg.s16(dbg.u32(PCLASTBLOCK) + BLOCK_COUNT)))

    def on_split(dbg):
        current.append("|%d|" % calls_emitted(dbg, done))

    def on_colored(dbg):
        # a function colored again (after spilling) has no new statement
        if current:
            functions.append(list(current))
            current.clear()
            done.clear()

    dbg = Debugger(cmd, ROOT)
    dbg.add_breakpoint(BP_STATEMENT, on_statement)
    dbg.add_breakpoint(BP_SPLIT, on_split)
    dbg.add_breakpoint(BP_COLORED, on_colored)
    dbg.run()
    if dbg.exit_code:
        sys.exit("mwcc_blocks: the compiler failed (exit code %d); run ninja to see why" % dbg.exit_code)
    if current:
        functions.append(list(current))
    if not functions:
        sys.exit("mwcc_blocks: no statement traced (breakpoints not reached)")
    return functions


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("source")
    ap.add_argument("--func", type=int, help="only this function (index in the output)")
    ap.add_argument("--version", default="eur")
    a = ap.parse_args()
    if os.name != "nt":
        sys.exit("mwcc_blocks: Windows only (Win32 debugging API)")
    if struct.calcsize("P") != 8:
        sys.exit("mwcc_blocks: needs a 64-bit Python (DEBUG_EVENT layout)")
    load_kernel32()
    for i, statements in enumerate(trace(a.source, a.version)):
        if a.func is None or a.func == i:
            splits = sum(1 for s in statements if s.startswith("|"))
            print("%d (%d splits): %s" % (i, splits, " ".join(statements)))


if __name__ == "__main__":
    main()
