/*
 * Unit 0x0200A2EC-0x0200A5E0: the action "Action Upgrade Indirectly": it replaces
 * the object by its upgraded version, with a fade. Bounds: hypothesis (from the
 * description of the action to its destructors). Layouts come from the code; all
 * names are placeholders.
 *
 * Open gap: func_18 98.71 % (registers of this, the items and the copy loop; 80
 * declaration orders tried).
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

class Unk0200a5cc : public Unk02002408 {
public:
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02009d08Desc *func_20();

    int id;
    bool copy;
    bool fade;
    u8 fading;
    s8 x;
    s8 y;
    Unk020680d4Dir dir;
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

const Unk02009d08Desc *Unk0200a5cc::func_20() {
    static Unk02009d08Desc desc(0xe, 0, 7, "Action Upgrade Indirectly");
    return &desc;
}

bool Unk0200a5cc::func_08() {
    return true;
}

int Unk0200a5cc::func_0c() {
    return 0;
}

int Unk0200a5cc::func_10() {
    return 1;
}

int Unk0200a5cc::func_14() {
    func_0205ec9c(func_02002438(this));
    func_0200264c(this);
    return 1;
}

int Unk0200a5cc::func_18() {
    Unk02099c78Var *var;
    Unk02061d08Item *item;
    Unk020956f8 *script;
    Unk02061d08Item *sim;
    u16 *vars;
    int i;
    sim = func_02002438(this);
    if (fade && sim->visible != 0) {
        if (!fading) {
            func_020a1494(func_020a18e4(), 0, 0x10);
            func_020a11f8(func_020a18e4(), 0, 1);
            fading = true;
            return 0;
        }
        if (!func_020a1280(func_020a18e4(), 0, 1)) {
            return 0;
        }
    }
    Unk020680d4Cell cell = sim->func_14();
    item = 0;
    if (x >= 0) {
        cell.xy.x = x;
    }
    if (y >= 0) {
        cell.xy.y = y;
    }
    if (id != 0) {
        item = new Unk02061d08Item(func_0205f6f8(data_020c3fc4, id), cell, dir);
    }
    if (sim->visible != 0) {
        func_0205e4d0(sim);
        if (item != 0) {
            func_0205e3f0(item);
        }
    }
    if (item != 0 && copy) {
        var = sim->def->script->func_0209585c();
        script = item->def->script;
        vars = item->vars;
        for (i = 0; i < 4; i++, var++) {
            int value = func_0205ecc0(sim, var->unk0);
            int index = script->func_020958bc(var->unk0);
            if (index >= 0) {
                vars[index] = value;
            }
        }
    }
    if (fading) {
        func_020a11f8(func_020a18e4(), 2, 0);
        fading = false;
    }
    func_0205fda0(data_020c3fd4, sim);
    return 1;
}

void Unk0200a5cc::func_1c() {
    Unk02061d08Item *sim = func_02002438(this);
    s8 map = data_020c3ba4.map;
    if (map != 0) {
        Unk020680d4Cell cell = sim->func_14();
        if (map == cell.pos.unk3) {
            func_020581f4(func_02058788(&data_020c3ba4, data_020c3ba4.map), 6);
            func_020585a0(&data_020c3ba4, map);
        }
    }
}
