/*
 * Unit 0x02006CAC-0x02007204: the base action `Unk020071d4`: the sim walks to the front
 * of the object and runs the block of the object script whose index is its key. Bounds:
 * hypothesis (after the inline destructors of the file before it, up to the action pool;
 * `.data` is the vtable; the last functions are its inline destructors). Layouts come
 * from the code; all names are placeholders. func_24 and func_28 (0x0200124C, 0x02001254)
 * are declared only: they sit out of this range.
 */
#include "game/unk_script.h"
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
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *visible;
};

/* The sim that runs the action. */
class Unk020071d4Actor {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 unk4[8];
    Unk02061d08Item *sim;
};

struct Unk020071d4Desc;

/* A cell built from its parts. */
struct Unk020071d4Cell {
    Unk020071d4Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
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
struct Unk020071d4Pos {
    Unk020071d4Cell func_add(Unk020680d4Xy d) const {
        return Unk020071d4Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

struct Unk020071d4Facing {
    bool func_same(Unk020680d4Dir b) const {
        return v == b.v;
    }

    int v;
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
    virtual const Unk020071d4Desc *func_20() = 0;

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
    virtual bool func_24();
    virtual int func_28();
    virtual void func_2c() = 0;

    int key;
    bool active;
};

extern "C" {
Unk020071d4Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, Unk020071d4Actor *actor);
void func_0205e1b8(Unk02061d08Item *item, Unk020071d4Actor *actor);
bool func_0206135c(Unk02060d78 *e);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
void func_020667f8(Unk020071d4Actor *actor, int a);
bool func_020691c4(void *sim);
extern Unk020c3ba4 data_020c3ba4;
}

static inline Unk020071d4Cell func_front(Unk02061d08Item *o) {
    return ((const Unk020071d4Pos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

bool Unk020071d4::func_08() {
    s8 map = data_020c3ba4.map;
    if (map != func_02002438(this)->func_14().pos.unk3) {
        return false;
    }
    return map == func_02002414(owner)->func_14().pos.unk3;
}

int Unk020071d4::func_0c() {
    return 0;
}

int Unk020071d4::func_10() {
    Unk020071d4Actor *actor = func_02002414(owner);
    if (func_02002438(this) != 0 && active) {
        func_0205e1b8(func_02002438(this), actor);
    }
    return 1;
}

int Unk020071d4::func_14() {
    Unk020071d4Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk02061d08Item *sim;
    sim = actor->sim;
    o = func_02002438(this);
    if (!func_0200292c(owner)) {
        return 0;
    }
    if (func_front(o) != sim->func_14()) {
        return func_0200294c(this, 1);
    }
    if (!func_24()) {
        func_0205e038(o, func_0205cea4(o->def, key), actor);
    }
    active = true;
    func_0200264c(this);
    sim->func_18(o->func_1c());
    return 1;
}

int Unk020071d4::func_18() {
    Unk020071d4Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk02061d08Item *sim;
    sim = actor->sim;
    o = func_02002438(this);
    if (func_front(o) != sim->func_14() || !((const Unk020071d4Facing &)sim->func_1c()).func_same(o->func_1c())) {
        return 2;
    }
    if (!func_020691c4(sim)) {
        return 0;
    }
    if (!func_0206135c(o->visible)) {
        return 0;
    }
    return func_28();
}

void Unk020071d4::func_1c() {
    func_2c();
    func_020667f8(func_02002414(owner), 0xa);
}
