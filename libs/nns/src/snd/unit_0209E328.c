/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

void OS_LockMutex(OSMutex * mutex);
void OS_UnlockMutex(OSMutex * mutex);
void NNS_SndStrmStop(NNSSndStrm * stream);
extern NNSSndStrmThread data_020d5600;
extern void func_0209e2bc(NNSSndStrmPlayer * player);
extern NNSSndStrmThread * data_020d5254;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
void func_0209e328 (NNSSndStrmPlayer * player);

void func_0209e328 (NNSSndStrmPlayer * player)
{

    OS_LockMutex(&data_020d5600.mutex);
    if (data_020d5254) OS_LockMutex(&data_020d5254->mutex);

    if (player->playFlag) {
        NNS_SndStrmStop(&player->stream);
    }

    if (player->activeFlag) {
        player->cancelStreamFunc(player);
    }

    func_0209e2bc(player);

    OS_UnlockMutex(&data_020d5600.mutex);
    if (data_020d5254) OS_UnlockMutex(&data_020d5254->mutex);
}
