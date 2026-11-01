/*
 * Unit 0x0200B23C-0x0200DD80: the collecting microgame `Unk0200cec8`: fifteen moving
 * catches `Unk0200c308` cross the screen, the stylus takes them under a countdown.
 * Strings: `collect_success`, `splat.nitro_map`, `walk.nitro_map`.
 *
 * Bounds: hypothesis. `.data` starts at the table (the pointer to member constants of
 * the file are written as one array, which is a hypothesis) and ends before the base
 * vtable of the next unit. Real file name unknown; all names are placeholders.
 *
 * Open gaps. `.data`: the strings land before the table, the original has them after
 * the vtables. Code: the table is reached through two anchors in the original, the
 * countdown hoists the address of its word, and the rest is register allocation. The
 * scores of each function are in the objdiff report.
 */
#include "game/unk_microgame.h"
#include "game/unk_catalog.h"
#include "game/unk_fishing.h"
#include "game/unk_sim.h"

class Unk0200cec8;

struct Unk0200cec8Sound {
    int unk0;
    int unk4;
};

struct Unk0200cec8Arg {
    int key;
    int value;
};

struct Unk0201a4e0Rect {
    int a, b, c, d;
    void func_0200cae0(const Unk0201a4e0Rect &o);
};

struct Unk0201a4e0RectWrap {
    Unk0201a4e0Rect r;
};

/* The view of a catch record. */
struct Unk0200dd50 {
    void *def;
    int unk4;
};

class Unk0200f174 {
public:
    union {
        struct {
            u32 frames : 6;
            u32 seconds : 6;
            u32 minutes : 6;
            u32 hours : 6;
        } f;
        u32 v;
    };

    Unk0200f174() {
        v = 0;
        func_set(0, 0);
    }
    void func_set(int s, int fr) {
        f.hours = 0;
        f.minutes = 0;
        f.seconds = s;
        f.frames = fr;
    }
    int func_get(int i) { return (int)v >> (i * 6) & 0x3f; }
    void func_put(int i, int x) { *(volatile u32 *)&v = *(volatile u32 *)&v & ~(0x3f << (i * 6)) | x << (i * 6); }
    void func_tick() {
        for (int i = 0; i < 4; i++) {
            int n = func_get(i);
            if (n > 0) {
                func_put(i, n - 1);
                break;
            }
            func_put(i, 59);
        }
    }
};

class Unk0200d090 {
public:
    ~Unk0200d090();
};

extern "C" {
void func_0200de30(Unk0200dd90 *e);
void func_0200df10(Unk0200dd90 *e, int a, int b);
void func_0200df54(Unk0200dd90 *e);
Unk0200dd90Part *func_0200dfc8(Unk0200dd90 *e, int i);
int func_0200dfd8(Unk0200dd90 *e, Unk02098e70 *v, int d);
void func_0200e010(Unk0200dd90 *e, Unk02098e70 *v, void *r, int a);
int func_0200e0fc(void *def);
int func_0200e120(void *def);
void func_0200ada4(Unk0200ad70 *e, void *view);
int func_0200af10(Unk0200ad70 *e);
void *func_0200af18(void *view, void *def, u32 key);
void *func_0200af2c(void *view);
u32 func_0200afc0(void *view);
int func_0200afd4(void *view);
void func_0200b09c(Unk0200b04c *a, int id);
void func_0200b120(Unk0200b04c *a);
int func_0200b150(Unk0200b04c *a, int f);
Unk0200dd50 *func_0200dd50(Unk0200dd50 *v, void *def);
Unk0200dd50 *func_0200dd6c(Unk0200dd50 *v);
Unk02098e70 func_0200b23c(const Unk02098e70 &v, int f);
Unk02098e70 func_0200ca5c(const Unk02098e70 *a, const Unk02098e70 &b);
void func_0200ca68(Unk02098e70 *a, const Unk02098e70 &b);
Unk02098e70 func_0200ca7c(const Unk02098e70 *a, const Unk02098e70 &b);
int func_0200ca88(int angle);
int func_0200cab0(int angle);
int func_0200cad0(int a, int b);
void func_0200cb04(Unk0201a4e0Rect *a, const Unk0201a4e0Rect &b);
Unk020a5ccc *func_0200cec8(Unk02093648 *file, Unk0200cec8Arg *args, int n);

int func_02054c1c(void *p, void *def, int a);
void *func_0205f6f8(void *db, u32 id);
void *func_0205fbf4(void *m, int id);
void func_0205e1b8(void *item, void *p);
void *func_0206bce0();
Unk020987d8 *func_0206af40(void *p, int i);
void func_0206af60(void *p, int i, const Unk020987d8 *plane);
int func_02097a58(int a, int b);
u32 func_0209a3c4(u32 h, const char *s);
int func_020a1280(int a, int b, int c);
int func_020a18e4();
int func_020a1e68(int a, int b, int c);
Unk0200cec8Sound *func_020a290c(int a, int b);
void func_020a2964(int a, Unk0200cec8Sound *b, int c);
int func_020a2994();
void func_020a3188(int a, u32 h, int b);
int func_020a32ac(int a, u32 h, int b, int c, int d);
void func_020a34e4(int a, int h);
void func_020a3858(int a, u32 h, int b, int c, int d);
int func_020a5ec0();
int func_020a5ef0(int a, int b);
Unk02098e70 func_020a5f28(int a, int b);
int func_020a6038(void *g, int hash);
void func_020a6058(void *g, int id);
int func_020a60bc();
int func_020a60e8();
void func_020a62dc(void *g, void *item);
void func_020a6340(void *g, u32 hash, const char *name, int a, int b);
Unk0201a4e0Rect func_020a6438(void *g, Unk020a9d58 *l, Unk020a7af4 *names, u32 hash);
void func_020a6980(Unk020a7c90 *s, u32 hash);
int func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a716c(Unk020a7c90 *s, int id);
int func_020a7a44(Unk020a7c90 *s);
int func_020a7a60(Unk020a7c90 *s);
int func_020a7a7c(Unk020a7c90 *s);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a7d30(Unk020a7c90 *s, int x);
void func_020a8064(Unk020a7c90 *s, int x);
void func_020a9168(Unk020a7c90 *s, int a);
int func_020a917c(Unk020a7c90 *s);
void func_020a922c(Unk020a7c90 *s, int x);
void func_020aa06c(Unk020a9d58 *l, bool shown);
void func_020aa158(Unk020a9d58 *l);
Unk020a7c90 *func_020aa04c(Unk020a9d58 *l, u32 id);
void func_020aa1c0(Unk020a9d58 *l, Unk02098e70 *p, int touched);
void func_020aa42c(Unk020a9d58 *l);
int func_020aba38(Unk02093648 *archive, u32 hash, Unk020a9d58 *layout, Unk020a7af4 *names);
void func_020acbc8(Unk02098e70 *v);
extern const s16 data_020af1e8[];
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020d6298[];
extern int data_020be23c[3];
}
int *func_02097a4c();
int func_020978dc(int a);
int func_0209774c(int a);
int func_020972c0(int key);

