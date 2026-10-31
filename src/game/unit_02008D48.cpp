/*
 * Unit 0x02008D48-0x020090B4: abstract action `Unk02009084`: the sim stands in front of
 * the object, then the derived class opens a screen through its slots 0x30-0x3C. Bounds:
 * hypothesis (from its constructor to its destructors; `.data` is the vtable, four more
 * pure slots). Base of the actions with vtables 0x020B724C, 0x020B7490, 0x020B74E4.
 * Layouts come from the code; all names are placeholders.
 *
 * Open gap: func_18 99.82 %: only the stack slots of the temporaries of case 0, as in
 * unit_020090B4.cpp (forms of the inline test tried, none moves them to the original
 * order). The casts to `Unk02009084Pos` and `Unk02009084Facing` are workarounds.
 */
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

class Unk02060d78;

class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *visible;
};

class Unk02009084Actor {
public:
    u8 unk0[0xc];
    Unk02061d08Item *sim;
};

/* What is shown of an action. */
struct Unk02009084Desc {
    Unk02009084Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

/* A cell built from its parts. */
struct Unk02009084Cell {
    Unk02009084Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    bool operator!=(const Unk020680d4Cell &o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A cell that adds an offset to itself. */
struct Unk02009084Pos {
    Unk02009084Cell func_add(Unk020680d4Xy d) const {
        return Unk02009084Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
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
    virtual const Unk02009084Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

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

class Unk0206bcf0 {
public:
    void func_0206f0ec(int a, int b, int c);

    u8 unk0[0x144];
    int unk144;
};

class Unk02009084 : public Unk020071d4 {
public:
    Unk02009084();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_18();
    virtual int func_30() = 0;
    virtual void func_34() = 0;
    virtual void func_38() = 0;
    virtual void func_3c() = 0;
    virtual ~Unk02009084();

    int state;
    int screen;
};

extern "C" {
Unk02009084Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
bool func_0206135c(Unk02060d78 *e);
bool func_020691c4(void *sim);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
Unk0206bcf0 *func_0206bce0();
int func_02028ebc();
}

struct Unk02009084Facing {
    bool func_same(Unk020680d4Dir b) const {
        return v == b.v;
    }

    int v;
};

static inline bool func_away(Unk02061d08Item *o, Unk020680d4Cell c) {
    Unk020680d4Xy size(o->def->w, o->def->h);
    Unk020680d4Xy rel = func_020619a8(o, size, o->func_1c());
    return ((const Unk02009084Pos &)o->func_14()).func_add(rel) != c;
}

Unk02009084::Unk02009084() {
    state = 0;
    screen = 0;
}

bool Unk02009084::func_08() {
    return true;
}

int Unk02009084::func_0c() {
    return 0;
}

int Unk02009084::func_18() {
    Unk02061d08Item *o = func_02002438(this);
    bool visible;
    bool done;
    Unk02061d08Item *sim;
    sim = func_02002414(owner)->sim;
    visible = func_0206135c(o->visible);
    done = func_020691c4(sim);
    switch (state) {
    case 0:
        if (func_away(o, sim->func_14()) || !((const Unk02009084Facing &)sim->func_1c()).func_same(o->func_1c())) {
            return 2;
        }
        if (done && visible) {
            Unk0206bcf0 *game = func_0206bce0();
            game->func_0206f0ec(func_30(), 0, (int)o);
            state = 2;
            func_34();
        }
        break;
    case 1:
        break;
    case 2:
        if (func_0206bce0()->unk144 == 0) {
            screen = func_02028ebc();
            if (screen == 0) {
                state = 4;
            } else {
                func_38();
                state = 3;
            }
        }
        break;
    case 3:
        if (done) {
            if (screen != 0) {
                func_3c();
            }
            state = 4;
        }
        break;
    case 4:
        return 1;
    }
    return 0;
}

Unk02009084::~Unk02009084() {
}
