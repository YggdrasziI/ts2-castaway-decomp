/*
 * Unit 0x020A7C10-0x020A7D74: the base of the placed elements of a layout: position, visibility,
 * palette and anchor cell. Bounds: hypothesis (one class, from its constructor to the next, and one
 * vtable, whose four empty slots are pure functions). All names are placeholders. Real file name
 * unknown.
 */
#include "game/unk_layoutsprite.h"

Unk020a7c10::Unk020a7c10() : x(0), y(0), unk14(0), cellX(-1), cellY(-1) {}

Unk020a7c10::~Unk020a7c10() {}

static inline bool func_shown(Unk020a7c10 *s) {
    return (s->flags & 2) != 0;
}

extern "C" void func_020a7c90(Unk020a7c90 *p, int x) {
    Unk020a7c10 *s = (Unk020a7c10 *)p;
    s->x = x;
    s->flags |= 4;
}

extern "C" int func_020a7ca4(Unk020a7c90 *p) {
    return ((Unk020a7c10 *)p)->x;
}

extern "C" void func_020a7cac(Unk020a7c90 *p, int y) {
    Unk020a7c10 *s = (Unk020a7c10 *)p;
    s->y = y;
    s->flags |= 4;
}

extern "C" int func_020a7cc0(Unk020a7c90 *p) {
    return ((Unk020a7c10 *)p)->y;
}

extern "C" void func_020a7cc8(Unk020a7c10 *s, int x, int y) {
    s->x = x;
    s->y = y;
    s->flags |= 4;
}

extern "C" void func_020a7ce0(Unk020a7c10 *s) {
    s->flags |= 0x10;
}

extern "C" void func_020a7cf0(Unk020a7c90 *p, bool show) {
    Unk020a7c10 *s = (Unk020a7c10 *)p;
    if (show == func_shown(s)) {
        return;
    }
    *(volatile u32 *)&s->flags = (*(volatile u32 *)&s->flags ^ 2) | 0x10;
}

extern "C" bool func_020a7d1c(Unk020a7c10 *s) {
    return (s->flags & 2) != 0;
}

extern "C" void func_020a7d30(Unk020a7c10 *s, int v) {
    s->unk14 = v;
    s->flags |= 8;
}

extern "C" int func_020a7d44(Unk020a7c10 *s) {
    return s->unk14;
}

extern "C" void func_020a7d4c(Unk020a7c10 *s, int cell) {
    s->cellX = cell;
    s->flags |= 0x20;
}

extern "C" void func_020a7d60(Unk020a7c10 *s, int cell) {
    s->cellY = cell;
    s->flags |= 0x20;
}
