/*
 * Unit 0x0208E570-0x0208F16C: a font (Unk0208e570) implementing the font interface
 * of the text layout (Unk02092830Font, include/game/unk_text.h), like the font of
 * unit_0208F16C.cpp. Characters map to glyph frames through up to 16 ranges
 * (0-255 by default); each glyph has a signed leading, kerning and baseline and
 * break flags. The metrics come from a data tree file (Unk02096348): the
 * "AdjustHeight" node ("Top", "Bottom"), the "Range" nodes ("StartCharacter",
 * "EndCharacter", "StartFrame") and the "Character" nodes ("Char", "Leading",
 * "Kerning", "Baseline", "CanBreak", "AlwaysBreak", "Whitespace").
 *
 * Bounds: hypothesis. Before 0x0208E570 lies a function writing the display
 * control registers; the interface destructor 0x0208F168, emitted here, closes the
 * file and 0x0208F16C starts unit_0208F16C.cpp. The strings, the vtable and the
 * first copy of the interface vtable (0x020BD130) are only used here. Real file
 * name unknown.
 * Not complete: func_0208e96c does not match yet (see above it), and the interface
 * destructor D0 this file emits clashes with its kept copy (0x0201B92C), still
 * assembly (notes/MATCHING.md, unsolved patterns). rangeCount is volatile as a
 * hypothesis: the original re-reads it at every test of the search loop.
 */

#include "game/unk_datatree.h"
#include "game/unk_resource.h"
#include "game/unk_text.h"

extern "C" {
u32 func_0209a418(const u8 *str, u32 ch);
int func_0209a510(const u8 *str);
u32 func_0209a550(const u8 *str);
int func_0209a5d8(const u8 *str, int *length);
}

typedef signed char s8;

/* Metrics of one glyph. */
struct Unk0208e570Glyph {
    s8 leading;
    s8 kerning;
    s8 baseline;
    s8 flags;
};

/* Characters start-end use the frames from base on. */
struct Unk0208e570Range {
    u32 start;
    u32 end;
    u32 base;
};

class Unk0208e570 : public Unk02092830Font {
public:
    Unk0208e570();
    virtual ~Unk0208e570();
    virtual void func_08(Unk02095140 *file, Unk02096348 *script);
    virtual int func_0c(u32 c);
    virtual int func_10(u32 c);
    virtual int func_14(u32 c);
    virtual int func_18(u32 c);
    virtual int func_1c(u32 c);
    virtual int func_20(const char *str);
    virtual int func_24();
    virtual bool func_28(u32 c);
    virtual bool func_2c(u32 c);
    virtual bool func_30(u32 c);
    virtual Unk02095140 *func_34();
    virtual void func_38();
    void func_0208e96c(Unk02096348 *script, u32 count);
    bool func_0208f088(Unk02096348 *script, int index, u32 *c);

    Unk02095140 *file;
    u16 width;
    u16 height;
    u16 count;
    Unk0208e570Glyph *glyphs;
    Unk0208e570Range ranges[16];
    volatile int rangeCount;
};

Unk0208e570::Unk0208e570() {
    file = 0;
    width = 0;
    height = 0;
    count = 0;
    glyphs = 0;
    rangeCount = 0;
}

Unk0208e570::~Unk0208e570() {
    func_38();
}

void Unk0208e570::func_08(Unk02095140 *file, Unk02096348 *script) {
    Unk02095140Header *header;

    if (file == 0) {
        return;
    }
    if (this->file != 0) {
        return;
    }
    if (!file->func_02094f88()) {
        return;
    }
    header = file->func_02095180();
    if (header == 0) {
        return;
    }
    if (this->file != 0) {
        func_38();
    }
    this->file = file;
    file->func_02094f9c();
    width = header->width << 3;
    height = header->height << 3;
    ranges[0].start = 0;
    ranges[0].end = 0xFF;
    ranges[0].base = 0;
    rangeCount = 1;
    if (script == 0) {
        return;
    }
    func_0208e96c(script, header->count);
}

