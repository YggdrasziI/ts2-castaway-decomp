/*
 * Camera controller of unit_02069EA8.cpp (Unk02069fec, 0x10C bytes), a member of
 * the game states. It drives the pool camera (data_020c7d38 + 0x54) either from
 * the buttons (mode 0) or by following a point kept inside four planes (mode 1),
 * and blends the field of view. Layout from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_CAMCTL_H
#define GAME_UNK_CAMCTL_H

#include "game/unk_camera.h"
#include "game/unk_plane.h"

class Unk02069fec {
public:
    Unk02069fec();

    Unk02098ff0 pos;
    Unk020899a4Angles angles;
    Unk02098ff0 target;
    Unk020899a4Angles saved;
    int unk30[3];
    unsigned short mode;
    unsigned short flags;
    unsigned short state;
    Unk02098e70 rangeX;
    Unk02098e70 rangeZ;
    int eyeA[2];
    int targetA[2];
    int eyeB[2];
    int targetB[2];
    int fovA;
    int fovB;
    int unk7c;
    int unk80;
    int unk84;
    int timer;
    Unk02098e70 focus;
    Unk02098e70 goal;
    Unk020987d8 planes[4];
    Unk02098e70 center;
    Unk02098e70 half;
    int unkec;
    int fov;
    int fovFrom;
    int fovTo;
    int fovT;
    int unk100;
    int fovMax;
    int fovMin;
};

#endif
