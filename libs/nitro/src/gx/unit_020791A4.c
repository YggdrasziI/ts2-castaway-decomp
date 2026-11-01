/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void MI_DmaCopy32Async(u32 ch, const void *src, void *dst, u32 len, void *cb, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 len);
extern char *data_020c5720;
extern u32 data_020bcb74;
void func_020791a4(const void *src, u32 offset, u32 len) {
    char *dst = data_020c5720 + offset;
    u32 dma = data_020bcb74;
    if (dma != 0xffffffff) {
        MI_DmaCopy32Async(dma, src, dst, len, 0, 0);
    } else {
        MIi_CpuCopy32(src, dst, len);
    }
}
