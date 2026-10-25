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

Not started (Step 4). Known landmarks:

| Range | Content | Evidence |
|---|---|---|
| 0x02000000-0x02000800 | BIOS call veneers (Thumb), secure area | dsd analysis (names from dsd) |
| 0x02000800-0x02000B64 | `Entry` (crt0), `AutoloadCallback` | ROM header entry point, autoload hook 0x02000A74 |
| 0x02000B64-0x02000BA0 | `BuildInfo`, nitrocode, `[SDK+NINTENDO:BACKUP]` | SDK version word, string |
| 0x02000BA0 | `main` | dsd (called by `Entry`) |
| 0x020ACC60-0x020AD024 | gap dsd merged into `.text` | `dsd init` warning; content to check |
| 0x0207AE98-0x0207C218 | NitroSDK `OS` / `DC` functions | `tools/compiler_sweep.py` on twewy's sources (`notes/COMPILER.md`) |
| 0x020818AC-0x020841DC | MSL C (`printf.c`, `string.c`) and runtime console I/O | same |

## Units

| Unit | Bounds | Content | Status |
|---|---|---|---|
| `src/game/unit_0205D6E0.c` | 0x0205D6E0-0x0205D6FC (hypothesis: one function of a larger unit whose other functions, 0x0205D618 and 0x0205D6C4, call it) | `func_0205d6e0`: clears 6 ints | complete (first compiled file, 2.0/sp1p5) |
