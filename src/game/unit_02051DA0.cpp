/*
 * Unit 0x02051DA0-0x02052814: a slider widget (Unk02051da0, vtable 0x020BA10C).
 * A track sprite and a knob sprite, a value in 20.12 fixed point (0 to 1) mapped
 * to a range; the knob follows the touch inside the track's hit rectangle, with a
 * dead zone, horizontally or vertically.
 *
 * The base class Unk020b9e88 (vtable 0x020B9E88) has only inline or pure
 * virtuals: every file of its derived widgets (from 0x0204F858) emits its vtable,
 * and the one kept is the first (0x020B9E80). Its inline update (a show / hide
 * state machine that moves the widget along two keyframe tracks) is emitted here
 * as the derived override, with the same code as the base's 0x0204FDE8.
 *
 * Bounds: hypothesis. The previous widget (vtable 0x020BA054) ends with its update
 * 0x02051AF4 at 0x02051DA0, the constructor of this class; 0x02052814 starts
 * unit_02052814.cpp. `.data` is the vtable of this class, then the unused copy of
 * the base vtable. Real file name unknown.
 *
 * The base's slots 7 to 20 point to functions of far files (0x02017150 to
 * 0x02031028) whose signatures are unknown: they are declared here under slot
 * names, so the vtables do not match (the base vtable copy is not emitted) and the
 * file cannot be complete.
 */

#include "game/unk_rect.h"
#include "game/unk_vector.h"

typedef unsigned char u8;

/* A sprite: only the size slots of its vtable are used here. */
class Unk020a7c90 {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual int func_10();
    virtual int func_14();
};

/* The touch input. */
class Unk020a0774;

/* The system (data_020d6240): only the input is used here. */
struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
};

extern Unk020d6240 data_020d6240;

extern "C" {
void func_020a7c90(Unk020a7c90 *s, int x);
int func_020a7ca4(Unk020a7c90 *s);
void func_020a7cac(Unk020a7c90 *s, int y);
int func_020a7cc0(Unk020a7c90 *s);
void func_020a7cf0(Unk020a7c90 *s, bool show);
bool func_020a075c(Unk020a0774 *input, int index);
bool func_020a078c(Unk020a0774 *input, int index);
Unk02098e70 func_020a07bc(Unk020a0774 *input, int index);
}

/* A keyframe track: values in 20.12 fixed point, sampled over a duration. */
struct Unk020b9e88Track {
    int *values;
    int count;
};

class Unk020b9e88 {
public:
    /*
     * The derived constructors reset the timer and the state after the base
     * fields and before their members: here a constant argument (hypothesis).
     */
    Unk020b9e88(bool shown) {
        trackX = 0;
        trackY = 0;
        timer = 0;
        duration = 0x3c;
        state = 5;
        keysX.values = valuesX;
        keysX.count = 2;
        keysY.values = valuesY;
        keysY.count = 2;
        if (shown) {
            timer = duration;
            state = 2;
        }
    }
    virtual ~Unk020b9e88() {}

    static inline int func_sample(const Unk020b9e88Track *track, int t, int max) {
        if (t > max) {
            t = max;
        }
        if (t < 0) {
            t = 0;
        }
        int pos = func_fxdiv(t << 12, func_fxdiv(max << 12, (track->count - 1) << 12));
        int i = pos >> 12;
        t = track->count - 1;
        if (i + 1 < t) {
            t = i + 1;
        }
        int frac = pos & 0xfff;
        if (t == i || frac == 0) {
            return track->values[i];
        }
        int a = track->values[i];
        return a + func_fxmul(track->values[t] - a, frac);
    }

    inline void func_update() {
        switch (state) {
        case 0:
            timer++;
            if (timer >= duration) {
                timer = duration;
                state = 1;
            }
            break;
        case 3:
            timer--;
            if (timer <= 0) {
                timer = 0;
                state = 4;
            }
            break;
        case 4:
            state = 5;
            break;
        case 1:
            state = 2;
            break;
        }
        if (func_hidden() && func_shown()) {
            return;
        }
        Unk020b9e88Track *track = trackX;
        if (track != 0) {
            int x = func_sample(track, timer, duration);
            func_14(x, func_10()->y);
        }
        track = trackY;
        if (track != 0) {
            int y = func_sample(track, timer, duration);
            func_14(func_10()->x, y);
        }
    }

