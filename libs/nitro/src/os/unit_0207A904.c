/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
#define SDK_THREAD_INFINITY 1
extern OSThreadInfo ThreadInfo;
static inline OSThreadInfo * OS_GetThreadInfo (void)
{
    return &ThreadInfo;
}
static inline OSThread * OS_GetCurrentThread (void)
{
    return OS_GetThreadInfo()->current;
}
extern OSIntrMode OS_DisableInterrupts(void);
extern u32 OSi_ThreadIdCount;
extern void * OSi_StackForDestructor;
extern u32 OSi_SystemStackBuffer;
extern vu32 killThreadStatus;
extern vu32 exitThreadStatus;
extern BOOL OSi_IsThreadInitialized;
#define OSi_CurrentThreadPtr data_020c57a8
extern OSThread ** OSi_CurrentThreadPtr;
extern u32 OSi_RescheduleCount;
extern void * data_0204430c;
extern OSThreadInfo ThreadInfo;
void OS_InitContext(OSContext * context, u32 newpc, u32 newsp);
void OS_LoadContext(OSContext * context);
extern void * data_020c5798;
extern OSThreadInfo ThreadInfo;
extern OSThread ** data_020c57a8;
void OS_Terminate();
void OS_RescheduleThread(void);
void func_0207a884(OSThreadQueue * queue);
u32 OS_DisableScheduler(void);
u32 OS_EnableScheduler(void);
void OSi_UnlockAllMutex(OSThread * thread);
extern void OSi_RemoveThreadFromList(OSThread * thread);
extern OSThread * OSi_RemoveSpecifiedLinkFromQueue (OSThreadQueue * queue, OSThread * thread);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0207acfc(void);
extern void OSi_InsertLinkToQueue (OSThreadQueue * queue, OSThread * thread);
void func_0207aa6c (void);
void func_0207a9fc (OSThread * thread, void * arg);
void func_0207a9b8 (void * arg);
void func_0207a958 (void);
void func_0207a904 (OSThreadQueue * queue);

void func_0207aa6c (void)
{
    (void)OS_DisableInterrupts();

#ifdef SDK_THREAD_INFINITY
    func_0207a9fc(OS_GetCurrentThread(), 0);
#else
    func_0207a958();
#endif
}

void func_0207a9fc (OSThread * thread, void * arg)
{
    if (data_020c5798) {
        OS_InitContext(&thread->context, (u32)func_0207a9b8, (u32)data_020c5798);
        thread->context.r[0] = (u32)arg;
        thread->context.cpsr |= HW_PSR_IRQ_DISABLE;
        thread->state = OS_THREAD_STATE_READY;
        OS_LoadContext(&thread->context);

    } else {
        func_0207a9b8(arg);

    }
}

void func_0207a9b8 (void * arg)
{
    OSThread * currentThread = OSi_GetCurrentThread();
    OSThreadDestructor destructor;

    destructor = currentThread->destructor;
    if (destructor) {
        currentThread->destructor = NULL;
        destructor(arg);
        (void)OS_DisableInterrupts();
    }

    func_0207a958();
}

void func_0207a958 (void)
{
    OSThread * currentThread = OSi_GetCurrentThread();

#ifdef SDK_THREAD_INFINITY
    (void)OS_DisableScheduler();
#endif

#ifndef SDK_THREAD_INFINITY

#endif

    OSi_UnlockAllMutex(currentThread);

    if (currentThread->queue) {
        (void)OSi_RemoveSpecifiedLinkFromQueue(currentThread->queue, currentThread);
    }

    OSi_RemoveThreadFromList(currentThread);

#ifndef SDK_THREAD_INFINITY
    ThreadInfo.entry[currentThread->id] = NULL;
#endif
    currentThread->state = OS_THREAD_STATE_TERMINATED;

#ifndef SDK_THREAD_INFINITY
    func_0207a884(&currentThread->joinQueue);
#else
    func_0207a884(&currentThread->joinQueue);
#endif

#ifdef SDK_THREAD_INFINITY
    (void)OS_EnableScheduler();
#endif

    OS_RescheduleThread();
    OS_Terminate();
}

void func_0207a904 (OSThreadQueue * queue)
{
    OSIntrMode enable;
    OSThread * currentThread;

    enable = OS_DisableInterrupts();
#ifndef SDK_THREAD_INFINITY
    {
        currentThread = OSi_GetCurrentThread();

        if (queue) {
            *queue |= (OSThreadQueue)(1UL << currentThread->id);
        }

        currentThread->state = OS_THREAD_STATE_WAITING;
        func_0207acfc();
    }
#else
    {
        currentThread = OSi_GetCurrentThread();

        if (queue) {
            currentThread->queue = queue;
            OSi_InsertLinkToQueue(queue, currentThread);
        }

        currentThread->state = OS_THREAD_STATE_WAITING;
        func_0207acfc();
    }
#endif
    (void)OS_RestoreInterrupts(enable);

}
