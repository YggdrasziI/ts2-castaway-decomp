/*
 * Unit 0x0205D4D8-0x0205D8D8: the parameter reader Unk0205d6b8 (six values,
 * one per index given by func_02067878). A level word of the script (-5 to
 * 5) maps to a signed amount from a table; the reader is filled from the
 * "Food" value block of a script, or from the runs of a script, or from the
 * parameters of a script step, and a value is set from a key / level pair.
 * Then a set membership count.
 *
 * Bounds: hypothesis. The functions before 0x0205D4D8 work on the object
 * definition record (unit_0205C700.cpp); the scene object class
 * (unit_0205D8D8.cpp) follows. `.data`: the amount table, the "Food" string,
 * then two strings and a table of pointers to them that no code reads
 * (0x020BC2A0-0x020BC2B8). `.bss`: the empty script block data_020c3fb0 that
 * unit_0205C700.cpp returns (it follows a larger object of that file, so it is
 * not one of its own). Real file name unknown.
 *
 * All functions keep C linkage: other files call them by their addresses.
 */

#include "game/unk_script.h"
#include "game/unk_sortedset.h"

Unk02099c78Block data_020c3fb0;

struct Unk02099c0cPair;

/* The parameters of a script step (unit_02099C0C.cpp). */
class Unk02099c0c {
public:
    Unk02099c0c(Unk02099c0cPair *pairs, int count) : unk0(0), unk4(0), pairs(pairs), count(count) {}
    bool func_02099c0c(int *value, int key);

    int unk0;
    s16 unk4;
    Unk02099c0cPair *pairs;
    int count;
};

/* The parameter reader (0x18 bytes). */
struct Unk0205d6b8 {
    int values[6];
};

int data_020bc284[5] = {5, 10, 15, 20, 30};

extern "C" {

u32 func_0209a32c(const u32 *str, u32 last, u32 end);
int func_02067878(u32 hash);
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

void func_0205d6e0(Unk0205d6b8 *p) {
    int i;
    for (i = 0; i < 6; i++) {
        p->values[i] = 0;
    }
}

int func_0205d6fc(Unk0205d6b8 *p, int i) {
    return p->values[i];
}

int func_0205d704(Unk0205d6b8 *p) {
    for (int i = 0; i < 6; i++) {
        if (p->values[i] != 0) {
            return i;
        }
    }
    return 6;
}

void func_0205d72c(Unk0205d6b8 *p, Unk020956f8 *script, int key) {
    Unk02099c78Block *block = script->func_020957ec(key);
    if (block == 0) {
        return;
    }
    Unk02099c78Op *ops = script->func_02095794();
    for (int i = 0; i < block->count; i++) {
        Unk02099c78Op op = ops[block->start + i];
        if (op.arg == 0x196aaa23) {
            Unk02099c0c node((Unk02099c0cPair *)&script->func_02095ab0()[op.a], op.b);
            func_0205d7f0(p, &node);
        }
    }
}

void func_0205d7f0(Unk0205d6b8 *p, Unk02099c0c *node) {
    Unk02099c78Value v;
    if (!node->func_02099c0c(&v.unk4, 0x7e5d2b3f)) {
        return;
    }
    if (!node->func_02099c0c(&v.unk0, 0x18a7f0fa)) {
        return;
    }
    func_0205d858(p, v.unk0, v.unk4);
}

void func_0205d858(Unk0205d6b8 *p, int key, int value) {
    int i = func_02067878(key);
    if (i == 6) {
        return;
    }
    int v;
    int level = func_0205d514(value);
    if (level != 0) {
        v = func_0205d4d8(level);
    } else if (value >= -100 && value <= 100) {
        v = value;
    }
    p->values[i] = v;
}

int func_0205d8b0(int value, Unk0206b630 *set) {
    int n = 0;
    if (set->func_0206b6bc(value)) {
        n++;
    }
    return n;
}

}

const char *data_020bc2b0[] = {"Invalid", "Test"};
