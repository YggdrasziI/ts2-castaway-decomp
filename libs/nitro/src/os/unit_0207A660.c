/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Swaps the IRQ work word +0x30 with the argument under an IRQ lock; returns the old value. */

extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int ThreadInfo[];

int func_0207a660(int arg0) {
    int mask;
    int old;
    mask = OS_DisableInterrupts();
    old = ThreadInfo[3];
    ThreadInfo[3] = arg0;
    OS_RestoreInterrupts(mask);
    return old;
}
