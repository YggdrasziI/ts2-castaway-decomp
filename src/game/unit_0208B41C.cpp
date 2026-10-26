/*
 * Unit 0x0208B41C-0x0208B554: a class (Unk0208b41c) implementing the interface
 * Unk020bd014 from memory it owns instead of a resource file: an embedded header
 * block at 4, five arrays freed by func_0208b464, a reference count at 0x8C. No
 * code in the ROM references its vtable besides the destructors. The constructor
 * is not in the ROM: the empty one here (its body unknown) makes the file emit the
 * interface vtable copy, and the -dead link drops it (notes/MATCHING.md).
 *
 * Bounds: hypothesis. Before 0x0208B41C, func_0208b40c stores to data_020c7d28 like
 * the functions of 0x0208AF.. (another file); 0x0208B554 is the constructor of the
 * static object of the next class (__sinit_020ae2b8), whose fields differ. .data:
 * the vtable data_020bcfd8 and the first copy of the interface vtable
 * (data_020bd014) right after it. Real file name unknown.
 */

#include "game/unk_blocks.h"

typedef unsigned char u8;
typedef signed short s16;

class Unk0208b41c : public Unk020bd014 {
public:
    virtual void *func_020954b4();
    virtual u32 func_020954dc();
    virtual void *func_020954f8();
    virtual int func_02095520();
    virtual void func_0208a1ec();
    virtual void func_0208aa84();
    virtual Unk0209543cBlockB *func_0209548c();
    virtual int func_020955e0();
    virtual void *func_02095558();
    virtual int func_02095580();
    virtual void *func_020955b8();
    Unk0208b41c();
    virtual ~Unk0208b41c();
    void func_0208b464();

    Unk0209543cBlockB blockB;
    u8 unk30[0x20];
    u8 *unk50;
    u8 *blockC;
    u8 unk58[4];
    u32 blockCSize;
    u8 unk60[0x14];
    u8 *unk74;
    u8 *unk78;
    u8 unk7c[4];
    s16 unk80;
    u8 unk82[2];
    u8 *blockE;
    u8 unk88[4];
    int refs;
};

Unk0208b41c::Unk0208b41c() {}

Unk0208b41c::~Unk0208b41c() {
    func_0208b464();
}

void Unk0208b41c::func_0208b464() {
    if (unk50 != 0) {
        delete[] unk50;
    }
    unk50 = 0;
    if (blockC != 0) {
        delete[] blockC;
    }
    blockC = 0;
    if (unk74 != 0) {
        delete[] unk74;
    }
    unk74 = 0;
    if (unk78 != 0) {
        delete[] unk78;
    }
    unk78 = 0;
    if (blockE != 0) {
        delete[] blockE;
    }
    blockE = 0;
}

void *Unk0208b41c::func_020954b4() {
    return blockC;
}

u32 Unk0208b41c::func_020954dc() {
    return blockCSize;
}

void *Unk0208b41c::func_020954f8() {
    return blockE;
}

int Unk0208b41c::func_02095520() {
    return unk80;
}

void Unk0208b41c::func_0208a1ec() {
    refs++;
}

void Unk0208b41c::func_0208aa84() {
    if (refs > 0) {
        refs--;
    }
}

Unk0209543cBlockB *Unk0208b41c::func_0209548c() {
    return &blockB;
}

int Unk0208b41c::func_020955e0() {
    return blockB.unk0;
}

void *Unk0208b41c::func_02095558() {
    return 0;
}

int Unk0208b41c::func_02095580() {
    return 0;
}

void *Unk0208b41c::func_020955b8() {
    return 0;
}
