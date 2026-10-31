/*
 * Unit 0x0201B648-0x0201B6D4: the treasure map microgame, an empty class on the
 * microgame base, named by its string "Treasure Map microgame", with a factory
 * called from the microgame switch at 0x020A5A38. All the behaviour is in the base.
 *
 * Bounds: hypothesis. The start is unit_0201B5BC.cpp, the end unit_0201B6D4.cpp;
 * `.data` holds the vtable and the name. Real file name unknown.
 */

#include "game/unk_microgame.h"

class Unk0201b648 : public Unk02013f8c {
public:
    Unk0201b648(Unk02093648 *file, int a, int b) : Unk02013f8c("Treasure Map microgame", 0xe68e9fde, file, a, b) {}
    ~Unk0201b648();
};

extern "C" Unk0201b648 *func_0201b648(Unk02093648 *file, int a, int b) {
    return new Unk0201b648(file, a, b);
}

Unk0201b648::~Unk0201b648() {}
