/*
 * Unit 0x020A9054-0x020A90F8: the vector element of a layout with a scale. Bounds: hypothesis (one
 * class, from its constructor to the next, and one vtable). All names are placeholders. Real file
 * name unknown.
 */
#include "game/unk_layoutsprite.h"

class Unk020a9054 : public Unk020a8f84 {
public:
    Unk020a9054();
    virtual ~Unk020a9054();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    int scaleX;
    int scaleY;
    int scaleZ;
};

Unk020a9054::Unk020a9054() : scaleX(0x1000), scaleY(0x1000), scaleZ(0x1000) {}

Unk020a9054::~Unk020a9054() {}

extern "C" void func_020a90b4(Unk020a9054 *s, int v) {
    s->scaleX = v;
    s->flags |= 0x10;
}

extern "C" void func_020a90c8(Unk020a9054 *s, int v) {
    s->scaleY = v;
    s->flags |= 0x20;
}

extern "C" void func_020a90dc(Unk020a9054 *s, int v) {
    s->scaleZ = v;
    s->flags |= 0x40;
}

void Unk020a9054::func_08(Unk020a9d58 *layout, int on) {}

void Unk020a9054::func_0c(Unk020a9d58 *layout) {}
