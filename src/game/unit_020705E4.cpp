/*
 * Unit 0x020705E4-0x02071020: texture coordinate animations
 * (include/game/unk_texanim.h). Unk020705e4 keeps the animation sets of the pool
 * objects and the container sub-files they were read from, with a reference
 * count; Unk02070eac builds one animation per element of the object's element set
 * listed in the data block; Unk02070cc0 runs its effects (move, offset, sine
 * waves on the offset or the scale, steps) through the table data_020bc918,
 * wraps the offset to the texture size and writes it to its element.
 *
 * Bounds: hypothesis. 0x020705E4 follows the palette set (unit_0206FAC8.cpp);
 * 0x02071020 starts the constructor of another class. The effect table
 * 0x020BC918-0x020BC934 is only used here. Real file name unknown.
 */

#include "game/unk_texanim.h"
#include "game/unk_archive.h"

extern "C" {
int func_02077ae4(int a, int b);
}

extern const short data_020af1e8[];

static inline int func_fxmulr(int a, int b) {
    return ((s64)a * b + 0x800) >> 12;
}

typedef void (*Unk02070cc0Effect)(Unk02070cc0State *s, const Unk02070cc0Param *p);

Unk020705e4::Unk020705e4(u32 capacity) {
    this->capacity = capacity;
    refCount = 0;
    setCount = 0;
    refs = new Unk020705e4Ref[this->capacity];
    sets = new Unk02070eac *[this->capacity];
}

Unk020705e4::~Unk020705e4() {
    for (u32 i = 0; i < setCount; i++) {
        delete sets[i];
    }
    delete[] refs;
    delete[] sets;
}

void Unk020705e4::func_02070688(Unk02093648 *container, u32 hash, Unk0208b554Item *item) {
    int index = container->func_02093e9c(hash);
    Unk0209487c *file = container->func_02093a9c(index);
    func_02070804(container, file, index);
    sets[setCount++] = new Unk02070eac(item, (u32 *)file->func_02094d4c(0x102ff), file->func_02094ddc(0x102ff));
}

void Unk020705e4::func_0207072c(Unk02093648 *container, u32 hash, Unk0208b554Item *item) {
    func_020708a8(container, container->func_02093e9c(hash));
    for (u32 i = 0; i < setCount; i++) {
        if (sets[i]->func_02070fd4(item)) {
            delete sets[i];
            if (--setCount != 0) {
                sets[i] = sets[setCount];
            }
        }
    }
}

void Unk020705e4::func_020707cc() {
    for (u32 i = 0; i < setCount; i++) {
        sets[i]->func_02070fe8();
    }
}

int Unk020705e4::func_02070804(Unk02093648 *container, Unk0209487c *file, int index) {
    for (u32 i = 0; i < refCount; i++) {
        if (refs[i].container == container && refs[i].index == index) {
            refs[i].refs++;
            return i;
        }
    }
    Unk020705e4Ref *r = &refs[refCount++];
    r->container = container;
    r->index = index;
    r->refs = 1;
    return refCount - 1;
}

void Unk020705e4::func_020708a8(Unk02093648 *container, int index) {
    for (u32 i = 0; i < refCount; i++) {
        if (refs[i].container == container && refs[i].index == index) {
            Unk020705e4Ref *r = &refs[i];
            if (--r->refs == 0 && --refCount != 0) {
                Unk020705e4Ref *last = &refs[refCount];
                r->container = last->container;
                r->index = last->index;
                r->refs = last->refs;
            }
            container->func_02093c58(index);
            return;
        }
    }
}

static void func_02070954(Unk02070cc0State *s, const Unk02070cc0Param *p) {
    if (p->enabled == 0) {
        return;
    }
    s->x += func_fxmulr(p->a, s->time);
    s->y += func_fxmulr(p->b, s->time);
}

static void func_020709b8(Unk02070cc0State *s, const Unk02070cc0Param *p) {
    if (p->enabled == 0) {
        return;
    }
    s->x += p->a;
    s->y += p->b;
}

