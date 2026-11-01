/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern u16 data_020c5700[];
extern u32 func_0207818c(int bank);
u32 func_0207815c(void) {
    return func_0207818c(data_020c5700[2]);
}
