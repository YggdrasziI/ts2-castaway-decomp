/*
 * Unit 0x0208D304-0x0208E570: the background layers of both screens. A layer
 * (Unk0208d304) keeps a copy of its BGxCNT register, its number, screen and
 * display flags, a scroll position, a tile map from a resource file
 * (Unk02095140) and the part of the map already copied to VRAM; func_0208d570
 * writes the registers and copies the newly visible tiles. A manager per screen
 * (Unk0208db14, main screen first in data_020c7f64) owns the four layers, hands
 * out 2 KB blocks of background VRAM for character and screen data, loads
 * background palettes and sets the layer bits of DISPCNT.
 *
 * Bounds: hypothesis. No call crosses 0x0208D304 or 0x0208E570 (the font of
 * unit_0208E570.cpp follows); the two manager pointers of .bss 0x020c7f64 are
 * only used here. Real file name unknown.
 * Not complete: four functions do not match yet (see above them).
 */

#include "game/unk_resource.h"
#include "game/unk_rect.h"
#include "game/unk_vector.h"

typedef short s16;

extern "C" {
void DispCnt_ApplyPendingMode();
int func_02078114();
int func_02078174();
void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
void GX_LoadBGPltt(void *data, u32 offset, u32 size);
void func_02099b84(const void *src, void *dest, u32 size);
}

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)

/* One background layer (0x38 bytes). */
class Unk0208d304 {
public:
    Unk0208d304();
    void func_0208d388(Unk02095140 *file, int index);
    void func_0208d438();
    void func_0208d444();
    void func_0208d4b0(int priority);
    int func_0208d4c8();
    void func_0208d4d8(int charBase);
    int func_0208d4f0();
    void func_0208d500(int screenBase);
    void func_0208d518(int color256);
    void func_0208d530(int size);
    int func_0208d548();
    bool func_0208d558();
    void func_0208d570();
    volatile u16 *func_0208d6fc();
    volatile u32 *func_0208d728();
    void func_0208d758(int bg);
    void func_0208d774(bool main);
    void func_0208d7a0(bool visible);
    bool func_0208d7b8();
    int func_0208d7d0();
    int func_0208d7ec();
    int func_0208d808();
    int func_0208d814();
    void func_0208d820(int w, int h);
    u16 *func_0208d82c();
    u8 *func_0208d850();
    void func_0208d874(bool on);
    bool func_0208d88c();
    void func_0208d8a4(int srcX, int srcY, int dstX, int dstY, int w, int h);
    void func_0208d9bc(int srcX, int srcY, int dstX, int dstY, int n);
    void func_0208da88(u32 *src, u16 *dst, int n);

    int x;
    int y;
    u16 bgcnt;
    u16 bg : 2;
    u16 sub : 1;
    u16 flag3 : 1;
    u16 visible : 1;
    Unk02095140 *file;
    u32 *map;
    u16 mapW;
    u16 mapH;
    u16 viewW;
    u16 viewH;
    u8 unk1c[0xC];
    Unk02098bc8 rect;
};

/* The background manager of one screen (0x11C bytes). */
class Unk0208db14 {
public:
    Unk0208db14(bool main);
    static Unk0208db14 *func_0208dbe8();
    static Unk0208db14 *func_0208dbf8();
    static Unk0208db14 *func_0208dc08(int main);
    int func_0208dc24();
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    Unk0208d304 *func_0208de60();
    int func_0208dee4();
    void func_0208df4c(Unk0208d304 *layer);
    void func_0208e058(Unk02095140 *file, int index, int mask);
    void func_0208e1b0(Unk02095140 *file, int index, u32 src, u32 dst, u32 n);
    void func_0208e224(void *data, u32 dst, u32 n);
    int func_0208e260(int size);
    int func_0208e2cc(int count);
    int func_0208e364(int count, int start, int end, int align);
    void func_0208e46c(int start, int count);
    void func_0208e4ec();

    u32 used : 31;
    u32 main : 1;
    u32 bits[4];
    Unk0208d304 layers[4];
    int charBlock[4];
    s16 charCount[4];
    s16 screenBlock[4];
    s16 screenCount[4];
};

Unk0208db14 *data_020c7f64[2];

Unk0208d304::Unk0208d304()
    : x(0), y(0), bgcnt(0), bg(0), sub(0), flag3(0), visible(0), file(0), map(0), mapW(0),
      mapH(0), viewW(0x21), viewH(0x19), rect(0, 0, 0, 0) {}

