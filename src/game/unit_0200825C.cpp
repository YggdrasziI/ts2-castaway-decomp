/*
 * Unit 0x0200825C-0x02008D48: the interaction base `Unk02008d18`: the sim walks to the
 * front of the object, runs the interaction of the current block of the object script
 * and shows the conversation attached to it. Bounds: hypothesis (from its constructor to
 * its destructors; `.data` is the two names and the vtable). Layouts come from the code;
 * all names are placeholders. func_24 (0x02008258) and func_28 (0x02004930) are declared
 * only: they sit out of this range.
 *
 * Open gaps: func_14 99.81 % (stack slots of the temporaries of the test, as in
 * unit_02008D48.cpp), func_18 99.73 % (the same slots, and r12 / r6 swapped between the
 * zero of the vectors and the sim). The casts to `Unk02008d18Pos` and `Unk02008d18Facing`
 * are workarounds.
 */
#include "game/unk_objscript.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
    u8 unk4[0xc];
    Unk020956f8 *script;
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
class Unk02008d18Actor {
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

struct Unk020615f0Def {
    u8 unk0[0x24];
    int key;
    u8 unk28[8];
    u32 flags;
};

struct Unk02008d18Panel;

class Unk0206bcf0 {
public:
    u8 unk0[0x11c];
    Unk02008d18Panel *panel;
    u8 unk120[0x24];
    int unk144;
};

/* The conversation of the action. */
class Unk0201c460 {
public:
    Unk0201c460(u32 key);
    virtual ~Unk0201c460();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    void func_0201cf6c(Unk020680d4Vec pos, Unk020680d4Vec offset);

