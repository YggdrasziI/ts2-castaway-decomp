/* NitroSDK: worker thread of the card library; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct Common {
    unsigned char pad[0x40];
    void (*func)(struct Common *c);
    unsigned char queue[0xc0];
    void *wait;
    unsigned char pad108[0xc];
    volatile unsigned int flags;
} Common;

extern Common data_020c4800;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void func_0207a904(void *queue);

void func_02075328(void) {
    Common *c = &data_020c4800;
    for (;;) {
        int mask = OS_DisableInterrupts();
        while (!(c->flags & 8)) {
            c->wait = c->queue;
            func_0207a904(0);
        }
        OS_RestoreInterrupts(mask);
        c->func(c);
    }
}
