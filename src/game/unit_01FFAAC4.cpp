/*
 * ITCM unit 0x01FFAAC4-0x01FFB0BC: VRAM transfers of the texture manager and of the
 * object (OAM) managers. func_01ffaac4 sends the textures in use this frame (the
 * slots of the manager, include/game/unk_texture.h) to the texture and palette
 * VRAM and releases the slots. func_01ffab9c copies the tiles of the current frame
 * of an object entry (include/game/unk_oam.h) into its block, through the two tile
 * copies func_01ffaca0 (4 bits per pixel) and func_01ffad44 (8 bits per pixel)
 * that flip a tile horizontally (bit 0) or vertically (bit 1). func_01ffadf8
 * writes the OAM of a manager: the affine parameters, the released entries, then
 * the attributes of the visible entries.
 *
 * Bounds: hypothesis. 0x01FFAAC4 follows the transform set code
 * (unit_01FFA2D0.cpp); 0x01FFB0BC is the end of the ITCM code. The two tile copies
 * are hand-written assembly (registers saved inside a branch, register
 * post-indexed loads). The functions keep C linkage and their addresses as names.
 * No data. Real file name unknown.
 */

#include "game/unk_texture.h"
#include "game/unk_resource.h"
#include "game/unk_oam.h"

/* A word of the tile table of a frame: tile index and flip bits. */
struct Unk01ffab9cTile {
    u32 index : 16;
    u32 unk16 : 10;
    u32 flip : 2;
    u32 unk28 : 4;
};

extern "C" {
void func_0207914c();
void func_020791a4(const void *data, u32 offset, u32 size);
void func_02079218();
void func_02079260();
void func_020792d0(const void *data, u32 offset, u32 size);
void func_02079434();

void func_01ffaca0(const u32 *src, u32 *dst, u32 flip);
void func_01ffad44(const u32 *src, u32 *dst, u32 flip);
}

static inline bool func_isDouble(const Unk0208f8b0 *e) {
    return (e->unk8 & 0x200) != 0;
}

static inline bool func_isVisible(Unk0208f8b0 *e) {
    int x = (int)e->unk0 >> 12;
    int y = (int)e->unk4 >> 12;
    int w = 1 << (e->unk10_0 + 3);
    int h = 1 << (e->unk10_2 + 3);

    if (func_isDouble(e)) {
        y -= h >> 1;
        h <<= 1;
        if (y < -83 || y + h > 274) {
            return false;
        }
        x -= w >> 1;
        w <<= 1;
    }
    if (x >= 256 || y >= 192 || x + w <= 0 || y + h <= 0) {
        return false;
    }
    return true;
}

