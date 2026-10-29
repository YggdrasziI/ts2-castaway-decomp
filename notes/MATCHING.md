# Matching techniques

Compiler idioms that fixed near-misses in this project, each tied to the unit that
proved it. Techniques from the Wii projects (mwcc PowerPC) do not carry over by
default: add one here only once a unit of this ROM proves it with mwccarm.

## Loads, constants and literal pools

- I/O registers written as base + offset after a call (`ldr r0, =0x040000B0`,
  `str r1, [r0, #0x8]`) come from a local pointer to a register struct
  (`volatile Dma *dma = (volatile Dma *)0x040000B0; dma->ctrl = ...`); a cast of
  each address gives a second pool word 0x040000B8 (`func_01ff8c64`,
  97.9 % -> 100 %).
- objdiff marks a `bl` as "argument differs" when its target is the function
  right after the caller's literal pool: target - 8 falls inside the caller, so
  objdiff reads the original's relocation as a branch inside the function. The
  bytes match (`func_01ff8c64` stays at 99.90 % in the report with its file
  `complete`, ITCM: OK).

## Registers and stack

- A global address loaded once into a callee-saved register (`ldr r4, =db` then
  `mov r0, r4` before each call) comes from a local (`u8 *db = data_020c3fc4;`);
  a test written in an inline helper (`return f(db, id) != -1;`) keeps the
  original `movne` / `moveq` / `cmp` that the same test written inline folds
  (`func_020648dc` 85 % -> 100 %).
- A loop counter and a pointer from a call swapped between two callee-saved
  registers: declare the counter (or the list cursor) before the local that
  takes the call's result (`int j; int *count = f(); for (j = 0; ...)`,
  `func_02060080` and `func_0205ffa4`, 99.0 % -> 100 %).
- A loop whose entry test is only the first half of its condition
  (`f(); beq out; top: cmp i, n; bge out; ...; f(); bne top`) is
  `while (f()) { if (i >= n) break; ... }`; `while (f() && i < n)` jumps to a
  bottom test instead (`func_0205f328`, 92.0 % -> 97.9 %, with the call result
  kept in a local so a store lands after the next call).
- Locals of one branch that take lower callee-saved registers than the
  function's result in the original are declared at the top of the function,
  before the result (`int id; int dirKey; int found = 0;`, `func_0205b7e0`,
  99.1 % -> 99.8 %); a local declared later takes a higher register.
- `int n = a - f(); n /= k;` keeps the difference in the register of the
  original where `(a - f()) / k` picks another one (`func_0205c680`,
  98.7 % -> 100 %).
- An argument loaded before a boolean argument is computed (`ldr r1, [sp]`
  between the tests) comes from an inline member that forwards both
  (`void set(u32 i, bool v) { p->f(i, v); }`) or from a local copy of the
  argument; written as a direct call the load comes after (`func_0205bfb4`).
- Two fields copied one by one after a compare that read the first one, with
  the first field read again (`ldr; ldr; cmp; ...; ldr; str`), come from an
  inline member copy (`void set(const T &o) { key = o.key; index = o.index; }`);
  written inline the compare's load is reused (`func_0205f184`, 75 % -> 80 %).

- Two nested loops over a footprint with a running bit counter: declaring
  `int bit = 0; int x; int y;` before the loops, in that order, gave the
  original registers (`func_02059534`, 97.7 % -> 100 %); the other five
  orders did not.
- Bounds tests that share one `return false` block in the original (`beq` /
  `bgt` to the same exit, last test `ble` into the body) come from one
  combined `if (a || b || c) return false;`; separate `if`s give conditional
  returns after each test (`func_02059710`, 71 % -> 82 %).

- A key search where the original keeps a byte offset (`i * 12`) next to the
  walked pointer: indexing the member array directly (`unk3c[i]`) instead of a local
  copy of it, and reusing the frame and index locals of the searches before, gave
  the original loop; loading the array inside the branches that use it fixed the
  last scheduling (`func_01ff84f0`, 97.57 % -> 100 %).
- Two loops sharing one counter declared at the top: the second loop got the
  counter, the entry pointer and its strength-reduced `i * 2` in rotated registers;
  `for (int i = 0; ...)` in each loop gave the original allocation
  (`func_01ffadf8`, 99.3 % -> 100 %).
- A product used only as a down counter (`while (n-- != 0)`): with `w` and `h`
  locals, mwccarm folds the test into `muls`; computing `n` in one expression and
  declaring it before the other locals gave the original `mul` / `cmp` and their
  order (`func_01ffab9c`, 58 % -> 100 %).
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
- A running index next to two nested loop counters (`dst[k] = m[i][j]`): `k++`
  inside the store copies k before the increment; `dst[k] = ...; k++;` with k
  declared in the outer loop's init, `for (int i = 0, k = 0; ...)`, gives the
  original's registers (`func_01ff8fd8`, 98.96 % -> 100 %).
