# Compiler, SDK and runtime evidence

Status: **mwccarm 2.0 family** for game code, MSL / runtime and the engine block;
**1.2 family (base ... sp2p3)** for NitroSDK and NitroSystem (2026-10-25, below).
Service packs not settled; `tools/configure.py` uses 2.0/sp1p5 by default and
1.2/sp2p3 for `libs/nitro` (`COMPILER_CONFIGS`).

## NitroSDK and NitroSystem: 1.2 family

The two families save a lone `lr` differently in a non-leaf function: 1.2 emits
`stmdb sp!, {lr}` + `sub sp, sp, #4`, 2.0 (base ... sp2p4) and DSi emit
`stmdb sp!, {r3, lr}` (checked on `OS_Terminate`, all 25 compilers). Function
starts in this ROM (2026-10-25):

| Region (`notes/SPLITS.md`) | `stmdb {lr}` + `sub sp, #4` | `stmdb {r3, lr}` |
|---|---|---|
| NitroSDK | 93 | 0 |
| NitroSystem | 17 | 0 |
| game blocks 1 and 2 | 0 | 172 |
| MSL / runtime | 0 | 13 |
| engine block | 0 | 64 |
| `.init` | 0 | 21 |

twewy's NitroSDK C sources confirm it: `FX_DivAsync`, `FX_InvAsync`,
`FX_GetDivResult`, `GX_VBlankIntr`, `SetLCDC`, `GetBankSize`, `OS_SetIRQMask`,
`OS_ResetIRQRequestFlags` and twewy's `OS_EnableInterrupts` match only with 1.2
(the 2.0-only hits of the first probes are `asm` functions of files 1.2 does not compile).
twewy's `OS_DisableInterrupts` (an IE-mask function, 0x0207A028) matches with 1.2
base, b56, sp2 and sp2p3 but not sp3 / sp4: the SDK is built with 1.2 sp2p3 or
earlier. `libs/nitro/src/os/os_terminate_proc.c` (C) matches with 1.2/sp2p3 and
`tools/configure.py`'s flags without `-ipa file` (1.2 rejects it).

The engine block (0x02089780-0x0209A740) is built like the game, not like the Nintendo
libraries: it is EA code.

## NitroSDK

| Evidence | Value | Where |
|---|---|---|
| SDK version word | `0x03027532`: major 3, minor 2, relstep 30002 | ARM9 0x02000B7C (in `BuildInfo` at 0x02000B64; dsd `sdk_version` in `extract/eur/arm9/arm9.yaml`) |
| Library marker | `[SDK+NINTENDO:BACKUP]` | ARM9 file offset 0xB88 (right after the nitrocode `0xDEC00621` / `0x2106C0DE` words) |

Reading of the relstep (hypothesis, from NitroSDK's `SDK_VERSION_RELSTEP` scheme:
1xxxx PR, 2xxxx RC, 3xxxx release): NitroSDK 3.2 release, patch level 2.

No other `[SDK+...]` markers (NitroSystem, NitroWiFi, CW) are in the ARM9, so the
library list must come from signatures and fingerprints.

## Probes (`tools/compiler_sweep.py`, 2026-10-25)

The sweep compiles a file with every mwccarm in `tools/mwccarm/` (flags: twewy's
common flags, `-O4,p`, `-lang=c99`) and searches each function in the ARM9 modules
with relocated words masked. "Unique" = found at exactly one address.

NitroSDK, twewy's CC0 sources `libs/nitro/src/*/*.c` (as written for twewy, not
necessarily this SDK 3.2 build): 32 functions unique with every 2.0 sp1 ... sp2p4;
2.0/base 20, 1.2 19-20, DSi 29-30. Found, e.g.: `DC_PurgeAll` 0x0207B3C4,
`DC_InvalidateRange` 0x0207B3F8, `OS_EnableIRQ` 0x0207C194, `OS_DisableIRQ` 0x0207C1A8,
`OS_PopThreadFromQueue` 0x0207AF1C, `OS_GetRegionBottom` 0x0207B724 (full list:
rerun the command below). So the SDK is built with 2.0 sp1 or later.

MSL C / runtime, twewy's `libs/c/src`, `libs/runtime/src` (built there with
`-Cpp_exceptions on -ipa file -str reuse`, not used here): `strcpy` 0x02082C28,
`strncpy` 0x02082CF0, `strcmp` 0x02082D40, `round_decimal` 0x020818AC (printf.c),
`sys_WriteChar` / `sys_ReadChar` / `sys_Exit` 0x020841B4-0x020841DC; all 2.0 versions
alike.

Game code, seven leaf functions rewritten from their assembly (scratch file, every
one byte-identical at its address on the first try):

| Address | Function | 1.2 | 2.0 (base ... sp2p4) | DSi |
|---|---|---|---|---|
| 0x0205D6E0 | clear 6 ints in a loop | ✓ | ✓ | ✓ |
| 0x020605D0 | 4 fields = 0, 0, 0, -1 | ✗ | ✓ | ✗ |
| 0x020388AC | 4 fields = -1, 0, 0, 0 | (several addresses) | (several) | ✗ |
| 0x02012558 | `if (++count == 200) flag = 1` | ✗ | ✓ | ✓ |
| 0x02017184 | short clamp + clear | (several) | (several) | ✗ |
| 0x0206AF40 | bounded array element address | ✓ | ✓ | ✓ |
| 0x02026F24 | `x == 2 \|\| x == 1` | ✗ | (several) | (several) |

Only the 2.0 family produces all seven. Five more probes with fixed-point arithmetic
(`FX_Mul`-style 64-bit multiplies with and without rounding, a multiply-and-clamp,
an `mla` element address) gave 2 unique matches (0x0206A7FC, 0x02066298) with every
2.0 version alike, and 3 without match: the service pack is still open.

