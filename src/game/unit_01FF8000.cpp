/*
 * ITCM unit 0x01FF8000-0x01FF8114: one function of the palette set
 * Unk0206fac8 (include/game/unk_palset.h, unit_0206FAC8.cpp).
 * func_01ff8000 handles one record (the first flagged one when the index is -1):
 * it reads back the texture palette into the first buffer when flag 2 is set,
 * writes one of the two buffers to the texture palette, then clears flag 1.
 *
 * Bounds: hypothesis. 0x01FF8000 is the start of the ITCM; 0x01FF8114 starts the
 * NitroSDK DMA code. The function keeps C linkage and its address as its name. No
 * data. Real file name unknown.
 */

#include "game/unk_palset.h"

extern "C" {

u16 func_01ff8000(Unk0206fac8 *set, int index) {
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
    Unk0206fac8Record *r = &set->records[index];
    if (r->flags & 2) {
        r->count = r->tex->func_0208c48c(set->colors + r->start, -1);
        set->func_02070318(r->start, r->count);
        r->flags &= ~2;
    }
    if (set->write) {
        if (set->useTinted) {
            r->tex->func_0208c50c(set->tinted + r->start, 0, r->count);
        } else {
            r->tex->func_0208c50c(set->colors + r->start, 0, r->count);
        }
    }
    r->flags &= ~1;
    set->pending--;
    return r->count;
}
}
