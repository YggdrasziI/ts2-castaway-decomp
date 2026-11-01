/*
 * Unit 0x020A70DC-0x020A79CC: the text of a layout: a sprite that owns a canvas (created and freed
 * with the visibility) and redraws its text when the flags ask for it. Bounds: hypothesis (one class,
 * from its constructor to the next, and one vtable). All names are placeholders. Real file name
 * unknown.
 */
#include "game/unk_layoutsprite.h"

#define va_start(ap, parm) ((ap) = (va_list)((char *)((u32)&(parm) & ~3U) + ((sizeof(parm) + 3U) & ~3U)))
#define va_end(ap) ((void)0)

class Unk020a70dc : public Unk020a7c10 {
public:
    Unk020a70dc();
    virtual ~Unk020a70dc();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);
    virtual int func_10();
    virtual int func_14();

    int spacing;
    int lineSpacing;
    int width;
    int height;
    int hAlign;
    int vAlign;
    int text;
    int font;
    Unk02090308 *canvas;
};

/* A text set of the layout, only what is used here. */
struct Unk020a70dcFont {
    u8 unk0[0x14];
    Unk02092830Font *font;
};

/* A layout, only what is used here. */
struct Unk020a70dcLayout {
    u8 unk0[0x74];
    u32 flags;
};

extern "C" {
int func_0208299c(char *buf, int size, const char *fmt, va_list args);
int func_020a705c(int align);
int func_020a709c(int align);
void func_020a6fd4(Unk02090308 *c, int flip);
void func_020a7018(Unk02090308 *c, int flip);
int func_020a7d44(Unk020a7c10 *s);
int func_020aa034(Unk020a9d58 *l, int type);
const char *func_020aa3c8(Unk020a9d58 *l, int text);
Unk020916a4 *func_020aa3f4(Unk020a9d58 *l);
bool func_020a71c0(Unk020a70dc *s);
bool func_020a7200(Unk020a70dc *s);
bool func_020a7240(Unk020a70dc *s);
void func_020a7600(Unk020a70dc *s, Unk020a9d58 *l);
void func_020a785c(Unk020a70dc *s, Unk020a9d58 *l);
void func_020a78cc(Unk020a70dc *s, Unk020a70dcFont *font, const char *fmt, ...);
}

static inline bool func_shown(u32 flags) {
    if (flags & 2) {
        return true;
    }
    return false;
}

static inline Unk020a70dcFont *func_font(Unk020a9d58 *l, int index) {
    return (Unk020a70dcFont *)((Unk020aa040Func)func_020aa040)(l, 0, index);
}

static inline void func_align(Unk020a70dc *s) {
    if (s->canvas != 0) {
        s->canvas->func_020908e0(func_020a705c(s->hAlign), func_020a709c(s->vAlign));
    } else {
        s->flags |= 0x10000;
    }
}

Unk020a70dc::Unk020a70dc() : width(0), height(0), hAlign(-1), vAlign(-1), text(0), font(-1), canvas(0) {}

Unk020a70dc::~Unk020a70dc() {}

extern "C" void func_020a7150(Unk020a70dc *s, int font) {
    s->font = font;
    s->flags |= 0x40000;
}

extern "C" int func_020a7164(Unk020a70dc *s) {
    return s->font;
}

extern "C" void func_020a716c(Unk020a70dc *s, int text) {
    s->text = text;
    s->flags |= 0x20000;
}

extern "C" int func_020a7180(Unk020a70dc *s) {
    return s->text;
}

extern "C" void func_020a7188(Unk020a70dc *s, int width) {
    s->width = width;
    s->flags |= 0x8000;
}

int Unk020a70dc::func_10() {
    return width;
}

extern "C" void func_020a71a4(Unk020a70dc *s, int height) {
    s->height = height;
    s->flags |= 0x8000;
}

int Unk020a70dc::func_14() {
    return height;
}

extern "C" bool func_020a71c0(Unk020a70dc *s) {
    return (s->flags & 0x100) != 0;
}

extern "C" void func_020a71d4(Unk020a70dc *s, int on) {
    if (on != func_020a7200(s)) {
        s->flags = (s->flags ^ 0x40) | 0x400;
    }
}

extern "C" bool func_020a7200(Unk020a70dc *s) {
    return (s->flags & 0x40) != 0;
}

extern "C" void func_020a7214(Unk020a70dc *s, int on) {
    if (on != func_020a7240(s)) {
        s->flags = (s->flags ^ 0x80) | 0x800;
    }
}

extern "C" bool func_020a7240(Unk020a70dc *s) {
    return (s->flags & 0x80) != 0;
}

extern "C" void func_020a7254(Unk020a70dc *s, int spacing) {
    s->spacing = spacing;
    s->flags |= 0x2000;
}

extern "C" void func_020a7268(Unk020a70dc *s, int spacing) {
    s->lineSpacing = spacing;
    s->flags |= 0x1000;
}

extern "C" void func_020a727c(Unk020a70dc *s, int align) {
    s->hAlign = align;
    func_align(s);
}

extern "C" int func_020a72c8(Unk020a70dc *s) {
    return s->hAlign;
}

extern "C" void func_020a72d0(Unk020a70dc *s, int align) {
    s->vAlign = align;
    func_align(s);
}

