#!/usr/bin/env python3
"""Search source forms of one function until its compiled bytes equal the original.

mwccarm's register allocation depends on declaration order, scopes and copies in ways that
cannot be predicted by hand, but a unit compiles in a fraction of a second, so a random
search is practical. Variants live in a temporary directory: the repository is never
written. A result counts only when the bytes equal the target (`score` 0), and then
`report_diff.py` and `ninja` remain the proof. The output form is a compiler fact, not
evidence of the original source.

  python tools/permute.py <unit> <symbol> [--seconds N] [--workers N] [--out DIR]
  python tools/permute.py src/game/unit_02093648 _ZN11Unk0209364813func_02093a9cEi

With 0 reached, mutations that are not needed are reverted and the function body is written
to <out>/<symbol>.txt, its first line being the offset-free signature key.
"""
import argparse
import difflib
import os
import random
import re
import struct
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor

CC = r"tools\mwccarm\2.0\sp1p5\mwccarm.exe"
FLAGS = ("-O4,p -enum int -char signed -proc arm946e -gccext,on -fp soft -inline noauto -RTTI off "
         "-interworking -w off -sym on -gccinc -nolink -msgstyle gcc -enc SJIS -str reuse "
         "-Cpp_exceptions off -avoid_byte strb -i include -i libs/c/include -i libs/cpp/include "
         "-i libs/nitro/include -i libs/runtime/include -lang=c++ -d REGION_EUR").split()


def elf_func(path, name):
    """Return (bytes, set of reloc offsets) of a function symbol."""
    b = open(path, "rb").read()
    shoff = struct.unpack_from("<I", b, 32)[0]
    shes, shnum = struct.unpack_from("<HH", b, 46)
    S = [struct.unpack_from("<10I", b, shoff + i * shes) for i in range(shnum)]
    # name, type, flags, addr, offset, size, link, info, align, entsize
    for s in S:
        if s[1] == 2:
            strs = S[s[6]]
            for o in range(s[4], s[4] + s[5], 16):
                n, val, size, info, oth, shndx = struct.unpack_from("<IIIBBH", b, o)
                e = b.index(b"\0", strs[4] + n)
                if b[strs[4] + n:e].decode("latin1") == name and shndx and shndx < shnum:
                    sec = S[shndx]
                    data = b[sec[4] + val : sec[4] + val + size]
                    rel = set()
                    for r in S:
                        if r[1] in (4, 9) and r[7] == shndx:
                            for q in range(r[4], r[4] + r[5], r[9]):
                                off = struct.unpack_from("<I", b, q)[0]
                                if val <= off < val + size:
                                    rel.add(off - val)
                    return data, rel
    return None, None


def score(path, name, tgt, trel):
    d, rel = elf_func(path, name)
    if d is None:
        return 10**6
    if len(d) != len(tgt):
        return 5000 + abs(len(d) - len(tgt))
    n = 0
    for i in range(0, len(tgt), 4):
        if i in trel or i in rel:
            continue
        if d[i : i + 4] != tgt[i : i + 4]:
            n += 1
    return n


DECL = re.compile(r"^(\s*)((?:const\s+)?(?:unsigned\s+)?[A-Za-z_]\w*(?:\s*\*+\s*|\s+)(?:const\s+)?)([a-z_A-Z]\w*)(\s*=\s*(.*))?;\s*$")
KW = {"return", "goto", "delete", "else", "case", "break", "continue", "new"}


def is_decl(l):
    m = DECL.match(l)
    return m if m and m.group(2).split()[0] not in KW else None


def block_end(L, i):
    return not L[i].rstrip().endswith("{") and not L[i].strip().startswith("}")


