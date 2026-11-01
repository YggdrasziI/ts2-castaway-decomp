/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#include "sdk/os.h"
#include "sdk/pxi.h"
#include "sdk/mi.h"
#include "sdk/spi.h"
#include "nnsys/fnd.h"
#define NNS_FROM_TOOL
#define offsetof(type, member) ((u32)&(((type *)0)->member))
typedef struct CaptureParam {
    BOOL activeFlag;
    NNSSndCaptureType type;
    NNSSndCaptureFormat format;
    void * bufferL;
    void * bufferR;
    u32 bufLen;
    u32 blockSize;
    int curBuffer;
    u32 chBitMask;
    u32 playChBitMask;
    u32 capBitMask;
    int alarmNo;
    int interval;
    NNSSndCaptureCallback callback;
    void * callbackArg;
    NNSSndFader fader;
    BOOL fadeOutFlag;
    int volume;
} CaptureParam;
static inline void PM_SetSleepCallbackInfo (PMSleepCallbackInfo * info, PMSleepCallback callback, void * arg)
{
    info->callback = callback;
    info->arg = arg;
}
extern NNSSndArc * data_020d5210;
extern CaptureParam data_020d51bc;
extern volatile BOOL data_020d5198;
void SND_SetChannelVolume(u32 chBitMask, int volume, SNDChannelDataShift shift);
int NNSi_SndFaderGet(const NNSSndFader * fader);
void NNSi_SndFaderUpdate(NNSSndFader * fader);
BOOL NNSi_SndFaderIsFinished(const NNSSndFader * fader);
BOOL OS_ReceiveMessage(OSMessageQueue * mq, OSMessage * msg, s32 flags);
BOOL func_0207d974(u32 flags);
void SND_WaitForCommandProc(u32 tag);
u32 func_0207d8a4(void);
void SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void SND_SetOutputSelector(
    SNDOutput left,
    SNDOutput right,
    SNDChannelOut channel1,
    SNDChannelOut channel3
);
void func_0209a8cc(u32 chBitFlag);
void func_0209a8b0(u32 capBitFlag);
void func_0209a890(int alarmNo);
extern OSMessageQueue data_020d519c;
void MI_CpuFillU32(u32 data, void * destp, u32 size);
void DC_FlushRange(const void * startAddr, u32 nBytes);
void SND_StartTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void NNS_FndInitList(NNSFndList * list, u16 offset);
extern NNSFndList data_020d50cc;
extern BOOL data_020d50c8;
void func_0207f464(PMSleepCallbackInfo * info);
void func_0207f44c(PMSleepCallbackInfo * info);
u16 func_0207e000(int dB);
extern NNSSndStrmChannel data_020d5118[ 16 ];
extern struct SNDExChannel;
void func_0207f434(PMSleepCallbackInfo * info);
void func_0207f41c(PMSleepCallbackInfo * info);
void NNS_FndRemoveListObject(NNSFndList * list, void * object);
extern void * data_020d50d8[ NNS_SND_STRM_CHANNEL_MAX ];
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
FSFileID NNS_SndArcGetFileID (void);
void * NNS_SndArcGetFileAddress (u32 fileId);
void func_0209b9a0 (u32 fileId, void * address);
void InfoDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);
void FatDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);
void SymbolDisposeCallback (void * mem, u32 size, u32 data1, u32 data2);
void NNSi_SndCaptureInit (void);
void NNSi_SndCaptureMain (void);
void NNSi_SndCaptureStop (void);
void NNSi_SndCaptureBeginSleep (void);
void NNSi_SndCaptureEndSleep (void);
void NNS_SndStrmInit (NNSSndStrm * stream);
void NNS_SndStrmFreeChannel (NNSSndStrm * stream);
void NNS_SndStrmStart (NNSSndStrm * stream);
void NNS_SndStrmStop (NNSSndStrm * stream);
void NNS_SndStrmSetVolume (NNSSndStrm * stream, int volume);
void ForceStopStrm (NNSSndStrm * stream);
void ShutdownStrm (NNSSndStrm * stream);
void StrmCallback (NNSSndStrm * stream, NNSSndStrmCallbackStatus status);
void func_0209b358 (void * arg);
void EndSleep (void * arg);

FSFileID NNS_SndArcGetFileID (void)
{
    NNSSndArc * arc = data_020d5210;

    return arc->fileId;
}

