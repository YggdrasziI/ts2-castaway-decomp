/*
 * Quaternion of unit_020988D8.cpp (x, y, z, w in 20.12 fixed point). Layout from
 * the code; all names are placeholders.
 */
#ifndef GAME_UNK_QUAT_H
#define GAME_UNK_QUAT_H

class Unk02097b6c;

class Unk020988d8 {
public:
    Unk020988d8() {}
    Unk020988d8(int x, int y, int z, int w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    void func_020988d8();
    int func_020988f4() const;
    Unk02097b6c func_02098934() const;
    Unk020988d8 func_02098a5c(const Unk020988d8 &o, int t) const;

    int x;
    int y;
    int z;
    int w;
};

#endif
