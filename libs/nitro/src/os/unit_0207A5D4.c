/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
extern void OS_EnableInterrupts(void);
extern void OS_Halt(void);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern u32 OSi_ThreadIdCount;
extern void * OSi_StackForDestructor;
extern u32 OSi_SystemStackBuffer;
extern vu32 killThreadStatus;
extern vu32 exitThreadStatus;
extern BOOL OSi_IsThreadInitialized;
extern OSThread ** OSi_CurrentThreadPtr;
extern u32 data_020c579c;
extern void * data_0204430c;
extern OSThreadInfo data_02044330;
void func_0207a64c(void);
u32 OS_DisableScheduler (void);
u32 OS_EnableScheduler (void);
void func_0207a5d4(int *p, int v);

void func_0207a64c(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}

u32 OS_DisableScheduler (void)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    u32 count;

    if (data_020c579c < (u32)(0 - 1)) {
        count = data_020c579c++;
    }
    (void)OS_RestoreInterrupts(enabled);

    return count;
}

u32 OS_EnableScheduler (void)
{
    OSIntrMode enabled = OS_DisableInterrupts();
    u32 count = 0;

    if (data_020c579c > 0) {
        count = data_020c579c--;
    }
    (void)OS_RestoreInterrupts(enabled);

    return count;
}

void func_0207a5d4(int *p, int v){ p[45] = v; }
