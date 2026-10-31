/*
 * Unit 0x0205D8D8-0x0205F16C: the scene object Unk02061d08Item (0x4C bytes,
 * allocated from the pool of unit_0205F80C.cpp) and the search list of scene
 * objects Unk0205f098. A scene object has a definition (unit_0205F16C.cpp),
 * a cell and a direction on a map, script variables, an action queue and,
 * while it is on the current map, a visible object (unit_02060ADC.cpp). It
 * implements the interface of the sim (vtable slots 0x00-0x2C).
 *
 * Bounds: hypothesis. The functions before 0x0205D8D8 are called from the
 * code before 0x0205D6E0; the class operators open this range and the search
 * list ends it, before unit_0205F16C.cpp. `.data`: the vtable with its header
 * (0x020BC2B8) and an all-zero copy of the interface vtable (0x020BC2F0);
 * the strings before it are used by the code before 0x0205D6E0. Real file
 * name unknown.
 *
 * Not complete: func_0205e87c and func_0205eed4 are not at 100 % (comments
 * above them). The compiler also emits a deleting destructor that the
 * original does not have.
 *
 * Functions other than the constructors, destructor, operators and virtual
 * functions keep C linkage: other files call them by their addresses.
 */

#include "game/unk_script.h"
#include "game/unk_objscript.h"
#include "game/unk_queue.h"
#include "game/unk_anim.h"

typedef signed char s8;

struct Unk020a4c4c;
struct Unk02058788;
struct Unk02063d84;
class Unk02060d78;
class Unk020c40cc;
class Unk020c3cc8;

/* A vector. */
struct Unk0205d8d8Vec {
    Unk0205d8d8Vec() {}
    Unk0205d8d8Vec(int x, int y, int z) : x(x), y(y), z(z) {}

    int x;
    int y;
    int z;
};

/* A box: corner and size. */
struct Unk0205d8d8Box {
    Unk0205d8d8Box(const Unk0205d8d8Vec &a, const Unk0205d8d8Vec &b) : a(a), b(b) {}

    Unk0205d8d8Vec a;
    Unk0205d8d8Vec b;
};

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

struct Unk020680d4Xy {
    Unk020680d4Xy() {}
    Unk020680d4Xy(s16 x, s16 y) {
        this->x = x;
        this->y = y;
    }

    s16 x;
    s16 y;
};

