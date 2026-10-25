/*
 * Unit 0x02093544-0x02093648: a resource file class (Unk02093544) derived from the
 * file class Unk0209487c. It caches the blocks 0x13 to 0x16. The file factory at
 * 0x02094598 creates it for type 3.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; the destructors close this one and 0x02093648 starts the
 * constructor of another file class. The vtable data_020bd2bc is only used by the
 * constructor. Real file name unknown.
 */

#include "game/unk_file.h"

class Unk02093544 : public Unk0209487c {
public:
    Unk02093544(void *data);
    ~Unk02093544();
    void *func_02093578();
    void *func_020935a0();
    void *func_020935c8();
    void *func_020935f0();

    void *block13;
    void *block14;
    void *block15;
    void *block16;
};

Unk02093544::Unk02093544(void *data) : Unk0209487c(data) {
    block13 = 0;
    block14 = 0;
    block15 = 0;
    block16 = 0;
}

void *Unk02093544::func_02093578() {
    if (block13 != 0) {
        return block13;
    }
    block13 = func_02094d4c(0x13);
    return block13;
}

void *Unk02093544::func_020935a0() {
    if (block14 != 0) {
        return block14;
    }
    block14 = func_02094d4c(0x14);
    return block14;
}

void *Unk02093544::func_020935c8() {
    if (block15 != 0) {
        return block15;
    }
    block15 = func_02094d4c(0x15);
    return block15;
}

void *Unk02093544::func_020935f0() {
    if (block16 != 0) {
        return block16;
    }
    block16 = func_02094d4c(0x16);
    return block16;
}

Unk02093544::~Unk02093544() {}
