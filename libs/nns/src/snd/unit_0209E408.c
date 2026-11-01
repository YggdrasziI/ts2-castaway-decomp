/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on


#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

extern const s16 data_020b335c[128 ];
static inline
s16 SND_CalcDecibel (int scale)
{
    return data_020b335c[scale];
}
void NNS_SndStrmStart(NNSSndStrm * stream);
void NNS_SndStrmSetVolume(NNSSndStrm * stream, int volume);
int NNSi_SndFaderGet(const NNSSndFader * fader);
void NNSi_SndFaderUpdate(NNSSndFader * fader);
BOOL NNSi_SndFaderIsFinished(const NNSSndFader * fader);
extern NNSSndStrmPlayer data_020d5aec[4 ];
extern void func_0209e328(NNSSndStrmPlayer * player);
extern void func_0209e328 (NNSSndStrmPlayer * player);

extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
/* func_0209e408 -- NitroSystem sndarc_stream.c: func_0209e408. */
void func_0209e408 (void)
{
    NNSSndStrmPlayer * player;
    int playerNo;
    int volume;

    for (playerNo = 0; playerNo < NNS_SND_STRM_PLAYER_NUM; ++playerNo) {
        player = &data_020d5aec[ playerNo ];

        if (!player->activeFlag) continue;

        if (player->finishCounter == 0) {
            func_0209e328(player);
            continue;
        }

        if (player->startFlag) {
            if (player->prepareFlag) {
                NNS_SndStrmStart(&player->stream);

                player->playFlag = TRUE;
                player->startFlag = FALSE;
            }
        }

        if (!player->playFlag) continue;

        NNSi_SndFaderUpdate(&player->fader);

        volume
            = SND_CalcDecibel(NNSi_SndFaderGet(&player->fader) >> 8)
              + SND_CalcDecibel(player->initVolume)
            ;
        if (volume != player->volume) {
            NNS_SndStrmSetVolume(&player->stream, volume);

            player->volume = volume;
        }

        if (player->fadeOutFlag) {
            if (NNSi_SndFaderIsFinished(&player->fader)) {
                func_0209e328(player);
            }
        }
    }
}
