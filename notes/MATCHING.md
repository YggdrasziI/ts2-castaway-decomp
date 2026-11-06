# Matching techniques

Compiler idioms that fixed near-misses in this project, each tied to the unit that
proved it. Techniques from the Wii projects (mwcc PowerPC) do not carry over by
default: add one here only once a unit of this ROM proves it with mwccarm.

## Loads, constants and literal pools

- A run of word copies from an extern array where the original never merges
  two loads into `ldm`: declare the array with its size (`extern const int
  data_020ae7cc[20];` rather than `[]`) (`__sinit_unit_02035FEC.cpp`, 60 % ->
  100 %).
- A local array of consecutive ids stored word by word (`add r0, r1, #0x1`,
  `str r0, [sp, ...]`) has a non-constant initializer: `int base = 0xd57;
  int ids[6] = {base, base + 1, ...};`. Plain constants are copied from
  `.rodata` with `ldm` / `stm` (`Unk0202fddc::func_020322b4`).
- A single key passed by address (`func_02054d94(..., &key, 1, 1)`) is a
  scalar local (`u32 key = 0x798b86ac;`): a one-element array with an
  initializer is copied from a `.data` literal (`ldr r0, [r0]`)
  (`Unk02033ee0::func_020354ec`, 97.3 % -> 100 %).
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

- A lone `bx lr` just after a derived class, shared with its base vtable, can be an inline
  virtual of the base: `virtual void func_24() {}` emits it last in the file that first
  builds a vtable with it (`unit_020080C0.cpp`).
- A destructor called before the next statement while the local is declared at function
  level: put the local in its own `{ }` block (`func_28` of `unit_020080C0.cpp`).
## Registers and stack

- `tools/decl_search.py` tries declaration orders, splits and types on all near matches: two passes moved 6 functions to 100 % and 20 closer. Its score is not objdiff's: about one applied unit in four regressed and was reverted, so always gate with `report_diff.py`.
- Library functions written from the ROM (2026-11-01): a register swap between two values read one after the other is often fixed by declaring the second first (`int max = d->max; int min = d->min;`, `int i = 0; const Split *s = ...`, `func_0207e2f4`, `func_0207c004`). Tests sharing one exit with values read on the way are one `if` with assignments in the operands (`(month = d->month) < 1`, `func_0207d164`). A global tick counter that reloads and adds in place is `volatile` (`func_0207bb4c`). A 64-bit product with `mla` on a zero register has both operands cast: `(u64)a * (u64)1000 / (u64)b` (`func_0209e520`). A switch whose table covers case 0 lists `case 0:` next to `default:` (`func_0207e2f4`).
- r0 / r1 flipping on a repeated pattern (`mov r1, r0, lsl #16` at every 5th or so of many identical statements, no visible rule) follows the number of virtual registers before the site: on 30 identical statements the sites repeat with a period set by the statement form alone. So forms that emit the same instructions can still move it: a local for the result and a `u32` local for the index (`func_sprite` in `include/game/unk_screen.h`) fixed nine constructors (98.9-99.9 % -> 100 %). Measure the pattern on a long run of statements, and count the `mov` words in the object rather than reading diffs. An inline stops being expanded past a budget in the longest constructors: there write the locals in a block (`unit_0202E0EC.cpp`). `({ ... })` is an internal compiler error.
- Inline slots of a class come out in the declaration order of their overrides: declare them first in the class to get the original tail (`func_34`, `func_2c`, then `func_1c`, ...; `Unk0204a9f8`). This only works for slots declared in a base: moving a new virtual changes the vtable while objdiff still scores `.text` 100 %.

- A value set to 0 in a branch before its only use (`moveq r4, #0`) may be a ternary in the
  argument: `f(o, flag ? actor : 0)` also gave `actor` a lower register than `this`
  (`func_18` of `unit_0200825C.cpp`, 99.08 % to 99.73 %).

- `add rN, sp, #x` before reading a temporary (`ldrsh r9, [r3, #6]`): the original calls an
  inline member on the temporary, so `this` is a pointer register. An inline free function
  taking `const T &` reads from sp directly. Same for a compare through `add r1, sp, #x`:
  member of the temporary, other value by copy (`unit_020090B4.cpp`, 93 % to 99.75 %).
- Registers rose with the declaration order of the locals in `func_18` of
  `unit_020090B4.cpp`: declaring first and assigning later moved them directly.

- A pointer used in a loop body and declared inside the loop can take the counter's
  register and the other way round. Declaring it at function scope, before the
  `for`, gave the original allocation (`func_0202171c` in `unit_0201E300.cpp`,
  98.52 % to 100 %; `func_02021888` and `func_020214cc` improved).

- Callee-saved registers rotated over a whole function with a parsing loop
  in the middle: move the loop into a `static inline` helper taking the
  output pointer and the field it reads by reference (`const int &id`), the
  field then read inside after the first store; written in place or with the
  id by value, the registers rotate (`Unk02033ee0::func_0203577c`,
  98.1 % -> 100 %).
- `pager.func_14(0, next.func_10()->y);` gives a `mov r1, r0` before the
  pager's vtable load in `unit_02033EE0.cpp`; `int y = next.func_10()->y;`
  first gives the original's direct `ldr r2, [r0, #4]` (98.43 % ->
  98.98 %), the opposite of the gap of `unit_0203B3B8.cpp`.
- Two results of consecutive calls kept in r5 / r6 the wrong way round:
  declare the later one first without an initializer (`u32 height;` before
  `Unk020a7c90 *font = ...;`, then `height = ...;`)
  (`Unk0203b3b8::func_0203bc24`, 99.7 % -> 100 %).
- A local read back from the stack (`ldr r1, [sp, #0x5c]`) where a member was
  compared: the source compared the local array that was copied into the
  member (`keys[0] == ...` rather than `key == ...`) (`Unk02038bcc::func_02039a08`,
  94.0 % -> 94.4 %).
- A result zeroed before an index computation (`mov r?, #0` first): declare
  and initialise it before the index block (`int c = 0;` then the index
  `if` / `else`), not in the branch that reads it (`func_0203b148` of
  `unit_02038BCC.cpp`).
- Stack arguments read with `ldrsh` and stored as bytes: the parameters are
  `short`, not `signed char` (which reads `ldrsb`); the register ones follow
  (`Unk02050640::func_02050bf0`, 91.8 % -> 100 %).
- Callee-saved registers swapped between locals: try every declaration order
  by script; a local initialised by re-reading the field (`int frame = unk64;`
  next to `int base = unk64;`) rather than by copying the other local can be
  needed for the order to work (`Unk02050640::func_02051294`, 97.7 % -> 100 %).
- An `else if (test) A; else B;` whose original conditionalizes B and branches
  over A: write the branches in that order, not `if (!test) B; else A;`
  (`Unk02050640::func_0c`, 99.4 % -> 100 %).
- A clamped parameter whose register is reused by a later index (`sub r6, r1,
  #1` into the register of the clamped time): reuse the parameter for that
  index (`t = count - 1; if (i + 1 < t) t = i + 1;`), not a new local
  (`func_sample` of `unit_02051DA0.cpp`).
- A flag tested twice (`ands r3, r0, #8`, then `cmp r3, #0`) and a value kept in
  one register across a dead-zone clamp: test `flags & 8` directly in both `if`s
  rather than through an `int` local (`Unk02051da0::func_0c`, 99.5 % -> 99.8 %).
