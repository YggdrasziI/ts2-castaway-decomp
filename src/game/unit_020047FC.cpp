/*
 * Unit 0x020047FC-0x02004938: the action "Action Interact": an interaction that runs a
 * script of the object, before or after the walk depending on a flag. Bounds: hypothesis
 * (from the description of the action, to the function before the "Motive Failure"
 * action; `.data` is the name and the vtable, `.bss` the guard and the local description).
 * Layouts come from the code; all names are placeholders. It holds the kept copy of the
 * base's inline func_28 (0x02004930).
 */
#include "game/unk_objscript.h"
#include "game/unk_script.h"

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02061d08Item {
public:
    u8 unk0[0x28];
    Unk0205cf00 *def;
};

/* What is shown of an action. */
struct Unk0200491cDesc {
    Unk0200491cDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk0200491cDesc *func_20() = 0;

    u8 unk4[0x1c];
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
    virtual int func_28() {
        return 1;
    }
    virtual void func_2c() = 0;

    int block;
    u8 unk24[0xc];
};

class Unk0200491c : public Unk02008d18 {
public:
    virtual const Unk0200491cDesc *func_20();
    virtual void func_24();
    virtual void func_2c();
    void func_0200488c();

    bool first;
    u32 key;
};

extern "C" {
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0205b074(void *c, int a, Unk02061d08Item *target, void *actor);
extern u8 data_020c3cc8[];
extern u8 data_020c43a8[];
}

const Unk0200491cDesc *Unk0200491c::func_20() {
    static Unk0200491cDesc desc(4, 0, 0xb, "Action Interact");
    return &desc;
}

extern "C" void func_02004848(Unk0200491c *o, int a, u32 key, bool first) {
    o->block = a;
    o->key = key;
    o->first = first;
}

void Unk0200491c::func_24() {
    if (first) {
        return;
    }
    func_0200488c();
}

void Unk0200491c::func_2c() {
    if (!first) {
        return;
    }
    func_0200488c();
}

void Unk0200491c::func_0200488c() {
    Unk02061d08Item *o = func_02002438(this);
    if (o->def->script->func_020957ec(key) == 0) {
        return;
    }
    func_0205b074(data_020c3cc8, block, o, data_020c43a8);
    Unk02061c04 runner(o);
    runner.func_02099ce0(key);
}
