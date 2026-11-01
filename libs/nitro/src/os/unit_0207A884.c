/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *OSi_RemoveLinkFromQueue(void *queue);
extern void func_0207acfc(void);

/* Makes every thread waiting on the queue runnable and empties the queue. */
void func_0207a884(char *queue) {
    int enabled = OS_DisableInterrupts();
    if (*(int *)queue != 0) {
        while (*(int *)queue != 0) {
            char *thread = OSi_RemoveLinkFromQueue(queue);
            *(int *)(thread + 0x64) = 1;
            *(int *)(thread + 0x78) = 0;
            *(int *)(thread + 0x80) = 0;
            *(int *)(thread + 0x7c) = *(int *)(thread + 0x80);
        }
        *(int *)(queue + 4) = 0;
        *(int *)queue = *(int *)(queue + 4);
        func_0207acfc();
    }
    OS_RestoreInterrupts(enabled);
}
