/*
 * The screen element base class Unk020b9b80 (vtable 0x020B9B80): the same
 * show / hide state machine over two keyframe tracks as the widget base
 * Unk020b9e88 (game/unk_widget.h), with another vtable and no virtual
 * destructor. Layout from the code; all names are placeholders.
 *
 * Its inline virtuals have kept copies near 0x0204D40C (update, set tracks,
 * shown test). Its slots 7 to 14 and 16 point to functions of far files
 * (0x0201F648 to 0x0202558C), kept copies too: slot 7 is in unit_0202402C.cpp,
 * the others in unit_0201E300.cpp. They are declared here under slot names
 * and marked inline without a body here: that makes every unit emit its base
 * vtable copy, as in the ROM.
 */
#ifndef GAME_UNK_ELEMENT_H
#define GAME_UNK_ELEMENT_H

#include "game/unk_widget.h"

class Unk020b9b80 {
public:
    Unk020b9b80() {
        trackX = 0;
        trackY = 0;
        timer = 0;
        duration = 0x3c;
        state = 5;
        keysX.values = valuesX;
        keysX.count = 2;
        keysY.values = valuesY;
        keysY.count = 2;
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
            int x = Unk020b9e88::func_sample(track, timer, duration);
            func_14(x, func_10()->y);
        }
        track = trackY;
        if (track != 0) {
            int y = Unk020b9e88::func_sample(track, timer, duration);
            func_14(func_10()->x, y);
        }
    }

    inline bool func_hidden() const {
        return state == 5 || state == 4;
    }

    inline bool func_shown() const {
        return state == 2 || state == 1;
    }

    virtual void func_00() {
        func_update();
    }
    virtual bool func_04(bool locked) = 0;
    virtual void func_08() = 0;
    virtual void func_0c(int priority) = 0;
    virtual Unk02098bc8 *func_10() = 0;
    virtual void func_14(int x, int y) = 0;
    virtual void func_18(Unk020b9e88Track *x, Unk020b9e88Track *y) {
        trackX = x;
        trackY = y;
    }
    inline virtual void func_1c(int x, int y);
    inline virtual void func_20(int a, int b);
    inline virtual void func_24(int duration);
    inline virtual void func_28(int duration);
    inline virtual void func_2c(int duration);
    inline virtual void func_30(int duration);
    inline virtual bool func_34();
    inline virtual bool func_38();
    virtual bool func_3c() {
        return state == 1;
    }
    inline virtual bool func_40();

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
