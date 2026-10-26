/*
 * ITCM unit 0x01FF8000-0x01FF8114: one function of the palette set of
 * 0x0206FD2C... (main module, still assembly). The set keeps two palette buffers,
 * an array of 0x14-byte records (texture entry of include/game/unk_texture.h,
 * start and count in the buffer, flags) and a count of the records to upload.
 * func_01ff8000 handles one record (the first flagged one when the index is -1):
 * it reads back the texture palette into the first buffer when flag 2 is set,
 * writes one of the two buffers to the texture palette, then clears flag 1.
 *
 * Bounds: hypothesis. 0x01FF8000 is the start of the ITCM; 0x01FF8114 starts the
 * NitroSDK DMA code. The function keeps C linkage and its address as its name. No
 * data. Real file name unknown.
 */

#include "game/unk_texture.h"

/* A record of the palette set (0x14 bytes). */
struct Unk01ff8000Record {
    Unk0208c050 *tex;
    u32 unk4;
    u32 unk8;
    u16 start;
    u16 count;
    u32 flags;
};

/* The palette set (layout of what this function uses). */
struct Unk01ff8000 {
    u16 *buf0;
    u16 *buf1;
    u32 unk8;
    u32 unkC;
    Unk01ff8000Record *records;
    u32 recordCount;
    u32 unk18;
    u32 unk1c;
    int pending;
    u32 unk24;
    u32 unk28;
    u8 useBuf1;
    u8 write;
};

extern "C" {
void func_02070318(Unk01ff8000 *set, u32 start, u32 count);

u16 func_01ff8000(Unk01ff8000 *set, int index) {
    if (index == -1) {
        for (u32 i = 0; i < set->recordCount; i++) {
            if (set->records[i].flags & 1) {
                index = i;
                break;
            }
        }
    }
    if (index == -1) {
        return 0;
    }
    Unk01ff8000Record *r = &set->records[index];
    if (r->flags & 2) {
        r->count = r->tex->func_0208c48c(set->buf0 + r->start, -1);
        func_02070318(set, r->start, r->count);
        r->flags &= ~2;
    }
    if (set->write) {
        if (set->useBuf1) {
            r->tex->func_0208c50c(set->buf1 + r->start, 0, r->count);
        } else {
            r->tex->func_0208c50c(set->buf0 + r->start, 0, r->count);
        }
    }
    r->flags &= ~1;
    set->pending--;
    return r->count;
}
}
