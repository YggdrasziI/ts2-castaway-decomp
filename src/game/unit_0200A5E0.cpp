/*
 * Unit 0x0200A5E0-0x0200AD70: the action "Use Tool From Inventory": it walks to the
 * target object, creates the tool item and plays its animation. Bounds: hypothesis
 * (from the description of the action to its deleting destructor; `.data` is the name
 * and the vtable). Layouts come from the code; all names are placeholders.
 *
 * Open gaps: func_14 95.84 % (stack slots of the temporaries, `add ip, sp, #0x20` kept
 * for the cell of func_add), func_18 98.10 % (order of the loads of the last animation),
 * func_08 99.48 % (order of the two conditional moves).
 */
#include "game/unk_catalog.h"
#include "game/unk_objscript.h"
#include "game/unk_pool.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
    s16 d0;
    s16 d1;
    u8 unk8[8];
    Unk020956f8 *script;
};

class Unk02061d08Item {
public:
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    ~Unk02061d08Item();
    void *operator new(unsigned long size);
    void operator delete(void *p);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 list[0xc];
    int unk10;
    u8 unk14[0x14];
    Unk0205cf00 *def;
    u8 unk2c[0x20];
};

/* The sim that runs the action. */
class Unk0200ad40Actor {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 unk4[8];
    Unk02061d08Item *sim;
    u8 unk10[0x3b8];
    u8 list[4];
};

/* An animation object. */
struct Unk0200ad40Anim {
    u8 unk0[0x18];
    int unk18;
    u8 unk1c[4];
    int unk20;
    u8 unk24;
    bool unk25;
};

/* What is shown of an action. */
struct Unk0200ad40Desc {
    Unk0200ad40Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

/* A cell built from its parts. */
struct Unk0200ad40Cell {
    Unk0200ad40Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    bool operator!=(const Unk020680d4Cell &o) const {
        return pos != o.pos || xy != o.xy;
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
    virtual const Unk0200ad40Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
    bool started;
    Unk020680d4Cell cell;
    Unk020680d4Dir dir;
};

class Unk0200ad40 : public Unk02002408 {
public:
    virtual ~Unk0200ad40();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk0200ad40Desc *func_20();

