/*
 * 20.12 fixed-point 3x3 matrix of unit_02097B6C.cpp. The constructor takes the
 * elements row by row and stores them column by column (m[column][row]). Layout
 * from the code; all names are placeholders.
 */
#ifndef GAME_UNK_MATRIX_H
#define GAME_UNK_MATRIX_H

#include "game/unk_vector.h"

class Unk02097bacSrc;

class Unk02097b6c {
public:
    Unk02097b6c() {}
    Unk02097b6c(int m00, int m01, int m02, int m10, int m11, int m12, int m20, int m21, int m22);
    Unk02097b6c(const Unk02097bacSrc &o);
    static Unk02097b6c func_02097bf8();
    static Unk02097b6c func_02097c2c(const Unk02098ff0 &scale);
    void func_02097c6c(const Unk02097b6c &a, const Unk02097b6c &b);
    Unk02097b6c func_02097cec() const;
    Unk02098ff0 func_02097d38(const Unk02098ff0 &v) const;
    static Unk02097b6c func_02097df8(int angle);
    static Unk02097b6c func_02097e5c(int angle);
    static Unk02097b6c func_02097ebc(int angle);
    static Unk02097b6c func_02097f1c(int z, int y, int x);
    static Unk02097b6c func_02097f78(int a, int b, int c);

    int m[3][3];
};

/* Source of the conversion func_02097bac: a matrix with rows of four words; only
 * its layout is known. */
class Unk02097bacSrc {
public:
    int m[4][4];
};

#endif
