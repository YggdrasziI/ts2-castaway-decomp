/*
 * Object grid canvas of unit_0208FF50.cpp (Unk02090308), shared with its users.
 * Layout from the code; all names are placeholders.
 */
#ifndef GAME_UNK_CANVAS_H
#define GAME_UNK_CANVAS_H

#include "game/unk_oam.h"
#include "game/unk_rect.h"
#include "game/unk_text.h"

/* va_list of the mwccarm runtime, as the variadic call site computes it. */
typedef char *va_list;

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

#endif
