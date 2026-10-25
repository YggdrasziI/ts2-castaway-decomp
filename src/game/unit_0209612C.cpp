/*
 * Unit 0x0209612C-0x020962EC: a resource file class (Unk0209612c) derived from the
 * file class Unk0209487c. It reads block 0x800 (an element count and a second
 * value divided by 60), allocates one 20-byte element (Unk020962d0) per entry, and
 * overrides two virtual functions to set up and release them.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; 0x020962EC starts unit_020962EC.cpp. The vtable data_020bd50c is
 * only used by the constructor. Real file name unknown.
 */

#include "game/unk_file.h"

extern "C" int func_02077c60(int a, int b);

struct Unk0209612cBlock {
    int count;
    int unk4;
};

class Unk020962d0 {
public:
    Unk020962d0();

    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
};

class Unk0209612c : public Unk0209487c {
public:
    Unk0209612c(void *data);
    ~Unk0209612c();
    Unk0209612cBlock *func_020961b0();
    virtual bool func_02094df4();
    virtual void func_02094f0c();
    bool func_02096268();

    Unk0209612cBlock *block;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    int unk50;
    int unk54;
    int unk58;
    int count;
    Unk020962d0 *elements;
};

Unk0209612c::Unk0209612c(void *data) : Unk0209487c(data) {
    block = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    unk54 = 0;
    unk58 = 0;
    count = 0;
    elements = 0;
    func_02096268();
}

Unk0209612c::~Unk0209612c() {}

Unk0209612cBlock *Unk0209612c::func_020961b0() {
    if (block != 0) {
        return block;
    }
    block = (Unk0209612cBlock *)func_02094d4c(0x800);
    return block;
}

bool Unk0209612c::func_02094df4() {
    if (Unk0209487c::func_02094df4() && !func_02096268()) {
        Unk0209487c::func_02094f0c();
        return false;
    }
    return true;
}

void Unk0209612c::func_02094f0c() {
    block = 0;
    unk40 = 0;
    unk44 = 0;
    unk48 = 0;
    unk4c = 0;
    unk50 = 0;
    unk54 = 0;
    unk58 = 0;
    count = 0;
    if (elements != 0) {
        delete[] elements;
        elements = 0;
    }
    Unk0209487c::func_02094f0c();
}

bool Unk0209612c::func_02096268() {
    Unk0209612cBlock *b = func_020961b0();

    if (b == 0) {
        return false;
    }
    elements = new Unk020962d0[b->count];
    if (elements == 0) {
        block = 0;
        return false;
    }
    unk58 = func_02077c60(b->unk4, 0x3c);
    count = b->count;
    return true;
}

Unk020962d0::Unk020962d0() {
    unk0 = 0;
    unk4 = 0;
    unk8 = 0;
    unkC = 0;
    unk10 = 0;
}
