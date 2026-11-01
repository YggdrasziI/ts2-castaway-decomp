/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#include "sdk/os.h"
#define data_0204a760 data_020d4c48
#define data_0204a314 data_020d47fc
#define data_0204a308 data_020d47f0
inline BOOL NNS_SndHandleIsValid (const struct NNSSndHandle * handle)
{
    return handle->player != NULL ;
}
#define FADER_SHIFT 8
void * NNS_FndGetNextListObject(NNSFndList * list, void * object);
void func_0209b154(NNSSndHandle * handle);
extern NNSSndPlayer data_020d4c48[ 32 ];
u32 func_0207d8a4(void);
void SND_PrepareSeq(int playerNo, const void *base, u32 offset, const struct SNDBankData *bank);
void SND_SetTrackAllocatableChannel(int playerNo, u32 trackBitMask, u32 chBitMask);
void NNSi_SndFaderSet(NNSSndFader * fader, int target, int frame);
void NNS_FndRemoveListObject(NNSFndList * list, void * object);
void func_0209c348(NNSSndHeapHandle heap);
void NNSi_SndFaderInit(NNSSndFader * fader);
void NNS_FndInsertListObject(NNSFndList * list, void * target, void * object);
extern NNSFndList data_020d47fc;
void SND_StopSeq(int playerNo);
void SND_SetPlayerVolume(int playerNo, int volume);
extern NNSFndList data_020d47f0;
void NNS_FndAppendListObject(NNSFndList * list, void * object);
void func_0209c408(NNSSndHeapHandle heap);
void SND_UnlockChannel(u32 chBitMask, u32 flags);
extern u32 sAlarmLock;
extern u32 data_0204a2fc;
extern u32 data_020d47ec;
extern u32 data_020d47e4;
extern u32 sChannelLock;
NNSSndSeqPlayer * func_0209ad38 (NNSSndHandle * handle, int playerNo, int prio);
void func_0209ad2c(NNSSndSeqPlayer *player);
void func_0209acd0 (NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const SNDBankData * bank);
void func_0209ac70 (NNSSndSeqPlayer * seqPlayer, int fadeFrame);
NNSSndHeapHandle func_0209ac14 (int playerNo, NNSSndSeqPlayer * seqPlayer);
void func_0209abc8 (NNSSndSeqPlayer * seqPlayer);
void func_0209ab6c (NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer);
void func_0209ab0c (NNSSndSeqPlayer * seqPlayer);
void func_0209aad0 (NNSSndSeqPlayer * seqPlayer);
NNSSndSeqPlayer * func_0209aa54 (int prio);
void func_0209a9c4 (NNSSndSeqPlayer * seqPlayer);
void func_0209a968 (void * mem, u32, u32, u32);
void func_0209a904 (NNSSndSeqPlayer * seqPlayer, int priority);
void func_0209a8cc (u32 chBitFlag);
void func_0209a8b0 (u32 capBitFlag);

NNSSndSeqPlayer * func_0209ad38 (NNSSndHandle * handle, int playerNo, int prio)
{
    NNSSndSeqPlayer * seqPlayer;
    NNSSndPlayer * player;

    player = &data_020d4c48[ playerNo ];

    if (NNS_SndHandleIsValid(handle)) {
        func_0209b154(handle);
    }

    if (player->playerList.numObjects >= player->playableSeqCount) {

        seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&player->playerList, NULL);
        if (seqPlayer == NULL) return NULL;
        if (prio < seqPlayer->prio) return NULL;

        func_0209aad0(seqPlayer);
    }

    seqPlayer = func_0209aa54(prio);
    if (seqPlayer == NULL) return NULL;

    func_0209ab6c(player, seqPlayer);

    seqPlayer->handle = handle;
    handle->player = seqPlayer;

    return seqPlayer;
}

void func_0209ad2c(NNSSndSeqPlayer *player) {
    func_0209a9c4(player);
}

void func_0209acd0 (NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const SNDBankData * bank)
{
    NNSSndPlayer * player;

    player = seqPlayer->player;

    SND_PrepareSeq(
        seqPlayer->playerNo,
        seqDataBase,
        seqDataOffset,
        bank
        );
    if (player->allocChBitFlag) {
        SND_SetTrackAllocatableChannel(
            seqPlayer->playerNo,
            0xffff,
            player->allocChBitFlag
            );
    }

    func_0209abc8(seqPlayer);
    seqPlayer->commandTag = func_0207d8a4();
    seqPlayer->prepareFlag = TRUE;
    seqPlayer->status = NNS_SND_SEQ_PLAYER_STATUS_PLAY;
}

void func_0209ac70 (NNSSndSeqPlayer * seqPlayer, int fadeFrame)
{
    if (seqPlayer == NULL) return;
    if (seqPlayer->status == NNS_SND_SEQ_PLAYER_STATUS_STOP) return;

    if (fadeFrame == 0) {
        func_0209aad0(seqPlayer);
        return;
    }

    NNSi_SndFaderSet(&seqPlayer->fader, 0, fadeFrame);
    func_0209a904(seqPlayer, 0);

    seqPlayer->status = NNS_SND_SEQ_PLAYER_STATUS_FADEOUT;
}

