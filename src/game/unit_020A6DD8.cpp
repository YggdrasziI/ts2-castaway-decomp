/*
 * Unit 0x020A6DD8-0x020A70DC: the group that shows a run of sprites, and small helpers on canvases
 * and alignment. Bounds: hypothesis, as for 0x020A690C; where the helpers end the class is unknown. All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

Unk020a6dd8::Unk020a6dd8() : unkc(0), unk10(0), first(-1), count(1) {}

Unk020a6dd8::~Unk020a6dd8() {}

extern "C" void func_020a6e44(Unk020a6dd8 *s, int first) {
    s->first = first;
    s->flags |= 0x40;
}

extern "C" int func_020a6e58(Unk020a6dd8 *s) {
    return s->first;
}

extern "C" void func_020a6e60(Unk020a6dd8 *s, int count) {
    s->count = count;
    s->flags |= 0x80;
}

extern "C" int func_020a6e74(Unk020a6dd8 *s) {
    return s->count;
}

extern "C" void func_020a6e7c(Unk020a6dd8 *s, int on) {
    if (on != func_020a6ea8(s)) {
        s->flags = (s->flags ^ 4) | 0x20;
    }
}

extern "C" bool func_020a6ea8(Unk020a6dd8 *s) {
    return (s->flags & 4) != 0;
}

extern "C" void func_020a6ebc(Unk020a6dd8 *s, int on) {
    if (on != func_020a6ee8(s)) {
        s->flags = (s->flags ^ 2) | 0x10;
    }
}

extern "C" bool func_020a6ee8(Unk020a6dd8 *s) {
    return (s->flags & 2) != 0;
}

extern "C" void func_020a6efc(Unk020a6dd8 *s, int on) {
    if (on != func_020a6f28(s)) {
        s->flags = (s->flags ^ 8) | 0x100;
    }
}

extern "C" bool func_020a6f28(Unk020a6dd8 *s) {
    return (s->flags & 8) != 0;
}

void Unk020a6dd8::func_08(Unk020a9d58 *layout, int on) {}

void Unk020a6dd8::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x1f0)) {
        return;
    }
    if ((f & 0x20) && first != -1 && count > 0) {
        u8 *sprite;
        int i;
        bool show = func_020a6ea8(this);
        sprite = (u8 *)((Unk020aa040Func)func_020aa040)(layout, 1, first);
        for (i = 0; i < count; i++) {
            func_020a7cf0((Unk020a7c90 *)sprite, show);
            sprite += 0x44;
        }
    }
    flags &= ~0x1f0;
}

extern "C" void func_020a6fd4(Unk02090308 *c, int flip) {
    int n = c->func_02090c84();
    for (int i = 0; i < n; i++) {
        c->func_02090c8c(i)->func_0208fbac(flip);
    }
}

extern "C" void func_020a7018(Unk02090308 *c, int flip) {
    int n = c->func_02090c84();
    for (int i = 0; i < n; i++) {
        c->func_02090c8c(i)->func_0208fbe0(flip);
    }
}

extern "C" int func_020a705c(int align) {
    switch (align) {
    case -1:
        return 0;
    case 0:
        return 1;
    case 1:
        return 2;
    }
    return 0;
}

extern "C" int func_020a709c(int align) {
    switch (align) {
    case -1:
        return 0;
    case 0:
        return 1;
    case 1:
        return 2;
    }
    return 0;
}
