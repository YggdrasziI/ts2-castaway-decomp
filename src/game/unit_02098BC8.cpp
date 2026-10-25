/*
 * Unit 0x02098BC8-0x02098E70: an integer rectangle (Unk02098bc8: x, y, width,
 * height): constructors, point test, overlap test, and the subtraction of another
 * rectangle into at most four pieces.
 *
 * Bounds: hypothesis. Before 0x02098BC8 lies a plane class built on the 3D vector
 * (func_02098824...); 0x02098E70 starts unit_02098E70.cpp (vectors), which the
 * rectangle does not use. Real file name unknown.
 */

#include "game/unk_rect.h"

Unk02098bc8::Unk02098bc8() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Unk02098bc8::Unk02098bc8(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Unk02098bc8::func_02098bf4(int px, int py) const {
    bool inside = true;

    if (px < x) {
        inside = false;
    }
    if (px > x + w) {
        inside = false;
    }
    if (py < y) {
        inside = false;
    }
    if (py > y + h) {
        inside = false;
    }
    return inside;
}

bool Unk02098bc8::func_02098c3c(const Unk02098bc8 &o) const {
    if (o.x < x + w && o.y < y + h && o.x + o.w > x && o.y + o.h > y) {
        return true;
    }
    return false;
}

int Unk02098bc8::func_02098c98(const Unk02098bc8 &o, Unk02098bc8 *out) const {
    int left;
    int top;
    int right;
    int bottom;
    int height;
    int count;

    if (!func_02098c3c(o)) {
        out[0] = *this;
        return 1;
    }
    top = o.y - y;
    bottom = (y + h) - (o.y + o.h);
    left = o.x - x;
    right = (x + w) - (o.x + o.w);
    height = o.h;
    if (top < 0) {
        height += top;
    }
    count = 0;
    if (bottom < 0) {
        height += bottom;
    }
    if (top > 0) {
        out[count++] = Unk02098bc8(x, y, w, top);
    }
    if (bottom > 0) {
        out[count++] = Unk02098bc8(x, o.y + o.h, w, bottom);
    }
    if (top < 0) {
        top = 0;
    }
    if (height > 0) {
        if (left > 0) {
            out[count++] = Unk02098bc8(x, y + top, left, height);
        }
        if (right > 0) {
            out[count++] = Unk02098bc8(o.x + o.w, y + top, right, height);
        }
    }
    return count;
}
