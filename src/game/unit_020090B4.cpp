/*
 * Unit 0x020090B4-0x02009404: the action "cAction ShakeTree": the sim stands in front
 * of the tree and plays two animations. Bounds: hypothesis (from the description of the
 * action to its last vtable slot; `.data` is the name and the vtable, `.bss` the guard
 * and the local description). Layouts come from the code; all names are placeholders.
 *
 * Open gap: func_18 99.93 % (order of two `mov` of the arguments). `state` is `volatile` as a hypothesis: the original stores 3, then 2.
 * The casts to `Unk020093ecPos` and `Unk020093ecFacing` are workarounds for inline
 * members on temporaries.
 */
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

class Unk02060d78;

class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *visible;
};

class Unk020093ecActor {
public:
    u8 unk0[0xc];
    Unk02061d08Item *sim;
};

/* What is shown of an action. */
struct Unk020093ecDesc {
    Unk020093ecDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

/* A cell built from its parts. */
struct Unk020093ecCell {
    Unk020093ecCell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    bool operator!=(Unk020680d4Cell o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A cell that adds an offset to itself. */
struct Unk020093ecPos {
    Unk020093ecCell func_add(Unk020680d4Xy d) const {
        return Unk020093ecCell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

class Unk02002408 {
public:
    virtual ~Unk02002408();
    void operator delete(void *p);
    virtual bool func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk020093ecDesc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

class Unk020071d4 : public Unk02002408 {
public:
    virtual ~Unk020071d4() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual void func_24();
    virtual void func_28();
    virtual void func_2c() = 0;

    int unk20;
    bool unk24;
};

class Unk020093ec : public Unk020071d4 {
public:
    virtual int func_18();
    virtual const Unk020093ecDesc *func_20();
    virtual void func_2c() {}

    volatile int state;
};

extern "C" {
Unk020093ecActor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
bool func_0206135c(Unk02060d78 *e);
bool func_020691c4(void *sim);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
int func_02063e2c(int a, int b);
void func_02069124(void *sim, int anim, int a, int b);
void func_0205e1b8(Unk02061d08Item *item, void *p);
}

struct Unk020093ecFacing {
    bool func_same(Unk020680d4Dir b) const {
        return v == b.v;
    }

    int v;
};

static inline Unk020093ecCell func_front(Unk02061d08Item *o) {
    return ((const Unk020093ecPos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

const Unk020093ecDesc *Unk020093ec::func_20() {
    static Unk020093ecDesc desc(0xc, 0, 0xd, "cAction ShakeTree");
    return &desc;
}

int Unk020093ec::func_18() {
    Unk02061d08Item *o = func_02002438(this);
    Unk020093ecActor *actor;
    bool visible;
    bool done;
    Unk02061d08Item *sim;
    func_02002438(this);
    actor = func_02002414(owner);
    sim = actor->sim;
    visible = func_0206135c(o->visible);
    done = func_020691c4(sim);
    switch (state) {
    case 0:
        if (func_front(o) != sim->func_14() || !((const Unk020093ecFacing &)sim->func_1c()).func_same(o->func_1c())) {
            return 2;
        }
        if (!done || !visible) {
            return 0;
        }
        break;
    case 1:
        if (!done || !visible) {
            return 0;
        }
        state = 3;
        func_02069124(sim, func_02063e2c(0, 2), 0xa, 0);
        state = 2;
        break;
    case 2:
        if (!done) {
            return 0;
        }
        func_02069124(sim, func_02063e2c(0, 2), 0xa, 0);
        state = 4;
        break;
    case 3:
    case 4:
        if (!done) {
            return 0;
        }
        break;
    }
    func_0205e1b8(o, actor);
    return 1;
}
