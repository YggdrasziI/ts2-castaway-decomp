/*
 * Unit 0x020A8228-0x020A8F84: the sprite of a layout drawn as a grid of objects of one file: the
 * objects are created with the visibility, tile the size of the sprite and can share their image
 * with another sprite of the same file. Bounds: hypothesis (one class, from its constructor to the
 * next, and one vtable). All names are placeholders. Real file name unknown.
 * Not complete: func_020a87f4 is at 99.39 % (register allocation only).
 */
#include "game/unk_layoutsprite.h"

class Unk020a8228 : public Unk020a690c {
public:
    Unk020a8228();
    virtual ~Unk020a8228();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);
    virtual int func_10();
    virtual int func_14();

    int width;
    int height;
    int offsetX;
    int offsetY;
    int rows;
    int cols;
    int order;
    int priority;
    int total;
    Unk0208f8b0 **objects;
};

extern "C" {
int func_020aa034(Unk020a9d58 *l, int type);
Unk020916a4 *func_020aa3f4(Unk020a9d58 *l);
int func_020a7d44(Unk020a7c10 *s);
bool func_020a82cc(Unk020a8228 *s);
bool func_020a830c(Unk020a8228 *s);
bool func_020a834c(Unk020a8228 *s);
int func_020a8388(Unk020a8228 *s);
void func_020a83b8(Unk020a8228 *s, int width);
void func_020a83d4(Unk020a8228 *s, int height);
Unk0208f8b0 *func_020a87e8(Unk020a8228 *s, int index);
void func_020a87f4(Unk020a8228 *s, Unk020a9d58 *l);
void func_020a8ec8(Unk020a8228 *s, Unk020a9d58 *l);
}

static inline bool func_shown(u32 flags) {
    if (flags & 2) {
        return true;
    }
    return false;
}

static inline int func_tileW(Unk0208f8b0 *o) {
    return 1 << (o->unk10_0 + 3);
}

static inline int func_tileH(Unk0208f8b0 *o) {
    return 1 << (o->unk10_2 + 3);
}

static inline float func_fixed(int value) {
    return value > 0 ? (float)(value << 12) + 0.5f : (float)(value << 12) - 0.5f;
}

Unk020a8228::Unk020a8228()
    : width(0), height(0), offsetX(0), offsetY(0), rows(1), cols(1), order(0), priority(0), total(0), objects(0) {}

Unk020a8228::~Unk020a8228() {}

extern "C" void func_020a82a8(Unk020a8228 *s, int on) {
    if (on != (int)((s->flags & 0x200) != 0)) {
        *(volatile u32 *)&s->flags = *(volatile u32 *)&s->flags ^ 0x200;
    }
}

extern "C" bool func_020a82cc(Unk020a8228 *s) {
    return (s->flags & 0x200) != 0;
}

extern "C" void func_020a82e0(Unk020a8228 *s, int on) {
    if (on == (int)((s->flags & 0x100) != 0)) {
        return;
    }
    *(volatile u32 *)&s->flags = (*(volatile u32 *)&s->flags ^ 0x100) | 0x800;
}

extern "C" bool func_020a830c(Unk020a8228 *s) {
    return (s->flags & 0x100) != 0;
}

extern "C" void func_020a8320(Unk020a8228 *s, int on) {
    if (on == (int)((s->flags & 0x400) != 0)) {
        return;
    }
    *(volatile u32 *)&s->flags = (*(volatile u32 *)&s->flags ^ 0x400) | 0x1000;
}

extern "C" bool func_020a834c(Unk020a8228 *s) {
    return (s->flags & 0x400) != 0;
}

extern "C" void func_020a8360(Unk020a8228 *s, int order) {
    s->order = order;
    s->flags |= 0x2000;
}

extern "C" void func_020a8374(Unk020a8228 *s, int priority) {
    s->priority = priority;
    s->flags |= 0x4000;
}

extern "C" int func_020a8388(Unk020a8228 *s) {
    return s->priority;
}

extern "C" void func_020a8390(Unk020a8228 *s, int rows) {
    s->rows = rows;
    s->flags |= 0x8000;
}

