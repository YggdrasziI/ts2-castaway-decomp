/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned int));
extern void CTRDG_Enable(int enable);
extern void func_020759bc(void);
extern void func_02075af8(void);
extern void CTRDGi_InitTaskThread(void *p);
extern void func_02075abc(int fifoNo, unsigned int data);
extern void func_02075a3c(int fifoNo, unsigned int data);
extern void func_02075a08(int fifoNo, unsigned int data);

extern int data_020c5078;
extern int data_020c507c;
extern int data_020c5080;

extern char data_020c5160;

void func_02075d10(void)
{
    if (data_020c5078 != 0)
        return;

    data_020c5078 = 1;
    func_020759bc();
    data_020c507c = 0;
    func_0207c3c8();
    while (!PXI_IsCallbackReady(13, 1)) {
    }
    func_0207c5d4(13, func_02075abc);
    func_02075af8();
    func_0207c5d4(13, 0);
    func_0207c5d4(13, func_02075a3c);
    data_020c5080 = 0;
    CTRDGi_InitTaskThread(&data_020c5160);
    func_0207c5d4(17, func_02075a08);
    CTRDG_Enable(0);
}
