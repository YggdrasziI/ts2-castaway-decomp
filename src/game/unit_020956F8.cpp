/*
 * Unit 0x020956F8-0x02095B88: the script resource file class (Unk020956f8,
 * include/game/unk_script.h) derived from the file class Unk0209487c. It caches
 * the blocks 0x400 to 0x407 and finds variables, instruction runs and other
 * entries by key with binary searches.
 *
 * Bounds: hypothesis. Each resource file class of this region starts its file with
 * its constructor; 0x02095B88 starts unit_02095B88.cpp. The vtable data_020bd434 is
 * only used by the constructor. Real file name unknown.
 */

#include "game/unk_script.h"

Unk020956f8::Unk020956f8(void *data) : Unk0209487c(data) {
    header = 0;
    vars = 0;
    values = 0;
    block406 = 0;
    block407 = 0;
    blocks = 0;
    ops = 0;
    keys = 0;
}

Unk020956f8::~Unk020956f8() {}

Unk020956f8Header *Unk020956f8::func_0209576c() {
    if (header != 0) {
        return header;
    }
    header = (Unk020956f8Header *)func_02094d4c(0x400);
    return header;
}

Unk02099c78Op *Unk020956f8::func_02095794() {
    if (ops != 0) {
        return ops;
    }
    ops = (Unk02099c78Op *)func_02094d4c(0x405);
    return ops;
}

Unk02099c78Block *Unk020956f8::func_020957c0() {
    if (blocks != 0) {
        return blocks;
    }
    blocks = (Unk02099c78Block *)func_02094d4c(0x404);
    return blocks;
}

Unk02099c78Block *Unk020956f8::func_020957ec(int key) {
    Unk020956f8Header *h;
    Unk02099c78Block *b;
    int lo;
    int hi;
    int mid;

    h = func_0209576c();
    if (h == 0) {
        return 0;
    }
    b = func_020957c0();
    if (b == 0) {
        return 0;
    }
    lo = 0;
    hi = h->blockCount - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (b[mid].unk0 == key) {
            return &b[mid];
        }
        if (key < b[mid].unk0) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

Unk02099c78Var *Unk020956f8::func_0209585c() {
    if (vars != 0) {
        return vars;
    }
    vars = (Unk02099c78Var *)func_02094d4c(0x401);
    return vars;
}

Unk02099c78Var *Unk020956f8::func_02095888(int key) {
    int i = func_020958bc(key);

    if (i == -1) {
        return 0;
    }
    return &func_0209585c()[i];
}

int Unk020956f8::func_020958bc(int key) {
    Unk020956f8Header *h;
    Unk02099c78Var *v;
    int lo;
    int hi;
    int mid;

    h = func_0209576c();
    if (h == 0) {
        return -1;
    }
    v = func_0209585c();
    if (v == 0) {
        return -1;
    }
    lo = 0;
    hi = h->varCount - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (v[mid].unk0 == key) {
            return mid;
        }
        if (key < v[mid].unk0) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return -1;
}

Unk02099c78Value *Unk020956f8::func_02095934() {
    if (block406 != 0) {
        return block406;
    }
    block406 = (Unk02099c78Value *)func_02094d4c(0x406);
    return block406;
}

Unk02099c78Value *Unk020956f8::func_02095960(int key) {
    Unk02099c78Value *t = func_02095934();
    int i;

    if (t == 0) {
        return 0;
    }
    i = func_0209599c(key);
    if (i == -1) {
        return 0;
    }
    return &t[i];
}

int Unk020956f8::func_0209599c(int key) {
    Unk020956f8Header *h;
    Unk02099c78Value *t;
    int lo;
    int hi;
    int mid;
    int v;

    h = func_0209576c();
    if (h == 0) {
        return 0;
    }
    t = func_02095934();
    if (t == 0) {
        return 0;
    }
    lo = 0;
    hi = h->count406 - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        v = t[mid].unk0;
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

Unk02099c78Value *Unk020956f8::func_02095a10() {
    if (block407 != 0) {
        return block407;
    }
    block407 = (Unk02099c78Value *)func_02094d4c(0x407);
    return block407;
}

Unk02099c78Value *Unk020956f8::func_02095a3c(int key) {
    Unk020956f8Header *h;
    Unk02099c78Value *t;
    int lo;
    int hi;
    int mid;
    int v;

    h = func_0209576c();
    if (h == 0) {
        return 0;
    }
    t = func_02095a10();
    if (t == 0) {
        return 0;
    }
    lo = 0;
    hi = h->count407 - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        v = t[mid].unk0;
        if (v == key) {
            return &t[mid];
        }
        if (key < v) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

Unk02099c78Value *Unk020956f8::func_02095ab0() {
    if (values != 0) {
        return values;
    }
    values = (Unk02099c78Value *)func_02094d4c(0x403);
    return values;
}

int *Unk020956f8::func_02095adc() {
    if (keys != 0) {
        return keys;
    }
    keys = (int *)func_02094d4c(0x402);
    return keys;
}

bool Unk020956f8::func_02095b08(int key) {
    Unk020956f8Header *h;
    int *k;
    int lo;
    int hi;
    int mid;

    h = func_0209576c();
    if (h == 0) {
        return false;
    }
    if (h->keyCount == 0) {
        return false;
    }
    k = func_02095adc();
    if (k == 0) {
        return false;
    }
    lo = 0;
    hi = h->keyCount - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (k[mid] == key) {
            return true;
        }
        if (key < k[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return false;
}