- A point copied to a member as `ldr ldr str str` rather than interleaved: an
  inline helper that reads both fields before the stores
  (`func_set(last, p)`); plain assignment, a base-class cast and field-by-field
  statements interleave (`Unk02051da0::func_0c`, 96.8 % -> 99.5 %, x / y registers
  still swapped).
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
- A float rounding of a small pixel constant done at run time (`mov r0, #0x1000;
  bl _fflt; ... _fadd; _ffix`): the value is a local int set once
  (`int countX = 1;`) and converted with
  `(int)(v > 0 ? v * 4096 + 0.5f : v * 4096 - 0.5f)`; the optimizer propagates it
  without folding the float operations, whereas a literal or an inline function
  with a literal argument folds them all (`func_02053ef8`, 76.6 % -> 91.5 %).
  `v * 4096.0f` gives an `_fmul` instead of the `lsl` / `_fflt` pair.
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
- A value kept for the whole function in a stack slot just above the spilled
  parameters, below every local: it is a parameter reassigned
  (`file = archive->func_02093e9c(file);`), not a new local, which takes the
  highest slot (`func_02052a74`, 99.85 % -> 99.99 %). The data tree reads of the
  same function take their slots in expansion order once written as inline
  helpers (`func_named`, `func_value`), after the caller's named nodes (100 %).
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

- A pointer and a loop index swapped (r6 / r7) in a loop that picks a sprite
  per slot: declaring the pointer at the top of the function, before the
  index, matches (`func_0204b984`, 98.8 % -> 100 %).
- `FX32(x)` of a coordinate that grows with the loop index: the original
  converts `x << 12` with the index-derived value in a register
  (`0x100 + i * 0x32` written in the call). A separate `x += 0x32`
  induction variable is strength-reduced to `x << 12` and spills `x`
  (`func_0204b984`, 89.4 % -> 98.8 %). An unsigned value calls `_ffltu`
  (0x020887B0, right after `_fflt`).

- Stack slots go down in declaration order: an object at the highest offset
  that is filled late is declared first, before the objects filled earlier
  (the ray of `func_0204a254`, declared at the top of its block and set
  later by an inline member).
- A struct of two vectors filled with `ldmia` / `stmia` x 3: members that wrap
  the vector (`struct Vec { Unk02098ff0 v; }`), assigned by an inline member
  (`pos = (const Vec &)p;`); with `Unk02098ff0` members the copy is field by
  field (`func_0204a254`, 95.2 % -> 100 %).
- Slots of a base vtable that point to short functions placed at the end of
  the first derived file (after its own inline slots) are inline virtuals of
  the base: every derived file emits them and the first copy is kept.
  Declaring them inline in the base made the kept copies match and raised
  the `.data` of every derived file (the page base `Unk020465bc`, slots 7,
  8, 9 and 13 in `unit_020450D4.cpp`, pages' `.data` 79.5 % -> 88.6 %).
  A file that only calls such slots virtually (the pages' owner) also emits
  them, each right next to the first function that calls it: slots of a
  base found inside an unrelated file, reading the base's layout, are the
  base's inline virtuals too (slots 5, 10, 11 and 17, 0x02044830-0x02044EC0,
  `.data` 88.6 % -> 97.7 %).
- A slot shared by many unrelated vtables, with no vtable of its own class
  anywhere and whose class's only function is an empty base destructor
  (`bx lr`), belongs to an abstract root: a pure virtual destructor with a
  body, so only D2 is kept, and an implicit constructor that stores no vptr
  (mwccarm emits the root vtable in every derived file, nothing references
  it, the link drops it). The screens' root `Unk020a07d4` (slot 12 =
  0x0201D6CC): every page vtable 97.7 % -> 100 %. Its slot 12 is an inline
  virtual kept in a file still in assembly, so it is declared non-inline
  until then (see "Unsolved patterns").
- Inline virtuals at the end of a file come out in declaration order, and a
  new virtual (one the base does not have) declared before the overrides of
  the base's slots comes out first: the owner's func_34, then func_1c,
  func_20, func_24 (`unit_02043FBC.cpp`, `check symbols` failed with slot
  order). With a root that declares the slots, only the new virtuals' order
  fixes the vtable; the overrides can be declared anywhere.
- A lookup through a layout held by pointer (`func_020aa040(top, 4,
  func_020a7b50(&names, hash))`) whose pointer the original loads after the
  inner call: write the nested call in place; an inline helper taking the
  layout as a parameter loads it first and keeps it in a callee-saved
  register (`func_020471b0`, 85.4 % -> 98.8 %; with layouts held by value the
  helper is fine, `unit_02047A8C.cpp`).
- A call whose last argument register already holds a field loaded for an
  earlier test (no `mov r2, #n` before the `bl`): the call passes that field
  (`func_0205f10c(&list, items, list.count)`).
- A loop counter declared at the top of the function (`int i;` then
  `for (i = 0; ...)`) instead of in the `for` changes which callee-saved
  register it gets: the hash / bool swap of `func_02043f0c` (98.3 % -> 100 %).
  Two loops that continue from the same counter (`for (i = 0; i < count;
  i++) ...; for (i = count; i < 6; i++) ...`) share it the same way
  (`func_02043b94`).
- Global pointers the original keeps in callee-saved registers across a loop
  (`data_020bfc9c`, `&data_020c3fc4`): local copies before the loop
  (`u8 *inventory = data_020bfc9c;`), and a value computed before a call
  that the original keeps live goes in its own local (`int count =
  o.colors.v[k] + 1;`) (`func_02042d2c`, 100 %).
- An unsigned compare `cmp r0, #1; bls` on `x - 3` of a `signed char` field:
  `(u8)(signed char)(part - 3) <= 1` (`func_02043b94`).
- Three stores of a member's fields grouped after the computation of one of
  them: an inline setter taking the three values (`slider.func_range(0,
  FX32(n - 1), -0x3000)`), not three assignments (constructor of
  `Unk02041b10`).

### Zero copies of nested grid loops

In a double loop with a running index, `int row = 0; int i = row; for (; row < 3; row++)` gives the
`mov r0, r8` copy of the zero that `int i = 0; for (int row = 0; ...)` misses, and it fixes the pool
offsets after it. With `int x;` declared before these two and assigned in the inner loop, the counter and
`x` take their registers. This took the screen constructors of `unit_02035FEC`, `unit_02038BCC` and
`unit_0203C2E8` to 100 %.

### An `int` local for a `short` argument

`int v = a[n].unk64; b[m].f(v, -1, -1);` makes the original read the argument before it computes the
receiver, and moves the `mla` of the receiver before the stack arguments. A `short` local gives nothing: the
`int` widening is what changes the order (`func_38` of three screens, `unit_02035FEC`, 98.86 % -> 100 %).

### A `u32` index against a signed count

`bge` with the index in the unsigned register order: keep `u32 k` and compare `(int)k < count`. With `int k`
the branches match but the registers rotate.

### Multiplying two shorts

`smlabb` where the original has `mla`: both operands are known shorts. Cast one to `u32`
(`(u32)c.xy.y * layer->info->width`): an `int` local does not help, the compiler still sees the shorts.

### A captured loop test

A `volatile` count read by the loop test and again just after it is reused by the original through
`for (i = 0; i < (n = count); i++)`, then `n` (`func_02094df4`).

### A pointer alias of a local changes the allocation and the guards

A class local used through a pointer (`T child = ...; T *c = &child;`, then `c->f()`) gives the
address its own register, hoisted out of the loop, and can add the second loop guard that a plain
local misses: `cmp rN, #0; ble end; cmp rN, #0; add rM, sp, #x; ble end`. The twelve sprite readers
and `func_020ab57c` of `unit_020AA648` went to 100 % this way. A use made directly on the local
stays `add r0, sp, #x`; a use through the alias is `mov r0, rM`, so the listing shows which calls
go through which. A `const T &child = f()` reference gives part of the effect (99.37 %). An
explicit `if (n > 0)` around the `for` then adds a third test (`cmpgt`): drop it.

