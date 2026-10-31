/*
 * Unit 0x0200318C-0x02003AB0: the action "Crafting": the sim stands in front of the object
 * and the survival guide opens on the recipe or on the object to build. Bounds: hypothesis
 * (from the description of the action, to the constructor of "Dig or Dive"; `.data` is the
 * name and the vtable, `.bss` the guard and the local description). The two setters stay
 * C-linkage functions, as `unit_02061D08.cpp` calls them. Layouts come from the code; all
 * names are placeholders.
 */
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

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

/* The sim that runs the action. */
class Unk020031d8Actor {
public:
    u8 unk0[0xc];
    Unk02061d08Item *sim;
};

struct Unk020031d8Cell {
    Unk020031d8Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
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
struct Unk020031d8Pos {
    Unk020031d8Cell func_add(Unk020680d4Xy d) const {
        return Unk020031d8Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* What is shown of an action. */
struct Unk020031d8Desc {
    Unk020031d8Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk020031d8Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

class Unk020031d8 : public Unk02002408 {
public:
    Unk020031d8();
    virtual ~Unk020031d8();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk020031d8Desc *func_20();

    int key;
    int object;
    int script;
    int state;
};

class Unk02027994;

class Unk0206bcf0 {
public:
    void func_0206f0ec(int a, int b, int c);

    u8 unk0[0x144];
    Unk02027994 *guide;
};

extern "C" {
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
Unk020031d8Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
Unk0205cf00 *func_02028ebc();
void func_02028ec8(Unk02027994 *o, u8 a, Unk02061d08Item *b);
void func_02028edc(Unk02027994 *o, int key);
void func_02028eec(Unk02027994 *o, int mode, Unk0205cf00 *def, void *p);
void func_0205e184(Unk02061d08Item *item, u32 key, Unk020031d8Actor *actor);
void func_0205ece8(Unk02061d08Item *item, int key);
int func_0205f6a4(void *db, int key);
Unk0205cf00 *func_0205f6f8(void *db, int id);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
Unk0206bcf0 *func_0206bce0();
extern u8 data_020c3fc4[];
}

static inline Unk020031d8Cell func_front(Unk02061d08Item *o) {
    return ((const Unk020031d8Pos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

static inline bool func_known(int key) {
    return func_0205f6a4(data_020c3fc4, key) != -1;
}

const Unk020031d8Desc *Unk020031d8::func_20() {
    static Unk020031d8Desc desc(4, 0, 0x18, "Crafting");
    return &desc;
}

Unk020031d8::Unk020031d8() {
    key = 0;
    object = 0;
    script = 0;
    state = 0;
}

Unk020031d8::~Unk020031d8() {
}

extern "C" void func_0200323c(Unk020031d8 *o, int key) {
    o->key = key;
    o->state = 1;
}

extern "C" void func_0200324c(Unk020031d8 *o, int object, int script) {
    if (func_known(object)) {
        o->object = object;
        o->script = script;
        o->state = 2;
    }
}

bool Unk020031d8::func_08() {
    return true;
}

int Unk020031d8::func_0c() {
    return state != 0;
}

int Unk020031d8::func_10() {
    int s = state;
    return s != 3 && s != 4;
}

int Unk020031d8::func_14() {
    if (!func_0200292c(owner)) {
        return 0;
    }
    Unk020031d8Actor *actor = func_02002414(owner);
    Unk02061d08Item *o = func_02002438(this);
    if (actor == 0 || o == 0) {
        return 2;
    }
    Unk02061d08Item *sim = actor->sim;
    if (sim == 0) {
        return 2;
    }
    if (func_front(o) != sim->func_14()) {
        return func_0200294c(this, 1);
    }
    return 1;
}

int Unk020031d8::func_18() {
    Unk020031d8Actor *actor = func_02002414(owner);
    Unk02061d08Item *o = func_02002438(this);
    Unk02061d08Item *sim = actor->sim;
    switch (state) {
    case 0:
        return 2;
    case 1:
        if (func_front(o) != sim->func_14()) {
            return 2;
        }
        sim->func_18(o->func_1c());
        switch (key) {
        case 0xe780812c:
        case 0xad4b65f7:
        case 0x2dfa05df:
        case 0x5f291f8d: {
            func_0205e184(o, 0xba0666a3, actor);
            func_0206bce0()->func_0206f0ec(0x10, 0, 0);
            Unk02027994 *guide = func_0206bce0()->guide;
            func_02028edc(guide, key);
            func_02028ec8(guide, 0, o);
            break;
        }
        case 0x89e11752: {
            func_0206bce0()->func_0206f0ec(0x11, 0, 0);
            Unk02027994 *guide = func_0206bce0()->guide;
            func_02028edc(guide, key);
            func_02028ec8(guide, 1, o);
            break;
        }
        default: {
            func_0206bce0()->func_0206f0ec(6, 0, 0);
            Unk02027994 *guide = func_0206bce0()->guide;
            func_02028edc(guide, key);
            func_02028ec8(guide, 1, o);
            break;
        }
        }
        state = 3;
        break;
    case 3:
        if (func_0206bce0()->guide == 0) {
            state = 5;
            return 1;
        }
        break;
    case 2: {
        if (func_front(o) != sim->func_14()) {
            return 2;
        }
        sim->func_18(o->func_1c());
        func_0206bce0()->func_0206f0ec(8, 0, 0);
        Unk02027994 *guide = func_0206bce0()->guide;
        func_02028eec(guide, 8, func_0205f6f8(data_020c3fc4, object), 0);
        func_02028ec8(guide, 1, o);
        state = 4;
        break;
    }
    case 4:
        if (func_0206bce0()->guide == 0) {
            if (func_02028ebc() != 0) {
                func_0205ece8(o, script);
            }
            state = 5;
            return 1;
        }
        break;
    case 5:
        return 1;
    default:
        return 2;
    }
    return 0;
}

void Unk020031d8::func_1c() {
    Unk020031d8Actor *actor = func_02002414(owner);
    Unk02061d08Item *o = func_02002438(this);
    switch (key) {
    case 0xe780812c:
    case 0xad4b65f7:
    case 0x2dfa05df:
    case 0x5f291f8d:
        func_0205e184(o, 0xd274ab12, actor);
        break;
    }
}
