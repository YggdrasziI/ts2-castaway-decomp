/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_0207553c(int a, int b, int c);

/* Raises the "card pulled out" fault when the cartridge id no longer matches the one recorded at
 * boot. */
void func_02075444(int id) {
    volatile int stored;
    int enabled;
    int *src;
    if (*(unsigned short *)0x027ffc10 == 0) {
        src = (int *)0x027ff800;
    } else {
        src = (int *)0x027ffc00;
    }
    stored = *src;
    if (id != stored) {
        enabled = OS_DisableInterrupts();
        func_0207553c(0xe, 0x11, 0);
        OS_RestoreInterrupts(enabled);
    }
}
