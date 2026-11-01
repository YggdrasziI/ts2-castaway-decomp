/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on


#include "sdk/types.h"
#include "sdk/os.h"

enum {
    CARD_RESULT_SUCCESS = 0,
    CARD_STAT_BUSY = 1 << 2,
    CARD_STAT_TASK = 1 << 3,
    CARD_STAT_RECV = 1 << 4,
    CARD_STAT_CANCEL = 1 << 6,
    CARD_ROM_PAGE_SIZE = 512
};

typedef void (*CARDCallback)(void *argument);

struct CARDiCommandArg {
    int result;
};

struct CARDiCommon {
    struct CARDiCommandArg *cmd;
    s32 command;
    volatile s32 lock_owner;
    volatile s32 lock_ref;
    u8 lock_queue[8];
    s32 lock_target;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    s32 req_type;
    s32 req_retry;
    s32 req_mode;
    CARDCallback callback;
    void *callback_arg;
    void (*task_func)(struct CARDiCommon *common);
    u8 thread[0xc8];
    u8 busy_q[8];
    volatile u32 flag;
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
};

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_StopDma(u32 channel);
extern void OS_DisableIrqMask(u32 mask);
extern void OS_ResetRequestIrqMask(u32 mask);
extern u32 func_02074c88(void);
extern void func_02075444(u32 id);
extern void func_0207a884(void *queue);
extern void OS_WakeupThreadDirect(void *thread);
extern void func_02075044(void);
extern struct CARDiCommon data_020c4800;
extern char data_020c4e40[];

static inline BOOL Card_AdvanceReadPage(struct CARDRomStat *state)
{
#pragma unused(state)
    struct CARDiCommon *common = &data_020c4800;
    common->src += CARD_ROM_PAGE_SIZE;
    common->dst += CARD_ROM_PAGE_SIZE;
    common->len -= CARD_ROM_PAGE_SIZE;
    return common->len > 0;
}

void func_02074f64(void)
{
    struct CARDRomStat *state = (struct CARDRomStat *)data_020c4e40;
    struct CARDiCommon *common = &data_020c4800;
    CARDCallback callback;
    void *callbackArgument;
    int interruptState;

    MI_StopDma(common->dma);
    if (!Card_AdvanceReadPage(state)) {
        OS_DisableIrqMask(OS_IE_CARD_DATA);
        OS_ResetRequestIrqMask(OS_IE_CARD_DATA);
        common = (struct CARDiCommon *)(char *)(void *)&data_020c4800;
        func_02075444(func_02074c88());
        common->cmd->result = CARD_RESULT_SUCCESS;
        callback = common->callback;
        callbackArgument = common->callback_arg;
        interruptState = OS_DisableInterrupts();
        common->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
        func_0207a884(common->busy_q);
        if ((common->flag & CARD_STAT_RECV) != 0) {
            OS_WakeupThreadDirect(common->thread);
        }
        OS_RestoreInterrupts(interruptState);
        if (callback == 0) {
            return;
        }
        callback(callbackArgument);
    } else {
        func_02075044();
    }
}