extern "C" void func_020a83a4(Unk020a8228 *s, int cols) {
    s->cols = cols;
    s->flags |= 0x10000;
}

extern "C" void func_020a83b8(Unk020a8228 *s, int width) {
    s->width = width;
    s->flags |= 0x20000;
}

int Unk020a8228::func_10() {
    return width;
}

extern "C" void func_020a83d4(Unk020a8228 *s, int height) {
    s->height = height;
    s->flags |= 0x20000;
}

int Unk020a8228::func_14() {
    return height;
}

void Unk020a8228::func_08(Unk020a9d58 *layout, int on) {
    if (on != func_020a7ad8(this)) {
        flags ^= 1;
        if (on == 1) {
            if (flags & 2) {
                func_020a87f4(this, layout);
            }
        } else {
            func_020a8ec8(this, layout);
        }
    }
}

void Unk020a8228::func_0c(Unk020a9d58 *layout) {
    u32 f = flags;
    if (!(f & 0x3f8fc)) {
        return;
    }
    if (func_shown(f) == false) {
        func_020a8ec8(this, layout);
    } else {
        int moved = (f & 0x10) != 0;
        int changed = (f & 0x38040) != 0;
        if (changed == 1 || moved == 1) {
            func_020a8ec8(this, layout);
            func_020a87f4(this, layout);
        } else {
            Unk020916a4 *oam = func_020aa3f4(layout);
            int i;
            for (i = 0; i < total && objects[i] != 0; i++) {
                if (flags & 0x80) {
                    objects[i]->func_0208faac(i + func_020a69cc(this));
                }
                if (flags & 0x800) {
                    objects[i]->func_0208fbac(func_020a830c(this));
                }
                if (flags & 0x1000) {
                    objects[i]->func_0208fbe0(func_020a834c(this));
                }
                if (flags & 8) {
                    objects[i]->func_0208fb98(func_020a7d44(this));
                }
                if (flags & 0x2000) {
                    oam->func_02091a0c(objects[i], order);
                }
                if (flags & 0x4000) {
                    objects[i]->func_0208fb80(priority);
                }
            }
            if (flags & 0x1824) {
                int px = offsetX + (x + (cellX + 1) * -(func_10() >> 1));
                int py = offsetY + (y + (cellY + 1) * -(func_14() >> 1));
                int row = func_020a834c(this) ? rows - 1 : 0;
                int col = func_020a830c(this) ? cols - 1 : 0;
                int r;
                i = 0;
                for (r = 0; r < rows && i < total; r++) {
                    int c;
                    for (c = 0; c < cols && i < total; c++, i++) {
                        objects[i]->unk0 = px + (int)func_fixed((1 << (objects[i]->unk10_0 + 3)) * col);
                        objects[i]->unk4 = py + (int)func_fixed((1 << (objects[i]->unk10_2 + 3)) * row);
                        if (func_020a830c(this)) {
                            col--;
                        } else {
                            col++;
                        }
                    }
                    col = func_020a830c(this) ? cols - 1 : 0;
                    if (func_020a834c(this)) {
                        row--;
                    } else {
                        row++;
                    }
                }
            }
        }
    }
    flags &= 0xfffc0703;
}

extern "C" Unk0208f8b0 *func_020a87e8(Unk020a8228 *s, int index) {
    return s->objects[index];
}

