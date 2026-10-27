/*
 * Unit 0x0206B630-0x0206B77C: Unk0206b630, a sorted set of ints. func_0206b630
 * inserts a value (false when it is already there), func_0206b6bc tests for one,
 * func_0206b6e8 searches by bisection (the index, or -(insertion point + 1)),
 * func_0206b73c / func_0206b75c save and load the whole object as one block.
 *
 * Bounds: hypothesis. The functions before 0x0206B630 belong to a class with a
 * pool object (Unk0206b4d4); unit_0206B77C.cpp starts after the load function.
 * Real file name unknown.
 */

#include "game/unk_sortedset.h"

extern "C" {
void func_020a4dc4(Unk020a4c4c *save, void *data, int size);
void func_020a4e14(Unk020a4c4c *save, void *data, int size);
}

bool Unk0206b630::func_0206b630(int value) {
    if (count < 1) {
        values[count++] = value;
        return true;
    }
    int i = func_0206b6e8(value);
    if (i >= 0) {
        return false;
    }
    i = -(i + 1);
    for (int j = count; j >= i; j--) {
        values[j] = values[j - 1];
    }
    values[i] = value;
    count++;
    return true;
}

bool Unk0206b630::func_0206b6bc(int value) {
    if (count != 0 && func_0206b6e8(value) >= 0) {
        return true;
    }
    return false;
}

int Unk0206b630::func_0206b6e8(int value) {
    int lo = 0;
    int hi = count - 1;
    while (lo <= hi) {
        int mid = (hi + lo) >> 1;
        if (values[mid] > value) {
            hi = mid - 1;
        } else if (values[mid] < value) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return -(lo + 1);
}

void Unk0206b630::func_0206b73c(Unk020a4c4c *save) {
    func_020a4dc4(save, this, sizeof(Unk0206b630));
}

void Unk0206b630::func_0206b75c(Unk020a4c4c *save) {
    func_020a4e14(save, this, sizeof(Unk0206b630));
}
