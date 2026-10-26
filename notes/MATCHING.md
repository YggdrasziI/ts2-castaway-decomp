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
- Reusing a dead local for a new value changes the coloring where no declaration
  order does: in `func_0201c2d8` the top of the items goes into `w` (no longer
  needed) instead of its own variable (98.8 % -> 100 %).
- A bool argument built from a flag: `(flags & 1) != 0` and `(flags & 1) ? 1 : 0`
  give the same `movne` / `moveq` but different loop registers around the call
  (`func_0201be00`, 99.7 % -> 100 %).
- An early `bxeq lr` then unconditional code comes from the main result in the
  `if` and the fallback after it (`if (x != -1) return a | f(x); return a;`); the
  reverse order gives conditional `ldrne` / `movne` / `orrne` (`func_0208c110`,
  87.2 % -> 100 %).
- A count-down loop over a new array (`cmp n, #0; sub r3, n, #1; beq`, pointer
  incremented in the body) is `p = array; i = count; while (i--) { p->f(); p++; }`
  with an unsigned count; `for (i = 0; i < count; i++) array[i].f()` reloads both
  (`func_0208d254`, 79.9 % -> 100 %).
- An increment that the original schedules before the compare of a following `if`
  (`add r7, r7, #1; cmp r8, #0`) is written before the preceding `if`
  (`func_0208cdc4`, 96.9 % -> 100 %).
- A field the original re-reads in a loop body although the loop condition just
  loaded it (`next = nodes[next].left`): take a pointer to the element in the body,
  `Node *n = &nodes[next]; parent = next; next = n->left;` (`func_0208c700`,
  88.8 % -> 95.2 %).
- Read the return register before naming a result: `mvn r0, #0; cmp r8, r0; popne`
  returns -1 when the search finds the key, not the index found (`func_0208cf6c`).

- A one-bit field set from a parameter: `bool` gives the plain `lsl #31` insert,
  an `int` adds an `lsl #16; lsr #16` truncation; `f = p ? 0 : 1` on a `bool`
  gave the original `moveq` / `movne` then truncation where `!p` dropped it
  (`func_0208d774`, 63 % -> 100 %).
- A field extracted into a local then tested (`asr`, `and #3`, `tst #1`): an
  `int` local lets mwccarm fold the `and`; a `u16` local keeps it
  (`func_0208d7d0`, 85.7 % -> 100 %).
- A `u16` parameter that the original normalises once at entry (`lsl #16; lsr
  #16`) after an early return, then shifts without truncation: take an `int` and
  copy `(u16)mask` into a `u32` local after that return (`func_0208e058`,
  89 % -> 100 %).
- Constants not shared between a local's initial value and a later `return -1` /
  `x = 0`: initialise the locals at their declaration; assigned as statements,
  mwccarm reuses their registers for the constant (`func_0208e364`, 94.5 % ->
  100 %).
- A second loop whose counter and accumulator take new registers (count copied
  to another register, the word in the freed one): move the loop into an inline
  function taking copies of the values (`func_0208e364`).

## Inlining and emission order

- C++ static object: write the global and its out-of-line constructor; mwccarm builds
  `__sinit_<file>` in `.init`, its `.ctor` pointer, and a 12-byte local `@<n>` chain
  node in `.bss` just before the object, and calls `__register_global_object(obj,
  dtor, &node)`. The constructor and destructor come out as C1/C2 and D1/D2 copies;
  the dead-stripping link drops the unused one (`notes/COMPILER.md`). Names in
  `symbols.txt`: `_ZN<class>C1Ev`, `_ZN<class>D1Ev`, `__sinit_<file> ... local`,
  `.p__sinit_<file> ... local`, `@<n> ... local` (`unit_02099800.cpp`).
- A struct returned by value through the hidden pointer and stored with one `stm`
  of two locals comes from a user-declared constructor, `return R(first, count);`;
  assigned field by field it is built in a stack copy first (`func_0208cdc4`,
  84.8 % -> 96.9 %).
