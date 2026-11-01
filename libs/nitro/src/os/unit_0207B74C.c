/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int func_0207b5f4(int arena);
extern void OS_SetArenaHi(int arena, int hi);
extern int func_0207b508(int arena);
extern void OS_SetArenaLo(int arena, int lo);
extern int func_0207b0dc(void);
extern void OS_SetProtectionRegion1(unsigned int v);
extern void OS_SetProtectionRegion2(unsigned int v);
extern int data_020c5a0c[];
void func_0207b74c(void);

void func_0207b74c(void) {
    OS_SetArenaHi(2, func_0207b5f4(2));
    OS_SetArenaLo(2, func_0207b508(2));
    if (data_020c5a0c[0] != 0) {
        if ((func_0207b0dc() & 3) != 1) {
            return;
        }
    }
    OS_SetProtectionRegion1(0x200002b);
    OS_SetProtectionRegion2(0x23e0021);
}