- Temporaries built inside an inline helper (a view matrix computed by
  `static inline Unk02098094 f(...)`, a product returned by an inline
  `func_mul`) get the lowest stack slots, below the caller's own temporaries;
  written in the caller they sit above them (`func_01ff9924`).
- A vector copy done with `ldm` / `stm` where the class copies member by member:
  copy construction (`Unk02098ff0 d = v.func_clamp();`) gives the block copy and
  the original's stack slot; the assignment operator does not (`func_01ff9f00`).
- A clamp that the original applies through a pointer kept in a register (`ldr r0,
  [r9]`, `strlt r7, [r9]`) is an inline member called on the temporary returned by
  a call (`m.func_02097d38(v).func_clamp()`), not a clamp of a named local
  (`func_01ff9f00`, 72.9 % -> 74.3 %).
- Packed values computed before an unrelated clamp in the original (light vector
  before the colour clamps): compute them first in the source; the scheduler does
  not move them across (`func_01ff9f00`, 74.6 % -> 98.4 %).
- Stack slots of local objects follow their declaration order: declare them so that
  the offsets match (`func_02097f1c`).
- A local object that the original keeps below the call temporaries (lowest stack
  slot), or temporaries in the reverse order of named locals: write the
  computation as an inline helper returning the object by value
  (`func_mul(a, b)` for a matrix product, `func_scale(v, t)` for a vector), whose
  locals take the lowest slots (`func_01ffa838`, `func_01ffa364`).
- Loop locals one register off around a call result: declare the other locals
  without initializer before the one initialised by the call, then assign them
  (`func_01ffa838`, 99.5 % -> 100 %). Two pointers swapped: swap their
  declarations (`func_01ffa538`).
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
- A colour channel taken out of a `u16` with `lsl #0x1b; lsr #0x18` then `and
  #0xff` is `int r = (u8)((c & 0x1f) << 3);`; a `u8` local gave other shifts and
  registers (`func_02070318`, 96.2 % -> 99.7 %). Sums of fixed-point products
  that the original adds with `add` (not `adds`) are `int` sums: cast each 64-bit
  product to `int` (82.9 % -> 92.2 %).
- A loop that reads three bytes `colors[k]`, `colors[k + 1]`, `colors[k + 2]`
  from one base register (`add r0, base, k` then `ldrb [r0, #1]`, `[r0, #2]`):
  take a pointer `const u8 *c = &colors[k];` for the first use only
  (`Unk0206fac8` constructor, 88.7 % -> 100 %).
- An array index the original computes once with `lsr #2` and then uses twice
  scaled by 4 (`ldr r0, [r1, r2, lsl #2]`, `add r1, r1, r2, lsl #2`) is a `u32`
  local `k = i * sizeof(Entry) / 4` read as `entries[k]` and `&entries[k] + 1`; a
  pointer to the entry gave `bic r1, off, #3` (`func_02070d5c`, 97.8 % -> 100 %).
- A call result shifted straight into the argument register (`mov r1, r0, lsl
  #0xc` after the call) before another argument is loaded: put the shifted value in
  a local before the call that uses it (`int w = tex->func_0208c16c() << 12;`,
  `func_02070d5c`, 94.0 % -> 97.8 %).
- A parameter shifted once (`mov r11, r11, lsr #2`) and used as the loop bound:
  `size /= 4;` before the loop, not `i < size / 4` (`Unk02070eac` constructor).
- A global pointer loaded before a member store that precedes the call through it
  (`ldr r0, [r0]` then `str key, [this, #0x40]`): copy the pointer to a local
  first (`Unk0208a0a8 *lib = data_020c7d24; modelKey = key; lib->f(file);`,
  `func_02071120`, 92 % -> 100 %). An early `return` in the equal case instead of
  the original's `if / else` moved the else block up (`func_020711e8`, 90.8 % ->
  100 %).
- A vector result copied once more with `ldm` / `stm` before a sum: pass it by
  value to an inline helper (`func_add(const Vec &a, Vec b)`) (`func_02071564`,
  83.5 % -> 99.9 %).
- A global object whose address the original keeps in a register across a loop
  (`ldr r4, =data_020c7d38` before the counters): take a local pointer to it
  (`Unk020c7d38 *pool = &data_020c7d38;`) and call through it (`Unk020717b8`
  constructor, `func_02071cc0`: 92 % / 94 % -> 100 %). A member array pointer
  the original reads once for a slot and again for a later field
  (`ldr r1, [r5, r4]`) is a local copy too (`Unk020717b8Slot *list = slots;`,
  `func_020718c0`, 84 % -> 96 %).