## Inlining and emission order

- Inline virtual functions called through an object's vtable are emitted right after
  the first function that calls them, in reverse order of their first call
  (`func_10`, `func_30`, `func_20` after `func_0201ef54`, which calls `func_20`,
  `func_30`, `func_10`; `unit_0201E300.cpp`). This order tells a kept copy's slot
  and the file that keeps it. `#pragma dont_inline on` around one function keeps
  calls the original did not inline; it also turns off its other inline helpers.

- A nested loop with hand-written induction variables can allocate them in the
  wrong order when they are declared in the `for`. Declaring the inner index
  and step variable before the outer loop gives the original registers
  (`Unk0202cdf0::func_0202df0c`, 99.0 % -> 100 %).

- A virtual call on a global object is devirtualized to `bl`. Through an inline
  function returning its address (`func_player()->func_14()`) the call stays
  indirect (`ldr r2, [r2, #0x14]`, `blx r2`) (`Unk0202fddc::func_0203161c`,
  97.62 % -> 98.66 %).

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
- A loop with a start index and a counter (`k = page * 12`, `i` from 0):
  `int i; int k = page * 12; for (i = 0; k < count && i < 12; k++, i++)`;
  the declaration order and the header order both pick the registers
  (`Unk02038bcc::func_0203afd0`, 100 %).
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

- A bool kept in a register then tested again (`tst`, `movne #1`, `moveq #0`, `cmp r0, #0`): an inline helper
  written `if (x) return true; return false;` keeps it; `return x != 0;` folds into the test
  (`func_020a5bec`, 83.89 % -> 100 %). Assigning the helper's result to an `int` local gives the same output.

- A flag word read again right after its test with no store between (`ldr`, `tst`, `ldreq`, `orreq`, `streq`): a
  `volatile` member gives it (`func_020a5d7c`, 97.3 % -> 100 %). That the field was volatile is a hypothesis.
- Copy of an 8-byte value through two registers (`ldr r1`, `ldr r0`, `str r1`, `str r0`): the block
  copy of a wrapper struct, as in `func_set` (`func_020a5f28`).
- Zero words in a vtable are pure functions in this compiler; a virtual that has no inline copy in a derived class's
  unit but sits last in the text is an ordinary definition placed last (`Unk020a5ccc::func_08`): written inline it clashes.

- A constant loaded before an unrelated store and used right after (`mov r1, #0x10`, `str r5`, `strh r1`): the
  assignment sits inside the next condition, `if (unk4 > (unk6 = 0x10))` (`Unk020a6588::func_0c`, 95.24 % -> 100 %).

- Registers permuted among locals: declare them up front, without initializers, and try the orders
  (`func_020a6d38`: `archive`, `file`, `layer`; `Unk020a6dd8::func_0c`: `sprite`, `i`, then `show`).
- A call that passes a word where the shared prototype truncates it to `u16`: call through a cast function pointer
  with an `int` parameter; the output is still a direct `bl` (`func_020a6bcc`, 88.34 % -> 100 %).

- A short branch with a conditional return (`ldreq`, `orreq`, `streq`, `popeq`) that stays a `bne` over the same
  code: an inline helper with `if (x != 0) { ... } else { ... }` gives the conditional form (`func_020a727c`,
  93.68 % -> 100 %); early returns and the inverted test do not.

- A value tested twice with the bool materialized the second time (`ands`, `popeq`, `cmp r0, #0`, `movne r0, #1`,
  `moveq r0, #0`, `cmp r0, #1`): an `int` local keeps it, `int c = f != 0; if (c == 1)`; a `bool` local folds into the
  first test (`Unk020a7d74::func_0c`, 75 % -> 100 %).

## Data layout

- Vtables of a file come out in reverse order of the classes: vtables in class order in `.data` mean one file for
  each class (0x020A690C, 0x020A6A00, 0x020A6DD8).

- A vtable starts 8 bytes before the address the constructor loads: `_ZTV` goes on the two zero words, the reloc takes
  `add:0x8`, and the unit's `.data` ends at the last slot (the zeros after it belong to the next vtable).

- Statics addressed from one anchor but in a different order than declared: one static struct fixes the layout
  (`unit_020A5948.cpp`: `.bss` 50 % -> 100 %). A `const char *const` goes to `.rodata`, a `const char *` to `.data`.

- `-dead` strips a whole unreferenced `.rodata` section of a gap object: splitting a range so that a gap only
  holds data no relocation reaches shifts every later address (0x194 bytes for the digit strings 0x020B59F4).
  Keep such data in the same range as a referenced object.

- A static `u8` array can land in its own `.bss` section, apart from the other statics of the file, and
  the anchored offsets then skip it (`[r0, #0x3c]` for `[r0, #0x64]`). objdiff still shows the `.bss` at 100 %
  because it is all zeros. A `u32` array of the same size stays in the common section
  (`data_020d6c6c`, `unit_020A22FC.cpp`).

- A file boundary from a static: mwccarm addresses all the function-local statics of a
  file from one anchor, so a second static is loaded as `[r0, #0x14]`. If the original
  loads it at offset 0 with its own pool word, the two statics are in two files
  (`unit_02009D08.cpp` / `unit_0200A2EC.cpp`).

- A word in `.data` (value 0) that only a static initializer writes from
  another unit's object (`ldr`, `str`): a namespace-scope `const` object
  with a dynamic initializer (`extern const int x = obj.count;`, `extern`
  for external linkage); without `const` mwccarm puts it in `.bss`, even as
  a one-element array. mwccarm lays it out before the vtable of its file
  whatever the definition order, so a word just after one class's vtable
  belongs to the next file when that file's `.data` starts with a vtable
  (`data_020b95f8`, moved into `unit_0203C188.cpp`). `explicit_zero_data` tables
  do the same (`data_020b7bb4` of `unit_02010E60.cpp`).
- A local static whose `.bss` slot comes after a file-scope object goes behind it
  only if a function comes before the static's own in the file; as the first
  function it comes first. This located the start of `unit_02010E60.cpp`.
- Two loads of one global's field through a pointer call: an inline accessor
  (`func_player()->func_14()`) keeps the `ldr vtable; blx`; a virtual call on the
  object itself is devirtualized.
- A `(u16)` narrowing done twice (`lsl #16; lsr #16` before an index already
  known as `u16`): the index goes through an inline taking `int`.
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
- A head pointer tested, then walked twice (count, then search): testing
  `p->head == 0` and copying it to a local only after the early branch gives
  the original registers; copying it before the test swaps two registers
  (`func_020548b0`, 99.2 % -> 100 %).
- A `frame != 0` test materialized (`movne r0, #1; moveq r0, #0; cmp r0, #0`)
  before `&&`: an inline helper returning `int` (`return frame != 0;`) keeps
  it; the same helper returning `bool`, a `bool` local, `(bool)`, `? :` or
  `if` / `else` assignments are all folded (`func_020543d4`, 98.1 % -> 100 %).
  The `!= -1` helper of `func_0205465c` needed the database pointer as a local
  taken before the previous call (`ldr r6, =db` ahead of the `bl`), passed to
  the helper (92.1 % -> 100 %).
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
- Two reads of the same global through a getter, both spilled before the
  calls that use them (`func_020a18e4()->archive` to sp+0x10 and sp+0xc):
  two locals read first (`a = f()->x; b = f()->x; b->g(a->h(k));`), not the
  nested calls (`unit_0203ECD4.cpp`, constructor 95.6 % -> 97.2 %).
- An `if (b) x &= ~8; else x |= 8;` whose original predicates the `bic`
  (`addne; ldrhne; bicne; bne`) is written `if (!b) x |= 8; else x &= ~8;`
  (`unit_0203ECD4.cpp`, 97.2 % -> 99.4 %).
