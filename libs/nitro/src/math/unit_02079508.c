/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
void func_02079508(const u32 *table, u32 *ctx, const u8 *data, u32 len) {
    u32 c = *ctx;
    u32 i;
    for (i = 0; i < len; i++) {
        c = table[(c ^ data[0]) & 0xff] ^ (c >> 8);
        data++;
    }
    *ctx = c;
}