- A returned vector the original copies once more with `ldm` / `stm` into a
  named local: `Unk02098ff0 r = f(); Unk02098ff0 dir(r);` (`func_02071a60`,
  84.5 % -> 99.9 %).
- A virtual call on a global object (`ldr r2, [r0]`, `ldr r2, [r2, #0x18]`, `blx`)
  goes through a local pointer (`Unk020c43a8 *owner = &data_020c43a8;`): called on
  the object itself, mwccarm calls the function directly. An argument stored to
  an unused stack slot before the call (`mov r1, #2`, `str r1, [sp, #8]`) is a
  one-word struct passed by value (`func_18(Unk020c43a8Mode(2))`,
  `func_02071e04`, 96 % -> 100 %).
- A not yet decompiled C function that fills a record on the caller's stack
  (`add r0, sp, #8`, then the record read in place): declare it with an out
  pointer; declared as returning the struct by value, the result is copied
  (`ldmia` / `stmia` x 3) (`func_02072398`, 78.6 % -> 99.3 %).

- A struct returned through a hidden pointer and read once: `T t; t = f();`
  (declaration, then assignment) or `T t = f();` give other stack slots and score
  differently than reading the member of the call (`func_0202071c(clock).hour`):
  try both forms (`func_02071fdc` of `unit_0206BCE0.cpp`, 98.4 % -> 99.0 %).

- A member read through an inline function is not merged with an earlier read
  of the same member: the original's reload of `unkc` before `unkc->flags`
  (`func_0206f0ec`, 98.8 % -> 100 %) and of `unk22c` (`func_02071fdc`) come from
  inline accessors (`bool func_busy() const { return unkc->flags & 0x40; }`).

- A loop over a member array whose element pointer the original sets after the
  first test (`ldmle` exit, then `add r9, r10, #0x24`) is written with
  `T *part = &p->parts[i];` inside the body; a pointer set before the loop moves
  the `add` ahead of the test (`func_0206961c`, 95.8 % -> 100 %).
- A local pointer to a global object (`Unk020c7d38 *pool = &data_020c7d38;`)
  gives the original's single literal load kept in a register; calling through
  the global reloads it at each call (`unit_020680D4.cpp`, five functions).
- Stack slots of matrix and vector temporaries follow their creation order
  (descending addresses): a named local takes a slot ahead of all temporaries.
  When the original places a value among the temporaries, write it as one;
  `f(a(), b())` through an inline wrapper evaluates `b()` first while keeping the
  slots in source order (`func_add` in `func_0206869c`, 98.9 % -> 100 %).
- Minimum / maximum per component: the original `cmp lo, t; movle t, lo` is
  `lo > t ? t : lo`, and `cmp hi, t; movge t, hi` is `hi < t ? t : hi`
  (`func_020693d8`, 88 % -> 99.4 % over 16 forms).

- A `bool` field passed to a `bool` parameter is passed as loaded; a test
  or a cast in between adds a normalization (`func_0205a5c8`).
- `mla` where `smlabb` was expected for a row index (`y * width + x` with `s16`
  coordinates): compute the index in `u32` through an inline helper taking
  `u32 x, u32 y` (`unit_02055EF8.cpp`, tile access of a layer; `func_020596b8`
  96.8 %, `func_020598e4` 97.0 % and `func_02059828` 98.5 % -> 100 %).
- An object pointer loaded before the argument calls (`ldr r5, [r4, #0x104]`
  ahead of the calls that build the arguments): read it into a loop-local
  first (`Unk020705e4 *texanim = world->texanim; texanim->f(...)`).
- A field read before a block of stores to the same object stays in a register
  only when it is read into a local first (`int map = w->map;`).

## Inlining and emission order

- A member the original reads twice (a flag test, then the whole word in an
  expression) where mwccarm keeps the first load in a register: testing the flag
  through a `static inline` predicate and doing the whole write in a `static inline`
  function with its arguments given inline gave the reload and the original
  registers (`func_01ffadf8`, 95.3 % -> 99.3 %).
- Leaf functions saving registers inside a branch or using register post-indexed
  loads (`ldr r2, [r0], r6`) are hand-written: write them as `asm` functions, as in
  the SDK (`func_01ffaca0`, `func_01ffad44`).
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
  Same fix for `groupCount` in `func_020606a0` (`unit_02060274.cpp`, 89 % ->
  100 %). A flag halfword tested, then read again for its update with no store
  between (`ldrsh; tst; ...; ldrsh; orr; strh`), also matched with `volatile`
  (`func_020606e0`, 98.8 % -> 99.7 %), hypothesis too.
- A global field read twice in a row with no store between (`ldrsb r1, [r0,
  #0xfc]; ldrsb r5, [r0, #0xfc]`, one call argument and one local kept for a
  later call) matched with a `volatile` read of the local's copy
  (`func_0205fde4`, `unit_0205F80C.cpp`, 98.6 % -> 100 %), hypothesis.
