/*
 * Unit 0x020142E0-0x02018668: the rod fishing microgame `Unk02015408` (its strings
 * name the "fishing_*" sounds and "mgpf*" idle animations), its three fish
 * `Unk02015790`, each driven by a pointer to member state function, and the line
 * `Unk0201567c`, a chain of sprites simulated between the rod tip and the hook. The
 * unit also holds the kept copies of the widget base slots 8, 10, 11, 14, 15, 18
 * and 19.
 *
 * Bounds: hypothesis. The start follows the empty function 0x020142DC of the
 * microgame base (`unit_02013F8C.cpp` ends at 0x020142E0), the end is
 * `unit_02018668.cpp`. `.data`: the pointer to member constants, three static
 * rectangles built by the static initializer, the sound name table, the vtables and
 * the strings. Real file name unknown.
 *
 * Not complete. Gaps: `func_02017588` (97.88 %: registers, stack slots, the bait
 * icon loop multiplies the index where ours steps a pointer), `func_02015844`
 * (99.47 %: stack slots of the temporaries),
 * `func_02015368` (the original writes the countdown through a second address),
 * `__sinit` (the second and third rectangles have their own pool entries in the
 * original), `func_02016484` (stack slots of the temporaries; the point loops index
 * the array like the original only with element stores) and smaller ones
 * (registers). Several `func_go*` helpers
 * exist only to place their pointer to member constant where the original has it: the
 * real form is unknown.
 */

#include "game/unk_microgame.h"
#include "game/unk_fishing.h"

/* A countdown: frames, seconds, minutes, hours, 6 bits each. */
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
    Unk0200f174(int h, int m, int s, int fr);
    void func_set(int s, int fr) {
        f.hours = 0;
        f.minutes = 0;
        f.seconds = s;
        f.frames = fr;
    }
    int func_get(int i) { return (int)*(volatile u32 *)&v >> (i * 6) & 0x3f; }
    void func_put(int i, int x) { volatile u32 *p = &v; u32 o = *p & ~(0x3f << (i * 6)); *p = o | x << (i * 6); }
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

/* The same with a destructor (the far empty function 0x0200D090). */
class Unk0200d090 : public Unk0200f174 {
public:
    Unk0200d090() {}
    ~Unk0200d090();
};

/* A movement limit: start, step, end and a period, in the static initializer. */
struct Unk02014394Rect {
    int a, b, c, d;

    Unk02014394Rect(int a, int b, int c, int d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};

/* A vector built from another one out of line. */
struct Unk02015830 {
    int x, y;

    Unk02015830(const Unk02098e70 &v);
    operator Unk02098e70 &() { return *(Unk02098e70 *)this; }
};

struct Unk02015670 {
    u32 v;

    Unk02015670();
    bool func_get() const { return v & 1; }
};

struct Unk02015408Arg {
    int key;
    int value;
};

class Unk02016074Camera {
public:
    virtual void func_00(Unk02098ff0 v);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 v);
    virtual Unk02098ff0 func_0c();
};

class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    void *head;
    int count;
};

struct Unk020bfc9c;

extern "C" {
int func_02011188(int *counts);
void func_0200b09c(Unk0200b04c *a, int id);
void func_0200b120(Unk0200b04c *a);
int func_0200b150(Unk0200b04c *a, int f);
void func_0200de30(Unk0200dd90 *e);
void func_0200df10(Unk0200dd90 *e, int a, int b);
void func_0200df54(Unk0200dd90 *e);
Unk0200dd90Part *func_0200dfc8(Unk0200dd90 *e, int i);
int func_0200dfd8(Unk0200dd90 *e, Unk02098e70 *v, int d);
void func_0200e010(Unk0200dd90 *e, Unk02098e70 *v, void *r, int a);
void func_02010954(Unk02010920 *e, void *def);
void func_02010b8c(void *def, int a);
void func_02010ba8(void *def);
u32 func_0200afc0(void *def);
int func_0200afd4(void *def);
void func_02010c74(int a, int b, int c, int *out, int n);
void func_02010f40(Unk020a9d58 *l, Unk020a7af4 *n, Unk020a7c90 *s);
void func_02011010();
void func_02011074(void *a, void *b, void *c);
void func_02011128(int *a, int *b);
void func_020a6058(void *g, int id);
int func_020a6038(void *g, int hash);
void func_020a62f0(void *g);
void func_020a6114(void *g, u32 a, u32 b);
void func_020a6340(void *g, u32 hash, const char *name, int a, int b);
int func_020a5ef0(int a, int b);
Unk02098e70 func_020a5f28(int a, int b);
int func_020a60bc();
int func_020a60e8();
int func_020a655c();
int func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int f);
int func_020a69cc(Unk020a7c90 *s);
int func_020a69d4(Unk020a7c90 *s);
void func_020a69dc(Unk020a7c90 *s);
void func_020a716c(Unk020a7c90 *s, int id);
void func_020a7cc8(Unk020a7c90 *s, int x, int y);
void func_020a7d30(Unk020a7c90 *s, int x);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a8048(Unk020a7c90 *s, u32 hash);
void func_020a8064(Unk020a7c90 *s, int x);
int func_020a917c(Unk020a7c90 *s);
void func_020a9168(Unk020a7c90 *s, int a);
void func_020a9184(Unk020a7c90 *s, int a);
void func_020a91ac(Unk020a7c90 *s, int a);
void func_020a91ec(Unk020a7c90 *s, int a);
void func_020aa1c0(Unk020a9d58 *l, Unk02098e70 *p, int down);
void func_020aa42c(Unk020a9d58 *l);
int func_020a18e4();
int func_020a1280(int a, int b, int c);
int func_020a13d4(int a, int b, int c);
int func_020a1e68(int a, int b, int c);
int func_020a2994();
void func_020a3858(int a, u32 h, int b, int c, int d);
int func_02097a58(int a, int b);
u32 func_0209a3c4(u32 h, const char *s);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
int *func_02054858(Unk020547f8 *list, int index);
int func_0205d234(int a, u32 b, u32 c);
void func_02069124(void *a, int b, int c, int d);
int func_02066704(void *a, int b, int c);
void G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
int func_02077ae4(int a, int b);
int func_02077b3c(int a, int b);
extern u8 data_020c43a8[];
extern u8 data_020c44a8[];
extern Unk020bfc9c data_020bfc9c;
extern const u32 data_020ae7e0[];
}
int *func_02097a4c();
int func_020978dc(int a);
int func_020972c0(int key);

inline Unk02098e70 func_position(Unk020a7c90 *const &s) {
    int x = func_020a7ca4(s);
    return Unk02098e70(x, func_020a7cc0(s));
}

