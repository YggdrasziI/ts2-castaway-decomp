/*
 * Unit 0x0200125C-0x02001FDC: the "ChangeLot" actions: the sim walks or the screen fades,
 * then the game changes lot; `Unk0200125c` is their base and the four others the actions
 * "cAction ChangeLot" and "cAction Special ChangeLot". Bounds: hypothesis (from the base
 * constructor to their inline destructors; `.data` is the two names and the five vtables,
 * `.bss` the guards and the local descriptions). Layouts come from the code; all names are
 * placeholders.
 */
#include "game/unk_action.h"
#include "game/unk_objscript.h"

struct Unk02000ba0Cell {
    Unk02000ba0Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
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
struct Unk02000ba0Pos {
    Unk02000ba0Cell func_add(Unk020680d4Xy d) const {
        return Unk02000ba0Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* The base of the "ChangeLot" actions. */
class Unk0200125c : public Unk02002408 {
public:
    Unk0200125c();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual void func_1c();
    bool func_02001358();
    void func_020014d4(Unk02061d08Item *item, Unk020680d4 *sim, u32 key);
    void func_020015a8(bool done);

    Unk020680d4Vec pos;
    Unk02061d08Item *item;
    int angle;
    int lot;
    int phase;
    u32 wait;
    bool walk;
    bool first;
    bool turn;
    int map;
};

class Unk02001f98 : public Unk0200125c {
public:
    virtual int func_14();
    virtual int func_18();
    virtual const Unk02000ba0Desc *func_20();
};

class Unk02001f68 : public Unk0200125c {
public:
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02000ba0Desc *func_20();
};

class Unk02001f38 : public Unk0200125c {
public:
    virtual int func_14();
    virtual int func_18();
    virtual const Unk02000ba0Desc *func_20();
};

class Unk02001f08 : public Unk0200125c {
public:
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02000ba0Desc *func_20();
};

extern "C" {
void func_02007d94(void *queue);
Unk020680d4Cell func_02057a54(Unk02058788 *map, const Unk02098ff0 *pos);
Unk02058788 *func_02058788(void *world, int map);
void func_02058cd8(void *world, int a, int b);
bool func_02059418(const Unk020593e4 *cell);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
bool func_0205d2c8(Unk0205cf00 *def, u32 a, u32 key);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
void func_020667f8(Unk02000ba0Actor *p, int a);
int func_020676b4(Unk02000ba0Actor *p);
int func_02067708(Unk02000ba0Actor *p, int a, int b);
void func_02067778(Unk02000ba0Actor *p, Unk020680d4Cell cell);
void func_020a1eb4(Unk02098ff0 *pos, Unk02098ff0 *out, s16 angle, int speed);
extern u8 data_020c4770[];
}

static inline Unk02000ba0Cell func_front(Unk02061d08Item *o) {
    return ((const Unk02000ba0Pos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

Unk0200125c::Unk0200125c() {
    item = 0;
    angle = 0;
    lot = -1;
    phase = 1;
    wait = 0;
    walk = false;
    first = true;
    turn = false;
}

bool Unk0200125c::func_08() {
    return map == func_02058788(&data_020c3ba4, data_020c3ba4.map)->unk24;
}

int Unk0200125c::func_0c() {
    return 0;
}

extern "C" void func_020012ec(Unk0200125c *o, Unk02061d08Item *item, int lot, int map) {
    o->item = item;
    o->lot = lot;
    o->angle = 0;
    o->wait = 0;
    o->walk = false;
    o->turn = false;
    o->map = map;
}

extern "C" void func_02001318(Unk0200125c *o, Unk02061d08Item *item, int lot, int map, u32 wait, int angle,
                              bool walk, bool turn) {
    o->item = item;
    o->lot = lot;
    o->angle = angle;
    o->wait = wait;
    o->walk = walk;
    o->turn = turn;
    o->map = map;
}

int Unk0200125c::func_10() {
    return 1;
}

bool Unk0200125c::func_02001358() {
    Unk02000ba0Actor *actor = func_02002414(this);
    int speed = func_020676b4(actor);
    int a = func_02067708(actor, angle, 0x1f4);
    if (first) {
        speed = 0;
        first = false;
    }
    Unk020680d4Vec out;
    func_020a1eb4(&pos.v, &out.v, a, speed);
    actor->func_00(out.v);
    if (speed >= 0xfce) {
        pos = out;
        Unk020680d4Cell cell = func_02057a54(func_02058788(&data_020c3ba4, data_020c3ba4.map), &pos.v);
        if (func_02059418(&cell.pos) && cell.xy.x >= 0 && cell.xy.y >= 0) {
            actor->func_10(cell);
            func_02067778(actor, cell);
        }
        return true;
    }
    return false;
}

void Unk0200125c::func_1c() {
    func_02007d94(data_020c4770);
    func_0206bce0()->func_0206ea00(lot, 1);
}

void Unk0200125c::func_020014d4(Unk02061d08Item *item, Unk020680d4 *sim, u32 key) {
    Unk0205cf00 *def = item->def;
    Unk020680d4Dir dir = item->func_1c();
    if (func_0205d2c8(def, 0x22d6e5e0, key)) {
        switch (func_0205d1b4(def, key)) {
        case 0xd82a09e8:
            dir = Unk020680d4Dir(0);
            break;
        case 0xfa6fc214:
            dir = Unk020680d4Dir(1);
            break;
        case 0x30a71683:
            dir = Unk020680d4Dir(2);
            break;
        case 0x1202d214:
            dir = Unk020680d4Dir(3);
            break;
        }
    }
    sim->func_18(dir);
}

void Unk0200125c::func_020015a8(bool done) {
    if (item == 0) {
        return;
    }
    u32 key = done ? 0x275ad95c : 0xc7ba0bce;
    if (item->def->script->func_020957ec(key) == 0) {
        return;
    }
    Unk02061c04 runner(item);
    runner.func_02099ce0(key);
}

const Unk02000ba0Desc *Unk02001f98::func_20() {
    static Unk02000ba0Desc desc(0, 0, 0x19, "cAction ChangeLot");
    return &desc;
}

int Unk02001f98::func_14() {
    if (wait == 0) {
        func_020a1494(func_020a18e4(), 2, 0x10);
        func_020a11f8(func_020a18e4(), 2, 1);
    }
    if (walk) {
        Unk02000ba0Actor *actor = func_02002414(this);
        pos = (const Unk020680d4Vec &)actor->func_04();
        Unk020680d4Vec target = pos;
        func_020a1eb4(&target.v, &target.v, angle, 0x1000);
        Unk020680d4Cell cell =
            func_02057a54(func_02058788(&data_020c3ba4, data_020c3ba4.map), &target.v);
        func_02067778(actor, cell);
    }
    func_0200264c(this);
    return 1;
}

int Unk02001f98::func_18() {
    bool done = false;
    if (walk) {
        done = func_02001358();
    }
    if (done && wait > 1) {
        if (--wait == 1) {
            if (turn) {
                angle += 0x4000;
            }
            func_020a1494(func_020a18e4(), 2, 0x10);
            func_020a11f8(func_020a18e4(), 2, 1);
        }
    }
    if (!func_020a1280(func_020a18e4(), 2, 1)) {
        return 0;
    }
    func_020015a8(false);
    return 1;
}

const Unk02000ba0Desc *Unk02001f68::func_20() {
    static Unk02000ba0Desc desc(0, 0, 0x1a, "cAction ChangeLot");
    return &desc;
}

int Unk02001f68::func_14() {
    Unk02000ba0Actor *actor = func_02002414(this);
    pos = (const Unk020680d4Vec &)actor->func_04();
    Unk020680d4Vec target = pos;
    func_020a1eb4(&target.v, &target.v, angle, 0x1000);
    Unk020680d4Cell cell = func_02057a54(func_02058788(&data_020c3ba4, data_020c3ba4.map), &target.v);
    func_02067778(actor, cell);
    func_0200264c(this);
    return 1;
}

int Unk02001f68::func_18() {
    if (!func_02001358()) {
        return 0;
    }
    func_020667f8(func_02002414(this), 0xa);
    func_020015a8(true);
    return 1;
}

void Unk02001f68::func_1c() {
}

const Unk02000ba0Desc *Unk02001f38::func_20() {
    static Unk02000ba0Desc desc(0, 0, 0x1b, "cAction Special ChangeLot");
    return &desc;
}

int Unk02001f38::func_14() {
    Unk02000ba0Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk020680d4 *sim = actor->sim;
    o = func_02002438(this);
    if (!func_0200292c(owner)) {
        return 0;
    }
    if (func_front(o) != sim->func_14()) {
        return func_0200294c(this, 1);
    }
    func_020014d4(o, sim, 0xba4d9ebf);
    func_0205e184(o, 0x5d704ff5, actor);
    func_0200264c(this);
    phase = 0;
    return 1;
}

int Unk02001f38::func_18() {
    Unk02000ba0Actor *actor = func_02002414(owner);
    func_02002438(this);
    if (phase == 0) {
        if (func_020691c4(actor->sim)) {
            func_020a1494(func_020a18e4(), 2, 0x10);
            func_020a11f8(func_020a18e4(), 2, 1);
            phase = 1;
        }
    } else if (func_020a1280(func_020a18e4(), 2, 1)) {
        func_020015a8(false);
        return 1;
    }
    return 0;
}

const Unk02000ba0Desc *Unk02001f08::func_20() {
    static Unk02000ba0Desc desc(0, 0, 0x1c, "cAction Special ChangeLot");
    return &desc;
}

int Unk02001f08::func_14() {
    Unk02000ba0Actor *actor = func_02002414(owner);
    Unk02061d08Item *o;
    Unk020680d4 *sim = actor->sim;
    o = func_02002438(this);
    if (!func_0200292c(owner)) {
        return 0;
    }
    if (func_front(o) != sim->func_14()) {
        return func_0200294c(this, 1);
    }
    func_020014d4(o, sim, 0x8283aa1a);
    func_0205e184(o, 0xcdffc907, actor);
    func_0200264c(this);
    return 1;
}

int Unk02001f08::func_18() {
    Unk02000ba0Actor *actor = func_02002414(owner);
    if (func_020691c4(actor->sim)) {
        if (func_02058788(&data_020c3ba4, data_020c3ba4.map)->unk24 == 0x1e) {
            func_02058cd8(&data_020c3ba4, 0x1e, 0);
        } else {
            func_020667f8(actor, 0xa);
        }
        func_020015a8(true);
        return 1;
    }
    return 0;
}

void Unk02001f08::func_1c() {
    func_0206bce0()->func_0206dd24();
}
