/*
 * Unit 0x02009848-0x02009D08: the action "Sleep": the sim lies down, the screen fades,
 * time passes and the needs are restored. Bounds: hypothesis (from the constructor
 * to the last vtable slot; `.data` is the name and the vtable, `.bss` the guard and
 * the local description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_anim.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
};

/* The sim of the player. */
class Unk020098a0Sim {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18(Unk020680d4Dir dir);

    u8 unk4[0x15c];
    void *anims;
};

struct Unk020098a0Player {
    u8 unk0[0xc];
    Unk020098a0Sim *sim;
};

struct Unk020098a0Panel {
    int unk0;
    u32 flags;
};

class Unk0206bcf0 {
public:
    void func_0206e104(int v);
    void func_0206f340();
    void func_0206f560(bool on);

    u8 unk0[0x11c];
    Unk020098a0Panel *panel;
    u8 unk120[0x104];
    int unk224;
    u8 unk228[4];
    u32 flags;
};

/* What is shown of an action. */
struct Unk020098a0Desc {
    Unk020098a0Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk020098a0Desc *func_20() = 0;

    u8 unk4[0x1c];
};

/* The base with a key (vtable 0x020B75A4). */
class Unk020071d4 : public Unk02002408 {
public:
    Unk020071d4() {
        unk20 = -1;
        unk24 = false;
    }
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

    int unk20;
    bool unk24;
};

class Unk020098a0 : public Unk020071d4 {
public:
    Unk020098a0();
    ~Unk020098a0();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_18();
    virtual const Unk020098a0Desc *func_20();
    Unk02099c78Block *func_02009cd0(int key);
    virtual void func_2c();

    int hours;
    int duration;
    int gain;
    int startKey;
    int endKey;
    int script0;
    int script1;
    int state;
    Unk020897c0 *anim;
    u8 unk4c[4];
    Unk02061d08Item *bed;
    bool ready;
};

extern "C" {
void func_020098d0(Unk020098a0 *o, Unk02061d08Item *bed, int hours, int gain, int rate, int start, int end);
void func_02009978(Unk020098a0 *o, int script);
void func_02009980(Unk020098a0 *o, int script);
Unk0206bcf0 *func_0206bce0();
int func_020a18e4();
void func_020a1494(int system, int a, int b);
void func_020a11f8(int system, int a, int b);
int func_020a1280(int system, int a, int b);
int func_0206647c(Unk020098a0Player *p, int i);
void func_020662c8(Unk020098a0Player *p, int i, int n);
bool func_0206757c(Unk020098a0Player *p, int a);
void func_02067178(Unk020098a0Player *p, u32 key);
void func_0205ff28(void *m, u32 key);
int func_02077c60(int a, int b);
void func_0200264c(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, void *p);
void func_0205ece8(Unk02061d08Item *item, int key);
Unk020897c0 *func_02063d84(void *anims);
void func_02068688(Unk020098a0Sim *sim, int a);
bool func_020691c4(Unk020098a0Sim *sim);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
extern Unk020098a0Player data_020c43a8;
extern u8 data_020c3fd4[];
}

Unk020098a0::Unk020098a0() {
    script0 = 0;
    script1 = 0;
    state = 0;
    anim = 0;
    ready = false;
}

Unk020098a0::~Unk020098a0() {
}

void func_020098d0(Unk020098a0 *o, Unk02061d08Item *bed, int hours, int gain, int rate, int start, int end) {
    int left = hours - func_0206647c(&data_020c43a8, 1) / 100000;
    o->hours = left;
    if (left < 0) {
        left = 0;
    }
    o->hours = left;
    o->duration = left * rate;
    int q = func_02077c60(gain << 12, 0x64000);
    o->gain = (int)(((s64)(o->hours << 12) * q + 0x800) >> 12) >> 12;
    o->startKey = start;
    o->endKey = end;
    o->bed = bed;
    o->ready = true;
}

void func_02009978(Unk020098a0 *o, int script) {
    o->script0 = script;
}

void func_02009980(Unk020098a0 *o, int script) {
    o->script1 = script;
}

bool Unk020098a0::func_08() {
    return true;
}

int Unk020098a0::func_0c() {
    return 0;
}

int Unk020098a0::func_18() {
    Unk0206bcf0 *game = func_0206bce0();
    Unk020098a0Player *player = &data_020c43a8;
    int system = func_020a18e4();
    if (state == 0) {
        func_0200264c(this);
        game->func_0206f560(true);
        Unk020098a0Sim *sim = player->sim;
        sim->func_18(bed->func_1c());
        Unk02099c78Block *block = func_02009cd0(startKey);
        anim = func_02063d84(player->sim->anims);
        func_0205e038(bed, block, player);
        func_02068688(player->sim, 0);
        state = 1;
        return 0;
    }
    if (state == 1) {
        Unk020897c0 *o = func_02063d84(player->sim->anims);
        if (anim == o) {
            return 0;
        }
        int frame = o->func_02089998() >> 12;
        if (o != 0 && frame <= o->func_01ff8a68() - 0x1c) {
            return 0;
        }
        func_020a1494(system, 2, 0x20);
        func_020a11f8(system, 2, 1);
        state = 2;
        return 0;
    }
    if (state == 2) {
        if (!func_020a1280(system, 0, 1) || !func_020a1280(system, 1, 1)) {
            return 0;
        }
        game->panel->flags |= 8;
        game->func_0206e104(duration);
        game->flags |= 0x2000;
        if (!func_0206757c(player, 0x20)) {
            func_02067178(player, 0xa1f6559e);
            func_0205ff28(data_020c3fd4, 0xa3287002);
        }
        state = 3;
        return 0;
    }
    if (state == 3) {
        if (game->unk224 > 0) {
            return 0;
        }
        func_020662c8(player, 1, hours);
        func_020662c8(player, 2, gain);
        game->func_0206f340();
        int script = script0;
        if (script != 0) {
            func_0205ece8(func_02002438(this), script);
        }
        game->flags &= ~0x2000;
        func_0205e038(bed, func_02009cd0(endKey), player);
        state = 4;
        return 0;
    }
    if (state == 4) {
        state = 5;
        return 0;
    }
    if (state == 5) {
        if (!func_020691c4(player->sim)) {
            return 0;
        }
    }
    func_02068688(player->sim, 1);
    int script = script1;
    if (script != 0) {
        func_0205ece8(func_02002438(this), script);
    }
    game->func_0206f560(false);
    return 1;
}

const Unk020098a0Desc *Unk020098a0::func_20() {
    static Unk020098a0Desc desc(0xd, 0, 0x15, "Sleep");
    return &desc;
}

Unk02099c78Block *Unk020098a0::func_02009cd0(int key) {
    Unk0205cf00 *def = bed->def;
    int index = def->script->func_0209599c(key);
    if (index == -1) {
        return 0;
    }
    return func_0205cea4(def, index);
}

void Unk020098a0::func_2c() {
}
