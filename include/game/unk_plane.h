/*
 * Plane of unit_020987D8.cpp (normal and distance, 20.12 fixed point), used by
 * the units around it. All names are placeholders.
 */
#ifndef GAME_UNK_PLANE_H
#define GAME_UNK_PLANE_H

#include "game/unk_vector.h"

class Unk020987d8 {
public:
    Unk020987d8();
    Unk020987d8(const Unk02098ff0 &normal, const Unk02098ff0 &point);
    Unk02098ff0 func_02098824(const Unk02098ff0 &origin, const Unk02098ff0 &dir) const;
    int func_020988c0(const Unk02098ff0 &point) const;

    Unk02098ff0 normal;
    int d;
};

#endif
