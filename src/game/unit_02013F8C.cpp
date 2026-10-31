/*
 * Unit 0x02013F8C-0x020142E0: the microgame base `Unk02013f8c`, the layout of its
 * screen, a blinking element and the exit test.
 *
 * Bounds: hypothesis. The start is the constructor called by the derived
 * microgames, the end follows the last virtual function of the vtable at
 * 0x020B80A0 (its `.data`: the two debug strings, then the vtable). Real file name
 * unknown.
 */

#include "game/unk_microgame.h"

extern "C" {
void func_020897b4(const char *fmt, ...);
void func_020a9dc4(Unk020a9d58 *layout, int type, int flag);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a8048(Unk020a7c90 *s, u32 hash);
void func_020a8078(Unk020a7c90 *s, int x);
void func_020a808c(Unk020a7c90 *s, int x);
void func_020a9990(Unk020a7c90 *s, int x);
void func_020a99ac(Unk020a7c90 *s, int x);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a7d30(Unk020a7c90 *s, int x);
void func_020a7dd4(Unk020a7c90 *s, u32 hash);
void func_020a7df0(Unk020a7c90 *s, u32 hash);
}
int func_020972c0(int key);

Unk02013f8c::Unk02013f8c(const char *name, u32 hash, Unk02093648 *file, int a, int b)
    : Unk020a5ccc(file, a, b), layout(file, 0) {
    Unk020a7c90 *s;

    timer = 30;
    this->name = name;
    func_020897b4("Starting %s!", name);
    func_020a5ea4(&layout);
    func_020a9dc4(&layout, 3, 1);
    func_020a9dc4(&layout, 2, 1);
    func_020a9dc4(&layout, 0, 1);
    func_020a9dc4(&layout, 5, 1);
    func_020a9dc4(&layout, 6, 1);

    s = func_020aa040(&layout, 6, 0);
    func_020a8048(s, hash);
    func_020a808c(s, 0x10);

    s = func_020aa040(&layout, 5, 0);
    func_020a8048(s, 0x1c802ada);
    func_020a8078(s, 0xf);
    func_020a808c(s, 1);

    s = func_020aa040(&layout, 2, 0);
    func_020a6980(s, hash);
    func_020a7cf0(s, true);

    s = func_020aa040(&layout, 3, 0);
    func_020a9990(s, 0);
    func_020a7cf0(s, false);
    func_020a99ac(s, 0x9c3);
    func_020a7c90(s, 0x40000);
    func_020a7cac(s, 0x80000);
    func_020a7d30(s, 0);

    s = func_020aa040(&layout, 0, 0);
    func_020a7dd4(s, 0x1c802ada);
    func_020a7df0(s, 0x7a91dd1b);
}

Unk02013f8c::~Unk02013f8c() {
    func_020897b4("Killing %s!", name);
}

void Unk02013f8c::func_10(bool a) {
    func_020aa06c(&layout, a);
    if (a == 1) {
        *(volatile u16 *)0x5000614 = *(volatile u16 *)0x5000402;
    }
}

bool Unk02013f8c::func_18() {
    if (timer == 0) {
        timer = 30;
        Unk020a7c90 *a = func_020aa040(&layout, 3, 0);
        Unk020a7c90 *b = func_020aa040(&layout, 3, 0);
        func_020a7cf0(b, func_020a7d1c(a) ^ 1);
    } else {
        timer--;
    }
    func_020aa158(&layout);
    return func_020972c0(3) != 1;
}

void Unk02013f8c::func_14() {}

void Unk02013f8c::func_1c() {}
