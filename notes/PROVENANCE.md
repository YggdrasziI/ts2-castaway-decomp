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

`libs/nitro/include/sdk/*.h`: khdays (CC0) `include/nitro/*.h`, includes renamed to `sdk/`. `libs/nitro/src/gx/unit_02078208.c`, `unit_02078C48.c`: khdays `libs/nitro/gx/{auto,calls}`, per-function sources merged in reverse address order.

`libs/nitro/src/mi/unit_02079590.c`, `libs/nitro/src/snd/unit_0207D1F8.c`: written from the ROM; khdays (CC0) `libs/nitro/{mi,snd}` for the loop shapes and the names.

`libs/nitro/src/fs/unit_02075F70.c`: khdays (CC0) `libs/nitro/fs/{auto,calls}`, per-function sources retyped against `sdk/fs.h`; the functions khdays lacks written from the ROM. Names from khdays, except `FS_RegisterArchiveName` and `FS_InitArchive` from Advance Wars' `symbols.txt` (same order, `FS_RegisterArchiveName` same size) and st's `fs_archive.h`.

`libs/nitro/src/fx/unit_02077AE4.c`: written from the ROM.

Generated NitroSDK / NitroSystem units `libs/{nitro,nns}/src/*/unit_*.c` named after their first address: khdays (CC0) per-function sources of byte-identical functions, merged, with the callee and data symbols of this ROM read from its relocations. `libs/nitro/include/nnsys/*.h`: khdays `include/nnsys`, includes renamed to `sdk/`. A name comes from khdays only when the function is exact, at least 0x20 bytes, and unique; the rest stay address based. Directory names are the khdays module of the first function, not evidence.

One-function NitroSDK / NitroSystem units `libs/{nitro,nns}/src/*/unit_*.c` with a "retyped for this ROM" header, and `libs/nns/src/snd/unit_0209D5E0.c`: khdays (CC0) per-function sources, callees and data renamed from the ROM relocations, struct offsets and constants corrected to this ROM.

`libs/nitro/src/card/unit_02074DF0.c`: khdays (CC0, local clone at commit `93535afd7ca082f3d856bbf1cadae65be16d44ba`) `libs/nitro/card/calls/CARDi_TryReadCardDma.c`, adapted to this ROM: no instruction / data cache thresholds (always invalidate by range), structure offsets, callees and data renamed from the ROM relocations.

Written from the ROM, no reference code: the 64-byte send `libs/nitro/src/gx/unit_020794B4.c` (`asm` function), the tail-call thunks `libs/nitro/src/card/unit_020745AC.c`, `card/unit_02075438.c`, `ctrdg/unit_020759FC.c` (1.2 with `-interworking` emits `ldr ip` / `bx ip`) and the empty functions `libs/nitro/src/fx/unit_02077E50.c`, `libs/nns/src/snd/unit_0209D4AC.c`, `snd/unit_0209D4D0.c`.

`libs/nitro/src/os/unit_0207BA54.c`: Advance Wars (CC0, local clone at commit `47864817dc01b491422fe6e9f02c8be6752efa7e`) `src/sdk/os/exception_run_user_hook.c`, the `asm` function only, data and callee symbols renamed for this ROM.

`libs/nitro/src/os/unit_02079FBC.c`, `os/unit_0207B508.c` and `os/unit_0207ABA0.c`: khdays (CC0, commit `93535afd7ca082f3d856bbf1cadae65be16d44ba`) `libs/nitro/os/calls/OSi_InitStackChecker.c`, `OS_GetInitArenaLo.c`, `OS_GetInitArenaHi.c` and `OS_InitThread.c`, retyped for this ROM (its arena bounds and IRQ stack size). The link-time constants are absolute symbols defined by `tools/lcf_keep.py`, as khdays does in its `tools/configure.py`.

`libs/nitro/src/crt0/unit_02000800.c`: written from the ROM; Advance Wars (CC0, commit `47864817dc01b491422fe6e9f02c8be6752efa7e`) `src/sdk/crt0/*.c` gave the structure of the asm functions and `include/text_data.h` the `#pragma define_section` that keeps BuildInfo in `.text`.

`libs/nns/src/fnd/unit_0209ECB8.c`: Heroes of Mana (CC0, [liolu/heroes-of-mana-decomp](https://github.com/liolu/heroes-of-mana-decomp), commit `d29040d08683bff5749126166f0fd2f86e20096b`) `src/auto/NNS_FndAllocFromFrmHeapEx.c`, its own code (not a `donor/` file), callees renamed for this ROM.

`libs/nns/src/fnd/unit_0209EDA0.c`: Heroes of Mana (CC0, commit `d29040d08683bff5749126166f0fd2f86e20096b`) `src/auto/func_020082c4.c`, callee renamed for this ROM.

`libs/nitro/src/os/unit_0207BBD4.c`: Rayman Raving Rabbids (CC0, [liolu/Rayman-RR-usa-decomp](https://github.com/liolu/Rayman-RR-usa-decomp), commit `dfb4f24f4bf88952270a012294c5a37cf3868ed3`) `src/nitro/os/os_tick_3.c`, its own code, retyped for this ROM (tick counter as a volatile 64-bit object).

`libs/nitro/src/gx/unit_020792D0.c`: Heroes of Mana (CC0, commit `d29040d08683bff5749126166f0fd2f86e20096b`) `src/nitro/gx/gx_load3d.c`, `GX_LoadTex` only (its own code), retyped for this ROM. The two copy inlines are written here (the CPU / DMA choice of the SDK, as in `gx/unit_020791A4.c`), not taken from that file's reused `UnkGxCopy32`.
