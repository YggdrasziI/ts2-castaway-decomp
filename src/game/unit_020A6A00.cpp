/*
 * Unit 0x020A6A00-0x020A6DD8: the sprite shown through a layer of the screen: its file is loaded
 * and freed with the visibility. Bounds: hypothesis, as for 0x020A690C. All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

static inline bool func_moved(u32 flags) {
    if (flags & 0xc0) {
        return true;
    }
    return false;
}

Unk020a6a00::Unk020a6a00() : priority(0), parent(-1), layer(0) {}

Unk020a6a00::~Unk020a6a00() {}

extern "C" void func_020a6a64(Unk020a6a00 *s, int priority) {
    s->priority = priority;
    s->flags |= 0x100;
}

extern "C" void func_020a6a78(Unk020a6a00 *s, int parent) {
    s->parent = parent;
    s->flags |= 0x200;
}

extern "C" int func_020a6a8c(Unk020a6a00 *s) {
    return s->parent;
}

void Unk020a6a00::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        flags ^= 1;
        if (on == 1) {
            func_020a6bcc(this, layout);
        } else {
            func_020a6d38(this, layout);
        }
    }
}

void Unk020a6a00::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x3fc)) {
        return;
    }
    if (func_moved(f) == true) {
        func_020a6d38(this, layout);
        func_020a6bcc(this, layout);
        return;
    }
    if (f & 4) {
        int px = x + (cellX + 1) * (func_10() >> 1);
        int py = y + (cellY + 1) * (func_14() >> 1);
        layer->x = px;
        layer->y = py;
    }
    if (flags & 0x10) {
        layer->func_0208d7a0(func_020a7d1c(this));
    }
    if (flags & 0x100) {
        layer->func_0208d4b0(priority);
    }
    flags &= ~0x3fc;
}

extern "C" void func_020a6bcc(Unk020a6a00 *s, Unk020a9d58 *l) {
    u32 hash = func_020a69a4(s);
    if (hash == 0) {
        return;
    }
    Unk02093648 *archive = func_020aa064(l);
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(hash));
    Unk02095140Header *header = file->func_02095180();
    s->count = header->count;
    if (func_020a69cc(s) >= s->count) {
        func_020a69ac(s, header->count - 1);
    }
    int flag = header->width == 0x20;
    int charBase = -1;
    if (s->parent != -1) {
        charBase = ((Unk020a6a00 *)((Unk020aa040Func)func_020aa040)(l, 2, s->parent))->layer->func_0208d4c8();
    }
    Unk0208db14 *list = func_020aa410(l);
    s->layer = list->func_0208dc44(file, flag, charBase, func_020a69cc(s));
    int px = s->x + (s->cellX + 1) * (s->func_10() >> 1);
    int py = s->y + (s->cellY + 1) * (s->func_14() >> 1);
    s->layer->x = px;
    s->layer->y = py;
    s->layer->func_0208d7a0(func_020a7d1c(s));
    s->layer->func_0208d4b0(s->priority);
    s->flags &= ~0x3fc;
}

extern "C" void func_020a6d38(Unk020a6a00 *s, Unk020a9d58 *l) {
    if (s->layer != 0) {
        Unk02093648 *archive;
        Unk0209487c *file;
        Unk0208d304 *layer;
        archive = func_020aa064(l);
        layer = s->layer;
        file = layer->file;
        func_020aa410(l)->func_0208df4c(layer);
        archive->func_02093c58(archive->func_02093f5c(file));
    }
    s->layer = 0;
}

int Unk020a6a00::func_10() {
    if (layer == 0) {
        return 0;
    }
    return layer->func_0208d808() << 12;
}

int Unk020a6a00::func_14() {
    if (layer == 0) {
        return 0;
    }
    return layer->func_0208d814() << 12;
}