class Unk020c43a8Screen {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
};
extern "C" Unk020c43a8Screen data_020c43a8;

struct Unk020c3ba4Map {
    u8 unk0[0xfc];
    s8 map;
};
extern "C" Unk020c3ba4Map data_020c3ba4;

static const u32 data_020ae52c[15] = {
    0x9b9c86fe, 0xf75394d5, 0xe944b810, 0x8f71ef0c, 0x6d543787, 0x7c2e1078, 0xe35ad9ef, 0xb0e2976a,
    0xd35cdf56, 0x8322527c, 0x93994472, 0xeaa6da8c, 0x6c7a71c3, 0xf6d408e9, 0x925ae156,
};
static const int data_020ae568[5][5] = {
    {0, 1, 9, 4, -1}, {1, 2, 3, 4, 5}, {0xc, 9, 1, 0xa, 0xd}, {8, 0, 1, 4, 0xb}, {7, 2, 3, 0xe, 6},
};
static const int data_020ae5cc[5][5] = {
    {4, 3, 3, 1, 0}, {4, 3, 3, 2, 1}, {3, 3, 4, 2, 3}, {1, 4, 5, 3, 1}, {4, 2, 4, 1, 1},
};
static const u32 data_020ae630 = 0x5beb1dfe;

enum Unk0200c308Idle {
    UNK_0200C308_BUSY,
    UNK_0200C308_IDLE
};

/* One catch. */
class Unk0200c308 : public Unk0200ad70 {
public:
    typedef void (Unk0200c308::*State)();

    Unk0200c308();
    ~Unk0200c308();

    void func_0200b268();
    void func_0200b298();
    void func_0200b2e4();
    void func_0200b310();
    void func_0200b334();
    void func_0200b3a0();
    void func_0200b3a4();
    void func_0200b420();
    void func_0200b488();
    void func_0200b674();
    void func_0200b700();
    void func_0200becc(int kind);
    virtual void *func_00();
    bool func_0200c310();
    void func_0200c99c(State s);
    void func_0200c9b8(int i, bool force);
    void *func_0200cb58();
    bool func_0200cb60();
    void func_0200cba8();

    inline Unk0200c308Idle func_idle();
    inline void func_play(int i, bool force);

    Unk0200cec8 *game;
    State state;
    int life;
    int t;
    Unk0201a4e0Rect rects[2];
    Unk0200b04cBit flags;
    Unk02098e70 touch;
    int angle;
    Unk020a7c90 *sprites[2];
    int file;
    Unk0200b04c anim;
    int index;
    u32 anims[2];
};

/* The player's sprite: its states run on this block of the game. */
class Unk0200b75c {
public:
    typedef void (Unk0200b75c::*State)();

    void func_0200b75c();
    void func_0200b7c4();
    void func_0200b7f8();
    void func_0200b8a4();
    void func_0200b8d8();
    void func_0200b8f4();
    void func_0200b910();

    State state;
    Unk0200cec8 *owner;
    Unk02098e70 pos;
    Unk0200b04cBit flags;
    int total;
};