extern "C" int func_020a731c(Unk020a70dc *s) {
    return s->vAlign;
}

void Unk020a70dc::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        u32 f = flags ^ 1;
        flags = f;
        if (f & 2) {
            if (on == 1) {
                func_020a7600(this, layout);
            } else {
                func_020a785c(this, layout);
            }
        }
    }
}

void Unk020a70dc::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x7fe3c)) {
        return;
    }
    if (func_shown(f) == false) {
        func_020a785c(this, layout);
    } else if (f & 0x8010) {
        func_020a785c(this, layout);
        func_020a7600(this, layout);
    } else {
        Unk020916a4 *oam = func_020aa3f4(layout);
        if (flags & 0x24) {
            int px = x + (cellX + 1) * -(func_10() >> 1);
            int py = y + (cellY + 1) * -(func_14() >> 1);
            canvas->func_02090878(px, py);
        }
        if (flags & 8) {
            canvas->func_020905d4((u16)func_020a7d44(this));
        }
        if (flags & 0x400) {
            func_020a6fd4(canvas, func_020a7200(this));
        }
        if (flags & 0x800) {
            func_020a7018(canvas, func_020a7240(this));
        }
        if (flags & 0x1000) {
            int n = canvas->func_02090c84();
            for (int i = 0; i < n; i++) {
                oam->func_02091a0c(canvas->func_02090c8c(i), lineSpacing);
            }
        }
        if (flags & 0x2000) {
            canvas->func_02090898((u16)spacing);
        }
        if (flags & 0x4000) {
            canvas->func_02090620(func_020a71c0(this) == 1);
        }
        if (flags & 0x10000) {
            canvas->func_020908e0(func_020a705c(hAlign), func_020a709c(vAlign));
        }
        if (text != 0 && font != -1) {
            u32 g = flags;
            if ((g & 0x20000) || (g & 0x40000)) {
                canvas->func_0209088c();
                Unk020a70dcFont *set = func_font(layout, font);
                func_020a78cc(this, set, func_020aa3c8(layout, text));
            }
        }
    }
    flags &= 0xfff801c3;
}

extern "C" void func_020a7600(Unk020a70dc *s, Unk020a9d58 *l) {
    int oy;
    int py;
    int ox;
    int px;
    if (s->width <= 0 || s->height <= 0) {
        return;
    }
    s->canvas = new Unk02090308();
    ox = (s->cellX + 1) * -(s->width >> 1);
    oy = (s->cellY + 1) * -(s->height >> 1);
    px = s->x;
    py = s->y;
    s->canvas->func_020905c4((((Unk020a70dcLayout *)l)->flags & 2) != 0);
    int cols = s->width >> 17;
    if ((s->width >> 12) % 32) {
        cols++;
    }
    int rows = s->height >> 17;
    if ((s->height >> 12) % 32) {
        rows++;
    }
    s->canvas->func_0209066c(cols, rows);
    Unk02098bc8 rect(0, 0, s->width >> 12, s->height >> 12);
    s->canvas->func_020908bc(&rect);
    s->canvas->func_02090878(px + ox, py + oy);
    s->canvas->func_020905d4((u16)func_020a7d44(s));
    s->canvas->func_02090898((u16)s->spacing);
    s->canvas->func_020908ac((u16)s->lineSpacing);
    s->canvas->func_020908e0(func_020a705c(s->hAlign), func_020a709c(s->vAlign));
    if (func_020a71c0(s) == 1) {
        s->canvas->func_02090620(1);
    }
    s->canvas->func_020905ac();
    func_020a6fd4(s->canvas, func_020a7200(s));
    func_020a7018(s->canvas, func_020a7240(s));
    if (s->text != 0 && s->font != -1) {
        if (s->font >= func_020aa034(l, 0)) {
            return;
        }
        if (func_font(l, s->font)->font == 0) {
            return;
        }
        Unk020a70dcFont *set = func_font(l, s->font);
        func_020a78cc(s, set, func_020aa3c8(l, s->text));
    }
    s->flags &= 0xfff801c3;
}

extern "C" void func_020a785c(Unk020a70dc *s, Unk020a9d58 *l) {
    delete s->canvas;
    s->canvas = 0;
}

extern "C" void func_020a788c(Unk020a70dc *s, int x, int y, Unk02095140 *file, int index) {
    if (s->canvas != 0) {
        s->canvas->func_020906e4(file, x, y, index);
    }
}

extern "C" void func_020a78cc(Unk020a70dc *s, Unk020a70dcFont *font, const char *fmt, ...) {
    char buf[0x200];
    va_list args;

    if (s->canvas == 0 || font->font == 0) {
        return;
    }
    va_start(args, fmt);
    func_0208299c(buf, 0x200, fmt, args);
    va_end(args);
    s->canvas->func_020909c8(font->font, buf);
}

extern "C" bool func_020a793c(Unk020a70dc *s, int page, Unk020a70dcFont *font, const char *fmt, ...) {
    char buf[0x200];
    va_list args;

    if (s->canvas == 0) {
        return false;
    }
    if (font->font == 0) {
        return false;
    }
    va_start(args, fmt);
    func_0208299c(buf, 0x200, fmt, args);
    va_end(args);
    return s->canvas->func_02090b08(page, font->font, buf);
}