    inline bool func_hidden() const {
        return state == 5 || state == 4;
    }

    inline bool func_shown() const {
        return state == 2 || state == 1;
    }

    virtual void func_08() {
        func_update();
    }
    virtual bool func_0c(bool done) {
        return done;
    }
    virtual Unk02098bc8 *func_10() = 0;
    virtual void func_14(int x, int y) = 0;
    virtual void func_18(bool show) = 0;
    virtual void func_1c();
    virtual void func_20();
    virtual void func_24();
    virtual void func_28();
    virtual void func_2c();
    virtual void func_30();
    virtual void func_34();
    virtual void func_38();
    virtual void func_3c();
    virtual void func_40();
    virtual void func_44();
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    Unk020b9e88Track *trackX;
    Unk020b9e88Track *trackY;
    short timer;
    short duration;
    int state;
    Unk020b9e88Track keysX;
    Unk020b9e88Track keysY;
    int valuesX[2];
    int valuesY[2];
};

class Unk02051da0 : public Unk020b9e88 {
public:
    Unk02051da0();
    ~Unk02051da0();
    void func_02051ec4(Unk020a7c90 *track, Unk020a7c90 *knob, int padX, int padY, bool horizontal, bool flag);
    void func_08();
    bool func_0c(bool done);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);
    void func_020520b0();
    int func_02052184();
    int func_020521a8();
    void func_020527a0(int v);
    void func_020527f0(int v);

    u16 flags;
    u16 touch;
    u8 delay;
    u8 held;
    int value;
    int min;
    int max;
    int offset;
    Unk02098e70 last;
    int deadZone;
    Unk02098bc8 bounds;
    Unk02098bc8 range;
    Unk02098bc8 hit;
    Unk020a7c90 *track;
    Unk020a7c90 *knob;
};

Unk02051da0::Unk02051da0()
    : Unk020b9e88(true), flags(2), touch(0), delay(0), held(0), value(0), min(0), max(0x1000), offset(0),
      last(0, 0), deadZone(0x1000), bounds(0, 0, 0, 0), range(0, 0, 0, 0), hit(0, 0, 0, 0), track(0), knob(0) {}

Unk02051da0::~Unk02051da0() {}

void Unk02051da0::func_02051ec4(Unk020a7c90 *track, Unk020a7c90 *knob, int padX, int padY, bool horizontal, bool flag) {
    this->track = track;
    bounds.x = func_020a7ca4(track);
    bounds.y = func_020a7cc0(track);
    bounds.w = track->func_10();
    bounds.h = track->func_14();
    hit.x = bounds.x + padX;
    hit.y = bounds.y + padY;
    hit.w = bounds.w - padX * 2;
    hit.h = bounds.h - padY * 2;
    range = hit;
    if (horizontal) {
        flags &= ~8;
        range.x += knob->func_10() >> 1;
        range.w -= knob->func_10();
    } else {
        flags |= 8;
        range.y += knob->func_14() >> 1;
        range.h -= knob->func_14();
    }
    this->knob = knob;
    if (flag) {
        flags |= 1;
    } else {
        flags &= ~1;
    }
}

void Unk02051da0::func_18(bool show) {
    if (track != 0) {
        func_020a7cf0(track, show);
    }
    if (knob != 0) {
        func_020a7cf0(knob, show);
    }
}

Unk02098bc8 *Unk02051da0::func_10() {
    return &bounds;
}

void Unk02051da0::func_14(int x, int y) {
    int dx = x - bounds.x;
    int dy = y - bounds.y;
    bounds.x = x;
    bounds.y = y;
    hit.x += dx;
    hit.y += dy;
    range.x += dx;
    range.y += dy;
    func_020520b0();
}

