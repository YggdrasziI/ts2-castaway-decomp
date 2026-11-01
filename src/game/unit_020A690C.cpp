/*
 * Unit 0x020A690C-0x020A6A00: the sprite base of a layout, with an animation name and frame.
 * Bounds: hypothesis (one class, from its constructor to the next; the order of the vtables in
 * `.data` needs one file for each class). All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

Unk020a690c::Unk020a690c() : frame(0), hash(0), count(0) {}

Unk020a690c::~Unk020a690c() {}

extern "C" void func_020a6980(Unk020a690c *s, u32 hash) {
    if (s->hash != hash) {
        s->count = 0;
    }
    s->hash = hash;
    s->flags |= 0x40;
}

extern "C" u32 func_020a69a4(Unk020a690c *s) {
    return s->hash;
}

extern "C" void func_020a69ac(Unk020a690c *s, int frame) {
    if (s->frame != frame) {
        s->frame = frame;
        s->flags |= 0x80;
    }
}

extern "C" int func_020a69cc(Unk020a690c *s) {
    return s->frame;
}

extern "C" int func_020a69d4(Unk020a690c *s) {
    return s->count;
}

extern "C" void func_020a69dc(Unk020a690c *s) {
    func_020a69ac(s, s->frame == s->count - 1 ? 0 : s->frame + 1);
}
