/*
 * Unit 0x02060ADC-0x02061D08: the visible objects of the scene. The server
 * (Unk020c40cc, one static object data_020c40cc; its strings name it
 * "cSimObjectVisibleServer") holds 40 visible objects and 4 temporary ones
 * (Unk02060d78, 0x38 bytes). A visible object owns a slot of the model pool
 * data_020c7d38 with its model, transforms, played animation, texture
 * animation and an attached object; the server shows the active ones, hides
 * the others and updates them each frame. Two script runners
 * (Unk02099c78) follow: one for an object definition, one that keeps the
 * script variables in the scene object.
 *
 * Bounds: hypothesis. The code before works on other scene objects; the
 * action handlers of unit_02061D08.cpp follow. The static initializer
 * (0x020AE1D8) builds data_020c40cc and registers its destructor. `.data`
 * holds the five strings used here and the vtables of the two runners.
 * Real file name unknown.
 *
 * Functions other than constructors, destructors and virtual functions keep
 * C linkage: other files call them by their addresses.
 */

#include "game/unk_sim.h"
#include "game/unk_objanim.h"
#include "game/unk_objscript.h"
#include "game/unk_objres.h"

class Unk02095d1c;
class Unk0205ed20;

/* The object attached to a visible object (vtable slots 0x08, 0x18 and 0x24, flags at 0x40). */
class Unk0201c460 {
public:
    virtual ~Unk0201c460();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual void func_20();
    virtual void func_24();

    u8 unk4[0x3c];
    u32 flags;
};

/* The definition given to func_020615f0. */
struct Unk020615f0Def {
    int model;
    u32 xform;
    u32 anim;
    u8 unkc[0x14];
    u32 texanim;
    int unk24;
    int unk28;
    int unk2c;
    u32 flags;
};

/* The definition of a scene object: only its script. */
struct Unk0205cf00 {
    u8 unk0[0x10];
    Unk020956f8 *script;
};

/* A scene object: its definition and script variables. */
class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual Unk020680d4Xy func_20();
    virtual int func_24();
    virtual int func_28();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    int unk2c;
    s16 vars[1];
};

/* A visible object (0x38 bytes). */
class Unk02060d78 {
public:
    Unk02060d78();
    ~Unk02060d78();

    u32 flags;
    Unk020c4390Base *owner;
    int unk8;
    int index;
    int model;
    u32 texanim;
    Unk0208be3c *xform;
    Unk02063d84 *anim;
    Unk0201c460 *attached;
    Unk0208be3c *prev;
    int blend;
    int step;
    int unk30;
    Unk0205ed20 *unk34;
};

class Unk020c40cc {
public:
    Unk020c40cc();
    ~Unk020c40cc();

    Unk02060d78 *objs[40];
    Unk02060d78 *temps[4];
};

/* The model library of unit_0208A0A8.cpp: only the function used here. */
class Unk0208a0a8 {
public:
    Unk02089f38 *func_0208a4c8(int key);
};

/* The game object (data_020d6240): only the list read here. */
struct Unk020d6240 {
    int unk0[2];
    void *unk8;
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

extern "C" {
void func_020897b4(const char *fmt, ...);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int index);
Unk0208be3cEntry *func_01ffa954(Unk0208be3c *xform, int index);
int func_01ffa9b0(Unk0208be3c *xform, const char *name);
void func_01ffa2d0(Unk0208be3c *xform, Unk020897c0 *anim);
void func_01ffa538(Unk0208be3c *a, Unk0208be3c *b, int t, u32 mask);
void func_01ffa838(Unk0208be3c *xform);
Unk020897c0 *func_02063d84(Unk02063d84 *a);
void func_02063d94(Unk02063d84 *a, int speed, int hold);
void func_02063db8(Unk02063d84 *a, int loop);
Unk02063d84 *func_02063e2c(u32 key, int mode);
u32 func_0209a3c4(u32 hash, const char *str);
void func_0201cf6c(Unk0201c460 *o, Unk020680d4Vec pos, Unk020680d4Vec offset);
void func_0205ed20(Unk0205ed20 *p);
bool func_020a0b8c(void *list, Unk0201c460 *o);
int func_0205afc8(int arg, Unk02099c78Call *call);

void func_02060b24(Unk020c40cc *s);
void func_02060b98(Unk020c40cc *s);
u32 func_02060c1c(Unk020c40cc *s);
Unk02060d78 *func_02060c48(Unk020c40cc *s, bool force);
Unk02060d78 *func_02060c90(Unk020c40cc *s);
void func_02060cdc(Unk020c40cc *s);
void func_02060e0c(Unk02060d78 *e);
void func_02060fc8(Unk02060d78 *e);
void func_02061060(Unk02060d78 *e);
void func_020610a0(Unk02060d78 *e);
void func_020610d8(Unk02060d78 *e, Unk020680d4Vec pos);
void func_0206110c(Unk02060d78 *e, Unk020680d4Vec rot);
void func_02061140(Unk02060d78 *e, int model);
void func_020611e8(Unk02060d78 *e, Unk0208be3c *xform);
void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames);
bool func_0206135c(Unk02060d78 *e);
Unk02098ff0 func_020613a4(Unk02060d78 *e);
Unk02098ff0 func_020613c8(Unk02060d78 *e);
Unk020680d4Vec func_020613f0(Unk02060d78 *e, const char *name, Unk020680d4Vec offset);
void func_020615f0(Unk02060d78 *e, Unk020615f0Def *def);
void func_02061838(Unk02060d78 *e, u32 texanim);
void func_0206189c(Unk02060d78 *e);
bool func_020618f4(Unk02060d78 *e, Unk0201c460 *o);
void func_02061930(Unk02060d78 *e);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
bool func_02061ab4(Unk02061d08Item *item, const Unk020680d4Cell *cell);
}