- The declaration order of an inline function's locals has no effect on the code
  where it is inlined: moving the body into the caller with the caller's own
  locals let the declaration search work (`func_0208c700`).

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
- A guarded return of a load: `if (i < n) return a[i]; return 0;` gives the
  original `movge r0, #0` / `ldmge` early exit and plain loads, while
  `if (i >= n) return 0; return a[i];` makes the loads conditional (`ldrlt`)
  (`unit_0208E570.cpp`, 75.8 % -> 100 %).
- `if (x != 0) { ... } else { return -1; }` puts the failure path after the body,
  where `if (x == 0) return -1;` gives a conditional `mvneq`.

- A loop bound re-read from memory at every test while the other members stay in
  registers (and no store in the loop) was matched by declaring that member
  `volatile` (`unit_02093648.cpp`, seven search loops 95 % -> 100 %; again for
  `rangeCount` in `unit_0208E570.cpp`, 92 % -> 100 %). Hypothesis
  only: it costs a reload after a loop elsewhere, and it did not help the same
  pattern in `func_020949b8` (`unit_02094824.cpp`). Not a compiler option: every
  2.0 service pack and `-opt noloop` / `nocse` / `nostrength` give the same code.
- A subexpression of the loop counter that the original recomputes at every
  iteration (`mov r2, r7, lsl #4; add r2, r2, #0x10`), where mwccarm makes it a
  running sum (`add r8, r8, #0x10`) whatever the counter type or expression form:
  write it through an inline function with an `int` parameter,
  `static inline int f(int i) { return i * 16 + 16; }` (`func_0201be00`, 97.95 % ->
  99.67 %; again in `func_0201c2d8`). Same for an address: `&a[i + 1]` that the
  original computes with `mla` comes from `static inline T *at(L *l, int k) {
  return &l->a[k]; }` (`func_02099280`, 94.1 % -> 98.6 %).
- A struct returned by value from a call whose fields the original re-reads from
  the stack inside the loop: give the struct a user-declared constructor, so the
  result is built in place in the local; without one, mwccarm copies it to a second
  slot and keeps the fields in registers (`func_0201baa4`, 79 % -> 88 %).
- A global read before an unrelated store in the original (`ldrh` of the angle
  ahead of `str` to another object) comes from copying it to a local before that
  store; read in the expression after the store, it is loaded after it
  (`func_0201baa4`, 91.2 % -> 99.8 %).
- A loop that advances a pointer before the counter (`add r9, r9, #0xc` then
  `add r6, r6, #1`) is `for (...; p++, i++)` (`func_0201b964`, 97 % -> 99.9 %).
- `switch` case groups: the return blocks follow the order of the groups in the
  source, and the `default:` block comes first when written first.

- `swpb` byte stores are plain C stores: the game flags include `-avoid_byte strb`
  (`notes/COMPILER.md`). A lock byte stored as `*(u8 *)&word = 1` is addressed
  from the first static of the file plus an offset; declaring it `u8 x[4]` keeps
  its own relocation and its 4-byte `.bss` slot (`unit_02096A74.cpp`).

- Functions called with an uninitialized local in r0 and an object in r1 are
  methods returning a class by value (hidden result pointer first, then `this`):
  `Unk02092b94 Unk02092830::func_02092b78(...) { return Unk02092b94(...); }`
  (`unit_02092830.cpp`). A class argument read through r3 is a reference.
- Inside a constructor, a member read where the parameter of the same name is
  still in a register (`ldr r0, [r4, #0x90]`) is `this->member`.
- Declaration order search: moving each declaration to each position (n^2 tries,
  scratch script) found 100 % for `func_02092a34` where full permutations are too
  many.

