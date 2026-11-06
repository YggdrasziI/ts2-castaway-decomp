/* NitroSDK os_arena.c: the default arena bounds (functions in reverse address order).
 * khdays' OS_GetInitArenaLo and OS_GetInitArenaHi (CC0), retyped for this ROM. The
 * SDK_* figures are link-time constants of the SDK build, defined as absolute symbols
 * by tools/lcf_keep.py with the values of this ROM's literal pools; the stack sizes
 * are tested at run time, so they must stay symbols. The other bounds are literals
 * here. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef int s32;
typedef int OSArenaId;

enum {
    OS_ARENA_MAIN = 0,
    OS_ARENA_MAIN_SUBPRIV,
    OS_ARENA_MAINEX,
    OS_ARENA_ITCM,
    OS_ARENA_DTCM,
    OS_ARENA_SHARED,
    OS_ARENA_WRAM_MAIN
};

extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);
extern void SDK_SECTION_ARENA_DTCM_START(void);
#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)
#define OSi_DTCM_ARENA_LO_DEFAULT ((u32)SDK_SECTION_ARENA_DTCM_START)

extern u32 data_027e0000;
#define HW_DTCM ((u32)&data_027e0000)
#define HW_DTCM_IRQ_STACK_END_ADDR (HW_DTCM + 0x3f80)

extern u32 data_020c5a0c; /* the extended main memory arena is enabled */
extern u32 func_0207b0dc(void); /* console type */

void *func_0207b5f4(OSArenaId id) {
    switch (id) {
    case OS_ARENA_MAIN:
        return (void *)0x023e0000;
    case OS_ARENA_MAINEX:
        if (!data_020c5a0c || (func_0207b0dc() & 3) == 1) {
            return (void *)0;
        } else {
            return (void *)0x02700000;
        }
    case OS_ARENA_ITCM:
        return (void *)0x02000000;
    case OS_ARENA_DTCM: {
        u32 irqStackLo;
        u32 sysStackLo;

        irqStackLo = HW_DTCM_IRQ_STACK_END_ADDR - OSi_IRQ_STACKSIZE;

        if (OSi_SYS_STACKSIZE == 0) {
            sysStackLo = HW_DTCM;
            if (sysStackLo < OSi_DTCM_ARENA_LO_DEFAULT) {
                sysStackLo = OSi_DTCM_ARENA_LO_DEFAULT;
            }
        } else if (OSi_SYS_STACKSIZE < 0) {
            sysStackLo = OSi_DTCM_ARENA_LO_DEFAULT - OSi_SYS_STACKSIZE;
        } else {
            sysStackLo = irqStackLo - OSi_SYS_STACKSIZE;
        }
        return (void *)sysStackLo;
    }
    case OS_ARENA_SHARED:
        return (void *)0x027ff680;
    case OS_ARENA_WRAM_MAIN:
        return (void *)0x037f8000;
    default:
    }

    return 0;
}

void *func_0207b508(OSArenaId id) {
    switch (id) {
    case OS_ARENA_MAIN:
        return (void *)0x020d7160;
    case OS_ARENA_MAINEX:
        if (!data_020c5a0c || (func_0207b0dc() & 3) == 1) {
            return (void *)0;
        }
        return (void *)0x023e0000;
    case OS_ARENA_ITCM:
        return (void *)0x01ffb0c0;
    case OS_ARENA_DTCM:
        return (void *)0x027e0080;
    case OS_ARENA_SHARED:
        return (void *)0x027ff000;
    case OS_ARENA_WRAM_MAIN:
        return (void *)0x037f8000;
    }

    return (void *)0;
}
