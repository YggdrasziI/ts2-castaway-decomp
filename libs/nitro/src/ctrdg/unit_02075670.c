/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/ctrdg.h"
#define reg_MI_EXMEMCNT (*(vu16 *)REG_EXMEMCNT_ADDR)
#define reg_OS_IME      (*(vu16 *)REG_IME_ADDR)
#define reg_OS_PAUSE    (*(vu16 *)REG_PAUSE_ADDR)
#define PXI_FIFO_TAG_CTRDG 13
#define PXI_FIFO_SUCCESS 0
#define SVC_WaitByLoop WaitByLoop
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
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern OSIrqMask OS_SetIrqMask(OSIrqMask intr);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_FlushAll(void);
extern void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
extern int PXI_SendWordByFifo(int tag, u32 data, BOOL err);
extern void WaitByLoop(s32 count);
extern unsigned short func_0207a280(void *lock);
extern int func_0207a320(int owner);
extern void func_02075438(int count);
extern void func_0207a21c();
extern int func_0207c4f8(int tag, u32 data, BOOL err);
extern int CTRDG_IsOptionCartridge(void);
extern void OS_SetDPermissionsForProtectionRegion(int region, int perms);
extern int data_020c5068;
void CTRDGi_ChangeLatestAccessCycle(int *saved);
void CTRDGi_RestoreAccessCycle (CTRDGRomCycle *r);
void CTRDGi_LockByProcessor(int owner, char *out);
void CTRDGi_UnlockByProcessor(int id, int *ctx);
extern void func_02075438(int count);
void CTRDGi_SendtoPxi (u32 data);
void CTRDG_Enable(int enable);

void CTRDGi_ChangeLatestAccessCycle(int *saved) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    saved[0] = (*exmemcnt & 0xc) >> 2;
    saved[1] = (*exmemcnt & 0x10) >> 4;
    *exmemcnt = (unsigned short)((*exmemcnt & ~0xc) | 0xc);
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x10);
}

void CTRDGi_RestoreAccessCycle (CTRDGRomCycle *r)
{
	MI_SetCartridgeRomCycle1st(r->c1);
	MI_SetCartridgeRomCycle2nd(r->c2);
}

void CTRDGi_LockByProcessor(int owner, char *out) {
    for (;;) {
        *(int *)(out + 4) = OS_DisableInterrupts();
        *(int *)out = func_0207a280((void *)0x027fffe8) & 0x40;
        if (*(int *)out != 0) {
            return;
        }
        if (func_0207a320(owner) == 0) {
            return;
        }
        OS_RestoreInterrupts(*(int *)(out + 4));
        func_02075438(1);
    }
}

void CTRDGi_UnlockByProcessor(int id, int *ctx) {
    if (ctx[0] == 0) {
        func_0207a21c(id);
    }
    OS_RestoreInterrupts(ctx[1]);
}

void CTRDGi_SendtoPxi (u32 data)
{
	while (func_0207c4f8(PXI_FIFO_TAG_CTRDG, data, FALSE) != PXI_FIFO_SUCCESS) {
		func_02075438(1);
	}
}

void CTRDG_Enable(int enable) {
    int enabled = OS_DisableInterrupts();
    int perms;
    data_020c5068 = enable;
    if (CTRDG_IsOptionCartridge() == 0) {
        if (enable != 0) {
            perms = 0x1000;
        } else {
            perms = 0x5000;
        }
        OS_SetDPermissionsForProtectionRegion(0xf000, perms);
    }
    OS_RestoreInterrupts(enabled);
}
