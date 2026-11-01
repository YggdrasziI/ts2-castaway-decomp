/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/pxi.h"
#include "sdk/snd.h"

const SNDCommand * func_0207dc18(u32 flags);
BOOL func_0207d974(u32 flags);
void NNSi_SndCaptureMain(void);
void func_0209adf4(void);
void func_0209e408(void);
void SND_WaitForCommandProc(u32 tag);
u32 func_0207d8a4(void);
void SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void NNSi_SndCaptureBeginSleep(void);
extern void *NNSi_SndCaptureEndSleep();
void func_0209a788 (void);
void func_0209a74c (void *);
void *func_0209a740();

void func_0209a788 (void)
{
    while (func_0207dc18(SND_COMMAND_NOBLOCK) != NULL) {
    }

    func_0209adf4();
    NNSi_SndCaptureMain();
#ifndef SDK_SMALL_BUILD
    func_0209e408();
#endif

    (void)func_0207d974(SND_COMMAND_NOBLOCK);
}

void func_0209a74c (void *)
{
    u32 commandTag;

    NNSi_SndCaptureBeginSleep();

    SND_StopTimer(0, 0, 0, 0);

    commandTag = func_0207d8a4();
    (void)func_0207d974(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}

void *func_0209a740() {
    return NNSi_SndCaptureEndSleep();
}
