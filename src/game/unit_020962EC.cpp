/*
 * Unit 0x020962EC-0x02096348: a resource file class (Unk020962ec) derived from the
 * file class Unk0209487c, with two words of its own and no other member function.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; 0x02096348 starts unit_02096348.cpp. The vtable data_020bd52c is
 * only used by the constructor. Real file name unknown.
 */

#include "game/unk_file.h"

class Unk020962ec : public Unk0209487c {
public:
    Unk020962ec(void *data);
    ~Unk020962ec();

    int unk3c;
    int unk40;
};

Unk020962ec::Unk020962ec(void *data) : Unk0209487c(data) {
    unk3c = 0;
    unk40 = 0;
}

Unk020962ec::~Unk020962ec() {}
