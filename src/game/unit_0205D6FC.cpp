/*
 * Unit 0x0205D6FC-0x0205D8D8: the second half of the parameter reader
 * Unk0205d6b8 (see unit_0205D4D8.cpp): value access, first non-zero index,
 * reading from the runs of a script or from the parameters of a script step,
 * and setting one value from a key / level pair; then a set membership
 * count.
 *
 * Bounds: hypothesis. func_0205d6e0 (unit_0205D6E0.c) is before; the scene
 * object class (unit_0205D8D8.cpp) follows. No `.data`: the strings and
 * table after "Food" are kept with unit_0205D4D8.cpp. Real file name unknown.
 *
 * All functions keep C linkage: other files call them by their addresses.
 */

#include "game/unk_script.h"
#include "game/unk_sortedset.h"

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

extern "C" {

int func_02067878(u32 hash);
int func_0205d4d8(int level);
int func_0205d514(int key);
void func_0205d7f0(Unk0205d6b8 *p, Unk02099c0c *node);
void func_0205d858(Unk0205d6b8 *p, int key, int value);

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
