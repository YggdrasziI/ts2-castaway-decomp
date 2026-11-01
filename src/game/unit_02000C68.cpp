/*
 * Unit 0x02000C68-0x02000DF0: the action "ActionAddInspiration": it adds an object to the
 * inspirations and can show its screen. Bounds: hypothesis (from the description of the
 * action to its inline functions; `.data` is the name and the vtable, `.bss` the guard and
 * the local description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_action.h"

/* The action "ActionAddInspiration". */
class Unk02000cb0 : public Unk02002408 {
public:
    Unk02000cb0();
    virtual bool func_08() {
        return true;
    }
    virtual int func_0c() {
        return 1;
    }
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c() {}
    virtual const Unk02000ba0Desc *func_20();

    int id;
    int notify;
    int always;
};

extern "C" {
int func_0205465c(void *p, Unk0205cf00 *def, bool a);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
extern u8 data_020bfc68[];
}

/* An enum keeps the `movne` / `moveq` order of the original. */
enum Unk02000ba0Bool { UNK_02000BA0_FALSE, UNK_02000BA0_TRUE };

static inline Unk02000ba0Bool func_idle(void *guide) {
    return guide != 0 ? UNK_02000BA0_FALSE : UNK_02000BA0_TRUE;
}

const Unk02000ba0Desc *Unk02000cb0::func_20() {
    static Unk02000ba0Desc desc(0, 0, 0x1e, "ActionAddInspiration");
    return &desc;
}

Unk02000cb0::Unk02000cb0() {
    id = 0;
    notify = 0;
    always = 0;
}

extern "C" void func_02000ce0(Unk02000cb0 *o, int id, int notify, int always) {
    o->id = id;
    o->notify = notify;
    o->always = always;
}

int Unk02000cb0::func_14() {
    return func_idle(func_0206bce0()->guide);
}

int Unk02000cb0::func_18() {
    Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, id);
    if (func_0205465c(data_020bfc68, def, notify != 1) || always) {
        def = func_0205f6f8(data_020c3fc4, func_0205d1b4(def, 0x798b86ac));
        if (notify) {
            func_0206bce0()->func_0206f3e8(def, 1, 1, 1);
        }
    }
    return 1;
}

int Unk02000cb0::func_10() {
    return 1;
}
