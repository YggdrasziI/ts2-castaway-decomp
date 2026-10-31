/*
 * Unit 0x02007204-0x02007C98: the pool of 128 action slots of 0x80 bytes and the factory
 * that builds an action of a given kind in a slot. Bounds: hypothesis (from the pool
 * set-up, after the inline destructors of the file before it, up to the list of actions;
 * `.bss` is the pool object, 16 bytes just before the local statics of the next file; it
 * may be one file with the list of actions). Layouts come from the code; all names are
 * placeholders. Each action class is declared here with what its inline constructor
 * needs; `func_key` is never defined, so that the vtables are not emitted here.
 */
#include "game/unk_sim.h"

typedef unsigned long Unk02007204Size;

struct Unk02007204Node {
    u8 unk0[8];
    Unk02007204Node *prev;
    Unk02007204Node *next;
    u8 unk10[0x70];
};

struct Unk02007204Pool {
    int count;
    Unk02007204Node *nodes;
    Unk02007204Node *used;
    Unk02007204Node *free;
};

/* The random number generator of func_020a20f0, 624 words and an index. */
struct Unk02007204Random {
    Unk02007204Random() : index(625) {}

    u32 state[624];
    int index;
};

extern "C" {
void func_02099b90(u32 data, void *dest, u32 size);
void func_020a20f0(Unk02007204Random *r);
u32 func_020a1f84(Unk02007204Random *r);
void func_02007204(Unk02007204Pool *pool);
void func_0200726c(Unk02007204Pool *pool);
Unk02007204Node *func_02007294(Unk02007204Pool *pool);
void func_020072ec(Unk02007204Pool *pool, Unk02007204Node *n);
void *func_02007340(Unk02007204Pool *pool, int kind);
}

class Unk02002408 {
public:
    Unk02002408();
    virtual ~Unk02002408();
    void *operator new(Unk02007204Size size, void *p);

    u8 unk4[0x1c];
};

/* kinds 0 and 1: the move actions (names at 0x020B7360-0x020B738C, a hypothesis) and their base. */
class Unk02005ad4 : public Unk02002408 {
public:
    Unk02005ad4() {
        unk40 = false;
        unk41 = false;
        unk42 = false;
        unk43 = true;
    }
    virtual void func_key();

    u8 unk20[0xc];
    Unk020680d4Cell cell0;
    Unk020680d4Cell cell1;
    u8 unk3c[4];
    bool unk40;
    bool unk41;
    bool unk42;
    bool unk43;
};

class Unk02005aa4 : public Unk02005ad4 {
public:
    Unk02005aa4() {}
    virtual void func_key();
};

class Unk02005a74 : public Unk02005ad4 {
public:
    Unk02005a74() {
        unk44 = false;
    }
    virtual void func_key();

    bool unk44;
};

class Unk02009818 : public Unk02002408 {
public:
    Unk02009818() {}
    virtual void func_key();
};

class Unk02002bc8 : public Unk02002408 {
public:
    Unk02002bc8();
    virtual void func_key();

    u8 unk20[0x1c];
};

class Unk020047cc : public Unk02002408 {
public:
    Unk020047cc() {
        unk20 = -1;
        unk24 = false;
        unk25 = true;
    }
    virtual void func_key();

    int unk20;
    bool unk24;
    bool unk25;
};

class Unk02006700 : public Unk02002408 {
public:
    Unk02006700();
    virtual void func_key();

    u8 unk20[0x30];
};

class Unk0200a5cc : public Unk02002408 {
public:
    Unk0200a5cc() {
        unk20 = 0;
        unk26 = false;
        unk2c = 4;
    }
    virtual void func_key();

    int unk20;
    u8 unk24[2];
    bool unk26;
    u8 unk27[5];
    int unk2c;
};

class Unk02008d18 : public Unk02002408 {
public:
    Unk02008d18();
    virtual void func_key();

    u8 unk20[5];
    bool unk25;
    u8 unk26[0xa];
};

class Unk0200a2d8 : public Unk02008d18 {
public:
    Unk0200a2d8() {
        unk30 = 0;
        unk50 = 0;
        unk54 = 0;
        unk58 = 0;
        unk25 = false;
    }
    virtual void func_key();

    int unk30;
    u8 unk34[0x1c];
    int unk50;
    int unk54;
    int unk58;
};

