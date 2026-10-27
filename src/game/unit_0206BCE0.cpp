/*
 * Unit 0x0206BCE0-0x0206FAC8: Unk0206bcf0, a game state (base Unk0206fab0,
 * include/game/unk_catalog.h, id 6), with the getter of its single instance
 * (data_020c4780, set by the constructor and cleared by the destructor).
 * func_02071e04 sets the screens up and builds the state's objects,
 * func_02072224 releases them.
 *
 * Bounds: hypothesis. The constructor at 0x0206BCF0 is the only code that loads
 * the first copy of the base vtable (0x020BC8FC), and the inline base
 * destructors 0x0206FAB0 / 0x0206FAB4 end the range, just before
 * unit_0206FAC8.cpp: one file, as mwccarm emits the weak functions after the
 * file's own. 0x0206BCE0 (the instance getter) is the first function using the
 * instance; the functions before it are called from here but use none of this
 * file's data, so the start is the least sure bound. `.data`: the strings
 * 0x020BC88C-0x020BC8E0 (used from 0x0206E9FC on), the vtable with its header
 * and the first copy of the base vtable (to 0x020BC918). `.bss`: the instance
 * pointer. Real file name unknown.
 *
 * Not complete: every function is written; the ones below 100 % carry a
 * comment with the remaining difference.
 */

#include "game/unk_catalog.h"
#include "game/unk_pool.h"
#include "game/unk_texture.h"
#include "game/unk_oam.h"
#include "game/unk_script.h"
#include "game/unk_vector.h"
#include "game/unk_palset.h"
#include "game/unk_camera.h"
#include "game/unk_queue.h"
#include "game/unk_sortedset.h"
#include "game/unk_icon.h"

typedef signed char s8;

/* One entry of the list given to func_0201b964 (the pie menu items). */
struct Unk0201b964Entry {
    int textId;
    int unk4;
    s8 unk8;
};

/* The pie menu (unit_0201B6D4.cpp): only the functions used here. */
class Unk0201b6d4 {
public:
    void func_0201b964(const Unk0201b964Entry *entries, u32 n, u32 enabledMask);
    int func_0201c198();
    int func_0201c208();
    void func_0201c2c4(int x, int y);

    bool func_busy() const {
        return (flags & 8) || (flags & 4) || (flags & 2);
    }

    u8 unk0[0x140];
    u32 flags;
    u8 unk144[4];
    int selected;
    u16 unk14c;
};


struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc;
    Unk0201b6d4 *menu;
};

/* The save data (data_020d60c8.save). */
struct Unk020a4c4c {
    u8 unk0[0xc];
    int unkc;
    u32 flags;
};

/* A block header of the save data. */
struct Unk020a4c60 {
    u32 magic;
    int size;
    int version;
};

/* The game settings (data_020d60c8): fields used here. */
struct Unk020d60c8 {
    Unk020a4c4c *save;
    Unk0206b630 *unk4;
    u8 unk8[0x134];
    int unk13c;
    u8 unk140[0x1c];
    u8 unk15c;
};

/* The clock (data_020d6298). */
struct Unk020d6298 {
    int func_hour() const {
        return (unk4 & 0x7c0) >> 6;
    }

    int unk0;
    u32 unk4;
};

struct Unk0206bcf0Point {
    Unk0206bcf0Point() {}

    int x;
    int y;
};

/* A ray from the camera through the touched point (position, direction). */
/* Only the implicit assignment of a struct holding the vector gives the
 * original block copies (ldm / stm); the casts to it are a workaround. */
struct Unk0206bcf0RayVec {
    Unk0206bcf0RayVec() {}

    Unk02098ff0 v;
};

struct Unk0206bcf0Ray {
    Unk0206bcf0RayVec pos;
    Unk0206bcf0RayVec dir;
};

/* The time read by func_0202071c. */
struct Unk0202071c {
    Unk0202071c() {}

    int func_hour() const {
        return (value & 0x7c0) >> 6;
    }

    u32 value;
};

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    bool operator==(Unk020593e4 o) const {
        return unk3 == o.unk3 && unk2 == o.unk2 && unk0 == o.unk0;
    }

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

struct Unk0206bcf0Xy {
    Unk0206bcf0Xy() {}
    Unk0206bcf0Xy(s16 x, s16 y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(Unk0206bcf0Xy o) const {
        return x == o.x && y == o.y;
    }

    s16 x;
    s16 y;
};

/* A map cell: its tile coordinates are -1 when it is not set. */
struct Unk0206bcf0Cell {
    Unk0206bcf0Cell() {
        xy.x = -1;
        xy.y = -1;
    }
    Unk0206bcf0Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    bool operator==(Unk0206bcf0Cell o) const {
        return pos == o.pos && xy == o.xy;
    }

    Unk0206bcf0Cell func_moved(Unk0206bcf0Xy d) const {
        return Unk0206bcf0Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk0206bcf0Xy xy;
};

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
};

/* The tile layer returned by func_02056ed0. */
struct Unk02056ed0 {
    int unk0;
    int unk4;
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;

    u32 *func_tile(int x, int y) {
        return &tiles[y * info->width + x];
    }
};

/* A map of the world (func_02058788). */
struct Unk02058788 {
    u8 unk0[0x24];
    int unk24;
};

struct Unk020589ac {
    s8 unk0;
    s8 unk1[3];
    u32 unk4;
    u32 unk8;
};

/* The world (data_020c3ba4). */
struct Unk020c3ba4 {
    int unk0;
    u8 unk4[0xf8];
    s8 map;
    Unk0206fac8 *palettes;
};

/* The definition of a scene object. */
struct Unk0205cf00 {
    s16 unk0;
    s16 unk2;
    u8 unk4[8];
    int unkc;
    Unk020956f8 *script;
};

/* A rotation, returned by Unk0206bcf0Item::func_1c. */
struct Unk0206bcf0Rot {
    Unk0206bcf0Rot() {}

    int value;
};

/* A scene object. */
class Unk0206bcf0Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual Unk02098ff0 func_0c();
    virtual void func_10();
    virtual Unk0206bcf0Cell func_14();
    virtual void func_18();
    virtual Unk0206bcf0Rot func_1c();

    u8 unk4[0xc];
    int unk10;
    u32 flags;
    u8 unk18[0x10];
    Unk0205cf00 *def;
    int unk2c;
    u8 unk30[0x18];
    Unk0206bcf0Item *next;
};

/* A node of the list returned by func_0205fd7c. */
struct Unk0205fd7c {
    u8 unk0[4];
    u8 unk4[0x3c];
    Unk0205fd7c *next;
};

/* A list of scene objects (constructor 0x0205F098, destructor 0x0205F0A8). */
struct Unk0205f098 {
    Unk0206bcf0Item *head;
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



class Unk020c43a8 {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10(Unk0206bcf0Cell cell);
    virtual Unk0206bcf0Cell func_14();

    u8 unk4[8];
    void *unkc;
    u8 unk10[0x3b8];
    u8 unk3c8[0xc];
    int unk3d4;
};

/* The windows owned by the state, deleted through their vtable. */
class Unk0206bcf0Obj {
public:
    virtual ~Unk0206bcf0Obj();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual void func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual void func_2c();
    virtual bool func_30();
};

/* The 0x1280-byte window at 0x11C. */
class Unk0201e300 : public Unk0206bcf0Obj {
public:
    Unk0201e300();

    u32 flags;
    u8 unk8[0x1270];
    u8 unk1278;
    u8 unk1279[7];
};

class Unk02027994 : public Unk0206bcf0Obj {
public:
    Unk02027994(int type);

    u8 unk4[0x62c];
};

class Unk0202402c : public Unk0206bcf0Obj {
public:
    Unk0202402c();

    u8 unk4[0x53e0];
    int unk53e4;
};

class Unk020238ec : public Unk0206bcf0Obj {
public:
    Unk020238ec();

    u8 unk4[0xb4];
    int unkb8;
};

class Unk0201dd90 : public Unk0206bcf0Obj {
public:
    Unk0201dd90();

    u8 unk4[0x29e4];
};

class Unk02027044 : public Unk0206bcf0Obj {
public:
    Unk02027044();

    u8 unk4[0x640];
};

class Unk02044234 : public Unk0206bcf0Obj {
public:
    Unk02044234(int a);

    u8 unk4[0x228];
};

/* data_020bfc3c: the ambient sound player. */
struct Unk020bfc3c {
    u8 unk0[0xc];
    u8 unkc;
    u8 unkd[0x17];
    int unk24;
};

struct Unk020c4770Obj {
    int unk0;
    u32 flags;
};

/* data_020c4770: a list of objects. */
struct Unk020c4770 {
    bool func_busy() const {
        return unkc->flags & 0x40;
    }

    u8 unk0[0xc];
    Unk020c4770Obj *unkc;
};

/* The object returned by func_020a0b68. */
class Unk020a0b68 {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
};

class Unk02055118 {
public:
    Unk02055118();
    ~Unk02055118();

    int unk0;
    u8 unk4[0x14];
};

class Unk02058eb8 {
public:
    Unk02058eb8();
    ~Unk02058eb8();

    u8 unk0[0x54];
};

class Unk020599a0 {
public:
    Unk020599a0();
    ~Unk020599a0();

