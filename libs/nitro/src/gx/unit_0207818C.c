/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
u32 func_0207818c(int b) {
    u32 s = 0;
    if (b & 1) s += 0x20000;
    if (b & 2) s += 0x20000;
    if (b & 4) s += 0x20000;
    if (b & 8) s += 0x20000;
    if (b & 16) s += 0x10000;
    if (b & 32) s += 0x4000;
    if (b & 64) s += 0x4000;
    if (b & 128) s += 0x8000;
    if (b & 256) s += 0x4000;
    return s;
}
