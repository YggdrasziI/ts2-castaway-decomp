/*
 * Unit 0x020647B0-0x02064984: the outfit record Unk020081dc
 * (include/game/unk_catalog.h): its initializer (0x020647B0, every part 0 and
 * every colour -1), its empty release (0x020647EC), the check of the first two
 * parts against their replacement item, and the lookups of the item of a part
 * in the database data_020c3fc4 (part 4 can be replaced by an item named by
 * part 3).
 *
 * Bounds: hypothesis. 0x020647B0 follows the icon functions (0x020644CC-
 * 0x020647B0, entries of 0x14 bytes); 0x02064984 starts unit_02064984.cpp,
 * whose constructor and reset call the first two functions. No data of its
 * own. Real file name unknown.
 *
 * The functions keep C linkage: other files call them by their addresses.
 *
 * Not complete: func_020647f0 is below 100 % (comment above it).
 */

#include "game/unk_catalog.h"

/* The record returned by func_0205cd6c (0x34 bytes; only the first word is read). */
struct Unk0205cd6c {
    int unk0;
    int unk4[12];
};

typedef unsigned char u8;

extern u8 data_020c3fc4[];

extern "C" {
Unk0205d000 *func_0205f6f8(void *db, int id);
int func_0205f6a4(void *db, int id);
int func_0205d1b4(Unk0205d000 *item, u32 key);
Unk0205cd6c func_0205cd6c(Unk0205d000 *item, int a);

void func_020647b0(Unk020081dc *o);
void func_020647ec(Unk020081dc *o);
void func_020647f0(Unk020081dc *o);
int func_0206486c(Unk020081dc *o, int i);
int func_02064894(Unk020081dc *o, int i);
int func_020648ac(Unk020081dc *o);
Unk0205d000 *func_020648dc(Unk020081dc *o, int i);
}

static inline bool func_isItemIn(void *db, int id) {
    return func_0205f6a4(db, id) != -1;
}

static inline bool func_isItem(int id) {
    return func_0205f6a4(data_020c3fc4, id) != -1;
}

void func_020647b0(Unk020081dc *o) {
    o->unk18 = 0;
    o->unk28 = 0;
    for (int i = 0; i < 6; i++) {
        o->parts[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        o->unk1c[i] = -1;
    }
}

void func_020647ec(Unk020081dc *o) {}

/* 98.1 %: the loop counter and `id` are in r8 / r9 swapped; nested tests, a
 * bool local, a database local and declaration orders gave the same code. */
void func_020647f0(Unk020081dc *o) {
    for (int i = 0; i < 2; i++) {
        int id = func_0205d1b4(func_0205f6f8(data_020c3fc4, o->parts[i]), 0x2a9ad5eb);
        if (id != 0 && !func_isItem(id)) {
            id = 0;
        }
        if (id != 0) {
            o->parts[i] = id;
        }
    }
}

int func_0206486c(Unk020081dc *o, int i) {
    return func_0205cd6c(func_020648dc(o, i), 0).unk0;
}

int func_02064894(Unk020081dc *o, int i) {
    return func_0205d1b4(func_020648dc(o, i), 0x275ea3a5);
}

int func_020648ac(Unk020081dc *o) {
    if (o->unk18 == 0) {
        return 0;
    }
    return func_0205d1b4(func_0205f6f8(data_020c3fc4, o->unk18), 0x275ea3a5);
}

Unk0205d000 *func_020648dc(Unk020081dc *o, int i) {
    u8 *db = data_020c3fc4;
    Unk0205d000 *item = func_0205f6f8(db, o->parts[i]);
    if (i == 4 && o->parts[3] != 0 && func_0205d1b4(func_0205f6f8(db, o->parts[3]), 0x66bd3af8)) {
        int id = func_0205d1b4(item, 0x5e68109b);
        if (id != 0 && func_isItemIn(db, id)) {
            return func_0205f6f8(db, id);
        }
    }
    return item;
}
