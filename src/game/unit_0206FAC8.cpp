/*
 * Unit 0x0206FAC8-0x020705E4: the palette set Unk0206fac8
 * (include/game/unk_palset.h). It holds up to `capacity` texture palettes of 256
 * colours in two buffers: the colours read back from VRAM or copied from the
 * texture file, and the same colours tinted with one of its tint colours (built
 * from RGB byte triplets, normalised by their mean). Records are shared by key
 * with a reference count; flagged records are uploaded by the ITCM function
 * func_01ff8000 (unit_01FF8000.cpp). func_02070318 tints a range of colours:
 * luminance (0.299, 0.587, 0.114) times the tint, averaged with the colour.
 *
 * Bounds: hypothesis. Before 0x0206FAC8 lie two destructors (0x0206FAB0,
 * 0x0206FAB4) found in many vtables, not this class; 0x020705E4 starts the
 * constructor of another class. Real file name unknown.
 */

#include "game/unk_palset.h"
#include "game/unk_model.h"
#include "game/unk_matset.h"

extern "C" {
int func_02077c60(int a, int b);
u16 func_01ff8000(Unk0206fac8 *set, int index);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
}

static inline s64 func_fxmul64(s64 a, s64 b) {
    return (a * b + 0x800) >> 12;
}

Unk0206fac8::Unk0206fac8(u32 capacity, const u8 *colors, u32 colorCount)
    : recordCount(0), capacity(capacity), tintCount(colorCount), pending(0), tintShown(-1), tint(0),
      useTinted(0), write(1) {
    this->colors = new u16[this->capacity * 256];
    tinted = new u16[this->capacity * 256];
    records = new Unk0206fac8Record[this->capacity];
    slotUsed = new u8[this->capacity];
    tints = new int[tintCount * 3];
    for (u32 i = 0; i < this->capacity; i++) {
        slotUsed[i] = 0;
        records[i].flags = 0;
    }
    for (u32 i = 0, k = 0; i < tintCount; i++, k += 3) {
        const u8 *c = &colors[k];
        int mean = func_fxmul64((c[0] + c[1] + c[2]) << 12, 0x555);
        if (mean == 0) {
            mean = 0x1000;
        }
        int inv = func_02077c60(0x1000, mean);
        tints[k] = ((s64)inv * (colors[k] << 13) + 0x800) >> 12;
        tints[k + 1] = ((s64)inv * (colors[k + 1] << 13) + 0x800) >> 12;
        tints[k + 2] = ((s64)inv * (colors[k + 2] << 13) + 0x800) >> 12;
    }
}

Unk0206fac8::~Unk0206fac8() {
    for (u32 i = 0; i < recordCount; i++) {
        if (!(records[i].flags & 2) && !(records[i].flags & 1)) {
            func_020705c0(&records[i]);
        }
    }
    delete[] colors;
    delete[] tinted;
    delete[] tints;
    delete[] slotUsed;
    delete[] records;
}

static inline void func_copy(void *src, void *dst, u32 size) {
    MIi_CpuCopy16(src, dst, size);
}

/* 96.23 %: the registers of recordCount and records are swapped (r3 / r7). The inline
 * copy wrapper computes the destination and size before func_0209608c, as the original. */
void Unk0206fac8::func_0206fd2c(Unk02095fdc *file) {
    Unk020c7f48 *m = func_0208c578();
    int id = m->func_0208ccc0(file->func_020960d4());
    if (id == -1) {
        return;
    }
    Unk0208c050 *tex = m->func_0208cc70(id);
    func_02070114(tex, file->func_020960d4());
    for (u32 i = 0; i < recordCount; i++) {
        if (records[i].tex == tex) {
            if (!(records[i].flags & 2)) {
                return;
            }
            func_copy(file->func_0209608c(), colors + records[i].start, records[i].count * 2);
            func_02070318(records[i].start, records[i].count);
            records[i].flags &= ~2;
            return;
        }
    }
}

void Unk0206fac8::func_0206fe30(int id) {
    Unk020c7f48 *m = func_0208c578();
    if (id == -1) {
        return;
    }
    Unk0208c050 *tex = m->func_0208cc70(id);
    for (u32 i = 0; i < recordCount; i++) {
        if (records[i].tex == tex) {
            func_0207024c(tex, records[i].key);
            return;
        }
    }
}

/* 99.89 %: the original reads unk14 through the returned pointer (r5), not
 * from the stack copy. */
void Unk0206fac8::func_0206fea8(Unk02089f38 *model) {
    if (model == 0) {
        return;
    }
    Unk0208adc0 *set = model->func_0208a048();
    Unk020c7f48 *m = func_0208c578();
    for (int i = 0; i < set->func_0208b058(); i++) {
        Unk0208af38 e = set->func_0208b190(i);
        int key = e.unk14;
        int id = m->func_0208ccc0(key);
        if (id == -1) {
            return;
        }
        Unk0208c050 *tex = m->func_0208cc70(id);
        if (tex != 0) {
            func_02070114(tex, key);
        }
    }
}