extern "C" void func_020a87f4(Unk020a8228 *s, Unk020a9d58 *l) {
    u32 hash;
    Unk02095140 *file;
    Unk02093648 *archive;
    Unk020916a4 *oam;
    int count;
    hash = func_020a69a4(s);
    if (hash == 0) {
        return;
    }
    archive = func_020aa064(l);
    file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(hash));
    count = file->func_02095180()->count;
    if (func_020a69cc(s) >= count) {
        func_020a69ac(s, count - 1);
    }
    oam = func_020aa3f4(l);
    if (s->rows < 1) {
        s->rows = 1;
    }
    if (s->cols < 1) {
        s->cols = 1;
    }
    s->total = s->rows * s->cols;
    s->objects = new Unk0208f8b0 *[s->total];
    int r;
    int c;
    int i;
    i = 0;
    for (r = 0; r < s->rows && i < s->total; r++) {
        for (c = 0; c < s->cols && i < s->total; c++, i++) {
            s->objects[i] = oam->func_020919e4((int)file, s->order);
        }
    }
    if (func_020a82cc(s) == 1) {
        Unk020a8228 *o = (Unk020a8228 *)((Unk020aa040Func)func_020aa040)(l, 11, 0);
        int n = func_020aa034(l, 11);
        for (; n > 0; n--, o++) {
            if (o != s && hash == func_020a69a4(o)) {
                int value = func_020a69cc(o);
                if (value == func_020a69cc(s)) {
                    value = func_020a8388(o);
                    if (value == func_020a8388(s) && func_020a87e8(o, 0) != 0) {
                        int r2;
                        int c2;
                        int i2 = 0;
                        for (r2 = 0; r2 < s->rows && i2 < s->total; r2++) {
                            for (c2 = 0; c2 < s->cols && i2 < s->total; c2++, i2++) {
                                oam->func_02091de0(o->objects[i2], s->objects[i2]);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    if (s->func_10() < 0x1000) {
        func_020a83b8(s, (int)func_fixed(s->cols * (1 << (s->objects[0]->unk10_0 + 3))));
    }
    if (s->func_14() < 0x1000) {
        func_020a83d4(s, (int)func_fixed(s->rows * (1 << (s->objects[0]->unk10_2 + 3))));
    }
    s->offsetX = func_020a830c(s) ? s->func_10() - (int)func_fixed(s->cols * (1 << (s->objects[0]->unk10_0 + 3))) : 0;
    s->offsetY = func_020a834c(s) ? s->func_14() - (int)func_fixed(s->rows * (1 << (s->objects[0]->unk10_2 + 3))) : 0;
    int px = s->offsetX + (s->x + (s->cellX + 1) * -(s->func_10() >> 1));
    int py = s->offsetY + (s->y + (s->cellY + 1) * -(s->func_14() >> 1));
    int row = func_020a834c(s) ? s->rows - 1 : 0;
    int col = func_020a830c(s) ? s->cols - 1 : 0;
    int r3;
    int c3;
    int i3 = 0;
    for (r3 = 0; r3 < s->rows && i3 < s->total; r3++) {
        for (c3 = 0; c3 < s->cols && i3 < s->total; c3++, i3++) {
            s->objects[i3]->unk0 = px + (int)func_fixed((1 << (s->objects[i3]->unk10_0 + 3)) * col);
            s->objects[i3]->unk4 = py + (int)func_fixed((1 << (s->objects[i3]->unk10_2 + 3)) * row);
            s->objects[i3]->func_0208faac(i3 + func_020a69cc(s));
            s->objects[i3]->func_0208fb98(func_020a7d44(s));
            s->objects[i3]->func_0208fbac(func_020a830c(s));
            s->objects[i3]->func_0208fbe0(func_020a834c(s));
            s->objects[i3]->func_0208fb80(s->priority);
            if (func_020a830c(s)) {
                col--;
            } else {
                col++;
            }
        }
        col = func_020a830c(s) ? s->cols - 1 : 0;
        if (func_020a834c(s)) {
            row--;
        } else {
            row++;
        }
    }
    s->count = s->objects[0]->func_0208fa84();
    s->flags &= 0xfffc0703;
}

extern "C" void func_020a8ec8(Unk020a8228 *s, Unk020a9d58 *l) {
    if (s->objects == 0) {
        return;
    }
    Unk0208f8b0 *first = s->objects[0];
    int i;
    int loaded = first != 0;
    Unk02095140 *file = loaded ? first->unk1c : 0;
    for (i = 0; i < s->total; i++) {
        Unk0208f8b0 *object = s->objects[i];
        if (object != 0) {
            func_020aa3f4(l)->func_02091c68(object);
        }
        s->objects[i] = 0;
    }
    delete[] s->objects;
    s->objects = 0;
    if (loaded == 1) {
        Unk02093648 *archive = func_020aa064(l);
        archive->func_02093c58(archive->func_02093f5c(file));
    }
}