    u8 unk0[0xa1c];
};

class Unk020717b8 {
public:
    Unk020717b8(u32 count);
    ~Unk020717b8();
    void func_020718c0(const Unk02098ff0 &pos, const u32 *attr);
    void func_02071a60();

    u8 unk0[0x18];
};

/* A Mersenne Twister state. */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

/* Objects of data_020be184 (func_02007340, func_02007c98). */
struct Unk02007340 {
    u8 unk0[0x44];
    u8 unk44;
};

/* The kinds of objects of data_020be184 created by func_0206e424. */
struct Unk02007340K0c {
    void func_set(Unk0206bcf0Cell c, Unk02058eb8 *p) {
        cell = c;
        unk28 = p;
    }

    u8 unk0[0x20];
    Unk0206bcf0Cell cell;
    Unk02058eb8 *unk28;
};

struct Unk02007340K06 {
    u8 unk0[0x30];
    u16 flags;
    u8 unk32[0x12];
    Unk0206bcf0Cell cell;
};

struct Unk02007340K0e {
    void func_set(Unk0206bcf0Cell c, int type, int key, int value) {
        cell = c;
        this->type = type;
        this->key = key;
        this->value = value;
    }

    u8 unk0[0x22];
    Unk0206bcf0Cell cell;
    int type;
    int key;
    int value;
    u8 unk38;
    u8 unk39[7];
    int unk40;
    int unk44;
};

struct Unk02007340K11 {
    void func_set(Unk0206bcf0Cell c) {
        cell = c;
    }

