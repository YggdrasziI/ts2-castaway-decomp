/*
 * Unit 0x02050640-0x02051704: a button widget (Unk02050640, vtable 0x020B9F9C)
 * on the widget base Unk020b9e88 (game/unk_widget.h). A main sprite, an icon
 * sprite and an array of extra sprites; a hit rectangle taken from the main
 * sprite; a press sound (hash, default 0x626F047C) played on release; an
 * optional toggle mode (flag 0x40, 0x80 locks it on). Its look is a set of
 * frame indexes and palettes for the idle, pressed, disabled and toggled states
 * (-1 for none), copied to the sprite either as palettes or, with flag 0x100,
 * as image rows of an archive file.
 *
 * Bounds: hypothesis. The previous widget (vtable 0x020B9EE4) ends with its slot
 * 4 0x02050638; 0x02051704 starts unit_02051704.cpp. `.data` is the vtable of
 * this class, then the unused copy of the base vtable. Real file name unknown.
 *
 * The rectangle accessor func_10 is inline: the vtable points to its kept copy
 * 0x02029B54 (`add r0, r0, #0x54`) in a far file. The base's slots 7 to 20 are
 * not named yet (see game/unk_widget.h): the vtables do not match and the file
 * cannot be complete.
 */

#include "game/unk_archive.h"
#include "game/unk_oam.h"
#include "game/unk_widget.h"

typedef signed char s8;

/* The touch input. */
class Unk020a0774;

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
    int unk8[3];
    Unk02093648 *archive;
};

extern Unk020d6240 data_020d6240;

extern "C" {
Unk020d6240 *func_020a18e4();
bool func_020a075c(Unk020a0774 *input, int index);
bool func_020a078c(Unk020a0774 *input, int index);
Unk02098e70 func_020a07bc(Unk020a0774 *input, int index);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
void func_020a6980(Unk020a7c90 *s, u32 hash);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
int func_020a7d1c(Unk020a7c90 *s);
void func_020a7d30(Unk020a7c90 *s, int frame);
void func_020a8360(Unk020a7c90 *s);
}

static inline Unk02093648 *func_archive() {
    return func_020a18e4()->archive;
}

class Unk02050640 : public Unk020b9e88 {
public:
    Unk02050640();
    ~Unk02050640();
    void func_02050838(Unk020a7c90 *sprite, bool flag);
    void func_020508a4(Unk020a7c90 *icon);
    void func_020508ac(u32 hash);
    void func_02050914(u32 count);
    void func_02050968(Unk020a7c90 *sprite);
    void func_02050990();
    void func_18(bool show);
    int func_02050a24();
    Unk020a7c90 *func_02050a40(int index);
    void func_02050a4c();
    void func_02050a64(bool toggle, bool lock);
    void func_02050aac(bool on);
    void func_02050ad0(u32 sound);
    void func_14(int x, int y);
    void func_02050bb4(short a, short b, short c, short d);
    void func_02050bf0(short a, short b, short c, short d, short e, short f);
    void func_02050c48(int a, int b, int c);
    void func_02050c64(int a, int b, int c);
    void func_02050c80(short a, short b);
    void func_02050c94(short a, short b);
    bool func_0c(bool done);
    void func_08();
    void func_02051294();
    void func_020514f0();

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk020b9e88Touch touch;
    Unk020b9e88Touch touch2;
    Unk0209487c *file;
    Unk020a7c90 *sprite;
    Unk020a7c90 *icon;
    u32 spriteCap;
    u32 spriteCount;
    Unk020a7c90 **sprites;
    Unk02098bc8 rect;
    s8 unk64;
    s8 unk65;
    s8 unk66;
    s8 unk67;
    s8 unk68;
    s8 unk69;
    s8 unk6a;
    s8 unk6b;
    s8 unk6c;
    s8 unk6d;
    s8 unk6e;
    s8 unk6f;
    s8 unk70;
    s8 unk71;
    s8 unk72;
    s8 unk73;
    s8 unk74;
    s8 unk75;
    s8 unk76;
    s8 unk77;
    s8 unk78;
    u32 sound;
    u16 flags;
};

