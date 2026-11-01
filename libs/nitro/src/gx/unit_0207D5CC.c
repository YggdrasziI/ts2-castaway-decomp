/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/snd.h"
#define data_0204472c data_020c5b90
#define data_02044730 data_020c5b94
#define data_020446d6 data_020c5b94
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))
#define initialized data_0204472c
#define sSndMutex data_02044730
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_0207b0f4(void);
extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern void OS_InitMutex(OSMutex *mutex);
extern void func_0207dd4c(void);
extern void func_0207dee4(void);
extern BOOL data_020c5b90;
extern OSMutex data_020c5b94;
extern void OS_LockMutex(void *p);
extern void OS_UnlockMutex(void *p);
int IsCommandAvailable(void);
void SND_Init(void);
void func_0207d5e0(void);
void func_0207d5cc(void);

int IsCommandAvailable(void) {
    volatile unsigned int *reg = (volatile unsigned int *)0x04fff200;
    int enabled;
    unsigned int busy;
    if (func_0207b0f4() == 0) {
        return 1;
    }
    enabled = OS_DisableInterrupts();
    *reg = 0x10;
    busy = *reg;
    OS_RestoreInterrupts(enabled);
    return busy != 0;
}

void SND_Init(void)
{
    {
        if (initialized)
            return;
        initialized = TRUE;
    }

    OS_InitMutex(&sSndMutex);
    func_0207dd4c();
    func_0207dee4();
}

void func_0207d5e0(void) {
    OS_LockMutex(&data_020c5b94);
}

void func_0207d5cc(void) {
    OS_UnlockMutex(&data_020c5b94);
}
