/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/hw.h"
#include "sdk/card.h"
#include "sdk/pxi.h"
extern u32 data_020bcb64;
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);
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
#define PXI_FIFO_TAG_CARD 14
#define PXI_FIFO_SUCCESS 0
extern u32 data_020bcb64;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

extern CARDiCommon data_020c4800;
extern int func_0207c4f8(int tag, u32 data, BOOL err);
extern void func_02075438(s32 count);
extern struct OSThread;
extern void OS_WakeupThreadDirect(struct OSThread *thread);
extern struct CARDiCommon data_020c4800;
void func_020753d4(u32 data, u32 wait);
void func_02075384(PXIFifoTag tag, u32 data, BOOL error);

void func_020753d4(u32 data, u32 wait)
{
    while (func_0207c4f8(PXI_FIFO_TAG_CARD, data, FALSE) != PXI_FIFO_SUCCESS) {
        func_02075438((s32)wait);
    }
}

void func_02075384(PXIFifoTag tag, u32 data, BOOL error)
{
#pragma unused(data)
    if ((tag == PXI_FIFO_TAG_FS) && error) {
        struct CARDiCommon *const common = &data_020c4800;
        common->flag &= ~CARD_STAT_REQ;
        OS_WakeupThreadDirect(common->cur_th);
    }
}
