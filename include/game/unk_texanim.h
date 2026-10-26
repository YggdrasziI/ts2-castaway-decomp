/*
 * Classes of unit_020705E4.cpp: texture coordinate animations of a model's
 * elements. Unk02070cc0 runs a list of effect entries (an effect index and seven
 * parameter words) on a texture offset and scale and writes them to one element
 * of the model's element set; Unk02070eac holds the animations built from one
 * data block of a pool object; Unk020705e4 owns those sets and the references to
 * the container files they come from. Layout from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_TEXANIM_H
#define GAME_UNK_TEXANIM_H

#include "game/unk_poolitem.h"
#include "game/unk_texture.h"

class Unk02093648;
class Unk0209487c;

/* The texture offset and scale an effect works on, and the time (20.12). */
struct Unk02070cc0State {
    int x;
    int y;
    int sx;
    int sy;
    int time;
};

/* The parameters of one effect entry. */
struct Unk02070cc0Param {
    int enabled;
    int a;
    int b;
    int c;
    int d;
    int unk14;
    int unk18;
};

/* One effect entry (0x20 bytes). */
struct Unk02070cc0Entry {
    u32 type;
    Unk02070cc0Param param;
};

/* One animation (0x2C bytes). */
class Unk02070cc0 {
public:
    Unk02070cc0(Unk0208b554Item *item, int id, u32 *entries, u32 count);
    ~Unk02070cc0();
    void func_02070d5c();

    u32 *entries;
    u32 count;
    Unk02070cc0State state;
    Unk0208c050 *tex;
    Unk0208adc0 *set;
    int id;
    u32 flags;
};

/* The animations of one pool object (0x0C bytes). */
class Unk02070eac {
public:
    Unk02070eac(Unk0208b554Item *item, u32 *data, u32 size);
    ~Unk02070eac();
    bool func_02070fd4(Unk0208b554Item *item);
    void func_02070fe8();

    Unk0208b554Item *item;
    Unk02070cc0 **anims;
    u32 count;
};

/* A reference to a sub-file of a container file (0x0C bytes). */
struct Unk020705e4Ref {
    Unk02093648 *container;
    int index;
    int refs;
};

class Unk020705e4 {
public:
    Unk020705e4(u32 capacity);
    ~Unk020705e4();
    void func_02070688(Unk02093648 *container, u32 hash, Unk0208b554Item *item);
    void func_0207072c(Unk02093648 *container, u32 hash, Unk0208b554Item *item);
    void func_020707cc();
    int func_02070804(Unk02093648 *container, Unk0209487c *file, int index);
    void func_020708a8(Unk02093648 *container, int index);

    Unk020705e4Ref *refs;
    Unk02070eac **sets;
    u32 capacity;
    u32 refCount;
    u32 setCount;
};

#endif
