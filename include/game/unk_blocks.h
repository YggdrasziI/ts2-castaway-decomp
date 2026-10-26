/*
 * Abstract interface Unk020bd014 (vtable data_020bd014: eleven pure virtual
 * functions) implemented by the resource file class of unit_0209543C.cpp and by
 * the class of unit_0208B41C.cpp: access to a header block (Unk0209543cBlockB) and
 * to four data blocks, then add and drop a reference. All names are placeholders;
 * each function keeps the name of its implementation in unit_0209543C.cpp.
 */
#ifndef GAME_UNK_BLOCKS_H
#define GAME_UNK_BLOCKS_H

typedef unsigned long u32;

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

#endif
