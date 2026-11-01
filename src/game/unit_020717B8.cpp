/*
 * Unit 0x020717B8-0x02071D94: Unk020717b8, short-lived effects drawn with pool
 * objects. It holds two textures (kept with a reference while loaded) and a
 * number of slots, each with a pool object; func_020718c0 starts one of the two
 * kinds of effect (data_020bc934: texture key, life, speed, scale) at a position,
 * in a free or expired slot; func_02071a60 ages them, scrolls their texture,
 * turns them to the pool camera and frees the expired ones.
 *
 * Bounds: hypothesis. 0x020717B8 follows unit_02071020.cpp; 0x02071D94 starts
 * the constructor of a class with a vtable. The effect table 0x020BC934-0x020BC954
 * is only used here; the eight zero bytes after it are the header of the vtable
 * data_020bc95c. Real file name unknown.
 */

#include "game/unk_pool.h"
#include "game/unk_camera.h"
#include "game/unk_matrix.h"
#include "game/unk_texture.h"

extern "C" {
void func_01ff924c(Unk0208adc0 *set, Unk0208af38 *e, int mask);
}

/* One kind of effect (0x10 bytes). */
struct Unk020717b8Kind {
    int key;
    int life;
    int speed;
    int scale;
};

/* One effect slot (0x18 bytes). */
struct Unk020717b8Slot {
    Unk020717b8Slot() {
        kind = 0;
        poolIndex = -1;
        item = 0;
        tex = 0;
        age = -1;
        start = 0;
    }

    Unk020717b8Kind *kind;
    int poolIndex;
    Unk0208b554Item *item;
    Unk0208c050 *tex;
    int age;
    int start;
};

class Unk020717b8 {
public:
    Unk020717b8(u32 count);
    ~Unk020717b8();
    void func_020718c0(const Unk02098ff0 &pos, const u32 *attr);
    void func_02071a60();
    void func_02071c54();
    void func_02071cc0();

    Unk0208c050 *tex[2];
    Unk020717b8Slot *slots;
    u32 count;
    int time;
    u8 loaded;
};

static Unk020717b8Kind data_020bc934[] = {
    {0x363bc6a6, 8, 0xf000, 0x20},
    {(int)0xbd155a14, 8, 0xa000, 0x20},
};

Unk020717b8::Unk020717b8(u32 count) {
    this->count = count;
    time = 0;
    loaded = 0;
    func_02071c54();
    slots = new Unk020717b8Slot[this->count];
    Unk020c7d38 *pool = &data_020c7d38;
    for (u32 i = 0; i < this->count; i++) {
        Unk020717b8Slot *s = &slots[i];
        s->kind = 0;
        s->poolIndex = pool->func_0208bbf4(0);
        s->item = pool->func_0208bcfc(s->poolIndex);
        s->tex = 0;
        s->age = 0;
        pool->func_0208bc68(s->poolIndex, 0);
    }
}

Unk020717b8::~Unk020717b8() {
    func_02071cc0();
    delete slots;
}

/* 98.03 %: the original gives the empty-slot test its own "n = i; break" block;
 * here both tests share one. The block copy of the position goes through a cast
 * to Unk020899a4Angles (a hypothesis, as in unit_02071020.cpp). */
void Unk020717b8::func_020718c0(const Unk02098ff0 &pos, const u32 *attr) {
    int type;
    u32 v = *attr & 0xc000;
    if (v == 0) {
        type = 0;
    } else if (v == 0x8000 || v == 0x4000 || v == 0xc000) {
        type = 1;
    } else {
        return;
    }
    u32 n = 0;
    for (u32 i = 0; i < count; i++) {
        Unk020717b8Slot *s = &slots[i];
        int age = s->age;
        if (s->kind != 0) {
            if (s->kind->life - age < -1) {
                n = i;
                break;
            }
        } else {
            n = i;
            break;
        }
    }
    Unk020717b8Slot *list = slots;
    Unk020717b8Slot *s = &list[n];
    s->kind = &data_020bc934[type];
    s->tex = tex[type];
    s->age = 0;
    s->item->func_0208ac48(0x950be33e);
    *(Unk020899a4Angles *)&s->item->pos = *(const Unk020899a4Angles *)&(const Unk02098ff0 &)pos.func_0209911c(Unk02098ff0(0x800, 0x800, 0x800));
    s->start = time;
    Unk0208af38 e;
    e.func_0208b3ec(list[n].kind->key);
    e.func_0208b278(0x1f);
    func_01ff924c(s->item->func_0208ad18(), &e, 0x5f0000);
    data_020c7d38.func_0208bd58(s->poolIndex, 0x83ff);
    data_020c7d38.func_0208bc68(s->poolIndex, 1);
}

/* 99.91 %: stack slots in another order (the direction and the rotation sit
 * lowest in the original). */
void Unk020717b8::func_02071a60() {
    Unk020899a4Angles angles = ((Unk020899a4 *)&data_020c7d38.unk54)->angles;
    Unk02097b6c m = Unk02097b6c::func_02097f1c(angles.v.z, angles.v.y, angles.v.x);
    Unk02098ff0 r = m.func_02097d38(Unk02098ff0(0, 0, 0x1000));
    Unk02098ff0 dir = r;
    for (u32 i = 0; i < count; i++) {
        Unk020717b8Slot *s = &slots[i];
        if (s->kind == 0) {
            continue;
        }
        s->age = (int)(((s64)s->kind->speed * (time - s->start) + 0x800) >> 12) >> 12;
        if (s->kind->life <= s->age) {
            s->item->func_0208ac48(0);
            data_020c7d38.func_0208bc68(s->poolIndex, 0);
            s->kind = 0;
            continue;
        }
        Unk0208adc0 *set = s->item->func_0208ad18();
        Unk0208af38 e = set->func_0208b0cc(0xf26be445);
        int x = (s->age * s->kind->scale) << 12;
        e.func_0208b400((((x & 0x7ffff000) >> 8) & ~0xf) | ((x & 0xfff) >> 8), 0);
        e.func_0208b3f4(func_02077c60(0x1000, s->kind->life << 12), 0x1000);
        set->func_0208b248(&e);
        Unk020899a4Angles rot(dir.x - 0x4000, dir.y, dir.z);
        *(Unk020899a4Angles *)&s->item->unk0c = rot;
    }
    time += 0x44;
}

void Unk020717b8::func_02071c54() {
    if (loaded) {
        return;
    }
    Unk020c7f48 *m = func_0208c578();
    for (int i = 0; i < 2; i++) {
        tex[i] = m->func_0208cc70(m->func_0208ccc0(data_020bc934[i].key));
        tex[i]->refs++;
    }
    loaded = 1;
}

void Unk020717b8::func_02071cc0() {
    if (!loaded) {
        return;
    }
    Unk020c7f48 *m = func_0208c578();
    Unk020c7d38 *pool = &data_020c7d38;
    for (int i = 0; i < 2; i++) {
        int id = m->func_0208ccc0(data_020bc934[i].key);
        tex[i]->refs--;
        tex[i] = 0;
        m->func_0208c700(id);
    }
    for (u32 i = 0; i < count; i++) {
        Unk020717b8Slot *s = &slots[i];
        s->kind = 0;
        s->item->func_0208ac48(0);
        pool->func_0208bc68(s->poolIndex, 0);
    }
    loaded = 0;
}
