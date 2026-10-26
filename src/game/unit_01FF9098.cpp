/*
 * ITCM unit 0x01FF9098-0x01FF9924: functions of the element set (Unk0208adc0,
 * include/game/unk_matset.h) placed in ITCM. They copy a set into a buffer or
 * over another set, update elements by id or through a mask, write the packed
 * words of the elements and the set's scale into a resource file's data at the
 * offsets of its records (flushing each with DC_StoreRange), and keep the
 * reference counts of the textures of the texture manager of unit_0208C050.cpp.
 *
 * Bounds: hypothesis. 0x01FF8FD8 before works on 4x4 matrices; 0x01FF9924 after
 * is a larger function that calls into this group and into the pool objects. The
 * functions keep C linkage and their addresses as names: whether they are members
 * of Unk0208adc0 is not known. No data. Real file name unknown.
 */

#include "game/unk_matset.h"
#include "game/unk_blocks.h"
#include "game/unk_texture.h"

typedef unsigned char u8;

extern "C" {
void func_02099b84(const void *src, void *dest, u32 size);
void DC_StoreRange(const void *start, u32 size);

void func_01ff9478(Unk0208adc0 *set, u8 *data, const Unk0208adf8Record *rec);
void func_01ff9624(Unk0208adc0 *set);
void func_01ff9708(Unk0208adc0 *set, Unk0208af38 *e, int key);
void func_01ff98b4(Unk0208adc0 *set, u8 *data, Unk020bd014 *file);
}

static inline int func_pow2(int shift) {
    if (shift >= 0) {
        return 0x1000 << shift;
    }
    return 0x1000 >> -shift;
}

