/*
 * Unit 0x02097B6C-0x02098094: 20.12 fixed-point 3x3 matrix (Unk02097b6c):
 * constructors, identity, scale, product, transpose, vector product, rotations
 * about the three axes, rotation from three angles.
 *
 * Bounds: hypothesis. Before 0x02097B6C lie fixed-point helpers (hardware square
 * root, arc cosine table); from 0x02098094 come functions on another matrix type
 * that do not use this constructor. Real file name unknown.
 * Not complete: func_02097f78 does not match yet (comment above it).
 */

#include "game/unk_matrix.h"

typedef unsigned short u16;

extern "C" const short data_020af1e8[];

static inline int func_sin(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2];
}

static inline int func_cos(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2 + 1];
}

Unk02097b6c::Unk02097b6c(int m00, int m01, int m02, int m10, int m11, int m12, int m20, int m21, int m22) {
    m[0][0] = m00;
    m[1][0] = m01;
    m[2][0] = m02;
    m[0][1] = m10;
    m[1][1] = m11;
    m[2][1] = m12;
    m[0][2] = m20;
    m[1][2] = m21;
    m[2][2] = m22;
}

Unk02097b6c::Unk02097b6c(const Unk02097bacSrc &o) {
    m[0][0] = o.m[0][0];
    m[1][0] = o.m[1][0];
    m[2][0] = o.m[2][0];
    m[0][1] = o.m[0][1];
    m[1][1] = o.m[1][1];
    m[2][1] = o.m[2][1];
    m[0][2] = o.m[0][2];
    m[1][2] = o.m[1][2];
    m[2][2] = o.m[2][2];
}

Unk02097b6c Unk02097b6c::func_02097bf8() {
    return Unk02097b6c(0x1000, 0, 0, 0, 0x1000, 0, 0, 0, 0x1000);
}

Unk02097b6c Unk02097b6c::func_02097c2c(const Unk02098ff0 &scale) {
    return Unk02097b6c(scale.x, 0, 0, 0, scale.y, 0, 0, 0, scale.z);
}

void Unk02097b6c::func_02097c6c(const Unk02097b6c &a, const Unk02097b6c &b) {
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m[j][i] = (int)((((s64)b.m[0][i] * a.m[j][0]) >> 12) + (((s64)b.m[1][i] * a.m[j][1]) >> 12) +
                            (((s64)b.m[2][i] * a.m[j][2]) >> 12));
        }
    }
}

Unk02097b6c Unk02097b6c::func_02097cec() const {
    return Unk02097b6c(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}

Unk02098ff0 Unk02097b6c::func_02097d38(const Unk02098ff0 &v) const {
    return Unk02098ff0((int)((((s64)v.x * m[0][0]) >> 12) + (((s64)v.y * m[1][0]) >> 12) + (((s64)v.z * m[2][0]) >> 12)),
                       (int)((((s64)v.x * m[0][1]) >> 12) + (((s64)v.y * m[1][1]) >> 12) + (((s64)v.z * m[2][1]) >> 12)),
                       (int)((((s64)v.x * m[0][2]) >> 12) + (((s64)v.y * m[1][2]) >> 12) + (((s64)v.z * m[2][2]) >> 12)));
}

Unk02097b6c Unk02097b6c::func_02097df8(int angle) {
    int s = func_sin(angle);
    int c = func_cos(angle);
    return Unk02097b6c(0x1000, 0, 0, 0, c, -s, 0, s, c);
}

Unk02097b6c Unk02097b6c::func_02097e5c(int angle) {
    int s = func_sin(angle);
    int c = func_cos(angle);
    return Unk02097b6c(c, 0, s, 0, 0x1000, 0, -s, 0, c);
}

Unk02097b6c Unk02097b6c::func_02097ebc(int angle) {
    int s = func_sin(angle);
    int c = func_cos(angle);
    return Unk02097b6c(c, -s, 0, s, c, 0, 0, 0, 0x1000);
}

Unk02097b6c Unk02097b6c::func_02097f1c(int z, int y, int x) {
    Unk02097b6c r;
    Unk02097b6c rz = func_02097ebc(z);
    Unk02097b6c yx;
    Unk02097b6c ry = func_02097e5c(y);
    Unk02097b6c rx = func_02097df8(x);

    yx.func_02097c6c(ry, rx);
    r.func_02097c6c(rz, yx);
    return r;
}

/* 51.49 %: same products, but the original computes the table indices of c, b,
 * then a, loads sin b, cos c, sin c, sin a, cos b, cos a, and schedules the nine
 * elements in another order. Local orders, index locals and int / short types were
 * tried. */
Unk02097b6c Unk02097b6c::func_02097f78(int a, int b, int c) {
    short sc = func_sin(c);
    short cc = func_cos(c);
    short sb = func_sin(b);
    short cb = func_cos(b);
    short sa = func_sin(a);
    short ca = func_cos(a);
    int sbcc = (sb * cc) >> 12;
    int sbsc = (sb * sc) >> 12;

    return Unk02097b6c(((sa * sbsc) >> 12) + ((ca * cc) >> 12), ((ca * sbsc) >> 12) + ((-sa * cc) >> 12),
                       (cb * sc) >> 12, (sa * cb) >> 12, (ca * cb) >> 12, -sb,
                       ((sa * sbcc) >> 12) + ((ca * -sc) >> 12), ((ca * sbcc) >> 12) + ((sa * sc) >> 12),
                       (cb * cc) >> 12);
}