/* A map cell: its tile coordinates are -1 when it is not set. */
struct Unk020680d4Cell {
    Unk020680d4Cell() {
        xy.x = -1;
        xy.y = -1;
    }
    Unk020680d4Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    Unk020680d4Cell func_add(Unk020680d4Xy d) const {
        return Unk020680d4Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }
    Unk020680d4Cell func_sub(Unk020680d4Xy d) const {
        return Unk020680d4Cell(pos.unk3, pos.unk2, pos.unk0, xy.x - d.x, xy.y - d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

struct Unk020680d4Dir {
    Unk020680d4Dir() {}
    Unk020680d4Dir(int v) : v(v) {}

    int v;
};

/* A rectangle of a definition: position and size. */
struct Unk0205eed4Rect {
    Unk020680d4Xy pos;
    Unk020680d4Xy size;
};

/* The definition of a scene object (unit_0205F16C.cpp). */
struct Unk0205cf00 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    int unk8;
    int key;
    Unk020956f8 *script;
    u32 flags;
    int group;
};

/* The definition given to func_020615f0. */
struct Unk020615f0Def {
    int model;
    u32 xform;
    u32 anim;
    u32 unkc;
    u8 unk10[0x10];
    u32 texanim;
    int unk24;
    int unk28;
    int unk2c;
    u32 flags;
};

/* The object attached to a visible object. */
class Unk0201c460 {
public:
    Unk0201c460(u32 key);
    virtual ~Unk0201c460();

    u8 unk4[0x84];
};

/* A script variable record (12 bytes). */
struct Unk0209585c {
    u8 unk0[6];
    s16 value;
    int unk8;
};

/* The player: only its sim. */
struct Unk020c43a8 {
    u8 unk0[0xc];
    void *sim;
};

/* The action queue of an object (functions 0x02007D30-0x02007E48). */
struct Unk0205da00Queue {
    Unk0205da00Queue(void *owner) : owner(owner), flags(0), unk8(0), head(0) {
        flags |= 1;
    }

    void *owner;
    u32 flags;
    int unk8;
    struct Unk02007340 *head;

    bool func_busy() const {
        return head != 0;
    }
};

struct Unk02007340 {
    u8 unk0[4];
    u32 flags;
    u8 unk8[0x10];
    void *unk18;
};

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

/* The main game state: only its timed queue. */
class Unk0206bcf0 {
public:
    u8 unk0[0xc];
    Unk0206b8cc *queue;
};

/* The world (data_020c3ba4). */
struct Unk020c3ba4 {
    int unk0;
    u8 unk4[0x54];
    Unk02058788 *maps[41];
    s8 map;
};

/* The interface shared with the sim: its vtable copies are all zero. */
class Unk020680d4Base {
public:
    virtual void func_00(Unk0205d8d8Vec pos) = 0;
    virtual Unk0205d8d8Vec func_04() = 0;
    virtual void func_08(Unk0205d8d8Vec rot) = 0;
    virtual Unk0205d8d8Vec func_0c() = 0;
    virtual void func_10(Unk020680d4Cell cell) = 0;
    virtual Unk020680d4Cell func_14() = 0;
    virtual void func_18(Unk020680d4Dir dir) = 0;
    virtual Unk020680d4Dir func_1c() = 0;
    virtual Unk020680d4Xy func_20() = 0;
    virtual int func_24() = 0;
    virtual int func_28() = 0;
    virtual bool func_2c(const Unk020680d4Cell &cell) = 0;
};

/* A scene object (0x4C bytes). */
class Unk02061d08Item : public Unk020680d4Base {
public:
    static void *operator new[](unsigned long size);
    static void operator delete[](void *p);
    static void *operator new(unsigned long size);
    static void operator delete(void *p);

    Unk02061d08Item();
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    Unk02061d08Item(Unk020a4c4c *save);
    ~Unk02061d08Item();

    virtual void func_00(Unk0205d8d8Vec pos);
    virtual Unk0205d8d8Vec func_04();
    virtual void func_08(Unk0205d8d8Vec rot);
    virtual Unk0205d8d8Vec func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual int func_24();
    virtual int func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);

    Unk0205da00Queue queue;
    u32 flags;
    Unk020680d4Cell cell;
    Unk020680d4Dir dir;
    int unk24;
    Unk0205cf00 *def;
    u32 id;
    s16 vars[4];
    u32 key;
    Unk02061d08Item *prev;
    Unk02061d08Item *next;
    Unk02060d78 *visible;
    Unk02061d08Item *found;

    bool func_flag(u32 mask) const {
        return (flags & mask) != 0;
    }
};

/* The objects found by a search, chained through Unk02061d08Item::found. */
struct Unk0205f098 {
    Unk02061d08Item *head;
    int count;
};

/* The scene object manager (unit_0205F80C.cpp): only its pool counters. */
class Unk020c3fd4 {
public:
    Unk02061d08Item *pool;
    Unk02061d08Item *removed;
    Unk02061d08Item *free;
    Unk02061d08Item *lists[41];
    int unkb0;
    int unkb4;
    u32 unkb8;
};

/* The saved state of a scene object (0x24 bytes). */
struct Unk0205ed90Save {
    u32 id;
    int defKey;
    int unk8;
    u32 key;
    Unk020680d4Cell cell;
    int dir;
    s16 vars[4];
};

extern "C" {

extern Unk020c3fd4 data_020c3fd4;
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020c3fc4[];
extern Unk020c40cc data_020c40cc;
extern Unk020c3cc8 data_020c3cc8;

void *func_0205f6f8(void *db, int key);
void func_0205fcac(Unk020c3fd4 *m, Unk02061d08Item *item);
void func_0205fcf0(Unk020c3fd4 *m, Unk02061d08Item *item);
int func_0205f990(Unk020c3fd4 *m);
void func_02007e38(Unk0205da00Queue *q);
bool func_02059418(const Unk020680d4Cell *cell);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk0205d8d8Vec func_02057b5c(Unk02058788 *map, const Unk020680d4Cell *cell);
void func_02057cec(Unk02058788 *map, const Unk020680d4Cell *cell, const Unk020680d4Xy *size, u32 mask);
void func_02057d14(Unk02058788 *map, const Unk020680d4Cell *cell, const Unk020680d4Xy *size);
bool func_02057d54(Unk02058788 *map, const Unk020680d4Cell *cell, const Unk020680d4Xy *size, int kind, int a);
void func_02057dd0(Unk02058788 *map, const Unk020680d4Cell *cell, const Unk020680d4Xy *size, int kind);
u32 func_0205c758(Unk0205cf00 *def, Unk020680d4Dir dir);
Unk020615f0Def func_0205c8b4(Unk0205cf00 *def, Unk02099c78Block *block);
Unk02099c78Block *func_0205cee4(Unk0205cf00 *def, int key);
bool func_0205cf28(Unk0205cf00 *def, int index, Unk02061d08Item *item, Unk020c43a8 *p);
bool func_0205d234(Unk0205cf00 *def, u32 a, u32 b);
int func_0205d340(Unk0205cf00 *def, u32 key);
void func_0205d35c(Unk0205cf00 *def);
void func_0205d37c(Unk0205cf00 *def);
void func_0205aff0(Unk020c3cc8 *c, int a, int b);
bool func_0205b00c(Unk020c3cc8 *c, int a);
void func_0205b030(Unk020c3cc8 *c);
bool func_0200292c(void *p);
Unk02063d84 *func_02063e2c(u32 key, int mode);
Unk020897c0 *func_02063d84(Unk02063d84 *a);
void func_02063db8(Unk02063d84 *a, int loop);
void func_02069124(void *sim, Unk02063d84 *a, int frames, int b);
void func_02069d4c(void *sim, int a, int b);
void func_020667f8(Unk020c43a8 *p, int a);
Unk02060d78 *func_02060c48(Unk020c40cc *s, bool force);
Unk02060d78 *func_02060c90(Unk020c40cc *s);
void func_02060fc8(Unk02060d78 *e);
void func_020610d8(Unk02060d78 *e, Unk0205d8d8Vec pos);
void func_0206110c(Unk02060d78 *e, Unk0205d8d8Vec rot);
void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames);
Unk0205d8d8Vec func_020613a4(Unk02060d78 *e);
Unk0205d8d8Vec func_020613c8(Unk02060d78 *e);
void func_020615f0(Unk02060d78 *e, Unk020615f0Def *def);
bool func_020618f4(Unk02060d78 *e, Unk0201c460 *o);
void func_02061930(Unk02060d78 *e);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
bool func_02061ab4(Unk02061d08Item *item, const Unk020680d4Cell *cell);
Unk0206bcf0 *func_0206bce0();
void func_020a20f0(Unk020a20f0 *random);
u32 func_020a1f84(Unk020a20f0 *random);
bool func_020a2118(void *hit, void *ray, Unk0205d8d8Box *box);
void func_020a4d78(Unk020a4c4c *save, int a);
Unk0205ed90Save *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4d2c(Unk020a4c4c *save, int a);
Unk0205ed90Save *func_020a4ce0(Unk020a4c4c *save, int size);

void func_0205dbc4(Unk02061d08Item *item, const Unk020680d4Cell *cell, Unk020680d4Dir dir);
void func_0205dd44(Unk02061d08Item *item);
void func_0205dd48(Unk02061d08Item *item);
void func_0205dd4c(Unk02061d08Item *item);
void func_0205ddf0(Unk02061d08Item *item);
void func_0205def0(Unk02061d08Item *item);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, Unk020c43a8 *p);
void func_0205e1b8(Unk02061d08Item *item, Unk020c43a8 *p);
void func_0205e4d0(Unk02061d08Item *item);
Unk0205d8d8Box func_0205e87c(Unk02061d08Item *item);
void func_0205ec7c(Unk02061d08Item *item);
void func_0205ece8(Unk02061d08Item *item, int key);
void func_0205ee30(Unk02061d08Item *item, Unk020a4c4c *save);
void func_0205f0bc(Unk0205f098 *list);

}

