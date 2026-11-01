/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void MI_WaitDma(u32 dma);
extern void GX_SetBankForTex(int bank);
extern u32 data_020bcb74;
extern int data_020c5728;
extern int data_020c5730;
extern int data_020c572c;
extern int data_020c571c;
void func_02079260(void) {
    if (data_020bcb74 != 0xffffffff) {
        MI_WaitDma(data_020bcb74);
    }
    GX_SetBankForTex(data_020c5728);
    data_020c5730 = 0;
    data_020c572c = 0;
    data_020c571c = 0;
    data_020c5728 = 0;
}
