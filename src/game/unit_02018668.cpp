/*
 * Unit 0x02018668-0x0201B5BC: the spear fishing microgame `Unk0201a2c8` (its strings
 * name the "fishing_spear_*" sounds), three fish `Unk0201a4e0` and the spear
 * `Unk0201af9c`, each driven by a pointer to member state function.
 *
 * Bounds: hypothesis. The start follows the deleting destructor of the rod fishing
 * class (vtable 0x020B8258, D0 0x02018594); the end is unit_0201B5BC.cpp. `.data`:
 * the sound names, their table, the pointer to member constants, the vtables and
 * the strings. Real file name unknown.
 *
 * Class layout (hypothesis, from the `.data` order): the fish and the spear are
 * classes nested in the game class. mwccarm creates the pointer to member
 * constants of class body code while it parses the bodies at the end of the
 * outermost class, last member first, and the original's 36 constants follow that
 * order for the game members, then the spear's, then the fish's. Separate classes
 * give the reverse (each class's bodies are parsed at its own end, and the game
 * class, which holds the fish and the spear, comes last). Functions the original calls out of line where it inlines
 * others (`func_14`, `func_02019444`, `func_02019b18`, `func_0201af10`,
 * `func_0201af9c`) are defined outside, after the bodies they must or must not
 * inline; their state constants come from one-line class body helpers
 * (`func_begin`, `func_finish`, `func_caught`, `func_reset`).
 *
 * Not complete. `.data` matches; the code gaps are registers and stack slots
 * (`func_02018f1c`, spilled sound index; `func_14`, `func_0201a12c`,
 * `func_02018de4`, `func_18`, `func_02018900`, `func_02019b18`, `func_02019fa0`,
 * `func_02019444`, `func_02019bd0`). `.rodata`: the last word 0xC5A28EFA is never
 * loaded and not reproduced.
 */

#include "game/unk_microgame.h"
#include "game/unk_fishing.h"

struct Unk0201a4e0Rect {
    int a, b, c, d;
    void func_0200cae0(const Unk0201a4e0Rect &o);
};

struct Unk0201a4e0RectWrap {
    Unk0201a4e0Rect r;
};

class Unk0201a2c8;

/* The catch of unit_0200B23C.cpp: only its key getter, called on a fish here. */
class Unk0200c308 {
public:
    void *func_0200cb58();
};

struct Unk0201a2c8Stream {
    int unk0;
    int unk4;
};

extern "C" {
void func_020897b4(const char *fmt, ...);
int func_02011188(int *counts);
void func_0200b09c(Unk0200b04c *a, int id);
void func_0200b120(Unk0200b04c *a);
int func_0200b150(Unk0200b04c *a, int f);
void func_0200de30(Unk0200dd90 *e);
int func_0200af10(Unk02010920 *e);
void func_0200df10(Unk0200dd90 *e, int a, int b);
void func_0200df54(Unk0200dd90 *e);
Unk0200dd90Part *func_0200dfc8(Unk0200dd90 *e, int i);
int func_0200dfd8(Unk0200dd90 *e, Unk02098e70 *v, int d);
void func_0200e010(Unk0200dd90 *e, Unk02098e70 *v, void *r, int a);
void func_02010954(Unk02010920 *e, void *def);
void func_020a6058(void *g, int id);
int func_020a6038(void *g, int hash);
void func_020a62f0(void *g);
void func_020a6114(void *g, u32 a, u32 b);
void func_020a6340(void *g, u32 hash, const char *name, int a, int b);
void func_020acbc8(Unk020acb90 *m);
void func_02010b8c(void *def, int a);
void func_02010ba8(void *def);
u32 func_0200afc0(void *def);
int func_0200afd4(void *def);
int func_02010efc();
int func_02010e60();
int func_02010c74(int a, int b, int c, int *out, int n);
void func_02010f40(Unk020a9d58 *l, Unk020a7af4 *n, Unk020a7c90 *s);
void func_02011010();
void func_02011074(void *a, void *b, void *c);
void func_02011128(int *a, int *b);
int func_020a5ef0(int a, int b);
Unk02098e70 func_020a5f28(int a, int b);
Unk0201a4e0Rect func_020a6438(void *g, Unk020a9d58 *l, Unk020a7af4 *n, u32 h);
int func_020a60bc();
int func_020a60e8();
int func_020a655c();
int func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a716c(Unk020a7c90 *s, int id);
void func_020a7d30(Unk020a7c90 *s, int x);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a8048(Unk020a7c90 *s, u32 hash);
void func_020a8064(Unk020a7c90 *s, int x);
void func_020a80a0(Unk020a7c90 *s, int x);
int func_020a917c(Unk020a7c90 *s);
void func_020a9168(Unk020a7c90 *s, int a);
void func_020aa42c(Unk020a9d58 *l);
int func_020a18e4();
int func_020a1280(int a, int b, int c);
int func_020a13d4(int a, int b, int c);
int func_020a1e68(int a, int b, int c);
int func_020a2994();
void *func_020a290c(int a, int b);
void func_020a2964(int a, void *b, int c);
void func_020a3188(int a, u32 h, int b);
void func_020a32ac(int a, u32 h, int b, int c, int d);
void func_020a3858(int a, u32 h, int b, int c, int d);
int func_02097a58(int a, int b);
u32 func_0209a3c4(u32 h, const char *s);
int func_0205f714(void *db, int key, int prev);
void func_02069124(void *a, int b, int c, int d);
void func_020667f8(void *a, int b);
void G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern u8 data_020c43a8[];
extern u8 data_020c44a8[];
extern u8 data_020c3fc4[];
extern const int data_020ae678[];
extern const short data_020af1e8[];
}
int *func_02097a4c();
void func_020978dc(int a);
int func_0209774c(int a);
int func_020972c0(int key);

