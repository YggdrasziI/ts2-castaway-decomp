#!/usr/bin/env python3
"""Compile C/C++ files with several mwccarm versions and look for their functions in
this ROM's code.

Every function of each compiled object is searched in the extracted ARM9 main, ITCM
and DTCM modules, with the words touched by a relocation masked (calls, pointers),
so a hit means the same instructions were generated: it gives the function's address
(a library signature) and which compilers produce it. A function found at one address
only is reported with that address; several addresses mean the bytes are not
distinctive (often tiny functions).

Usage:
  python tools/compiler_sweep.py <file.c> [<file.c> ...]
      [--compilers 2.0/sp1p5,2.0/sp2p3 | all]   (default: all of tools/mwccarm)
      [--include <dir>] ...                      (extra include dirs)
      [--ref <reference project root>]           (adds its include/ and libs/*/include)
      [--flags "<mwccarm flags>"]                (default: DEFAULT_FLAGS below)
      [--min-size 12]                            (smaller functions are not reported)
      [--json out.json]                          (machine-readable results)

Example (NitroSDK OS sources of twewy, every compiler):
  python tools/compiler_sweep.py --ref E:/Projets/Github/Decomp/DS/twewy \\
      E:/Projets/Github/Decomp/DS/twewy/libs/nitro/src/os/*.c
"""

import argparse
import glob
import json
import os
import struct
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MWCC_ROOT = os.path.join(ROOT, "tools", "mwccarm")
EXTRACT = os.path.join(ROOT, "extract", "eur", "arm9")

# twewy's COMMON_CC_FLAGS without the options some old compilers reject; a sweep
# compares compilers, the project's real flags are in tools/configure.py.
DEFAULT_FLAGS = ("-O4,p -enum int -char signed -proc arm946e -gccext,on -fp soft "
                 "-inline noauto -RTTI off -Cpp_exceptions off -interworking -w off "
                 "-gccinc -nolink -msgstyle gcc")

# ELF relocation types that change a whole word (ARM) or a BL pair (Thumb)
R_ARM_PC24, R_ARM_ABS32, R_ARM_THM_CALL = 1, 2, 10
R_ARM_CALL, R_ARM_JUMP24 = 28, 29


def modules():
    """[(name, base address, bytes)] of the extracted ARM9 modules."""
    out = []
    for name, yaml_name in (("main", "arm9.yaml"), ("itcm", "itcm.yaml"), ("dtcm", "dtcm.yaml")):
        bin_path = os.path.join(EXTRACT, yaml_name.replace(".yaml", ".bin"))
        with open(os.path.join(EXTRACT, yaml_name), encoding="utf-8") as f:
            base = next(int(line.split(":")[1]) for line in f if line.startswith("base_address"))
        with open(bin_path, "rb") as f:
            out.append((name, base, f.read()))
    return out


def read_elf(path):
    """{name: (bytes, mask)} for each function of an ELF32 relocatable object."""
    data = open(path, "rb").read()
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    sections = []
    for i in range(shnum):
        sections.append(struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize))

    def name_at(strtab, off):
        start = sections[strtab][4] + off
        return data[start:data.index(b"\0", start)].decode("latin-1")

    def sec_name(i):
        return name_at(shstrndx, sections[i][0])

    contents = {i: bytearray(data[s[4]:s[4] + s[5]]) for i, s in enumerate(sections) if s[1] == 1}
    masks = {i: bytearray(b"\xff" * len(c)) for i, c in contents.items()}
    symbols = []
    for s in sections:
        if s[1] == 2:  # SHT_SYMTAB
            for off in range(s[4], s[4] + s[5], 16):
                st_name, value, size, info, _, shndx = struct.unpack_from("<IIIBBH", data, off)
                if info & 0xF == 2 and shndx in contents:  # STT_FUNC
                    symbols.append((name_at(s[6], st_name), shndx, value, size))
    for s in sections:
        if s[1] == 9 and s[7] in masks:  # SHT_REL, applies to section sh_info
            mask = masks[s[7]]
            for off in range(s[4], s[4] + s[5], 8):
                r_off, r_info = struct.unpack_from("<II", data, off)
                width = 4
                if r_info & 0xFF in (R_ARM_PC24, R_ARM_ABS32, R_ARM_CALL, R_ARM_JUMP24,
                                     R_ARM_THM_CALL):
                    mask[r_off:r_off + width] = b"\0" * width
    funcs = {}
    for name, shndx, value, size in symbols:
        start = value & ~1
        if size == 0 or not sec_name(shndx).startswith(".text"):
            continue
        code = bytes(contents[shndx][start:start + size])
        mask = bytes(masks[shndx][start:start + size])
        funcs[name] = (code, mask)
    return funcs


