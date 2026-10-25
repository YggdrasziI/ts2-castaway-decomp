/*
 * Unit 0x0208FF50-0x02090CCC: a grid of 64 x 64 objects used as a canvas
 * (Unk02090308). It takes its objects from the object manager of unit_020916A4.cpp,
 * places them in rows and columns, and draws text into their 4-bit pixel buffers:
 * a printf-style call lays the text out with unit_02092830.cpp and copies each
 * glyph of the font's file (Unk02095140) at its position, over up to four objects.
 * func_0208ff50 copies the 8 x 8 tiles of one glyph into an object, clipped to it;
 * func_020901a4 merges one tile (flips, horizontal shift) into the buffer.
 *
 * Bounds: hypothesis. Before 0x0208FF50 lie the functions of the 40-byte object
 * entry (func_0208ff24 and earlier); 0x02090CCC starts unit_02090CCC.cpp. The two
 * tile functions are only called from here. Real file name unknown.
 */

#include "game/unk_file.h"
#include "game/unk_oam.h"
#include "game/unk_rect.h"
#include "game/unk_text.h"

/* va_list of the mwccarm runtime, as the variadic call site computes it. */
typedef char *va_list;
#define va_start(ap, parm) \
    ((ap) = (va_list)((char *)((u32)&(parm) & ~3U) + ((sizeof(parm) + 3U) & ~3U)))
#define va_end(ap) ((void)0)

/* Header of the font file: size in tiles and bits per pixel. */
struct Unk02095140Header {
    int width;
    int height;
    int count;
    int unkC;
    u8 bpp;
};

class Unk02095140 : public Unk0209487c {
public:
    Unk02095140Header *func_02095180();
    u8 *func_020951e4(int index);
    u8 *func_020952b0(int index);
};

extern "C" {
int func_0208299c(char *buf, int size, const char *fmt, va_list args);
void func_0208fadc(Unk0208f8b0 *entry, int shape, int size);
void func_0208fb44(Unk0208f8b0 *entry, int unk);
void func_0208fb6c(Unk0208f8b0 *entry, int unk);
void func_0208fb80(Unk0208f8b0 *entry, int unk);
void func_0208fb98(Unk0208f8b0 *entry, int unk);
void func_0208fddc(Unk0208f8b0 *entry);
void func_0208ff24(Unk0208f8b0 *entry, int unk);
}

void func_0208ff50(Unk0208f8b0 *entry, Unk02095140 *file, int index, int x, int y);

class Unk02090308 {
public:
    Unk02090308();
    ~Unk02090308();
    void func_02090420();
    void func_020905ac();
    void func_020905c4(int screen);
    void func_020905d4(int unk);
    void func_02090620(int unk);
    void func_0209066c(int w, int h);
    void func_020906e4(Unk02095140 *file, int x, int y, int index);
    void func_02090878(int x, int y);
    void func_0209088c();
    void func_02090898(int unk);
    void func_020908ac(int priority);
    void func_020908bc(const Unk02098bc8 *rect);
    void func_020908e0(int hAlign, int vAlign);
    void func_020908ec();
    void func_02090958();
    void func_020909c8(Unk02092830Font *font, const char *fmt, ...);
    void func_02090a10(Unk02092830Font *font, const char *fmt, va_list args);
    bool func_02090b08(int pages, Unk02092830Font *font, const char *fmt, ...);
    bool func_02090b64(int pages, Unk02092830Font *font, const char *fmt, va_list args);
    int func_02090c84();
    Unk0208f8b0 *func_02090c8c(int index);
    u16 func_02090cbc();
    u16 func_02090cc4();

    u16 cols;
    u16 rows;
    u16 unk4;
    u16 priority;
    u16 unk8;
    u16 screen;
    u16 flags;
    int unk10;
    int hAlign;
    int vAlign;
    Unk02098bc8 rect;
    Unk0208f8b0 **entries;
    int count;
    int spacing;
    int lineSpacing;
    int x;
    int y;
};

void func_020901a4(u32 *src, u32 *dst, int shift, int tiles, u32 start, u32 rows, int flags);

