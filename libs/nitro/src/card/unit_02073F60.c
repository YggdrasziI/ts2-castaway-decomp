/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern void func_0207a904(void *queue);
extern char data_020c4800;

/* Blocks until the card's pending transfer finishes; true if it succeeded. */
int func_02073f60(void) {
    char *card = (char *)&data_020c4800;
    int enabled = OS_DisableInterrupts();
    if ((*(volatile int *)(card + 0x114) & 4) != 0) {
        char *q = card + 0x10c;
        do {
            func_0207a904(q);
        } while ((*(volatile int *)(card + 0x114) & 4) != 0);
    }
    OS_RestoreInterrupts(enabled);
    return **(int **)card == 0;
}