void Unk0208e570::func_38() {
    if (file != 0) {
        file->func_02094fb8();
    }
    file = 0;
    if (glyphs != 0) {
        delete[] glyphs;
    }
    glyphs = 0;
    rangeCount = 0;
}

int Unk0208e570::func_0c(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return glyphs[i].kerning;
    }
    return 0;
}

int Unk0208e570::func_10(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return glyphs[i].leading;
    }
    return 0;
}

int Unk0208e570::func_14(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return glyphs[i].baseline;
    }
    return 0;
}

bool Unk0208e570::func_28(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return (glyphs[i].flags & 3) != 0;
    }
    return false;
}

bool Unk0208e570::func_2c(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return (glyphs[i].flags & 2) != 0;
    }
    return false;
}

bool Unk0208e570::func_30(u32 c) {
    int i = func_1c(c);

    if (i < count) {
        return (glyphs[i].flags & 4) != 0;
    }
    return false;
}

int Unk0208e570::func_18(u32 c) {
    int i = func_1c(c);

    if (i >= count) {
        return width;
    }
    return width - glyphs[i].leading - glyphs[i].kerning;
}

int Unk0208e570::func_20(const char *str) {
    int total = 0;
    int len = 0;
    u32 c;

    while ((c = func_0209a5d8((const u8 *)str, &len)) != 0) {
        total += func_18(c);
        str += len;
    }
    return total;
}

int Unk0208e570::func_1c(u32 c) {
    Unk0208e570Range *r = ranges;
    int i;

    for (i = 0; i < rangeCount; i++, r++) {
        if (c >= r->start && c <= r->end) {
            return r->base + (c - r->start);
        }
    }
    return 0;
}

int Unk0208e570::func_24() {
    return height;
}

Unk02095140 *Unk0208e570::func_34() {
    return file;
}

/*
 * 99.56 %: in the "Character" loop the original schedules `add r0, sp, #0x50` (the
 * node argument of the loop test) after the first four flag stores, ours before
 * them; declaration orders and initialisation forms tried.
 */
