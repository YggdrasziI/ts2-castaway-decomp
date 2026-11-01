/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/snd.h"
#define PushCommand(c, a0, a1, a2, a3) PushCommand_impl((c), (u32)(a0), (u32)(a1), (u32)(a2), (u32)(a3))
extern void PushCommand_impl(int command, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern void func_0207d5e0(void);
extern void func_0207d5cc(void);
extern void DC_StoreRange(void *addr, u32 size);
void func_0207e5d8(SNDBankData *bank, int index, SNDWaveArc *waveArc);

void func_0207e5d8(SNDBankData *bank, int index, SNDWaveArc *waveArc)
{
    SNDWaveArcLink *next;
    SNDWaveArcLink *prev;

    func_0207d5e0();

    if (bank->waveArcLink[index].waveArc != NULL) {
        if (waveArc == bank->waveArcLink[index].waveArc) {
            func_0207d5cc();
            return;
        }

        if (&bank->waveArcLink[index] == bank->waveArcLink[index].waveArc->topLink) {
            bank->waveArcLink[index].waveArc->topLink = bank->waveArcLink[index].next;

            DC_StoreRange(bank->waveArcLink[index].waveArc, sizeof(SNDWaveArc));
        } else {
            prev = bank->waveArcLink[index].waveArc->topLink;
            while (prev != NULL) {
                if (&bank->waveArcLink[index] == prev->next)
                    break;
                prev = prev->next;
            }
            prev->next = bank->waveArcLink[index].next;

            DC_StoreRange(prev, sizeof(SNDWaveArcLink));
        }
    }

    next = waveArc->topLink;
    waveArc->topLink = &bank->waveArcLink[index];
    bank->waveArcLink[index].next = next;
    bank->waveArcLink[index].waveArc = waveArc;

    func_0207d5cc();

    DC_StoreRange(bank, sizeof(SNDBankData));
    DC_StoreRange(waveArc, sizeof(SNDWaveArc));
}
