/*
 * Integer rectangle of unit_02098BC8.cpp (x, y, width, height), used by the units
 * around it, and the base class of unit_02092704.cpp that holds one. All names are
 * placeholders.
 */
#ifndef GAME_UNK_RECT_H
#define GAME_UNK_RECT_H

class Unk02098bc8 {
public:
    Unk02098bc8();
    Unk02098bc8(int x, int y, int w, int h);
    bool func_02098bf4(int px, int py) const;
    bool func_02098c3c(const Unk02098bc8 &o) const;
    int func_02098c98(const Unk02098bc8 &o, Unk02098bc8 *out) const;

    int x;
    int y;
    int w;
    int h;
};

typedef unsigned short u16;

/* Base class of unit_02092704.cpp: a screen rectangle and three halfwords. */
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

#endif
