/*
 * Unit 0x0209A11C-0x0209A32C: a growable bit set (Unk0209a11c) whose word array is
 * allocated on the first set.
 *
 * Bounds: hypothesis. Before 0x0209A11C, func_0209a108 is the deleting destructor of
 * the class whose vtable is data_020bd584 (its constructor is func_02099c78); after
 * 0x0209A32C come string hash and UTF-8 helpers that use no bit set. The seven
 * functions only use each other and operator new[] / delete[], and are called from
 * several unrelated places (0x02058xxx, 0x0208Bxxx, 0x020A3xxx). Real file name
 * unknown.
 */

typedef unsigned long u32;

class Unk0209a11c {
public:
    Unk0209a11c();
    Unk0209a11c(u32 size);
    ~Unk0209a11c();
    void func_0209a164();
    bool func_0209a188(u32 index);
    void func_0209a1c4(u32 index, bool value);
    void func_0209a27c(u32 start, u32 count, bool value);
    void func_0209a2c4(u32 word, u32 index);

    u32 *bits;
    u32 size;
};

Unk0209a11c::Unk0209a11c() {
    bits = 0;
    size = 0x400;
}

Unk0209a11c::Unk0209a11c(u32 size) {
    bits = 0;
    this->size = size == 0 ? 0x20 : (size + 0x1f) & ~0x1f;
}

Unk0209a11c::~Unk0209a11c() {
    func_0209a164();
}

void Unk0209a11c::func_0209a164() {
    if (bits != 0) {
        delete[] bits;
    }
    bits = 0;
}

bool Unk0209a11c::func_0209a188(u32 index) {
    if (bits == 0) {
        return false;
    }
    if (index >= size) {
        return false;
    }
    return (bits[index >> 5] & (1 << (index & 0x1f))) != 0;
}

void Unk0209a11c::func_0209a1c4(u32 index, bool value) {
    if (bits == 0 && !value) {
        return;
    }
    if (index >= size) {
        return;
    }
    if (bits == 0) {
        bits = new u32[size >> 5];
        for (u32 i = 0; i < size >> 5; i++) {
            bits[i] = 0;
        }
    }
    if (value) {
        bits[index >> 5] |= 1 << (index & 0x1f);
    } else {
        bits[index >> 5] &= ~(1 << (index & 0x1f));
    }
}

void Unk0209a11c::func_0209a27c(u32 start, u32 count, bool value) {
    u32 end = start + count;
    if (end > size) {
        return;
    }
    for (; start < end; start++) {
        func_0209a1c4(start, value);
    }
}

void Unk0209a11c::func_0209a2c4(u32 word, u32 index) {
    if (bits == 0) {
        bits = new u32[size >> 5];
        for (u32 i = 0; i < size >> 5; i++) {
            bits[i] = 0;
        }
    }
    bits[index] = word;
}