inline u16 func_id(u32 x) { return x; }
inline Unk020a7c90 *func_get1(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 1, i); }
inline Unk020a7c90 *func_get2(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 2, i); }
inline Unk020a7c90 *func_get4(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 4, i); }
inline Unk020a7c90 *func_get5(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 5, i); }
inline Unk020a7c90 *func_get11(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 0xb, i); }

extern const Unk02014394Rect data_020b8188;
extern const Unk02014394Rect data_020b8198;
extern const Unk02014394Rect data_020b81a8;

class Unk02015408;
class Unk0201567c;

class Unk02015790 : public Unk02010920 {
public:
    Unk02015790();
    ~Unk02015790();
    void *func_00() { return sprites; }
    bool func_04(int index, bool force);

    void func_020142e0();
    void func_02014318() {}
    void func_0201431c();
    void func_02014394();
    void func_020144f8();
    void func_0201456c();
    void func_02014888();
    void func_02014b2c();
    void func_02014c40();
    void func_02014ce0();
    void func_02014d44();
    void func_02014e28();
    void func_020173f4();
    bool func_020174a4(Unk0201567c *line);

    void func_part(int i, bool on) { func_0200dfc8(this, i)->flag = on; }
    bool func_near();
    bool func_wants();
    void func_caught();
    void func_goFlee();
    void func_goFall();
    void func_goIdle();
    void func_goBite();
    void func_goHook();
    void func_goFlee2();
    void func_goStart();
    void func_escape();
    bool func_is56c() { return state == &Unk02015790::func_0201456c; }
    void func_init(Unk02015408 *o, Unk020a7c90 *a, Unk020a7c90 *b, Unk020a7c90 *c, Unk020a7c90 *d) {
        owner = o;
        sprites[0] = a;
        sprites[1] = b;
        sprites[2] = c;
        sprites[3] = d;
        func_0200df54(this);
        state = &Unk02015790::func_020142e0;
    }
    void func_start() {
        state = &Unk02015790::func_0201431c;
    }
    bool func_dead() { return state == &Unk02015790::func_02014318; }
    bool func_is394() { return state == &Unk02015790::func_02014394; }

    Unk02015408 *owner;
    Unk02098e70 target;
    int fade;
    int unkfc;
    Unk020a7c90 *sprites[4];
    Unk0200b04c anim;
    int id;
    Unk0200b04cBit flags;
    void (Unk02015790::*state)();
    Unk0200d090 time[2];
    int timer;
};

class Unk0201567c {
public:
    Unk0201567c();
    void func_02015844();
    void func_reset() {
        state = 0;
        func_set(tail, Unk02098e70(0, 0));
        for (u32 i = 0; i < 29; i++) {
            func_020a7cf0(sprites[i], false);
        }
        panel.func_18(false);
    }

    int state;
    Unk02015408 *owner;
    Unk02098e70 base;
    int unk10;
    Unk02015790 *fish;
    Unk020a7c90 *sprites[29];
    Unk02051704 panel;
    Unk02098e70 points[8];
    Unk02098e70 tail;
    Unk02098e70 vel;
    u8 timer;
};

class Unk02015408 : public Unk020a5ccc {
public:
    Unk02015408(Unk02093648 *file, int a, int b);
    virtual ~Unk02015408();
    virtual bool func_08();
    virtual void func_10(bool a);
    virtual void func_14();
    virtual bool func_18();
    virtual void func_1c();

    void func_02015194();
    void func_02015368();
    void func_02015dd8(int index, int a, bool force, int b);
    void func_02015e28(int lo, int hi, int a, bool force, int b);
    void func_02015e60();
    void func_02016074();
    void func_020161a0();
    void func_02016208();
    void func_02016484();
    void func_02017588(Unk020a7af4 *names);
    void func_02017f54(int x, int y);

    bool func_all() { return func_02011188(counts) == 6; }
    void func_splash0(Unk02098e70 p) {
        func_020a7c90(rod, p.x);
        func_020a7cac(rod, p.y);
        func_0200b09c(&anims[0], ids[0]);
    }
    void func_splash1(Unk02098e70 p) {
        func_020a7c90(rod2, p.x);
        func_020a7cac(rod2, p.y);
        func_0200b09c(&anims[1], ids[1]);
    }
    bool func_spawn(int flag);
    void func_goEnd();
    void func_bite();

    Unk020a9d58 *layouts[2];
    Unk020a9d58 layout0;
    Unk020a9d58 layout1;
    Unk020a7c90 *unk138;
    Unk020a7c90 *rod;
    Unk020a7c90 *rod2;
    Unk020a7c90 *marker;
    Unk020a7c90 *bait0;
    Unk020a7c90 *bait1;
    Unk020a7c90 *unk150[12];
    Unk020a7c90 *unk180[36];
    Unk020a7c90 *result;
    Unk020a7c90 *unk214;
    Unk020a7c90 *unk218;
    Unk020a7c90 *unk21c;
    Unk02050640 buttons[4];
    Unk02051704 panel0;
    Unk02051704 panel1;
    Unk02015830 scroll;
    Unk02050640 button;
    signed char bait;
    u8 baits[16];
    int ids[2];
    Unk02015790 fish[3];
    Unk0201567c line;
    u32 mode;
    int depth;
    int score;
    int delay;
    int counts[3];
    void (Unk02015408::*state)();
    Unk0200f174 time;
    Unk02015670 shown;
    Unk0200b04c anims[2];
    int unkb08;
    u8 flash;
    int sound;
    int kinds[3];
    Unk020a7c90 *splash;
    Unk02015830 wind;
    u8 gust;
    u8 hidden;
};

inline bool Unk02015790::func_near() {
    Unk0201567c *l = &owner->line;
    bool near = false;
    if (l->state == 2 && l->fish == 0) {
        Unk02098e70 p = func_position(l->sprites[28]);
        if (func_0200dfd8(this, &p, 0x1000000) != 0) {
            near = true;
        }
    }
    return near;
}

inline bool Unk02015790::func_wants() {
    return bait == -1 || bait == owner->bait;
}

void Unk02015790::func_020142e0() {
    func_0200df10(this, 0, 1);
    timer = 900;
    state = &Unk02015790::func_02014318;
}

inline void Unk02015790::func_0201431c() {
    func_0200dfc8(this, 2)->flag = 0;
    func_0200dfc8(this, 3)->flag = 0;
    func_set(target, func_020a5f28(1, 0x20000));
    state = &Unk02015790::func_02014394;
}

/*
 * The two states set below: the original lays their constants out in the reverse of
 * the code order, as helpers defined here do (hypothesis on the form).
 */
inline void Unk02015790::func_goFlee() {
    state = &Unk02015790::func_02014c40;
}

inline void Unk02015790::func_goBite() {
    state = &Unk02015790::func_020144f8;
}

