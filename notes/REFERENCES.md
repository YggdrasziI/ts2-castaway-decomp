# References

## Tools

- [AetiasHax/ds-decomp](https://github.com/AetiasHax/ds-decomp) (`dsd`, MIT): ROM
  extract, analysis, delink, linker script, ROM rebuild, checks, objdiff config. Local
  clone: `E:\Projets\Github\Decomp\Tools\NDS\ds-decomp` (docs: `README.md`,
  `docs/delinks.md`, `docs/symbols.md`, `docs/relocs.md`). Undocumented commands worth
  knowing: `fix {thumb-nop, ctor-symbols, ctor-zero, ...}`, `dump {elf-symbols,
  ambig-relocs, elf-function}`, `sig {list, apply, new}`.
- [AetiasHax/ds-rom](https://github.com/AetiasHax/ds-rom): ROM extract / build library
  used by dsd.
- [AetiasHax/unarm](https://github.com/AetiasHax/unarm): ARM disassembler used by
  objdiff for DS projects.
- [AetiasHax/dsd-ghidra](https://github.com/AetiasHax/dsd-ghidra): Ghidra loader and
  `SyncDsd.java` script (`tools/ghidra_sync.py`).
- [encounter/objdiff](https://github.com/encounter/objdiff): local diff (reads
  `objdiff.json`), `objdiff-cli report` / `diff`.
- mwccarm / mwldarm: `http://decomp.aetias.com/files/mwccarm.zip` (downloaded by
  `ninja` into `tools/mwccarm/`).
- [decompals/wibo](https://github.com/decompals/wibo): runs mwccarm on Linux (CI).
- [decomp.me](https://decomp.me): compiler tests (`mwcc_30_131` = 2.0/sp1p5); not used
  for sharing, the project is private.
- [decomp.dev](https://decomp.dev): not used (private project).

## Hardware documentation

- Rodrigo Copetti, *Architecture of consoles: Nintendo DS*
  ([article source](https://github.com/flipacholas/Architecture-of-consoles/blob/master/articles/nintendo-ds.Rmd.md)):
  ARM946E-S and ARM7TDMI, ITCM / DTCM, memory map, 2D / 3D engines, sound, cartridge.
  Context only, never evidence for a name or a structure. Used for: autoload and
  memory map bounds (`notes/SPLITS.md`), `-proc arm946e` and ARM/Thumb interworking
  (`notes/COMPILER.md`), recognising I/O register accesses (0x04000000...) in game
  code. A local copy (e.g. under `E:\Projets\Github\Decomp\Docs\`) only with the
  owner's agreement.
- GBATEK (problemkaputt.de/gbatek.htm): register-level reference for the same
  purposes.

## Reference projects (local clones)

Search the local clones (Grep/Glob) before GitHub. A clone may be behind GitHub: ask
the owner before `git pull`. When reusing code, record the clone's commit
(`git -C <path> rev-parse HEAD`) and the license in `notes/PROVENANCE.md`.

DS, `E:\Projets\Github\Decomp\DS\`:

| Folder | Project | License | dsd | Compiler | Notes |
|---|---|---|---|---|---|
| `twewy` | [Yotona/twewy](https://github.com/Yotona/twewy) | CC0 | 0.12.1 | 2.0/sp1p5 (+1.2/sp4 per file) | template of `tools/configure.py`; libs c, cpp, cri, nitro, runtime |
| `ph` | [zeldaret/ph](https://github.com/zeldaret/ph) | CC0 | 0.11.0 | 2.0/sp1p5 | reference dsd project, docs `build_system.md`, `decompiling.md` |
| `st` | [zeldaret/st](https://github.com/zeldaret/st) | CC0 | 0.12.0 | dsi/1.2p1 | libs nitro, nns, c, cpp, runtime; **CONTRIBUTING forbids AI use for its library decompilation and mostly-AI PRs**: build patterns only |
| `DQIV-DECOMP` | [GoldieLeGenie/DQIV-DECOMP](https://github.com/GoldieLeGenie/DQIV-DECOMP) | none | 0.10.2 | 2.0/sp1p6, libs 2.0/sp1p2 | libs MSL, NitroSDK, NitroSystem, Runtime; ask before reuse |
| `fe11-us` | [Eebit/fe11-us](https://github.com/Eebit/fe11-us) | none | 0.12.0 | 2.0/sp2p2 | ask before reuse |
| `khdays-decomp` | [Yokimitsuro/khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp) | CC0 | own build | 3.0_patch4 | heavily customised; `libs/{nitro,nns,msl}` used as sweep fingerprints (nothing copied) |
| `advance-wars-dual-strike-decomp` | [sturmds/advance-wars-dual-strike-decomp](https://github.com/sturmds/advance-wars-dual-strike-decomp) | CC0 | 0.12.1 | metroskrew 2.0-72 | `tools/dsd_init.py` works around `dsd init` aborting |
| `pokebw2` | [fuddlesworth/pokebw2](https://github.com/fuddlesworth/pokebw2) | GPL-3.0 | fork | dsi/1.1p1 | `docs/configs.md` (ambiguous relocs); GPL: patterns only, no code |
| `dqix-decomp` | [DQIX/dqix-decomp](https://github.com/DQIX/dqix-decomp) | Unlicense | 0.10.2 | 2.0/sp2p2, SDK 2.0/sp1p2 | Dragon Quest IX, USA and JPN; C++ game code by subsystem (`src/Graphics`, `src/Filesystem`, ...) with ITCM files (`src/Graphics/itcm`, `src/NitroSDK/itcm`); clone at 1253a35 (2026-10-23); public-domain dedication, reuse allowed like CC0 (owner, 2026-10-26) |

Other platforms:

- `E:\Projets\Github\Decomp\WIII\Castaway`: [HaydnTrigg/Castaway](https://github.com/HaydnTrigg/Castaway)
  (CC0), **Wii version** of the same game, with DWARF debug info
  (`dwarf/split/.../SKU2_Code/src/target/game/...`). Hypothesis: the DS version is a
  separate code base (DS engine built on `nitro_*` formats; a sample of 60 DS strings
  matched only generic words in the Wii tree, 2026-10-25). Usable as a source of
  candidate names for shared game concepts, never as evidence.
- Sibling projects of the owner: `E:\Projets\Dev\mlab-decomp`,
  `E:\Projets\Dev\spyro-dotd-decomp` (methodology, scripts).

## Reuse permissions

- CC0 and Unlicense projects (dqix-decomp, owner's go on 2026-10-26): allowed,
  logged in `notes/PROVENANCE.md`.
- No license (DQIV, fe11) or GPL (pokebw2): ask the owner first.
- zeldaret/st library code: not reused (its AI policy), unless the owner decides
  otherwise.
