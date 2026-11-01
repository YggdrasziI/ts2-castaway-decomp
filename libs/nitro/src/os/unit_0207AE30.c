/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define ThreadInfo ThreadInfo

extern OSThreadInfo ThreadInfo;
void func_0207ae30(OSThread *thread);

void func_0207ae30(OSThread *thread)
{
    OSThread *current = ThreadInfo.list;
    OSThread *previous = 0;

    while (current != 0 && current->priority < thread->priority) {
        previous = current;
        current = current->next;
    }

    if (previous == 0) {
        thread->next = ThreadInfo.list;
        ThreadInfo.list = thread;
    } else {
        thread->next = previous->next;
        previous->next = thread;
    }
}