void Unk02015790::func_02014394() {
    Unk0201567c *l = &owner->line;
    bool near = false;
    if (l->state == 2 && l->fish == 0) {
        Unk02098e70 p = func_position(l->sprites[28]);
        if (func_0200dfd8(this, &p, 0x1000000) != 0) {
            near = true;
        }
    }
    if (near == 1) {
        func_goBite();
    } else if (func_0200dfd8(this, &target, 0xa000) == 1) {
        func_0201431c();
    } else if (timer == 0) {
        func_goFlee();
    } else {
        timer--;
        func_0200e010(this, &target, (void *)&data_020b8188, 1);
    }
}

void Unk02015790::func_020144f8() {
    func_0200dfc8(this, 2)->flag = 1;
    func_0200dfc8(this, 2)->unk10 = 0;
    if (bait != -1) {
        func_0200dfc8(this, 3)->flag = 1;
    }
    state = &Unk02015790::func_0201456c;
}

inline void Unk02015790::func_goHook() {
    state = &Unk02015790::func_02014888;
}

inline void Unk02015790::func_goFlee2() {
    state = &Unk02015790::func_02014c40;
}

inline void Unk02015790::func_goStart() {
    state = &Unk02015790::func_0201431c;
}

void Unk02015790::func_0201456c() {
    Unk0201567c *l = &owner->line;
    bool near = func_near();
    if (!near) {
        func_goStart();
    } else if (l->vel.func_02098e94() > 0x6000) {
        for (int i = 0; i < 3; i++) {
            Unk02015408 *g = owner;
            if (g->fish[i].func_dead() == 0) {
                g->fish[i].func_goFlee2();
            }
        }
    } else if (func_wants() && func_020174a4(l) == 1) {
        func_goHook();
    } else {
        Unk02098e70 p = func_position(l->sprites[28]);
        Unk02098e70 d = p.func_02098fcc(pos);
        if (func_wants() && d.func_02098e94() < 0x400000) {
            func_0200dfc8(this, 2)->unk10 = 1;
            func_0200dfc8(this, 3)->flag = 0;
        } else {
            func_0200dfc8(this, 2)->unk10 = 0;
            if (bait != -1) {
                func_0200dfc8(this, 3)->flag = 1;
            }
        }
        func_0200e010(this, &target, (void *)&data_020b8188, 1);
    }
    if (time[0].v != 0) {
        time[0].func_tick();
    }
}

inline void Unk02015408::func_bite() {
    func_020a7cf0(marker, true);
    Unk02098e70 y = func_position(line.sprites[28]);
    Unk02098e70 x = func_position(line.sprites[28]);
    Unk02098e70 p((x.x & 0x1000) >> 12 << 20, ((y.y & 0x1000) >> 12) * 3 << 18);
    Unk02098e70 a = func_position(line.sprites[28]);
    int d = p.x - a.x;
    if (d <= 0) {
        d = -d;
    }
    if (d < 0x80000) {
        Unk02098e70 b = func_position(line.sprites[28]);
        d = p.y - b.y;
        if (d <= 0) {
            d = -d;
        }
        if (d < 0x60000) {
            p.x = 0x100000 - p.x;
        }
    }
    if (p.x < 0x80000) {
        func_020a91ac(marker, 0);
        p.x -= 0x40000;
    } else {
        func_020a91ac(marker, 1);
    }
    if (p.y < 0x60000) {
        func_020a91ec(marker, 0);
        p.y -= 0x40000;
    } else {
        func_020a91ec(marker, 1);
    }
    func_020a7c90(marker, p.x);
    func_020a7cac(marker, p.y);
}

void Unk02015790::func_02014888() {
    func_0200dfc8(this, 2)->flag = 0;
    func_0200dfc8(this, 3)->flag = 0;
    Unk0201567c *l = &owner->line;
    l->fish = this;
    l->owner->func_02015e28(0xf, 0x13, 0, 0, 0);
    l->owner->func_splash0(func_position(l->sprites[28]));
    l->owner->func_bite();
    func_020a69ac(l->sprites[28], 0x12);
    time[0].func_set(3, 0);
    fade = 0x1000;
    func_020a3858(func_020a2994(), 0x876da727, 0, 0, 0);
    state = &Unk02015790::func_02014b2c;
}

void Unk02015790::func_02014b2c() {
    if (fade > 0) {
        func_020a7cf0(owner->splash, true);
        int t = pos.x - 0x10000;
        func_020a7c90(owner->splash, t - (((0x1000 - fade) << 5) >> 1));
        func_020a7cac(owner->splash, pos.y - 0x10000);
        func_020a9184(owner->splash, fade >> 4);
        Unk0201567c *l = &owner->line;
        func_set(pos, func_position(l->sprites[28]));
        fade -= 20;
    } else {
        owner->line.fish = 0;
        func_020a7cf0(owner->splash, false);
        state = &Unk02015790::func_02014c40;
        func_020a3858(func_020a2994(), 0x6fb35c8e, 0, 0, 0);
    }
}

void Unk02015790::func_02014c40() {
    func_0200dfc8(this, 2)->flag = 1;
    func_0200dfc8(this, 2)->unk10 = 2;
    func_0200dfc8(this, 3)->flag = 0;
    move.speed = move.speed * 3 / 4;
    func_set(target, func_020a5f28(0, 0x20000));
    state = &Unk02015790::func_02014ce0;
}

inline void Unk02015790::func_goFall() {
    state = &Unk02015790::func_02014e28;
}

inline void Unk02015790::func_goIdle() {
    state = &Unk02015790::func_020142e0;
}

void Unk02015790::func_02014ce0() {
    if (func_0200dfd8(this, &target, 0xa000) == 1) {
        func_020a7cf0(owner->splash, false);
        state = &Unk02015790::func_020142e0;
    } else {
        func_0200e010(this, &target, (void *)&data_020b81a8, 1);
    }
}

void Unk02015790::func_02014d44() {
    flags.v |= 1;
    Unk02015408 *g = owner;
    Unk02098e70 v = func_position(g->marker);
    Unk02098e70 *q = &v;
    if (q->x < 0x80000) {
        move.dir.x = func_02077b3c(-pos.x, 0x3c);
    } else {
        move.dir.x = func_02077b3c(0x100000 - pos.x, 0x3c);
    }
    if (q->y < 0x60000) {
        move.dir.y = func_02077b3c(-pos.y, 0x3c);
    } else {
        move.dir.y = func_02077b3c(0xc0000 - pos.y, 0x3c);
    }
    owner->line.fish = 0;
    func_goFall();
    func_020a3858(func_020a2994(), 0x2e337af8, 0, 0, 0);
}