/* The base with a key. */
class Unk020071d4 : public Unk02002408 {
public:
    Unk020071d4() {
        unk20 = -1;
        unk24 = false;
    }
    virtual void func_key();

    int unk20;
    bool unk24;
};

/* kind 9: "Action Pickup". */
class Unk02005e1c : public Unk020071d4 {
public:
    Unk02005e1c() {
        Unk02007204Random random;
        func_020a20f0(&random);
        u32 n = func_020a1f84(&random) % 3;
        if (n == 2) {
            unk28 = 0x27c4a91f;
            unk2c = 0x27c4a91f + 1;
        } else if (n == 1) {
            unk28 = 0x1a0e9efd;
            unk2c = 0x1a0e9efd + 1;
        } else {
            unk28 = 0x1a0ea2dd;
            unk2c = 0x1a0ea2dd + 1;
        }
        unk34 = 0;
        unk30 = 0;
        unk3c = 0;
        unk38 = 0;
        unk40 = 0;
    }
    virtual void func_key();

    u8 unk25[3];
    u32 unk28;
    u32 unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
};

class Unk02008240 : public Unk02008d18 {
public:
    Unk02008240() {
        unk30 = false;
    }
    virtual void func_key();

    bool unk30;
};

class Unk0200491c : public Unk02008d18 {
public:
    Unk0200491c() {
        unk30 = true;
        unk34 = 0x5f807ef0;
    }
    virtual void func_key();

    bool unk30;
    u32 unk34;
};

class Unk02003ab0 : public Unk02002408 {
public:
    Unk02003ab0();
    virtual void func_key();

    u8 unk20[0x18];
};

/* "cAction ShakeTree". */
class Unk020093ec : public Unk020071d4 {
public:
    Unk020093ec() {
        unk28 = 0;
    }
    virtual void func_key();

    int unk28;
};

class Unk0200ad40 : public Unk02002408 {
public:
    Unk0200ad40() : unk20(false) {
        unk2c = 4;
        unk3c = 0;
        unk48 = true;
        unk49 = true;
    }
    virtual void func_key();

    bool unk20;
    u8 unk21;
    Unk020680d4Cell cell;
    u8 unk2a[2];
    int unk2c;
    u8 unk30[0xc];
    int unk3c;
    u8 unk40[8];
    bool unk48;
    bool unk49;
};

/* "Sim Animation". */
class Unk02007c84 : public Unk02002408 {
public:
    Unk02007c84() {
        playing = false;
    }
    virtual void func_key();

    bool playing;
    int key;
    bool loop;
};

/* The changes of the needs after an animation. */
struct Unk02007204Amounts {
    Unk02007204Amounts() {
        for (u32 i = 0; i < 6; i++) {
            amounts[i] = 0;
        }
    }

    int amounts[6];
};

class Unk02009764 : public Unk02007c84, public Unk02007204Amounts {
public:
    Unk02009764() {
        Unk02007c84();
    }
    virtual void func_key();
};

class Unk02009734 : public Unk02007c84, public Unk02007204Amounts {
public:
    Unk02009734() {
        Unk02007c84();
    }
    virtual void func_key();

    Unk020680d4Cell cell;
};

class Unk02006228 : public Unk02002408 {
public:
    Unk02006228();
    virtual void func_key();

    u8 unk20[0x10];
};

class Unk02005e7c : public Unk02002408 {
public:
    Unk02005e7c();
    virtual void func_key();

    u8 unk20[0x10];
};

class Unk020064a4 : public Unk02002408 {
public:
    Unk020064a4();
    virtual void func_key();

    u8 unk20[0x20];
};

class Unk020098a0 : public Unk02002408 {
public:
    Unk020098a0();
    virtual void func_key();

    u8 unk20[0x38];
};

class Unk02000df0 : public Unk02002408 {
public:
    Unk02000df0();
    virtual void func_key();

    u8 unk20[0x30];
};

class Unk02004398 : public Unk02002408 {
public:
    Unk02004398();
    virtual void func_key();

    u8 unk20[0x18];
};

class Unk02004984 : public Unk02002408 {
public:
    Unk02004984();
    virtual void func_key();

    u8 unk20[0x18];
};

class Unk020031d8 : public Unk02002408 {
public:
    Unk020031d8();
    virtual void func_key();

    u8 unk20[0x10];
};

class Unk0200429c : public Unk02002408 {
public:
    Unk0200429c();
    virtual void func_key();

