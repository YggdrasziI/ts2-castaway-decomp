/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on




int OS_GetArenaHi(int i);
int OS_GetArenaLo(int i);

int OS_GetArenaHi(int i){ return *(int *)(0x27ff000 + (i << 2) + 3524); }

int OS_GetArenaLo(int i){ return *(int *)(0x27ff000 + (i << 2) + 3488); }
