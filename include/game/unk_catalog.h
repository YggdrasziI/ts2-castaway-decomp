/*
 * Classes shared by unit_02071D94.cpp and unit_020724CC.cpp. Unk0206fab0 is the
 * base of the game states (vtable data_020bc904: the inline destructors
 * 0x0206FAB0 / 0x0206FAB4 and three pure virtual functions, copied by every file
 * that defines a derived constructor); the pure functions are named after the
 * first state's implementations. Unk020724cc lists, per value of
 * Unk020081dc::unk28 (2) and per part (6), the items of the database
 * data_020c3fc4 that carry the part keys, and the items of another key.
 * Unk020081dc is the 0x2C-byte outfit record that func_020081dc returns for an
 * object; its constructor (0x020647B0) and destructor (0x020647EC) are out of
 * line in unit_020647B0.cpp, as the outfit screen passes them to
 * __cxa_vec_ctor / __cxa_vec_dtor. The parts and colours are wrapped in structs:
 * the record copies move them as blocks. Layouts from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_CATALOG_H
#define GAME_UNK_CATALOG_H

#include "game/unk_camctl.h"

typedef unsigned long u32;

class Unk0206fab0 {
public:
    Unk0206fab0(int id) {
        this->id = id;
        next = 0;
    }
    virtual ~Unk0206fab0() {}
    virtual void func_02071e04() = 0;
    virtual void func_02072224() = 0;
    virtual void func_02071fdc(int dt) = 0;

    int id;
    int next;
};


struct Unk020081dcParts {
    int v[6];
};

struct Unk020081dcColors {
    int v[3];
};

class Unk020081dc {
public:
    Unk020081dc();
    ~Unk020081dc();

    Unk020081dcParts parts;
    int unk18;
    Unk020081dcColors colors;
    int unk28;
};

/* An item of the database (only the word at 0x0C is used here). */
struct Unk0205d000 {
    int unk0[3];
    int unkc;
};

class Unk020c43a8;

class Unk020724cc {
public:
    Unk020724cc(Unk020c43a8 *owner);
    ~Unk020724cc();
    int func_020726bc(int part);
    int func_02072710(int part, int index);
    int func_0207278c(int part, int index);
    void func_020727e8(int part, int index);
    bool func_020728c4(int part, int index);
    void func_020729ac();
    void func_020729e8(int index);
    void func_02072a30(int kind);
    void func_02072a78(int kind, Unk020081dc *out);
    void func_02072ba0();

    Unk0205d000 *items[2][6][20];
    int counts[2][6];
    Unk0205d000 **others;
    int otherCount;
    Unk020c43a8 *owner;
};

#endif
