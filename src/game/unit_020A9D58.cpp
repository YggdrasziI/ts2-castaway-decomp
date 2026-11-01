/*
 * Unit 0x020A9D58-0x020AA648: the layout of a screen: it holds thirteen arrays of sprites, one per
 * type, each built in one block with the size of its type; it shows, updates and frees them, finds
 * the button under the stylus and tells it what happens. Bounds: hypothesis (the functions that
 * take a layout, with their table of sizes and their string). All names are placeholders. Real file
 * name unknown.
 */
#include "game/unk_layoutsprite.h"

inline void *operator new(unsigned long, void *p) {
    return p;
}

class Unk020a7d74 {
public:
    Unk020a7d74();
};

class Unk020a9914 {
public:
    Unk020a9914();
};

class Unk020a7fdc {
public:
    Unk020a7fdc();
};

class Unk020a9054 {
public:
    Unk020a9054();
};

class Unk020a7b94 {
public:
    Unk020a7b94();
};

class Unk020a8228 {
public:
    Unk020a8228();
};

class Unk020a70dc {
public:
    Unk020a70dc();
};

class Unk020a79cc {
public:
    Unk020a79cc();
};

/* What a button is told (state: 0 pressed, 1 left, 2 released; hypothesis). */
struct Unk020aa1c0Event {
    Unk020a6dd8 *button;
    Unk02098e70 *point;
    int state;
};

typedef void (*Unk020aa1c0Func)(Unk020aa1c0Event *event, void *user);
typedef void (*Unk020a80bcLoad)(void *data, u32 offset, u32 size);

extern "C" {
extern const int data_020b6d0c[13];
void func_020a80bc(void *s, Unk020a80bcLoad load);
void GXS_LoadOBJPltt(void *data, u32 offset, u32 size);
void GX_LoadOBJPltt(void *data, u32 offset, u32 size);
void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
void GX_LoadBGPltt(void *data, u32 offset, u32 size);
int func_020a6e58(Unk020a6dd8 *s);
int func_020a6e74(Unk020a6dd8 *s);
void func_020aa42c(Unk020a9d58 *l);
Unk020a6dd8 *func_020aa4c4(Unk020a9d58 *l, Unk02098e70 *p);
}

const int data_020b6d0c[13] = {0x18, 0x44, 0x38, 0x3c, 0x44, 0x2c, 0x2c, 0x1c, 0x18, 0x24, 0x10, 0x54, 0x14};

Unk020a9d58::Unk020a9d58(Unk02093648 *archive, int screen)
    : archive(archive), text(0), user(0), flags(0), button(0) {
    if (screen == 1) {
        flags |= 2;
    }
    for (int i = 0; i < 13; i++) {
        items[i] = 0;
        counts[i] = 0;
    }
}

Unk020a9d58::~Unk020a9d58() {
    func_020aa42c(this);
}

extern "C" void func_020a9db8(Unk020a9d58 *l, Unk020a9d58Text text, void *user) {
    l->text = text;
    l->user = user;
}

extern "C" void func_020a9dc4(Unk020a9d58 *l, int type, int count) {
    int i;
    if (l->counts[type] > 0) {
        for (i = 0; i < l->counts[type]; i++) {
            if (func_020a7ad8(l->items[type][i]) == 1) {
                l->items[type][i]->func_08(l, 0);
            }
            l->items[type][i]->~Unk020a7aa0();
        }
        delete[] l->items[type];
    }
    Unk020a7aa0 **block = 0;
    if (count > 0) {
        int size = data_020b6d0c[type];
        block = (Unk020a7aa0 **)operator new[](size * count + (count << 2));
        for (i = 0; i < count; i++) {
            block[i] = (Unk020a7aa0 *)((u8 *)(block + count) + i * size);
            switch (type) {
            case 1:
                new (block[i]) Unk020a90f8;
                break;
            case 2:
                new (block[i]) Unk020a6a00;
                break;
            case 3:
                new (block[i]) Unk020a9914;
                break;
            case 0:
                new (block[i]) Unk020a7d74;
                break;
            case 7:
                new (block[i]) Unk020a6dd8;
                break;
            case 5:
                new (block[i]) Unk020a7fdc;
                func_020a80bc(block[i], (l->flags & 2) ? GX_LoadOBJPltt : GXS_LoadOBJPltt);
                break;
            case 6:
                new (block[i]) Unk020a7fdc;
                func_020a80bc(block[i], (l->flags & 2) ? GX_LoadBGPltt : GXS_LoadBGPltt);
                break;
            case 8:
                new (block[i]) Unk020a8f84;
                break;
            case 9:
                new (block[i]) Unk020a9054;
                break;
            case 10:
                new (block[i]) Unk020a7b94;
                break;
            case 11:
                new (block[i]) Unk020a8228;
                break;
            case 4:
                new (block[i]) Unk020a70dc;
                break;
            case 12:
                new (block[i]) Unk020a79cc;
                break;
            }
        }
    }
    l->items[type] = block;
    l->counts[type] = count;
}

extern "C" int func_020aa034(Unk020a9d58 *l, int type) {
    return l->counts[type];
}

