/*
 * Unit 0x02064984-0x020680D4: Unk020c43a8, the player (the object at
 * data_020c43a8). It owns the sim of unit_020680D4.cpp (created by
 * func_02065db8), its outfit, six motives and four relationship values
 * (Unk02064bf8 counters from 0 to 10,000,000), the tuning read from
 * "build/data/screens/motives.motives.nitro_xml" and
 * "build/data/screens/relationships.motives.nitro_xml" (needs, deltas,
 * thresholds), the idle animations (func_02066884) and a queue of actions
 * (offset 0x3C8). Its twelve virtual functions implement the interface of the
 * sim and mostly forward to it; two of them (0x02003BFC and 0x020041F0) are
 * defined in another file.
 *
 * Bounds: hypothesis. 0x02064984 (reset) is called by the constructor at
 * 0x02064A24, the first function to use the vtable 0x020BC6F8; the outfit
 * functions before it (0x020647B0-0x02064984) belong to another file;
 * 0x020680D4 starts unit_020680D4.cpp. `.rodata`: the animation keys
 * (data_020af010, read by func_02066704 and func_02067d0c), the initializers
 * of the local tables of func_02066090, func_02066374 and func_02067970 and
 * the search key data_020af1a8, up to 0x020AF1AC. `.data`: the two tuning
 * file names, the strings, the vtables of the player and of the counters and
 * the interface vtable copy, from 0x020BC620 up to 0x020BC7C4. Real file name
 * unknown.
 *
 * The functions other than the constructors, destructors and virtual
 * functions keep C linkage and their addresses as names.
 *
 * Not complete: the functions below 100 % carry a comment with the remaining
 * difference; `.data` scores low because objdiff does not pair the string
 * literals with the original symbols.
 */

#include "game/unk_sim.h"
#include "game/unk_datatree.h"
#include "game/unk_catalog.h"

/* The save stream of func_020a4dc4 (write) and func_020a4e14 (read). */
struct Unk020a4dc4;

/*
 * A value from 0 to 10,000,000 that decreases by `rate` at each tick once
 * `delay` reaches 0 (0x10 bytes; the motives and relationships).
 */
class Unk02064bf8 {
public:
    Unk02064bf8() : value(10000000), rate(0), delay(0) {}
    ~Unk02064bf8() {}
    virtual void func_00(int n);
    virtual void func_04(Unk020a4dc4 *s);
    virtual void func_08(Unk020a4dc4 *s);
    virtual void func_0c();

    int value;
    int rate;
    int delay;
};

/* A motive: the same counter with its own vtable. */
class Unk02064c24 : public Unk02064bf8 {
public:
    Unk02064c24() {}
    ~Unk02064c24() {}
};

/* A need: when the motive crosses `level`, the deltas are added to the rates (0x14 bytes). */
struct Unk020c43a8Need {
    Unk020c43a8Need() : motive(6), level(0), above(0) {
        for (int i = 0; i < 6; i++) {
            deltas[i] = 0;
        }
    }

    int motive;
    s8 level;
    u8 above;
    s16 deltas[6];
};

/* An idle animation chosen by the motive or relationship ranges (0x14 bytes). */
struct Unk020c43a8Idle {
    Unk020c43a8Idle() : motive(6), rel(4), min(0), max(0), key(0), anim(0x32) {}

    int motive;
    int rel;
    s8 min;
    s8 max;
    u32 key;
    int anim;
};

class Unk020c43a8;

/* The action queue (functions 0x02007D30-0x02007E48). */
struct Unk020c43a8Queue {
    Unk020c43a8Queue(Unk020c43a8 *owner) : owner(owner), flags(0), unk8(0), head(0) {}

    Unk020c43a8 *owner;
    u32 flags;
    int unk8;
    struct Unk02007340 *head;
};

/* The object attached to the player's head (vtable slots 0x18 and 0x24, flags at 0x40). */
class Unk0201c460 {
public:
    Unk0201c460(u32 key);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual void func_20();
    virtual void func_24();
    void func_0201cf6c(Unk020680d4Vec pos, Unk020680d4Vec offset);

    u8 unk4[0x3c];
    u32 flags;
    u8 unk44[0x44];
};

/* The part of the player written to the save (0x98 bytes). */
struct Unk020c43a8Save {
    int unk150[4];
    int unk160;
    int unk164;
    u8 name[0x40];
    Unk020081dc outfit;
    u16 unk1d4;
    u16 unk1d6;
    u16 unk1d8;
    u16 flags1da;
    u16 flags1dc;
    u16 unk1de;
    Unk020680d4Cell cell;
};

class Unk020c43a8 : public Unk020680d4Base {
public:
    Unk020c43a8();
    ~Unk020c43a8();
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);

    Unk020680d4Cell home;
    Unk020680d4 *sim;
    int unk10;
    int timer;
    int unk18;
    int unk1c[6];
    int bone;
    u8 unk38;
    u8 done;
    Unk0201c460 *obj;
    Unk02064c24 motives[6];
    Unk02064c24 unka0;
    Unk02064bf8 rels[4];
    int unkf0[4];
    int unk100;
    int unk104;
    int unk108;
    int unk10c;
    s8 table[6][6];
    int rates[6];
    u8 unk14c;
    Unk020c43a8Save save;
    Unk020c43a8Need needs[10];
    Unk020c43a8Idle idles[14];
    Unk020c43a8Queue queue;
};

/* The objects of data_020be184 (func_02007340). */
struct Unk02007340 {
    u8 unk0[0x24];
    int kind;
    int index;
    u8 unk2c[8];
    u32 key;
};

struct Unk02007340K00 {
    void func_set(Unk020680d4Cell c) {
        cell = c;
    }

    u8 unk0[0x34];
    Unk020680d4Cell cell;
};

/* A list of objects found by func_0205fb4c. */
struct Unk0205f098 {
    Unk020680d4Base *head;
    int count;
};

struct Unk0205cf00;

struct Unk020bfc9cItem {
    int unk0;
    int unk4;
    int unk8;
};

/* The random generator (0x9C4 bytes; see unit_020724CC.cpp). */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

/* A search over data_020bfc9c (constructor 0x020547F8). */
struct Unk020547f8Node {
    Unk0205cf00 *def;
    int count;
    int unk8;
    Unk020547f8Node *next;
};

class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk020547f8Node *head;
    int count;
};

/* An item drawn by func_02067970 and how many times. */
struct Unk020c43a8Pick {
    Unk020c43a8Pick() : node(0), count(0) {}

    Unk020547f8Node *node;
    int count;
};

struct Unk020589ac {
    int unk0;
    int unk4;
    u32 unk8;
};

struct Unk020d60c8Mode {
    int unk0;
    int unk4;
};

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    u8 unk0[0x140];
    Unk020d60c8Mode *mode;
    u8 unk144[0x14];
    void *text;
};

