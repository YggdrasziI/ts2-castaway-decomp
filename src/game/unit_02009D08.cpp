/*
 * Unit 0x02009D08-0x0200A2EC: the action "Action Upgrade": it pays the cost, fades
 * the screen and replaces the object by its upgraded version. Bounds: hypothesis
 * (from the description of the action to its destructors; the next action loads
 * its static at offset 0, so it has its own file). Layouts come from the code; all
 * names are placeholders. `end` is `volatile` as a hypothesis: the original reloads
 * it across a call in func_2c.
 */
#include "game/unk_objscript.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

struct Unk020615f0Def {
    u8 unk0[0x30];
    u32 flags;
};

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02060d78;

class Unk02061d08Item {
public:
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    void *operator new(unsigned long size);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 list[0x24];
    Unk0205cf00 *def;
    u8 unk2c[4];
    u16 vars[10];
    Unk02060d78 *visible;
    u8 unk48[4];
};

/* The sim that runs the action. */
class Unk02009d08Actor {
public:
    u8 unk0[0xc];
    void *sim;
};

struct Unk02009d08Counter {
    int unk0;
    int unk4;
};

struct Unk02009d08Panel {
    int unk0;
    u32 flags;
};

class Unk0206bcf0 {
public:
    void func_0206e104(int v);

    u8 unk0[0x11c];
    Unk02009d08Panel *panel;
    u8 unk120[0x104];
    int unk224;
    u8 unk228[4];
    u32 flags;
};

struct Unk02009d08World {
    u8 unk0[0xfc];
    s8 map;
};

/* What is shown of an action. */
struct Unk02009d08Desc {
    Unk02009d08Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02009d08Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

/* The interaction base (vtable 0x020B7654). */
class Unk02008d18 : public Unk02002408 {
public:
    virtual ~Unk02008d18() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual void func_24();
    virtual int func_28() = 0;
    virtual void func_2c() = 0;

    u8 unk20[0x10];
};

class Unk0200a2d8 : public Unk02008d18 {
public:
    virtual const Unk02009d08Desc *func_20();
    virtual void func_24();
    virtual int func_28();
    virtual void func_2c();

    int id;
    int inventory;
    int facing;
    int duration;
    int cost;
    int start;
    volatile int end;
    s8 x;
    s8 y;
    bool copy;
    int state;
    Unk02061d08Item *item;
    void *anim;
};

extern "C" {
Unk0206bcf0 *func_0206bce0();
int func_020a18e4();
void func_020a1494(int system, int a, int b);
void func_020a11f8(int system, int a, int b);
int func_020a1280(int system, int a, int b);
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
void func_0205e3f0(Unk02061d08Item *item);
void func_0205e4d0(Unk02061d08Item *item);
bool func_0205ec9c(Unk02061d08Item *item);
int func_0205ecc0(Unk02061d08Item *item, u32 key);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Value *block, void *p);
void func_0205e1b8(Unk02061d08Item *item, void *p);
void func_0205fda0(void *m, Unk02061d08Item *item);
Unk020615f0Def func_0205cd6c(Unk0205cf00 *def, int key);
bool func_020691c4(void *sim);
bool func_0206135c(Unk02060d78 *e);
void *func_02007340(void *p, int kind);
void func_02007ea4(void *list, void *o);
void func_02002784(void *o);
Unk02009d08Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
void func_020662c8(void *p, int i, int n);
Unk02009d08Counter *func_02066494(void *p, int i);
void func_02054cb4(void *p, int id, int a);
void *func_02058788(void *world, int map);
void func_020581f4(void *lot, int a);
void func_020585a0(void *world, int map);
extern u8 data_020be184[];
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern Unk02009d08World data_020c3ba4;
}

const Unk02009d08Desc *Unk0200a2d8::func_20() {
    static Unk02009d08Desc desc(0xe, 0, 8, "Action Upgrade");
    return &desc;
}

void Unk0200a2d8::func_24() {
}

