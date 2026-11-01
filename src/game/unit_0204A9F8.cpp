/*
 * Unit 0x0204A9F8-0x0204BEEC: a paged screen (Unk0204a9f8, 0x484 bytes, vtable
 * 0x020B9AEC) built by the game states of unit_02073878.cpp with a page range
 * (0 to 6 or 7 to 14). It loads two layouts from the screens archive (top and
 * bottom screen), scrolls up to five of ten sprites across the top screen,
 * shows one image per page with its sound and its palette (twelve palette
 * buffers filled by the layout's callbacks), and holds a panel with two
 * buttons (0x1A8, 0x22C) and a panel with the previous / next buttons (0x378,
 * 0x3FC). It has its own show / hide timer at 0x04 and a slide timer at 0x368.
 *
 * Bounds: hypothesis. The start is the constructor, after the slots of the
 * class with vtable 0x020B9AA4 (0x0204A9F4); the class's inline virtual
 * functions end the file before the key's constructor (unit_0204BEEC.cpp).
 * `.rodata` holds the two name tables copied by the constructor and the image
 * and sound tables of the pages, `.data` this class's vtable with its header,
 * `.bss` the twelve palette buffers (0x020BE42C, before the keyboard screen's
 * counter). Real file name unknown.
 *
 * The engine functions 0x020A07D4, 0x020A7AF4 / 0x020A7B04 and 0x020A9D58 /
 * 0x020A9DA4 are named as the base, name list and layout constructors and
 * destructors from where this code calls them (members built in order and
 * destroyed in reverse, the base destructor last, local objects destroyed at
 * the end of the constructor).
 */

#include "game/unk_screen.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

/* The settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    void *unk0;
    u8 unk4[0x154];
    void *texts;
};

typedef void (*Unk020a80bcLoad)(const u16 *src, u32 unk, u32 size);

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern u8 data_020c4510[];
extern u8 data_020d62a4[];

extern "C" {
void func_020a80bc(Unk020a7c90 *s, Unk020a80bcLoad load);
void *func_020a80c4(Unk020a7c90 *s);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a6a64(Unk020a7c90 *s, int mode);
Unk020d6240 *func_020a18e4();
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a4c4c(void *settings);
void *func_020a00a0(void *texts, u32 id);
int func_020a20bc(void *random, int min, int max);
void *func_020a2994();
void *func_020a3858(void *sound, u32 hash, int a, int b, int c);
void func_020a25fc(void *handle);
void DC_FlushRange(const void *start, u32 size);
void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
}

class Unk0204a9f8 : public Unk020a07d4 {
public:
    Unk0204a9f8(Unk02093648 *archive, int first, int last);
    virtual ~Unk0204a9f8();
    virtual void func_08();
    virtual bool func_0c(short);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c() {
        flags &= ~2;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28();
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual bool func_30();
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_0204b418();
    void func_0204b478();
    void func_0204b79c();
    void func_0204b7d0();
    void func_0204b95c();
    void func_0204b970();
    void func_0204b984();
    void func_0204bd6c();

    Unk020a07d4Timer fade;
    u32 flags;
    Unk020a9d58 top;
    Unk020a9d58 bottom;
    Unk020a7c90 *image;
    Unk020a7c90 *sprites[10];
    Unk020a7c90 *shown[5];
    Unk020a7c90 *palettes[12];
    void *paletteData[12];
    Unk02050640 button1a8;
    Unk02050640 button22c;
    Unk02051704 panel2b0;
    Unk02051704 panel30c;
    Unk020a07d4Timer slide;
    int page;
    int lastPage;
    Unk02050640 previous;
    Unk02050640 next;
    void *sound;
};

extern const u32 data_020ae9fc[15];
extern const u32 data_020aea38[15];

static u16 data_020be42c[12][0x100];

static void func_0204baa4(const u16 *src, u32 unk, u32 size);
static void func_0204bad8(const u16 *src, u32 unk, u32 size);
static void func_0204bb14(const u16 *src, u32 unk, u32 size);
static void func_0204bb50(const u16 *src, u32 unk, u32 size);
static void func_0204bb8c(const u16 *src, u32 unk, u32 size);
static void func_0204bbc8(const u16 *src, u32 unk, u32 size);
static void func_0204bc04(const u16 *src, u32 unk, u32 size);
static void func_0204bc40(const u16 *src, u32 unk, u32 size);
static void func_0204bc7c(const u16 *src, u32 unk, u32 size);
static void func_0204bcb8(const u16 *src, u32 unk, u32 size);
static void func_0204bcf4(const u16 *src, u32 unk, u32 size);
static void func_0204bd30(const u16 *src, u32 unk, u32 size);
static void *func_0204be78(u32 id, void *user);

/*
 * 99.45 %: register choices only. Several lookups truncate their index in r1
 * where this code uses r0 (and once the reverse), and one `sub r3` is scheduled
 * before `mov r1`; a lookup helper and a u16 result were tried.
 */