extern Unk020c3ba4 data_020c3ba4;
extern Unk020d6240 data_020d6240;
extern Unk0208a0a8 *data_020c7d24;

static inline Unk020680d4Vec &func_vec(Unk02098ff0 &v) {
    return (Unk020680d4Vec &)v;
}

static inline Unk020680d4Vec &func_vec(int &v) {
    return (Unk020680d4Vec &)v;
}

static inline const Unk020680d4Vec &func_vec(const Unk02098ff0 &v) {
    return (const Unk020680d4Vec &)v;
}

Unk020c40cc data_020c40cc;

Unk020c40cc::Unk020c40cc() {
    for (int i = 0; i < 40; i++) {
        objs[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        temps[i] = 0;
    }
}

Unk020c40cc::~Unk020c40cc() {
    func_02060b98(this);
}

void func_02060b24(Unk020c40cc *s) {
    func_020897b4("cSimObjectVisibleServer::Initialise()");
    for (int i = 0; i < 40; i++) {
        s->objs[i] = new Unk02060d78();
    }
    for (int i = 0; i < 4; i++) {
        s->temps[i] = new Unk02060d78();
    }
}

void func_02060b98(Unk020c40cc *s) {
    func_020897b4("cSimObjectVisibleServer::Release()");
    for (int i = 0; i < 40; i++) {
        if (s->objs[i] != 0) {
            delete s->objs[i];
        }
        s->objs[i] = 0;
    }
    for (int j = 0; j < 4; j++) {
        if (s->temps[j] != 0) {
            delete s->temps[j];
        }
        s->temps[j] = 0;
    }
}

u32 func_02060c1c(Unk020c40cc *s) {
    u32 n = 0;
    for (int i = 0; i < 40; i++) {
        if (!(s->objs[i]->flags & 1)) {
            n++;
        }
    }
    return n;
}

Unk02060d78 *func_02060c48(Unk020c40cc *s, bool force) {
    if (!force && func_02060c1c(s) < 4) {
        return 0;
    }
    for (int i = 0; i < 40; i++) {
        if (!(s->objs[i]->flags & 1)) {
            return s->objs[i];
        }
    }
    return 0;
}

Unk02060d78 *func_02060c90(Unk020c40cc *s) {
    for (int i = 0; i < 4; i++) {
        if (!(s->temps[i]->flags & 1)) {
            func_020897b4("allocated temporary object visible");
            return s->temps[i];
        }
    }
    return 0;
}

void func_02060cdc(Unk020c40cc *s) {
    int i;
    func_02058788(&data_020c3ba4, data_020c3ba4.map);
    for (i = 0; i < 40; i++) {
        if (!(s->objs[i]->flags & 1)) {
            func_020610a0(s->objs[i]);
        } else {
            func_02061060(s->objs[i]);
        }
    }
    for (i = 0; i < 40; i++) {
        func_02060e0c(s->objs[i]);
    }
    for (i = 0; i < 4; i++) {
        if (!(s->temps[i]->flags & 1)) {
            func_020610a0(s->temps[i]);
        } else {
            func_02061060(s->temps[i]);
            func_02060e0c(s->temps[i]);
        }
    }
}

Unk02060d78::Unk02060d78()
    : flags(0x18), owner(0), unk8(0), index(-1), model(0), texanim(0), xform(0), anim(0), attached(0), prev(0),
      blend(0), step(0), unk30(0x1000), unk34(0) {
    index = data_020c7d38.func_0208bbf4(0);
    data_020c7d38.func_0208bc68(index, false);
}

Unk02060d78::~Unk02060d78() {
    if (flags & 1) {
        func_02060fc8(this);
    }
}

void func_02060e0c(Unk02060d78 *e) {
    if (!(e->flags & 1)) {
        return;
    }
    if (e->anim != 0) {
        func_02063d94(e->anim, 0x1000, 0);
        if (e->xform != 0) {
            if ((e->flags & 0x10) && e->blend > 0) {
                func_01ffa2d0(e->xform, func_02063d84(e->anim));
                func_01ffa538(e->xform, e->prev, e->blend, 0);
            } else {
                func_01ffa2d0(e->xform, func_02063d84(e->anim));
            }
            func_01ffa838(e->xform);
        }
        if (e->blend > 0) {
            e->blend -= e->step;
        }
        if (e->unk34 != 0) {
            Unk020897c0 *a = func_02063d84(e->anim);
            if ((a->func_01ff8a78() && a->func_01ff8aa0()) || a->func_01ff8a8c()) {
                a->func_01ff8a80();
                func_0205ed20(e->unk34);
            }
        }
    }
    if (e->attached != 0) {
        func_0201cf6c(e->attached, func_020613f0(e, "head", Unk020680d4Vec(0, 0, 0)), Unk020680d4Vec(0, 0, 0));
        if (e->attached->flags & 4) {
            e->attached->func_18();
            e->attached->func_24();
            e->attached = 0;
        }
    }
}

void func_02060fc8(Unk02060d78 *e) {
    if (!(e->flags & 1)) {
        return;
    }
    data_020c7d38.func_0208bcfc(e->index);
    func_020610a0(e);
    e->flags &= ~1;
    func_02061140(e, 0);
    func_020611e8(e, 0);
    func_02061930(e);
    if (e->anim != 0 && e->owner != 0) {
        e->owner->func_04((int)e->anim);
    }
    e->anim = 0;
    e->owner = 0;
    e->unk34 = 0;
    e->flags &= ~4;
}

void func_02061060(Unk02060d78 *e) {
    if (e->flags & 2) {
        return;
    }
    if (!(e->flags & 8)) {
        data_020c7d38.func_0208bc68(e->index, true);
    }
    e->flags |= 2;
}

void func_020610a0(Unk02060d78 *e) {
    if (!(e->flags & 2)) {
        return;
    }
    data_020c7d38.func_0208bc68(e->index, false);
    e->flags &= ~2;
}

void func_020610d8(Unk02060d78 *e, Unk020680d4Vec pos) {
    func_vec(data_020c7d38.func_0208bcfc(e->index)->pos) = pos;
}

void func_0206110c(Unk02060d78 *e, Unk020680d4Vec rot) {
    func_vec(data_020c7d38.func_0208bcfc(e->index)->unk0c) = rot;
}

void func_02061140(Unk02060d78 *e, int model) {
    if (e->flags & 1) {
        return;
    }
    Unk020c7d38 *pool = &data_020c7d38;
    pool->func_0208bc68(e->index, false);
    e->flags &= ~2;
    if (model != e->model) {
        if (e->model != 0) {
            func_0206189c(e);
        }
        pool->func_0208bcfc(e->index)->func_0208ac48(model);
        e->model = model;
        if (model == 0) {
            e->flags |= 8;
        } else {
            e->flags &= ~8;
        }
        func_020611e8(e, 0);
    }
    pool->func_0208bcfc(e->index)->func_0208ad38(0);
}

void func_020611e8(Unk02060d78 *e, Unk0208be3c *xform) {
    if (e->flags & 1) {
        return;
    }
    if (e->xform != 0) {
        delete e->xform;
        e->xform = 0;
    }
    if (e->prev != 0) {
        delete e->prev;
        e->prev = 0;
    }
    e->xform = xform;
    if ((e->flags & 0x10) && e->xform != 0) {
        e->prev = new Unk0208be3c(e->xform->file, 0);
    }
    e->blend = 0;
}

void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames) {
    if (e->anim != 0) {
        if (e->prev == 0) {
            blend = false;
        }
        if ((e->flags & 0x10) && blend) {
            func_01ffa2d0(e->prev, func_02063d84(e->anim));
            if (frames <= 0 || frames > 0x40) {
                frames = 16;
            }
            e->step = 0x1000 / frames;
            e->blend = 0x1000 - e->step;
        }
        if (e->owner != 0) {
            e->owner->func_04((int)e->anim);
        }
    }
    e->anim = anim;
    if (e->anim == 0) {
        return;
    }
    func_02063d94(e->anim, 0, 0);
    data_020c7d38.func_0208bcfc(e->index)->func_0208ad38((int)e->xform);
}

