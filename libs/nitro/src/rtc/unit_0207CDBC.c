/* NitroSDK RTC: asynchronous request; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    int lock;
    void *callback;
    void *a;
    void *b;
    void *arg;
    int command;
    int status;
} Work;

extern Work data_020c5b6c;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int func_0207cfe8(void);

int func_0207cdbc(void *a, void *b, void *callback, void *arg) {
    int mask = OS_DisableInterrupts();
    if (data_020c5b6c.lock) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    data_020c5b6c.lock = 1;
    OS_RestoreInterrupts(mask);
    data_020c5b6c.command = 2;
    data_020c5b6c.status = 0;
    data_020c5b6c.a = a;
    data_020c5b6c.b = b;
    data_020c5b6c.callback = callback;
    data_020c5b6c.arg = arg;
    return func_0207cfe8() ? 0 : 3;
}
