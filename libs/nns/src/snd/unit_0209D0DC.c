/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"
typedef struct LoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer * player;
    NNSSndStrmCallbackStatus status;
    int numChannels;
    void * buffer[6 ];
    u32 bufLen;
} LoadCommand;
void func_0207a904(OSThreadQueue * queue);
void OS_LockMutex(OSMutex * mutex);
void OS_UnlockMutex(OSMutex * mutex);
extern LoadCommand * ReadCommandBuffer(NNSFndList * commandList);
extern void FreeCommandBuffer(LoadCommand * command);
extern void func_0209d668(LoadCommand * command);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
NNSSndArc * func_0209bdf8(void);
const NNSSndArcPlayerInfo * func_0209bba0(int playerNo);
void NNS_SndPlayerSetPlayableSeqCount(int playerNo, int seqCount);
void func_0209b290(int playerNo, u32 chBitFlag);
BOOL NNS_SndPlayerCreateHeap(int playerNo, NNSSndHeapHandle heap, u32 size);
const NNSSndArcSeqInfo * func_0209bd94(int seqNo);
const NNSSndSeqArcSeqInfo * NNSi_SndSeqArcGetSeqInfo(const struct NNSSndSeqArc * seqArc, int seqNo);
const NNSSndArcSeqArcInfo * func_0209bd30(int seqNo);
void * NNS_SndArcGetFileAddress(u32 fileId);
void func_0209b134(NNSSndHandle * handle, int volume);
void func_0209b104(NNSSndHandle * handle, int priority);
void func_0209b048(NNSSndHandle * handle, int seqNo);
void func_0209acd0(NNSSndSeqPlayer * seqPlayer, const void * seqDataBase, u32 seqDataOffset, const struct SNDBankData * bank);
NNSSndSeqPlayer * func_0209ad38(NNSSndHandle * handle, int playerNo, int prio);
void func_0209ad2c(NNSSndSeqPlayer * seqPlayer);
NNSSndHeapHandle func_0209ac14(int playerNo, NNSSndSeqPlayer * seqPlayer);
NNSSndArcLoadResult func_0209ce64(int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);
NNSSndArcLoadResult func_0209cc94(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);
void func_0209b020(NNSSndHandle * handle, int seqArcNo, int index);
void StrmThread (void * arg);
BOOL NNS_SndArcPlayerSetup (NNSSndHeapHandle heap);
BOOL NNS_SndArcPlayerStartSeq (NNSSndHandle * handle, int seqNo);
BOOL NNS_SndArcPlayerStartSeqArc (NNSSndHandle * handle, int seqArcNo, int index);
BOOL StartSeq (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndArcSeqInfo * info, int seqNo);
BOOL StartSeqArc (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndSeqArcSeqInfo * sound, const NNSSndSeqArc * seqArc, int seqArcNo, int index);

void StrmThread (void * arg)
{
    NNSSndStrmThread * thread = (NNSSndStrmThread *)arg;

    while (1) {
        LoadCommand * command;

        func_0207a904(&thread->threadQ);

        while (1) {
            OS_LockMutex(&thread->mutex);

            command = ReadCommandBuffer(&thread->commandList);
            if (command == NULL) {
                OS_UnlockMutex(&thread->mutex);
                break;
            }

            func_0209d668(command);
            FreeCommandBuffer(command);
            OS_UnlockMutex(&thread->mutex);
        }
    }
}