Unk02050640::Unk02050640()
    : Unk020b9e88(true), file(0), sprite(0), icon(0), spriteCap(0), spriteCount(0), sprites(0), unk64(-1), unk65(-1),
      unk66(-1), unk67(-1), unk68(-1), unk69(-1), unk6a(-1), unk6b(-1), unk6c(-1), unk6d(-1), unk6e(-1), unk6f(-1),
      unk70(-1), unk71(-1), unk72(-1), unk73(-1), unk74(-1), unk75(-1), unk76(-1), unk77(-1), unk78(-1),
      sound(0x626f047c), flags(2) {}

Unk02050640::~Unk02050640() {
    func_02050990();
    if (file != 0) {
        func_archive()->func_02093c3c(file);
    }
}

void Unk02050640::func_02050838(Unk020a7c90 *sprite, bool flag) {
    this->sprite = sprite;
    if (flag) {
        flags |= 1;
    } else {
        flags &= ~1;
    }
    if (this->sprite == 0) {
        return;
    }
    rect.x = func_020a7ca4(this->sprite);
    rect.y = func_020a7cc0(this->sprite);
    rect.w = this->sprite->func_10();
    rect.h = this->sprite->func_14();
}

void Unk02050640::func_020508a4(Unk020a7c90 *icon) {
    this->icon = icon;
}

void Unk02050640::func_020508ac(u32 hash) {
    if (sprite != 0) {
        func_020a6980(sprite, hash);
    }
    if (file == 0) {
        return;
    }
    func_archive()->func_02093c3c(file);
    file = func_archive()->func_02093a9c(func_archive()->func_02093e9c(hash));
}

void Unk02050640::func_02050914(u32 count) {
    if (sprites != 0) {
        return;
    }
    spriteCap = count;
    sprites = new Unk020a7c90 *[count];
    for (u32 i = 0; i < spriteCap; i++) {
        sprites[i] = 0;
    }
}

void Unk02050640::func_02050968(Unk020a7c90 *sprite) {
    if (spriteCount < spriteCap) {
        sprites[spriteCount] = sprite;
        spriteCount++;
    }
}

void Unk02050640::func_02050990() {
    if (sprites != 0) {
        delete[] sprites;
    }
    sprites = 0;
    spriteCount = 0;
}

void Unk02050640::func_18(bool show) {
    if (sprite != 0) {
        func_020a7cf0(sprite, show);
    }
    if (icon != 0) {
        func_020a7cf0(icon, show);
    }
    for (u32 i = 0; i < spriteCount; i++) {
        if (sprites[i] != 0) {
            func_020a7cf0(sprites[i], show);
        }
    }
}

int Unk02050640::func_02050a24() {
    if (sprite == 0) {
        return 0;
    }
    return func_020a7d1c(sprite);
}

Unk020a7c90 *Unk02050640::func_02050a40(int index) {
    return sprites[index];
}

void Unk02050640::func_02050a4c() {
    if (sprite != 0) {
        func_020a8360(sprite);
    }
}

void Unk02050640::func_02050a64(bool toggle, bool lock) {
    if (toggle) {
        flags |= 0x40;
        if (lock) {
            flags |= 0x80;
        } else {
            flags &= ~0x80;
        }
    } else {
        flags &= ~0x40;
        flags &= ~0x80;
    }
}

void Unk02050640::func_02050aac(bool on) {
    if (!(flags & 0x40)) {
        return;
    }
    if (on) {
        flags |= 0x10;
    } else {
        flags &= ~0x10;
    }
}

void Unk02050640::func_02050ad0(u32 sound) {
    this->sound = sound;
}

