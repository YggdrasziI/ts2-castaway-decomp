/*
 * Model of unit_02089F38.cpp (Unk02089f38, 0x50 bytes): a resource file seen
 * through the interface Unk020bd014, its data block and size, a transform set
 * (unit_0208BE3C.cpp), two words of its header block, a reference count and two
 * element sets built from the file. All names are placeholders.
 */
#ifndef GAME_UNK_MODEL_H
#define GAME_UNK_MODEL_H

#include "game/unk_blocks.h"
#include "game/unk_matset.h"

class Unk0208be3c;

class Unk02089f38 {
public:
    Unk02089f38(Unk020bd014 *file);
    ~Unk02089f38();
    void func_02089fb4(Unk020bd014 *file);
    Unk0208adc0 *func_0208a048();
    Unk0208adc0 *func_0208a050();
    void func_0208a058();
    void func_0208a084();
    void func_0208a094();

    Unk020bd014 *file;
    void *data;
    u32 size;
    Unk0208be3c *xform;
    int refs;
    int unk14;
    int unk18;
    int unk1c;
    Unk0208adc0 setA;
    Unk0208adc0 setB;
};

#endif
