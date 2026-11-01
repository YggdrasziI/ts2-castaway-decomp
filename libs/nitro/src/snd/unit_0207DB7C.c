/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/snd.h"
#include "sdk/types.h"
#include "sdk/os.h"
#define data_02041588 data_020b345c
#define data_02046220 data_020c7680
#define data_02044a20 data_020c5e80
#define data_02044748 data_020c5bac
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))
#define SND_CHANNEL_DATASHIFT_NONE 0
#define SND_CHANNEL_DATASHIFT_1BIT 1
#define SND_CHANNEL_DATASHIFT_2BIT 2
#define SND_CHANNEL_DATASHIFT_4BIT 3
#define VolumeTable data_02041588
typedef struct SndSharedWorkSlot {
    short cells[16];
    int val;
} SndSharedWorkSlot;
typedef struct SndSharedWork {
    int field_00;
    int field_04;
    short field_08;
    short field_0a;
    unsigned char pad_0c[0x20 - 0x0c];
    SndSharedWorkSlot slots[16];
    short field_260[16];
} SndSharedWork;
typedef struct AlarmCallbackInfo {
    SNDAlarmHandler func;         /* 0x00 */
    void *arg;                    /* 0x04 */
    u8 id;                        /* 0x08 */
} AlarmCallbackInfo;
#define sCallbackTable data_02046220
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define sFreeList data_02044748
#define sWaitingCommandListQueue data_020c5bd0
#define sSharedWork data_020c5c00
extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));
#define sCommandArray data_02044a20
#define SNDi_SharedWork data_020c76e0
extern void func_0207d5e0(void);
extern void func_0207d5cc(void);
extern void DC_StoreRange(void *p, unsigned int len);
extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern const u8 data_020b345c[];
extern void DC_InvalidateRange(void *p, unsigned int len);
extern void DC_FlushRange(void *address, unsigned int size);
extern unsigned char data_020c7680;
extern int data_020c5bc8;
extern int data_020c5bc4;
extern int data_020c5bc0;
extern SNDCommand *data_020c5bbc;
extern SNDCommand *data_020c5bb8;
extern SNDCommand *data_020c5bb4;
extern u32 data_020c5bb0;
extern SNDCommand *data_020c5bac;
extern u32 data_020c5bcc;
extern SNDCommand *data_020c5bd0[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern SNDSharedWork data_020c5c00;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SpinWait(u32 cycles);
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(int tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void func_0207d714(void);
extern void func_0207db34(SNDCommand *command);
extern BOOL func_0207d974(u32 flags);
extern int sWaitingCommandListQueueWrite;
extern SNDCommand *sReserveListEnd;
extern SNDCommand *sReserveList;
extern u32 sCurrentTag;
extern SNDCommand *data_020c5bd0[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern SNDSharedWork data_020c5c00;
extern int *data_020c76e0;
extern void InitPXI(void);
extern void SND_PushCommand(SNDCommand *command);
extern BOOL SND_FlushCommand(u32 flags);
extern SNDCommand *func_0207d688(void);
extern int func_0207d7b0(void);
extern void func_0207d6e0(void);
SNDInstPos SND_GetFirstInstDataPos(const SNDBankData *bank);
BOOL SND_GetNextInstData(const SNDBankData *bank, SNDInstData *inst, SNDInstPos *pos);
int func_0207e0f4(int *p);
void func_0207e0bc(char *table, int slot, void *addr);
const SNDWaveData *func_0207e074(const SNDWaveArc *waveArc, int index);
u16 func_0207e000(int dB);
int func_0207dfc8(void);
int func_0207df94(void);
void func_0207df14(SndSharedWork *self);
void func_0207dee4(void);
void func_0207dec4(int n);
void func_0207de64(int msg);
void func_0207dd4c (void);
const SNDCommand * func_0207dc18 (u32 flags);
SNDCommand *func_0207db7c(u32 flags);

SNDInstPos SND_GetFirstInstDataPos(const SNDBankData *bank)
{
    SNDInstPos pos;
    (void)bank;
    pos.prgNo = 0;
    pos.index = 0;
    return pos;
}

BOOL SND_GetNextInstData(const SNDBankData *bank, SNDInstData *inst, SNDInstPos *pos)
{
    for (; pos->prgNo < bank->instCount; pos->prgNo++, pos->index = 0) {
        u32 instOffset = bank->instOffset[pos->prgNo];
        inst->type = (u8)(instOffset & 0xff);
        instOffset >>= 8;

        switch (inst->type) {
        case SND_INST_PCM:
        case SND_INST_PSG:
        case SND_INST_NOISE:
        case SND_INST_DIRECTPCM:
        case SND_INST_NULL:
        {
            const SNDInstParam *param = (const SNDInstParam *)((u8 *)bank + instOffset);
            inst->param = *param;
            pos->prgNo++;
            return TRUE;
        }
        case SND_INST_DRUM_SET:
        {
            const SNDDrumSet *drumSet = (const SNDDrumSet *)((u8 *)bank + instOffset);
            for (; pos->index < drumSet->max - drumSet->min + 1; pos->index++) {
                *inst = drumSet->instOffset[pos->index];
                pos->index++;
                return TRUE;
            }
            break;
        }
        case SND_INST_KEY_SPLIT:
        {
            const SNDKeySplit *keySplit = (const SNDKeySplit *)((u8 *)bank + instOffset);
            for (; pos->index < SND_INST_KEYSPLIT_MAX; pos->index++) {
                if (keySplit->key[pos->index] == 0)
                    break;
                *inst = keySplit->instOffset[pos->index];
                pos->index++;
                return TRUE;
            }
            break;
        }
        default:
            break;
        }
    }

    return FALSE;
}

int func_0207e0f4(int *p){ return p[14]; }

void func_0207e0bc(char *table, int slot, void *addr) {
    func_0207d5e0();
    *(void **)(table + slot * 4 + 0x3c) = addr;
    DC_StoreRange(table + 0x3c + slot * 4, 4);
    func_0207d5cc();
}

const SNDWaveData *func_0207e074(const SNDWaveArc *waveArc, int index)
{
    const SNDWaveData *wave;
    u32 offset;

    func_0207d5e0();

    offset = waveArc->waveOffset[index];

    if (offset != 0) {
        if (offset < HW_MAIN_MEM)
            wave = (const SNDWaveData *)((u8 *)waveArc + offset);
        else
            wave = (const SNDWaveData *)offset;
    } else {
        wave = NULL;
    }

    func_0207d5cc();

    return wave;
}

u16 func_0207e000(int dB)
{
    SNDChannelDataShift shift;
    u8 volume;

    if (dB < SND_VOLUME_DB_MIN) {
        dB = SND_VOLUME_DB_MIN;
    } else if (dB > SND_VOLUME_DB_MAX) {
        dB = SND_VOLUME_DB_MAX;
    }

    volume = VolumeTable[dB - SND_VOLUME_DB_MIN];

    if (dB < SND_VOLUME_SHIFT_2_MIN) {
        shift = SND_CHANNEL_DATASHIFT_4BIT;
    } else if (dB < SND_VOLUME_SHIFT_1_MIN) {
        shift = SND_CHANNEL_DATASHIFT_2BIT;
    } else if (dB < SND_VOLUME_SHIFT_0_MIN) {
        shift = SND_CHANNEL_DATASHIFT_1BIT;
    } else {
        shift = SND_CHANNEL_DATASHIFT_NONE;
    }

    return (u16)(shift << 8 | volume);
}

int func_0207dfc8(void) {
    DC_InvalidateRange(data_020c76e0 + 1, 4);
    return data_020c76e0[1];
}

int func_0207df94(void) {
    DC_InvalidateRange(data_020c76e0, 4);
    return *data_020c76e0;
}

void func_0207df14(SndSharedWork *self) {
    int i;
    int j;

    self->field_04 = 0;
    self->field_08 = 0;
    self->field_0a = 0;
    self->field_00 = 0;

    for (i = 0; i < 16; i++) {
        self->slots[i].val = 0;
        for (j = 0; j < 16; j++) {
            self->slots[i].cells[j] = -1;
        }
    }

    for (j = 0; j < 16; j++) {
        self->field_260[j] = -1;
    }

    DC_FlushRange(self, 0x280);
}

void func_0207dee4(void) {
    int i;
    char *p = (char *)&data_020c7680;

    for (i = 0; i < 8; i++) {
        *(int *)p = 0;
        *(int *)(p + 4) = 0;
        *(unsigned char *)(p + 8) = 0;
        p += 0xc;
    }
}

void func_0207dec4(int n) {
    ++*(unsigned char *)((int)&data_020c7680 + n * 0xc + 8);
}

void func_0207de64(int msg)
{
    AlarmCallbackInfo *info;
    int alarmNo = msg & 0xff;
    int id = (msg >> 8) & 0xff;

    info = &((AlarmCallbackInfo *)&sCallbackTable)[alarmNo];

    if (id == info->id) {
        if (info->func != NULL) {
            info->func(info->arg);
        }
    }
}

void func_0207dd4c (void)
{
    SNDCommand * command;
    int i;

    func_0207d714();

    sFreeList = &sCommandArray[0];
    for (i = 0; i < SND_COMMAND_NUM - 1; i++) {
        sCommandArray[i].next = &sCommandArray[i + 1];
    }
    sCommandArray[SND_COMMAND_NUM - 1].next = NULL;
    data_020c5bbc = &sCommandArray[SND_COMMAND_NUM - 1];

    data_020c5bb4 = NULL;
    data_020c5bb8 = NULL;

    data_020c5bc8 = 0;

    data_020c5bc0 = 0;
    data_020c5bc4 = 0;

    data_020c5bcc = 1;
    data_020c5bb0 = 0;

    SNDi_SharedWork = (int *)&sSharedWork;
    func_0207df14((void *)SNDi_SharedWork);

    command = func_0207db7c(SND_COMMAND_BLOCK);
    if (command != NULL) {
        command->id = SND_COMMAND_SHARED_WORK;
        command->arg[0] = (u32)SNDi_SharedWork;

        func_0207db34(command);
        (void)func_0207d974(SND_COMMAND_BLOCK);
    }

}

const SNDCommand * func_0207dc18 (u32 flags)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();
    SNDCommand * commandList;
    SNDCommand * commandListEnd;

    if (flags & SND_COMMAND_BLOCK) {
        while (data_020c5bb0 == func_0207df94()) {
            (void)OS_RestoreInterrupts(bak_psr);
            OS_SpinWait(100);
            bak_psr = OS_DisableInterrupts();
        }
    } else {
        if (data_020c5bb0 == func_0207df94()) {
            (void)OS_RestoreInterrupts(bak_psr);
            return NULL;
        }
    }

    commandList = sWaitingCommandListQueue[data_020c5bc0];
    data_020c5bc0++;
    if (data_020c5bc0 > SND_PXI_FIFO_MESSAGE_BUFSIZE)
        data_020c5bc0 = 0;

    commandListEnd = commandList;
    while (commandListEnd->next != NULL) {
        commandListEnd = commandListEnd->next;
    }

    if (data_020c5bbc != NULL) {
        data_020c5bbc->next = commandList;
    } else {
        sFreeList = commandList;
    }

    data_020c5bbc = commandListEnd;

    data_020c5bc8--;
    data_020c5bb0++;

    (void)OS_RestoreInterrupts(bak_psr);
    return commandList;
}

SNDCommand *func_0207db7c(u32 flags)
{
    SNDCommand *command;

    if (!IsCommandAvailable())
        return NULL;

    command = func_0207d688();
    if (command != NULL)
        return command;

    if ((flags & SND_COMMAND_BLOCK) == 0)
        return NULL;

    if (func_0207d7b0() > 0) {
        while (func_0207dc18(SND_COMMAND_NOBLOCK) != NULL) {
        }

        command = func_0207d688();
        if (command != NULL)
            return command;
    } else {
        (void)func_0207d974(SND_COMMAND_BLOCK);
    }

    func_0207d6e0();

    do {
        (void)func_0207dc18(SND_COMMAND_BLOCK);
        command = func_0207d688();
    } while (command == NULL);

    return command;
}
