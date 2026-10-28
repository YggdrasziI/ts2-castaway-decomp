/*
 * Unit 0x0205C700-0x0205D4D8: the object definition record Unk0205cf00 (0x1C
 * bytes, one per definition in the database of unit_0205F16C.cpp). It holds
 * the footprint of the object (size and a bit mask of the occupied tiles), its
 * key, its script file, flags and resource group. The functions read the
 * script's blocks: the visible object description (model, skeleton,
 * animations, conversation, flags) for a state, values by key, and the runs
 * of the script.
 *
 * Bounds: hypothesis. The functions before 0x0205C700 are script callbacks
 * registered by the static initializer before 0x020AE130 and end with an
 * empty function (0x0205C6FC); the record constructor opens this range. After
 * 0x0205D4D8 come a hash table and another class (0x0205D608). The static
 * initializer 0x020AE130 builds the default description data_020c3f7c;
 * data_020c3fb0 is the empty block returned when a run is missing. `.data`
 * holds the two file extensions hashed into the description. Real file name
 * unknown.
 *
 * Not complete: the compiler puts data_020c3fb0 (8 bytes) before
 * data_020c3f7c in `.bss` whatever the order of the definitions (also tried
 * static, a constructor, a function-local static); the original has the
 * description first. The static initializer, func_0205c8b4 and func_0205cd6c
 * differ only by that offset.
 *
 * Functions other than the constructor keep C linkage: other files call them
 * by their addresses.
 */

#include "game/unk_script.h"
#include "game/unk_objscript.h"

/* The record (0x1C bytes). */
struct Unk0205cf00 {
    Unk0205cf00();

    bool func_tile(int i) const { return mask & (1 << i); }
    int func_width() const { return width; }

    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 mask;
    int key;
    Unk020956f8 *script;
    u32 flags;
    int group;
};

/* The description of the visible object of a state (0x34 bytes). */
struct Unk020615f0Def {
    Unk020615f0Def() {
        model = 0;
        xform = 0;
        anim = 0;
        unkc = 0;
        unk10 = 0;
        unk14 = 0;
        unk18 = 0;
        unk1c = 0;
        texanim = 0;
        unk2c = 0;
        flags = 0;
    }

    int model;
    u32 xform;
    u32 anim;
    u32 unkc;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    u32 texanim;
    int unk24;
    int unk28;
    int unk2c;
    u32 flags;
};

struct Unk020680d4Dir {
    int v;
};

/* A scene object: only the fields used here. */
class Unk02061d08Item {
public:
    void *vtable;
    u8 list[0x24];
    Unk0205cf00 *def;
};

/* The player: only its action list. */
struct Unk0205cfd4Player {
    u8 unk0[0x3c8];
    u8 list[0xc];
};

/* The action context (data_020c3cc8). */
struct Unk020c3cc8 {
    u8 unk0[0x18];
    u8 result;
};

/* An action object (only the field used here). */
struct Unk0205cfd4Obj {
    u8 unk0[0x18];
    void *unk18;
};

class Unk02061b90 : public Unk02099c78 {
public:
    Unk02061b90(Unk0205cf00 *def);
    ~Unk02061b90();
    virtual bool vfunc_00(int key);
    virtual short vfunc_04(int index);
    virtual void vfunc_08(int index, short value);
    virtual int vfunc_14(int arg, Unk02099c78Call *call);
};

class Unk020c409c;

extern Unk020c3cc8 data_020c3cc8;
extern Unk020c409c data_020c409c;
extern u8 data_020be184[];

Unk020615f0Def data_020c3f7c;
Unk02099c78Block data_020c3fb0;

