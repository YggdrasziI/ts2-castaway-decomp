/*
 * Unit 0x0204BEEC-0x0204D698: a key (Unk0204beec, 0xE4 bytes, vtable 0x020B9B34)
 * on the screen element base Unk020b9b80 (game/unk_element.h): up to six objects
 * showing frames of an archive image, a text canvas, a hit rectangle and two
 * touch states (inside on press, inside). Its palettes and frames depend on its
 * state (idle, pressed, disabled, toggled, toggled pressed), with an alternate
 * palette set copied into the palette slot (flag 0x200); a pressed key can play
 * a rotation and scale animation.
 *
 * Bounds: hypothesis. The start is the constructor, after the functions of the
 * class with vtable 0x020B9AEC (whose slots reach 0x0204BEE8); the file ends with
 * the base's kept functions 0x0204D40C-0x0204D698 before the keyboard screen's
 * constructor. `.data` is this class's vtable, then the kept copy of the base
 * vtable (0x020B9B78). Real file name unknown.
 *
 * The rectangle accessor func_10 is inline: the vtable points to its kept copy
 * 0x0201F640 in a far file. The base's slots 7 to 14 and 16 are not named yet:
 * the vtables do not match, the base vtable copy is not emitted and with it
 * the base update kept here (0x0204D40C); the file cannot be complete.
 */

#include "game/unk_archive.h"
#include "game/unk_canvas.h"
#include "game/unk_element.h"
#include "game/unk_resource.h"
#include "game/unk_vector.h"

typedef signed char s8;

#define va_start(ap, parm) \
    ((ap) = (va_list)((char *)((u32)&(parm) & ~3U) + ((sizeof(parm) + 3U) & ~3U)))
#define va_end(ap) ((void)0)

/* The touch input. */
class Unk020a0774;

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
    int unk8[3];
    Unk02093648 *archive;
    Unk02092830Font *font18;
    Unk02092830Font *font1c;
};

/* The settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    u8 unk0[0x158];
    void *texts;
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;

extern "C" {
Unk020d6240 *func_020a18e4();
int func_0209f0a4(Unk020d60c8 *settings);
const char *func_020a00a0(void *texts, int id);
bool func_020a075c(Unk020a0774 *input, int index);
bool func_020a078c(Unk020a0774 *input, int index);
Unk02098e70 func_020a07bc(Unk020a0774 *input, int index);
int vsnprintf(char *buf, int size, const char *fmt, va_list args);
}

static inline Unk02093648 *func_archive() {
    return func_020a18e4()->archive;
}

/* A 20.12 fixed-point product computed in 64 bits. */
static inline int func_fxmul64(int a, int b) {
    return (int)(((long long)a * b) >> 12);
}

/*
 * The palettes (idle, pressed, alternate idle, alternate pressed, disabled,
 * alternate disabled, toggled, toggled pressed and their alternates), the
 * palette last copied and the frames (idle, pressed, disabled, toggled,
 * toggled pressed); -1 for none.
 */
struct Unk0204beecLook {
    Unk0204beecLook() {
        palettes[0] = -1;
        palettes[1] = -1;
        palettes[2] = -1;
        palettes[3] = -1;
        palettes[4] = -1;
        palettes[5] = -1;
        palettes[6] = -1;
        palettes[7] = -1;
        palettes[8] = -1;
        palettes[9] = -1;
        palette = -1;
        frames[0] = 0;
        frames[1] = -1;
        frames[2] = -1;
        frames[3] = -1;
        frames[4] = -1;
    }

    s8 palettes[10];
    s8 palette;
    s8 frames[5];
};

