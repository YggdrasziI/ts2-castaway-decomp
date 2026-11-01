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
| `tools/progress_badges.py` | default version `eur`; function addresses read from the dsd `symbols.txt` files (dsd's objdiff report has no `virtual_address`); regions from `notes/SPLITS.md` |

## Project documents

`SPEC.md` and `notes/` follow the structure of spyro-dotd-decomp (same commit),
rewritten for the DS toolchain.

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

## MSL C and C++ runtime (`libs/c`, `libs/runtime`, `libs/cpp/include`, `libs/nitro/include`)

Source: twewy (**CC0-1.0**), local clone at commit
`3f916f1a2d31f29bd7ec6fd89f3a87b696e79b9b`, taken on 2026-11-01. Every function was
checked at 100 % in objdiff against this ROM.

| Our files | Their files | Changes |
|---|---|---|
| `libs/c/include/*`, `libs/runtime/include/*`, `libs/cpp/include/*` | same paths | none |
| `libs/nitro/include/nitro/{types.h,os/mutex.h,os/thread.h,os/context.h}` | same paths | none; needed by `critical_regions.h` |
| `libs/c/src/{abort_exit_arm_eabi,critical_regions,file_io,mem,mem_funcs,signal,string}.c` | same paths | none |
| `libs/c/src/mbstring.c` | same path | `mbtowc` removed (not in this ROM, it was kept by the link) |
| `libs/c/src/scanf.c` | same path | reduced to `__StringRead`, the only function linked here |
| `libs/c/src/{ansi_files,buffer_io,math_api}.c`, `libs/c/src/math/{s_copysign,s_fabs,s_frexp,s_ldexp}.c` | same paths | none |
| `libs/c/src/ansi_fp.c` | same path | `__equals_dec`, `__less_dec`, `__minus_dec`, `__dec2num` removed (not in this ROM) |
| `libs/c/src/strtoul.c` | same path | `__strtoull`, `strtoul` removed (not in this ROM); `strtol`, `atoi` written from the ROM |
| `libs/c/src/string.c` | same path | `strstr` written from the ROM |
| `libs/c/src/arith.c` | none | `abs` written from the ROM; file name from the header `arith.h` |
| `libs/c/src/printf.c` | same path | `vsprintf` replaced by `snprintf` (written from the ROM); `%s` path rewritten from the ROM: wide strings rejoin the narrow path, `strptr` merged into `buff_ptr`; `case 'p'` dropped (jump table end) |
| `libs/runtime/src/{console_io.c,CompressedNumbers.cpp,StaticInitializers.cpp}` | same paths | none |
| `libs/runtime/src/ExceptionHandler.cpp` | same path | `__unexpected` removed (not in this ROM); two `continue` tests rewritten for the branch order (`break`, `goto`); `__end_catch` renamed `__end__catch`, the name the compiler calls |
| `libs/runtime/src/ExceptionHandlerTS.cpp` | same path | `mov pc, address` instead of `bx address` |
| `libs/runtime/src/MWException.cpp` | same path | `unexpected` removed; `__register_global_object` written from the ROM |
| `libs/runtime/src/cxxabi_alloc.cpp` | same path | `__cxa_vec_newinit`, `__cxa_vec_ctor`, `__cxa_vec_cleanup`, `__cxa_vec_delete2` written from the ROM |

## Runtime FP and division helpers (`libs/runtime/src`)

Source: advance-wars-dual-strike-decomp (**CC0-1.0**), local clone at commit
`47864817dc01b491422fe6e9f02c8be6752efa7e`, `src/sdk/runtime`, taken on 2026-11-01.

| Our files | Their files | Changes |
|---|---|---|
| `_dadd.c`, `ll_ufrom_d.c`, `_dmul.c`, `_dsub.c`, `fadd.c`, `fdiv.c`, `ffix.c`, `fflt.c`, `ffltu.c`, `fmul.c`, `fsub.c`, `ll_sdiv.c`, `ll_udiv.c`, `s32_div_f.c`, `u32_div_f.c` | same names | `__MWERKS__` branch only; helper names not proven replaced by address names; `#pragma force_active on`; hand-encoded branches recomputed for this ROM's layout; swap entry added before `_fdiv` and `_fsub` |
| `ffix_tail.c` | `func_02128438.c` | same changes, renamed for its role |
| `fp_compare.c` | none | written from this ROM: the reference has other functions in another order |

`libs/runtime/src/__arm_eabi_init.c`: twewy (CC0, commit in the MSL section), `_ExitProcess` only, include replaced by a declaration.
`libs/c/src/fp_trap.c`, `fp_status.c`, `fp_handlers.c`, `fp_control.c`: written from this ROM.
`libs/nitro/src/os/os_mutex.c`: khdays (CC0) `libs/nitro/os/{auto,calls}/` mutex functions and twewy (CC0) `libs/nitro/src/os/mutex.c` for the shape, retyped; every function at 100 %.

`libs/nitro/src/os/unit_02079FF4.c`, `os/unit_0207AE98.c`, `pm/unit_0207F47C.c`, `libs/nns/src/snd/unit_0209E798.c`,
`libs/nns/src/fnd/unit_0209E854.c`: khdays (CC0) `libs/nitro/{os,spi,nns}` and `libs/nns/snd`, one file each, retyped with local types.