void * NNS_SndArcGetFileAddress (u32 fileId)
{
    NNSSndArc * arc = data_020d5210;

    if (fileId >= arc->fat->count) return NULL;
    return arc->fat->files[ fileId ].mem;
}

void func_0209b9a0 (u32 fileId, void * address)
{
    NNSSndArc * arc = data_020d5210;

    arc->fat->files[ fileId ].mem = address;
}

void InfoDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;

    (void)mem;
    (void)size;
    (void)data2;

    arc->info = NULL;
}

void FatDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;
    int i;

    (void)mem;
    (void)size;
    (void)data2;

    for (i = 0; i < arc->fat->count; i++) {
#ifndef NNS_FROM_TOOL
#endif
    }

    arc->fat = NULL;
}

void SymbolDisposeCallback (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;

    (void)mem;
    (void)size;
    (void)data2;

    arc->symbol = NULL;
}

void NNSi_SndCaptureInit (void)
{
    data_020d5198 = FALSE;
    data_020d51bc.activeFlag = FALSE;
}

void NNSi_SndCaptureMain (void)
{
    CaptureParam * cap;
    NNSSndFader * fader;
    int volume;

    cap = &data_020d51bc;

    if (cap->activeFlag && cap->type == NNS_SND_CAPTURE_TYPE_REVERB) {
        fader = &cap->fader;

        NNSi_SndFaderUpdate(fader);

        if (cap->fadeOutFlag) {
            if (NNSi_SndFaderIsFinished(fader)) {
                NNSi_SndCaptureStop();
                return;
            }
        }

        volume = (NNSi_SndFaderGet(fader) >> 8);

        if (volume != cap->volume) {
            SND_SetChannelVolume(
                cap->playChBitMask,
                volume,
                SND_CHANNEL_DATASHIFT_NONE
                );

            cap->volume = volume;
        }
    }
}

void NNSi_SndCaptureStop (void)
{
    CaptureParam * cap = &data_020d51bc;
    u32 commandTag;
    BOOL useAlarm;

    if (!cap->activeFlag) return;

    useAlarm = cap->alarmNo >= 0 ? TRUE : FALSE;

    SND_StopTimer(
        cap->playChBitMask,
        cap->capBitMask,
        useAlarm ? (u32)(1 << cap->alarmNo) : 0,
        0
        );

    if (useAlarm) {

        commandTag = func_0207d8a4();
        (void)func_0207d974(SND_COMMAND_BLOCK);
        SND_WaitForCommandProc(commandTag);

        while (OS_ReceiveMessage(&data_020d519c, NULL, OS_MESSAGE_NOBLOCK)) {
        }
    }

    if (cap->capBitMask) func_0209a8b0(cap->capBitMask);
    if (cap->chBitMask) func_0209a8cc(cap->chBitMask);
    if (useAlarm) func_0209a890(cap->alarmNo);

    if (cap->type == NNS_SND_CAPTURE_TYPE_EFFECT) {
        SND_SetOutputSelector(
            SND_OUTPUT_MIXER,
            SND_OUTPUT_MIXER,
            SND_CHANNEL_OUT_MIXER,
            SND_CHANNEL_OUT_MIXER
            );
    }

    cap->activeFlag = FALSE;
}

