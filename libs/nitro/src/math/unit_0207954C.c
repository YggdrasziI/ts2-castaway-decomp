/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
void func_0207954c(u32 *table, u32 poly) {
    u32 r, i, j;
    for (i = 0; i < 0x100; i++) {
        r = i;
        for (j = 0; j < 8; j++) {
            if (r & 1) {
                r = poly ^ (r >> 1);
            } else {
                r >>= 1;
            }
        }
        table[i] = r;
    }
}
