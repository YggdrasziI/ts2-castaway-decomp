/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"
#define BLOCK_SIZE 512
#define BLOCK_NUM 4
void * func_0209c2d8(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
const NNSSndArcStrmPlayerInfo * func_0209bb3c(int playerNo);
extern NNSSndStrmPlayer data_020d5aec[4 ];
extern void func_0209e328(NNSSndStrmPlayer * player);
extern void func_0209e05c(void * mem, u32 size, u32 data1, u32 data2);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
BOOL func_0209e578 (NNSSndHeapHandle heap);

BOOL func_0209e578 (NNSSndHeapHandle heap)
{
    int playerNo;
    const NNSSndArcStrmPlayerInfo * playerInfo;
    NNSSndStrmPlayer * player;
    void * buffer;
    u32 bufSize;
    int i;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; ++playerNo) {
        player = &data_020d5aec[ playerNo ];

        playerInfo = func_0209bb3c(playerNo);
        if (playerInfo == NULL) continue;

        player->numChannels = playerInfo->numChannels;
        for (i = 0; i < playerInfo->numChannels; i++) {
            player->chNoList[ i ] = playerInfo->chNoList[ i ];
        }

        if (heap != NNS_SND_HEAP_INVALID_HANDLE) {
            bufSize = (unsigned long)(BLOCK_SIZE * BLOCK_NUM * player->numChannels);
            buffer = func_0209c2d8(heap, bufSize, func_0209e05c, (u32)player, 0);
            if (buffer == NULL) return FALSE;

            func_0209e328(player);

            player->buffer = buffer;
            player->bufSize = bufSize;
        }
    }

    return TRUE;
}
