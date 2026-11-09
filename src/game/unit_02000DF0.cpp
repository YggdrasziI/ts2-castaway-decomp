/*
 * Unit 0x02000DF0-0x0200125C: the action "AdvanceTime": the screen fades out, time passes
 * and the screen fades back in, with scripts of the object before and after. Bounds:
 * hypothesis (from the constructor to the kept copies of the inline func_24 and func_28 of
 * `Unk020071d4`; `.data` is the name and the vtable, `.bss` the guard and the local
 * description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_action.h"

class Unk020071d4 : public Unk02002408 {
public:
    Unk020071d4() : key(-1), active(false) {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual int func_24() {
        return 0;
    }
    virtual int func_28() {
        return 1;
    }
    virtual void func_2c() = 0;

    int key;
    bool active;
};

/* The action "AdvanceTime". */
class Unk02000df0 : public Unk020071d4 {
public:
    Unk02000df0();
    virtual ~Unk02000df0();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02000ba0Desc *func_20();
    virtual void func_2c();

    Unk02063d84 *anim;
    int hours;
    int enter;
    int leave;
    int before;
    int after;
    int state;
    int unk44;
    Unk02061d08Item *item;
    bool set;
};

/* The player, as a global object. */
struct Unk02000df0Player {
    u8 unk0[0xc];
    Unk020680d4 *sim;
};

extern "C" {
void *func_02063d84(void *anim);
extern Unk02000df0Player data_020c43a8;
}

Unk02000df0::Unk02000df0() {
    anim = 0;
    state = 0;
    set = false;
}

Unk02000df0::~Unk02000df0() {
}

extern "C" void func_02000e70(Unk02000df0 *o, Unk02061d08Item *item, int hours, int before, int after,
                              int enter, int leave) {
    o->hours = hours;
    o->enter = enter;
    o->leave = leave;
    o->before = before;
    o->after = after;
    o->item = item;
    o->set = true;
}

bool Unk02000df0::func_08() {
    return true;
}

int Unk02000df0::func_0c() {
    return state == 6;
}

int Unk02000df0::func_10() {
    return 1;
}

int Unk02000df0::func_14() {
    return func_0200292c(owner) != 0;
}

void Unk02000df0::func_1c() {
}

/* The animation is read from the global, not through `player` (one more `mov r0, r4`). */
int Unk02000df0::func_18() {
    Unk0206bcf0 *game;
    Unk020680d4 *sim;
    Unk02000df0Player *player;
    game = func_0206bce0();
    if (state == 0) {
        func_0200264c(this);
        func_0206bce0()->func_0206f560(true);
        player = &data_020c43a8;
        sim = player->sim;
        sim->func_18(item->func_1c());
        if (enter != 0) {
            anim = (Unk02063d84 *)func_02063d84(data_020c43a8.sim->anim);
            func_0205e184(item, enter, player);
        }
        state = 1;
        return 0;
    }
    if (state == 1) {
        if (enter != 0 && !func_020691c4(data_020c43a8.sim)) {
            return 0;
        }
        int system = func_020a18e4();
        func_020a1494(system, 2, 0x20);
        func_020a11f8(system, 2, 1);
        state = 2;
        return 0;
    }
    if (state == 2) {
        int system = func_020a18e4();
        if (!func_020a1280(system, 0, 1) || !func_020a1280(system, 1, 1)) {
            return 0;
        }
        func_0206bce0()->func_0206e104(hours);
        func_0206bce0()->screen->flags |= 8;
        state = 3;
        return 0;
    }
    if (state == 3) {
        int system = func_020a18e4();
        if (game->unk224 > 0 || !(func_0206bce0()->screen->flags & 0x80)) {
            return 0;
        }
        if (before != 0) {
            func_0205ece8(func_02002438(this), before);
        }
        if (leave != 0) {
            func_0205e184(item, leave, &data_020c43a8);
        }
        func_020a1494(system, 2, 0x20);
        func_020a11f8(system, 2, 0);
        func_0206bce0()->screen->flags &= ~8;
        state = 4;
        return 0;
    }
    if (state == 4) {
        int system = func_020a18e4();
        if (!func_020a1280(system, 0, 0) || !func_020a1280(system, 1, 0)) {
            return 0;
        }
        state = 5;
        return 0;
    }
    if (state == 5 && leave != 0 && !func_020691c4(data_020c43a8.sim)) {
        return 0;
    }
    if (after != 0) {
        func_0205ece8(func_02002438(this), after);
    }
    func_0206bce0()->func_0206f560(false);
    state = 6;
    return 1;
}

const Unk02000ba0Desc *Unk02000df0::func_20() {
    static Unk02000ba0Desc desc(0xd, 0, 0x1d, "AdvanceTime");
    return &desc;
}

void Unk02000df0::func_2c() {
}
