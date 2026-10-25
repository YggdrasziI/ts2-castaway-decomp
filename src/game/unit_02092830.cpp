/*
 * Unit 0x02092830-0x02093544: text layout (include/game/unk_text.h). A text
 * (Unk02092830: UTF-8 string and font) is split into words (Unk020928dc), the words
 * into lines no wider than a maximum (Unk02092b94), and the lines into positioned
 * glyphs with horizontal and vertical alignment (Unk020930e8). The text also
 * computes the bounding rectangle of its layout, skips whole pages and counts
 * them. Character widths and classes come from virtual functions of the font.
 *
 * Bounds: hypothesis. 0x02092830 follows the base class of unit_02092704.cpp;
 * 0x02093544 starts unit_02093544.cpp. The functions only call each other, the
 * UTF-8 helpers of unit_0209A32C.c and the rectangle constructors. Real file name
 * unknown.
 * Not complete: four functions do not match yet (see above them).
 */

#include "game/unk_text.h"

extern "C" {
u32 func_0209a418(const u8 *str, u32 ch);
u32 func_0209a5d8(const u8 *str, int *length);
}

Unk02092830::Unk02092830(const char *text, Unk02092830Font *font) {
    this->text = text;
    this->font = font;
    length = 0;
    visible = 0;
    func_02092854();
}

/* 98.97 %: the text pointer and the character swap registers (r8 / r6). */
void Unk02092830::func_02092854() {
    const u8 *p;
    int n;
    u32 c;
    int len;

    if (font == 0 || text == 0) {
        return;
    }
    length = func_0209a418((const u8 *)text, 0);
    p = (const u8 *)text;
    n = 0;
    do {
        c = func_0209a5d8(p, &len);
        if (c != 0) {
            if (!font->func_30(c)) {
                n++;
            }
        }
        p += len;
    } while (c != 0);
    visible = n;
}

Unk020928dc::Unk020928dc() : next(-1), spacing(0), text(0), font(0) {}

Unk020928dc::Unk020928dc(const char *text, Unk02092830Font *font, int spacing)
    : next(0), spacing(spacing), text(text), font(font) {
    next = func_02092a34(0);
}

bool Unk020928dc::func_02092970() {
    return word.start != -1;
}

Unk020928dcWord Unk020928dc::func_02092988() {
    Unk020928dcWord w = word;

    if (next != -1) {
        next = func_02092a34(next);
    } else {
        word = Unk020928dcWord();
    }
    return w;
}

void Unk020928dc::func_02092a20(int pos) {
    next = func_02092a34(pos);
}

int Unk020928dc::func_02092a34(int pos) {
    u32 c;
    const char *p;
    int w;
    int result;
    int count;
    int visible;
    int length;
    int width;
    int len;

    p = text + pos;
    word.lastWidth = 0;
    word.lastLength = 0;
    word.end = false;
    count = 0;
    result = -1;
    visible = 0;
    length = 0;
    width = 0;
    do {
        c = func_0209a5d8((const u8 *)p, &len);
        if (c != 0) {
            if (!font->func_30(c)) {
                visible++;
            }
            w = spacing + font->func_18(c);
            p += len;
            length += len;
            width += w;
            count++;
            if (font->func_28(c)) {
                result = pos + length;
                if (font->func_30(c)) {
                    if (count > 1) {
                        word.lastWidth = w;
                        word.lastLength = len;
                    }
                }
                word.end = font->func_2c(c);
                break;
            }
        }
    } while (c != 0);
    word.length = length;
    word.start = pos;
    word.count = count;
    word.visible = visible;
    word.width = width;
    return result;
}

Unk02092b94 Unk02092830::func_02092b78(int maxWidth, int spacing) {
    return Unk02092b94(text, font, maxWidth, spacing);
}

Unk02092b94::Unk02092b94(const char *text, Unk02092830Font *font, int maxWidth, int spacing) {
    this->maxWidth = maxWidth;
    words = Unk020928dc(text, font, spacing);
    func_02092c34();
}

/* 95.92 %: register allocation of the sums; best of the declaration orders tried. */
void Unk02092b94::func_02092c34() {
    int width;
    int lastWidth;
    int words;
    int start;
    int length;
    int lastLength;
    int visible;
    int count;
    int x;

    width = 0;
    lastWidth = 0;
    lastLength = 0;
    words = 0;
    length = 0;
    visible = 0;
    count = 0;
    start = -1;
    if (this->words.func_02092970()) {
        do {
            Unk020928dcWord w = this->words.func_02092988();
            x = width + w.width - w.lastWidth;
            if (width != 0 && x > maxWidth) {
                this->words.func_02092a20(w.start);
                break;
            }
            if (start == -1) {
                start = w.start;
            }
            visible += w.visible;
            width += w.width;
            length += w.length;
            count += w.count;
            lastWidth = w.lastWidth;
            words++;
            lastLength = w.lastLength;
            if (w.end) {
                break;
            }
        } while (this->words.func_02092970());
    }
    if (lastLength != 0) {
        count--;
    }
    width -= lastWidth;
    length -= lastLength;
    line.width = width;
    line.words = words;
    line.count = count;
    line.length = length;
    line.start = start;
    line.visible = visible;
}

bool Unk02092b94::func_02092d3c() {
    return line.start != -1;
}

