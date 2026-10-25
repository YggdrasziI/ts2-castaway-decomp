/*
 * Heap types shared by unit_02099210.cpp (the heap) and unit_02099870.cpp (the heap
 * table). Layouts come from the code of both units; all names are placeholders.
 */
#ifndef GAME_UNK_HEAP_H
#define GAME_UNK_HEAP_H

typedef unsigned long u32;
typedef unsigned char u8;

/* Header of an allocated block: in front of it, or kept by the caller. */
struct Unk02099210Header {
    u32 size : 24;
    u32 used : 1;
    u32 unk25 : 1;
    u32 id : 6;
};

/* A free range, as an offset from the heap start. */
struct Unk02099210Node {
    u32 offset;
    u32 size;
    Unk02099210Node *next;
};

/* Free list of one heap (0xC0C bytes). */
struct Unk020c8700 {
    Unk020c8700() { total = 0; }
    ~Unk020c8700() {}

    Unk02099210Node nodes[256];
    Unk02099210Node *free;
    Unk02099210Node *spare;
    u32 total;
};

/* Block whose header the caller keeps. */
struct Unk02099210Handle {
    void *ptr;
    Unk02099210Header header;
};

/* One heap (0x2C bytes). */
class Unk020c8440 {
public:
    Unk020c8440();
    ~Unk020c8440();

    Unk020c8700 *list;
    u32 start;
    u32 size;
    u32 padding;
    u32 alignShift;
    u32 align;
    int id;
    u32 used;
    u32 unk20;
    u32 unk24;
    u32 flags;
};

extern "C" void func_02099280(Unk020c8440 *heap, void *start, u32 size, u32 alignShift, int id, u8 inlineHeader, Unk020c8700 *list);
extern "C" void *func_02099390(Unk020c8440 *heap, u32 size);
extern "C" void func_02099638(Unk020c8440 *heap, void *ptr);
extern "C" int func_020997ac(Unk020c8440 *heap);
extern "C" int func_020997e4(void *ptr);

#endif