inline u16 func_0201b164(u32 x);
inline Unk020a7c90 *func_0201b150(Unk020a9d58 *l, u16 i);
inline Unk020a7c90 *func_0201b13c(Unk020a9d58 *l, u16 i);
inline Unk020a7c90 *func_0201b128(Unk020a9d58 *l, u16 i);
inline Unk020a7c90 *func_0201b114(Unk020a9d58 *l, u16 i);
inline Unk020a7c90 *func_0201b100(Unk020a9d58 *l, u16 i);
inline Unk020a7c90 *func_0201b0ec(Unk020a9d58 *l, u16 i);


Unk02098e70 func_02018668(const Unk02098e70 &v, int f);

Unk02098e70 func_02018668(const Unk02098e70 &v, int f) {
    return Unk02098e70(((s64)v.x * f) >> 12, ((s64)v.y * f) >> 12);
}

/* A countdown: frames, seconds, minutes, hours, 6 bits each. */
struct Unk0201a2c8Time {
    union {
        struct {
            u32 frames : 6;
            u32 seconds : 6;
            u32 minutes : 6;
            u32 hours : 6;
        } f;
        u32 v;
    };

    Unk0201a2c8Time() {
        v = 0;
        func_set(0, 0);
    }
    void func_set(int s, int fr) {
        f.hours = 0;
        f.minutes = 0;
        f.seconds = s;
        f.frames = fr;
    }
    int func_get(int i) { return (int)*(volatile u32 *)&v >> (i * 6) & 0x3f; }
    void func_put(int i, int x) { *(volatile u32 *)&v = *(volatile u32 *)&v & ~(0x3f << (i * 6)) | x << (i * 6); }
};

class Unk0201a2c8 : public Unk020a5ccc {
public:
    class Unk0201a4e0 : public Unk02010920 {
    public:
        Unk0201a4e0() : Unk02010920(2), owner(0), state(&Unk0201a4e0::func_020187d4), unk138(0) {}
        ~Unk0201a4e0();
        void *func_00() { return &sprite; }
        bool func_04(int index, bool force);
        void func_reset() { state = &Unk0201a4e0::func_02018798; }
        void func_0201af10(Unk0201a2c8 *o, Unk020a7c90 *a, Unk020a7c90 *b);
        void func_start() {
            void (Unk0201a4e0::*s)();
            s = 0;
            switch (unkc0) {
            case (int)0x97de12bf:
                s = &Unk0201a4e0::func_02018730;
                break;
            case (int)0xcbd6cda5:
                s = &Unk0201a4e0::func_0201870c;
                break;
            case 0x4c444ea5:
                s = &Unk0201a4e0::func_020186e0;
                break;
            case 0x2743d311:
                s = &Unk0201a4e0::func_02018694;
                break;
            }
            state = s;
        }

