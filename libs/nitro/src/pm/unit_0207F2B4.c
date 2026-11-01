/* NitroSDK PM: asynchronous command with a selector; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned short u16;
typedef void (*Callback)(int result, void *arg);

typedef struct {
    int lock;
    Callback callback;
    void *arg;
    int pad;
    Callback alarm;
    void *alarmArg;
    u16 *status;
} Work;

extern Work data_020c7724;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int func_0207f0f8(int command);

int func_0207f2b4(int selector, u16 *status, Callback callback, void *arg) {
    int command;
    int mask;
    if (selector >= 6) {
        return 2;
    }
    switch (selector) {
    case 0:
        command = 0;
        break;
    case 1:
        command = 1;
        break;
    case 2:
        command = 2;
        break;
    case 3:
        command = 3;
        break;
    default:
        return 2;
    }
    mask = OS_DisableInterrupts();
    if (data_020c7724.lock) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    data_020c7724.lock = 1;
    OS_RestoreInterrupts(mask);
    data_020c7724.callback = callback;
    data_020c7724.arg = arg;
    data_020c7724.status = status;
    return func_0207f0f8(command) ? 0 : 3;
}