void *Unk02061d08Item::operator new[](unsigned long size) {
    return ::operator new[](size);
}

void Unk02061d08Item::operator delete[](void *p) {
    ::operator delete(p);
}

void *Unk02061d08Item::operator new(unsigned long size) {
    Unk020c3fd4 *m = &data_020c3fd4;
    if (m->free == 0) {
        return 0;
    }
    Unk02061d08Item *item = m->free;
    m->free = item->next;
    if (m->free != 0) {
        m->free->prev = 0;
    }
    item->next = 0;
    item->prev = 0;
    m->unkb0++;
    item->id = m->unkb8 | ((item - m->pool) << 24);
    m->unkb8++;
    return item;
}

void Unk02061d08Item::operator delete(void *p) {
    Unk020c3fd4 *m = &data_020c3fd4;
    Unk02061d08Item *item = (Unk02061d08Item *)p;
    func_0205fcf0(m, item);
    item->next = m->free;
    m->free = item;
    if (item->next != 0) {
        item->next->prev = item;
    }
    m->unkb0--;
    item->cell = Unk020680d4Cell();
    func_0205f990(m);
}

Unk02061d08Item::Unk02061d08Item()
    : queue(this), flags(0), dir(4), unk24(0), def(0), id(0), key(0x7a90e673), prev(0), next(0), visible(0),
      found(0) {
    id = 0;
}