    int id;
    int key;
    bool unk38;
    Unk02061d08Item *item;
    int unk40;
    int script;
    u8 unk48;
    bool unk49;
};

extern "C" {
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e3f0(Unk02061d08Item *item);
Unk020680d4Cell func_0205eed4(Unk02061d08Item *item, Unk0205cf00 *def);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
void *func_02007340(void *p, int kind);
void *func_02007c98(void *p, int kind, int b);
void func_02007ea4(void *list, void *o);
void func_02004848(void *o, int a, int key, int b);
Unk0200ad40Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
bool func_0200273c(Unk02002408 *a);
bool func_02002760(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
int func_02002abc(Unk02002408 *a, Unk020680d4Cell cell, u8 b);
extern u8 data_020be184[];
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
}

static inline Unk0200ad40Cell func_add(const Unk020680d4Cell &c, Unk020680d4Xy d) {
    return Unk0200ad40Cell(c.pos.unk3, c.pos.unk2, c.pos.unk0, c.xy.x + d.x, c.xy.y + d.y);
}

static inline bool func_same(Unk020680d4Dir a, Unk020680d4Dir b) {
    return a.v == b.v;
}

enum Unk0200ad40Found {
    UNK_0200AD40_MISSING,
    UNK_0200AD40_FOUND
};

static inline Unk0200ad40Found func_found(void *p) {
    return p != 0 ? UNK_0200AD40_FOUND : UNK_0200AD40_MISSING;
}

static inline bool func_differs(const Unk020680d4Cell &a, Unk020680d4Cell b) {
    return a != b;
}

static inline bool func_away(Unk02061d08Item *o, Unk020680d4Cell c) {
    Unk020680d4Xy size(o->def->w, o->def->h);
    Unk020680d4Xy rel = func_020619a8(o, size, o->func_1c());
    return func_add(o->func_14(), rel) != c;
}

const Unk0200ad40Desc *Unk0200ad40::func_20() {
    static Unk0200ad40Desc desc(0xf, 0, 0xe, "Use Tool From Inventory");
    return &desc;
}

bool Unk0200ad40::func_08() {
    Unk020680d4Cell c = (func_02002760(this) ? func_02002414(this) : func_02002414(owner))->func_14();
    return cell.pos.unk3 != c.pos.unk3 ? false : true;
}

int Unk0200ad40::func_0c() {
    return 0;
}

int Unk0200ad40::func_10() {
    delete item;
    return 1;
}

int Unk0200ad40::func_14() {
    Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, id);
    Unk02061d08Item *sim;
    if (func_02002760(this)) {
        sim = func_02002414(this)->sim;
        if (func_differs(cell, sim->func_14())) {
            return func_02002abc(this, cell, unk48);
        }
    } else {
        if (!func_0200292c(owner)) {
            return 0;
        }
        sim = func_02002414(owner)->sim;
        if (func_away(func_02002438(this), sim->func_14())) {
            return func_0200294c(this, unk48);
        }
        cell = func_0205eed4(func_02002438(this), def);
    }
    if (func_found(func_02054dc4(data_020bfc9c, def, 0)) == UNK_0200AD40_MISSING) {
        return 2;
    }
    if (unk38) {
        key = def->script->func_0209599c(key);
        unk38 = false;
    }
    if (func_same(dir, 4)) {
        Unk02098ff0 rot = sim->func_0c();
        if (rot.y < 0x2000) {
            dir.v = 0;
        } else if (rot.y < 0x6000) {
            dir.v = 1;
            cell.xy.y -= def->d0 - 1;
        } else if (rot.y < 0xa000) {
            dir.v = 2;
            cell.xy.x -= def->d0 - 1;
            cell.xy.y -= def->d1 - 1;
        } else if (rot.y >= 0xe000) {
            dir.v = 0;
        } else {
            dir.v = 3;
            cell.xy.x -= def->d1 - 1;
        }
    }
    func_0200264c(this);
    item = new Unk02061d08Item(def, cell, dir);
    return 1;
}

int Unk0200ad40::func_18() {
    int done = 0;
    Unk0200ad40Actor *actor;
    if (func_02002760(this)) {
        actor = func_02002414(this);
    } else {
        actor = func_02002414(owner);
    }
    if (item != 0) {
        if (!started) {
            func_0205e3f0(item);
            Unk0205cf00 *d = item->def;
            Unk02099c78Block *block = func_0205cea4(d, key);
            Unk02099c78Value *values = d->script->func_02095ab0();
            Unk0200ad40Anim *o = (Unk0200ad40Anim *)func_02007c98(data_020be184, 0xb, 2);
            if (o == 0) {
                return 2;
            }
            o->unk20 = key;
            for (int i = block->start; i < block->start + block->count; i++) {
                u32 h = values[i].unk0;
                if (h == 0x032a3395 || h == 0x2d81e2b8) {
                    func_02004848(o, key, values[i].unk4, 1);
                }
            }
            func_02007ea4(item->list, o);
            if (actor != 0) {
                func_02007ea4(actor->list, (void *)o->unk18);
            }
            if (func_0200273c(this)) {
                Unk0200ad40Anim *p = (Unk0200ad40Anim *)func_02007340(data_020be184, 4);
                if (p != 0) {
                    bool v = unk49;
                    p->unk20 = unk40;
                    p->unk25 = v;
                    func_02007ea4(func_02002438(this)->list, p);
                }
            }
            started = true;
        } else if (item->unk10 == 0) {
            done = 1;
        }
    }
    return done;
}

void Unk0200ad40::func_1c() {
    delete item;
    if (func_0200273c(this)) {
        if (func_02002438(this)->def->script->func_020957ec(script) != 0) {
            Unk02061c04 runner(func_02002438(this));
            runner.func_02099ce0(script);
        }
    }
}

Unk0200ad40::~Unk0200ad40() {
}