inline bool Unk02015408::func_spawn(int flag) {
    if (score == 6) {
        return false;
    }
    int n = -1;
    for (int i = 0; i < 3; i++) {
        if (fish[i].func_dead() == 1) {
            n = i;
            break;
        }
    }
    if (n == -1) {
        return false;
    }
    int k = func_020a5ef0(0, 3);
    u8 def[8];
    func_02010b8c(def, kinds[k]);
    func_02010954(&fish[n], def);
    func_02010ba8(def);
    func_020a7d30(fish[n].sprites[0], k);
    fish[n].func_04(0, true);
    func_set(*(Unk02098e70 *)func_0200dfc8(&fish[n], 1), Unk02098e70(0x10000, 0x10000));
    Unk0200dd90Part *p = func_0200dfc8(&fish[n], 2);
    p->flags |= 2;
    p->flag = 0;
    func_set(*(Unk02098e70 *)func_0200dfc8(&fish[n], 2), Unk02098e70(0x8000, -0x14000));
    p = func_0200dfc8(&fish[n], 3);
    p->flags |= 2;
    p->flag = 0;
    func_set(*(Unk02098e70 *)func_0200dfc8(&fish[n], 3), Unk02098e70(-0x18000, -0x14000));
    if (fish[n].bait != -1) {
        int a = func_02077ae4(fish[n].bait, 4);
        func_0200dfc8(&fish[n], 3)->unk10 = a;
        int b = func_02077b3c(fish[n].bait, 4);
        func_0200dfc8(&fish[n], 3)->unk14 = b + 8;
    }
    func_0200df10(&fish[n], 1, 0);
    fish[n].func_start();
    fish[n].unkfc = 0;
    fish[n].flags.v = 0;
    score++;
    if (flag == 1) {
        delay = 240;
    }
    return true;
}

void Unk02015790::func_02014e28() {
    if (!func_020a7d1c(owner->marker)) {
        func_goIdle();
        Unk02015408 *g = owner;
        for (int i = 0; i < 3; i++) {
            int kind = g->kinds[i];
            if (kind == key) {
                g->counts[i]++;
                g->func_spawn(0);
                return;
            }
        }
    } else {
        pos.x += move.dir.x;
        pos.y += move.dir.y;
    }
}

inline void Unk02015790::func_caught() {
    func_020a7cf0(owner->splash, false);
    state = &Unk02015790::func_02014d44;
}

inline void Unk02015790::func_escape() {
    func_020a7cf0(owner->splash, false);
    state = &Unk02015790::func_02014c40;
}

bool Unk02015790::func_04(int index, bool force) {
    if (!Unk02010920::func_04(index, force)) {
        return false;
    }
    if (id != 0) {
        func_020a6058(owner, id);
    }
    id = func_020a6038(owner, func_020a69a4(sprites[0]));
    func_0200b09c(&anim, id);
    return true;
}

void Unk02015408::func_02015194() {
    line.func_reset();
    for (int i = 0; i < 3; i++) {
        func_0200df10(&fish[i], 0, 1);
    }
    if (func_all()) {
        func_020a716c(result, 0x9e1);
        func_020a3858(func_020a2994(), 0xbe776b91, 0, 0, 0);
        func_02015dd8(0x1a, 0, 0, 0);
    } else if (func_02011188(counts) > 0) {
        func_020a716c(result, 0x9e2);
        func_02015dd8(func_02011188(counts) > 1 ? 0x19 : 0x18, 0, 0, 0);
    } else {
        func_020a716c(result, 0x9e0);
        func_02015dd8(0x1b, 0, 0, 0);
    }
    func_020a7cf0(result, true);
    buttons[0].func_18(true);
    time.func_set(3, 0);
    state = &Unk02015408::func_02015368;
}

void Unk02015408::func_02015368() {
    time.func_tick();
    if (time.v == 0) {
        state = 0;
    }
}

/* Set from func_18, but its constant comes here in the original. */
inline void Unk02015408::func_goEnd() {
    state = &Unk02015408::func_02015194;
}

inline Unk02015790::Unk02015790() : Unk02010920(4), owner(0), id(0), state(&Unk02015790::func_02014318) {}

inline Unk02015408::Unk02015408(Unk02093648 *file, int a, int b)
    : Unk020a5ccc(file, a, b), layout0(file, 0), layout1(file, 0), scroll(Unk02098e70(0, 0)), bait(-1),
      mode(0x694ac647), state(0), time(0, 0, 0, 0), wind(Unk02098e70(0, 0)), gust(0), hidden(0) {
    for (u32 i = 0; i < 16; i++) {
        baits[i] = 0;
    }
    func_020a5ea4(&layout0);
    layouts[0] = &layout0;
    layouts[1] = &layout1;
    for (int i = 0; i < 2; i++) {
        ids[i] = 0;
    }
    Unk02015408Arg *args = (Unk02015408Arg *)a;
    for (int i = 0; i < b; i++) {
        if (args[i].key == 0x6e48cc6d) {
            if (args[i].value == 0x04dfd3c1) {
                mode = 0x694ac647;
            } else if (args[i].value == 0x55b52658) {
                mode = 0x55b52658;
            }
        }
    }
}

extern "C" Unk02015408 *func_02015408(Unk02093648 *file, int a, int b) {
    return new Unk02015408(file, a, b);
}

Unk02015670::Unk02015670() {
    v = 0;
}

inline Unk0201567c::Unk0201567c() : state(0), unk10(0) {
    Unk02098e70 t0(0, 0);
    *(Unk02098e70Wrap *)&tail = *(Unk02098e70Wrap *)&t0;
    Unk02098e70 t1(0, 0);
    *(Unk02098e70Wrap *)&vel = *(Unk02098e70Wrap *)&t1;
    u32 i = 0;
    timer = i;
    for (; i < 8; i++) {
        Unk02098e70 t(0x80000, 0x60000);
        ((Unk02098e70Wrap *)points)[i] = *(Unk02098e70Wrap *)&t;
    }
}

inline Unk02015790::~Unk02015790() {
    func_0200b120(&anim);
    if (id != 0) {
        func_020a6058(owner, id);
    }
}

const Unk02014394Rect data_020b8188(0, 1, 0x40000000, 8);
const Unk02014394Rect data_020b8198(0, 1, 0x1000000, 0xc);
const Unk02014394Rect data_020b81a8(0, 2, 0x40000000, 0x14);

Unk02015830::Unk02015830(const Unk02098e70 &v) {
    *(Unk02098e70Wrap *)this = *(Unk02098e70Wrap *)&v;
}

static inline void func_put(Unk02098e70 &d, const Unk02098e70 &s) {
    int x = s.x, y = s.y;
    d.x = x;
    d.y = y;
}

