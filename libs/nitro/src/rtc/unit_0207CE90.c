/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
extern int func_0207cfd8(void);

extern int data_020c5b6c[];

int func_0207ce90(void *time, void *callback, void *arg) {
    int mask;

    mask = OS_DisableInterrupts();
    if (data_020c5b6c[0] != 0) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    data_020c5b6c[0] = 1;
    OS_RestoreInterrupts(mask);
    data_020c5b6c[5] = 1;
    data_020c5b6c[6] = 0;
    data_020c5b6c[2] = (int)time;
    data_020c5b6c[1] = (int)callback;
    data_020c5b6c[4] = (int)arg;
    if (func_0207cfd8() != 0) {
        return 0;
    }
    return 3;
}