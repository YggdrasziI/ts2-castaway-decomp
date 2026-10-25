/*
 * Unit 0x02095FDC-0x0209612C: a resource file class (Unk02095fdc) derived from the
 * file class Unk0209487c. It caches the blocks 1, 2 and 3 and the size of block
 * 2, and keeps flags (bit 0: block 3 looked up, bit 1: block 3 found).
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; the destructors close this one and 0x0209612C starts
 * unit_0209612C.cpp. The vtable data_020bd4ec is only used by the constructor. Real
 * file name unknown.
 */

#include "game/unk_file.h"

struct Unk02095fdcBlock1 {
    int unk0;
    int unk4;
};

class Unk02095fdc : public Unk0209487c {
public:
    Unk02095fdc(void *data);
    ~Unk02095fdc();
    Unk02095fdcBlock1 *func_02096014();
    void *func_0209603c();
    u32 func_02096064();
    void *func_0209608c();
    int func_020960d4();

    Unk02095fdcBlock1 *block1;
    void *block3;
    void *block2;
    u32 block2Size;
    u32 flags;
};

Unk02095fdc::Unk02095fdc(void *data) : Unk0209487c(data) {
    block1 = 0;
    block3 = 0;
    block2 = 0;
    block2Size = 0;
    flags = 0;
}

Unk02095fdcBlock1 *Unk02095fdc::func_02096014() {
    if (block1 != 0) {
        return block1;
    }
    block1 = (Unk02095fdcBlock1 *)func_02094d4c(1);
    return block1;
}

void *Unk02095fdc::func_0209603c() {
    if (block2 != 0) {
        return block2;
    }
    block2 = func_02094d4c(2);
    return block2;
}

u32 Unk02095fdc::func_02096064() {
    if (block2Size != 0) {
        return block2Size;
    }
    block2Size = func_02094ddc(2);
    return block2Size;
}

void *Unk02095fdc::func_0209608c() {
    if (block3 != 0) {
        return block3;
    }
    block3 = func_02094d4c(3);
    if (block3 != 0) {
        flags |= 2;
    }
    flags |= 1;
    return block3;
}

int Unk02095fdc::func_020960d4() {
    if (func_02096014() == 0) {
        return 0;
    }
    return func_02096014()->unk4;
}

Unk02095fdc::~Unk02095fdc() {}