void Unk0201567c::func_02015844() {
    if (state == 0) {
        return;
    }
    switch (state) {
    case 1:
        func_set(points[0], base);
        panel.func_14(base.x, base.y);
        return;
    case 2:
        break;
    default:
        return;
    }
    Unk02098e70 *w = (Unk02098e70 *)&owner->wind;
    Unk02098e70 tip = func_position(sprites[28]).func_02098fa8(*w);
    func_set(tail, base.func_02098fcc(points[0]));
    func_set(points[0], base);
    if (tip.func_02098fa8(vel).func_02098fcc(points[0]).func_02098e94() < 0x1000000) {
        tip.x += vel.x;
        tip.y += vel.y;
    } else {
        func_set(vel, Unk02098e70(0, 0));
    }
    vel.func_02098ec0(0xfc3);
    int len2 = tip.func_02098fcc(points[0]).func_02098e94();
    int len = func_02097a6c(len2);
    Unk02098e70 dir = tip.func_02098fcc(points[0]).func_02098eec();
    if (len2 > 0x1000000) {
        Unk02098e70 m = dir;
        m.func_02098ec0(0x40000);
        Unk02098e70 p = points[0].func_02098fa8(m);
        Unk02098e70 q = p.func_02098fcc(tip);
        s64 l = q.func_02098e94();
        if (vel.func_02098e94() < l) {
            func_set(vel, q);
        }
        func_set(tip, p);
        func_set(dir, tip.func_02098fcc(points[0]).func_02098eec());
    } else if (len2 > 0x900000 && vel.func_02098e94() < 0x400) {
        func_set(vel, dir);
        vel.func_02098ec0(-len2 >> 12);
    }
    func_set(points[7], tip);
    int v = vel.func_02098e84();
    if (v > 0x9000) {
        vel.func_02098ec0(func_fxdiv(9, v));
    }
    panel.func_14(points[0].x, points[0].y);
    func_020a7cc8(sprites[0], points[0].x, points[0].y);
    func_020a7cc8(sprites[28], tip.x, tip.y);
    int step = func_02077b3c(len, 7);
    u32 i;
    int d = step;
    for (i = 1; i < 7; d += step, i++) {
        Unk02098e70 a = points[i];
        Unk02098e70 b = dir;
        b.func_02098ec0(d);
        Unk02098e70 c = points[0].func_02098fa8(b);
        int dist = c.func_02098fcc(a).func_02098e94();
        if (dist > 0x53978) {
            func_put(points[i], c.func_02098fa8(a.func_02098fcc(c).func_02098eec().func_02098ec0(0x9249)));
        } else if (dist > 0x4000) {
            func_put(points[i], a.func_02098fa8(c.func_02098fcc(a).func_02098eec().func_02098ec0(0x1000)));
        }
    }
    Unk02098e70 *p = points;
    u32 n = 0;
    for (u32 i = 0; i < 7; i++, p++, n += 4) {
        Unk02098e70 e;
        func_set(e, points[i + 1].func_02098fcc(*p).func_02098ec0(0x400));
        int dx = 0, dy = 0;
        for (u32 j = 0; j < 4; j++) {
            func_020a7cc8(sprites[n + j], p->x + dx, p->y + dy);
            dy += e.y;
            dx += e.x;
        }
    }
    if (timer == 0) {
        Unk020a7c90 *s = sprites[28];
        timer = 10;
        if (fish == 0) {
            int frame;
            if (func_020a69cc(s) >= 0x11) {
                frame = 10;
            } else {
                frame = func_020a69cc(s) + 1;
            }
            func_020a69ac(s, frame);
        } else {
            int frame;
            int f = func_020a69cc(s);
            if (f >= func_020a69d4(s) - 1) {
                frame = 0x14;
            } else {
                frame = func_020a69cc(s) + 1;
            }
            func_020a69ac(s, frame);
        }
    } else {
        timer--;
    }
}

void Unk02015408::func_02015dd8(int index, int a, bool force, int b) {
    static const char *data_020b81b8[28] = {
        "fishing_cast", "fishing_cast2", "fishing_cast3", "fishing_pullout1", "fishing_pullout2",
        "fishing_pullout_idle", "fishing_idle0", "mgpf26_looking_fish", "mgpf27_yawn", "mgpf28_scratching",
        "mgpf29_adjust_rod", "mgpf30_insect_bite", "mgpf31_look_around", "mgpf32_noddingoff", "mgpf33_needstoilet",
        "fishing_fishpull_idle", "fishing_fishpull", "fishing_fishpull2", "fishing_simpull", "fishing_simpull2",
        "fishing_escape", "fishing_escape2", "fishing_catch", "fishing_catch2", "fishing_victory",
        "fishing_bigvictory", "fishing_hugevictory", "fishing_fail",
    };
    static const u32 hash = 0xa030f2c3;
    if (force || sound != index) {
        func_020a6340(this, hash, data_020b81b8[index], a, b);
        sound = index;
    }
}

void Unk02015408::func_02015e28(int lo, int hi, int a, bool force, int b) {
    func_02015dd8(func_020a5ef0(lo, hi + 1), a, force, b);
}

void Unk02015408::func_02015e60() {
    switch (sound) {
    case 0:
    case 1:
    case 2:
    case 20:
    case 21:
        if (func_020a60bc() != 0) {
            func_02015dd8(6, 0, 0, 0);
        }
        break;
    case 3:
    case 4:
        if (func_020a60bc() != 0) {
            func_02015dd8(5, 1, 0, 0);
        }
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        if (func_020a60bc() != 0) {
            func_02015e28(6, 0xe, 0, 0, 0);
        }
        break;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        if (func_020a60bc() != 0) {
            if (line.fish == 0) {
                func_02015e28(6, 0xe, 0, 0, 0);
            } else {
                func_02015e28(0xf, 0x13, 0, 0, 10);
            }
        }
        break;
    case 22:
    case 23:
        if (func_020a60bc() != 0) {
            if (line.state != 0) {
                line.func_reset();
            }
            func_02015e28(3, 4, 0, 0, 0);
        }
        break;
    }
}

void Unk02015408::func_02016074() {
    if (func_020a13d4(func_020a18e4(), 2, 0) == 0) {
        return;
    }
    Unk02016074Camera *c = *(Unk02016074Camera **)(data_020c43a8 + 0xc);
    Unk02098ff0 a(0x1000, 0, 0);
    c->func_00(c->func_04().func_0209911c(a));
    Unk02098ff0 b(0, 0x8000, 0);
    c->func_08(c->func_0c().func_0209911c(b));
    func_020a6114(this, 0x665ae357, 0xf80d180b);
    func_02015e28(3, 4, 0, 1, 0);
    state = &Unk02015408::func_020161a0;
}

void Unk02015408::func_020161a0() {
    if (func_020a1280(func_020a18e4(), 2, 0) != 0) {
        G2x_SetBlendAlpha_(0x4001050, 0, 1, 0xf, 3);
        state = &Unk02015408::func_02016484;
    }
}

