/*
 * Unit 0x020A07D4-0x020A0BC0: the stack of screens (0x2C bytes): ten slots, the top one last,
 * updated once per frame; a screen under the top one is hidden or shown again, and a finished
 * screen leaves its slot. It also holds the body of the pure destructor of the screen root.
 * Bounds: hypothesis (after the input state; 0x020A0BC0 is the constructor of another class).
 * No data. Layouts come from the code; all names are placeholders. Real file name unknown.
 */
#include "game/unk_screen.h"

/* The root seen from the stack: its slots from 0x34 are only called here. */
class Unk020a07f8Screen {
public:
    virtual ~Unk020a07f8Screen();
    virtual void func_08();
    virtual void func_0c(int a);
    virtual void func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual bool func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_30();
    virtual bool func_34();
    virtual void func_38(int frame);
    virtual Unk020a07f8Screen *func_3c(bool handled);
};

class Unk020a07d8 {
public:
    Unk020a07d8();
    ~Unk020a07d8();

    Unk020a07f8Screen *items[10];
    Unk020a07f8Screen *handled;
};

extern "C" bool func_020a0b8c(Unk020a07d8 *o, Unk020a07f8Screen *screen);

Unk020a07d4::~Unk020a07d4() {}

Unk020a07d8::Unk020a07d8() {
    for (int i = 0; i < 10; i++) {
        items[i] = 0;
    }
}

Unk020a07d8::~Unk020a07d8() {}

extern "C" bool func_020a07f8(Unk020a07d8 *o, int frame) {
    int i;
    o->handled = 0;
    for (i = 9; i >= 0; i--) {
        if (o->items[i] != 0) {
            o->handled = o->items[i]->func_3c(o->handled != 0);
        }
    }
    for (i = 9; i >= 0; i--) {
        if (o->items[i] != 0) {
            o->items[i]->func_38(frame);
        }
    }
    if (frame == 0) {
        return o->handled != 0;
    }
    Unk020a07f8Screen *top = 0;
    for (i = 9; i >= 0; i--) {
        if (o->items[i] != 0 && !o->items[i]->func_34()) {
            top = o->items[i];
            break;
        }
    }
    for (i = 9; i >= 0; i--) {
        if (top != 0 && o->items[i] == top) {
            break;
        }
        if (o->items[i] != 0 && o->items[i]->func_34()) {
            break;
        }
    }
    bool shown;
    bool below;
    shown = true;
    below = true;
    if (top == 0) {
        below = false;
    }
    for (i = 0; i < 10; i++) {
        Unk020a07f8Screen *screen = o->items[i];
        if (screen == 0) {
            continue;
        }
        if (screen != top) {
            if (below) {
                if (!screen->func_2c() && !o->items[i]->func_34()) {
                    o->items[i]->func_10();
                    shown = false;
                }
            } else if (screen->func_34() && o->items[i]->func_2c() && !o->items[i]->func_14()) {
                o->items[i]->func_0c(1);
            }
        } else {
            if (shown && !top->func_28() && !top->func_14()) {
                top->func_0c(3);
            }
            below = false;
        }
    }
    for (i = 9; i >= 0; i--) {
        if (o->items[i] != 0 && o->items[i]->func_14()) {
            if (o->items[i]->func_28()) {
                o->items[i]->func_10();
            }
            if (o->items[i]->func_2c()) {
                o->items[i]->func_1c();
                if (o->items[i]->func_20()) {
                    Unk020a07f8Screen *screen = o->items[i];
                    o->items[i] = 0;
                    delete screen;
                } else {
                    o->items[i] = 0;
                }
            }
        }
    }
    return o->handled != 0;
}

extern "C" void func_020a0b0c(Unk020a07d8 *o, Unk020a07f8Screen *screen) {
    if (screen == 0) {
        return;
    }
    if (func_020a0b8c(o, screen)) {
        return;
    }
    for (int i = 9; i > 0; i--) {
        if (o->items[i] == 0 && o->items[i - 1] != 0) {
            o->items[i] = screen;
            return;
        }
    }
    if (o->items[0] == 0) {
        o->items[0] = screen;
    }
}

extern "C" Unk020a07f8Screen *func_020a0b68(Unk020a07d8 *o) {
    for (int i = 9; i >= 0; i--) {
        if (o->items[i] != 0) {
            return o->items[i];
        }
    }
    return 0;
}

extern "C" bool func_020a0b8c(Unk020a07d8 *o, Unk020a07f8Screen *screen) {
    if (screen == 0) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (o->items[i] == screen) {
            return true;
        }
    }
    return false;
}
