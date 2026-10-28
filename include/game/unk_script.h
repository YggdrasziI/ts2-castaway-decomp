/*
 * Script resource file of unit_020956F8.cpp (Unk020956f8), read by the bytecode
 * interpreter of unit_02099C78.cpp. Block layouts come from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_SCRIPT_H
#define GAME_UNK_SCRIPT_H

#include "game/unk_file.h"

/* Block 0x400: counts of the other blocks. */
struct Unk020956f8Header {
    int varCount;
    int unk4;
    int count406;
    int count407;
    int keyCount;
    int blockCount;
};

/* Block 0x405: one 12-byte instruction. */
struct Unk02099c78Op {
    int arg;
    u32 code;
    short a;
    short b;
};

/* Block 0x401: variables, sorted by key. */
struct Unk02099c78Var {
    int unk0;
    short unk4;
    short init;
    short min;
    short max;
};

/* Block 0x404: instruction runs, sorted by key. */
struct Unk02099c78Block {
    int func_start() const { return start; }
    int func_end() const { return start + count; }

    int unk0;
    short start;
    short count;
};

/* Blocks 0x403, 0x406 and 0x407: 8-byte entries, the last two sorted by key. */
struct Unk02099c78Value {
    int unk0;
    int unk4;
};

class Unk020956f8 : public Unk0209487c {
public:
    Unk020956f8(void *data);
    ~Unk020956f8();
    Unk020956f8Header *func_0209576c();
    Unk02099c78Op *func_02095794();
    Unk02099c78Block *func_020957c0();
    Unk02099c78Block *func_020957ec(int key);
    Unk02099c78Var *func_0209585c();
    Unk02099c78Var *func_02095888(int key);
    int func_020958bc(int key);
    Unk02099c78Value *func_02095934();
    Unk02099c78Value *func_02095960(int key);
    int func_0209599c(int key);
    Unk02099c78Value *func_02095a10();
    Unk02099c78Value *func_02095a3c(int key);
    Unk02099c78Value *func_02095ab0();
    int *func_02095adc();
    bool func_02095b08(int key);

    Unk020956f8Header *header;
    Unk02099c78Var *vars;
    Unk02099c78Value *values;
    Unk02099c78Value *block406;
    Unk02099c78Value *block407;
    Unk02099c78Block *blocks;
    Unk02099c78Op *ops;
    int *keys;
};

#endif
