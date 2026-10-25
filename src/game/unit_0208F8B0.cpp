/*
 * Unit 0x0208F8B0-0x0208FF50: the 40-byte object entry (Unk0208f8b0) handed out by
 * the object manager of unit_020916A4.cpp. It builds the OAM attributes of one
 * object: size and shape (from the four tables below), 16 or 256 colors, mode,
 * priority, palette, flips and affine parameter set; it keeps the file of its
 * pixels (Unk02095140) and a block of the heap of unit_02099210.cpp for them.
 *
 * Bounds: hypothesis. Before 0x0208F8B0 lie small functions of another class
 * (virtual call at 0x1c, fields 0x12 and 0x14); 0x0208FF50 starts
 * unit_0208FF50.cpp. The constructor is the only one building this layout, and the
 * tables at 0x020B38B8-0x020B38E8 are only read here. Real file name unknown.
 */

#include "game/unk_resource.h"
#include "game/unk_heap.h"
#include "game/unk_oam.h"

extern "C" {
Unk020c8440 *func_020999e8(int id);
void *func_020993b0(Unk020c8440 *heap, u32 size, Unk02099210Handle *handle);
void func_02099654(Unk020c8440 *heap, Unk02099210Handle *handle);
u32 func_020997a4(Unk020c8440 *heap);
void func_02099b90(u32 data, void *dest, u32 size);
}

/* Width and height in pixels of each size (index & 3) and shape (index >> 2). */
extern const u8 data_020b38b8[12];
extern const u8 data_020b38c4[12];
/* Their base-2 logarithms. */
extern const u8 data_020b38d0[12];
extern const u8 data_020b38dc[12];

/* Declared in this order to get the ROM order (notes/MATCHING.md, data layout). */
const u8 data_020b38d0[12] = {3, 4, 5, 6, 4, 5, 5, 6, 3, 3, 4, 5};
const u8 data_020b38c4[12] = {8, 16, 32, 64, 8, 8, 16, 32, 16, 32, 32, 64};
const u8 data_020b38b8[12] = {8, 16, 32, 64, 16, 32, 32, 64, 8, 8, 16, 32};
const u8 data_020b38dc[12] = {3, 4, 5, 6, 3, 3, 4, 5, 4, 5, 5, 6};

Unk0208f8b0::Unk0208f8b0() {
    unk0 = 0;
    unk4 = 0;
    unk8 = 0;
    unkC = 0;
    unk10_0 = 0;
    unk10_2 = 0;
    unk10_4 = 0;
    unk10_11 = 0;
    unk10_13 = 0;
    unk10_14 = 0;
    unk10_22 = 0;
    unk14 = -1;
    unk18 = -1;
    unk1c = 0;
    unk20 = 0;
}

void Unk0208f8b0::func_0208f90c(Unk02095140 *file) {
    Unk02095140Header *header;
    int size;
    int shape;

    if (unk20 != 0) {
        return;
    }
    if (file == 0) {
        return;
    }
    if (!file->func_02094f88()) {
        return;
    }
    header = file->func_02095180();
    if (!func_0208fc14(header->width * 8, header->height * 8, &size, &shape)) {
        return;
    }
    func_0208fadc(size, shape);
    func_0208fb44(header->bpp == 8);
    if (header->bpp == 4) {
        func_0208fb98(header->unkC);
    }
    unk1c = file;
    file->func_02094f9c();
    func_0208faac(0);
}

void Unk0208f8b0::func_0208f9dc() {
    if (unk20 != 0) {
        return;
    }
    unk0 = 0;
    unk4 = 0;
    unk8 = 0;
    unkC = 0;
    unk14 = -1;
    unk18 = -1;
    unk1c = 0;
    unk20 = 0;
}

void Unk0208f8b0::func_0208fa14(int heap) {
    if (unk20 != 0) {
        func_0208fe80(heap);
    }
    unk8 = 0;
    unkC = 0;
    unk0 = 0;
    unk4 = 0;
    unk10_22 = 0;
    func_0208fa60();
}

void Unk0208f8b0::func_0208fa60() {
    if (unk1c == 0) {
        return;
    }
    unk1c->func_02094fb8();
    unk1c = 0;
}

int Unk0208f8b0::func_0208fa84() {
    if (unk1c == 0) {
        return 0;
    }
    return unk1c->func_02095180()->count;
}

int Unk0208f8b0::func_0208faa4() {
    return unk18;
}

void Unk0208f8b0::func_0208faac(int frame) {
    if (unk1c == 0) {
        return;
    }
    if (frame < 0) {
        return;
    }
    if (frame < func_0208fa84()) {
        unk18 = frame;
    }
}

