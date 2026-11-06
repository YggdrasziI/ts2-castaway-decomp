/* NitroSDK; khdays (CC0) per-function source for func_02074728; func_0207481c (backup stream request task) written from the ROM with the SDK structure names. Merged in reverse address order. File bounds are a hypothesis. */
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
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_WaitWriteBufferEmpty(void);
extern BOOL func_020751d4(struct CARDiCommon *p, int req_type, int retry_max);
extern u32 func_02074700(void);
extern void OS_WakeupThreadDirect(void *thread);

static inline void CARDi_EndTask(struct CARDiCommon *p, BOOL is_own_task)
{
    const CARDCallback func = p->callback;
    void *const arg = p->callback_arg;

    {
        int bak_psr = OS_DisableInterrupts();

        p->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
        func_0207a884(p->busy_q);

        if ((p->flag & CARD_STAT_RECV) != 0) {
            OS_WakeupThreadDirect(p->thread);
        }

        (void)OS_RestoreInterrupts(bak_psr);
    }

    if (is_own_task && func) {
        (*func)(arg);
    }
}

void func_0207481c(struct CARDiCommon *p)
{
    const CARDRequest req_type = p->req_type;
    const int req_mode = p->req_mode;
    const int retry_count = p->req_retry;
    u32 size = sizeof(p->backup_cache_page_buf);

    func_02000b60((void *)0x02000b88);
    if (req_type == CARD_REQ_ERASE_SECTOR_BACKUP) {
        size = func_02074700();
    }

    for (;;) {
        const u32 len = (size < p->len) ? size : p->len;

        p->cmd->len = len;
        if ((p->flag & CARD_STAT_CANCEL) != 0) {
            p->flag &= ~CARD_STAT_CANCEL;
            p->cmd->result = CARD_RESULT_CANCELED;
            break;
        }
        switch (req_mode) {
        case CARD_REQUEST_MODE_RECV:
            DC_InvalidateRange(p->backup_cache_page_buf, len);
            p->cmd->src = p->src;
            p->cmd->dst = (u32)p->backup_cache_page_buf;
            break;
        case CARD_REQUEST_MODE_SEND:
        case CARD_REQUEST_MODE_SEND_VERIFY:
            MI_CpuCopy8((const void *)p->src, p->backup_cache_page_buf, len);
            DC_FlushRange(p->backup_cache_page_buf, len);
            DC_WaitWriteBufferEmpty();
            p->cmd->src = (u32)p->backup_cache_page_buf;
            p->cmd->dst = p->dst;
            break;
        case CARD_REQUEST_MODE_SPECIAL:
            p->cmd->src = p->src;
            p->cmd->dst = p->dst;
            break;
        }
        if (!func_020751d4(p, req_type, retry_count)) {
            break;
        }
        if (req_mode == CARD_REQUEST_MODE_SEND_VERIFY) {
            if (!func_020751d4(p, CARD_REQ_VERIFY_BACKUP, 1)) {
                break;
            }
        } else if (req_mode == CARD_REQUEST_MODE_RECV) {
            MI_CpuCopy8(p->backup_cache_page_buf, (void *)p->dst, len);
        }
        p->src += len;
        p->dst += len;
        p->len -= len;
        if (p->len == 0) {
            break;
        }
    }
    CARDi_EndTask(p, TRUE);
}
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
