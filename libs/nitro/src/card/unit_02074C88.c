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
#define cardi_common data_020464e0
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
extern u32 data_020bcb64;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void func_0207509c(u32 cmd1, u32 cmd2);
extern CARDiCommon data_020464e0;
extern CARDRomStat data_02046b20 __attribute__((aligned(32)));
u32 func_02074c88(void);

u32 func_02074c88(void)
{
    func_0207509c(MROMOP_G_READ_ID, 0);
    *(vu32 *)REG_CARDCNT = (u32)(CARDi_GetRomFlag(CARD_COMMAND_ID) & ~CARD_LATENCY1_MASK);
    while (!(*(vu32 *)REG_CARDCNT & CARD_DATA_READY)) {
    }
    return reg_CARD_DATA;
}
