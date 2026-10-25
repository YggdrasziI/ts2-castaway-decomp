/*
 * Unit 0x02092704-0x02092830: a base class (Unk02092704) holding a rectangle that
 * defaults to the 256 x 192 screen in 20.12 fixed point and three halfwords. Its
 * setters store the rectangle or the low four bits of the first halfword and call
 * two virtual functions that are empty here.
 *
 * Bounds: hypothesis. The vtable data_020bd2a4 is only used by the constructor;
 * the class derived at 0x02090CD4 calls the constructor and the base destructor;
 * 0x02092830 starts code without a vtable. Real file name unknown.
 */

#include "game/unk_rect.h"

typedef unsigned short u16;

class Unk02092704 {
public:
    Unk02092704();
    virtual ~Unk02092704();
    void func_0209276c(int x, int y);
    virtual void func_020927bc();
    virtual void func_02092788();
    void func_0209278c(int w, int h);
    void func_020927c0(const Unk02098bc8 *rect);
    void func_02092808(int a, int b);

    u16 unk4;
    u16 unk6;
    u16 unk8;
    Unk02098bc8 rect;
};

Unk02092704::Unk02092704() : unk4(0), unk6(0), unk8(0), rect(0, 0, 0x100000, 0xc0000) {}

Unk02092704::~Unk02092704() {}

void Unk02092704::func_0209276c(int x, int y) {
    rect.x = x;
    rect.y = y;
    func_02092788();
}

void Unk02092704::func_02092788() {}

void Unk02092704::func_0209278c(int w, int h) {
    rect.w = w;
    rect.h = h;
    func_020927bc();
    func_02092788();
}

void Unk02092704::func_020927bc() {}

void Unk02092704::func_020927c0(const Unk02098bc8 *rect) {
    this->rect = *rect;
    func_020927bc();
    func_02092788();
}

void Unk02092704::func_02092808(int a, int b) {
    unk4 = (unk4 & ~0xf) | a | b;
    func_02092788();
}
