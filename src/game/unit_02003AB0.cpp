/*
 * Unit 0x02003AB0-0x02004250: the action "Dig or Dive": the sim walks to a tile, digs or
 * dives (a tool object plays a block of its script when the tile is water), then gets the
 * object of the tile. Bounds: hypothesis (from the constructor, to the description of
 * "Display Task Reminder"; `.data` is the two key tables, the vtable and the name, `.bss`
 * the guard and the local description). It holds the kept copies of the inline slots
 * func_14 (0x02003BFC) and func_18 (0x020041F0) of the player. Layouts come from the code;
 * all names are placeholders.
 */
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02058eb8;

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
};

class Unk02056ed0 {
public:
    u8 unk0[8];
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;
};

/* A cell compared by value. */
struct Unk02003ab0Cell {
    Unk02003ab0Cell() {
        xy.x = -1;
        xy.y = -1;
    }

    bool operator!=(Unk02003ab0Cell o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A scene object. */
class Unk02061d08Item {
public:
    void *operator new(unsigned long size);
    void operator delete(void *p);
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    ~Unk02061d08Item();

    int unk0;
    u8 list[0xc];
    int count;
    u8 unk14[0x38];
};

/* The player. */
class Unk020c43a8 : public Unk020680d4Base {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14() {
        return cell;
    }
    virtual void func_18(Unk020680d4Dir dir) {
        sim->func_18(dir);
    }
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);

    u8 unk4[8];
    Unk020680d4 *sim;
    u8 unk10[0x28];
    bool busy;
    u8 unk39[0x1a7];
    Unk020680d4Cell cell;
    u8 unk1e8[0x1e0];
    u8 list[4];
};

/* What is shown of an action. */
struct Unk02003ab0Desc {
    Unk02003ab0Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual int func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk02003ab0Desc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk02003ab0 : public Unk02002408 {
public:
    Unk02003ab0();
    virtual ~Unk02003ab0();
    virtual int func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02003ab0Desc *func_20();
    bool func_02004084(u32 key);
    void func_0200421c();

    Unk02003ab0Cell cell;
    Unk02058eb8 *groups;
    u32 flags;
    Unk02061d08Item *tool;
    bool unk34;
};

struct Unk02003ab0Next {
    u8 unk0[0x18];
    void *owner;
    u8 unk1c[4];
    int block;
};

extern "C" {
Unk020c43a8 *func_02002414(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
int func_02002abc(Unk02002408 *a, Unk02003ab0Cell cell, u8 b);
Unk02003ab0Next *func_02007c98(void *pool, int a, int b);
void func_02007ea4(void *list, void *o);
void func_02054b80(void *p, Unk0205cf00 *def, int a);
void func_02054c1c(void *p, Unk0205cf00 *def, int a);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk02003ab0Cell *cell);
Unk02058788 *func_02058788(void *world, int map);
u32 func_02058f14(Unk02058eb8 *p, const u32 *o);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e3f0(Unk02061d08Item *item);
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
void *func_02063e2c(u32 key, int mode);
void func_020667a8(void *p, int a);
void func_020667f8(Unk020c43a8 *p, int a);
void func_02069124(void *a, void *b, int c, int d);
bool func_020691c4(void *sim);
u32 func_020a1f84(void *random);
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020bfc9c[];
extern u8 data_020be184[];
extern u8 data_020c3fc4[];
extern u8 data_020c43a8[];
extern u8 data_020d62a4[];
}

static u32 data_020b714c[3] = {0x7ac83351, 0x7ac83352, 0x7ac83353};
static u32 data_020b7158[3] = {0xbe13300e, 0xfb182d8a, 0xdebef109};

/* An enum keeps the `movne` / `moveq` order of the original. */
enum Unk02003ab0Bool { UNK_02003AB0_FALSE, UNK_02003AB0_TRUE };

static inline Unk02003ab0Bool func_land(u32 type) {
    return type != 0 && type != 0x8000 ? UNK_02003AB0_FALSE : UNK_02003AB0_TRUE;
}

static inline Unk02003ab0Bool func_water(u32 tile) {
    return (tile & 0xc000) == 0 ? UNK_02003AB0_FALSE : UNK_02003AB0_TRUE;
}

static inline u32 *func_tile(Unk02056ed0 *layer, const Unk02003ab0Cell &cell) {
    u32 *tiles = layer->tiles;
    return &tiles[(u32)cell.xy.y * layer->info->width + (u32)cell.xy.x];
}

static inline bool func_in_inventory(void *inventory, Unk0205cf00 *def) {
    return func_02054dc4(inventory, def, 0) != 0;
}

Unk02003ab0::Unk02003ab0() {
    flags = 0;
    tool = 0;
    unk34 = false;
}

Unk02003ab0::~Unk02003ab0() {
}

const Unk02003ab0Desc *Unk02003ab0::func_20() {
    static Unk02003ab0Desc desc(2, 0, 0xc, "Dig or Dive");
    return &desc;
}

int Unk02003ab0::func_08() {
    Unk020680d4Cell here = func_02002414(this)->func_14();
    if (cell.pos.unk3 != here.pos.unk3) {
        return false;
    }
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    u32 *tiles = layer->tiles;
    u32 type = tiles[(u32)cell.xy.y * layer->info->width + (u32)cell.xy.x] & 0xc000;
    return func_land(type);
}

int Unk02003ab0::func_0c() {
    return 0;
}

int Unk02003ab0::func_10() {
    if (flags & 1) {
        Unk020c43a8 *actor = func_02002414(this);
        actor->busy = false;
        func_020667f8(actor, 0xa);
    }
    return 1;
}

int Unk02003ab0::func_14() {
    Unk020c43a8 *actor = func_02002414(this);
    Unk020680d4 *sim = actor->sim;
    if (cell != (const Unk02003ab0Cell &)sim->func_14()) {
        return func_02002abc(this, cell, 1);
    }
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    u32 *tiles = layer->tiles;
    flags |= (tiles[(u32)cell.xy.y * layer->info->width + (u32)cell.xy.x] & 0xc000) == 0 ? 2 : 0;
    if (sim != 0) {
        func_0200264c(this);
        actor->busy = true;
        void *random = data_020d62a4;
        flags |= 1;
        if (flags & 2) {
            u32 n = func_020a1f84(random) % 3;
            if (!func_02004084(data_020b714c[n])) {
                return 2;
            }
        } else {
            u32 i = func_020a1f84(random) % 3;
            func_02069124(sim, func_02063e2c(data_020b7158[i], 0), 0xa, 0);
        }
    }
    return 1;
}

int Unk02003ab0::func_18() {
    Unk020680d4 *sim = func_02002414(this)->sim;
    if (cell != (const Unk02003ab0Cell &)sim->func_14()) {
        return 2;
    }
    if (flags & 2) {
        if (tool->count != 0) {
            return 0;
        }
    } else if (!func_020691c4(sim)) {
        return 0;
    }
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    u32 *tile = func_tile(layer, cell);
    u32 id = func_02058f14(groups, tile);
    if (id != 0) {
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, id);
        void *inventory = data_020bfc9c;
        if (func_in_inventory(inventory, def)) {
            func_02054c1c(inventory, def, 0);
        } else {
            func_02054b80(inventory, def, 0);
        }
    }
    func_020667a8(data_020c43a8, func_water(*tile));
    return 1;
}

void Unk02003ab0::func_1c() {
    if (flags & 1) {
        Unk020c43a8 *actor = func_02002414(this);
        actor->busy = false;
        func_020667f8(actor, 0xa);
    }
    if (flags & 2) {
        func_0200421c();
        flags &= ~2;
    }
}

bool Unk02003ab0::func_02004084(u32 key) {
    Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, 0x469724a2);
    int found = -1;
    for (int i = 0; i < def->script->func_0209576c()->count406; i++) {
        if (key == func_0205cea4(def, i)->unk0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        return false;
    }
    Unk020c43a8 *actor = func_02002414(this);
    if (tool == 0) {
        actor->func_18(Unk020680d4Dir(0));
        tool = new Unk02061d08Item(def, actor->func_14(), Unk020680d4Dir(0));
    }
    if (tool != 0) {
        func_0205e3f0(tool);
        Unk02003ab0Next *next = func_02007c98(data_020be184, 0xb, 2);
        if (next == 0) {
            return false;
        }
        next->block = found;
        func_02007ea4(tool->list, next);
        if (actor != 0) {
            func_02007ea4(actor->list, next->owner);
        }
    }
    return true;
}

void Unk02003ab0::func_0200421c() {
    if (tool != 0) {
        delete tool;
        tool = 0;
    }
}
