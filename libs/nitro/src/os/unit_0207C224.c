/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void OS_Terminate(void);
extern unsigned short data_020c5ac8;
extern void func_02075438(int n);
extern void OS_WaitIrq(int clear, int mask);
void OSi_CommonCallback(int unused, int status);
void OS_WaitVBlankIntr(void);

void OSi_CommonCallback(int unused, int status) {
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        data_020c5ac8 = 1;
        return;
    }
    OS_Terminate();
}

void OS_WaitVBlankIntr(void) {
    int one = 1;
    func_02075438(one);
    OS_WaitIrq(one, one);
}
