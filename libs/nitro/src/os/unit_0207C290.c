/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


extern struct { unsigned short state; } data_020c5ac4;
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned));
extern void OSi_CommonCallback(int, unsigned);
void func_0207c290(void);

void func_0207c290(void)
{
    if (data_020c5ac4.state != 0) return;
    data_020c5ac4.state = 1;
    func_0207c3c8();
    while (!PXI_IsCallbackReady(0xc, 1));
    func_0207c5d4(0xc, OSi_CommonCallback);
}
