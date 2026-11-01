/*
 * The widget base class Unk020b9e88 (vtable 0x020B9E88) shared by the widget units
 * from 0x0204F798 (unit_0204F798.cpp to unit_02051DA0.cpp), their
 * touch state and the sprite class they hold. Layouts come from the code; all
 * names are placeholders.
 *
 * The base has only inline or pure virtuals, so every widget file emits its
 * vtable (the kept copy is the first, 0x020B9E80). Its slots 7 to 20 point to
 * functions of far files (0x02017150 to 0x02031028) mostly not yet decompiled
 * (slot 7 is in unit_0202FDDC.cpp, slot 9 in unit_02029B80.cpp, slots 12, 13, 16
 * and 17 in unit_02027994.cpp, slot 20 in unit_0202AEF4.cpp): they
 * are declared here under slot names inline without a body, with the arguments and
 * results their callers use: that makes every widget file emit its base
 * vtable copy, as in the ROM.
 */
#ifndef GAME_UNK_WIDGET_H
#define GAME_UNK_WIDGET_H

#include "game/unk_rect.h"
#include "game/unk_vector.h"

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

extern "C" {
void func_020a7c90(Unk020a7c90 *s, int x);
int func_020a7ca4(Unk020a7c90 *s);
void func_020a7cac(Unk020a7c90 *s, int y);
int func_020a7cc0(Unk020a7c90 *s);
void func_020a7cf0(Unk020a7c90 *s, bool show);
}

typedef unsigned char u8;

/*
 * The touch state of a widget: flags (0x10 touched this frame, then 1 held,
 * 2 held before, 4 pressed, 8 released), a press delay and a hold counter.
 */
struct Unk020b9e88Touch {
    Unk020b9e88Touch() {
        flags = 0;
        delay = 0;
        held = 0;
    }

    inline void func_touched(bool in) {
        if (in) {
            flags |= 0x10;
        } else {
            flags &= ~0x10;
        }
    }

    inline void func_update() {
        bool down = (flags & 0x10) != 0;
        bool was = (flags & 2) != 0;
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
        flags = 0;
        if (was && !down) {
            flags |= 8;
        }
        if (down && !was) {
            flags |= 4;
        }
        if (down) {
            flags |= 3;
        }
    }

    u16 flags;
    u8 delay;
    u8 held;
};

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
    inline virtual void func_1c(Unk020b9e88Track *x, Unk020b9e88Track *y);
    inline virtual void func_20(int x, int y);
    inline virtual void func_24(int x, int y);
    inline virtual void func_28(int value);
    inline virtual void func_2c(int value);
    inline virtual void func_30(int value);
    inline virtual void func_34(int value);
    inline virtual bool func_38();
    inline virtual bool func_3c();
    inline virtual bool func_40();
    inline virtual bool func_44();
    inline virtual bool func_48();
    inline virtual bool func_4c();
    inline virtual bool func_50();

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

/* The gauge widget of unit_0205007C.cpp (0x60 bytes); its implicit D1 is the far copy 0x0201EB6C. */
class Unk0205007c : public Unk020b9e88 {
public:
    Unk0205007c();
    void func_0205012c(Unk020a7c90 *sprite);
    void func_14(int x, int y);
    void func_18(bool show);
    void func_020501a8(int v);
    void func_020501f8(int v);
    void func_08();
    void func_02050580();
    void func_02050600(int min, int max);
    bool func_0205060c();

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk020a7c90 *sprite;
    Unk02098bc8 rect;
    int value;
    int target;
    int min;
    int max;
    int counter;
    int delay;
};

#endif