class Unk0204beec : public Unk020b9b80 {
public:
    Unk0204beec();
    ~Unk0204beec();
    void func_0204c0f8(bool main);
    void func_0204c11c(const u32 *name);
    void func_0204c144(u32 hash);
    void func_0204c16c(int priority);
    void func_0204c1b8(int priority);
    void func_0204c1c4(int w, int h);
    void func_0204c1d0(int count);
    void func_0204c1dc(bool toggle);
    void func_0204c1f4(bool on);
    void func_0204c218(bool lock);
    void func_0204c23c(short a, short b, short c, short d);
    void func_0204c264(int hAlign, int vAlign);
    void func_0204c280(const char *fmt, ...);
    void func_0204c2d4(const char *text, int color, bool alt);
    void func_14(int x, int y);
    void func_0204c440();
    void func_0204c4c4(short a, short b, short c, short d);
    void func_0204c500(short a, short b, short c, short d, short e, short f);
    void func_0204c540(int a, int b, int c);
    void func_0204c55c(int a, int b);
    bool func_04(bool locked);
    void func_00();
    void func_0204cdbc();
    void func_0204cfa8();
    void func_0c(int priority);
    void func_08();
    void func_0204d3c0(int frame);

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk020b9e88Touch touch;
    Unk020b9e88Touch inside;
    Unk0209487c *file;
    Unk0208f8b0 *objects[6];
    int textId;
    Unk02090308 canvas;
    int textX;
    int textY;
    int hAlign;
    int vAlign;
    Unk02092830Font *font;
    Unk02098bc8 rect;
    int resource;
    Unk0204beecLook look;
    u16 flags;
    s8 priority;
    s8 color;
    u8 animation;
    u8 count;
    s8 oamPriority;
    int angle;
};

Unk0204beec::Unk0204beec()
    : file(0), textId(0), textX(0), textY(0), hAlign(0), vAlign(1), font(0), resource(-1), flags(1), priority(0),
      color(0x20), animation(0), count(1), oamPriority(6), angle(0) {
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x20000;
    rect.h = 0x20000;
    canvas.func_020905c4(1);
    canvas.func_020908e0(hAlign, vAlign);
    canvas.func_020905d4(0xf);
    for (int i = 0; i < 6; i++) {
        objects[i] = 0;
    }
}

Unk0204beec::~Unk0204beec() {
    func_08();
}

void Unk0204beec::func_0204c0f8(bool main) {
    if (main) {
        flags |= 1;
    } else {
        flags &= ~1;
    }
    canvas.func_020905c4(main);
}

void Unk0204beec::func_0204c11c(const u32 *name) {
    resource = func_archive()->func_02093db0(name, 9);
}

void Unk0204beec::func_0204c144(u32 hash) {
    resource = func_archive()->func_02093ef4(hash, 9);
}

void Unk0204beec::func_0204c16c(int priority) {
    this->priority = priority;
    if (!(flags & 2)) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (objects[i] != 0) {
            objects[i]->func_0208fb80(priority);
        }
    }
}

void Unk0204beec::func_0204c1b8(int priority) {
    oamPriority = priority;
}

void Unk0204beec::func_0204c1c4(int w, int h) {
    rect.w = w;
    rect.h = h;
}

void Unk0204beec::func_0204c1d0(int count) {
    this->count = count;
}

void Unk0204beec::func_0204c1dc(bool toggle) {
    if (toggle) {
        flags |= 0x80;
    } else {
        flags &= ~0x80;
    }
}

void Unk0204beec::func_0204c1f4(bool on) {
    if (!(flags & 0x80)) {
        return;
    }
    if (on) {
        flags |= 0x20;
    } else {
        flags &= ~0x20;
    }
}

void Unk0204beec::func_0204c218(bool lock) {
    if (!(flags & 0x80)) {
        return;
    }
    if (lock) {
        flags |= 0x100;
    } else {
        flags &= ~0x100;
    }
}

void Unk0204beec::func_0204c23c(short a, short b, short c, short d) {
    look.palettes[6] = a;
    look.palettes[7] = b;
    look.palettes[8] = c;
    look.palettes[9] = d;
}

void Unk0204beec::func_0204c264(int hAlign, int vAlign) {
    this->hAlign = hAlign;
    this->vAlign = vAlign;
    canvas.func_020908e0(this->hAlign, vAlign);
}

