/*
 * Unit 0x02001FDC-0x02002144: the commands "AwardMineableObject" and "Echo" of the script
 * table, an empty function called by the startup code and the inline functions of the file
 * factory (D1 of `Unk02053204`, then D1 and D0 of its interface). Bounds: hypothesis (after
 * the inline destructors of the "ChangeLot" actions, to the next script commands; `.data`
 * is the path of the sound data and the vtable of the interface). `main` very likely comes
 * from this object (see unit_02000BA0.cpp). Layouts come from the code; all names are
 * placeholders.
 */
#include "game/unk_action.h"
#include "game/unk_vm.h"

/* The interface of the file factories. */
class Unk020bd2d4 {
public:
    virtual ~Unk020bd2d4() {}
    virtual int func_02095c74(int id) = 0;
    virtual Unk0209487c *func_02095cd0(void *data, int kind) = 0;
};

class Unk02053204 : public Unk020bd2d4 {
public:
    int func_02095c74(int id);
    Unk0209487c *func_02095cd0(void *data, int kind);
};

/* The parameters of a script step (unit_02099C0C.cpp). */
class Unk02099c0c {
public:
    int func_02099c58(int key);

    void *owner;
    u16 next;
};

void func_020947a4(Unk020bd2d4 *factory);

extern "C" {
void func_02054b80(void *p, Unk0205cf00 *def, int a);
void func_02054c1c(void *p, Unk0205cf00 *def, int a);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
int func_020591e4(void *lots, int lot);
int func_0205b0d0(int a, int b);
u32 func_020a1f84(void *random);
extern u8 data_020bfc9c[];
extern u8 data_020d62a4[];
}

const char *data_020b7074 = "re/build/data/sound/sound_data.sdat";

static inline bool func_in_inventory(void *inventory, Unk0205cf00 *def) {
    return func_02054dc4(inventory, def, 0) != 0;
}

extern "C" u16 func_02001fdc(Unk02099c0c *node) {
    int chance;
    int lot = node->func_02099c58(0x1eb09665);
    chance = node->func_02099c58(0x13809715);
    if (lot == 0) {
        return node->next;
    }
    chance = chance ? chance : 100;
    lot = func_020591e4(func_0206bce0()->lots, lot);
    if (lot != 0) {
        if (func_020a1f84(data_020d62a4) % 0x64000 <= (u32)chance << 12) {
            Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, lot);
            void *inventory = data_020bfc9c;
            if (func_in_inventory(inventory, def)) {
                func_02054c1c(inventory, def, 0);
            } else {
                func_02054b80(inventory, def, 0);
            }
        } else {
            lot = 0;
        }
    }
    return func_0205b0d0(lot, 0);
}

extern "C" u16 func_020020dc(Unk02099c0c *node) {
    int key = node->func_02099c58(0x971e15d6);
    node->func_02099c58(0x11b44);
    if (key == 0) {
        return node->next;
    }
    ((Unk02099c78 *)node->owner)->func_0209a0f4(key);
    return node->next;
}

extern "C" void func_02002124() {
}

/*
 * Stands for `main`, which uses the factory in the same way: it makes this object emit the
 * inline functions of the factory, and the linker drops it.
 */
extern "C" void func_keep() {
    Unk02053204 factory;
    func_020947a4(&factory);
    while (true) {
    }
}
