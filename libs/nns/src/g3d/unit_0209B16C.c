/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"

extern NNSSndPlayer data_020d4c48[ 32 ];
void NNS_FndAppendListObject(NNSFndList * list, void * object);
NNSSndHeapHandle func_0209c424(void * startAddress, u32 size);
void * func_0209c2d8(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
extern void func_0209a968(void * mem, u32 size, u32 data1, u32 data2);
void func_0209ac70(NNSSndSeqPlayer * seqPlayer, BOOL flag);
extern NNSSndSeqPlayer data_020d4808[ 16 ];
void NNS_SndPlayerSetPlayableSeqCount (int playerNo, int seqCount);
void func_0209b290 (int playerNo, u32 chBitFlag);
BOOL NNS_SndPlayerCreateHeap (int playerNo, NNSSndHeapHandle heap, u32 size);
void func_0209b1e0 (NNSSndHandle * handle, BOOL flag);
void NNS_SndPlayerStopSeqByPlayerNo (int playerNo, int fadeFrame);
void func_0209b16c(int *p);

void NNS_SndPlayerSetPlayableSeqCount (int playerNo, int seqCount)
{

    data_020d4c48[ playerNo ].playableSeqCount = (u16)seqCount;
}

void func_0209b290 (int playerNo, u32 chBitFlag)
{

    data_020d4c48[ playerNo ].allocChBitFlag = chBitFlag;
}

BOOL NNS_SndPlayerCreateHeap (int playerNo, NNSSndHeapHandle heap, u32 size)
{
    NNSSndHeapHandle playerHeapHandle;
    NNSSndPlayerHeap * playerHeap;
    void * buffer;

    buffer = func_0209c2d8(heap, sizeof(NNSSndPlayerHeap) + size, func_0209a968, 0, 0);
    if (buffer == NULL) {
        return FALSE;
    }

    playerHeap = (NNSSndPlayerHeap *)buffer;

    playerHeap->player = NULL;
    playerHeap->playerNo = playerNo;
    playerHeap->handle = NNS_SND_HEAP_INVALID_HANDLE;

    playerHeapHandle = func_0209c424(
        (u8 *)buffer + sizeof(NNSSndPlayerHeap),
        size
        );
    if (playerHeapHandle == NNS_SND_HEAP_INVALID_HANDLE) {
        return FALSE;
    }

    playerHeap->handle = playerHeapHandle;
    NNS_FndAppendListObject(&data_020d4c48[ playerNo ].heapList, playerHeap);

    return TRUE;
}

void func_0209b1e0 (NNSSndHandle * handle, BOOL flag)
{
    func_0209ac70(handle->player, flag);
}

void NNS_SndPlayerStopSeqByPlayerNo (int playerNo, int fadeFrame)
{
    NNSSndSeqPlayer * seqPlayer;
    int i;

    for (i = 0; i < SND_PLAYER_NUM; i++) {
        seqPlayer = &data_020d4808[ i ];

        if (seqPlayer->status != NNS_SND_SEQ_PLAYER_STATUS_STOP &&
            seqPlayer->player == &data_020d4c48[ playerNo ]) {
            func_0209ac70(seqPlayer, fadeFrame);
        }
    }
}

void func_0209b16c(int *p)
{
    *p = 0;
}
