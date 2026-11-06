/*
 * Unit 0x0204F798-0x0205007C: an animated sprite widget (Unk0204f798, vtable
 * 0x020B9E2C) on the widget base Unk020b9e88 (game/unk_widget.h). It holds an
 * array of sprites moved and shown together; while running, each update past
 * `delay` steps their palette index by `step`, inside an optional range, looping
 * or stopping at the ends.
 *
 * Bounds: hypothesis. The start is the constructor (called from far files; the
 * function before it draws text and does not use this class); the end is
 * unit_0205007C.cpp. This file emits the base's kept functions after its own
 * (D1, update, D0) with the inline rectangle accessor and the base func_0c.
 * `.data` is this class's vtable, then the kept copy of the base vtable
 * (0x020B9E80). Real file name unknown.
 *
 * The base's slots 7 to 20 are not named yet (see game/unk_widget.h): the
 * vtables do not match, the base vtable copy is not emitted and with it the
 * base's D1, update and D0 kept here; the file cannot be complete.
 */

#include "game/unk_widget.h"

extern "C" {
int func_020a69cc(Unk020a7c90 *s);
int func_020a69d4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
}

typedef unsigned int u32;

class Unk0204f798 : public Unk020b9e88 {
public:
    Unk0204f798();
    ~Unk0204f798();
    void func_0204f8a0(int n);
    void func_0204f8f4(Unk020a7c90 *sprite);
    void func_0204f91c();
    void func_18(bool show);
    void func_14(int x, int y);
    void func_0204fa10(int a, int b);
    void func_08();
    Unk020a7c90 *func_0204fda8(int i);
    void func_0204fdb4();
    void func_0204fdcc(bool loop);

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk02098bc8 rect;
    u32 capacity;
    u32 count;
    Unk020a7c90 **sprites;
    int flags;
    int counter;
    int delay;
    int step;
    int first;
    int last;
};

Unk0204f798::Unk0204f798()
    : Unk020b9e88(true), rect(0, 0, 0, 0), capacity(0), count(0), sprites(0), flags(5), counter(0), delay(0),
      step(1), first(-1), last(-1) {}

Unk0204f798::~Unk0204f798() {
    func_0204f91c();
}

void Unk0204f798::func_0204f8a0(int n) {
    if (sprites != 0) {
        return;
    }
    capacity = n;
    sprites = new Unk020a7c90 *[n];
    for (u32 i = 0; i < capacity; i++) {
        sprites[i] = 0;
    }
}

void Unk0204f798::func_0204f8f4(Unk020a7c90 *sprite) {
    if (count < capacity) {
        sprites[count] = sprite;
        count++;
    }
}

void Unk0204f798::func_0204f91c() {
    if (sprites != 0) {
        delete[] sprites;
    }
    sprites = 0;
    count = 0;
}

void Unk0204f798::func_18(bool show) {
    for (u32 i = 0; i < count; i++) {
        if (sprites[i] != 0) {
            func_020a7cf0(sprites[i], show);
        }
    }
}

void Unk0204f798::func_14(int x, int y) {
    int dx = x - rect.x;
    int dy = y - rect.y;
    rect.x = x;
    rect.y = y;
    for (u32 i = 0; i < count; i++) {
        if (sprites[i] != 0) {
            func_020a7c90(sprites[i], dx + func_020a7ca4(sprites[i]));
            func_020a7cac(sprites[i], dy + func_020a7cc0(sprites[i]));
        }
    }
}

void Unk0204f798::func_0204fa10(int a, int b) {
    if (a < b) {
        first = a;
        last = b;
    } else {
        first = b;
        last = a;
    }
}

/*
 * 99.69 %: the index and the upper bound swap r6 / r8 (lo is r7 in both).
 * Tried: declaration order and scope of i / lo / hi / p, nested if instead of
 * continue, if / else for the range, int index, other wrap expressions, and the
 * source permuter (17140 variants).
 */
void Unk0204f798::func_08() {
    func_update();
    if (flags & 2) {
        return;
    }
    if (!(flags & 4)) {
        return;
    }
    if (++counter <= delay) {
        return;
    }
    counter = 0;
    for (u32 i = 0; i < count; i++) {
        if (sprites[i] == 0) {
            continue;
        }
        int hi;
        int lo = 0;
        hi = func_020a69d4(sprites[i]) - 1;
        if (first >= 0 && last >= 0) {
            hi = last;
            lo = first;
        }
        int p = func_020a69cc(sprites[i]) + step;
        if (p > hi) {
            if (!(flags & 1)) {
                flags |= 2;
                p -= step;
            } else {
                p = lo + p - hi - 1;
            }
        } else if (p < lo) {
            if (!(flags & 1)) {
                flags |= 2;
                p -= step;
            } else {
                p = hi + p - lo + 1;
            }
        }
        func_020a69ac(sprites[i], p);
    }
}

Unk020a7c90 *Unk0204f798::func_0204fda8(int i) {
    return sprites[i];
}

void Unk0204f798::func_0204fdb4() {
    counter = 0;
    flags &= ~2;
}

void Unk0204f798::func_0204fdcc(bool loop) {
    if (loop) {
        flags |= 1;
    } else {
        flags &= ~1;
    }
}
