/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/snd.h"
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))
extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern BOOL func_0207d850(u32 tag);
extern const SNDCommand *func_0207dc18(u32 flags);
extern void func_0207d6e0(void);
void SND_WaitForCommandProc(u32 tag);

void SND_WaitForCommandProc(u32 tag)
{
    if (func_0207d850(tag)) {
        return;
    }

    while (func_0207dc18(SND_COMMAND_NOBLOCK) != NULL) {
    }

    if (func_0207d850(tag)) {
        return;
    }

    func_0207d6e0();

    while (!func_0207d850(tag)) {
        (void)func_0207dc18(SND_COMMAND_BLOCK);
    }
}
