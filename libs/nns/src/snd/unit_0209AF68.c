/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
void NNS_FndInitList(NNSFndList * list, u16 offset);
void NNS_FndAppendListObject(NNSFndList * list, void * object);
extern NNSSndSeqPlayer data_020d4808[ 16 ];
extern NNSSndPlayer data_020d4c48[ 32 ];
extern NNSFndList data_020d47fc;
extern NNSFndList data_020d47f0;
void NNSi_SndPlayerInit (void);

void NNSi_SndPlayerInit (void)
{
    NNSSndPlayer * player;
    int playerNo;

    NNS_FND_INIT_LIST(&data_020d47fc, NNSSndSeqPlayer, prioLink);
    NNS_FND_INIT_LIST(&data_020d47f0, NNSSndSeqPlayer, prioLink);

    for (playerNo = 0; playerNo < SND_PLAYER_NUM; playerNo++) {
        data_020d4808[ playerNo ].status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
        data_020d4808[ playerNo ].playerNo = (u8)playerNo;
        NNS_FndAppendListObject(&data_020d47f0, &data_020d4808[ playerNo ]);
    }

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_NUM; playerNo++) {
        player = &data_020d4c48[ playerNo ];

        NNS_FND_INIT_LIST(&player->playerList, NNSSndSeqPlayer, playerLink);
        NNS_FND_INIT_LIST(&player->heapList, NNSSndPlayerHeap, link);
        player->volume = 127;
        player->playableSeqCount = 1;
        player->allocChBitFlag = 0;
    }
}
