/* NitroSDK OS: moves the current thread after the last thread of its priority; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct Thread {
    unsigned char pad[0x68];
    struct Thread *next;
    int pad6c;
    int priority;
} Thread;

extern struct {
    int pad;
    Thread *current;
    Thread *list;
} ThreadInfo;

extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void func_0207acfc(void);

void func_0207a748(void) {
    Thread *current = ThreadInfo.current;
    Thread *before = 0;
    Thread *last = 0;
    int count = 0;
    int mask = OS_DisableInterrupts();
    Thread *t = ThreadInfo.list;
    Thread *prev = 0;
    while (t != 0) {
        if (t == current) {
            before = prev;
        }
        if (current->priority == t->priority) {
            last = t;
            count++;
        }
        prev = t;
        t = t->next;
    }
    if (count <= 1 || last == current) {
        OS_RestoreInterrupts(mask);
        return;
    }
    if (before == 0) {
        ThreadInfo.list = current->next;
    } else {
        before->next = current->next;
    }
    current->next = last->next;
    last->next = current;
    func_0207acfc();
    OS_RestoreInterrupts(mask);
}