extern "C" {

void func_01ffaac4(Unk020c7f48 *m) {
    int i;

    if (m->entries == 0) {
        return;
    }
    func_02079434();
    func_02079218();
    for (i = 0; i < m->slotCount; i++) {
        Unk0208c630 *s = &m->slots[i];
        if (s->texData != 0) {
            func_020792d0(s->texData, s->texOffset, s->texSize);
        }
        s = &m->slots[i];
        if (s->plttData != 0) {
            func_020791a4(s->plttData, s->plttOffset, s->plttSize);
        }
        Unk0208c050 *entry = m->slots[i].entry;
        if (entry != 0) {
            entry->refs--;
        }
        m->slots[i] = Unk0208c630();
    }
    func_0207914c();
    func_02079260();
    m->slotCount = 0;
}

void func_01ffab9c(Unk0208f8b0 *e, int heap) {
    if (e->unk20 == 0 && !e->func_0208fe08(heap)) {
        return;
    }
    if (e->unk14 == e->unk18 || e->unk1c == 0) {
        return;
    }
    const u32 *tiles = (const u32 *)e->unk1c->func_020951e4(e->unk18);
    const Unk01ffab9cTile *t = (const Unk01ffab9cTile *)e->unk1c->func_020952b0(e->unk18);
    int n = ((1 << (e->unk10_0 + 3)) >> 3) * ((1 << (e->unk10_2 + 3)) >> 3);
    u32 *dst = (u32 *)e->unk20;
    int shift = (e->unk8 & 0x2000) ? 6 : 5;
    while (n-- != 0) {
        u32 idx = t->index;
        u32 flip = t->flip;
        const u32 *src = tiles + (idx << (shift - 2));
        if (shift == 6) {
            func_01ffad44(src, dst, flip);
        } else {
            func_01ffaca0(src, dst, flip);
        }
        dst += 1 << (shift - 2);
        t++;
    }
    e->unk14 = e->unk18;
}

asm void func_01ffaca0(register const u32 *src, register u32 *dst, register u32 flip)
{
    tst     r2, #1
    bne     @hflip
    tst     r2, #2
    bne     @vflip
    stmdb   sp!, {r4}
    ldmia   r0!, {r2, r3, r4, ip}
    stmia   r1!, {r2, r3, r4, ip}
    ldmia   r0!, {r2, r3, r4, ip}
    stmia   r1!, {r2, r3, r4, ip}
    ldmia   sp!, {r4}
    bx      lr
@vflip:
    add     r0, r0, #0x1c
    mov     r3, #8
@vloop:
    ldr     r2, [r0], #-4
    str     r2, [r1], #4
    subs    r3, r3, #1
    bne     @vloop
    bx      lr
@hflip:
    stmdb   sp!, {r4, r5, r6}
    mov     r4, #0xf
    orr     r4, r4, r4, lsl #16
    mov     r3, #8
    mov     r6, #4
    tst     r2, #2
    subne   r6, r6, #8
    addne   r0, r0, #0x1c
@hloop:
    ldr     r2, [r0], r6
    mov     r2, r2, ror #16
    and     r5, r2, r4, lsl #4
    mov     ip, r5, lsl #4
    and     r5, r2, r4, lsl #8
    orr     ip, ip, r5, lsr #4
    and     r5, r2, r4, lsl #12
    orr     ip, ip, r5, lsr #12
    and     r5, r2, r4
    orr     ip, ip, r5, lsl #12
    str     ip, [r1], #4
    subs    r3, r3, #1
    bne     @hloop
    ldmia   sp!, {r4, r5, r6}
    bx      lr
}

asm void func_01ffad44(register const u32 *src, register u32 *dst, register u32 flip)
{
    tst     r2, #1
    bne     @hflip
    tst     r2, #2
    bne     @vflip
    stmdb   sp!, {r4, r5, r6}
    ldmia   r0!, {r2, r3, r4, r5, r6, ip}
    stmia   r1!, {r2, r3, r4, r5, r6, ip}
    ldmia   r0!, {r2, r3, r4, r5, r6, ip}
    stmia   r1!, {r2, r3, r4, r5, r6, ip}
    ldmia   r0!, {r2, r3, r4, r5}
    stmia   r1!, {r2, r3, r4, r5}
    ldmia   sp!, {r4, r5, r6}
    bx      lr
@vflip:
    add     r0, r0, #0x40
    mov     ip, #8
@vloop:
    ldmdb   r0!, {r2, r3}
    stmia   r1!, {r2, r3}
    subs    ip, ip, #1
    bne     @vloop
    bx      lr
@hflip:
    stmdb   sp!, {r4, r5, r6}
    mov     r3, #8
    mov     r5, #0xff
    orr     r5, r5, r5, lsl #16
    mov     ip, #8
    tst     r2, #2
    addne   r0, r0, #0x38
    subne   ip, ip, #0x10
@hloop:
    ldr     r4, [r0, #0]
    and     r6, r4, r5
    mov     r6, r6, ror #8
    and     r4, r4, r5, lsl #8
    orr     r6, r6, r4, ror #24
    str     r6, [r1, #4]
    ldr     r4, [r0, #4]
    add     r0, r0, ip
    and     r6, r4, r5
    mov     r6, r6, ror #8
    and     r4, r4, r5, lsl #8
    orr     r6, r6, r4, ror #24
    str     r6, [r1], #8
    subs    r3, r3, #1
    bne     @hloop
    ldmia   sp!, {r4, r5, r6}
    bx      lr
}

static inline void func_writeOam(u32 *o, Unk0208f8b0 *e, u16 v) {
    int x = (int)e->unk0 >> 12;
    int y = (int)e->unk4 >> 12;
    if (func_isDouble(e)) {
        x -= (1 << (e->unk10_0 + 3)) >> 1;
        y -= (1 << (e->unk10_2 + 3)) >> 1;
    }
    o[0] = e->unk8 | ((y & 0xff) | ((x & 0x1ff) << 16));
    o[1] = e->unkC | (v << 16);
}

void func_01ffadf8(Unk020916a4 *mgr) {
    Unk020916a4Node *p;
    Unk020916a4Affine *a;

    for (int i = 0; i < 0x80; i++) {
        u16 v = (&mgr->affines[i >> 2].pa)[i & 3];
        u32 *o = &((u32 *)mgr->oam)[i * 2];
        o[0] = 0x010000c0;
        o[1] = v << 16;
    }
    while (mgr->pending != 0) {
        Unk0208f8b0 *e = &mgr->entries[mgr->pending->index];
        if (e->func_0208fcf0()) {
            mgr->func_0209241c(e);
        }
        e->func_0208fa14(mgr->unk820);
        Unk020916a4Node *q = mgr->pending;
        mgr->pending = q->next;
        mgr->count--;
        q->next = mgr->free;
        mgr->free = q;
    }
    p = mgr->used;
    a = mgr->affines;
    for (int i = 0; i < mgr->count; i++) {
        Unk0208f8b0 *e = &mgr->entries[p->index];
        if (func_isVisible(e)) {
            bool same = true;
            if (e->unk18 != -1 && e->unk14 != e->unk18) {
                same = false;
            }
            if (!same) {
                func_01ffab9c(e, mgr->unk820);
            }
            func_writeOam(&((u32 *)mgr->oam)[i * 2], e, (&a->pa)[i & 3]);
        }
        if ((i & 3) == 3) {
            a++;
        }
        p = p->next;
    }
}

}