extern "C" {

u32 func_0209a3c4(u32 hash, const char *str);
bool func_0205c564(bool *out, int value);
void func_0205b058(Unk020c3cc8 *c, int a, Unk02061d08Item *item, Unk0205cfd4Player *p);
void func_0205b074(Unk020c3cc8 *c, int a, Unk02061d08Item *item, Unk0205cfd4Player *p);
void *func_02007c98(void *p, int kind, int b);
void func_02004848(void *o, int a, int key, int b);
void func_02007e48(void *list, void *o);
void func_020606e0(Unk020c409c *o, int group);
void func_020608a8(Unk020c409c *o, int group);
void func_0205c728(Unk0205cf00 *def);
Unk020615f0Def func_0205c8b4(Unk0205cf00 *def, Unk02099c78Block *block);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
int func_0205d3dc(Unk0205cf00 *def, int index);
int func_0205d41c(Unk0205cf00 *def, int index, int key);
bool func_0205d498(Unk0205cf00 *def, int *out, int index, int key);

}

static inline Unk02099c78Value *func_find(Unk02099c78Block *block, Unk02099c78Value *values, int key) {
    for (int i = block->func_start(); i < block->func_end(); i++) {
        if (key == values[i].unk0) {
            return &values[i];
        }
    }
    return 0;
}

Unk0205cf00::Unk0205cf00() : x(-1), y(-1), width(-1), height(-1) {
    func_0205c728(this);
}

extern "C" {

void func_0205c728(Unk0205cf00 *def) {
    def->x = 0;
    def->y = 0;
    def->width = 0;
    def->height = 0;
    def->mask = 0;
    def->key = 0;
    def->script = 0;
    def->flags = 0;
    def->group = -1;
}

u32 func_0205c758(Unk0205cf00 *def, Unk020680d4Dir dir) {
    u32 mask = def->mask;
    int bit;
    switch (dir.v) {
    case 3: {
        mask = 0;
        bit = 0;
        for (int x = 0; x < def->func_width(); x++) {
            for (int y = def->height - 1; y >= 0; y--) {
                if (def->func_tile(x + y * def->width)) {
                    mask |= 1 << bit;
                }
                bit++;
            }
        }
        break;
    }
    case 2: {
        mask = 0;
        bit = 0;
        for (int y = def->height - 1; y >= 0; y--) {
            for (int x = def->width - 1; x >= 0; x--) {
                if (def->func_tile(y * def->width + x)) {
                    mask |= 1 << bit;
                }
                bit++;
            }
        }
        break;
    }
    case 1: {
        mask = 0;
        bit = 0;
        for (int x = def->width - 1; x >= 0; x--) {
            for (int y = 0; y < def->height; y++) {
                if (def->func_tile(x + y * def->func_width())) {
                    mask |= 1 << bit;
                }
                bit++;
            }
        }
        break;
    }
    }
    return mask;
}

/* 99.96 %: the offset of data_020c3f7c in `.bss` (see the header). */
Unk020615f0Def func_0205c8b4(Unk0205cf00 *def, Unk02099c78Block *block) {
    if (block == 0) {
        return data_020c3f7c;
    }
    Unk020956f8 *script = def->script;
    Unk020615f0Def d;
    d.unk28 = 0x7fff;
    d.flags |= 0x600;
    Unk02099c78Value *values = script->func_02095ab0();
    for (int i = block->start; i < block->start + block->count; i++) {
        switch (values[i].unk0) {
        case 0x8637d208:
            d.model = values[i].unk4;
            break;
        case 0xe39ba351:
            d.anim = values[i].unk4;
            d.flags |= 1;
            break;
        case 0xfb1a6fe5:
            d.flags &= ~4;
            d.flags |= values[i].unk4 != 0 ? 4 : 0;
            break;
        case 0x4c62a562:
            d.unkc = values[i].unk4;
            d.flags |= 2;
            break;
        case 0x34e43b31:
            d.flags &= ~8;
            d.flags |= values[i].unk4 != 0 ? 8 : 0;
            break;
        case 0xf6171b5d:
            d.flags &= ~0x80;
            d.flags |= values[i].unk4 == 0xe8b6eebf ? 0x80 : 0;
            break;
        case 0x2feaa295:
            d.xform = func_0209a3c4(values[i].unk4, ".nitro_skeleton");
            break;
        case 0xc607b8b3:
            d.unk10 = values[i].unk4;
            d.flags |= 0x10;
            break;
        case 0xdfae32b6:
            d.unk14 = values[i].unk4;
            break;
        case 0x52a69bfd:
            d.unk18 = values[i].unk4;
            d.flags |= 0x20;
            break;
        case 0x108ff6ef:
            d.unk1c = values[i].unk4;
            break;
        case 0x3e5cda2c:
            d.texanim = values[i].unk4;
            break;
        case 0x29ac88ab:
            d.unk24 = func_0209a3c4(values[i].unk4, ".conversation.nitro_xml");
            d.flags |= 0x40;
            break;
        case 0x5a20ad89:
            d.unk2c = values[i].unk4 << 12;
            d.flags |= 0x100;
            break;
        case 0xabafb595: {
            int v = values[i].unk4;
            if (v < 0) {
                v = 0;
            } else if (v > 0xff) {
                v = 0xff;
            }
            d.unk28 = v << 8;
            break;
        }
        case 0x45d46c0d:
            if (values[i].unk4 == 0 || values[i].unk4 == 0xe8b6eebf) {
                d.flags &= ~0x200;
            }
            break;
        case 0x6c7e5ed5:
            if (values[i].unk4 == 0 || values[i].unk4 == 0xe8b6eebf) {
                d.flags &= ~0x400;
            }
            break;
        case 0xf49bd463: {
            bool on;
            if (func_0205c564(&on, values[i].unk4)) {
                d.flags |= on ? 0x800 : 0;
            }
            break;
        }
        }
    }
    return d;
}

/* 99.67 %: the offset of data_020c3f7c in `.bss` (see the header). */
Unk020615f0Def func_0205cd6c(Unk0205cf00 *def, int key) {
    if (def->script == 0) {
        return data_020c3f7c;
    }
    Unk02099c78Block *block;
    if (key == 0) {
        block = (Unk02099c78Block *)def->script->func_02095960(0x7a90e673);
    } else {
        block = (Unk02099c78Block *)def->script->func_02095960(key);
    }
    if (block == 0) {
        return data_020c3f7c;
    }
    return func_0205c8b4(def, block);
}

Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index) {
    if (index < 0 || index >= def->script->func_0209576c()->count406) {
        return &data_020c3fb0;
    }
    return (Unk02099c78Block *)&def->script->func_02095934()[index];
}

