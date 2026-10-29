/*
 * Unit 0x02058EB8-0x020593E4: Unk02058eb8 (0x54 bytes, the object at 0x210
 * of the main game state). For each of seven object groups (the keys of
 * data_020aefa8) it keeps the number of object definitions of the group and
 * the inverse of their greatest weight; it picks a weighted random object of
 * a group among those allowed at a level, and queues an action (kind 0x1E)
 * with a group's id when all the objects of the group are in the collection.
 *
 * Bounds: hypothesis. The constructor 0x02058EB8 opens the range (the code
 * before it reads a block tagged 0x4C4F5453); the map cell class (constructor
 * 0x020593E4) follows. `.rodata` holds the group keys and the reward ids.
 * Real file name unknown.
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses.
 *
 * Not complete: func_02058f14, func_02058f34, func_02059150 and func_02059224
 * are not at 100 % (comments above them).
 */

typedef unsigned long u32;
typedef unsigned short u16;
typedef long long s64;

class Unk0206b630 {
public:
    bool func_0206b6bc(int value);
};

/* An object definition (only the id at 0x0C is used here). */
struct Unk0205cf00 {
    int unk0[3];
    int unkc;
};

/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4;

/* The player (data_020c43a8). */
struct Unk020c43a8 {
    unsigned char unk0[0x1de];
    u16 level;
};

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
};

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0;

/* The outfit record (include/game/unk_catalog.h; only the fields used here). */
class Unk020081dc {
public:
    Unk020081dc();
    ~Unk020081dc();

    int parts[6];
    int unk18;
    int colors[3];
    int unk28;
};

/* An object whose flags tell the group (func_02058f14). */
struct Unk02058f14Obj {
    u32 flags;
};

class Unk02058eb8 {
public:
    Unk02058eb8();
    ~Unk02058eb8();

    unsigned char unk0[0x1c];
    int counts[7];
    int scales[7];
};

extern Unk020c43a8 data_020c43a8;
extern Unk020d60c8 data_020d60c8;
extern Unk020a20f0 data_020d62a4;
extern Unk020c3fc4 data_020c3fc4;
extern unsigned char data_020bfc9c[];
extern unsigned char data_020be184[];
extern unsigned char data_020c4770[];

extern "C" {

extern const int data_020aefa8[7] = {
    0x31b3a4ac, (int)0xc17e4108, (int)0xcf78e68b, (int)0xc07f23df,
    (int)0xc17e54bd, 0x2514c1ab, (int)0xf9462fe2,
};

Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
Unk0205cf00 *func_0205f714(Unk020c3fc4 *db, int key, Unk0205cf00 *rec);
int func_0205f780(Unk020c3fc4 *db, int key);
int func_0205d234(Unk0205cf00 *def, int blockKey, int key);
int func_0205d340(Unk0205cf00 *def, u32 key);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
Unk020081dc func_020081dc(Unk020c43a8 *p);
int func_02077c60(int a, int b);
int func_020a20bc(Unk020a20f0 *random, int min, int max);
void *func_02007340(void *p, int kind);
void func_02000ce0(void *o, int id, int a, int b);
void func_02007e48(void *list, void *o);

int func_02058f34(Unk02058eb8 *p, int group, int level);
int func_02059150(Unk02058eb8 *p, int group);
int func_020591e4(Unk02058eb8 *p, int key);
bool func_02059224(Unk02058eb8 *p);
int func_02058f14(Unk02058eb8 *p, const Unk02058f14Obj *o);

}

static inline int func_fxmulr(int a, int b) {
    return (int)(((s64)a * b + 0x800) >> 12);
}

Unk02058eb8::Unk02058eb8() {
    for (int i = 0; i < 7; i++) {
        counts[i] = func_0205f780(&data_020c3fc4, data_020aefa8[i]);
        scales[i] = func_02059150(this, i);
    }
}

Unk02058eb8::~Unk02058eb8() {}

/* 98.50 %: the original sets the group with moveq #0 then movne #1, ours in
 * the reverse order (tried: != 0, ?:, == 0 ? 0 : 1, !!, bool / int locals,
 * if / else, an inline member, a bit field). */
int func_02058f14(Unk02058eb8 *p, const Unk02058f14Obj *o) {
    return func_02058f34(p, (o->flags & 0xc000) ? 1 : 0, -1);
}

/* 96.15 %: registers rotated (the original keeps the definition in r4, the
 * flag in r5, the level in r6, the group in r7, ours in r8, r4, r5, r6);
 * tried: all declaration orders of the locals, the definition declared at
 * each position, while / goto loops, locals for the flag, the owned test,
 * the level, the scales. */