    u8 unk0[0x24];
    int unk24;
    u8 unk28[8];
    int unk30;
    int unk34;
    int unk38;
    u8 unk3c[8];
    Unk0206bcf0Cell cell;
};

struct Unk02007c98 {
    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[0xc];
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
};

class Unk0208a0a8 {
public:
    void func_0208aae0();
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern Unk020d6298 data_020d6298;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020bfc9c[];
extern u8 data_020c4390[];
extern u8 data_020c40cc[];
extern u8 data_020c409c[];
extern u8 data_020c3fd4[];
extern u8 data_020c3fc4[];
extern u8 data_020be184[];
extern Unk020c4770 data_020c4770;
extern Unk020bfc3c data_020bfc3c;
extern u8 data_020bfc68[];
extern u8 data_020bfc80[];
extern Unk0208a0a8 *data_020c7d24;

void func_02096dac(int a, int b, int c, int d, int e, int f);
void func_02097a38();
bool func_02097298(int button);
int *func_02097a4c();

class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbe8();
    static Unk0208db14 *func_0208dbf8();
    void func_0208e4ec();
};

class Unk0206bcf0;

extern "C" {
Unk0206bcf0 *func_0206bce0();
void func_0206c290(Unk020d6240 *system);
void *func_0206c2a4(Unk020d6240 *system);
Unk020d6240 *func_020a18e4();
void func_020a18f0(void *p);
void func_020a0cd8(Unk020d6240 *system);
void func_020a0f0c(Unk020d6240 *system);
void func_020a1070();
void func_020a10a8();
void func_020a1138(Unk020d6240 *system, int a, int b);
Unk020a0b68 *func_020a0b68(void *p);
void func_020a07f8(void *p, int a);
void *func_020a2994();
void func_020a28ec(void *sound);
void func_0209f880(Unk020d60c8 *settings, int a);
void func_02064270(void *p);
void func_020642cc(void *p);
void func_02064ca0(void *p);
void func_0206061c(void *p);
void func_02060b24(void *p);
void func_02060b98(void *p);
void func_02058380(void *p);
void func_02058688(void *p);
void func_0205f934(void *p);
void func_0205f844(void *p);
void func_0205f9e4(void *p);
void func_0205f7f8(void *p);
void func_0205285c(void *p);
void func_020528b4(void *p);
void func_02054360(void *p);
void func_02054a70(void *p);
void func_02055198(Unk02055118 *p);
void func_02007204(void *p);
void func_0200726c(void *p);
int func_020543d4(void *p);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int index);
Unk020589ac *func_020589ac(Unk020c3ba4 *world, int index);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk0206bcf0Cell *cell);
bool func_0205809c(Unk02058788 *map, Unk0206bcf0Cell *cell, Unk0206bcf0Ray *ray);
bool func_02057f90(Unk02058788 *map, const Unk0206bcf0Cell *cell);
bool func_02057ed8(Unk02058788 *map, const Unk0206bcf0Cell *cell);
bool func_02059418(const Unk0206bcf0Cell *cell);
bool func_0206757c(Unk020c43a8 *p, int mask);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_02054d94(void *p, Unk020547f8 *out, int *key, int a, int b);
Unk0205cf00 *func_0205f6f8(void *db, u32 key);
void func_0205f10c(Unk0205f098 *list, Unk0206bcf0Item **out, int count);
Unk0206bcf0Item *func_0205fb4c(void *list, u32 key, Unk0205f098 *ctx, int a);
void func_0205f098(Unk0205f098 *ctx);
void func_0205f0a8(Unk0205f098 *ctx);
int func_0205cf00(Unk0205cf00 *def, int index);
int func_0205d134(Unk0205cf00 *def, u32 key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
int func_0205d340(Unk0205cf00 *def, u32 key);
bool func_0205e00c(Unk0206bcf0Item *item, int index, Unk020c43a8 *p);
bool func_0205ec0c(Unk0206bcf0Item *item);
Unk02007340 *func_02007340(void *p, int a);
Unk02007c98 *func_02007c98(void *p, int a, int b);
void func_02007e48(void *list, void *o);
bool func_02005654(Unk02007340 *o, Unk0206bcf0Cell cell, int kind, int v);
bool func_02066518(Unk020c43a8 *p, Unk0206bcf0Cell *cell);
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
Unk02098ff0 func_02057b5c(Unk02058788 *map, const Unk0206bcf0Cell *cell);
Unk0206bcf0Item *func_0205fbf4(void *list, int id);
int func_0205465c(void *p, Unk0205cf00 *def, int a);
void func_02028eec(Unk0206bcf0Obj *o, int a, Unk0205cf00 *def, Unk0206bcf0Item *item);
void func_0205ece8(Unk0206bcf0Item *item, u32 key);
void func_0205cfd4(Unk0205cf00 *def, int index, Unk0206bcf0Item *item, Unk020c43a8 *p);
Unk0206bcf0Xy func_020619a8(Unk0206bcf0Item *item, Unk0206bcf0Xy size, Unk0206bcf0Rot rot);
void func_020a20f0(Unk020a20f0 *random);
u32 func_020a1f84(Unk020a20f0 *random);
int func_0209a3c4(u32 hash, const char *str);
u32 func_0209a32c(const char *str, u32 last, u32 end);
u32 func_02059cf8(Unk020599a0 *p);
void func_020529b4(Unk020bfc3c *p, u32 key, int a);
void func_02052974(Unk020bfc3c *p, int id, int a);
void func_02052a00(Unk020bfc3c *p, int a);
void func_02066d1c(Unk020c43a8 *p);
void func_02007d94(Unk020c4770 *list);
void func_02029128(Unk0206bcf0Obj *o, int a);
int func_0205803c(Unk02058788 *map, Unk0206bcf0Cell *cell);
void func_02028ec8(Unk0206bcf0Obj *o, int a, int b);
bool func_020a1524(Unk0206bcf0Obj *o);
void func_0205ff28(void *list, u32 key);
void func_0205fea0(void *list, u32 key);
void func_02059224(Unk02058eb8 *p);
void func_020a4c4c(Unk020a4c4c *save);
bool func_020a5cb0();
void func_020a10dc(Unk020d6240 *system, int dt);
void func_020a15a8(Unk020d6240 *system, int dt);
void func_020553dc(Unk02055118 *p);
void func_020559cc(Unk02055118 *p);
void func_02055220(Unk02055118 *p, int a, int b);
void func_02065b80(Unk020c43a8 *p, int dt);
bool func_020a0744(void *input, int index);
bool func_020a075c(void *input, int index);
bool func_020a078c(void *input, int index);
Unk0206bcf0Point func_020a07bc(void *input, int index);
void func_02065eb8(Unk020c43a8 *p);
void func_0206622c(Unk020c43a8 *p);
int func_02007dec(void *list);
void func_0206b30c(Unk02069fec *p, int a, int b);
void func_0206b4c8(Unk02069fec *p);
void func_0206af98(Unk02069fec *p, int mode);
bool func_020693d8(void *p, Unk0206bcf0Ray *ray);
void func_0205fa30(void *list, Unk0206bcf0Ray ray, Unk0205f098 *out);
void func_0205f998(void *list);
void func_02060cdc(void *p);
void func_0205899c(Unk020c3ba4 *world);
void func_02052e8c(Unk020bfc3c *p);
bool func_020a14d8(Unk020d6240 *system);
Unk0202071c func_0202071c(Unk020d6298 *clock);
bool func_020a19cc(Unk020d6298 *clock, int step);
void func_020a194c(Unk020d6298 *clock, int step);
void func_02059cb0(Unk020599a0 *p, bool on);
void func_02059d10(Unk020599a0 *p, bool on);
void func_01ff9924(Unk020c7d38 *pool);
void func_01ff9dbc(Unk020c7d38 *pool);
void func_0207c224();
void func_01ffadf8(Unk020916a4 *manager);
void func_02053100(Unk020bfc3c *p);
Unk0205fd7c *func_0205fd7c(void *list, int map);
void func_0205e4d0(Unk0205fd7c *node);
void func_0205e3f0(Unk0205fd7c *node);
void func_02007e10(void *p);
void func_02007e38(void *p);
void func_0205fde4(void *list);
void func_02065e80(Unk020c43a8 *p);
void func_0205a548(Unk020599a0 *p);
void func_02056c7c(void *p);
void func_020585a0(Unk020c3ba4 *world, int map);
void func_01ffaac4(Unk020c7f48 *m);
bool func_020573a4(void *layers, Unk0206bcf0Cell *cell, int old);
void func_020577a4(void *layers, Unk0206bcf0Cell *cell);
void func_020667f8(Unk020c43a8 *p, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
void func_02058cd8(Unk020c3ba4 *world, int map, int a);
void func_02001318(void *o, Unk0206bcf0Item *item, int a, int map, int b, int y, int c, int d);
void func_0205a484(Unk020599a0 *p);
void func_02059c10(Unk020599a0 *p, bool on);
void func_02006754(void *o, s16 a, s16 b, u32 key, int c);
int func_0206647c(Unk020c43a8 *p, int index);
int func_020667d4(Unk020c43a8 *p, int index);
int func_02067b70(Unk020c43a8 *p);
int func_02077b3c(int a, int b);
void func_020a4d78(Unk020a4c4c *save, int a);
void func_020a4d2c(Unk020a4c4c *save, int a);
Unk020a4c60 *func_020a4c60(Unk020a4c4c *save, int size, int a);
Unk020a4c60 *func_020a4ce0(Unk020a4c4c *save, int size);
void func_020a1994(Unk020d6298 *clock, Unk020a4c4c *save);
void func_020a19b0(Unk020d6298 *clock, Unk020a4c4c *save);
void func_0205501c(void *p, Unk020a4c4c *save);
void func_0205507c(void *p, Unk020a4c4c *save);
void func_02054b30(void *p);
void func_02054ab4(void *p);
void func_02058ce8(Unk020c3ba4 *world, Unk020a4c4c *save);
void func_02058dd4(Unk020c3ba4 *world, Unk020a4c4c *save);
void func_0205ffa4(void *p, Unk020a4c4c *save);
void func_02060080(void *p, Unk020a4c4c *save);
void func_02067594(Unk020c43a8 *p, Unk020a4c4c *save);
void func_02067620(Unk020c43a8 *p, Unk020a4c4c *save);
void func_02064cdc(Unk020c43a8 *p);
void func_0205a5c8(Unk020599a0 *p, Unk020a4c4c *save);
void func_0205a6cc(Unk020599a0 *p, Unk020a4c4c *save);
void func_02020978(Unk0201e300 *p);
void func_02020fb8(Unk0201e300 *p);
void func_0206a120(Unk02069fec *p);
void *func_02058518(Unk020c3ba4 *world, int a, int b);
void func_02056b80(void *p);
void func_020585e0(Unk020c3ba4 *world, int a);
void func_02065db8(Unk020c43a8 *p);
void *func_0206cfa8(Unk020d6240 *system);
int func_0206cfb8(Unk0206bcf0 *state);
void func_0207a748();
bool func_01ff9ee8(Unk020c7d38 *pool);
}

class Unk0206bcf0 : public Unk0206fab0 {
public:
    Unk0206bcf0();
    ~Unk0206bcf0();
    void func_02071e04();
    void func_02072224();
    void func_02071fdc(int dt);
    int func_0206cfcc(Unk0205f098 *list, bool extra);
    void func_0206d0ec(Unk0206bcf0Point *pt, Unk0206bcf0Ray *ray);
    void func_0206d3dc(u32 *tile, int *n);
    bool func_0206d630(Unk0206bcf0Item *item);
    bool func_0206d6dc();
    void func_0206d858(Unk0206bcf0Point *pt, Unk0206bcf0Item *item);
    void func_0206d9c4(Unk0206bcf0Ray ray);
    void func_0206da24(Unk0206bcf0Cell *cell);
    void func_0206dd24();
    void func_0206ddb4();
    void func_0206df74();
    void func_0206dfdc();
    void func_0206e104(int v);
    bool func_0206e134(Unk0206bcf0Item *item);
    bool func_0206e240(Unk0206bcf0Item *item);
    void func_0206e40c();
    void func_0206e424();
    void func_0206ea00(int a, int b);
    void func_0206ef04(int map);
    void func_0206ef8c(int a);
    void func_0206f008(int a);
    void func_0206f084();
    void func_0206f0d8();
    bool func_0206f0ec(int type, int b, int c);
    bool func_0206f258(int a);
    void func_0206f340();
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
    bool func_0206f4e4(u32 key);
    void func_0206f548(bool on);
    void func_0206f560(bool on);
    void func_0206f578(bool on);
    void func_0206f5dc(bool on);
    void func_0206f5f4();
    void func_0206f610();
    void func_0206f62c();
    void func_0206f654();
    void func_0206f67c();
    void func_0206f6d0();
    void func_0206f6fc();
    void func_0206f7e4();
    void func_0206f96c();
    void func_0206fa30();

    Unk0206b8cc *unkc;
    Unk02069fec unk10;
    Unk0201e300 *unk11c;
    Unk0206bcf0Point unk120;
    Unk0206bcf0Ray unk128;
    Unk0206bcf0Obj *unk140;
    Unk0206bcf0Obj *unk144;
    Unk0206bcf0Obj *unk148;
    Unk02055118 unk14c;
    Unk0206bcf0Obj *unk164;
    Unk0206bcf0Obj *unk168;
    Unk0206bcf0Obj *unk16c;
    Unk0206b4d4 *unk170;
    Unk0201b964Entry entries[12];
    Unk0206bcf0Cell unk204;
    int unk20c;
    Unk02058eb8 *unk210;
    Unk020599a0 *unk214;
    Unk020717b8 *unk218;
    Unk0206bcf0Obj *unk21c;
    u8 unk220;
    u8 unk221;
    int unk224;
    int unk228;
    int unk22c;

    bool func_isPaused() const {
        return unk22c & 1;
    }

};

static Unk0206bcf0 *data_020c4780;

#define DELETE(p)  \
    if (p != 0) {  \
        delete p;  \
        p = 0;     \
    }

static inline int func_index(int x, int y, u32 w) {
    return y * w + x;
}

static inline u32 *func_tileAt(Unk02056ed0 *l, const Unk0206bcf0Xy &p) {
    return &l->tiles[func_index(p.x, p.y, l->info->width)];
}

static inline bool func_isPlaced(const Unk0206bcf0Cell &c) {
    return func_02059418(&c) && c.xy.x >= 0 && c.xy.y >= 0;
}

static inline bool func_isWater(u32 tile) {
    bool w = true;
    u32 k = tile & 0xc000;
    if (k != 0x4000 && k != 0xc000) {
        w = false;
    }
    return w;
}

static inline bool func_owns(void *db, Unk0205cf00 *def) {
    return func_02054dc4(db, def, 0) != 0;
}

static inline bool func_has(void *db, u32 key) {
    return func_02054dc4(db, func_0205f6f8(data_020c3fc4, key), 0) != 0;
}

static inline bool func_isSetA(int id) {
    bool r = false;
    u32 i = id - 7;
    if (i <= 0x16 && (0x600801 & (1 << i))) {
        r = true;
    }
    return r;
}

static inline bool func_isSetB(int id) {
    bool r = false;
    u32 i = id - 0x27;
    if (i <= 0x1b && (0xa30c303 & (1 << i))) {
        r = true;
    }
    return r;
}

static inline bool func_isKept(int id) {
    bool r = true;
    if (!func_isSetA(id) && !func_isSetB(id)) {
        r = false;
    }
    return r;
}

Unk0206bcf0 *func_0206bce0() {
    return data_020c4780;
}

Unk0206bcf0::Unk0206bcf0()
    : Unk0206fab0(6), unkc(0), unk140(0), unk144(0), unk148(0), unk164(0), unk168(0), unk16c(0),
      unk170(0), unk20c(0), unk214(0), unk218(0), unk21c(0), unk220(1),
      unk221(0), unk224(0), unk228(0), unk22c(0) {
    data_020c4780 = this;
}

Unk0206bcf0::~Unk0206bcf0() {
    data_020c4780 = 0;
}

void Unk0206bcf0::func_02071e04() {
    func_02096dac(7, 0x20, 0x40, 0x180, 0x10, 8);
    func_0205f934(data_020c3fd4);
    func_0205f844(data_020c3fd4);
    func_020a18f0(&data_020d6298);
    unk210 = new Unk02058eb8;
    unk214 = new Unk020599a0;
    func_020a0cd8(&data_020d6240);
    func_020a1138(func_020a18e4(), 2, 1);
    unk170 = new Unk0206b4d4;
    unk11c = new Unk0201e300;
    unk11c->func_08();
    unkc = new Unk0206b8cc(0x14);
    func_020a1070();
    func_02064270(data_020c4390);
    func_0206061c(data_020c409c);
    func_02007204(data_020be184);
    func_02060b24(data_020c40cc);
    func_02058380(&data_020c3ba4);
    unk218 = new Unk020717b8(5);
    func_020a28ec(func_020a2994());
    func_0205285c(&data_020bfc3c);
    func_0209f880(&data_020d60c8, data_020d60c8.unk13c);
    unk224 = 0;
    unk228 = 0;
    func_02097a38();
    unk22c = 0x80;
}

void Unk0206bcf0::func_02072224() {
    Unk020c7d38 *pool = &data_020c7d38;
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    void *list = func_0206c2a4(func_020a18e4());
    while (func_020a0b68(list) != 0) {
        func_020a0b68(list)->func_18();
        func_020a07f8(list, 1);
    }
    func_02055198(&unk14c);
    func_02054a70(data_020bfc80);
    func_0206ea00(-1, 0);
    DELETE(unk214);
    DELETE(unk170);
    DELETE(unk210);
    DELETE(unkc);
    DELETE(unk218);
    func_02064ca0(&data_020c43a8);
    func_0205f9e4(data_020c3fd4);
    func_0200726c(data_020be184);
    func_02058688(&data_020c3ba4);
    func_0205f934(data_020c3fd4);
    func_0205f844(data_020c3fd4);
    func_020642cc(data_020c4390);
    func_020528b4(&data_020bfc3c);
    func_02054360(data_020bfc68);
    func_02060b98(data_020c40cc);
    data_020c7d38.func_0208b9dc();
    func_020a10a8();
    DELETE(unk11c);
    DELETE(unk140);
    DELETE(unk168);
    DELETE(unk16c);
    DELETE(unk148);
    func_0206c290(func_020a18e4());
    unk22c = 0;
    func_0205f7f8(data_020c3fc4);
    data_020c7d24->func_0208aae0();
    func_0208c578()->func_0208ca24();
    Unk020916a4::func_02091820()->func_02091d58();
    Unk020916a4::func_02091830()->func_02091d58();
}

void func_0206c290(Unk020d6240 *system) {
    func_020a0f0c(&data_020d6240);
}

void *func_0206c2a4(Unk020d6240 *system) {
    return data_020d6240.unk8;
}

/*
 * 99.39 %: the touched point's stack slot comes below the two clock reads (it is
 * above them in the original), and the pie menu and the touch flag swap r5 / r6.
 */
void Unk0206bcf0::func_02071fdc(int dt) {
    if ((unk144 != 0 || unk21c != 0 || unk16c != 0 || unk140 != 0 || func_020a5cb0()) && dt == 0) {
        return;
    }
    Unk020c7d38 *pool;
    Unk020d6240 *system;
    Unk0201b6d4 *menu;
    Unk020c43a8 *p;
    int touched;
    void *input;
    pool = &data_020c7d38;
    system = func_020a18e4();
    input = data_020d6240.input;
    menu = data_020d6240.menu;
    p = &data_020c43a8;
    touched = 0;
    func_020a10dc(system, dt);
    unk170->func_0206b5e4();
    if (unk164 != 0) {
        if (unk22c & 0x20) {
            if ((unk144 != 0 && func_020a1524(unk144)) || (unk144 == 0 && func_020a1524(unk11c))) {
                unk164->func_08();
                unk22c &= ~0x20;
            }
        } else if (func_020a1524(unk164)) {
            if (unk144 == 0) {
                unk11c->func_08();
            }
            delete unk164;
            unk164 = 0;
            func_0206f560(false);
            func_0206f578(false);
            func_0206f548(false);
            func_02097a38();
        }
    }
    if (unk148 != 0) {
        if (unk22c & 0x100) {
            if (func_020a1524(unk11c)) {
                unk11c->flags &= ~8;
                unk148->func_08();
                unk22c &= ~0x100;
            }
        } else if (func_020a1524(unk148)) {
            delete unk148;
            unk148 = 0;
            func_0206f578(false);
            func_0206f548(false);
            func_02097a38();
            if (next == 0) {
                unk11c->func_08();
            }
        }
    }
    if (unk21c != 0) {
        if (unk22c & 0x200) {
            if (func_020a1524(unk11c)) {
                unk21c->func_08();
                unk22c &= ~0x200;
            }
        } else if (func_020a1524(unk21c)) {
            func_0206f548(false);
            delete unk21c;
            unk21c = 0;
            unk11c->flags &= ~0x10;
            unk11c->func_08();
        }
    }
    if (!func_isPaused()) {
        if (unk144 != 0) {
            if (unk22c & 0x10) {
                if (func_020a1524(unk11c)) {
                    unk144->func_08();
                    unk22c &= ~0x10;
                }
            } else {
                if (dt) {
                    func_020553dc(&unk14c);
                }
                if (func_020a1524(unk144)) {
                    unk11c->func_08();
                    if (unk14c.unk0 == 0) {
                        func_02055198(&unk14c);
                        delete unk144;
                        unk144 = 0;
                        func_0206f560(false);
                        func_0206f578(false);
                        func_02097a38();
                    } else if (!func_isKept(unk14c.unk0)) {
                        func_020559cc(&unk14c);
                    }
                }
            }
        }
        if (unk140 != 0) {
            if (dt) {
                func_020553dc(&unk14c);
            }
            if (unk22c & 0x40) {
                if (func_020a1524(unk11c)) {
                    unk140->func_08();
                    unk22c &= ~0x40;
                }
            } else if (func_020a1524(unk140)) {
                unk11c->func_08();
                if (unk14c.unk0 == 0) {
                    delete unk140;
                    unk140 = 0;
                    func_0206f578(false);
                    func_0206f560(false);
                    func_02097a38();
                } else if (!func_isKept(unk14c.unk0)) {
                    func_020559cc(&unk14c);
                }
            }
        }
        if (unk16c != 0) {
            if (dt) {
                func_020553dc(&unk14c);
            }
            if (unk22c & 0x800) {
                if (func_020a1524(unk11c)) {
                    unk16c->func_08();
                    unk22c &= ~0x800;
                }
            } else if (func_020a1524(unk16c)) {
                unk11c->func_08();
                if (unk14c.unk0 == 0) {
                    delete unk16c;
                    unk16c = 0;
                    func_0206f578(false);
                    func_0206f560(false);
                    func_02097a38();
                } else if (!func_isKept(unk14c.unk0)) {
                    func_02055220(&unk14c, 0, 0);
                    func_020559cc(&unk14c);
                }
            }
        }
        func_02065b80(p, dt);
        if (func_020a0744(func_0206cfa8(func_020a18e4()), 6) && !(unk22c & 0x2000)) {
            func_0206f258(0);
        }
        if (!(unk22c & 2) && !(unk22c & 8)) {
            func_02065eb8(p);
            func_0206622c(p);
        }
        if (!(unk22c & 4) && !(unk22c & 8) && !(unk11c->flags & 4) && func_02007dec(&p->unk3c8) < 4) {
            if (func_0206cfb8(this)) {
                touched |= 1;
            }
            if (func_020a078c(input, 1)) {
                func_0206b30c(&unk10, 0, 0);
            }
            if (!(touched & 1) && func_020a075c(input, 1)) {
                Unk0206bcf0Point pt;
                pt = func_020a07bc(input, 1);
                unk120 = pt;
                int *screen = func_02097a4c();
                Unk020899a4 *camera = (Unk020899a4 *)&data_020c7d38.unk54;
                Unk02098ff0 dir = camera->func_02089cac(screen[0] << 12, screen[1] << 12);
                dir.func_02099048(0xa000);
                unk128.pos = (const Unk0206bcf0RayVec &)camera->pos;
                unk128.dir = (const Unk0206bcf0RayVec &)dir;
                bool hit = false;
                if (p->unkc != 0 && func_020693d8(p->unkc, &unk128)) {
                    hit = true;
                }
                Unk0205f098 list;
                func_0205f098(&list);
                func_0205fa30(data_020c3fd4, unk128, &list);
                func_0206dd24();
                if (list.count != 0) {
                    if (!hit && list.count == 1) {
                        func_0206d858(&unk120, list.head);
                    } else if (func_0206cfcc(&list, hit && func_0206d6dc()) == 1) {
                        if (hit) {
                            func_0206dd24();
                        } else {
                            int id = entries[0].unk4;
                            func_0206dd24();
                            if (id != 0) {
                                Unk0206bcf0Item *item = func_0205fbf4(data_020c3fd4, id);
                                if (item != 0) {
                                    func_0206d858(&unk120, item);
                                }
                            }
                        }
                    }
                }
                if (unk20c == 0) {
                    if (hit) {
                        func_0206d0ec(&unk120, &unk128);
                    } else {
                        func_0206d9c4(unk128);
                    }
                }
                func_0205f0a8(&list);
            }
            if (!menu->func_busy()) {
                if (menu->unk14c & 8) {
                    func_0206b4c8(&unk10);
                    bool ok = menu->selected >= 0 && menu->selected < 10;
                    if (ok) {
                        switch (unk20c) {
                        case 1:
                            func_0206ddb4();
                            break;
                        case 2:
                            func_0206df74();
                            break;
                        case 3:
                            func_0206dfdc();
                            break;
                        case 4:
                            func_0206e40c();
                            break;
                        }
                    } else {
                        unk20c = 0;
                    }
                    func_02097a38();
                }
            } else {
                func_0206b30c(&unk10, 0, 0);
            }
            if (func_02097298(2)) {
                func_0206f0ec(0, 1, 0);
            }
            if ((data_020d60c8.unk15c && func_02097298(6)) || (!data_020d60c8.unk15c && func_02097298(10))) {
                func_0206f0ec(4, 1, 0);
            }
        }
        if (!(unk22c & 4)) {
            unkc->func_0206bae4();
        }
        func_0205f998(data_020c3fd4);
        func_02060cdc(data_020c40cc);
        func_0205899c(&data_020c3ba4);
        func_0205fde4(data_020c3fd4);
        func_02052e8c(&data_020bfc3c);
    }
    if (!menu->func_busy() && func_020a14d8(func_020a18e4())) {
        func_0206af98(&unk10, -1);
    }
    if (!(unk22c & 2) || (unk224 > 0 && unk21c == 0)) {
        int step = 1;
        if (unk224 > 0) {
            int v = unk224;
            if (v > 10) {
                v = 10;
            }
            step = v * 15;
            unk224 -= step / 15;
            if (unk224 <= 0) {
                unk11c->flags &= ~0x40;
            }
        }
        Unk020d6298 *clock = &data_020d6298;
        Unk0202071c t = func_0202071c(clock);
        int hour = t.func_hour();
        if (unk224 > 0 || (p->unk3d4 == 0 && unk144 == 0) || !func_020a19cc(clock, step)) {
            func_020a194c(clock, step);
            Unk0202071c t2 = func_0202071c(clock);
            if (hour != t2.func_hour()) {
                func_0206f0d8();
            }
            func_0206f96c();
        }
    }
    func_02059cb0(unk214, (unk22c & 1) != 0);
    func_02059d10(unk214, (unk22c & 1) != 0);
    unk218->func_02071a60();
    if (dt) {
        func_01ff9924(pool);
        while (func_01ff9ee8(pool)) {
            func_0207a748();
        }
        *(volatile u32 *)0x4000540 = 3;
        func_0207c224();
        func_01ffaac4(func_0208c578());
        data_020c3ba4.palettes->func_0207005c();
        func_01ff9dbc(pool);
        Unk0208db14::func_0208dbe8()->func_0208e4ec();
        Unk0208db14::func_0208dbf8()->func_0208e4ec();
        func_01ffadf8(Unk020916a4::func_02091820());
        func_01ffadf8(Unk020916a4::func_02091830());
        if (unk22c & 0x1000) {
            unk22c &= ~0x1000;
        } else {
            func_020a15a8(system, dt);
        }
        func_0205f7f8(data_020c3fc4);
    }
    unk228++;
}

void *func_0206cfa8(Unk020d6240 *system) {
    return data_020d6240.input;
}

int func_0206cfb8(Unk0206bcf0 *state) {
    return func_020543d4(data_020bfc68);
}

int Unk0206bcf0::func_0206cfcc(Unk0205f098 *list, bool extra) {
    Unk0206bcf0Item *items[10];
    int n = 0;
    func_0205f10c(list, items, list->count);
    for (int i = 0; i < list->count; i++) {
        if (func_0206d630(items[i]) && n != 10) {
            entries[n].textId = func_0205d134(items[i]->def, 0xbe33d1b8);
            entries[n].unk4 = items[i]->unk2c;
            n++;
        }
    }
    if (extra) {
        entries[n].textId = 0xd5e;
        entries[n].unk4 = 0;
        n++;
    }
    if (n <= 0) {
        unk20c = 0;
        return 0;
    }
    Unk0201b6d4 *menu = data_020d6240.menu;
    menu->func_0201b964(entries, n, 0);
    menu->func_0201c2c4(unk120.x, unk120.y);
    menu->func_0201c198();
    unk20c = 2;
    return n;
}

/* 96.76 %: the load of the tile layer and the mov r1, #0x20 are scheduled
 * differently. */
void Unk0206bcf0::func_0206d0ec(Unk0206bcf0Point *pt, Unk0206bcf0Ray *ray) {
    if (!func_0206d6dc()) {
        return;
    }
    Unk020c43a8 *p = &data_020c43a8;
    int n = 0;
    unk204 = p->func_14();
    if (unk204.pos.unk3 == -1) {
        return;
    }
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &unk204);
    u32 *tile = &layer->tiles[func_index(unk204.xy.x, unk204.xy.y, layer->info->width)];
    if (!func_0206757c(p, 0x20)) {
        if (p->unk3d4 == 0) {
            entries[n].textId = 0x49;
            entries[n].unk8 = 7;
            n++;
            if (func_0206757c(p, 2) && !(*tile & 0xc000)) {
                entries[n].textId = 0xd4d;
                entries[n].unk8 = 5;
                n++;
            }
        }
    } else {
        if (!(*tile & 0xc000) && !(func_020589ac(&data_020c3ba4, data_020c3ba4.map)->unk8 & 0x10) &&
            func_has(data_020bfc9c, 0x469724a2)) {
            entries[n].textId = 0xb0b;
            entries[n].unk8 = 0;
            n++;
        }
        u32 k = *tile & 0xc000;
        if ((k == 0 || k == 0x4000 || k == 0xc000) && p->unk3d4 == 0) {
            entries[n].textId = 0xd4d;
            entries[n].unk8 = 5;
            n++;
            if (!(*tile & 0xc000)) {
                entries[n].textId = 0x1a;
                entries[n].unk8 = 6;
                n++;
            }
        }
    }
    func_0206d3dc(tile, &n);
    if (n <= 0) {
        unk20c = 0;
        return;
    }
    Unk0201b6d4 *menu = data_020d6240.menu;
    menu->func_0201b964(entries, n, 0);
    menu->func_0201c2c4(pt->x, pt->y);
    menu->func_0201c198();
    unk20c = 4;
}

