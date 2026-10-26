/*
 * Palette set of unit_0206FAC8.cpp (Unk0206fac8), shared with the ITCM upload
 * function of unit_01FF8000.cpp. It keeps the palettes of the textures in use
 * (include/game/unk_texture.h) in two buffers of 256-colour slots, the original
 * colours and a copy tinted with one of its tint colours, and uploads them.
 * Layout from the code; all names are placeholders.
 */
#ifndef GAME_UNK_PALSET_H
#define GAME_UNK_PALSET_H

#include "game/unk_texture.h"

class Unk02089f38;

/* One texture palette in the set (0x14 bytes). */
struct Unk0206fac8Record {
    Unk0208c050 *tex;
    int key;
    int refs;
    u16 start;
    u16 count;
    u32 flags;
};

class Unk0206fac8 {
public:
    Unk0206fac8(u32 capacity, const u8 *colors, u32 colorCount);
    ~Unk0206fac8();
    void func_0206fd2c(Unk02095fdc *file);
    void func_0206fe30(int id);
    void func_0206fea8(Unk02089f38 *model);
    void func_0206ff5c(Unk02089f38 *model);
    void func_02070010(u8 write);
    void func_0207001c(u8 useTinted);
    void func_02070048();
    void func_0207005c();
    void func_02070114(Unk0208c050 *tex, int key);
    void func_0207024c(Unk0208c050 *tex, int key);
    void func_02070318(u32 start, int count);
    void func_020705c0(Unk0206fac8Record *r);

    u16 *colors;
    u16 *tinted;
    u8 *slotUsed;
    int *tints;
    Unk0206fac8Record *records;
    u32 recordCount;
    u32 capacity;
    u32 tintCount;
    int pending;
    int tintShown;
    int tint;
    u8 useTinted;
    u8 write;
};

#endif
