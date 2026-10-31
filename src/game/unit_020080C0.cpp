/*
 * Unit 0x020080C0-0x0200825C: the action "Action Change Clothing": it fades the screen,
 * applies the outfit of the player to the sim and fades back; func_020081dc returns that
 * outfit. Bounds: hypothesis (from the description of the action to the inline
 * functions; `.data` is the name and the vtable, `.bss` the guard and the local
 * description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_catalog.h"
#include "game/unk_sim.h"

/* What is shown of an action. */
struct Unk02008240Desc {
    Unk02008240Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

/* The player, the sim that runs the action. */
class Unk02008240Actor {
public:
    u8 unk0[0xc];
    void *sim;
    u8 unk10[0x198];
    Unk020081dc outfit;
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
    virtual const Unk02008240Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

class Unk02008d18 : public Unk02002408 {
public:
    virtual ~Unk02008d18() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual void func_24() {}
    virtual int func_28() = 0;
    virtual void func_2c() = 0;

    u8 unk20[0x10];
};

class Unk02008240 : public Unk02008d18 {
public:
    virtual const Unk02008240Desc *func_20();
    virtual int func_28();
    virtual void func_2c() {}

    bool started;
};

extern "C" {
Unk02008240Actor *func_02002414(Unk02002408 *a);
int func_020a18e4();
void func_020a1494(int system, int a, int b);
void func_020a11f8(int system, int a, int b);
int func_020a1280(int system, int a, int b);
void func_020685e0(void *sim);
void func_0206708c(Unk02008240Actor *actor, int a, int b);
void func_020684f4(void *sim, Unk020081dc *outfit);
Unk020081dc func_020081dc(Unk02008240Actor *actor);
}

const Unk02008240Desc *Unk02008240::func_20() {
    static Unk02008240Desc desc(0, 0, 0xa, "Action Change Clothing");
    return &desc;
}

int Unk02008240::func_28() {
    Unk02008240Actor *actor = func_02002414(owner);
    void *sim = actor->sim;
    if (!started) {
        func_020a1494(func_020a18e4(), 0, 0x10);
        func_020a11f8(func_020a18e4(), 0, 1);
        started = true;
        return 0;
    }
    if (!func_020a1280(func_020a18e4(), 0, 1)) {
        return 0;
    }
    func_020685e0(sim);
    func_0206708c(actor, -1, 0);
    {
        Unk020081dc outfit = func_020081dc(actor);
        func_020684f4(sim, &outfit);
    }
    func_020a11f8(func_020a18e4(), 0, 0);
    return 1;
}

extern "C" Unk020081dc func_020081dc(Unk02008240Actor *actor) {
    return actor->outfit;
}