void Unk0206bcf0::func_0206d3dc(u32 *tile, int *n) {
    u32 k = *tile & 0xc000;
    if (k == 0x8000) {
        entries[*n].textId = 0xb0c;
        entries[*n].unk8 = 1;
        (*n)++;
        return;
    }
    if (k != 0x4000 && k != 0xc000) {
        return;
    }
    if (func_0206757c(&data_020c43a8, 0x20)) {
        entries[*n].textId = 0x1e;
        entries[*n].unk8 = 4;
        (*n)++;
    }
    u8 *db = data_020bfc9c;
    if (func_has(db, 0xab8dd75e)) {
        entries[*n].textId = 0xc94;
        entries[*n].unk8 = 2;
        (*n)++;
    }
    if ((*tile & 0xc000) != 0xc000) {
        return;
    }
    int key = 0x9f2c933a;
    Unk020547f8 found;
    func_02054d94(db, &found, &key, 1, 1);
    for (Unk020547f8Node *node = found.head; node != 0; node = node->next) {
        int i = node->def->script->func_0209599c(0xef2746ec);
        if (i == -1) {
            continue;
        }
        entries[*n].textId = func_0205cf00(node->def, i);
        entries[*n].unk8 = 3;
        entries[*n].unk4 = node->def->unkc;
        (*n)++;
    }
}