struct Unk020d6240 {
    u8 unk0[0x14];
    Unk02093648 *archive;
};

struct Unk020d6298 {
    int unk0;
    u32 unk4;
};

struct Unk0206bce0 {
    u8 unk0[0x214];
    void *unk214;
};

/* The table of func_02066090: what to queue when a motive reaches 0. */
struct Unk020af138 {
    int kind;
    u32 mask;
    u32 key;
};

extern "C" {
void func_020a20f0(Unk020a20f0 *random);
void func_02054d94(void *db, Unk020547f8 *out, const u32 *keys, int a, int b);
Unk020547f8Node *func_02054858(Unk020547f8 *list, int index);
void func_02054cf0(void *db, Unk020547f8Node *node, int a);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
Unk020d6240 *func_020a18e4();
void func_020897b4(const char *fmt, ...);
void func_020a4dc4(Unk020a4dc4 *s, void *p, int size);
void func_020a4e14(Unk020a4dc4 *s, void *p, int size);
u32 func_020a1f84(Unk020a20f0 *random);
int func_020a1e68(int a, int b, int c);
const u8 *func_020a00a0(void *text, int id);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int index);
Unk020589ac *func_020589ac(Unk020c3ba4 *world, int index);
int func_0205803c(Unk02058788 *map, const Unk020680d4Cell *cell);
bool func_02059418(const Unk020680d4Cell *cell);
u32 func_02059cf8(void *p);
Unk0206bce0 *func_0206bce0();
Unk0205cf00 *func_0205f6f8(void *db, u32 key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
bool func_0205d340(Unk0205cf00 *def, u32 key);
Unk020bfc9cItem *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_0205f098(Unk0205f098 *list);
void func_0205f0a8(Unk0205f098 *list);
void func_0205fb4c(void *db, u32 key, Unk0205f098 *list, int map);
Unk02007340 *func_02007340(void *p, int kind);
void func_02007d30(Unk020c43a8Queue *q);
void func_02007d94(Unk020c43a8Queue *q);
void func_02007e38(Unk020c43a8Queue *q);
void func_02007e48(Unk020c43a8Queue *q, void *o);
Unk020081dc func_020081dc(Unk020c43a8 *p);
Unk02063d84 *func_02063e2c(u32 key, int mode);
Unk020897c0 *func_02063d84(Unk02063d84 *a);
void *func_02002438(int a);
Unk02098ff0 func_020613a4(int a);
Unk0208be3cEntry *func_01ffa954(Unk0208be3c *xform, int index);
int func_01ffa9b0(Unk0208be3c *xform, const char *name);

void func_020684f4(Unk020680d4 *p, Unk020081dc *outfit);
void func_020685e0(Unk020680d4 *p);
void func_0206869c(Unk020680d4 *p, bool place);
void func_02069124(Unk020680d4 *p, Unk02063d84 *anim, int time, bool hide);
Unk020680d4Vec func_0206920c(Unk020680d4 *p, const char *name, Unk020680d4Vec offset);
void func_020695f0(Unk020680d4 *p);
void func_02069d4c(Unk020680d4 *p, int angle, bool b);

void func_02064984(Unk020c43a8 *p);
void func_02064ca0(Unk020c43a8 *p);
void func_02064cfc(Unk020c43a8 *p, int kind, Unk020724cc *catalog);
void func_02064d38(Unk020c43a8 *p, int hash, u32 key, int value);
void func_02065b80(Unk020c43a8 *p, bool place);
void func_02065e80(Unk020c43a8 *p);
void func_02065eb8(Unk020c43a8 *p);
void func_0206622c(Unk020c43a8 *p);
void func_0206632c(Unk020c43a8 *p, int i, int n);
void func_02066374(Unk020c43a8 *p, int row);
int func_0206647c(Unk020c43a8 *p, int i);
Unk02064bf8 *func_02066488(Unk020c43a8 *p, int i);
Unk02064c24 *func_02066494(Unk020c43a8 *p, int i);
bool func_02066518(Unk020c43a8 *p, const Unk020680d4Cell *cell);
void func_020667a8(Unk020c43a8 *p, int i);
int func_020667d4(Unk020c43a8 *p, int i);
void func_02066d1c(Unk020c43a8 *p);
Unk02098ff0 func_02066f14(Unk020c43a8 *p);
void func_020670fc(Unk020c43a8 *p, Unk020081dc *outfit);
void func_02067160(Unk020c43a8 *p, int i, int v);
int func_0206716c(Unk020c43a8 *p, int i);
void func_02067178(Unk020c43a8 *p, int hash);
bool func_02067364(Unk020c43a8 *p, int hash);
void func_02067560(Unk020c43a8 *p, u32 n);
void func_02067594(Unk020c43a8 *p, Unk020a4dc4 *s);
void func_02067620(Unk020c43a8 *p, Unk020a4dc4 *s);
int func_020676b4(Unk020c43a8 *p);
int func_02067708(Unk020c43a8 *p, int a, int b);
void func_02067778(Unk020c43a8 *p, Unk020680d4Cell cell);
int func_02067b70();
void func_02067bc4(Unk020c43a8 *p, const Unk0209674c *node, int index);
void func_02067d0c(Unk020c43a8 *p, const Unk0209674c *node, int index);
void func_02064cdc(Unk020c43a8 *p);
void func_02064e10(Unk020c43a8 *p);
void func_02064d38(Unk020c43a8 *p, int hash, u32 key, int value);
void func_02067bc4(Unk020c43a8 *p, const Unk0209674c *node, int index);
void func_02067d0c(Unk020c43a8 *p, const Unk0209674c *node, int index);
void func_0206562c(Unk020c43a8 *p);
void func_02065a60(Unk020c43a8 *p, u32 cls, bool rot);
void func_02065d48(Unk020c43a8 *p);
void func_02065db8(Unk020c43a8 *p);
void func_02066090(Unk020c43a8 *p);
int func_02066298(Unk020c43a8 *p, int n);
void func_020662c8(Unk020c43a8 *p, int i, int n);
void func_020664a0(Unk020c43a8 *p, const u8 *name);
Unk02063d84 *func_02066704(Unk020c43a8 *p, u32 anim, bool loop);
bool func_02066748(Unk020c43a8 *p, int anim, bool loop, int time, bool hide, int angle);
void func_020667f8(Unk020c43a8 *p, int time);
void func_02066884(Unk020c43a8 *p);
void func_0206702c(Unk020c43a8 *p);
void func_0206708c(Unk020c43a8 *p, int kind, Unk020724cc *catalog);
bool func_0206757c(Unk020c43a8 *p, int mask);
int func_02067878(u32 hash);
int func_0206790c(u32 hash);
void func_02067970(Unk020c43a8 *p);
bool func_02067ec0(Unk020c43a8 *p);
void func_02067fb0(Unk02064bf8 *c);
void func_0206800c(Unk02064bf8 *c, int n);
}

