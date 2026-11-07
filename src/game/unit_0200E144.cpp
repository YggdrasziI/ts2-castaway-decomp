/*
 * Unit 0x0200E144-0x02010920: the fire making microgame `Unk0200ed88`: rub on the
 * touch screen to raise the fire gauge against a decay that depends on the map.
 * Strings: `fire_out` and `it20_fire_starting`.
 *
 * Bounds: hypothesis. The start is the first state of its table, the end the
 * deleting destructor of its vtable. Real file name unknown.
 *
 * Open gaps (same code, allocation or order): func_0200eb70 95.15 %, func_0200e1f8
 * 95.62 %, func_0200f250 96.49 %, func_14 97.12 %, D1 97.26 %, D0 97.33 %, func_18
 * 99.79 %. The key table data_020ae654 is defined at the end of the file: defined
 * before its users, the compiler reaches it from data_020ae63c plus an offset; the
 * class body func_14 still does (its body is compiled after the definition).
 */

#include "game/unk_microgame.h"
#include "game/unk_catalog.h"
#include "game/unk_objscript.h"
#include "game/unk_pool.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
};

class Unk02061d08Item {
public:
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    ~Unk02061d08Item();
    void *operator new(unsigned long size);
    void operator delete(void *p);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    int unk44;
    int unk48;
};

struct Unk02063d84;

struct Unk0200ed88Sound {
    int unk0;
    int unk4;
};

struct Unk0200ed88Arg {
    int key;
    int value;
};

/* The decay of the gauge per map. */
struct Unk0200ed88Rate {
    int unk0;
    int decay;
    int reach;
};

class Unk0200ed88Player {
public:
    void *func_020106c4() {
        return sim;
    }

    u8 unk0[0xc];
    void *sim;
};

class Unk0200ed88World {
public:
    int func_0200f154();

    u8 unk0[0xfc];
    s8 map;
};

class Unk0200ed88Flip {
public:
    u8 func_02010770() {
        return flipped;
    }

    u8 unk0[0x15c];
    u8 flipped;
};

class Unk0200ed88Touch {
public:
    bool func_02010728() {
        return flags & 1;
    }

    u8 unk0[0x18];
    u32 flags;
};

/* A cell built from its parts. */
struct Unk0200ed88Cell {
    Unk0200ed88Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

static inline Unk0200ed88Cell func_add(const Unk020680d4Cell &c, Unk020680d4Xy d) {
    return Unk0200ed88Cell(c.pos.unk3, c.pos.unk2, c.pos.unk0, c.xy.x + d.x, c.xy.y + d.y);
}

static inline Unk0200ed88Cell func_sub(const Unk0200ed88Cell &c, Unk020680d4Xy d) {
    return Unk0200ed88Cell(c.pos.unk3, c.pos.unk2, c.pos.unk0, c.xy.x - d.x, c.xy.y - d.y);
}

/* A clock: hours, minutes, seconds and frames, 6 bits each. */
class Unk0200f174 {
public:
    Unk0200f174(int h, int m, int s, int fr);

    u32 v;
};

class Unk0200f1a8 {
public:
    Unk0200f1a8();