- A table element compared with a field read before the loop gives
  `cmp element, field` when the element is a local (`int v = t[i]; if (v ==
  p->f)`); written inline, `cmp field, element` (`func_0203f9c8`).
- A run of `s = get(); set(s); use(s);` blocks where the last one reuses a
  register freed by a dead local (`add r1, r4, #k; mov r4, r0`): one local
  per block instead of one reused variable gives that reuse
  (`unit_0203FA44.cpp`, constructor slot loop; same score, closer code).
- A record with an out-of-line constructor and destructor (`Unk020081dc`, C1
  0x020647B0 / D1 0x020647EC) is non-POD, so `a = T();` and `a = *b;` copy
  member by member (one `ldm` / `stm` per array wrapped in a struct, `ldr` /
  `str` per word) as in the original (`func_02064984`, `func_020670fc`). Inline
  members calling C-named functions gave the same copies but not the
  `__cxa_vec_ctor` / `__cxa_vec_dtor` arguments of an array of the record. A
  record returned by value and only read is a temporary
  (`func_020081dc(o).unk28`); its destructor call on every return path comes
  by itself.
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
- A namespace-scope `const` object with a constructor
  (`static const Unk02098bc8 r(...);`) goes to `.data`, not `.bss` nor
  `.rodata`: its storage is reserved with its static size and filled by the
  static initializer (the text field rectangle 0x020B9BC4 of
  `unit_0204D698.cpp`).
- Several `static const` tables of one file are emitted in an order that does
  not follow the declarations. When the original keeps them in address order,
  declare one two-dimensional array (`static const u32 t[11][29];`), drop the
  inner dsd symbols and rewrite their relocations as offsets from the array
  (`add:0x74`) (`unit_0204D698.cpp`).
- Two objects of one file's `.data` (a pointer, then a `static const` table
  with a dynamic initializer) addressed from the first one: the static
  initializer and a function using both load the pointer's address and reach
  the table at +4, a function using only the table loads the table's own
  address. mwccarm does this by itself for such a pair; no struct is needed
  (`data_020b947c` / `data_020b9480` of `unit_02035FEC.cpp`).
- A pointer global in `.data` with value 0 (not `.bss`): `#pragma
  explicit_zero_data on` around `T *x = 0;`, then `#pragma explicit_zero_data
  reset` (hypothesis: it worked for `data_020b954c` of `unit_02038BCC.cpp`).
- A `static const` table emitted before the key list initializer of another
  function when the original has it after: define it just before the
  function that uses it, after the earlier functions (the move fixed the
  order of `data_020ae8e8` in `unit_02038BCC.cpp`; the rule behind it is not
  known).

## C++ classes

- A virtual call on a global object that the compiler would devirtualize
  (`bl _ZN...func_14Ev` instead of `ldr [vtable, #0x14]; blx`) goes through a
  pointer in the source (`Unk020c43a8 *player = &data_020c43a8;`).
- Arguments passed to a member without the `lsl #16 / asr #16` a `short`
  parameter needs mean the parameter is wider: the button setter
  0x02050C64 takes `int`s (its callee code is the same either way).

- Base fields set again before the members are constructed (stores between
  the inline base constructor and the first member constructor call): a base
  constructor argument with a constant value, `Base(true)` doing
  `if (shown) { timer = duration; state = 2; }`; the derived fields then go in
  the initializer list, in declaration order, where scalar inits fall between
  the member constructor calls (`Unk02051da0::Unk02051da0`, 25 % -> 100 %).
- Destructor order at the end of a file: an implicit (or inline) virtual
  destructor is emitted D0, then D1 (`unit_02095BF4.cpp`, `unit_02053204.cpp`);
  D1, then D0 comes from a destructor declared in the class and defined
  (`~T() {}`) at the end of the file (`unit_02053408.cpp`: with the implicit one
  the link put D0 first and `check symbols` failed).
- Two classes in one file whose destructors are only emitted at its end: the vtables of
  the classes and the destructor pairs are ordered by the class definitions. The class
  defined last has its vtable first and its destructors last. In `unit_02053204.cpp` the
  factory is defined before the file class, whose written-out `~T() {}` gives D1, then D0.
- `mov r1, #1`, then `moveq r1, #0` for a flag kept in a local: declare the `bool` apart and assign
  `true` in a statement of its own, then clear it in an `if`. An initializer is propagated into the
  branches, and `a || b` as a value gives two `mov` (`func_020a04d4`, 94 % -> 99.9 %).
- A literal used in a function comes out in the order of first use in the source; a literal in an
  inline comes first, but an inline not called or called in `if (0)` does not count, and the inline
  can change the registers of the caller (`unit_020A0014.cpp`, cause of its original order unknown).
- `mov r0, #1; cmp r0, #1; bne` before a wait loop: the local is an enum (`while (busy == BUSY)`,
  assigned apart from its declaration). An `int`, `u32` or `for` form folds the first test
  (`func_0209fa80`, 98.88 % -> 100 %).
- `b` to a `b` in a `switch`: the cases assign a second local instead of leaving the parameter
  alone, so the block stays (`func_0209f05c`, 92.5 % -> 100 %).
- A local read as signed and tested as unsigned from separate loads: test through a cast of its
  address, `*(u8 *)&p[i] <= 1`; `(u8)p[i]` gives `and` and an `if`-conversion (`func_0209f74c`).
- A pointer static tested with a run-time guard: a `static T &` reference to a global
  (`func_0209f880`, 59.6 % -> 100 %, the form of `unit_02055118.cpp`).
- A member sub-object whose first field is set before its arrays are built: the sub-object's
  initializer list, not its constructor body (`Unk0209f0ac`).
- A value read before a flag that tests it, with the value kept for later tests: `bool moving =
  true; int state = ...; if (state != 0 && state != 3) moving = false;`. The declaration order
  picks the two registers (`func_020a15a8`, 96.7 % -> 100 %).
- `delete p` with a null test on a class with no destructor code: an empty inline destructor in the
  class. Without one the `delete` is a bare call (`func_020a0f0c`).
- A switch whose original jump table covers ids that an earlier test already
  excludes (`if (id < 0) return 0x10;`, then `sub r0, r1, =0xFFFEFEF7`): the
  source lists those negative cases too, written `(int)0xfffefef7` and so on
  (`unit_02053204.cpp`, 100 %).
- A function returning one of several new objects with a single return and a
  separate `return 0` is a switch assigning a local, with `default: return 0;`;
  returning from each case gives conditional `ldmeq` exits (`unit_02053204.cpp`,
  83.9 % -> 100 %).
- `__cxa_vec_new(n, size, 8, ctor, 0)` (a cookie with no destructor): declaring a sized class
  `operator delete[](void *, size_t)` gives it; without it the padding is 0 (`unit_020A4E60.cpp`, 99.23 % -> 100 %).
  The declaration is not needed by anything else in the file: its presence in the original is a hypothesis.
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
- A `.rodata` word no code loads can be a function-local `static const` whose
  value is folded into the code: mwccarm keeps the object all the same.
  `static const u32 hash = 0xa030f2c3;` in `func_02015dd8` gives the last word of
  the `.rodata` of `unit_020142E0.cpp`. In an inline member defined in the class
  body the object comes first in `.rodata` instead (spear unit, reverted).
  The name list sizes of the screens are this form (`static const int size = 0x46;`
  before `entries[size]`); `.rodata` 100 % in seven units.
