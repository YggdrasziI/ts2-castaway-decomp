/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/ctrdg.h"
extern BOOL data_020c5070;
#define reg_MI_EXMEMCNT (*(vu16 *)REG_EXMEMCNT_ADDR)
#define reg_OS_IME      (*(vu16 *)REG_IME_ADDR)
#define reg_OS_PAUSE    (*(vu16 *)REG_PAUSE_ADDR)
#define PXI_FIFO_TAG_CTRDG 13
#define PXI_FIFO_SUCCESS 0
static inline void MI_SetCartridgeRomCycle1st(MICartridgeRomCycle1st c1)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_ROM1st_MASK) |
              (c1 << REG_MI_EXMEMCNT_ROM1st_SHIFT));
}
static inline MICartridgeRomCycle1st MI_GetCartridgeRomCycle1st(void)
{
    return (MICartridgeRomCycle1st)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_ROM1st_MASK) >>
                                    REG_MI_EXMEMCNT_ROM1st_SHIFT);
}
static inline void MI_SetCartridgeRomCycle2nd(MICartridgeRomCycle2nd c2)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_ROM2nd_MASK) |
              (c2 << REG_MI_EXMEMCNT_ROM2nd_SHIFT));
}
static inline MICartridgeRomCycle2nd MI_GetCartridgeRomCycle2nd(void)
{
    return (MICartridgeRomCycle2nd)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_ROM2nd_MASK) >>
                                    REG_MI_EXMEMCNT_ROM2nd_SHIFT);
}
static inline void MI_SetMainMemoryPriority(MIProcessor proc)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_EP_MASK) | (proc << REG_MI_EXMEMCNT_EP_SHIFT));
}
static inline MIProcessor MI_GetMainMemoryPriority(void)
{
    return (MIProcessor)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_EP_MASK) >> REG_MI_EXMEMCNT_EP_SHIFT);
}
static inline BOOL OS_EnableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = OS_IME_ENABLE;
    return (BOOL)prep;
}
static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}
#define CTRDGi_Work data_020c506c
#define headerBuf data_020c50a0
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern OSIrqMask OS_SetIrqMask(OSIrqMask intr);
extern void CTRDGi_LockByProcessor(int lockID, CTRDGLockByProc *info);
extern void CTRDGi_UnlockByProcessor(int lockID, CTRDGLockByProc *info);
extern void CTRDGi_ChangeLatestAccessCycle(CTRDGRomCycle *r);
extern void CTRDGi_RestoreAccessCycle(CTRDGRomCycle *r);
extern void CTRDGi_SendtoPxi(u32 data);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_FlushAll(void);
extern void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
extern int PXI_SendWordByFifo(int tag, u32 data, BOOL err);
extern void func_02075438(s32 count);
extern CTRDGWork data_020c506c;
extern CTRDGHeader data_020c50a0 __attribute__((aligned(32)));
extern BOOL func_0207584c(void);
extern void OS_Terminate(void);
void func_02075af8 (void);
void func_02075abc(int unused, int status);

void func_02075af8 (void)
{

#define isInitialized data_020c5070
	CTRDGLockByProc lockInfo;
	OSIrqMask lastIE;
	BOOL lastIME;

	if (isInitialized) {
		return;
	}

	isInitialized = TRUE;

	if (!(reg_OS_PAUSE & REG_OS_PAUSE_CHK_MASK)) {
		return;
	}

	lastIE = OS_SetIrqMask(OS_IE_SPFIFO_RECV);
	lastIME = OS_EnableIrq();

	CTRDGi_LockByProcessor(CTRDGi_Work.lockID, &lockInfo);

	{
		MIProcessor proc = MI_GetMainMemoryPriority();
		CTRDGRomCycle rc;

		CTRDGi_ChangeLatestAccessCycle(&rc);

		MI_SetMainMemoryPriority(MI_PROCESSOR_ARM9);

		DC_InvalidateRange(&((u8 *)&headerBuf)[0x80], sizeof(headerBuf) - 0x80);
		MI_DmaCopy16(1, (void *)(HW_CTRDG_ROM + 0x80),
		             &((u8 *)&headerBuf)[0x80], sizeof(headerBuf) - 0x80);

		MI_SetMainMemoryPriority(proc);
		CTRDGi_RestoreAccessCycle(&rc);
	}

	CTRDGi_UnlockByProcessor(CTRDGi_Work.lockID, &lockInfo);

	if ((*(u8 *)HW_IS_CTRDG_EXIST) || !(*(u8 *)HW_SET_CTRDG_MODULE_INFO_ONCE)) {
		int i;
		CTRDGHeader *chb = &headerBuf;
		CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();

		cip->moduleID.raw = chb->moduleID;
		for (i = 0; i < 3; i++) {
			cip->exLsiID[i] = chb->exLsiID[i];
		}
		cip->makerCode = chb->makerCode;
		cip->gameCode = chb->gameCode;

		*(u8 *)HW_IS_CTRDG_EXIST = (u8)((func_0207584c())? 1 : 0);

		(*(u8 *)HW_SET_CTRDG_MODULE_INFO_ONCE) = TRUE;
	}

	MI_CpuCopy32((void *)CTRDG_SYSROM9_NINLOGO_ADR, &headerBuf.nintendoLogo, sizeof(headerBuf.nintendoLogo));
	DC_FlushAll();

	CTRDGi_SendtoPxi(CTRDG_PXI_COMMAND_INIT_MODULE_INFO | (((u32) & headerBuf - HW_MAIN_MEM) >> 5) << CTRDG_PXI_COMMAND_PARAM_SHIFT);

	while (CTRDGi_Work.subpInitialized != TRUE) {
		func_02075438(1);
	}

	(void)OS_RestoreIrq(lastIME);
	(void)OS_SetIrqMask(lastIE);

}

void func_02075abc(int unused, int status) {
    if ((status & 0x3f) == 1) {
        data_020c506c.subpInitialized = 1;
        return;
    }
    OS_Terminate();
}