int Unk0200a2d8::func_28() {
    if (state != 0) {
        Unk02009d08Actor *actor = func_02002414(owner);
        Unk02061d08Item *sim = func_02002438(this);
        switch (state) {
        case 1:
            if (duration <= 0) {
                state = 4;
            } else {
                func_0206bce0()->flags |= 0x2000;
                func_020a1494(func_020a18e4(), 2, 0x10);
                func_020a11f8(func_020a18e4(), 2, 1);
                state = 2;
            }
            break;
        case 2:
            if (func_020a1280(func_020a18e4(), 2, 1)) {
                func_0206bce0()->panel->flags |= 8;
                func_0206bce0()->func_0206e104(duration);
                state = 3;
            }
            break;
        case 3:
            if (func_0206bce0()->unk224 <= 0) {
                state = 4;
            }
            break;
        }
        if (state == 4) {
            if (cost > 0) {
                func_020662c8(actor, 1, -cost);
            }
            if ((cost == 0 || func_02066494(actor, 1)->unk4 > 0) && id != 0) {
                Unk020680d4Dir dir = sim->func_1c();
                if (facing != 0) {
                    switch (facing) {
                    case (int)0xd82a09e8:
                        dir.v = 0;
                        break;
                    case (int)0xfa6fc214:
                        dir.v = 1;
                        break;
                    case 0x1202d214:
                        dir.v = 3;
                        break;
                    case 0x30a71683:
                        dir.v = 2;
                        break;
                    }
                }
                Unk020680d4Cell cell = sim->func_14();
                if (x >= 0) {
                    cell.xy.x = x;
                }
                if (y >= 0) {
                    cell.xy.y = y;
                }
                item = new Unk02061d08Item(func_0205f6f8(data_020c3fc4, id), cell, dir);
                if (item != 0) {
                    if (sim->visible != 0) {
                        func_0205e4d0(sim);
                        func_0205e3f0(item);
                    }
                    if (inventory != 0) {
                        func_02054cb4(data_020bfc9c, inventory, 0);
                    }
                    if (copy) {
                        int i;
                        Unk020956f8 *script;
                        u16 *vars;
                        Unk02099c78Var *var = sim->def->script->func_0209585c();
                        vars = item->vars;
                        script = item->def->script;
                        for (i = 0; i < 4; i++, var++) {
                            int value = func_0205ecc0(sim, var->unk0);
                            int index = script->func_020958bc(var->unk0);
                            if (index >= 0) {
                                vars[index] = value;
                            }
                        }
                    }
                }
            }
            if (duration > 0) {
                state = 5;
            } else {
                state = 7;
            }
        } else if (state == 5) {
            if (func_0206bce0()->panel->flags & 0x80) {
                func_020a1494(func_020a18e4(), 2, 0x20);
                func_020a11f8(func_020a18e4(), 2, 0);
                state = 6;
            }
        } else if (state == 6) {
            if (func_020a1280(func_020a18e4(), 2, 0)) {
                func_0206bce0()->panel->flags &= ~8;
                func_0206bce0()->flags &= ~0x2000;
                state = 7;
            }
        }
        if (state == 7) {
            if (start != 0 && item != 0) {
                anim = func_02007340(data_020be184, 2);
                func_02007ea4(item->list, anim);
                Unk02099c78Value *block = item->def->script->func_02095960(start);
                if (block == 0) {
                    state = 0;
                } else {
                    func_0205e038(item, block, actor);
                    state = 8;
                }
            } else {
                state = 0;
            }
        } else if (state == 8) {
            const Unk020615f0Def &def = func_0205cd6c(item->def, start);
            if ((def.flags & 2) && actor->sim != 0 && !func_020691c4(actor->sim)) {
            } else if ((def.flags & 1) && item->visible != 0 && !func_0206135c(item->visible)) {
            } else {
                state = 0;
            }
        }
        if (state != 0) {
            return 0;
        }
    }
    return 1;
}

void Unk0200a2d8::func_2c() {
    if (item != 0) {
        if (end != 0) {
            Unk02099c78Block *block = func_02002438(this)->def->script->func_020957ec(end);
            if (block != 0) {
                Unk02061c04 runner(func_02002438(this));
                runner.func_02099ce0(end);
            }
        }
        func_0205fda0(data_020c3fd4, func_02002438(this));
        if (anim != 0) {
            func_02002784(anim);
        }
        func_0205e1b8(item, func_02002414(owner));
    }
}
