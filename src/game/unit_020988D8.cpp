/*
 * Unit 0x020988D8-0x02098BC8: a quaternion (Unk020988d8: x, y, z, w in 20.12 fixed
 * point): identity, norm, rotation matrix, spherical interpolation.
 *
 * Bounds: hypothesis. Before 0x020988D8 lies unit_020987D8.cpp (a plane); 0x02098BC8
 * starts unit_02098BC8.cpp (a rectangle). The matrix and interpolation functions
 * have no direct caller. Real file name unknown.
 * func_02097b6c is taken as the constructor of a 3x3 matrix: it receives the
 * hidden result pointer and the nine elements.
 * Not complete: func_02098934 and func_02098a5c do not match yet (comments above
 * them).
 */

typedef unsigned short u16;

extern "C" int func_02077c60(int a, int b);
extern "C" int func_02097a6c(long long x);
extern "C" int func_02097b14(int x);
extern "C" const short data_020af1e8[];

static inline int func_fxdiv(int a, int b) {
    if (b != 0) {
        return func_02077c60(a, b);
    }
    return a;
}

static inline int func_sin(u16 index) {
    return data_020af1e8[(index >> 4) * 2];
}

/* 3x3 matrix built by func_02097b6c (not decompiled). */
class Unk02097b6c {
public:
    Unk02097b6c(int m00, int m01, int m02, int m10, int m11, int m12, int m20, int m21, int m22);

    int m[3][3];
};

class Unk020988d8 {
public:
    Unk020988d8(int x, int y, int z, int w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    void func_020988d8();
    int func_020988f4() const;
    Unk02097b6c func_02098934() const;
    Unk020988d8 func_02098a5c(const Unk020988d8 &o, int t) const;

    int x;
    int y;
    int z;
    int w;
};

void Unk020988d8::func_020988d8() {
    x = 0;
    y = 0;
    z = 0;
    w = 0x1000;
}

int Unk020988d8::func_020988f4() const {
    return func_02097a6c(((w * w) >> 12) + ((x * x) >> 12) + ((y * y) >> 12) + ((z * z) >> 12));
}

/* 99.26 %: the three w products land in other registers (original: w * z in r9,
 * w * x in r8, w * y in r10). Declaration orders (150 sampled) and inline products
 * were tried. */
Unk02097b6c Unk020988d8::func_02098934() const {
    int norm = func_020988f4();
    int s;
    int d = norm - 0x1000;

    if (d <= 0) {
        d = -d;
    }
    if (d < 4) {
        s = 0x2000;
    } else {
        s = func_fxdiv(0x2000, norm);
    }
    {
        int xx = (x * x) >> 12;
        int yy = (y * y) >> 12;
        int zz = (z * z) >> 12;
        int xy = (x * y) >> 12;
        int xz = (x * z) >> 12;
        int yz = (y * z) >> 12;
        int wy = (w * y) >> 12;
        int wx = (w * x) >> 12;
        int wz = (w * z) >> 12;

        return Unk02097b6c(0x1000 - ((s * (yy + zz)) >> 12), (s * (xy - wz)) >> 12, (s * (xz + wy)) >> 12,
                           (s * (xy + wz)) >> 12, 0x1000 - ((s * (zz + xx)) >> 12), (s * (yz - wx)) >> 12,
                           (s * (xz - wy)) >> 12, (s * (wx + yz)) >> 12, 0x1000 - ((s * (yy + xx)) >> 12));
    }
}

/* 99.34 %: the flip flag and the angle swap registers (original: flag in r5,
 * angle in r11). All 720 declaration orders and five control-flow forms were
 * tried. */
Unk020988d8 Unk020988d8::func_02098a5c(const Unk020988d8 &o, int t) const {
    int dot;
    int flip;
    int a;
    int b;
    int angle;
    int sinAngle;

    dot = ((x * o.x) >> 12) + ((y * o.y) >> 12) + ((z * o.z) >> 12) + ((w * o.w) >> 12);
    flip = 0;
    if (dot < 0) {
        dot = -dot;
        flip = 1;
    }
    if (0x1000 - dot > 0xc) {
        angle = func_02097b14(dot);
        sinAngle = func_sin((u16)angle);
        a = func_fxdiv(func_sin((u16)(((0x1000 - t) * angle) >> 12)), sinAngle);
        b = func_fxdiv(func_sin((u16)((t * angle) >> 12)), sinAngle);
    } else {
        a = 0x1000 - t;
        b = t;
    }
    if (flip) {
        b = -b;
    }
    return Unk020988d8(((x * a) >> 12) + ((o.x * b) >> 12), ((y * a) >> 12) + ((o.y * b) >> 12),
                       ((z * a) >> 12) + ((o.z * b) >> 12), ((w * a) >> 12) + ((o.w * b) >> 12));
}