Confirmed in the build: `src/game/unit_0205D6E0.c` compiled with 2.0/sp1p5 and
`tools/configure.py`'s flags is 100 % in objdiff and linked (`complete`), ROM OK.

Command (NitroSDK): `python tools/compiler_sweep.py --ref E:/Projets/Github/Decomp/DS/twewy
--define REGION_USA "E:/Projets/Github/Decomp/DS/twewy/libs/nitro/src/*/*.c"`

## NitroSystem and MSL

Both are linked (region map in `notes/SPLITS.md`): MSL C and the C++ runtime at
0x02080114-~0x02089780 (fingerprints from twewy and khdays: `printf.c`, `string.c`,
console I/O, `CompressedNumbers.cpp`, `ExceptionHandlerTS.cpp`), NitroSystem at
0x0209A740-~0x0209F0AC (khdays fingerprints: `NNS_Fnd` lists, `NNSi_SndFader`,
`NNS_SndArc` callbacks). Their versions are unknown: no `[SDK+...]` marker for them.
Only 0x02080114-0x02085EEC (MSL / runtime) has `.exceptix` entries: that code is
built with C++ exception tables, the game and the other libraries are not (or have no
function that needs one). CRI middleware (twewy's `libs/cri`) is absent: only 8-byte or mid-function hits.

## Candidates

Available in `tools/mwccarm/`: 1.2 (base, b56, sp2, sp2p3, sp3, sp4), 2.0 (base, sp1,
sp1p2, sp1p5, sp1p6, sp1p7, sp2, sp2p2, sp2p3, sp2p4), DSi (1.1 ... 1.6sp2).

What reference projects use (context, not evidence for this game): ph and twewy
2.0/sp1p5, DQIV 2.0/sp1p6 (libs 2.0/sp1p2), fe11 2.0/sp2p2.

## ARM / Thumb

dsd found 18 Thumb functions, all BIOS call veneers at 0x02000062-0x02000776 (`Sqrt`,
`Div`, `CpuSet`, ...); everything else is ARM. Game code is therefore built ARM-mode
unless a unit proves otherwise.

## Static initializers

`.init` (0x020AD024-0x020AE514) holds 32 functions listed by `.ctor`
(0x020B6E44-0x020B6EC4), named `__sinit_<addr>` by dsd: most likely C++ units with
static objects (hypothesis until one is decompiled). They come in two
runs, 0x020AD024-0x020AD318 and 0x020AE130-0x020AE4E8; what lies between (0x020AD318-
0x020AE130) is not known yet.

## Game flags: `-avoid_byte strb`

The game code has no `STRB`: every byte store is a `SWPB` (result register dead),
loads stay `LDRB`. `build/eur/asm/_dsd_gap@main_14.s` has 0 `strb` and 21 `swpb`,
`_dsd_gap@main_18.s` 2 and 481, including conditional `swpbne` and stores to stack
locals, so it is code generation, not inline asm (inline asm also lowers the
optimization of the whole function, which the ROM does not show). mwccarm has the
option `-avoid_byte none|strb|all` ("replace STRB instructions only" for `strb`),
next to `-allow_byte global|local` (strings of `mwccarm.exe`, `-help all` does not
list them). With `-avoid_byte strb`, `p->b = v` compiles to the ROM's
`add rX, p, #off; swpb rY, v, [rX]`. Added to the game flags in
`tools/configure.py` (build of 2026-10-25: ROM identical, no report regression);
`unit_02096A74.cpp` then became complete. The C library and runtime units keep
`STRB` (they are not compiled with these flags).

## Game flags: no `-ipa file`

twewy's flags include `-ipa file`. With it, mwccarm emits a file's deferred functions
(array destructors `__arraydtor$N`, out-of-line copies of inline constructors and
destructors) in the opposite order to the ROM: in `unit_02099870.cpp` the ROM has
`__arraydtor` (second array), `D1`, `C1`, `__arraydtor` (first array), and every
2.0 service pack from base to sp2p4 gives the reverse with `-ipa file`. Without it
(or with `-ipa function`) the order matches; `-inline auto`, `-inline off` and
`-O4,s` do not change it. The three units complete before (`unit_0205D6E0.c`,
`unit_02099800.cpp`, `unit_02099840.cpp`) match either way.

## Link: dead stripping

mwccarm (every 2.0 and DSi version in `tools/mwccarm`) emits a C++ constructor
twice, as the complete-object (`C1`) and base-object (`C2`) variants, each in its own
section, and a destructor likewise (`D1`, `D2`). The ROM holds one copy only
(`unit_02099800.cpp`: one 0x24-byte constructor, one 4-byte destructor), so the
original link stripped the unused variant. With twewy's `-nodead` both copies stay
and every later address moves; the link therefore uses `-dead`.

`-dead` alone fails: dsd's LCF keeps `.init`, `.ctor` and `.exceptix` but not
`.exception`, whose records no relocation reaches, so the linker drops its 0xC4 bytes
and `.init` moves. `tools/lcf_keep.py` adds `.exception` to `KEEP_SECTION` after
`dsd lcf`; with it the ARM9, ITCM and DTCM modules and the ROM stay identical
(build of 2026-10-25, before and after `unit_02099800.cpp` became complete).

## Open questions

- Game-code service pack inside 2.0 (probe larger functions: switches, multiplies,
  division by constants, inlining, struct copies).
- NitroSDK / NitroSystem service pack inside 1.2 base ... sp2p3, and their flags.
- MSL / runtime version (look for `__call_static_initializers`, `_s32_div_f`-style
  helpers; the `%a %b %e %T %Y` / `%I:%M:%S %p` strings look like a C library's
  C-locale `strftime` formats, to compare with MSL sources).
