/*
 * Unit 0x02002B80-0x0200318C: the action "Move" with member function callbacks: the sim
 * goes to the front of the object (it queues a move action until it stands there), runs a
 * block of the object script, then waits for a callback of the player. Bounds: hypothesis
 * (from the description of the action, to the description of "Crafting"; `.data` is the
 * name and the vtable, `.bss` the guard and the local description). Layouts come from the
 * code; all names are placeholders.
 */
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

struct Unk02099c78Block;

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
};

struct Unk02002bc8Cell {
    Unk02002bc8Cell() {
    }
    Unk02002bc8Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
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
struct Unk02002bc8Pos {
    Unk02002bc8Cell func_add(Unk020680d4Xy d) const {
        return Unk02002bc8Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* What is shown of an action. */
struct Unk02002bc8Desc {
    Unk02002bc8Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

class Unk02002408 {
public:
    Unk02002408();
    virtual ~Unk02002408();
    void operator delete(void *p);
    virtual bool func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk02002bc8Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

class Unk02002bc8;

/* The player. */
class Unk02002bc8Actor {
public:
    typedef bool (Unk02002bc8Actor::*Callback)(Unk02061d08Item *o, Unk02002bc8 *action);

    u8 unk0[0xc];
    Unk02061d08Item *sim;
    u8 unk10[0x3b8];
    u8 list[4];
};

class Unk02002bc8 : public Unk02002408 {
public:
    Unk02002bc8();
    virtual ~Unk02002bc8();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02002bc8Desc *func_20();

    Unk02002bc8Actor *player;
    Unk02002bc8Actor::Callback done;
    Unk02002bc8Actor::Callback ready;
    s16 block;
    s16 wait;
    u16 flags;
    s16 count;
};

struct Unk02002bc8Next {
    void func_set(Unk02002bc8Cell c) {
        cell = c;
    }

    u8 unk0[4];
    u32 flags;
    u8 unk8[0x2c];
    Unk02002bc8Cell cell;
};

extern "C" {
void func_0200264c(Unk02002408 *a);
void *func_02002734(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
Unk02002bc8Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
Unk02002bc8Next *func_02007340(void *pool, int kind);
void func_02007edc(void *list, Unk02002bc8Next *next, Unk02002408 *owner);
void func_02008064(void *list, Unk02002408 *a);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, Unk02002bc8Actor *actor);
void func_0205e1b8(Unk02061d08Item *item, Unk02002bc8Actor *actor);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
extern u8 data_020be184[];
}

static inline Unk02002bc8Cell func_front(Unk02061d08Item *o) {
    return ((const Unk02002bc8Pos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

const Unk02002bc8Desc *Unk02002bc8::func_20() {
    static Unk02002bc8Desc desc(1, 0, 0, "Move");
    return &desc;
}

Unk02002bc8::Unk02002bc8() {
    player = 0;
    done = 0;
    ready = 0;
    block = -1;
    wait = 0;
    flags = 0;
    count = 0;
    if (player != 0) {
        func_02008064(player->list, this);
        flags |= 8;
    }
}

bool Unk02002bc8::func_08() {
    Unk02002bc8Actor *actor = func_02002414(owner);
    if (actor == 0) {
        return false;
    }
    return (actor->*ready)(func_02002438(this), this);
}

int Unk02002bc8::func_0c() {
    return 0;
}

int Unk02002bc8::func_10() {
    if (flags & 8) {
        func_02008064(player->list, this);
        flags &= ~8;
    }
    if (flags & 1) {
        Unk02002bc8Actor *actor = func_02002414(owner);
        func_0205e1b8(func_02002438(this), actor);
    }
    return 1;
}

int Unk02002bc8::func_14() {
    Unk02002bc8Actor *actor = func_02002414(owner);
    Unk02061d08Item *sim = actor->sim;
    if (func_0200292c(owner)) {
        if (func_front(func_02002438(this)) != sim->func_14()) {
            Unk02002bc8Next *next = func_02007340(data_020be184, 0);
            if (next == 0) {
                return 2;
            }
            next->func_set(func_front(func_02002438(this)));
            Unk02002408 *a = owner;
            func_02007edc(func_02002734(a), next, a);
            next->flags |= 0x10;
            return 0;
        }
    } else {
        return 0;
    }
    Unk02061d08Item *o = func_02002438(this);
    func_0205e038(func_02002438(this), func_0205cea4(o->def, block), actor);
    flags |= 1;
    func_0200264c(this);
    sim->func_18(func_02002438(this)->func_1c());
    return 1;
}

int Unk02002bc8::func_18() {
    count++;
    if (!(flags & 4) && count >= wait) {
        Unk02002bc8Actor *actor = func_02002414(owner);
        Unk02061d08Item *o = func_02002438(this);
        if ((actor->*done)(o, this)) {
            flags |= 4;
            if (flags & 8) {
                func_02008064(player->list, this);
                flags &= ~8;
            }
        }
    }
    if (flags & 2) {
        Unk02061d08Item *o = func_02002438(this);
        func_0205e1b8(o, func_02002414(owner));
        return 1;
    }
    return 0;
}

void Unk02002bc8::func_1c() {
}

Unk02002bc8::~Unk02002bc8() {
}
