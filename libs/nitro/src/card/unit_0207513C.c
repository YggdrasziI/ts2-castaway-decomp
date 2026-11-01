/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/hw.h"
#include "sdk/card.h"
#include "sdk/pxi.h"
extern s32 func_0207c4f8(PXIFifoTag tag, u32 data, BOOL error);
extern u32 data_020bcb64;
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);
static inline void CARDi_SendPxi(u32 data)
{
    while (func_0207c4f8(PXI_FIFO_TAG_FS, data, TRUE) < 0) {
    }
}
#define CARD_RESULT_SUCCESS 0
#define MROMOP_G_READ_ID        0xB8000000
#define MROMOP_G_READ_PAGE      0xB7000000
#define cardi_common data_020c4800
#define rom_stat data_02046b20
#define cardi_rom_header_addr data_020bcb64
static inline u32 CARDi_GetRomFlag(u32 flag)
{
    const u32 rom_ctrl = *(vu32 *)(cardi_rom_header_addr + 0x60);
    return (u32)((rom_ctrl & ~CARD_COMMAND_MASK) | flag |
                 CARD_READ_MODE | CARD_START | CARD_RESET_HI);
}
static inline void CARDi_SetRomOpReadPage1(u32 src)
{
    CARDi_SetRomOp((u32)(MROMOP_G_READ_PAGE | (src >> 8)), (u32)(src << 24));
}
extern struct OSThreadQueue;
extern BOOL PXI_IsCallbackReady(PXIFifoTag tag, PXIProc processor);
extern void OS_SpinWait(u32 cycles);
extern void DC_FlushRange(void *address, u32 size);
extern void DC_WaitWriteBufferEmpty(void);
extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void func_0207a904(struct OSThreadQueue *queue);
extern void DC_InvalidateRange(void *address, u32 size);
extern u32 data_020bcb64;
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

extern CARDiCommon data_020c4800;
extern CARDRomStat data_02046b20 __attribute__((aligned(32)));
BOOL func_020751d4(struct CARDiCommon *common, CARDRequest requestType, s32 retryCount);
BOOL func_0207513c(CARDRomStat *p);

BOOL func_020751d4(struct CARDiCommon *common, CARDRequest requestType, s32 retryCount)
{
    if ((common->flag & CARD_STAT_INIT_CMD) == 0) {
        common->flag |= CARD_STAT_INIT_CMD;
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_FS, PXI_PROC_ARM7)) {
            OS_SpinWait(100);
        }

        func_020751d4(common, CARD_REQ_INIT, 1);
    }
    DC_FlushRange(common->cmd, sizeof(*common->cmd));
    DC_WaitWriteBufferEmpty();

    do {
        common->command = requestType;
        common->flag |= CARD_STAT_REQ;
        CARDi_SendPxi((u32)requestType);

        switch (requestType) {
        case CARD_REQ_INIT:
            CARDi_SendPxi((u32)common->cmd);
            break;
        }

        {
            OSIntrMode interruptState = OS_DisableInterrupts();
            while ((common->flag & CARD_STAT_REQ) != 0) {
                func_0207a904(0);
            }
            OS_RestoreInterrupts(interruptState);
        }
        DC_InvalidateRange(common->cmd, sizeof(*common->cmd));
    } while ((common->cmd->result == CARD_RESULT_TIMEOUT) &&
             (--retryCount > 0));

    return common->cmd->result == CARD_RESULT_SUCCESS;
}

BOOL func_0207513c(CARDRomStat *p)
{
    CARDiCommon *c = &cardi_common;
    const u32 cur_page = CARD_ALIGN_HI_BIT(c->src);

    if (cur_page == (u32)p->cache_page) {
        const u32 mod = c->src - cur_page;
        u32 len = CARD_ROM_PAGE_SIZE - mod;

        if (len > c->len)
            len = c->len;

        MI_CpuCopy8(p->cache_buf + mod, (void *)c->dst, len);

        c->src += len;
        c->dst += len;
        c->len -= len;
    }

    return (c->len > 0);
}