    u8 unk20[0x4];
};

class Unk02000cb0 : public Unk02002408 {
public:
    Unk02000cb0();
    virtual void func_key();

    u8 unk20[0xc];
};

/* kinds 25 to 28. */
class Unk0200125c : public Unk02002408 {
public:
    Unk0200125c();
    virtual void func_key();

    u8 unk20[0x28];
};

class Unk02001f98 : public Unk0200125c {
public:
    Unk02001f98() {}
    virtual void func_key();
};

class Unk02001f68 : public Unk0200125c {
public:
    Unk02001f68() {}
    virtual void func_key();
};

class Unk02001f38 : public Unk0200125c {
public:
    Unk02001f38() {}
    virtual void func_key();
};

class Unk02001f08 : public Unk0200125c {
public:
    Unk02001f08() {}
    virtual void func_key();
};

Unk02007204Pool data_020be184;

void func_02007204(Unk02007204Pool *pool) {
    pool->nodes = (Unk02007204Node *)new u8[0x4000];
    func_02099b90(0, pool->nodes, 0x4000);
    pool->count = 0;
    Unk02007204Node *prev = 0;
    Unk02007204Node *n = pool->nodes;
    for (int i = 0; i < 0x80; i++) {
        n->prev = prev;
        prev = n;
        n++;
        prev->next = n;
    }
    prev->next = 0;
    pool->used = 0;
    pool->free = pool->nodes;
}

void func_0200726c(Unk02007204Pool *pool) {
    delete pool->nodes;
    pool->nodes = 0;
    pool->used = 0;
    pool->free = 0;
    pool->count = 0;
}

Unk02007204Node *func_02007294(Unk02007204Pool *pool) {
    Unk02007204Node *n = pool->free;
    if (n == 0) {
        return 0;
    }
    Unk02007204Node *next = n->next;
    pool->free = next;
    if (next != 0) {
        next->prev = 0;
    }
    n->prev = 0;
    n->next = pool->used;
    if (pool->used != 0) {
        pool->used->prev = n;
    }
    pool->used = n;
    pool->count++;
    return n;
}

void func_020072ec(Unk02007204Pool *pool, Unk02007204Node *n) {
    if (n->next != 0) {
        n->next->prev = n->prev;
    }
    if (n->prev != 0) {
        n->prev->next = n->next;
    } else {
        pool->used = n->next;
    }
    n->prev = 0;
    n->next = pool->free;
    if (pool->free != 0) {
        pool->free->prev = n;
    }
    pool->free = n;
    pool->count--;
}

void *func_02007340(Unk02007204Pool *pool, int kind) {
    void *p = func_02007294(pool);
    if (p == 0) {
        return 0;
    }
    switch (kind) {
    case 0:
        return new (p) Unk02005aa4();
    case 1:
        return new (p) Unk02005a74();
    case 2:
        return new (p) Unk02009818();
    case 3:
        return new (p) Unk02002bc8();
    case 4:
        return new (p) Unk020047cc();
    case 6:
        return new (p) Unk02006700();
    case 7:
        return new (p) Unk0200a5cc();
    case 8:
        return new (p) Unk0200a2d8();
    case 9:
        return new (p) Unk02005e1c();
    case 10:
        return new (p) Unk02008240();
    case 11:
        return new (p) Unk0200491c();
    case 12:
        return new (p) Unk02003ab0();
    case 13:
        return new (p) Unk020093ec();
    case 14:
        return new (p) Unk0200ad40();
    case 15:
        return new (p) Unk02007c84();
    case 16:
        return new (p) Unk02009764();
    case 17:
        return new (p) Unk02009734();
    case 18:
        return new (p) Unk02006228();
    case 19:
        return new (p) Unk02005e7c();
    case 20:
        return new (p) Unk020064a4();
    case 21:
        return new (p) Unk020098a0();
    case 29:
        return new (p) Unk02000df0();
    case 22:
        return new (p) Unk02004398();
    case 23:
        return new (p) Unk02004984();
    case 24:
        return new (p) Unk020031d8();
    case 25:
        return new (p) Unk02001f98();
    case 26:
        return new (p) Unk02001f68();
    case 27:
        return new (p) Unk02001f38();
    case 28:
        return new (p) Unk02001f08();
    case 31:
        return new (p) Unk0200429c();
    case 30:
        return new (p) Unk02000cb0();
    }
    return 0;
}