Unk02099c78Block *func_0205cee4(Unk0205cf00 *def, int key) {
    Unk02099c78Block *block = (Unk02099c78Block *)def->script->func_02095960(key);
    if (block == 0) {
        block = &data_020c3fb0;
    }
    return block;
}

int func_0205cf00(Unk0205cf00 *def, int index) {
    int v;
    if (func_0205d498(def, &v, index, 0x68d173a0)) {
        return v;
    }
    return 0;
}

u8 func_0205cf28(Unk0205cf00 *def, int a, Unk02061d08Item *item, Unk0205cfd4Player *p) {
    int key;
    if (func_0205d498(def, &key, a, 0x50383bf0) && item->def->script->func_020957ec(key)) {
        func_0205b058(&data_020c3cc8, a, item, p);
        Unk02061c04 runner(item);
        if (runner.func_02099ce0(key)) {
            return data_020c3cc8.result;
        }
    }
    return 0;
}

int func_0205cfd4(Unk0205cf00 *def, int a, Unk02061d08Item *item, Unk0205cfd4Player *p) {
    Unk02099c78Block *block = func_0205cea4(def, a);
    Unk02099c78Value *values = def->script->func_02095ab0();
    for (int i = block->func_start(); i < block->func_end(); i++) {
        switch (values[i].unk0) {
        case 0x2d81e2b8: {
            func_0205b074(&data_020c3cc8, a, item, p);
            if (!item->def->script->func_020957ec(values[i].unk4)) {
                return 0;
            }
            Unk02061c04 runner(item);
            return runner.func_02099ce0(values[i].unk4);
        }
        case 0x032a3395: {
            Unk0205cfd4Obj *o = (Unk0205cfd4Obj *)func_02007c98(data_020be184, 0xb, 2);
            func_02004848(o, a, values[i].unk4, 1);
            if (o == 0) {
                return 0;
            }
            func_02007e48(item->list, o);
            if (p != 0) {
                func_02007e48(p->list, o->unk18);
            }
            return 1;
        }
        }
    }
    return 0;
}