- Out-of-order pointer to member constants (a state set late in the code with its
  constant early) were reproduced with small inline setters defined at the place of
  the constant (`unit_020142E0.cpp`, `func_go*`); the real source form is unknown.
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
  When the second test is also a pair (`cmp r1, #2; cmpne r1, #1` on the same
  register, no reload, no bool), two `const` inline members do it:
  `if (func_hidden() && func_shown()) return;` (the slider update of
  `unit_02051DA0.cpp`, 93.7 % -> 100 %; with the state in a local, mwccarm
  folds the impossible test away).
  The same holds for a pair followed by a single value
  (`cmp r1, #2; cmpne r1, #1; movne r0, #0` then `cmp r1, #0` on the same
  register): two `const` inline members,
  `if (fade.func_shown()) return true; if (fade.func_opening()) return false;`.
  A state local gives a copy (`mov r1, r0`), a field read reloads it, and a
  static helper taking the state folds the bool (`func_0c` / `func_10` of
  the three screens 0x020471B0-0x0204BEEC, 92.9-95.8 % -> 100 %; the slide
  tests of `Unk02047a8c::func_38`, 99.94 % -> 100 %).

## Control flow

- `sub r0, id, #K` then `cmp r0, #1` / `cmp r0, #2` with each body after its
  own compare: an `if` / `else if` chain on a local `u32 k = id - K`; a
  `switch (id - K)` with two cases puts both compares first (the text
  callback of `unit_0203B3B8.cpp`, 69.0 % -> 99.8 % -> 100 %).
- `cmp #0; beq <case 0 body placed last>; cmp #1; <case 1 conditionalized>`:
  a `switch` with `case 0:` and `case 1:` bodies, not `if (== 0) else if
  (== 1)` (constructor of `unit_0203B3B8.cpp`, 97.5 % -> 98.3 %).
- A switch whose binary search starts from the middle of the keys sorted as
  signed values switches on an `int`: with a `u32` table the cases are sorted
  unsigned and the pivot and literal order change (`func_0c` of
  `unit_0203C2E8.cpp`, 98.0 % -> 100 %, with `case (int)0x...:`).
- A jump table whose first case only leads to the default code has that case
  in the source next to `default:` (`case 0x800000: default:`; the text
  callback of `unit_0203C2E8.cpp`, 96.5 % -> 100 %).
- A mirrored index kept in its own decrementing register (`mov r7, #3` ...
  `sub r7, r7, #1`) next to the column counter is a second loop variable,
  `for (int col = 0, c = 3; col < 4; col++, c--)`; `3 - col` is recomputed with
  `rsb` each pass. Pointers stepped after the compare come from `n++` in the
  same header (`func_38` of `unit_0203C2E8.cpp`, 91.6 % -> 98.6 %).
- A value read once, compared and used as an index before a store to a global
  (`ldrsh; cmp; ldr [table, r0, lsl #2]; movle / movgt; str`) is read before
  the store in the source: set the result first (`if (c <= 5) s = 0x19; else
  s = 0x13;`), then store `table[c]`; the reverse order reloads it after the
  store (`func_3c` of `unit_0203C2E8.cpp`).
- `cmp r0, #0; movne r0, #1; moveq r0, #0; cmp r0, #0` after a call returning
  a pointer is an inline helper returning `ptr != 0` as `bool`.

- Early exits that all return a saved parameter (`movs r4, r1` at the top,
  `mov r0, r4` in each exit) return that parameter in the source, even on paths
  where it is known to be zero: `return false` there gives `mov r0, #0` and
  predicated exits (`func_04` of `unit_0204BEEC.cpp`, 93.4 % -> 99.4 %).
- A two-way store left as a branch (`moveq; strheq; beq` then the other store
  unpredicated) instead of fully predicated: write the `if` with the branch the
  original falls into first, `if (in) a(); else b();` rather than
  `if (!in) b(); else a();` (same function, 99.4 % -> 100 %).
- Two compares joining at one conditional store (`ble` to `cmp r0, #0x10`, else
  `cmp r0, #0x8` and `b`, then a shared `movgt` / `strgt`) are an `if` / `else`
  with the same body in both branches, merged by the compiler; a ternary limit
  (`counter > (low ? 16 : 8)`) puts the limit in a register instead. The `if`
  tests the condition of the fall-through branch (`if (value > 0x19)` for
  `ble`) (`func_0204ec44`, 96.6 % -> 100 %).
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

- A test that returns a constant on one value and a call otherwise, left as
  a branch (`bne` over `ldr; ldmia`) rather than predicated: a `switch` with
  that `case` and a `default` (`func_0204be78`).
- An early exit that branches to the shared epilogue (`beq` to the final
  `mov r0, r9`) instead of a predicated return: nest the rest of the body in
  `if (cond) { ... } return done;` (`func_0204a254`, 90.3 % -> 95.2 %).
- A result returned on a branch (`blt` over the success path, then
  `mvn r0, #0` at the end) instead of a predicated `mvnlt`: write the success
  path first, `if (r >= 0) { ...; return r; } return -1;` (`func_0204a670`).
- `orrs` of two tests before an early return: the bitwise form
  `if (fade.func_hidden() | !active) return;` (`func_38` of
  `unit_02047A8C.cpp`).

- `teq r0, #1; movne r1, #1; moveq r1, #0` for a `bool` argument: `f(g() ^ 1)` with
  a `bool` `g`, not `f(!g())`, which gives `cmp #0; moveq / movne`
  (`Unk02013f8c::func_18`, 98 % -> 100 %).

- A two-word vector copied as `ldr ldr str str` for every assignment in a file:
  assign through a struct wrapping the vector (`Unk02098e70Wrap`), as for the block
  copies of three-word vectors (`unit_02018668.cpp`, 70 % -> 99.8 %).
- A flag word read by `tst`, then reloaded by the `bic` or `eor` of the same test:
  a small class with inline `get` / `set` / `clear`, not a bit-field, whose
  `lsl` / `lsr` pair gives it away (`func_02018d04`).
- Inline helpers kept out of line at the end of the file, in reverse order of first
  call: `#pragma dont_inline on` around the one big caller (`Unk0201a2c8::func_14`).
- A value loaded again before each store on a loop's two branches: a `volatile`
  access through an inline member (`Unk0201a2c8Time::func_put`, hypothesis).
- `adds` where a 32-bit `add` is expected: the sum is computed in `s64`, then
  truncated (`func_020191b4`).

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
- A `new` of a class that calls the base copy `...C2Ev` (and `delete` that calls
  `...D2Ev`) instead of `C1` / `D1`: the object is an empty derived class, with
  implicit constructor and destructor (`class Line : public Unk02090308 {};`,
  `unit_0201D70C.cpp`).
- A class whose only non-pure virtual is defined in the file gets its vtable
  emitted there. When the original has no such copy, define the function
  `inline` outside the class: it stays emitted through the derived vtable, and
  the class vtable is not (`Unk020a07d4::func_30`, `unit_0201C460.cpp`).
- A sparse `switch` tests its cases in sorted order, and the signedness of the
  value sets it: an `int` value tests 0xE0343C1B before 0x4CCC5ACE, a `u32` the
  reverse (`unit_0201D70C.cpp`).
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
- A derived member object called directly (`drawer.func_1c(0, x)`) devirtualizes,
  so an inline base virtual gets its kept copy right after the first user. Defined
  `inline` in that file, it does not emit the base vtable; defined plainly, the
  first non-inline virtual is the key function and the whole vtable lands in
  `.data` of that file.
- Copying an array row by row: `snapshot[i * n + j]` gives a kept running offset
  in the outer loop; a separate `k += n` counter gets its register order wrong.
- A search loop written `for (; py >= 0; py--) { if (test) break; }` keeps the
  original rotated loop; the same test inside the `for` condition does not.
