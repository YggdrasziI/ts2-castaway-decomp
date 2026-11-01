/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned int));
extern void OS_InitMutex(void *mutex);
extern void func_0207fe78(int fifoNo, unsigned int data);
extern unsigned short data_020c7740;
extern int data_020c7758[];
extern int data_020c7750;
extern unsigned short data_020c7780[5][4];
extern int data_020c7768;
void func_0207ff64(void)
{
    int i;
    if (data_020c7740 != 0)
        return;
    data_020c7740 = 1;
    data_020c7758[0] = 0;
    data_020c7758[1] = 0;
    func_0207c3c8();
    while (!PXI_IsCallbackReady(8, 1)) {
    }
    func_0207c5d4(8, func_0207fe78);
    for (i = 0; i < 5; i++) {
        data_020c7780[i][0] = 0;
    }
    OS_InitMutex(&data_020c7768);
    data_020c7750 = *(int *)0x027ffc3c;
}
