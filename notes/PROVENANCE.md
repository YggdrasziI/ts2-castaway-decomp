# Provenance of reused code

Every file or function taken from another project, with the project, its commit
(`git -C <clone> rev-parse HEAD`), its license (or its absence and the owner's
approval, see `notes/REFERENCES.md`) and the changes made.

## Build system (`tools/`)

Source: [Yotona/twewy](https://github.com/Yotona/twewy), local clone at commit
`0026d7347107415cbfbf2cd218f5859ae00b69a7`, license **CC0-1.0**. Fetched on 2026-10-25.

| Our file | Their file | Changes |
|---|---|---|
| `tools/configure.py` | `tools/configure.py` | `GAME = "ts2c"`, one version `eur`; twewy's per-path compiler configs removed (`COMPILER_CONFIGS` empty); ROM check against `build_nobios.sha1` when `arm7_bios.bin` is absent |
| `tools/download_tool.py`, `get_platform.py`, `ninja_syntax.py`, `transform_dep.py`, `m2ctx.py`, `mangle.py`, `sha1.py`, `requirements.txt` | same paths | none |

## Scripts from the sibling projects

Source: `YggdrasziI/spyro-dotd-decomp` (private, same owner), commit
`35d0baf60d7df46879015cda2fa7f45807bc5b2e`.

| Our file | Changes |
|---|---|
| `tools/report_diff.py` | default version `eur`, lower-case version names |
| `tools/progress_badges.py` | default version `eur`; function addresses read from the dsd `symbols.txt` files (dsd's objdiff report has no `virtual_address`); no regions yet |

## Project documents

`CLAUDE.md`, `SPEC.md`, `ROADMAP.md`, `TASKS.md`, `notes/` and `.claude/skills/` follow
the structure of spyro-dotd-decomp (same commit), rewritten for the DS toolchain.
