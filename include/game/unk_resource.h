/*
 * Resource file class of unit_02095140.cpp, shared by the units that read its
 * blocks (object entry, object grid canvas, object manager, ...). Layouts come from
 * the code; all names are placeholders.
 */
#ifndef GAME_UNK_RESOURCE_H
#define GAME_UNK_RESOURCE_H

#include "game/unk_file.h"

/* Block 0x20: size in 8 x 8 tiles, entry count, palette and bits per pixel. */
struct Unk02095140Header {
    int width;
    int height;
    int count;
    int unkC;
    u8 bpp;
};

/* One 8-byte entry of the blocks 0x24, 0x25 and 0x26. */
struct Unk02095140Entry {
    u32 size;
    u32 offset;
};

class Unk02095140 : public Unk0209487c {
public:
    Unk02095140(void *data);
    ~Unk02095140();
    Unk02095140Header *func_02095180();
    bool func_020951a8(int index);
    u8 *func_020951e4(int index);
    u32 func_02095244(int index);
    Unk02095140Entry *func_0209526c(int index);
    u8 *func_020952b0(int index);
    Unk02095140Entry *func_02095310(int index);
    u8 *func_02095354(int index);
    Unk02095140Entry *func_020953b4(int index);

    Unk02095140Header *header;
    u8 *block22;
    u8 *block21;
    u8 *block23;
    Unk02095140Entry *block24;
    Unk02095140Entry *block25;
    Unk02095140Entry *block26;
};

#endif
