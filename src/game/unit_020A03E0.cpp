/*
 * Unit 0x020A03E0-0x020A07D4: the input state (0x5C bytes): fifteen keys with a press
 * counter and two touch positions. The keys are the buttons, plus the touch and the two
 * touch screens as keys 7, 0 and 1. Bounds: hypothesis (the object is built and updated by
 * the screen manager at 0x020A0CD8; 0x020A07D4 is the root destructor of the screens). No
 * data. Layouts come from the code; all names are placeholders. Real file name unknown.
 */
#include "game/unk_vector.h"

typedef unsigned char u8;
typedef unsigned short u16;

void func_02097100();
bool func_02097248(int key);
bool func_02097298(int key);
void func_02097464();
int func_020978dc(int a);
int *func_02097a4c();

struct Unk020a03e0Key {
    Unk020a03e0Key() {
        flags = 0;
        threshold = 0;
        held = 0;
    }

    u16 flags;
    u8 threshold;
    u8 held;
};

struct Unk020a03e0Touch {
    Unk020a03e0Touch() : pos(0) {}

    Unk02098e70 pos;
    Unk02098e70 fixed;
};

class Unk020a03e0 {
public:
    Unk020a03e0();

    Unk020a03e0Key keys[15];
    Unk020a03e0Touch touch[2];
};

/* The game object (data_020d6240): only the screen flags are used here. */
struct Unk020d6240Screen {
    char unk0[0x140];
    int flags;
};

struct Unk020d6240 {
    int unk0[4];
    Unk020d6240Screen *screen;
};

extern "C" {
extern Unk020d6240 data_020d6240;
}

/* 99.35 %: r12, r3, r2 for the pointer, x and y; ours has r2, r3, r12. Copy forms tried. */
Unk020a03e0::Unk020a03e0() {
    int i;
    for (i = 0; i < 15; i++) {
        keys[i].flags = 0;
    }
    for (i = 0; i < 2; i++) {
        Unk02098e70 zero(0);
        int x = zero.x;
        int y = zero.y;
        touch[i].pos.x = x;
        touch[i].pos.y = y;
        keys[i].threshold = 3;
    }
}

extern "C" void func_020a04a4(Unk020a03e0 *o, int key, int button) {
    if (func_02097248(button)) {
        o->keys[key].flags |= 0x10;
    }
}

/*
 * 99.90 %: `lower` and `any` swapped between r2 and r1 at the two `mov`. The first constants
 * only stay when they are assigned apart from the declarations; 30 declaration, type and
 * assignment forms tried.
 */
extern "C" void func_020a04d4(Unk020a03e0 *o) {
    int i;
    func_02097100();
    func_02097464();
    for (i = 0; i < 15; i++) {
        o->keys[i].flags &= ~0x10;
    }
    func_020a04a4(o, 4, 6);
    func_020a04a4(o, 5, 7);
    func_020a04a4(o, 3, 5);
    func_020a04a4(o, 2, 4);
    func_020a04a4(o, 6, 3);
    if (func_020978dc(0) || func_02097298(3) || func_02097298(0)) {
        o->keys[7].flags |= 0x10;
    }
    int flags = data_020d6240.screen->flags;
    bool any;
    bool lower;
    lower = true;
    any = true;
    if (!(flags & 8) && !(flags & 4)) {
        lower = false;
    }
    if (!lower && !(flags & 2)) {
        any = false;
    }
    if (any) {
        if (func_020978dc(0)) {
            o->keys[0].flags |= 0x10;
            o->touch[0].pos.x = func_02097a4c()[0];
            o->touch[0].fixed.x = o->touch[0].pos.x << 12;
            o->touch[0].pos.y = func_02097a4c()[1];
            o->touch[0].fixed.y = o->touch[0].pos.y << 12;
        }
    } else {
        if (func_020978dc(0)) {
            o->keys[1].flags |= 0x10;
            o->touch[1].pos.x = func_02097a4c()[0];
            o->touch[1].fixed.x = o->touch[1].pos.x << 12;
            o->touch[1].pos.y = func_02097a4c()[1];
            o->touch[1].fixed.y = o->touch[1].pos.y << 12;
        }
    }
    for (i = 0; i < 15; i++) {
        u16 state = o->keys[i].flags;
        bool down = (state & 0x10) != 0;
        bool last = (state & 2) != 0;
        if (down) {
            if (o->keys[i].held < 0xff) {
                o->keys[i].held++;
            }
            if (o->keys[i].held < o->keys[i].threshold) {
                down = false;
            }
        } else {
            o->keys[i].held = 0;
        }
        o->keys[i].flags = 0;
        if (last && !down) {
            o->keys[i].flags |= 8;
        }
        if (down && !last) {
            o->keys[i].flags |= 4;
        }
        if (down) {
            o->keys[i].flags |= 3;
        }
    }
}

extern "C" bool func_020a0744(Unk020a03e0 *o, int key) {
    return o->keys[key].flags & 4;
}

extern "C" bool func_020a075c(Unk020a03e0 *o, int key) {
    return o->keys[key].flags & 4;
}

extern "C" bool func_020a0774(Unk020a03e0 *o, int key) {
    return o->keys[key].flags & 8;
}

extern "C" bool func_020a078c(Unk020a03e0 *o, int key) {
    return o->keys[key].flags & 1;
}

extern "C" Unk02098e70 func_020a07a4(Unk020a03e0 *o, int i) {
    return o->touch[i].pos;
}

extern "C" Unk02098e70 func_020a07bc(Unk020a03e0 *o, int i) {
    return o->touch[i].fixed;
}
