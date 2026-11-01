/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern u32 func_0207f980(void);
extern void OS_SpinWait(u32 cycles);
extern void func_020753d4(u32 data, u32 wait);
extern void OS_Terminate(void);
static inline int PAD_DetectFold(void) { return (int)((*(volatile u16 *)0x027fffa8 & 0x8000) >> 15); }
void func_020754b4(void)
{
    int halt = 1;
    if (PAD_DetectFold()) {
        u32 res;
        while ((res = func_0207f980()) == 4) {
            OS_SpinWait(0xa3a47);
        }
        if (res == 0) {
            halt = 0;
        }
    }
    if (halt) {
        func_020753d4(1, 1);
    }
    OS_Terminate();
}