void Unk0208f8b0::func_0208fadc(int size, int shape) {
    int i;

    if (unk20 != 0) {
        return;
    }
    i = size + shape * 4;
    unk8 = unk8 | (shape << 14) | (size << 30);
    unk10_0 = data_020b38d0[i] - 3;
    unk10_2 = data_020b38dc[i] - 3;
}

void Unk0208f8b0::func_0208fb44(int color256) {
    if (unk20 != 0) {
        return;
    }
    if (color256) {
        unk8 |= 0x2000;
    } else {
        unk8 &= ~0x2000;
    }
}

void Unk0208f8b0::func_0208fb6c(int mode) {
    unk8 = (unk8 & ~0xC00) | (mode << 10);
}

void Unk0208f8b0::func_0208fb80(int priority) {
    unkC = (unkC & ~0xC00) | ((priority & 3) << 10);
}

void Unk0208f8b0::func_0208fb98(int palette) {
    unkC = (unkC & ~0x1F000) | (palette << 12);
}

void Unk0208f8b0::func_0208fbac(int flip) {
    if (func_0208fcf0()) {
        return;
    }
    if (flip) {
        unk8 |= 0x10000000;
    } else {
        unk8 &= ~0x10000000;
    }
}

void Unk0208f8b0::func_0208fbe0(int flip) {
    if (func_0208fcf0()) {
        return;
    }
    if (flip) {
        unk8 |= 0x20000000;
    } else {
        unk8 &= ~0x20000000;
    }
}

bool Unk0208f8b0::func_0208fc14(int width, int height, int *size, int *shape) {
    int i;

    for (i = 0; i < 12; i++) {
        if (data_020b38b8[i] == width && data_020b38c4[i] == height) {
            *size = i & 3;
            *shape = i >> 2;
            return true;
        }
    }
    return false;
}

int Unk0208f8b0::func_0208fc74() {
    if (unk8 & 0x2000) {
        return (1 << (unk10_0 + 3)) * (1 << (unk10_2 + 3));
    }
    return ((1 << (unk10_0 + 3)) * (1 << (unk10_2 + 3))) >> 1;
}

void Unk0208f8b0::func_0208fcd8(int affine) {
    unk8 = affine ? (unk8 | 0x100) : (unk8 & ~0x100);
}

bool Unk0208f8b0::func_0208fcf0() {
    return (unk8 & 0x100) != 0;
}

void Unk0208f8b0::func_0208fd04(int index) {
    unk8 = (unk8 & ~0x3E000000) + ((index & 0x1F) << 25);
}

int Unk0208f8b0::func_0208fd1c() {
    return (unk8 & 0x3E000000) >> 25;
}

bool Unk0208f8b0::func_0208fd2c() {
    return unk10_11;
}

void Unk0208f8b0::func_0208fd44(int unk) {
    unk10_11 = unk;
}

bool Unk0208f8b0::func_0208fd5c() {
    return unk10_12;
}

void Unk0208f8b0::func_0208fd74(int unk) {
    unk10_12 = unk;
}

int Unk0208f8b0::func_0208fd8c() {
    return unk10_14;
}

void Unk0208f8b0::func_0208fd9c(int next) {
    unk10_14 = next;
}

void Unk0208f8b0::func_0208fdb4(int index) {
    unk10_4 = index;
}

int Unk0208f8b0::func_0208fdcc() {
    return unk10_4;
}

void Unk0208f8b0::func_0208fddc() {
    if (unk1c != 0) {
        return;
    }
    func_0208fe08(unk10_13 ? 6 : 7);
}

bool Unk0208f8b0::func_0208fe08(int heap) {
    Unk020c8440 *h;
    void *block;
    u32 offset;

    if (unk20 != 0) {
        return false;
    }
    h = func_020999e8(heap);
    block = func_020993b0(h, func_0208fc74(), (Unk02099210Handle *)&unk20);
    if (block == 0) {
        return false;
    }
    offset = (u32)block - func_020997a4(h);
    unkC = (unkC & ~0x3FF) | (offset >> h->alignShift);
    return true;
}

void Unk0208f8b0::func_0208fe80(int heap) {
    if (unk20 == 0) {
        return;
    }
    if (unk10_21) {
        unk10_21 = 0;
    } else {
        func_02099654(func_020999e8(heap), (Unk02099210Handle *)&unk20);
    }
    unk20 = 0;
    unk18 = -1;
    unk14 = -1;
}

void Unk0208f8b0::func_0208fed4(Unk0208f8b0 *other) {
    if (other->unk1c == 0) {
        return;
    }
    if (unk1c != other->unk1c) {
        return;
    }
    unk20 = other->unk20;
    unkC = (unkC & ~0x3FF) | (other->unkC & 0x3FF);
    unk10_21 = 1;
}

void Unk0208f8b0::func_0208ff24(u32 data) {
    void *dest = unk20;

    if (dest == 0) {
        return;
    }
    func_02099b90(data, dest, func_0208fc74());
}
