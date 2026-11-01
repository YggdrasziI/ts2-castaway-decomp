/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/hw.h"
#include "sdk/os.h"

extern void func_02075438(unsigned count);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int OS_DisableInterrupts_IrqAndFiq(void);
extern void OS_RestoreInterrupts_IrqAndFiq(int state);
extern int MI_SwapWord(unsigned short id, void *lock);
int func_0207a490(unsigned short id, char *lock, void (*onLock)(void), int fiq);
int func_0207a480(unsigned short a, void *b, void *c);
int func_0207a3f0(unsigned short id, char *lock, void (*onUnlock)(void), int fiq);
int func_0207a3e0(unsigned short a, void *b, void *c);
int func_0207a360(unsigned short id, char *lock, void (*onLock)(void), int fiq);
int func_0207a340(unsigned short id);
int func_0207a320(unsigned short id);
void OSi_AllocateCartridgeBus(void);
void OSi_FreeCartridgeBus(void);
void func_0207a2d4(u16 lockId);
void func_0207a2b8(u16 lockId);
void OSi_AllocateCardBus(void);
void OSi_FreeCardBus(void);
unsigned short func_0207a280(unsigned short *p);

int func_0207a490(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int prev = func_0207a360(id, lock, onLock, fiq);

    while (prev > 0) {
        func_02075438(0x400);
        prev = func_0207a360(id, lock, onLock, fiq);
    }
    return prev;
}

int func_0207a480(unsigned short a, void *b, void *c) {
    return func_0207a490(a, b, c, 0);
}

int func_0207a3f0(unsigned short id, char *lock, void (*onUnlock)(void), int fiq) {
    int enabled;
    if (id != *(unsigned short *)(lock + 4)) {
        return ~1;
    }
    if (fiq != 0) {
        enabled = OS_DisableInterrupts_IrqAndFiq();
    } else {
        enabled = OS_DisableInterrupts();
    }
    *(unsigned short *)(lock + 4) = 0;
    if (onUnlock != 0) {
        onUnlock();
    }
    *(int *)lock = 0;
    if (fiq != 0) {
        OS_RestoreInterrupts_IrqAndFiq(enabled);
    } else {
        OS_RestoreInterrupts(enabled);
    }
    return 0;
}

int func_0207a3e0(unsigned short a, void *b, void *c) {
    return func_0207a3f0(a, b, c, 0);
}

int func_0207a360(unsigned short id, char *lock, void (*onLock)(void), int fiq) {
    int enabled;
    int prev;
    if (fiq != 0) {
        enabled = OS_DisableInterrupts_IrqAndFiq();
    } else {
        enabled = OS_DisableInterrupts();
    }
    prev = MI_SwapWord(id, lock);
    if (prev == 0) {
        if (onLock != 0) {
            onLock();
        }
        *(unsigned short *)(lock + 4) = id;
    }
    if (fiq != 0) {
        OS_RestoreInterrupts_IrqAndFiq(enabled);
    } else {
        OS_RestoreInterrupts(enabled);
    }
    return prev;
}

int func_0207a340(unsigned short id) {
    return func_0207a3f0(id, (void *)0x27fffe8, OSi_FreeCartridgeBus, 1);
}

int func_0207a320(unsigned short id) {
    return func_0207a360(id, (void *)0x27fffe8, OSi_AllocateCartridgeBus, 1);
}

void OSi_AllocateCartridgeBus(void)
{
    REG_EXMEM_CNT &= ~0x0080;
}

void OSi_FreeCartridgeBus(void)
{
    REG_EXMEM_CNT |= 0x0080;
}

void func_0207a2d4(u16 lockId)
{
    func_0207a480(lockId, OSi_CardLock, OSi_AllocateCardBus);
}

void func_0207a2b8(u16 lockId)
{
    func_0207a3e0(lockId, OSi_CardLock, OSi_FreeCardBus);
}

void OSi_AllocateCardBus(void) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x800);
}

void OSi_FreeCardBus(void)
{
    REG_EXMEM_CNT |= 0x0800;
}

unsigned short func_0207a280(unsigned short *p){ return p[2]; }