void Unk02015408::func_02016208() {
    Unk020a7c90 *s = marker;
    if (line.state != 2 || line.fish == 0) {
        bool hide = true;
        if (func_020a7ca4(s) > -0x40000 && func_020a7ca4(s) <= 0) {
            hide = false;
            func_020a7c90(s, func_020a7ca4(s) - 0x1000);
        } else if (func_020a7ca4(s) >= 0xc0000 && func_020a7ca4(s) < 0x100000) {
            hide = false;
            func_020a7c90(s, func_020a7ca4(s) + 0x1000);
        }
        if (func_020a7cc0(s) > -0x40000 && func_020a7cc0(s) <= 0) {
            hide = false;
            func_020a7cac(s, func_020a7cc0(s) - 0x1000);
        } else if (func_020a7cc0(s) >= 0x80000 && func_020a7cc0(s) < 0xc0000) {
            hide = false;
            func_020a7cac(s, func_020a7cc0(s) + 0x1000);
        }
        if (hide) {
            func_020a7cf0(s, false);
        }
    } else {
        if (func_020a7ca4(s) >= -0x40000 && func_020a7ca4(s) < 0) {
            func_020a7c90(s, func_020a7ca4(s) + 0x1000);
        } else if (func_020a7ca4(s) > 0xc0000 && func_020a7ca4(s) <= 0x100000) {
            func_020a7c90(s, func_020a7ca4(s) - 0x1000);
        }
        if (func_020a7cc0(s) >= -0x40000 && func_020a7cc0(s) < 0) {
            func_020a7cac(s, func_020a7cc0(s) + 0x1000);
        } else if (func_020a7cc0(s) > 0x80000 && func_020a7cc0(s) <= 0xc0000) {
            func_020a7cac(s, func_020a7cc0(s) - 0x1000);
        }
        if (flash == 0) {
            flash = 8;
            func_020a69dc(s);
        } else {
            flash--;
        }
    }
}

void Unk02015408::func_02016484() {
    int *touch = func_02097a4c();
    Unk02098e70 p(touch[0] << 12, touch[1] << 12);
    int pressed = func_020978dc(0);
    if (panel1.func_38() || panel1.func_4c()) {
        func_02017f54(touch[0], touch[1]);
    }
    int down = (pressed & (panel1.func_3c() || p.x < 0xdc000 || p.y > 0x84000)) != 0;
    for (int i = 0; i < 2; i++) {
        func_020aa1c0(layouts[i], &p, down);
    }
    if (down == 1) {
        switch (sound) {
        case 5:
            line.state = 1;
            line.fish = 0;
            func_set(line.base, Unk02098e70(0, -0x20000));
            for (u32 i = 0; i < 8; i++) {
                int x = line.base.x;
                int y = line.base.y;
                line.points[i].x = x;
                line.points[i].y = y;
            }
            line.panel.func_18(true);
            func_splash1(p);
            func_02015e28(0, 2, 0, 0, 0);
            break;
        case 0:
        case 1:
        case 2: {
            int t = 0xa000 - func_020a60e8();
            if (t >= 0) {
                func_set(line.base, Unk02098e70(p.x, p.y + func_fxmul(t, (0xc0000 - p.y) >> 3)));
                break;
            }
        }
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            if (line.state == 2) {
                if (func_020a7d1c(marker) &&
                    func_position(line.sprites[28]).func_02098fcc(func_position(marker)).func_02098e94() < 0x1000000) {
                    if (line.fish != 0) {
                        func_02015e28(0x16, 0x17, 0, 1, 0);
                        line.fish->func_caught();
                    } else {
                        func_02015e28(3, 4, 0, 0, 10);
                    }
                    line.func_reset();
                    break;
                }
                func_set(line.base, p);
            } else {
                Unk02098e70 q = p;
                line.state = 2;
                for (u32 i = 0; i < 29; i++) {
                    func_020a7cf0(line.sprites[i], true);
                    func_020a7cc8(line.sprites[i], q.x, q.y);
                }
                for (u32 i = 0; i < 8; i++) {
                    line.points[i] = q;
                }
                func_020a69ac(line.sprites[28], 0);
                func_set(line.vel, Unk02098e70(0, -0x1000));
                Unk02015790 *f = fish;
                for (u32 i = 0; i < 3; i++, f++) {
                    if ((f->func_is394() || f->func_is56c()) && f->func_0200df08()->func_02098fcc(p).func_02098e94() < 0x400000) {
                        f->state = &Unk02015790::func_02014c40;
                    }
                }
                func_set(line.base, p);
            }
            break;
        }
    } else if (line.state != 0) {
        func_02015e28(3, 4, 0, 0, 10);
        if (line.fish != 0) {
            line.fish->func_escape();
        }
        if (line.state == 2) {
            func_splash0(func_position(line.sprites[28]));
        }
        line.func_reset();
        panel1.func_28(8);
    }
    if (line.state != 0) {
        if (panel1.func_4c() || panel1.func_38()) {
            panel1.func_2c(8);
        }
    } else if ((panel1.func_48() || panel1.func_3c()) && !func_020a7d1c(marker)) {
        panel1.func_28(8);
    }
    if (gust == 0) {
        gust = func_020a5ef0(0x3c, 0x78);
        int x = func_020a5ef0(-0x199, 0x199);
        Unk02098e70 g(x, func_020a5ef0(-0x199, 0x199));
        wind.x += g.x;
        wind.y += g.y;
        func_set(wind, ((Unk02098e70 &)wind).func_02098f74(-0x800, 0x800));
    } else {
        gust--;
    }
    scroll.x += wind.x;
    scroll.y += wind.y;
    if (scroll.x > 0x40000) {
        scroll.x -= 0x80000;
    } else if (scroll.x < -0x40000) {
        scroll.x += 0x80000;
    }
    if (scroll.y > 0x40000) {
        scroll.y -= 0x80000;
    } else if (scroll.y < -0x40000) {
        scroll.y += 0x80000;
    }
    panel0.func_14(scroll.x, scroll.y);
    line.func_02015844();
    func_02016208();
    Unk02015790 *f = fish;
    for (int i = 0; i < 3; i++, f++) {
        func_0200de30(f);
        f->func_020173f4();
        (f->*(f->state))();
    }
    func_020a7cf0(rod, anims[0].playing.func_get());
    if (anims[0].playing.func_get()) {
        func_020a69ac(rod, func_0200b150(&anims[0], 0x1000));
    }
    func_020a7cf0(rod2, anims[1].playing.func_get());
    if (anims[1].playing.func_get()) {
        func_020a69ac(rod2, func_0200b150(&anims[1], 0x1000));
    }
    if (delay == 0) {
        func_spawn(1);
    } else {
        delay--;
    }
    bool done = score == 6;
    for (int i = 0; i < 3; i++) {
        done = done & fish[i].func_dead();
    }
    for (int i = 0; i < 2; i++) {
        done = done & !anims[i].playing.func_get();
    }
    if (done == 1) {
        state = &Unk02015408::func_02015194;
    }
}

