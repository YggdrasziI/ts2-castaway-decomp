/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned int));
extern void func_0207f130(int fifoNo, unsigned int data);
extern unsigned short data_020c7720;
extern int data_020c7724[];
void func_0207f390(void)
{
    if (data_020c7720 != 0)
        return;
    data_020c7720 = 1;
    data_020c7724[0] = 0;
    data_020c7724[1] = 0;
    func_0207c3c8();
    while (!PXI_IsCallbackReady(9, 1)) {
    }
    *(int *)0x027fff90 = 0;
    func_0207c5d4(9, func_0207f130);
}