bool func_0206135c(Unk02060d78 *e) {
    Unk02063d84 *a = e->anim;
    if (a != 0) {
        if (a->anim->func_01ff8a8c() || a->anim->func_01ff8aa0()) {
            return true;
        }
        return false;
    }
    return true;
}

Unk02098ff0 func_020613a4(Unk02060d78 *e) {
    return data_020c7d38.func_0208bcfc(e->index)->pos;
}

Unk02098ff0 func_020613c8(Unk02060d78 *e) {
    return func_vec(data_020c7d38.func_0208bcfc(e->index)->unk0c).v;
}

Unk020680d4Vec func_020613f0(Unk02060d78 *e, const char *name, Unk020680d4Vec offset) {
    if (e->xform != 0 && (e->xform->unk10 & 1)) {
        Unk0208be3cEntry *entry = func_01ffa954(e->xform, func_01ffa9b0(e->xform, name));
        if (entry == 0) {
            return Unk020680d4Vec(0, 0, 0);
        }
        Unk02098ff0 t = entry->mtx.func_020982a8();
        Unk020680d4Vec v = func_vec(t);
        Unk02097b6c m(entry->mtx);
        Unk02098ff0 o = m.func_02097d38(offset.v);
        Unk020680d4Vec scale(0x1000, 0x1000, 0x1000);
        v.v.x += o.x;
        v.v.y += o.y;
        v.v.z += o.z;
        Unk0208b554Item *item = data_020c7d38.func_0208bcfc(e->index);
        if (item != 0) {
            scale = *(Unk020680d4Vec *)item->func_0208ad18();
        }
        v.v.x = func_fxmul(v.v.x, scale.v.x);
        v.v.y = func_fxmul(v.v.y, scale.v.y);
        v.v.z = func_fxmul(v.v.z, scale.v.z);
        Unk02098ff0 pos;
        Unk02097b6c r = Unk02097b6c::func_02097e5c(func_020613c8(e).y);
        v = func_vec(r.func_02097d38(v.v));
        pos = func_020613a4(e);
        v.v.x += pos.x;
        v.v.y += pos.y;
        v.v.z += pos.z;
        return v;
    }
    return Unk020680d4Vec(0, 0, 0);
}

