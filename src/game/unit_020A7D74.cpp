/*
 * Unit 0x020A7D74-0x020A7FDC: the font of a layout: built from one or two files when the element
 * is shown, freed when it is hidden. Bounds: hypothesis (one class, from its constructor to the
 * next, and one vtable). All names are placeholders. Real file name unknown.
 */
#include "game/unk_font.h"
#include "game/unk_layoutsprite.h"

class Unk020a7d74 : public Unk020a7aa0 {
public:
    Unk020a7d74();
    virtual ~Unk020a7d74();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    u32 hash;
    u32 script;
    Unk0208e570 *font;
};

extern "C" {
Unk02093648 *func_020aa064(Unk020a9d58 *l);
u32 func_020a7de8(Unk020a7d74 *s);
u32 func_020a7e04(Unk020a7d74 *s);
void func_020a7ea8(Unk020a7d74 *s, Unk020a9d58 *l);
void func_020a7f6c(Unk020a7d74 *s, Unk020a9d58 *l);
}

Unk020a7d74::Unk020a7d74() : hash(0), script(0), font(0) {}

Unk020a7d74::~Unk020a7d74() {}

extern "C" void func_020a7dd4(Unk020a7d74 *s, u32 hash) {
    s->hash = hash;
    s->flags |= 2;
}

extern "C" u32 func_020a7de8(Unk020a7d74 *s) {
    return s->hash;
}

extern "C" void func_020a7df0(Unk020a7d74 *s, u32 hash) {
    s->script = hash;
    s->flags |= 4;
}

extern "C" u32 func_020a7e04(Unk020a7d74 *s) {
    return s->script;
}

void Unk020a7d74::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        flags ^= 1;
        if (on == 1) {
            func_020a7ea8(this, layout);
        } else {
            func_020a7f6c(this, layout);
        }
    }
}

void Unk020a7d74::func_0c(Unk020a9d58 *layout) {
    u32 f = flags & 6;
    if (f == 0) {
        return;
    }
    int c = f != 0;
    if (c == 1) {
        func_020a7f6c(this, layout);
        func_020a7ea8(this, layout);
    }
    flags &= ~6;
}

extern "C" void func_020a7ea8(Unk020a7d74 *s, Unk020a9d58 *l) {
    u32 hash = func_020a7de8(s);
    if (hash == 0) {
        return;
    }
    u32 name = func_020a7e04(s);
    Unk02093648 *archive = func_020aa064(l);
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(hash));
    Unk02096348 *script = 0;
    int index;
    if (name != 0) {
        index = archive->func_02093e9c(name);
        script = (Unk02096348 *)archive->func_02093a9c(index);
    }
    s->font = new Unk0208e570();
    s->font->func_08(file, script);
    if (name != 0) {
        archive->func_02093c58(index);
    }
    s->flags &= ~6;
}

extern "C" void func_020a7f6c(Unk020a7d74 *s, Unk020a9d58 *l) {
    if (s->font != 0) {
        Unk02093648 *archive = func_020aa064(l);
        Unk02095140 *file = s->font->func_34();
        delete s->font;
        archive->func_02093c58(archive->func_02093f5c(file));
    }
    s->font = 0;
}