int func_0205d134(Unk0205cf00 *def, int key) {
    Unk02099c78Block *block = (Unk02099c78Block *)def->script->func_02095a3c(0x71ca2e4d);
    if (block != 0) {
        Unk02099c78Value *v = func_find(block, def->script->func_02095ab0(), key);
        if (v != 0) {
            return v->unk4;
        }
    }
    return -1;
}

int func_0205d1b4(Unk0205cf00 *def, int key) {
    Unk02099c78Block *block = (Unk02099c78Block *)def->script->func_02095a3c(0x22d6e5e0);
    if (block != 0) {
        Unk02099c78Value *v = func_find(block, def->script->func_02095ab0(), key);
        if (v != 0) {
            return v->unk4;
        }
    }
    return 0;
}

int func_0205d234(Unk0205cf00 *def, int blockKey, int key) {
    Unk02099c78Block *block = (Unk02099c78Block *)def->script->func_02095a3c(blockKey);
    if (block != 0) {
        Unk02099c78Value *v = func_find(block, def->script->func_02095ab0(), key);
        if (v != 0) {
            return v->unk4;
        }
    }
    return 0;
}

bool func_0205d2ac(Unk0205cf00 *def, int key) {
    return def->script->func_02095a3c(key) != 0;
}

bool func_0205d2c8(Unk0205cf00 *def, int blockKey, int key) {
    Unk02099c78Block *block = (Unk02099c78Block *)def->script->func_02095a3c(blockKey);
    if (block == 0) {
        return false;
    }
    return func_find(block, def->script->func_02095ab0(), key) != 0;
}

bool func_0205d340(Unk0205cf00 *def, int key) {
    if (def->script == 0) {
        return false;
    }
    return def->script->func_02095b08(key);
}

void func_0205d35c(Unk0205cf00 *def) {
    if (def->group >= 0) {
        func_020606e0(&data_020c409c, def->group);
    }
}

void func_0205d37c(Unk0205cf00 *def) {
    if (def->group >= 0) {
        func_020608a8(&data_020c409c, def->group);
    }
}

int func_0205d39c(Unk0205cf00 *def, int key) {
    Unk02061b90 runner(def);
    return runner.func_02099ce0(key);
}

int func_0205d3dc(Unk0205cf00 *def, int index) {
    if (index < 0 || index >= def->script->func_0209576c()->unk4) {
        return 0;
    }
    return def->script->func_02095ab0()[index].unk4;
}

int func_0205d41c(Unk0205cf00 *def, int index, int key) {
    if (index < 0 || index >= def->script->func_0209576c()->count406) {
        return -1;
    }
    Unk02099c78Block *block = (Unk02099c78Block *)&def->script->func_02095934()[index];
    Unk02099c78Value *values = def->script->func_02095ab0();
    int end = block->func_end();
    for (int i = block->func_start(); i < end; i++) {
        if (key == values[i].unk0) {
            return i;
        }
    }
    return -1;
}

bool func_0205d498(Unk0205cf00 *def, int *out, int index, int key) {
    int i = func_0205d41c(def, index, key);
    if (i == -1) {
        return false;
    }
    *out = func_0205d3dc(def, i);
    return true;
}

}
