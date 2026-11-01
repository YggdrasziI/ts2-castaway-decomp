/*
 * Unit 0x020A7AF4-0x020A7B94: the name list of a layout, pairs of a hash and a value over the
 * caller's buffer. Bounds: hypothesis (from its constructor to the next class). All names are
 * placeholders. Real file name unknown.
 */
#include "game/unk_screen.h"

Unk020a7af4::Unk020a7af4(Unk020a7af4Entry *entries, int count) : entries(entries), count(count), used(0) {}

Unk020a7af4::~Unk020a7af4() {}

extern "C" int func_020a7b08(Unk020a7af4 *n, u32 hash, u32 value) {
    if (n->used == n->count) {
        return -1;
    }
    ((u32 *)n->entries)[n->used * 2] = hash;
    ((u32 *)n->entries)[n->used * 2 + 1] = value;
    n->used++;
    return n->used - 1;
}

extern "C" u32 func_020a7b50(Unk020a7af4 *n, u32 hash) {
    Unk020a7af4Entry *e;
    int i = n->used;
    e = n->entries;
    for (; i > 0; i--, e++) {
        if (e->unk0 == hash) {
            return e->unk4;
        }
    }
    return -1;
}

extern "C" void func_020a7b88(Unk020a7af4 *n) {
    n->used = 0;
}