/* 89.67 %: register allocation (the original loads the glyph size with one ldm). */
void func_0208ff50(Unk0208f8b0 *entry, Unk02095140 *file, int index, int x, int y) {
    Unk02095140Header *h = file->func_02095180();
    u32 *cells;
    u32 *pixels;
    int width;
    int height;
    int right;
    int bottom;
    int stride;
    int tiles;
    int start;
    int sizeW;
    int sizeH;
    int th;
    int tw;
    u32 *dst;
    int n;
    int shift;
    int rowStep;
    int w;
    int col;
    int cx;
    int cflags;
    u32 cell;

    if (h->bpp != 4) {
        return;
    }
    if (entry->unk8 & 0x2000) {
        return;
    }
    if (entry->unk20 == 0) {
        return;
    }
    cells = (u32 *)file->func_020952b0(index);
    pixels = (u32 *)file->func_020951e4(index);
    sizeW = entry->unk10_0;
    sizeH = entry->unk10_2;
    tw = h->width;
    th = h->height;
    width = tw << 3;
    right = x + (tw << 3);
    height = th << 3;
    stride = width >> 3;
    tiles = (1 << (sizeW + 3)) >> 3;
    bottom = y + (th << 3);
    start = 0;
    if (right > (1 << (sizeW + 3))) {
        width -= right - (1 << (sizeW + 3));
    }
    if (bottom > (1 << (sizeH + 3))) {
        height -= bottom - (1 << (sizeH + 3));
    }
    if (x < 0) {
        n = -x;
        width -= n & ~7;
        cells += n >> 3;
        x = -(n & 7);
    }
    if (y < 0) {
        n = -y;
        height -= n & ~7;
        start = n & 7;
        cells += (n >> 3) * stride;
        y = -start;
    }
    dst = (u32 *)((u8 *)entry->unk20 + ((y & 7) << 2)) + (x & ~7) + ((y >> 3) * tiles) * 8;
    if (height <= 0) {
        return;
    }
    shift = x & 7;
    rowStep = tiles << 3;
    do {
        w = width;
        col = 0;
        cx = x;
        while (w > 0) {
            /* Tile number in bits 0-15, flips in bits 26-27. */
            cell = cells[col];
            cflags = ((cell << 4) >> 30) & 3;
            if (w < 8) {
                cflags |= 8;
            }
            if (cx < 0) {
                cflags |= 4;
            }
            func_020901a4(pixels + ((cell & 0xffff) << 3), dst + col * 8, shift, tiles, start,
                          height >= 8 ? 8 : height, cflags);
            w -= 8;
            cx += 8;
            col++;
        }
        height -= 8;
        dst += rowStep;
        start = 0;
        cells += stride;
    } while (height > 0);
}

void func_020901a4(u32 *src, u32 *dst, int shift, int tiles, u32 start, u32 rows, int flags) {
    u32 mask;
    int rshift;
    u32 px;
    u32 t;
    int i;

    if (start > 7) {
        return;
    }
    if (rows > 8) {
        rows = 8;
    }
    rshift = (8 - shift) << 2;
    if (flags & 2) {
        src += 7 - start;
    } else {
        src += start;
    }
    rows -= start;
    shift <<= 2;
    tiles = (tiles << 3) - 8;
    while (start-- != 0) {
        dst++;
        if (!((u32)dst & 0x1f)) {
            dst += tiles;
        }
    }
    while (rows-- != 0) {
        mask = 0;
        px = *src;
        if (flags & 1) {
            t = (px << 16) | (px >> 16);
            px = ((t & 0xf000f000) >> 12) | ((t & 0x000f000f) << 12) | ((t & 0x0f000f00) >> 4) | ((t & 0x00f000f0) << 4);
        }
        for (i = 0; i < 32; i += 4) {
            if (px & (0xf << i)) {
                mask |= 0xf << i;
            }
        }
        if (!(flags & 4)) {
            dst[0] = (dst[0] & ~(mask << shift)) | (px << shift);
        }
        if (!(flags & 8)) {
            dst[8] = (dst[8] & ~(mask >> rshift)) | (px >> rshift);
        }
        if (flags & 2) {
            src--;
        } else {
            src++;
        }
        dst++;
        if (!((u32)dst & 0x1f)) {
            dst += tiles;
        }
    }
}

