/*
 * Unit 0x020066B4-0x02006CAC: the action "Play Microgame": after a delay it starts a
 * microgame through the script interface, waits for its end and applies its result.
 * Bounds: hypothesis (from the description of the action to its inline destructors;
 * `.data` is the name and the vtable, `.bss` the guard and the local description).
 * Layouts come from the code; all names are placeholders.
 */
#include "game/unk_sim.h"

/* A map cell compared by value. */
struct Unk02006700Cell {
    Unk02006700Cell() {
        xy.x = -1;
        xy.y = -1;
    }

    bool operator!=(Unk02006700Cell o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

struct Unk02006700Sim {
    u8 unk0[0x160];
    void *unk160;
};

/* The player. */
class Unk02006700Player {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk02006700Cell func_14();

    u8 unk4[8];
    Unk02006700Sim *sim;
};

/* What is shown of an action. */
struct Unk02006700Desc {
    Unk02006700Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02006700Desc *func_20() = 0;

    u8 unk4[0x14];
    void *owner;
    u8 unk1c[4];
};

/* The action of kind 11 that this one starts first. */
struct Unk02006700Next {
    u8 unk0[0x18];
    void *owner;
    u8 unk1c[4];
    int block;
    u8 unk24;
    bool free;
};

class Unk02006700 : public Unk02002408 {
public:
    Unk02006700();
    virtual ~Unk02006700() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02006700Desc *func_20();
    bool func_has(int m) const {
        return flags & m;
    }

    int unk20;
    int key;
    int param;
    s16 time;
    s16 id;
    u16 flags;
    s16 counter;
    u8 *unk34;
    int unk38;
    int unk3c;
    int unk40;
    Unk02006700Cell cell;
    int result;
};

struct Unk02006700Arg {
    u32 key;
    int value;
};

class Unk0206bcf0 {
public:
    void func_0206e104(int n);
    void func_0206f560(bool a);
    void func_0206f578(bool a);

    u8 unk0[0x144];
    int unk144;
    u8 unk148[0xdc];
    int unk224;
};

struct Unk02006700Timer {
    u8 unk0[8];
    u32 frames;
};

extern "C" {
void func_0200245c(Unk02002408 *a, void *b);
void func_0200264c(Unk02002408 *a);
bool func_0200292c(void *a);
int func_02002abc(Unk02002408 *a, Unk02006700Cell cell, u8 b);
void func_02006754(Unk02006700 *o, s16 a, s16 b, int c, int d);
void func_02006c6c(Unk02006700 *o);
void *func_02002438(Unk02002408 *a);
Unk02006700Next *func_02007c98(void *pool, int a, int b);
void func_02007ea4(void *list, void *o);
void func_0205e1b8(void *item, void *actor);
void func_020667f8(Unk02006700Player *p, int a);
bool func_020691c4(void *sim);
Unk0206bcf0 *func_0206bce0();
void *func_020a18e4();
void func_020a11f8(void *a, int b, int c);
int func_020a5b58(int key, Unk02006700Arg *args, int n);
int func_020a5bec();
int func_020a5c38();
extern u8 data_020be184[];
extern u8 data_020c4770[];
extern Unk02006700Player data_020c43a8;
extern Unk02006700Timer data_020d60c8;
}

static inline Unk02006700Player *func_player() {
    return &data_020c43a8;
}

const Unk02006700Desc *Unk02006700::func_20() {
    static Unk02006700Desc desc(0xb, 0, 6, "Play Microgame");
    return &desc;
}

Unk02006700::Unk02006700()
    : unk20(0), flags(0), counter(0), unk34(0), unk38(0), unk3c(0), unk40(0) {}

void func_02006754(Unk02006700 *o, s16 a, s16 b, int c, int d) {
    o->id = a;
    o->time = b;
    o->key = c;
    o->param = d;
}

bool Unk02006700::func_08() {
    return true;
}

int Unk02006700::func_0c() {
    return 0;
}

int Unk02006700::func_10() {
    if (flags & 4) {
        return 0;
    }
    if (func_has(1)) {
        func_0205e1b8(func_02002438(this), 0);
    }
    return 1;
}

int Unk02006700::func_14() {
    if (owner != 0 && !func_0200292c(owner)) {
        return 0;
    }
    if (flags & 0x40) {
        func_0200264c(this);
        Unk02006700Next *next = func_02007c98(data_020be184, 0xb, 2);
        if (next == 0) {
            return 2;
        }
        next->block = id;
        next->free = false;
        func_02007ea4(data_020c4770, next->owner);
        func_0200245c(this, next);
        flags &= ~0x40;
        return 0;
    }
    if (flags & 0x10) {
        if (func_player()->func_14() != cell) {
            func_02002abc(this, cell, 1);
        }
        flags &= ~0x10;
        flags |= 0x20;
        return 0;
    }
    if (flags & 0x20) {
        if (func_player()->func_14() != cell) {
            return 2;
        }
    }
    flags |= 1;
    func_0200264c(this);
    return 1;
}

int Unk02006700::func_18() {
    if (func_0206bce0()->unk144 != 0) {
        return 0;
    }
    if (data_020d60c8.frames & 1) {
        counter++;
    }
    if (!(flags & 4)) {
        if (counter >= time) {
            Unk02006700Arg args[5];
            args[0].key = 0xe6884a5d;
            args[0].value = param;
            args[1].key = 0x35c7a149;
            args[1].value = unk34 != 0 ? *(int *)(unk34 + 0x2c) : 0;
            args[2].key = 0xf89be826;
            args[2].value = unk38;
            args[3].key = 0xbf6ec11d;
            args[3].value = unk3c;
            args[4].key = 0x6e48cc6d;
            args[4].value = unk40;
            if (func_020a5b58(key, args, 5) == 1) {
                func_0206bce0()->func_0206f560(true);
                func_0206bce0()->func_0206f578(true);
                flags |= 4;
            }
        }
    } else if (!func_has(2)) {
        if (func_020a5bec() == 0) {
            flags |= 2;
        }
    }
    if (flags & 2) {
        if (!(flags & 0x80)) {
            result = func_020a5c38();
            func_0206bce0()->func_0206f560(false);
            func_0206bce0()->func_0206f578(false);
            flags |= 0x80;
        } else if (!(flags & 0x100)) {
            Unk02006700Sim *sim = data_020c43a8.sim;
            if (sim->unk160 == 0 || func_020691c4(sim)) {
                int n = result;
                if (n > 0) {
                    func_0206bce0()->func_0206e104(n);
                    flags |= 0x100;
                } else {
                    return 1;
                }
            }
        } else if (func_0206bce0()->unk224 <= 0) {
            func_020a11f8(func_020a18e4(), 2, 0);
            return 1;
        }
    }
    return 0;
}

void Unk02006700::func_1c() {
    if (!(flags & 0x200)) {
        func_020667f8(&data_020c43a8, 0xa);
    }
}

void func_02006c6c(Unk02006700 *o) {
    o->flags |= 0x200;
}
