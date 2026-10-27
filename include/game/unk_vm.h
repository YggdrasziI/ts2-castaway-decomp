/*
 * The script runner of unit_02099C78.cpp (Unk02099c78): an abstract class that
 * runs bytecode from a resource and reads and writes its variables through
 * virtual functions. Layout from the code; all names are placeholders. The
 * destructor is inline: the destructors of the derived classes do not call
 * it, and unit_02099C78.cpp emits it with the vtable.
 */
#ifndef GAME_UNK_VM_H
#define GAME_UNK_VM_H

#include "game/unk_script.h"

class Unk02099c78;

struct Unk02099c78Call {
    Unk02099c78 *self;
    short result;
    Unk02099c78Value *value;
    int b;
};

class Unk02099c78 {
public:
    Unk02099c78(Unk020956f8 *res);
    virtual bool vfunc_00(int key) = 0;
    virtual short vfunc_04(int index) = 0;
    virtual void vfunc_08(int index, short value) = 0;
    virtual ~Unk02099c78() {}
    virtual int vfunc_14(int arg, Unk02099c78Call *call) = 0;

    void func_02099ce0(int key);
    int func_02099d04(Unk02099c78Block *block, int budget);
    int func_02099fd0(int index, int a, int b);
    bool func_0209a034(int index);
    bool func_0209a078(int index);
    void func_0209a0bc(int index);
    int func_0209a0f4(int key);

    Unk020956f8 *res;
    short unk8;
};

#endif
