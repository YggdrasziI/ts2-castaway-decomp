/*
 * Unit 0x02089F38-0x0208A0A8: the model (Unk02089f38, include/game/unk_model.h).
 * It is built from a resource file seen through the interface Unk020bd014: it
 * keeps the file, its data block and size, two words of the header block and two
 * element sets read from the file; the library of unit_0208A0A8.cpp counts its
 * references.
 *
 * Bounds: hypothesis. Before 0x02089F38, func_02089d48 belongs to other code;
 * 0x0208A0A8 starts the library (its constructor). No data. Real file name
 * unknown.
 */

#include "game/unk_model.h"

Unk02089f38::Unk02089f38(Unk020bd014 *file)
    : file(0), data(0), size(0), unk0c(0), refs(0), unk14(0x1000), unk18(0x1000), unk1c(0) {
    func_02089fb4(file);
}

Unk02089f38::~Unk02089f38() {
    func_0208a058();
}

void Unk02089f38::func_02089fb4(Unk020bd014 *file) {
    if (file == 0) {
        return;
    }
    if (this->file != 0) {
        func_0208a058();
    }
    Unk0209543cBlockB *header = file->func_0209548c();
    this->file = file;
    data = file->func_020954b4();
    size = file->func_020954dc();
    if (header != 0) {
        unk14 = header->unk24;
        unk18 = header->unk28;
    }
    setA.func_0208adf8(file);
    setB.func_0208adf8(file);
}

Unk0208adc0 *Unk02089f38::func_0208a048() {
    return &setA;
}

Unk0208adc0 *Unk02089f38::func_0208a050() {
    return &setB;
}

void Unk02089f38::func_0208a058() {
    setA.func_0208b020();
    setB.func_0208b020();
    file = 0;
    data = 0;
    size = 0;
}

void Unk02089f38::func_0208a084() {
    refs++;
}

void Unk02089f38::func_0208a094() {
    if (refs > 0) {
        refs--;
    }
}
