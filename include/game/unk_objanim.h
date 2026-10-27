/*
 * The object animation archive holder of unit_02064224.cpp (Unk020c4390, one
 * static object data_020c4390) and its interface. All names are placeholders.
 */
#ifndef GAME_UNK_OBJANIM_H
#define GAME_UNK_OBJANIM_H

#include "game/unk_archive.h"

/* Interface of five functions (the zero vtable copy at 0x020BC5C4). */
class Unk020c4390Base {
public:
    virtual void func_00() = 0;
    virtual void func_04(int id) = 0;
    virtual void func_08() = 0;
    virtual void func_0c() = 0;
    virtual int func_10() = 0;
};

class Unk020c4390 : public Unk020c4390Base {
public:
    Unk020c4390();
    ~Unk020c4390();
    virtual void func_00();
    virtual void func_04(int id);
    virtual void func_08();
    virtual void func_0c();
    virtual int func_10();

    u8 loaded;
    Unk02093648 *archive;
};

extern Unk020c4390 data_020c4390;

#endif
