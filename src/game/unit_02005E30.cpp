/*
 * Unit 0x02005E30-0x020061DC: the action "Place Object", derived from `Unk02009084`: the
 * sim replaces the object by the chosen one, the old object returns to the inventory and
 * the need of the room is updated. Bounds: hypothesis (from the description of the action
 * to its inline destructors; `.rodata` is the local table of func_38, `.data` the name
 * and the vtable, `.bss` the guard and the local description). Layouts come from the
 * code; all names are placeholders.
 */
#include "game/unk_sim.h"

class Unk0205cf00;

/* A scene object. */
class Unk02061d08Item {
public:
    void *operator new(unsigned long size);
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    void *visible;
    u8 unk48[4];
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

/* What is shown of an action. */
struct Unk02005e7cDesc {
    Unk02005e7cDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02005e7cDesc *func_20() = 0;

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

class Unk02005e7c : public Unk02009084 {
public:
    Unk02005e7c();
    virtual ~Unk02005e7c() {}
    virtual const Unk02005e7cDesc *func_20();
    virtual void func_2c();
    virtual int func_30() {
        return 0xa;
    }
    virtual void func_34();
    virtual void func_38();
    virtual void func_3c();
};

struct Unk02005e7cEntry {
    void *unk0;
    int count;
};

struct Unk02005e7cNeed {
    u8 unk0[8];
    int value;
};

struct Unk02005e7cPlayer {
    u8 unk0[0xc];
    void *sim;
};

struct Unk02005e7cAudio {
    u8 unk0[0xd0];
    int unkd0;
};

struct Unk02005e7cSounds {
    u8 unk0[0xc];
    u8 unkc;
};

extern "C" {
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_02052a00(Unk02005e7cSounds *s, u8 a);
void func_02054c1c(void *p, Unk0205cf00 *def, int a);
void func_02054cf0(void *p, Unk02005e7cEntry *e, int a);
Unk02005e7cEntry *func_02054dc4(void *p, Unk0205cf00 *def, int a);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
void func_0205e3f0(Unk02061d08Item *item);
void func_0205e4d0(Unk02061d08Item *item);
Unk02061d08Item *func_0205fb4c(void *list, int key, Unk0205f098 *out, int a);
void func_0205fda0(void *m, Unk02061d08Item *item);
void *func_02063e2c(u32 key, int mode);
Unk02005e7cNeed *func_02066488(Unk02005e7cPlayer *p, int i);
bool func_02066748(Unk02005e7cPlayer *p, int key, int a, int b, int c, int d);
void func_02069124(void *a, void *b, int c, int d);
Unk02005e7cAudio *func_020a2994();
void func_020a3734(Unk02005e7cAudio *a, int b);
u32 func_020a1f84(void *random);
extern u8 data_020bfc9c[];
extern Unk02005e7cSounds data_020bfc3c;
extern u8 data_020c3fd4[];
extern Unk02005e7cPlayer data_020c43a8;
extern u8 data_020d62a4[];
}

static inline bool func_in_inventory(void *inventory, Unk0205cf00 *def) {
    return func_02054dc4(inventory, def, 0) != 0;
}

const Unk02005e7cDesc *Unk02005e7c::func_20() {
    static Unk02005e7cDesc desc(8, 0, 0x13, "Place Object");
    return &desc;
}

Unk02005e7c::Unk02005e7c() {
}

void Unk02005e7c::func_34() {
    func_02066748(&data_020c43a8, 0x32, 1, 0xa, 0, 0);
}

void Unk02005e7c::func_38() {
    u32 keys[3] = {0x04d1fb53, 0xadade1d2, 0xadade1d3};
    u32 i = func_020a1f84(data_020d62a4) % 3;
    func_02069124(data_020c43a8.sim, func_02063e2c(keys[i], 2), 0xa, 1);
    if (func_020a2994()->unkd0 != 0) {
        func_020a3734(func_020a2994(), 0);
        func_02052a00(&data_020bfc3c, data_020bfc3c.unkc);
    }
}

void Unk02005e7c::func_3c() {
    void *inventory = data_020bfc9c;
    Unk02005e7cEntry *e = func_02054dc4(inventory, screen, 0);
    if (e != 0) {
        func_02054cf0(inventory, e, 0);
    }
    Unk0205cf00 *def = func_02002438(this)->def;
    if (func_in_inventory(inventory, def)) {
        func_02054dc4(inventory, def, 0)->count++;
    } else {
        func_02054c1c(inventory, def, 0);
    }
}

void Unk02005e7c::func_2c() {
    Unk02061d08Item *o = func_02002438(this);
    if (screen == 0) {
        return;
    }
    Unk02061d08Item *item = new Unk02061d08Item(screen, o->func_14(), o->func_1c());
    if (o->visible != 0) {
        func_0205e4d0(o);
        if (item != 0) {
            func_0205e3f0(item);
        }
    }
    int map = o->func_14().pos.unk3;
    int found = 4;
    Unk0205f098 list;
    u32 keys[4];
    keys[0] = 0x0e2508ee;
    keys[1] = 0x4089a7c6;
    keys[2] = 0x61aadad6;
    keys[3] = 0xaaba8051;
    for (int i = 0; i < 4; i++) {
        if (func_0205fb4c(data_020c3fd4, keys[i], &list, map) != 0) {
            found = i;
            break;
        }
    }
    if (found != 4) {
        Unk02005e7cNeed *need = func_02066488(&data_020c43a8, found);
        int value = need->value;
        u32 key = keys[found];
        value -= func_0205d1b4(o->def, key);
        if (item != 0) {
            value += func_0205d1b4(item->def, key);
        }
        need->value = value;
    }
    func_0205fda0(data_020c3fd4, o);
}
