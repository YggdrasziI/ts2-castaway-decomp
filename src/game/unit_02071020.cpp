/*
 * Unit 0x02071020-0x020717B8: Unk02071020, a pool object (Unk0208b554Item) with
 * its model, texture and texture coordinate animation (unit_020705E4.cpp) read by
 * name hash from a container file. Each load releases the previous resource and
 * keeps the sub-file index for the release; the texture also sets the element
 * set's entries (element 0x8AEEBD7B and the others with decreasing values).
 * func_02071564 places the object in front of the camera of the pool.
 *
 * Bounds: hypothesis. 0x02071020 follows the texture coordinate animations;
 * 0x020717B8 starts the constructor of another class (__cxa_vec_new). No data.
 * Real file name unknown.
 */

#include "game/unk_texanim.h"
#include "game/unk_archive.h"
#include "game/unk_blockfile.h"
#include "game/unk_pool.h"
#include "game/unk_camera.h"
#include "game/unk_matrix.h"

extern "C" {
void func_01ff9180(Unk0208adc0 *set, int id, Unk0208af38 *e);
void func_01ff924c(Unk0208adc0 *set, Unk0208af38 *e, int mask);
}

class Unk0208a0a8 {
public:
    void func_0208a0d4(Unk0209543c *file);
    void func_0208a5d8(int key);
};

extern Unk0208a0a8 *data_020c7d24;

class Unk02071020 {
public:
    Unk02071020(Unk02093648 *container, Unk0208b554Item *item, u32 texture, u32 model, u32 anim);
    ~Unk02071020();
    void func_02071120(u32 hash);
    void func_020711e8(u32 hash);
    void func_020713f8(u32 hash);
    void func_02071494(u16 value);
    void func_020714b0(bool on);
    void func_020714e0(const s16 *rgb);
    void func_02071518(u32 value);
    u32 func_0207155c();
    void func_02071564();
    void func_02071680();
    void func_020716dc();
    void func_02071740();
    void func_0207179c(u32 bit, bool on);

    Unk02093648 *container;
    Unk0208b554Item *item;
    Unk0208af38 elem;
    int poolIndex;
    int texIndex;
    int modelIndex;
    int animIndex;
    int texKey;
    int modelKey;
    u32 animHash;
    u32 flags;
    u32 unk4c;
    Unk0209487c *animFile;
    Unk02070eac *anims;
};

Unk02071020::Unk02071020(Unk02093648 *container, Unk0208b554Item *item, u32 texture, u32 model, u32 anim)
    : container(container), item(item), texIndex(-1), modelIndex(-1), animIndex(-1), texKey(0), modelKey(0),
      animHash(0), flags(0), unk4c(0x1f), animFile(0), anims(0) {
    poolIndex = data_020c7d38.func_0208bd20(this->item);
    this->item->func_0208ac48(0);
    func_02071120(model);
    func_020711e8(texture);
    func_020713f8(anim);
}

Unk02071020::~Unk02071020() {
    if (item != 0) {
        item->func_0208ac48(0);
    }
    func_02071740();
    func_020716dc();
    func_02071680();
}

void Unk02071020::func_02071120(u32 hash) {
    if (hash == 0) {
        func_020716dc();
        return;
    }
    int index = container->func_02093e9c(hash);
    if (index == -1) {
        return;
    }
    Unk0209543c *file = (Unk0209543c *)container->func_02093a9c(index);
    if (file == 0) {
        return;
    }
    int key = file->func_020955e0();
    if (key != modelKey) {
        func_020716dc();
        Unk0208a0a8 *lib = data_020c7d24;
        modelKey = key;
        lib->func_0208a0d4(file);
        item->func_0208ac48(modelKey);
        data_020c7d38.func_0208bd58(poolIndex, 0xffff);
        modelIndex = index;
    } else {
        container->func_02093c58(index);
    }
    func_020714b0(1);
}

