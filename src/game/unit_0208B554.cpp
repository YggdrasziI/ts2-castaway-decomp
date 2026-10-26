/*
 * Unit 0x0208B554-0x0208BE3C: a pool of objects (Unk020c7d38, one static object
 * data_020c7d38). It allocates on its heap (0x15C) an array of 0x40-byte objects
 * (Unk0208b554Item, include/game/unk_poolitem.h) with two
 * u16 index tables, two pairs of word buffers and 0x84-byte records, a table of
 * 0x30-byte records (a 3x3 matrix and a vector) and two word tables; two bit
 * sets mark the objects in use. It also keeps two rows of four 0x14-byte records
 * (a vector and four s16) reset together.
 *
 * Bounds: hypothesis. Before 0x0208B554 lies unit_0208B41C.cpp (another class);
 * 0x0208BE3C starts unit_0208BE3C.cpp. The static initializer (0x020AE2B8) builds
 * data_020c7d38 and registers its destructor (chain node 0x020C7D2C). The element constructors and
 * destructors emitted after func_0208b744 are the inline ones it passes to
 * __cxa_vec_new. Real file name unknown.
 */

#include "game/unk_pool.h"

extern "C" {
void func_01ff924c(Unk0208adc0 *obj, Unk0208af38 *arg, int value);
void func_02099afc(int id);
void func_02099b28(void);
void func_02099b90(u32 data, void *dest, u32 size);
int func_02077c60(int a, int b);
}

Unk020c7d38 data_020c7d38;

Unk020c7d38::Unk020c7d38()
    : count(0), unk4(0), unk8(0), capacity(0x80), bufferWords(0), recordCount(0), frameCount(0x10), items(0),
      unk38(0), unk3c(0), unk40(0), unk54(0), unk58(0), unk5c(0), unk60(0), unk64(0), unk68(0), unk6c(0x4cd),
      unk70(0xc8000), unk74(0x1555), unk78(0xe80), unk7c(0xb90 - 0x4cd), unk80(0x3200), unk94(0), flags(0),
      unk15a(0), heap(0) {
    func_0208b99c(0x80, 0x2000);
    for (int i = 0; i < 2; i++) {
        buffers[i] = 0;
        records[i] = 0;
    }
    resetLights();
}

Unk020c7d38::~Unk020c7d38() {
    func_0208b9dc();
}

void Unk020c7d38::func_0208b744() {
    if (items != 0) {
        func_0208b9dc();
    }
    func_02099afc(heap);
    items = new Unk0208b554Item[capacity];
    unk20 = new u16[capacity];
    unk24 = new u16[capacity];
    for (int i = 0; i < capacity; i++) {
        unk20[i] = i;
        unk24[i] = 0x7fff;
        items[i].index = i;
    }
    count = 0;
    for (int j = 0; j < 2; j++) {
        buffers[j] = new u32[bufferWords];
        records[j] = new Unk0208b554Record[recordCount];
    }
    unk38 = new int[capacity];
    frames = new Unk0208b554Frame[frameCount];
    unk3c = new int[capacity];
    func_02099b90(-1, unk3c, capacity * 4);
    func_02099b28();
}

void Unk020c7d38::func_0208b99c(u32 count, u32 size) {
    if (items != 0) {
        return;
    }
    if (count < 0x10) {
        count = 0x10;
    }
    if (count > 0x100) {
        count = 0x100;
    }
    if (size < 0x400) {
        size = 0x400;
    }
    if (size > 0x8000) {
        size = 0x8000;
    }
    recordCount = count;
    bufferWords = (size + 3) >> 2;
}

void Unk020c7d38::func_0208b9dc() {
    resetLights();
    for (int i = 0; i < count; i++) {
        if (func_0208bcd0(i)) {
            func_0208bc68(i, false);
        }
    }
    if (unk20 != 0) {
        delete[] unk20;
    }
    if (unk24 != 0) {
        delete[] unk24;
    }
    if (items != 0) {
        delete[] items;
    }
    items = 0;
    count = 0;
    if (unk38 != 0) {
        delete[] unk38;
    }
    unk38 = 0;
    if (frames != 0) {
        delete[] frames;
    }
    frames = 0;
    if (unk3c != 0) {
        delete[] unk3c;
    }
    unk3c = 0;
    unk4 = 0;
    unk8 = 0;
    unk40 = 0;
    unk15a = 0;
    flags = 0;
    for (int j = 0; j < 2; j++) {
        if (records[j] != 0) {
            delete[] records[j];
        }
        records[j] = 0;
        if (buffers[j] != 0) {
            delete[] buffers[j];
        }
        buffers[j] = 0;
    }
    used.func_0209a164();
    active.func_0209a164();
}

int Unk020c7d38::func_0208bbf4(int key) {
    if (count >= capacity) {
        return -1;
    }
    if (items == 0) {
        func_0208b744();
    }
    int index = count;
    items[index].func_0208ac48(key);
    count++;
    unk38[index] = 0;
    func_0208bc68(index, true);
    return index;
}

void Unk020c7d38::func_0208bc68(int index, bool on) {
    if (index < 0) {
        return;
    }
    if (index >= count) {
        return;
    }
    if (!on) {
        if (active.func_0209a188(index)) {
            items[index].func_0208ad60();
        }
        active.func_0209a1c4(index, false);
    }
    used.func_0209a1c4(index, on);
}

bool Unk020c7d38::func_0208bcd0(int index) {
    if (index < 0 || index >= count) {
        return false;
    }
    return used.func_0209a188(index);
}

Unk0208b554Item *Unk020c7d38::func_0208bcfc(int index) {
    if (index >= 0 && index < count) {
        return &items[index];
    }
    return 0;
}

int Unk020c7d38::func_0208bd20(Unk0208b554Item *item) {
    if (items == 0) {
        return -1;
    }
    u32 index = func_02077c60((char *)item - (char *)items, 0x40) >> 12;
    if (index >= (u32)count) {
        return -1;
    }
    return index;
}

void Unk020c7d38::func_0208bd58(int index, u16 value) {
    if (index < 0) {
        return;
    }
    if (index >= count) {
        return;
    }
    if (value != unk24[index]) {
        flags |= 2;
        unk24[index] = value;
    }
    Unk0208af38 arg;
    Unk0208b554Item *item = &items[index];
    u32 level = ((u32)value << 6) >> 16;
    if (level > 0x3f) {
        level = 0x3f;
    }
    arg.func_0208b25c(level);
    func_01ff924c(item->func_0208ad18(), &arg, 0x3f000000);
}

Unk0208b554Frame *Unk020c7d38::func_0208be18(int index) {
    return &frames[index];
}

void Unk020c7d38::func_0208be28(int index, int value) {
    if (value < frameCount) {
        unk3c[index] = value;
    }
}