int func_02058f34(Unk02058eb8 *p, int group, int level) {
    Unk0205cf00 *def;
    Unk0206b630 *set = data_020d60c8.collection;
    int best = 0;
    u32 bestValue = 0;
    if (level < 0) {
        level = data_020c43a8.level;
    }
    bool first = func_020081dc(&data_020c43a8).unk28 == 0;
    for (def = func_0205f714(&data_020c3fc4, data_020aefa8[group], 0); def != 0;
         def = func_0205f714(&data_020c3fc4, data_020aefa8[group], def)) {
        if (func_0205d234(def, 0x102647da, 0x0c9b830d) > level) {
            continue;
        }
        bool owned = set->func_0206b6bc(def->unkc);
        if (func_0205d234(def, 0x102647da, 0xc6276e01) == 0x64378dc5 && owned) {
            continue;
        }
        if (func_0205d340(def, 0x891a34ba)) {
            if (!first && !func_0205d340(def, 0x1e49458c)) {
                continue;
            }
            if (first && !func_0205d340(def, 0x85fba6e5)) {
                continue;
            }
        }
        int weight = func_0205d234(def, 0x102647da, 0x4c43f955);
        int r = func_020a20bc(&data_020d62a4, 0, 0x7fffffff);
        u32 value = func_fxmulr(r, func_fxmulr(weight << 12, p->scales[group]));
        if (func_0205d234(def, 0x102647da, 0xa70a5f1a) == 0x64378dc5 && !owned) {
            return def->unkc;
        }
        if (value >= bestValue) {
            bestValue = value;
            best = def->unkc;
        }
    }
    return best;
}

/* 98.65 %: the original keeps the group key in r4 and the definition in r9,
 * ours in r9 and r6 (tried: declaration orders, a weight local, inline
 * helpers for the walk). */
int func_02059150(Unk02058eb8 *p, int group) {
    Unk0205cf00 *def;
    int max = 0;
    Unk020c3fc4 *db = &data_020c3fc4;
    for (def = func_0205f714(db, data_020aefa8[group], 0); def != 0;
         def = func_0205f714(db, data_020aefa8[group], def)) {
        int weight = func_0205d234(def, 0x102647da, 0x4c43f955);
        if (weight > max) {
            max = weight;
        }
    }
    if (max <= 0) {
        return 0x1000;
    }
    return func_02077c60(0x1000, max << 12);
}

int func_020591e4(Unk02058eb8 *p, int key) {
    for (int i = 0; i < 7; i++) {
        if (key == data_020aefa8[i]) {
            return func_02058f34(p, i, -1);
        }
    }
    return 0;
}

/* 99.29 %: the original keeps the settings' collection in r7 (ours r5, the
 * counters one register lower) and the id / flag stack slots swapped (tried:
 * declaration orders of the array, the database, the collection, the flag,
 * the counters). */
bool func_02059224(Unk02058eb8 *p) {
    int ids[7] = {
        0x7f4aaab5, 0x40131b79, 0x41239553, (int)0xe22f893b,
        (int)0xa15edd64, (int)0xd2310469, 0x5562b4fe,
    };
    Unk020c3fc4 *db = &data_020c3fc4;
    Unk0206b630 *set = data_020d60c8.collection;
    bool first = func_020081dc(&data_020c43a8).unk28 == 0;
    for (int i = 0; i < 7; i++) {
        bool all;
        int id = ids[i];
        if (func_02054dc4(data_020bfc9c, func_0205f6f8(db, id), 0) != 0) {
            continue;
        }
        int n = 0;
        all = true;
        for (Unk0205cf00 *def = func_0205f714(db, data_020aefa8[i], 0); def != 0;
             def = func_0205f714(db, data_020aefa8[i], def)) {
            if (i == 6 && func_0205d340(def, 0x891a34ba)) {
                if (!first && !func_0205d340(def, 0x1e49458c)) {
                    continue;
                }
                if (first && !func_0205d340(def, 0x85fba6e5)) {
                    continue;
                }
            }
            n++;
            if (!set->func_0206b6bc(def->unkc)) {
                all = false;
                break;
            }
        }
        if (all && n != 0) {
            void *o = func_02007340(data_020be184, 0x1e);
            if (o != 0) {
                func_02000ce0(o, id, 1, 1);
                func_02007e48(data_020c4770, o);
            }
        }
    }
    return true;
}