class Unk0200cec8 : public Unk020a5ccc {
public:
    typedef void (Unk0200cec8::*State)();

    Unk0200cec8(Unk02093648 *file, Unk0200cec8Arg *args, int n);

    void func_0200b940();
    void func_0200b9c0();
    void func_0200ba70();
    void func_0200bab4();
    bool func_0200c550();
    int func_0200cb28();
    void func_0200cc60();
    void func_0200ce18();
    void func_0200d138(Unk020a7af4 *names);

    int func_sum() {
        int i;
        int n = caught[0];
        for (i = 1; i < 5; i++) {
            n += caught[i];
        }
        return n;
    }

    virtual ~Unk0200cec8() {
        func_0205e1b8(item, &data_020c43a8);
        if (sound != 0) {
            func_020a2964(func_020a2994(), sound, 1);
            sound = 0;
        }
    }

    virtual void func_10(bool a) {
        func_020aa06c(&layout, a);
        if (a != shown.func_get()) {
            shown.v ^= 1;
        }
    }

    virtual void func_14();
    virtual bool func_18();

    virtual void func_1c() {
    }

    virtual bool func_08() {
        int n = caught[0];
        for (int i = 1; i < 5; i++) {
            n += caught[i];
        }
        return n != 0;
    }

    Unk020a9d58 layout;
    Unk020a7c90 *sprite;
    Unk020a7c90 *texts[4];
    Unk02050640 buttons[4];
    Unk0200c308 catches[15];
    Unk0200b75c player;
    int unk16e0;
    int spawned;
    int spawnedKind[5];
    int total;
    int unk1700;
    int caught[5];
    State state;
    Unk0200f174 clock;
    int anim;
    int map;
    void *defs[5];
    Unk0201a4e0Rect rects[2];
    u8 unk1760[4];
    Unk0200b04cBit shown;
    int unk1768;
    u8 paused;
    Unk0200cec8Sound *sound;
    int rub;
};

/* The table of the file. */
struct Unk020b7900 {
    int radius;
    const char *names[5];
    Unk0200cec8::State game[7];
    Unk0200b75c::State player[10];
    Unk0200c308::State catches[15];
    int tail[5];
};

extern Unk020b7900 data_020b7900;


#define T data_020b7900
#define TF T.catches
#define TP T.player
#define TG T.game

static inline int func_sin(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2];
}

static inline int func_cos(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2 + 1];
}

extern "C" Unk02098e70 func_0200b23c(const Unk02098e70 &v, int f) {
    return Unk02098e70((int)(((s64)v.x * f) >> 12), (int)(((s64)v.y * f) >> 12));
}

void Unk0200c308::func_0200b268() {
    func_0200df10(this, 0, 1);
    state = TF[13];
}

void Unk0200c308::func_0200b298() {
    func_set(target, func_020a5f28(1, 0x20000));
    state = TF[6];
}

void Unk0200c308::func_0200b2e4() {
    func_set(move.dir, unka8);
    state = TF[5];
}

void Unk0200c308::func_0200b310() {
    t = 0;
    state = TF[4];
}

void Unk0200c308::func_0200b334() {
    int r = T.radius;
    t = 0;
    func_set(target, unkb0.func_02098fa8(func_0200b23c(unka8, r << 12)));
    state = TF[3];
}

void Unk0200c308::func_0200b3a0() {
}

void Unk0200c308::func_0200b3a4() {
    if (func_0200dfd8(this, &target, 0xa000) == 1) {
        func_set(target, func_020a5f28(1, 0x20000));
        state = TF[6];
    } else {
        func_0200e010(this, &target, &rects[0], 1);
    }
}

void Unk0200c308::func_0200b420() {
    if (func_0200dfd8(this, &target, 0xa000) == 1) {
        func_0200df10(this, 0, 1);
        state = TF[0];
    }
    pos.x += move.dir.x;
    pos.y += move.dir.y;
}

void Unk0200c308::func_0200b488() {
    if (t * 6 > T.radius << 13) {
        func_0200df10(this, 0, 1);
        state = TF[0];
        return;
    }
    func_set(move.dir, Unk02098e70(0x1000, 0));
    func_020acbc8(&move.dir);
    int step = move.dir.func_02098e84() * 0x2aa;
    int a = t;
    Unk02098e70 p = unkb0.func_02098fa8(func_0200b23c(unka8, a * 6));
    Unk02098e70 s = func_0200b23c(unka8, func_sin(a) * func_0200af10(this));
    func_set(pos, Unk02098e70(p.x - s.y, p.y + s.x));
    a = t + (step >> 12);
    p = unkb0.func_02098fa8(func_0200b23c(unka8, a * 6));
    s = func_0200b23c(unka8, func_sin(a) * func_0200af10(this));
    func_set(target, Unk02098e70(p.x - s.y, p.y + s.x));
    Unk02098e70 d = target.func_02098fcc(pos);
    func_set(move.dir, d.func_02098eec());
    t += step >> 12;
}

