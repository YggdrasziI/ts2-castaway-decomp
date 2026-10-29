/*
 * Unit 0x0204EB78-0x0204EE14: a scaled sprite meter (Unk0204eb78, 0x28 bytes, no
 * vtable). Its value moves by one per update towards a target (0 to 0x100) and
 * scales the main sprite, anchored on one side by the mode; a second sprite
 * blinks, faster when the value is low (25 or less), and a third shows by its
 * palette whether the value is rising, falling or settled.
 *
 * Bounds: hypothesis. The constructor and the empty destructor are passed
 * together as function pointers by far code (array construction); the
 * function before them is the last slot of the keyboard screen's vtable, and
 * 0x0204EE14 starts unit_0204EE14.cpp. No data. Real file name unknown.
 */

#include "game/unk_widget.h"

extern "C" {
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a9184(Unk020a7c90 *s, int scale);
void func_020a9198(Unk020a7c90 *s, int scale);
}

class Unk0204eb78 {
public:
    Unk0204eb78();
    ~Unk0204eb78();
    void func_0204ebd4(int mode);
    void func_0204ebdc(Unk020a7c90 *arrow);
    void func_0204ebe4(Unk020a7c90 *sprite);
    void func_0204ec10(Unk020a7c90 *blink);
    bool func_0204ec18();
    void func_0204ec2c(int target);
    void func_0204ec44();

    Unk020a7c90 *sprite;
    Unk020a7c90 *blink;
    Unk020a7c90 *arrow;
    Unk02098bc8 rect;
    short value;
    short target;
    int mode;
    int counter;
};

Unk0204eb78::Unk0204eb78()
    : sprite(0), blink(0), arrow(0), rect(0, 0, 0, 0), value(-1), target(0x100), mode(0), counter(0) {}

Unk0204eb78::~Unk0204eb78() {}

void Unk0204eb78::func_0204ebd4(int mode) {
    this->mode = mode;
}

void Unk0204eb78::func_0204ebdc(Unk020a7c90 *arrow) {
    this->arrow = arrow;
}

void Unk0204eb78::func_0204ebe4(Unk020a7c90 *sprite) {
    this->sprite = sprite;
    if (this->sprite == 0) {
        return;
    }
    rect.x = func_020a7ca4(this->sprite);
    rect.y = func_020a7cc0(this->sprite);
}

void Unk0204eb78::func_0204ec10(Unk020a7c90 *blink) {
    this->blink = blink;
}

bool Unk0204eb78::func_0204ec18() {
    return value <= 0x19;
}

void Unk0204eb78::func_0204ec2c(int target) {
    if (target >= 0x100) {
        target = 0x100;
    }
    if (target < 0) {
        target = 0;
    }
    this->target = target;
}

void Unk0204eb78::func_0204ec44() {
    if (sprite == 0) {
        return;
    }
    counter++;
    if (value > 0x19) {
        if (counter > 8) {
            counter = 0;
        }
    } else {
        if (counter > 0x10) {
            counter = 0;
        }
    }
    if (value != target) {
        if (value == -1) {
            value = target;
        } else if (value < target) {
            if (target - value < 1) {
                value = target;
            } else {
                value = value + 1;
            }
        } else {
            if (value - target < 1) {
                value = target;
            } else {
                value = value - 1;
            }
        }
    }
    if (arrow != 0) {
        int d = target - value;
        if (d > 0xf) {
            func_020a69ac(arrow, 1);
        } else if (d < -0xf) {
            func_020a69ac(arrow, 2);
        } else {
            func_020a69ac(arrow, 0);
        }
    }
    if (counter > 8) {
        func_020a7cf0(blink, true);
        return;
    }
    func_020a7cf0(blink, false);
    if (mode == 3) {
        func_020a9198(sprite, value);
        int v = value;
        int h = (0x100 - v) << 12;
        int off = 0;
        if (v != 0x100 && v != 0x80 && v != 0x40 && v != 0x20 && v != 0x10 && v % 8 == 0) {
            off -= 0x1000;
        }
        func_020a7cac(sprite, rect.y + (h >> 3) + off);
        return;
    }
    int scale = value + 5;
    if (scale > 0x100) {
        scale = 0x100;
    }
    func_020a9184(sprite, scale);
    int w = ((0x100 - scale) << 12) >> (mode == 0 ? 1 : 2);
    if (mode == 2) {
        func_020a7c90(sprite, rect.x + (w >> 2));
    } else {
        func_020a7c90(sprite, rect.x - (w >> 2));
    }
}
