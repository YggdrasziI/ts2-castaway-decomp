# Compiler, SDK and runtime evidence

Status: **mwccarm 2.0 family** for game code and NitroSDK (proven by byte-identical
probes, below); the service pack is not settled yet. `tools/configure.py` keeps
2.0/sp1p5 as a working choice inside the family.

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

## Open questions

- Game-code service pack inside 2.0 (probe larger functions: switches, multiplies,
  division by constants, inlining, struct copies).
- Whether the SDK libraries were built with another version (`COMPILER_CONFIGS`).
- MSL / runtime version (look for `__call_static_initializers`, `_s32_div_f`-style
  helpers; the `%a %b %e %T %Y` / `%I:%M:%S %p` strings look like a C library's
  C-locale `strftime` formats, to compare with MSL sources).
