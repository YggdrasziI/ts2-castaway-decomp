/* NitroSDK: worker thread body running queued requests; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct Request {
    int (*func)(struct Request *r);
    void (*done)(struct Request *r);
    int result;
    int pad[6];
} Request;

typedef struct {
    unsigned char pad[0xc0];
    Request *volatile request;
} Thread;

extern struct {
    unsigned char pad[0x22];
    unsigned char busy;
} data_020c524c;
extern int data_020c5248;

extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void func_0207a904(int queue);
extern void func_0207aa6c(void);

void func_02075de0(Thread *thread) {
    Request r;
    int mask;
    for (;;) {
        MI_CpuFill8(&r, 0, sizeof(Request));
        mask = OS_DisableInterrupts();
        while (thread->request == 0) {
            func_0207a904(0);
        }
        r = *thread->request;
        OS_RestoreInterrupts(mask);
        if (r.func) {
            r.result = r.func(&r);
        }
        mask = OS_DisableInterrupts();
        data_020c524c.busy = 0;
        if (r.done) {
            r.done(&r);
        }
        if (data_020c5248 == 0) {
            break;
        }
        thread->request = 0;
        OS_RestoreInterrupts(mask);
    }
    func_0207aa6c();
}