        bool func_dead() { return state == &Unk0201a4e0::func_020187d4; }
        bool func_fleeing() { return state == &Unk0201a4e0::func_02018c38; }
        void func_02018798() {
            func_0200df10(this, 0, 1);
            timer = 750;
            state = &Unk0201a4e0::func_020187d4;
        }
        void func_020187d4() {}
        void func_wait() {
            func_set(target, func_020a5f28(1, 0x20000));
            state = &Unk0201a4e0::func_020187d8;
        }
        void func_020187d8() {
            if (func_0200dfd8(this, &target, 0xa000) == 1) {
                func_wait();
            } else if (timer == 0) {
                state = &Unk0201a4e0::func_02018bd4;
            } else {
                timer--;
                func_0200e010(this, &target, rects, 1);
            }
        }
        void func_02018694() {
            func_wait();
        }
        void func_020186e0() {
            func_set(move.step, unka8);
            state = &Unk0201a4e0::func_02018884;
        }
        void func_0201870c() {
            angle = 0;
            state = &Unk0201a4e0::func_02018900;
        }
        void func_02018730() {
            angle = 0;
            int d = func_02010efc() << 12;
            func_set(target, unkb0.func_02098fa8(func_02018668(unka8, d)));
            state = &Unk0201a4e0::func_02018b10;
        }
        void func_02018884() {
            if (func_0200dfd8(this, &target, 0xa000) == 1) {
                func_die();
            }
            func_020acbc8(&move);
            pos.x += move.dir.x;
            pos.y += move.dir.y;
        }
        void func_02018900() {
            if (angle * 6 > func_02010efc() << 13) {
                func_die();
                return;
            }
            func_set(move.dir, Unk02098e70(0));
            func_set(move.step, Unk02098e70(0x1000, 0));
            func_020acbc8(&move);
            int d = move.dir.func_02098e84() * 0x2aa;
            int a = angle;
            Unk02098e70 p = unkb0.func_02098fa8(func_02018668(unka8, a * 6));
            Unk02098e70 q;
            q = func_02018668(unka8, data_020af1e8[(u16)a >> 4 << 1] * func_0200af10(this));
            func_set(pos, Unk02098e70(p.x - q.y, p.y + q.x));
            a = angle + (d >> 12);
            Unk02098e70 r = unkb0.func_02098fa8(func_02018668(unka8, a * 6));
            Unk02098e70 t = func_02018668(unka8, data_020af1e8[(u16)a >> 4 << 1] * func_0200af10(this));
            func_set(target, Unk02098e70(r.x - t.y, r.y + t.x));
            func_set(move.dir, target.func_02098fcc(pos).func_02098eec());
            angle += d >> 12;
        }
        void func_02018b10() {
            if (func_0200dfd8(this, &target, 0xc8000) == 1) {
                if (angle == 0) {
                    func_set(target, unka0);
                    angle++;
                } else {
                    func_die();
                }
            } else if (timer == 0) {
                state = &Unk0201a4e0::func_02018bd4;
            } else {
                timer--;
                func_0200e010(this, &target, rects, 1);
            }
        }
        void func_02018bd4() {
            move.speed = move.speed * 3 / 4;
            func_set(target, func_020a5f28(0, 0x20000));
            state = &Unk0201a4e0::func_02018c38;
        }
        void func_02018c38() {
            if (func_0200dfd8(this, &target, 0xa000) == 1) {
                func_die();
            } else {
                func_0200e010(this, &target, &rects[1], 1);
            }
        }
        void func_die() {
            func_0200df10(this, 0, 1);
            state = &Unk0201a4e0::func_02018798;
            func_020897b4("Escaped!");
        }
        bool func_02019b18();
        void func_caught() { state = &Unk0201a4e0::func_02018798; }

        bool func_02019ea0();
        void func_02019ee8();

        Unk0201a2c8 *owner;
        void (Unk0201a4e0::*state)();
        int misses;
        int angle;
        Unk0201a4e0Rect rects[2];
        Unk0200b04cBit hitting;
        Unk02098e70 unk124;
        int unk12c;
        Unk020a7c90 *sprite;
        Unk020a7c90 *sprite2;
        int unk138;
        Unk0200b04c anim;
        int timer;
    };

    class Unk0201af9c : public Unk0200dd90 {
    public:
        Unk0201af9c() : Unk0200dd90(5) {}
        void *func_00() { return &sprites; }