void Unk02071020::func_020711e8(u32 hash) {
    if (hash == 0) {
        func_02071680();
        return;
    }
    int index = container->func_02093e9c(hash);
    if (index == -1) {
        return;
    }
    Unk02095fdc *file = (Unk02095fdc *)container->func_02093a9c(index);
    if (file == 0) {
        return;
    }
    int key = file->func_020960d4();
    if (key != texKey) {
        func_02071680();
        Unk020c7f48 *m = func_0208c578();
        texKey = key;
        m->func_0208cec4(file, 0);
        Unk0208adc0 *set = item->func_0208ad18();
        elem = set->func_0208b0cc(0x8aeebd7b);
        elem.func_0208b3ec(texKey);
        func_01ff9180(set, 0x8aeebd7b, &elem);
        u32 value = 0x3e;
        for (int i = 0; i < set->func_0208b058(); i++) {
            if (set->func_0208b09c(i) != (int)0x8aeebd7b) {
                elem = set->func_0208b0cc(set->func_0208b09c(i));
                elem.func_0208b25c(value--);
                set->func_0208b248(&elem);
            }
        }
        texIndex = index;
    } else {
        container->func_02093c58(index);
    }
}

void Unk02071020::func_020713f8(u32 hash) {
    int index = container->func_02093e9c(hash);
    if (index == -1) {
        return;
    }
    Unk0209487c *file = container->func_02093a9c(index);
    if (file == 0) {
        return;
    }
    func_02071740();
    animIndex = index;
    animHash = hash;
    animFile = file;
    anims = new Unk02070eac(item, (u32 *)animFile->func_02094d4c(0x102ff), animFile->func_02094ddc(0x102ff));
}

void Unk02071020::func_02071494(u16 value) {
    data_020c7d38.func_0208bd58(poolIndex, value);
}

void Unk02071020::func_020714b0(bool on) {
    func_0207179c(2, on);
    data_020c7d38.func_0208bc68(poolIndex, on);
}

void Unk02071020::func_020714e0(const s16 *rgb) {
    item->func_0208ad18();
    elem.func_0208b308(rgb);
    func_01ff924c(item->func_0208ad18(), &elem, 0x400);
}

void Unk02071020::func_02071518(u32 value) {
    item->func_0208ad18();
    if (value > 0x1f) {
        value = 0x1f;
    }
    unk4c = value;
    elem.func_0208b278(value);
    func_01ff924c(item->func_0208ad18(), &elem, 0x1f0000);
}

u32 Unk02071020::func_0207155c() {
    return unk4c;
}

/*
 * The original copies the sum to the item's position and the angles to its words
 * 0x0C-0x14 with ldm / stm, the block copy of a struct holding a vector
 * (notes/MATCHING.md); the casts to Unk020899a4Angles stand for that.
 */
static inline Unk020899a4Angles func_add(const Unk02098ff0 &a, Unk02098ff0 b) {
    return Unk020899a4Angles(a.x + b.x, a.y + b.y, a.z + b.z);
}

/* 99.89 %: two stack temporaries swapped (the matrix product and its copy). */
void Unk02071020::func_02071564() {
    Unk020899a4 *cam = (Unk020899a4 *)&data_020c7d38.unk54;
    if (!(flags & 2)) {
        return;
    }
    Unk020899a4Angles angles = cam->angles;
    angles.v.z += 0x4000;
    angles.v.y -= 0x4000;
    angles.v.x += 0x4000;
    Unk02097b6c m = Unk02097b6c::func_02097f78(cam->angles.v.z, cam->angles.v.x, cam->angles.v.y);
    Unk02098ff0 f(0, 0, 0x1000);
    *(Unk020899a4Angles *)&item->pos = func_add(cam->pos, m.func_02097d38(f));
    *(Unk020899a4Angles *)&item->unk0c = angles;
    if (anims == 0) {
        return;
    }
    if (flags & 1) {
        return;
    }
    anims->func_02070fe8();
}

void Unk02071020::func_02071680() {
    Unk020c7f48 *m = func_0208c578();
    int id = m->func_0208ccc0(texKey);
    if (id != -1) {
        m->func_0208c700(id);
        texKey = 0;
    }
    if (texIndex != -1) {
        container->func_02093c58(texIndex);
        texIndex = -1;
    }
}

void Unk02071020::func_020716dc() {
    func_020714b0(0);
    item->func_0208ac48(0);
    if (modelKey != 0) {
        data_020c7d24->func_0208a5d8(modelKey);
        modelKey = 0;
    }
    if (modelIndex != -1) {
        container->func_02093c58(modelIndex);
        modelIndex = -1;
    }
}

void Unk02071020::func_02071740() {
    delete anims;
    if (animFile != 0 && animFile->func_02094f88()) {
        container->func_02093c58(animIndex);
    }
    anims = 0;
    animFile = 0;
    animHash = 0;
}

void Unk02071020::func_0207179c(u32 bit, bool on) {
    if (on) {
        flags |= bit;
    } else {
        flags &= ~bit;
    }
}
