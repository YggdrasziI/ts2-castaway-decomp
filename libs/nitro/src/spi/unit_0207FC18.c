/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


struct CC {
    char _0[4];
    int field_20;
    int field_24;
};
extern int func_020800c4(void);
extern void PMi_SendPxiData(unsigned int cmd);
extern struct CC data_020c7758;
int func_0207fc18(int arg0, int arg1, int arg2, int arg3);

int func_0207fc18(int arg0, int arg1, int arg2, int arg3)
{
    if (func_020800c4() == 0) return 1;
    data_020c7758.field_20 = arg2;
    data_020c7758.field_24 = arg3;
    PMi_SendPxiData((arg0 & 0xff) | 0x02006400);
    PMi_SendPxiData(0x01010000 | (arg1 & 0xffff));
    return 0;
}
