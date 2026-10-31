/*
 * Unit 0x020061DC-0x02006458: the action "Plant Seed", derived from `Unk02009084`: the
 * sim plants the chosen seed, the object gets a new definition and starts the follow-up
 * action, then the seed leaves the inventory. Bounds: hypothesis (from the description
 * of the action to its inline destructors; `.data` is the name and the vtable, `.bss`
 * the guard and the local description). Layouts come from the code; all names are
 * placeholders.
 */
#include "game/unk_sim.h"

class Unk0205cf00;

struct Unk02006228Cell {
    Unk02006228Cell() {
        xy.x = -1;
        xy.y = -1;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* The object that is planted in. */
class Unk02006228Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk02006228Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 list[0x20];
    int key;
};

/* The action of kind 14 that follows. */
struct Unk02006228Next {
    void func_set(Unk02006228Cell c, Unk020680d4Dir rot, int key, int value, int unk40, int unk44) {
        cell = c;
        this->rot = rot;
        this->key = key;
        this->value = value;
        unk38 = true;
        this->unk40 = unk40;
        this->unk44 = unk44;
    }

    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[6];
    Unk02006228Cell cell;
    Unk020680d4Dir rot;
    int key;
    int value;
    bool unk38;
    u8 unk39[7];
    int unk40;
    int unk44;
};

/* What is shown of an action. */
struct Unk02006228Desc {
    Unk02006228Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02006228Desc *func_20() = 0;

    u8 unk4[0x1c];
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

    int key;
    bool active;
};

class Unk02009084 : public Unk020071d4 {
public:
    Unk02009084();
    virtual ~Unk02009084() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_18();
    virtual int func_30() = 0;
    virtual void func_34() = 0;
    virtual void func_38() = 0;
    virtual void func_3c() = 0;

    int state;
    Unk0205cf00 *screen;
};

class Unk02006228 : public Unk02009084 {
public:
    Unk02006228();
    virtual ~Unk02006228() {}
    virtual const Unk02006228Desc *func_20();
    virtual void func_2c();
    virtual int func_30() {
        return 0xb;
    }
    virtual void func_34();
    virtual void func_38();
    virtual void func_3c();
};

extern "C" {
Unk02006228Item *func_02002438(Unk02002408 *a);
Unk02006228Next *func_02007c98(void *pool, int a, int b);
void func_02007ea4(void *list, void *o);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_02054cf0(void *p, void *e, int a);
void func_0205b074(void *c, int a, Unk02006228Item *target, void *actor);
int func_0205d234(Unk0205cf00 *def, u32 key, u32 key2);
int func_0205f6a4(void *db, int key);
bool func_02066748(void *p, int key, int a, int b, int c, int d);
extern u8 data_020be184[];
extern u8 data_020bfc9c[];
extern u8 data_020c3cc8[];
extern u8 data_020c3fc4[];
extern u8 data_020c43a8[];
extern u8 data_020c4770[];
}

static inline bool func_exists(int def) {
    return func_0205f6a4(data_020c3fc4, def) != -1;
}

const Unk02006228Desc *Unk02006228::func_20() {
    static Unk02006228Desc desc(9, 0, 0x12, "Plant Seed");
    return &desc;
}

Unk02006228::Unk02006228() {
}

void Unk02006228::func_34() {
    func_02066748(data_020c43a8, 0x32, 1, 0xa, 0, 0);
}

void Unk02006228::func_38() {
}

void Unk02006228::func_3c() {
    void *inventory = data_020bfc9c;
    void *e = func_02054dc4(inventory, screen, 0);
    if (e != 0) {
        func_02054cf0(inventory, e, 0);
    }
}

void Unk02006228::func_2c() {
    Unk02006228Item *o = func_02002438(this);
    if (screen == 0) {
        return;
    }
    func_0205b074(data_020c3cc8, key, o, data_020c43a8);
    int def = func_0205d234(screen, 0xe3549bc4, 0x3c1b8a2e);
    if (func_exists(def)) {
        o->key = def;
    }
    Unk02006228Next *next = func_02007c98(data_020be184, 0xe, 2);
    if (next == 0) {
        return;
    }
    next->func_set(o->func_14(), o->func_1c(), 0x469724a2, 0xa3cedc45, key, 0);
    func_02007ea4(o->list, next);
    func_02007ea4(data_020c4770, next->unk18);
}
