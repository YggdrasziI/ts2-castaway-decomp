#ifndef GAME_UNK_MICROGAME_H
#define GAME_UNK_MICROGAME_H

#include "game/unk_archive.h"

/* Base of the game mode classes, constructor 0x020A5CCC. */
class Unk020a5ccc {
public:
    virtual ~Unk020a5ccc();
    virtual void func_08();
    virtual void func_0c();
};

/* Microgame base, 0xBC bytes, constructor 0x02013F8C. */
class Unk02013f8c : public Unk020a5ccc {
public:
    Unk02013f8c(const char *name, u32 hash, Unk02093648 *file, int a, int b);
    virtual ~Unk02013f8c();
    virtual void func_10(int a);
    virtual void func_14();
    virtual bool func_18();
    virtual void func_1c();

    u8 unk4[0xb8];
};

#endif