Unk02061d08Item::Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir)
    : queue(this), flags(0), dir(4), unk24(0), def(def), key(0x7a90e673), visible(0), found(0) {
    func_0205dbc4(this, &cell, dir);
}

Unk02061d08Item::Unk02061d08Item(Unk020a4c4c *save)
    : queue(this), flags(0), dir(4), unk24(0), def(0), id(0), key(0x7a90e673), visible(0), found(0) {
    func_0205ee30(this, save);
    func_0205fcac(&data_020c3fd4, this);
}

extern "C" {

void func_0205dbc4(Unk02061d08Item *item, const Unk020680d4Cell *cell, Unk020680d4Dir dir) {
    func_0205ec7c(item);
    item->func_10(*cell);
    item->func_18(dir);
    item->key = 0x7a90e673;
    int n;
    Unk020956f8 *script = item->def->script;
    if (script != 0) {
        n = script->func_0209576c()->varCount;
        if (n > 4) {
            n = 4;
        }
        if (n > 0) {
            Unk0209585c *vars = (Unk0209585c *)script->func_0209585c();
            if (vars != 0) {
                for (int i = 0; i < n; i++) {
                    item->vars[i] = vars->value;
                    vars++;
                }
            }
        }
        for (; n < 4; n++) {
            item->vars[n] = 0;
        }
    }
    func_0205fcac(&data_020c3fd4, item);
    func_0205f990(&data_020c3fd4);
    func_0205dd44(item);
}

}

Unk02061d08Item::~Unk02061d08Item() {
    if (id != 0) {
        func_0205dd48(this);
        id = 0;
        func_02007e38(&queue);
        if (visible != 0) {
            func_0205e4d0(this);
        }
        func_0205dd4c(this);
        func_0205ec7c(this);
    }
}