bool func_0206d5f4(Unk0206bcf0Item *item) {
    if (func_0205d340(item->def, 0x1f319e5)) {
        return false;
    }
    return func_0205ec0c(item) != 0;
}

bool Unk0206bcf0::func_0206d630(Unk0206bcf0Item *item) {
    if (item->flags & 0x200) {
        return false;
    }
    if (item->unk10 != 0) {
        return false;
    }
    if (func_0206e134(item)) {
        return true;
    }
    if (func_0206d5f4(item)) {
        return true;
    }
    Unk020c43a8 *p;
    int i;
    Unk0205cf00 *def;
    def = item->def;
    p = &data_020c43a8;
    for (i = 0; i < def->script->func_0209576c()->count406; i++) {
        if (func_0205e00c(item, i, p)) {
            return true;
        }
    }
    return false;
}

/* 99.63 %: the loop index and the database pointer swap registers. */
bool Unk0206bcf0::func_0206d6dc() {
    int i;
    u8 *db;
    u32 *tiles;
    Unk020c43a8 *p;
    Unk02056ed0 *layer;
    p = &data_020c43a8;
    db = data_020bfc9c;
    Unk0206bcf0Cell cell = p->func_14();
    if (cell.pos.unk3 == -1) {
        return false;
    }
    layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    tiles = layer->tiles;
    i = func_index(cell.xy.x, cell.xy.y, layer->info->width);
    if (!(tiles[i] & 0xc000) && !(func_020589ac(&data_020c3ba4, data_020c3ba4.map)->unk8 & 0x10) &&
        func_has(db, 0x469724a2)) {
        return true;
    }
    if (func_0206757c(p, 0x20) && func_isWater(tiles[i])) {
        return true;
    }
    if ((tiles[i] & 0xc000) == 0x8000) {
        return true;
    }
    if (p->unk3d4 != 0) {
        return false;
    }
    if (!func_0206757c(p, 0x20)) {
        return true;
    }
    u32 k = tiles[i] & 0xc000;
    return k == 0 || k == 0x4000 || k == 0xc000;
}

