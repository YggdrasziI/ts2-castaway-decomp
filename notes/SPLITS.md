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
| `src/game/unit_02099210.cpp` | `.text` 0x02099210-0x02099800 (hypothesis: fixed-point vector helpers before, unit_02099800.cpp after) | heap class `Unk020c8440`: constructor, destructor, init, aligned first-fit allocation from a hint, free with neighbour merging, block headers (24-bit size, used bit, 6-bit heap id) | not complete: 12 / 14 functions at 100 % (`func_02099280` 94 %, `func_02099678` 99.3 %) |
| `src/game/unit_02099800.cpp` | `.text` 0x02099800-0x02099840, `.init` 0x020AE384-0x020AE3B0, `.ctor` 0x020B6EA8-0x020B6EAC, `.bss` 0x020C80A4-0x020C82C4 (hypothesis for `.text`: the object's constructor, destructor, three empty methods called only on it, and its accessor; 0x02099840-0x0209986C may belong too) | `Unk020c80b0` static object (0x214 bytes) | complete |
| `src/game/unit_02099840.cpp` | 0x02099840-0x02099870 (hypothesis: may belong to the unit before or to the allocator after) | global `operator new`, `new[]`, `delete`, `delete[]`, forwarding to func_02099b44 / func_02099b60 | complete |
| `src/game/unit_02099870.cpp` | `.text` 0x02099870-0x02099C0C, `.init` 0x020AE3B0-0x020AE43C, `.ctor` 0x020B6EAC-0x020B6EB0, `.data` 0x020BD578-0x020BD57C, `.bss` 0x020C82C4-0x020D47C0 (start is a hypothesis; the end is the last array destructor its `__sinit` registers) | heap table from the OS arenas (main, main-ex, DTCM, ITCM), current-heap stack, alloc / free used by operator new and delete; static arrays of 16 heaps (`Unk020c8440`, 0x2C) and 16 blocks (`Unk020c8700`, 0xC0C) | complete |
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
