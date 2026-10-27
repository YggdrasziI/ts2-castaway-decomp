/*
 * A played animation of unit_02063CD0.cpp (Unk02063d84, 8 bytes): its sampler
 * and the optional sound player bound to it. All names are placeholders.
 */
#ifndef GAME_UNK_ANIMINST_H
#define GAME_UNK_ANIMINST_H

#include "game/unk_anim.h"

class Unk020a3d2c;
class Unk020a3a44;

class Unk02063d84 {
public:
    Unk02063d84(Unk02093544 *file, Unk020a3a44 *bank);
    ~Unk02063d84();

    Unk020a3d2c *unk0;
    Unk020897c0 *anim;
};

#endif
