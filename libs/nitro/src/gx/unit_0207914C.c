/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void MI_WaitDma(u32 dma);
extern void GX_SetBankForTexPltt(int bank);
extern u32 data_020bcb74;
extern int data_020c5724;
extern int data_020c5720;
void func_0207914c(void) {
    if (data_020bcb74 != 0xffffffff) {
        MI_WaitDma(data_020bcb74);
    }
    GX_SetBankForTexPltt(data_020c5724);
    data_020c5724 = 0;
    data_020c5720 = 0;
}