Unk0204a9f8::Unk0204a9f8(Unk02093648 *archive, int first, int last)
    : flags(0), top(archive, 0), bottom(archive, 1), page(first), lastPage(last), sound(0) {
    const u32 spriteNames[10] = {0x0c7425c2, 0x0c7425c3, 0x0c7425c4, 0x0c7425c5, 0x0c7425c6,
                                 0x0c7425c7, 0x0c7425c8, 0x0c7425c9, 0x0c7425ca, 0x0c7425cb};
    const u32 paletteNames[12] = {0x009a3572, 0xdde86ddf, 0xdde86de0, 0xdde86de1, 0xdde86de2, 0xdde86de3,
                                  0x9a5e10f2, 0x9a5e10f3, 0x9a5e10f4, 0x9a5e10f5, 0x9a5e10f6, 0x9a5e10f7};
    Unk020a7af4Entry topEntries[30];
    Unk020a7af4Entry bottomEntries[40];
    Unk020a7af4 topNames(topEntries, 30);
    Unk020a7af4 bottomNames(bottomEntries, 40);
    u32 i;

    func_020aba38(archive, 0xe6665353, &top, &topNames);
    func_020aba38(archive, 0xa3afd44b, &bottom, &bottomNames);
    func_020a9db8(&top, func_020a154c, 0);
    func_020a9db8(&bottom, func_0204be78, this);
    image = func_sprite(&bottom, 2, func_020a7b50(&bottomNames, 0x3abbc872));
    for (i = 0; i < 10; i++) {
        sprites[i] = func_sprite(&top, 0xb, func_020a7b50(&topNames, spriteNames[i]));
    }
    for (i = 0; i < 5; i++) {
        shown[i] = 0;
    }
    for (i = 0; i < 12; i++) {
        palettes[i] = func_sprite(&bottom, 6, func_020a7b50(&bottomNames, paletteNames[i]));
        paletteData[i] = func_020a80c4(palettes[i]);
    }
    func_020a80bc(palettes[0], func_0204baa4);
    func_020a80bc(palettes[1], func_0204bad8);
    func_020a80bc(palettes[2], func_0204bb14);
    func_020a80bc(palettes[3], func_0204bb50);
    func_020a80bc(palettes[4], func_0204bb8c);
    func_020a80bc(palettes[5], func_0204bbc8);
    func_020a80bc(palettes[6], func_0204bc04);
    func_020a80bc(palettes[7], func_0204bc40);
    func_020a80bc(palettes[8], func_0204bc7c);
    func_020a80bc(palettes[9], func_0204bcb8);
    func_020a80bc(palettes[10], func_0204bcf4);
    func_020a80bc(palettes[11], func_0204bd30);

    button1a8.func_02050838(func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0x3adec7b0)), true);
    button1a8.func_02050c48(0, 4, 4);
    button1a8.func_020508a4(func_sprite(&bottom, 1, func_020a7b50(&bottomNames, 0x1efebfc0)));
    button1a8.func_02050914(1);
    button1a8.func_02050968(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0xe444dd9b)));

    button22c.func_02050838(func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0x1ae5bc53)), true);
    button22c.func_02050c48(0, 4, 4);
    button22c.func_020508a4(func_sprite(&bottom, 1, func_020a7b50(&bottomNames, 0x9ebd8282)));
    button22c.func_02050914(1);
    button22c.func_02050968(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0xc7748c58)));

    Unk020a7c90 *frame = func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0x224ac889));
    panel2b0.func_14(func_020a7ca4(frame), func_020a7cc0(frame));
    panel2b0.func_24(0xc0000, func_020a7cc0(frame));
    panel2b0.func_02051804(3);
    panel2b0.func_020518a8(2);
    panel2b0.func_02051858(frame);
    panel2b0.func_02051858(func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0x39877310)));
    panel2b0.func_02051858(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0xd4050781)));
    panel2b0.func_020518fc(&button1a8);
    panel2b0.func_020518fc(&button22c);
    panel2b0.func_34(0xf);

    previous.func_02050838(func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0xcba0dc91)), false);
    previous.func_02050c48(2, 3, -1);
    previous.func_02050c64(3, 4, 5);
    previous.func_020508a4(func_sprite(&bottom, 1, func_020a7b50(&bottomNames, 0x8f6a6fb5)));
    previous.func_18(false);

    next.func_02050838(func_sprite(&bottom, 0xb, func_020a7b50(&bottomNames, 0xb24b9ba5)), false);
    next.func_02050c48(0, 1, -1);
    next.func_18(true);

    panel30c.func_14(0, 0);
    panel30c.func_02051804(4);
    panel30c.func_020518a8(2);
    panel30c.func_02051858(image);
    panel30c.func_02051858(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0x3b5d157f)));
    panel30c.func_02051858(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0x006c6d63)));
    panel30c.func_02051858(func_sprite(&bottom, 4, func_020a7b50(&bottomNames, 0x15b39762)));
    panel30c.func_020518fc(&previous);
    panel30c.func_020518fc(&next);

    slide.func_duration(0xf);
    slide.timer = 0;
    slide.state = 5;
}

