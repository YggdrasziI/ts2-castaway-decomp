/*
 * Unit 0x02099870-0x02099C0C: heap table set up from the OS arenas, current-heap
 * stack, and the allocation entry points that operator new and delete use.
 *
 * Bounds: hypothesis for the start. __sinit_020ae384's neighbour __sinit_020ae3b0
 * (.ctor entry 0x020B6EAC) builds the two static arrays data_020c8440 and
 * data_020c8700 used here, and registers their array destructors 0x02099BE8 and
 * 0x02099BB0, which close this file's .text; 0x02099C0C starts unrelated code.
 * All users of .data 0x020BD578 and .bss 0x020C82C4-0x020D47C0 are in this range.
 * Real file name unknown.
 */

#include "game/unk_heap.h"

extern "C" void *OS_GetArenaLo(int id);
extern "C" void *OS_GetArenaHi(int id);
extern "C" void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern "C" void MIi_CpuClearFast(u32 data, void *dest, u32 size);

/* Start of the DTCM module. The DTCM heap start 0x027E0080 and the ITCM heap start
 * 0x01FFB0C0 have no relocation in the original, so they stay constants here. */
extern char data_027e0000[];

extern "C" Unk020c8440 *func_020999e8(int id);
extern "C" int func_02099a0c(void *start, u32 size, u32 alignShift, u8 inlineHeader, int id);
extern "C" void func_02099afc(int id);

static int data_020bd578 = -1;

/* Declaration order chosen to reproduce the .bss layout: mwccarm does not place
 * statics in declaration order (notes/MATCHING.md). */
static u32 data_020c82cc;
static u32 data_020c82c8;
static u32 data_020c82d0;
static void *data_020c82c4;
static u32 data_020c82e4;
static int data_020c82e0;
static void *data_020c82dc;
static int data_020c8340[64];
static Unk020c8440 *data_020c8300[16];
static void *data_020c82d4;
static Unk020c8440 data_020c8440[16];
static void *data_020c82d8;
static Unk020c8700 data_020c8700[16];

extern "C" void func_02099870(void) {
    int i;
    void *lo;
    int size;

    data_020bd578 = -1;
    for (i = 0; i < 16; i++) {
        data_020c8300[i] = 0;
    }
    for (i = 0; i < 64; i++) {
        data_020c8340[i] = -1;
    }
    func_02099afc(0);

    lo = OS_GetArenaLo(0);
    data_020c82c8 = (u32)OS_GetArenaHi(0) - (u32)lo;
    data_020c82d4 = OS_GetArenaLo(0);
    lo = OS_GetArenaLo(2);
    data_020c82e4 = (u32)OS_GetArenaHi(2) - (u32)lo;
    data_020c82c4 = OS_GetArenaLo(2);

    func_02099a0c(data_020c82d4, data_020c82c8, 2, 1, 0);
    if (data_020c82c4 != 0) {
        func_02099a0c(data_020c82c4, data_020c82e4, 2, 1, 1);
    }

    lo = (void *)0x027E0080;
    size = (int)((u32)data_027e0000 + 0x4000 - (u32)lo) - 0x1400;
    data_020c82dc = lo;
    data_020c82d0 = size;
    if (size > 0) {
        func_02099a0c(lo, size, 2, 1, 2);
    }

    lo = (void *)0x01FFB0C0;
    data_020c82d8 = lo;
    data_020c82cc = 0x02000000 - (u32)lo;
    func_02099a0c(lo, data_020c82cc, 2, 1, 3);
}

extern "C" Unk020c8440 *func_020999e8(int id) {
    if (id < 0 && id >= 16) {
        return 0;
    }
    return data_020c8300[id];
}

extern "C" int func_02099a0c(void *start, u32 size, u32 alignShift, u8 inlineHeader, int id) {
    if (id < 0 || id >= 16) {
        return -1;
    }
    if (data_020c8300[id] != 0) {
        return -1;
    }
    data_020c8300[id] = &data_020c8440[id];
    func_02099280(&data_020c8440[id], start, size, alignShift, id, inlineHeader, &data_020c8700[id]);
    return id;
}

extern "C" void func_02099aa8(int id) {
    if (id < 0 || id >= 16) {
        return;
    }
    if (func_020997ac(data_020c8300[id])) {
        data_020c8300[id] = 0;
    }
}

extern "C" int func_02099ae0(void) {
    return data_020c8340[data_020c82e0];
}

extern "C" void func_02099afc(int id) {
    if (data_020c82e0 >= 63) {
        return;
    }
    data_020c82e0++;
    data_020c8340[data_020c82e0] = id;
}

extern "C" void func_02099b28(void) {
    if (data_020c82e0 != 0) {
        data_020c82e0--;
    }
}

extern "C" void *func_02099b44(u32 size) {
    return func_02099390(func_020999e8(func_02099ae0()), size);
}

extern "C" void func_02099b60(void *ptr) {
    Unk020c8440 *heap = func_020999e8(func_020997e4(ptr));
    if (heap != 0) {
        func_02099638(heap, ptr);
    }
}

extern "C" void func_02099b84(const void *src, void *dest, u32 size) {
    MIi_CpuCopyFast(src, dest, size);
}

extern "C" void func_02099b90(u32 data, void *dest, u32 size) {
    if (data != 0) {
        MIi_CpuClearFast(data, dest, size);
    } else {
        MIi_CpuClearFast(0, dest, size);
    }
}
