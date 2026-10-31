/*
 * Unit 0x0201B5BC-0x0201B648: the telescope microgame, an empty class on the
 * microgame base, named by its string "Telescope microgame", with a factory called
 * from the microgame switch at 0x020A5A60. All the behaviour is in the base.
 *
 * Bounds: hypothesis. The start follows the destructor of the class with vtable
 * 0x020B8788; the end is unit_0201B648.cpp, the vtable and name of each class being
 * laid out one after the other in `.data`. Real file name unknown.
 */

#include "game/unk_microgame.h"

class Unk0201b5bc : public Unk02013f8c {
public:
    Unk0201b5bc(Unk02093648 *file, int a, int b) : Unk02013f8c("Telescope microgame", 0x40daa67d, file, a, b) {}
    ~Unk0201b5bc();
};

extern "C" Unk0201b5bc *func_0201b5bc(Unk02093648 *file, int a, int b) {
    return new Unk0201b5bc(file, a, b);
}

Unk0201b5bc::~Unk0201b5bc() {}