- `p = new T(n)` where the original keeps the `operator new` result in a
  callee-saved register (`movs r4, r0`), calls the "constructor" and stores r4
  (not the call's return value): the called function is not the constructor but
  an initializer returning `*this`, called by an inline constructor
  (`T(u32 n) { init(n); }`). Same code at the callee, and the caller ignores its
  return value (`func_0208c5c0` 84.75 % -> 100 %, `func_0208a1f8` 99.6 % ->
  100 %). `-Cpp_exceptions on` also keeps the pointer but adds exception tables
  the ROM does not have.
- A lookup inlined in some functions but called out of line (and emitted after
  it) by another: two functions with the same body. The out-of-line one is an
  `inline` function defined after its caller; the inlined one is defined in the
  class body (used by `contains` / `get`). The two copies can need different
  local forms: without a `base` pointer local the inlined copies match
  (`func_0208ccc0` 97.4 % -> 100 %, `func_0208cf6c` 99.4 % -> 100 %,
  `func_0208a4c8` 96.7 % -> 100 %).

- Stack temporaries are laid out in creation order, top down. A product of two
  matrices built from temporaries (`view = mul(T(-pos), R(rot).transposed())`)
  gets the original slots only through an inline `mul` returning by value
  around the out-of-line `void m.mul(a, b)`; named locals for the factors are
  laid out in another order (`func_02089d48`, 99.9 % -> 100 %).

## Data layout

- A dsd symbol inside a static object (here `data_020c806c`, the object + 4 that
  one function returns) makes `.bss` score 3 %: drop the symbol and write the
  relocation as `to:<object> add:0x4` (`unit_02097434.cpp`).
- A class with user-declared constructors is copied member by member
  (`ldr` / `str` pairs); deriving it from a plain struct that holds the members
  gives the block copy (`ldm` / `stm`) of the original (`unit_02098E70.cpp`, 0 % ->
  100 % for the copying functions).
- Assigning such a vector directly (`e->pos = Vec(0, 0, 0)`) is folded into three
  stores even through a named temporary, an aggregate or an inline helper. The
  original's stack temporary copied with one `ldm` / `stm` comes from the implicit
  assignment of a struct that contains the vector: `Light::reset() { *this =
  Light(); }` (`func_0208b9dc` and the constructor of `unit_0208B554.cpp`, 99.9 %
  -> 100 %), or a position wrapper `struct Pos { Vec v; }` declared before the
  next local so the temporaries take the original stack slots (`func_0208befc`,
  92.3 % -> 100 %). The u16 members of such a struct must be separate fields: a
  `u16[4]` array is copied through the stack too (69.6 % -> 99.9 %).
- Copying a returned vector back into the slot of a local (`ldm` / `stm` from the
  call's temporary into the argument's slot) also needs the wrapper's implicit
  assignment: `p = (const Point &)f(p.v);` with `struct Point { Vec v; }`
  (`func_02089cac`, 69.1 % -> 100 %). A plain `p = f(p)` is three stores; a new
  local initialized from the result takes its own slot (96.7 %).
- A file-scope pointer initialized to 0 goes to `.bss`; when the ROM has it in
  `.data` next to another initialized word, a struct holding both with an
  initializer list puts it there (`unit_02093648.cpp`, hook and name). A string
  literal is a local `@<n>` symbol: give the dsd symbol its exact length
  (`data(byte[21])`) and `local`, or `.data` scores below 100 %.
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
  Initialized `const` arrays in `.rodata` follow the same pattern: four 12-byte
  tables declared `a0 a1 a2 a3` come out `a2 a1 a0 a3`, so the source declares them
  in the order `a2 a1 a0 a3` to get the ROM order (`unit_0208F8B0.cpp`).
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

- `.data` objects defined before a file's first out-of-line function are laid out
  by size, whatever the declaration order (a 4-byte pointer always lands before
  0x40-byte tables); an object defined after a function is appended after them,
  and its string literal follows that function's code. A pointer after larger
  tables in the ROM, followed by its own string, points to a file boundary. Here
  the tables and their static initializer are a unit with no code
  (`unit_020B8888.cpp`), and the pie menu keeps the pointer (`unit_0201B6D4.cpp`).
- A static object loaded through its own symbol where mwccarm reaches it through
  another static of the file plus an offset is the only `.bss` object of its file
  (`data_020be384`, `unit_0201B6D4.cpp`).
- A static initializer builds objects in declaration order, independently of their
  `.bss` order: declared `data_020be37c` then `data_020be374`, they are built in
  that order and laid out `374, 37c` as in the ROM (`unit_020B8888.cpp`).

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
- A file emits the vtable of a base class only when it defines a constructor of a
  derived class (the implicit base constructor stores the base vptr). The first
  interface vtable copy (0x020BD014) sits after the vtable of a class whose
  constructor is not in the ROM: an out-of-line `Unk0208b41c::Unk0208b41c() {}`
  emits the copy, and the `-dead` link drops the unused constructor
  (`unit_0208B41C.cpp`). The derived class's own vtable is emitted without it.
- Once every copy is compiled, mwccarm's multiply-definable copies link like the
  original (one copy keeps the name, the others are anonymous bytes); the later
  copies must then leave `symbols.txt`, or `check symbols` fails ("not found by
  address in linked binary") (`unit_0209543C.cpp`, 0x020BD400).

## Control flow

- A two-way test whose original keeps the `== 0` branch conditional (`ldreq`,
  `biceq`, `streq`, `bxeq`) and the other one after it did not move with any
  `if` / `else` order on an `int` parameter; a `bool` parameter gave it
  (`func_0209185c`, 48.75 % -> 100 %).
- Members stored before an array member is constructed (the array loop comes after
  the field stores) are a member initializer list, bitfields included:
  `: used(0), ..., main(main), rest(0), unk820(unk820)` (`unit_020916A4.cpp`,
  43.8 % -> 100 %).
- A function that reuses one loop counter for several loops can need a second
  counter: a separate `j` for the middle loop gave the original register of the
  counter (`func_02092554`, 98.7 % -> 100 %).
- Arguments computed before the `if (main)` that picks one of two calls with the
  same arguments: modify the parameters first (`data += src; n *= 2;`); written in
  each call, mwccarm sinks the last argument into both branches
  (`func_0209201c`, 90.2 % -> 99.0 %).
- `switch` case bodies come out in source order while the tests stay in value
  order: an original that tests 4 then 8 but places the case 8 body first was
  `switch (v) { case 8: ...; case 4: ...; }` (`func_02092788`, 68 % -> 94 %).
- Variadic functions: mwccarm's `va_start(ap, fmt)` is
  `ap = (char *)((u32)&fmt & ~3) + 4` after the `push {r0-r3}` of the prologue; no
  header in the project defines it, so the unit defines the macro
  (`unit_02090CCC.cpp`).
- A flag word tested inside a loop (`flags & 1`, `flags & 4`) whose original
  computes the masks after the loop's first test: use the expression in the loop,
  not a local; mwccarm hoists it behind the guard. Dropping the local `vflip`
  (writing `flags & 2` twice) gave the original stack slots (`func_020901a4`,
  90.5 % -> 100 %).
- A parameter changed in two steps (`tiles <<= 3; ... tiles -= 8;`) can come out
  as two registers; one assignment `tiles = (tiles << 3) - 8;` keeps one
  (`func_020901a4`, 81.6 % -> 90.5 %).
- An index register that grows by 8 next to a column counter is `col * 8` in the
  source (`dst + col * 8`); a separate `off += 8` became a pointer increment
  (`func_0208ff50`, 77.5 % -> 85.8 %).
- A `u16` local shifted in a loop is masked again after every shift (`lsl #0xf`,
  `lsr #0x10`); the original's plain `lsr` comes from a `u32` local set from
  `(u16)param` (`func_02091eb4`, 92.4 % -> 100 %).

## ARM / Thumb

(none yet)

## Unsolved patterns

- mwccarm gives such vtable copies (and other multiply-defined objects) symbol
  binding 13. While the first copy is still assembly, dsd emits it as a global or
  weak symbol: a global one clashes ("Multiply-defined") and a weak one loses to
  the compiled copy. The file stays not `complete` until the first copy's file is
  compiled too (solved for `unit_0209543C.cpp` by `unit_0208B41C.cpp`, see "Data
  layout").
- The same holds for the inline virtual destructor of an interface: every file
  emitting the interface vtable emits D1 and D0 as multiply-definable functions,
  and the link keeps the first copy of each (`unit_0208F16C.cpp`: D1 0x0208F168 at
  the end of the other font's file, D0 0x0201B92C in a far file). Named after the
  interface while they are assembly, they clash ("Multiply-defined"); left with
  their dsd names, this file's copies stay in its `.text` and shift everything.
- String literals: mwccarm puts each one in its own `.data` section with alignment
  1, and the link still places them 4-byte aligned in source order (trial link of
  `unit_0208F16C.cpp`). objdiff does not pair these sections with the original
  `.data` (`data_<addr>` symbols), so `.data` scores low although the bytes are
  right; it only shows once the file links as `complete`.
