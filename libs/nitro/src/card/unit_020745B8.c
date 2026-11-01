/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/card.h"
extern void func_0207a904(void *queue);
extern void func_0207a884(void *queue);
extern void func_02000b60(void *symbol);
#include "sdk/pxi.h"
#include "sdk/mi.h"
extern void OS_WakeupThreadDirect(void *thread);
extern u32 data_020bcb64;
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);
#define ThreadInfo ThreadInfo
#define CARD_BACKUP_TYPE_NOT_USE        0
#define PXI_FIFO_TAG_FS 11
#define MB_TYPE_MULTIBOOT       2
#define cardi_backup_assert ((char *)0x02000b88)
#define SDK_USING_BACKUP() func_02000b60((void *)cardi_backup_assert)
extern struct { u32 initialized; struct OSThread *current; } ThreadInfo;
#define OS_GetCurrentThread() (ThreadInfo.current)
static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}
static inline void CARDi_WaitTask(CARDiCommon *p, MIDmaCallback callback, void *callback_arg)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    while ((p->flag & CARD_STAT_BUSY) != 0) {
        func_0207a904(p->busy_q);
    }

    p->flag |= CARD_STAT_BUSY;
    p->callback = callback;
    p->callback_arg = callback_arg;

    (void)OS_RestoreInterrupts(bak_psr);
}
static inline void CARDi_EndTask(CARDiCommon *p, BOOL is_own_task)
{
    const MIDmaCallback func = p->callback;
    void *const arg = p->callback_arg;

    {
        OSIntrMode bak_psr = OS_DisableInterrupts();

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
#define cardi_common data_020c4800
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_Terminate(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_WaitWriteBufferEmpty(void);
extern BOOL func_020751d4(CARDiCommon *p, int req_type, int retry_max);
extern void CARDi_SetTask(void (*task)(CARDiCommon *));
extern u32 CARD_GetBackupSectorSize(void);
extern void CARD_CheckEnabled(void);
extern CARDiCommon data_020c4800;
extern void func_02074290(CARDBackupType type);
BOOL func_020745b8 (CARDBackupType type);

BOOL func_020745b8 (CARDBackupType type)
{
	CARDiCommon *const p = &cardi_common;

	SDK_USING_BACKUP();
	if (type == CARD_BACKUP_TYPE_NOT_USE) {
		OS_TPanic("cannot specify CARD_BACKUP_TYPE_NOT_USE.");
	}

	CARD_CheckEnabled();

	CARDi_WaitTask(p, NULL, NULL);
	func_02074290(type);
	cardi_common.cur_th = OS_GetCurrentThread();
	(void)func_020751d4(p, CARD_REQ_IDENTIFY, 1);

	p->cmd->src = 0;
	p->cmd->dst = (u32)p->backup_cache_page_buf;
	p->cmd->len = 1;
	(void)func_020751d4(p, CARD_REQ_READ_BACKUP, 1);
	CARDi_EndTask(p, TRUE);
	return (p->cmd->result == CARD_RESULT_SUCCESS);
}
