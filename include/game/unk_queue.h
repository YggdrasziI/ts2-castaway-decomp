/*
 * Timed queue of unit_0206B77C.cpp (Unk0206b8cc): a fixed pool of 16-byte nodes,
 * a free list and an active list sorted by due time, then by order. Used by the
 * main game state (unit_0206BCE0.cpp). All names are placeholders.
 */
#ifndef GAME_UNK_QUEUE_H
#define GAME_UNK_QUEUE_H

typedef unsigned short u16;
typedef signed short s16;

struct Unk020a4c4c;
class Unk0206bcf0Item;

/* A request given to Unk0206b8cc::func_0206b998. */
struct Unk0206b998Req {
    Unk0206b998Req() : item(0), key(0), delay(0), order(100) {}

    Unk0206bcf0Item *item;
    int key;
    u16 delay;
    u16 order;
};

/* A queue node (0x10 bytes). */
class Unk0206b95c {
public:
    Unk0206b95c() {
        reset();
    }

    void reset() {
        next = 0;
        time = 0;
        order = 0;
        id = 0;
        key = 0;
    }

    Unk0206b95c *func_0206b77c(Unk0206b95c *node);
    void func_0206b828(Unk020a4c4c *save);
    void func_0206b87c(Unk020a4c4c *save);

    Unk0206b95c *next;
    u16 time;
    u16 order;
    int id;
    int key;
};

class Unk0206b8cc {
public:
    Unk0206b8cc(int count);
    ~Unk0206b8cc();
    void func_0206b998(const Unk0206b998Req *req);
    void func_0206ba1c(const Unk0206bcf0Item *item);
    void func_0206bae4();
    void func_0206bbdc(Unk020a4c4c *save);
    void func_0206bc48(Unk020a4c4c *save);

    Unk0206b95c *nodes;
    int count;
    Unk0206b95c *head;
    Unk0206b95c *free;
    u16 time;
};

#endif