void NNSi_SndCaptureBeginSleep (void)
{
    CaptureParam * cap;
    u32 commandTag;

    cap = &data_020d51bc;

    if (!cap->activeFlag) return;

    SND_StopTimer(
        cap->playChBitMask,
        cap->capBitMask,
        cap->alarmNo >= 0 ? (u32)(1 << cap->alarmNo) : 0,
        0
        );

    commandTag = func_0207d8a4();
    (void)func_0207d974(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}

void NNSi_SndCaptureEndSleep (void)
{
    CaptureParam * cap;

    cap = &data_020d51bc;

    if (!cap->activeFlag) return;

    cap->curBuffer = 0;

    MI_CpuClear32(cap->bufferL, cap->bufLen);
    MI_CpuClear32(cap->bufferR, cap->bufLen);
    DC_FlushRange(cap->bufferL, cap->bufLen);
    DC_FlushRange(cap->bufferR, cap->bufLen);

    SND_StartTimer(
        cap->playChBitMask,
        cap->capBitMask,
        cap->alarmNo >= 0 ? (u32)(1 << cap->alarmNo) : 0,
        0
    );
}

void NNS_SndStrmInit (NNSSndStrm * stream)
{

    {

        if (!data_020d50c8) {
            NNS_FND_INIT_LIST(&data_020d50cc, NNSSndStrm, link);
            data_020d50c8 = TRUE;
        }
    }

    PM_SetSleepCallbackInfo(&stream->preSleepInfo, func_0209b358, stream);
    PM_SetSleepCallbackInfo(&stream->postSleepInfo, EndSleep, stream);

    stream->chBitMask = 0;
    stream->numChannels = 0;
    stream->activeFlag = FALSE;
    stream->startFlag = FALSE;
}

void NNS_SndStrmFreeChannel (NNSSndStrm * stream)
{

    if (stream->chBitMask == 0) return;

    func_0209a8cc(stream->chBitMask);

    stream->chBitMask = 0;
    stream->numChannels = 0;
}

void NNS_SndStrmStart (NNSSndStrm * stream)
{

    SND_StartTimer(
        stream->chBitMask,
        0,
        (u32)(1 << stream->alarmNo),
        0
        );

    if (!stream->startFlag) {
        func_0207f464(&stream->preSleepInfo);
        func_0207f44c(&stream->postSleepInfo);

        stream->startFlag = TRUE;
    }
}

void NNS_SndStrmStop (NNSSndStrm * stream)
{

    if (!stream->activeFlag) return;

    ForceStopStrm(stream);
}

void NNS_SndStrmSetVolume (NNSSndStrm * stream, int volume)
{
    u16 chVolume;
    int vol;
    int chNo;
    int i;

    stream->volume = volume;

    for (i = 0; i < stream->numChannels; i++) {
        chNo = stream->channelNo[ i ];
        vol = stream->volume + data_020d5118[ chNo ].volume;
        chVolume = func_0207e000(vol);

        SND_SetChannelVolume(
            (u32)(1 << chNo),
            chVolume & 0xff,
            (SNDChannelDataShift)(chVolume >> 8)
            );
    }
}

void ForceStopStrm (NNSSndStrm * stream)
{
    u32 commandTag;

    if (stream->startFlag) {
        SND_StopTimer(
            stream->chBitMask,
            0,
            (u32)(1 << stream->alarmNo),
            0
            );

        func_0207f434(&stream->preSleepInfo);
        func_0207f41c(&stream->postSleepInfo);

        stream->startFlag = FALSE;

        commandTag = func_0207d8a4();
        (void)func_0207d974(SND_COMMAND_BLOCK);
        SND_WaitForCommandProc(commandTag);
    }

    ShutdownStrm(stream);
}

void ShutdownStrm (NNSSndStrm * stream)
{
    func_0209a890(stream->alarmNo);
    NNS_FndRemoveListObject(&data_020d50cc, stream);

    stream->activeFlag = FALSE;
}

void StrmCallback (NNSSndStrm * stream, NNSSndStrmCallbackStatus status)
{
    const unsigned long blockSize = stream->chBufLen / stream->interval;
    const unsigned long offset = blockSize * stream->curBuffer;
    int index;
    int chNo;

    for (index = 0; index < stream->numChannels; index++) {
        chNo = stream->channelNo[index];

        data_020d50d8[index] = (u8 *)(data_020d5118[chNo].buffer) + offset;
    }

    stream->callback(
        status,
        stream->numChannels,
        data_020d50d8,
        blockSize,
        stream->format,
        stream->callbackArg
        );

    stream->curBuffer++;
    if (stream->curBuffer >= stream->interval) stream->curBuffer = 0;
}

void func_0209b358 (void * arg)
{
    NNSSndStrm * stream = (NNSSndStrm *)arg;
    u32 commandTag;

    if (!stream->startFlag) return;

    SND_StopTimer(
        stream->chBitMask,
        0,
        (u32)(1 << stream->alarmNo),
        0
        );

    commandTag = func_0207d8a4();
    (void)func_0207d974(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}

void EndSleep (void * arg)
{
    NNSSndStrm * stream = (NNSSndStrm *)arg;

    if (!stream->startFlag) return;

    while (stream->curBuffer != 0) {
        OSIntrMode old = OS_DisableInterrupts();

        StrmCallback(stream, NNS_SND_STRM_CALLBACK_INTERVAL);

        (void)OS_RestoreInterrupts(old);
    }

    SND_StartTimer(
        stream->chBitMask,
        0,
        (u32)(1 << stream->alarmNo),
        0
        );
}
