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
int func_0207fd4c(unsigned int arg0, int arg1, int arg2);

int func_0207fd4c(unsigned int arg0, int arg1, int arg2)
{
    if (func_020800c4() == 0) return 1;
    data_020c7758.field_20 = arg1;
    data_020c7758.field_24 = arg2;
    PMi_SendPxiData(((arg0 >> 16) & 0xff) | 0x02006300);
    PMi_SendPxiData(0x01010000 | (arg0 & 0xffff));
    return 0;
}
