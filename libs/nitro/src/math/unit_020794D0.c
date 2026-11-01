/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void func_02079508(const u32 *table, u32 *ctx, const u8 *data, u32 len);
u32 func_020794d0(const u32 *table, const u8 *data, u32 len) {
    u32 c = 0xffffffff;
    func_02079508(table, &c, data, len);
    return ~c;
}
