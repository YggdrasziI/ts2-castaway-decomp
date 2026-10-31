/*
 * Unit 0x02004FBC-0x02005AF0: the move actions: the sim walks cell by cell to a target
 * cell, in two derived classes ("Move" and "Action Exit", kinds 0 and 1 of the action
 * factory); func_02005654 finds the exit of a lot. Bounds: hypothesis (from the first
 * function of the base vtable to the last inline function; `.data` is four strings and
 * three vtables, `.bss` the guards and local descriptions). The constructors are inline in
 * the action factory (`unit_02007204.cpp`). Layouts come from the code; all names are
 * placeholders.
 */
#include "game/unk_sim.h"

class Unk02058788 {
public:
    u8 unk0[0x24];
    int lot;
};

class Unk0205cf00;

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
    s16 height;
};

class Unk02056ed0 {
public:
    u32 *func_tile(u32 x, u32 y) {
        return &tiles[y * info->width + x];
    }

    u8 unk0[8];
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;
};

/* A scene object. */
class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual Unk02098ff0 func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 list[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x1c];
    Unk02061d08Item *next;
};

class Unk0205f098;

extern "C" {
void func_0205f098(Unk0205f098 *list);
void func_0205f0a8(Unk0205f098 *list);
}

class Unk0205f098 {
public:
    Unk0205f098() {
        func_0205f098(this);
    }
    ~Unk0205f098() {
        func_0205f0a8(this);
    }

    Unk02061d08Item *head;
    int count;
};

struct Unk02005ad4Sim {
    u8 unk0[0x160];
    void *unk160;
};

/* The player. */
class Unk02005ad4Actor {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();

    Unk020680d4Cell target;
    Unk02005ad4Sim *sim;
};

/* What is shown of an action. */
struct Unk02005ad4Desc {
    Unk02005ad4Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
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
    virtual const Unk02005ad4Desc *func_20() = 0;

    u32 flags;
    u8 unk8[0x18];
};

/* Assigned as a block. */
struct Unk02005ad4Pos {
    Unk02098ff0 v;
};

class Unk02005ad4 : public Unk02002408 {
public:
    virtual bool func_08();
    virtual int func_0c() {
        return 0;
    }
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();

    Unk02005ad4Pos pos;
    Unk020680d4Cell cell0;
    Unk020680d4Cell cell1;
    int angle;
    bool diagonal;
    bool done;
    bool started;
    bool stop;
};

class Unk02005aa4 : public Unk02005ad4 {
public:
    virtual void func_1c();
    virtual const Unk02005ad4Desc *func_20();
};

class Unk02005a74 : public Unk02005ad4 {
public:
    virtual void func_1c();
    virtual const Unk02005ad4Desc *func_20();

    void func_target(Unk020680d4Cell c) {
        cell1 = c;
    }

    bool failed;
};

class Unk0206bcf0 {
public:
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
};

