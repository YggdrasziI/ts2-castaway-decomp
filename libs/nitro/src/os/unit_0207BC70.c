/* NitroSDK: frame counter from the V count; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

extern int data_020c5ab4;
extern int data_020c5ab8;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);

int func_0207bc70(int count) {
    int mask = OS_DisableInterrupts();
    if (count < data_020c5ab4) {
        data_020c5ab8++;
    }
    data_020c5ab4 = count;
    OS_RestoreInterrupts(mask);
    return data_020c5ab8;
}