extern "C" {

void func_0205dd44(Unk02061d08Item *item) {}

void func_0205dd48(Unk02061d08Item *item) {}

void func_0205dd4c(Unk02061d08Item *item) {
    int map;
    Unk020c3ba4 *world = &data_020c3ba4;
    map = item->cell.pos.unk3;
    if (map == world->map && func_02059418(&item->cell) && item->cell.xy.x >= 0 && item->cell.xy.y >= 0 &&
        (item->flags & 4)) {
        Unk02058788 *m = func_02058788(world, map);
        Unk020680d4Xy size = item->func_20();
        func_02057dd0(m, &item->cell, &size, 6);
    }
    item->flags &= ~4;
    item->flags &= ~8;
}

void func_0205ddf0(Unk02061d08Item *item) {
    int map = item->cell.pos.unk3;
    Unk02058788 *m = func_02058788(&data_020c3ba4, map);
    Unk020680d4Xy size = item->func_20();
    if (!func_02057d54(m, &item->cell, &size, 2, -1)) {
        return;
    }
    if (!func_02059418(&item->cell)) {
        return;
    }
    if (item->cell.xy.x < 0 || item->cell.xy.y < 0) {
        return;
    }
    Unk0205cf00 *def = item->def;
    m = func_02058788(&data_020c3ba4, map);
    Unk020680d4Xy size2 = item->func_20();
    Unk020680d4Dir dir = item->func_1c();
    func_02057cec(m, &item->cell, &size2, func_0205c758(def, dir));
    item->flags |= 8;
}

void func_0205def0(Unk02061d08Item *item) {
    int map = item->cell.pos.unk3;
    Unk02058788 *m = func_02058788(&data_020c3ba4, map);
    if (m == 0) {
        return;
    }
    Unk020680d4Xy size = item->func_20();
    if (!func_02057d54(m, &item->cell, &size, 4, -1)) {
        return;
    }
    if (!func_02059418(&item->cell)) {
        return;
    }
    if (item->cell.xy.x < 0 || item->cell.xy.y < 0) {
        return;
    }
    m = func_02058788(&data_020c3ba4, map);
    Unk020680d4Xy size2 = item->func_20();
    func_02057d14(m, &item->cell, &size2);
    item->flags |= 4;
}

void func_0205dfcc(Unk02061d08Item *item) {
    if (item->def->flags & 1) {
        return;
    }
    if (data_020c3ba4.maps[item->cell.pos.unk3] == 0) {
        return;
    }
    func_0205def0(item);
    func_0205ddf0(item);
}

bool func_0205e00c(Unk02061d08Item *item, int index, Unk020c43a8 *p) {
    if (item->flags & 0x200) {
        return false;
    }
    return func_0205cf28(item->def, index, item, p);
}

void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, Unk020c43a8 *p) {
    const Unk020615f0Def &d = func_0205c8b4(item->def, block);
    if (p != 0) {
        if (d.flags & 2) {
            Unk02063d84 *a = func_02063e2c(d.unkc, 0);
            if (a != 0) {
                int frames = (d.flags & 0x400) ? 10 : 0;
                func_02063db8(a, (d.flags & 8) ? 1 : 0);
                func_02069124(p->sim, a, frames, (d.flags & 0x80) ? 1 : 0);
                if (d.flags & 0x100) {
                    func_02069d4c(p->sim, d.unk2c, 1);
                }
            }
        } else if (d.flags & 1) {
            func_020667f8(p, 10);
        }
    }
    func_02061930(item->visible);
    func_020615f0(item->visible, (Unk020615f0Def *)&d);
    Unk02099c78Value *values = item->def->script->func_02095ab0();
    for (int i = block->func_start(); i < block->func_end(); i++) {
        if (values[i].unk0 == 0x56b7749d) {
            item->key = values[i].unk4;
            break;
        }
    }
    item->flags &= ~0x2000;
}

void func_0205e184(Unk02061d08Item *item, int key, Unk020c43a8 *p) {
    if (item->visible == 0) {
        return;
    }
    func_0205e038(item, func_0205cee4(item->def, key), p);
}