extern Unk020c3ba4 data_020c3ba4;
extern Unk020d60c8 data_020d60c8;
extern Unk020d6298 data_020d6298;
extern Unk020a20f0 data_020d62a4;
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020be184[];
extern Unk020c43a8 data_020c43a8;

/* The object whose word at 0x18 holds a sim (data_020c439c). */
struct Unk020c439c {
    u8 unk0[0x18];
    Unk020680d4 *sim;
};

extern Unk020c439c data_020c439c;

/* The animation keys (indices of func_02066704). */
const u32 data_020af010[0x4a] = {
    0x184765d1, 0x957e85bc, 0xe5189dca, 0x5e42b82d, 0xa55293b7, 0xbe792964,
    0x45ceb787, 0x934060c4, 0x192da069, 0x326103f8, 0xeb68c390, 0x4ddeea31,
    0x846c4a77, 0x915a7d12, 0xe03f28b8, 0xeca7c1b5, 0xfc030921, 0xb6299715,
    0x399be1f6, 0xb57d799a, 0x0488fa46, 0x8399fb35, 0x2990ca28, 0xe1007fbf,
    0x3cf8af39, 0x839a0ab2, 0x307cfb72, 0xad8b455d, 0xd817a8a8, 0x0aed9a04,
    0x05d5e875, 0xbbe9df03, 0x3c6a72ae, 0x470803a9, 0xd54e6a8f, 0x9cddd763,
    0xf39aa5d1, 0x7aa30219, 0xa2ab1526, 0xc1bc4dcc, 0xe6c10257, 0x707af439,
    0x50ac7f4d, 0x7400de57, 0x67625ce6, 0x38c95ed9, 0x8c7ac30e, 0x199cc6b1,
    0xb1495c75, 0xc60da1e6, 0x98bcfaae, 0x3b2fa614, 0x58a38e8b, 0x9697cdc2,
    0x8c3d5220, 0x59823aaa, 0xd8a35447, 0xb02adb8a, 0xa612b99c, 0x7c8143f8,
    0x7c8143f9, 0x7c8143fa, 0x7c8143fb, 0xcd5448a8, 0xcd5448a9, 0xcd5448aa,
    0xaa79dd14, 0x948a56c3, 0x6d85596b, 0x6d85596c, 0xa3ebb64f, 0x494ff9aa,
    0x2f6f9f8a, 0xf4f385ef,
};

static inline bool func_isLoaded(Unk020c43a8 *p) {
    return p->sim != 0 && (p->sim->flags & 2);
}

void func_02064984(Unk020c43a8 *p) {
    p->save.unk160 = 0;
    p->save.unk164 = -1;
    p->save.unk1d4 = 0;
    p->save.unk1d4 |= 1;
    p->save.outfit = Unk020081dc();
    p->save.unk1d6 = 0;
    p->save.unk1d8 = 0;
    p->save.flags1da = 0x40;
    p->save.flags1dc = 0;
    p->save.unk1de = 0;
    p->unk38 = 0;
}

Unk020c43a8::Unk020c43a8()
    : sim(0), unk10(1), timer(5), unk18(0), bone(-1), unk38(0), done(0), obj(0), queue(this) {
    queue.flags |= 2;
    func_02064984(this);
    for (int i = 0; i < 6; i++) {
        unk1c[i] = 0;
    }
}

Unk020c43a8::~Unk020c43a8() {}

void func_02064ca0(Unk020c43a8 *p) {
    func_02007e38(&p->queue);
    if (p->sim != 0) {
        delete p->sim;
        p->sim = 0;
    }
}

void func_02064cdc(Unk020c43a8 *p) {
    func_02064984(p);
    func_02064e10(p);
    func_0206562c(p);
}

void func_02064cfc(Unk020c43a8 *p, int kind, Unk020724cc *catalog) {
    func_02064cdc(p);
    func_0206708c(p, kind, catalog);
    func_02065a60(p, 0x1adc021f, false);
}

void func_02064d38(Unk020c43a8 *p, int hash, u32 key, int value) {
    int row;
    switch (hash) {
    case 0x732a908e:
        row = 0;
        break;
    case 0x65b8f595:
        row = 1;
        break;
    case 0x123510ae:
        row = 2;
        break;
    case 0x68de29ae:
        row = 3;
        break;
    case 0xcce58e2e:
        row = 4;
        break;
    case 0xf3e27c18:
        row = 5;
        break;
    default:
        return;
    }
    int col = func_02067878(key);
    if (col == 6) {
        return;
    }
    p->table[row][col] = value;
}

void func_02064e10(Unk020c43a8 *p) {
    Unk0209674c root;
    Unk0209674c child;
    Unk0209674c sub;
    int needs;
    int idles;
    Unk02093648 *archive = func_020a18e4()->archive;
    for (u32 i = 0; i < 6; i++) {
        for (u32 j = 0; j < 6; j++) {
            p->table[i][j] = 0;
        }
    }
    Unk02096348 *file = (Unk02096348 *)archive->func_02093c18(
        (const u32 *)"build/data/screens/motives.motives.nitro_xml");
    int values[6];
    root = file->func_02096980();
    needs = 0;
    idles = needs;
    for (u32 i = 0; i < root.func_020967ec(); i++) {
        child = root.func_02096774(i);
        int hash = child.func_02096800();
        if (hash == 0x2fd6225b) {
            continue;
        }
        switch (hash) {
        case 0x809bfa56:
            values[0] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x731b5b5d:
            values[1] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xed9e7fad:
            values[2] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x805798cc:
            values[3] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xda47eff7:
            values[4] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xd11d6717:
            values[5] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xeb5296ca:
            p->unka0.value = file->func_02096574(child.func_02096774(0).func_0209688c()) * 100000;
            break;
        case 0x9616553f:
            p->rates[0] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x8895b646:
            p->rates[1] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x27ce430a:
            p->rates[2] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xba78580a:
            p->rates[3] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xefc1d2df:
            p->rates[4] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x0b4d2a74:
            p->rates[5] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x732a908e:
        case 0x65b8f595:
        case 0x123510ae:
        case 0x68de29ae:
        case 0xcce58e2e:
        case 0xf3e27c18:
            for (u32 k = 0; k < child.func_020967ec(); k++) {
                sub = child.func_02096774(k);
                func_02064d38(p, hash, sub.func_02096800(), file->func_02096574(sub.func_0209688c()));
            }
            break;
        case 0xa5357d08:
            p->unk10 = child.func_02096774(0).func_020968a0();
            break;
        case 0xd7e2be9b:
            p->unkf0[0] = child.func_02096774(0).func_020968a0();
            break;
        case 0x8ea2d64b:
            p->unkf0[1] = child.func_02096774(0).func_020968a0();
            break;
        case 0xdfb12acd:
            p->unkf0[2] = child.func_02096774(0).func_020968a0();
            break;
        case 0xb2694026:
            p->unkf0[3] = child.func_02096774(0).func_020968a0();
            break;
        case 0xa8d184ef:
            if (needs < 10) {
                func_02067bc4(p, &child, needs);
            }
            needs++;
            break;
        case 0x5e00d1c3:
            if (idles < 14) {
                func_02067d0c(p, &child, idles);
            }
            idles++;
            break;
        case 0x08085901:
            p->unk100 = child.func_02096774(0).func_020968a0();
            break;
        case 0x789db16d:
            p->unk104 = child.func_02096774(0).func_020968a0();
            break;
        case 0xdb6e4e6f:
            p->unk108 = child.func_02096774(0).func_020968a0();
            break;
        case 0x27276279:
            p->unk10c = child.func_02096774(0).func_020968a0();
            break;
        }
    }
    for (u32 i = 0; i < 6; i++) {
        p->motives[i].value = values[i] * 100000;
        p->motives[i].rate = p->rates[i];
    }
    p->unk14c = 0;
    archive->func_02093d14((const u32 *)"build/data/screens/motives.motives.nitro_xml");
}

