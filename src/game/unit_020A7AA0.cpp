/*
 * Unit 0x020A7AA0-0x020A7AF4: the base of the elements of a layout. Bounds: hypothesis (one class,
 * from its constructor to the name list, and one vtable, whose two empty slots are pure functions).
 * All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

Unk020a7aa0::Unk020a7aa0() : flags(0), unk8(0) {}

Unk020a7aa0::~Unk020a7aa0() {}

extern "C" bool func_020a7ad8(Unk020a7aa0 *s) {
    return (s->flags & 1) != 0;
}

extern "C" void func_020a7aec(Unk020a7aa0 *s, int v) {
    s->unk8 = v;
}