Unk02090308::Unk02090308()
    : cols(2), rows(2), unk4(0), priority(0), unk8(0), screen(0), flags(0), unk10(0),
      hAlign(0), vAlign(0), rect(0, 0, 0x80, 0x80), entries(0), count(0), spacing(0),
      lineSpacing(0), x(0), y(0) {}

Unk02090308::~Unk02090308() {
    func_02090958();
}

void Unk02090308::func_02090420() {
    int idx;
    Unk0208f8b0 *e;
    int r;
    int c;
    int flip;

    count = cols * rows;
    entries = new Unk0208f8b0 *[count];
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            flip = 0;
            idx = r * cols + c;
            e = Unk020916a4::func_02091840(screen != 0)->func_0209189c(priority);
            entries[idx] = e;
            if (c == cols - 1 && (flags & 1)) {
                flip |= 1;
            }
            if (r == rows - 1 && (flags & 2)) {
                flip |= 2;
            }
            switch (flip) {
            case 0:
                func_0208fadc(e, 3, 0);
                break;
            case 1:
                func_0208fadc(e, 3, 2);
                break;
            case 2:
                func_0208fadc(e, 3, 1);
                break;
            case 3:
                func_0208fadc(e, 2, 0);
                break;
            }
            func_0208fb44(e, 0);
            func_0208fb80(e, unk4);
            func_0208fb98(e, unk8);
            func_0208fddc(e);
            func_0208ff24(e, 0);
            func_0208fb6c(e, unk10);
        }
    }
    func_020908ec();
}

void Unk02090308::func_020905ac() {
    if (entries != 0) {
        return;
    }
    func_02090420();
}

void Unk02090308::func_020905c4(int screen) {
    if (entries == 0) {
        this->screen = screen;
    }
}

void Unk02090308::func_020905d4(int unk) {
    int i;

    unk8 = unk;
    if (entries == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        func_0208fb98(entries[i], unk8);
    }
}

void Unk02090308::func_02090620(int unk) {
    int i;

    unk10 = unk;
    if (entries == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        func_0208fb6c(entries[i], unk10);
    }
}