extern "C" {

int func_01ff9098(Unk0208adc0 *set, const Unk0208adc0 *src, Unk0208af38 *buffer, int maxWords) {
    if (set->elems != 0) {
        set->func_0208b020();
    }
    set->count = src->count;
    set->scale = src->scale;
    int words = set->count * sizeof(Unk0208af38) / 4;
    if (maxWords < words) {
        return 0;
    }
    set->elems = buffer;
    set->flags |= 1;
    set->flags = (set->flags & ~2) | (src->flags & 2);
    func_02099b84(src->elems, set->elems, set->count * sizeof(Unk0208af38));
    return words;
}

void func_01ff9128(Unk0208adc0 *set, const Unk0208adc0 *src) {
    if (set->count != src->count) {
        return;
    }
    set->scale = src->scale;
    set->flags = (set->flags & ~2) | (src->flags & 2);
    func_02099b84(src->elems, set->elems, set->count * sizeof(Unk0208af38));
}

int func_01ff9180(Unk0208adc0 *set, int id, const Unk0208af38 *src) {
    int n = set->count;
    Unk0208af38 *e = set->elems;
    int found = 0;
    while (n-- != 0) {
        if (e->unk18 == id) {
            e->unk0 = src->unk0;
            e->unk4 = src->unk4;
            e->unk8 = src->unk8;
            e->unk0c = (e->unk0c & 0x3ff0ffff) | (src->unk0c & 0xc00f0000);
            if (e->unk14 != src->unk14) {
                func_01ff9708(set, e, src->unk14);
            }
            e->unk1c = src->unk1c;
            e->unk1e = src->unk1e;
            e->unk20 = src->unk20;
            e->unk22 = src->unk22;
            found = 1;
        }
        e++;
    }
    return found;
}

void func_01ff924c(Unk0208adc0 *set, const Unk0208af38 *src, u32 mask) {
    int n = set->count;
    Unk0208af38 *e = set->elems;
    u32 m = mask & 0xc0e00700;
    mask &= 0x3f1ff8ff;
    u32 mask4 = 0;
    u32 mask0 = 0;
    if (m & 0x100) {
        mask4 |= 0x7fff0000;
    }
    if (m & 0x200) {
        mask4 |= 0x7fff;
    }
    if (m & 0x200000) {
        mask0 |= 0x7fff0000;
    }
    if (m & 0x400) {
        mask0 |= 0x7fff;
    }
    while (n-- != 0) {
        e->unk8 = (e->unk8 & ~mask) | (src->unk8 & mask);
        if (mask4 != 0) {
            e->unk4 = (e->unk4 & ~mask4) | (src->unk4 & mask4);
        }
        if (mask0 != 0) {
            e->unk0 = (e->unk0 & ~mask0) | (src->unk0 & mask0);
        }
        if (m & 0x400000) {
            func_01ff9708(set, e, src->unk14);
        }
        if (m & 0x800000) {
            e->unk1c = src->unk1c;
            e->unk1e = src->unk1e;
            e->unk20 = src->unk20;
            e->unk22 = src->unk22;
        }
        if (m & 0x40000000) {
            e->unk0c = (e->unk0c & ~0x40000000) | (src->unk0c & 0x30000);
        }
        if (m & 0x80000000) {
            e->unk0c = (e->unk0c & ~0x80000000) | (src->unk0c & 0xc0000);
        }
        e++;
    }
}

void func_01ff9404(Unk0208adc0 *set, u8 *data, Unk020bd014 *file) {
    const Unk0208adf8Record *rec = (const Unk0208adf8Record *)file->func_020954f8();
    if (rec == 0) {
        return;
    }
    bool skip = false;
    if ((set->flags & 2) && !(set->flags & 4)) {
        skip = true;
    }
    if (!skip) {
        func_01ff9624(set);
    }
    func_01ff9478(set, data, rec);
    func_01ff98b4(set, data, file);
}

void func_01ff9478(Unk0208adc0 *set, u8 *data, const Unk0208adf8Record *rec) {
    Unk0208af38 *e = set->elems;
    if (e == 0) {
        return;
    }
    int n = set->count;
    while (n-- != 0) {
        u32 *p0 = (u32 *)(data + (rec->offset0 & ~3));
        u32 *p4 = (u32 *)(data + (rec->offset4 & ~3));
        u32 *p8 = (u32 *)(data + (rec->offset8 & ~3));
        int *p0c = (int *)(data + (rec->unk10[0] & ~3));
        int *p10 = (int *)(data + (rec->unk10[1] & ~3));
        *p0 = e->unk0;
        *p4 = e->unk4;
        *p8 = e->unk8 & 0x3f1ff8ff;
        *p0c = e->unk0c;
        *p10 = e->unk10;
        int *scale = (int *)(data + (rec->unk10[2] & ~3));
        u32 param = e->unk0c;
        int sx = ((param & 0x700000) >> 20) - 4;
        int sy = ((param & 0x3800000) >> 23) - 4;
        int fx;
        int fy;
        if (sx < 0) {
            fx = 0x1000 >> -sx;
        } else {
            fx = 0x1000 << sx;
        }
        if (sy < 0) {
            fy = 0x1000 >> -sy;
        } else {
            fy = 0x1000 << sy;
        }
        scale[0] = (fx * e->unk20) >> 12;
        scale[1] = (fy * e->unk22) >> 12;
        int *offset = (int *)(data + (rec->unk10[3] & ~3));
        offset[0] = e->unk1c << 12;
        offset[1] = e->unk1e << 12;
        DC_StoreRange(p0, 4);
        DC_StoreRange(p4, 4);
        DC_StoreRange(p8, 4);
        DC_StoreRange(p0c, 4);
        DC_StoreRange(p10, 4);
        DC_StoreRange(scale, 8);
        DC_StoreRange(offset, 8);
        rec++;
        e++;
    }
}

void func_01ff9624(Unk0208adc0 *set) {
    Unk0208af38 *e = set->elems;
    if (e == 0) {
        return;
    }
    int n = set->count;
    Unk020c7f48 *m = func_0208c578();
    while (n-- != 0) {
        int id = m->func_0208ccc0(e->unk14);
        if (id != -1) {
            Unk0208c050 *t = m->func_0208cc70(id);
            if (t->texOffset == -1) {
                m->func_0208caa8(id);
            }
            e->unk0c &= 0xc00f0000;
            e->unk0c |= t->func_0208c110();
            e->unk10 = t->func_0208c134();
        } else {
            e->unk0c &= 0xc00f0000;
            e->unk10 = 0;
        }
        e++;
    }
    set->flags &= ~4;
}

void func_01ff9708(Unk0208adc0 *set, Unk0208af38 *e, int key) {
    if (e->unk14 == key) {
        return;
    }
    Unk020c7f48 *m = func_0208c578();
    if (set->flags & 2) {
        int id = m->func_0208ccc0(e->unk14);
        if (id != -1) {
            Unk0208c050 *t = m->func_0208cc70(id);
            if (t != 0) {
                t->refs--;
            }
        }
        id = m->func_0208ccc0(key);
        if (id != -1) {
            Unk0208c050 *t = m->func_0208cc70(id);
            if (t != 0) {
                t->refs++;
                set->flags |= 4;
            }
        }
        e->unk14 = key;
        return;
    }
    e->unk14 = key;
}

void func_01ff97bc(Unk0208adc0 *set) {
    Unk0208af38 *e = set->elems;
    if (e == 0) {
        return;
    }
    int n = set->count;
    Unk020c7f48 *m = func_0208c578();
    while (n-- != 0) {
        int id = m->func_0208ccc0(e->unk14);
        if (id != -1) {
            m->func_0208cc70(id)->refs++;
        }
        e++;
    }
    set->flags |= 2;
}

void func_01ff9838(Unk0208adc0 *set) {
    Unk0208af38 *e = set->elems;
    if (e == 0) {
        return;
    }
    int n = set->count;
    Unk020c7f48 *m = func_0208c578();
    while (n-- != 0) {
        int id = m->func_0208ccc0(e->unk14);
        if (id != -1) {
            m->func_0208cc70(id)->refs--;
        }
        e++;
    }
    set->flags &= ~2;
}

void func_01ff98b4(Unk0208adc0 *set, u8 *data, Unk020bd014 *file) {
    Unk0209543cBlockB *header = file->func_0209548c();
    if (header->unk20 == -1) {
        return;
    }
    int s = header->unk24;
    int *p = (int *)(data + header->unk20);
    p[0] = (s * set->scale.v.x) >> 12;
    p[1] = (s * set->scale.v.y) >> 12;
    p[2] = (s * set->scale.v.z) >> 12;
    DC_StoreRange(p, 0xc);
}
}
