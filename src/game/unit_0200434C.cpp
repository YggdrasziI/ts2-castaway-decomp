/*
 * Unit 0x0200434C-0x020046B4: the action "Give Gift", derived from `Unk02009084`: the sim
 * gives an object to the target, whose reaction comes from the gift valuation file and
 * the parameters of the gift. Bounds: hypothesis (from the description of the action, to
 * the description of "Immediate"; `.data` is the strings and the vtable, `.bss` the guard
 * and the local description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_archive.h"
#include "game/unk_datatree.h"
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

struct Unk0205d6b8 {
    int values[6];
};

/* What is shown of an action. */
struct Unk02004398Desc {
    Unk02004398Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02004398Desc *func_20() = 0;

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
    Unk0205cf00 *gift;
};

class Unk02004398 : public Unk02009084 {
public:
    Unk02004398();
    virtual ~Unk02004398() {}
    virtual const Unk02004398Desc *func_20();
    virtual void func_2c();
    virtual int func_30() {
        return 0xc;
    }
    virtual void func_34();
    virtual void func_38();
    virtual void func_3c();

    int kind;
    int value;
};

extern "C" {
void *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_02054cf0(void *p, void *e, int a);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
bool func_0205d340(Unk0205cf00 *def, u32 key);
Unk0205d6b8 *func_0205d608(Unk0205d6b8 *p, Unk020956f8 *script);
void func_0205d6dc(Unk0205d6b8 *p);
int func_0205d6fc(Unk0205d6b8 *p, int i);
void func_0205e184(Unk02061d08Item *item, u32 key, void *actor);
void func_0205e1b8(Unk02061d08Item *item, void *actor);
void func_0206632c(void *actor, int kind, int value);
extern u8 data_020bfc9c[];
}

const Unk02004398Desc *Unk02004398::func_20() {
    static Unk02004398Desc desc(3, 0, 0x16, "Give Gift");
    return &desc;
}

Unk02004398::Unk02004398() {
    kind = 4;
}

void Unk02004398::func_34() {
}

void Unk02004398::func_38() {
    void *actor = func_02002414(owner);
    Unk02061d08Item *o = func_02002438(this);
    Unk0205cf00 *def = o->def;
    if (gift != 0 && kind < 4) {
        int best = 0;
        Unk02093648 archive("ROM_Euro/source/archives/gifting.nitro_archive");
        archive.func_02094df4();
        Unk02096348 *file =
            (Unk02096348 *)archive.func_02093c18((const u32 *)"build/data/gifts/valuation.nitro_xml");
        Unk0209674c root = file->func_02096980();
        int count = root.func_020967ec();
        for (int i = 0; i < count; i++) {
            Unk0209674c group = root.func_02096774(i);
            if (!group.func_02096864() && func_0205d340(gift, group.func_02096800())) {
                int n = group.func_020967ec();
                for (int j = 0; j < n; j++) {
                    Unk0209674c leaf = group.func_02096774(j);
                    if (leaf.func_02096864() && func_0205d340(def, leaf.func_02096800())) {
                        int v = leaf.func_020968a0();
                        if (v > best) {
                            best = v;
                        }
                    }
                }
            }
        }
        archive.func_02093d14((const u32 *)"build/data/gifts/valuation.nitro_xml");
        archive.func_02094f0c();
        value = 1;
        if (gift->script != 0) {
            Unk0205d6b8 params;
            func_0205d608(&params, gift->script);
            int sum = 0;
            for (int i = 0; i < 6; i++) {
                sum += func_0205d6fc(&params, i);
            }
            value = sum / 25;
            if (value == 0) {
                value = sum >= 0 ? 1 : -1;
            }
            func_0205d6dc(&params);
        }
        value *= best;
    }
    if (value <= 0) {
        func_0205e184(o, 0xd47fbaa5, actor);
    } else {
        func_0205e184(o, 0xc8d43a97, actor);
    }
}

void Unk02004398::func_3c() {
    void *inventory = data_020bfc9c;
    void *e = func_02054dc4(inventory, gift, 0);
    if (e != 0) {
        func_02054cf0(inventory, e, 0);
    }
}

void Unk02004398::func_2c() {
    void *actor = func_02002414(owner);
    if (gift != 0 && kind < 4) {
        func_0206632c(actor, kind, value);
    }
    func_0205e1b8(func_02002438(this), actor);
}
