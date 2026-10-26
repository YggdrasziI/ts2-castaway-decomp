/*
 * Unit 0x020897C0-0x020899A4: an animation (Unk020897c0, 0x4C bytes) read from a
 * resource file (Unk02093544): it keeps the file and two words of its header
 * block 0x13, the blocks 0x14 to 0x16, a frame rate derived from the third
 * header word, and a copy of the 12-byte records of block 0x14 allocated on its
 * heap. Its ITCM functions (unit_01FF84D0.cpp) sample and advance it.
 *
 * Bounds: hypothesis. 0x020897B4 before is an empty variadic function called from
 * everywhere; the class starts with its constructor. It ends with the empty
 * constructor of the 0x28-byte elements that the ITCM function passes to
 * __cxa_vec_new, defined out of line here; 0x020899A4 starts unit_020899A4.cpp.
 * No data. Real file name unknown.
 */

#include "game/unk_file.h"
#include "game/unk_anim.h"

class Unk02093544 : public Unk0209487c {
public:
    void *func_02093578();
    void *func_020935a0();
    void *func_020935c8();
    void *func_020935f0();

    void *block13;
    void *block14;
    void *block15;
    void *block16;
};

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
}

Unk020897c0::Unk020897c0(Unk02093544 *file, int heap)
    : file(0), unk04(0), unk08(0), unk0c(0), unk10(0), unk14(0), unk18(0), unk1c(0), unk20(0), unk24(0),
      unk28(0), unk2c(0), unk30(0), unk32(0), heap(heap), unk44(0), unk48(0) {
    func_02089874(file);
}

Unk020897c0::~Unk020897c0() {
    if (unk44 != 0) {
        delete[] unk44;
    }
    unk44 = 0;
    if (unk48 != 0) {
        delete[] unk48;
    }
    unk48 = 0;
    if (file != 0) {
        file->func_02094fb8();
        file = 0;
    }
}

void Unk020897c0::func_02089874(Unk02093544 *file) {
    if (!file->func_02094d18()) {
        file = 0;
    }
    this->file = file;
    unk04 = 0;
    if (this->file == 0) {
        return;
    }
    this->file->func_02094f9c();
    unk18 = ((int *)this->file->func_02093578())[0];
    unk1c = ((int *)this->file->func_02093578())[1];
    unk38 = (Unk020897c0Track *)this->file->func_020935a0();
    unk3c = (Unk020897c0RotKey *)this->file->func_020935c8();
    unk40 = (Unk020897c0VecKey *)this->file->func_020935f0();
    unk28 = func_02077c60(((int *)this->file->func_02093578())[2] << 12, 0x3c000);
    unk0c = 0;
    unk10 = unk18;
    func_02099afc(heap);
    unk48 = new Unk020897c0Track[unk1c];
    func_02099b28();
    for (int i = 0; i < unk1c; i++) {
        unk48[i] = unk38[i];
    }
}

int Unk020897c0::func_02089998() {
    return unk24;
}

Unk020897c0Elem::Unk020897c0Elem() {}