        void func_reset() { state = &Unk0201af9c::func_02018ca0; }
        void func_0201af9c(Unk0201a2c8 *o, Unk020a7c90 *s, Unk020a7c90 *t);
        bool func_ready() { return state == &Unk0201af9c::func_02018d04; }
        void func_02018ca0() {
            Unk0201a2c8 *g = owner;
            g->func_sound(0, 1);
            state = &Unk0201af9c::func_02018d04;
        }
        void func_02018d04() {
            if (thrown.func_get()) {
                thrown.func_clear();
                state = &Unk0201af9c::func_02018d38;
            }
        }
        void func_02018d38() {
            Unk0201a2c8 *g = owner;
            int i = func_020a5ef0(1, 3);
            g->func_sound(i);
            func_set(pos, Unk02098e70(unkac.x, -0x20000));
            caught = func_02011188(owner->counts);
            state = &Unk0201af9c::func_02018de4;
        }
        void func_02018de4() {
            int t = func_020a60e8();
            if (t < 0x10000) {
                return;
            }
            Unk02098e70 start(unkac.x, -0x20000);
            func_set(pos, start.func_02098fa8(func_02018668(unkac.func_02098fcc(start), (t - 0x10000) / 5)));
            if (func_020a60bc() != 1) {
                return;
            }
            Unk0201a2c8 *g = owner;
            Unk02098e70 *p;
            Unk0201a4e0 *f = g->fish;
            p = g->spear.func_0200df08();
            for (int i = 0; i < 3; i++) {
                func_set(f->unk124, *p);
                f->hitting.func_set();
                f++;
            }
            func_020a7c90(g->cursor2, p->x);
            func_020a7cac(g->cursor2, p->y);
            func_020a6980(g->cursor2, 0x4d7b721c);
            func_0200b09c(&g->anims[1], g->ids[1]);
            state = &Unk0201af9c::func_02018f1c;
        }
        void func_02018f1c() {
            int n = func_02011188(owner->counts);
            Unk0201a2c8 *g = owner;
            int base = owner->sound - 1;
            if (n - caught != 0) {
                int k = base + 3;
                g->func_sound(k);
                g = owner;
                Unk0201a2c8Stream *s = g->stream;
                if (s != 0) {
                    func_020a32ac(func_020a2994(), 0xf557e3ff, s->unk4, 0x7f, 0);
                }
            } else {
                Unk0201a4e0 *f = g->fish;
                for (int i = 0; i < 3; i++, f++) {
                    owner->func_flee(f);
                }
                g = owner;
                Unk0201a2c8Stream *s = g->stream;
                if (s != 0) {
                    func_020a32ac(func_020a2994(), 0x43f9fd12, s->unk4, 0x7f, 0);
                }
                int k = base + 7;
                owner->func_sound(k);
            }
            g = owner;
            Unk02098e70 *p;
            Unk0201a4e0 *f = g->fish;
            p = g->spear.func_0200df08();
            for (int i = 0; i < 3; i++) {
                func_set(f->unk124, *p);
                f->hitting.func_set();
                f++;
            }
            func_020a7c90(g->cursor2, p->x);
            func_020a7cac(g->cursor2, p->y);
            if (g->func_hit()) {
                func_020a6980(g->cursor2, 0x6ec697c0);
                func_0200b09c(&g->anims[1], g->ids[2]);
            } else {
                func_020a6980(g->cursor2, 0xf8f35efd);
                func_0200b09c(&g->anims[1], g->ids[3]);
            }
            state = &Unk0201af9c::func_020191b4;
        }
        void func_020191b4() {
            int t = func_020a60e8();
            int n;
            if (owner->func_hit()) {
                n = 10;
                if (t >= (int)((float)(n << 12) + 0.5f)) {
                    state = &Unk0201af9c::func_020192bc;
                }
            } else {
                n = 13;
                if (t >= (int)((float)(n << 12) + 0.5f)) {
                    state = &Unk0201af9c::func_02018ca0;
                }
            }
            Unk02098e70 v(unkac.x, -0x20000);
            s64 d = ((s64)(unkac.y - v.y) * (0x1000 - t / n)) >> 12;
            pos.x = unkac.x;
            pos.y = v.y + d;
        }
        void func_020192bc() {
            Unk0201a2c8 *g = owner;
            g->func_sound(9, 0);
            state = &Unk0201af9c::func_0201931c;
        }
        void func_0201931c() {
            if (func_020a60bc() != 0) {
                state = &Unk0201af9c::func_02018ca0;
            }
        }

        void (Unk0201af9c::*state)();
        Unk0201a2c8 *owner;
        Unk02098e70 unkac;
        Unk0200b04cBit thrown;
        int caught;
        Unk020a7c90 *sprites[4];
        Unk020a7c90 *top;
        Unk0200b04c anim1;
        Unk0200b04c anim2;
    };

