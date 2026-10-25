/*
 * Unit 0x02099C0C-0x02099C78: lookup in a table of key / value pairs.
 *
 * Bounds: hypothesis. unit_02099870.cpp ends before 0x02099C0C with the array
 * destructors its static initializer registers; from 0x02099C78 starts a class
 * with another layout (vtable data_020bd584). Both functions are called from many
 * places in 0x02001xxx-0x02002xxx and 0x0205Bxxx-0x02063xxx. Real file name
 * unknown.
 */

struct Unk02099c0cPair {
    int key;
    int value;
};

class Unk02099c0c {
public:
    bool func_02099c0c(int *value, int key);
    int func_02099c58(int key);

    int unk0;
    int unk4;
    Unk02099c0cPair *pairs;
    int count;
};

bool Unk02099c0c::func_02099c0c(int *value, int key) {
    int i;
    Unk02099c0cPair *p;
    int n;

    n = count;
    p = pairs;
    for (i = 0; i < n; i++) {
        if (key == p[i].key) {
            *value = p[i].value;
            return true;
        }
    }
    return false;
}

int Unk02099c0c::func_02099c58(int key) {
    int value;

    if (func_02099c0c(&value, key)) {
        return value;
    }
    return 0;
}