void Unk0206bcf0::func_0206d858(Unk0206bcf0Point *pt, Unk0206bcf0Item *item) {
    if (item == 0) {
        return;
    }
    if (!func_0206d630(item)) {
        return;
    }
    int n = 0;
    Unk0205cf00 *def = item->def;
    if (func_0206e134(item)) {
        entries[0].textId = 0x9db;
        entries[0].unk4 = item->unk2c;
        n = 1;
        entries[0].unk8 = n;
    } else if (func_0206d5f4(item)) {
        entries[0].textId = 0x9a0;
        entries[0].unk4 = item->unk2c;
        entries[0].unk8 = n;
        n = 1;
    }
    Unk020c43a8 *p = &data_020c43a8;
    for (int i = 0; i < def->script->func_0209576c()->count406; i++) {
        if (func_0205e00c(item, i, p) && n != 12) {
            entries[n].textId = func_0205cf00(def, i);
            entries[n].unk8 = i + 2;
            entries[n].unk4 = item->unk2c;
            n++;
        }
    }
    if (n <= 0) {
        unk20c = 0;
        return;
    }
    Unk0201b6d4 *menu = data_020d6240.menu;
    menu->func_0201b964(entries, n, 0);
    menu->func_0201c2c4(pt->x, pt->y);
    menu->func_0201c198();
    unk20c = 3;
}

void Unk0206bcf0::func_0206d9c4(Unk0206bcf0Ray ray) {
    Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    if (map == 0) {
        return;
    }
    if (!func_0205809c(map, &unk204, &ray)) {
        return;
    }
    func_0206da24(&unk204);
}

/* 98.79 %: stack slots and registers of the entry and the cell copies. */
void Unk0206bcf0::func_0206da24(Unk0206bcf0Cell *cell) {
    Unk020c3ba4 *world = &data_020c3ba4;
    Unk02058788 *map = func_02058788(world, world->map);
    if (map == 0) {
        return;
    }
    Unk0201b6d4 *menu = data_020d6240.menu;
    unk20c = 1;
    if (func_02057f90(map, cell)) {
        Unk0201b964Entry e;
        e.textId = 0x16e;
        Unk02056ed0 *layer = func_02056ed0(map, cell);
        int kind = ((layer->tiles[func_index(cell->xy.x, cell->xy.y, layer->info->width)] & 0x3000) >> 12) - 1;
        if (func_020589ac(world, map->unk24)->unk1[kind] != -1) {
            Unk0205f098 ctx;
            func_0205f098(&ctx);
            for (Unk0206bcf0Item *o = func_0205fb4c(data_020c3fd4, 0x12d2c5be, &ctx, map->unk24); o != 0; o = o->next) {
                Unk0206bcf0Cell c = o->func_14();
                if (!func_isPlaced(c)) {
                    continue;
                }
                u32 *p = func_tileAt(layer, o->func_14().xy);
                if (p == 0) {
                    continue;
                }
                if (kind != ((*p & 0x3000) >> 12) - 1) {
                    continue;
                }
                int id = func_0205d1b4(o->def, 0x1b8bb551);
                if (id != 0) {
                    e.textId = id;
                }
                break;
            }
            func_0205f0a8(&ctx);
        }
        unk204 = *cell;
        menu->func_0201b964(&e, 1, 0);
        menu->func_0201c2c4(unk120.x, unk120.y);
        menu->func_0201c198();
        return;
    }
    if (func_02057ed8(map, cell)) {
        Unk02056ed0 *layer = func_02056ed0(map, cell);
        u32 *tiles = layer->tiles;
        int i = func_index(cell->xy.x, cell->xy.y, layer->info->width);
        int n = 0;
        unk204 = *cell;
        u32 *tile = &tiles[i];
        entries[n++].textId = (tiles[i] & 0xc000) == 0x8000 ? 0xfce : 0x14;
        func_0206d3dc(tile, &n);
        if (n == 1) {
            unk20c = 0;
            func_0206ddb4();
            return;
        }
        menu->func_0201b964(entries, n, 0);
        menu->func_0201c2c4(unk120.x, unk120.y);
        menu->func_0201c198();
        return;
    }
    unk20c = 0;
}

void Unk0206bcf0::func_0206dd24() {
    for (u32 i = 0; i < 12; i++) {
        entries[i].textId = 0;
        entries[i].unk8 = -1;
    }
    data_020d6240.menu->func_0201c208();
    unk204 = Unk0206bcf0Cell();
    unk20c = 0;
}

/* 99.02 %: world / map / x registers rotate, and kind + info is added the
 * other way round (index forms tried). */
void Unk0206bcf0::func_0206ddb4() {
    int sel;
    Unk020c3ba4 *world;
    u32 *tile;
    bool sound;
    Unk02058788 *map;
    world = &data_020c3ba4;
    sel = data_020d6240.menu->selected;
    map = func_02058788(world, world->map);
    Unk02056ed0 *layer = func_02056ed0(map, &unk204);
    tile = func_tileAt(layer, unk204.xy);
    sound = false;
    if (unk20c != 1 || sel == 0) {
        Unk020c43a8 *p = &data_020c43a8;
        if (func_02057f90(map, &unk204)) {
            int kind = ((*tile & 0x3000) >> 12) - 1;
            s8 v = func_020589ac(world, map->unk24)->unk1[kind];
            if (v != -1) {
                Unk02007340 *o = func_02007340(data_020be184, 1);
                if (o != 0) {
                    func_02007e48(&p->unk3c8, o);
                    if (func_02005654(o, unk204, kind, v)) {
                        sound = true;
                    } else {
                        o->unk44 = 1;
                    }
                }
            }
        } else if (func_02066518(p, &unk204)) {
            if (func_02057ed8(map, &unk204)) {
                sound = true;
            }
        }
        if (sound) {
            func_020a2ce8(func_020a2994(), 0x2c8ca60c, 0x7f, 0);
        }
    } else {
        func_0206e424();
    }
    Unk02098ff0 pos = func_02057b5c(map, &unk204);
    unk218->func_020718c0(pos, tile);
    unk20c = 0;
}

void Unk0206bcf0::func_0206df74() {
    unk20c = 0;
    int sel = data_020d6240.menu->selected;
    if (entries[sel].unk4 == 0) {
        func_0206d0ec(&unk120, &unk128);
        return;
    }
    Unk0206bcf0Item *item = func_0205fbf4(data_020c3fd4, entries[sel].unk4);
    if (item == 0) {
        return;
    }
    func_0206d858(&unk120, item);
}

void Unk0206bcf0::func_0206dfdc() {
    int sel = data_020d6240.menu->selected;
    Unk0206bcf0Item *item = func_0205fbf4(data_020c3fd4, entries[sel].unk4);
    if (item == 0) {
        unk20c = 0;
        return;
    }
    switch (entries[sel].unk8) {
    case 0: {
        Unk0205cf00 *def = item->def;
        func_0205465c(data_020bfc68, def, 1);
        func_0206f0ec(0xe, 1, 0);
        if (unk144 != 0) {
            func_02028eec(unk144, 0xe, def, item);
        }
        if (item->def->script->func_020957ec(0x7dabdf66)) {
            func_0205ece8(item, 0x7dabdf66);
        }
        break;
    }
    case 1:
        func_0206e240(item);
        break;
    default: {
        Unk020c43a8 *p = &data_020c43a8;
        int i = entries[sel].unk8 - 2;
        if (func_0205e00c(item, i, p)) {
            func_0205cfd4(item->def, i, item, p);
        }
        break;
    }
    }
    unk20c = 0;
}

void Unk0206bcf0::func_0206e104(int v) {
    unk224 = v;
    if (unk11c == 0) {
        return;
    }
    if (unk224 <= 0) {
        unk11c->flags &= ~0x40;
    } else {
        unk11c->flags |= 0x40;
    }
}

/* 99.88 %: the stack slots of the rotation, the offset and the moved cell
 * are in another order. */
bool Unk0206bcf0::func_0206e134(Unk0206bcf0Item *item) {
    if (func_0205d340(item->def, 0x2539c423)) {
        Unk0206bcf0Cell to = item->func_14().func_moved(
            func_020619a8(item, Unk0206bcf0Xy(item->def->unk0, item->def->unk2), item->func_1c()));
        return func_02057ed8(func_02058788(&data_020c3ba4, data_020c3ba4.map), &to) != 0;
    }
    return false;
}

bool Unk0206bcf0::func_0206e240(Unk0206bcf0Item *item) {
    Unk02007c98 *o = func_02007c98(data_020be184, 9, 2);
    if (o == 0) {
        return false;
    }
    int k0;
    int k1;
    int k2;
    int k3;
    int t30;
    int t3c;
    int t38;
    int t34;
    Unk0205cf00 *def;
    u32 a;
    u32 b;
    def = item->def;
    Unk020a20f0 random;
    func_020a20f0(&random);
    u32 r = func_020a1f84(&random) % 3;
    if (r == 2) {
        a = 0x27c4a91f;
        b = a + 1;
    } else if (r == 1) {
        a = 0x1a0e9efd;
        b = a + 1;
    } else {
        a = 0x1a0ea2dd;
        b = a + 1;
    }
    t34 = 0;
    t30 = t34;
    t3c = t34;
    t38 = t34;
    k0 = func_0205d1b4(def, 0xc69c426b);
    k1 = func_0205d1b4(def, 0xa1c45150);
    k2 = func_0205d1b4(def, 0xf7223421);
    k3 = func_0205d1b4(def, 0x56b2733d);
    if (k0 != 0) {
        a = k0;
        b = func_0205d1b4(def, 0xc69c426c);
        if (b == 0) {
            b = 0;
        }
    }
    if (k1 != 0) {
        t30 = k1;
        t34 = func_0205d1b4(def, 0xa1c45151);
        if (t34 == 0) {
            t34 = 0;
        }
    }
    o->unk28 = a;
    o->unk2c = b;
    o->unk30 = t30;
    if (k2 != 0) {
        t38 = k2;
    }
    o->unk34 = t34;
    o->unk38 = t38;
    if (k3 != 0) {
        t3c = k3;
    }
    o->unk3c = t3c;
    o->unk40 = 0;
    func_02007e48(&item->unk4, o);
    func_02007e48(&data_020c4770, o->unk18);
    return true;
}