void Unk0204beec::func_0204c280(const char *fmt, ...) {
    char buf[0x80];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 0x80, fmt, args);
    textId = 0;
    func_0204c2d4(buf, 0x80, false);
}

void Unk0204beec::func_0204c2d4(const char *text, int color, bool alt) {
    this->color = color;
    if (alt) {
        flags |= 0x40;
    } else {
        flags &= ~0x40;
    }
    canvas.func_0209088c();
    int w = (u32)rect.w >> 12;
    int h = (u32)rect.h >> 12;
    int cols = w / 32;
    if (w % 32 != 0) {
        cols++;
    }
    int rows = h / 32;
    if (h % 32 != 0) {
        rows++;
    }
    canvas.func_020908ac(oamPriority);
    canvas.func_02090898(priority);
    canvas.func_0209066c(cols, rows);
    Unk02098bc8 area(0, 0, (u32)rect.w >> 12, (u32)rect.h >> 12);
    canvas.func_020908bc(&area);
    canvas.func_02090878(rect.x + textX, rect.y + textY);
    canvas.func_020908e0(hAlign, vAlign);
    Unk02092830Font *font = this->font;
    if (font == 0) {
        if (alt) {
            font = func_020a18e4()->font1c;
        } else {
            Unk020d6240 *system = func_020a18e4();
            font = func_0209f0a4(&data_020d60c8) == 7 ? system->font1c : system->font18;
        }
    }
    canvas.func_020909c8(font, text);
}

void Unk0204beec::func_14(int x, int y) {
    rect.x = x;
    rect.y = y;
    func_0204c440();
}

void Unk0204beec::func_0204c440() {
    if (objects[0] != 0) {
        int step = 1 << (objects[0]->unk10_0 + 3);
        int x = rect.x;
        for (int i = 0; i < 6; i++) {
            if (objects[i] == 0) {
                break;
            }
            objects[i]->unk0 = x;
            objects[i]->unk4 = rect.y;
            x += step << 12;
        }
    }
    canvas.func_02090878(rect.x + textX, rect.y + textY);
}

void Unk0204beec::func_0204c4c4(short a, short b, short c, short d) {
    look.palettes[0] = a;
    look.palettes[1] = b;
    look.palettes[2] = c;
    look.palettes[3] = d;
    look.palettes[4] = -1;
    look.palettes[5] = -1;
}

void Unk0204beec::func_0204c500(short a, short b, short c, short d, short e, short f) {
    look.palettes[0] = a;
    look.palettes[1] = b;
    look.palettes[4] = c;
    look.palettes[2] = d;
    look.palettes[3] = e;
    look.palettes[5] = f;
}

void Unk0204beec::func_0204c540(int a, int b, int c) {
    look.frames[0] = a;
    look.frames[1] = b;
    look.frames[2] = c;
}

void Unk0204beec::func_0204c55c(int a, int b) {
    look.frames[3] = a;
    look.frames[4] = b;
}

bool Unk0204beec::func_04(bool locked) {
    if (locked || (flags & 0x10)) {
        touch.flags = 0;
        return locked;
    }
    if ((flags & 0x80) && (flags & 0x20) && (flags & 0x100)) {
        touch.flags = 0;
        return locked;
    }
    Unk02098e70 p = func_020a07bc(data_020d6240.input, 1);
    if (func_020a075c(data_020d6240.input, 1)) {
        if (rect.func_02098bf4(p.x, p.y)) {
            flags |= 8;
        } else {
            flags &= ~8;
        }
    }
    if ((flags & 4) && !(flags & 8)) {
        touch.flags = 0;
        return locked;
    }
    if (func_020a078c(data_020d6240.input, 1)) {
        bool in = rect.func_02098bf4(p.x, p.y);
        if (in) {
            touch.func_touched(in);
        } else {
            touch.flags = 0;
        }
    } else {
        if (rect.func_02098bf4(p.x, p.y)) {
            touch.func_touched(false);
        } else {
            touch.flags = 0;
        }
    }
    touch.func_update();
    inside.func_touched(rect.func_02098bf4(p.x, p.y));
    inside.func_update();
    if ((touch.flags & 8) && (flags & 0x80)) {
        if ((flags & 0x20) && !(flags & 0x100)) {
            flags &= ~0x20;
        } else {
            flags |= 0x20;
        }
    }
    return (touch.flags & 1) != 0;
}

