/*
 * Unit 0x020A79CC-0x020A7AA0: an element of a layout with four 16-bit values. Bounds: hypothesis
 * (one class, from its constructor to the next, and one vtable). All names are placeholders. Real
 * file name unknown.
 */
#include "game/unk_layoutsprite.h"

class Unk020a79cc : public Unk020a7aa0 {
public:
    Unk020a79cc();
    virtual ~Unk020a79cc();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    s16 unkc;
    s16 unke;
    s16 unk10;
    s16 unk12;
};

Unk020a79cc::Unk020a79cc() : unkc(0), unke(0), unk10(0), unk12(0) {}

Unk020a79cc::~Unk020a79cc() {}

extern "C" void func_020a7a30(Unk020a79cc *s, s16 v) {
    s->unkc = v;
    s->flags |= 2;
}

extern "C" s16 func_020a7a44(Unk020a79cc *s) {
    return s->unkc;
}

extern "C" void func_020a7a4c(Unk020a79cc *s, s16 v) {
    s->unke = v;
    s->flags |= 4;
}

extern "C" s16 func_020a7a60(Unk020a79cc *s) {
    return s->unke;
}

extern "C" void func_020a7a68(Unk020a79cc *s, s16 v) {
    s->unk10 = v;
    s->flags |= 8;
}

extern "C" s16 func_020a7a7c(Unk020a79cc *s) {
    return s->unk10;
}

extern "C" void func_020a7a84(Unk020a79cc *s, s16 v) {
    s->unk12 = v;
    s->flags |= 0x10;
}

void Unk020a79cc::func_08(Unk020a9d58 *layout, int on) {}

void Unk020a79cc::func_0c(Unk020a9d58 *layout) {}