def mutate(L):
    L = list(L)
    k = random.random()
    idx = list(range(len(L)))
    if k < 0.28:  # swap adjacent simple statements
        c = [i for i in idx[:-1] if block_end(L, i) and block_end(L, i + 1) and L[i].strip().endswith(";") and L[i + 1].strip().endswith(";")]
        if c:
            i = random.choice(c)
            L[i], L[i + 1] = L[i + 1], L[i]
    elif k < 0.48:  # move a declaration without initializer anywhere above its use
        c = [i for i in idx if is_decl(L[i]) and not is_decl(L[i]).group(4)]
        if c:
            i = random.choice(c)
            l = L.pop(i)
            L.insert(random.randrange(0, min(i + 3, len(L))), l)
    elif k < 0.66:  # split `T x = e;` into a declaration at the top and an assignment
        c = [i for i in idx if is_decl(L[i]) and is_decl(L[i]).group(4)]
        if c:
            i = random.choice(c)
            m = is_decl(L[i])
            L[i] = "%s%s = %s;" % (m.group(1), m.group(3), m.group(5))
            L.insert(random.randrange(0, 4) if len(L) > 4 else 0, "    %s%s;" % (m.group(2).replace("const ", ""), m.group(3)))
    elif k < 0.76:  # add or drop const on an initialised local
        c = [i for i in idx if is_decl(L[i]) and is_decl(L[i]).group(4)]
        if c:
            i = random.choice(c)
            L[i] = L[i].replace("const ", "", 1) if "const " in L[i] else re.sub(r"^(\s*)", r"\1const ", L[i], count=1)
    elif k < 0.88:  # commute an operator
        c = [i for i in idx if re.search(r"\S+ (==|!=|\+|\*|&|\|) \S+", L[i])]
        if c:
            i = random.choice(c)
            ms = list(re.finditer(r"([\w\->\.\[\]]+) (==|!=|\+|\*|&|\|) ([\w\->\.\[\]]+)", L[i]))
            if ms:
                m = random.choice(ms)
                L[i] = L[i][: m.start()] + m.group(3) + " " + m.group(2) + " " + m.group(1) + L[i][m.end() :]
    elif k < 0.95:  # a copy of a local: `T y = x;` right after its declaration, then use y
        c = [i for i in idx if is_decl(L[i]) and is_decl(L[i]).group(4)]
        if c:
            i = random.choice(c)
            m = is_decl(L[i])
            n = m.group(3)
            nn = n + "_"
            if nn not in "\n".join(L):
                L.insert(i + 1, "%s%s%s = %s;" % (m.group(1), m.group(2), nn, n))
                for j in range(i + 2, len(L)):
                    if random.random() < 0.7:
                        L[j] = re.sub(r"\b%s\b" % n, nn, L[j])
    else:  # compound assignment split `x += e;` <-> `x = x + e;`
        c = [i for i in idx if re.search(r"^\s*\w+ [-+|&]= ", L[i])]
        if c:
            i = random.choice(c)
            m = re.match(r"^(\s*)(\w+) ([-+|&])= (.*);", L[i])
            if m:
                L[i] = "%s%s = %s %s %s;" % (m.group(1), m.group(2), m.group(2), m.group(3), m.group(4))
    return L



def locate(symbol):
    """Regex for the definition of a mangled or plain symbol."""
    m = re.match(r"_ZNK?(\d+)", symbol)
    if not m:
        return r"^[^\n;#]*\b%s\([^;{]*\{\n" % re.escape(symbol)
    p = m.end(1)
    n = int(m.group(1))
    cls = symbol[p : p + n]
    rest = symbol[p + n :]
    c = re.match(r"(C|D)[0-9]", rest)
    if c:
        name = cls if c.group(1) == "C" else "~" + cls
    else:
        q = re.match(r"(\d+)", rest)
        if not q:
            return None
        name = rest[q.end() : q.end() + int(q.group(1))]
    return r"^[^\n;#]*\b%s::%s\([^;{]*\{\n" % (cls, re.escape(name))


