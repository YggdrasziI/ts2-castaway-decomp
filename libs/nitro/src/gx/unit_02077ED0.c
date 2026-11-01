/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
void func_02077ed0(int x) {
    *(volatile u16 *)0x04000004 = (*(volatile u16 *)0x04000004 & 0x3f) | ((x & 0xff) << 8) | ((x & 0x100) >> 1);
}
