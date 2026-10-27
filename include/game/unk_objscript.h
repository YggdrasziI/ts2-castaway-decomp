/*
 * The script runner of a scene object (Unk02061c04, unit_02060ADC.cpp): it keeps
 * the variables of the script in the object. All names are placeholders.
 */
#ifndef GAME_UNK_OBJSCRIPT_H
#define GAME_UNK_OBJSCRIPT_H

#include "game/unk_vm.h"

class Unk02061d08Item;

class Unk02061c04 : public Unk02099c78 {
public:
    Unk02061c04(Unk02061d08Item *item);
    ~Unk02061c04();
    virtual bool vfunc_00(int key);
    virtual short vfunc_04(int index);
    virtual void vfunc_08(int index, short value);
    virtual int vfunc_14(int arg, Unk02099c78Call *call);

    Unk02061d08Item *item;
};

#endif
