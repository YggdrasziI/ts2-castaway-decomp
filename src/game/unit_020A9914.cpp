/*
 * Unit 0x020A9914-0x020A9D58: the text box of a layout: a text object created and freed with the
 * visibility. Bounds: hypothesis (one class, from its constructor to the layout itself, and one
 * vtable). All names are placeholders. Real file name unknown.
 */
#include "game/unk_layoutsprite.h"

class Unk02090ccc : public Unk02092704 {
public:
    Unk02090ccc();
    ~Unk02090ccc();
    void func_02090d80(int screen);
    void func_02090d9c(Unk02092830Font *font, const char *fmt, ...);
    void func_02090e18(int unk);
    void func_02090e78(int priority);
    void func_02090e84(int unk);
    void func_020927bc();
    void func_02092788();

    u8 unk[0x63c - sizeof(Unk02092704)];
};

class Unk020a9914 : public Unk020a7c10 {
public:
    Unk020a9914();
    virtual ~Unk020a9914();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);
    virtual int func_10();
    virtual int func_14();

    int font;
    int text;
    int spacing;
    int priority;
    int width;
    int height;
    Unk02090ccc *box;
};

/* A text set of the layout, only what is used here. */
struct Unk020a9914Font {
    u8 unk0[0x14];
    Unk02092830Font *font;
};

/* A layout, only what is used here. */
struct Unk020a9914Layout {
    u8 unk0[0x74];
    u32 flags;
};

extern "C" {
int func_020a7d44(Unk020a7c10 *s);
int func_020a9894(int align);
int func_020a98d4(int align);
int func_020a99c0(Unk020a9914 *s);
void func_020a9bd8(Unk020a9914 *s, Unk020a9d58 *l);
void func_020a9d2c(Unk020a9914 *s, Unk020a9d58 *l);
int func_020aa034(Unk020a9d58 *l, int type);
const char *func_020aa3c8(Unk020a9d58 *l, int text);
}

static inline bool func_shown(u32 flags) {
    if (flags & 2) {
        return true;
    }
    return false;
}

Unk020a9914::Unk020a9914() : font(-1), text(0), spacing(0), priority(0), width(0x100000), height(0xc0000), box(0) {}

Unk020a9914::~Unk020a9914() {}

extern "C" void func_020a9990(Unk020a9914 *s, int font) {
    s->font = font;
    s->flags |= 0x40;
}

extern "C" int func_020a99a4(Unk020a9914 *s) {
    return s->font;
}

extern "C" void func_020a99ac(Unk020a9914 *s, int text) {
    s->text = text;
    s->flags |= 0x80;
}

extern "C" int func_020a99c0(Unk020a9914 *s) {
    return s->text;
}

extern "C" void func_020a99c8(Unk020a9914 *s, int width) {
    s->width = width;
    s->flags |= 0x100;
}

int Unk020a9914::func_10() {
    return width;
}

extern "C" void func_020a99e4(Unk020a9914 *s, int height) {
    s->height = height;
    s->flags |= 0x100;
}

int Unk020a9914::func_14() {
    return height;
}

extern "C" void func_020a9a00(Unk020a9914 *s, int v) {
    s->spacing = v;
    s->flags |= 0x200;
}

extern "C" void func_020a9a14(Unk020a9914 *s, int v) {
    s->priority = v;
    s->flags |= 0x400;
}

void Unk020a9914::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        u32 f = flags ^ 1;
        flags = f;
        if (f & 2) {
            if (on == 1) {
                func_020a9bd8(this, layout);
            } else {
                func_020a9d2c(this, layout);
            }
        }
    }
}

void Unk020a9914::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x7fc)) {
        return;
    }
    if (func_shown(f) == false) {
        func_020a9d2c(this, layout);
    } else {
        int moved = (f & 0x10) != 0;
        int changed = (f & 0xc0) != 0;
        if (changed == 1 || moved == 1) {
            func_020a9d2c(this, layout);
            func_020a9bd8(this, layout);
        } else {
            if (f & 0x100) {
                box->func_0209278c(width, height);
            }
            if (flags & 4) {
                box->func_0209276c(x, y);
            }
            if (flags & 8) {
                box->func_02090e18(func_020a7d44(this));
            }
            if (flags & 0x20) {
                box->func_02092808(func_020a9894(cellX), func_020a98d4(cellY));
            }
            if (flags & 0x200) {
                box->func_02090e84((u16)spacing);
            }
            if (flags & 0x400) {
                box->func_02090e78((u16)priority);
            }
        }
    }
    flags &= 0xfffff803;
}

extern "C" void func_020a9bd8(Unk020a9914 *s, Unk020a9d58 *l) {
    const char *str;
    Unk02092830Font *font;
    if (func_020a99c0(s) == 0 || s->font == -1) {
        return;
    }
    if (s->font >= func_020aa034(l, 0)) {
        return;
    }
    font = ((Unk020a9914Font *)((Unk020aa040Func)func_020aa040)(l, 0, s->font))->font;
    if (font == 0) {
        return;
    }
    str = func_020aa3c8(l, s->text);
    s->box = new Unk02090ccc();
    Unk02098bc8 rect(s->x, s->y, s->width, s->height);
    s->box->func_02090d80((((Unk020a9914Layout *)l)->flags & 2) != 0);
    s->box->func_020927c0(&rect);
    s->box->func_02092808(func_020a9894(s->cellX), func_020a98d4(s->cellY));
    s->box->func_02090e18(s->unk14);
    s->box->func_02090e84((u16)s->spacing);
    s->box->func_02090e78((u16)s->priority);
    s->box->func_02090d9c(font, str);
    s->flags &= 0xfffff803;
}

extern "C" void func_020a9d2c(Unk020a9914 *s, Unk020a9d58 *l) {
    delete s->box;
    s->box = 0;
}
