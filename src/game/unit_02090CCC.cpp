/*
 * Unit 0x02090CCC-0x020916A4: a text drawn with objects (Unk02090ccc, derived from
 * Unk02092704 of unit_02092704.cpp). A printf-style call formats up to 128
 * characters, decodes them from UTF-8 and takes one object per visible character
 * from the object manager of unit_020916A4.cpp. Per character it keeps the glyph
 * tile and a word of metrics and flags from the font (unk_text.h). The two virtual
 * functions of the base class are overridden: one breaks the text into lines no
 * wider than the rectangle, the other places the objects with the alignment bits
 * of unk4.
 *
 * Bounds: hypothesis. The vtable at 0x020BD284 is only used by the constructor and
 * the destructors; the code before 0x02090CCC uses another class (fields 0x2c and
 * 0x30); 0x020916A4 starts unit_020916A4.cpp. Real file name unknown.
 * Not complete: two functions do not match yet (see above them).
 */

#include "game/unk_oam.h"
#include "game/unk_rect.h"
#include "game/unk_text.h"

/* va_list of the mwccarm runtime, as the variadic call site computes it. */
typedef char *va_list;
#define va_start(ap, parm) \
    ((ap) = (va_list)((char *)((u32)&(parm) & ~3U) + ((sizeof(parm) + 3U) & ~3U)))
#define va_end(ap) ((void)0)

extern "C" {
int func_0208299c(char *buf, int size, const char *fmt, va_list args);
int func_0209a670(const u8 *str, u32 *out, int max);
void func_0208faac(Unk0208f8b0 *entry, int tile);
void func_0208fb80(Unk0208f8b0 *entry, int unk);
void func_0208fb98(Unk0208f8b0 *entry, int unk);
}

/* Fields of the per-character word. */
#define INFO_BREAK 0x1
#define INFO_NEWLINE 0x2
#define INFO_HIDDEN 0x4
#define INFO_LINE 0x8

class Unk02090ccc : public Unk02092704 {
public:
    Unk02090ccc();
    ~Unk02090ccc();
    void func_02090d80(int screen);
    void func_02090d9c(Unk02092830Font *font, const char *fmt, ...);
    void func_02090dc4(Unk02092830Font *font, const char *fmt, va_list args);
    void func_02090e18(int unk);
    void func_02090e78(int priority);
    void func_02090e84(int unk);
    int func_02090e90(Unk02092830Font *font, int n);
    void func_02090ee4(Unk02092830Font *font, int n);
    void func_020910a4(Unk02092830Font *font, int n);
    void func_020927bc();
    void func_02092788();
    void func_02091654();

    u32 chars[0x80];
    u16 tiles[0x80];
    u32 infos[0x80];
    u16 lineWidths[0x80];
    u16 length;
    u16 lineCount;
    u16 allocated;
    u16 maxLength;
    u16 screen;
    u16 priority;
    u16 unk628;
    s16 spacing;
    int unk62c;
    Unk02092640 it;
};

Unk02090ccc::Unk02090ccc()
    : length(0), lineCount(0), allocated(0), maxLength(0x80), screen(0), priority(0),
      unk628(0), spacing(0), unk62c(-1) {}

Unk02090ccc::~Unk02090ccc() {
    func_02091654();
}

void Unk02090ccc::func_02090d80(int screen) {
    func_02091654();
    this->screen = screen;
}

void Unk02090ccc::func_02090d9c(Unk02092830Font *font, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    func_02090dc4(font, fmt, args);
    va_end(args);
}

void Unk02090ccc::func_02090dc4(Unk02092830Font *font, const char *fmt, va_list args) {
    char buf[0x80];
    int n;

    n = func_0209a670((const u8 *)buf, chars, func_0208299c(buf, 0x80, fmt, args));
    if (n > maxLength) {
        n = maxLength;
    }
    func_02090ee4(font, n);
}

void Unk02090ccc::func_02090e18(int unk) {
    unk62c = unk;
    if (unk < 0) {
        return;
    }
    if (allocated == 0) {
        return;
    }
    it.func_0209266c();
    while (it.func_020926d4()) {
        func_0208fb98((Unk0208f8b0 *)it.func_02092678(), unk62c);
    }
}

void Unk02090ccc::func_02090e78(int priority) {
    this->priority = priority;
}

void Unk02090ccc::func_02090e84(int unk) {
    unk628 = unk;
}

int Unk02090ccc::func_02090e90(Unk02092830Font *font, int n) {
    int count = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (!font->func_30(chars[i])) {
            count++;
        }
    }
    return count;
}

void Unk02090ccc::func_02090ee4(Unk02092830Font *font, int n) {
    int visible = func_02090e90(font, n);

    if (allocated == 0 || allocated != visible) {
        if (allocated != 0) {
            Unk020916a4::func_02091840(screen != 0)->func_02091bec(it);
            allocated = 0;
        }
        if (visible != 0) {
            Unk020916a4 *manager = Unk020916a4::func_02091840(screen != 0);

            it = manager->func_02091b9c(visible, (int)font->func_34(), priority);
            allocated = it.func_020926fc();
        }
    }
    length = n;
    if (allocated == 0) {
        return;
    }
    it.func_0209266c();
    while (it.func_020926d4()) {
        func_0208fb80((Unk0208f8b0 *)it.func_02092678(), unk628);
    }
    if (unk62c >= 0) {
        it.func_0209266c();
        while (it.func_020926d4()) {
            func_0208fb98((Unk0208f8b0 *)it.func_02092678(), unk62c);
        }
    }
    func_020910a4(font, n);
    func_020927bc();
    func_02092788();
}

