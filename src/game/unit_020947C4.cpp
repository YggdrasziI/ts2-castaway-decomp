/*
 * Unit 0x020947C4-0x02094824: a resource file class (Unk020947c4) derived from the
 * file class Unk0209487c, with three words of its own and no overrides. The file
 * factory at 0x02094598 creates it for type 13.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; the destructors close this one and 0x02094824 starts
 * unit_02094824.cpp. The vtable data_020bd31c is only used by the constructor. Real
 * file name unknown.
 */

#include "game/unk_file.h"

class Unk020947c4 : public Unk0209487c {
public:
    Unk020947c4(void *data);
    ~Unk020947c4();

    int unk3c;
    int unk40;
    int unk44;
};

Unk020947c4::Unk020947c4(void *data) : Unk0209487c(data) {
    unk3c = 0;
    unk40 = 0;
    unk44 = 0;
}

Unk020947c4::~Unk020947c4() {}
