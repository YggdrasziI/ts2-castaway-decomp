/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/os.h"
#include "sdk/pxi.h"
#include "sdk/snd.h"
#define func_02008aa0 func_0207d7d0
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define sFreeList data_020c5bac
#define sWaitingCommandListQueue data_0204476c
#define sSharedWork data_020447a0
extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));
#define sCommandArray data_02044a20
#define SNDi_SharedWork data_02046280
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_020c5bac;
extern char *data_020c5bb4;
extern void func_0207de64(int data);
extern int sWaitingCommandListCount;
extern int sWaitingCommandListQueueWrite;
extern int sWaitingCommandListQueueRead;
extern SNDCommand *sFreeListEnd;
extern SNDCommand *sReserveListEnd;
extern SNDCommand *sReserveList;
extern u32 sFinishedTag;
extern u32 sCurrentTag;
extern SNDCommand *data_0204476c[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern SNDSharedWork data_020447a0;
extern SNDSharedWork *data_02046280;
extern void OS_SpinWait(u32 cycles);
extern void func_0207c5d4(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern BOOL IsCommandAvailable(void);
extern void SNDi_InitSharedWork(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *SND_AllocCommand(u32 flags);
extern void SND_PushCommand(SNDCommand *command);
extern BOOL SND_FlushCommand(u32 flags);
extern int func_0207c4f8(int a, int b, int c);
int func_0207d810(void);
int func_0207d7d0(void);
int func_0207d7b0(void);
void func_0207d780(PXIFifoTag tag, u32 data, BOOL err);
void func_0207d714 (void);
void func_0207d6e0(void);

int func_0207d810(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_020c5bac;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}

int func_0207d7d0(void) {
    int enabled = OS_DisableInterrupts();
    int count = 0;
    char *cmd = *(char **)&data_020c5bb4;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}

int func_0207d7b0(void) {
    int reserved = func_0207d810();
    return 0x100 - reserved - func_0207d7d0();
}

void func_0207d780(PXIFifoTag tag, u32 data, BOOL err)
{
    OSIntrMode enabled;
    (void)tag;
    (void)err;
    enabled = OS_DisableInterrupts();
    func_0207de64((int)data);
    (void)OS_RestoreInterrupts(enabled);
}

void func_0207d714 (void)
{
    func_0207c5d4(PXI_FIFO_TAG_SOUND, func_0207d780);

    if (IsCommandAvailable()) {
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_SOUND, PXI_PROC_ARM7)) {
            OS_SpinWait(100);
        }
    }
}

void func_0207d6e0(void) {
    int cmd = 7;
    int zero = 0;
    while (func_0207c4f8(cmd, zero, zero) < 0) {
        ;
    }
}
