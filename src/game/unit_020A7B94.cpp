/*
 * Unit 0x020A7B94-0x020A7C10: an element of a layout with one value. Bounds: hypothesis (one class,
 * from its constructor to the next, and one vtable). All names are placeholders. Real file name
 * unknown.
 */
#include "game/unk_layoutsprite.h"

class Unk020a7b94 : public Unk020a7aa0 {
public:
    Unk020a7b94();
    virtual ~Unk020a7b94();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    int value;
};

Unk020a7b94::Unk020a7b94() : value(0) {}

Unk020a7b94::~Unk020a7b94() {}

extern "C" void func_020a7bec(Unk020a7b94 *s, int value) {
    s->value = value;
    s->flags |= 2;
}

extern "C" int func_020a7c00(Unk020a7b94 *s) {
    return s->value;
}

void Unk020a7b94::func_08(Unk020a9d58 *layout, int on) {}

void Unk020a7b94::func_0c(Unk020a9d58 *layout) {}
