# The Sims 2: Castaway (DS) decompilation — specification

## Goal

Rebuild The Sims 2: Castaway (Nintendo DS) from C/C++ source written from scratch so
that, compiled with the original compiler and flags, it produces ARM9 modules (main,
ITCM, DTCM) identical byte for byte to the original, and so the original ROM.

Out of scope: a port, game assets, any redistribution of game files, the ARM7 binary
(standard SDK component, rebuilt from the extracted binary as is).

## Target ROM

| Item | Value | Evidence |
|---|---|---|
| Game code | `YS2P` (Europe), maker `69` (Electronic Arts) | ROM header 0x0C, 0x10 (`extract/eur/header.yaml`) |
| Internal title | `SIMSCASTAWAY` | ROM header 0x00 |
| Revision | 0 | ROM header 0x1E |
| Banner | "The Sims™ 2 Castaway / © 2007 Electronic Arts Inc." | `extract/eur/banner/banner.yaml` |
| ROM SHA-1 | `035eb8f242d3c83acb478b313e1b135c6aebc76d` (64 MiB) | `config/eur/build.sha1` |
| Overlays | none (ARM9 and ARM7 overlay tables empty) | ROM header 0x50-0x5C |
| ARM9 main | load 0x02000000, entry 0x02000800 (`Entry`), uncompressed | `extract/eur/arm9/arm9.yaml` |
| ARM9 sections | `.text` 0x02000000-0x020AD024, `.init` 0x020AD024-0x020AE514, `.rodata` -0x020B6E44, `.ctor` 0x020B6E44-0x020B6EC4, `.data` 0x020B6EE0-0x020BDFE0, `.bss` 0x020BDFE0-0x020D7160 | `config/eur/arm9/delinks.txt` (dsd analysis) |
| ITCM | 0x01FF8000, 0x30C0 bytes code | `extract/eur/arm9/itcm.yaml` |
| DTCM | 0x027E0000, 0x60 bytes data + 0x20 bss | `extract/eur/arm9/dtcm.yaml` |
| ARM7 | load 0x02380000, 0x289C0 bytes | ROM header 0x30-0x3C |
| NitroSDK | version word `0x03027532` at ARM9 0x02000B7C (major 3, minor 2, relstep 30002) | build info (`extract/eur/arm9/arm9.yaml`, `sdk_version`) |
| Code size | 720812 bytes, 4553 functions (dsd analysis) | `build/eur/report.json` |
| Build date | unknown (ROM file dated 2007-10-24, not evidence of the build) | — |

Game files: 12 `ROM_Euro/Source/Archives/*.nitro_archive` and one `sound_data.sdat`;
their format is EA's own (`nitro_map`, `nitro_xml`, `nitro_lot` names in the ARM9).

## Toolchain

Evidence and the candidate analysis go in `notes/COMPILER.md`.

- ds-decomp (`dsd`) **v0.12.1**: extract, analysis (`dsd init`), delink, linker script,
  ROM rebuild, checks, objdiff config.
- objdiff-cli **v3.8.1** (report, diff with the unarm disassembler), objdiff GUI.
- mwccarm / mwldarm from `decomp.aetias.com/files/mwccarm.zip` (1.2, 2.0 and DSi
  families in `tools/mwccarm/`). Game code: **mwccarm 2.0 family**; NitroSDK and
  NitroSystem: **1.2 family** (byte-identical probes, `notes/COMPILER.md`). Service
  packs not settled: `configure.py` uses 2.0/sp1p5 and 1.2/sp2p3 as working choices.
  Game flags: twewy's without `-ipa file` (`notes/COMPILER.md`, "Game flags: no
  `-ipa file`").
- Linker flags: `-proc arm946e -interworking -dead -nostdlib -m Entry` (twewy has
  `-nodead`; `-dead` drops the unused C1/C2, D1/D2 copies, as the original link did,
  and `tools/lcf_keep.py` keeps `.exception` alive; notes/COMPILER.md).
- Optional: Ghidra 11.2.1 with the dsd-ghidra v0.7.0 extension, outside the repository
  (`tools/ghidra_sync.py` pushes the dsd symbols to a Ghidra project).

## Acceptance criteria

- Every build ends with `build\eur\ts2c_eur.nds: OK` (`ninja`), after `dsd check
  modules` (main, ITCM, DTCM OK) and `dsd check symbols`, locally and in CI.
