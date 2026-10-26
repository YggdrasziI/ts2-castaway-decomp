/*
 * ITCM unit 0x01FFA2D0-0x01FFAAC4: functions of the transform set (Unk0208be3c,
 * include/game/unk_xform.h). They copy or blend the sampled values of an
 * animation (Unk020897c0, include/game/unk_anim.h) into the entries, blend two
 * sets, build the entry matrices (with the parent of each item, read from block
 * 0x12 of the file) and the products with the matrices of that block, and find an
 * entry by index or by name.
 *
 * Bounds: hypothesis. 0x01FFA2D0 follows the pool drawing code
 * (unit_01FF9924.cpp); from 0x01FFAAC4 the code works on another object. The
 * functions keep C linkage and their addresses as names. No data. Real file name
 * unknown.
 */

#include "game/unk_file.h"
#include "game/unk_xform.h"
#include "game/unk_anim.h"

class Unk02095d1c : public Unk0209487c {
public:
    void *func_02095d98();
};

/* A record of block 0x12 of the file (0x58 bytes). */
struct Unk01ffa2d0Record {
    int parent;
    u32 mask;
    Unk02098094 mtx;
    u32 name[4];
};

extern "C" int func_0209a474(const u32 *a, const u32 *b);

static inline void func_setPos(Unk0208be3cPos &p, const Unk02098ff0 &v) {
    p = (const Unk0208be3cPos &)v;
}

static inline Unk02098094 func_mul(const Unk02098094 &a, const Unk02098094 &b) {
    Unk02098094 m;
    m.func_0209873c(a, b);
    return m;
}

static inline Unk02098ff0 func_scale(const Unk02098ff0 &v, int t) {
    return Unk02098ff0(func_fxmul(v.x, t), func_fxmul(v.y, t), func_fxmul(v.z, t));
}

extern "C" {
void func_01ffa2d0(Unk0208be3c *xform, Unk020897c0 *anim) {
    int count = xform->count;
    if (count == 0) {
        return;
    }
    if (count != anim->func_01ff8a60()) {
        return;
    }
    Unk020897c0Elem *src = anim->func_01ff8a4c();
    Unk0208be3cEntry *entry = xform->entries;
    while (count-- != 0) {
        func_setPos(entry->pos, src->pos.v);
        entry->rot = src->rot;
        src++;
        entry++;
    }
    xform->unk10 |= 1;
}

void func_01ffa364(Unk0208be3c *xform, Unk020897c0 *anim, int t, u32 mask) {
    int count = xform->count;
    if (count == 0) {
        return;
    }
    if (count != anim->func_01ff8a60()) {
        return;
    }
    if (xform->file == 0) {
        return;
    }
    if (t <= 0) {
        return;
    }
    if (t > 0x1000) {
        t = 0x1000;
    }
    if (!(xform->unk10 & 1)) {
        func_01ffa2d0(xform, anim);
        return;
    }
    Unk01ffa2d0Record *rec = (Unk01ffa2d0Record *)xform->file->func_02095d98();
    Unk020897c0Elem *src = anim->func_01ff8a4c();
    Unk0208be3cEntry *entry = xform->entries;
    while (count-- != 0) {
        if (rec->mask & mask) {
            func_setPos(entry->pos,
                        entry->pos.v.func_0209911c(func_scale(src->pos.v.func_02099150(entry->pos.v), t)));
            entry->rot = entry->rot.func_02098a5c(src->rot, t);
        }
        src++;
        entry++;
        rec++;
    }
    xform->unk10 |= 1;
}

void func_01ffa538(Unk0208be3c *a, Unk0208be3c *b, int t, u32 mask) {
    if (a->file == 0) {
        return;
    }
    if (a->file != b->file) {
        return;
    }
    if (t < 0) {
        return;
    }
    if (t > 0x1000) {
        t = 0x1000;
    } else if (t == 0) {
        return;
    }
    if (!(a->unk10 & 1)) {
        return;
    }
    if (!(b->unk10 & 1)) {
        return;
    }
    Unk01ffa2d0Record *rec = (Unk01ffa2d0Record *)a->file->func_02095d98();
    Unk0208be3cEntry *ea = a->entries;
    Unk0208be3cEntry *eb = b->entries;
    if (mask != 0) {
        for (int i = 0; i < a->count; i++) {
            if (mask & rec->mask) {
                Unk02098ff0 s = func_scale(eb->pos.v.func_02099150(ea->pos.v), t);
                ea->pos.v.x += s.x;
                ea->pos.v.y += s.y;
                ea->pos.v.z += s.z;
                ea->rot = ea->rot.func_02098a5c(eb->rot, t);
            }
            rec++;
            ea++;
            eb++;
        }
    } else {
        for (int i = 0; i < a->count; i++) {
            Unk02098ff0 s = func_scale(eb->pos.v.func_02099150(ea->pos.v), t);
            ea->pos.v.x += s.x;
            ea->pos.v.y += s.y;
            ea->pos.v.z += s.z;
            ea->rot = ea->rot.func_02098a5c(eb->rot, t);
            ea++;
            eb++;
        }
    }
    a->unk10 |= 1;
}

void func_01ffa838(Unk0208be3c *xform) {
    if (xform->count == 0) {
        return;
    }
    if (!(xform->unk10 & 1)) {
        return;
    }
    int count;
    Unk0208be3cEntry *entry;
    int i;
    Unk01ffa2d0Record *rec = (Unk01ffa2d0Record *)xform->file->func_02095d98();
    count = xform->count;
    entry = xform->entries;
    for (i = 0; i < count; i++) {
        entry->mtx = Unk02098094(entry->rot.func_02098934());
        entry->mtx.func_020982bc(entry->pos.v);
        if (rec->parent != -1) {
            entry->mtx = func_mul(entry->mtx, xform->entries[rec->parent].mtx);
        }
        entry++;
        rec++;
    }
}

Unk0208be3cEntry *func_01ffa94c(Unk0208be3c *xform) {
    return xform->entries;
}

Unk0208be3cEntry *func_01ffa954(Unk0208be3c *xform, int index) {
    if (xform->file == 0 || xform->entries == 0) {
        return 0;
    }
    if (!(xform->unk10 & 1)) {
        return 0;
    }
    /* As in the original: the bound check only runs for negative indices. */
    if (index < 0 && index >= xform->func_0208c040()) {
        return 0;
    }
    return &xform->entries[index];
}

int func_01ffa9b0(Unk0208be3c *xform, const u32 *name) {
    if (xform->file == 0 || xform->entries == 0) {
        return -1;
    }
    Unk01ffa2d0Record *rec = (Unk01ffa2d0Record *)xform->file->func_02095d98();
    for (int i = 0; i < xform->func_0208c040(); i++) {
        if (func_0209a474(name, rec->name)) {
            return i;
        }
        rec++;
    }
    return -1;
}

void func_01ffaa28(Unk0208be3c *xform) {
    int count;
    if (!(xform->unk10 & 1) || (count = xform->count) == 0) {
        return;
    }
    Unk0208be3cEntry *entry = xform->entries;
    Unk0208be3cMtx *mtx = xform->mtxs;
    int i;
    Unk01ffa2d0Record *rec = (Unk01ffa2d0Record *)xform->file->func_02095d98();
    for (i = 0; i < count; i++) {
        Unk02098094 m;
        m.func_0209873c(rec->mtx, entry->mtx);
        mtx->m = m;
        mtx++;
        entry++;
        rec++;
    }
}
}