void Unk02051da0::func_020520b0() {
    func_020a7c90(track, bounds.x);
    func_020a7cac(track, bounds.y);
    if (flags & 8) {
        func_020a7c90(knob, bounds.x + offset);
        int k = func_fxmul(range.h, value);
        func_020a7cac(knob, range.y + k - (knob->func_14() >> 1));
    } else {
        func_020a7cac(knob, bounds.y + offset);
        int k = func_fxmul(range.w, value);
        func_020a7c90(knob, range.x + k - (knob->func_10() >> 1));
    }
}

static inline int func_lerp(const Unk02051da0 *w) {
    return w->min + func_fxmul(w->max - w->min, w->value);
}

int Unk02051da0::func_02052184() {
    return func_lerp(this);
}

int Unk02051da0::func_020521a8() {
    return (func_lerp(this) + 0x800) >> 12;
}

static inline void func_set(Unk02098e70 &v, const Unk02098e70 &p) {
    int y = p.y;
    int x = p.x;
    v.x = x;
    v.y = y;
}

static inline int func_dead(int d, int zone) {
    if (d >= zone) {
        return d - zone;
    }
    if (d <= -zone) {
        return d + zone;
    }
    return 0;
}

/*
 * 99.83 %: the original copies the touch point to `last` with x in r1 and y in
 * r0 (loaded x first); this code loads y first. Same instructions otherwise.
 */
bool Unk02051da0::func_0c(bool done) {
    Unk02098e70 p = func_020a07bc(data_020d6240.input, 1);
    if (done) {
        touch = 0;
        flags &= ~4;
        return done;
    }
    bool in = false;
    if (func_020a075c(data_020d6240.input, 1)) {
        in = hit.func_02098bf4(p.x, p.y);
        if (in) {
            flags |= 4;
        } else {
            flags &= ~4;
        }
        func_set(last, p);
    }
    if ((flags & 2) && !(flags & 4)) {
        touch = 0;
        return done;
    }
    if (func_020a078c(data_020d6240.input, 1)) {
        if (flags & 2) {
            in = true;
        } else {
            in = hit.func_02098bf4(p.x, p.y);
        }
        if (!(touch & 1) && in) {
            func_set(last, p);
            }
        if (in) {
            touch |= 0x10;
        } else {
            touch &= ~0x10;
        }
    } else {
        touch &= ~0x10;
        flags &= ~4;
    }
    if (in) {
        int d;
        if (flags & 8) {
            d = p.y - last.y;
        } else {
            d = p.x - last.x;
        }
        if (d >= deadZone) {
            d -= deadZone;
        } else if (d <= -deadZone) {
            d += deadZone;
        } else {
            d = 0;
        }
        if (flags & 8) {
            p.y = d + last.y;
        } else {
            p.x = d + last.x;
        }
        if (d != 0) {
            func_set(last, p);
            }
        if (p.x < range.x) {
            p.x = range.x;
        }
        if (p.x > range.x + range.w) {
            p.x = range.x + range.w;
        }
        if (p.y < range.y) {
            p.y = range.y;
        }
        if (p.y > range.y + range.h) {
            p.y = range.y + range.h;
        }
    }
    bool down = (touch & 0x10) != 0;
    bool was = (touch & 2) != 0;
    if (down) {
        if (held < 0xff) {
            held++;
        }
        if (held < delay) {
            down = false;
        }
    } else {
        held = 0;
    }
    touch = 0;
    if (was && !down) {
        touch |= 8;
    }
    if (down && !was) {
        touch |= 4;
    }
    if (down) {
        touch |= 3;
    }
    if (touch & 1) {
        if (flags & 8) {
            func_020527f0(func_fxdiv(p.y - range.y, range.h));
        } else {
            func_020527f0(func_fxdiv(p.x - range.x, range.w));
        }
    }
    return (touch & 1) != 0;
}

void Unk02051da0::func_08() {
    func_update();
}

void Unk02051da0::func_020527a0(int v) {
    v = func_fxdiv(v - min, max - min);
    if (v >= 0x1000) {
        v = 0x1000;
    } else if (v < 0) {
        v = 0;
    }
    value = v;
    func_020520b0();
}

void Unk02051da0::func_020527f0(int v) {
    if (v < 0) {
        v = 0;
    } else if (v > 0x1000) {
        v = 0x1000;
    }
    value = v;
    func_020520b0();
}