class Search:
    def __init__(self, pre, post, srcdir, symbol, tgt, trel, tmp, workers):
        self.pre, self.post, self.srcdir, self.symbol = pre, post, srcdir, symbol
        self.tgt, self.trel, self.tmp = tgt, trel, tmp
        self.ex = ThreadPoolExecutor(workers)
        self.workers = workers

    def run(self, i, lines):
        c = os.path.join(self.tmp, "v%d.cpp" % i)
        ob = os.path.join(self.tmp, "v%d.o" % i)
        with open(c, "w", encoding="utf-8", newline="\n") as f:
            f.write(self.pre + "\n".join(lines) + "\n" + self.post)
        if os.path.exists(ob):
            os.remove(ob)
        r = subprocess.run([CC] + FLAGS + ["-i", self.srcdir, "-c", c, "-o", ob], capture_output=True)
        if r.returncode or not os.path.exists(ob):
            return 10**6
        return score(ob, self.symbol, self.tgt, self.trel)

    def batch(self, C):
        return list(self.ex.map(self.run, range(len(C)), C))


def cleanup(s, body, L):
    """Revert every difference from the original body that the match does not need."""
    changed = True
    while changed:
        changed = False
        ops = [o for o in difflib.SequenceMatcher(None, body, L, autojunk=False).get_opcodes() if o[0] != "equal"]
        C = [L[: o[3]] + body[o[1] : o[2]] + L[o[4] :] for o in ops]
        for k in range(0, len(C), s.workers):
            part = C[k : k + s.workers]
            R = s.batch(part)
            ok = [x for r, x in zip(R, part) if r == 0]
            if ok:
                L = min(ok, key=lambda x: sum(a != b for a, b in zip(x, body)))
                changed = True
                break
    return L


def main():
    a = argparse.ArgumentParser()
    a.add_argument("unit")
    a.add_argument("symbol")
    a.add_argument("--seconds", type=int, default=60)
    a.add_argument("--workers", type=int, default=16)
    a.add_argument("--out", default=None)
    o = a.parse_args()
    src = o.unit + ".cpp"
    target = os.path.join("build", "eur", "delinks", o.unit.replace("/", os.sep) + ".o")
    tgt, trel = elf_func(target, o.symbol)
    if tgt is None:
        sys.exit("symbol not in target: " + o.symbol)
    text = open(src, newline="", encoding="utf-8").read().replace("\r\n", "\n")
    rx = locate(o.symbol)
    m = re.search(rx, text, re.M) if rx else None
    if not m:
        sys.exit("definition not found: " + o.symbol)
    s0 = m.end()
    e = text.index("\n}\n", s0) + 1
    pre, body, post = text[:s0], text[s0:e].split("\n")[:-1], text[e:]
    with tempfile.TemporaryDirectory(prefix="perm_") as tmp:
        s = Search(pre, post, os.path.dirname(os.path.abspath(src)), o.symbol, tgt, trel, tmp, o.workers)
        best = cur = s.run(0, body)
        print("start", cur, "of", len(tgt) // 4, flush=True)
        bestL = curL = body
        t0 = time.time()
        n = 0
        while time.time() - t0 < o.seconds and best > 0:
            C = []
            for _ in range(o.workers):
                L = curL
                for _ in range(random.choice((1, 1, 2, 3))):
                    L = mutate(L)
                C.append(L)
            R = s.batch(C)
            n += len(C)
            v, L = min(zip(R, C), key=lambda x: x[0])
            if v < 5000 and (v <= cur or random.random() < 0.015):
                cur, curL = v, L
            if v < best:
                best, bestL = v, L
                print(round(time.time() - t0), n, "best", best, flush=True)
            if cur > best + 6:
                cur, curL = best, bestL
        print("done", n, "variants, best", best, flush=True)
        if best == 0 and o.out:
            bestL = cleanup(s, body, bestL)
            os.makedirs(o.out, exist_ok=True)
            with open(os.path.join(o.out, o.symbol + ".txt"), "w", encoding="utf-8", newline="\n") as f:
                f.write(src + "\n" + m.group(0).rstrip("\n") + "\n" + "\n".join(bestL) + "\n")
        s.ex.shutdown()
    return 0 if best == 0 else 1


if __name__ == "__main__":
    main()
