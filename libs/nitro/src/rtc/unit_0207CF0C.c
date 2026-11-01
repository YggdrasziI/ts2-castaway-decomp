/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned int));
extern void func_0207c7f8(int fifoNo, unsigned int data);
extern unsigned short data_020c5b68;
extern int data_020c5b6c[];
void func_0207cf0c(void)
{
    if (data_020c5b68 != 0)
        return;
    data_020c5b68 = 1;
    data_020c5b6c[0] = 0;
    data_020c5b6c[1] = 0;
    data_020c5b6c[7] = 0;
    data_020c5b6c[2] = 0;
    data_020c5b6c[3] = 0;
    func_0207c3c8();
    while (!PXI_IsCallbackReady(5, 1)) {
    }
    func_0207c5d4(5, func_0207c7f8);
}
