/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void resetBankForX_(void *p);
extern unsigned short data_020c5700[];
void func_020781f4(void);
void func_020781e0(void);

void func_020781f4(void) {
    resetBankForX_(&data_020c5700[4]);
}

void func_020781e0(void) {
    resetBankForX_(&data_020c5700[5]);
}
