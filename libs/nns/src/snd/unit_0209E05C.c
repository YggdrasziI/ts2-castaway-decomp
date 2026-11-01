/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
static inline void OS_InitThreadQueue (OSThreadQueue * queue)
{
    queue->head = queue->tail = NULL ;
}
typedef struct LoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer * player;
    NNSSndStrmCallbackStatus status;
    int numChannels;
    void * buffer[6 ];
    u32 bufLen;
} LoadCommand;
void NNS_SndStrmFreeChannel(NNSSndStrm * stream);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
void func_0207aa98(OSThread * thread, void (*func)(void *), void * arg, void * stack, u32 stackSize, u32 prio);
void OS_WakeupThreadDirect(OSThread * thread);
void OS_InitMutex(OSMutex * mutex);
void NNS_FndInitList(NNSFndList * list, u16 offset);
extern void StrmThread(void * arg);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
void NNS_FndRemoveListObject(NNSFndList * list, void * object);
void * NNS_FndGetNextListObject(NNSFndList * list, void * object);
void NNS_FndAppendListObject(NNSFndList * list, void * object);
extern NNSFndList data_020d525c;
void OS_LockMutex(OSMutex * mutex);
void OS_UnlockMutex(OSMutex * mutex);
extern NNSSndStrmThread data_020d5600;
extern void func_0209e328(NNSSndStrmPlayer * player);
extern NNSSndStrmThread * data_020d5254;
void FreeChannel (NNSSndStrmPlayer * player);
void CreateThread (NNSSndStrmThread * thread, u32 threadPrio);
void RemoveCommandByPlayer (NNSFndList * commandList, const NNSSndStrmPlayer * player);
LoadCommand * ReadCommandBuffer (NNSFndList * commandList);
void FreeCommandBuffer (LoadCommand * command);
void func_0209e05c (void * mem, u32, u32 data1, u32);

void FreeChannel (NNSSndStrmPlayer * player)
{

    if (player->allocChannelCount == 0) {
        return;
    }

    player->allocChannelCount--;

    if (player->allocChannelCount == 0) {
        NNS_SndStrmFreeChannel(&player->stream);
    }
}

void CreateThread (NNSSndStrmThread * thread, u32 threadPrio)
{
    func_0207aa98(
        &thread->thread,
        StrmThread,
        thread,
        thread->stack + NNS_SND_STRM_THREAD_STACK_SIZE / sizeof(u64),
        NNS_SND_STRM_THREAD_STACK_SIZE,
        threadPrio
        );
    NNS_FND_INIT_LIST(&thread->commandList, LoadCommand, link);
    OS_InitMutex(&thread->mutex);
    OS_InitThreadQueue(&thread->threadQ);
    OS_WakeupThreadDirect(&thread->thread);
}

void RemoveCommandByPlayer (NNSFndList * commandList, const NNSSndStrmPlayer * player)
{
    OSIntrMode old;
    LoadCommand * command;
    LoadCommand * next;

    old = OS_DisableInterrupts();

    for (command = (LoadCommand *)NNS_FndGetNextListObject(commandList, NULL);
         command != NULL; command = next) {
        next = (LoadCommand *)NNS_FndGetNextListObject(commandList, command);

        if (command->player == player) {
            NNS_FndRemoveListObject(commandList, command);
            FreeCommandBuffer(command);
        }
    }

    (void)OS_RestoreInterrupts(old);
}

LoadCommand * ReadCommandBuffer (NNSFndList * commandList)
{
    OSIntrMode old;
    LoadCommand * command;

    old = OS_DisableInterrupts();

    command = (LoadCommand *)NNS_FndGetNextListObject(commandList, NULL);
    if (command != NULL) {
        NNS_FndRemoveListObject(commandList, command);

        command->player->commandCount--;
    }

    (void)OS_RestoreInterrupts(old);

    return command;
}

void FreeCommandBuffer (LoadCommand * command)
{
    OSIntrMode old;

    old = OS_DisableInterrupts();

    NNS_FndAppendListObject(&data_020d525c, command);

    (void)OS_RestoreInterrupts(old);
}

void func_0209e05c (void * mem, u32, u32 data1, u32)
{
    NNSSndStrmPlayer * player = (NNSSndStrmPlayer *)data1;

    if (mem == player->buffer) {
        OS_LockMutex(&data_020d5600.mutex);
        if (data_020d5254) OS_LockMutex(&data_020d5254->mutex);

        func_0209e328(player);

        player->buffer = NULL;
        player->bufSize = 0;

        player->numChannels = 0;
        if (player->allocChannelCount > 0) {
            NNS_SndStrmFreeChannel(&player->stream);
            player->allocChannelCount = 0;
        }

        OS_UnlockMutex(&data_020d5600.mutex);
        if (data_020d5254) OS_UnlockMutex(&data_020d5254->mutex);
    }
}
