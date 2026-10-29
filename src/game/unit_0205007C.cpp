/*
 * Unit 0x0205007C-0x02050640: a gauge widget (Unk0205007c, vtable 0x020B9EE4) on
 * the widget base Unk020b9e88 (game/unk_widget.h). One sprite whose palette
 * index shows a value from 0 to 1 (20.12 fixed point) mapped from a range; the
 * value moves to its target by 1 / (palette count) every `delay` updates.
 *
 * Bounds: hypothesis. The previous widget (vtable 0x020B9E2C) ends with the base
 * functions its file emits first (0x0204FDE4-0x02050074); 0x02050640 starts
 * unit_02050640.cpp. `.data` is the vtable of this class, then the unused copy
 * of the base vtable. Real file name unknown.
 *
 * The destructor is implicit: its D1 in the vtable is the kept copy 0x0201EB6C
 * (`bx lr`) of a far file, its D0 and the inline rectangle accessor close this
 * file. The base's slots 7 to 20 are not named yet (see game/unk_widget.h): the
 * vtables do not match and the file cannot be complete.
 */

#include "game/unk_widget.h"

extern "C" {
int func_020a69d4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
}

/* A pixel value as 20.12 fixed point, rounded. */
#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

Unk0205007c::Unk0205007c()
    : Unk020b9e88(true), sprite(0), rect(0, 0, 0, 0), value(0), target(0), min(0), max(0), counter(0), delay(1) {}

void Unk0205007c::func_0205012c(Unk020a7c90 *sprite) {
    this->sprite = sprite;
    if (sprite == 0) {
        return;
    }
    rect.x = func_020a7ca4(sprite);
    rect.y = func_020a7cc0(sprite);
}

void Unk0205007c::func_14(int x, int y) {
    rect.x = x;
    rect.y = y;
    if (sprite != 0) {
        func_020a7c90(sprite, x);
        func_020a7cac(sprite, y);
    }
}

void Unk0205007c::func_18(bool show) {
    if (sprite != 0) {
        func_020a7cf0(sprite, show);
    }
}

void Unk0205007c::func_020501a8(int v) {
    v = func_fxdiv(v - min, max - min);
    if (v > 0x1000) {
        v = 0x1000;
    } else if (v < 0) {
        v = 0;
    }
    target = v;
    counter = 0;
}

void Unk0205007c::func_020501f8(int v) {
    func_020501a8(v);
    value = target;
    if (sprite != 0) {
        func_02050580();
    }
}

void Unk0205007c::func_08() {
    if (sprite == 0) {
        return;
    }
    func_update();
    if (func_020a69d4(sprite) <= 0) {
        return;
    }
    int n = FX32(func_020a69d4(sprite));
    if (value != target) {
        if (++counter >= delay) {
            counter = 0;
            int step = func_fxdiv(0x1000, n);
            if (value > target) {
                value -= step;
                if (value < target) {
                    value = target;
                }
            } else {
                value += step;
                if (value > target) {
                    value = target;
                }
            }
        }
    }
    func_02050580();
}

void Unk0205007c::func_02050580() {
    int n = FX32(func_020a69d4(sprite));
    if (n < 0x1000) {
        return;
    }
    int i = func_fxmul(value, n);
    if (i >= n) {
        i = n - 0x800;
    }
    func_020a69ac(sprite, i >> 12);
}

void Unk0205007c::func_02050600(int min, int max) {
    this->min = min;
    this->max = max;
}

bool Unk0205007c::func_0205060c() {
    return value == target;
}
