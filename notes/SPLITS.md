# Splits and region map

A delink that builds proves the bytes, not the translation unit: dsd copies the
original code and data into the delinked objects, so a wrong boundary still links.
A unit boundary is proven only once the unit is decompiled and `complete`.

## Modules

| Module | Range | Sections |
|---|---|---|
| ARM9 main | 0x02000000-0x020D7160 | `.text` 0x02000000-0x020ACC60, `.exception` -0x020ACD24, `.exceptix` -0x020AD024, `.init` -0x020AE514, `.rodata` -0x020B6E44, `.ctor` -0x020B6EC4, `.data` 0x020B6EE0-0x020BDFE0, `.bss` -0x020D7160 |
| ITCM (autoload) | 0x01FF8000-0x01FFB0C0 | `.text` 0x01FF8000-0x01FFB0BC, empty `.bss` |
| DTCM (autoload) | 0x027E0000-0x027E0080 | `.data` -0x027E0060, `.bss` -0x027E0080 |

## Region map

Drawn on 2026-10-25 from two kinds of evidence:

- **Library fingerprints**: `tools/compiler_sweep.py` (2.0/sp1p5, project flags) on the
  CC0 sources of twewy (`libs/{nitro,c,runtime,cri}`) and khdays-decomp
  (`libs/{nitro,nns,msl}`): functions found at exactly one address, 8-byte and
  mid-function hits ignored.
- **Call direction** (direct calls of `relocs.txt`): a library never calls the code
  linked against it. The library block below has **no direct call** into
  0x02000C68-0x02073ED0, and the block inside it that NitroSDK and MSL never call
  starts at 0x02089780; NitroSDK makes one call into the block above it
  (0x0207B0FC -> 0x02089368, runtime or MSL).

- **Prologue style** (`notes/COMPILER.md`): NitroSDK and NitroSystem are built with
  mwccarm 1.2 (`stmdb {lr}` + `sub sp, #4`), the rest with 2.0 (`stmdb {r3, lr}`).
  The last 2.0 prologue of game block 1 is at 0x02073D08 and the first 1.2 one at
  0x02073FCC; engine block / NitroSystem: 0x0209A3C4 / 0x0209A7BC; NitroSystem /
  game block 2: 0x0209ED0C / 0x0209F74C. Both agree with the call-direction bounds.

Bounds marked ~ are within one or two small functions (a leaf called from both
sides cannot be placed by calls alone).

| Range | Content | Evidence |
|---|---|---|
| 0x02000000-0x02000800 | BIOS call veneers (Thumb), secure area | dsd analysis |
| 0x02000800-0x02000BA0 | crt0: `Entry`, `MIi_UncompressBackward` 0x02000950, `AutoloadCallback`, `BuildInfo` / nitrocode / `[SDK+NINTENDO:BACKUP]` | ROM header entry, autoload hook 0x02000A74, khdays fingerprint |
| 0x02000BA0-~0x02073ED0 | **Game code, block 1** (`main` first) | calls into everything below; no library fingerprint |
| ~0x02073ED0-0x02080114 | **NitroSDK** | fingerprints from 0x020755F4 (`CP_SaveContext`) to 0x0207F540 (`PMi_PrependList`); 0x02073EF0 is called by FS and calls OS card-bus functions |
| 0x02080114-~0x02089780 | **MSL C and the C++ runtime** | `.exceptix` covers 0x02080114-0x02085EEC (the only code built with exception tables); `round_decimal` (printf.c) 0x020818AC, `strcpy` / `strncpy` / `strcmp` 0x02082C28-0x02082D40, `sys_*` console I/O 0x020841B4, `__DecodeSignedNumber` 0x02084278, `__PopStackFrame` 0x02085D24; NitroSDK and MSL never call above 0x02089780 |
| ~0x02089780-0x0209A740 | **EA engine code** (never calls the game blocks) | built with 2.0 like the game (`stmdb {r3, lr}` prologues, none of the 1.2 SDK style: `notes/COMPILER.md`); heavily called by game code (e.g. 559 calls into 0x02099000-0x0209A000); `FontMetrics` / `Character` XML keys (0x0208E96C-0x0208F5EC), `"    File %s"`; the runtime calls it (0x020857B8 -> 0x0209984C, 0x02099864: hypothesis, the allocator behind `operator new`) |
| 0x0209A740-~0x0209F0AC | **NitroSystem** (NNS) | `NNS_SndArc` dispose callbacks 0x0209B97C-0x0209B994, `NNSi_SndFader*` 0x0209E798, `NNS_Fnd` list functions 0x0209E854-0x0209EA64; no call from the SDK or MSL into it |
| ~0x0209F0AC-0x020ACC60 | **Game code, block 2** | calls game block 1 (e.g. 0x0209FA80), the engine block and NNS; strings `build/data/text/*.nitro_text`, `ROM_Euro/source/archives/text.nitro_archive`, sound and micro-game messages |
| 0x020ACC60-0x020AD024 | `.exception` (-0x020ACD24) and `.exceptix`: C++ exception tables | `.exceptix` entries are (function, size and flags, action), 64 of them, for functions 0x02080114-0x02085EEC only |
| 0x020AD024-0x020AE514 | `.init`: 32 `__sinit_*` | `.ctor` 0x020B6E44-0x020B6EC4 |
| ITCM 0x01FF8000-0x01FFB0BC | 57 functions. Hypothesis: 0x01FF8000-0x01FF8114 EA (calls game block 1 and the engine block); 0x01FF8114-~0x01FF84D0 NitroSDK (1.2 prologue at 0x01FF8174, khdays fingerprint at 0x01FF8114, calls only NitroSDK, the IRQ handler at 0x01FF8374 references the DTCM); ~0x01FF84D0-0x01FFB0BC EA (2.0 prologues at 0x01FF84D0, 0x01FF8D4C, 0x01FF9128; calls the engine block) | `itcm/relocs.txt`, prologue style |