Unk0204a9f8::~Unk0204a9f8() {
    func_0204b478();
}

void Unk0204a9f8::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

bool Unk0204a9f8::func_30() {
    bool ready = false;
    bool idle = false;
    if (func_28() && !func_14()) {
        if (!slide.func_moving()) {
            idle = true;
        }
    }
    if (idle) {
        if (!panel2b0.func_50()) {
            ready = true;
        }
    }
    return ready;
}

bool Unk0204a9f8::func_14() {
    return (flags & 2) != 0;
}

bool Unk0204a9f8::func_28() {
    return fade.func_shown();
}

bool Unk0204a9f8::func_0c(short) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0204b418();
    fade.func_duration(0x14);
    fade.state = 0;
    return false;
}

bool Unk0204a9f8::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x14);
    fade.state = 3;
    return false;
}

void Unk0204a9f8::func_0204b418() {
    func_0204b478();
    func_020aa06c(&top, true);
    func_020aa06c(&bottom, true);
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a122c(func_020a18e4());
    flags |= 1;
    slide.timer = slide.duration;
    slide.state = 2;
}

void Unk0204a9f8::func_0204b478() {
    if (!(flags & 1)) {
        return;
    }
    func_020aa06c(&top, false);
    func_020aa06c(&bottom, false);
    flags &= ~1;
}

void Unk0204a9f8::func_38(bool active) {
    if (fade.func_hidden()) {
        return;
    }
    if (!active) {
        return;
    }
    panel2b0.func_08();
    fade.func_step();
    slide.func_step();
    panel30c.func_08();
    if (flags & 1) {
        func_0204b984();
        func_020aa158(&top);
        func_020aa158(&bottom);
        int t = func_fxdiv(slide.timer << 12, slide.duration << 12);
        panel30c.func_14(-0x100 - ((0x1000 - t) << 8), 0);
    }
    if (fade.state == 4) {
        func_0204b478();
    }
}

void Unk0204a9f8::func_18() {
    flags |= 2;
}

bool Unk0204a9f8::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button1a8.func_0c(done);
    if (button1a8.touch.flags & 8) {
        flags |= 4;
        func_18();
    }
    done = button22c.func_0c(done);
    if (button22c.touch.flags & 8) {
        flags |= 0xc;
        func_020a4c4c(data_020d60c8.unk0);
        func_18();
    }
    return previous.func_0c(next.func_0c(done));
}

void Unk0204a9f8::func_0204b79c() {
    panel2b0.func_18(true);
    panel2b0.func_30(0xf);
}

void Unk0204a9f8::func_0204b7d0() {
    if (page < lastPage) {
        page++;
        func_020a6980(image, data_020aea38[page]);
        func_0204bd6c();
        slide.state = 0;
        if (sound != 0) {
            func_020a25fc(sound);
        }
        u32 hash = data_020ae9fc[page];
        if (hash != 0) {
            sound = func_020a3858(func_020a2994(), hash, 0, 1, 0);
        }
    }
    if (page == 0 || page == 7) {
        next.func_18(true);
        previous.func_18(false);
    } else {
        next.func_18(false);
        previous.func_18(true);
    }
    if (page == 14) {
        previous.func_18(false);
    }
    if (page == 1) {
        func_020a7cf0(panel30c.func_02051ad0(1), true);
        func_020a7cf0(panel30c.func_02051ad0(2), true);
        func_020a7cf0(panel30c.func_02051ad0(3), true);
    } else {
        func_020a7cf0(panel30c.func_02051ad0(1), false);
        func_020a7cf0(panel30c.func_02051ad0(2), false);
        func_020a7cf0(panel30c.func_02051ad0(3), false);
    }
}

