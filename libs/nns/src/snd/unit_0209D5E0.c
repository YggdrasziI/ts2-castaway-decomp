/*
 * NitroSystem sndarc_stream.c, part: stream set-up, wave data and end of data
 * (0x0209D5E0-0x0209E05C). khdays (CC0) per-function sources, retyped for this
 * ROM's player layout. File bounds are a hypothesis.
 */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

#define ADPCM_INDEX_NUM 89
#define STRM_CHANNEL_MAX 6

typedef enum StrmFormat {
    STRM_FORMAT_PCM8,
    STRM_FORMAT_PCM16,
    STRM_FORMAT_ADPCM
} StrmFormat;

typedef struct LoadCommand {
    NNSFndLink link;
    NNSSndStrmPlayer * player;
    NNSSndStrmCallbackStatus status;
    int numChannels;
    void * buffer[STRM_CHANNEL_MAX];
    u32 bufLen;
} LoadCommand;

extern const s8 data_020b58ec[16];
extern const s16 data_020b58fc[ADPCM_INDEX_NUM];
extern OSMutex data_020d5268;
extern u8 *data_020d5258;
void *NNS_SndArcGetFileAddress(u32 fileId);
const NNSSndArcStrmInfo *func_0209bc04(int strmNo);
BOOL OpenFileStream(NNSSndStrmPlayer *player, u32 fileId);
void func_0209d550(NNSSndStrmPlayer *player);
s32 ReadFileStream(NNSSndStrmPlayer *player, void *dest, u32 size, u32 offset);
void func_0209d504(NNSSndStrmPlayer *player);
BOOL OpenMemoryStream(NNSSndStrmPlayer *player, u32 fileId);
void func_0209d4d0(NNSSndStrmPlayer *player);
s32 ReadMemoryStream(NNSSndStrmPlayer *player, void *dest, u32 size, u32 offset);
void func_0209d4ac(NNSSndStrmPlayer *player);
void OS_LockMutex(OSMutex *mutex);
void OS_UnlockMutex(OSMutex *mutex);
void MI_CpuFill8(void *dest, u8 data, u32 size);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void DC_FlushRange(const void *startAddr, u32 nBytes);
void func_0209def8(NNSSndStrmPlayer *player);
void func_0209d5e0(NNSSndStrmPlayer *player, u32 fileId);
#define MI_CpuClear8(dest, size) MI_CpuFill8((dest), 0, (size))

void func_0209def8 (NNSSndStrmPlayer * player)
{
    NNSSndArcStrmCallbackInfo info;
    NNSSndArcStrmCallbackParam param;
    const NNSSndArcStrmInfo * strmInfo;
    u8 old_format;
    u16 old_sampleRate;
    BOOL result;

    info.playerNo = player->playerNo;
    info.strmNo = player->strmNo;

    param.strmNo = player->strmNo;
    param.offset = 0;

    result = player->sndArcStrmCallback(
        NNS_SND_ARC_STRM_CALLBACK_DATA_END,
        &info,
        &param,
        player->sndArcStrmCallbackArg
        );
    if (!result) return;

    strmInfo = func_0209bc04(param.strmNo);
    if (strmInfo == NULL) return;

    old_format = player->info.format;
    old_sampleRate = player->info.sampleRate;

    player->closeStreamFunc(player);

    func_0209d5e0(player, strmInfo->fileId);

    if (!player->openStreamFunc(player, strmInfo->fileId)) {
        return;
    }

    if (old_sampleRate != player->info.sampleRate) {
        return;
    }
    if (old_format == STRM_FORMAT_PCM8 && player->info.format != STRM_FORMAT_PCM8 ||
        old_format != STRM_FORMAT_PCM8 && player->info.format == STRM_FORMAT_PCM8) {
        return;
    }

    player->strmNo = param.strmNo;
    player->curSample = player->info.sampleRate * param.offset / 1000;
    if (player->curSample != 0 && player->info.format == STRM_FORMAT_ADPCM) {
        player->dirtyFlag = TRUE;
    } else {
        player->dirtyFlag = FALSE;
    }

    player->finishFlag = FALSE;
}

static inline s16 DecodeAdpcm (int code, AdpcmState * state)
{
    int step;
    int sample;
    int index;
    int d;

    sample = state->prevSample;
    index = state->prevIndex;

    step = data_020b58fc[ index ];

    d = step >> 3;
    if (code & 4) d += step;
    if (code & 2) d += step >> 1;
    if (code & 1) d += step >> 2;

    if (code & 8) {
        sample -= d;
        if (sample < -32768) sample = -32768;
    } else {
        sample += d;
        if (sample > 32767) sample = 32767;
    }

    index += data_020b58ec[ code ];

    if (index < 0) index = 0;
    else if (index > ADPCM_INDEX_NUM - 1) index = ADPCM_INDEX_NUM - 1;

    state->prevSample = (s16)sample;
    state->prevIndex = (u8)index;

    return (s16)sample;
}

