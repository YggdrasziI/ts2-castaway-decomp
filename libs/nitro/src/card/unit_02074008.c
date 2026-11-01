/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef struct { void *volatile head; void *volatile tail; } Queue;
typedef struct { void *cmd; int a4; volatile int owner; volatile int ref; Queue lockQ; int target; char a1c[0x28]; char thread[0xc4]; volatile int prio; Queue busyQ; } Common;
extern Common data_020c4800;
extern char data_020c47a0[];
extern char data_020c4e20[];
extern void MIi_CpuClearFast(u32 v, void *d, u32 n);
extern void DC_FlushRange(const void *p, u32 n);
extern void MI_CpuCopy8(const void *s, void *d, u32 n);
extern void func_0207aa98(void *t, void (*f)(void *), void *a, void *stack, u32 size, u32 prio);
extern void OS_WakeupThreadDirect(void *t);
extern void func_0207c5d4(int tag, void (*cb)(int, u32, int));
extern void func_02073fbc(int e);
extern void func_02075328(void *);
extern void func_02075384(int, u32, int);
static inline int child(void) { return *(const u16 *)0x027ffc40 == 2; }
static inline void clearFast(void *d, u32 n) { MIi_CpuClearFast(0, d, n); }
static inline void qinit(Queue *q) { q->tail = 0; q->head = q->tail; }
void func_02074008(void)
{
    Common *p = &data_020c4800;
    p->owner = -3;
    p->ref = 0;
    p->target = 0;
    p->cmd = data_020c47a0;
    clearFast(data_020c47a0, 0x60);
    DC_FlushRange(data_020c47a0, 0x60);
    if (!child()) {
        MI_CpuCopy8((const void *)0x027ffe00, (void *)0x027ffa80, 0x160);
    }
    qinit(&p->lockQ);
    qinit(&p->busyQ);
    p->prio = 4;
    func_0207aa98(p->thread, func_02075328, 0, data_020c4e20, 0x400, p->prio);
    OS_WakeupThreadDirect(p->thread);
    func_0207c5d4(0xb, func_02075384);
    if (!child()) {
        func_02073fbc(1);
    }
}
