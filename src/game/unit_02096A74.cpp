/*
 * Unit 0x02096A74-0x020970E0: system set-up. Projection matrix from the view
 * parameters, the start-up sequence (power, interrupts, VBlank handler, input, the
 * object stored in data_020c7f78), 3D display settings, VRAM bank allocation and
 * the VRAM heaps 4 to 7 placed in the banks.
 *
 * Bounds: hypothesis. Before 0x02096A74 come the two destructors of the class whose
 * vtable is data_020bd54c (its constructor is before them); func_020970e0 starts the
 * button state code. The start-up entry points are called from 0x02000BA8-0x02000BB0.
 * The data 0x020C7F74-0x020C7F80 have no other user. Real file
 * name unknown.
 */

#include "game/unk_matrix.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

class Unk0208a0a8 {
public:
    Unk0208a0a8();
    static void func_0208ab3c(Unk0208a0a8 *library);

    int unk[4];
};

extern "C" void func_02077e50();
extern "C" void func_02077e54();
extern "C" void func_02077ef8();
extern "C" void GX_VBlankIntr(int enable);
extern "C" u32 func_0207812c();
extern "C" u32 func_02078144();
extern "C" u32 func_0207815c();
extern "C" u32 func_020780fc();
extern "C" void GX_SetBankForSubOBJ(int x);
extern "C" void GX_SetBankForSubBG(int x);
extern "C" void GX_SetBankForTexPltt(int x);
extern "C" void GX_SetBankForTex(int x);
extern "C" void GX_SetBankForOBJ(int x);
extern "C" void GX_SetBankForBG(int x);
extern "C" void func_02078b98(const Unk02098094 *m);
extern "C" void G3X_InitTable();
extern "C" void G3X_SetClearColor(u16 rgb, int alpha, int depth, int polygonId, int fog);
extern "C" void G3X_InitMtxStack();
extern "C" void G3X_Init();
extern "C" void func_0207a174(int mask, void (*handler)());
extern "C" void OS_EnableIrqMask(int mask);
extern "C" void func_0207b47c();
extern "C" void func_0207b4cc();
extern "C" void func_0207bbd4();
extern "C" int OS_EnableInterrupts();
extern "C" void func_0207cf0c();
extern "C" void func_0208dac8();
void func_020916a4();
extern "C" void func_02095134(int x);
extern "C" void *func_020999e8(int id);
extern "C" int func_02099a0c(void *start, u32 size, u32 alignShift, u8 inlineHeader, int id);
extern "C" void func_02099aa8(int id);
extern "C" void func_02099870();
void func_020970e0();
void func_02097434();
void func_020973bc();

class Unk020c80b0 {
public:
    void func_02099828();
};

Unk020c80b0 *func_02099834();

extern char data_027e0000[];

/* Declaration order chosen to reproduce the .bss layout (notes/MATCHING.md).
 * data_020c7f74 has no user; of the lock word data_020c7f7c only the first byte is
 * set (a SWPB under -avoid_byte strb, notes/COMPILER.md). */
Unk0208a0a8 *data_020c7f78;
int data_020c7f74;
u8 data_020c7f7c[4];

void func_02096d5c();
void func_02096d78();
void func_02096dac(int a, int b, int c, int d, int e, int f);
void func_02096e60(int a, int b, int c, int d, int e, int f);
int func_02097058(int size);

Unk02098094 func_02096a74(int a, int b, int c, int d, int e) {
    int m00 = func_fxdiv(b, (c * a) >> 12);
    int m11 = func_fxdiv(b, a);
    int range = e - d;
    int m22 = func_fxdiv(e + d, range);
    int m23 = func_fxdiv((e * d) >> 11, range);

    *(volatile u32 *)0x4000440 = 0;
    Unk02098094 m(m00, 0, 0, 0, 0, m11, 0, 0, 0, 0, m22, -m23, 0, 0, 0x1000, 0);
    func_02078b98(&m);
    *(volatile u32 *)0x4000440 = 2;
    return m;
}

void func_02096b70() {
    func_0207b4cc();
    func_0207b47c();
    func_02099870();
    func_02099834()->func_02099828();
}

