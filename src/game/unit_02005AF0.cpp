/*
 * Unit 0x02005AF0-0x02005E30: the action "Action Pickup": the sim plays its animations in
 * front of the object, then the object goes to the inventory and its script runs. Bounds:
 * hypothesis (from the description of the action to its inline destructors; `.data` is
 * the name and the vtable, `.bss` the guard and the local description). Its constructor
 * is inline in the action factory (`unit_02007204.cpp`). Layouts come from the code; all
 * names are placeholders.
 */
#include "game/unk_objscript.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02060d78;
struct Unk02063d84;

class Unk02061d08Item {
public:
    virtual void func_00(Unk020680d4Vec v);
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *visible;
};

class Unk02005e1cActor {
public:
    u8 unk0[0xc];
    void *sim;
};

/* The definition given to func_020615f0. */
struct Unk02005e1cDef {
    Unk02005e1cDef() {
        model = 0;
        xform = 0;
        anim = 0;
        unkc = 0;
        unk10 = 0;
        unk14 = 0;
        unk18 = 0;
        unk1c = 0;
        texanim = 0;
        unk2c = 0;
        flags = 0;
    }

    int model;
    u32 xform;
    u32 anim;
    u32 unkc;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1c;
    u32 texanim;
    int unk24;
    int unk28;
    int unk2c;
    u32 flags;
};

/* What is shown of an action. */
struct Unk02005e1cDesc {
    Unk02005e1cDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02005e1cDesc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
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
    virtual bool func_24();
    virtual int func_28();
    virtual void func_2c() = 0;

    int key;
    bool active;
};

class Unk02005e1c : public Unk020071d4 {
public:
    virtual int func_18();
    virtual const Unk02005e1cDesc *func_20();
    virtual bool func_24();
    virtual void func_2c();
    virtual bool func_30();
    void func_02005d18();

    u32 anim0;
    u32 anim1;
    u32 anim2;
    int unk34;
    int model;
    u32 xform;
    int state;
};

extern "C" {
Unk02005e1cActor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_02002670(Unk02002408 *a);
void func_02002784(Unk02002408 *a);
void func_02054c1c(void *p, Unk0205cf00 *def, int a);
bool func_0205ec9c(Unk02061d08Item *item);
void func_0205e4d0(Unk02061d08Item *item);
void func_0205fda0(void *m, Unk02061d08Item *item);
void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames);
void func_020615f0(Unk02060d78 *e, Unk02005e1cDef *def);
Unk02063d84 *func_02063e2c(u32 key, int mode);
void func_020667a8(void *p, int a);
void func_020667f8(Unk02005e1cActor *actor, int a);
void func_02069124(void *sim, Unk02063d84 *anim, int a, int b);
bool func_020691c4(void *sim);
extern u8 data_020bfc9c[];
extern u8 data_020c3fd4[];
extern u8 data_020c43a8[];
}

const Unk02005e1cDesc *Unk02005e1c::func_20() {
    static Unk02005e1cDesc desc(7, 0, 9, "Action Pickup");
    return &desc;
}

bool Unk02005e1c::func_24() {
    Unk02005e1cActor *actor = func_02002414(owner);
    void *sim = actor->sim;
    Unk02060d78 *visible = func_02002438(this)->visible;
    if (actor != 0) {
        if (anim0 != 0) {
            func_02069124(sim, func_02063e2c(anim0, 2), 0xa, 0);
        } else if (anim2 != 0) {
            func_020667f8(actor, 0xa);
        }
    }
    if (model != 0) {
        Unk02005e1cDef def;
        def.model = model;
        def.xform = xform;
        if (xform != 0) {
            def.flags = 1;
        }
        func_020615f0(visible, &def);
    }
    if (anim2 != 0) {
        func_02061298(visible, func_02063e2c(anim2, 0), false, 0x10);
    } else {
        func_02061298(visible, 0, false, 0x10);
    }
    return true;
}

bool Unk02005e1c::func_30() {
    return func_0205ec9c(func_02002438(this));
}

int Unk02005e1c::func_18() {
    if (state == 0) {
        if (Unk020071d4::func_18() != 0) {
            state = 1;
            Unk02005e1cActor *actor = func_02002414(owner);
            void *sim = actor->sim;
            if (actor != 0) {
                if (anim1 != 0) {
                    func_02005d18();
                    func_02069124(sim, func_02063e2c(anim1, 2), 0xa, 0);
                } else {
                    return 1;
                }
            } else {
                return 1;
            }
        }
    } else if (func_020691c4(func_02002414(owner)->sim)) {
        return 1;
    }
    return 0;
}

void Unk02005e1c::func_02005d18() {
    Unk02061d08Item *o = func_02002438(this);
    o->func_00(Unk020680d4Vec(0, -0x64000, 0));
}

void Unk02005e1c::func_2c() {
    Unk02061d08Item *o = func_02002438(this);
    if (o->visible != 0) {
        func_0205e4d0(o);
    }
    func_02002670(this);
    func_02002784(owner);
    func_02054c1c(data_020bfc9c, o->def, 0);
    if (o->def->script->func_020957ec(0x15370570) != 0) {
        Unk02061c04 vm(o);
        vm.func_02099ce0(0x15370570);
    }
    func_0205fda0(data_020c3fd4, o);
    func_020667a8(data_020c43a8, 3);
}
