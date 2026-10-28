/*
 * Unit 0x0205D4D8-0x0205D6E0: the first half of the parameter reader
 * Unk0205d6b8 (six values, one per index given by func_02067878). A level
 * word of the script (-5 to 5) maps to a signed amount from a table; the
 * reader is filled from the "Food" value block of a script, or from the runs
 * of a script, or from the parameters of a script step.
 *
 * Bounds: hypothesis. The functions before 0x0205D4D8 work on the object
 * definition record (unit_0205C700.cpp). func_0205d6e0 (unit_0205D6E0.c,
 * clears the six values) and the functions after it up to 0x0205D8D8
 * (unit_0205D6FC.cpp) most likely belong to the same source file; this unit
 * stops at 0x0205D6E0 to keep that file. `.data`: the amount table, the
 * "Food" string, then two strings and a table of pointers to them that no
 * code reads (0x020BC2A0-0x020BC2B8). Delinked alone, that unreferenced range
 * would be dropped by the dead-stripping link, so it stays in this unit's
 * `.data`; compiled, data_020bc2b0 is dropped too (not linked as complete
 * until a form that keeps it is found). Real file name unknown.
 *
 * All functions keep C linkage: other files call them by their addresses.
 */

#include "game/unk_script.h"

class Unk02099c0c;

/* The parameter reader (0x18 bytes). */
struct Unk0205d6b8 {
    int values[6];
};

int data_020bc284[5] = {5, 10, 15, 20, 30};

extern "C" {

u32 func_0209a32c(const u32 *str, u32 last, u32 end);
void func_0205d6e0(Unk0205d6b8 *p);
void func_0205d72c(Unk0205d6b8 *p, Unk020956f8 *script, int key);
void func_0205d7f0(Unk0205d6b8 *p, Unk02099c0c *node);
void func_0205d858(Unk0205d6b8 *p, int key, int value);

int func_0205d4d8(int level) {
    if (level == 0) {
        return 0;
    }
    if (level > 0) {
        return data_020bc284[level - 1];
    }
    return -data_020bc284[-1 - level];
}

int func_0205d514(int key) {
    int level = 0;
    switch (key) {
    case 0x749283fa:
        level = 5;
        break;
    case 0xb770d89c:
        level = 4;
        break;
    case 0xc50fec0b:
        level = 3;
        break;
    case 0xb91baa50:
        level = 2;
        break;
    case 0x699cb0c7:
        level = 1;
        break;
    case 0x4b2c7b3c:
        level = -1;
        break;
    case 0x9f1ef38d:
        level = -2;
        break;
    case 0x11cc340e:
        level = -3;
        break;
    case 0x9d7421d9:
        level = -4;
        break;
    case 0xcc490cf0:
        level = -5;
        break;
    }
    return level;
}

Unk0205d6b8 *func_0205d608(Unk0205d6b8 *p, Unk020956f8 *script) {
    Unk02099c78Value *values;
    int i;
    func_0205d6e0(p);
    Unk02099c78Block *block = (Unk02099c78Block *)script->func_02095a3c(func_0209a32c((const u32 *)"Food", 0, 0));
    if (block == 0) {
        func_0205d72c(p, script, 0x07ede381);
    } else {
        values = script->func_02095ab0();
        for (i = block->start; i < block->start + block->count; i++) {
            Unk02099c78Value v = values[i];
            func_0205d858(p, v.unk0, v.unk4);
        }
    }
    return p;
}

Unk0205d6b8 *func_0205d6b8(Unk0205d6b8 *p, Unk02099c0c *node) {
    func_0205d6e0(p);
    func_0205d7f0(p, node);
    return p;
}

void func_0205d6dc(Unk0205d6b8 *p) {}

}

const char *data_020bc2b0[] = {"Invalid", "Test"};