- A flag set with `bic` then `orr` of the same mask, and a flag tested then
  read again for its update (`ldr; tst; ldr; bic; str`), come from inline
  member helpers: `void set(u32 mask, bool on) { flags &= ~mask; if (on)
  flags |= mask; }` and `bool test(u32 mask) const { return (flags & mask) !=
  0; }` (`func_02060080`, 95.0 % -> 99.7 %). A bitfield gives `lsl` / `lsr`
  tests instead, `(flags & ~mask) | (on ? mask : 0)` folds to one `orr`.
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
- A state set tested as `i <= n` then `tst mask, 1 << i`, with each result kept
  as a bool (`mov r3, #0` ... `movne r3, #1; cmp r3, #0`) and the `||` of two
  sets kept as a bool too: an inline `func_bit(u32 i, u32 n, u32 mask)
  { return i <= n && (mask & (1 << i)) != 0; }` called from a second inline
  that stores its result in a local, combined in a third inline (`return
  a(s) || b(s);`). A `switch` gives compare chains; one inline level gives no
  bools (`func_020559cc`, 31.7 % -> 100 %).
- A struct returned by value and passed by address (`f(&d)`) is copied to a
  second stack slot when written `T d = g();`; binding it to a const
  reference (`const T &d = g(); f((T *)&d);`) matches (`func_02055cb8`,
  70.2 % -> 100 %).
- A call nested in an argument list is evaluated after the other arguments
  (`g(h(x), loop ? 1 : 2)` computes the select first); a local for the call's
  result keeps the original order (`func_02055c60`, 62.4 % -> 100 %).

## Data layout

- A table filled by a static initializer with both fields stored at run time
  (hash from a call, then a function pointer) has an element type with an
  inline constructor (`Entry(const char *name, Func f) : key(hash(name)),
  func(f) {}`); an aggregate initializer `{hash(name), f}` keeps the constant
  pointers in `.data` and stores only the hashes. The first element is
  addressed from the start of the `.bss` block that also holds the chain node
  of the registered global (`str r0, [r2, #0x38]`), the others by their own
  address: dsd makes one symbol per element; drop them and write the
  relocations as `to:<table> add:<offset>` (`unit_0205AF94.cpp`).
- A callback stored in a table of `u16 (*)(Node *)` that returns a constant
  without the `lsl` / `lsr` truncation is declared `int` and cast in the table
  (`func_0205bc88`, `func_0205c548`).
- A dsd symbol inside a static object (here `data_020c806c`, the object + 4 that
  one function returns) makes `.bss` score 3 %: drop the symbol and write the
  relocation as `to:<object> add:0x4` (`unit_02097434.cpp`).
- A static object followed by dsd symbols referenced from elsewhere: dsd sizes
  the object up to the next symbol, which leaves `.bss` at 28 %. Give the object
  its size (`kind:bss(size=0x3e84)`) and move the other references to it: the
  BuildInfo autoload list words (0x02000B64, 0x02000B68) are addresses of the
  load image that fall inside `.bss`, written as `to:data_020bfc9c add:0x1464`
  / `add:0x147c`; without that the link drops the words and `Check ARM9 main`
  fails (`unit_02054AB4.cpp`).
- The `volatile` loop bound fix also matched `func_02054dfc` (a `short` count
  of a script run, 96.3 % -> 100 %). In `func_02054cf0`, `if (list != 0 &&
  list->head != 0) { prev = 0; for (n = list->head; ...` tests the head twice;
  `if (list != 0) { prev = 0; for (n = list->head; n != 0; ...` gives the
  original's single conditional test (90.1 % -> 100 %). Register order of
  `func_02054fbc` came from `u32 i; u32 hits; int found = 0; i = 0; hits = 0;
  for (; i < n; i++)` (97.7 % -> 100 %).
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
- `new T[n]` of a vector class with a constructor, even an empty inline one,
  calls `__cxa_vec_new`; the original `_Znam(n * 12)` and the word-by-word copy
  loop come from the plain base struct (`Unk02098ff0Base`) as element type
  (`func_02089874`, 92.3 % -> 100 %).
- Stores at offsets read from records (`*(u32 *)(data + (rec->a & ~3))`) keep the
  original load order and registers only through one pointer local per field
  (`u32 *p = (u32 *)(data + (rec->a & ~3)); *p = ...; DC_StoreRange(p, 4)`); offset
  locals added to `data` at each use are scheduled differently
  (`func_01ff9478`, 95.7 % -> 100 %).
- `x >= 0 ? 1 << x : 1 >> -x` written as `if (x < 0) ... else ...` gives the
  original mix of a branch for the first value and conditional moves for the
  second (84.7 % -> 95.7 %). A mask parameter narrowed in place (`mask &= ...`)
  right after a second mask is taken from it, with the loop's count and pointer
  read first, gives the original registers (`func_01ff924c`, 89.7 % -> 100 %).
