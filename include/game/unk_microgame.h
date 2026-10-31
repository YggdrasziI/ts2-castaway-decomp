#ifndef GAME_UNK_MICROGAME_H
#define GAME_UNK_MICROGAME_H

#include "game/unk_archive.h"
#include "game/unk_screen.h"

/* Base of the game mode classes, constructor 0x020A5CCC. */
class Unk020a5ccc {
public:
    Unk020a5ccc(Unk02093648 *file, int a, int b);
    virtual ~Unk020a5ccc();
    virtual bool func_08();
    virtual void func_0c();

    void func_020a5ea4(Unk020a9d58 *layout);

    Unk02093648 *file;
    u8 unk8[0x30];
};

/* Microgame base, 0xBC bytes, constructor 0x02013F8C. */
class Unk02013f8c : public Unk020a5ccc {
public:
    Unk02013f8c(const char *name, u32 hash, Unk02093648 *file, int a, int b);
    virtual ~Unk02013f8c();
    virtual void func_10(bool a);
    virtual void func_14();
    virtual bool func_18();
    virtual void func_1c();

    Unk020a9d58 layout;
    int timer;
    const char *name;
};

#endif