NNSSndHeapHandle func_0209ac14 (int playerNo, NNSSndSeqPlayer * seqPlayer)
{
    NNSSndPlayer * player;
    NNSSndPlayerHeap * heap;

    player = &data_020d4c48[ playerNo ];

    heap = (NNSSndPlayerHeap *)NNS_FndGetNextListObject(&player->heapList, NULL);
    if (heap == NULL) return NULL;

    NNS_FndRemoveListObject(&player->heapList, heap);

    heap->player = seqPlayer;
    seqPlayer->heap = heap;

    func_0209c348(heap->handle);

    return heap->handle;
}

void func_0209abc8 (NNSSndSeqPlayer * seqPlayer)
{

    seqPlayer->pauseFlag = FALSE;
    seqPlayer->startFlag = FALSE;
    seqPlayer->prepareFlag = FALSE;

    seqPlayer->seqType = NNS_SND_PLAYER_SEQ_TYPE_INVALID;

    seqPlayer->volume = 0;

    seqPlayer->initVolume = 127;
    seqPlayer->extVolume = 127;

    NNSi_SndFaderInit(&seqPlayer->fader);
    NNSi_SndFaderSet(&seqPlayer->fader, 127 << FADER_SHIFT, 1);
}

void func_0209ab6c (NNSSndPlayer * player, NNSSndSeqPlayer * seqPlayer)
{
    NNSSndSeqPlayer * next = NULL;
    while ((next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&player->playerList, next)) != NULL) {
        if (seqPlayer->prio < next->prio) break;
    }

    NNS_FndInsertListObject(&player->playerList, next, seqPlayer);

    seqPlayer->player = player;
}

void func_0209ab0c (NNSSndSeqPlayer * seqPlayer)
{
    NNSSndSeqPlayer * next = NULL;
    while ((next = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020d47fc, next)) != NULL) {
        if (seqPlayer->prio < next->prio) break;
    }

    NNS_FndInsertListObject(&data_020d47fc, next, seqPlayer);
}

void func_0209aad0 (NNSSndSeqPlayer * seqPlayer)
{
    if (seqPlayer->status == NNS_SND_SEQ_PLAYER_STATUS_FADEOUT) {
        SND_SetPlayerVolume(seqPlayer->playerNo, SND_VOLUME_DB_MIN);
    }
    SND_StopSeq(seqPlayer->playerNo);
    func_0209a9c4(seqPlayer);
}

NNSSndSeqPlayer * func_0209aa54 (int prio)
{
    NNSSndSeqPlayer * seqPlayer;

    seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020d47f0, NULL);
    if (seqPlayer == NULL) {
        seqPlayer = (NNSSndSeqPlayer *)NNS_FndGetNextListObject(&data_020d47fc, NULL);

        if (prio < seqPlayer->prio) return NULL;

        func_0209aad0(seqPlayer);
    }
    NNS_FndRemoveListObject(&data_020d47f0, seqPlayer);

    seqPlayer->prio = (u8)prio;

    func_0209ab0c(seqPlayer);

    return seqPlayer;
}

void func_0209a9c4 (NNSSndSeqPlayer * seqPlayer)
{
    NNSSndPlayer * player;

    if (seqPlayer->handle != NULL) {
        seqPlayer->handle->player = NULL;
        seqPlayer->handle = NULL;
    }

    player = seqPlayer->player;
    NNS_FndRemoveListObject(&player->playerList, seqPlayer);
    seqPlayer->player = NULL;

    if (seqPlayer->heap != NULL) {
        NNS_FndAppendListObject(&player->heapList, seqPlayer->heap);
        seqPlayer->heap->player = NULL;
        seqPlayer->heap = NULL;
    }

    NNS_FndRemoveListObject(&data_020d47fc, seqPlayer);
    NNS_FndAppendListObject(&data_020d47f0, seqPlayer);

    seqPlayer->status = NNS_SND_SEQ_PLAYER_STATUS_STOP;
}

void func_0209a968 (void * mem, u32, u32, u32)
{
    NNSSndPlayerHeap * heap = (NNSSndPlayerHeap *)mem;
    NNSSndSeqPlayer * seqPlayer;

    if (heap->handle == NNS_SND_HEAP_INVALID_HANDLE) return;

    func_0209c408(heap->handle);

    seqPlayer = heap->player;
    if (seqPlayer != NULL) {
        seqPlayer->heap = NULL;
    } else {
        NNS_FndRemoveListObject(&data_020d4c48[ heap->playerNo ].heapList, heap);
    }
}

void func_0209a904 (NNSSndSeqPlayer * seqPlayer, int priority)
{
    NNSSndPlayer * player;

    player = seqPlayer->player;

    if (player != NULL) {
        NNS_FndRemoveListObject(&player->playerList, seqPlayer);
        seqPlayer->player = NULL;
    }

    NNS_FndRemoveListObject(&data_020d47fc, seqPlayer);

    seqPlayer->prio = (u8)priority;

    if (player != NULL) {
        func_0209ab6c(player, seqPlayer);
    }

    func_0209ab0c(seqPlayer);
}

void func_0209a8cc (u32 chBitFlag)
{

    if (chBitFlag == 0) return;

    SND_UnlockChannel(chBitFlag, 0);

    data_020d47ec &= ~chBitFlag;
}

void func_0209a8b0 (u32 capBitFlag)
{
    data_020d47e4 &= ~capBitFlag;
}
