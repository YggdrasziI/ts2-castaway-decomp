/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern int func_020781e0(void);
const u16 data_020b32ec[8] = {
    0x0000, 0x6880, 0x6890, 0x6880, 0x6894, 0x0000, 0x6890, 0x6880,
};
extern int data_020c5724;
extern int data_020c5720;
void func_02079218(void) {
    int s = func_020781e0();
    data_020c5724 = s;
    data_020c5720 = data_020b32ec[s >> 4] << 12;
}