extern "C" Unk020a7c90 *func_020aa040(Unk020a9d58 *l, int type, u16 index) {
    return (Unk020a7c90 *)l->items[type][index];
}

extern "C" Unk020a7c90 *func_020aa04c(Unk020a9d58 *l, int id) {
    return func_020aa040(l, id >> 16, id);
}

extern "C" Unk02093648 *func_020aa064(Unk020a9d58 *l) {
    return l->archive;
}

extern "C" void func_020aa06c(Unk020a9d58 *l, bool shown) {
    if (shown == ((l->flags & 1) != 0)) {
        return;
    }
    l->flags ^= 1;
    if (shown == 1) {
        for (int type = 0; type < 13; type++) {
            for (int i = 0; i < l->counts[type]; i++) {
                l->items[type][i]->func_08(l, shown);
            }
        }
    } else {
        for (int type = 12; type >= 0; type--) {
            for (int i = 0; i < l->counts[type]; i++) {
                l->items[type][l->counts[type] - i - 1]->func_08(l, shown);
            }
        }
    }
}

extern "C" void func_020aa158(Unk020a9d58 *l) {
    if (!(l->flags & 1)) {
        return;
    }
    for (int type = 0; type < 13; type++) {
        for (int i = 0; i < l->counts[type]; i++) {
            l->items[type][i]->func_0c(l);
        }
    }
}

static inline void func_notify(Unk020a9d58 *l, Unk020a6dd8 *button, Unk02098e70 *p, int state) {
    Unk020aa1c0Event event;
    event.button = button;
    event.point = p;
    event.state = state;
    if (l->button->unk10 != 0) {
        ((Unk020aa1c0Func)l->button->unk10)(&event, (void *)l->button->unkc);
    }
}

extern "C" void func_020aa1c0(Unk020a9d58 *l, Unk02098e70 *p, int touched) {
    if (touched ^ ((l->flags & 4) != 0)) {
        l->flags ^= 4;
        if (l->counts[7] <= 0) {
            return;
        }
        if (touched == 1) {
            Unk020a6dd8 *b = func_020aa4c4(l, p);
            l->button = b;
            if (b == 0) {
                return;
            }
            func_notify(l, b, p, 0);
        } else {
            Unk020a6dd8 *b = l->button;
            if (b == 0) {
                return;
            }
            if (func_020aa4c4(l, p) == b) {
                func_notify(l, b, p, 2);
            } else {
                func_notify(l, b, p, 1);
            }
            l->button = 0;
        }
    } else {
        if (touched != 1) {
            return;
        }
        if (l->counts[7] <= 0) {
            return;
        }
        if (l->button != 0 && func_020a6f28(l->button) == 1) {
            return;
        }
        Unk020a6dd8 *b = func_020aa4c4(l, p);
        if (l->button != 0) {
            if (l->button != b) {
                func_notify(l, l->button, p, 1);
            }
            l->button = 0;
        }
        if (b == 0) {
            return;
        }
        l->button = b;
        func_notify(l, b, p, 0);
    }
}

extern "C" void *func_020aa3c8(Unk020a9d58 *l, u32 id) {
    if (l->text == 0) {
        return (void *)"No Provider";
    }
    return l->text(id, l->user);
}

extern "C" Unk020916a4 *func_020aa3f4(Unk020a9d58 *l) {
    return Unk020916a4::func_02091840((l->flags & 2) != 0);
}

extern "C" Unk0208db14 *func_020aa410(Unk020a9d58 *l) {
    return Unk0208db14::func_0208dc08((l->flags & 2) != 0);
}

extern "C" void func_020aa42c(Unk020a9d58 *l) {
    if (l->flags & 1) {
        func_020aa06c(l, 0);
    }
    for (int type = 12; type >= 0; type--) {
        Unk020a7aa0 **items = l->items[type];
        if (items != 0) {
            for (int i = 0; i < l->counts[type]; i++) {
                items[l->counts[type] - i - 1]->~Unk020a7aa0();
            }
            delete[] items;
            l->items[type] = 0;
            l->counts[type] = 0;
        }
    }
    l->button = 0;
}

extern "C" Unk020a6dd8 *func_020aa4c4(Unk020a9d58 *l, Unk02098e70 *p) {
    int count = l->counts[7];
    if (count == 0) {
        return 0;
    }
    Unk020a6dd8 *b = (Unk020a6dd8 *)func_020aa040(l, 7, 0);
    for (int i = 0; i < count; i++, b++) {
        if (func_020a6ea8(b) && func_020a6ee8(b)) {
            int first = func_020a6e58(b);
            if (first != -1) {
                int n = func_020a6e74(b);
                if (n != 0) {
                    Unk020a90f8 *s = (Unk020a90f8 *)((Unk020aa040Func)func_020aa040)(l, 1, first);
                    for (int j = 0; j < n; j++, s++) {
                        Unk02098e70 lo(s->x, s->y);
                        int w = s->func_10();
                        int h = s->func_14();
                        Unk02098e70 hi(lo.x + w, lo.y + h);
                        if (p->x >= lo.x && p->x < hi.x && p->y >= lo.y && p->y < hi.y) {
                            return b;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
