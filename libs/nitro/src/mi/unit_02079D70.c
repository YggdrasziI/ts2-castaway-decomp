/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/mi.h"
#define DTCM ((char *)&data_027e0000)
static inline void MIi_CallCallback(MIDmaCallback callback, void *arg)
{
    if (callback) {
        (callback)(arg);
    }
}
#define MIi_DmaSetParams_wait func_01ff85d0
#define MIi_GXDmaParams data_020446b0
extern void *func_02079f20();
extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void func_0207a904(void *queue);
extern u32 data_027e0000;
extern u32 data_027e0060;
extern void MI_SetWramBank(int bank);
extern void MI_StopDma(int ch);
extern void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);
extern void func_01ff8220(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff85d0(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void MI_WaitDma(u32 dmaNo);
extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);
extern u32 OS_ResetRequestIrqMask(u32 intr);
extern void OS_Terminate(void);
extern MIiGXDmaParams data_020446b0;
extern void MIi_DMACallback(void *arg);
extern void MIi_DMAFastCallback(void *arg);
void *func_02079f10();
void *func_02079f00();
void *func_02079ef0();
void *func_02079ee0();
void *func_02079ed0();
void *func_02079ec0();
void *func_02079eb0();
void *func_02079ea0();
void OS_WaitIrq(BOOL clear, u32 irqFlags);
void MI_Init(void);
void MIi_CardDmaCopy32 (u32 dmaNo, const void * src, void * dest, u32 size);

void *func_02079f10() {
    return func_02079f20(0);
}

void *func_02079f00() {
    return func_02079f20(1);
}

void *func_02079ef0() {
    return func_02079f20(2);
}

void *func_02079ee0() {
    return func_02079f20(3);
}

void *func_02079ed0() {
    return func_02079f20(4);
}

void *func_02079ec0() {
    return func_02079f20(5);
}

void *func_02079eb0() {
    return func_02079f20(6);
}

void *func_02079ea0() {
    return func_02079f20(7);
}

void OS_WaitIrq(BOOL clear, u32 irqFlags)
{
    OSIntrMode last = OS_DisableInterrupts();

    if (clear) {
        OSi_IrqCheckFlags &= ~irqFlags;
    }
    OS_RestoreInterrupts(last);

    /* The base belongs to the block holding BOTH the early exit and the wait, and the
       wait's own pointer to a block inside that one. Hoist either to function scope and
       the scheduler builds the loop's address in the load-use shadow of the first read,
       which is the whole difference against the original. */
    {
        char *const dtcm = DTCM;

        if (irqFlags & *(volatile u32 *)(dtcm + 0x3ff8)) {
            return;
        }
        {
            volatile u32 *flags = (volatile u32 *)(dtcm + 0x3ff8);

            do {
                func_0207a904(&data_027e0060);
            } while ((irqFlags & *flags) == 0);
        }
    }
}

void MI_Init(void) {
    MI_SetWramBank(3);
    MI_StopDma(0);
}

void MIi_CardDmaCopy32 (u32 dmaNo, const void * src, void * dest, u32 size)
{
    vu32 * dmaCntp;

    (void)size;

    MIi_CheckAnotherAutoDMA(dmaNo, MIi_DMA_TIMING_ANY);

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, MI_DMA_SRC_FIX);

    if (size == 0) {
        return;
    }

    MIi_Wait_BeforeDMA(dmaCntp, dmaNo);
    func_01ff8220(dmaNo, (u32)src, (u32)dest, (u32)(MI_CNT_CARDRECV32(4) | MI_DMA_CONTINUOUS_ON));
}
