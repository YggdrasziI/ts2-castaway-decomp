/*
 * Class of unit_020899A4.cpp: a camera (0x104 bytes). It keeps a position, three
 * rotation angles, the clipNear / clipFar planes, an aspect ratio and the cosine and sine
 * of half the field of view, and builds from them a projection matrix, a view
 * matrix and its inverse. Layout from the code; all names are placeholders.
 */
#ifndef GAME_UNK_CAMERA_H
#define GAME_UNK_CAMERA_H

#include "game/unk_matrix.h"

/* The rotation angles; the wrapper makes their copies block copies (ldm / stm). */
struct Unk020899a4Angles {
    Unk020899a4Angles() {}
    Unk020899a4Angles(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

class Unk020899a4 {
public:
    void func_020899a4(const Unk02098ff0 &target, int roll);
    void func_02089b48(int angle);
    Unk02098094 func_02089ba4();
    Unk02098ff0 func_02089c1c(const Unk02098ff0 &v);
    Unk02098ff0 func_02089cac(int x, int y);
    void func_02089d48();

    Unk02098ff0 pos;
    Unk020899a4Angles angles;
    int clipNear;
    int clipFar;
    int aspect;
    int cos;
    int sin;
    int fov;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    unsigned long flags;
    Unk02098094 proj;
    Unk02098094 view;
    Unk02098094 inverse;
};

#endif
