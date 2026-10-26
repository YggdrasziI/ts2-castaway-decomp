/*
 * Unit 0x0209543C-0x020956F8: a resource file class (Unk0209543c) derived from the
 * file class Unk0209487c and from an abstract interface (Unk020bd014, eleven pure
 * virtual functions, vtable data_020bd014). It caches the blocks 0x0B, 0x0C, 0x0E,
 * 0x10 and 0x64 and reads three words of block 0x0B. The last two interface
 * functions, which add and drop a reference on the file, are defined in
 * unit_0208A0A8.cpp (0x0208A1EC and 0x0208AA84). The interface is shared in
 * include/game/unk_blocks.h, the class in include/game/unk_blockfile.h.
 *
 * Bounds: hypothesis. Before 0x0209543C lie the destructors that close
 * unit_02095140.cpp; 0x020956F8 starts unit_020956F8.cpp. The thunks of the
 * interface vtable close the file. The interface vtable is emitted here too
 * (0x020BD400, unused: references go to the first copy, 0x020BD014, emitted by
 * unit_0208B41C.cpp). Real file name unknown.
 */

#include "game/unk_blockfile.h"

Unk0209543c::Unk0209543c(void *data) : Unk0209487c(data) {
    blockB = 0;
    blockE = 0;
    block10 = 0;
    blockC = 0;
    block64 = 0;
}

Unk0209543cBlockB *Unk0209543c::func_0209548c() {
    if (blockB != 0) {
        return blockB;
    }
    blockB = (Unk0209543cBlockB *)func_02094d4c(0xb);
    return blockB;
}

void *Unk0209543c::func_020954b4() {
    if (blockC != 0) {
        return blockC;
    }
    blockC = func_02094d4c(0xc);
    return blockC;
}

u32 Unk0209543c::func_020954dc() {
    Unk0209487cEntry *e = func_02095030(0xc);

    if (e != 0) {
        return e->size;
    }
    return 0;
}

void *Unk0209543c::func_020954f8() {
    if (blockE != 0) {
        return blockE;
    }
    blockE = func_02094d4c(0xe);
    return blockE;
}

int Unk0209543c::func_02095520() {
    if (func_0209548c() == 0) {
        return 0;
    }
    return func_0209548c()->unk18;
}

void *Unk0209543c::func_02095558() {
    if (block10 != 0) {
        return block10;
    }
    block10 = func_02094d4c(0x10);
    return block10;
}

int Unk0209543c::func_02095580() {
    if (func_0209548c() == 0) {
        return 0;
    }
    return func_0209548c()->unk1c;
}

void *Unk0209543c::func_020955b8() {
    if (block64 != 0) {
        return block64;
    }
    block64 = func_02094d4c(0x64);
    return block64;
}

int Unk0209543c::func_020955e0() {
    if (func_0209548c() == 0) {
        return 0;
    }
    return func_0209548c()->unk0;
}

Unk0209543c::~Unk0209543c() {}
