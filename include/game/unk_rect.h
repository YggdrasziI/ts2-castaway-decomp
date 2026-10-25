/*
 * Integer rectangle of unit_02098BC8.cpp (x, y, width, height), used by the units
 * around it. All names are placeholders.
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

#endif
