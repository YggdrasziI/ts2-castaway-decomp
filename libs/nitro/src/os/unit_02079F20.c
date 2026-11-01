/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"

typedef void (*OSIrqFunction)(void *arg);

extern void OS_DisableIrqMask(u32 mask);

/* One 12-byte record per interrupt source: the handler to run once, whether the
   source stays enabled afterwards, and the argument the handler receives. The
   three pool words the original carries are the three field bases of this one
   table. bKeepEnabled is written by the code that arms a slot, so it is read
   fresh here rather than folded into the test below. */
typedef struct {
    OSIrqFunction pfnHandler;
    volatile u32 bKeepEnabled;
    void *pArg;
} OSiIrqSlot;

extern OSiIrqSlot data_020c5734[];

/* One hardware bit index per slot. */
extern u16 data_020bcb78[];

extern u32 data_027e0000;

#define DTCM ((char *)&data_027e0000)
#define OSi_IrqCheckFlags (*(volatile u32 *)(DTCM + 0x3ff8))

void func_02079f20(u32 slot)
{
    u32 mask = 1 << data_020bcb78[slot];
    OSIrqFunction handler = data_020c5734[slot].pfnHandler;

    /* A slot fires once: clear it before running it so a handler may re-arm it. */
    data_020c5734[slot].pfnHandler = 0;
    if (handler != 0) {
        handler(data_020c5734[slot].pArg);
    }

    {
        OSi_IrqCheckFlags |= mask;
        if (data_020c5734[slot].bKeepEnabled == 0) {
            OS_DisableIrqMask(mask);
        }
    }
}