void Unk0200c308::func_0200b674() {
    if (func_0200dfd8(this, &target, 0xc8000) == 1) {
        if (t == 0) {
            func_set(target, unka0);
            t++;
        } else {
            func_0200df10(this, 0, 1);
            state = TF[0];
        }
    } else {
        func_0200e010(this, &target, &rects[0], 1);
    }
}

void Unk0200c308::func_0200b700() {
    if (func_0200dfd8(this, &target, 0xa000) == 1) {
        func_0200df10(this, 0, 1);
        state = TF[0];
    } else {
        func_0200e010(this, &target, &rects[1], 1);
    }
}

void Unk0200b75c::func_0200b75c() {
    Unk0200cec8 *g = owner;
    if (g->anim != 0) {
        func_020a6340(g, data_020ae630, T.names[0], 0, 0);
        g->anim = 0;
    }
    state = TP[7];
}

void Unk0200b75c::func_0200b7c4() {
    if (flags.func_get()) {
        flags.func_clear();
        state = TP[6];
    }
}

void Unk0200b75c::func_0200b7f8() {
    Unk0200cec8 *g = owner;
    int r = func_020a5ef0(1, 3);
    if (g->anim != r) {
        func_020a6340(g, data_020ae630, T.names[r], 0, 0);
        g->anim = r;
    }
    total = owner->func_sum();
    state = TP[5];
}

void Unk0200b75c::func_0200b8a4() {
    func_020a60e8();
    if (func_020a60bc() == 1) {
        state = TP[4];
    }
}

void Unk0200b75c::func_0200b8d8() {
    state = TP[3];
}

void Unk0200b75c::func_0200b8f4() {
    state = TP[2];
}

void Unk0200b75c::func_0200b910() {
    if (func_020a60bc()) {
        state = TP[0];
    }
}

void Unk0200cec8::func_0200b940() {
    clock.func_set(0, 0);
    clock.f.frames = 1;
    state = TG[5];
    func_020a6340(this, data_020ae630, T.names[0], 1, 0);
    anim = 0;
}

void Unk0200cec8::func_0200b9c0() {
    if (clock.v == 0) {
        state = TG[4];
    } else {
        clock.func_tick();
    }
}

void Unk0200cec8::func_0200ba70() {
    state = TG[3];
    clock.f.hours = 0;
    clock.f.minutes = 1;
    clock.f.seconds = 0;
    clock.f.frames = 0;
    unk1768 = 0;
}

inline Unk0200c308Idle Unk0200c308::func_idle() {
    return state != TF[8] ? UNK_0200C308_BUSY : UNK_0200C308_IDLE;
}

void Unk0200cec8::func_0200bab4() {
    int *t = func_02097a4c();
    int down = func_020978dc(0);
    Unk02098e70 p(t[0] << 12, t[1] << 12);
    func_020aa1c0(&layout, &p, down);
    clock.func_tick();
    if (func_0209774c(0) == 1) {
        func_set(player.pos, p);
        player.flags.func_set();
        for (int i = 0; i < 15; i++) {
            if (catches[i].func_idle() == UNK_0200C308_BUSY) {
                func_set(catches[i].touch, p);
                catches[i].flags.func_set();
            }
        }
    }
    (player.*player.state)();
    for (int i = 0; i < 15; i++) {
        Unk0200c308 *c = &catches[i];
        func_0200de30(c);
        c->func_0200cba8();
        (c->*c->state)();
        if (!c->func_0200cb60()) {
            if (c->func_0200c310() != 1) {
                c->life++;
            }
        }
    }
    if (spawned != total) {
        int kind;
        if (spawned < 10) {
            const int *row = data_020ae5cc[map];
            kind = 0;
            while (spawnedKind[kind] >= row[kind]) {
                kind++;
            }
            spawnedKind[kind]++;
            if (defs[kind] == 0) {
                kind = func_020a5ec0() & 1;
            }
        } else {
            kind = spawned < data_020ae5cc[map][3] + 10 ? 3 : 4;
        }
        catches[spawned++].func_0200becc(kind);
    }
    bool all = spawned == total;
    for (int i = 0; i < 15; i++) {
        all = all & catches[i].func_idle();
    }
    bool last = !(player.state != TP[8]);
    if ((all & last) == 1) {
        state = TG[2];
    }
}

inline void Unk0200c308::func_play(int i, bool force) {
    if (!force && index == i) {
        return;
    }
    index = i;
    Unk020a7c90 **s = (Unk020a7c90 **)func_00();
    func_020a6980(s[0], anims[index]);
    func_020a6980(s[1], anims[index]);
    func_0200b120(&anim);
    if (file != 0) {
        func_020a6058(game, file);
    }
    file = func_020a6038(game, func_020a69a4(sprites[0]));
    func_0200b09c(&anim, file);
}

