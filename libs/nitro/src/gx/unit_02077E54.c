/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern unsigned short data_020c56fc;
extern short data_020bcb70;
int GX_VBlankIntr(int enable);
void DispCnt_ApplyPendingMode(void);

int GX_VBlankIntr(int enable) {
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    int prev = *dispstat & 8;
    if (enable != 0) {
        *dispstat |= 8;
        return prev;
    }
    *dispstat &= ~8;
    return prev;
}

void DispCnt_ApplyPendingMode(void) {
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    unsigned short v;
    data_020bcb70 = 1;
    v = data_020c56fc;
    if (v != 0) {
        *reg_dispcnt = *reg_dispcnt & 0xfffcffff | (unsigned int)v << 0x10;
        return;
    }
    *reg_dispcnt = *reg_dispcnt | 0x10000;
}