void Unk0204a9f8::func_0204b95c() {
    func_020a6a64(image, 3);
}

void Unk0204a9f8::func_0204b970() {
    func_020a6a64(image, 1);
}

void Unk0204a9f8::func_0204b984() {
    Unk020a7c90 *s;
    u32 i;
    for (i = 0; i < 5; i++) {
        s = shown[i];
        if (s == 0) {
            bool found;
            do {
                found = false;
                s = sprites[func_020a20bc(data_020d62a4, 0, 10)];
                for (u32 j = 0; j < 5; j++) {
                    if (s == shown[j]) {
                        found = true;
                    }
                }
            } while (found);
            func_020a7c90(s, FX32(0x100 + i * 0x32));
            func_020a7cf0(s, true);
            shown[i] = s;
        }
        func_020a7c90(s, func_020a7ca4(s) - 0x800);
        if (func_020a7ca4(s) < -0x80000) {
            func_020a7cf0(s, false);
            shown[i] = 0;
        }
    }
}

#define PALETTE_LOAD(name, index)                          \
    static void name(const u16 *src, u32 unk, u32 size) {  \
        for (u32 i = 0; i < size / 2; i++) {               \
            data_020be42c[index][i] = src[i];              \
        }                                                  \
    }

PALETTE_LOAD(func_0204baa4, 0)
PALETTE_LOAD(func_0204bad8, 1)
PALETTE_LOAD(func_0204bb14, 2)
PALETTE_LOAD(func_0204bb50, 3)
PALETTE_LOAD(func_0204bb8c, 4)
PALETTE_LOAD(func_0204bbc8, 5)
PALETTE_LOAD(func_0204bc04, 6)
PALETTE_LOAD(func_0204bc40, 7)
PALETTE_LOAD(func_0204bc7c, 8)
PALETTE_LOAD(func_0204bcb8, 9)
PALETTE_LOAD(func_0204bcf4, 10)
PALETTE_LOAD(func_0204bd30, 11)

void Unk0204a9f8::func_0204bd6c() {
    u16 *palette;
    switch (page) {
    case 0:
    case 7:
    case 14:
        palette = data_020be42c[0];
        break;
    case 2:
        palette = data_020be42c[1];
        break;
    case 3:
        palette = data_020be42c[2];
        break;
    case 4:
        palette = data_020be42c[3];
        break;
    case 5:
        palette = data_020be42c[4];
        break;
    case 6:
        palette = data_020be42c[5];
        break;
    case 8:
        palette = data_020be42c[6];
        break;
    case 9:
        palette = data_020be42c[7];
        break;
    case 10:
        palette = data_020be42c[8];
        break;
    case 11:
        palette = data_020be42c[9];
        break;
    case 12:
        palette = data_020be42c[10];
        break;
    case 13:
        palette = data_020be42c[11];
        break;
    default:
        palette = 0;
        break;
    }
    if (palette == 0) {
        return;
    }
    DC_FlushRange(palette, 0x1a0);
    GX_LoadBGPltt(palette, 0x60, 0x1a0);
}

static void *func_0204be78(u32 id, void *user) {
    switch (id) {
    case 0x800001:
        return data_020c4510;
    default:
        return func_020a00a0(data_020d60c8.texts, id);
    }
}

const u32 data_020ae9fc[15] = {
    0, 0x4498ea6a, 0x4498ea6b, 0x4498ea6c, 0x4498ea6d, 0x4498ea6e, 0x4498ea6f, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u32 data_020aea38[15] = {
    0xc2cdd00c, 0x6cb8f8d7, 0x6e99ce73, 0x633a9fe2, 0x95cbea01, 0xc756b1b6, 0x8603346a, 0xc2cdd00c,
    0x4dc562d1, 0x7db0efa6, 0xb652b50b, 0x7a5efa8a, 0x652f40c9, 0x96ebd57d, 0xc2cdd00c,
};