def find(code, mask, mods):
    """Addresses where code matches, ignoring the bytes whose mask is 0."""
    # Anchor on the longest run of unmasked bytes, then check the whole function.
    best, run_start = (0, 0), None
    for i, m in enumerate(mask + b"\0"):
        if m and run_start is None:
            run_start = i
        elif not m and run_start is not None:
            if i - run_start > best[1] - best[0]:
                best = (run_start, i)
            run_start = None
    a, b = best
    if b - a < 4:
        return []
    anchor = code[a:b]
    hits = []
    for _, base, blob in mods:
        pos = blob.find(anchor)
        while pos != -1:
            start = pos - a
            if start >= 0 and start + len(code) <= len(blob) and start % 2 == 0:
                window = blob[start:start + len(code)]
                if all(m == 0 or x == y for x, y, m in zip(window, code, mask)):
                    hits.append(base + start)
            pos = blob.find(anchor, pos + 1)
    return sorted(set(hits))


def compilers(arg):
    if arg != "all":
        return arg.split(",")
    found = []
    for family in sorted(os.listdir(MWCC_ROOT)):
        for version in sorted(os.listdir(os.path.join(MWCC_ROOT, family))):
            if os.path.isfile(os.path.join(MWCC_ROOT, family, version, "mwccarm.exe")):
                found.append(f"{family}/{version}")
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("sources", nargs="+")
    parser.add_argument("--compilers", default="all")
    parser.add_argument("--include", action="append", default=[])
    parser.add_argument("--ref", help="reference project root")
    parser.add_argument("--flags", default=DEFAULT_FLAGS)
    parser.add_argument("--define", action="append", default=[], help="extra -d defines")
    parser.add_argument("--min-size", type=int, default=12)
    parser.add_argument("--json")
    args = parser.parse_args()

    includes = list(args.include)
    if args.ref:
        includes.append(os.path.join(args.ref, "include"))
        includes += glob.glob(os.path.join(args.ref, "libs", "*", "include"))
    sources = [p for s in args.sources for p in (glob.glob(s) or [s])]
    mods = modules()
    versions = compilers(args.compilers)
    results = {}  # source -> function -> compiler -> [addresses] or None (compile error)
    with tempfile.TemporaryDirectory() as tmp:
        for src in sources:
            lang = "-lang=c++" if src.endswith(".cpp") else "-lang=c99"
            per_func = results.setdefault(src, {})
            for ver in versions:
                obj = os.path.join(tmp, "out.o")
                if os.path.exists(obj):
                    os.remove(obj)
                cmd = [os.path.join(MWCC_ROOT, *ver.split("/"), "mwccarm.exe"),
                       *args.flags.split(), lang]
                for d in args.define:
                    cmd += ["-d", d]
                for inc in includes:
                    cmd += ["-i", inc]
                cmd += ["-c", src, "-o", obj]
                out = subprocess.run(cmd, capture_output=True, text=True)
                if out.returncode != 0 or not os.path.exists(obj):
                    per_func.setdefault("<compile>", {})[ver] = None
                    continue
                for name, (code, mask) in read_elf(obj).items():
                    if len(code) < args.min_size:
                        continue
                    per_func.setdefault(name, {})[ver] = find(code, mask, mods)

    totals = {ver: 0 for ver in versions}
    for src, funcs in results.items():
        print(f"== {os.path.basename(src)}")
        failed = [v for v, r in funcs.get("<compile>", {}).items() if r is None]
        if failed:
            print(f"   compile failed with: {', '.join(failed)}")
        for name, per_ver in sorted(funcs.items()):
            if name == "<compile>":
                continue
            unique = {v: h[0] for v, h in per_ver.items() if h and len(h) == 1}
            multi = {v for v, h in per_ver.items() if h and len(h) > 1}
            for v in unique:
                totals[v] += 1
            if unique:
                addrs = sorted(set(unique.values()))
                print(f"   {name}: {', '.join(f'0x{a:08X}' for a in addrs)} "
                      f"with {', '.join(sorted(unique))}")
            elif multi:
                print(f"   {name}: several addresses with {', '.join(sorted(multi))}")
    print("== unique matches per compiler")
    for ver, n in totals.items():
        print(f"   {ver}: {n}")
    if args.json:
        with open(args.json, "w", encoding="utf-8") as f:
            json.dump({src: {fn: {v: h for v, h in pv.items()} for fn, pv in funcs.items()}
                       for src, funcs in results.items()}, f, indent=1)


if __name__ == "__main__":
    main()