void func_0206562c(Unk020c43a8 *p) {
    for (int i = 0; i < 4; i++) {
        p->save.unk150[i] = 0;
    }
    Unk0209674c root;
    Unk0209674c child;
    Unk0209674c sub;
    Unk02093648 *archive = func_020a18e4()->archive;
    Unk02096348 *file = (Unk02096348 *)archive->func_02093c18(
        (const u32 *)"build/data/screens/relationships.motives.nitro_xml");
    int values[4];
    int rates[4];
    root = file->func_02096980();
    for (u32 i = 0; i < root.func_020967ec(); i++) {
        child = root.func_02096774(i);
        int hash = child.func_02096800();
        if (hash == 0x2fd6225b) {
            continue;
        }
        switch (hash) {
        case 0x38f5c45e:
            values[0] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xa50e540c:
            values[1] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x8c6d06a5:
            values[2] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x5b32cf0b:
            values[3] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x1120dc10:
            file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x173ace11:
            file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x64a6adf8:
            file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x3a8ca430:
            file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x4e701f66:
            rates[0] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xa4786c63:
            rates[1] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0xa1e7618e:
            rates[2] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        case 0x95531629:
            rates[3] = file->func_02096574(child.func_02096774(0).func_0209688c());
            break;
        }
    }
    for (u32 i = 0; i < 4; i++) {
        Unk02064bf8 &r = p->rels[i];
        r.value = values[i] * 100000;
        r.rate = rates[i];
    }
    archive->func_02093d14((const u32 *)"build/data/screens/relationships.motives.nitro_xml");
}

void func_02065a60(Unk020c43a8 *p, u32 cls, bool rot) {
    int map = data_020c3ba4.map;
    Unk0205f098 list;
    func_0205f098(&list);
    func_0205fb4c(data_020c3fd4, cls, &list, map);
    if (list.count > 0) {
        Unk020680d4Cell cell = list.head->func_14();
        p->func_10(cell);
        if (rot) {
            p->func_08(list.head->func_0c());
        }
        func_020897b4("Placed Sim here: ");
        func_020897b4("Lot Position Lot:%d Segment:%d Room:%d X:%d Y:%d", cell.pos.unk3, cell.pos.unk2,
                      cell.pos.unk0, cell.xy.x, cell.xy.y);
    } else {
        func_020897b4("SetPosAtObjectOfClass::Couldn't find a place for the Sim to stand!");
    }
    func_0205f0a8(&list);
}

void func_02065b80(Unk020c43a8 *p, bool place) {
    if (p->sim == 0) {
        return;
    }
    Unk02063d84 *anim = p->sim->anim;
    p->done = 0;
    if (anim == 0 || anim->anim->func_01ff8a8c() || anim->anim->func_01ff8aa0()) {
        p->done = 1;
        if (anim != 0) {
            func_02063d84(anim)->func_01ff8a80();
        }
    }
    if (p->obj != 0) {
        p->obj->func_0201cf6c(func_0206920c(p->sim, "head", Unk020680d4Vec(0, 0, 0)), Unk020680d4Vec(0, 0, 0));
        if (p->obj->flags & 4) {
            p->obj->func_18();
            p->obj->func_24();
            p->obj = 0;
        }
    }
    if (p->timer == 0x400) {
        func_02065d48(p);
    } else if (p->queue.head == 0) {
        if (p->done) {
            if (--p->timer == 0) {
                func_02066884(p);
            } else {
                func_020667f8(p, 10);
            }
        }
    } else {
        if (p->obj != 0) {
            p->obj->func_18();
            p->obj->func_24();
            p->obj = 0;
        }
        func_02007d30(&p->queue);
    }
    if (p->sim != 0) {
        func_0206869c(p->sim, place);
    }
}

void func_02065d48(Unk020c43a8 *p) {
    if (p->queue.head != 0) {
        p->timer = 5;
        func_02007d30(&p->queue);
        return;
    }
    if (!p->done) {
        return;
    }
    func_020667f8(p, 10);
    p->timer = func_020a1f84(&data_020d62a4) % 5 + 5;
}

/* 97.6 %: after the loaded test the original reloads `sim` (the test keeps it
 * in another register); helper forms (bool local, ternary, `!= 0`) gave the
 * same code. */
void func_02065db8(Unk020c43a8 *p) {
    if (func_isLoaded(p)) {
        return;
    }
    if (p->sim == 0) {
        p->sim = new Unk020680d4;
    }
    if (p->sim == 0) {
        return;
    }
    p->sim->func_10(p->save.cell);
    func_020684f4(p->sim, &p->save.outfit);
    func_020667f8(p, 0);
    p->bone = func_01ffa9b0(p->sim->xform, "rootbone");
}

/* 91.8 %: same reload of `sim` as func_02065db8. */
void func_02065e80(Unk020c43a8 *p) {
    if (func_isLoaded(p) && p->sim != 0) {
        func_020685e0(p->sim);
    }
}