- Two branches that store a vector into the same array element (a key's vector,
  or an interpolated temporary) share the original's copy tail (`add r3, r1,
  #0x10; ldm; stm`, with `r1` the element) only through an inline setter of the
  element (`unk44[n].setPos(v)`, whose body does the wrapper assignment). A named
  reference to the interpolated value moves its temporary to the top of the frame
  (`func_01ff84f0`, 83.4 % -> 97.5 %).
- A quaternion built member by member (`q.x = k->x; ...`) loads and stores each
  field in turn as the original; the four-argument constructor loads all four
  first (88.1 % -> 93.9 % with the key array read once into a local before the
  branches).
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

- A `u32` loop counter that also indexes a global byte array: mwccarm turned
  `data_020d60c8.unk110[i]` into a pointer stepping with the loop; the original
  reloads the base each pass, which `unk110[(int)i]` gives (`func_020732c4`,
  93.3 % -> 98.3 %). In the same loop, the two results declared before the loop
  and `h << 11` written in both calls instead of a local gave the original
  registers (98.3 % -> 100 %).
- A member array of vectors assigned with `ldm` / `stm`: the elements are a
  struct wrapping the vector (`Unk0205fae8Pos { Unk02098ff0 v; }`), whose implicit
  assignment is a block copy; the vector class's own `operator=` copies field by
  field (`func_020732c4`, 87.3 % -> 93.3 %).

- String literals land in the `.data` sections in the order of the functions
  that use them in the source: keep the definitions in address order. Functions
  added at the end of the file put their strings last (`unit_0206BCE0.cpp`,
  `.data` 82.9 % -> 100 % once sorted).

- A constructor that builds two members through one base register (`add r5, r4,
  #0x150`, then `r5 + 0x58`, `r5 + 0x90`) owns a sub-struct starting there; here
  the 0x98-byte block written to the save as one piece (`unit_02064984.cpp`,
  constructor 96.2 % -> 100 %).
- A record whose constructor and destructor keep C names (`func_020647b0`,
  `func_020647ec`): inline members calling them (`T() { func_020647b0(this); }`)
  give the calls and make the class non-POD, so `a = T();` and `a = *b;` copy
  member by member (one `ldm` / `stm` per array, `ldr` / `str` per word) as in
  the original (`func_02064984`, `func_020670fc`).
- Fields of an array element written as `p->a[i].f` (base `p + i * size`, field
  offsets from `p`) instead of through an element pointer local (offsets from the
  element): `func_02067d0c` 93.5 % -> 100 %, `func_02065eb8`, `func_02066884`. A
  reference local (`T &r = p->a[i];`) gives the pointer stepped by the element
  size instead (`func_0206562c` 98.0 % -> 100 %).
- Counters kept on the stack get slots in declaration order: declared without a
  value next to the other locals and set later (`int needs; ... needs = 0;`),
  they take the original slots (`func_02064e10`).
- Two `.data` tables whose order does not follow their definitions (in either
  order) are one object: a struct holding both (`data_020bb9f0`: 37 link masks,
  then an unused table of orders, `unit_02055EF8.cpp`).
- A function-local static with a dynamic initializer takes 8 bytes of `.bss`:
  a guard word (`_ZGV<name>$<n>`) and the value. A reference static
  (`static T &p = *f();`) puts the guard first, as the original does; a
  pointer static (`static T *p = f();`) puts the value first. Name the static
  after the address of its value (`data_020c3b24`), so the symbols are
  `_ZGVdata_020c3b24$882` and `data_020c3b24$882` (`unit_02055118.cpp`).

## C++ classes

