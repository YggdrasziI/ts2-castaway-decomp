/*
 * The object pool of unit_0208B554.cpp (Unk020c7d38, static object
 * data_020c7d38), its records and the bit set of unit_0209A11C.cpp it uses; the
 * pool's drawing functions are in ITCM (unit_01FF9924.cpp). All names are
 * placeholders.
 */
#ifndef GAME_UNK_POOL_H
#define GAME_UNK_POOL_H

#include "game/unk_matrix.h"
#include "game/unk_poolitem.h"

typedef unsigned short u16;
typedef unsigned long u32;

class Unk0208be3c;

class Unk0209a11c {
public:
    Unk0209a11c();
    Unk0209a11c(u32 size);
    ~Unk0209a11c();
    void func_0209a164();
    bool func_0209a188(u32 index);
    void func_0209a1c4(u32 index, bool value);
    void func_0209a27c(u32 start, u32 count, bool value);
    void func_0209a2c4(u32 word, u32 index);

    u32 *bits;
    u32 size;
};

/* A 0x84-byte record of the two record arrays. */
struct Unk0208b554Record {
    Unk02089f38 *model;
    Unk0208adc0 set;
    Unk02098094 mtx;
    Unk02097b6c rot;
    Unk0208be3c *xform;
};

/* A 0x30-byte record: a 3x3 matrix and a vector. */
struct Unk0208b554Frame {
    Unk0208b554Frame() {
        mtx = Unk02097b6c::func_02097bf8();
        pos.x = 0;
        pos.y = 0;
        pos.z = 0;
    }

    Unk02097b6c mtx;
    Unk02098ff0 pos;
};

/* A 0x14-byte record of the two rows: a vector and four u16. */
struct Unk0208b554Light {
    Unk0208b554Light() : dir(0, -0x1000, 0) {
        unk0c = 0xff;
        unk0e = 0xff;
        unk10 = 0xff;
        unk12 = 0xff;
    }

    void reset() {
        *this = Unk0208b554Light();
    }

    Unk02098ff0 dir;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    s16 unk12;
};

class Unk020c7d38 {
public:
    Unk020c7d38();
    ~Unk020c7d38();
    void func_0208b744();
    void func_0208b99c(u32 count, u32 size);
    void func_0208b9dc();
    int func_0208bbf4(int key);
    void func_0208bc68(int index, bool used);
    bool func_0208bcd0(int index);
    Unk0208b554Item *func_0208bcfc(int index);
    int func_0208bd20(Unk0208b554Item *item);
    void func_0208bd58(int index, u16 value);
    Unk0208b554Frame *func_0208be18(int index);
    void func_0208be28(int index, int value);

    void resetLights() {
        for (int i = 0; i < 4; i++) {
            lights[0][i].reset();
            lights[1][i].reset();
        }
    }

    int count;
    int unk4;
    int unk8;
    int capacity;
    u32 bufferWords;
    int recordCount;
    int frameCount;
    Unk0208b554Item *items;
    u16 *unk20;
    u16 *unk24;
    Unk0208b554Record *records[2];
    u32 *buffers[2];
    int *unk38;
    int *unk3c;
    int unk40;
    Unk0209a11c used;
    Unk0209a11c active;
    int unk54;
    int unk58;
    int unk5c;
    int unk60;
    int unk64;
    int unk68;
    int unk6c;
    int unk70;
    int unk74;
    int unk78;
    int unk7c;
    int unk80;
    int unk84[4];
    int unk94;
    int unk98[0x30];
    u16 flags;
    u16 unk15a;
    int heap;
    Unk0208b554Frame *frames;
    Unk0208b554Light lights[2][4];
};

extern Unk020c7d38 data_020c7d38;

#endif
