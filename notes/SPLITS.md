# Splits and region map

A delink that builds proves the bytes, not the translation unit: dsd copies the
original code and data into the delinked objects, so a wrong boundary still links.
A unit boundary is proven only once the unit is decompiled and `complete`.

## Modules

| Module | Range | Sections |
|---|---|---|
| ARM9 main | 0x02000000-0x020D7160 | `.text` 0x02000000-0x020AD024, `.init` -0x020AE514, `.rodata` -0x020B6E44, `.ctor` -0x020B6EC4, `.data` 0x020B6EE0-0x020BDFE0, `.bss` -0x020D7160 |
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

Bounds marked ~ are within one or two small functions (a leaf called from both
sides cannot be placed by calls alone).

| Range | Content | Evidence |
|---|---|---|
| 0x02000000-0x02000800 | BIOS call veneers (Thumb), secure area | dsd analysis |
| 0x02000800-0x02000BA0 | crt0: `Entry`, `MIi_UncompressBackward` 0x02000950, `AutoloadCallback`, `BuildInfo` / nitrocode / `[SDK+NINTENDO:BACKUP]` | ROM header entry, autoload hook 0x02000A74, khdays fingerprint |
| 0x02000BA0-~0x02073ED0 | **Game code, block 1** (`main` first) | calls into everything below; no library fingerprint |
| ~0x02073ED0-0x02080114 | **NitroSDK** | fingerprints from 0x020755F4 (`CP_SaveContext`) to 0x0207F540 (`PMi_PrependList`); 0x02073EF0 is called by FS and calls OS card-bus functions |
| 0x02080114-~0x02089780 | **MSL C and the C++ runtime** | `round_decimal` (printf.c) 0x020818AC, `strcpy` / `strncpy` / `strcmp` 0x02082C28-0x02082D40, `sys_*` console I/O 0x020841B4, `__DecodeSignedNumber` 0x02084278, `__PopStackFrame` 0x02085D24; NitroSDK and MSL never call above 0x02089780 |
| ~0x02089780-0x0209A740 | **Engine code that never calls the game** (not identified) | no fingerprint; heavily called by game code (e.g. 559 calls into 0x02099000-0x0209A000); uses `FontMetrics` / `Character` XML key strings (0x0208E96C-0x0208F5EC) and `"    File %s"`; the runtime calls it (0x020857B8 -> 0x0209984C, 0x02099864: hypothesis, the allocator behind `operator new`). Hypothesis: an EA engine library, or game files linked after the libraries |
| 0x0209A740-~0x0209F0AC | **NitroSystem** (NNS) | `NNS_SndArc` dispose callbacks 0x0209B97C-0x0209B994, `NNSi_SndFader*` 0x0209E798, `NNS_Fnd` list functions 0x0209E854-0x0209EA64; no call from the SDK or MSL into it |
| ~0x0209F0AC-0x020ACC60 | **Game code, block 2** | calls game block 1 (e.g. 0x0209FA80), the engine block and NNS; strings `build/data/text/*.nitro_text`, `ROM_Euro/source/archives/text.nitro_archive`, sound and micro-game messages |
| 0x020ACC60-0x020AD024 | gap dsd merged into `.text` | `dsd init` warning; content to check |
| 0x020AD024-0x020AE514 | `.init`: 32 `__sinit_*` | `.ctor` 0x020B6E44-0x020B6EC4 |
| ITCM 0x01FF8000-0x01FFB0BC | 57 functions: SDK (calls `OS_DisableInterrupts` / `OS_RestoreInterrupts`, references `CP_SaveContext`) and engine code (calls 0x02098A5C-0x02099B28) | `relocs.txt` of the ITCM; not split yet |

Link order read from this map (hypothesis): game objects, NitroSDK, MSL / runtime,
engine block, NitroSystem, game objects. Inside NitroSDK the modules found are in
alphabetical order (CP, CTRDG, FS, GX, MI, OS, PM), so 0x02073ED0-0x020755F4 is
probably CARD (not fingerprinted).

Commands: `python tools/compiler_sweep.py --ref <project> --compilers 2.0/sp1p5
--min-size 8 --json out.json <sources>` (khdays: add `--include
<khdays>/include/{nitro,nnsys,game}`, and batches of ~150 files on Windows).

## Units

| Unit | Bounds | Content | Status |
|---|---|---|---|
| `src/game/unit_0205D6E0.c` | 0x0205D6E0-0x0205D6FC (hypothesis: one function of a larger unit whose other functions, 0x0205D618 and 0x0205D6C4, call it) | `func_0205d6e0`: clears 6 ints | complete (first compiled file, 2.0/sp1p5) |