- `new T[n]` with a class `operator new[]` and a non-trivial constructor calls
  the class operator, then `__cxa_vec_newinit(p, n, size, 8, ctor, dtor)` only
  when it returned a block; `delete[] p` with a class `operator delete[]` calls
  `__cxa_vec_delete2(p, size, 8, dtor, dealloc)`; `new T(arg)` with a class
  `operator new` calls the constructor only when it returned an object, and
  `delete p` with a non-virtual destructor calls it, then the class `operator
  delete` (`unit_0205F80C.cpp`; the names come from the compiler's output).
- A large function stops inlining after a while, even with `inline` helpers:
  the remaining calls go to out-of-line copies that mwccarm emits right after
  that function, in order of first use (`func_0206a120`: the plane assignment
  `_ZN11Unk020987d8aSERKS_`, two helpers and the implicit constructors of two
  records sit at 0x0206A7DC-0x0206A850). Code that the original inlined there
  (a camera getter, vector copies) must be written out, or it becomes such a
  call too. Splitting the body into `static inline` functions changed the stack
  layout to the original's (locals in ascending declaration order).
- A camera record copied as a block (`ldm` / `stm` from a stack temporary) comes
  from a wrapper struct around the vector with its own constructor
  (`Unk0206a07cVec`, `func_0206a07c` 37.9 % -> 100 %).
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

- Pointers to member functions are two words (function, `this` adjustment),
  passed by value in two registers. Each `&C::f` taken in the source becomes its
  own 8-byte `.data` constant, emitted in source order before the vtable (one
  per use, duplicates included); `(this->*phase)()` tests the adjustment's bit 0
  (`unit_02072D94.cpp`, 0x020BC9C8-0x020BCA28).
- A pointer to member constant that no code loads (0x020BCAC4 in
  `unit_02073878.cpp`) still comes from the source: mwccarm emits the constant
  for a `&C::f` in a dead branch (`if (0)`, or after a `return`) and drops the
  code. Its place in `.data` tells which function held it.

- A virtual call on a global object (`data_020c43a8.func_14()`) is made direct by
  mwccarm; the original's call through the vtable comes from a local pointer
  (`Unk020c43a8 *p = &data_020c43a8; p->func_14()`).
- An inline `operator==` taking its operand by value copies it to the stack as
  halfword blocks, then compares field by field (`func_0206ea00`, cell compare).

- Stack temporaries filled with halfword block copies of a member struct, with no
  constructor call, come from an inline function taking the struct by value
  (`o->func_set(unk204, 4, key, v)` with `void func_set(Unk0206bcf0Cell c, ...)
  { cell = c; ... }`): `func_0206e424` 81.3 % -> 94.6 %. The same holds for a
  returned struct used once: `item->func_14().func_moved(d)` (`func_0206e134`,
  88.1 % -> 99.9 %), and for a member of a returned struct given to a `const &`
  helper (`func_tileAt(layer, o->func_14().xy)`, `func_0206da24`).
- A check repeated on a local (`func_02059418(&c) && c.xy.x >= 0 && c.xy.y >= 0`)
  written in an inline helper taking the cell by `const &` lets the original keep
  the coordinates in registers for the next comparison (`func_0206ea00`,
  95.4 % -> 98.7 %).

- A 4-byte struct returned by value comes back in r0 when it is a plain struct
  and through the hidden result pointer when it has a constructor: the clock value
  of `func_0202071c` needs `Unk0202071c() {}` (`func_020695f0`, 46 % -> 100 %).
- A virtual function taking a one-word struct by value and storing it in a member:
  `this->dir.v = dir.v;` keeps the spilled argument in its register; the struct
  assignment re-reads it from the stack (`func_18`, 83.6 % -> 100 %).

- A fixed-point product rounded with `+ 0x800` before the shift is a
  separate inline (`func_fxmulr` in `unit_020599A0.cpp`): the shared
  `func_fxmul` of `include/game/unk_vector.h` does not round; the guarded
  divide is `func_fxdiv` there.
- Color stores with the alpha written late: a constructor that sets only
  `r`, `g`, `b`, then `c.a = 0xff` where the original stores it
  (`func_0205ae10`).
- A state test `state == a || state == b` that the original materializes
  as a bool and follows with `&& state != b`: a `const` inline member
  returning the test (`p->func_fadingIn() && p->state != 1`) comes closest
  (`func_02059d10`, 94.1 % -> 96.0 %, still not matching).

## Control flow

- A loop whose first test is duplicated before the body (`ldr; cmp; beq` then the
  test again at the bottom) comes from a `for` whose condition holds every exit
  test, `for (n = 4; n > 0 && (node = head) != 0 && time >= node->time; n--)`, or
  from `for (node = head; node != 0; node = head) { if (...) break; ... }`; the same
  tests as `while (a && b)` or as `return`s inside the body give a jump to a
  bottom test (`unit_0206B77C.cpp`, 68.8 % / 79.5 % -> 100 %).
- A member read early, before stores it could alias (`ldrh r2, [r4, #0x10]` ahead
  of the other node fields), is a local taken before those stores:
  `u16 now = time;` placed after the null tests (taken before them it lost
  points) (`func_0206b998`, 93.5 % -> 100 %).
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
  Again in `func_020608d8` (`case 4` body before `case 2`, 82 % -> 98 %).
- A walk to the end of a list that reads `p->next` twice per step (`ldr r1,
  [r1, #8]; ldr r0, [r1, #8]`) is `for (p = head; p->next != 0; p = p->next) {}`;
  `while (head->next != 0) head = head->next;` keeps the loaded value
  (`func_020602b0`, 96.1 % -> 99.0 %). A list loop with no test before its first
  pass is a `do { ... } while (f != 0);`.
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

- A test of a small set of ids written as a `switch` gives a compare tree. The
  original's `sub r1, id, #lo; cmp r1, #n; ... tst mask, r2, lsl r1` is the
  explicit bit test `u32 i = id - lo; if (i <= n && (mask & (1 << i)))`
  (`func_02071fdc`, 78.7 % -> 95.3 %).

- A hash switch whose first test is one key alone (`cmp; beq <loop end>`) before
  the binary search of the others is `if (h == key) continue;` ahead of the
  `switch`; with three cases left, mwccarm tests them one by one. Signed
  comparisons (`bgt` / `bge`) in the search mean an `int` operand: `switch ((int)
  hash)` for a `u32` value (`func_02067d0c` 93.5 % -> 100 %, `func_02067878`).
- `cmp r0, #0; movne r1, #1; moveq r1, #0` on the result of a `bool` function
  is an `if (f()) a = 1; else a = 0;`; `a = f() ? 1 : 0` is folded to a move
  (`func_02067778`).
- `mov r2, #0` reused for an earlier store, then `orr r2, r2, #1` before a
  halfword store: `x = 0; x |= 1;` (`func_02064984`).
- A main loop that loads the cursor at the top and returns on null is
  `for (;;) { cur = ...; if (cur == 0) return; ... }`.
- A sorted insertion without conditional execution: write the end test before
  the advance, `else if (it->next == 0) { append } else it = it->next;`
  (`func_02056070`).

## ARM / Thumb

(none yet)

## Unsolved patterns

- mwccarm gives such vtable copies (and other multiply-defined objects) symbol
  binding 13. While the first copy is still assembly, dsd emits it as a global or
  weak symbol: a global one clashes ("Multiply-defined") and a weak one loses to
  the compiled copy. The file stays not `complete` until the first copy's file is
  compiled too (solved for `unit_0209543C.cpp` by `unit_0208B41C.cpp`, see "Data
  layout"; `unit_02072BEC.cpp`, at 100 %, waits on the base vtable copy 0x020BC8FC
  of the game states).
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
- A search loop that returns from inside and ends on `cmp r2, #0x10; bne` is
  written `for (int i = 0; i != 16; i++)`; `i < 16` gives `blt` and an unsigned
  counter `blo` (`func_020644cc`). Short loops over a member array ending on
  `blo` take a `u32` counter (`func_020643c4`, `func_020643ec`).
- An element pointer `e = &a[i]` that the original recomputes (`add r3, r4, r7`)
  after a call is only a short-lived local: use it for the first statements and
  write `a[i].f` after (`func_020644cc`, 99.1 % -> 100 %).
- With `-str reuse`, identical string literals of one file share one copy: two
  copies of the same string in `.data` belong to two files, which bounds the
  split between their users ("lot.lot.nitro_lot" at 0x020BB9C8 and 0x020BBBA0,
  `unit_020582E0.cpp`).
- In a `complete` file, `check symbols` looks the string literals up by name:
  rename their `data_<addr>` symbols to the object's `@<n>` names (`... local`,
  exact `byte[N]` length), as printed in the error ("Possible name: @241").
