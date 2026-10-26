/*
 * Transform set of unit_0208BE3C.cpp (Unk0208be3c): one entry per item (position,
 * rotation quaternion and 4x4 matrix) and one more 4x4 matrix per item, read
 * from a resource file (Unk02095d1c). Layout from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_XFORM_H
#define GAME_UNK_XFORM_H

#include "game/unk_matrix.h"
#include "game/unk_quat.h"

typedef unsigned short u16;

class Unk02095d1c;

/* One matrix of the second array (0x40 bytes). */
struct Unk0208be3cMtx {
    Unk0208be3cMtx() {}

    Unk02098094 m;
};

/*
 * The position wraps the vector: the implicit assignment of the wrapper copies it
 * as a block (ldm / stm) from a stack temporary, as in the original.
 */
struct Unk0208be3cPos {
    Unk0208be3cPos() {}
    Unk0208be3cPos(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

/* One transform (0x5C bytes). */
struct Unk0208be3cEntry {
    Unk0208be3cEntry() {}

    Unk0208be3cPos pos;
    Unk020988d8 rot;
    Unk02098094 mtx;
};

class Unk0208be3c {
public:
    Unk0208be3c(Unk02095d1c *file, u16 heap);
    ~Unk0208be3c();
    void func_0208befc();
    int func_0208c040();
    Unk0208be3cMtx *func_0208c048();

    Unk0208be3cEntry *entries;
    Unk0208be3cMtx *mtxs;
    Unk02095d1c *file;
    int count;
    u16 unk10;
    u16 heap;
};

#endif
