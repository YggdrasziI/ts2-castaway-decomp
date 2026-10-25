/*
 * Unit 0x02095B88-0x02095BF4: a resource file class (Unk02095b88) derived from the
 * file class Unk0209487c, with six words of its own and no other member function.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; 0x02095BF4 starts unit_02095BF4.cpp. The vtable data_020bd454 is
 * only used by the constructor. Real file name unknown.
 */

#include "game/unk_file.h"

class Unk02095b88 : public Unk0209487c {
public:
    Unk02095b88(void *data);
    ~Unk02095b88();

    int unk3c[6];
};

Unk02095b88::Unk02095b88(void *data) : Unk0209487c(data) {
    unk3c[0] = 0;
    unk3c[1] = 0;
    unk3c[2] = 0;
    unk3c[3] = 0;
    unk3c[4] = 0;
    unk3c[5] = 0;
}

Unk02095b88::~Unk02095b88() {}