BOOL NNS_SndArcPlayerSetup (NNSSndHeapHandle heap)
{
    NNSSndArc * arc = func_0209bdf8();
    int playerNo;
    const NNSSndArcPlayerInfo * playerInfo;

    for (playerNo = 0; playerNo < NNS_SND_PLAYER_NUM; ++playerNo) {
        playerInfo = func_0209bba0(playerNo);
        if (playerInfo == NULL) continue;

        NNS_SndPlayerSetPlayableSeqCount(playerNo, playerInfo->seqMax);
        func_0209b290(playerNo, playerInfo->allocChBitFlag);

        if (playerInfo->heapSize > 0 && heap != NNS_SND_HEAP_INVALID_HANDLE) {
            int i;

            for (i = 0; i < playerInfo->seqMax; i++) {
                if (!NNS_SndPlayerCreateHeap(playerNo, heap, playerInfo->heapSize)) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

BOOL NNS_SndArcPlayerStartSeq (NNSSndHandle * handle, int seqNo)
{
    const NNSSndArcSeqInfo * info;

    info = func_0209bd94(seqNo);
    if (info == NULL) return FALSE;

    return StartSeq(
        handle,
        info->param.playerNo,
        info->param.bankNo,
        info->param.playerPrio,
        info,
        seqNo
        );
}

BOOL NNS_SndArcPlayerStartSeqArc (NNSSndHandle * handle, int seqArcNo, int index)
{
    const NNSSndArcSeqArcInfo * info;
    const NNSSndSeqArcSeqInfo * sound;
    const NNSSndSeqArc * seqArc;

    info = func_0209bd30(seqArcNo);
    if (info == NULL) return FALSE;
    seqArc = (NNSSndSeqArc *)NNS_SndArcGetFileAddress(info->fileId);
    if (seqArc == NULL) return FALSE;
    sound = NNSi_SndSeqArcGetSeqInfo(seqArc, index);
    if (sound == NULL) return FALSE;

    return StartSeqArc(
        handle,
        sound->param.playerNo,
        sound->param.bankNo,
        sound->param.playerPrio,
        sound,
        seqArc,
        seqArcNo,
        index
        );
}

BOOL StartSeq (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndArcSeqInfo * info, int seqNo)
{
    NNSSndSeqPlayer * player;
    NNSSndHeapHandle heap;
    NNSSndSeqData * seq;
    SNDBankData * bank;
    NNSSndArcLoadResult result;

    player = func_0209ad38(handle, playerNo, playerPrio);
    if (player == NULL) return FALSE;

    heap = func_0209ac14(playerNo, player);

    result = func_0209cc94(bankNo, NNS_SND_ARC_LOAD_BANK | NNS_SND_ARC_LOAD_WAVE, heap, FALSE, &bank);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        func_0209ad2c(player);
        return FALSE;
    }

    result = func_0209ce64(seqNo, NNS_SND_ARC_LOAD_SEQ, heap, FALSE, &seq);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        func_0209ad2c(player);
        return FALSE;
    }

    func_0209acd0(
        player,
        (u8 *)seq + seq->baseOffset,
        0,
        bank
        );

    func_0209b134(handle, info->param.volume);
    func_0209b104(handle, info->param.channelPrio);
    func_0209b048(handle, seqNo);

    return TRUE;
}

BOOL StartSeqArc (NNSSndHandle * handle, int playerNo, int bankNo, int playerPrio, const NNSSndSeqArcSeqInfo * sound, const NNSSndSeqArc * seqArc, int seqArcNo, int index)
{
    NNSSndSeqPlayer * player;
    NNSSndHeapHandle heap;
    SNDBankData * bank;
    NNSSndArcLoadResult result;

    player = func_0209ad38(handle, playerNo, playerPrio);
    if (player == NULL) return FALSE;

    heap = func_0209ac14(playerNo, player);

    result = func_0209cc94(bankNo, NNS_SND_ARC_LOAD_BANK | NNS_SND_ARC_LOAD_WAVE, heap, FALSE, &bank);
    if (result != NNS_SND_ARC_LOAD_SUCESS) {
        func_0209ad2c(player);
        return FALSE;
    }

    func_0209acd0(
        player,
        (u8 *)seqArc + seqArc->baseOffset,
        sound->offset,
        bank
        );

    func_0209b134(handle, sound->param.volume);
    func_0209b104(handle, sound->param.channelPrio);
    func_0209b020(handle, seqArcNo, index);

    return TRUE;
}