    Unk0201a2c8(Unk02093648 *file, int a, int b);
    virtual ~Unk0201a2c8();
    virtual bool func_08();
    virtual void func_10(bool a);
    void func_flee(Unk0201a4e0 *f) {
        if (!f->func_dead()) {
            if (!f->func_fleeing()) {
                f->state = &Unk0201a4e0::func_02018bd4;
            }
        }
    }
    void func_updateAnims() {
        func_020a7cf0(cursor, anims[0].playing.func_get());
        func_020a7cf0(cursor2, anims[1].playing.func_get());
        if (anims[0].playing.func_get()) {
            func_020a69ac(cursor, func_0200b150(&anims[0], 0x1000));
        }
        if (anims[1].playing.func_get()) {
            func_020a69ac(cursor2, func_0200b150(&anims[1], 0x1000));
        }
    }
    void func_updateFish() {
        Unk0201a4e0 *f = fish;
        for (int i = 0; i < 3; i++, f++) {
            func_0200de30(f);
            f->func_02019ee8();
            (f->*(f->state))();
            if (!f->func_02019ea0() && f->func_02019b18() != 1) {
                fish[i].misses++;
            }
        }
    }
    void func_begin() { state = &Unk0201a2c8::func_0201934c; }
    virtual void func_14();
    void func_0201934c() {
        if (func_020a13d4(func_020a18e4(), 2, 0) != 0) {
            func_020a6114(this, 0xab8dd75e, 0xf8ef1cc5);
            func_sound(0, 1, 1);
            state = &Unk0201a2c8::func_020193dc;
        }
    }
    void func_020193dc() {
        if (func_020a1280(func_020a18e4(), 2, 0) != 0) {
            G2x_SetBlendAlpha_(0x4001050, 0, 1, 0xf, 3);
            state = &Unk0201a2c8::func_02019444;
        }
    }
    void func_finish() { state = &Unk0201a2c8::func_02019fa0; }
    void func_02019444();
    void func_02019fa0() {
        if (func_all()) {
            func_020a716c(result, 0x9e1);
            func_020a3858(func_020a2994(), 0xbe776b91, 0, 0, 0);
            func_sound(13);
        } else if (func_02011188(counts) > 0) {
            func_020a716c(result, 0x9e2);
            int i = func_02011188(counts) > 1 ? 12 : 11;
            func_sound(i);
        } else {
            func_020a716c(result, 0x9e0);
            func_sound(14);
        }
        func_020a7cf0(result, true);
        buttons[0].func_18(true);
        time.func_set(3, 0);
        state = &Unk0201a2c8::func_0201a12c;
    }
    void func_0201a12c();
    virtual bool func_18() {
        int i;
        if (!shown.func_get()) {
            return true;
        }
        for (int i = 0; i < 2; i++) {
            func_020aa158(layouts[i]);
        }
        if (state == 0) {
            func_02011128(counts, unk920);
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
                func_020a7cf0(unk16c, false);
                func_020a7cf0(unk170, false);
                func_020a7cf0(unk174, false);
                hidden = 0;
                if (buttons[3].touch.flags & 8) {
                    Unk0201a4e0 *f = fish;
                    for (i = 0; i < 3; i++, f++) {
                        func_flee(f);
                    }
                    state = &Unk0201a2c8::func_02019fa0;
                }
            }
        } else if (func_020972c0(3) != 0 && !func_020a7d1c(result) && func_020a1280(func_020a18e4(), 2, 0) != 0) {
            buttons[1].func_18(true);
            buttons[2].func_18(true);
            buttons[3].func_18(true);
            func_020a7cf0(unk16c, true);
            func_020a7cf0(unk170, true);
            func_020a7cf0(unk174, true);
            hidden = 1;
        } else {
            (this->*state)();
            func_02011074(&unk148, &unk158, &unk918);
        }
        return true;
    }
    virtual void func_1c();

    bool func_02019bd0(int flag);
    bool func_all() { return func_02011188(counts) == 6; }
    bool func_hit() { return sound >= 3 && sound <= 6; }
    void func_sound(int index, int a = 0, int force = 0, int b = 0) {
        static const char *data_020b8624[15] = {
            "fishing_spear_idle", "fishing_spear_jab", "fishing_spear_jab2",
            "fishing_spear_jabhit", "fishing_spear_jabhit2", "fishing_spear_jabhit3",
            "fishing_spear_jabhit4", "fishing_spear_jabmiss", "fishing_spear_jabmiss2",
            "fishing_spear_stash", "fishing_spear_stash2", "fishing_spear_victory",
            "fishing_spear_bigvictory", "fishing_spear_hugevictory", "fishing_spear_fail",
        };
        if (force || sound != index) {
            func_020a6340(this, 0xc5a28efa, data_020b8624[index], a, b);
            sound = index;
        }
    }

    Unk020a9d58 *layouts[2];
    Unk020a9d58 layout0;
    Unk020a9d58 layout1;
    Unk020a7c90 *unk138;
    Unk020a7c90 *cursor;
    Unk020a7c90 *cursor2;
    Unk020a7c90 *unk144;
    Unk020a7c90 *unk148;
    void *unk14c[3];
    Unk020a7c90 *unk158;
    void *unk15c[3];
    Unk020a7c90 *result;
    Unk020a7c90 *unk16c;
    Unk020a7c90 *unk170;
    Unk020a7c90 *unk174;
    Unk02050640 buttons[4];
    int ids[4];
    Unk0201a4e0 fish[3];
    Unk0201af9c spear;
    int unk8b4;
    int depth;
    int score;
    int delay;
    int counts[3];
    void (Unk0201a2c8::*state)();
    Unk0201a2c8Time time;
    Unk0200b04cBit shown;
    Unk0200b04c anims[2];
    int unk918;
    int sound;
    int unk920[3];
    Unk0201a4e0Rect rects[2];
    u8 hidden;
    Unk0201a2c8Stream *stream;
};

typedef Unk0201a2c8::Unk0201a4e0 Unk0201a4e0;
typedef Unk0201a2c8::Unk0201af9c Unk0201af9c;