void func_020615f0(Unk02060d78 *e, Unk020615f0Def *def) {
    Unk02093648 *archive = data_020c409c.resources;
    e->flags &= ~1;
    e->owner = &data_020c4390;
    bool load = false;
    e->unk8 = 0;
    if (e->model != def->model) {
        if (def->model != 0 && data_020c7d24->func_0208a4c8(def->model) != 0) {
            func_02061140(e, def->model);
            load = true;
        } else {
            func_02061140(e, 0);
        }
    } else if (e->model != 0 && e->xform == 0) {
        load = true;
    }
    if (load && (def->flags & 1)) {
        int index = archive->func_02093ef4(def->xform, 5);
        if (index >= 0 && archive->func_02094000(index)) {
            Unk02095d1c *file = (Unk02095d1c *)archive->func_02093a58(index);
            func_020611e8(e, new Unk0208be3c(file, 0));
        }
    }
    if (e->model != 0) {
        if (def->texanim != 0) {
            func_02061838(e, def->texanim);
        } else {
            func_0206189c(e);
        }
        data_020c7d38.func_0208bd58(e->index, def->unk28);
    }
    e->flags |= 1;
    if (def->flags & 1) {
        Unk02063d84 *a = 0;
        if (data_020c4390.archive->func_02093ef4(func_0209a3c4(def->anim, ".nitro_animation"), 3) != -1) {
            func_02061298(e, 0, (def->flags & 0x200) ? true : false, 16);
            a = func_02063e2c(def->anim, 0);
        }
        if (a != 0) {
            func_02063db8(a, (def->flags & 4) ? 1 : 0);
            func_02061298(e, a, false, 16);
            return;
        }
        func_02061298(e, 0, false, 16);
    } else if (!(def->flags & 0x800)) {
        func_02061298(e, 0, false, 16);
    }
}