void func_02096b8c() {
    func_0207bbd4();
    func_02077e50();
    func_02077ef8();
    G3X_Init();
    func_0207cf0c();
    G3X_InitTable();
    G3X_InitMtxStack();
    *(volatile u16 *)0x4000304 = (*(volatile u16 *)0x4000304 & ~0x20e) | 0xe | 0x200;
    func_02077e54();
    *(volatile u32 *)0x4001000 |= 0x10000;
    func_02096d78();
    func_0207a174(1, func_02096d5c);
    OS_EnableIrqMask(1);
    GX_VBlankIntr(1);
    {
        u16 prev = *(volatile u16 *)0x4000208;
        *(volatile u16 *)0x4000208 = 1;
    }
    OS_EnableInterrupts();
    func_02095134(3);
    func_020970e0();
    func_02097434();
    func_020973bc();
    func_020916a4();
    func_0208dac8();
    data_020c7f78 = new Unk0208a0a8;
    Unk0208a0a8::func_0208ab3c(data_020c7f78);
    *(volatile u32 *)0x4000580 = 0xbfff0000;
    func_02096a74(0x6c3, 0xe80, 0x1555, 0x333, 0xc8000);
}

void func_02096cb0() {
    *(volatile u16 *)0x4000060 = (*(volatile u16 *)0x4000060 & ~0x3002) | 2;
    *(volatile u16 *)0x4000060 = (*(volatile u16 *)0x4000060 & ~0x3000) | 8;
    *(volatile u16 *)0x4000060 = (*(volatile u16 *)0x4000060 & ~0x3000) | 0x10;
    G3X_SetClearColor(0x7def, 1, 0x7fff, 0x3f, 1);
    *(volatile u32 *)0x4000580 = 0xbfff0000;
    func_02096a74(0x6c3, 0xe80, 0x1555, 0x333, 0xc8000);
}

void func_02096d5c() {
    *(volatile u32 *)((u32)data_027e0000 + 0x3ff8) |= 1;
}

void func_02096d78() {
    func_02096dac(0xf, 0x10, 0x20, 0x80, 0x40, 0x100);
}

void func_02096dac(int a, int b, int c, int d, int e, int f) {
    GX_SetBankForTex(0);
    GX_SetBankForTexPltt(0);
    GX_SetBankForBG(0);
    GX_SetBankForSubBG(0);
    GX_SetBankForOBJ(0);
    GX_SetBankForSubOBJ(0);
    GX_SetBankForTex(a);
    GX_SetBankForTexPltt(b);
    GX_SetBankForBG(c);
    GX_SetBankForSubBG(d);
    GX_SetBankForOBJ(e);
    GX_SetBankForSubOBJ(f);
    func_02096e60(a, b, c, d, e, f);
    data_020c7f7c[0] = 1;
}

void func_02096e60(int a, int b, int c, int d, int e, int f) {
    u8 *main = (u8 *)0x6800000;
    u8 *sub = (u8 *)0x6880000;
    int mainShift;
    int subShift;

    switch (a) {
    case 2:
    case 6:
    case 14:
        main += 0x20000;
        break;
    case 4:
    case 12:
        main += 0x40000;
        break;
    case 8:
        main += 0x60000;
        break;
    }
    switch (b) {
    case 0x20:
    case 0x60:
        sub = (u8 *)0x6890000;
        break;
    case 0x40:
        sub = (u8 *)0x6894000;
        break;
    }
    if (func_020999e8(4)) {
        func_02099aa8(4);
    }
    if (func_020999e8(5)) {
        func_02099aa8(5);
    }
    if (func_020999e8(6)) {
        func_02099aa8(6);
    }
    if (func_020999e8(7)) {
        func_02099aa8(7);
    }
    if (func_02078144()) {
        func_02099a0c(main, func_02078144(), 3, 0, 4);
    }
    if (func_0207812c()) {
        func_02099a0c(sub, func_0207812c(), 4, 0, 5);
    }
    mainShift = func_02097058(func_0207815c());
    subShift = func_02097058(func_020780fc());
    if (func_0207815c()) {
        func_02099a0c((void *)0x6400000, func_0207815c(), mainShift, 0, 6);
    }
    if (func_020780fc()) {
        func_02099a0c((void *)0x6600000, func_020780fc(), subShift, 0, 7);
    }
    *(volatile u32 *)0x4000000 = (*(volatile u32 *)0x4000000 & ~0x300000) + ((mainShift - 5) << 20);
    *(volatile u32 *)0x4001000 = (*(volatile u32 *)0x4001000 & ~0x300000) + ((subShift - 5) << 20);
}

int func_02097058(int size) {
    int shift = 5;

    switch (size) {
    case 0:
        shift = 0;
        break;
    case 0x4000:
    case 0x8000:
        shift = 5;
        break;
    case 0x10000:
        shift = 6;
        break;
    case 0x14000:
    case 0x18000:
    case 0x20000:
        shift = 7;
        break;
    case 0x40000:
        shift = 8;
        break;
    }
    return shift;
}
