/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void func_0207a174(u32 mask, void (*fn)(void));
extern void func_0207bd0c(void);
extern void func_02077ed0(int x);
extern u32 OS_EnableIrqMask(u32 mask);
void func_0207bf14(const char *p) {
    func_0207a174(4, func_0207bd0c);
    func_02077ed0(*(const short *)(p + 0x10));
    *(volatile u16 *)0x04000004 |= 0x20;
    OS_EnableIrqMask(4);
}