bool Unk0201a4e0::func_02019b18() {
    if (hitting.v & 1) {
        if (hit(&unk124, &scale, &pos, unk12c) == 1) {
            Unk0201a2c8 *g = owner;
            int k = (int)((Unk0200c308 *)this)->func_0200cb58();
            for (int i = 0; i < 3; i++) {
                if (g->unk920[i] == k) {
                    g->counts[i]++;
                    g->func_02019bd0(0);
                    break;
                }
            }
            func_caught();
            return true;
        }
        hitting.v &= ~1;
    }
    return false;
}

void Unk0201a2c8::func_14() {
    Unk020a7af4Entry entries[0x3c];
    Unk020a7af4 names(entries, 0x3c);
    int i;
    for (i = 0; i < 2; i++) {
        func_020aa42c(layouts[i]);
    }
    shown.v &= 1;
    for (i = 0; i < 2; i++) {
        func_0200b120(&anims[i]);
    }
    delay = 0;
    score = 0;
    depth = *(u16 *)(data_020c44a8 + 0xde);
    unk8b4 = func_02010e60();
    int n = func_02010c74(depth, unk8b4, func_020a655c(), unk920, 3);
    if (n < 3) {
        int prev = 0;
        for (; n < 3; n++) {
            prev = func_0205f714(data_020c3fc4, data_020ae678[0], prev);
            unk920[n] = prev;
        }
    }
    for (i = 0; i < 3; i++) {
        counts[i] = 0;
    }
    u32 maps[2] = {0xaf10306c, 0};
    maps[1] = func_0209a3c4(func_0209a3c4(0x26ac6082, unk8b4 == 0x9e3e1df3 ? "sea" : "stream"), "/custom.visualisation.nitro_xml");
    for (i = 0; i < 2; i++) {
        func_020aba38(file, maps[i], layouts[i], &names);
    }
    Unk020a9d58 *l0 = layouts[0];
    Unk020a9d58 *l1 = layouts[1];
#define ID(h) func_0201b164(func_020a7b50(&names, h))
    cursor = func_0201b150(l0, ID(0x9fe0dc0b));
    cursor2 = func_0201b150(l0, ID(0x3cb5044c));
    unk144 = func_0201b150(l0, ID(0x5604960d));
    result = func_0201b13c(l0, ID(0xc4189d9c));
    unk16c = func_0201b13c(l0, ID(0xdc127127));
    unk170 = func_0201b13c(l0, ID(0xfd435bc9));
    unk174 = func_0201b13c(l0, ID(0xba4ed5b8));
    buttons[0].func_02050838(func_0201b128(l0, ID(0x4ec86058)), false);
    buttons[1].func_02050838(func_0201b128(l0, ID(0x66c2a823)), false);
    buttons[2].func_02050838(func_0201b128(l0, ID(0x254bb7bc)), false);
    buttons[2].func_02050c48(0, 3, -1);
    buttons[3].func_02050838(func_0201b128(l0, ID(0x4eb9e48d)), false);
    buttons[3].func_02050c48(0, 3, -1);
    Unk020a7c90 *f0 = func_0201b150(l0, ID(0x3e74a03c));
    Unk020a7c90 *f1 = func_0201b150(l0, ID(0xdcb8bb7a));
    Unk020a7c90 *f2 = func_0201b150(l0, ID(0xf0c21ef4));
    Unk020a7c90 *t0 = func_0201b114(l0, ID(0x86deea9f));
    Unk020a7c90 *t1 = func_0201b114(l0, ID(0xb6a2ce2f));
    Unk020a7c90 *t2 = func_0201b114(l0, ID(0xdcdfa5b));
    Unk020a7c90 *t3 = func_0201b114(l0, ID(0xb16658d1));
    Unk020a7c90 *t4 = func_0201b114(l0, ID(0x4e2b7d12));
    Unk020a7c90 *t5 = func_0201b114(l0, ID(0xb6be87c4));
    unk138 = func_0201b100(l1, ID(0x4b50843d));
    unk158 = func_0201b150(l1, ID(0x29f55a05));
    unk148 = func_0201b150(l1, ID(0x2b8fe1af));
    unk15c[0] = (u8 *)unk158 + 0x44;
    unk15c[1] = (u8 *)unk158 + 0x110;
    unk15c[2] = (u8 *)unk158 + 0x154;
    unk14c[0] = (u8 *)unk148 + 0x44;
    unk14c[1] = (u8 *)unk148 + 0x110;
    unk14c[2] = (u8 *)unk148 + 0x154;
    Unk020a7c90 *t6 = func_0201b114(l1, ID(0x2efb9952));
    Unk020a7c90 *t7 = func_0201b114(l1, ID(0x2d6111a8));
    Unk020a7c90 *t8 = func_0201b0ec(l1, ID(0xa3c0d290));
    rects[0].func_0200cae0(func_020a6438(this, l1, &names, 0xc7345340));
    rects[1].func_0200cae0(func_020a6438(this, l1, &names, 0x74e76299));
    int lang = func_020a655c();
    func_020a8064(t1, lang);
    func_020a8064(t2, lang);
    func_020a8064(t3, lang);
    func_020a8064(t4, lang);
    func_020a8064(t5, lang);
    func_020a8064(t6, lang);
    func_020a8064(t7, lang);
    func_020a80a0(t8, lang);
    spear.func_0201af9c(this, f2, unk144);
    for (i = 0; i < 3; i++) {
        fish[i].func_0201af10(this, f0, f1);
        f1 = (Unk020a7c90 *)((u8 *)f1 + 0x44);
        f0 = (Unk020a7c90 *)((u8 *)f0 + 0x44);
    }
    func_02010f40(l1, &names, t0);
    for (i = 0; i < 3; i++) {
        u8 def[8];
        func_02010b8c(def, unk920[i]);
        func_020a8048(t0, func_0209a3c4(func_0200afc0(def), "swim.nitro_map"));
        func_020a8064(t0, func_0200afd4(def));
        func_02010ba8(def);
        t0 = (Unk020a7c90 *)((u8 *)t0 + 0x2c);
    }
    for (i = 0; i < 4; i++) {
        if (ids[i] != 0) {
            func_020a6058(this, ids[i]);
        }
    }
    ids[0] = func_020a6038(this, func_020a69a4(cursor));
    ids[1] = func_020a6038(this, 0x4d7b721c);
    ids[2] = func_020a6038(this, 0x6ec697c0);
    ids[3] = func_020a6038(this, 0xf8f35efd);
    unk918 = 6;
    func_02011010();
    if (shown.func_get()) {
        for (i = 0; i < 2; i++) {
            func_020aa06c(layouts[i], 1);
        }
    }
    func_begin();
}

