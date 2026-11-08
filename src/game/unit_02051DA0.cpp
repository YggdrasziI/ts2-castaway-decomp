/*
 * Unit 0x02051DA0-0x02052814: a slider widget (Unk02051da0, vtable 0x020BA10C).
 * A track sprite and a knob sprite, a value in 20.12 fixed point (0 to 1) mapped
 * to a range; the knob follows the touch inside the track's hit rectangle, with a
 * dead zone, horizontally or vertically.
 *
 * The inline update of the widget base Unk020b9e88 (game/unk_widget.h: a show /
 * hide state machine that moves the widget along two keyframe tracks) is emitted
 * here as the derived override, with the same code as the base's 0x0204FDE8.
 *
 * Bounds: hypothesis. The previous widget (vtable 0x020BA054) ends with its update
 * 0x02051AF4 at 0x02051DA0, the constructor of this class; 0x02052814 starts
 * unit_02052814.cpp. `.data` is the vtable of this class, then the unused copy of
 * the base vtable. Real file name unknown.
 *
 * The base's slots 7 to 20 are not named yet (see game/unk_widget.h): the
 * vtables do not match and the file cannot be complete.
 */

#include "game/unk_widget.h"

typedef unsigned char u8;

/* The touch input. */
class Unk020a0774;

/* The system (data_020d6240): only the input is used here. */
struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
};

extern Unk020d6240 data_020d6240;

extern "C" {
bool func_020a075c(Unk020a0774 *input, int index);
bool func_020a078c(Unk020a0774 *input, int index);
Unk02098e70 func_020a07bc(Unk020a0774 *input, int index);
}

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
    Unk020b9e88Touch touch;
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
    : Unk020b9e88(true), flags(2), value(0), min(0), max(0x1000), offset(0),
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

/* An 8-byte block copy: loads both words before the stores. */
struct Unk02098e70Wrap {
    Unk02098e70 v;
};

static inline void func_set(Unk02098e70 &v, const Unk02098e70 &p) {
    *(Unk02098e70Wrap *)&v = *(Unk02098e70Wrap *)&p;
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

bool Unk02051da0::func_0c(bool done) {
    Unk02098e70 p = func_020a07bc(data_020d6240.input, 1);
    if (done) {
        touch.flags = 0;
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
        touch.flags = 0;
        return done;
    }
    if (func_020a078c(data_020d6240.input, 1)) {
        if (flags & 2) {
            in = true;
        } else {
            in = hit.func_02098bf4(p.x, p.y);
        }
        if (!(touch.flags & 1) && in) {
            func_set(last, p);
        }
        touch.func_touched(in);
    } else {
        touch.flags &= ~0x10;
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
    touch.func_update();
    if (touch.flags & 1) {
        if (flags & 8) {
            func_020527f0(func_fxdiv(p.y - range.y, range.h));
        } else {
            func_020527f0(func_fxdiv(p.x - range.x, range.w));
        }
    }
    return (touch.flags & 1) != 0;
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
