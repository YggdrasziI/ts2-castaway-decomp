/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


extern struct { int field_1c; } data_020c7758;
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
int func_020800c4(void);

int func_020800c4(void) {
    int mask = OS_DisableInterrupts();
    if (data_020c7758.field_1c != 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    data_020c7758.field_1c = 1;
    OS_RestoreInterrupts(mask);
    return 1;
}