bool Unk020b9e88::func_4c() {
    return state == 0;
}

bool Unk020b9e88::func_48() {
    return state == 3;
}

void Unk020b9e88::func_2c(int value) {
    duration = value;
    if (timer > duration) {
        timer = duration;
    }
    state = 3;
}

void Unk020b9e88::func_28(int value) {
    duration = value;
    if (timer > duration) {
        timer = duration;
    }
    state = 0;
}

bool Unk020b9e88::func_3c() {
    return state == 5 || state == 4;
}

bool Unk020b9e88::func_38() {
    return state == 2 || state == 1;
}

#pragma dont_inline on
void Unk02015408::func_14() {
    Unk020a7af4Entry entries[0x80];
    Unk020a7af4 names(entries, 0x80);
    int i;
    for (i = 0; i < 2; i++) {
        func_020aa42c(layouts[i]);
    }
    *(u32 *)&shown &= 1;
    for (i = 0; i < 2; i++) {
        func_0200b120(&anims[i]);
    }
    delay = 0;
    score = 0;
    depth = *(u16 *)(data_020c44a8 + 0xde);
    func_02010c74(depth, mode, func_020a655c(), kinds, 3);
    for (i = 0; i < 3; i++) {
        counts[i] = 0;
    }
    u32 maps[2] = {0x00fcb968, 0};
    maps[1] = func_0209a3c4(func_0209a3c4(0x373909a6, mode == 0x694ac647 ? "sea" : "lagoon"),
                            "/custom.visualisation.nitro_xml");
    for (i = 0; i < 2; i++) {
        func_020aba38(file, maps[i], layouts[i], &names);
    }
    func_02017588(&names);
    ids[0] = func_020a6038(this, func_020a69a4(rod));
    ids[1] = func_020a6038(this, func_020a69a4(rod2));
    unkb08 = 6;
    func_02011010();
    delay = 0;
    score = 0;
    for (i = 0; i < 3; i++) {
        counts[i] = 0;
    }
    if (shown.v & 1) {
        for (i = 0; i < 2; i++) {
            func_020aa06c(layouts[i], true);
        }
    }
    state = &Unk02015408::func_02016074;
}
#pragma dont_inline reset

void Unk02015790::func_020173f4() {
    int f = func_0200b150(&anim, 0x1000);
    func_020a69ac(sprites[0], f);
    func_020a69ac(sprites[1], f);
    move.dir.func_02098e94();
    Unk02098e70 d = move.dir.func_02098f38();
    int a = func_020a917c(sprites[0]);
    if (flags.v & 1) {
        a += 0x1000;
    } else {
        a = func_020a1e68(a, func_02097a58(d.x, -d.y), 500);
    }
    for (int i = 0; i < 2; i++) {
        func_020a9168(sprites[i], a);
    }
}

bool Unk02015790::func_020174a4(Unk0201567c *line) {
    if (line->fish != 0) {
        return false;
    }
    int f = scale.y == 0 ? 0x1000 : func_02077c60(0x1000, scale.y);
    Unk02098e70 d = target.func_02098fcc(pos).func_02098f38();
    Unk02098e70 a = pos.func_02098fa8(d.func_02098ec0(f));
    if ((int)func_position(line->sprites[28]).func_02098fcc(a).func_02098e94() > 0x40000) {
        return false;
    }
    return line->vel.func_02098e94() < 0x1800;
}

void Unk02015408::func_02017588(Unk020a7af4 *names) {
    Unk020a9d58 *l0 = layouts[0];
    Unk020a9d58 *l1 = layouts[1];
#define ID(h) func_id(func_020a7b50(names, h))
    rod = func_get1(l0, ID(0x3cb5044c));
    rod2 = func_get1(l0, ID(0xe434d171));
    marker = func_get1(l0, ID(0x1e5993c1));
    bait0 = func_get1(l0, ID(0xcf185704));
    bait1 = func_get1(l0, ID(0xaeb9a27d));
    result = func_get4(l0, ID(0xc4189d9c));
    unk214 = func_get4(l0, ID(0xdc127127));
    unk218 = func_get4(l0, ID(0xfd435bc9));
    unk21c = func_get4(l0, ID(0xba4ed5b8));
    buttons[0].func_02050838(func_get11(l0, ID(0x4ec86058)), false);
    buttons[1].func_02050838(func_get11(l0, ID(0x66c2a823)), false);
    buttons[2].func_02050838(func_get11(l0, ID(0x254bb7bc)), false);
    buttons[2].func_02050c48(0, 3, -1);
    buttons[3].func_02050838(func_get11(l0, ID(0x4eb9e48d)), false);
    buttons[3].func_02050c48(0, 3, -1);
    u8 *f0 = (u8 *)func_get1(l0, ID(0x3e74a03c));
    u8 *f1 = (u8 *)func_get1(l0, ID(0xdcb8bb7a));
    u8 *f2 = (u8 *)func_get1(l0, ID(0x98ad93db));
    u8 *f3 = (u8 *)func_get1(l0, ID(0xf40bcca0));
    u8 *chain = (u8 *)func_get1(l0, ID(0x06e4dc6c));
    splash = func_get1(l0, ID(0xf8fc96b7));
    Unk020a7c90 *t0 = func_get5(l0, ID(0x86deea9f));
    Unk020a7c90 *t1 = func_get5(l0, ID(0x0dcdfa5b));
    Unk020a7c90 *t2 = func_get5(l0, ID(0x61493f9c));
    panel0.func_14(0, 0);
    panel0.func_02051804(0x24);
    unk138 = func_get2(l1, ID(0x4b50843d));
    unk180[0] = func_get1(l1, ID(0x29f55a05));
    panel0.func_02051858(unk180[0]);
    for (u32 i = 1; i < 0x24; i++) {
        unk180[i] = (Unk020a7c90 *)((u8 *)unk180[0] + i * 0x44);
        panel0.func_02051858(unk180[i]);
    }
    unk150[0] = func_get1(l1, ID(0x2b8fe1af));
    for (u32 i = 1; i < 12; i++) {
        unk150[i] = (Unk020a7c90 *)((u8 *)unk150[0] + i * 0x44);
    }
    Unk020a7c90 *t3 = func_get5(l1, ID(0x2efb9952));
    Unk020a7c90 *t4 = func_get5(l1, ID(0x2d6111a8));
    line.panel.func_14(0, 0);
    line.panel.func_02051804(3);
    line.panel.func_02051858(func_get1(l0, ID(0x4423d42f)));
    line.panel.func_02051858(func_get1(l0, ID(0x4423d430)));
    line.panel.func_02051858(func_get1(l0, ID(0x4423d431)));
    panel1.func_14(0, 0);
    panel1.func_02051804(6);
    u8 *icons = (u8 *)func_get1(l0, ID(0xf7a3b5ca));
    Unk020a7c90 *s = func_get11(l0, ID(0x1db45113));
    button.func_02050838(s, false);
    panel1.func_02051858(s);
    panel1.func_02051858(bait1);
    u8 *icon = icons;
    for (u32 i = 0; i < 4; i++) {
        panel1.func_02051858((Unk020a7c90 *)icon);
        icon += 0x44;
    }
    panel1.func_20(0x24000, 0);
    Unk020547f8 list;
    func_02054d94(&data_020bfc9c, &list, data_020ae7e0, 1, 1);
    for (u32 i = 0; i < (u32)list.count; i++) {
        baits[func_0205d234(*func_02054858(&list, i), 0x03e0cdc7, 0x2b3e6dd7)] = 1;
    }
    int n = 0;
    for (u32 i = 0; i < 16; i += 4) {
        func_020a69ac((Unk020a7c90 *)(icons + n * 0x44),
                      (baits[i + 3] ? 8 : 0) + ((baits[i + 2] ? 4 : 0) + (baits[i] + (baits[i + 1] ? 2 : 0))));
        n++;
    }
    int lang = func_020a655c();
    func_020a8064(t1, lang);
    func_020a8064(t3, lang);
    func_020a8064(t4, lang);
    func_020a8064(t2, lang);
    func_02010f40(l1, names, t0);
    line.owner = this;
    for (u32 i = 0; i < 29; i++) {
        line.sprites[i] = (Unk020a7c90 *)chain;
        chain += 0x44;
    }
    line.func_reset();
    line.fish = 0;
    line.func_02015844();
    line.unk10 = 0;
    for (int i = 0; i < 3; i++) {
        Unk020a7c90 *a = (Unk020a7c90 *)f0;
        f0 += 0x44;
        Unk020a7c90 *b = (Unk020a7c90 *)f1;
        f1 += 0x44;
        Unk020a7c90 *c = (Unk020a7c90 *)f2;
        f2 += 0x44;
        Unk020a7c90 *d = (Unk020a7c90 *)f3;
        f3 += 0x44;
        fish[i].func_init(this, a, b, c, d);
        fish[i].anim.mode = 1;
    }
    for (int i = 0; i < 3; i++) {
        u8 def[8];
        func_02010b8c(def, kinds[i]);
        func_020a8048(t0, func_0209a3c4(func_0200afc0(def), "swim.nitro_map"));
        func_020a8064(t0, func_0200afd4(def));
        func_02010ba8(def);
        t0 = (Unk020a7c90 *)((u8 *)t0 + 0x2c);
    }
}

