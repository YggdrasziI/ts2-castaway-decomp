/* NitroSDK os_thread.c: OS_InitThread (khdays' source, CC0), retyped for this ROM. The
 * launcher stack bounds come from the link-time constants SDK_SYS_STACKSIZE,
 * SDK_IRQ_STACKSIZE and SDK_SECTION_ARENA_DTCM_START (absolute symbols defined by
 * tools/lcf_keep.py), tested at run time. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef unsigned short u16;
typedef int s32;

typedef struct OSThread OSThread;
typedef struct {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;
struct OSThread {
    unsigned char context[0x64];
    int state;           /* 0x64 */
    OSThread *next;      /* 0x68 */
    u32 id;              /* 0x6c */
    u32 priority;        /* 0x70 */
    void *profiler;      /* 0x74 */
    unsigned char pad78[0x18];
    u32 stackTop;        /* 0x90 */
    u32 stackBottom;     /* 0x94 */
    u32 stackWarningOffset; /* 0x98 */
    OSThreadQueue joinQueue; /* 0x9c */
    unsigned char padA4[0x1c];
};
typedef struct {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

extern void SDK_SYS_STACKSIZE(void);
extern void SDK_IRQ_STACKSIZE(void);
extern void SDK_SECTION_ARENA_DTCM_START(void);
#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE)

extern u32 data_027e0000;
#define HW_DTCM ((u32)&data_027e0000)
#define HW_DTCM_SVC_STACK_ADDR (HW_DTCM + 0x3f80)
#define OSi_LAUNCHER_STACK_LO_DEFAULT ((u32)SDK_SECTION_ARENA_DTCM_START)
#define OSi_LAUNCHER_STACK_HI_MAX (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)
#define OSi_LAUNCHER_STACK_BOTTOM (HW_DTCM_SVC_STACK_ADDR - OSi_IRQ_STACKSIZE)

extern OSThread **data_020c57a8;   /* current thread pointer */
extern int data_020c57ac;          /* thread system initialized */
extern OSThreadInfo ThreadInfo;
extern OSThread *data_020c57b4;    /* ThreadInfo.current, referenced by its own symbol */
extern OSThread data_020c57c0;     /* idle thread */
extern OSThread data_020c5880;     /* launcher thread */
extern u32 data_020c5a08[];        /* end of the idle thread stack */

extern void *func_0207a660(void *callback);
extern void func_0207aa98(OSThread *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 prio);
extern void func_0207a64c(void *arg);

void func_0207aba0(void) {
    void *stackLo;

    if (data_020c57ac) {
        return;
    }

    data_020c57ac = 1;

    data_020c57a8 = &data_020c57b4;
    data_020c5880.priority = 16;
    data_020c5880.id = 0;
    data_020c5880.state = 1;
    data_020c5880.next = 0;
    data_020c5880.profiler = 0;

    ThreadInfo.list = &data_020c5880;

    ThreadInfo.current = &data_020c5880;

    stackLo = (OSi_SYS_STACKSIZE <= 0) ? (void *)((u32)OSi_LAUNCHER_STACK_LO_DEFAULT - OSi_SYS_STACKSIZE)
                                       : (void *)((u32)OSi_LAUNCHER_STACK_HI_MAX - OSi_SYS_STACKSIZE);

    data_020c5880.stackBottom = (u32)OSi_LAUNCHER_STACK_BOTTOM;
    data_020c5880.stackTop = (u32)stackLo;
    data_020c5880.stackWarningOffset = 0;

    *(u32 *)(data_020c5880.stackBottom - sizeof(u32)) = 0xfddb597dUL;
    *(u32 *)data_020c5880.stackTop = 0x7bf9dd5bUL;

    data_020c5880.joinQueue.head = data_020c5880.joinQueue.tail = 0;

    ThreadInfo.isNeedRescheduling = 0;
    ThreadInfo.irqDepth = 0;

    *(OSThreadInfo **)0x027fffa0 = &ThreadInfo;

    func_0207a660(0);

    func_0207aa98(&data_020c57c0, func_0207a64c, 0, data_020c5a08, 0xc8, 31);

    data_020c57c0.priority = 32;
    data_020c57c0.state = 1;
}
