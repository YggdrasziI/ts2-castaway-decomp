/*
 * Unit 0x02098094-0x020987D8: 20.12 fixed-point 4x4 matrix (Unk02098094, stored by
 * column): constructors from a 3x3 matrix, sixteen elements or a translation,
 * identity, translation access, point transform, projection, products.
 *
 * Bounds: hypothesis. Before 0x02098094 lies unit_02097B6C.cpp (3x3 matrix);
 * 0x020987D8 starts unit_020987D8.cpp (a plane). Real file name unknown.
 */

#include "game/unk_matrix.h"

Unk02098094::Unk02098094(const Unk02097b6c &r) {
    m[0][0] = r.m[0][0];
    m[1][0] = r.m[1][0];
    m[2][0] = r.m[2][0];
    m[3][0] = 0;
    m[0][1] = r.m[0][1];
    m[1][1] = r.m[1][1];
    m[2][1] = r.m[2][1];
    m[3][1] = 0;
    m[0][2] = r.m[0][2];
    m[1][2] = r.m[1][2];
    m[2][2] = r.m[2][2];
    m[3][2] = 0;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 0x1000;
}

Unk02098094::Unk02098094(const Unk02097b6c &r, const Unk02098ff0 &t) {
    m[0][0] = r.m[0][0];
    m[1][0] = r.m[1][0];
    m[2][0] = r.m[2][0];
    m[3][0] = t.x;
    m[0][1] = r.m[0][1];
    m[1][1] = r.m[1][1];
    m[2][1] = r.m[2][1];
    m[3][1] = t.y;
    m[0][2] = r.m[0][2];
    m[1][2] = r.m[1][2];
    m[2][2] = r.m[2][2];
    m[3][2] = t.z;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 0x1000;
}

Unk02098094::Unk02098094(int m00, int m01, int m02, int m03, int m10, int m11, int m12, int m13, int m20,
                         int m21, int m22, int m23, int m30, int m31, int m32, int m33) {
    m[0][0] = m00;
    m[1][0] = m01;
    m[2][0] = m02;
    m[3][0] = m03;
    m[0][1] = m10;
    m[1][1] = m11;
    m[2][1] = m12;
    m[3][1] = m13;
    m[0][2] = m20;
    m[1][2] = m21;
    m[2][2] = m22;
    m[3][2] = m23;
    m[0][3] = m30;
    m[1][3] = m31;
    m[2][3] = m32;
    m[3][3] = m33;
}

Unk02098094::Unk02098094(const Unk02098ff0 &t) {
    m[0][0] = 0x1000;
    m[1][0] = 0;
    m[2][0] = 0;
    m[3][0] = t.x;
    m[0][1] = 0;
    m[1][1] = 0x1000;
    m[2][1] = 0;
    m[3][1] = t.y;
    m[0][2] = 0;
    m[1][2] = 0;
    m[2][2] = 0x1000;
    m[3][2] = t.z;
    m[0][3] = 0;
    m[1][3] = 0;
    m[2][3] = 0;
    m[3][3] = 0x1000;
}

Unk02098094 Unk02098094::func_02098254() {
    return Unk02098094(0x1000, 0, 0, 0, 0, 0x1000, 0, 0, 0, 0, 0x1000, 0, 0, 0, 0, 0x1000);
}

Unk02098ff0 Unk02098094::func_020982a8() const {
    return Unk02098ff0(m[3][0], m[3][1], m[3][2]);
}

void Unk02098094::func_020982bc(const Unk02098ff0 &t) {
    m[3][0] = t.x;
    m[3][1] = t.y;
    m[3][2] = t.z;
}

Unk02098ff0 Unk02098094::func_020982d8(const Unk02098ff0 &v) const {
    return Unk02098ff0(
        (int)((((s64)v.x * m[0][0]) >> 12) + (((s64)v.y * m[1][0]) >> 12) + (((s64)v.z * m[2][0]) >> 12) +
              m[3][0]),
        (int)((((s64)v.x * m[0][1]) >> 12) + (((s64)v.y * m[1][1]) >> 12) + (((s64)v.z * m[2][1]) >> 12) +
              m[3][1]),
        (int)((((s64)v.x * m[0][2]) >> 12) + (((s64)v.y * m[1][2]) >> 12) + (((s64)v.z * m[2][2]) >> 12) +
              m[3][2]));
}

Unk02098ff0 Unk02098094::func_020983ac(const Unk02098ff0 &v) const {
    int w = (int)((((s64)v.x * m[0][3]) >> 12) + (((s64)v.y * m[1][3]) >> 12) + (((s64)v.z * m[2][3]) >> 12) +
                  m[3][3]);
    s64 inv = func_fxdiv(0x1000, w);
    s64 x = (((s64)v.x * m[0][0]) >> 12) + (((s64)v.y * m[1][0]) >> 12) + (((s64)v.z * m[2][0]) >> 12) + m[3][0];
    s64 z = (((s64)v.x * m[0][2]) >> 12) + (((s64)v.y * m[1][2]) >> 12) + (((s64)v.z * m[2][2]) >> 12) + m[3][2];
    s64 y = (((s64)v.x * m[0][1]) >> 12) + (((s64)v.y * m[1][1]) >> 12) + (((s64)v.z * m[2][1]) >> 12) + m[3][1];

    int rz = (int)((inv * z) >> 12);
    int ry = (int)((inv * y) >> 12);
    int rx = (int)((inv * x) >> 12);
    return Unk02098ff0(rx, ry, rz);
}

void Unk02098094::func_020985b0(const Unk02098094 &o) {
    Unk02098094 r;
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        s64 b1 = o.m[1][i];
        s64 b0 = o.m[0][i];
        s64 b2 = o.m[2][i];
        s64 b3 = o.m[3][i];

        for (j = 0; j < 4; j++) {
            r.m[j][i] = (int)(((m[j][0] * b0) >> 12) + ((m[j][1] * b1) >> 12) + ((m[j][2] * b2) >> 12) +
                              ((m[j][3] * b3) >> 12));
        }
    }
    *this = r;
}

void Unk02098094::func_0209873c(const Unk02098094 &a, const Unk02098094 &b) {
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m[j][i] = (int)((((s64)b.m[0][i] * a.m[j][0]) >> 12) + (((s64)b.m[1][i] * a.m[j][1]) >> 12) +
                            (((s64)b.m[2][i] * a.m[j][2]) >> 12) + (((s64)b.m[3][i] * a.m[j][3]) >> 12));
        }
    }
}
