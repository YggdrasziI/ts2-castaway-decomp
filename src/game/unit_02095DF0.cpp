/*
 * Unit 0x02095DF0-0x02095FDC: a resource file class (Unk02095df0) derived from the
 * file class Unk0209487c. It caches the blocks 0x2800 (count), 0x2801 (sorted
 * keys), 0x2802 (12-byte entries) and 0x2803 (data), finds a key by binary search
 * and returns the data of an entry.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; the destructors close this one and 0x02095FDC starts
 * unit_02095FDC.cpp. The vtable data_020bd4cc is only used by the constructor. Real
 * file name unknown.
 */

#include "game/unk_file.h"

struct Unk02095df0Header {
    int count;
};

struct Unk02095df0Entry {
    int unk0;
    int offset;
    int unk8;
};

class Unk02095df0 : public Unk0209487c {
public:
    Unk02095df0(void *data);
    ~Unk02095df0();
    Unk02095df0Header *func_02095e24();
    Unk02095df0Entry *func_02095e4c();
    int *func_02095e78();
    u8 *func_02095ea4();
    int func_02095ed0();
    int func_02095ef8(int key);
    u8 *func_02095f58(int index);

    Unk02095df0Header *header;
    u8 *data;
    int *keys;
    Unk02095df0Entry *entries;
};

Unk02095df0::Unk02095df0(void *data) : Unk0209487c(data) {
    header = 0;
    this->data = 0;
    keys = 0;
    entries = 0;
}

Unk02095df0Header *Unk02095df0::func_02095e24() {
    if (header != 0) {
        return header;
    }
    header = (Unk02095df0Header *)func_02094d4c(0x2800);
    return header;
}

Unk02095df0Entry *Unk02095df0::func_02095e4c() {
    if (entries != 0) {
        return entries;
    }
    entries = (Unk02095df0Entry *)func_02094d4c(0x2802);
    return entries;
}

int *Unk02095df0::func_02095e78() {
    if (keys != 0) {
        return keys;
    }
    keys = (int *)func_02094d4c(0x2801);
    return keys;
}

u8 *Unk02095df0::func_02095ea4() {
    if (data != 0) {
        return data;
    }
    data = (u8 *)func_02094d4c(0x2803);
    return data;
}

int Unk02095df0::func_02095ed0() {
    if (func_02095e24() == 0) {
        return 0;
    }
    return func_02095e24()->count;
}

int Unk02095df0::func_02095ef8(int key) {
    int *k;
    int lo;
    int hi;
    int mid;
    int v;

    func_02095e4c();
    k = func_02095e78();
    lo = 0;
    hi = func_02095ed0() - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        v = k[mid];
        if (v == key) {
            return mid;
        }
        if (key < v) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return -1;
}

u8 *Unk02095df0::func_02095f58(int index) {
    u8 *d;

    if (index < 0 || index >= func_02095ed0()) {
        return 0;
    }
    d = func_02095ea4();
    if (d == 0) {
        return 0;
    }
    return d + func_02095e4c()[index].offset;
}

Unk02095df0::~Unk02095df0() {}