void Unk0200c308::func_0200becc(int kind) {
    Unk0200dd50 view;
    func_0200dd50(&view, game->defs[kind]);
    func_0200ada4(this, &view);
    for (int i = 0; i < 2; i++) {
        *(Unk0201a4e0RectWrap *)&rects[i] = *(Unk0201a4e0RectWrap *)&game->rects[i];
    }
    move.unk14 = (int)(((s64)(0x1000 - func_0200e0fc(&view)) << 12) >> 12);
    move.speed = func_0200e120(&view);
    func_020acbc8(&move.dir);
    u16 a = func_020a5ec0();
    u16 b = a + 0x8000 + (func_020a5ef0(0, 0x4000) - 0x2000);
    int r = T.radius;
    Unk02098e70 c(0x80000, 0x60000);
    int d = kind >= 3 ? r : func_020a5ec0() & 0x3f;
    func_set(unkb0, c.func_02098fa8(Unk02098e70(d * func_sin(a), d * func_cos(a))));
    func_set(unka0, c.func_02098fa8(Unk02098e70(r * func_sin(b), r * func_cos(b))));
    func_set(unka8, unka0.func_02098fcc(unkb0).func_02098eec());
    func_set(pos, unkb0);
    func_set(target, unka0);
    u32 k = func_0200afc0(&view);
    anims[0] = func_0209a3c4(k, "walk.nitro_map");
    anims[1] = func_0209a3c4(k, "splat.nitro_map");
    func_020a7d30(sprites[0], kind);
    func_play(0, true);
    func_0200dfc8(this, 1)->pos = Unk02098e70(0x4000, 0x4000);
    func_0200df10(this, 1, 0);
    State s = 0;
    switch (unkc0) {
    case (int)0x97de12bf:
        s = TF[9];
        break;
    case (int)0xcbd6cda5:
        s = TF[10];
        break;
    case 0x4c444ea5:
        s = TF[11];
        break;
    case 0x2743d311:
        s = TF[12];
        break;
    }
    angle = func_02097a58(unka8.x, -unka8.y);
    for (int i = 0; i < 2; i++) {
        func_020a9168(sprites[i], angle);
    }
    state = s;
    life = 0;
    func_0200de30(this);
    func_0200dd6c(&view);
}

void *Unk0200c308::func_00() {
    return sprites;
}

bool Unk0200c308::func_0200c310() {
    if (flags.func_get()) {
        if (hit(&touch, &scale, &pos, angle) == 1) {
            Unk0200cec8 *g = game;
            void *k = func_0200cb58();
            for (int i = 0; i < 5; i++) {
                if (g->defs[i] == k) {
                    Unk0200cec8Sound *sound = g->sound;
                    if (sound != 0) {
                        func_020a32ac(func_020a2994(), 0x34311573, sound->unk4, 0x7f, 0);
                    }
                    g->caught[i]++;
                    if (g->func_0200cb28() == 10) {
                        g->total += data_020ae5cc[g->map][3];
                    } else {
                        const int *row = data_020ae5cc[g->map];
                        if (row[3] + 10 == g->func_0200cb28()) {
                            g->total += row[4];
                        }
                    }
                    g->func_0200c550();
                    break;
                }
            }
            func_play(1, false);
            Unk020a7c90 **s = (Unk020a7c90 **)func_00();
            func_020a922c(s[0], 0xc);
            func_020a922c(s[1], 0xc);
            func_0200dfc8(this, 1)->flag = 0;
            state = TF[1];
            return true;
        }
        flags.func_clear();
    }
    return false;
}

#pragma dont_inline on
bool Unk0200cec8::func_0200c550() {
    if (spawned == total) {
        return false;
    }
    int kind;
    if (spawned < 10) {
        const int *row = data_020ae5cc[map];
        kind = 0;
        while (spawnedKind[kind] >= row[kind]) {
            kind++;
        }
        spawnedKind[kind]++;
        if (defs[kind] == 0) {
            kind = func_020a5ec0() & 1;
        }
    } else {
        kind = spawned < data_020ae5cc[map][3] + 10 ? 3 : 4;
    }
    Unk0200c308 *c = &catches[spawned++];
    Unk0200dd50 view;
    func_0200dd50(&view, c->game->defs[kind]);
    func_0200ada4(c, &view);
    for (int i = 0; i < 2; i++) {
        Unk0201a4e0Rect q;
        func_0200cb04(&q, c->game->rects[i]);
        c->rects[i].func_0200cae0(q);
    }
    c->move.unk14 = func_0200cad0(0x1000 - func_0200e0fc(&view), 0x1000);
    c->move.speed = func_0200e120(&view);
    func_020acbc8(&c->move.dir);
    u16 a = func_020a5ec0();
    u16 b = a + 0x8000 + (func_020a5ef0(0, 0x4000) - 0x2000);
    int r = T.radius;
    Unk02098e70 o(0x80000, 0x60000);
    int d = kind >= 3 ? r : func_020a5ec0() & 0x3f;
    int sa = func_0200cab0(a);
    Unk02098e70 v1(d * sa, d * func_0200ca88(a));
    Unk02098e70 p1 = func_0200ca7c(&o, v1);
    func_0200ca68(&c->unkb0, p1);
    int sb = func_0200cab0(b);
    Unk02098e70 v2(r * sb, r * func_0200ca88(b));
    Unk02098e70 p2 = func_0200ca7c(&o, v2);
    func_0200ca68(&c->unka0, p2);
    Unk02098e70 e = func_0200ca5c(&c->unka0, c->unkb0);
    func_0200ca68(&c->unka8, e.func_02098eec());
    func_0200ca68(&c->pos, c->unkb0);
    func_0200ca68(&c->target, c->unka0);
    u32 k = func_0200afc0(&view);
    c->anims[0] = func_0209a3c4(k, "walk.nitro_map");
    c->anims[1] = func_0209a3c4(k, "splat.nitro_map");
    func_020a7d30(c->sprites[0], kind);
    c->func_0200c9b8(0, true);
    Unk02098e70 sc(0x4000, 0x4000);
    func_0200ca68(&func_0200dfc8(c, 1)->pos, sc);
    func_0200df10(c, 1, 0);
    Unk0200c308::State s = 0;
    switch (c->unkc0) {
    case (int)0x97de12bf:
        s = TF[9];
        break;
    case (int)0xcbd6cda5:
        s = TF[10];
        break;
    case 0x4c444ea5:
        s = TF[11];
        break;
    case 0x2743d311:
        s = TF[12];
        break;
    }
    c->angle = func_02097a58(c->unka8.x, -c->unka8.y);
    for (int i = 0; i < 2; i++) {
        func_020a9168(c->sprites[i], c->angle);
    }
    c->func_0200c99c(s);
    c->life = 0;
    func_0200de30(c);
    func_0200dd6c(&view);
    return true;
}
#pragma dont_inline reset

