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

## NitroSDK sources (`libs/nitro/src/`)

Sources: [Yokimitsuro/khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp),
local clone at commit `261a89eaa8f65dd566ae0828b0b57c85c847a6ee`, and twewy (commit `0026d7347107415cbfbf2cd218f5859ae00b69a7`), both
**CC0-1.0**. Taken on 2026-10-25. Each function was first found byte-identical in
this ROM by `tools/compiler_sweep.py`, then checked at 100 % in objdiff and linked
(`complete`).

| Our file | Their files | Changes |
|---|---|---|
| `libs/nitro/src/os/os_cache.c` | khdays `libs/nitro/os/asm_stubs/auto/{DC_FlushAll,DC_InvalidateRange,DC_StoreRange,DC_WaitWriteBufferEmpty,IC_InvalidateRange}.c`, `libs/nitro/os/calls/DC_FlushRange.c` | one file; `nitro/hw.h` constants defined locally; `DC_FlushRange` written as the `asm` function its C version compiles to |
| `libs/nitro/src/os/os_system.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_{EnableInterrupts,DisableInterrupts,RestoreInterrupts,DisableInterrupts_IrqAndFiq,RestoreInterrupts_IrqAndFiq,GetCpsrIrq,GetProcMode,SpinWait}.c` | one file; constants and typedefs local; `@1` label in `OS_SpinWait` |
| `libs/nitro/src/os/os_context.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_InitContext.c`, `libs/nitro/os/asm_stubs/calls/OS_{SaveContext,LoadContext}.c` | one file; `nitro/os.h` / `nitro/hw.h` constants local; register names for the parameters of `OS_InitContext` |
| `libs/nitro/src/os/os_tcm.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_GetDTCMAddress.c` | constant local |
| `libs/nitro/src/os/os_protectionUnit.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_{EnableProtectionUnit,DisableProtectionUnit}.c` | one file; constant local |
| `libs/nitro/src/os/os_protectionRegion.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_{SetDPermissionsForProtectionRegion,SetProtectionRegion1,SetProtectionRegion2}.c` | one file |
| `libs/nitro/src/os/os_terminate_proc.c` | khdays `libs/nitro/os/asm_stubs/auto/OS_Halt.c`, `libs/nitro/os/calls/OS_Terminate.c` | one file; built with 1.2/sp2p3 |
| `libs/nitro/src/mi/cpumem.c` | khdays `libs/nitro/mi/asm_stubs/auto/{MIi_CpuCopy16,MIi_CpuCopy32,MIi_CpuClearFast,MIi_CpuCopyFast,MI_Copy36B,MI_CpuFill8,MI_CpuCopy8}.c`; twewy `libs/nitro/src/mi/cpumem.c` (`MI_CpuFillU32`, `MI_CpuSwap` body) | one file; `MI_CpuSwap` named `MI_SwapWord` (khdays' name) |