- An inline `bool pop(short &x, short &y)` in `while (pop(x, y))` gives the
  `moveq r0, #0` / `mov r0, #1` then `cmp r0, #0` shape, with the jump to the test
  right after the first push.
- A call argument with no narrowing at the call (`add r1, r0, #2` for a value that
  is not a known short) means the callee takes `int`, even when it stores a short.
- A kept copy of a base virtual whose class has its key function elsewhere: a plain
  definition still emits the base vtable (`.data` 76 bytes too long); `inline`
  keeps the copy, emitted when this file's derived vtable refers to it.
- A class holding a key as its first member, not deriving from it: `C1` instead of
  `C2` for the key constructor and no vptr store in the constructor.
- An argument evaluated before an earlier one (`knob` first): take it in a local,
  arguments are evaluated left to right.
- An archive call whose argument loads after the archive: an inline returning the
  archive makes the load follow it, a direct `f()->archive->g(field)` loads it first.
- A table of string pointers whose strings follow the vtable in source order, in
  the table's order, is a `static` local of the function that reads it. At file
  scope the same strings come out sorted by length and before the main `.data`
  section, which shifts everything. The symbol becomes `<name>$<n> ... local`
  (`data_020b7ec8$645`, `unit_02013258.cpp`, `.data` 0 word left).
- A file-scope table defined after a table that points to it needs its `extern`
  declaration first; the extern-declared tables are emitted after the other
  definitions (`data_020b7dd8`, `data_020b7e2c`, `unit_02013258.cpp`).
- Two locals swapped in the registers with every declaration order tried: try
  `u32` for one of them. `u32 x` for a value only passed on, not `int x`, moved
  it above the loop counter (`func_14` of `unit_02013258.cpp`, 99.86 % -> 100 %).
- `bars[index - 1]` after `index - 1 > 0` reuses the difference; `(&bars[index])[-1]`
  gives the original's `add r0, r9, r1, lsl #2; ldr r0, [r0, #0xd4]`
  (`func_02013b04`).
- A name table with many readers can still be a `static` local: put it in an
  inline helper with the guard as an argument (`func_sound(index, a, force, b)`).
  Calls show as `mov r12, #0` after the table load, `str r12, [sp]` before the
  `bl`; a written-out call stores the zero first (`unit_02018668.cpp`,
  `func_02018ca0` 85.4 % -> 99.9 %). Give `symbols.txt` the mangled `_ZZ...` name
  (`local`), or objdiff stops pairing the table and `.data` drops to 0.
- Open: in `unit_02018668.cpp` the original addresses its pointer to member
  constants from the table (`data_020b8624 + offset`), table first, constants in
  descending creation order; ours are ascending in a separate block, as they are
  in the original `unit_02013258.cpp`.
- Pointer to member constants come out in descending creation order under `ipa file`
  and in ascending order without it (2.0/sp1p5, game flags, scratch files). A
  `#pragma ipa file` at the file start has the same effect as the flag: on
  `unit_02018668.cpp` it keeps the ROM identical and moves the constant order toward
  the original's (sequence similarity 0.27 -> 0.43), but the report loses 52 bytes
  (`func_14`, `func_02018d04`), so it is not kept. Creation order under `ipa file`,
  from scratch tests:
  - inline members defined in a class body first, last member first, so their
    constants end the block;
  - then the functions defined outside the class, in file order, statement by
    statement;
  - an `inline` function defined outside the class creates its constants where it is
    defined, and a function above it in the file still inlines it;
  - a constant in an inline function is created once for all its callers.
  The original has 36 constants and ours 39, which fits helpers that are inline in
  the original and written out in ours (hypothesis). Not explained yet: in the
  original, the constant of `func_02018798` is created before those of
  `func_020186e0`, `func_0201870c` and `func_02018730`, which precede it in `.text`.
  The whole `unit_02018668.cpp` under `ipa file` does not follow these rules either:
  its order is mixed even with the game class bodies blanked (fish only: the constant
  of `func_020186e0` first, then the class body ones, then the rest descending). The
  order does not move with longer names or shifted `@` numbers, so it is structural.
- Data object sort (from advance-wars-dual-strike-decomp `tools/mwcc_order.py`, CC0,
  commit 47864817d, read only): mwccarm 2.0 heapsorts a file's data objects by size,
  starting from the reverse definition order; the sort is not stable, so objects of
  equal size (all pointer to member constants are 8 bytes) come out in an order that
  depends only on their positions. DQIV-DECOMP adds unreferenced, dead-stripped
  objects to move that order. The model gives exactly the order of a 40-constant
  scratch file under `ipa file`. It does not explain `unit_02018668.cpp`: under
  `ipa file` the constants and the table share one section, and in the original
  the strings and vtables are not sorted by size, so the original file was likely
  not built with `ipa file`. Every mwccarm 1.2, 2.0 and dsi version gives our order
  for this unit (scratch sweep): not a compiler version difference.
- Without `ipa`, the constants of inline member functions defined in class bodies
  are not emitted in `@` number order (two-class scratch test: `a2 a0 a1`, `b0 b2
  b1`); their order matches the symbol table order of the target functions. Rule
  not worked out.
- A class whose constructor is inlined in its factory, with D1 (no vptr store),
  then a virtual, then D0 after the factory: everything is defined in the class,
  with `virtual ~X() {}` written out. The implicit destructor gives the order
  D0, D1, virtual (`unit_02011524.cpp`).
- A string literal in an inline constructor is a global `_ZZ<ctor>Es`: no `local`
  in `symbols.txt`, and its `.data` follows the vtable (`unit_02011524.cpp`).
- States before the factory, then D1, the virtuals and D0 last: the whole class is
  defined in its body (`unit_020116E0.cpp`, the same as `unit_02011524.cpp`). The
  `.text` order then does not depend on the member order, but the order of the
  pointer to member constants does. Their bodies are parsed last member first.
- `#pragma dont_inline` has no effect inside a class body: an inline method that
  needs it goes outside the class as `inline`, under the pragma, and keeps its place
  in the emission order (`func_18` of `unit_020116E0.cpp`).
- Two copies of one string in a file are not a file boundary when the users are
  inline: `-str reuse` does not merge strings of inline functions (`head` and the
  jam track name in `unit_020116E0.cpp`).
- `if (x) { f = 1; } else { f = 0; }` on a byte member gives the conditional `add`
  and `mov` of each branch; `f = x != 0` gives one store with a late `add`.
- Block copy of a return value under `dont_inline`, no `operator=` call: a POD
  initialised from a cast (`Pod head = (const Pod &)f();`); assigning calls the
  out-of-line operator.
- `#pragma explicit_zero_data on` places a zero table in `.data`, before the vtable of
  the file: a table after a vtable therefore opens the next file (`unit_0200E144.cpp`,
  `unit_02010920.cpp`).
- A local static goes after a file-scope `.bss` object only if a function precedes it
  in the file.
- A vtable symbol at the header start needs relocs `to:<ZTV> add:0x8`; inner
  references to a `.bss` object need `to:<sym> add:0xc`.
- Struct assignment of a wrapper class in an array (`history[i] = ...`) keeps
  `add rX, base, i, lsl #3`: no strength reduction. Assign from a direct cast of a
  temporary, `(const Wrap &)Vec(x, y)`, not through an inline helper: the temporary
  then stays on the stack with `[sp, #n]` loads (`func_0200f0e0`, 100 %).
- Small getters called with `bl` from a constructor inlined in its factory: plain
  non-inline functions, declared before the class, defined after the factory.
- Open: the original `Unk0200f174` constructor packs four fields from an unfolded
  zero with one register per step and no masks; explicit masks and nested inlines
  fold the zero, a union bit-field adds masks.