extern "C" {
Unk02005ad4Actor *func_02002414(void *a);
void func_0200264c(Unk02002408 *a);
void func_02001318(void *o, Unk02061d08Item *item, int a, int map, int b, int y, int c, int d);
int func_0200527c(Unk02005ad4 *o, Unk02005ad4Actor *actor, Unk02005ad4Sim *sim);
bool func_02005654(Unk02005a74 *o, Unk020680d4Cell cell, int kind, int v);
void *func_02007340(void *p, int kind);
void *func_02007c98(void *pool, int a, int b);
void func_02007e48(void *list, void *o);
int func_0205465c(void *p, Unk0205cf00 *def, bool a);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
Unk02098ff0 func_02057b5c(Unk02058788 *lot, const Unk020680d4Cell *c);
Unk020680d4Cell func_02057bb8(Unk02058788 *lot, const Unk020680d4Cell *from, const Unk020680d4Cell *to);
Unk02058788 *func_02058788(void *world, int map);
bool func_02059418(const Unk020593e4 *cell);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
bool func_0205d340(Unk0205cf00 *def, u32 key);
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
Unk02061d08Item *func_0205fb4c(void *list, int key, Unk0205f098 *out, int a);
void func_0205fea0(void *list, u32 key);
bool func_0206757c(void *p, int mask);
int func_020676b4(Unk02005ad4Actor *p);
int func_02067708(Unk02005ad4Actor *p, int a, int b);
void func_02067778(Unk02005ad4Actor *p, Unk020680d4Cell cell);
void func_02066748(Unk02005ad4Actor *p, int key, int a, int b, int c, int d);
void func_020667f8(Unk02005ad4Actor *p, int a);
Unk0206bcf0 *func_0206bce0();
void func_020897b4(const char *fmt, ...);
int func_02097a58(int a, int b);
void func_020a1eb4(Unk02098ff0 *pos, Unk02098ff0 *out, s16 angle, int speed);
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020be184[];
extern u8 data_020bfc68[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020c43a8[];
extern u8 data_020c4770[];
}

static inline bool func_valid(const Unk020680d4Cell &c) {
    return func_02059418(&c.pos) && c.xy.x >= 0 && c.xy.y >= 0;
}

static inline Unk020680d4Cell func_path(Unk02058788 *lot, const Unk020680d4Cell &from, const Unk020680d4Cell &to) {
    return func_02057bb8(lot, &from, &to);
}

bool Unk02005ad4::func_08() {
    return cell1.pos.unk3 == data_020c3ba4.map;
}

int Unk02005ad4::func_10() {
    if (started) {
        if (cell1.pos.unk3 != data_020c3ba4.map) {
            return 1;
        }
        done = true;
        func_0200264c(this);
        flags &= ~2;
        return 0;
    }
    return 1;
}

int Unk02005ad4::func_14() {
    Unk02005ad4Actor *actor = func_02002414(this);
    Unk02005ad4Sim *sim = actor->sim;
    if (sim == 0) {
        return 2;
    }
    started = true;
    cell0 = Unk020680d4Cell();
    actor->target = cell1;
    int r = func_0200527c(this, actor, sim);
    if (r == 0) {
        r = 1;
    }
    return r;
}

int Unk02005ad4::func_18() {
    Unk02005ad4Actor *actor = func_02002414(this);
    int speed;
    Unk02005ad4Sim *sim = actor->sim;
    if (sim == 0) {
        return 2;
    }
    if (func_valid(cell0)) {
        speed = func_020676b4(actor);
        int scale = 0x1000;
        if (diagonal) {
            scale = 0x16a1;
            speed = ((s64)speed * (u32)scale) >> 12;
        }
        if (speed >= scale - 0x32) {
            if (!func_0206757c(data_020c43a8, 1)) {
                func_0205fea0(data_020c3fd4, 0x9af6210a);
            }
            actor->func_10(cell0);
            int r = func_0200527c(this, actor, sim);
            if (r != 0) {
                return r;
            }
        } else {
            int a = func_02067708(actor, angle, 0x1f4);
            Unk02098ff0 out;
            func_020a1eb4(&pos.v, &out, a, speed);
            actor->func_00(out);
        }
        if (sim->unk160 == 0) {
            func_02066748(actor, 0, 0, 0xa, 0, 0);
        }
        return 0;
    }
    return 1;
}

/*
 * 99.93 %: the two `add` that prepare func_0209911c are swapped (the original sets r1, the
 * receiver, before r0, the result); registers, stack and all other instructions match.
 */
int func_0200527c(Unk02005ad4 *o, Unk02005ad4Actor *actor, Unk02005ad4Sim *sim) {
    if (o->done) {
        return 1;
    }
    if (func_valid(o->cell0) && func_valid(o->cell1) && o->cell0 == o->cell1) {
        return 1;
    }
    Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    o->cell0 = func_path(map, actor->func_14(), o->cell1);
    if (func_valid(o->cell0) && func_valid(o->cell1)) {
        func_02067778(actor, o->cell0);
        Unk02098ff0 target = func_02057b5c(func_02058788(&data_020c3ba4, data_020c3ba4.map), &o->cell0)
                                 .func_0209911c(Unk02098ff0(0x800, 0, 0x800));
        o->pos = (const Unk02005ad4Pos &)actor->func_04();
        o->angle = func_02097a58(target.x - o->pos.v.x, target.z - o->pos.v.z);
        if (o->cell0.xy.x == actor->func_14().xy.x || o->cell0.xy.y == actor->func_14().xy.y) {
            o->diagonal = false;
        } else {
            o->diagonal = true;
        }
    } else {
        return 1;
    }
    return 0;
}

const Unk02005ad4Desc *Unk02005aa4::func_20() {
    static Unk02005ad4Desc desc(0, 0, 0, "Move");
    return &desc;
}

void Unk02005aa4::func_1c() {
    func_020897b4("Action Move Completed");
    Unk02005ad4Actor *actor = func_02002414(this);
    if (stop) {
        func_020667f8(actor, 0xa);
    }
    actor->target = Unk020680d4Cell();
}

const Unk02005ad4Desc *Unk02005a74::func_20() {
    static Unk02005ad4Desc desc(6, 0, 1, "Action Exit");
    return &desc;
}

bool func_02005654(Unk02005a74 *o, Unk020680d4Cell cell, int kind, int v) {
    func_02002414(o);
    Unk02056ed0 *layer;
    Unk02061d08Item *item;
    const Unk020680d4Cell *c;
    Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    layer = func_02056ed0(map, &cell);
    Unk0205f098 list;
    for (item = func_0205fb4c(data_020c3fd4, 0x12d2c5be, &list, map->lot); item != 0;
         item = item->next) {
        c = &(const Unk020680d4Cell &)item->func_14();
        if (func_valid(*c)) {
            const Unk020680d4Xy &xy = item->func_14().xy;
            u32 *tile = layer->func_tile(xy.x, xy.y);
            if (tile != 0 && kind == (int)(((*tile & 0x3000) >> 12) - 1)) {
                int value;
                Unk0205cf00 *def = item->def;
                if (def != 0) {
                    value = item->func_0c().y;
                    o->func_target(item->func_14());
                    if (func_0205d340(def, 0x1b24f464)) {
                        Unk0205cf00 *bulb = func_0205f6f8(data_020c3fc4, 0xc447032e);
                        if (func_0205465c(data_020bfc68, bulb, false)) {
                            Unk0205cf00 *d = func_0205f6f8(data_020c3fc4, func_0205d1b4(bulb, 0x798b86ac));
                            func_0206bce0()->func_0206f3e8(d, 1, 1, 1);
                            return false;
                        }
                    }
                    if (func_0205d340(def, 0x4c4f47d9)) {
                        u8 *next = (u8 *)func_02007c98(data_020be184, 0x1b, 2);
                        if (next != 0) {
                            func_02001318(next, item, v, map->lot, 0, value, 1, 0);
                            func_02007e48(item->list, next);
                            func_02007e48(data_020c4770, *(void **)(next + 0x18));
                            return true;
                        }
                    } else {
                        void *next = func_02007340(data_020be184, 0x19);
                        if (next != 0) {
                            int key = func_0205d1b4(def, 0xeaa383d2);
                            func_02001318(next, item, v, map->lot, key, value, 1,
                                          def != 0 && func_0205d340(def, 0x21c9d38d));
                            func_02007e48(data_020c4770, next);
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    o->failed = true;
    return false;
}

void Unk02005a74::func_1c() {
    func_020897b4("Action Move Exit Completed");
    if (done || failed) {
        Unk02005ad4Actor *actor = func_02002414(this);
        func_020667f8(actor, 0xa);
        actor->target = Unk020680d4Cell();
    }
}
