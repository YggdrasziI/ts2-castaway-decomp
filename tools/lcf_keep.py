#!/usr/bin/env python3
"""Run `dsd lcf`, then keep `.exception` alive in the dead-stripping link.

The link strips unused code (`-dead`), as the original link did: mwccarm emits the
base-object and complete-object variants of every constructor and destructor
(C1/C2, D1/D2), and the ROM holds only the one that is used. dsd's KEEP_SECTION
lists `.init`, `.ctor` and `.exceptix`, but not `.exception`, whose records nothing
refers to by relocation, so the linker would drop them.

Usage (from the ninja lcf rule):
  python tools/lcf_keep.py <lcf file> <dsd command and arguments...>
"""

import subprocess
import sys

KEEP = ".exception"


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    lcf_path = sys.argv[1]
    res = subprocess.run(sys.argv[2:])
    if res.returncode != 0:
        return res.returncode

    with open(lcf_path, encoding="utf-8") as f:
        lcf = f.read()
    if f"({KEEP})" not in lcf:
        return 0
    head, sep, rest = lcf.partition("KEEP_SECTION {")
    if not sep:
        sys.exit(f"{lcf_path}: no KEEP_SECTION block")
    body, end, tail = rest.partition("}")
    names = [name.strip() for name in body.split(",") if name.strip()]
    if KEEP not in names:
        names.append(KEEP)
    body = "\n" + ",\n".join(f"    {name}" for name in names) + "\n"
    with open(lcf_path, "w", encoding="utf-8", newline="\n") as f:
        f.write(head + sep + body + end + tail)
    return 0


if __name__ == "__main__":
    sys.exit(main())
