/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define ThreadInfo ThreadInfo
#define offsetof(type, member) ((u32)&(((type *)0)->member))
extern u32 OSi_ThreadIdCount;
extern void * OSi_StackForDestructor;
extern u32 OSi_SystemStackBuffer;
extern vu32 killThreadStatus;
extern vu32 exitThreadStatus;
extern BOOL OSi_IsThreadInitialized;
extern OSThread ** OSi_CurrentThreadPtr;
extern u32 OSi_RescheduleCount;
extern void * data_0204430c;
extern OSThreadInfo ThreadInfo;
void OSi_RemoveThreadFromList (OSThread * thread);

void OSi_RemoveThreadFromList (OSThread * thread)
{
    OSThread * t = ThreadInfo.list;
    OSThread * pre = NULL;

    while (t && t != thread) {
        pre = t;
        t = t->next;
    }

    if (!pre) {
        ThreadInfo.list = thread->next;
    } else {
        pre->next = thread->next;
    }
}
