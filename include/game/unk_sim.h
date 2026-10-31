/*
 * The sim of unit_020680D4.cpp (Unk020680d4, 0x184 bytes) and its interface
 * Unk020680d4Base, shared with the player of unit_02064984.cpp, with the small
 * types they use (map cell, direction, vector wrapper) and the world
 * (data_020c3ba4). Layouts come from the code; all names are placeholders.
 */
#ifndef GAME_UNK_SIM_H
#define GAME_UNK_SIM_H

#include "game/unk_pool.h"
#include "game/unk_archive.h"
#include "game/unk_blockfile.h"
#include "game/unk_xform.h"
#include "game/unk_anim.h"
#include "game/unk_animinst.h"
#include "game/unk_texture.h"
#include "game/unk_model.h"
#include "game/unk_palset.h"
#include "game/unk_camctl.h"
#include "game/unk_texanim.h"

typedef signed char s8;

/* A vector; the wrapper makes its copies block copies (ldm / stm). */
struct Unk020680d4Vec {
    Unk020680d4Vec() {}
    Unk020680d4Vec(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

/* The bounding box of the bones (0x18 bytes). */
struct Unk020680d4Box {
    Unk020680d4Box() {}
    Unk020680d4Box(const Unk020680d4Vec &min, const Unk020680d4Vec &max) : min(min), max(max) {}

    Unk020680d4Vec min;
    Unk020680d4Vec max;
};

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    bool operator==(Unk020593e4 o) const {
        return unk3 == o.unk3 && unk2 == o.unk2 && unk0 == o.unk0;
    }

    bool operator!=(Unk020593e4 o) const {
        return unk2 != o.unk2 || unk0 != o.unk0 || unk3 != o.unk3;
    }

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

struct Unk020680d4Xy {
    Unk020680d4Xy() {}
    Unk020680d4Xy(s16 x, s16 y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(Unk020680d4Xy o) const {
        return x == o.x && y == o.y;
    }

    bool operator!=(Unk020680d4Xy o) const {
        return x != o.x || y != o.y;
    }

    s16 x;
    s16 y;
};

/* A map cell: its tile coordinates are -1 when it is not set. */
struct Unk020680d4Cell {
    Unk020680d4Cell() {
        xy.x = -1;
        xy.y = -1;
    }

    bool operator==(Unk020680d4Cell o) const {
        return pos == o.pos && xy == o.xy;
    }

    bool operator!=(const Unk020680d4Cell &o) const {
        return pos != o.pos || xy != o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* The time read by func_0202071c. */
struct Unk0202071c {
    Unk0202071c() {}

    u32 value;
};


struct Unk02058788;

/* The world (data_020c3ba4). */
struct Unk020c3ba4 {
    int unk0;
    u8 unk4[0x54];
    Unk02058788 *maps[0x29];
    s8 map;
    Unk0206fac8 *palettes;
    Unk020705e4 *texanims;
};

/* A body part (0x2C bytes). */
struct Unk020680d4Part {
    Unk020680d4Part() : index(-1), file(0), flags(0), bone(-1), offset(0, 0, 0), name(0), frame(-1) {
        tex[0] = -1;
        tex[1] = -1;
    }

    int index;
    Unk0209543c *file;
    int tex[2];
    u32 flags;
    int bone;
    Unk020680d4Vec offset;
    const char *name;
    int frame;
};

/* A direction (0 to 3; 4 when not set). */
struct Unk020680d4Dir {
    Unk020680d4Dir() {}
    Unk020680d4Dir(int v) : v(v) {}

    int v;
};

/*
 * The interface: its vtable copies are all zero; the first one (0x020BC740,
 * after the vtables of the player) keeps the name `_ZTV15Unk020680d4Base`, the
 * one after the vtable of the sim (0x020BC800) is anonymous.
 */
class Unk020680d4Base {
public:
    virtual void func_00(Unk02098ff0 pos) = 0;
    virtual Unk02098ff0 func_04() = 0;
    virtual void func_08(Unk02098ff0 rot) = 0;
    virtual Unk02098ff0 func_0c() = 0;
    virtual void func_10(Unk020680d4Cell cell) = 0;
    virtual Unk020680d4Cell func_14() = 0;
    virtual void func_18(Unk020680d4Dir dir) = 0;
    virtual Unk020680d4Dir func_1c() = 0;
    virtual Unk020680d4Xy func_20() = 0;
    virtual bool func_24() = 0;
    virtual bool func_28() = 0;
    virtual bool func_2c(const Unk020680d4Cell &cell) = 0;
};

class Unk020680d4 : public Unk020680d4Base {
public:
    Unk020680d4();
    ~Unk020680d4();
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);

    int id;
    Unk020680d4Dir dir;
    Unk020680d4Cell cell;
    u32 flags;
    int unk18;
    u32 time;
    Unk02093648 *archive;
    Unk020680d4Part parts[5];
    Unk020680d4Part body;
    int alpha;
    int alphaTo;
    int count;
    Unk020680d4Box box;
    Unk020680d4Vec scale;
    Unk0208be3c *xform;
    Unk02063d84 *anim;
    int speed;
    int blend;
    int blendStep;
    Unk02063d84 *prevAnim;
    int unk174;
    int unk178;
    int unk17c;
    u8 unk180;
};

#endif
