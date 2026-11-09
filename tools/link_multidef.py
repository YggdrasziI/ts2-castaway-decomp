#!/usr/bin/env python3
"""Run the linker with every copy of a multiply-definable object made
multiply-definable.

mwccarm emits the objects that every file using them may define (a base class vtable
emitted with a derived constructor, an inline virtual destructor) with ELF symbol
binding 13, and the linker keeps the first copy in link order. While the first copy
is still in a delinked (assembly) object, dsd gives it a global binding, and a
compiled copy of a `complete` file then clashes with it ("Multiply-defined").

The same holds for a kept copy written as a plain definition so that it lands where
the original has it (an inline function emitted by its first user): it is global,
and a later file emitting the inline copy clashes with it.

This script reads the linker's objects file, collects the names that the compiled
objects define with binding 13, and links copies (under <objects file dir>/multidef/)
of the objects that define one of these names, global or weak and no larger than the
compiled copy, with the binding set to 13. The link then keeps the first copy as the original did;
the ROM checksum and `dsd check symbols` still verify the result. Other objects are
linked as they are.

Usage (from the ninja mwld rule):
  python tools/link_multidef.py <objects file> <linker command and arguments...>
The argument `@<objects file>` of the linker command is replaced by the new list,
<objects file dir>/objects_multidef.txt.
"""

import os
import struct
import subprocess
import sys

MULTIDEF = 13
STB_GLOBAL, STB_WEAK = 1, 2
SHT_SYMTAB = 2
SHN_LORESERVE = 0xFF00  # ABS, COMMON and the like: not a section definition


def symbols(data):
    """Yield (offset of the entry, name, size, binding, section index) of each symbol of
    an ELF32 LE object; nothing for another kind of file."""
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        return
    (shoff,) = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum = struct.unpack_from("<HH", data, 0x2E)
    sections = [struct.unpack_from("<10I", data, shoff + i * shentsize) for i in range(shnum)]
    for sh in sections:
        if sh[1] != SHT_SYMTAB:
            continue
        strtab = sections[sh[6]][4]
        entsize = sh[9] or 16
        for k in range(sh[5] // entsize):
            off = sh[4] + k * entsize
            name, _, size, info, _, shndx = struct.unpack_from("<IIIBBH", data, off)
            end = data.index(b"\0", strtab + name)
            yield off, data[strtab + name : end].decode("latin-1"), size, info >> 4, shndx


def defined(shndx):
    return 0 < shndx < SHN_LORESERVE


def read_objects(path):
    with open(path, encoding="utf-8") as f:
        return [line.strip().strip('"') for line in f if line.strip()]


def key(path):
    """A path compared with another: one separator, case folded on Windows."""
    return os.path.normcase(os.path.normpath(path.replace("\\", "/")))


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    objects_file, cmd = sys.argv[1], sys.argv[2:]
    at = "@" + objects_file
    if at not in cmd:
        sys.exit("link_multidef.py: %s not in the linker command" % at)
    root = os.path.dirname(key(objects_file))
    delinks = os.path.join(root, "delinks") + os.sep
    objects = read_objects(objects_file)
    if not any(key(p).startswith(delinks) for p in objects):
        print("link_multidef.py: warning: no object of %s is under %s" % (objects_file, delinks), file=sys.stderr)

    # name -> size of the compiled multiply-definable copies
    sizes = {}
    for p in objects:
        if not key(p).startswith(delinks):
            with open(p, "rb") as f:
                data = f.read()
            for _, n, size, b, shndx in symbols(data):
                if b == MULTIDEF and defined(shndx):
                    sizes.setdefault(n, size)

    linked = []
    for p in objects:
        with open(p, "rb") as f:
            data = bytearray(f.read())
        # Only global or weak definitions no larger than the compiled copy (dsd ends a
        # delinked symbol at the next label, such as the vtable address after its header).
        hits = [off for off, n, size, b, shndx in symbols(data)
                if b in (STB_GLOBAL, STB_WEAK) and defined(shndx) and n in sizes and size <= sizes[n]]
        if hits:
            for off in hits:
                data[off + 12] = (MULTIDEF << 4) | (data[off + 12] & 0xF)
            k = key(p)
            rel = os.path.join("delinks", k[len(delinks):]) if k.startswith(delinks) else os.path.relpath(k, root)
            q = os.path.join(root, "multidef", rel)
            os.makedirs(os.path.dirname(q), exist_ok=True)
            with open(q, "wb") as f:
                f.write(data)
            p = q
        linked.append(p)

    new_file = os.path.join(root, "objects_multidef.txt")
    with open(new_file, "w", encoding="utf-8", newline="\n") as f:
        f.writelines('"%s"\n' % p for p in linked)
    cmd = ["@" + new_file if a == at else a for a in cmd]
    return subprocess.run(cmd).returncode


if __name__ == "__main__":
    sys.exit(main())