void Unk0208e570::func_0208e96c(Unk02096348 *script, u32 count) {
    int adjust;
    int n;

    if (!script->func_02094f88()) {
        return;
    }
    glyphs = new Unk0208e570Glyph[count];
    if (glyphs == 0) {
        return;
    }
    Unk0209674c root = script->func_02096980();

    adjust = 0;
    for (int i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c node = root.func_02096774(i);
        if (node.func_02096864()) {
            continue;
        }
        if (!node.func_0209683c((const u32 *)"AdjustHeight")) {
            continue;
        }
        for (int j = 0; j < node.func_020967ec(); j++) {
            Unk0209674c value = node.func_02096774(j);
            if (value.func_02096864()) {
                int index = value.func_0209688c();
                bool isInt = script->func_02096538(index, 1);
                if (value.func_0209683c((const u32 *)"Top")) {
                    if (isInt) {
                        int top = script->func_02096574(index);
                        adjust -= top;
                        height -= top;
                    }
                } else if (value.func_0209683c((const u32 *)"Bottom") && isInt) {
                    height -= script->func_02096574(index);
                }
            }
        }
    }

    for (u32 k = 0; k < count; k++) {
        glyphs[k].leading = 0;
        glyphs[k].kerning = 0;
        glyphs[k].baseline = adjust;
        glyphs[k].flags = 0;
    }

    n = 0;
    for (int i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c node = root.func_02096774(i);
        if (node.func_02096864()) {
            continue;
        }
        if (!node.func_0209683c((const u32 *)"Range")) {
            continue;
        }
        int start = 0;
        int end = 0;
        int frame = 0;
        for (int j = 0; j < node.func_020967ec(); j++) {
            Unk0209674c value = node.func_02096774(j);
            if (value.func_02096864()) {
                int index = value.func_0209688c();
                if (script->func_02096538(index, 1)) {
                    if (value.func_0209683c((const u32 *)"StartCharacter")) {
                        start = script->func_02096574(index);
                    } else if (value.func_0209683c((const u32 *)"EndCharacter")) {
                        end = script->func_02096574(index);
                    } else if (value.func_0209683c((const u32 *)"StartFrame")) {
                        frame = script->func_02096574(index);
                    }
                }
            }
        }
        ranges[n].start = start;
        ranges[n].end = end;
        ranges[n].base = frame;
        rangeCount = ++n;
    }

    for (int i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c node = root.func_02096774(i);
        if (node.func_02096864()) {
            continue;
        }
        if (!node.func_0209683c((const u32 *)"Character")) {
            continue;
        }
        int leading;
        int kerning;
        int baseline;
        int mask = 0;
        int j;
        int hasChar = 0;
        int charOk = 0;
        int hasLeading = 0;
        int hasKerning = 0;
        int flags = 0;
        int hasBaseline = 0;
        u32 c;
        for (j = 0; j < node.func_020967ec(); j++) {
            Unk0209674c value = node.func_02096774(j);
            if (value.func_02096864()) {
                int index = value.func_0209688c();
                bool isInt = script->func_02096538(index, 1);
                bool isBool = script->func_02096538(index, 3);
                if (value.func_0209683c((const u32 *)"Char")) {
                    hasChar = 1;
                    charOk = func_0208f088(script, index, &c);
                } else if (value.func_0209683c((const u32 *)"Leading")) {
                    if (isInt) {
                        leading = script->func_02096574(index);
                        hasLeading = 1;
                    }
                } else if (value.func_0209683c((const u32 *)"Kerning")) {
                    if (isInt) {
                        kerning = script->func_02096574(index);
                        hasKerning = 1;
                    }
                } else if (value.func_0209683c((const u32 *)"Baseline")) {
                    if (isInt) {
                        baseline = adjust + script->func_02096574(index);
                        hasBaseline = 1;
                    }
                } else if (value.func_0209683c((const u32 *)"CanBreak")) {
                    if (isBool) {
                        if (script->func_020965c8(index)) {
                            flags |= 1;
                        } else {
                            flags &= ~1;
                        }
                        mask |= 1;
                    }
                } else if (value.func_0209683c((const u32 *)"AlwaysBreak")) {
                    if (isBool) {
                        if (script->func_020965c8(index)) {
                            flags |= 2;
                        } else {
                            flags &= ~2;
                        }
                        mask |= 4;
                    }
                } else if (value.func_0209683c((const u32 *)"Whitespace") && isBool) {
                    if (script->func_020965c8(index)) {
                        flags |= 4;
                    } else {
                        flags &= ~4;
                    }
                    mask |= 4;
                }
            }
        }
        if (hasChar && charOk) {
            u32 g = func_1c(c);
            if (g < count) {
                Unk0208e570Glyph *glyph = &glyphs[g];
                if (hasLeading) {
                    glyph->leading = leading;
                }
                if (hasKerning) {
                    glyph->kerning = kerning;
                }
                if (hasBaseline) {
                    glyph->baseline = baseline;
                }
                glyph->flags = flags | (glyph->flags & ~mask);
            }
        }
    }
    this->count = count;
}

bool Unk0208e570::func_0208f088(Unk02096348 *script, int index, u32 *c) {
    const u8 *s;

    if (script->func_02096538(index, 1)) {
        int digit = script->func_02096574(index);
        if (digit >= 0 && digit < 10) {
            *c = digit + '0';
            return true;
        }
    } else if (script->func_02096538(index, 0)) {
        s = script->func_02096564(index);
        if (func_0209a510(s)) {
            *c = func_0209a550(s);
            return true;
        }
        if (func_0209a418(s, 0) == 0) {
            *c = 0;
            return true;
        }
        if (func_0209a418(s, 0) == 1) {
            *c = *s;
            return true;
        }
    }
    return false;
}