void func_02061838(Unk02060d78 *e, u32 texanim) {
    if (e->texanim == texanim) {
        return;
    }
    func_0206189c(e);
    if (texanim == 0) {
        return;
    }
    Unk02093648 *archive = data_020c409c.resources;
    data_020c3ba4.texanims->func_02070688(archive, texanim, data_020c7d38.func_0208bcfc(e->index));
    e->texanim = texanim;
}

void func_0206189c(Unk02060d78 *e) {
    if (e->texanim == 0) {
        return;
    }
    Unk02093648 *archive = data_020c409c.resources;
    data_020c3ba4.texanims->func_0207072c(archive, e->texanim, data_020c7d38.func_0208bcfc(e->index));
    e->texanim = 0;
}

bool func_020618f4(Unk02060d78 *e, Unk0201c460 *o) {
    if (e->attached != 0 || o == 0) {
        return false;
    }
    e->attached = o;
    o->func_08();
    return true;
}

void func_02061930(Unk02060d78 *e) {
    if (e->attached == 0) {
        return;
    }
    if (!func_020a0b8c(data_020d6240.unk8, e->attached)) {
        delete e->attached;
        e->attached = 0;
        return;
    }
    e->attached->func_18();
    e->attached->func_24();
    e->attached = 0;
}

Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir) {
    switch (dir.v) {
    case 0:
        return Unk020680d4Xy(p.x, p.y);
    case 1:
        return Unk020680d4Xy(p.y, item->func_24() - 1 - p.x);
    case 2:
        return Unk020680d4Xy(item->func_24() - 1 - p.x, item->func_28() - 1 - p.y);
    case 3:
        return Unk020680d4Xy(item->func_28() - 1 - p.y, p.x);
    }
    return Unk020680d4Xy(p.x, p.y);
}

bool func_02061ab4(Unk02061d08Item *item, const Unk020680d4Cell *cell) {
    Unk020680d4Cell c = item->func_14();
    if (cell->pos.unk2 != c.pos.unk2) {
        return false;
    }
    if (cell->pos.unk0 != c.pos.unk0) {
        return false;
    }
    if (cell->xy.x < c.xy.x) {
        return false;
    }
    if (cell->xy.y < c.xy.y) {
        return false;
    }
    Unk020680d4Xy size = item->func_20();
    if (cell->xy.x >= c.xy.x + size.x) {
        return false;
    }
    return cell->xy.y < c.xy.y + size.y;
}

Unk02061b90::Unk02061b90(Unk0205cf00 *def) : Unk02099c78(def->script) {}

Unk02061b90::~Unk02061b90() {}

bool Unk02061b90::vfunc_00(int key) {
    return key == 0x164079fa;
}

short Unk02061b90::vfunc_04(int index) {
    return 0;
}

void Unk02061b90::vfunc_08(int index, short value) {}

int Unk02061b90::vfunc_14(int arg, Unk02099c78Call *call) {
    return func_0205afc8(arg, call);
}

Unk02061c04::Unk02061c04(Unk02061d08Item *item) : Unk02099c78(item->def->script) {
    this->item = item;
}

Unk02061c04::~Unk02061c04() {}

bool Unk02061c04::vfunc_00(int key) {
    return key == (int)0xdbbf2534;
}

short Unk02061c04::vfunc_04(int index) {
    if (index < 0 || index >= unk8) {
        return 0;
    }
    return item->vars[index];
}

void Unk02061c04::vfunc_08(int index, short value) {
    if (index < 0) {
        return;
    }
    if (index >= unk8) {
        return;
    }
    Unk02099c78Var *vars = res->func_0209585c();
    if (vars != 0) {
        Unk02099c78Var *v = &vars[index];
        if (value > v->max) {
            value = v->max;
        } else if (value < v->min) {
            value = v->min;
        }
    }
    item->vars[index] = value;
}

int Unk02061c04::vfunc_14(int arg, Unk02099c78Call *call) {
    return func_0205afc8(arg, call);
}
