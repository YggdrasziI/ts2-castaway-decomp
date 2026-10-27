/*
 * Unit 0x02061D08-0x02063CD0: action handlers of the scene objects. Each one
 * takes the parameter node of a script step (Unk02099c0c: key / value pairs,
 * index of the next step at 4), reads the current action context
 * data_020c3cc8 (actor object, target, player) and returns the next step.
 * They test the cell in front of an object, queue actions of the object
 * kinds of data_020be184 on an object or on the player, start sim
 * animations, change the player's needs and play object scripts. The table
 * of the static initializer at 0x020AD318 (another file) registers them by
 * name hash.
 *
 * Bounds: hypothesis. The two vtables before this file's data
 * (0x020BC49C-0x020BC4DC) point to the code up to 0x02061D08; the played
 * animations of unit_02063CD0.cpp follow. func_02061edc and func_02062700
 * are the same code (two static copies, or a file boundary between them).
 * `.data` holds the "[PerformShakeTree]" string and the two keys searched by
 * func_02063af4. Real file name unknown.
 *
 * The functions keep C linkage: the table and other files call them by their
 * addresses.
 */

#include "game/unk_script.h"

typedef signed char s8;

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

struct Unk02061d08Xy {
    Unk02061d08Xy() {}
    Unk02061d08Xy(s16 x, s16 y) {
        this->x = x;
        this->y = y;
    }

    s16 x;
    s16 y;
};

/* A map cell. */
struct Unk02061d08Cell {
    Unk02061d08Cell() {
        xy.x = -1;
        xy.y = -1;
    }
    Unk02061d08Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    Unk02061d08Cell func_moved(Unk02061d08Xy d) const {
        return Unk02061d08Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk02061d08Xy xy;
};

/* A rotation (0 to 3). */
struct Unk02061d08Rot {
    Unk02061d08Rot() {}

    int value;
};

/* The definition of a scene object. */
struct Unk0205cf00 {
    s16 unk0;
    s16 unk2;
    u8 unk4[8];
    int unkc;
    Unk020956f8 *script;
};

/* A scene object. */
class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk02061d08Cell func_14();
    virtual void func_18();
    virtual Unk02061d08Rot func_1c();

    u8 list[0xc];
    u8 unk10[0x18];
    Unk0205cf00 *def;
    u8 unk2c[0x1c];
    Unk02061d08Item *next;
};

/* The player (data_020c43a8): its sim and action list. */
struct Unk02061d08Player {
    u8 unk0[0xc];
    void *sim;
    u8 unk10[0x3b8];
    u8 list[0xc];
    int unk3d4;
};

/* The action context (data_020c3cc8). */
struct Unk020c3cc8 {
    int unk0;
    Unk02061d08Item *actor;
    int unk8;
    Unk02061d08Item *target;
    Unk02061d08Player *player;
    int unk14;
    u8 result;
};

/* The world (data_020c3ba4). */
struct Unk02058788 {
    u8 unk0[0x24];
    int unk24;
};

struct Unk020c3ba4 {
    u8 unk0[0xfc];
    s8 map;
};

/* The owner of a parameter node. */
struct Unk02099c0cOwner {
    u8 unk0[0xc];
    struct {
        u8 unk0[0x24];
        int unk24;
    } *unkc;
};

/* The parameters of a script step (unit_02099C0C.cpp). */
class Unk02099c0c {
public:
    bool func_02099c0c(int *value, int key);
    int func_02099c58(int key);

    Unk02099c0cOwner *owner;
    u16 next;
    u16 unk6;
};

/* The script runner of an object (0x10 bytes). */
class Unk02099c78 {
public:
    void func_02099ce0(int key);

    u8 unk0[0x10];
};

class Unk02061d08Runner;
class Unk0205d6b8;

extern "C" {
void func_02061c04(Unk02061d08Runner *r, Unk02061d08Item *item);
void func_02061c34(Unk02061d08Runner *r);
void func_0205d6b8(Unk0205d6b8 *p, Unk02099c0c *node);
void func_0205d6dc(Unk0205d6b8 *p);
}

class Unk02061d08Runner {
public:
    Unk02061d08Runner(Unk02061d08Item *item) {
        func_02061c04(this, item);
    }
    ~Unk02061d08Runner() {
        func_02061c34(this);
    }

