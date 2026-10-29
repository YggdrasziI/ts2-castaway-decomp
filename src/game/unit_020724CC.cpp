/*
 * Unit 0x020724CC-0x02072BEC: the item catalog Unk020724cc
 * (include/game/unk_catalog.h). The constructor sorts the items of the database
 * data_020c3fc4 that have the type 0x8F3C48FD by part (keys data_020aefe8) and by
 * kind (keys data_020aefe0), at the index each item stores, and lists the items
 * of the type 0x3A969FC1 apart (part 8). The other functions read the owner's
 * record (Unk020081dc, func_020081dc), report or change the item of a part, draw
 * a random record (func_02072a78, with a local random generator) and write the
 * record back (func_020670fc).
 *
 * Bounds: hypothesis. 0x020724CC is called from unit_02071D94.cpp but uses no
 * state; 0x02072BEC is the constructor of the next game state. No data of its own
 * (the key tables 0x020AEFE0 / 0x020AEFE8 are read-only data of unknown owner).
 * Real file name unknown.
 */

#include "game/unk_catalog.h"

typedef unsigned char u8;

/*
 * The random generator of func_02072a78 (0x9C4 bytes): the word at 0x9C0 is set
 * to 0x271 (625) before func_020a20f0 seeds it, as in an MT19937 state of 624
 * words. That reading is a hypothesis.
 */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

extern u8 data_020c3fc4[];
extern const u32 data_020aefe0[];
extern const u32 data_020aefe8[];

extern "C" {
void func_02080824(void *dest, int value, u32 size);
Unk0205d000 *func_0205f714(void *db, u32 type, Unk0205d000 *prev);
int func_0205f780(void *db, u32 type);
Unk0205d000 *func_0205f6f8(void *db, int id);
bool func_0205d340(Unk0205d000 *item, u32 key);
bool func_0205d2c8(Unk0205d000 *item, u32 key, u32 key2);
int func_0205d1b4(Unk0205d000 *item, u32 key);
int func_0205d134(Unk0205d000 *item, u32 key);
Unk020081dc func_020081dc(Unk020c43a8 *owner);
void func_020647f0(Unk020081dc *record);
void func_020670fc(Unk020c43a8 *owner, Unk020081dc *record);
void func_020a20f0(Unk020a20f0 *random);
u32 func_020a1f84(Unk020a20f0 *random);
}

/* 95.66 %: the original loads the type key before the database address for the
 * searches and keeps the key of the second list in a register (here the address);
 * member calls on the database, key locals and loop forms gave the same code. */
Unk020724cc::Unk020724cc(Unk020c43a8 *owner) {
    others = 0;
    otherCount = 0;
    this->owner = owner;
    func_02080824(counts, 0, sizeof(counts));
    func_02080824(items, 0, sizeof(items));
    for (Unk0205d000 *item = func_0205f714(data_020c3fc4, 0x8f3c48fd, 0); item != 0;
         item = func_0205f714(data_020c3fc4, 0x8f3c48fd, item)) {
        for (int part = 0; part < 6; part++) {
            if (!func_0205d340(item, data_020aefe8[part])) {
                continue;
            }
            for (int kind = 0; kind < 2; kind++) {
                if (func_0205d340(item, data_020aefe0[kind]) && func_0205d2c8(item, 0x22d6e5e0, 0x42d81a25)) {
                    items[kind][part][func_0205d1b4(item, 0x42d81a25)] = item;
                    counts[kind][part]++;
                }
            }
        }
    }
    otherCount = func_0205f780(data_020c3fc4, 0x3a969fc1);
    if (otherCount > 0) {
        others = new Unk0205d000 *[otherCount];
        otherCount = 0;
        for (Unk0205d000 *item = func_0205f714(data_020c3fc4, 0x3a969fc1, 0); item != 0;
             item = func_0205f714(data_020c3fc4, 0x3a969fc1, item)) {
            others[otherCount++] = item;
        }
    }
}

Unk020724cc::~Unk020724cc() {
    if (others != 0) {
        delete[] others;
    }
}

int Unk020724cc::func_020726bc(int part) {
    if (part == 8) {
        return otherCount;
    }
    return counts[func_020081dc(owner).unk28][part];
}

int Unk020724cc::func_02072710(int part, int index) {
    if (part == 8) {
        return func_0205d134(others[index], 0x9d5bba8e);
    }
    return func_0205d134(items[func_020081dc(owner).unk28][part][index], 0x9d5bba8e);
}

int Unk020724cc::func_0207278c(int part, int index) {
    return func_0205d1b4(items[func_020081dc(owner).unk28][part][index], 0x2b3e6dd7);
}

void Unk020724cc::func_020727e8(int part, int index) {
    if (part == 8) {
        func_020729e8(index);
        return;
    }
    Unk020081dc r = func_020081dc(owner);
    if (func_0205d340(items[r.unk28][part][index], 0x291d04a3)) {
        r.parts.v[part] = 0;
    } else {
        r.parts.v[part] = items[r.unk28][part][index]->unkc;
    }
    if ((u32)part <= 1) {
        r.colors.v[part] = func_0205d1b4(items[r.unk28][part][index], 0x2b3e6dd7);
    }
    func_020670fc(owner, &r);
}

bool Unk020724cc::func_020728c4(int part, int index) {
    Unk020081dc r = func_020081dc(owner);
    if (part == 8) {
        return r.unk18 == others[index]->unkc;
    }
    if (part == 3 && r.parts.v[part] == 0) {
        return func_0205d340(items[r.unk28][part][index], 0x291d04a3);
    }
    return r.parts.v[part] == items[r.unk28][part][index]->unkc;
}

void Unk020724cc::func_020729ac() {
    Unk020081dc r = func_020081dc(owner);
    r.parts.v[3] = 0;
    func_020670fc(owner, &r);
}

void Unk020724cc::func_020729e8(int index) {
    Unk020081dc r = func_020081dc(owner);
    r.unk18 = others[index]->unkc;
    func_020670fc(owner, &r);
}

void Unk020724cc::func_02072a30(int kind) {
    Unk020081dc r = func_020081dc(owner);
    func_02072a78(kind, &r);
    func_020670fc(owner, &r);
}

void Unk020724cc::func_02072a78(int kind, Unk020081dc *out) {
    Unk020a20f0 random;
    func_020a20f0(&random);
    if (kind == -1) {
        kind = func_020a1f84(&random) & 1;
    }
    out->unk28 = kind;
    for (int part = 0; part < 6; part++) {
        u32 n = counts[out->unk28][part];
        u32 k = func_020a1f84(&random) % n;
        if (part == 3) {
            out->parts.v[part] = 0;
        } else {
            out->parts.v[part] = items[out->unk28][part][k]->unkc;
        }
    }
    for (int i = 0; i < 3; i++) {
        out->colors.v[i] = func_0205d1b4(func_0205f6f8(data_020c3fc4, out->parts.v[i]), 0x2b3e6dd7);
    }
    int n = otherCount;
    int v;
    if (n <= 0) {
        v = 0;
    } else {
        v = others[func_020a1f84(&random) % n]->unkc;
    }
    out->unk18 = v;
}

void Unk020724cc::func_02072ba0() {
    func_020729ac();
    Unk020081dc r = func_020081dc(owner);
    func_020647f0(&r);
    r.parts.v[2] = 0x79a1e22e;
    func_020670fc(owner, &r);
}
