/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* NitroSDK SND: pops a command from the free list under an IRQ lock; NULL when empty. */

extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int *data_020c5bac[];
extern int *data_020c5bbc;

int *func_0207d688(void) {
    int mask;
    int *h;
    int *n;
    mask = OS_DisableInterrupts();
    h = data_020c5bac[0];
    if (h == 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    n = (int *)*h;
    data_020c5bac[0] = n;
    if (n == 0) data_020c5bbc = 0;
    OS_RestoreInterrupts(mask);
    return h;
}