    u8 unk4[0x3c];
    u32 flags;
    u8 unk44[0x44];
};

struct Unk02008d18System {
    u8 unk0[8];
    void *list;
};

/* What is shown of an action. */
struct Unk02008d18Desc;

/* A cell built from its parts. */
struct Unk02008d18Cell {
    Unk02008d18Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    bool operator!=(const Unk020680d4Cell &o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A cell that adds an offset to itself. */
struct Unk02008d18Pos {
    Unk02008d18Cell func_add(Unk020680d4Xy d) const {
        return Unk02008d18Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

struct Unk02008d18Facing {
    bool func_same(Unk020680d4Dir b) const {
        return v == b.v;
    }

    int v;
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
    virtual const Unk02008d18Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

class Unk02008d18 : public Unk02002408 {
public:
    Unk02008d18();
    virtual ~Unk02008d18();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual void func_24();
    virtual int func_28();
    virtual void func_2c() = 0;

    Unk02099c78Value *func_02008abc(Unk020956f8 *script, Unk02099c78Block *block, u32 key);
    bool func_02008b14();

    int block;
    bool active;
    bool free;
    int unk28;
    Unk0201c460 *conversation;
};

extern "C" {
Unk02008d18Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
void func_02020938(Unk02008d18Panel *p, int need);
void func_0205aff0(void *c, int i, int v);
int func_0205b00c(void *c, int i);
void func_0205b030(void *c);
void func_0205b074(void *c, int a, Unk02061d08Item *target, Unk02008d18Actor *actor);
Unk020615f0Def func_0205c8b4(Unk0205cf00 *def, Unk02099c78Block *block);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
bool func_0205d340(Unk0205cf00 *def, u32 key);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, Unk02008d18Actor *actor);
void func_0205e1b8(Unk02061d08Item *item, Unk02008d18Actor *actor);
bool func_0206135c(Unk02060d78 *e);
Unk020680d4Vec func_020613f0(Unk02060d78 *e, const char *name, Unk020680d4Vec offset);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
void func_020667f8(Unk02008d18Actor *actor, int a);
bool func_020691c4(void *sim);
Unk020680d4Vec func_0206920c(void *sim, const char *name, Unk020680d4Vec offset);
Unk0206bcf0 *func_0206bce0();
u32 func_0209a3c4(u32 h, const char *s);
int func_020a0b8c(void *list, void *object);
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020c3cc8[];
extern Unk02008d18System data_020d6240;
}

enum Unk02008d18Found {
    UNK_02008D18_MISSING,
    UNK_02008D18_FOUND
};

static inline Unk02008d18Found func_found(void *p) {
    return p != 0 ? UNK_02008D18_FOUND : UNK_02008D18_MISSING;
}

static inline bool func_away(Unk02061d08Item *o, Unk020680d4Cell c) {
    Unk020680d4Xy size(o->def->w, o->def->h);
    Unk020680d4Xy rel = func_020619a8(o, size, o->func_1c());
    return ((const Unk02008d18Pos &)o->func_14()).func_add(rel) != c;
}

Unk02008d18::Unk02008d18() {
    block = -1;
    active = false;
    free = true;
    unk28 = 0;
    conversation = 0;
}

bool Unk02008d18::func_08() {
    s8 map = data_020c3ba4.map;
    if (map != func_02002438(this)->func_14().pos.unk3) {
        return false;
    }
    return map == func_02002414(owner)->func_14().pos.unk3;
}

int Unk02008d18::func_0c() {
    return 0;
}

int Unk02008d18::func_10() {
    Unk02008d18Actor *actor = func_02002414(owner);
    if (func_02002438(this) != 0 && active) {
        func_0205e1b8(func_02002438(this), actor);
    }
    return 1;
}

int Unk02008d18::func_14() {
    Unk02008d18Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk02061d08Item *sim;
    sim = actor->sim;
    o = func_02002438(this);
    if (!func_0200292c(owner)) {
        return 0;
    }
    if (func_away(o, sim->func_14())) {
        return func_0200294c(this, 1);
    }
    Unk0205cf00 *def = o->def;
    func_0205e038(o, func_0205cea4(def, block), actor);
    Unk0205cf00 *def2 = o->def;
    const Unk020615f0Def &d = func_0205c8b4(def2, func_0205cea4(def, block));
    if (d.flags & 0x40) {
        conversation = new Unk0201c460(d.key);
        conversation->func_08();
    }
    active = true;
    func_0200264c(this);
    sim->func_18(o->func_1c());
    func_24();
    return 1;
}

int Unk02008d18::func_18() {
    Unk02008d18Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk02061d08Item *sim;
    sim = actor->sim;
    o = func_02002438(this);
    if (func_away(o, sim->func_14()) || !((const Unk02008d18Facing &)sim->func_1c()).func_same(o->func_1c())) {
        return 2;
    }
    if (func_0206bce0()->unk144 != 0) {
        return 0;
    }
    if (conversation != 0) {
        Unk02061d08Item *head = actor->sim;
        conversation->func_0201cf6c(func_0206920c(head, "head", Unk020680d4Vec(0, 0, 0)),
                                    func_020613f0(o->visible, "head", Unk020680d4Vec(0, 0, 0)));
    }
    Unk0205cf00 *def = o->def;
    const Unk020615f0Def &d = func_0205c8b4(def, func_0205cea4(def, block));
    if ((d.flags & 2) && sim != 0) {
        if (!func_020691c4(sim)) {
            return 0;
        }
    }
    if ((d.flags & 1) && o->visible != 0) {
        if (!func_0206135c(o->visible)) {
            return 0;
        }
    }
    if (conversation != 0 && (conversation->flags & 4)) {
        conversation->func_18();
        if (func_0205d340(def, 0x0d933e26)) {
            if (func_0205d340(def, 0x0e2508ee)) {
                func_02020938(func_0206bce0()->panel, 0);
            } else if (func_0205d340(def, 0x4089a7c6)) {
                func_02020938(func_0206bce0()->panel, 1);
            } else if (func_0205d340(def, 0x61aadad6)) {
                func_02020938(func_0206bce0()->panel, 2);
            } else if (func_0205d340(def, 0xaaba8051)) {
                func_02020938(func_0206bce0()->panel, 3);
            }
        }
    }
    if (conversation != 0 && !func_020a0b8c(data_020d6240.list, conversation)) {
        delete conversation;
        conversation = 0;
    }
    if (func_02008b14()) {
        return 0;
    }
    if (conversation != 0) {
        return 0;
    }
    func_0205e1b8(o, free ? actor : 0);
    return func_28();
}

void Unk02008d18::func_1c() {
    if (conversation != 0) {
        conversation->func_18();
    }
    conversation = 0;
    func_2c();
    if (free) {
        func_020667f8(func_02002414(owner), 0xa);
    }
}

Unk02099c78Value *Unk02008d18::func_02008abc(Unk020956f8 *script, Unk02099c78Block *block, u32 key) {
    Unk02099c78Value *values = script->func_02095ab0();
    for (int i = block->func_start(); i < block->func_end(); i++) {
        if (key == values[i].unk0) {
            return &values[i];
        }
    }
    return 0;
}

bool Unk02008d18::func_02008b14() {
    Unk02061d08Item *o = func_02002438(this);
    Unk02008d18Actor *actor = func_02002414(owner);
    int next;
    Unk0205cf00 *def;
    Unk020956f8 *script;
    Unk02099c78Block *current;
    def = o->def;
    current = func_0205cea4(def, block);
    script = def->script;
    next = -1;
    Unk02061c04 runner(o);
    func_0205b030(data_020c3cc8);
    Unk02099c78Value *value = func_02008abc(script, current, 0x4966402b);
    if (value != 0) {
        next = script->func_0209599c(value->unk4);
    } else {
        value = func_02008abc(script, current, 0x17888c61);
        if (value != 0) {
            func_0205aff0(data_020c3cc8, 0, 0);
            runner.func_02099ce0(value->unk4);
            int key = func_0205b00c(data_020c3cc8, 0);
            if (key != 0) {
                next = script->func_0209599c(key);
            }
        }
    }
    if (next != -1) {
        block = next;
        current = func_0205cea4(def, next);
        func_0205e038(o, current, actor);
        value = func_02008abc(script, current, 0x2d81e2b8);
        if (value != 0 && func_found(script->func_020957ec(value->unk4)) != UNK_02008D18_MISSING) {
            func_0205b074(data_020c3cc8, block, o, actor);
            runner.func_02099ce0(value->unk4);
        }
        if (conversation == 0) {
            value = func_02008abc(script, current, 0x29ac88ab);
            if (value != 0) {
                u32 key = func_0209a3c4(value->unk4, ".conversation.nitro_xml");
                conversation = new Unk0201c460(key);
                conversation->func_08();
            }
        }
        return true;
    }
    return false;
}

Unk02008d18::~Unk02008d18() {
}