    Unk02099c78 vm;
};

/* The parameter reader of func_02062620 (0x18 bytes). */
class Unk0205d6b8 {
public:
    Unk0205d6b8(Unk02099c0c *node) {
        func_0205d6b8(this, node);
    }
    ~Unk0205d6b8() {
        func_0205d6dc(this);
    }

    u8 unk0[0x18];
};

/* A list of scene objects (constructor 0x0205F098, destructor 0x0205F0A8). */
class Unk0205f098;

extern "C" {
void func_0205f098(Unk0205f098 *list);
void func_0205f0a8(Unk0205f098 *list);
}

class Unk0205f098 {
public:
    Unk0205f098() {
        func_0205f098(this);
    }
    ~Unk0205f098() {
        func_0205f0a8(this);
    }

    Unk02061d08Item *head;
    int count;
};

/* A search over data_020bfc9c (constructor 0x020547F8). */
struct Unk020547f8Node {
    Unk0205cf00 *def;
    int unk4[2];
    Unk020547f8Node *next;
};

class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk020547f8Node *head;
    int unk4;
};

/* The main game state (unit_0206BCE0.cpp): only the functions used here. */
class Unk0206bcf0 {
public:
    void func_0206ef8c(int a);
    void func_0206f008(int a);
    void func_0206f084();
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
    void func_0206f5dc(bool on);
};

/* Objects of data_020be184 by kind. */
struct Unk02061d08Obj {
    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[4];
    int unk20;
};

struct Unk02061d08K06 {
    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[0x14];
    u16 flags;
    u8 unk32[2];
    Unk02061d08Item *item;
    int unk38;
    int unk3c;
    int unk40;
};

struct Unk02061d08K07 {
    void func_set(int key, Unk02061d08Rot rot, u8 a, u8 b, s8 c, s8 d) {
        unk20 = key;
        this->rot = rot;
        unk24 = a;
        unk25 = b;
        unk27 = c;
        unk28 = d;
    }

    u8 unk0[0x20];
    int unk20;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    s8 unk27;
    s8 unk28;
    u8 unk29[3];
    Unk02061d08Rot rot;
};

struct Unk02061d08K08 {
    void func_set(int key, int id, int v, int c, int d, int e, int f, int g, u8 h, u8 x, u8 y) {
        unk30 = key;
        unk34 = id;
        unk20 = v;
        unk38 = c;
        unk3c = d;
        unk40 = e;
        unk44 = f;
        unk48 = g;
        unk4e = h;
        unk4c = x;
        unk4d = y;
        unk50 = 1;
    }

    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[4];
    int unk20;
    u8 unk24[0xc];
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
    u8 unk4c;
    u8 unk4d;
    u8 unk4e;
    u8 unk4f;
    int unk50;
};

struct Unk02061d08K0e {
    void func_set(Unk02061d08Cell c, Unk02061d08Rot rot, int key, int value, int unk40, int unk44) {
        cell = c;
        this->rot = rot;
        this->key = key;
        this->value = value;
        unk38 = 1;
        this->unk40 = unk40;
        this->unk44 = unk44;
    }

    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[6];
    Unk02061d08Cell cell;
    Unk02061d08Rot rot;
    int key;
    int value;
    u8 unk38;
    u8 unk39[7];
    int unk40;
    int unk44;
    u8 unk48;
    u8 unk49;
};

struct Unk02061d08K16 {
    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[4];
    int unk20;
    u8 unk24[0xc];
    int unk30;
};

/* A need counter of the player (value at 4). */
struct Unk02066488 {
    int unk0;
    int value;
};

class Unk02063d84;