- The chain node of a static object (`.bss`, 12 bytes before it) has no name
  in our object file listing; set its dsd name back and read the real one from
  the `check symbols` error ("Possible name: @52"). A made-up `@<n>` name was
  not caught by the check, so never guess it (`unit_02064224.cpp`).
- A parameter whose register later holds a derived value was reassigned:
  `key = func_0209a3c4(key, ...)` instead of a new `hash` local
  (`func_02064074`, 96.9 % -> 100 %).
- Relocations of a static initializer into the middle of its object (second
  table, counts) are `to:<object> add:<offset>`; the dsd symbols inside the
  object leave `symbols.txt`, or `.bss` scores low (`unit_02063CD0.cpp`).
- Fields stored from many locals after some of them are loaded early (out of
  the store order) come from an inline setter whose arguments are evaluated
  right to left: `o->func_set(key, id, v, c, d, e, f, g, h, x, y)`
  (`func_02063590`, 93.3 % -> 100 %; `func_02063934` / `func_02063b94`, the
  context word read before the two virtual calls, 79-85 % -> 100 %).
- A small struct returned by a virtual call and passed by value to an inline
  setter: an extra stack copy of it means the setter stores it into a field of
  the struct type (`this->rot = rot`), not its `int` member (`func_020632ec`,
  89.0 % -> 100 %).
- `bool ok = true; if (key != 0) ok = f(key); if (ok)` gives the `mov r0, #1`
  before the test; `key == 0 || f(key)` branches instead (`func_0206344c`).
- A function-local static array is named `<name>$<n>` in the object; name it
  after its address (`data_020bc4f0`) so the symbol is `data_020bc4f0$1323`.
