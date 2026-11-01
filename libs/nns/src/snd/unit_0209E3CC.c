/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
void FreePlayer (NNSSndStrmPlayer * player);

void FreePlayer (NNSSndStrmPlayer * player)
{

    if (player->handle != NULL) {
        player->handle->player = NULL;
        player->handle = NULL;
    }

    player->activeFlag = FALSE;
    player->startFlag = FALSE;
    player->playFlag = FALSE;
}