void func_0205e1b8(Unk02061d08Item *item, Unk020c43a8 *p) {
    Unk02060d78 *visible = item->visible;
    if (visible == 0) {
        return;
    }
    Unk02099c78Block *block = func_0205cee4(item->def, item->key);
    func_0205e038(item, block, p);
    item->flags |= 0x2000;
    const Unk020615f0Def &d = func_0205c8b4(item->def, block);
    if (d.flags & 0x40) {
        Unk0201c460 *o = new Unk0201c460(d.unk24);
        if (!func_020618f4(visible, o) && o != 0) {
            delete o;
        }
    }
    if (!(item->flags & 0x1000)) {
        return;
    }
    u32 keys[3] = {0, 0, 0};
    int n = 0;
    Unk02099c78Value *values = item->def->script->func_02095ab0();
    for (int i = block->start; i < block->start + block->count; i++) {
        switch (values[i].unk0) {
        case 0xfd7539de:
            keys[n++] = values[i].unk4;
            break;
        case 0xfd7539df:
            keys[n++] = values[i].unk4;
            break;
        case 0xfd7539e0:
            keys[n++] = values[i].unk4;
            break;
        }
    }
    if (n == 0) {
        return;
    }
    Unk020a20f0 random;
    func_020a20f0(&random);
    Unk02063d84 *a = func_02063e2c(keys[func_020a1f84(&random) % n], 2);
    if (a == 0) {
        return;
    }
    Unk0206b998Req req;
    req.delay = func_02063d84(a)->func_01ff8a68() * 2;
    req.key = 0x904eb81f;
    req.item = (Unk0206bcf0Item *)item;
    func_0206bce0()->queue->func_0206b998(&req);
    func_02061298(visible, a, false, 16);
    item->flags &= ~0x1000;
}

void func_0205e3f0(Unk02061d08Item *item) {
    if (item->visible != 0) {
        return;
    }
    if (item->flags & 0x80) {
        item->visible = func_02060c90(&data_020c40cc);
    } else {
        item->visible = func_02060c48(&data_020c40cc, (item->flags & 0x100) ? true : false);
    }
    if (item->visible == 0) {
        return;
    }
    if (func_0205d340(item->def, 0xd47616b6)) {
        *(Unk02061d08Item **)((u8 *)item->visible + 0x34) = item;
    }
    func_0205d35c(item->def);
    item->flags |= 0x40;
    func_0205e1b8(item, 0);
    item->func_10(item->cell);
    item->func_18(item->dir);
}

void func_0205e4d0(Unk02061d08Item *item) {
    if (item->visible == 0) {
        return;
    }
    item->flags &= ~0x40;
    func_02060fc8(item->visible);
    item->visible = 0;
    func_0205d37c(item->def);
}

}

void Unk02061d08Item::func_00(Unk0205d8d8Vec pos) {
    if (visible != 0) {
        func_020610d8(visible, pos);
    }
}

void Unk02061d08Item::func_08(Unk0205d8d8Vec rot) {
    if (visible != 0) {
        func_0206110c(visible, rot);
    }
}

void Unk02061d08Item::func_10(Unk020680d4Cell c) {
    cell = c;
    if (!func_02059418(&c)) {
        return;
    }
    if (c.xy.x < 0 || c.xy.y < 0) {
        return;
    }
    if (visible == 0) {
        return;
    }
    Unk0205d8d8Vec pos = func_02057b5c(func_02058788(&data_020c3ba4, c.pos.unk3), &c);
    bool straight = dir.v == 0 || dir.v == 2;
    if (straight) {
        pos.x += func_24() << 11;
        pos.z += func_28() << 11;
    } else {
        pos.z += func_24() << 11;
        pos.x += func_28() << 11;
    }
    func_020610d8(visible, pos);
}

void Unk02061d08Item::func_18(Unk020680d4Dir d) {
    dir.v = d.v;
    Unk0205d8d8Vec rot(0, d.v << 14, 0);
    if (visible != 0) {
        func_0206110c(visible, rot);
    }
    func_10(cell);
}

Unk0205d8d8Vec Unk02061d08Item::func_04() {
    if (visible != 0) {
        return func_020613a4(visible);
    }
    return Unk0205d8d8Vec(0, 0, 0);
}

Unk0205d8d8Vec Unk02061d08Item::func_0c() {
    if (visible != 0) {
        return func_020613c8(visible);
    }
    return Unk0205d8d8Vec(0, 0, 0);
}

Unk020680d4Cell Unk02061d08Item::func_14() {
    return cell;
}

Unk020680d4Dir Unk02061d08Item::func_1c() {
    return dir;
}