Link order read from this map (hypothesis): game objects, NitroSDK, MSL / runtime,
EA engine objects, NitroSystem, game objects. Inside NitroSDK the modules found are in
alphabetical order (CP, CTRDG, FS, GX, MI, OS, PM), so 0x02073ED0-0x020755F4 is
probably CARD (not fingerprinted).

Commands: `python tools/compiler_sweep.py --ref <project> --compilers 2.0/sp1p5
--min-size 8 --json out.json <sources>` (khdays: add `--include
<khdays>/include/{nitro,nnsys,game}`, and batches of ~150 files on Windows).

## Units

| Unit | Bounds | Content | Status |
|---|---|---|---|
| `src/game/unit_0209612C.cpp` | `.text` 0x0209612C-0x020962EC, `.data` 0x020BD50C-0x020BD52C (hypothesis: each resource file class of this region starts its file with its constructor; the vtable is only used here) | resource file class `Unk0209612c` (derived from `Unk0209487c`, `include/game/unk_file.h`): block 0x800, array of 20-byte elements `Unk020962d0` (`new[]` through `__cxa_vec_new`), overrides of two virtual functions | complete |
| `src/game/unit_020962EC.cpp` | `.text` 0x020962EC-0x02096348, `.data` 0x020BD52C-0x020BD54C (same hypothesis) | resource file class `Unk020962ec`: constructor and destructors only | complete |
| `src/game/unit_02096348.cpp` | `.text` 0x02096348-0x02096A74, `.data` 0x020BD54C-0x020BD56C (hypothesis: the destructors of the class with vtable `data_020bd52c` close the file before, its own destructors close this one; the vtable is only used here) | resource file class `Unk02096348` (derived from the file class `Unk0209487c` of 0x02094xxx, `include/game/unk_file.h`): cached blocks 0x40 / 0x41 / 0x45 / 0x46, lookup by name hash, typed entries in blocks 0x42-0x44; node handle `Unk0209674c` (children, name hash, data entry) | complete |
| `src/game/unit_02096A74.cpp` | `.text` 0x02096A74-0x020970E0, `.bss` 0x020C7F74-0x020C7F80 (hypothesis: the destructors of the class with vtable `data_020bd54c` before, button state after; the data have no other user) | system set-up: projection matrix, start-up sequence (power, interrupts, VBlank handler, input set-up, `new Unk0208a0a8`), 3D display settings, VRAM bank allocation and VRAM heaps 4-7 | not complete: 9 / 10 functions at 100 % (`func_02096dac` 89.5 %) |
| `src/game/unit_020970E0.cpp` | `.text` 0x020970E0-0x020973BC, `.init` 0x020AE310-0x020AE33C, `.ctor` 0x020B6EA0-0x020B6EA4, `.bss` 0x020C7F80-0x020C8034 (hypothesis for `.text`: graphics setup code before, another object setup after; the data are the objects its code and `__sinit` use) | button state: held / released / pressed masks from KEYINPUT and the ARM7 X / Y copy, per-button press, held and idle counters (`Unk020c7f8c`, built with `__cxa_vec_ctor`), queries with an optional swap for the other hand | complete |
| `src/game/unit_020973BC.cpp` | `.text` 0x020973BC-0x02097434, `.data` 0x020BD56C-0x020BD570, `.bss` 0x020C8034-0x020C8048 (hypothesis: button state before, touch screen state after; the 16-byte arrays `data_020c8048` / `data_020c8058` it clears belong to another file, since `.bss` is sorted by size) | one set-up function: three calls, clears `data_020c8034` and the two arrays, resets `data_020bd56c` | complete |
| `src/game/unit_02097434.cpp` | `.text` 0x02097434-0x02097A58, `.init` 0x020AE33C-0x020AE384, `.ctor` 0x020B6EA4-0x020B6EA8, `.data` 0x020BD570-0x020BD578, `.bss` 0x020C8068-0x020C80A4 (hypothesis for `.text`: another file's object setup before, fixed-point helpers after; the data are the objects its code and `__sinit` use) | touch screen state: static object `Unk020c8068` (current / pressed / released points, drag, tap counters), per-frame update from the touch panel driver, press / release / down / up / drag queries per screen, drag and double-tap thresholds | complete |
| `src/game/unit_02097A58.c` | `.text` 0x02097A58-0x02097B6C (hypothesis: touch screen state before, the 3x3 matrix after) | 20.12 fixed-point helpers: 16-bit wrapper, 64-bit and 32-bit square roots through the hardware root unit, a tail call, arc cosine from the 2049-entry table `data_020b38e8` (left in the original binary) with linear interpolation | complete |
| `src/game/unit_02097B6C.cpp` | `.text` 0x02097B6C-0x02098094 (hypothesis: fixed-point helpers before, the 4x4 matrix after) | 20.12 fixed-point 3x3 matrix `Unk02097b6c` (stored by column; `include/game/unk_matrix.h`): constructors, identity, scale, product, transpose, vector product, rotations about X / Y / Z, rotation from three angles | not complete: 11 / 12 functions at 100 % (`func_02097f78` 51 %) |
| `src/game/unit_02098094.cpp` | `.text` 0x02098094-0x020987D8 (hypothesis: the 3x3 matrix before, the plane after) | 20.12 fixed-point 4x4 matrix `Unk02098094` (stored by column; `include/game/unk_matrix.h`): constructors from a 3x3 matrix (with or without translation), sixteen elements or a translation, identity, translation get / set, point transform, projection with division by w, in-place and two-operand products | complete |
| `src/game/unit_020987D8.cpp` | `.text` 0x020987D8-0x020988D8 (hypothesis: a 4x4 matrix product before, quaternion functions after) | plane `Unk020987d8` (3D vector normal, distance): constructors, line intersection, signed distance; vectors from `include/game/unk_vector.h` | complete |
| `src/game/unit_020988D8.cpp` | `.text` 0x020988D8-0x02098BC8 (hypothesis: the plane before, the rectangle after) | quaternion `Unk020988d8`: identity, norm, rotation matrix (through the 3x3 matrix constructor func_02097b6c), slerp (NitroSDK sine table data_020af1e8) | not complete: 2 / 4 functions at 100 % (matrix 99.26 %, slerp 99.34 %) |
| `src/game/unit_02098BC8.cpp` | `.text` 0x02098BC8-0x02098E70 (hypothesis: a plane class on the 3D vector before, the vectors after) | integer rectangle `Unk02098bc8` (x, y, width, height): constructors, point test, overlap test, subtraction into up to four pieces | complete |
| `src/game/unit_02098E70.cpp` | `.text` 0x02098E70-0x02099210 (hypothesis: a rectangle class before, unit_02099210.cpp after; may be two files) | 20.12 fixed-point 2D and 3D vectors `Unk02098e70` / `Unk02098ff0` (derived from plain structs): constructors, squared length, length, scale, normalise, clamp, sum, difference, dot product, interpolation | not complete: 17 / 19 functions at 100 % (`func_02098e94` 96.8 %, `func_02099000` 90 %) |
| `src/game/unit_02099210.cpp` | `.text` 0x02099210-0x02099800 (hypothesis: fixed-point vector helpers before, unit_02099800.cpp after) | heap class `Unk020c8440`: constructor, destructor, init, aligned first-fit allocation from a hint, free with neighbour merging, block headers (24-bit size, used bit, 6-bit heap id) | not complete: 12 / 14 functions at 100 % (`func_02099280` 94 %, `func_02099678` 99.3 %) |
| `src/game/unit_02099800.cpp` | `.text` 0x02099800-0x02099840, `.init` 0x020AE384-0x020AE3B0, `.ctor` 0x020B6EA8-0x020B6EAC, `.bss` 0x020C80A4-0x020C82C4 (hypothesis for `.text`: the object's constructor, destructor, three empty methods called only on it, and its accessor; 0x02099840-0x0209986C may belong too) | `Unk020c80b0` static object (0x214 bytes) | complete |
| `src/game/unit_02099840.cpp` | 0x02099840-0x02099870 (hypothesis: may belong to the unit before or to the allocator after) | global `operator new`, `new[]`, `delete`, `delete[]`, forwarding to func_02099b44 / func_02099b60 | complete |
| `src/game/unit_02099870.cpp` | `.text` 0x02099870-0x02099C0C, `.init` 0x020AE3B0-0x020AE43C, `.ctor` 0x020B6EAC-0x020B6EB0, `.data` 0x020BD578-0x020BD57C, `.bss` 0x020C82C4-0x020D47C0 (start is a hypothesis; the end is the last array destructor its `__sinit` registers) | heap table from the OS arenas (main, main-ex, DTCM, ITCM), current-heap stack, alloc / free used by operator new and delete; static arrays of 16 heaps (`Unk020c8440`, 0x2C) and 16 blocks (`Unk020c8700`, 0xC0C) | complete |
| `src/game/unit_02099C0C.cpp` | `.text` 0x02099C0C-0x02099C78 (hypothesis: array destructors of unit_02099870.cpp before, a class with another layout after) | lookup of a key in a table of key / value pairs (`Unk02099c0c`, table at +8, count at +0xC) and its value-or-zero wrapper | complete |
| `src/game/unit_02099C78.cpp` | `.text` 0x02099C78-0x0209A11C, `.data` 0x020BD57C-0x020BD59C (hypothesis for `.text`: unit_02099C0C.cpp before, the bit set after; `.data` is the class's vtable, 0x20 bytes as mwccarm emits it) | abstract bytecode interpreter `Unk02099c78`: constructor, run, interpreter (11 opcodes: virtual call, set, copy, reset, add, three compares, jump, sub-block, stop), compare flags, min / max tests, reset to the initial value, destructors; the virtual get / set / call are pure (zero vtable entries) | complete |
| `src/game/unit_0209A11C.cpp` | `.text` 0x0209A11C-0x0209A32C (hypothesis: the deleting destructor of the class with vtable data_020bd584 before, string hash / UTF-8 helpers after) | growable bit set `Unk0209a11c` (word array allocated on first set): two constructors, destructor, free, test, set, set range, set word | complete |
| `src/game/unit_0209A32C.c` | `.text` 0x0209A32C-0x0209A740 (start a hypothesis; the end is the end of the engine block) | string helpers: word-wise string hash (`rotl(h, 5) * 31 + c`, with a variant from a seed and one that hashes the last characters before a terminator), word-wise string equality, UTF-8 lead-byte test, one-character and whole-string UTF-8 decoding | complete |
| `src/game/unit_0205D6E0.c` | 0x0205D6E0-0x0205D6FC (hypothesis: one function of a larger unit whose other functions, 0x0205D618 and 0x0205D6C4, call it) | `func_0205d6e0`: clears 6 ints | complete (first compiled file, 2.0/sp1p5) |
| `libs/nitro/src/mi/cpumem.c` | 0x02079ABC-0x02079D70 (hypothesis: twewy's `cpumem.c` layout; neighbours unlike its functions) | 9 MI copy / fill primitives | complete |
| `libs/nitro/src/os/os_context.c` | 0x0207AFE0-0x0207B0DC (after the thread queue functions, before func_0207b0dc) | `OS_InitContext`, `OS_SaveContext`, `OS_LoadContext` | complete |
| `libs/nitro/src/os/os_cache.c` | 0x0207B3C4-0x0207B47C (hypothesis: earlier `DC_*` functions of the file may precede) | `DC_FlushAll` ... `IC_InvalidateRange` (6) | complete |
| `libs/nitro/src/os/os_tcm.c` | 0x0207B8E4-0x0207B8F8 (after the arena setup, before `os_protectionUnit.c`) | `OS_GetDTCMAddress` | complete |
| `libs/nitro/src/os/os_protectionUnit.c` | 0x0207B8F8-0x0207B918 | `OS_EnableProtectionUnit`, `OS_DisableProtectionUnit` | complete |
| `libs/nitro/src/os/os_protectionRegion.c` | 0x0207B918-0x0207B93C (before the exception handler 0x0207B93C) | `OS_SetDPermissionsForProtectionRegion`, `OS_SetProtectionRegion1`, `OS_SetProtectionRegion2` | complete |
| `libs/nitro/src/os/os_system.c` | 0x0207C194-0x0207C224 (hypothesis: the file may go on; `OS_Halt` 0x0207C3A8 is `os_terminate_proc.c`) | interrupt masks, `OS_GetProcMode`, `OS_SpinWait` (8) | complete |
| `libs/nitro/src/os/os_terminate_proc.c` | 0x0207C3A8-0x0207C3C8 (after a data initializer, before a tail call) | `OS_Halt`, `OS_Terminate` | complete (1.2/sp2p3) |
| `libs/c/src/*`, `libs/runtime/src/*` (14 files, below) | see `delinks.txt` | MSL C and runtime, not decompiled | delinked, no source |

### MSL / runtime files (2026-10-25)

Function bounds are exact (every function of 0x02080114-0x02085EEC has a `.exceptix`
entry with its address and size). File bounds come from twewy's file layout (its
MSL / runtime is another version): the sequence of function sizes was aligned with
ours in order, and a file is delinked only when the functions on both sides of each
of its bounds have the same size as in twewy (byte-identical where a fingerprint
exists: `round_decimal`, `strcpy`, `strncpy`, `strcmp`, the console I/O,
`CompressedNumbers.cpp`, `BinarySearch`, `SetupCatchInfo`, `__end_catch`,
`__throw_catch_compare`, `__PopStackFrame`). Each file takes the `.exceptix` entries of
its functions and the `.exception` records they point to; the files twewy has
without exception tables (`mem_funcs.c`, `string.c`, `CompressedNumbers.cpp`) have
none here either.

| File | `.text` | Matched in order (twewy names) |
|---|---|---|
| `abort_exit_arm_eabi.c` | 0x02080114-0x020802AC | `abort`, `exit`, `__exit` |
| `file_io.c` | 0x0208063C-0x02080724 | `fflush` |
| `mbstring.c` | 0x02080724-0x02080804 | `__mbtowc_noconv`, `__wctomb_noconv`, `wctomb`, `wcstombs` |
| `mem.c` | 0x02080804-0x02080864 | `memcpy`, `memset`, `memchr` |
| `mem_funcs.c` | 0x02080864-0x02080914 | `__fill_mem` |
| `printf.c` | 0x02080914-0x02082A58 | `parse_format` ... `sprintf` (11) |
| `scanf.c` | 0x02082A58-0x02082ADC | `__StringRead` only |
| `signal.c` | 0x02082ADC-0x02082C0C | `raise` |
| `string.c` | 0x02082C0C-0x02082E90 | `strlen`, `strcpy`, `strncpy`, `strcmp`, `strchr` |
| `console_io.c` | 0x020841B4-0x02084278 | `sys_*`, `__read_console`, `__write_console`, `__close_console` |
| `CompressedNumbers.cpp` | 0x02084278-0x02084390 | `__DecodeSignedNumber`, `__DecodeUnsignedNumber` |
| `ExceptionHandler.cpp` | 0x02084390-0x02085750 | `BinarySearch` ... `func_02058614` |
| `MWException.cpp` | 0x02085B34-0x02085D24 | `dthandler`, `duhandler`, `terminate`, `unexpected`, `__throw_catch_compare` |
| `ExceptionHandlerTS.cpp` | 0x02085D24-0x02085EA0 | `__PopStackFrame` ... `__TransferControl` |

Left in gaps (no anchor on one side): 0x020802AC-0x0208063C (`ansi_files.c`,
`buffer_io.c` and unknown functions), 0x02082E90-0x020841B4 (`strtoul.c`, `fabs`,
`pool_alloc.c`, unknown), 0x02085750-0x02085B34 (`New.cpp`, `StaticInitializers.cpp`
region, sizes differ), 0x02085EA0-0x02089780 (end of `ExceptionHandlerTS.cpp`, FP
emulation, division helpers). Function names stay `func_<addr>` where only the size
matches (`SPEC.md`).
