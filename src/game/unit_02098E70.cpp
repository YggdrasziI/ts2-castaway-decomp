/*
 * Unit 0x02098E70-0x02099210: 2D and 3D vectors of 20.12 fixed-point numbers
 * (Unk02098e70, Unk02098ff0): constructors, squared length and length, scaling,
 * normalisation, clamping, sum, difference, dot product, interpolation.
 *
 * The classes derive from plain structs: a class with constructors copies member by
 * member, while the original copies these vectors as blocks (ldm / stm).
 *
 * Bounds: hypothesis. Before 0x02098E70 lies a rectangle class (0x02098BC8...)
 * that uses no vector; 0x02099210 starts unit_02099210.cpp (a heap). Real file
 * name unknown; the two classes may come from two files.
 * Not complete: func_02098e94 and func_02099000 do not match yet (comments above
 * them).
 */

#include "game/unk_vector.h"

Unk02098e70::Unk02098e70(int v) {
    x = v;
    y = v;
}

Unk02098e70::Unk02098e70(int x, int y) {
    this->x = x;
    this->y = y;
}

int Unk02098e70::func_02098e84() const {
    return func_02097a6c(func_02098e94());
}

/* 96.82 %: the two products sit in swapped register pairs (the original squares
 * x first into r2:r3). Term order, locals, casts and an inline helper were
 * tried. */
s64 Unk02098e70::func_02098e94() const {
    return (((s64)y * y) >> 12) + (((s64)x * x) >> 12);
}

Unk02098e70 &Unk02098e70::func_02098ec0(int f) {
    x = func_fxmul(x, f);
    y = func_fxmul(y, f);
    return *this;
}

Unk02098e70 &Unk02098e70::func_02098eec() {
    int length = func_02098e84();
    if (length != 0) {
        x = func_fxdiv(x, length);
        y = func_fxdiv(y, length);
    }
    return *this;
}

Unk02098e70 Unk02098e70::func_02098f38() const {
    Unk02098e70 v = *this;
    return v.func_02098eec();
}

Unk02098e70 &Unk02098e70::func_02098f74(int min, int max) {
    if (x < min) {
        x = min;
    }
    if (x > max) {
        x = max;
    }
    if (y < min) {
        y = min;
    }
    if (y > max) {
        y = max;
    }
    return *this;
}

Unk02098e70 Unk02098e70::func_02098fa8(const Unk02098e70 &o) const {
    return Unk02098e70(x + o.x, y + o.y);
}

Unk02098e70 Unk02098e70::func_02098fcc(const Unk02098e70 &o) const {
    return Unk02098e70(x - o.x, y - o.y);
}

int Unk02098ff0::func_02098ff0() const {
    return func_02097a6c(func_02099000());
}

/* 90.00 %: same register-pair swap as func_02098e94, plus the order of the two
 * 64-bit additions (the original adds x + y, then z). All six term orders, both
 * groupings and locals were tried. */
s64 Unk02098ff0::func_02099000() const {
    return (((s64)z * z) >> 12) + (((s64)y * y) >> 12) + (((s64)x * x) >> 12);
}

void Unk02098ff0::func_02099048(int f) {
    x = func_fxmul(x, f);
    y = func_fxmul(y, f);
    z = func_fxmul(z, f);
}

Unk02098ff0 &Unk02098ff0::func_02099088() {
    int length = func_02098ff0();
    if (length != 0) {
        x = func_fxdiv(x, length);
        y = func_fxdiv(y, length);
        z = func_fxdiv(z, length);
    }
    return *this;
}

Unk02098ff0 Unk02098ff0::func_020990ec() const {
    Unk02098ff0 v = *this;
    return v.func_02099088();
}

Unk02098ff0 Unk02098ff0::func_0209911c(const Unk02098ff0 &o) const {
    return Unk02098ff0(x + o.x, y + o.y, z + o.z);
}

Unk02098ff0 Unk02098ff0::func_02099150(const Unk02098ff0 &o) const {
    return Unk02098ff0(x - o.x, y - o.y, z - o.z);
}

int Unk02098ff0::func_02099184(const Unk02098ff0 &o) const {
    return (int)(((s64)x * o.x + (s64)y * o.y + (s64)z * o.z) >> 12);
}

Unk02098ff0 Unk02098ff0::func_020991b8(const Unk02098ff0 &o, int t) const {
    return Unk02098ff0(((x * (0x1000 - t)) >> 12) + ((o.x * t) >> 12),
                       ((y * (0x1000 - t)) >> 12) + ((o.y * t) >> 12),
                       ((z * (0x1000 - t)) >> 12) + ((o.z * t) >> 12));
}