void func_02065eb8(Unk020c43a8 *p) {
    p->motives[1].rate = p->rates[1];
    p->motives[2].rate = p->rates[2];
    p->motives[5].rate = p->rates[5];
    p->motives[3].rate = p->rates[3];
    p->motives[0].rate = p->rates[0];
    p->motives[4].rate = p->rates[4];
    if (func_0206757c(p, 0x20)) {
        p->save.flags1da &= ~0x40;
    }
    if (!(p->save.flags1da & 0x40)) {
        if (func_02067ec0(p)) {
            p->motives[2].rate += p->unk100;
        }
        if ((int)((data_020d6298.unk4 & 0x7c0) >> 6) < 6) {
            p->motives[2].rate += p->unk104;
        }
        p->motives[2].rate += p->unk108 * p->save.unk160 / 256;
        p->motives[3].rate += p->unk10c * p->save.unk160 / 256;
        for (int i = 0; i < 10; i++) {
            if (p->needs[i].motive == 6) {
                continue;
            }
            if ((!p->needs[i].above && p->motives[p->needs[i].motive].value <= p->needs[i].level * 100000) ||
                (p->needs[i].above && p->motives[p->needs[i].motive].value >= p->needs[i].level * 100000)) {
                for (int j = 0; j < 6; j++) {
                    p->motives[j].rate += p->needs[i].deltas[j];
                }
            }
        }
        func_02066090(p);
    }
    int min = 10000000;
    for (int i = 0; i < 6; i++) {
        if (p->motives[i].value < min) {
            min = p->motives[i].value;
        }
    }
    p->unka0.value = min;
}

/* 99.0 %: register allocation of the loop pointers (r7 / r8 / r9 swapped). */
void func_02066090(Unk020c43a8 *p) {
    Unk020af138 t[6] = {
        {1, 1, 0x57713c5b}, {2, 2, 0x890f1fb8}, {0, 4, 0x9b3ea8ad},
        {1, 8, 0x764f589f}, {1, 0x10, 0x5dc93a88}, {1, 0x20, 0x8086f1f9},
    };
    func_0205803c(func_02058788(&data_020c3ba4, data_020c3ba4.map), &p->save.cell);
    for (int i = 0; i < 6; i++) {
        if (!p->unk14c && p->motives[i].value <= 0 && p->unk1c[i] == 0) {
            if (func_02054dc4(data_020bfc9c,
                              func_0205f6f8(data_020c3fc4,
                                            func_0205d1b4(func_0205f6f8(data_020c3fc4, t[i].key), 0x798b86ac)),
                              0) == 0 ||
                t[i].kind != 0) {
                if (t[i].kind == 2) {
                    func_02007d94(&p->queue);
                }
                Unk02007340 *o = func_02007340(data_020be184, 0x17);
                if (o != 0) {
                    o->index = i;
                    o->kind = t[i].kind;
                    if (!(p->save.flags1da & t[i].mask)) {
                        o->key = t[i].key;
                    }
                    func_02007e48(&p->queue, o);
                    p->unk1c[i] = 0x708;
                }
            }
        }
        func_02067fb0(&p->motives[i]);
    }
    if (p->unk18 != 0) {
        p->unk18--;
    }
    for (int i = 0; i < 6; i++) {
        if (p->unk1c[i] != 0) {
            p->unk1c[i]--;
        }
    }
}

void func_0206622c(Unk020c43a8 *p) {
    if (p->save.flags1dc & 0x40) {
        func_02067fb0(&p->rels[0]);
    }
    if (p->save.flags1dc & 0x80) {
        func_02067fb0(&p->rels[1]);
    }
    if (p->save.flags1dc & 0x100) {
        func_02067fb0(&p->rels[2]);
    }
    if (p->save.flags1dc & 0x200) {
        func_02067fb0(&p->rels[3]);
    }
}

int func_02066298(Unk020c43a8 *p, int n) {
    int v = n * 100000;
    if (v > 10000000) {
        return 10000000;
    }
    if (v < -10000000) {
        v = -10000000;
    }
    return v;
}

void func_020662c8(Unk020c43a8 *p, int i, int n) {
    if (n == 0) {
        return;
    }
    int v = func_02066298(p, n);
    if (v < 0) {
        if (func_0206757c(p, 0x20)) {
            func_0206800c(&p->motives[i], -v);
        }
    } else {
        p->motives[i].func_00(v);
    }
}

void func_0206632c(Unk020c43a8 *p, int i, int n) {
    if (n == 0) {
        return;
    }
    int v = func_02066298(p, n);
    if (v < 0) {
        func_0206800c(&p->rels[i], -v);
    } else {
        p->rels[i].func_00(v);
    }
}

/* 99.9 %: the first loop ends with an unsigned compare (`blo`) in the
 * original, a signed one here although the counter is u32. */
void func_02066374(Unk020c43a8 *p, int row) {
    if (row == 1) {
        int v = func_02066298(p, 20);
        for (u32 i = 0; i < 6; i++) {
            if (p->motives[i].value < v) {
                p->motives[i].value = v;
            }
        }
        func_02067970(p);
        Unk020680d4 *sim = data_020c439c.sim;
        if (sim == 0) {
            return;
        }
        int anims[3] = {0x43, 0x44, 0x45};
        Unk02063d84 *a = func_02066704(p, anims[func_020a1f84(&data_020d62a4) % 3], false);
        if (a == 0) {
            return;
        }
        func_02069124(sim, a, 0, false);
        return;
    }
    for (int i = 0; i < 6; i++) {
        func_020662c8(p, i, p->table[row][i]);
    }
}

int func_0206647c(Unk020c43a8 *p, int i) {
    return p->motives[i].value;
}

Unk02064bf8 *func_02066488(Unk020c43a8 *p, int i) {
    return &p->rels[i];
}

Unk02064c24 *func_02066494(Unk020c43a8 *p, int i) {
    return &p->motives[i];
}

void func_020664a0(Unk020c43a8 *p, const u8 *name) {
    int i;
    for (i = 0; name[i] != 0; i++) {
        if (i >= 0x3f) {
            p->save.name[i] = 0;
            return;
        }
        p->save.name[i] = name[i];
    }
    for (; i < 0x40; i++) {
        p->save.name[i] = 0;
    }
}

/* 94.0 %: the original compares the home cell with the x / y values loaded
 * for the `>= 0` tests and keeps one more callee-saved register. */
bool func_02066518(Unk020c43a8 *p, const Unk020680d4Cell *cell) {
    if (p->func_14() == *cell) {
        return false;
    }
    if (func_02059418(&p->home) && p->home.xy.x >= 0 && p->home.xy.y >= 0 && p->home == *cell) {
        return false;
    }
    Unk02007340K00 *o = (Unk02007340K00 *)func_02007340(data_020be184, 0);
    if (o != 0) {
        o->func_set(*cell);
        func_02007e48(&p->queue, o);
        if (p->sim != 0) {
            func_020695f0(p->sim);
        }
        return true;
    }
    return false;
}

Unk02063d84 *func_02066704(Unk020c43a8 *p, u32 anim, bool loop) {
    Unk020680d4 *sim = p->sim;
    if (anim >= 0x4a) {
        anim = 10;
    }
    if (sim != 0) {
        return func_02063e2c(data_020af010[anim], loop ? 1 : 2);
    }
    return 0;
}