void Unk0200c308::func_0200c99c(State s) {
    state = s;
}

void Unk0200c308::func_0200c9b8(int i, bool force) {
    func_play(i, force);
}

extern "C" Unk02098e70 func_0200ca5c(const Unk02098e70 *a, const Unk02098e70 &b) {
    return a->func_02098fcc(b);
}

extern "C" void func_0200ca68(Unk02098e70 *a, const Unk02098e70 &b) {
    func_set(*a, b);
}

extern "C" Unk02098e70 func_0200ca7c(const Unk02098e70 *a, const Unk02098e70 &b) {
    return a->func_02098fa8(b);
}

extern "C" int func_0200ca88(int angle) {
    return func_cos(angle);
}

extern "C" int func_0200cab0(int angle) {
    return func_sin(angle);
}

extern "C" int func_0200cad0(int a, int b) {
    return (int)(((s64)a * b) >> 12);
}

void Unk0201a4e0Rect::func_0200cae0(const Unk0201a4e0Rect &o) {
    a = o.a;
    b = o.b;
    c = o.c;
    d = o.d;
}

extern "C" void func_0200cb04(Unk0201a4e0Rect *r, const Unk0201a4e0Rect &o) {
    r->a = o.a;
    r->b = o.b;
    r->c = o.c;
    r->d = o.d;
}

int Unk0200cec8::func_0200cb28() {
    return func_sum();
}

void *Unk0200c308::func_0200cb58() {
    return (void *)key;
}

bool Unk0200c308::func_0200cb60() {
    return !(state != TF[8]);
}

void Unk0200c308::func_0200cba8() {
    int f = func_0200b150(&anim, 0x1000);
    for (int i = 0; i < 2; i++) {
        func_020a69ac(sprites[i], f);
    }
    if ((int)move.dir.func_02098e94() > 0x19a) {
        Unk02098e70 d = move.dir.func_02098f38();
        int to = func_02097a58(d.x, -d.y);
        angle = func_020a1e68(func_020a917c(sprites[0]), to, 0x1f4);
        for (int i = 0; i < 2; i++) {
            func_020a9168(sprites[i], angle);
        }
    }
}

void Unk0200cec8::func_0200cc60() {
    if (rub != -1) {
        func_020a34e4(func_020a2994(), rub);
    }
    for (int i = 0; i < 15; i++) {
        func_0200df10(&catches[i], 0, 1);
    }
    if (total == func_sum()) {
        func_020a716c(texts[0], 0x9e1);
        func_020a3858(func_020a2994(), 0xbe776b91, 0, 0, 0);
    } else if (func_sum() > 0) {
        func_020a716c(texts[0], 0x9e2);
    } else {
        func_020a716c(texts[0], 0x9e0);
    }
    int r = func_020a5ef0(3, 5);
    if (anim != r) {
        func_020a6340(this, data_020ae630, T.names[r], 0, 0);
        anim = r;
    }
    func_020a7cf0(texts[0], 1);
    buttons[0].func_18(1);
    clock.func_set(3, 0);
    state = TG[1];
}

void Unk0200cec8::func_0200ce18() {
    clock.func_tick();
    if (clock.v == 0) {
        state = 0;
    }
}

