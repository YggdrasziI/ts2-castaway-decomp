/*
 * NitroSDK OS_InitLock (0x0207A4E4); khdays (CC0) OS_InitLock.c, retyped for this ROM. File bounds
 * are a hypothesis.
 */
#pragma force_active on

#include "sdk/types.h"

extern void *func_0207a480(int id, void *word, void *callback);
extern void *func_0207a3e0(int id, void *word, void *callback);
extern void func_02075438(u32 count);
extern void MI_CpuFillU32(u32 value, void *dst, u32 size);

extern u32 data_020c5794;

typedef struct {
    u32 lockFlag;
    u16 ownerId;
    u16 extension;
} OSLockWord;

#define OSi_LockWord ((OSLockWord *)0x027ffff0)
#define OSi_LockIdFlags ((u32 *)0x027fffb0)
#define REG_EXMEM_CNT (*(vu16 *)0x04000204)

void func_0207a4e4(void) {
    if (data_020c5794 != 0) {
        return;
    }
    data_020c5794 = 1;
    OSi_LockWord->lockFlag = 0;
    func_0207a480(0x7e, OSi_LockWord, 0);

    {
        OSLockWord *w = OSi_LockWord;

        while (w->extension != 0) {
            func_02075438(0x400);
        }
    }

    OSi_LockIdFlags[0] = 0xffffffff;
    OSi_LockIdFlags[1] = 0xffff0000;
    MI_CpuFillU32(0, OSi_LockIdFlags + 4, 40);

    REG_EXMEM_CNT |= 0x800;
    REG_EXMEM_CNT |= 0x80;

    func_0207a3e0(0x7e, OSi_LockWord, 0);
    func_0207a480(0x7f, OSi_LockWord, 0);
}
