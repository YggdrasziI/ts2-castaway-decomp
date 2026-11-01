/*
 * Unit 0x020A8F84-0x020A9054: an element of a layout with a vector. Bounds: hypothesis (one class,
 * from its constructors to the next, and one vtable). All names are placeholders. Real file name
 * unknown.
 */
#include "game/unk_layoutsprite.h"

Unk020a8f84::Unk020a8f84() {}

Unk020a8f84::~Unk020a8f84() {}

extern "C" void func_020a9008(Unk020a8f84 *s, int x) {
    s->pos.x = x;
    s->flags |= 2;
}

extern "C" void func_020a901c(Unk020a8f84 *s, int y) {
    s->pos.y = y;
    s->flags |= 4;
}

extern "C" void func_020a9030(Unk020a8f84 *s, int z) {
    s->pos.z = z;
    s->flags |= 8;
}

extern "C" Unk020a8f84Vec *func_020a9044(Unk020a8f84 *s) {
    return &s->pos;
}

void Unk020a8f84::func_08(Unk020a9d58 *layout, int on) {}

void Unk020a8f84::func_0c(Unk020a9d58 *layout) {}
