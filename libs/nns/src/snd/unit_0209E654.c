/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"
#define BLOCK_SIZE 512
#define BLOCK_NUM 4
typedef struct StrmCommand {
    NNSFndLink link;
    u32 param[10];
} StrmCommand;
#define COMMAND_NUM 8
#pragma opt_rotateloops off
#pragma opt_strength_reduction off
#pragma opt_strength_reduction reset
#pragma opt_rotateloops reset
void * NNS_SndHeapAlloc(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
const NNSSndArcStrmPlayerInfo * NNS_SndArcGetStrmPlayerInfo(int playerNo);
extern NNSSndStrmPlayer data_020d5aec[NNS_SND_STRM_PLAYER_NUM];
extern NNSFndList data_020d525c;
extern OSMutex data_020d5268;
extern StrmCommand data_020d5280[COMMAND_NUM];
extern u8 data_020d5400[BLOCK_SIZE];
extern NNSSndStrmThread data_020d5600;
void NNS_FndInitList(NNSFndList * list, u16 offset);
void NNS_FndAppendListObject(NNSFndList * list, void * object);
void OS_InitMutex(OSMutex * mutex);
void FS_InitFile(FSFile * p_file);
void NNS_SndStrmInit(NNSSndStrm * stream);
BOOL func_0209e578(NNSSndHeapHandle heap);
void CreateThread(NNSSndStrmThread * thread, u32 threadPrio);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_020d5250;
extern u8 * data_020d5258;
void func_0209e654 (u32 threadPrio, NNSSndHeapHandle heap);

void func_0209e654 (u32 threadPrio, NNSSndHeapHandle heap)
{
    int i;
    int playerNo;
    NNSSndStrmPlayer * player;

    if (data_020d5250) {
        (void)func_0209e578(heap);
        return;
    }
    data_020d5250 = TRUE;

    NNS_FndInitList(&data_020d525c, 0);
    for (i = 0; i < COMMAND_NUM; i++) {
        NNS_FndAppendListObject(&data_020d525c, &data_020d5280[i]);
    }
    OS_InitMutex(&data_020d5268);

    data_020d5258 = data_020d5400;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; playerNo++) {
        player = &data_020d5aec[playerNo];

        player->activeFlag = FALSE;
        FS_InitFile(&player->file);
        NNS_SndStrmInit(&player->stream);
        player->playerNo = playerNo;
        player->numChannels = 0;
        player->buffer = NULL;
        player->bufSize = 0;
        player->allocChannelCount = 0;
    }

    (void)func_0209e578(heap);

    CreateThread(&data_020d5600, threadPrio);
}