void Unk0204beec::func_00() {
    func_update();
    if (!(flags & 2) || objects[0] == 0) {
        return;
    }
    func_0204cdbc();
    if (touch.flags & 4) {
        switch (animation) {
        case 1:
            Unk020916a4::func_02091840((flags & 1) != 0)->func_020922cc(objects[0], angle, 200, 200, 0);
            objects[0]->unk0 = rect.x - func_fxmul64((u32)rect.w >> 2, 0x380);
            objects[0]->unk4 = rect.y - func_fxmul64((u32)rect.h >> 2, 0x380);
            break;
        case 2:
            Unk020916a4::func_02091840((flags & 1) != 0)->func_020922cc(objects[0], angle, 200, 200, 0);
            objects[0]->unk0 = rect.x - func_fxmul64((u32)rect.w >> 2, 0x380);
            objects[0]->unk4 = rect.y - func_fxmul64((u32)rect.h >> 1, 0x380);
            break;
        case 3:
            Unk020916a4::func_02091840((flags & 1) != 0)->func_020922cc(objects[0], angle, 200, 200, 0);
            objects[0]->unk0 = rect.x - func_fxmul64((u32)rect.w >> 2, 0x380);
            objects[0]->unk4 = rect.y + func_fxmul64((u32)rect.h >> 2, 0x380);
            break;
        }
        return;
    }
    if (touch.flags & 1) {
        return;
    }
    int angle = this->angle;
    if (angle != 0) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_020922cc(objects[0], angle, 0xff, 0xff, 0);
        return;
    }
    if (objects[0]->func_0208fcf0()) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_0209241c(objects[0]);
        func_0204c440();
    }
}

void Unk0204beec::func_0204cdbc() {
    int pal;
    int frame;
    int base = look.palettes[0];
    if (base < 0) {
        return;
    }
    pal = base;
    frame = look.frames[0];
    bool toggled = (flags & 0x20) != 0;
    if (flags & 0x200) {
        pal = look.palettes[2];
        if (toggled) {
            if (look.palettes[8] >= 0) {
                pal = look.palettes[8];
            }
            if (look.frames[3] >= 0) {
                frame = look.frames[3];
            }
        }
        if (flags & 0x10) {
            if (look.palettes[5] >= 0) {
                pal = look.palettes[5];
            }
            if (look.frames[2] >= 0) {
                frame = look.frames[2];
            }
        } else if (touch.flags & 1) {
            if (toggled) {
                if (look.palettes[9] >= 0) {
                    pal = look.palettes[9];
                }
                if (look.frames[4] >= 0) {
                    frame = look.frames[4];
                }
            } else {
                if (look.palettes[3] >= 0) {
                    pal = look.palettes[3];
                }
                if (look.frames[1] >= 0) {
                    frame = look.frames[1];
                }
            }
        }
    } else {
        if (toggled) {
            if (look.palettes[6] >= 0) {
                pal = look.palettes[6];
            }
            if (look.frames[3] >= 0) {
                frame = look.frames[3];
            }
        }
        if (flags & 0x10) {
            if (look.palettes[4] >= 0) {
                pal = look.palettes[4];
            }
            if (look.frames[2] >= 0) {
                frame = look.frames[2];
            }
        } else if (touch.flags & 1) {
            if (toggled) {
                if (look.palettes[7] >= 0) {
                    pal = look.palettes[7];
                }
                if (look.frames[4] >= 0) {
                    frame = look.frames[4];
                }
            } else {
                if (look.palettes[1] >= 0) {
                    pal = look.palettes[1];
                }
                if (look.frames[1] >= 0) {
                    frame = look.frames[1];
                }
            }
        }
    }
    if (flags & 0x200) {
        if (look.palette != pal) {
            Unk020916a4::func_02091840((flags & 1) != 0)
                ->func_0209201c((Unk02095140 *)file, 0, pal << 4, base << 4, 0x10);
            look.palette = pal;
        }
        pal = look.palettes[0];
    }
    for (int i = 0; i < 6; i++) {
        if (objects[i] != 0) {
            objects[i]->func_0208faac(frame + i);
            objects[i]->func_0208fb98(pal);
        }
    }
}

