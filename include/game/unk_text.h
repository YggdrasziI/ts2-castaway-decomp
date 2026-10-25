/*
 * Text layout of unit_02092830.cpp: a UTF-8 text with its font, split into words,
 * lines and positioned glyphs. Layouts come from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_TEXT_H
#define GAME_UNK_TEXT_H

#include "game/unk_rect.h"

typedef unsigned char u8;
typedef unsigned long u32;

class Unk02095140;

class Unk02096348;

/*
 * The font interface: a virtual destructor and 13 pure virtual functions, named by
 * their vtable offset because two classes implement them (vtables 0x020BD0F4 and
 * unit_0208F16C.cpp's 0x020BD204). c is a character code.
 */
class Unk02092830Font {
public:
    virtual ~Unk02092830Font() {}
    virtual void func_08(Unk02095140 *file, Unk02096348 *script) = 0;
    virtual int func_0c(u32 c) = 0;
    virtual int func_10(u32 c) = 0;
    virtual int func_14(u32 c) = 0;
    virtual int func_18(u32 c) = 0;
    virtual int func_1c(u32 c) = 0;
    virtual int func_20(const char *str) = 0;
    virtual int func_24() = 0;
    virtual bool func_28(u32 c) = 0;
    virtual bool func_2c(u32 c) = 0;
    virtual bool func_30(u32 c) = 0;
    virtual Unk02095140 *func_34() = 0;
    virtual void func_38() = 0;
};

/* One word: counts, byte range, width and the trailing character. */
struct Unk020928dcWord {
    Unk020928dcWord() : visible(0), count(0), start(-1), length(0), width(0), lastWidth(0),
                        lastLength(0), end(0) {}

    int visible;
    int count;
    int start;
    int length;
    int width;
    int lastWidth;
    int lastLength;
    bool end;
};

class Unk020928dc {
public:
    Unk020928dc();
    Unk020928dc(const char *text, Unk02092830Font *font, int spacing);
    bool func_02092970();
    Unk020928dcWord func_02092988();
    void func_02092a20(int pos);
    int func_02092a34(int pos);

    int next;
    int spacing;
    Unk020928dcWord word;
    const char *text;
    Unk02092830Font *font;
};

/* One line: counts, byte range, word count and width. */
struct Unk02092b94Line {
    Unk02092b94Line() : visible(0), count(0), start(-1), length(0), words(0), width(0) {}

    int visible;
    int count;
    int start;
    int length;
    int words;
    int width;
};

class Unk02092b94 {
public:
    Unk02092b94(const char *text, Unk02092830Font *font, int maxWidth, int spacing);
    void func_02092c34();
    bool func_02092d3c();
    Unk02092b94Line func_02092d54();

    Unk020928dc words;
    Unk02092b94Line line;
    int maxWidth;
};

/* One positioned character. */
struct Unk020930e8Glyph {
    Unk020930e8Glyph() : c(0), unk4(0), x(0), y(0), lineY(0), advance(0), visible(0) {}

    u32 c;
    int unk4;
    int x;
    int y;
    int lineY;
    int advance;
    bool visible;
};

class Unk020930e8 {
public:
    Unk020930e8(const char *text, Unk02092830Font *font, const Unk02092b94 &lines, int hAlign,
                int vAlign, int width, int height, int spacing, int lineSpacing);
    bool func_02093354();
    void func_02093368();
    Unk020930e8Glyph func_020934f8();

    int width;
    int height;
    int pos;
    int remaining;
    int lineCount;
    int lineStep;
    int spacing;
    Unk02092b94 lines;
    Unk020930e8Glyph glyph;
    const char *text;
    int hAlign;
    int vAlign;
    Unk02092830Font *font;
};

class Unk02092830 {
public:
    Unk02092830(const char *text, Unk02092830Font *font);
    void func_02092854();
    Unk02092b94 func_02092b78(int maxWidth, int spacing);
    Unk02098bc8 func_02092db0(int hAlign, int vAlign, int width, int height, int spacing,
                              int lineSpacing);
    Unk020930e8 func_02092ee8(int hAlign, int vAlign, int width, int height, int spacing,
                              int lineSpacing);
    Unk020930e8 func_02092f50(int hAlign, int vAlign, int width, int height, int spacing,
                              int lineSpacing, int pages);
    int func_0209303c(int hAlign, int vAlign, int width, u32 height, int spacing,
                      int lineSpacing);

    const char *text;
    Unk02092830Font *font;
    u32 length;
    int visible;
};

#endif