Unk020680d4Xy Unk02061d08Item::func_20() {
    bool straight = dir.v == 0 || dir.v == 2;
    if (straight) {
        return Unk020680d4Xy(func_24(), func_28());
    }
    return Unk020680d4Xy(func_28(), func_24());
}

int Unk02061d08Item::func_24() {
    return def->width;
}

int Unk02061d08Item::func_28() {
    return def->height;
}

extern "C" {

/*
 * 74.46 %: the original keeps two vectors on the stack (corner at sp+0x1C,
 * size at sp+0x10) and copies them into the result with ldmia/stmia; here
 * the result is built in place. Separate locals (kept in registers),
 * pointers, references, by-value constructor and helpers tried.
 */
Unk0205d8d8Box func_0205e87c(Unk02061d08Item *item) {
    Unk020956f8 *script = item->def->script;
    Unk0205d8d8Box box(Unk0205d8d8Vec(0, 0, 0), Unk0205d8d8Vec(0, 0, 0));
    Unk02099c78Block *block = (Unk02099c78Block *)script->func_02095a3c(0x75d11eb1);
    if (block == 0) {
        return box;
    }
    Unk02099c78Value *values = script->func_02095ab0();
    for (int i = block->start; i < block->start + block->count; i++) {
        switch (values[i].unk0) {
        case 0x4cd76e93:
            box.a.x = values[i].unk4;
            break;
        case 0x8706ee93:
            box.a.y = values[i].unk4;
            break;
        case 0xc1366e93:
            box.a.z = values[i].unk4;
            break;
        case 0x4c23274d:
            box.b.x = values[i].unk4;
            break;
        case 0x8652a74d:
            box.b.y = values[i].unk4;
            break;
        case 0xc082274d:
            box.b.z = values[i].unk4;
            break;
        }
    }
    Unk020680d4Dir dir = item->func_1c();
    switch (dir.v) {
    case 0:
        break;
    case 3: {
        int x = box.a.x;
        int bz = box.b.z;
        box.a.x = -box.a.z - box.b.z;
        box.a.z = x;
        box.b.z = box.b.x;
        box.b.x = bz;
        break;
    }
    case 1: {
        int z = box.a.z;
        int bz = box.b.z;
        box.a.z = -box.a.x - box.b.x;
        box.a.x = z;
        box.b.z = box.b.x;
        box.b.x = bz;
        break;
    }
    case 2:
        box.a.x = -box.a.x - box.b.x;
        box.a.z = -box.a.z - box.b.z;
        break;
    }
    Unk0205d8d8Vec pos = item->func_04();
    box.a.x += pos.x;
    box.a.y += pos.y;
    box.a.z += pos.z;
    return box;
}

}

bool Unk02061d08Item::func_2c(const Unk020680d4Cell &c) {
    if (!func_02061ab4(this, &c)) {
        return false;
    }
    s16 dx = c.xy.x - func_14().xy.x;
    s16 dy = c.xy.y - func_14().xy.y;
    u32 mask = func_0205c758(def, dir);
    if (mask == 0 || (mask & (1 << (dy * func_24() + dx)))) {
        return true;
    }
    return false;
}

