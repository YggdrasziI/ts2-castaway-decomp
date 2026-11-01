/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#define OS_ARENA_MAIN       0
#define OS_ARENA_MAINEX     2
#define OS_ARENA_ITCM       3
#define OS_ARENA_DTCM       4
#define OS_ARENA_SHARED     5
#define OS_ARENA_WRAM_MAIN  6
extern void *func_0207b5f4(int nArena);
extern void *func_0207b508(int nArena);
extern void OS_SetArenaHi(int nArena, void *pAddress);
extern void OS_SetArenaLo(int nArena, void *pAddress);
extern BOOL data_020c5a08;
void OS_InitArena(void);

void OS_InitArena(void)
{
    if (data_020c5a08) {
        return;
    }
    data_020c5a08 = 1;

    OS_SetArenaHi(OS_ARENA_MAIN, func_0207b5f4(OS_ARENA_MAIN));
    OS_SetArenaLo(OS_ARENA_MAIN, func_0207b508(OS_ARENA_MAIN));

    OS_SetArenaLo(OS_ARENA_MAINEX, (void *)0);
    OS_SetArenaHi(OS_ARENA_MAINEX, (void *)0);

    OS_SetArenaHi(OS_ARENA_ITCM, func_0207b5f4(OS_ARENA_ITCM));
    OS_SetArenaLo(OS_ARENA_ITCM, func_0207b508(OS_ARENA_ITCM));

    OS_SetArenaHi(OS_ARENA_DTCM, func_0207b5f4(OS_ARENA_DTCM));
    OS_SetArenaLo(OS_ARENA_DTCM, func_0207b508(OS_ARENA_DTCM));

    OS_SetArenaHi(OS_ARENA_SHARED, func_0207b5f4(OS_ARENA_SHARED));
    OS_SetArenaLo(OS_ARENA_SHARED, func_0207b508(OS_ARENA_SHARED));

    OS_SetArenaHi(OS_ARENA_WRAM_MAIN, func_0207b5f4(OS_ARENA_WRAM_MAIN));
    OS_SetArenaLo(OS_ARENA_WRAM_MAIN, func_0207b508(OS_ARENA_WRAM_MAIN));
}
