/*
 * Classes of unit_0208ADC0.cpp: a 0x24-byte element (Unk0208af38) holding three
 * packed words and four s16, and a set of such elements (Unk0208adc0) with a scale
 * vector. The packed words look like the GX DIF_AMB, SPE_EMI and POLYGON_ATTR
 * registers (two 15-bit colours each in the first two, bits 16-20 and 24-29 of the
 * third written by func_0208b278 / func_0208b25c): a hypothesis, the names stay
 * placeholders.
 */
#ifndef GAME_UNK_MATSET_H
#define GAME_UNK_MATSET_H

#include "game/unk_vector.h"

typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short s16;

class Unk020bd014;

/* One element (0x24 bytes). */
struct Unk0208af38 {
    Unk0208af38() {
        unk0 = 0;
        unk4 = 0;
        unk8 = 0;
        unk0c = 0;
        unk10 = 0;
        unk14 = 0;
        unk18 = 0;
        unk1c = 0;
        unk1e = 0;
        unk20 = 0x1000;
        unk22 = 0x1000;
    }
    void func_0208b25c(u32 value);
    void func_0208b278(u32 value);
    void func_0208b294(const s16 *rgb);
    void func_0208b308(const s16 *rgb);
    void func_0208b378(const s16 *rgb);
    void func_0208b3ec(int value);
    void func_0208b3f4(s16 a, s16 b);
    void func_0208b400(s16 a, s16 b);

    u32 unk0;
    u32 unk4;
    u32 unk8;
    int unk0c;
    int unk10;
    int unk14;
    int unk18;
    s16 unk1c;
    s16 unk1e;
    s16 unk20;
    s16 unk22;
};

/* The scale of a set; the wrapper makes its copies block copies (ldm / stm). */
struct Unk0208adc0Scale {
    Unk0208adc0Scale() {}
    Unk0208adc0Scale(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

/* A set of elements (0x18 bytes). */
class Unk0208adc0 {
public:
    Unk0208adc0();
    ~Unk0208adc0();
    void func_0208adf8(Unk020bd014 *src);
    void func_0208af70(const Unk0208adc0 &o);
    void func_0208b020();
    int func_0208b058();
    bool func_0208b060(int id);
    int func_0208b09c(int index);
    Unk0208af38 func_0208b0cc(int id);
    Unk0208af38 func_0208b190(int index);
    void func_0208b248(Unk0208af38 *e);
    static void func_0208b40c(int heap);

    Unk0208adc0Scale scale;
    int count;
    Unk0208af38 *elems;
    u32 flags;
};

#endif