void Unk02090308::func_0209066c(int w, int h) {
    if (entries != 0) {
        return;
    }
    if (w < 0 || h < 0) {
        return;
    }
    cols = (w + 1) >> 1;
    rows = (h + 1) >> 1;
    flags = 0;
    if (w & 1) {
        flags |= 1;
    }
    if (h & 1) {
        flags |= 2;
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = w << 5;
    rect.h = h << 5;
}

/*
 * 88.21 %: the original copies the glyph index argument into a local stack slot;
 * an int local is merged with the argument, and a u16 argument
 * changes the callers.
 */
void Unk02090308::func_020906e4(Unk02095140 *file, int x, int y, int index) {
    Unk02095140Header *h;
    int cx;
    int cy;
    int cx1;
    int cy1;
    int lx;
    int ly;
    int split;

    if (entries == 0) {
        func_02090420();
    }
    h = file->func_02095180();
    cx = x >> 6;
    cy = y >> 6;
    cx1 = (x + (h->width << 3)) >> 6;
    cy1 = (y + (h->height << 3)) >> 6;
    if (cx >= cols) {
        return;
    }
    if (cy >= rows) {
        return;
    }
    if (cx1 < 0 || cy1 < 0) {
        return;
    }
    if (cx < 0) {
        cx = 0;
    }
    if (cy < 0) {
        cy = 0;
    }
    ly = y - (cy << 6);
    lx = x - (cx << 6);
    split = 0;
    func_0208ff50(entries[cy * cols + cx], file, index, lx, ly);
    if (cx != cx1 && cx1 < cols) {
        split |= 1;
    }
    if (cy != cy1 && cy1 < rows) {
        split |= 2;
    }
    if (split & 1) {
        func_0208ff50(entries[cy * cols + (cx + 1)], file, index, lx - 0x40, ly);
    }
    if (split & 2) {
        func_0208ff50(entries[(cy + 1) * cols + cx], file, index, lx, ly - 0x40);
    }
    if (split == 3) {
        func_0208ff50(entries[(cy + 1) * cols + (cx + 1)], file, index, lx - 0x40, ly - 0x40);
    }
}

void Unk02090308::func_02090878(int x, int y) {
    this->x = x;
    this->y = y;
    func_020908ec();
}

void Unk02090308::func_0209088c() {
    func_02090958();
}

void Unk02090308::func_02090898(int unk) {
    unk4 = unk & 3;
    func_020908ec();
}

void Unk02090308::func_020908ac(int priority) {
    if (entries == 0) {
        this->priority = priority;
    }
}

void Unk02090308::func_020908bc(const Unk02098bc8 *rect) {
    this->rect = *rect;
}

void Unk02090308::func_020908e0(int hAlign, int vAlign) {
    this->hAlign = hAlign;
    this->vAlign = vAlign;
}

void Unk02090308::func_020908ec() {
    int px;
    int py;
    int n;
    int i;
    Unk0208f8b0 *e;

    if (entries == 0) {
        return;
    }
    n = cols;
    px = x;
    py = y;
    for (i = 0; i < count; i++) {
        e = entries[i];
        e->unk0 = px;
        e->unk4 = py;
        func_0208fb80(e, unk4);
        px += 0x40000;
        if (--n == 0) {
            n = cols;
            px = x;
            py += 0x40000;
        }
    }
}

void Unk02090308::func_02090958() {
    int i;

    for (i = 0; i < count; i++) {
        Unk020916a4::func_02091840(screen != 0)->func_02091c68(entries[i]);
    }
    if (entries != 0) {
        delete[] entries;
    }
    entries = 0;
    count = 0;
}

void Unk02090308::func_020909c8(Unk02092830Font *font, const char *fmt, ...) {
    va_list args;

    if (entries == 0) {
        func_02090420();
    }
    va_start(args, fmt);
    func_02090a10(font, fmt, args);
    va_end(args);
}

void Unk02090308::func_02090a10(Unk02092830Font *font, const char *fmt, va_list args) {
    char buf[0x200];
    Unk02095140 *file;
    int bottom;

    func_0208299c(buf, 0x200, fmt, args);
    file = font->func_34();
    Unk02092830 text(buf, font);
    Unk020930e8 layout =
        text.func_02092ee8(hAlign, vAlign, rect.w, rect.h, spacing, lineSpacing);
    bottom = rect.y + rect.h;
    while (layout.func_02093354()) {
        Unk020930e8Glyph g = layout.func_020934f8();

        if (g.y > bottom) {
            return;
        }
        func_020906e4(file, rect.x + g.x, rect.y + g.y, g.unk4);
    }
}

bool Unk02090308::func_02090b08(int pages, Unk02092830Font *font, const char *fmt, ...) {
    va_list args;

    if (entries == 0) {
        func_02090420();
    }
    va_start(args, fmt);
    return func_02090b64(pages, font, fmt, args);
}

bool Unk02090308::func_02090b64(int pages, Unk02092830Font *font, const char *fmt,
                                va_list args) {
    char buf[0x200];
    Unk02095140 *file;
    int bottom;

    func_0208299c(buf, 0x200, fmt, args);
    file = font->func_34();
    Unk02092830 text(buf, font);
    Unk020930e8 layout = text.func_02092f50(hAlign, vAlign, rect.w, rect.h, spacing,
                                            lineSpacing, pages);
    bottom = rect.y + rect.h - font->func_24();
    while (layout.func_02093354()) {
        Unk020930e8Glyph g = layout.func_020934f8();

        if (g.y > bottom) {
            return false;
        }
        func_020906e4(file, rect.x + g.x, rect.y + g.y, g.unk4);
    }
    return true;
}

int Unk02090308::func_02090c84() {
    return count;
}

Unk0208f8b0 *Unk02090308::func_02090c8c(int index) {
    if (entries == 0) {
        return 0;
    }
    if (index >= 0 && index < count) {
        return entries[index];
    }
    return 0;
}

u16 Unk02090308::func_02090cbc() {
    return cols;
}

u16 Unk02090308::func_02090cc4() {
    return rows;
}
