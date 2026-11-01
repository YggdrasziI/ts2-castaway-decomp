/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on




void OS_SetArenaHi(int i, int v);
void OS_SetArenaLo(int i, int v);

void OS_SetArenaHi(int i, int v){ *(int *)(0x27ff000 + (i << 2) + 3524) = v; }

void OS_SetArenaLo(int i, int v){ *(int *)(0x27ff000 + (i << 2) + 3488) = v; }