extern Unk020c3cc8 data_020c3cc8;
extern Unk020c3ba4 data_020c3ba4;
extern Unk02061d08Player data_020c43a8;
extern u8 data_020be184[];
extern u8 data_020c4770[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020bfc9c[];
extern u8 data_020bfc68[];

extern "C" {
Unk0206bcf0 *func_0206bce0();
Unk02058788 *func_02058788(Unk020c3ba4 *world, int index);
bool func_02057ed8(Unk02058788 *map, const Unk02061d08Cell *cell);
Unk02061d08Xy func_020619a8(Unk02061d08Item *item, Unk02061d08Xy size, Unk02061d08Rot rot);
Unk02061d08Item *func_0205c5e0(Unk02099c0c *node);
void *func_02007340(void *p, int kind);
void *func_02007c98(void *p, int kind, int b);
void func_02007e48(void *list, void *o);
void func_02007e10(void *p);
void func_02007ea4(void *list, void *o);
void func_02007d94(void *list);
void func_02007f84(void *list, void *o, int a);
void func_020012ec(void *o, Unk02061d08Item *item, int a, int b);
int func_0205d340(Unk0205cf00 *def, u32 key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
Unk02061d08Item *func_0205fb4c(void *list, int key, Unk0205f098 *out, int a);
Unk02061d08Item *func_0205fae8(void *list, Unk0205cf00 *def, Unk0205f098 *out);
void func_020064e0(void *o, int a, int b, int c, int d);
void func_02006754(void *o, s16 a, s16 b, int c, int d);
void func_02006c6c(void *o);
int func_0205d704(Unk0205d6b8 *p);
int func_0205d6fc(Unk0205d6b8 *p, int a);
void func_020662c8(Unk02061d08Player *p, int a, int b);
int func_02067878(int a);
int func_0206647c(Unk02061d08Player *p, int index);
int func_0205b0d0(int a, int b);
void func_0206632c(Unk02061d08Player *p, int need, int b);
Unk02066488 *func_02066488(Unk02061d08Player *p, int need);
void func_02067160(Unk02061d08Player *p, int need, int b);
void func_0200323c(void *o, int a);
void func_0200324c(void *o, int a, int b);
void func_02065a60(Unk02061d08Player *p, int a, bool b);
Unk02063d84 *func_02063e2c(u32 key, int mode);
void func_02063db8(Unk02063d84 *a, int loop);
void func_02069124(void *sim, Unk02063d84 *anim, int time, bool hide);
int func_0205f6a4(void *db, int id);
Unk0205cf00 *func_0205f6f8(void *db, int id);
int func_0205465c(void *p, Unk0205cf00 *def, int a);
void func_02000ce0(void *o, int id, int a, int b);
void func_020098d0(void *o, Unk02061d08Item *item, int a, int b, int c, int d, int e);
void func_02009978(void *o, int a);
void func_02009980(void *o, int a);
void func_020897b4(const char *fmt, ...);
struct Unk02054dc4 {
    int unk0;
    int count;
};
Unk02054dc4 *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_02054cb4(void *p, int id, int a);
void func_0200264c(void *o);
void func_02054d94(void *p, Unk020547f8 *out, const int *keys, int n, int a);

u16 func_02061d08(Unk02099c0c *node);
u16 func_02061e00(Unk02099c0c *node);
u16 func_02061e90(Unk02099c0c *node);
int func_02061edc(int key);
u16 func_02061f38(Unk02099c0c *node);
u16 func_0206207c(Unk02099c0c *node);
u16 func_02062104(Unk02099c0c *node);
u16 func_02062120(Unk02099c0c *node);
u16 func_02062138(Unk02099c0c *node);
u16 func_02062154(Unk02099c0c *node);
u16 func_02062184(Unk02099c0c *node);
u16 func_020621a0(Unk02099c0c *node);
u16 func_020621d0(Unk02099c0c *node);
u16 func_020622a4(Unk02099c0c *node);
u16 func_020623bc(Unk02099c0c *node);
u16 func_0206241c(Unk02099c0c *node);
u16 func_02062438(Unk02099c0c *node);
u16 func_020624a8(Unk02099c0c *node);
u16 func_020624c4(Unk02099c0c *node);
u16 func_02062620(Unk02099c0c *node);
u16 func_0206267c(Unk02099c0c *node);
int func_02062700(int key);
u16 func_0206275c(Unk02099c0c *node);
u16 func_020627ac(Unk02099c0c *node);
u16 func_02062814(Unk02099c0c *node);
u16 func_02062864(Unk02099c0c *node);
u16 func_0206297c(Unk02099c0c *node);
u16 func_020629fc(Unk02099c0c *node);
u16 func_02062a48(Unk02099c0c *node);
u16 func_02062b34(Unk02099c0c *node);
u16 func_02062c58(Unk02099c0c *node);
u16 func_02062d20(Unk02099c0c *node);
u16 func_02062e54(Unk02099c0c *node);
u16 func_02062f00(Unk02099c0c *node);
u16 func_0206302c(Unk02099c0c *node);
u16 func_0206308c(Unk02099c0c *node);
u16 func_020630f8(Unk02099c0c *node);
void func_020632ec(Unk02099c0c *node, int key, int dir, int id, u8 a, u8 b, s8 c, s8 d);
u16 func_0206344c(Unk02099c0c *node);
u16 func_02063590(Unk02099c0c *node);
u16 func_020637f0(Unk02099c0c *node);
u16 func_02063934(Unk02099c0c *node);
int func_02063af4();
u16 func_02063b60(Unk02099c0c *node);
u16 func_02063b94(Unk02099c0c *node);
}

static inline bool func_isItem(int id) {
    return func_0205f6a4(data_020c3fc4, id) != -1;
}

static inline bool func_isItemIn(u8 *db, int id) {
    return func_0205f6a4(db, id) != -1;
}

/* The cell in front of an object (the one its size and rotation point to). */
static inline Unk02061d08Cell func_front(Unk02061d08Item *item) {
    return item->func_14().func_moved(
        func_020619a8(item, Unk02061d08Xy(item->def->unk0, item->def->unk2), item->func_1c()));
}

static inline bool func_isFree(Unk02061d08Cell *cell) {
    return func_02057ed8(func_02058788(&data_020c3ba4, data_020c3ba4.map), cell);
}

/* Queues an object action on the target and the player. */
static inline void func_queue(Unk02061d08Obj *o) {
    o->unk20 = data_020c3cc8.unk0;
    func_02007e48(data_020c3cc8.target->list, o);
    func_02007e48(data_020c3cc8.player->list, o->unk18);
}

u16 func_02061d08(Unk02099c0c *node) {
    Unk02061d08Cell to = func_front(data_020c3cc8.actor);
    data_020c3cc8.result = func_isFree(&to);
    return node->next;
}

u16 func_02061e00(Unk02099c0c *node) {
    int v = 0;
    node->func_02099c0c(&v, 0xcb28f2e3);
    func_02007e10(data_020c4770);
    void *o = func_02007340(data_020be184, 0x19);
    if (o != 0) {
        Unk02061d08Item *item = func_0205c5e0(node);
        func_020012ec(o, item, v, func_02058788(&data_020c3ba4, data_020c3ba4.map)->unk24);
        func_02007e48(data_020c4770, o);
    }
    return node->next;
}

u16 func_02061e90(Unk02099c0c *node) {
    int v = node->func_02099c58(0xfb17602f);
    Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007340(data_020be184, 0x1f);
    if (o == 0) {
        return node->next;
    }
    o->unk20 = v;
    func_02007ea4(data_020c4770, o);
    return node->next;
}

int func_02061edc(int key) {
    int dir = 0;
    switch (key) {
    case 0x0e2508ee:
        dir = 0;
        break;
    case 0x4089a7c6:
        dir = 1;
        break;
    case 0x61aadad6:
        dir = 2;
        break;
    case (int)0xaaba8051:
        dir = 3;
        break;
    }
    return dir;
}

u16 func_02061f38(Unk02099c0c *node) {
    if (data_020c3cc8.actor != 0 && func_0205d340(data_020c3cc8.actor->def, 0x0d933e26) && data_020c3cc8.unk8 != 0) {
        Unk02061d08Cell to = func_front(data_020c3cc8.actor);
        data_020c3cc8.result = func_isFree(&to);
        return node->next;
    }
    data_020c3cc8.result = 0;
    return node->next;
}

u16 func_0206207c(Unk02099c0c *node) {
    int v = node->func_02099c58(0x0d933e26);
    Unk02061d08K16 *o = (Unk02061d08K16 *)func_02007c98(data_020be184, 0x16, 2);
    if (o != 0 && data_020c3cc8.target != 0) {
        int dir = func_02061edc(v);
        o->unk20 = data_020c3cc8.unk0;
        o->unk30 = dir;
        func_02007e48(data_020c3cc8.target->list, o);
        func_02007e48(data_020c3cc8.player->list, o->unk18);
    }
    return node->next;
}

u16 func_02062104(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_02062120(Unk02099c0c *node) {
    func_0206bce0()->func_0206f084();
    return node->next;
}

u16 func_02062138(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_02062154(Unk02099c0c *node) {
    func_02007d94(data_020c4770);
    func_0206bce0()->func_0206ef8c((int)data_020c3cc8.target);
    return node->next;
}

u16 func_02062184(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_020621a0(Unk02099c0c *node) {
    func_02007d94(data_020c4770);
    func_0206bce0()->func_0206f008((int)data_020c3cc8.target);
    return node->next;
}

u16 func_020621d0(Unk02099c0c *node) {
    int key = 0;
    if (node->func_02099c0c(&key, 0xfdec430b)) {
        int script = 0;
        if (node->func_02099c0c(&script, 0x67f8d0e1)) {
            Unk0205f098 list;
            for (Unk02061d08Item *item = func_0205fb4c(data_020c3fd4, key, &list, -1); item != 0;) {
                Unk02061d08Runner runner(item);
                if (item->def->script->func_020957ec(script)) {
                    runner.vm.func_02099ce0(script);
                }
                item = item->next;
            }
        }
    }
    return node->next;
}

u16 func_020622a4(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0) {
        Unk02061d08Cell to = func_front(item);
        data_020c3cc8.result = func_isFree(&to);
        return node->next;
    }
    data_020c3cc8.result = 0;
    return node->next;
}

u16 func_020623bc(Unk02099c0c *node) {
    Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0x12, 2);
    if (o != 0) {
        func_queue(o);
    }
    return node->next;
}

u16 func_0206241c(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_02062438(Unk02099c0c *node) {
    int a = node->func_02099c58(0xd5fa5227);
    int b = node->func_02099c58(0xe6884a5d);
    void *o = func_02007340(data_020be184, 0x14);
    if (o != 0) {
        func_020064e0(o, -1, 3, a, b);
        func_02007e48(data_020c4770, o);
    }
    return node->next;
}

u16 func_020624a8(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_020624c4(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return node->next;
    }
    int a = node->func_02099c58(0xd5fa5227);
    int b = node->func_02099c58(0xe6884a5d);
    int id;
    if (node->func_02099c0c(&id, 0xd3084047)) {
        id = item->def->script->func_0209599c(id);
    } else {
        id = data_020c3cc8.unk0;
    }
    Unk02061d08K06 *o = (Unk02061d08K06 *)func_02007c98(data_020be184, 6, 2);
    if (o != 0) {
        func_02006754(o, id, 3, a, b);
        o->item = item;
        o->flags |= 0x40;
        int v;
        if ((v = node->func_02099c58(0xf89be826)) != 0) {
            o->unk38 = v;
        }
        if ((v = node->func_02099c58(0xbf6ec11d)) != 0) {
            o->unk3c = v;
        }
        if ((v = node->func_02099c58(0x6e48cc6d)) != 0) {
            o->unk40 = v;
        }
        if (node->func_02099c58(0x66805f84) != 0) {
            func_02006c6c(o);
        }
        func_02007e48(item->list, o);
        func_02007e48(data_020c4770, o->unk18);
    }
    return node->next;
}

u16 func_02062620(Unk02099c0c *node) {
    Unk0205d6b8 p(node);
    int a = func_0205d704(&p);
    func_020662c8(&data_020c43a8, a, func_0205d6fc(&p, a));
    return node->next;
}

u16 func_0206267c(Unk02099c0c *node) {
    int a = node->func_02099c58(0x18a7f0fa);
    int b = node->func_02099c58(0x7e5d2b3f);
    if (a != 0 && func_02067878(a) != 6) {
        return func_0205b0d0(func_0206647c(&data_020c43a8, 1) / 100000, b);
    }
    return node->next;
}

int func_02062700(int key) {
    int dir = 0;
    switch (key) {
    case 0x0e2508ee:
        dir = 0;
        break;
    case 0x4089a7c6:
        dir = 1;
        break;
    case 0x61aadad6:
        dir = 2;
        break;
    case (int)0xaaba8051:
        dir = 3;
        break;
    }
    return dir;
}

u16 func_0206275c(Unk02099c0c *node) {
    int need = node->func_02099c58(0x0d933e26);
    int b = node->func_02099c58(0x7e5d2b3f);
    func_0206632c(&data_020c43a8, func_02062700(need), b);
    return node->next;
}

u16 func_020627ac(Unk02099c0c *node) {
    int need = node->func_02099c58(0x0d933e26);
    int b = node->func_02099c58(0x7e5d2b3f);
    return func_0205b0d0(func_02066488(&data_020c43a8, func_02062700(need))->value, (b + 100) * 50000);
}

u16 func_02062814(Unk02099c0c *node) {
    int need = node->func_02099c58(0x0d933e26);
    int b = node->func_02099c58(0xfb17602f);
    func_02067160(&data_020c43a8, func_02062700(need), b);
    return node->next;
}

u16 func_02062864(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0) {
        Unk02061d08Cell to = func_front(item);
        data_020c3cc8.result = func_isFree(&to);
        return node->next;
    }
    data_020c3cc8.result = 0;
    return node->next;
}

u16 func_0206297c(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    int v;
    if (item != 0 && node->func_02099c0c(&v, 0x1eb09665)) {
        Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0x18, 2);
        if (o != 0) {
            func_0200323c(o, v);
            func_02007e48(item->list, o);
            func_02007e48(data_020c4770, o->unk18);
        }
    }
    return node->next;
}

u16 func_020629fc(Unk02099c0c *node) {
    int a = node->func_02099c58(0xe97ebfa5);
    func_02065a60(&data_020c43a8, a, node->func_02099c58(0x81502345) != 0);
    return node->next;
}

u16 func_02062a48(Unk02099c0c *node) {
    int anim;
    void *sim = data_020c43a8.sim;
    anim = node->func_02099c58(0xc8f42062);
    int loop = 0;
    int time = 0;
    int flag = 0;
    node->func_02099c0c(&loop, 0x7c4cd0f0);
    node->func_02099c0c(&time, 0x1eee55a1);
    if (node->func_02099c0c(&flag, 0xdb3bc91f)) {
        func_0206bce0()->func_0206f5dc(flag != 0);
    }
    if (sim != 0 && anim != 0) {
        Unk02063d84 *a = func_02063e2c(anim, 0);
        if (a != 0) {
            func_02063db8(a, loop != 0);
            func_02069124(sim, a, time, false);
        }
    }
    return node->next;
}

u16 func_02062b34(Unk02099c0c *node) {
    int id = node->func_02099c58(0xdb82c7bb);
    int flag = 0;
    if (node->func_02099c0c(&flag, 0xdb3bc91f)) {
        func_0206bce0()->func_0206f5dc(flag != 0);
    }
    if (func_isItem(id)) {
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, id);
        int n = 0;
        node->func_02099c0c(&n, 0x3b7ba692);
        if (func_0205465c(data_020bfc68, def, n != 1)) {
            def = func_0205f6f8(data_020c3fc4, func_0205d1b4(def, 0x798b86ac));
            if (n != 0) {
                func_0206bce0()->func_0206f3e8(def, 1, 1, 1);
            }
        }
    }
    return node->next;
}

u16 func_02062c58(Unk02099c0c *node) {
    int id = node->func_02099c58(0xdb82c7bb);
    if (func_isItem(id)) {
        int a = 0;
        int b = 0;
        node->func_02099c0c(&a, 0x3b7ba692);
        node->func_02099c0c(&b, 0xef72c56c);
        void *o = func_02007340(data_020be184, 0x1e);
        if (o != 0) {
            func_02000ce0(o, id, a, b);
            func_02007f84(data_020c4770, o, data_020c43a8.unk3d4);
        }
    }
    return node->next;
}

u16 func_02062d20(Unk02099c0c *node) {
    int a = node->func_02099c58(0x6d71c18d);
    int b = node->func_02099c58(0xb2fcebc8);
    int c = node->func_02099c58(0x32ba0b69);
    int d = node->func_02099c58(0x8c75aba3);
    int e = node->func_02099c58(0x8e032298);
    int f = node->func_02099c58(0xb2b663fb);
    int g = node->func_02099c58(0x7285597c);
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0) {
        Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0x15, 2);
        if (o == 0) {
            return node->next;
        }
        func_020098d0(o, item, a, b, c, f, g);
        func_02009978(o, d);
        func_02009980(o, e);
        o->unk20 = data_020c3cc8.unk0;
        func_02007e48(item->list, o);
        func_02007e48(data_020c4770, o->unk18);
    }
    return node->next;
}

