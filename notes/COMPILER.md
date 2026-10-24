# Compiler, SDK and runtime evidence

Status: **not identified** (Step 2). `tools/configure.py` builds with a provisional
2.0/sp1p5 and twewy's flags; nothing is compiled from source yet, so this choice is
untested.

## NitroSDK

| Evidence | Value | Where |
|---|---|---|
| SDK version word | `0x03027532`: major 3, minor 2, relstep 30002 | ARM9 0x02000B7C (in `BuildInfo` at 0x02000B64; dsd `sdk_version` in `extract/eur/arm9/arm9.yaml`) |
| Library marker | `[SDK+NINTENDO:BACKUP]` | ARM9 file offset 0xB88 (right after the nitrocode `0xDEC00621` / `0x2106C0DE` words) |

Reading of the relstep (hypothesis, from NitroSDK's `SDK_VERSION_RELSTEP` scheme:
1xxxx PR, 2xxxx RC, 3xxxx release): NitroSDK 3.2 release, patch level 2.

No other `[SDK+...]` markers (NitroSystem, NitroWiFi, CW) are in the ARM9, so the
library list must come from signatures and fingerprints.

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

- Game-code compiler version and flags (probe leaf functions with every version).
- Whether the SDK libraries were built with another version (`COMPILER_CONFIGS`).
- MSL / runtime version (look for `__call_static_initializers`, `_s32_div_f`-style
  helpers; the `%a %b %e %T %Y` / `%I:%M:%S %p` strings look like a C library's
  C-locale `strftime` formats, to compare with MSL sources).
