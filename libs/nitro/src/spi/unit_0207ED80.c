/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned int));
extern void func_0207ee10(int fifoNo, unsigned int data);
extern unsigned short data_020c76e4;
extern struct { int cb; char a[8]; unsigned short index; char b[2]; int bufs; char c[0x1c]; unsigned short flg, state, err, cmd; } data_020c76e8;
void func_0207ed80(void)
{
    if (data_020c76e4 != 0)
        return;
    data_020c76e4 = 1;
    func_0207c3c8();
    data_020c76e8.state = 0;
    data_020c76e8.cmd = 0;
    data_020c76e8.index = 0;
    data_020c76e8.cb = 0;
    data_020c76e8.bufs = 0;
    data_020c76e8.flg = 0;
    data_020c76e8.err = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    func_0207c5d4(6, func_0207ee10);
}