bool func_02066748(Unk020c43a8 *p, int anim, bool loop, int time, bool hide, int angle) {
    if (p->sim != 0) {
        p->sim->speed = 0x1000;
        func_02069124(p->sim, func_02066704(p, anim, loop), time, hide);
        if (angle != 0) {
            func_02069d4c(p->sim, angle, true);
        }
        return true;
    }
    return false;
}

void func_020667a8(Unk020c43a8 *p, int i) {
    if (i > -1 && i < 4) {
        func_020662c8(p, 1, p->unkf0[i]);
    }
}

int func_020667d4(Unk020c43a8 *p, int i) {
    if (i > -1 && i < 4) {
        return p->unkf0[i];
    }
    return 0;
}

void func_020667f8(Unk020c43a8 *p, int time) {
    if (p->unk38) {
        return;
    }
    int kind = func_0205803c(func_02058788(&data_020c3ba4, data_020c3ba4.map), &p->save.cell);
    int anim = 10;
    if (kind == 3) {
        anim = 12;
    } else if (kind == 2) {
        anim = 11;
    } else if (func_02067ec0(p)) {
        anim = 0x1a;
    }
    func_02066748(p, anim, true, time, false, 0);
}

/* 99.3 %: register allocation (`p` in r5, the idle pointer in r4). */
void func_02066884(Unk020c43a8 *p) {
    if (p->sim == 0) {
        return;
    }
    if (p->unk38) {
        return;
    }
    int kind = func_0205803c(func_02058788(&data_020c3ba4, data_020c3ba4.map), &p->save.cell);
    int anim = 10;
    if (kind == 3) {
        anim = 0x1f;
    } else if (kind == 2) {
        if (func_020a1f84(&data_020d62a4) % 100 < 25 && p->unka0.value > 7500000) {
            anim = 0x1b;
        } else {
            switch (func_020a1f84(&data_020d62a4) % 3) {
            case 0:
                anim = 0x1d;
                break;
            case 1:
                anim = 0x1c;
                break;
            case 2:
                anim = 0x1e;
                break;
            }
        }
    } else if (!func_02067ec0(p)) {
        int picked[14];
        bool done = false;
        if (p->obj == 0 && func_0206757c(p, 0x20) && func_020a1f84(&data_020d62a4) % 100 < 80) {
            int count = 0;
            for (int i = 0; i < 14; i++) {
                if (p->idles[i].motive != 6) {
                    int v = p->motives[p->idles[i].motive].value;
                    if (v >= (int)(10000000.0f * (p->idles[i].min / 100.0f)) && v <= (int)(10000000.0f * (p->idles[i].max / 100.0f))) {
                        picked[count++] = i;
                    }
                } else if (p->idles[i].rel != 4) {
                    int v = p->rels[p->idles[i].rel].value;
                    if (v >= (int)(10000000.0f * (p->idles[i].min / 100.0f)) && v <= (int)(10000000.0f * (p->idles[i].max / 100.0f))) {
                        picked[count++] = i;
                    }
                }
            }
            if (count > 0) {
                u32 k = func_020a1f84(&data_020d62a4) % count;
                Unk0201c460 *o = new Unk0201c460(p->idles[picked[k]].key);
                p->obj = o;
                p->obj->func_08();
                done = true;
                anim = p->idles[picked[k]].anim;
            }
        }
        if (!done) {
            if (func_020a1f84(&data_020d62a4) % 100 < 25) {
                if (p->unka0.value > 8500000) {
                    anim = 0x12;
                } else if (p->unka0.value > 7500000) {
                    anim = 0xf;
                } else if (p->unka0.value > 6000000) {
                    anim = 0x13;
                } else if (p->unka0.value > 2500000) {
                    anim = 0x18;
                } else {
                    switch (func_020a1f84(&data_020d62a4) % 3) {
                    case 0:
                        anim = 0x10;
                        break;
                    case 1:
                        anim = 0x11;
                        break;
                    case 2:
                        anim = 0x19;
                        break;
                    }
                }
            } else {
                switch (func_020a1f84(&data_020d62a4) % 5) {
                case 0:
                    anim = 0x14;
                    break;
                case 1:
                    anim = 0xd;
                    break;
                case 2:
                    anim = 0xe;
                    break;
                case 3:
                    anim = 0x16;
                    break;
                case 4:
                    anim = 0x17;
                    break;
                }
            }
        }
    } else if (p->unka0.value > 2500000) {
        anim = 0x1a;
    } else {
        switch (func_020a1f84(&data_020d62a4) % 3) {
        case 0:
            anim = 0x10;
            break;
        case 1:
            anim = 0x11;
            break;
        case 2:
            anim = 0x19;
            break;
        }
    }
    func_02066748(p, anim, false, 10, false, 0);
    p->timer = 0x400;
}

/* 99.7 %: the two database addresses are loaded into the other registers. */
void func_02066d1c(Unk020c43a8 *p) {
    p->save.unk160 = 0;
    for (int i = 0; i < 2; i++) {
        if (p->save.outfit.parts.v[i] != 0) {
            Unk020bfc9cItem *o = func_02054dc4(data_020bfc9c, func_0205f6f8(data_020c3fc4, p->save.outfit.parts.v[i]), 0);
            if (o != 0) {
                int v = o->unk8 - p->unk10;
                if (v < 0) {
                    v = 0;
                }
                o->unk8 = v;
                p->save.unk160 += 0xff - v;
            }
        }
    }
    p->save.unk160 >>= 1;
}

void Unk020c43a8::func_10(Unk020680d4Cell cell) {
    save.cell = cell;
    if (sim != 0) {
        sim->func_10(cell);
    }
}

void Unk020c43a8::func_00(Unk02098ff0 pos) {
    if (sim != 0) {
        sim->func_00(pos);
    }
}

void Unk020c43a8::func_08(Unk02098ff0 rot) {
    if (sim != 0) {
        sim->func_08(rot);
    }
}

Unk02098ff0 Unk020c43a8::func_04() {
    if (sim != 0) {
        return sim->func_04();
    }
    return Unk02098ff0(0, 0, 0);
}

Unk02098ff0 Unk020c43a8::func_0c() {
    if (sim != 0) {
        return sim->func_0c();
    }
    return Unk02098ff0(0, 0, 0);
}

/* 99.8 %: r0 / r1 are set in the other order before func_0209911c. */
Unk02098ff0 func_02066f14(Unk020c43a8 *p) {
    if (p->sim != 0) {
        Unk02098ff0 pos = p->sim->func_04().func_0209911c(Unk02098ff0(0, 0xb33, 0));
        if (p->queue.head == 0 || ((int *)p->queue.head)[6] == 0) {
            return pos;
        }
        int *o = (int *)func_02002438(((int *)p->queue.head)[6]);
        if (o == 0) {
            return pos;
        }
        if (o[0x11] == 0) {
            return pos;
        }
        (Unk020680d4Vec &)pos = (const Unk020680d4Vec &)pos.func_020991b8(func_020613a4(o[0x11]), 0xe66);
        return pos;
    }
    return Unk02098ff0(0, 0, 0);
}