inline void Unk0201a4e0::func_0201af10(Unk0201a2c8 *o, Unk020a7c90 *a, Unk020a7c90 *b) {
    owner = o;
    sprite = a;
    sprite2 = b;
    for (int i = 0; i < 2; i++) {
        rects[i] = owner->rects[i];
    }
    func_0200df54(this);
    anim.mode = 1;
    func_reset();
}

inline void Unk0201af9c::func_0201af9c(Unk0201a2c8 *o, Unk020a7c90 *s, Unk020a7c90 *t) {
    owner = o;
    for (int i = 0; i < 4; i++) {
        sprites[i] = s;
        s = (Unk020a7c90 *)((u8 *)s + 0x44);
    }
    top = t;
    func_set(pos, Unk02098e70(0x80000, -0x20000));
    func_0200df54(this);
    func_set(*(Unk02098e70 *)func_0200dfc8(this, 0), Unk02098e70(0, -0xa000));
    func_set(*(Unk02098e70 *)func_0200dfc8(this, 1), Unk02098e70(0, -0x4a000));
    func_set(*(Unk02098e70 *)func_0200dfc8(this, 2), Unk02098e70(0, -0x8a000));
    func_set(*(Unk02098e70 *)func_0200dfc8(this, 3), Unk02098e70(0, -0xca000));
    func_0200dfc8(this, 4)->flags |= 2;
    func_0200df10(this, 1, 0);
    func_reset();
}

inline Unk020a7c90 *func_0201b0ec(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 6, i); }
inline Unk020a7c90 *func_0201b100(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 2, i); }
inline Unk020a7c90 *func_0201b114(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 5, i); }
inline Unk020a7c90 *func_0201b128(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 0xb, i); }
inline Unk020a7c90 *func_0201b13c(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 4, i); }
inline Unk020a7c90 *func_0201b150(Unk020a9d58 *l, u16 i) { return func_020aa040(l, 1, i); }
inline u16 func_0201b164(u32 x) { return x; }

bool Unk0201a4e0::func_04(int index, bool force) {
    if (!Unk02010920::func_04(index, force)) {
        return false;
    }
    func_0200b120(&anim);
    if (unk138 != 0) {
        func_020a6058(owner, unk138);
    }
    unk138 = func_020a6038(owner, func_020a69a4(sprite));
    func_0200b09c(&anim, unk138);
    return true;
}

bool Unk0201a4e0::func_02019ea0() {
    return func_dead();
}

void Unk0201a4e0::func_02019ee8() {
    u32 f = func_0200b150(&anim, 0x1000);
    for (int i = 0; i < 2; i++) {
        func_020a69ac((&sprite)[i], f);
    }
    if ((int)move.dir.func_02098e94() <= 0x19a) {
        return;
    }
    Unk02098e70 d = move.dir.func_02098f38();
    int a = func_02097a58(d.x, -d.y);
    unk12c = func_020a1e68(func_020a917c(sprite), a, 500);
    for (int i = 0; i < 2; i++) {
        func_020a9168((&sprite)[i], unk12c);
    }
}

