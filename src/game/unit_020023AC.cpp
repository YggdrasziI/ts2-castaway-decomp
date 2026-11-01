/*
 * Unit 0x020023AC-0x02002B80: the action base `Unk02002408`: an action of a list runs in
 * phases (enter, run, finish, or leave), may depend on the action it was linked to and can
 * queue a move action. Bounds: hypothesis (from its class operators, to the description of
 * the "Move" action with callbacks; `.data` is its vtable, all pure slots). Most functions
 * keep C linkage, as many files declare them that way. Layouts come from the code; all
 * names are placeholders.
 */
#include "game/unk_sim.h"

typedef unsigned long Unk02002408Size;

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    void *visible;
};

struct Unk02002408Cell {
    Unk02002408Cell() {
    }
    Unk02002408Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A cell that adds an offset to itself. */
struct Unk02002408Pos {
    Unk02002408Cell func_add(Unk020680d4Xy d) const {
        return Unk02002408Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* The sim that runs the action. */
struct Unk02002408Actor {
    u8 unk0[0xc];
    void *sim;
    u8 unk10[0x3b8];
    u8 list[4];
};

class Unk02002408;

/* The actions of an object or of the player. */
struct Unk02002408List {
    void *obj;
    u32 flags;
    u8 unk8[4];
    Unk02002408 *first;
};

class Unk02002408 {
public:
    Unk02002408();
    virtual ~Unk02002408();
    void *operator new(Unk02002408Size size, void *p);
    void operator delete(void *p);
    virtual int func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const void *func_20() = 0;

    u32 flags;
    u8 unk8[8];
    Unk02002408List *list;
    Unk02002408 *next;
    Unk02002408 *owner;
    Unk02002408 *link;
};

/* A queued move action. */
struct Unk02002408Next {
    void func_set(Unk02002408Cell c, u8 b) {
        cell = c;
        unk43 = b;
    }

    u8 unk0[4];
    u32 flags;
    u8 unk8[0x2c];
    Unk02002408Cell cell;
    u8 unk3c[7];
    u8 unk43;
};

extern "C" {
Unk02002408Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200245c(Unk02002408 *a, void *next);
int func_02002490(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
void func_02002670(Unk02002408 *a);
void func_02002694(Unk02002408 *a);
void func_020026d0(Unk02002408 *a);
Unk02002408List *func_02002734(Unk02002408 *a);
bool func_0200273c(Unk02002408 *a);
bool func_02002760(Unk02002408 *a);
void func_02002784(Unk02002408 *a);
void func_020027bc(Unk02002408 *a);
bool func_020027e0(Unk02002408 *a);
bool func_0200283c(Unk02002408 *a);
bool func_02002880(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
int func_02002abc(Unk02002408 *a, Unk02002408Cell cell, u8 b);
Unk02002408Next *func_02007340(void *pool, int kind);
void func_02007edc(Unk02002408List *list, void *next, Unk02002408 *a);
void func_02007eec(void *list, Unk02002408Next *next, Unk02002408 *a, Unk02002408 *b);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
extern u8 data_020be184[];
}

static inline Unk02002408Cell func_front(Unk02061d08Item *o) {
    return ((const Unk02002408Pos &)o->func_14())
        .func_add(func_020619a8(o, Unk020680d4Xy(o->def->w, o->def->h), o->func_1c()));
}

/* An enum keeps the test materialised, as in the original. */
enum Unk02002408Bool { UNK_02002408_FALSE, UNK_02002408_TRUE };

static inline Unk02002408Bool func_notified(u32 flags) {
    return flags & 0x20 ? UNK_02002408_TRUE : UNK_02002408_FALSE;
}

void *Unk02002408::operator new(Unk02002408Size size, void *p) {
    return p;
}

void Unk02002408::operator delete(void *p) {
}

Unk02002408::Unk02002408() {
    flags = 0;
    list = 0;
    next = 0;
    owner = 0;
    link = 0;
}

Unk02002408::~Unk02002408() {
    list = 0;
}

Unk02002408Actor *func_02002414(Unk02002408 *a) {
    Unk02002408List *l = a->list;
    if (l == 0) {
        return 0;
    }
    return l->flags & 2 ? (Unk02002408Actor *)l->obj : 0;
}

Unk02061d08Item *func_02002438(Unk02002408 *a) {
    Unk02002408List *l = a->list;
    if (l == 0) {
        return 0;
    }
    return l->flags & 1 ? (Unk02061d08Item *)l->obj : 0;
}

void func_0200245c(Unk02002408 *a, void *next) {
    a->flags |= 0x80;
    Unk02002408List *l = func_02002734(a);
    if (l != 0) {
        func_02007edc(l, next, a);
    }
}

int func_02002490(Unk02002408 *a) {
    if (a->flags & 2) {
        /* Hypothesis: a volatile read; the original loads the flags again here. */
        u32 f = *(volatile u32 *)&a->flags;
        if (f & 4 && !func_notified(f) && a->owner != 0) {
            return 0;
        }
        switch (a->func_10()) {
        case 0:
            return 0;
        case 1:
            func_020027bc(a);
            return 2;
        default:
            return 0;
        }
    }
    if (!(a->flags & 1)) {
        if (!func_02002880(a)) {
            func_020026d0(a);
            return 0;
        }
        switch (a->func_14()) {
        case 0:
            return 0;
        case 1:
            a->flags |= 1;
            if (!func_0200292c(a)) {
                return 0;
            }
            break;
        case 2:
            func_020026d0(a);
            return 0;
        default:
            return 0;
        }
    }
    if (!(a->flags & 0x200)) {
        if (!func_02002880(a)) {
            func_020026d0(a);
            return 0;
        }
        switch (a->func_18()) {
        case 0:
            return 0;
        case 1:
            a->flags |= 0x200;
            return 0;
        case 2:
            func_020026d0(a);
            return 0;
        default:
            return 0;
        }
    }
    a->func_1c();
    func_020027bc(a);
    return 1;
}

void func_0200264c(Unk02002408 *a) {
    a->flags |= 0x40;
    if (a->owner != 0) {
        a->owner->flags |= 0x40;
    }
}

void func_02002670(Unk02002408 *a) {
    a->flags &= ~0x40;
    if (a->owner != 0) {
        a->owner->flags &= ~0x40;
    }
}

void func_02002694(Unk02002408 *a) {
    a->flags = (a->flags | 2) & ~0x404;
    if (a->owner != 0 && !(a->owner->flags & 2)) {
        func_020026d0(a->owner);
    }
}

void func_020026d0(Unk02002408 *a) {
    if (a->link != 0) {
        func_020026d0(a->link);
    }
    if (a->flags & 0x80) {
        for (Unk02002408 *p = func_02002734(a)->first; p != 0; p = p->next) {
            if (a == p->link) {
                func_02002694(p);
            }
        }
    }
    func_02002694(a);
}

Unk02002408List *func_02002734(Unk02002408 *a) {
    return a->list;
}

bool func_0200273c(Unk02002408 *a) {
    Unk02002408List *l = a->list;
    if (l == 0) {
        return false;
    }
    return (l->flags & 1) != 0;
}

bool func_02002760(Unk02002408 *a) {
    Unk02002408List *l = a->list;
    if (l == 0) {
        return false;
    }
    return (l->flags & 2) != 0;
}

void func_02002784(Unk02002408 *a) {
    if (a->flags & 2) {
        return;
    }
    if (a->link == 0) {
        if (!(a->flags & 0x40)) {
            func_020026d0(a);
        }
    } else {
        func_02002784(a->link);
    }
}

void func_020027bc(Unk02002408 *a) {
    if (a->owner != 0 && a->flags & 0x400) {
        a->owner->flags |= 0x20;
    }
}

bool func_020027e0(Unk02002408 *a) {
    if (func_0200273c(a)) {
        if (func_02002438(a)->visible == 0) {
            return false;
        }
    } else if (func_02002760(a)) {
        if (func_02002414(a)->sim == 0) {
            return false;
        }
    }
    return true;
}

bool func_0200283c(Unk02002408 *a) {
    if (func_0200273c(a)) {
        if (func_02002438(a) != 0) {
            return true;
        }
    } else if (func_02002414(a) != 0) {
        return true;
    }
    return false;
}

bool func_02002880(Unk02002408 *a) {
    if (!func_0200283c(a)) {
        return false;
    }
    if (a->flags & 0x400) {
        Unk02002408 *o = a->owner;
        if (o == 0) {
            return false;
        }
        if (!func_020027e0(o)) {
            return false;
        }
        if (!(o->flags & 4)) {
            return false;
        }
    } else if (a->flags & 4) {
        Unk02002408 *o = a->owner;
        if (o == 0) {
            return false;
        }
        func_020027e0(o);
        if (!(o->flags & 0x400)) {
            return false;
        }
    }
    return a->func_08() != 0;
}

bool func_0200292c(Unk02002408 *a) {
    return a == func_02002734(a)->first;
}

int func_0200294c(Unk02002408 *a, u8 b) {
    Unk02002408Next *next = func_02007340(data_020be184, 0);
    if (next == 0) {
        return 2;
    }
    next->func_set(func_front(func_02002438(a)), b);
    a->owner->flags |= 0x80;
    Unk02002408 *o = a->owner;
    func_02007eec(func_02002734(o), next, o, o);
    next->flags |= 0x10;
    return 0;
}

int func_02002abc(Unk02002408 *a, Unk02002408Cell cell, u8 b) {
    Unk02002408Next *next = func_02007340(data_020be184, 0);
    if (next == 0) {
        return 2;
    }
    next->func_set(cell, b);
    a->flags |= 0x80;
    func_02007eec(func_02002414(a)->list, next, a, a);
    next->flags |= 0x10;
    return 0;
}