extern "C" {

bool func_0205ebd4(Unk02061d08Item *item, void *ray, void *hit) {
    Unk0205d8d8Box box = func_0205e87c(item);
    return func_020a2118(hit, ray, &box);
}

bool func_0205ec0c(Unk02061d08Item *item) {
    if (!item->def->script->func_020957ec(0xde4df67)) {
        return func_0205d234(item->def, 0x71ca2e4d, 0x6a4a2934);
    }
    func_0205aff0(&data_020c3cc8, 0, 0);
    func_0205ece8(item, 0xde4df67);
    return func_0205b00c(&data_020c3cc8, 0);
}

void func_0205ec7c(Unk02061d08Item *item) {
    func_02007e38(&item->queue);
    item->visible = 0;
    item->found = 0;
}

bool func_0205ec9c(Unk02061d08Item *item) {
    if (item->func_flag(0x200)) {
        return false;
    }
    item->flags |= 0x200;
    return true;
}

int func_0205ecc0(Unk02061d08Item *item, int key) {
    int i = item->def->script->func_020958bc(key);
    if (i < 0) {
        return 0;
    }
    return item->vars[i];
}

void func_0205ece8(Unk02061d08Item *item, int key) {
    Unk02061c04 runner(item);
    runner.func_02099ce0(key);
}

void func_0205ed20(Unk02061d08Item *item) {
    if (item->visible == 0) {
        return;
    }
    if (item->queue.func_busy()) {
        Unk02007340 *head = item->queue.head;
        if (!(head->flags & 0x400) || head->unk18 == 0) {
            return;
        }
        if (func_0200292c(head->unk18)) {
            return;
        }
    }
    if (item->flags & 0x4000) {
        return;
    }
    func_0205b030(&data_020c3cc8);
    func_0205ece8(item, 0xdff0aab5);
}

void func_0205ed90(Unk02061d08Item *item, Unk020a4c4c *save) {
    func_020a4d78(save, 2);
    Unk0205ed90Save *s = func_020a4c60(save, 0x24, 1);
    if (s == 0) {
        return;
    }
    s->id = item->id;
    s->defKey = item->def->key;
    s->unk8 = item->unk24;
    s->key = item->key;
    s->cell = item->cell;
    s->dir = item->dir.v;
    for (int i = 0; i < 4; i++) {
        s->vars[i] = item->vars[i];
    }
}

void func_0205ee30(Unk02061d08Item *item, Unk020a4c4c *save) {
    func_020a4d2c(save, 2);
    Unk0205ed90Save *s = func_020a4ce0(save, 0x24);
    if (s == 0) {
        return;
    }
    item->id = s->id;
    item->def = (Unk0205cf00 *)func_0205f6f8(data_020c3fc4, s->defKey);
    item->unk24 = s->unk8;
    item->key = s->key;
    item->cell = s->cell;
    item->dir.v = s->dir;
    for (int i = 0; i < 4; i++) {
        item->vars[i] = s->vars[i];
    }
}

/*
 * 99.79 %: stack layout only; the original puts the temporary of the second
 * offset just below p. Declaration orders tried.
 */
Unk020680d4Cell func_0205eed4(Unk02061d08Item *item, const Unk0205eed4Rect *rect) {
    Unk020680d4Xy p;
    Unk0205cf00 *def = item->def;
    Unk020680d4Xy origin(def->x, def->y);
    Unk020680d4Xy rel = func_020619a8(item, origin, item->func_1c());
    Unk020680d4Cell r = item->func_14().func_add(rel);
    p.x = rect->pos.x;
    p.y = rect->pos.y;
    switch (item->dir.v) {
    case 0:
        break;
    case 1:
        p = Unk020680d4Xy(p.y, rect->size.x - 1 - p.x);
        break;
    case 2:
        p = Unk020680d4Xy(rect->size.x - 1 - p.x, rect->size.y - 1 - p.y);
        break;
    case 3:
        p = Unk020680d4Xy(rect->size.y - 1 - p.y, p.x);
        break;
    }
    r = r.func_sub(p);
    return r;
}

void func_0205f098(Unk0205f098 *list) {
    list->head = 0;
    list->count = 0;
}

Unk0205f098 *func_0205f0a8(Unk0205f098 *list) {
    func_0205f0bc(list);
    return list;
}

void func_0205f0bc(Unk0205f098 *list) {
    for (Unk02061d08Item *item = list->head; item != 0;) {
        Unk02061d08Item *next = item->found;
        item->found = 0;
        item = next;
    }
    list->head = 0;
    list->count = 0;
}

void func_0205f0f0(Unk0205f098 *list, Unk02061d08Item *item) {
    item->found = list->head;
    list->head = item;
    list->count++;
}

Unk02061d08Item **func_0205f10c(Unk0205f098 *list, Unk02061d08Item **out, int max) {
    if (list->count <= 0 || out == 0 || max <= 0) {
        return 0;
    }
    Unk02061d08Item *item = list->head;
    for (int i = 0; i < list->count; i++) {
        if (i >= max) {
            break;
        }
        out[i] = item;
        item = item->found;
    }
    return out;
}

}