void Unk020b9e88::func_20(int x, int y) {
    valuesX[0] = x;
    valuesX[1] = y;
    trackX = &keysX;
}

void Unk02015408::func_02017f54(int x, int y) {
    button.func_0c(false);
    if (!(button.touch.flags & 4)) {
        return;
    }
    bait = (y >> 3) & ~1;
    if (x > 0xf0) {
        bait++;
    }
    while (bait > 0xf) {
        bait -= 2;
    }
    if (baits[bait] == 0) {
        bait = -1;
        func_020a7cf0(bait0, false);
        func_020a7cf0(bait1, false);
        return;
    }
    func_020a69ac(bait0, func_02077ae4(bait, 4));
    func_020a7d30(bait0, func_02077b3c(bait, 4) + 8);
    func_020a7cf0(bait0, true);
    func_020a7cac(bait1, (bait >> 2) << 17);
    func_020a69ac(bait1, func_02077ae4(bait, 4));
    func_020a7d30(bait1, func_02077b3c(bait, 4) + 8);
    func_020a7cf0(bait1, true);
}

Unk02015408::~Unk02015408() {
    for (int i = 0; i < 2; i++) {
        if (ids[i] != 0) {
            func_020a6058(this, ids[i]);
        }
    }
}

void Unk02015408::func_10(bool a) {
    if (a == shown.func_get()) {
        return;
    }
    *(u32 *)&shown ^= 1;
    for (int i = 0; i < 2; i++) {
        func_020aa06c(layouts[i], a);
    }
    if (shown.func_get()) {
        return;
    }
    func_020a62f0(this);
    func_02069124(*(void **)(data_020c43a8 + 0xc), 0, 0, 0);
    Unk02016074Camera *c = *(Unk02016074Camera **)(data_020c43a8 + 0xc);
    Unk02098ff0 d0(0x1000, 0, 0);
    c->func_00(c->func_04().func_02099150(d0));
    Unk02098ff0 d1(0, 0x8000, 0);
    c->func_08(c->func_0c().func_02099150(d1));
    void *o = *(void **)(data_020c43a8 + 0xc);
    func_02069124(o, func_02066704(data_020c43a8, 0x2c, 0), 0, 0);
}

bool Unk02015408::func_18() {
    if (!shown.func_get()) {
        return true;
    }
    for (int i = 0; i < 2; i++) {
        func_020aa158(layouts[i]);
    }
    if (state == 0) {
        func_02011128(counts, kinds);
        return false;
    }
    if (hidden != 0) {
        buttons[3].func_0c(buttons[2].func_0c(false));
        buttons[2].func_08();
        buttons[3].func_08();
        if (func_020972c0(3) != 0 || (buttons[2].touch.flags & 8) || (buttons[3].touch.flags & 8)) {
            buttons[1].func_18(false);
            buttons[2].func_18(false);
            buttons[3].func_18(false);
            func_020a7cf0(unk214, false);
            func_020a7cf0(unk218, false);
            func_020a7cf0(unk21c, false);
            hidden = 0;
            if (buttons[3].touch.flags & 8) {
                func_goEnd();
            }
        }
    } else if (func_020972c0(3) != 0 && !func_020a7d1c(result) && func_020a1280(func_020a18e4(), 2, 0) != 0) {
        buttons[1].func_18(true);
        buttons[2].func_18(true);
        buttons[3].func_18(true);
        func_020a7cf0(unk214, true);
        func_020a7cf0(unk218, true);
        func_020a7cf0(unk21c, true);
        hidden = 1;
    } else {
        (this->*state)();
        func_02015e60();
        panel1.func_08();
        func_02011074(unk150, unk180, &unkb08);
    }
    return true;
}

void Unk02015408::func_1c() {}

bool Unk02015408::func_08() {
    return func_02011188(counts) != 0;
}
