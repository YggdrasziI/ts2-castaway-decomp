/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/mi.h"
#include "sdk/os.h"
#include "sdk/card.h"
#include "sdk/pxi.h"
extern void func_0207a904(void *queue);
extern u32 data_020bcb64;
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);
#define ThreadInfo ThreadInfo
static inline void Card_WaitTask(struct CARDiCommon *common,
                                 CARDCallback callback,
                                 void *callbackArgument)
{
    int interruptState = OS_DisableInterrupts();
    while ((common->flag & CARD_STAT_BUSY) != 0) {
        func_0207a904(common->busy_q);
    }
    common->flag |= CARD_STAT_BUSY;
    common->callback = callback;
    common->callback_arg = callbackArgument;
    OS_RestoreInterrupts(interruptState);
}
extern void func_02073fcc(void);
extern void MI_StopDma(u32 channel);
extern BOOL func_02074df0(struct CARDRomStat *state);
extern void func_02074248(void (*task)(struct CARDiCommon *common));
extern void func_02074bdc(struct CARDiCommon *common);
extern struct CARDRomStat data_020c4e40 __attribute__((aligned(32)));
extern struct CARDiCommon data_020c4800;
extern u32 data_020c4e20;
extern struct OSiThreadInfoPrefix ThreadInfo;
extern struct CARDRomStat;
extern void func_02074008(void);
extern void (*func_02074a18(void))(struct CARDRomStat *state);
extern void func_020755bc(void);
extern void *func_02073f60();
extern void func_02074cf0(void);
void func_02074ab4(u32 dma, const void *source, void *destination, u32 length,
                   CARDCallback callback, void *callbackArgument, BOOL asynchronous);
void func_02074a30(void);
void *func_02074a24();

void func_02074ab4(u32 dma, const void *source, void *destination, u32 length,
                   CARDCallback callback, void *callbackArgument, BOOL asynchronous)
{
    struct CARDRomStat *const state = &data_020c4e40;
    struct CARDiCommon *const common = &data_020c4800;

    func_02073fcc();
    Card_WaitTask(common, callback, callbackArgument);

    common->dma = dma;
    common->src = (u32)source + data_020c4e20;
    common->dst = (u32)destination;
    common->len = length;
    if (dma <= MI_DMA_MAX_NUM) {
        MI_StopDma(dma);
    }

    if (func_02074df0(state)) {
        if (!asynchronous) {
            func_02074a24();
        }
    } else if (asynchronous) {
        func_02074248(func_02074bdc);
    } else {
        common->cur_th = ThreadInfo.current_thread;
        func_02074bdc(common);
    }
}

void func_02074a30(void)
{
    struct CARDiCommon *const common = &data_020c4800;

    if (common->flag == 0) {
        common->flag = CARD_STAT_INIT;
        common->src = common->dst = common->len = 0;
        common->dma = (u32)~0;
        common->callback = 0;
        common->callback_arg = 0;

        data_020c4e20 = 0;
        func_02074008();
        data_020c4e40.read_func = func_02074a18();
        func_020755bc();
    }
}

void *func_02074a24() {
    return func_02073f60();
}

void (*func_02074a18(void))(struct CARDRomStat *state) {
    return (void (*)(struct CARDRomStat *))func_02074cf0;
}
