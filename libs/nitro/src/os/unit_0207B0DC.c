/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_0207a904(void *queue);
extern void func_0207a884(void *queue);
extern long long _s32_div_f(int a, int b);
extern int data_020bcb88;
int OS_ReceiveMessage(char *q, void **out, int flags);
int func_0207b0f4(void);
int func_0207b0dc(void);

int OS_ReceiveMessage(char *q, void **out, int flags) {
    int enabled = OS_DisableInterrupts();
    while (*(int *)(q + 0x1c) == 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        func_0207a904(q + 8);
    }
    if (out != 0) {
        *out = (*(void ***)(q + 0x10))[*(int *)(q + 0x18)];
    }
    *(int *)(q + 0x18) = (int)(_s32_div_f(
        *(int *)(q + 0x18) + 1, *(int *)(q + 0x14)) >> 32);
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) - 1;
    func_0207a884(q);
    OS_RestoreInterrupts(enabled);
    return 1;
}

int func_0207b0f4(void){ return 0; }

int func_0207b0dc(void) {
    return data_020bcb88 = 0x82000001;
}
