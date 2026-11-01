/*
 * Unit 0x020A90F8-0x020A9914: the sprite of a layout drawn as one object: its file is loaded and freed
 * with the visibility, an object of the same image and frame can be shared, and it can be rotated
 * and scaled. Bounds: hypothesis (one class, from its constructor to the next, and one vtable). All
 * names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

extern "C" {
Unk02093648 *func_020aa064(Unk020a9d58 *l);
int func_020aa034(Unk020a9d58 *l, int type);
Unk020916a4 *func_020aa3f4(Unk020a9d58 *l);
int func_020a7d44(Unk020a7c10 *s);
bool func_020a91d8(Unk020a90f8 *s);
bool func_020a9218(Unk020a90f8 *s);
bool func_020a9278(Unk020a90f8 *s);
bool func_020a92b0(Unk020a90f8 *s);
void func_020a9584(Unk020a90f8 *s, Unk020a9d58 *l);
void func_020a97d4(Unk020a90f8 *s, Unk020a9d58 *l);
}

static inline bool func_shown(u32 flags) {
    if (flags & 2) {
        return true;
    }
    return false;
}

static inline volatile u32 *func_flags(Unk020a90f8 *s) {
    return (volatile u32 *)&s->flags;
}

Unk020a90f8::Unk020a90f8() : angle(0), scaleX(0x100), scaleY(0x100), order(0), priority(0), object(0) {}

Unk020a90f8::~Unk020a90f8() {}

extern "C" void func_020a9168(Unk020a90f8 *s, int angle) {
    s->angle = angle;
    s->flags |= 0x1000;
}

extern "C" int func_020a917c(Unk020a90f8 *s) {
    return s->angle;
}

extern "C" void func_020a9184(Unk020a90f8 *s, int scale) {
    s->scaleX = scale;
    s->flags |= 0x1000;
}

extern "C" void func_020a9198(Unk020a90f8 *s, int scale) {
    s->scaleY = scale;
    s->flags |= 0x1000;
}

extern "C" void func_020a91ac(Unk020a90f8 *s, int on) {
    if (on == (int)((s->flags & 0x100) != 0)) {
        return;
    }
    *func_flags(s) = (*func_flags(s) ^ 0x100) | 0x2000;
}

extern "C" bool func_020a91d8(Unk020a90f8 *s) {
    return (s->flags & 0x100) != 0;
}

extern "C" void func_020a91ec(Unk020a90f8 *s, int on) {
    if (on == (int)((s->flags & 0x200) != 0)) {
        return;
    }
    *func_flags(s) = (*func_flags(s) ^ 0x200) | 0x4000;
}

extern "C" bool func_020a9218(Unk020a90f8 *s) {
    return (s->flags & 0x200) != 0;
}

extern "C" void func_020a922c(Unk020a90f8 *s, int order) {
    s->order = order;
    s->flags |= 0x8000;
}

extern "C" void func_020a9240(Unk020a90f8 *s, int priority) {
    s->priority = priority;
    s->flags |= 0x10000;
}

extern "C" void func_020a9254(Unk020a90f8 *s, int on) {
    if (on != (int)((s->flags & 0x400) != 0)) {
        *func_flags(s) = *func_flags(s) ^ 0x400;
    }
}

extern "C" bool func_020a9278(Unk020a90f8 *s) {
    return (s->flags & 0x400) != 0;
}

extern "C" void func_020a928c(Unk020a90f8 *s, int on) {
    if (on != (int)((s->flags & 0x800) != 0)) {
        *func_flags(s) = *func_flags(s) ^ 0x800;
    }
}

extern "C" bool func_020a92b0(Unk020a90f8 *s) {
    return (s->flags & 0x800) != 0;
}

void Unk020a90f8::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        flags ^= 1;
        if (on == 1) {
            if (flags & 2) {
                func_020a9584(this, layout);
            }
        } else {
            func_020a97d4(this, layout);
        }
    }
}

void Unk020a90f8::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x3f0fc)) {
        return;
    }
    if (func_shown(f) == false) {
        func_020a97d4(this, layout);
    } else {
        int moved = (f & 0x10) != 0;
        int changed = (f & 0x40) != 0;
        if (changed == 1 || moved == 1) {
            func_020a97d4(this, layout);
            func_020a9584(this, layout);
        } else {
            Unk020916a4 *oam = func_020aa3f4(layout);
            if (flags & 0x80) {
                object->func_0208faac(func_020a69cc(this));
            }
            if (flags & 0x24) {
                int px = x + (cellX + 1) * -(func_10() >> 1);
                int py = y + (cellY + 1) * -(func_14() >> 1);
                object->unk0 = px;
                object->unk4 = py;
            }
            if (flags & 8) {
                object->func_0208fb98(func_020a7d44(this));
            }
            if (flags & 0x1000) {
                if (angle == 0 && scaleX == 0x100 && scaleY == 0x100) {
                    if (object->func_0208fcf0() == true) {
                        oam->func_0209241c(object);
                    }
                } else {
                    oam->func_020921c4(object, angle, scaleX, scaleY);
                }
            }
            if (flags & 0x2000) {
                object->func_0208fbac(func_020a91d8(this));
            }
            if (flags & 0x4000) {
                object->func_0208fbe0(func_020a9218(this));
            }
            if (flags & 0x8000) {
                oam->func_02091a0c(object, order);
            }
            if (flags & 0x10000) {
                object->func_0208fb80(priority);
            }
            if (flags & 0x20000) {
                object->func_0208fb6c(func_020a92b0(this) == true);
            }
        }
    }
    flags &= 0xfffc0f03;
}

extern "C" void func_020a9584(Unk020a90f8 *s, Unk020a9d58 *l) {
    u32 hash = func_020a69a4(s);
    if (hash == 0) {
        return;
    }
    Unk02093648 *archive = func_020aa064(l);
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(hash));
    int count = file->func_02095180()->count;
    if (func_020a69cc(s) >= count) {
        func_020a69ac(s, count - 1);
    }
    Unk020916a4 *oam = func_020aa3f4(l);
    s->object = oam->func_020919e4((int)file, s->order);
    if (func_020a9278(s) == true) {
        Unk020a90f8 *o = (Unk020a90f8 *)func_020aa040(l, 1, 0);
        int n = func_020aa034(l, 1);
        for (; n > 0; n--, o++) {
            if (o != s && hash == func_020a69a4(o)) {
                int frame = func_020a69cc(o);
                if (frame == func_020a69cc(s) && o->object != 0) {
                    oam->func_02091de0(o->object, s->object);
                    break;
                }
            }
        }
    }
    int px = s->x + (s->cellX + 1) * -(s->func_10() >> 1);
    int py = s->y + (s->cellY + 1) * -(s->func_14() >> 1);
    s->object->unk0 = px;
    s->object->unk4 = py;
    s->object->func_0208faac(func_020a69cc(s));
    s->object->func_0208fb98(func_020a7d44(s));
    s->object->func_0208fbac(func_020a91d8(s));
    s->object->func_0208fbe0(func_020a9218(s));
    s->object->func_0208fb80(s->priority);
    if (func_020a92b0(s) == true) {
        s->object->func_0208fb6c(1);
    }
    s->count = s->object->func_0208fa84();
    if (!(s->angle == 0 && s->scaleX == 0x100 && s->scaleY == 0x100)) {
        oam->func_020921c4(s->object, s->angle, s->scaleX, s->scaleY);
    }
    s->flags &= 0xfffc0f03;
}

extern "C" void func_020a97d4(Unk020a90f8 *s, Unk020a9d58 *l) {
    if (s->object != 0) {
        Unk02093648 *archive;
        Unk02095140 *file;
        Unk0208f8b0 *object;
        archive = func_020aa064(l);
        object = s->object;
        file = object->unk1c;
        func_020aa3f4(l)->func_02091c68(object);
        archive->func_02093c58(archive->func_02093f5c(file));
    }
    s->object = 0;
}

int Unk020a90f8::func_10() {
    if (object == 0) {
        return 0;
    }
    return (1 << (object->unk10_0 + 3)) << 12;
}

int Unk020a90f8::func_14() {
    if (object == 0) {
        return 0;
    }
    return (1 << (object->unk10_2 + 3)) << 12;
}

extern "C" int func_020a9894(int align) {
    switch (align) {
    case -1:
        return 0;
    case 0:
        return 2;
    case 1:
        return 1;
    }
    return 0;
}

extern "C" int func_020a98d4(int align) {
    switch (align) {
    case -1:
        return 0;
    case 0:
        return 8;
    case 1:
        return 4;
    }
    return 0;
}