static inline int func_wave(const Unk02070cc0State *s, const Unk02070cc0Param *p) {
    int angle = p->d + func_fxmulr(p->c, s->time);
    int v = data_020af1e8[((u16)(((s64)angle * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4) * 2];
    return (int)(((float)v / 4096.0f) > 0 ? ((float)v / 4096.0f) * 4096.0f + 0.5f
                                           : ((float)v / 4096.0f) * 4096.0f - 0.5f);
}

/* 99.24 %: the angle is in r12 in the original, r2 here (and the 64-bit product
 * registers follow). */
static void func_020709e8(Unk02070cc0State *s, const Unk02070cc0Param *p) {
    if (p->enabled == 0) {
        return;
    }
    int v = func_wave(s, p);
    s->x += func_fxmulr(p->a, v);
    s->y += func_fxmulr(p->b, v);
}

static void func_02070b24(Unk02070cc0State *s, const Unk02070cc0Param *p) {
}

static void func_02070b28(Unk02070cc0State *s, const Unk02070cc0Param *p) {
}

/* 99.24 %: same gap as func_020709e8. */
static void func_02070b2c(Unk02070cc0State *s, const Unk02070cc0Param *p) {
    if (p->enabled == 0) {
        return;
    }
    int v = func_wave(s, p);
    s->sx += func_fxmulr(p->a, v);
    s->sy += func_fxmulr(p->b, v);
}

static void func_02070c68(Unk02070cc0State *s, const Unk02070cc0Param *p) {
    if (p->enabled == 0) {
        return;
    }
    int step = func_02077ae4(func_fxmulr(s->time, p->b) >> 12, p->a);
    s->x += (step * p->c) << 12;
}

static Unk02070cc0Effect data_020bc918[] = {
    func_02070954, func_020709b8, func_020709e8, func_02070b24, func_02070b28, func_02070b2c, func_02070c68,
};

/* 97.24 %: the original reads unk14 of the returned element through a pointer
 * (add r1, sp, #0), not from sp directly. */
Unk02070cc0::Unk02070cc0(Unk0208b554Item *item, int id, u32 *entries, u32 count) {
    set = item->func_0208ad18();
    this->id = id;
    flags = 0;
    this->entries = entries;
    this->count = count;
    state.time = 0;
    Unk020c7f48 *m = func_0208c578();
    Unk0208af38 e = set->func_0208b0cc(this->id);
    tex = m->func_0208cc70(m->func_0208ccc0(e.unk14));
    flags |= tex == 0;
}

Unk02070cc0::~Unk02070cc0() {
}

void Unk02070cc0::func_02070d5c() {
    if (flags & 1) {
        return;
    }
    Unk0208af38 e = set->func_0208b0cc(id);
    state.x = 0;
    state.y = 0;
    state.sx = 0x1000;
    state.sy = 0x1000;
    for (u32 i = 0; i < count; i++) {
        u32 k = i * sizeof(Unk02070cc0Entry) / 4;
        data_020bc918[entries[k]](&state, (Unk02070cc0Param *)(&entries[k] + 1));
    }
    int w = tex->func_0208c16c() << 12;
    state.x = func_02077ae4(state.x, w);
    int h = tex->func_0208c184() << 12;
    state.y = func_02077ae4(state.y, h);
    e.func_0208b400((((state.x & 0x7ffff000) >> 8) & ~0xf) | ((state.x & 0xfff) >> 8),
                    (((state.y & 0x7ffff000) >> 8) & ~0xf) | ((state.y & 0xfff) >> 8));
    e.func_0208b3f4(state.sx, state.sy);
    set->func_0208b248(&e);
    state.time += 0x44;
}

/* 99.23 %: id, n and the record pointer take r5 / r7 / r8 in the original
 * (rotated here). */
Unk02070eac::Unk02070eac(Unk0208b554Item *item, u32 *data, u32 size) {
    this->item = item;
    count = data[0];
    anims = new Unk02070cc0 *[count];
    u32 i = 1;
    u32 n = 0;
    item->func_0208ad18();
    size /= 4;
    for (; i < size; ) {
        int id = data[i];
        u32 entries = data[i + 1];
        u32 *rec = &data[i];
        if (item->func_0208ad18()->func_0208b060(id)) {
            anims[n++] = new Unk02070cc0(item, id, &rec[2], entries);
        }
        i += entries * sizeof(Unk02070cc0Entry) / 4 + 2;
    }
    count = n;
}

Unk02070eac::~Unk02070eac() {
    for (u32 i = 0; i < count; i++) {
        delete anims[i];
    }
    delete anims;
}

bool Unk02070eac::func_02070fd4(Unk0208b554Item *item) {
    return this->item == item;
}

void Unk02070eac::func_02070fe8() {
    for (u32 i = 0; i < count; i++) {
        anims[i]->func_02070d5c();
    }
}