inline Unk0200cec8::Unk0200cec8(Unk02093648 *file, Unk0200cec8Arg *args, int n) : Unk020a5ccc(file, (int)args, n), layout(file, 0), state(0) {
    paused = 0;
    sound = 0;
    rub = -1;
    func_020a5ea4(&layout);
    for (int i = 0; i < n; i++) {
        if (args[i].key == 0x35c7a149) {
            func_020a62dc(this, func_0205fbf4(data_020c3fd4, args[i].value));
        }
    }
    sound = func_020a290c(func_020a2994(), 2);
    if (sound != 0) {
        func_020a3188(func_020a2994(), 0x28959cf0, sound->unk4);
        func_020a3188(func_020a2994(), 0x34311573, sound->unk4);
        rub = func_020a32ac(func_020a2994(), 0x28959cf0, sound->unk4, 0x7f, 0);
    }
}

Unk020a5ccc *func_0200cec8(Unk02093648 *file, Unk0200cec8Arg *args, int n) {
    return new Unk0200cec8(file, args, n);
}

Unk0200d090::~Unk0200d090() {
}

Unk0200c308::~Unk0200c308() {
    func_0200b120(&anim);
    if (file != 0) {
        func_020a6058(game, file);
    }
}

Unk0200c308::Unk0200c308() : Unk0200ad70(2), game(0), state(TF[14]), file(0) {
    index = 2;
}

void Unk0200cec8::func_0200d138(Unk020a7af4 *names) {
    sprite = func_020aa04c(&layout, func_020a7b50(names, 0x6f9e2311));
    texts[0] = func_020aa040(&layout, 4, func_020a7b50(names, 0xc4189d9c));
    texts[1] = func_020aa040(&layout, 4, func_020a7b50(names, 0xdc127127));
    texts[2] = func_020aa040(&layout, 4, func_020a7b50(names, 0xfd435bc9));
    texts[3] = func_020aa040(&layout, 4, func_020a7b50(names, 0xba4ed5b8));
    buttons[0].func_02050838(func_020aa040(&layout, 0xb, func_020a7b50(names, 0x4ec86058)), 0);
    buttons[1].func_02050838(func_020aa040(&layout, 0xb, func_020a7b50(names, 0x66c2a823)), 0);
    buttons[2].func_02050838(func_020aa040(&layout, 0xb, func_020a7b50(names, 0x254bb7bc)), 0);
    buttons[2].func_02050c48(0, 3, -1);
    buttons[3].func_02050838(func_020aa040(&layout, 0xb, func_020a7b50(names, 0x4eb9e48d)), 0);
    buttons[3].func_02050c48(0, 3, -1);
    u32 id0 = func_020a7b50(names, 0x611e8f21);
    func_020a7b50(names, 0x4ff10ee4);
    u32 id1 = func_020a7b50(names, 0xf25fcce1);
    func_020a7b50(names, 0x5dec82fb);
    Unk020a7c90 *a = func_020aa040(&layout, 1, id0);
    Unk020a7c90 *b = func_020aa040(&layout, 1, id1);
    Unk020a7c90 *icon = func_020aa040(&layout, 5, func_020a7b50(names, 0x4e9c9a0b));
    rects[0] = func_020a6438(this, &layout, names, 0xfe825036);
    rects[1] = func_020a6438(this, &layout, names, 0xc0c6810e);
    player.owner = this;
    player.state = TP[9];
    for (int i = 0; i < 15; i++) {
        Unk0200c308 *c = &catches[i];
        c->game = this;
        c->sprites[0] = a;
        c->sprites[1] = b;
        for (int j = 0; j < 2; j++) {
            c->rects[j] = c->game->rects[j];
        }
        func_0200df54(c);
        c->anim.mode = 1;
        c->state = TF[13];
        a = (Unk020a7c90 *)((u8 *)a + 0x44);
        b = (Unk020a7c90 *)((u8 *)b + 0x44);
    }
    for (int i = 0; i < 5; i++) {
        if (defs[i] != 0) {
            Unk0200dd50 view;
            func_0200dd50(&view, defs[i]);
            func_020a8064(icon, func_0200afd4(&view));
            func_0200dd6c(&view);
        }
        icon = (Unk020a7c90 *)((u8 *)icon + 0x2c);
    }
}