- A derived destructor that is only `bx lr` (no call to the base destructor):
  the base's empty virtual destructor is inline in the shared header
  (`include/game/unk_vm.h`); the base's own file still emits its out-of-line
  D1 / D0 with its vtable (`unit_02060ADC.cpp`, `unit_02099C78.cpp`).
- Once the derived constructors are compiled, they call the base-object
  constructor `C2`; the `C1` alias at the same address is then dropped from the
  link, so the symbol is named `C2` (`_ZN11Unk02099c78C2EP11Unk020956f8`).
- `delete a[i]; a[i] = 0;` in a loop gave another register allocation than
  the original; an explicit `if (a[i] != 0) delete a[i];` matches
  (`func_02060b98`, 96.2 % -> 100 %).
- `movs r0, r5` before storing a parameter into a field and testing it: store
  then test the field (`e->anim = anim; if (e->anim == 0)`), not the
  parameter (`func_02061298`, 93.7 % -> 100 %).
- A by-value argument read back from the stack (`ldr r2, [sp, #0x1c]` after
  `push {r0-r3}`) is a one-word struct, not an `int`
  (`Unk020680d4Dir`, `func_020619a8`, 98.4 % -> 100 %).
- Stack slots follow the order of appearance of locals, temporaries of an
  initializer going below the later named locals: to put the last local at the
  bottom, declare it early without an initializer (`Unk02098ff0 pos; ...
  pos = f();`), and keep the earlier results named (`func_020613f0`,
  99.6 % -> 100 %).
- A function returning a struct, bound to a `const &` local, keeps the result
  in place and works through a pointer to it; a by-value local copies it to a
  second stack slot (`func_0205e038`, 80.1 % -> 95.7 %; `func_0205e1b8`).
- An inline accessor prevents the hoisting or CSE of the fields it reads: a
  loop over a script block that loads `start` once at the entry and reloads
  `start` and `count` at each test is
  `for (i = block->func_start(); i < block->func_end(); i++)` (both
  accessors; with `func_end()` alone `start` is loaded twice):
  `func_0205e038`, 98.7 % -> 100 %, `func_0205d134`, 96.5 % -> 100 %. A loop
  whose body calls functions reloads the fields by itself: plain
  `block->start + block->count` (`func_0205c8b4`). A field read again after
  a call is `q->func_busy()` (`func_0205ed20`).
- `for (i = 0; i < count; i++) { if (i >= max) break; ... }` for a loop with
  two bounds where the second test sits inside the body (`func_0205f10c`).
- Dead stores of default values before the real ones come from an inline
  constructor (`Unk0206b998Req() : ... order(100) {}`), not an aggregate
  initializer, which copies a `.rodata` template (`func_0205e1b8`).
- `dir.v = d.v` rather than `dir = d` lets the stored value stay in its
  register for the next use (`func_18`, 96.8 % -> 100 %).
- Small structs copied to the stack before their fields are used were passed
  by value to an inline member (`c.func_add(rel)`, `r.func_sub(p)`); a jump
  table instead of a compare chain needs the empty `case 0: break;`
  (`func_0205eed4`, 65.3 % -> 99.8 %).
- The bodies of a `switch` are laid out in source order, not by case value:
  read the order of the case bodies in the original and write the cases in
  that order (`func_0205c8b4`, 95.6 % -> 99.2 %).
- Loops that reload a field at each outer iteration go through inline
  accessors (`def->func_tile(i)`, `def->func_width()`), and a counter shared
  by all the cases of a switch is one local declared at the top of the
  function, not one per case (register allocation; `func_0205c758`,
  78.3 % -> 100 %).
- A field the original never stores before the loop is not initialized in
  the source (`d.unk24` in `func_0205c8b4`): an extra `= 0` adds a store and
  moves the stack slots.
- mwccarm puts a small uninitialized global before a larger one built by a
  static initializer in `.bss`, whatever the definition order; no form found
  for the reverse order (`unit_0205C700.cpp`).
- An 8-byte entry loaded with `ldmia` and stored to the stack before a call
  that receives its two words in r1 / r2: a local copy of the struct passed
  as two `int` arguments (`Value v = values[i]; f(p, v.unk0, v.unk4)`), not
  the struct by value, which spills the arguments on entry (`func_0205d858`,
  62.3 % -> 100 %; `func_0205d608`).
- Stores of a stack object after the call that computes one of its fields:
  an inline constructor taking the computed values
  (`Unk02099c0c node(pairs, count)`), not field assignments
  (`func_0205d72c`, 67.0 % -> 99.9 %).
- A delinked `.data` range that no relocation reaches is dropped by the
  `-dead` link (a delinked unit's section is kept only when referenced): keep
  such bytes in the range of a neighbouring unit whose data is used
  (`unit_0205D4D8.cpp`, 0x020BC2A0-0x020BC2B8).