void Unk0204beec::func_0204cfa8() {
    if (look.palettes[0] == -1 || resource == -1) {
        return;
    }
    Unk02095140 *file = (Unk02095140 *)func_archive()->func_02093a9c(resource);
    if (file == 0) {
        return;
    }
    Unk020916a4::func_02091840((flags & 1) != 0)
        ->func_0209201c(file, look.frames[0], look.palettes[2] << 4, look.palettes[0] << 4, 0x10);
    int dst = look.palettes[1];
    int src;
    if (dst != -1 && (src = look.palettes[3]) != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_0209201c(file, look.frames[0], src << 4, dst << 4, 0x10);
    }
    dst = look.palettes[4];
    if (dst != -1 && (src = look.palettes[5]) != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_0209201c(file, look.frames[0], src << 4, dst << 4, 0x10);
    }
    if ((flags & 0x80) && (dst = look.palettes[6]) != -1 && (src = look.palettes[8]) != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_0209201c(file, look.frames[0], src << 4, dst << 4, 0x10);
    }
    if ((flags & 0x80) && (dst = look.palettes[7]) != -1 && (src = look.palettes[9]) != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)->func_0209201c(file, look.frames[0], src << 4, dst << 4, 0x10);
    }
    func_archive()->func_02093c3c(file);
}

/*
 * 99.58 %: the new file and the first loop index swap r4 / r5. Tried: the
 * file and the index declared at function or block scope in both orders, a
 * resource file cast, an OAM manager local, int / u8 counts.
 */
void Unk0204beec::func_0c(int priority) {
    if (flags & 2) {
        return;
    }
    if (priority >= 0) {
        func_0204c16c(priority);
    }
    if (resource != -1) {
        Unk0209487c *file = func_archive()->func_02093a9c(resource);
        if (file == 0) {
            return;
        }
        if (this->file != 0) {
            func_archive()->func_02093c3c(this->file);
        }
        this->file = file;
        for (int i = 0; i < count; i++) {
            objects[i] = Unk020916a4::func_02091840((flags & 1) != 0)->func_020919e4((int)file, oamPriority);
        }
        for (int i = 0; i < 6; i++) {
            if (objects[i] != 0) {
                objects[i]->func_0208fb80(this->priority);
                objects[i]->func_0208faac(look.frames[0] + i);
                if (look.palettes[0] != -1) {
                    objects[i]->func_0208fb98(look.palettes[0]);
                }
            }
        }
    }
    canvas.func_020908ac(oamPriority);
    canvas.func_02090898(this->priority);
    canvas.func_020908bc(&rect);
    canvas.func_0209088c();
    if (textId != 0) {
        func_0204c2d4(func_020a00a0(data_020d60c8.texts, textId), color, (flags & 0x40) != 0);
    } else {
        canvas.func_0209088c();
    }
    func_0204c440();
    flags &= ~0x10;
    flags |= 2;
}

void Unk0204beec::func_08() {
    if (!(flags & 2)) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        Unk0208f8b0 *object = objects[i];
        if (object != 0) {
            Unk020916a4::func_02091840((flags & 1) != 0)->func_02091c68(object);
        }
        objects[i] = 0;
    }
    if (file != 0) {
        func_archive()->func_02093c3c(file);
        file = 0;
    }
    canvas.func_0209088c();
    flags &= ~2;
}

void Unk0204beec::func_0204d3c0(int frame) {
    look.frames[0] = frame;
    if (objects[0] == 0) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (objects[i] != 0) {
            objects[i]->func_0208faac(look.frames[0] + i);
        }
    }
}