- The ROM check uses `config/eur/build.sha1` (the original ROM) when `arm7_bios.bin`
  is in the repository root, and `config/eur/build_nobios.sha1` otherwise. Without the
  BIOS, dsd cannot encrypt the secure area, so exactly four bytes differ from the
  original: the secure area CRC (0x6C-0x6D) and the header CRC (0x15E-0x15F); every
  other byte, all modules included, is identical (checked 2026-10-25 with `cmp`).
  With the owner's ARM7 BIOS dump (`bios/biosnds7.bin`, 16 KiB, SHA-1
  `24f67bdea115a2c847c8813a262502ee1607b7df`, copied to `arm7_bios.bin`) the rebuilt
  ROM is identical to the original (checked 2026-10-25). BIOS and firmware dumps are
  the owner's console dumps: `bios/` and `arm7_bios.bin` are git-ignored and never
  pushed anywhere, including the private build image, so CI checks
  `build_nobios.sha1` and the original SHA-1 is checked locally only.
- A file in `delinks.txt` is `complete` only when objdiff reports 100 % for all its
  functions and data and the build still matches. Anything else stays not
  `complete`, with the remaining gap written above each unfinished function.
- A delink that builds proves the bytes, not the translation unit: a TU boundary is
  proven only once the unit is decompiled and matches (`notes/SPLITS.md`).
- Every name, compiler fact or structure layout rests on evidence (strings with their
  offset, library signatures, symbols of another project on the same library, an
  objdiff diff, a build result). Without evidence it is labelled a hypothesis. Names
  given in Ghidra are not evidence by themselves.
- Reused code from another project is logged with its commit and license in
  `notes/PROVENANCE.md`.

## Naming conventions

- dsd default names stay until proven: `func_<addr>`, `data_<addr>`, `__sinit_<addr>`
  (static initializers in `.init`).
- Game units: `src/game/unit_<start address>.cpp` while real file names are unknown;
  the unit table with bounds and contents is in `notes/SPLITS.md`.
- Unknown classes and structs: `Unk<Name>` or `Unk<address>`; unknown methods keep
  the address (`func_<addr>`, mangled as a member when the unit is C++).
- SDK and library code under `libs/<lib>/{include,src}` with the real names of the
  library once identified by signature or reference project.
- Library function names (owner's choice, 2026-10-25): a function found at exactly
  one address by `tools/compiler_sweep.py` (more than 8 bytes) takes khdays-decomp's
  name, which follows the NitroSDK / NitroSystem API (`MIi_CpuCopy16`,
  `DC_FlushAll`); twewy's name only where khdays has no match. The byte match is the
  evidence; the name is the reference's. Advance Wars fingerprints (CC0) confirm a
  function whose khdays name is known from khdays' symbols (runtime helpers), and
  name one that neither khdays nor twewy has (`_drsb`). Library file names: the
  NitroSDK file khdays cites in its source comment, else twewy's file name.
- Code, comments, notes and commit messages are in English.

## Repository layout

```
README.md SPEC.md LICENSE
config/eur/               build.sha1, build_nobios.sha1, arm9/ (dsd configs:
                          config.yaml, delinks.txt, symbols.txt, relocs.txt; itcm/, dtcm/)
extract/                  baserom_ts2c_eur.nds and dsd extraction (git-ignored)
build/                    build output (git-ignored)
src/  include/  libs/     sources and headers (game, SDK, MSL), when added
tools/                    configure.py and scripts (progress badges, report diff)
progress/eur/             progress badges and history (README images)
notes/                    reference documentation
.github/workflows/        CI: delink, link, rebuild and check the ROM in a private image
```

## Build

```
pip install -r tools/requirements.txt
python tools/configure.py # generate build.ninja (first run: then `ninja` downloads the tools)
ninja                     # delink, compile, link, check modules and symbols, rebuild
                          # the ROM, check its SHA-1, write build/eur/report.json
```

Put the ROM at `extract/baserom_ts2c_eur.nds`. Useful targets: `ninja objdiff`
(objdiff.json for the GUI), `ninja report`, `ninja dis` (disassembly in
`build/eur/asm/`), `ninja apply` (names from the built ELF back into `symbols.txt`).
On Windows use native tools, not WSL.