- A test materialised as `movne r0, #0; moveq r0, #1; cmp r0, #0` that bool helpers,
  ternaries and inline levels all fold: the helper returns an `enum`; a value kept in
  `r2` across a compare then follows (`Unk0200b04c`, 83 % -> 100 %). The same unit:
  `movs r0, r5` for a pointer tested after a store comes from re-reading the member
  into a local (`a->f = f; p = a->f; if (p == 0)`).
- `movne r0, #0; moveq r0, #1` on a returned test, not followed by a `cmp`: same cause, an
  inline helper returning an `enum` (`func_18` of `unit_02004938.cpp`, 99.88 % -> 100 %);
  `bool` and `int` helpers, ternaries, `if` forms and pointer members give the reverse order.
  The enum needs a function returning `int`: returned as `bool` it adds a `cmp` and two moves, so a
  `bool` slot is declared `int` in that file (`func_08` of `unit_02003AB0.cpp`, 91 % -> 100 %).
- A string literal in a table initializer lands before the table, even at the end of
  the file; the original has such strings after the vtables, in reverse order of use
  (`unit_0200B23C.cpp`, open).
- A file whose pointer to member constants are all read from one anchor
  (`[r0, #0x108]`) can be written as one table object: same shape of the loads and
  the same `.data` words; the second word of a compared constant keeps its own anchor
  in the original (`unit_0200B23C.cpp`, open).
- A `complete` unit can be at 100 % in objdiff and still fail the link check: inline array element constructors are emitted after their user, as weak symbols. When the original has them before, define them as plain functions at the file start (`Unk0200dd90Part`).
- A byte field passed to or set from a `bool` parameter without a `cmp` or an `and #0xff`: the field is a `bool` too (`Unk0200dd90Part::flag`).
- A `new (p) T()` in a factory needs only the inline constructors: a class with a declared, never defined non-inline virtual references `_ZTV<class>` without emitting the vtable, so the vtable stays with its own file (`unit_02007204.cpp`).
- A loop that runs before the vtable store of the class is the constructor of a second, vtable-less base class; a member set before a member constructor is an initializer list entry. Both are in `unit_02007204.cpp`.
- A class destructor at the end of a file, with no call to it left in the code: the implicit destructor of a temporary written as an expression statement (`Unk02007c84();`). The call is inlined and the D1 is still emitted; a named local or a user-declared inline destructor does not emit it (`unit_02007204.cpp`).
- A base constructor called from a derived constructor is the `C2` symbol: name the address `C2` in `symbols.txt`; the `C1` alias at that address is then dropped.
- The test "the object's front cell differs from the sim's cell" (`unit_02006CAC.cpp`, also 0x02008D48, 0x020090B4, 0x0200825C): an inline returning the cell, written as one nested expression, compared with `func_front(o) != sim->func_14()`, `operator!=` taking its cell by value. The result temporary takes the top slot, the sim's cell the next, then the expression's temporaries in creation order. An inline taking the cell and returning `bool` gave 99.7 % at best.
- Stores scheduled differently in a block with the same statements: a local holding an intermediate result (`actor = func_02002414(owner); sim = actor->sim;` vs. `sim = func_02002414(owner)->sim;`), 93.4 % -> 100 % (`unit_02006CAC.cpp`).
- A field reloaded for one bit test while other tests of the same field share a load: the reloading test goes through an inline const getter (`func_has`); a local or another block shape does not reload (`unit_020066B4.cpp`).
- Registers one step off with a sign-extended byte kept in a local: the local is an `int`, not an `s8` (`unit_02005E30.cpp`, 98.6 % -> 99.6 %). Two locals with swapped registers although their loads are in the original order: declare them in the other order, the scheduler keeps the loads (99.6 % -> 100 %, same file). Declaration order at the top of the function changed nothing there.
- D0 before D1 in `.text`: the destructor is implicit (none declared in the class); `virtual ~T() {}` gives D1 then D0. objdiff scores both orders 100 %, only the module check sees it (`unit_02005AF0.cpp`).
- A vector member copied with `ldm` / `stm` and reread afterwards: a wrapper struct
  (`Unk02005ad4Pos { Unk02098ff0 v; }`) assigned from a cast
  (`pos = (const Pos &)f();`); the vector class alone is copied field by field and its
  fields are forwarded from registers (`func_0200527c`, 94.4 % -> 99.9 %).
- Hoisted stack addresses in a loop (`add r7, sp, #x` before the loop, `ldrsh r0, [r7,
  #4]` inside): a reference or pointer bound to the temporary, not a value. Its register
  follows the declaration order: `const Cell *c;` declared before `map`, assigned with
  `c = &(const Cell &)f();`, gave the original allocation (`func_02005654`, 99.67 % ->
  100 %).
- A local declared before a variable that a call result initialises swaps their
  registers: `int speed;` before `sim` (`Unk02005ad4::func_18`, 98.9 % -> 100 %).
- A `return 1` placed before the `return 0` at the end of the function: `if (ok) { ... }
  else { return 1; } return 0;` (`func_0200527c`).
- A `Vec` virtual call with only its `y` used, where the frame seems 4 bytes too large:
  the result is a 12-byte vector, not an 8-byte pair (`func_02005654`).
- A `swpb` store comes from assigning a `bool` field: a `u8` source then gets normalized
  (`movne/moveq`), so the source field is a `bool` too (`unit_0200A5E0.cpp`).
- Arguments are evaluated right to left: an inline taking a call result by value plus
  another call places the calls in reverse order (`unit_0200A5E0.cpp`).
- A compare order different from `operator==` (here `+2, +0, +3`, result 1 then cleared)
  is a separate `operator!=`, taking its cell by reference while the parts stay by
  value; the by-value copy comes from an inline around it (`unit_0200A5E0.cpp`).

- A table of the `.data` that is all zeros in the ROM, filled by code on first use behind one
  guard word of a shared `.bss` block, one address per element: a `static const` local array of
  a struct with an inline constructor. Without `const` it goes to `.bss` next to its own guard;
  without the constructor the stores fold on one base (`unit_020AA648.cpp`). The table sits where
  it is declared: after a call that comes first in the code.
- `(int)` of a float computed before a virtual call but converted after it: an inline returning
  the float, whose body runs before the call (`func_fixed`, `unit_020A8228.cpp`).
- A local that lives across one loop only: separate loop variables per loop, not one shared set,
  free the registers of the other loops (`func_020a87f4`, 96.6 % -> 99.3 %).

## File bounds

- Several classes in a row: the compiler writes the vtables of one object in reverse order
  of their first use and emits their inline functions at its end. Name, vtable and inline
  functions of each class following each other in the ROM mean one object per class
  (`unit_02000C68.cpp`, `unit_02000DF0.cpp`); vtables in a block after shared names mean
  one object for the group (`unit_0200125C.cpp`).
- A default written `x = x ? x : c;` rather than `if (x == 0) x = c;` swaps the registers
  of the neighbouring locals (`func_02001fdc`, 98.9 % -> 100 %).
- A local declared without its initializer, above another local, swaps their registers
  (`Unk02001f08::func_14`, 99.6 % -> 100 %).
- A `__sinit` that keeps the address of a sub-object in a register instead of folding it into
  the object's offset: write the inline constructor of the sub-object through a local pointer
  (`T *self = this; self->a = ...; self->b = ...;`). Initializer list and plain assignments
  all fold (`unit_020A18F0.cpp`, `__sinit` 45 % -> 100 %).
- A table entry read into its own local before the expression (`u32 mag = table[y & 1];`)
  gives the expression a free register (`func_020a1f84`, 96.2 % -> 100 %).
- Fields read from one word: the order of the locals sets the order of the masks and the
  registers; try all permutations (`func_020a1aa4`: year, day, month, not day, month, year).