void Unk02090ccc::func_020910a4(Unk02092830Font *font, int n) {
    int i;
    int w;
    u32 c;
    int x;
    int y;
    u32 info;

    font->func_10(chars[0]);
    unk6 = font->func_24();
    for (i = 0; i < n; i++) {
        c = chars[i];
        w = font->func_18(c) - spacing;
        if (w < 0) {
            w = 0;
        }
        x = font->func_10(c);
        y = font->func_14(c);
        info = ((w << 20) & 0x3f00000) | ((x << 26) & 0xfc000000) | ((y << 10) & 0xffc00);
        if (font->func_28(c)) {
            info |= INFO_BREAK;
            if (font->func_2c(c)) {
                info |= INFO_NEWLINE;
            }
        }
        if (font->func_30(c)) {
            info |= INFO_HIDDEN;
        }
        infos[i] = info;
        tiles[i] = font->func_1c(c);
    }
}

/*
 * 95.15 %: register and stack slot allocation; inside the loop the original reads
 * lineCount twice (once through a pointer kept in r4) for each new line.
 */
void Unk02090ccc::func_020927bc() {
    Unk0208f8b0 *e;
    int i;
    u32 info;
    int breakAt;
    int lineStart;
    bool newLine;
    int maxWidth;
    int breakEnd;
    bool fetch;
    int width;
    bool afterBreak;
    int breakEndWidth;
    int breakWidth;
    u32 adv;

    e = 0;
    i = 0;
    breakAt = -1;
    lineStart = 0;
    newLine = false;
    maxWidth = rect.w;
    breakEnd = -1;
    fetch = true;
    width = 0;
    afterBreak = false;
    if (allocated == 0) {
        return;
    }
    lineCount = 0;
    it.func_0209266c();
    while (!fetch || it.func_020926d4()) {
        if (fetch) {
            e = (Unk0208f8b0 *)it.func_02092678();
        }
        info = infos[i] & ~INFO_LINE;
        adv = (info & 0x3f00000) >> 20;
        if (newLine) {
            if (afterBreak) {
                if (breakEnd == i) {
                    info |= INFO_LINE;
                } else {
                    infos[breakEnd] |= INFO_LINE;
                }
                width -= breakEndWidth;
                lineWidths[lineCount++] = breakWidth;
                afterBreak = false;
            } else {
                info |= INFO_LINE;
                lineWidths[lineCount++] = width;
                width = 0;
            }
            breakAt = -1;
            lineStart = i;
            newLine = false;
        }
        width += adv;
        if (info & INFO_HIDDEN) {
            if (afterBreak) {
                breakEnd = i + 1;
                breakEndWidth = width;
            }
        } else {
            afterBreak = false;
            if (maxWidth < (width << 12) && i > lineStart) {
                if (breakAt > lineStart) {
                    if (breakEnd == i) {
                        info |= INFO_LINE;
                    } else {
                        infos[breakEnd] |= INFO_LINE;
                    }
                    width -= breakEndWidth;
                    lineWidths[lineCount++] = breakWidth;
                } else {
                    info |= INFO_LINE;
                    lineWidths[lineCount++] = width - adv;
                    width = adv;
                }
                breakAt = -1;
            }
        }
        if (!afterBreak && (info & INFO_BREAK)) {
            if (info & INFO_HIDDEN) {
                breakWidth = width - adv;
                breakAt = i;
            } else {
                breakAt = i + 1;
                breakWidth = width;
            }
            breakEnd = i + 1;
            breakEndWidth = width;
            afterBreak = true;
        }
        if (info & INFO_NEWLINE) {
            newLine = true;
        }
        if (info & INFO_HIDDEN) {
            fetch = false;
        } else {
            func_0208faac(e, tiles[i]);
            fetch = true;
        }
        infos[i] = info;
        i++;
    }
    if (afterBreak) {
        lineWidths[lineCount++] = breakWidth;
    } else {
        lineWidths[lineCount++] = width;
    }
}

/* 99.85 %: dx and adv swap registers (best of the declaration orders tried). */
void Unk02090ccc::func_02092788() {
    Unk0208f8b0 *e = 0;
    int i = 0;
    int dy;
    int line = 0;
    int x = 0;
    int y = rect.y;
    int w = rect.w;
    bool fetch = true;
    int dx;
    u32 adv;
    int align;
    u32 info;
    int lw;

    if (allocated == 0) {
        return;
    }
    switch (unk4 & 0xc) {
    case 8:
        y += ((u32)rect.h >> 1) - ((lineCount * (unk6 << 12)) >> 1);
        break;
    case 4:
        y += rect.h - lineCount * (unk6 << 12);
        break;
    }
    it.func_0209266c();
    while (!fetch || it.func_020926d4()) {
        if (fetch) {
            e = (Unk0208f8b0 *)it.func_02092678();
        }
        info = infos[i];
        adv = (info & 0x3f00000) >> 20;
        dx = (info & 0xfc000000) >> 26;
        dy = (int)((info & 0xffc00) << 12) >> 22;
        if (i == 0 || (info & INFO_LINE)) {
            align = unk4 & 3;
            lw = lineWidths[line++];
            x = rect.x;
            switch (align) {
            case 2:
                x += (w - (lw << 12)) >> 1;
                break;
            case 1:
                x += w - (lw << 12);
                break;
            }
            if (info & INFO_LINE) {
                y += unk6 << 12;
            }
        }
        if (info & INFO_HIDDEN) {
            fetch = false;
        } else {
            e->unk0 = x - (dx << 12);
            e->unk4 = y + (dy << 12);
            fetch = true;
        }
        x += adv << 12;
        i++;
    }
}

void Unk02090ccc::func_02091654() {
    chars[0] = 0;
    length = 0;
    lineCount = 0;
    if (allocated == 0) {
        return;
    }
    Unk020916a4::func_02091840(screen != 0)->func_02091bec(it);
    allocated = 0;
}