void Unk0208d304::func_0208d388(Unk02095140 *file, int index) {
    Unk02095140Header *header;

    this->file = file;
    file->func_02094f9c();
    map = (u32 *)this->file->func_020952b0(index);
    if (map == 0) {
        return;
    }
    header = file->func_02095180();
    if (header->width < 0x20) {
        return;
    }
    mapW = header->width;
    mapH = header->height;
    if (header->bpp == 8) {
        func_0208d518(1);
    } else {
        func_0208d518(0);
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    flag3 = 0;
    visible = 0;
    x = 0;
    y = 0;
}

void Unk0208d304::func_0208d438() {
    func_0208d444();
}

void Unk0208d304::func_0208d444() {
    if (file != 0) {
        file->func_02094fb8();
    }
    file = 0;
    map = 0;
    mapW = 0;
    mapH = 0;
    func_0208d518(0);
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    flag3 = 0;
    visible = 0;
    x = 0;
    y = 0;
}

void Unk0208d304::func_0208d4b0(int priority) {
    bgcnt = (bgcnt & ~3) + (priority & 3);
}

int Unk0208d304::func_0208d4c8() {
    return (bgcnt >> 2) & 0xF;
}

void Unk0208d304::func_0208d4d8(int charBase) {
    bgcnt = (bgcnt & ~0x3C) + ((charBase & 0xF) << 2);
}

int Unk0208d304::func_0208d4f0() {
    return (bgcnt >> 8) & 0x1F;
}

void Unk0208d304::func_0208d500(int screenBase) {
    bgcnt = (bgcnt & ~0x1F00) + ((screenBase & 0x1F) << 8);
}

void Unk0208d304::func_0208d518(int color256) {
    if (color256) {
        bgcnt |= 0x80;
    } else {
        bgcnt &= ~0x80;
    }
}

void Unk0208d304::func_0208d530(int size) {
    bgcnt = (bgcnt & ~0xC000) + ((size & 3) << 14);
}

int Unk0208d304::func_0208d548() {
    return bg;
}

bool Unk0208d304::func_0208d558() {
    return !sub;
}

/*
 * 99.34 %: register allocation only. The original keeps the loop counter in r5 and
 * the wrapped x in r6, ours the reverse (declaration orders and scopes, argument
 * forms and an inline wrap helper tried).
 */
void Unk0208d304::func_0208d570() {
    *func_0208d6fc() = bgcnt;
    *func_0208d728() = ((-x >> 12) & 0x1FF) + (((-y >> 12) & 0x1FF) << 16);
    if (file == 0) {
        return;
    }
    Unk02098bc8 view(-x >> 15, -y >> 15, viewW, viewH);
    Unk02098bc8 parts[4];
    int i;

    for (i = 0; i < view.func_02098c98(rect, parts); i++) {
        int sx = parts[i].x - mapW * (func_fxdiv(parts[i].x, mapW) >> 12);
        int sy = parts[i].y - mapH * (func_fxdiv(parts[i].y, mapH) >> 12);
        func_0208d8a4(sx, sy, parts[i].x, parts[i].y, parts[i].w, parts[i].h);
    }
    rect = view;
}

volatile u16 *Unk0208d304::func_0208d6fc() {
    return (volatile u16 *)(sub ? 0x04001008 : 0x04000008) + bg;
}

volatile u32 *Unk0208d304::func_0208d728() {
    return (volatile u32 *)(sub ? 0x04001010 : 0x04000010) + bg;
}

void Unk0208d304::func_0208d758(int bg) {
    this->bg = bg & 3;
}

void Unk0208d304::func_0208d774(bool main) {
    sub = main ? 0 : 1;
}

void Unk0208d304::func_0208d7a0(bool visible) {
    this->visible = visible;
}

bool Unk0208d304::func_0208d7b8() {
    return visible;
}

int Unk0208d304::func_0208d7d0() {
    u16 size = (bgcnt >> 14) & 3;

    return (size & 1) ? 0x200 : 0x100;
}

int Unk0208d304::func_0208d7ec() {
    u16 size = (bgcnt >> 14) & 3;

    return (size & 2) ? 0x200 : 0x100;
}

int Unk0208d304::func_0208d808() {
    return mapW << 3;
}

int Unk0208d304::func_0208d814() {
    return mapH << 3;
}

void Unk0208d304::func_0208d820(int w, int h) {
    viewW = w;
    viewH = h;
}

u16 *Unk0208d304::func_0208d82c() {
    u32 base = sub ? 0x06200000 : 0x06000000;

    return (u16 *)(base + (func_0208d4f0() << 11));
}

u8 *Unk0208d304::func_0208d850() {
    u32 base = sub ? 0x06200000 : 0x06000000;

    return (u8 *)(base + (func_0208d4c8() << 14));
}

void Unk0208d304::func_0208d874(bool on) {
    flag3 = on;
}

bool Unk0208d304::func_0208d88c() {
    return flag3;
}

/*
 * 99.93 %: the two spilled values swap stack slots (srcX + w at sp+0xc and the
 * first width at sp+8 in the original); declaration orders tried.
 */
void Unk0208d304::func_0208d8a4(int srcX, int srcY, int dstX, int dstY, int w, int h) {
    if (w > func_0208d7d0() >> 3) {
        return;
    }
    if (h > func_0208d7ec() >> 3) {
        return;
    }
    if (srcX >= mapW) {
        srcX -= mapW;
    }
    if (srcY >= mapH) {
        srcY -= mapH;
    }
    while (h-- != 0) {
        int over = srcX + w - mapW;
        if (over > 0) {
            int first = w - over;
            func_0208d9bc(srcX, srcY, dstX, dstY, first);
            func_0208d9bc(0, srcY, dstX + first, dstY, over);
        } else {
            func_0208d9bc(srcX, srcY, dstX, dstY, w);
        }
        srcY++;
        dstY++;
        if (srcY >= mapH) {
            srcY -= mapH;
        }
    }
}

/*
 * 97.22 %: register allocation only. The original keeps dst in r7 and the count
 * (sharing dstY's register) in r5, ours the reverse, and masks dstX before the
 * size (declaration orders, initialisers, statement orders, types and reuse of
 * dstY as the count tried).
 */
void Unk0208d304::func_0208d9bc(int srcX, int srcY, int dstX, int dstY, int n) {
    int size = (bgcnt >> 14) & 3;
    int end = 0x20;
    u16 *dst;
    u32 *src = &map[srcY * mapW + srcX];
    int count;

    dstY &= 0x3F;
    dstX &= 0x3F;
    dst = func_0208d82c() + ((dstY & 0x1F) << 5);
    if (size & 2) {
        dst += (dstY & 0x20) << ((size & 1) ? 6 : 5);
    }
    for (; n > 0; end += 0x20) {
        count = end - dstX;
        if (count > n) {
            count = n;
        }
        if (count > 0) {
            int i = dstX & 0x1F;
            if (size & 1) {
                i += (dstX & 0x20) << 5;
            }
            func_0208da88(src, dst + i, count);
            n -= count;
            src += count;
            dstX += count;
        }
    }
}

void Unk0208d304::func_0208da88(u32 *src, u16 *dst, int n) {
    while (n-- != 0) {
        u32 v = *src++;
        *dst++ = ((v >> 16) & 0xFC00) | (v & 0x3FF);
    }
}

extern "C" void func_0208dac8() {
    data_020c7f64[0] = new Unk0208db14(true);
    data_020c7f64[1] = new Unk0208db14(false);
}

Unk0208db14::Unk0208db14(bool main) : used(0), main(main) {
    Unk0208d304 *layer = layers;
    int i;

    if (main) {
        DispCnt_ApplyPendingMode();
    } else {
        REG_DB_DISPCNT |= 0x10000;
    }
    for (i = 0; i < 4; i++) {
        layer->func_0208d774(main);
        layer->func_0208d758(i);
        charBlock[i] = -1;
        charCount[i] = -1;
        screenBlock[i] = -1;
        screenCount[i] = -1;
        layer++;
    }
    for (i = 0; i < 4; i++) {
        bits[i] = 0;
    }
}

Unk0208db14 *Unk0208db14::func_0208dbe8() {
    return data_020c7f64[0];
}

Unk0208db14 *Unk0208db14::func_0208dbf8() {
    return data_020c7f64[1];
}

Unk0208db14 *Unk0208db14::func_0208dc08(int main) {
    if (main) {
        return data_020c7f64[0];
    }
    return data_020c7f64[1];
}

int Unk0208db14::func_0208dc24() {
    if (main) {
        return func_02078174();
    }
    return func_02078114();
}

/*
 * 99.82 %: both `func_0208d530(flag ? 0 : 1)` calls give `moveq r1, #1; movne r1,
 * #0` where the original has `movne r1, #0; moveq r1, #1` (`!flag`, `flag == 0`,
 * if / else, a bool parameter and an inline helper tried).
 */
Unk0208d304 *Unk0208db14::func_0208dc44(Unk02095140 *file, int flag, int charBase, int index) {
    int slot = func_0208dee4();
    Unk0208d304 *layer = slot == -1 ? 0 : &layers[slot];

    if (layer == 0) {
        return 0;
    }
    if (file == 0) {
        if (charBase < 0) {
            charBase = 0;
        }
        layer->func_0208d4d8(charBase);
        layer->func_0208d500(0);
        layer->func_0208d530(flag ? 0 : 1);
        if (flag) {
            layer->func_0208d820(0x20, 0x19);
        } else {
            layer->func_0208d820(0x21, 0x19);
        }
        layer->func_0208d438();
        return layer;
    }
    if (!file->func_02094f88()) {
        return 0;
    }
    file->func_02095180();
    if (!file->func_020951a8(index)) {
        index = 0;
    }
    if (charBase < 0) {
        int size = file->func_02095244(index);
        charBase = func_0208e260(size);
        if (charBase != -1) {
            layer->func_0208d4d8(charBase);
            charBlock[slot] = charBase;
            charCount[slot] = ((size + 0x7FF) & -0x800) >> 11;
            func_02099b84(file->func_020951e4(index), layer->func_0208d850(), size);
        }
    } else {
        layer->func_0208d4d8(charBase);
    }
    int count = flag ? 1 : 2;
    int screenBase = func_0208e2cc(count);
    if (screenBase != -1) {
        layer->func_0208d500(screenBase);
        screenBlock[slot] = screenBase;
        screenCount[slot] = count;
    }
    layer->func_0208d530(flag ? 0 : 1);
    if (flag) {
        layer->func_0208d820(0x20, 0x19);
    } else {
        layer->func_0208d820(0x21, 0x19);
    }
    layer->func_0208d388(file, index);
    return layer;
}

Unk0208d304 *Unk0208db14::func_0208de60() {
    if (!main) {
        return 0;
    }
    if (used & 1) {
        return 0;
    }
    layers[0].func_0208d438();
    used |= 1;
    REG_DISPCNT |= 8;
    layers[0].func_0208d874(1);
    layers[0].x = 0;
    layers[0].y = 0;
    return &layers[0];
}

int Unk0208db14::func_0208dee4() {
    int i;

    if ((used & 0xF) == 0xF) {
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if (!(used & (1 << i))) {
            used |= 1 << i;
            return i;
        }
    }
    return -1;
}

void Unk0208db14::func_0208df4c(Unk0208d304 *layer) {
    int bg;

    if (layer->func_0208d558() != main) {
        return;
    }
    bg = layer->func_0208d548();
    if (!(used & (1 << bg))) {
        return;
    }
    used &= ~(1 << bg);
    layer->func_0208d7a0(0);
    if (layer->func_0208d88c()) {
        REG_DISPCNT &= ~8;
        layer->func_0208d874(0);
    }
    if (charBlock[bg] != -1) {
        func_0208e46c(charBlock[bg] << 3, charCount[bg]);
        charBlock[bg] = -1;
    }
    if (screenBlock[bg] != -1) {
        func_0208e46c(screenBlock[bg], screenCount[bg]);
        screenBlock[bg] = -1;
    }
    layer->func_0208d444();
}

void Unk0208db14::func_0208e058(Unk02095140 *file, int index, int mask) {
    u8 *data;
    int offset;
    u32 m;

    if (!file->func_02094f88()) {
        return;
    }
    m = (u16)mask;
    if (m == 0xFFFF) {
        if (main) {
            GX_LoadBGPltt(file->func_02095354(index), 0, 0x200);
        } else {
            GXS_LoadBGPltt(file->func_02095354(index), 0, 0x200);
        }
        return;
    }
    data = file->func_02095354(index);
    offset = 0;
    if (main) {
        while (m != 0) {
            int n = 0;
            while ((m & 1) == 0) {
                m >>= 1;
                offset += 0x20;
            }
            while ((m & 1) != 0) {
                m >>= 1;
                n += 0x20;
            }
            GX_LoadBGPltt(data + offset, offset, n);
            offset += n;
        }
    } else {
        while (m != 0) {
            int n = 0;
            while ((m & 1) == 0) {
                m >>= 1;
                offset += 0x20;
            }
            while ((m & 1) != 0) {
                m >>= 1;
                n += 0x20;
            }
            GXS_LoadBGPltt(data + offset, offset, n);
            offset += n;
        }
    }
}

void Unk0208db14::func_0208e1b0(Unk02095140 *file, int index, u32 src, u32 dst, u32 n) {
    u8 *data;

    if (!file->func_02094f88()) {
        return;
    }
    data = file->func_02095354(index);
    if (src + n > 0x100 || dst + n > 0x100) {
        return;
    }
    data += src * 2;
    if (main) {
        GX_LoadBGPltt(data, dst * 2, n * 2);
    } else {
        GXS_LoadBGPltt(data, dst * 2, n * 2);
    }
}

void Unk0208db14::func_0208e224(void *data, u32 dst, u32 n) {
    if (dst + n > 0x100) {
        return;
    }
    if (main) {
        GX_LoadBGPltt(data, dst * 2, n * 2);
    } else {
        GXS_LoadBGPltt(data, dst * 2, n * 2);
    }
}

int Unk0208db14::func_0208e260(int size) {
    int start = 0;

    if (func_0208dc24() > 0x10000) {
        start = 0x10;
    }
    size = ((size + 0x7FF) & -0x800) >> 11;
    return func_0208e364(size, start, func_0208dc24() >> 11, 7) >> 3;
}

int Unk0208db14::func_0208e2cc(int count) {
    int size = func_0208dc24();
    int result;
    int start;
    int n;

    if (size > 0x10000) {
        size = 0x10000;
    }
    result = -1;
    start = 8 - count;
    n = size >> 14;
    while (n-- != 0 && result == -1) {
        result = func_0208e364(count, start, start + count, 0);
        start += 8;
    }
    if (result != -1) {
        return result;
    }
    return func_0208e364(count, 0, size >> 11, 0);
}

/*
 * Inline helper (hypothesis): marking the blocks through a function with its own
 * copies of start and count gives the original registers of the marking loop.
 */
static inline void func_setBits(u32 *bits, int start, int count) {
    int cur = -1;
    u32 word;

    while (count-- != 0) {
        if (start >> 5 != cur) {
            if (cur >= 0) {
                bits[cur] = word;
            }
            word = bits[start >> 5];
            cur = start >> 5;
        }
        word |= 1 << (start & 0x1F);
        start++;
    }
    bits[(start - 1) >> 5] = word;
}

int Unk0208db14::func_0208e364(int count, int start, int end, int align) {
    u32 word;
    int cur = -1;
    int run = 0;
    int i;

    if (end > 0x80) {
        end = 0x80;
    }
    if (start >= end) {
        return -1;
    }
    for (i = start; i < end; i++) {
        if (cur != i >> 5) {
            word = bits[i >> 5];
            cur = i >> 5;
        }
        if (run == 0 && (i & align)) {
            continue;
        }
        if ((word & (1 << (i & 0x1F))) == 0) {
            if (run == 0) {
                start = i;
            }
            run++;
        } else {
            run = 0;
        }
        if (run == count) {
            break;
        }
    }
    if (run == count) {
        func_setBits(bits, start, count);
        return start;
    }
    return -1;
}

void Unk0208db14::func_0208e46c(int start, int count) {
    int cur;
    u32 word;

    if (count <= 0) {
        return;
    }
    if (start < 0) {
        return;
    }
    if (start + count >= 0x80) {
        return;
    }
    cur = -1;
    while (count-- != 0) {
        if (start >> 5 != cur) {
            if (cur >= 0) {
                bits[cur] = word;
            }
            word = bits[start >> 5];
            cur = start >> 5;
        }
        word &= ~(1 << (start & 0x1F));
        start++;
    }
    bits[cur] = word;
}

void Unk0208db14::func_0208e4ec() {
    Unk0208d304 *layer = layers;
    u32 mask = 0;
    int i;

    for (i = 0; i < 4; i++) {
        layer->func_0208d570();
        if (layer->func_0208d7b8()) {
            mask |= 1 << (i + 8);
        }
        layer++;
    }
    if (main) {
        REG_DISPCNT = (REG_DISPCNT & ~0xF00) | mask;
    } else {
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0xF00) | mask;
    }
}
