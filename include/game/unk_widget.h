/*
 * The widget base class Unk020b9e88 (vtable 0x020B9E88) shared by the widget units
 * from 0x0204F858 (unit_02051704.cpp, unit_02051DA0.cpp), and the sprite class its
 * widgets hold. Layouts come from the code; all names are placeholders.
 *
 * The base has only inline or pure virtuals, so every widget file emits its
 * vtable (the kept copy is the first, 0x020B9E80). Its slots 7 to 20 point to
 * functions of far files (0x02017150 to 0x02031028) whose signatures are
 * unknown: they are declared here under slot names (non-inline), so the base
 * vtable copy is not emitted and the tail of the widget vtables does not match.
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

#endif