void func_0209d668 (LoadCommand * command)
{
    NNSSndStrmPlayer * player = command->player;
    BOOL loopFlag;
    long destOffset;
    u32 restSize;
    u32 blockNo;
    u32 blockSize;
    u32 blockSamples;
    u32 blockOffsetSample;
    u32 blockOffset;
    u32 offset;
    u32 samples;
    u32 size;
    u32 readSize;
    int ch;

    if (player->finishFlag && player->finishCounter > 0) {
        player->finishCounter--;
    }

    destOffset = 0;

    restSize = command->bufLen;
    while (restSize > 0) {
        if (player->finishFlag) {
            for (ch = 0; ch < command->numChannels; ch++) {
                MI_CpuClear8((u8 *)(command->buffer[ ch ]) + destOffset, restSize);
            }
            break;
        }

        blockNo = player->curSample / player->info.blockSamples;

        if (blockNo < player->info.numBlocks - 1) {
            blockSize = player->info.blockSize;
            blockSamples = player->info.blockSamples;
        } else {
            blockSize = player->info.lastBlockSize;
            blockSamples = player->info.lastBlockSamples;
        }

        blockOffsetSample = player->curSample;
        blockOffsetSample -= blockNo * player->info.blockSamples;

        samples = restSize;
        if (player->info.format != STRM_FORMAT_PCM8) {
            samples >>= 1;
        }

        if (player->dirtyFlag) {
            if (blockOffsetSample == 0) {
                player->dirtyFlag = FALSE;
            } else {
                samples = blockOffsetSample;
                blockOffsetSample = 0;
            }
        }

        loopFlag = FALSE;
        if (blockOffsetSample + samples >= blockSamples) {
            samples = blockSamples - blockOffsetSample;

            if (blockNo >= player->info.numBlocks - 1) {
                if (player->info.loopFlag) {
                    loopFlag = TRUE;
                } else {
                    player->finishFlag = TRUE;
                }
            }
        }

        blockOffset = blockOffsetSample;
        size = samples;
        switch (player->info.format) {
        case STRM_FORMAT_PCM8:
            readSize = size;
            break;
        case STRM_FORMAT_PCM16:
            blockOffset <<= 1;
            size <<= 1;
            readSize = size;
            break;
        case STRM_FORMAT_ADPCM: {
            u32 endSample = blockOffsetSample + samples;
            blockOffset >>= 1;
            endSample++; endSample >>= 1;
            readSize = endSample - blockOffset;
            if (blockOffsetSample == 0) {
                readSize += sizeof(AdpcmState);
            } else {
                blockOffset += sizeof(AdpcmState);
            }
            size <<= 1;

            break;
        }
        }

        offset = blockOffset;
        offset += blockNo * player->info.blockSize * player->info.numChannels;
        offset += player->info.dataOffset;

        for (ch = 0; ch < command->numChannels; ch++) {
            void * dest;
            void * read_dest;

            dest = read_dest = (u8 *)(command->buffer[ ch ]) + destOffset;

            if (ch < player->info.numChannels) {
                s32 resultSize;

                if (player->info.format == STRM_FORMAT_ADPCM) {
                    OS_LockMutex(&data_020d5268);
                    read_dest = data_020d5258;
                }

                resultSize = player->readStreamFunc(
                    player,
                    read_dest,
                    readSize,
                    offset + ch * blockSize
                    );

                if (resultSize != readSize) {
                    size = 0;
                    samples = 0;
                    loopFlag = FALSE;
                    player->finishFlag = TRUE;
                    if (player->info.format == STRM_FORMAT_ADPCM) {
                        OS_UnlockMutex(&data_020d5268);
                    }
                    break;
                }

                if (player->info.format == STRM_FORMAT_ADPCM) {
                    AdpcmState * state = &player->adpcmState[ ch ];
                    u8 * srcp = data_020d5258;
                    s16 * destp = dest;
                    u32 i;
                    u32 end;

                    if (blockOffsetSample == 0) {
                        *state = *((AdpcmState *)srcp)++;
                    }

                    end = blockOffsetSample + samples;

                    i = blockOffsetSample;
                    if (i & 0x01) {
                        *destp++ = DecodeAdpcm((*srcp >> 4) & 0x0f, state); i++;
                        srcp++;
                    }
                    while (i < (end & ~0x01)) {
                        *destp++ = DecodeAdpcm(*srcp & 0x0f, state); i++;
                        *destp++ = DecodeAdpcm((*srcp >> 4) & 0x0f, state); i++;
                        srcp++;
                    }
                    if (i < end) {
                        *destp++ = DecodeAdpcm(*srcp & 0x0f, state); i++;
                    }
                    OS_UnlockMutex(&data_020d5268);
                }
            } else {
                if (player->monoFlag) {
                    MI_CpuClear8(dest, size);
                } else {
                    MI_CpuCopy8((u8 *)(command->buffer[ 0 ]) + destOffset, dest, size);
                }
            }
        }

        if (player->dirtyFlag) {
            player->dirtyFlag = FALSE;
            continue;
        }

        if (loopFlag) {
            player->curSample = player->info.loopStart;
        } else {
            player->curSample += samples;
        }

        destOffset += size;

        restSize -= size;

        if (player->finishFlag && player->sndArcStrmCallback) {
            func_0209def8(player);
        }
    }

    if (player->strmCallback != NULL) {
        player->strmCallback(
            command->status,
            command->numChannels,
            command->buffer,
            command->bufLen,
            player->info.format == STRM_FORMAT_PCM8 ? NNS_SND_STRM_FORMAT_PCM8 : NNS_SND_STRM_FORMAT_PCM16,
            player->strmCallbackArg
            );
    }

    for (ch = 0; ch < command->numChannels; ch++) {
        DC_FlushRange(command->buffer[ ch ], command->bufLen);
    }

    if (command->status == NNS_SND_STRM_CALLBACK_SETUP) {
        player->prepareFlag = TRUE;
    }
}

void func_0209d5e0 (NNSSndStrmPlayer * player, u32 fileId)
{
    if (NNS_SndArcGetFileAddress(fileId) == NULL) {
        player->openStreamFunc = OpenFileStream;
        player->closeStreamFunc = func_0209d550;
        player->readStreamFunc = ReadFileStream;
        player->cancelStreamFunc = func_0209d504;
    } else {
        player->openStreamFunc = OpenMemoryStream;
        player->closeStreamFunc = func_0209d4d0;
        player->readStreamFunc = ReadMemoryStream;
        player->cancelStreamFunc = func_0209d4ac;
    }

}
