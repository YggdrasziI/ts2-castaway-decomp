/*
 * The animation of unit_020897C0.cpp (main) and unit_01FF84D0.cpp (ITCM): per
 * track, a rotation key list (12-byte keys: frame and four s16) and two vector
 * key lists (16-byte keys: frame and a vector) read from a resource file, and an
 * array of sampled values (Unk020897c0Elem). Layout from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_ANIM_H
#define GAME_UNK_ANIM_H

#include "game/unk_vector.h"
#include "game/unk_quat.h"

typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;

class Unk02093544;

/* The key indices of one track (rotation, first vector, second vector). */
struct Unk020897c0Track {
    u32 rot;
    u32 pos;
    u32 scale;
};

/* A rotation key (12 bytes). */
struct Unk020897c0RotKey {
    u32 frame;
    s16 x;
    s16 y;
    s16 z;
    s16 w;
};

/* A vector key (16 bytes). */
struct Unk020897c0VecKey {
    u32 frame;
    Unk02098ff0 value;
};

/* A sampled vector; the wrapper makes its assignments block copies (ldm / stm). */
struct Unk020897c0Vec {
    Unk02098ff0 v;
};

/* The sampled values of one track (0x28 bytes). */
struct Unk020897c0Elem {
    Unk020897c0Elem();

    void setPos(const Unk02098ff0 &v) {
        pos = (const Unk020897c0Vec &)v;
    }
    void setScale(const Unk02098ff0 &v) {
        scale = (const Unk020897c0Vec &)v;
    }

    Unk020988d8 rot;
    Unk020897c0Vec pos;
    Unk020897c0Vec scale;
};

class Unk020897c0 {
public:
    Unk020897c0(Unk02093544 *file, int heap);
    ~Unk020897c0();
    void func_02089874(Unk02093544 *file);
    int func_02089998();
    void func_01ff84d0(u32 frame, int t);
    void func_01ff84f0(u32 frame, u32 next, int t);
    Unk020897c0Elem *func_01ff8a4c();
    int func_01ff8a60();
    int func_01ff8a68();
    void func_01ff8a70(u16 mode);
    u16 func_01ff8a78();
    void func_01ff8a80();
    bool func_01ff8a8c();
    bool func_01ff8aa0();
    void func_01ff8ab4(int dt, int hold);

    Unk02093544 *file;
    int unk04;
    int unk08;
    int unk0c;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    int unk24;
    int unk28;
    int unk2c;
    u16 unk30;
    u16 unk32;
    int heap;
    Unk020897c0Track *unk38;
    Unk020897c0RotKey *unk3c;
    Unk020897c0VecKey *unk40;
    Unk020897c0Elem *unk44;
    Unk020897c0Track *unk48;
};

#endif