void Unk0206bcf0::func_0206e40c() {
    func_0206e424();
    unk20c = 0;
}

/* 94.65 %: the original's frame is 8 bytes larger (a second copy of the
 * kind 4 in case 3), and the tile index / tile array registers are swapped. */
void Unk0206bcf0::func_0206e424() {
    Unk020c43a8 *p;
    int sel;
    Unk02056ed0 *layer;
    int i;
    u32 *tiles;
    sel = data_020d6240.menu->selected;
    p = &data_020c43a8;
    if (unk204.pos.unk3 == -1) {
        return;
    }
    layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &unk204);
    i = func_index(unk204.xy.x, unk204.xy.y, layer->info->width);
    tiles = layer->tiles;
    switch (entries[sel].unk8) {
    case 0:
    case 1: {
        u32 k = tiles[i] & 0xc000;
        if (k != 0 && k != 0x8000) {
            return;
        }
        Unk02007340K0c *o = (Unk02007340K0c *)func_02007340(data_020be184, 0xc);
        if (o == 0) {
            return;
        }
        o->func_set(unk204, unk210);
        func_02007e48(&p->unk3c8, o);
        break;
    }
    case 2: {
        if (!func_isWater(tiles[i])) {
            return;
        }
        if (!func_has(data_020bfc9c, 0xab8dd75e)) {
            return;
        }
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, 0x936f2a);
        if (func_0205465c(data_020bfc68, def, 0)) {
            def = func_0205f6f8(data_020c3fc4, func_0205d1b4(def, 0x798b86ac));
            func_0206bce0()->func_0206f3e8(def, 1, 1, 1);
        }
        Unk02007340K06 *o = (Unk02007340K06 *)func_02007340(data_020be184, 6);
        if (o == 0) {
            return;
        }
        func_02006754(o, 0, 3, 0x5e691f68, 0);
        o->cell = unk204;
        o->flags |= 0x10;
        func_02007e48(&p->unk3c8, o);
        break;
    }
    case 3: {
        if ((tiles[i] & 0xc000) != 0xc000) {
            return;
        }
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, entries[sel].unk4);
        if (!func_owns(data_020bfc9c, def)) {
            return;
        }
        int v = def->script->func_0209599c(0xef2746ec);
        if (v == -1) {
            return;
        }
        Unk02007340K0e *o = (Unk02007340K0e *)func_02007340(data_020be184, 0xe);
        if (o == 0) {
            return;
        }
        o->func_set(unk204, 4, entries[sel].unk4, v);
        o->unk38 = 0;
        o->unk40 = 0;
        o->unk44 = 0;
        func_02007e48(&p->unk3c8, o);
        break;
    }
    case 4: {
        if (!func_isWater(tiles[i])) {
            return;
        }
        Unk02007340K11 *o = (Unk02007340K11 *)func_02007340(data_020be184, 0x11);
        if (o == 0) {
            return;
        }
        int v;
        if ((tiles[i] & 0xc000) == 0xc000) {
            if (data_020c3ba4.map == 0xf) {
                v = 0x4c4b40;
            } else {
                v = 0x632ea0 - func_0206647c(&data_020c43a8, 3);
            }
        } else {
            v = 0x4c4b40 - func_0206647c(&data_020c43a8, 3);
        }
        if (v < 0) {
            v = 0;
        }
        o->unk24 = func_02067b70(&data_020c43a8);
        o->func_set(unk204);
        o->unk38 += func_02077b3c(v * 100, 0x989680);
        o->unk34 += 0x14;
        o->unk30 += func_02077b3c(v * func_020667d4(p, 2), 0x4c4b40);
        func_02007e48(&p->unk3c8, o);
        break;
    }
    case 5: {
        u32 k = tiles[i] & 0xc000;
        if (k != 0 && k != 0x4000 && k != 0xc000) {
            return;
        }
        if (!func_0206f0ec(0, 1, 0)) {
            return;
        }
        func_02029128(unk144, 1);
        break;
    }
    case 6:
        if (tiles[i] & 0xc000) {
            return;
        }
        if (!func_0206f0ec(1, 1, 0)) {
            return;
        }
        func_02029128(unk144, 1);
        break;
    case 7:
        if (func_0206757c(p, 0x20)) {
            return;
        }
        if (!func_0206f0ec(0xe, 1, 0)) {
            return;
        }
        func_02029128(unk144, 1);
        func_02028eec(unk144, 0xe, func_0205f6f8(data_020c3fc4, func_0209a32c("build/data/objects/help", 0, 0)), 0);
        break;
    }
}

/* 98.74 %: the store of 1 to data_020c409c + 0x20 uses r1 for the address
 * where the original uses r0. */
void Unk0206bcf0::func_0206ea00(int map, int flag) {
    Unk020c7d38 *pool;
    Unk020c3ba4 *world;
    Unk020c7f48 *tex;
    int old;
    Unk020589ac *info;
    void *layers;
    pool = &data_020c7d38;
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    world = &data_020c3ba4;
    func_0206dd24();
    old = world->map;
    if (old == map) {
        return;
    }
    func_02053100(&data_020bfc3c);
    if (old != -1) {
        func_0206f610();
        for (Unk0205fd7c *n = func_0205fd7c(data_020c3fd4, old); n != 0; n = n->next) {
            func_0205e4d0(n);
            func_02007e10(&n->unk4);
            func_02007e38(&n->unk4);
        }
        func_020585e0(world, old);
        func_0205fde4(data_020c3fd4);
        func_0205f7f8(data_020c3fc4);
    }
    func_02065e80(&data_020c43a8);
    func_0205a548(unk214);
    func_02054a70(data_020bfc80);
    if (map == -1) {
        return;
    }
    info = func_020589ac(world, map);
    layers = func_02058518(world, map, 1);
    func_0206ef04(map);
    func_02056c7c(layers);
    func_020585a0(world, map);
    tex = func_0208c578();
    data_020c409c[0x20] = 0;
    for (Unk0205fd7c *n = func_0205fd7c(data_020c3fd4, map); n != 0;) {
        func_0205e3f0(n);
        n = n->next;
        func_01ffaac4(tex);
        world->palettes->func_0207005c();
        func_0205f7f8(data_020c3fc4);
    }
    data_020c409c[0x20] = 1;
    Unk0206bcf0Cell cell;
    if (!func_020573a4(layers, &cell, old)) {
        func_020577a4(layers, &cell);
    }
    if (func_isPlaced(cell)) {
        Unk020c43a8 *p = &data_020c43a8;
        p->func_10(cell);
        func_020667f8(&data_020c43a8, 0);
    }
    func_02065db8(&data_020c43a8);
    func_0206a120(&unk10);
    func_020a18e4();
    if (!func_020a1524(unk11c) && unk224 <= 0) {
        func_020a1494(func_020a18e4(), 2, 0x10);
        func_020a11f8(func_020a18e4(), 2, 0);
        unk22c |= 0x1000;
    }
    func_02058cd8(world, map, 1);
    func_0206f5f4();
    if (flag) {
        Unk020c43a8 *p = &data_020c43a8;
        Unk0206bcf0Cell here = p->func_14();
        Unk0205f098 ctx;
        func_0205f098(&ctx);
        for (Unk0206bcf0Item *item = func_0205fb4c(data_020c3fd4, 0x12d2c5be, &ctx, map); item != 0;
             item = item->next) {
            Unk0206bcf0Cell c = item->func_14();
            if (!func_isPlaced(c)) {
                continue;
            }
            if (!(c == here)) {
                continue;
            }
            Unk0205cf00 *def = item->def;
            int y = item->func_0c().y + 0x8000;
            if (def != 0 && func_0205d340(def, 0x350465a)) {
                Unk02007c98 *o = func_02007c98(data_020be184, 0x1c, 2);
                if (o != 0) {
                    func_02001318(o, item, 0, map, 0, y, 1, 0);
                    func_02007e48(&item->unk4, o);
                    func_02007e48(&data_020c4770, o->unk18);
                }
            } else {
                Unk02007340 *o = func_02007340(data_020be184, 0x1a);
                if (o != 0) {
                    func_02001318(o, item, 0, map, 0, y, 1, 0);
                    func_02007e48(&data_020c4770, o);
                }
            }
            break;
        }
        func_0205f0a8(&ctx);
    }
    func_0205a484(unk214);
    func_02059c10(unk214, !(info->unk8 & 8));
}

void Unk0206bcf0::func_0206ef04(int map) {
    Unk020c3ba4 *world = &data_020c3ba4;
    int id = func_0209a3c4(func_020589ac(world, map)->unk4, "lot.ambient.nitro_xml");
    Unk020bfc3c *ambient = &data_020bfc3c;
    if (ambient->unkc) {
        ambient->unk24 = id;
        u32 key = 0x53204676;
        if (func_02059cf8(func_0206bce0()->unk214) == 0xa8e91b4e) {
            key = 0xc4f6bea5;
        }
        func_020529b4(&data_020bfc3c, key, world->unk0);
    } else {
        func_02052974(ambient, id, world->unk0);
    }
}

