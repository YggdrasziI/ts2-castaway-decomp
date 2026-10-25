#!/usr/bin/env python3
"""List small functions of the game code region that are not delinked yet.

ARM mwccarm units have no __sinit end marker (static initializers live in .init), so
this lists functions instead of units: for each function of the game region not
covered by a file in delinks.txt, its size, the calls it makes and its callers (from
the dsd relocs.txt; direct calls only, calls through vtables or function pointers are
not counted). Call-tree leaves (no calls) come first, then by size. A
function whose callers are all close to it most likely shares their unit.

Usage:
  python tools/unit_candidates.py              # 30 smallest leaves, then other functions
  python tools/unit_candidates.py -n 50 --max-calls 2
  python tools/unit_candidates.py --start 0x02040000 --end 0x02050000
"""

import argparse
import bisect
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# Game code region (notes/SPLITS.md): after main, before NitroSDK (first SDK function
# found by compiler_sweep at 0x0207AE98). Approximate until the region map is done.
GAME_START, GAME_END = 0x02000C68, 0x0207A000


def read_symbols(path):
    funcs = []
    for line in open(path, encoding="utf-8"):
        m = re.match(r"(\S+) kind:function\((arm|thumb),size=(0x[0-9a-f]+)\S*\) addr:(0x[0-9a-f]+)", line)
        if m:
            funcs.append((int(m.group(4), 16), int(m.group(3), 16), m.group(1), m.group(2)))
    return sorted(funcs)


def read_calls(path):
    calls = []
    for line in open(path, encoding="utf-8"):
        m = re.match(r"from:(0x[0-9a-f]+) kind:(arm_call|thumb_call)\S* to:(0x[0-9a-f]+)", line)
        if m:
            calls.append((int(m.group(1), 16), int(m.group(3), 16)))
    return calls


def read_delinked(path):
    """[start, end) ranges of every .text section of a file block in delinks.txt."""
    ranges, in_files = [], False
    for line in open(path, encoding="utf-8"):
        if not line.strip():
            in_files = True
            continue
        m = re.match(r"\s+\.text\s+start:(0x[0-9a-f]+) end:(0x[0-9a-f]+)", line)
        if in_files and m:
            ranges.append((int(m.group(1), 16), int(m.group(2), 16)))
    return ranges


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--version", default="eur")
    parser.add_argument("-n", type=int, default=30, help="rows to print")
    parser.add_argument("--max-calls", type=int, default=0, help="most outgoing calls (default 0: leaves)")
    parser.add_argument("--min-size", type=lambda x: int(x, 0), default=8,
                        help="smallest size (default 8: skips 4-byte 'bx lr' stubs)")
    parser.add_argument("--start", type=lambda x: int(x, 0), default=GAME_START)
    parser.add_argument("--end", type=lambda x: int(x, 0), default=GAME_END)
    args = parser.parse_args()

    cfg = os.path.join(ROOT, "config", args.version, "arm9")
    funcs = read_symbols(os.path.join(cfg, "symbols.txt"))
    calls = read_calls(os.path.join(cfg, "relocs.txt"))
    delinked = read_delinked(os.path.join(cfg, "delinks.txt"))

    starts = [f[0] for f in funcs]
    out_calls, callers = {}, {}
    for src, dst in calls:
        i = bisect.bisect_right(starts, src) - 1
        if i >= 0 and src < funcs[i][0] + funcs[i][1]:
            out_calls[funcs[i][0]] = out_calls.get(funcs[i][0], 0) + 1
        callers.setdefault(dst, []).append(src)

    rows = []
    for addr, size, name, mode in funcs:
        if not args.start <= addr < args.end or size < args.min_size:
            continue
        if any(s <= addr < e for s, e in delinked):
            continue
        n_calls = out_calls.get(addr, 0)
        if n_calls > args.max_calls:
            continue
        who = callers.get(addr, [])
        near = sum(1 for c in who if abs(c - addr) < 0x400)
        rows.append((n_calls, size, addr, name, mode, len(who), near))
    rows.sort()
    print(f"{'address':<11} {'size':>6} {'mode':<5} {'calls':>5} {'callers':>7} {'near':>4}  name")
    for n_calls, size, addr, name, mode, n_callers, near in rows[:args.n]:
        print(f"0x{addr:08X} {size:>#6x} {mode:<5} {n_calls:>5} {n_callers:>7} {near:>4}  {name}")
    print(f"{len(rows)} functions (calls <= {args.max_calls}) in 0x{args.start:08X}-0x{args.end:08X}, "
          f"not delinked; 'near' = callers within 0x400 bytes")


if __name__ == "__main__":
    main()