u16 func_02062e54(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    int a;
    int b;
    if (item != 0 && node->func_02099c0c(&a, 0xf7d71823) && node->func_02099c0c(&b, 0xf4c84997)) {
        Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0x18, 2);
        if (o != 0) {
            func_02007d94(data_020c4770);
            func_0200324c(o, a, b);
            func_02007e48(item->list, o);
            func_02007e48(data_020c4770, o->unk18);
        }
    }
    return node->next;
}

u16 func_02062f00(Unk02099c0c *node) {
    if (data_020c3cc8.unk8 != 0) {
        Unk02061d08Cell to = func_front(data_020c3cc8.actor);
        if (!func_isFree(&to)) {
            data_020c3cc8.result = 0;
            return node->next;
        }
    }
    data_020c3cc8.result = 1;
    return node->next;
}

u16 func_0206302c(Unk02099c0c *node) {
    Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0xa, 2);
    if (o != 0) {
        func_queue(o);
    }
    return node->next;
}

u16 func_0206308c(Unk02099c0c *node) {
    func_020897b4("[PerformShakeTree]");
    Unk02061d08Obj *o = (Unk02061d08Obj *)func_02007c98(data_020be184, 0xd, 2);
    if (o != 0) {
        func_queue(o);
    }
    return node->next;
}