void func_0206702c(Unk020c43a8 *p) {
    if (p->save.outfit.unk28 == 1) {
        func_020664a0(p, func_020a00a0(data_020d60c8.text, 0xc9e));
    } else {
        func_020664a0(p, func_020a00a0(data_020d60c8.text, 0xc9f));
    }
}

void func_0206708c(Unk020c43a8 *p, int kind, Unk020724cc *catalog) {
    bool own = catalog == 0;
    if (own) {
        catalog = new Unk020724cc(p);
    }
    catalog->func_02072a30(kind);
    if (own) {
        delete catalog;
    }
    func_0206702c(p);
}

void func_020670fc(Unk020c43a8 *p, Unk020081dc *outfit) {
    p->save.outfit = *outfit;
    if (p->sim == 0) {
        return;
    }
    func_020685e0(p->sim);
    func_020684f4(p->sim, outfit);
}

void func_02067160(Unk020c43a8 *p, int i, int v) {
    p->save.unk150[i] = v;
}

int func_0206716c(Unk020c43a8 *p, int i) {
    return p->save.unk150[i];
}

void func_02067178(Unk020c43a8 *p, int hash) {
    switch (hash) {
    case 0x11c6a6eb:
        p->save.flags1dc |= 0x1;
        break;
    case 0x05ee0c54:
        p->save.flags1dc |= 0x2;
        break;
    case 0xfbc8f754:
        p->save.flags1dc |= 0x4;
        break;
    case 0x35175e25:
        p->save.flags1dc |= 0x8;
        break;
    case 0x81281c6b:
        p->save.flags1dc |= 0x10;
        break;
    case 0xa1f6559e:
        p->save.flags1dc |= 0x20;
        break;
    case 0x0e2508ee:
        p->save.flags1dc |= 0x40;
        break;
    case 0x4089a7c6:
        p->save.flags1dc |= 0x80;
        break;
    case 0x61aadad6:
        p->save.flags1dc |= 0x100;
        break;
    case 0xaaba8051:
        p->save.flags1dc |= 0x200;
        break;
    case 0xce6c7716:
        p->save.flags1dc |= 0x400;
        break;
    case 0xb82e8cf1:
        p->save.flags1dc |= 0x800;
        break;
    }
}

bool func_02067364(Unk020c43a8 *p, int hash) {
    switch (hash) {
    case 0x11c6a6eb:
        return (p->save.flags1dc & 0x1) != 0;
    case 0x05ee0c54:
        return (p->save.flags1dc & 0x2) != 0;
    case 0xfbc8f754:
        return (p->save.flags1dc & 0x4) != 0;
    case 0x35175e25:
        return (p->save.flags1dc & 0x8) != 0;
    case 0x81281c6b:
        return (p->save.flags1dc & 0x10) != 0;
    case 0xa1f6559e:
        return (p->save.flags1dc & 0x20) != 0;
    case 0x0e2508ee:
        return (p->save.flags1dc & 0x40) != 0;
    case 0x4089a7c6:
        return (p->save.flags1dc & 0x80) != 0;
    case 0x61aadad6:
        return (p->save.flags1dc & 0x100) != 0;
    case 0xaaba8051:
        return (p->save.flags1dc & 0x200) != 0;
    case 0xb82e8cf1:
        return (p->save.flags1dc & 0x800) != 0;
    }
    return false;
}

void func_02067560(Unk020c43a8 *p, u32 n) {
    if (n <= p->save.unk1de) {
        return;
    }
    if (n <= 6) {
        p->save.unk1de = n;
    }
}

bool func_0206757c(Unk020c43a8 *p, int mask) {
    return (p->save.flags1dc & mask) != 0;
}

void func_02067594(Unk020c43a8 *p, Unk020a4dc4 *s) {
    for (int i = 0; i < 6; i++) {
        p->motives[i].func_04(s);
    }
    p->unka0.func_04(s);
    for (int i = 0; i < 4; i++) {
        p->rels[i].func_04(s);
    }
    func_020a4dc4(s, &p->save, sizeof(p->save));
}

void func_02067620(Unk020c43a8 *p, Unk020a4dc4 *s) {
    for (int i = 0; i < 6; i++) {
        p->motives[i].func_08(s);
    }
    p->unka0.func_08(s);
    for (int i = 0; i < 4; i++) {
        p->rels[i].func_08(s);
    }
    func_020a4e14(s, &p->save, sizeof(p->save));
    func_02065db8(p);
}

int func_020676b4(Unk020c43a8 *p) {
    if (p->bone != -1) {
        Unk0208be3cEntry *e = func_01ffa954(p->sim->xform, p->bone);
        if (e != 0) {
            return -e->mtx.func_020982a8().z;
        }
    }
    return 0;
}

int func_02067708(Unk020c43a8 *p, int a, int b) {
    int y = func_020a1e68(p->func_0c().y, a, b);
    p->func_08(Unk02098ff0(0, y, 0));
    return y;
}