Unk02092b94Line Unk02092b94::func_02092d54() {
    Unk02092b94Line l = line;

    if (!words.func_02092970()) {
        line.start = -1;
    } else {
        func_02092c34();
    }
    return l;
}

Unk02098bc8 Unk02092830::func_02092db0(int hAlign, int vAlign, int width, int height,
                                       int spacing, int lineSpacing) {
    Unk020930e8 layout = func_02092ee8(hAlign, vAlign, width, height, spacing, lineSpacing);
    int minX;
    int maxX;
    int minY;
    int maxY;

    if (!layout.func_02093354()) {
        return Unk02098bc8(0, 0, 0, 0);
    }
    Unk02098bc8 rect;
    minX = 0x7fffffff;
    maxX = 0x80000000;
    minY = minX;
    maxY = maxX;
    while (layout.func_02093354()) {
        Unk020930e8Glyph g = layout.func_020934f8();
        if (g.x < minX) {
            minX = g.x;
        }
        if (g.y < minY) {
            minY = g.y;
        }
        if (g.x + g.advance > maxX) {
            maxX = g.x + g.advance;
        }
        if (g.y + font->func_24() > maxY) {
            maxY = g.y + font->func_24();
        }
    }
    return Unk02098bc8(minX, minY, maxX - minX, maxY - minY);
}

/*
 * 69.50 %: the original keeps width in a callee-saved register across the call to
 * func_02092b78 (and saves r3-r8); this one reads it from the stack twice.
 */
Unk020930e8 Unk02092830::func_02092ee8(int hAlign, int vAlign, int width, int height,
                                       int spacing, int lineSpacing) {
    return Unk020930e8(text, font, func_02092b78(width, spacing), hAlign, vAlign, width,
                       height, spacing, lineSpacing);
}

/*
 * 78.81 %: as in func_02092ee8, the original keeps width (in a stack slot) and
 * height (in r9) as locals; this one reads the stack arguments.
 */
Unk020930e8 Unk02092830::func_02092f50(int hAlign, int vAlign, int width, int height,
                                       int spacing, int lineSpacing, int pages) {
    Unk02092b94 lines = func_02092b78(width, spacing);
    int lineHeight = font->func_24();
    int i;
    int h;

    for (i = 0; i < pages; i++) {
        h = height;
        while (lines.func_02092d3c()) {
            h -= lineHeight;
            if (h < 0) {
                break;
            }
            lines.func_02092d54();
        }
    }
    return Unk020930e8(text, font, lines, hAlign, vAlign, width, height, spacing,
                       lineSpacing);
}

int Unk02092830::func_0209303c(int hAlign, int vAlign, int width, u32 height, int spacing,
                               int lineSpacing) {
    int step = lineSpacing + font->func_24();
    int pages;
    int h;

    if (step > height) {
        return 0;
    }
    pages = 0;
    h = 0;
    Unk02092b94 lines = func_02092b78(width, spacing);
    while (lines.func_02092d3c()) {
        if (h - step < 0) {
            h = height;
            pages++;
        }
        h -= step;
        lines.func_02092d54();
    }
    return pages;
}

Unk020930e8::Unk020930e8(const char *text, Unk02092830Font *font, const Unk02092b94 &lines,
                         int hAlign, int vAlign, int width, int height, int spacing,
                         int lineSpacing)
    : width(width), height(height), pos(0), remaining(0), lineCount(0), lineStep(0),
      spacing(spacing), lines(lines), text(text), hAlign(hAlign), vAlign(vAlign),
      font(font) {
    Unk02092b94 copy = lines;

    while (copy.func_02092d3c()) {
        lineCount++;
        copy.func_02092d54();
    }
    lineStep = this->font->func_24() + lineSpacing;
    if (this->vAlign == 1) {
        glyph.lineY = (this->height >> 1) - ((lineCount * lineStep) >> 1);
    } else if (this->vAlign == 2) {
        glyph.lineY = this->height - lineCount * lineStep;
    } else {
        glyph.lineY = 0;
    }
    func_02093368();
}

bool Unk020930e8::func_02093354() {
    return glyph.c != 0;
}

void Unk020930e8::func_02093368() {
    int len;

    glyph.x += glyph.advance;
    if (remaining == 0 && lines.func_02092d3c()) {
        Unk02092b94Line l = lines.func_02092d54();
        remaining = l.length;
        pos = l.start;
        if (hAlign == 2) {
            glyph.x = width - l.width;
        } else if (hAlign == 1) {
            glyph.x = (width >> 1) - (l.width >> 1);
        } else {
            glyph.x = 0;
        }
        if (glyph.c != 0) {
            glyph.lineY += lineStep;
        }
    } else if (remaining == 0) {
        glyph.c = 0;
        return;
    }
    glyph.c = func_0209a5d8((const u8 *)text + pos, &len);
    glyph.unk4 = font->func_1c(glyph.c);
    glyph.advance = spacing + font->func_18(glyph.c);
    glyph.visible = !font->func_30(glyph.c);
    glyph.y = glyph.lineY + font->func_14(glyph.c);
    remaining -= len;
    pos += len;
}

Unk020930e8Glyph Unk020930e8::func_020934f8() {
    Unk020930e8Glyph g = glyph;

    func_02093368();
    return g;
}
