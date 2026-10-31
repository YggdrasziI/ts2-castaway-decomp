/*
 * Scene elements of the fishing microgames: the 4-byte flag word and the sprite
 * animation, the element made of up to five parts and the fish base. Layouts come
 * from the code; all names are placeholders.
 */
#ifndef GAME_UNK_FISHING_H
#define GAME_UNK_FISHING_H

#include "game/unk_vector.h"

/* One flag word. */
struct Unk0200b04cBit {
    u32 v;

    Unk0200b04cBit() { v = 0; }
    bool func_get() const { return v & 1; }
    void func_set() { v |= 1; }
    void func_clear() { v &= ~1; }
};

class Unk02095140;

enum Unk0200b04cDir {
    UNK_0200B04C_UP,
    UNK_0200B04C_DOWN
};

/* A sprite animation (0x1C bytes). */
class Unk0200b04c {
public:
    Unk0200b04c();
    ~Unk0200b04c();

    Unk0200b04cDir func_dir() const {
        return playing.v & 2 ? UNK_0200B04C_UP : UNK_0200B04C_DOWN;
    }
    void func_set_dir(Unk0200b04cDir dir) {
        if (func_dir() != dir) {
            playing.v ^= 2;
        }
    }
    int func_start() const {
        return func_dir() == UNK_0200B04C_UP ? 0 : count - 1;
    }
    int func_end(Unk0200b04cDir dir) const {
        return dir == UNK_0200B04C_DOWN ? count - 1 : 0;
    }

    int frame;
    int mode;
    Unk0200b04cBit playing;
    int loops;
    int cur;
    int count;
    Unk02095140 *file;
};

struct Unk0200dd90Part {
    Unk02098e70 pos;
    u8 flag;
    int flags;
    int unk10;
    int unk14;
};

/* The movement block at 0x08 of a scene element. */
struct Unk020acb90 {
    Unk02098e70 dir;
    Unk02098e70 step;
    int speed;
    int unk14;
};

/* A scene element made of up to five parts. */
class Unk0200dd90 {
public:
    Unk0200dd90(int count);
    ~Unk0200dd90();
    virtual void *func_00() = 0;

    Unk02098e70 *func_0200df08();

    int count;
    Unk020acb90 move;
    Unk02098e70 pos;
    Unk0200dd90Part parts[5];
};

/* An 8-byte block copy: loads both words before the stores (notes/MATCHING.md). */
struct Unk02098e70Wrap {
    Unk02098e70 v;
};

inline void func_set(Unk02098e70 &d, const Unk02098e70 &s) {
    *(Unk02098e70Wrap *)&d = *(Unk02098e70Wrap *)&s;
}

/* Base of Unk02010920. */
class Unk0200ad70 : public Unk0200dd90 {
public:
    Unk0200ad70(int count);
    ~Unk0200ad70();

    Unk02098e70 unka0;
    Unk02098e70 unka8;
    Unk02098e70 unkb0;
    Unk02098e70 target;
    int unkc0;
    int (*hit)(Unk02098e70 *a, void *b, Unk02098e70 *c, int d);
    Unk02098e70 scale;
    int sizes[2];
    int key;
};

class Unk02010920 : public Unk0200ad70 {
public:
    Unk02010920(int count);
    ~Unk02010920();
    virtual bool func_04(int index, bool force);

    int index;
    u32 anims[2];
    int bait;
};

#endif
