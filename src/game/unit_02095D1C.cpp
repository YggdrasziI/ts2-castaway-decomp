/*
 * Unit 0x02095D1C-0x02095DF0: a resource file class (Unk02095d1c) derived from the
 * file class Unk0209487c. It caches the blocks 0x11 (count first) and 0x12.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; the destructors close this one and 0x02095DF0 starts
 * unit_02095DF0.cpp. The vtable data_020bd4ac is only used by the constructor. Real
 * file name unknown.
 */

#include "game/unk_file.h"

struct Unk02095d1cHeader {
    int count;
};

class Unk02095d1c : public Unk0209487c {
public:
    Unk02095d1c(void *data);
    ~Unk02095d1c();
    Unk02095d1cHeader *func_02095d48();
    int func_02095d70();
    void *func_02095d98();

    Unk02095d1cHeader *header;
    void *block12;
};

Unk02095d1c::Unk02095d1c(void *data) : Unk0209487c(data) {
    header = 0;
    block12 = 0;
}

Unk02095d1cHeader *Unk02095d1c::func_02095d48() {
    if (header != 0) {
        return header;
    }
    header = (Unk02095d1cHeader *)func_02094d4c(0x11);
    return header;
}

int Unk02095d1c::func_02095d70() {
    if (func_02095d48() == 0) {
        return 0;
    }
    return func_02095d48()->count;
}

void *Unk02095d1c::func_02095d98() {
    if (block12 != 0) {
        return block12;
    }
    block12 = func_02094d4c(0x12);
    return block12;
}

Unk02095d1c::~Unk02095d1c() {}
