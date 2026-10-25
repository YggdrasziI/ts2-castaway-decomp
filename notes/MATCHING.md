# Matching techniques

Compiler idioms that fixed near-misses in this project, each tied to the unit that
proved it. Techniques from the Wii projects (mwcc PowerPC) do not carry over by
default: add one here only once a unit of this ROM proves it with mwccarm.

## Loads, constants and literal pools

(none yet)

## Registers and stack

- `h = f(h) * 31 + c;` gave `add rd, c, x`; splitting it into `h = f(h) * 31;
  h += c;` gave the original `add rd, x, c` and its register allocation
  (`func_0209a3c4`, `func_0209a32c`, 99.5 % -> 100 %).
- A call result compared with a parameter: `v = f(...); if (v == p)` gives
  `cmp r0, rp`, while `if (f(...) == p)` gives `cmp rp, r0` (`func_0209a418`).
- Members loaded once before a loop (`ldr` of the array and the count ahead of the
  first test) come from copying them to locals; reading them in the loop condition
  reloads the array inside the loop (`unit_02099C0C.cpp`, 83 % -> 100 %).
- A loop whose first test leaves through the function's shared return is
  `for (;;) { ... if (c == 0) break; ... }`; `return` there gives a conditional
  `ldmeq` instead (`func_0209a32c`, 95.5 % -> 99.7 %).

## Inlining and emission order

- C++ static object: write the global and its out-of-line constructor; mwccarm builds
  `__sinit_<file>` in `.init`, its `.ctor` pointer, and a 12-byte local `@<n>` chain
  node in `.bss` just before the object, and calls `__register_global_object(obj,
  dtor, &node)`. The constructor and destructor come out as C1/C2 and D1/D2 copies;
  the dead-stripping link drops the unused one (`notes/COMPILER.md`). Names in
  `symbols.txt`: `_ZN<class>C1Ev`, `_ZN<class>D1Ev`, `__sinit_<file> ... local`,
  `.p__sinit_<file> ... local`, `@<n> ... local` (`unit_02099800.cpp`).

- Global `operator new` and friends: mwccarm mangles them `_Znwm`, `_Znam`, `_ZdlPv`,
  `_ZdaPv` (size_t is `unsigned long`). A `new T(...)` call site is `bl _Znwm`,
  `cmp r0,#0`, then the constructor; `delete p` is `movs`, null exit, destructor,
  `bl _ZdlPv`. A forward to another function compiles to `ldr ip,=f; bx ip` whether
  `f` is in the same file or not, so it says nothing about bounds.
- Calling a not yet decompiled function from C++: declare it `extern "C"` so its
  name stays `func_<addr>` (`unit_02099840.cpp`).

- A field re-read from memory where the source could reuse a register (here
  `heap->list` after the first search) and checks split into separate branches
  point to inline helpers; rewriting the body as `static inline` functions fixed
  the control flow of `func_020993d8` (83 % -> 96 %).
- Local declaration order drives register allocation: permuting the declarations
  with a script took `func_02099678` from 89.9 % to 99.3 % and `func_020993d8` to
  99.8 %. Removing a temporary (`end = a + b; ... rest = end - c` -> `rest = a + b -
  c`) fixed the last swap (100 %).
- Assigning a member from a conditional: `m = c ? a : b;` (or `if` / `else` on the
  parameter before the store) keeps the result in the parameter register and stores
  each member alone; computing it first and storing both members after gave a second
  register and an `stmia` (`unit_0209A11C.cpp`, 53.75 % -> 100 %).
- `if (x != 0) { ... } else { return -1; }` puts the failure path after the body,
  where `if (x == 0) return -1;` gives a conditional `mvneq`.

## Data layout

- `.bss` order of file statics is not the declaration order: with all statics in
  one run of declarations, k ints come out as `a(k-2) ... a1 a0 a(k-1)`; a function
  definition between declarations starts a new run, and arrays and compiler nodes
  (`@<n>`) change the pattern. Fit the order with a script that rewrites the
  declarations, compiles, and compares symbol offsets (`unit_02099870.cpp`).
- dsd gives one `data_<addr>` to a run of adjacent statics the code reaches through
  one base; add a `local` symbol per static to `symbols.txt` so that objdiff pairs
  them (`.bss` 99.96 % -> 100 %).
- `(int)(a - b) - c` with `a - b` unsigned keeps the runtime `add` and both `sub`
  (`(u32)x + 0x4000 - y - 0x1400` folds `0x4000 - 0x1400`).

(none yet)

## Control flow

(none yet)

## ARM / Thumb

(none yet)

## Unsolved patterns

(none yet)