u16 func_020630f8(Unk02099c0c *node) {
    if (data_020c3cc8.unk8 != 0) {
        Unk02061d08Cell to = func_front(data_020c3cc8.actor);
        if (!func_isFree(&to)) {
            data_020c3cc8.result = 0;
            return node->next;
        }
    }
    int id = node->func_02099c58(0x35c7a149);
    if (id != 0) {
        if (!func_isItem(id)) {
            data_020c3cc8.result = 0;
            return node->next;
        }
        Unk02054dc4 *e = func_02054dc4(data_020bfc9c, func_0205f6f8(data_020c3fc4, id), 0);
        if (e != 0 && e->count > 0) {
            data_020c3cc8.result = 1;
            return node->next;
        }
        data_020c3cc8.result = 0;
        return node->next;
    }
    data_020c3cc8.result = 1;
    return node->next;
}

void func_020632ec(Unk02099c0c *node, int key, int dir, int id, u8 a, u8 b, s8 c, s8 d) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return;
    }
    Unk02061d08Rot rot = item->func_1c();
    if (dir != 0) {
        switch (dir) {
        case (int)0xd82a09e8:
            rot.value = 0;
            break;
        case (int)0xfa6fc214:
            rot.value = 1;
            break;
        case 0x30a71683:
            rot.value = 2;
            break;
        case 0x1202d214:
            rot.value = 3;
            break;
        }
    }
    Unk02061d08K07 *o = (Unk02061d08K07 *)func_02007340(data_020be184, 7);
    if (o == 0) {
        return;
    }
    o->func_set(key, rot, a, b, c, d);
    func_02007e48(item->list, o);
    if (id == 0) {
        return;
    }
    if (!func_isItem(id)) {
        return;
    }
    func_02054cb4(data_020bfc9c, id, 0);
}