- An access by the static object's own name, compiled as an offset in the unit's `.bss`:
  define the object after its uses (`func_020a1aa4`).

## Library code (2026-11-01)

- `beq top` + `b next` in the original where ours has `bne next` + `b top`: write the
  exit first, `if (x) { break; } continue;` (or `goto` a label in front of the code
  after the `if`), not `if (!x) { continue; }`. It also fixed the order of the hoisted
  `add rN, sp, #...` in `FindExceptionHandler`.
- `dsd` splits a catch block or a function tail into its own symbol: the `.exceptix`
  entries give the real function sizes.
- A whole file off by one pattern is a build setting: `mov pc, lr` against `bx lr` was
  `-interworking`; a register-level gap in only some functions was a service pack (sweep
  the compilers on the function before changing the source).
- CI builds under wibo: a function compiled to 100 % on Windows can differ there (jump
  table on the density limit, `notes/COMPILER.md`). Check the CI run before building on
  a new `complete` file.

- Hand-written library `asm`: a function nothing calls is dropped by the `-dead` link and
  every later address moves; `#pragma force_active on` keeps it. Without `global` labels,
  a label reached from another block must be its own `asm` function; a branch into the
  middle of another function is a `dcd`, whose value depends on the layout.
- objdiff stays below 100 % on such files (`_fdiv` 91.08 %) with identical bytes: data
  decoded as `<illegal>` in the original, `dcd` branches, pool targets. `Check ARM9
  main: OK` is the proof there.
- Two `.bss` objects in the wrong order whatever the definition order: `.bss` is sorted by
  size inside an object, so they are two files (`fp_status.c`, `fp_handlers.c`). dsd also
  wants a `.bss` symbol of `symbols.txt` global: no `static`.
- Library functions with few hits in a sweep: score each undelinked function against every
  compiled reference function of about the same size instead of requiring an exact match.
  It finds the SDK function behind most `func_` names, and the rest of the gap is usually
  names, constants or `.bss` offsets. Functions compiled in reverse source order (1.2)
  give the file order.

Two 32-bit stores through one base register, the high word 0 or the low word 0, come from a single write to a `vu64` register (hardware divider, `libs/nitro/src/fx/unit_02077AE4.c`).

`asm` functions of a file are emitted in source order, after and not reversed like its C functions: keep a mix of both out of one file, and write `asm` functions in address order. A khdays score below 100 % may hide only unrelocated `bl` words; a function exact by bytes may still target other symbols, which only the ROM relocations tell (`.rela.text` in mwccarm objects).

A khdays function off by one or two words is mostly a different field offset, not different code: this ROM's SDK has shorter structures (`NNSSndStrmPlayer` 0x170, one word less than khdays; `OSThreadInfo.list` at 8; `CARD` backup assert at 0x02000B88). Compare the words first, then fix the type, not the code. Note `ldrh` immediates are split: `e1d000b2` is offset 2, not 0xb2.

Link-time constants without relocation (`SDK_IRQ_STACKSIZE`, `SDK_SYS_STACKSIZE`, `SDK_SECTION_ARENA_DTCM_START` as function addresses) cannot be written as C constants, the compiler folds them: `func_0207b5f4` stays unmatched until they exist at link time.

- Value read through an inline helper is loaded before the operands of the comparison: `v == get()` with an inline `get` loads the register first, unlike a macro (`PM_GoSleepMode` VBlank loops). Likewise `SND_CalcDecibel` as an inline keeps one saved register per term (`NNSi_SndPlayerMain`); a plain table read saves fewer registers and shrinks the function.
- `block + size` on a `char *` keeps the pointer as first operand whatever the source order; write `size + (u32)block` to get `add rd, size, block` (frame heap head allocator).

## Data sections (2026-11-01)

- The compilers put each `.bss` and `.data` variable in its own section and sort them by
  size inside an object. In the binary, a drop in size between neighbours therefore marks a
  file boundary. Equal sizes keep an odd order: try the declaration permutations.
- Initialized objects with relocations sort apart from those without, so a run mixing the
  two needs separate objects (`locale.c` split in three).
- A variable that is all zero goes to `.bss`, even initialized. Merge it with a non-zero
  neighbour when the binary has it in `.data` (`data_020bcca0`).
- The linker aligns each object section to 4: two 2-byte-aligned neighbours cannot be two
  objects. They are members of one object: drop the inner symbols, use `add:` relocations
  (`data_020c5700`, 28 bytes).
- A code literal naming an inner address can force two objects: `data_020b38e8[i + 1]`
  reuses one literal and loses 4 bytes of code, so the arc cosine table stays two arrays.
- objdiff pairs data by symbol. In a partly matched unit, a literal only scores once the
  target symbol has the `@<n>` name of the object and the exact size (`data(byte[<n>])`),
  without padding. Pair them on bytes, or on the relocated function for a method pointer
  constant, never by guess. Keep the name of a symbol used from another unit.
- A base class whose virtuals live in far files emits no vtable copy in the derived units.
  Declaring those slots `inline virtual` without a body in the header emits the copy and
  keeps the far definitions as they are (`unk_element.h`, `unk_widget.h`).
- Symbols 8 bytes into a vtable are its first slot: drop them and use addends.
- A static initializer in a gap belongs to the unit that defines the object: the order of
  `.init` follows the units. Name it `__sinit_<file>`; keep it global when a library uses
  its address. The compiled object size shows when neighbouring `.bss` symbols are members.
- The bytes between the last object and the end of `.data` or `.bss` are section padding,
  not part of a unit.
- Vectors that the original keeps on the stack while ours go to registers or to the result:
  hold them in a struct with `int v[3]` (named fields get promoted, arrays do not), and
  copy that struct to get `ldmia` / `stmia` (`func_0205e87c`).
- `-a - b` folds to `add` then `rsb`. `int n = -a; n -= b;` keeps `rsb` then `sub`.
- A stack parameter the original loads into a register (and maybe spills) while ours reads
  the stack each time: `const int w = width;` survives where a plain local is copy-propagated
  away. Inside a loop the same form stays in the loop and gets hoisted (`func_02092f50`).
- Clock field writes that go through a hoisted address: `volatile u32 *p = &v;` in the inline,
  not a cast at each access (`func_tick` of unit_0200B23C).
- Literal pool words in the wrong order (the same words, swapped, and the registers of the
  loop-invariant addresses swapped with them): hold the global address in a local declared
  at the function start (`void *db = data_020c3fc4;`), one per address, in the order of
  the original pool. `func_02066d1c` (99.7 % -> 100 %: `inv` then `db`) and the
  `Unk020724cc` constructor (95.7 % -> 100 %: `db` alone puts the key before it). Five
  other functions show swapped pool words only (`func_0200bab4`, `func_18` of
  unit_020116E0, the `Unk0202aef4` constructor, `func_02039a08`, `func_020573a4`).

## Source permuter

`python tools/permute.py <unit> <symbol> [--seconds N] [--workers N] [--out DIR]` searches
random source edits of one function (swapped statements, moved declarations, split
initializers, `const`, commuted operators, local copies) and scores each compiled variant
against the original bytes, masking relocated words. On a hit it reverts the edits that are not
needed and writes the body to `<out>/<symbol>.txt`; it never writes into the repository.

- Use it for a same-size function whose gap is registers only: it found `func_02093a9c` in 20 s
  after 720 hand-tried orders. A 60 s pass over the 245 unmatched functions matched 7 (2152 bytes).
- Its result proves the bytes, not the source: declarations it moves can look unnatural, and
  an unused declaration can be what makes the match. Keep them only if the report stays at 100 %.
- A function whose size differs starts at a score above 5000: the gap is structural, fix that first.