void Unk0206bcf0::func_0206ef8c(int a) {
    func_0206f578(true);
    func_0206f560(true);
    delete unk140;
    Unk0202402c *o = new Unk0202402c;
    unk140 = o;
    o->unk53e4 = a;
    unk22c |= 0x40;
    unk11c->func_18();
}

void Unk0206bcf0::func_0206f008(int a) {
    func_0206f578(true);
    func_0206f560(true);
    delete unk16c;
    Unk020238ec *o = new Unk020238ec;
    unk16c = o;
    if (o == 0) {
        return;
    }
    o->unkb8 = a;
    unk22c |= 0x800;
    unk11c->func_18();
}

void Unk0206bcf0::func_0206f084() {
    func_0206f578(true);
    if (unk168 == 0) {
        unk168 = new Unk0201dd90;
    }
    if (unk168 == 0) {
        return;
    }
    unk168->func_08();
}

void Unk0206bcf0::func_0206f0d8() {
    func_02066d1c(&data_020c43a8);
}

bool Unk0206bcf0::func_0206f0ec(int type, int b, int c) {
    if (unk144 != 0 || unk14c.unk0 != 0) {
        return false;
    }
    Unk020c43a8 *p = &data_020c43a8;
    Unk020c4770 *q = &data_020c4770;
    if (b) {
        func_02007d94(q);
    }
    if (!b || q->unkc == 0 || !q->func_busy()) {
        bool flag = false;
        if (type == 4 && unk11c->unk1278) {
            flag = true;
        }
        func_02054360(data_020bfc68);
        func_0206f560(true);
        func_0206f578(true);
        unk11c->func_18();
        unk144 = new Unk02027994(type);
        unk22c |= 0x10;
        func_02029128(unk144, flag);
        Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
        Unk0206bcf0Cell cell = p->func_14();
        if (func_0205803c(map, &cell) == 1) {
            func_02028ec8(unk144, 1, c);
        } else {
            func_02028ec8(unk144, 0, c);
        }
        return true;
    }
    return false;
}

bool Unk0206bcf0::func_0206f258(int a) {
    if (unk164 != 0) {
        return false;
    }
    if (unk144 != 0) {
        if (!unk144->func_30()) {
            return false;
        }
    } else if (unk11c != 0) {
        if (!unk11c->func_30()) {
            return false;
        }
    }
    func_0206f560(true);
    func_0206f578(true);
    func_0206f548(true);
    if (unk144 != 0) {
        unk144->func_18();
    } else {
        unk11c->func_18();
    }
    unk164 = new Unk02044234(a);
    unk22c |= 0x20;
    return true;
}

void Unk0206bcf0::func_0206f340() {
    if (unk148 != 0) {
        return;
    }
    func_0206f560(true);
    func_0206f578(true);
    func_0206f548(true);
    if (!func_020a1524(unk11c)) {
        unk11c->func_18();
        if (!unk11c->func_28()) {
            unk11c->flags |= 8;
        }
    }
    unk148 = new Unk02027994(0x12);
    unk22c |= 0x100;
}

bool Unk0206bcf0::func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d) {
    if (unk144 == 0) {
        if (c) {
            if (!func_0206f0ec(9, b, 0)) {
                return false;
            }
            func_02029128(unk144, d);
            func_02028eec(unk144, 9, def, 0);
            func_020a2ce8(func_020a2994(), func_0209a32c("GROUP_SE_COMMON SE_TUTORIALBLING", 0, 0), 0x7f, 0);
            return true;
        }
        if (func_0206f0ec(5, b, 0)) {
            func_02029128(unk144, d);
            func_02028eec(unk144, 5, def, 0);
            func_020a2ce8(func_020a2994(), func_0209a32c("GROUP_SE_COMMON SE_TUTORIALBLING", 0, 0), 0x7f, 0);
            return true;
        }
    }
    return false;
}

bool Unk0206bcf0::func_0206f4e4(u32 key) {
    if (unk144 == 0 && func_0206f0ec(0xd, 0, 0)) {
        func_02028eec(unk144, 0xd, func_0205f6f8(data_020c3fc4, key), 0);
        return true;
    }
    return false;
}

void Unk0206bcf0::func_0206f548(bool on) {
    if (on) {
        unk22c |= 1;
    } else {
        unk22c &= ~1;
    }
}

void Unk0206bcf0::func_0206f560(bool on) {
    if (on) {
        unk22c |= 2;
    } else {
        unk22c &= ~2;
    }
}

void Unk0206bcf0::func_0206f578(bool on) {
    if (on) {
        unk221++;
        unk22c |= 4;
        return;
    }
    if (unk221 != 0) {
        unk221--;
        if (unk221 != 0) {
            return;
        }
    }
    unk22c &= ~4;
}

void Unk0206bcf0::func_0206f5dc(bool on) {
    if (on) {
        unk22c |= 8;
    } else {
        unk22c &= ~8;
    }
}

void Unk0206bcf0::func_0206f5f4() {
    func_0205ff28(data_020c3fd4, 0x2a8bd5f9);
}

void Unk0206bcf0::func_0206f610() {
    func_0205ff28(data_020c3fd4, 0x66334a39);
}

void Unk0206bcf0::func_0206f62c() {
    func_0205fea0(data_020c3fd4, 0xac58df5f);
    func_02059224(unk210);
}

void Unk0206bcf0::func_0206f654() {
    func_0205fea0(data_020c3fd4, 0x1993a570);
    func_02059224(unk210);
}

void Unk0206bcf0::func_0206f67c() {
    int w = data_020c3ba4.unk0;
    if (w == 0) {
        return;
    }
    u32 key = 0x53204676;
    if (func_02059cf8(unk214) == 0xa8e91b4e) {
        key = 0xc4f6bea5;
    }
    func_020529b4(&data_020bfc3c, key, w);
}

void Unk0206bcf0::func_0206f6d0() {
    func_0205fea0(data_020c3fd4, 0x956204c);
    func_02052a00(&data_020bfc3c, 0);
}

void Unk0206bcf0::func_0206f6fc() {
    Unk020a4c4c *save = data_020d60c8.save;
    func_020a4c4c(save);
    func_020a4d78(save, 2);
    Unk020a4c60 *header = func_020a4c60(save, 0xc, 1);
    if (header == 0) {
        save->flags |= 0xc;
        return;
    }
    header->magic = 0x53494d4d;
    header->size = 0xc;
    header->version = 7;
    func_020a1994(&data_020d6298, save);
    func_0205501c(data_020bfc9c, save);
    data_020d60c8.unk4->func_0206b73c(save);
    unkc->func_0206bbdc(save);
    func_02058ce8(&data_020c3ba4, save);
    func_0205ffa4(data_020c3fd4, save);
    func_02067594(&data_020c43a8, save);
    func_0205a5c8(unk214, save);
}

void Unk0206bcf0::func_0206f7e4() {
    func_02054b30(data_020bfc9c);
    func_02054ab4(data_020bfc9c);
    data_020d60c8.unk4->count = 0;
    Unk020a4c4c *save = data_020d60c8.save;
    save->unkc = 0;
    func_020a4d2c(save, 2);
    Unk020a4c60 *header = func_020a4ce0(save, 0xc);
    if (header == 0 || header->magic != 0x53494d4d || header->size != 0xc || header->version != 7) {
        save->flags |= 0xc;
        return;
    }
    func_020a19b0(&data_020d6298, save);
    unk220 = data_020d6298.func_hour() >= 6;
    data_020c3ba4.palettes->func_0207001c(!unk220);
    func_0205507c(data_020bfc9c, save);
    data_020d60c8.unk4->func_0206b75c(save);
    unkc->func_0206bc48(save);
    func_02058dd4(&data_020c3ba4, save);
    func_02060080(data_020c3fd4, save);
    func_02064cdc(&data_020c43a8);
    func_02067620(&data_020c43a8, save);
    if (unk11c != 0) {
        func_02020978(unk11c);
    }
    func_0205a6cc(unk214, save);
    func_0206ef04(data_020c3ba4.map);
    func_0205ff28(data_020c3fd4, 0x58cc062);
    func_0206a120(&unk10);
}

void Unk0206bcf0::func_0206f96c() {
    Unk020d6298 *clock = &data_020d6298;
    if (unk220 == (clock->func_hour() >= 6)) {
        return;
    }
    if (unk21c != 0) {
        return;
    }
    func_0206f548(true);
    unk220 = clock->func_hour() >= 6;
    unk22c &= ~0x400;
    unk11c->flags &= ~0x10;
    unk22c |= 0x200;
    unk21c = new Unk02027044;
    unk11c->func_18();
}

void Unk0206bcf0::func_0206fa30() {
    Unk020c3ba4 *world = &data_020c3ba4;
    for (int i = 0; i < 0x29; i++) {
        func_02056b80(func_02058518(world, i, 0));
        func_020585e0(world, i);
    }
    func_0206ea00(1, 0);
    func_02065db8(&data_020c43a8);
    func_02020fb8(unk11c);
    func_0205fea0(data_020c3fd4, 0xd528485d);
}
