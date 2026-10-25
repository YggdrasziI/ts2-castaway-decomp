/*
 * The two fonts implementing Unk02092830Font: unit_0208E570.cpp (ranges of glyph
 * frames) and unit_0208F16C.cpp (sorted character list). Layouts from the code;
 * all names are placeholders.
 */
#ifndef GAME_UNK_FONT_H
#define GAME_UNK_FONT_H

#include "game/unk_datatree.h"
#include "game/unk_text.h"

typedef signed char s8;
typedef unsigned short u16;

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

/* One character: code, break flags and kerning. */
struct Unk0208f16cEntry {
    Unk0208f16cEntry() {
        code = 0;
        flags = 0;
        kerning = 0;
    }

    u32 code;
    u16 flags;
    u16 kerning;
};

class Unk0208f16c : public Unk02092830Font {
public:
    Unk0208f16c();
    virtual ~Unk0208f16c();
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
    void func_0208f2c8(Unk02096348 *script);
    void func_0208f3a4(Unk02096348 *script);
    void func_0208f464(Unk02096348 *script, const Unk0209674c &node);
    void func_0208f5ec(Unk02096348 *script, const Unk0209674c &node);

    Unk0208f16cEntry *entries;
    int count;
    Unk02095140 *file;
    u16 width;
    u16 height;
    u16 baseline;
};

#endif