u16 func_0206344c(Unk02099c0c *node) {
    int key = node->func_02099c58(0x6ab6646f);
    int id = node->func_02099c58(0xbe39b00d);
    int dir = node->func_02099c58(0x272910bb);
    bool a = node->func_02099c58(0x0999564b) != 0;
    bool b = node->func_02099c58(0xd1aed813) != 0;
    int c;
    if (!node->func_02099c0c(&c, 0x58)) {
        c = -1;
    }
    int d;
    if (!node->func_02099c0c(&d, 0x59)) {
        d = -1;
    }
    if (key == (int)0x884a5a82) {
        key = node->owner->unkc->unk24;
    }
    bool ok = true;
    if (key != 0) {
        ok = func_isItem(key);
    }
    if (ok) {
        func_020632ec(node, key, dir, id, a, b, c, d);
    }
    return node->next;
}

u16 func_02063590(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return node->next;
    }
    int key = node->func_02099c58(0x6ab6646f);
    int id = node->func_02099c58(0xbe39b00d);
    int c = node->func_02099c58(0x272910bb);
    int s = node->func_02099c58(0xd283d63c);
    int d = node->func_02099c58(0xbbb0caef);
    int e = node->func_02099c58(0xab28bc00);
    int f = node->func_02099c58(0xae9ed90e);
    int g = node->func_02099c58(0xe5466c12);
    bool h = node->func_02099c58(0x0999564b) != 0;
    int x;
    if (!node->func_02099c0c(&x, 0x58)) {
        x = -1;
    }
    int y;
    if (!node->func_02099c0c(&y, 0x59)) {
        y = -1;
    }
    u8 *db = data_020c3fc4;
    if (key != 0 && !func_isItemIn(db, key)) {
        return node->next;
    }
    if (id != 0 && !func_isItemIn(db, id)) {
        id = 0;
    }
    Unk02061d08K08 *o = (Unk02061d08K08 *)func_02007c98(data_020be184, 8, 2);
    if (o != 0) {
        int v;
        if (s == 0) {
            v = data_020c3cc8.unk0;
        } else {
            v = item->def->script->func_0209599c(s);
        }
        o->func_set(key, id, v, c, d, e, f, g, h, x, y);
        int z;
        if (node->func_02099c0c(&z, 0x3074c4)) {
            func_0200264c(o);
        }
        func_02007e48(item->list, o);
        func_02007e48(data_020c4770, o->unk18);
    }
    return node->next;
}

