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
- `p + i * 12` with `i` a `short` gives `smlabb`; with an `int` it gives `mla`. A
  parameter passed on without `lsl` / `asr` is an `int` (`unit_02099C78.cpp`).
- Fields read into locals before the stores of a stack struct (`short a = op->a;
  short b = op->b;`) keep the original load order (`func_02099d04`, 97.4 % -> 100 %).
- A constructor that ends with a chain of tests: `if (!x) return;` for the last one
  too, not `if (x) { ... }` (`moveq r0, this` / `movne r0, this` in the original).
- `a + b` where both sides are products: mwccarm emits the right-hand product
  first. Writing the terms in the reverse order fixed `func_020991b8` (45.7 % ->
  100 %).
- `return a && b && c;` for a bool builds flag registers; `if (a && b && c) return
  true; return false;` gives the original branch chain and `ldmgt` exit
  (`func_02098c3c`, 39 % -> 100 %).
- A default set first and overridden (`s = k; if (c) s = f();`) moves the `mov`
  of the default before the test; `if (!c) s = k; else s = f();` puts it after the
  compare, as in the original (`func_02098934`, 94.3 % -> 99.3 %).
- Sums of four products: try all 24 term orders with a script; one order matched
  the loads each time (`func_020988f4`, `func_02098a5c`).
- A sum of 64-bit fixed-point products truncated once (`adds` without `adc`) is
  `(int)((((s64)a * b) >> 12) + ...)`; a sum of per-term `int` casts gives `add`
  (`func_02097c6c`, `func_02097d38`).
- Stack slots of local objects follow their declaration order: declare them so that
  the offsets match (`func_02097f1c`).
- Results that the original computes in reverse order before one constructor call
  (z, y, x, then `stm`) come from locals assigned in that order and passed to the
  constructor (`func_020983ac`, 91.7 % -> 100 %).
- An `if (c) { x = 1; return; } x++;` tail gives conditional `ldrle` / `addle`;
  `if (!c) x++; else x = 1;` gives the original early `ldmgt` exit (`func_02097464`).
- A loop over a global array whose original keeps the counter in a lower register
  than the element pointer is written with an explicit pointer, set before the loop
  and incremented after the body; `array[i].field` and `&array[i]` swap the two
  registers (`func_02097100`, 98.5 % -> 100 %).
- Two tests of the same array element (`==`, then `<`) compiled into one `cmp`
  with the operands of the first test: read the element into a local first; the
  original then compares twice (`func_02095ef8`, 95.4 % -> 100 %).
- `if (c) return x; return 0;` puts the conditional `moveq r0, #0` last; the
  original's `moveq` before `ldrne` / `addne` comes from
  `if (!c) return 0; return x;` (`func_0209526c`, 88.2 % -> 100 %).
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
- `delete p` / `delete[] p` on a type with a trivial destructor is a bare
  `bl _ZdlPv` / `bl _ZdaPv` without a null test; a `cmp r0,#0; beq` before the call
  means the source tested the pointer itself (`if (p != 0) delete[] p;`,
  `unit_02094824.cpp`, 80 % -> 100 %).
- `if` / `else` order shows in the conditional loads: the branch written first
  becomes the conditional (`ldrge ...; bge`) block. `if (tag < 0) {B} else {A}`
  gave the original `ldrge` A loads; `if (tag >= 0) {A} else {B}` gave `ldrlt` B
  loads. Wrapping the body in `if (e != 0) { ... } return 0;` also moved the null
  exit to the end (`func_02094d4c`, 89 % -> 100 %).
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

- A dsd symbol inside a static object (here `data_020c806c`, the object + 4 that
  one function returns) makes `.bss` score 3 %: drop the symbol and write the
  relocation as `to:<object> add:0x4` (`unit_02097434.cpp`).
- A class with user-declared constructors is copied member by member
  (`ldr` / `str` pairs); deriving it from a plain struct that holds the members
  gives the block copy (`ldm` / `stm`) of the original (`unit_02098E70.cpp`, 0 % ->
  100 % for the copying functions).
- Vtables: mwccarm emits `_ZTV<class>` with two zero words (offset to top, no RTTI
  with `-RTTI off`) before the slots, and the object points 8 bytes in. Pure virtual
  slots are zero; a virtual destructor takes two slots (D1, then the deleting D0). In
  `symbols.txt` the vtable symbol goes at the start, and the constructor's load in
  `relocs.txt` becomes `to:<_ZTV> add:0x8` (`unit_02099C78.cpp`).
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
- mwccarm lays out a file's `.bss` objects by increasing size (equal sizes keep a
  compiler-chosen order), whatever the declaration order. A larger object below a
  smaller one in the original means they come from different files
  (`unit_020973BC.cpp`). To order equal-size objects, try the declaration
  permutations (`unit_02096A74.cpp`: a word reached at +4 from `data_020c7f74` is
  its own 4-byte object, declared first).

## C++ classes

- mwccarm emits a C1 and a C2 copy of every constructor (and D1 / D2 of a
  destructor); a derived class calls its base through C2 and D2, and the linker
  drops the copies nobody calls. Two identical constructors in a row in the original
  are such a pair. Name the base functions the derived code calls `...C2E...` /
  `...D2Ev` (`unit_02096348.cpp`).
- An implicit virtual destructor comes out of the link as D0 then D1; an explicit
  `~Class() {}` defined at the end of the file gives D1 then D0, as in the original
  (`unit_02096348.cpp`).
- A class with a second base: its overrides of the second base's functions get new
  slots in the primary vtable in the class's declaration order, and the second
  vtable lists `_ZThn<offset>_` thunks in the interface's order; the thunks are
  emitted after the destructors in reverse slot order. Declaring the overrides in
  the primary-vtable order and the interface in the thunk order matches both
  (`unit_0209543C.cpp`).
- Every file that constructs a class with no key function (an all-pure interface)
  emits its vtable; the linker keeps the bytes and resolves references to the first
  copy. A vtable that sits alone between other data (all zero for an interface) is
  such a copy (`unit_0209543C.cpp`, 0x020BD400).

## Control flow

(none yet)

## ARM / Thumb

(none yet)

## Unsolved patterns

- `swpb` (a byte lock set to 1) has no C form. Inline `asm { swpb ... }` gives the
  right instructions, but mwccarm then puts a zero word before the function's
  literal pool, for every form tried (`func_02096dac`, 89.5 %).
- mwccarm gives such vtable copies (and other multiply-defined objects) symbol
  binding 13. While the first copy is still assembly, dsd emits it as a global or
  weak symbol: a global one clashes ("Multiply-defined") and a weak one loses to
  the compiled copy. The file stays not `complete` until the first copy's file is
  compiled too (`unit_0209543C.cpp`).