void Unk02050640::func_14(int x, int y) {
    int dx = x - rect.x;
    int dy = y - rect.y;
    rect.x = x;
    rect.y = y;
    if (sprite != 0) {
        func_020a7c90(sprite, x);
        func_020a7cac(sprite, y);
    }
    if (icon != 0) {
        func_020a7c90(icon, dx + func_020a7ca4(icon));
        func_020a7cac(icon, dy + func_020a7cc0(icon));
    }
    for (u32 i = 0; i < spriteCount; i++) {
        if (sprites[i] != 0) {
            func_020a7c90(sprites[i], dx + func_020a7ca4(sprites[i]));
            func_020a7cac(sprites[i], dy + func_020a7cc0(sprites[i]));
        }
    }
}

void Unk02050640::func_02050bb4(short a, short b, short c, short d) {
    unk64 = a;
    unk65 = b;
    unk66 = c;
    unk67 = d;
    unk68 = -1;
    unk69 = -1;
}

void Unk02050640::func_02050bf0(short a, short b, short c, short d, short e, short f) {
    if (a >= 0) {
        unk64 = a;
    }
    if (b >= 0) {
        unk65 = b;
    }
    if (c >= 0) {
        unk68 = c;
    }
    if (d >= 0) {
        unk66 = d;
    }
    if (e >= 0) {
        unk67 = e;
    }
    if (f >= 0) {
        unk69 = f;
    }
}

void Unk02050640::func_02050c48(int a, int b, int c) {
    unk6f = a;
    unk70 = b;
    unk71 = c;
}

void Unk02050640::func_02050c64(int a, int b, int c) {
    unk74 = a;
    unk75 = b;
    unk76 = c;
}

void Unk02050640::func_02050c80(short a, short b) {
    unk72 = a;
    unk73 = b;
}

void Unk02050640::func_02050c94(short a, short b) {
    unk77 = a;
    unk78 = b;
}

bool Unk02050640::func_0c(bool done) {
    bool hidden = false;
    if (sprite != 0 && !func_020a7d1c(sprite)) {
        hidden = true;
    }
    if (done || (flags & 8) || hidden) {
        touch.flags = 0;
        return done;
    }
    if ((flags & 0x40) && (flags & 0x10) && (flags & 0x80)) {
        touch.flags = 0;
        return done;
    }
    Unk02098e70 p = func_020a07bc(data_020d6240.input, 1);
    if (func_020a075c(data_020d6240.input, 1)) {
        if (rect.func_02098bf4(p.x, p.y)) {
            flags |= 4;
        } else {
            flags &= ~4;
        }
    }
    if ((flags & 2) && !(flags & 4)) {
        touch.flags = 0;
        return done;
    }
    if (func_020a078c(data_020d6240.input, 1)) {
        bool in = rect.func_02098bf4(p.x, p.y);
        if (in) {
            touch.func_touched(in);
        } else {
            touch.flags = 0;
        }
    } else if (rect.func_02098bf4(p.x, p.y)) {
        touch.func_touched(false);
    } else {
        touch.flags = 0;
    }
    touch.func_update();
    touch2.func_touched(rect.func_02098bf4(p.x, p.y));
    touch2.func_update();
    if ((touch.flags & 8) && (flags & 0x40)) {
        if ((flags & 0x10) && !(flags & 0x80)) {
            flags &= ~0x10;
        } else {
            flags |= 0x10;
        }
    }
    return (touch.flags & 1) != 0;
}

void Unk02050640::func_08() {
    if ((touch.flags & 8) && sound != 0) {
        func_020a2ce8(func_020a2994(), sound, 0x7f, 0);
    }
    if (sprite == 0) {
        return;
    }
    func_update();
    func_02051294();
}

