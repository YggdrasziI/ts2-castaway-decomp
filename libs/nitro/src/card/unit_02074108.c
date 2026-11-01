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
extern struct CARDiCommon data_020c4800;
extern int func_0207a694(void *target, int newval);
extern void func_0207a850(void *thread);
extern u32 data_020bcb64;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0207a904(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);

extern CARDiCommon data_020c4800 __attribute__((aligned(32)));
extern void OS_SleepThread(OSThreadQueue *queue);
extern void func_0207a884(OSThreadQueue *queue);
void func_02074248(void (*task)(struct CARDiCommon *common));
void func_020741ac(CARDiOwner owner, CARDTargetMode target);
void func_02074108(CARDiOwner owner, CARDTargetMode target);

void func_02074248(void (*task)(struct CARDiCommon *common))
{
    struct CARDiCommon *const common = &data_020c4800;

    func_0207a694(common->thread, common->priority);
    common->cur_th = (struct OSThread *)common->thread;
    common->task_func = task;
    common->flag |= 8;
    func_0207a850(common->thread);
}

void func_020741ac(CARDiOwner owner, CARDTargetMode target)
{
    CARDiCommon *const p = &cardi_common;
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if (p->lock_owner == owner) {
        if (p->lock_target != target) {
            OS_TPanic("card-lock : can not reuse same ID for locking without unlocking!");
        }
    } else {
        while (p->lock_owner != OS_LOCK_ID_ERROR)
            func_0207a904(p->lock_queue);
        p->lock_owner = owner;
        p->lock_target = target;
    }

    ++p->lock_ref;
    p->cmd->result = CARD_RESULT_SUCCESS;
    (void)OS_RestoreInterrupts(bak_psr);
}

void func_02074108(CARDiOwner owner, CARDTargetMode target)
{
    CARDiCommon *p = &cardi_common;
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if ((p->lock_owner != owner) || !p->lock_ref) {
        OS_Panic("card-unlock : specified ID for unlocking is not locking one!");
    } else {
        if (p->lock_target != target) {
            OS_Panic("card-unlock : locking target and unlocking one are different!");
        }
        if (!--p->lock_ref) {
            p->lock_owner = OS_LOCK_ID_ERROR;
            p->lock_target = CARD_TARGET_NONE;
            func_0207a884(p->lock_queue);
        }
    }
    p->cmd->result = CARD_RESULT_SUCCESS;
    (void)OS_RestoreInterrupts(bak_psr);
}
