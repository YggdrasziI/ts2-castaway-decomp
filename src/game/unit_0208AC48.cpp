/*
 * Unit 0x0208AC48-0x0208ADC0: the functions of the 0x40-byte pool object
 * (Unk0208b554Item, include/game/unk_poolitem.h). An object takes a key, loads the
 * model from the library object pointed to by data_020c7d24 on first use (flag 1),
 * copies the model's second element set and, while flag 2 is set, keeps it
 * registered with the ITCM functions func_01ff97bc / func_01ff9838.
 *
 * Bounds: hypothesis. Before 0x0208AC48 lies the library code (0x0208A1F8...) that
 * ends with the inline element constructor func_0208ac30 and owns the setter of
 * data_020c7d24 (func_0208ab3c); 0x0208ADC0 starts unit_0208ADC0.cpp. No data.
 * Real file name unknown.
 */

#include "game/unk_poolitem.h"
#include "game/unk_model.h"

class Unk0208a0a8 {
public:
    Unk02089f38 *func_0208a4c8(int key);
};

extern "C" {
void func_01ff9624(Unk0208adc0 *set);
void func_01ff97bc(Unk0208adc0 *set);
void func_01ff9838(Unk0208adc0 *set);
}

extern Unk0208a0a8 *data_020c7d24;

void Unk0208b554Item::func_0208ac48(int key) {
    flags |= 1;
    this->key = key;
    func_0208ad80();
}

Unk02089f38 *Unk0208b554Item::func_0208ac64() {
    if (flags & 1) {
        model = data_020c7d24->func_0208a4c8(key);
        if (model != 0) {
            model->func_0208a084();
            set.func_0208af70(*model->func_0208a050());
            if (flags & 2) {
                bool skip = false;
                if ((set.flags & 2) && !(set.flags & 4)) {
                    skip = true;
                }
                if (!skip) {
                    func_01ff9624(&set);
                }
                func_01ff97bc(&set);
            }
        } else {
            flags &= ~2;
        }
    }
    if (model != 0) {
        flags &= ~1;
    }
    return model;
}

Unk0208adc0 *Unk0208b554Item::func_0208ad18() {
    if (flags & 1) {
        func_0208ac64();
    }
    return &set;
}

void Unk0208b554Item::func_0208ad38(int value) {
    unk38 = value;
}

void Unk0208b554Item::func_0208ad40() {
    func_01ff97bc(&set);
    flags |= 2;
}

void Unk0208b554Item::func_0208ad60() {
    func_01ff9838(&set);
    flags &= ~2;
}

void Unk0208b554Item::func_0208ad80() {
    if (model != 0) {
        model->func_0208a094();
        model = 0;
    }
    if (flags & 2) {
        func_01ff9838(&set);
    }
    set.func_0208b020();
}
