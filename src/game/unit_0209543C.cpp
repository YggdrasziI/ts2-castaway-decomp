/*
 * Unit 0x0209543C-0x020956F8: a resource file class (Unk0209543c) derived from the
 * file class Unk0209487c and from an abstract interface (Unk020bd014, eleven pure
 * virtual functions, vtable data_020bd014). It caches the blocks 0x0B, 0x0C, 0x0E,
 * 0x10 and 0x64 and reads three words of block 0x0B. The last two interface
 * functions, which add and drop a reference on the file, are defined in another
 * file (0x0208A1EC and 0x0208AA84).
 *
 * Bounds: hypothesis. Before 0x0209543C lie the destructors that close
 * unit_02095140.cpp; 0x020956F8 starts unit_020956F8.cpp. The thunks of the
 * interface vtable close the file. The interface vtable is emitted here too
 * (0x020BD400, unused: references go to the first copy, 0x020BD014). Real file name
 * unknown.
 * Not complete although every function and the data match: mwccarm emits the
 * interface vtable copy with a multiply-definable binding, and the first copy
 * (0x020BD014) still comes from assembly as a plain global, so the link fails
 * (strong) or resolves to this copy (weak). It completes with the file that owns
 * 0x020BD014.
 */

#include "game/unk_file.h"

struct Unk0209543cBlockB {
    int unk0;
    int unk4[5];
    int unk18;
    int unk1c;
};

class Unk020bd014 {
public:
    virtual Unk0209543cBlockB *func_0209548c() = 0;
    virtual int func_020955e0() = 0;
    virtual void *func_020954f8() = 0;
    virtual int func_02095520() = 0;
    virtual void *func_020954b4() = 0;
    virtual u32 func_020954dc() = 0;
    virtual void *func_02095558() = 0;
    virtual int func_02095580() = 0;
    virtual void *func_020955b8() = 0;
    virtual void func_0208a1ec() = 0;
    virtual void func_0208aa84() = 0;
};

class Unk0209543c : public Unk0209487c, public Unk020bd014 {
public:
    Unk0209543c(void *data);
    ~Unk0209543c();
    virtual void *func_020954b4();
    virtual u32 func_020954dc();
    virtual Unk0209543cBlockB *func_0209548c();
    virtual void *func_020954f8();
    virtual int func_02095520();
    virtual void *func_02095558();
    virtual int func_02095580();
    virtual void *func_020955b8();
    virtual int func_020955e0();
    virtual void func_0208a1ec();
    virtual void func_0208aa84();

    Unk0209543cBlockB *blockB;
    void *blockE;
    void *block10;
    void *blockC;
    void *block64;
};

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
