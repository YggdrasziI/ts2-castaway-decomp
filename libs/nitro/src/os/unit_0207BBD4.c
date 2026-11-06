/* NitroSDK os_tick.c: OS_InitTick. Rayman Raving Rabbids' source (CC0, its own
 * os_tick_3.c, not a donor file), retyped for this ROM. The tick counter must be a
 * volatile 64-bit object: as two plain words, the second pool load is scheduled after
 * the first store. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern void *func_0207a174(u32 mask, void (*function)(void)); /* OS_SetIrqFunction */
extern u32 OS_EnableIrqMask(u32 mask);
extern void func_0207bb30(int timer); /* OSi_SetTimerReserved */
extern void func_0207bb4c(void);      /* OSi_CountUpTick */
extern u16 data_020c5aa0;             /* OSi_UseTick */
extern s32 data_020c5aa4;             /* OSi_NeedResetTimer */
extern volatile unsigned long long data_020c5aa8; /* OSi_TickCounter */

void func_0207bbd4(void) {
    if (data_020c5aa0 != 0) {
        return;
    }
    data_020c5aa0 = 1;
    func_0207bb30(0);
    data_020c5aa8 = 0;
    *(s16 *)0x04000102 = 0;
    *(s16 *)0x04000100 = 0;
    *(s16 *)0x04000102 = 0xC1;
    func_0207a174(8, func_0207bb4c);
    OS_EnableIrqMask(8);
    data_020c5aa4 = 0;
}
