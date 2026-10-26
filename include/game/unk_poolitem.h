/*
 * The 0x40-byte object of the pool of unit_0208B554.cpp (Unk0208b554Item), whose
 * functions are in unit_0208AC48.cpp: it loads a model from the library object
 * data_020c7d24 by the key at 0x18, keeps it at 0x1C and copies its second element
 * set into its own set at 0x20. All names are placeholders.
 */
#ifndef GAME_UNK_POOLITEM_H
#define GAME_UNK_POOLITEM_H

#include "game/unk_matset.h"

class Unk02089f38;

struct Unk0208b554Item {
    Unk0208b554Item()
        : unk0(0), unk4(0), unk8(0), unk0c(0), unk10(0), unk14(0), key(0), model(0), unk38(0), flags(0),
          index(-1) {}
    ~Unk0208b554Item() {
        func_0208ad80();
    }
    void func_0208ac48(int key);
    Unk02089f38 *func_0208ac64();
    Unk0208adc0 *func_0208ad18();
    void func_0208ad38(int value);
    void func_0208ad40();
    void func_0208ad60();
    void func_0208ad80();

    int unk0;
    int unk4;
    int unk8;
    int unk0c;
    int unk10;
    int unk14;
    int key;
    Unk02089f38 *model;
    Unk0208adc0 set;
    int unk38;
    u16 flags;
    short index;
};

#endif