u16 func_020637f0(Unk02099c0c *node) {
    int key = node->func_02099c58(0x6ab6646f);
    int id = node->func_02099c58(0xc5448de6);
    if (!func_isItem(key)) {
        return node->next;
    }
    Unk0205f098 list;
    for (Unk02061d08Item *item = func_0205fae8(data_020c3fd4, func_0205f6f8(data_020c3fc4, id), &list); item != 0;
         item = item->next) {
        Unk02061d08K07 *o = (Unk02061d08K07 *)func_02007340(data_020be184, 7);
        if (o == 0) {
            return node->next;
        }
        o->func_set(key, item->func_1c(), 0, 0, -1, -1);
        func_02007e48(item->list, o);
    }
    return node->next;
}

u16 func_02063934(Unk02099c0c *node) {
    int id = 0;
    if (node->func_02099c0c(&id, 0x1e1a6a8c) && func_isItem(id)) {
        int anim = 0;
        if (node->func_02099c0c(&anim, 0xc8f42062)) {
            Unk02061d08K0e *o = (Unk02061d08K0e *)func_02007c98(data_020be184, 0xe, 2);
            if (o == 0) {
                data_020c3cc8.result = 0;
                return node->next;
            }
            int value = node->func_02099c58(0x67f8d0e1);
            o->func_set(data_020c3cc8.target->func_14(), data_020c3cc8.target->func_1c(), id, anim,
                        data_020c3cc8.unk0, value);
            int v;
            if (node->func_02099c0c(&v, 0xb954c92c)) {
                o->unk49 = 0;
            }
            func_02007e48(data_020c3cc8.target->list, o);
            func_02007e48(data_020c3cc8.player->list, o->unk18);
        }
    }
    return node->next;
}

int func_02063af4() {
    static int data_020bc4f0[2] = {(int)0xe03edad9, 0x51a12c57};
    Unk020547f8 list;
    func_02054d94(data_020bfc9c, &list, data_020bc4f0, 2, 2);
    if (list.unk4 != 0) {
        return list.head->def->unkc;
    }
    return 0;
}

u16 func_02063b60(Unk02099c0c *node) {
    if (func_02063af4()) {
        data_020c3cc8.result = 1;
    } else {
        data_020c3cc8.result = 0;
    }
    return node->next;
}

u16 func_02063b94(Unk02099c0c *node) {
    int key = func_02063af4();
    if (key != 0) {
        Unk02061d08K0e *o = (Unk02061d08K0e *)func_02007c98(data_020be184, 0xe, 2);
        if (o == 0) {
            data_020c3cc8.result = 0;
            return node->next;
        }
        int value = node->func_02099c58(0x67f8d0e1);
        o->func_set(data_020c3cc8.target->func_14(), data_020c3cc8.target->func_1c(), key, 0x490ed6f1,
                    data_020c3cc8.unk0, value);
        func_02007e48(data_020c3cc8.target->list, o);
        func_02007e48(data_020c3cc8.player->list, o->unk18);
    }
    return node->next;
}