inline bool Unk0201a2c8::func_02019bd0(int flag) {
    u8 def[8];

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
    func_02010b8c(def, fish[n].owner->unk920[k]);
    func_02010954(&fish[n], def);
    func_02010ba8(def);
    for (int i = 0; i < 2; i++) {
        const Unk0201a4e0Rect &r = fish[n].owner->rects[i];
        int a = r.a;
        int b = r.b;
        int c = r.c;
        int d = r.d;
        fish[n].rects[i].a = a;
        fish[n].rects[i].b = b;
        fish[n].rects[i].c = c;
        fish[n].rects[i].d = d;
    }
    fish[n].unk12c = 0;
    func_020a7d30(fish[n].sprite, k);
    fish[n].func_04(0, true);
    func_set(*(Unk02098e70 *)func_0200dfc8(&fish[n], 1), Unk02098e70(0x10000, 0x10000));
    func_0200df10(&fish[n], 1, 0);
    fish[n].func_start();
    fish[n].misses = 0;
    score++;
    if (flag == 1) {
        delay = 240;
    }
    return true;
}

void Unk0201a2c8::func_02019444() {
    int *touch = func_02097a4c();
    func_020978dc(0);
    Unk02098e70 p(touch[0] << 12, touch[1] << 12);
    bool done = score == 6;
    for (int i = 0; i < 3; i++) {
        done = done & fish[i].func_dead();
    }
    if (done) {
    } else if (!spear.func_ready()) {
    } else if (func_0209774c(0) != 0) {
        func_set(spear.unkac, p);
        spear.thrown.func_set();
        func_020a7c90(cursor, p.x);
        func_020a7cac(cursor, p.y);
        func_0200b09c(&anims[0], ids[0]);
    }
    func_0200de30(&spear);
    (spear.*(spear.state))();
    func_updateFish();
    func_updateAnims();
    if (score < 6) {
        if (delay == 0) {
            func_02019bd0(1);
        } else {
            delay--;
        }
    }
    done = score == 6;
    for (int i = 0; i < 3; i++) {
        done = done & fish[i].func_dead();
    }
    done = done & spear.func_ready();
    for (int i = 0; i < 2; i++) {
        done = done & !anims[i].playing.func_get();
    }
    if (done == 1) {
        func_finish();
    }
}

void Unk0201a2c8::func_0201a12c() {
    for (int i = 0; i < 4; i++) {
        int v = time.func_get(i);
        if (v > 0) {
            time.func_put(i, v - 1);
            break;
        }
        Unk0201a2c8Time *t = &time;
        t->func_put(i, 59);
    }
    func_updateFish();
    func_updateAnims();
    if (*(volatile u32 *)&time.v == 0) {
        state = 0;
    }
}

inline Unk0201a4e0::~Unk0201a4e0() {
    func_0200b120(&anim);
    if (unk138 != 0) {
        func_020a6058(owner, unk138);
    }
}

inline Unk0201a2c8::Unk0201a2c8(Unk02093648 *file, int a, int b)
    : Unk020a5ccc(file, a, b), layout0(file, 0), layout1(file, 0), state(0) {
    hidden = 0;
    stream = 0;
    func_020a5ea4(&layout0);
    layouts[0] = &layout0;
    layouts[1] = &layout1;
    for (int i = 0; i < 4; i++) {
        ids[i] = 0;
    }
    stream = (Unk0201a2c8Stream *)func_020a290c(func_020a2994(), 2);
    if (stream != 0) {
        func_020a3188(func_020a2994(), 0xf557e3ff, stream->unk4);
        func_020a3188(func_020a2994(), 0x43f9fd12, stream->unk4);
    }
}

extern "C" Unk0201a2c8 *func_0201a2c8(Unk02093648 *file, int a, int b) {
    return new Unk0201a2c8(file, a, b);
}

Unk0201a2c8::~Unk0201a2c8() {
    func_02069124(*(void **)(data_020c43a8 + 0xc), 0, 0, 0);
    func_020667f8(data_020c43a8, 0);
    for (int i = 0; i < 4; i++) {
        if (ids[i] != 0) {
            func_020a6058(this, ids[i]);
        }
    }
    if (stream != 0) {
        func_020a2964(func_020a2994(), stream, 1);
        stream = 0;
    }
}

void Unk0201a2c8::func_10(bool a) {
    for (int i = 0; i < 2; i++) {
        func_020aa06c(layouts[i], a);
    }
    if (a != shown.func_get()) {
        shown.v ^= 1;
        if (!shown.func_get()) {
            func_020a62f0(this);
        }
    }
}

void Unk0201a2c8::func_1c() {}

bool Unk0201a2c8::func_08() {
    return func_02011188(counts) != 0;
}
