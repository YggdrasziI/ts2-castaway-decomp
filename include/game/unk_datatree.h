/*
 * Data tree file of unit_02096348.cpp (Unk02096348) and its node handle
 * (Unk0209674c), shared by the units that read named values from it. Layouts come
 * from the code; all names are placeholders.
 */
#ifndef GAME_UNK_DATATREE_H
#define GAME_UNK_DATATREE_H

#include "game/unk_file.h"

struct Unk02096348Block40 {
    u32 count;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 nodeCount;
};

struct Unk02096348Entry {
    u32 hash;
    u32 offset : 24;
    u32 type : 8;
};

struct Unk02096348Record {
    u8 unk0[0x84];
    int count;
    int base;
};

struct Unk02096348Node {
    u32 hash;
    u32 children;
    u16 childCount;
    short entry;
};

class Unk0209674c;

class Unk02096348 : public Unk0209487c {
public:
    Unk02096348(void *data);
    ~Unk02096348();
    Unk02096348Block40 *func_0209638c();
    Unk02096348Entry *func_020963b4();
    Unk02096348Record *func_020963dc();
    Unk02096348Node *func_02096404();
    u32 func_0209642c();
    u32 func_02096444();
    int func_0209645c(const u32 *name, int sub);
    bool func_02096538(int index, u32 type);
    u8 *func_02096564(int index);
    int func_02096574(int index);
    int func_02096590(int index);
    int func_020965ac(int index);
    bool func_020965c8(int index);
    Unk02096348Entry *func_0209661c(int index);
    u8 *func_0209665c(int index, u32 type);
    Unk02096348Record *func_02096700(int index);
    Unk0209674c func_02096980();
    Unk02096348Node *func_020969b8(int index);
    int func_02096a00(int index, u32 n);

    Unk02096348Block40 *block40;
    Unk02096348Entry *block41;
    Unk02096348Record *block46;
    Unk02096348Node *block45;
    int lastIndex;
    u32 lastHash;
    u32 hashSeed;
};

class Unk0209674c {
public:
    Unk0209674c();
    Unk0209674c(Unk02096348 *file, Unk02096348Node *node, int index);
    Unk0209674c func_02096774(u32 n) const;
    int func_020967ec() const;
    u32 func_02096800() const;
    bool func_02096814(u32 hash) const;
    bool func_0209683c(const u32 *name) const;
    bool func_02096864() const;
    int func_0209688c() const;
    int func_020968a0() const;
    int func_020968d8() const;
    int func_02096910() const;
    bool func_02096948() const;

    int index;
    Unk02096348Node *node;
    Unk02096348 *file;
};

#endif
