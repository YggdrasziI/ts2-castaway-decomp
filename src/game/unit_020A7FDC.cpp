/*
 * Unit 0x020A7FDC-0x020A8228: an element of a layout that sends a frame of a file through a load
 * function given by the caller, in units of 32 bytes. Bounds: hypothesis (one class, from its
 * constructor to the next, and one vtable). All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

typedef void (*Unk020a80bcLoad)(void *data, u32 offset, u32 size);

class Unk020a7fdc : public Unk020a7aa0 {
public:
    Unk020a7fdc();
    virtual ~Unk020a7fdc();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    u32 hash;
    int source;
    int offset;
    int size;
    int frame;
    int count;
    Unk020a80bcLoad load;
    Unk02095140 *file;
};

extern "C" {
Unk02093648 *func_020aa064(Unk020a9d58 *l);
u32 func_020a805c(Unk020a7fdc *s);
void func_020a80a0(Unk020a7fdc *s, int frame);
int func_020a80b4(Unk020a7fdc *s);
void func_020a8168(Unk020a7fdc *s, Unk020a9d58 *l);
}

Unk020a7fdc::Unk020a7fdc() : hash(0), source(0), offset(0), size(0), load(0), file(0) {}

Unk020a7fdc::~Unk020a7fdc() {}

extern "C" void func_020a8048(Unk020a7fdc *s, u32 hash) {
    s->hash = hash;
    s->flags |= 2;
}

extern "C" u32 func_020a805c(Unk020a7fdc *s) {
    return s->hash;
}

extern "C" void func_020a8064(Unk020a7fdc *s, int v) {
    s->source = v;
    s->flags |= 4;
}

extern "C" void func_020a8078(Unk020a7fdc *s, int v) {
    s->offset = v;
    s->flags |= 8;
}

extern "C" void func_020a808c(Unk020a7fdc *s, int v) {
    s->size = v;
    s->flags |= 0x10;
}

extern "C" void func_020a80a0(Unk020a7fdc *s, int frame) {
    s->frame = frame;
    s->flags |= 0x20;
}

extern "C" int func_020a80b4(Unk020a7fdc *s) {
    return s->frame;
}

extern "C" void func_020a80bc(Unk020a7fdc *s, Unk020a80bcLoad load) {
    s->load = load;
}

extern "C" Unk020a80bcLoad func_020a80c4(Unk020a7fdc *s) {
    return s->load;
}

void Unk020a7fdc::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        flags ^= 1;
        if (on == 1) {
            func_020a8168(this, layout);
        } else {
            Unk02093648 *archive = func_020aa064(layout);
            if (file != 0) {
                archive->func_02093c58(archive->func_02093f5c(file));
                file = 0;
            }
        }
    }
}

void Unk020a7fdc::func_0c(Unk020a9d58 *layout) {
    if (flags & 0x3e) {
        func_020a8168(this, layout);
        flags &= ~0x3e;
    }
}

extern "C" void func_020a8168(Unk020a7fdc *s, Unk020a9d58 *l) {
    if (s->load == 0) {
        return;
    }
    u32 hash = func_020a805c(s);
    if (hash == 0) {
        return;
    }
    Unk02093648 *archive = func_020aa064(l);
    s->file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(hash));
    Unk02095140Header *header = s->file->func_02095180();
    s->count = header->count;
    if (func_020a80b4(s) >= s->count) {
        func_020a80a0(s, header->count - 1);
    }
    u8 *data = s->file->func_02095354(func_020a80b4(s));
    s->load(data + (s->source << 5), s->offset << 5, s->size << 5);
    s->flags &= ~0x3e;
}