/* 99.89 %: same gap as func_0206fea8. */
void Unk0206fac8::func_0206ff5c(Unk02089f38 *model) {
    if (model == 0) {
        return;
    }
    Unk0208adc0 *set = model->func_0208a048();
    Unk020c7f48 *m = func_0208c578();
    for (int i = 0; i < set->func_0208b058(); i++) {
        Unk0208af38 e = set->func_0208b190(i);
        int key = e.unk14;
        int id = m->func_0208ccc0(key);
        if (id == -1) {
            return;
        }
        Unk0208c050 *tex = m->func_0208cc70(id);
        if (tex != 0) {
            func_0207024c(tex, key);
        }
    }
}

void Unk0206fac8::func_02070010(u8 write) {
    this->write = write;
}

void Unk0206fac8::func_0207001c(u8 useTinted) {
    bool changed = useTinted != this->useTinted;
    this->useTinted = useTinted;
    if (changed) {
        func_02070048();
    }
}

void Unk0206fac8::func_02070048() {
    tintShown = -1;
    func_0207005c();
}

void Unk0206fac8::func_0207005c() {
    if (tintShown != tint) {
        tintShown = tint;
        pending = recordCount;
        for (u32 i = 0; i < recordCount; i++) {
            records[i].flags |= 1;
        }
    }
    if (pending <= 0) {
        return;
    }
    for (u32 i = 0; i < recordCount; i++) {
        if (records[i].flags & 1) {
            func_01ff8000(this, i);
        }
    }
}

void Unk0206fac8::func_02070114(Unk0208c050 *tex, int key) {
    Unk0206fac8Record *r;
    int n;
    n = tex->func_0208c1a4() >> 1;
    if (n > 0x100) {
        return;
    }
    if (n < 1) {
        return;
    }
    for (u32 i = 0; i < recordCount; i++) {
        if (records[i].key == key) {
            records[i].refs++;
            return;
        }
    }
    if (recordCount >= capacity) {
        return;
    }
    if (tex->format() == 7) {
        return;
    }
    r = &records[recordCount++];
    r->key = key;
    r->start = 0xffff;
    for (u32 j = 0; j < capacity; j++) {
        if (slotUsed[j] == 0) {
            r->start = j << 8;
            slotUsed[j] = 1;
            break;
        }
    }
    r->refs = 1;
    r->count = n;
    r->tex = tex;
    r->flags = 3;
    pending++;
}

void Unk0206fac8::func_0207024c(Unk0208c050 *tex, int key) {
    for (u32 i = 0; i < recordCount; i++) {
        Unk0206fac8Record *r = &records[i];
        if (r->key == key) {
            if (--r->refs != 0) {
                return;
            }
            recordCount--;
            if (r->flags & 1) {
                pending--;
            }
            slotUsed[r->start >> 8] = 0;
            if (recordCount == 0) {
                return;
            }
            Unk0206fac8Record *last = &records[recordCount];
            r->tex = last->tex;
            r->key = last->key;
            r->refs = last->refs;
            r->start = last->start;
            r->count = last->count;
            r->flags = last->flags;
            return;
        }
    }
}

/* 99.68 %: register swap in the prologue (colors and the tint index, r4/r7;
 * the tint pointer, r5/r6). */
void Unk0206fac8::func_02070318(u32 start, int count) {
    int t = tint * 3;
    int *p = &tints[t];
    u16 *src = colors + start;
    int tr = p[0];
    int tg = p[1];
    int tb = p[2];
    u16 *dst = tinted + start;
    for (int i = 0; i < count; i++) {
        int c = *src++;
        int r = (u8)((c & 0x1f) << 3);
        int g = (u8)(((c >> 5) & 0x1f) << 3);
        int b = (u8)(((c >> 10) & 0x1f) << 3);
        int lum = (int)func_fxmul64(r << 12, 0x4c9) + (int)func_fxmul64(g << 12, 0x964) +
                  (int)func_fxmul64(b << 12, 0x1d3);
        int l = func_fxmul64(lum, 0x555);
        s16 nr = (r + ((int)func_fxmul64(l, tr) >> 12)) >> 1;
        s16 ng = (g + ((int)func_fxmul64(l, tg) >> 12)) >> 1;
        s16 nb = (b + ((int)func_fxmul64(l, tb) >> 12)) >> 1;
        if (nr > 0xff) {
            nr = 0xff;
        }
        if (nr < 0) {
            nr = 0;
        }
        if (ng > 0xff) {
            ng = 0xff;
        }
        if (ng < 0) {
            ng = 0;
        }
        if (nb > 0xff) {
            nb = 0xff;
        }
        if (nb < 0) {
            nb = 0;
        }
        *dst++ = (nr >> 3) + ((ng >> 3) << 5) + ((nb >> 3) << 10);
    }
}

void Unk0206fac8::func_020705c0(Unk0206fac8Record *r) {
    r->tex->func_0208c50c(colors + r->start, 0, r->count);
}