    Unk02098e70 v;
};

extern "C" {
void *func_02063e2c(u32 key, int mode);
void func_02069124(void *a, void *b, int c, int d);
bool func_020691c4(void *sim);
int func_020a2994();
Unk0200ed88Sound *func_020a290c(int a, int b);
void func_020a2964(int a, Unk0200ed88Sound *b, int c);
void func_020a3188(int a, u32 h, int b);
int func_020a32ac(int a, u32 h, int b, int c, int d);
void func_020a34e4(int a, int h);
int func_020a3514(int a, int h);
void func_020a35a4(int a, int h, int v);
void func_020a3858(int a, u32 h, int b, int c, int d);
int func_020a18e4();
int func_020a1280(int a, int b, int c);
int func_020a13d4(int a, int b, int c);
void func_020a3f84(void *a, int b);
int func_020a5ec0();
int func_020a5ef0(int a, int b);
void func_020a69ac(Unk020a7c90 *s, int f);
int func_020a69cc(Unk020a7c90 *s);
void func_020a716c(Unk020a7c90 *s, int id);
void func_020a7b88(Unk020a7af4 *n);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a9198(Unk020a7c90 *s, int scale);
void func_020a91ac(Unk020a7c90 *s, int a);
void func_020a91ec(Unk020a7c90 *s, int a);
void func_020aa06c(Unk020a9d58 *layout, bool shown);
void func_020aa158(Unk020a9d58 *layout);
Unk020a7c90 *func_020aa04c(Unk020a9d58 *l, u32 id);
void func_020aa42c(Unk020a9d58 *l);
int func_020aba38(Unk02093648 *archive, u32 hash, Unk020a9d58 *layout, Unk020a7af4 *names);
u32 func_0209a32c(const char *str, u32 last, u32 end);
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
Unk02061d08Item *func_0205fbf4(void *m, int id);
void func_0205e3f0(Unk02061d08Item *item);
void func_0205e4d0(Unk02061d08Item *item);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
void *func_02007340(void *p, int kind);
void func_02007f84(void *list, void *o, int a);
bool func_0205d340(Unk0205cf00 *def, u32 key);
int func_0200cab0(int angle);
Unk020081dc func_020081dc(Unk0200ed88Player *p);
int func_02077c60(int a, int b);
void func_0205e3f0(Unk02061d08Item *item);
Unk020a5ccc *func_0200ed88(Unk02093648 *file, Unk0200ed88Arg *args, int n);
extern u8 data_020be184[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern Unk0200ed88Player data_020c43a8;
extern Unk0200ed88World data_020c3ba4;
extern u8 data_020c4770[];
extern u8 data_020d6298[];
extern Unk0200ed88Flip data_020d60c8;
extern Unk0200ed88Touch data_020d6cdc;
Unk0200ed88Player *func_0200f168();
void *func_0200f0d4();
Unk0200ed88World *func_0200f15c();
inline Unk0200ed88Flip *func_02010778() {
    return &data_020d60c8;
}
inline Unk0200ed88Touch *func_0201073c() {
    return &data_020d6cdc;
}
}
int *func_02097a4c();
int func_020978dc(int a);
int func_020972c0(int key);

static const u8 data_020ae634[6] = {8, 8, 5, 8, 8, 5};
static const Unk0200ed88Rate data_020ae63c = {4, 2, 0x18000};
static const Unk0200ed88Rate data_020ae648 = {6, 4, 0x10000};
extern const u32 data_020ae654[9];

static int data_020be2f4;
static int data_020be2f0;

#define FUNC_ABS(x) ((x) > 0 ? (x) : -(x))
#define FUNC_SHAKE(s, opx, opy)                         {                                                       int v = func_020a7ca4(s);                           func_020a7c90(s, v opx func_020a5ef0(0, 0x5000));         v = func_020a7cc0(s);                               func_020a7cac(s, v opy func_020a5ef0(0, 0x5000));     }

class Unk0200ed88 : public Unk020a5ccc {
public:
    typedef void (Unk0200ed88::*State)();

    Unk0200ed88(Unk02093648 *file, Unk0200ed88Arg *args, int n);

    void func_0200e144();
    void func_0200e190();
    void func_0200e1f8();
    void func_0200e9ec();
    void func_0200eb70();
    void func_0200f1ac();
    bool func_0200f250();
    void func_0200f470();
    void func_0200f4a4();

    void func_show(Unk020a7c90 *s) {
        func_020a7cf0(s, 1);
        func_020a69ac(s, 0);
        func_020a7c90(s, history[0].v.x);
        func_020a7cac(s, history[0].v.y);
        func_020a91ac(s, func_020a5ef0(0, 2) == 0);
        func_020a91ec(s, func_020a5ef0(0, 2) == 0);
    }

    void func_0200f0e0(int x, int y);

    virtual ~Unk0200ed88() {
        func_02069124(data_020c43a8.sim, 0, 0, 0);
        delete smoke;
        if (item->unk44 == 0) {
            func_0205e3f0(item);
        }
        if (value != 0x1000 && item != 0 && func_0205d340(item->def, 0xb592872e)) {
            Unk02061c04 runner(item);
            runner.func_02099ce0(0x7a111f56);
        }
        if (sound != 0) {
            func_020a2964(func_020a2994(), sound, 1);
            sound = 0;
        }
    }

    virtual void func_10(bool a) {
        func_020aa06c(&layout0, a);
        func_020aa06c(&layout1, a);
        if (!a) {
            func_0200f470();
            func_0200f4a4();
        }
    }

    Unk020a7c90 *func_named(u32 hash) {
        return func_020aa04c(&layout1, func_020a7b50(&names1, hash));
    }

    Unk020a7c90 *func_text(int type, u32 hash) {
        return func_020aa040(&layout1, type, func_020a7b50(&names1, hash));
    }

    virtual void func_14() {
        func_020aa42c(&layout0);
        func_020aa42c(&layout1);
        func_020a7b88(&names0);
        func_020a7b88(&names1);
        func_020aba38(file, (int)((*(u32 *)(data_020d6298 + 4) & 0x7c0) >> 6) >= 6 ? 0x9dd1e576 : 0xbc42d497, &layout0, &names0);
        func_020aba38(file, data_020d60c8.flipped != 0 ? 0xb271d3f2 : 0x224bafd8, &layout1, &names1);
        sprites[0] = func_named(0x4ab25202);
        gaugeY = func_020a7cc0(sprites[0]);
        sprites[1] = func_named(0x3821fa2e);
        sprites[2] = func_named(0xb71f6e57);
        sprites[3] = func_named(0x5631c8d1);
        sprites[4] = func_named(0x00ea2b48);
        sprites[5] = func_named(0xd24d3b6d);
        sprites[6] = func_named(0xa89a355f);
        sprites[7] = func_named(0xa89a3560);
        sprites[8] = func_named(0xa89a3561);
        sprites[9] = func_named(0xa89a3562);
        sprites[10] = func_named(0xa89a3563);
        sprites[11] = func_named(0xa89a3564);
        sprites[12] = func_named(0xcf144334);
        sprites[13] = func_named(0xe85a37e9);
        sprites[14] = func_named(0x7b3044e7);
        Unk02098e70 t(func_020a7ca4(sprites[13]), func_020a7cc0(sprites[13]));
        hand = *(Unk0200f1a8 *)&t;
        sprites[15] = func_named(0x68c46d2e);
        sprites[16] = func_named(0x5ed5d382);
        int range = func_020a7cc0(sprites[15]) - func_020a7cc0(sprites[16]);
        fill = 0x1000 - range / 64;
        full = fill + 0x19a;
        texts[0] = func_text(4, 0xc4189d9c);
        texts[1] = func_text(4, 0xdc127127);
        texts[2] = func_text(4, 0x50ff48fb);
        texts[3] = func_text(4, 0xfd435bc9);
        texts[4] = func_text(4, 0xba4ed5b8);
        buttons[0].func_02050838(func_text(0xb, 0x4ec86058), 0);
        buttons[1].func_02050838(func_text(0xb, 0x66c2a823), 0);
        buttons[2].func_02050838(func_text(0xb, 0xe56a57d0), 0);
        buttons[3].func_02050838(func_text(0xb, 0x254bb7bc), 0);
        buttons[3].func_02050c48(0, 3, -1);
        buttons[4].func_02050838(func_text(0xb, 0x4eb9e48d), 0);
        buttons[4].func_02050c48(0, 3, -1);
        state = states[1];
        void *sim = data_020c43a8.sim;
        u32 key = data_020ae654[0];
        if (key != 0) {
            void *a = func_02063e2c(key, 2);
            if (a != 0) {
                func_02069124(sim, a, 10, 0);
            }
        }
        anim = 0;
    }

    void func_02010784(Unk020a7c90 *s, int n, int step, u8 *t) {
        int f = func_020a69cc(s);
        if (f < n) {
            if (*t == 0) {
                *t = step;
                func_020a69ac(s, f + 1);
                if (f == n - 1) {
                    func_020a7cf0(s, 0);
                }
            } else {
                *t = *t - 1;
            }
        }
    }

    void func_020106cc(Unk020a7c90 *s, int n, int step, u8 *t) {
        int f = func_020a69cc(s);
        if (f < n) {
            if (*t == 0) {
                *t = step;
                func_020a69ac(s, f == n - 1 ? 0 : f + 1);
            } else {
                *t = *t - 1;
            }
        }
    }

    bool func_0201075c() {
        return left == 0;
    }

    bool func_02010748() {
        return value == 0x1000;
    }

    void func_0201065c(void *sim, int index, int loop, bool force, int delay) {
        if (force || anim != index) {
            u32 key = data_020ae654[index];
            if (key != 0) {
                void *a = func_02063e2c(key, loop ? 1 : 2);
                if (a != 0) {
                    func_02069124(sim, a, delay, 0);
                }
            }
            anim = index;
        }
    }

    virtual bool func_18();

    virtual void func_1c() {
    }

    static State states[6];

    Unk020a9d58 layout0;
    Unk020a9d58 layout1;
    Unk020a7af4 names0;
    Unk020a7af4 names1;
    Unk020a7af4Entry entries0[2];
    Unk020a7af4Entry entries1[0x1e];
    Unk020a7c90 *sprites[17];
    u8 timer0;
    u8 timer1;
    u8 timers[2];
    u8 timer2;
    u8 sparks[6];
    u8 timer4;
    u8 timer5;
    u16 flash;
    int gaugeY;
    Unk0200f1a8 hand;
    int full;
    int fill;
    Unk020a7c90 *texts[5];
    Unk02050640 buttons[5];
    State state;
    int value;
    int left;
    const Unk0200ed88Rate *rate;
    Unk0200f1a8 history[6];
    Unk0200f1a8 start;
    u16 frames;
    u8 unk5a6[0x26];
    int anim;
    Unk0200f174 clock;
    Unk0200ed88Sound *sound;
    int burn;
    int done;
    u32 burnKey;
    int rub;
    int angle;
    Unk02061d08Item *item;
    Unk02061d08Item *smoke;
    Unk02061d08Item *ash;
    u8 unk5f8[0xc];
    int script;
    u8 paused;
};

Unk0200ed88::State Unk0200ed88::states[6] = {
    &Unk0200ed88::func_0200e1f8, &Unk0200ed88::func_0200e144, &Unk0200ed88::func_0200eb70,
    &Unk0200ed88::func_0200e9ec, &Unk0200ed88::func_0200e9ec, &Unk0200ed88::func_0200e190,
};

void Unk0200ed88::func_0200e144() {
    func_020a9198(sprites[0], (0x1000 - value) >> 4);
    func_020a7cac(sprites[0], gaugeY - (value << 5));
    state = states[5];
}

void Unk0200ed88::func_0200e190() {
    if (func_020a13d4(func_020a18e4(), 2, 0)) {
        func_0200f250();
        if (func_0205d340(item->def, 0xb592872e)) {
            func_0200f1ac();
        }
        state = states[0];
    }
}

void Unk0200ed88::func_0200e1f8() {
    int *t = func_02097a4c();
    func_020a3f84(&data_020d6cdc, 0x1770);
    Unk02098e70 p(t[0] << 12, t[1] << 12);
    if (func_020978dc(0)) {
        if (frames == 0) {
            int y = p.y;
            for (u32 i = 0; i < 6; i++) {
                history[i] = (const Unk0200f1a8 &)Unk02098e70(p.x, y);
            }
            start = (const Unk0200f1a8 &)Unk02098e70(p.x, y);
        } else {
            for (int i = 5; i > 0; i--) {
                history[i] = history[i - 1];
            }
            history[0] = (const Unk0200f1a8 &)Unk02098e70(p.x, p.y);
            bool turned = false;
            if (history[0].v.func_02098fcc(start.v).func_02098e94() <
                history[3].v.func_02098fcc(start.v).func_02098e94()) {
                turned = true;
            }
            if (history[0].v.func_02098fcc(history[1].v).func_02098e94() > 0x64000) {
                    if (turned) {
                        if (++data_020be2f4 == 4) {
                            data_020be2f4 = 0;
                            if (rub != -1) {
                                func_020a34e4(func_020a2994(), rub);
                                rub = -1;
                            }
                            if (sound != 0) {
                                rub = func_020a32ac(func_020a2994(), 0x0269eff8, sound->unk4, 0x7f, 0);
                            }
                        }
                        data_020be2f0 = 1 - data_020be2f0;
                        if (rub != -1 && frames != -1) {
                            if (data_020be2f0 != 0) {
                                func_020a35a4(func_020a2994(), rub, 0x40);
                            } else {
                                func_020a35a4(func_020a2994(), rub, 0);
                            }
                        }
                    }
                int x = p.x;
                int y = p.y;
                bool near;
                if (data_020d60c8.flipped != 0) {
                    x = 0xff000 - x;
                }
                if (x > 0xc0000) {
                    near = false;
                } else {
                    int a = 0xe0000 - x - y;
                    int b = 0xe0000 - y - x;
                    int d = FUNC_ABS(b) < FUNC_ABS(a) ? FUNC_ABS(b) : FUNC_ABS(a);
                    near = d < rate->reach;
                }
                if (near) {
                    if (value < full) {
                        left -= 2;
                    }
                    int i = 11;
                    Unk020a7c90 *s = 0;
                    while (s == 0 && i <= 12) {
                        if (!func_020a7d1c(sprites[i])) {
                            s = sprites[i];
                        }
                        i++;
                    }
                    if (s != 0) {
                        func_show(s);
                    }
                    if (turned) {
                        if (frames > 2 && frames < 8 && value < full) {
                            int speed = history[0].v.func_02098fcc(start.v).func_02098e84();
                            if ((u32)frames << 12) {
                                speed = func_02077c60(speed, frames << 12);
                            }
                            int v = speed * (fill + 0x800 - value) >> 12;
                            value += v * 0x14 >> 12;
                            Unk020a7c90 *f = sprites[5];
                            if (!func_020a7d1c(f)) {
                                bool left2 = history[0].v.x < history[1].v.x;
                                func_020a7cf0(f, 1);
                                func_020a69ac(f, 0);
                                func_020a91ac(f, data_020d60c8.flipped != 0 ? !left2 : left2);
                                func_020a91ec(f, left2);
                            }
                            if (!func_020a7d1c(sprites[3])) {
                                f = sprites[3];
                            } else if (!func_020a7d1c(sprites[4])) {
                                f = sprites[4];
                            } else {
                                frames = 0;
                                goto skip;
                            }
                            bool left3 = history[0].v.x < history[1].v.x;
                            func_020a7cf0(f, 1);
                            func_020a69ac(f, 0);
                            func_020a7c90(f, history[0].v.x - 0x10000);
                            func_020a7cac(f, history[0].v.y - 0x10000);
                            func_020a91ac(f, data_020d60c8.flipped != 0 ? !left3 : left3);
                            func_020a91ec(f, left3);
                        }
                        frames = 0;
                    }
                } else {
                    if (value < full) {
                        left -= 0x14;
                    }
                    int i = 6;
                    Unk020a7c90 *s = 0;
                    while (s == 0 && i <= 12) {
                        if (!func_020a7d1c(sprites[i])) {
                            s = sprites[i];
                        }
                        i++;
                    }
                    if (s != 0) {
                        func_show(s);
                    }
                    frames = 0;
                }
            }
        skip:
            if (left < 0) {
                left = 0;
            }
        }
        frames++;
    } else {
        if (rub != -1) {
            func_020a34e4(func_020a2994(), rub);
            rub = -1;
        }
    }
    if (value > fill && (data_020d6cdc.flags & 1)) {
        value += 8;
        if (burn == -1 && sound != 0) {
            burn = func_020a32ac(func_020a2994(), burnKey, sound->unk4, 0x7f, 0);
        }
    } else if (burn != -1) {
        if (func_020a3514(func_020a2994(), burn) == 0) {
            burn = -1;
        }
    }
    value -= rate->decay;
    if (value < 0) {
        value = 0;
    }
    if (value > 0x1000) {
        value = 0x1000;
    }
    func_020a9198(sprites[0], (0x1000 - value) >> 4);
    func_020a7cac(sprites[0], gaugeY - (value << 5));
    if ((value == 0x1000) | (left == 0)) {
        func_020a7cf0(sprites[13], 0);
        func_020a7cf0(sprites[14], 0);
        func_020a7cf0(texts[2], 0);
        buttons[2].func_18(0);
        state = states[3];
    }
}

void Unk0200ed88::func_0200e9ec() {
    void *sim = data_020c43a8.sim;
    u32 key = data_020ae654[8];
    if (key != 0) {
        void *a = func_02063e2c(key, 2);
        if (a != 0) {
            func_02069124(sim, a, 10, 0);
        }
    }
    anim = 8;
    if (value == 0x1000) {
        if (sound != 0) {
            done = func_020a32ac(func_020a2994(), 0xb2765490, sound->unk4, 0x7f, 0);
        }
        func_020a3858(func_020a2994(), 0xbe776b91, 0, 0, 0);
        func_020a716c(texts[0], 0x9e1);
        func_020a7cf0(sprites[0], 0);
        func_020a7cf0(sprites[2], 1);
        if (item != 0) {
            Unk02061c04 runner(item);
            runner.func_02099ce0(script);
        }
    } else {
        func_020a716c(texts[0], 0x9e0);
    }
    func_020a7cf0(texts[0], 1);
    buttons[0].func_18(1);
    func_020a7cf0(texts[2], 0);
    buttons[2].func_18(0);
    func_020a7cf0(sprites[13], 0);
    func_020a7cf0(sprites[14], 0);
    state = states[2];
}

void Unk0200ed88::func_0200eb70() {
    if (flash < 0x28) {
        if (value == 0x1000 && !(flash & 1)) {
            if ((int)((*(u32 *)(data_020d6298 + 4) & 0x7c0) >> 6) >= 6) {
                volatile u16 *p = (volatile u16 *)0x5000400;
                for (int n = 0x200; n > 0; n--) {
                    int c = *p;
                    int r = c & 0x1f;
                    int g = c >> 5 & 0x1f;
                    int b = c >> 10 & 0x1f;
                    if (r < 0x1f && (u32)r >= 9) {
                        r++;
                    }
                    if (g < 0x1f && (u32)g >= 9) {
                        g++;
                    }
                    *p++ = r + (g << 5) + (b << 10);
                }
            } else {
                volatile u16 *p = (volatile u16 *)0x5000400;
                for (int n = 0x200; n > 0; n--) {
                    int c = *p;
                    int r = c & 0x1f;
                    int g = c >> 5 & 0x1f;
                    int b = c >> 10 & 0x1f;
                    if (r < 0x1f) {
                        r++;
                    }
                    if (g < 0x1f) {
                        g++;
                    }
                    *p++ = r + (g << 5) + (b << 10);
                }
                p = (volatile u16 *)0x5000400;
                for (int n = 0x200; n > 0; n--) {
                    int c = *p;
                    int r = c & 0x1f;
                    int g = c >> 5 & 0x1f;
                    int b = c >> 10 & 0x1f;
                    if (b < 0x1f && (u32)b >= 9) {
                        b++;
                    }
                    *p++ = r + (g << 5) + (b << 10);
                }
            }
        }
    } else if (flash > 0x3c) {
        u8 *o = (u8 *)func_02007340(data_020be184, 0xf);
        if (o != 0) {
            *(int *)(o + 0x24) = value == 0x1000 ? 0x2a : 0x2b;
            o[0x28] = 0;
            func_02007f84(data_020c4770, o, *(int *)((u8 *)&data_020c43a8 + 0x3d4));
        }
        state = 0;
    } else if (value == 0x1000) {
        volatile u16 *p = (volatile u16 *)0x5000400;
        for (int n = 0x200; n > 0; n--) {
            int c = *p;
            int r = c & 0x1f;
            int g = c >> 5 & 0x1f;
            int b = c >> 10 & 0x1f;
            if (r < 0x1f) {
                r++;
            }
            if (g < 0x1f) {
                g++;
            }
            if (b < 0x1f) {
                b++;
            }
            *p++ = r + (g << 5) + (b << 10);
        }
    }
    flash++;
}

#pragma dont_inline on
inline Unk0200ed88::Unk0200ed88(Unk02093648 *file, Unk0200ed88Arg *args, int n)
    : Unk020a5ccc(file, (int)args, n), layout0(file, 0), layout1(file, 0), names0(entries0, 2),
      names1(entries1, 0x1e), timer0(0), timer1(0), timer2(0), timer4(0), timer5(0), flash(0), state(0),
      value(0), left(0x1000), frames(0), clock(0, 0, 0, 0), sound(0), burn(-1), done(-1), rub(-1), angle(0),
      item(0), smoke(0), ash(0), script(0), paused(0) {
    sound = func_020a290c(func_020a2994(), 2);
    if (sound != 0) {
        bool male;
        {
            Unk020081dc outfit = func_020081dc(func_0200f168());
            male = outfit.unk28 == 0;
        }
        burnKey = male ? 0xf2fc665a : 0xf2fc6653;
        func_020a3188(func_020a2994(), burnKey, sound->unk4);
        func_020a3188(func_020a2994(), 0xb2765490, sound->unk4);
        func_020a3188(func_020a2994(), 0x0269eff8, sound->unk4);
    }
    for (u8 i = 0; i < 6; i++) {
        sparks[i] = 0;
    }
    for (u8 j = 0; j < 2; j++) {
        timers[j] = 0;
    }
    func_020a5ea4(&layout1);
    switch (func_0200f15c()->func_0200f154()) {
    case 2:
        rate = &data_020ae63c;
        break;
    case 0xd:
        rate = &data_020ae648;
        break;
    default:
        rate = &data_020ae63c;
        break;
    }
    func_0200f0e0(0x80000, 0x60000);
    for (int i = 0; i < n; i++) {
        switch (args[i].key) {
        case 0x35c7a149:
            item = func_0205fbf4(func_0200f0d4(), args[i].value);
            break;
        case 0xf89be826:
            script = args[i].value;
            break;
        }
    }
}

inline bool Unk0200ed88::func_18() {
    Unk020a7c90 *o;
    Unk020a7c90 *s;
    void *sim;
    func_020aa158(&layout0);
    func_020aa158(&layout1);
    if (!paused && !func_020a7d1c(texts[0])) {
        if (timer0 == 0) {
            timer0 = 6;
            Unk020a7c90 *s = sprites[1];
            if (value < 0x4cd) {
                func_020a7cf0(s, 0);
            } else {
                func_020a7cf0(s, 1);
                int f;
                f = func_020a69cc(sprites[1]);
                if (value < 0x4f6) {
                    func_020a69ac(s, 1);
                } else if (value < 0x51f) {
                    func_020a69ac(s, 2);
                } else if (value < 0x548) {
                    func_020a69ac(s, 3);
                } else if (value < 0x571) {
                    func_020a69ac(s, 4);
                } else if (value < 0x59a) {
                    func_020a69ac(s, 5);
                } else if (value < 0x5c3) {
                    func_020a69ac(s, 6);
                } else if (value < 0x6b8) {
                    func_020a69ac(s, f >= 0xe ? 7 : f + 1);
                } else if (value < 0x7d7) {
                    func_020a69ac(s, f >= 0x16 ? 0xf : f + 1);
                } else {
                    func_020a69ac(s, f >= 0x22 ? 0x17 : f + 1);
                }
            }
        } else {
            timer0 = timer0 - 1;
        }
        s = sprites[2];
        if (func_020a7d1c(s)) {
            if (timer1 == 0) {
                u32 f;
                timer1 = 5;
                f = func_020a69cc(s);
                func_020a69ac(s, f == 0x10 ? 0xa : f + 1);
            } else {
                timer1 = timer1 - 1;
            }
        }
        func_02010784(sprites[3], 6, 0, &timers[0]);
        func_02010784(sprites[4], 6, 0, &timers[1]);
        func_02010784(sprites[5], 8, 0, &timer2);
        for (u8 i = 0; i < 6; i++) {
            o = sprites[i + 6];
            if (func_020a7d1c(o)) {
                func_02010784(o, data_020ae634[i], 1, &sparks[i]);
                if (func_02010778()->func_02010770()) {
                    if (0xff000 - func_020a7ca4(o) + func_020a7cc0(o) < 0xe0000) {
                        FUNC_SHAKE(o, +, -)
                    } else {
                        FUNC_SHAKE(o, -, +)
                    }
                } else if (func_020a7ca4(o) + func_020a7cc0(o) < 0xe0000) {
                    FUNC_SHAKE(o, -, -)
                } else {
                    FUNC_SHAKE(o, +, +)
                }
            }
        }
        if (func_0201075c()) {
            func_020a69ac(sprites[12], 0x12);
        } else {
            func_020a69ac(sprites[12], (0x1000 - left) * 0x11 >> 12);
        }
        s = sprites[13];
        if (paused || func_020978dc(0) || value > full || func_02010748() || func_0201075c()) {
            func_020a7cf0(s, 0);
        } else {
            func_020a7cf0(s, 1);
            if (func_02010778()->func_02010770()) {
                func_020a7c90(s, hand.v.x + (func_0200cab0(angle) << 5));
            } else {
                func_020a7c90(s, hand.v.x - (func_0200cab0(angle) << 5));
            }
            func_020a7cac(s, hand.v.y + (func_0200cab0(angle) << 5));
            angle += 0x800;
        }
        s = sprites[14];
        if (func_0201073c()->func_02010728() || value < fill || func_02010748() || func_0201075c()) {
            if (timer5 == 0) {
                func_020a7cf0(s, 0);
                func_020a7cf0(texts[2], 0);
                buttons[2].func_18(0);
            } else {
                func_020106cc(s, 8, 2, &timer4);
                timer5 = timer5 - 1;
            }
        } else {
            func_020a7cf0(s, 1);
            func_020106cc(s, 8, 2, &timer4);
            func_020a7cf0(texts[2], 1);
            buttons[2].func_18(1);
            timer5 = 0x14;
        }
    }
    if (state == 0) {
        return false;
    }
    if (paused) {
        buttons[4].func_0c(buttons[3].func_0c(0));
        buttons[3].func_08();
        buttons[4].func_08();
        if (func_020972c0(3) || (buttons[3].touch.flags & 8) || (buttons[4].touch.flags & 8)) {
            buttons[1].func_18(0);
            buttons[3].func_18(0);
            buttons[4].func_18(0);
            func_020a7cf0(texts[1], 0);
            func_020a7cf0(texts[3], 0);
            func_020a7cf0(texts[4], 0);
            paused = 0;
            if (buttons[4].touch.flags & 8) {
                state = states[4];
            }
        }
    } else if (func_020972c0(3) && !func_020a7d1c(texts[0]) && func_020a1280(func_020a18e4(), 2, 0)) {
        buttons[1].func_18(1);
        buttons[2].func_18(0);
        buttons[3].func_18(1);
        buttons[4].func_18(1);
        func_020a7cf0(texts[1], 1);
        func_020a7cf0(texts[2], 0);
        func_020a7cf0(texts[3], 1);
        func_020a7cf0(texts[4], 1);
        func_020a7cf0(sprites[13], 0);
        func_020a7cf0(sprites[14], 0);
        paused = 1;
    } else {
        (this->*state)();
        if (state != 0) {
            sim = func_0200f168()->func_020106c4();
            switch (anim) {
            case 0:
            case 7:
            case 8:
                if (func_020691c4(sim)) {
                    func_0201065c(sim, 1, 1, 0, 10);
                }
                break;
            case 1:
                if (!func_02010748() && !func_0201075c()) {
                    if (func_020978dc(0)) {
                        func_0201065c(sim, 2, 0, 0, 10);
                    } else if (func_0201073c()->func_02010728()) {
                        func_0201065c(sim, 4, 0, 0, 10);
                    }
                }
                break;
            case 2:
                if (func_020691c4(sim)) {
                    func_0201065c(sim, 3, 1, 0, 10);
                }
                break;
            case 3:
                if (!func_020978dc(0)) {
                    func_0201065c(sim, 8, 0, 0, 10);
                }
                break;
            case 4:
                if (func_020691c4(sim)) {
                    func_0201065c(sim, func_020a5ec0() & 1 ? 5 : 6, 1, 0, 10);
                }
                break;
            case 5:
            case 6:
                if (!func_0201073c()->func_02010728()) {
                    func_0201065c(sim, 7, 0, 0, 10);
                }
                break;
            }
        }
    }
    return true;
}
#pragma dont_inline reset

Unk020a5ccc *func_0200ed88(Unk02093648 *file, Unk0200ed88Arg *args, int n) {
    return new Unk0200ed88(file, args, n);
}

void *func_0200f0d4() {
    return data_020c3fd4;
}

void Unk0200ed88::func_0200f0e0(int x, int y) {
    for (u32 i = 0; i < 6; i++) {
        history[i] = (const Unk0200f1a8 &)Unk02098e70(x, y);
    }
    start = (const Unk0200f1a8 &)Unk02098e70(x, y);
}

int Unk0200ed88World::func_0200f154() {
    return map;
}

Unk0200ed88World *func_0200f15c() {
    return &data_020c3ba4;
}

Unk0200ed88Player *func_0200f168() {
    return &data_020c43a8;
}

Unk0200f174::Unk0200f174(int h, int m, int s, int fr) {
    v = 0;
    v &= ~0xfc0000;
    v |= h << 18;
    v &= ~0x3f000;
    v |= m << 12;
    v &= ~0xfc0;
    v |= s << 6;
    v &= ~0x3f;
    v |= fr;
}

Unk0200f1a8::Unk0200f1a8() {
}

void Unk0200ed88::func_0200f1ac() {
    Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, func_0209a32c("build/data/objects/fire/f1_fire/fire_out", 0, 0));
    smoke = new Unk02061d08Item(def, item->func_14(), item->func_1c());
    func_0205e3f0(smoke);
    func_0205e4d0(item);
}

bool Unk0200ed88::func_0200f250() {
    if (ash == 0) {
        Unk02061d08Item *o = item;
        Unk020680d4Xy size(o->def->w, o->def->h);
        Unk020680d4Xy rel = func_020619a8(o, size, o->func_1c());
        Unk0200ed88Cell cell = func_add(o->func_14(), rel);
        Unk020680d4Dir dir = item->func_1c();
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, func_0209a32c("build/data/objects/items/it20_fire_starting", 0, 0));
        ash = new Unk02061d08Item(def, *(Unk020680d4Cell *)&cell, dir);
        Unk020680d4Xy size2(def->w, def->h);
        Unk020680d4Xy rel2 = func_020619a8(ash, size2, dir);
        cell = func_sub(cell, rel2);
        ash->func_10(*(Unk020680d4Cell *)&cell);
        func_0205e3f0(ash);
    }
    return ash != 0;
}

void Unk0200ed88::func_0200f470() {
    if (ash != 0) {
        delete ash;
        ash = 0;
    }
}

void Unk0200ed88::func_0200f4a4() {
    if (smoke != 0) {
        delete smoke;
        smoke = 0;
    }
}

extern const u32 data_020ae654[9] = {
    0x901a9bfe, 0, 0x8cdc993f, 0x8047e4fb, 0x3352e506, 0x10b38b9d, 0xb7bd00d0, 0xe27417c8, 0x8d900ac5,
};
