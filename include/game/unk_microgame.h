#ifndef GAME_UNK_MICROGAME_H
#define GAME_UNK_MICROGAME_H

#include "game/unk_archive.h"
#include "game/unk_screen.h"

class Unk0205cf00;
class Unk02060d78;
class Unk020a5cccPlayer;

/* The screen of a game mode, 0x18 bytes, constructor 0x020A6588. */
class Unk020a6588 : public Unk020a07d4 {
public:
    Unk020a6588();
    virtual ~Unk020a6588();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual bool func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_34();
    virtual void func_38(int a);
    virtual bool func_3c();

    s16 unk4;
    s16 unk6;
    int unk8;
    int unkc;
    volatile u32 flags;
    int state;
};

/* Base of the game mode classes, constructor 0x020A5CCC. */
class Unk020a5ccc {
public:
    Unk020a5ccc(Unk02093648 *file, int a, int b);
    virtual ~Unk020a5ccc();
    virtual bool func_08();
    virtual const char *func_0c(u32 id);
    virtual void func_10(bool a) = 0;
    virtual void func_14() = 0;
    virtual bool func_18() = 0;
    virtual void func_1c() = 0;

    void func_020a5ea4(Unk020a9d58 *layout);

    Unk02093648 *file;
    Unk020a5cccPlayer *player;
    void *item;
    Unk020a6588 screen;
    volatile u32 flags;
    Unk0205cf00 *def;
    Unk0209487c *model;
    Unk02060d78 *entity;
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
