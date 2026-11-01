/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/card.h"
extern void func_0207a904(void *queue);
extern void func_0207a884(void *queue);
extern void func_02000b60(void *symbol);
#include "sdk/pxi.h"
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
extern void func_02074248(void (*task)(struct CARDiCommon *common));
extern void func_0207481c(struct CARDiCommon *common);
extern struct CARDiCommon data_020c4800;
extern struct OSiThreadInfoPrefix ThreadInfo;
BOOL func_02074728(u32 src, u32 dst, u32 len, CARDCallback callback,
                    void *callbackArgument, BOOL asynchronous,
                    s32 reqType, s32 reqRetry, s32 reqMode);

BOOL func_02074728(u32 src, u32 dst, u32 len, CARDCallback callback,
                    void *callbackArgument, BOOL asynchronous,
                    s32 reqType, s32 reqRetry, s32 reqMode)
{
    struct CARDiCommon *const common = &data_020c4800;

    func_02000b60((void *)0x02000b88);
    Card_WaitTask(common, callback, callbackArgument);

    common->src = src;
    common->dst = dst;
    common->len = len;
    common->req_type = reqType;
    common->req_retry = reqRetry;
    common->req_mode = reqMode;

    if (asynchronous) {
        func_02074248(func_0207481c);
        return 1;
    }

    data_020c4800.cur_th = ThreadInfo.current_thread;
    func_0207481c(common);
    return (common->cmd->result == 0);
}
