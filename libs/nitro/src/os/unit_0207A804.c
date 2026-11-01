/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/os_types.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void func_0207acfc(void);
void OS_RescheduleThread(void);

void OS_RescheduleThread(void)
{
    OSIntrMode nLast = OS_DisableInterrupts();

    func_0207acfc();
    OS_RestoreInterrupts(nLast);
}