void Unk0200cec8::func_14() {
    Unk020a7af4Entry entries[0x3c];
    Unk020a7af4 names(entries, 0x3c);
    func_020aa42c(&layout);
    shown.v &= 1;
    func_020aba38(file, 0x62075f76, &layout, &names);
    spawned = 0;
    unk1700 = 1;
    total = 10;
    unk16e0 = 3;
    if ((int)((*(u32 *)(data_020d6298 + 4) & 0x7c0) >> 6) < 6) {
        shown.v |= 2;
    }
    int m;
    switch (data_020c3ba4.map) {
    case 4:
        m = 0;
        break;
    case 7:
        m = 1;
        break;
    case 0x10:
        m = 2;
        break;
    case 0x18:
        m = 3;
        break;
    case 0x1f:
        m = 4;
        break;
    default:
        m = 0;
        break;
    }
    const int *row = data_020ae568[m];
    for (int i = 0; i < 5; i++) {
        int n = row[i];
        spawnedKind[i] = 0;
        if (n == -1) {
            defs[i] = 0;
        } else {
            defs[i] = func_0205f6f8(data_020c3fc4, data_020ae52c[n]);
        }
    }
    map = m;
    for (int i = 0; i < 5; i++) {
        caught[i] = 0;
    }
    func_0200d138(&names);
    Unk020a7c90 *s = func_020aa040(&layout, 0xc, func_020a7b50(&names, func_0209a3c4(0xca93af1a, shown.v & 2 ? "Night" : "Day")));
    data_020be23c[0] = func_020a7a44(s) << 4;
    data_020be23c[1] = func_020a7a60(s) << 4;
    data_020be23c[2] = func_020a7a7c(s) << 4;
    void *g = func_0206bce0();
    Unk02098ff0 pos = data_020c43a8.func_04();
    Unk020987d8 plane = *func_0206af40((u8 *)g + 0x10, 0);
    func_0206af60((u8 *)g + 0x10, 0, &plane);
    for (int i = 0; i < 10; i++) {
        if (spawned != total) {
            int kind;
            if (spawned < 10) {
                const int *r = data_020ae5cc[map];
                kind = 0;
                while (spawnedKind[kind] >= r[kind]) {
                    kind++;
                }
                spawnedKind[kind]++;
                if (defs[kind] == 0) {
                    kind = func_020a5ec0() & 1;
                }
            } else {
                kind = spawned < data_020ae5cc[map][3] + 10 ? 3 : 4;
            }
            catches[spawned++].func_0200becc(kind);
        }
    }
    state = TG[6];
    if (shown.func_get()) {
        func_020aa06c(&layout, 1);
    }
}

bool Unk0200cec8::func_18() {
    if (!shown.func_get()) {
        return true;
    }
    func_020aa158(&layout);
    if (state == 0) {
        for (int i = 0; i < 5; i++) {
            void *def = defs[i];
            if (def != 0) {
                for (int j = 0; j < caught[i]; j++) {
                    func_02054c1c(data_020bfc9c, def, 0);
                }
            }
        }
        return false;
    }
    if (paused) {
        buttons[3].func_0c(buttons[2].func_0c(0));
        buttons[2].func_08();
        buttons[3].func_08();
        if (func_020972c0(3) || (buttons[2].touch.flags & 8) || (buttons[3].touch.flags & 8)) {
            buttons[1].func_18(0);
            buttons[2].func_18(0);
            buttons[3].func_18(0);
            func_020a7cf0(texts[1], 0);
            func_020a7cf0(texts[2], 0);
            func_020a7cf0(texts[3], 0);
            paused = 0;
            if (buttons[3].touch.flags & 8) {
                state = TG[0];
            }
        }
    } else if (func_020972c0(3) && !func_020a7d1c(texts[0]) && func_020a1280(func_020a18e4(), 2, 0)) {
        buttons[1].func_18(1);
        buttons[2].func_18(1);
        buttons[3].func_18(1);
        func_020a7cf0(texts[1], 1);
        func_020a7cf0(texts[2], 1);
        func_020a7cf0(texts[3], 1);
        paused = 1;
    } else {
        (this->*state)();
    }
    return true;
}

extern "C" Unk0200dd50 *func_0200dd50(Unk0200dd50 *v, void *def) {
    func_0200af18(v, def, 0x03e0cdc7);
    return v;
}

extern "C" Unk0200dd50 *func_0200dd6c(Unk0200dd50 *v) {
    func_0200af2c(v);
    return v;
}

extern "C" int func_02097acc(int x);

Unk020b7900 data_020b7900 = {
    func_02097acc(0x6400) + 0x26,
    {"idle", "grab", "grab2", "collect_success", "collect_success2"},
    {
        &Unk0200cec8::func_0200cc60, &Unk0200cec8::func_0200ce18, &Unk0200cec8::func_0200cc60,
        &Unk0200cec8::func_0200bab4, &Unk0200cec8::func_0200ba70, &Unk0200cec8::func_0200b9c0,
        &Unk0200cec8::func_0200b940,
    },
    {
        &Unk0200b75c::func_0200b75c, &Unk0200b75c::func_0200b910, &Unk0200b75c::func_0200b75c,
        &Unk0200b75c::func_0200b8f4, &Unk0200b75c::func_0200b8d8, &Unk0200b75c::func_0200b8a4,
        &Unk0200b75c::func_0200b7f8, &Unk0200b75c::func_0200b7c4, &Unk0200b75c::func_0200b7c4,
        &Unk0200b75c::func_0200b75c,
    },
    {
        &Unk0200c308::func_0200b3a0, &Unk0200c308::func_0200b3a0, &Unk0200c308::func_0200b700,
        &Unk0200c308::func_0200b674, &Unk0200c308::func_0200b488, &Unk0200c308::func_0200b420,
        &Unk0200c308::func_0200b3a4, &Unk0200c308::func_0200b3a0, &Unk0200c308::func_0200b3a0,
        &Unk0200c308::func_0200b334, &Unk0200c308::func_0200b310, &Unk0200c308::func_0200b2e4,
        &Unk0200c308::func_0200b298, &Unk0200c308::func_0200b268, &Unk0200c308::func_0200b3a0,
    },
    {0, 0, 0, 0, 0},
};
