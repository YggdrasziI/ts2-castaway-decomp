/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define data_027e006c data_027e0060
#define data_020442a8 data_020c5734
#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)
#define OSi_TimerSlots     (&data_020442a8[4])
extern int data_027e0060;
extern OSiIrqSlot data_020c5734[];
extern unsigned int data_027e0000;
extern u32 OS_EnableIrqMask(u32 mask);
void func_0207a204(void);
void func_0207a174(unsigned int intrBits, OSIrqFunction function);
void func_0207a128(u32 dmaNo, OSIrqFunction function, void *arg);
void func_0207a0dc(u32 timerNo, OSIrqFunction function, void *arg);

void func_0207a204(void) {
    *(int *)((int)&data_027e0060 + 4) = 0;
    data_027e0060 = 0;
}

void func_0207a174(unsigned int intrBits, OSIrqFunction function)
{
    int i;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1) {
        if (intrBits & 1) {
            OSiIrqSlot *slot = 0;

            if (i >= 8 && i <= 11) {
                slot = &data_020c5734[i - 8];
            } else if (i >= 3 && i <= 6) {
                slot = &data_020c5734[i + 1];
            } else {
                OSi_IrqTable[i] = function;
            }

            if (slot != 0) {
                slot->pfnHandler = function;
                slot->pArg = 0;
                slot->bKeepEnabled = 1;
            }
        }
    }
}

void func_0207a128(u32 dmaNo, OSIrqFunction function, void *arg)
{
    u32 mask = 1 << (dmaNo + OS_IRQ_DMA0_BIT);

    data_020c5734[dmaNo].pfnHandler = function;
    data_020c5734[dmaNo].pArg = arg;
    data_020c5734[dmaNo].bKeepEnabled = OS_EnableIrqMask(mask) & mask;
}

void func_0207a0dc(u32 timerNo, OSIrqFunction function, void *arg)
{
    OSi_TimerSlots[timerNo].pfnHandler = function;
    OSi_TimerSlots[timerNo].pArg = arg;

    OS_EnableIrqMask(1 << (timerNo + OS_IRQ_TIMER0_BIT));

    OSi_TimerSlots[timerNo].bKeepEnabled = 1;
}