void func_02067778(Unk020c43a8 *p, Unk020680d4Cell cell) {
    Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    Unk020680d4Cell here = p->func_14();
    int from = func_0205803c(map, &here);
    int to = func_0205803c(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    int anim;
    switch (from) {
    case 1:
    default:
        if (to == 1) {
            if (func_02067ec0(p)) {
                anim = 1;
            } else {
                anim = 0;
            }
        } else if (to == 2) {
            anim = 2;
        } else {
            anim = 7;
        }
        break;
    case 2:
        if (to == 1) {
            anim = 3;
        } else if (to == 2) {
            anim = 4;
        } else {
            anim = 5;
        }
        break;
    case 3:
        if (to == 1) {
            anim = 8;
        } else if (to == 2) {
            anim = 6;
        } else {
            anim = 9;
        }
        break;
    }
    func_02066748(p, anim, false, 10, false, 0);
}

int func_02067878(u32 hash) {
    int i = 6;
    switch ((int)hash) {
    case 0x55cac6c6:
        i = 0;
        break;
    case 0x48592bcd:
        i = 1;
        break;
    case 0x04d73112:
        i = 2;
        break;
    case 0x95afca12:
        i = 3;
        break;
    case 0xaf85c067:
        i = 4;
        break;
    case 0xe6849c7c:
        i = 5;
        break;
    }
    return i;
}

int func_0206790c(u32 hash) {
    int i = 4;
    switch ((int)hash) {
    case 0x0e2508ee:
        i = 0;
        break;
    case 0x4089a7c6:
        i = 1;
        break;
    case 0x61aadad6:
        i = 2;
        break;
    case 0xaaba8051:
        i = 3;
        break;
    }
    return i;
}

/* The key of the items searched by func_02067970. */
const u32 data_020af1a8[1] = {0xef816a84};

/* 91.2 %: the original enters the draw loop through a jump to its test (here
 * a test before the loop) and allocates the counters to other registers;
 * while / for forms and declaration orders gave the same code. */
void func_02067970(Unk020c43a8 *p) {
    Unk020a20f0 random;
    u8 *db = data_020bfc9c;
    func_020a20f0(&random);
    int limits[7] = {1, 2, 3, 4, 5, 5, 5};
    Unk020547f8 list;
    func_02054d94(db, &list, data_020af1a8, 1, 1);
    int total = 0;
    for (Unk020547f8Node *n = list.head; n != 0; n = n->next) {
        total += n->count;
    }
    if (limits[p->save.unk1de] <= total) {
        total = limits[p->save.unk1de];
    }
    int count = 0;
    Unk020c43a8Pick picked[5];
    for (int added = 0; added < total;) {
        int size = list.count;
        Unk020547f8Node *n = func_02054858(&list, func_020a1f84(&random) % size);
        int found = -1;
        for (int i = 0; i < count; i++) {
            if (picked[i].node == n) {
                found = i;
                break;
            }
        }
        if (found != -1) {
            Unk020c43a8Pick *e = &picked[found];
            if (n->count - e->count > 0) {
                e->count++;
                added++;
            }
        } else {
            picked[count].node = n;
            picked[count].count = 1;
            count++;
            added++;
        }
    }
    for (int i = 0; i < count; i++) {
        int n = picked[i].count;
        for (int j = 0; j < n; j++) {
            func_02054cf0(db, picked[i].node, 0);
        }
    }
    func_020a2ce8(func_020a2994(), 0x92526783, 0x7f, 0);
}

int func_02067b70() {
    switch (func_020a1f84(&data_020d62a4) % 3) {
    case 0:
        return 0x2f;
    case 1:
        return 0x30;
    default:
        return 0x31;
    }
}

/* 98.5 %: the original tests the three keys in the order 0xB0E8A958,
 * 0xED32B5E6, 0x18A7F0FA (the last one falling through to its case); no
 * order of the cases or if / else chain gave it. */
void func_02067bc4(Unk020c43a8 *p, const Unk0209674c *node, int index) {
    if (index >= 10) {
        return;
    }
    p->needs[index].motive = 6;
    for (int i = 0; i < node->func_020967ec(); i++) {
        Unk0209674c c = node->func_02096774(i);
        int hash = c.func_02096800();
        if (hash == 0x2fd6225b) {
            continue;
        }
        switch (hash) {
        case 0x18a7f0fa: {
            int m = func_02067878(c.func_020968d8());
            if (m != 6) {
                p->needs[index].motive = m;
            }
            break;
        }
        case 0xed32b5e6: {
            int v = c.func_020968a0();
            if (v >= 0 && v <= 100) {
                p->needs[index].level = v;
            }
            break;
        }
        case 0xb0e8a958:
            if (c.func_020968d8() == 0xd6398f1e) {
                p->needs[index].above = 1;
            }
            break;
        default: {
            int m = func_02067878(hash);
            if (m != 6) {
                p->needs[index].deltas[m] = c.func_020968a0();
            }
            break;
        }
        }
    }
}

void func_02067d0c(Unk020c43a8 *p, const Unk0209674c *node, int index) {
    if (index >= 14) {
        return;
    }
    p->idles[index].motive = 6;
    p->idles[index].rel = 4;
    for (int i = 0; i < node->func_020967ec(); i++) {
        Unk0209674c c = node->func_02096774(i);
        switch ((int)c.func_02096800()) {
        case 0x18a7f0fa: {
            u32 h = c.func_020968d8();
            int m = func_02067878(h);
            if (m != 6) {
                p->idles[index].motive = m;
            } else {
                int r = func_0206790c(h);
                if (r != 4) {
                    p->idles[index].rel = r;
                }
            }
            break;
        }
        case 0x0476de97: {
            int v = c.func_020968a0();
            if (v >= -100 && v <= 100) {
                p->idles[index].min = v;
            }
            break;
        }
        case 0x63863388: {
            int v = c.func_020968a0();
            if (v >= -100 && v <= 100) {
                p->idles[index].max = v;
            }
            break;
        }
        case 0xe2269ce9:
            p->idles[index].key = c.func_020968d8();
            break;
        case 0xc8f42062: {
            u32 h = c.func_020968d8();
            for (int k = 0; k < 0x4a; k++) {
                if (h == data_020af010[k]) {
                    p->idles[index].anim = k;
                    break;
                }
            }
            break;
        }
        }
    }
}

bool func_02067ec0(Unk020c43a8 *p) {
    if (!(func_020589ac(&data_020c3ba4, data_020c3ba4.map)->unk8 & 8) && data_020d60c8.mode->unk4 == 6 &&
        func_02059cf8(func_0206bce0()->unk214)) {
        int part = func_020081dc(p).parts.v[3];
        if (part == 0 || func_0205d340(func_0205f6f8(data_020c3fc4, part), 0x291d04a3)) {
            return true;
        }
    }
    return false;
}

Unk020680d4Dir Unk020c43a8::func_1c() {
    return sim->func_1c();
}

Unk020680d4Xy Unk020c43a8::func_20() {
    return Unk020680d4Xy(1, 1);
}

bool Unk020c43a8::func_24() {
    return true;
}

bool Unk020c43a8::func_28() {
    return true;
}

bool Unk020c43a8::func_2c(const Unk020680d4Cell &cell) {
    return false;
}

void func_02067fb0(Unk02064bf8 *c) {
    if (c->delay == 0) {
        c->value -= c->rate;
        c->func_0c();
    } else if (c->delay > 0) {
        c->delay--;
    }
}

void Unk02064bf8::func_00(int n) {
    value += n;
    func_0c();
}

void func_0206800c(Unk02064bf8 *c, int n) {
    c->value -= n;
    c->func_0c();
}

void Unk02064bf8::func_0c() {
    if (value < 0) {
        value = 0;
    } else if (value > 10000000) {
        value = 10000000;
    }
}

void Unk02064bf8::func_04(Unk020a4dc4 *s) {
    func_020a4dc4(s, &value, 4);
    func_020a4dc4(s, &rate, 4);
    func_020a4dc4(s, &delay, 4);
}

void Unk02064bf8::func_08(Unk020a4dc4 *s) {
    func_020a4e14(s, &value, 4);
    func_020a4e14(s, &rate, 4);
    func_020a4e14(s, &delay, 4);
}
