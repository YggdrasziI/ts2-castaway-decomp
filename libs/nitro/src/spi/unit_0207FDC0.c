/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern int func_020800c4(void);
extern void PMi_SendPxiData(u32 cmd);
extern int func_0207f590(int a, int b, int c, int d);
extern volatile int data_020c7744;
extern volatile int data_020c7748;
int func_0207fdc0(u32 ch, u32 value) {
    if (func_020800c4() == 0) {
        return 1;
    }
    data_020c7744 = 0;
    PMi_SendPxiData(0x03006000);
    while (data_020c7744 == 0) {
    }
    data_020c7744 = 0;
    data_020c7748 = 0;
    func_0207f590(0, 2, 0, 0);
    PMi_SendPxiData((ch & 0xff) | 0x02006100);
    PMi_SendPxiData((value & 0xffff) | 0x01010000);
    return 0;
}