void Unk02050640::func_02051294() {
    bool toggled = (flags & 0x10) != 0;
    int base = unk64;
    int frame = unk64;
    int palette = unk6f;
    int palette2 = unk74;
    if (flags & 0x100) {
        frame = unk66;
        if (toggled) {
            if (unk6c >= 0) {
                frame = unk6c;
            }
            if (unk72 >= 0) {
                palette = unk72;
            }
            if (unk77 >= 0) {
                palette2 = unk77;
            }
        }
        if (flags & 8) {
            if (unk69 >= 0) {
                frame = unk69;
            }
            if (unk71 >= 0) {
                palette = unk71;
            }
            if (unk76 >= 0) {
                palette2 = unk76;
            }
        } else if (touch.flags & 1) {
            if (toggled) {
                if (unk6d >= 0) {
                    frame = unk6d;
                }
                if (unk73 >= 0) {
                    palette = unk73;
                }
                if (unk78 >= 0) {
                    palette2 = unk78;
                }
            } else {
                if (unk67 >= 0) {
                    frame = unk67;
                }
                if (unk70 >= 0) {
                    palette = unk70;
                }
                if (unk75 >= 0) {
                    palette2 = unk75;
                }
            }
        }
    } else {
        if (toggled) {
            if (unk6a >= 0) {
                frame = unk6a;
            }
            if (unk72 >= 0) {
                palette = unk72;
            }
            if (unk77 >= 0) {
                palette2 = unk77;
            }
        }
        if (flags & 8) {
            if (unk68 >= 0) {
                frame = unk68;
            }
            if (unk71 >= 0) {
                palette = unk71;
            }
            if (unk76 >= 0) {
                palette2 = unk76;
            }
        } else if (touch.flags & 1) {
            if (toggled) {
                if (unk6b >= 0) {
                    frame = unk6b;
                }
                if (unk73 >= 0) {
                    palette = unk73;
                }
                if (unk78 >= 0) {
                    palette2 = unk78;
                }
            } else {
                if (unk65 >= 0) {
                    frame = unk65;
                }
                if (unk70 >= 0) {
                    palette = unk70;
                }
                if (unk75 >= 0) {
                    palette2 = unk75;
                }
            }
        }
    }
    if (flags & 0x100) {
        if (unk6e != frame && frame >= 0) {
            Unk020916a4::func_02091840((flags & 1) != 0)
                ->func_0209201c((Unk02095140 *)file, 0, frame << 4, base << 4, 0x10);
            unk6e = frame;
        }
        frame = unk64;
    }
    if (palette2 >= 0 && icon != 0) {
        func_020a69ac(icon, palette2);
    }
    if (palette >= 0) {
        func_020a69ac(sprite, palette);
    }
    if (frame >= 0) {
        func_020a7d30(sprite, frame);
    }
}

/*
 * 99.06 %: the original keeps the palette in r5 and the hash, the file and the
 * row indexes in r4; this code swaps them. Declaration order, types, a local
 * for the file and inline helpers tried.
 */
void Unk02050640::func_020514f0() {
    if (unk64 == -1 || sprite == 0) {
        return;
    }
    int palette = unk6f;
    if (palette < 0) {
        palette = func_020a69cc(sprite);
    }
    if (file == 0) {
        u32 hash = func_020a69a4(sprite);
        if (hash != 0) {
            file = func_archive()->func_02093a9c(func_archive()->func_02093e9c(hash));
        }
    }
    Unk0209487c *f = file;
    if (f == 0) {
        return;
    }
    Unk020916a4::func_02091840((flags & 1) != 0)->func_0209201c((Unk02095140 *)f, palette, unk66 << 4, unk64 << 4, 0x10);
    if (unk65 != -1 && unk67 != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)
            ->func_0209201c((Unk02095140 *)file, palette, unk67 << 4, unk65 << 4, 0x10);
    }
    if (unk68 != -1 && unk69 != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)
            ->func_0209201c((Unk02095140 *)file, palette, unk69 << 4, unk68 << 4, 0x10);
    }
    if ((flags & 0x40) && unk6a != -1 && unk6c != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)
            ->func_0209201c((Unk02095140 *)file, palette, unk6c << 4, unk6a << 4, 0x10);
    }
    if ((flags & 0x40) && unk6b != -1 && unk6d != -1) {
        Unk020916a4::func_02091840((flags & 1) != 0)
            ->func_0209201c((Unk02095140 *)file, palette, unk6d << 4, unk6b << 4, 0x10);
    }
}
