/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_0207acfc(void);
void OS_WakeupThreadDirect(char *thread);

void OS_WakeupThreadDirect(char *thread) {
    int enabled = OS_DisableInterrupts();
    *(int *)(thread + 0x64) = 1;
    func_0207acfc();
    OS_RestoreInterrupts(enabled);
}
