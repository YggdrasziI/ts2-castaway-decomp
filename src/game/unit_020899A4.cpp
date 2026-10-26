/*
 * Unit 0x020899A4-0x02089F38: the camera (Unk020899a4, include/game/unk_camera.h).
 * It turns towards a target, sets its field of view from the sine / cosine table,
 * rebuilds its projection, view and inverse view matrices, loads the projection
 * into the geometry engine (MTX_MODE 0x04000440) and maps screen points back
 * into the world.
 *
 * Bounds: hypothesis. Before 0x020899A4 lies the animation of unit_020897C0.cpp
 * (its element constructor ends it); 0x02089F38 starts unit_02089F38.cpp. No data. Real
 * file name unknown.
 */

#include "game/unk_camera.h"

typedef unsigned short u16;
typedef unsigned long u32;

extern "C" {
int func_02097b14(int x);
void func_02078b98(const Unk02098094 *m);
}

extern const short data_020af1e8[];

static inline int func_clampOne(int x) {
    if (x > 0x1000) {
        x = 0x1000;
    }
    if (x < -0x1000) {
        x = -0x1000;
    }
    return x;
}

static inline Unk02098094 func_mul(const Unk02098094 &a, const Unk02098094 &b) {
    Unk02098094 m;
    m.func_0209873c(a, b);
    return m;
}

void Unk020899a4::func_020899a4(const Unk02098ff0 &target, int roll) {
    Unk02098ff0 axisX(-0x1000, 0, 0);
    Unk02098ff0 axisZ(0, 0, -0x1000);
    Unk02098ff0 flat = Unk02098ff0(pos.x - target.x, 0, pos.z - target.z).func_02099088();
    Unk02098ff0 dir = Unk02098ff0(pos.x - target.x, pos.y - target.y, pos.z - target.z).func_02099088();
    Unk02098ff0 up(0, 0x1000, 0);
    int pitch = 0x4000 - func_02097b14(func_clampOne(dir.func_02099184(up)));
    int z = flat.z;
    if (z <= 0) {
        z = -z;
    }
    int x = flat.x;
    if (x <= 0) {
        x = -x;
    }
    int yaw;
    if (x > z) {
        yaw = func_02097b14(func_clampOne(flat.func_02099184(axisZ)));
        if (flat.x > 0) {
            yaw = -yaw;
        }
    } else {
        yaw = func_02097b14(func_clampOne(flat.func_02099184(axisX)));
        if (flat.z > 0) {
            yaw = -yaw;
        }
        yaw = 0x4000 - yaw;
    }
    angles = Unk020899a4Angles(pitch, yaw, roll);
}

void Unk020899a4::func_02089b48(int angle) {
    int i = (u16)(angle >> 1) >> 4;
    int s = data_020af1e8[i * 2];
    int c = data_020af1e8[i * 2 + 1];
    if (s != sin || c != cos) {
        flags |= 1;
    }
    cos = c;
    sin = s;
    fov = angle;
}

Unk02098094 Unk020899a4::func_02089ba4() {
    func_02089d48();
    if (flags & 1) {
        *(volatile u32 *)0x04000440 = 0;
        func_02078b98(&proj);
        *(volatile u32 *)0x04000440 = 2;
        flags &= ~1;
    }
    return proj;
}

Unk02098ff0 Unk020899a4::func_02089c1c(const Unk02098ff0 &v) {
    Unk02098ff0 p;
    p.x = func_fxdiv(v.x, unk30);
    p.y = func_fxdiv(v.y, unk34);
    p.z = 0x1000;
    p.func_02099048(func_fxdiv(unk3c, v.z - unk38));
    return inverse.func_020982d8(p);
}

/*
 * A point of func_02089cac. Only the implicit assignment of a struct holding the
 * vector gives the original block copy (ldm / stm) back into the point's slot;
 * the cast of the returned vector is a workaround, not the original code.
 */
struct Unk02089cacPoint {
    Unk02089cacPoint(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

Unk02098ff0 Unk020899a4::func_02089cac(int x, int y) {
    Unk02098ff0 from = pos;
    Unk02089cacPoint p(x / 128 - 0x1000, -(y / 96 - 0x1000), 0x1000);
    p = (const Unk02089cacPoint &)func_02089c1c(p.v);
    return p.v.func_02099150(from).func_020990ec();
}

void Unk020899a4::func_02089d48() {
    int sx = func_fxdiv(cos, (aspect * sin) >> 12);
    int sy = func_fxdiv(cos, sin);
    int sz = func_fxdiv(clipFar + clipNear, clipFar - clipNear);
    int tz = -func_fxdiv((clipFar * clipNear) >> 11, clipFar - clipNear);
    proj = Unk02098094(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, tz, 0, 0, 0x1000, 0);
    unk30 = sx;
    unk34 = sy;
    unk38 = sz;
    unk3c = tz;
    view = func_mul(Unk02098094(Unk02098ff0(-pos.x, -pos.y, -pos.z)),
                    Unk02098094(Unk02097b6c::func_02097f78(angles.v.z, angles.v.x, angles.v.y).func_02097cec()));
    inverse = Unk02098094(Unk02097b6c::func_02097f78(angles.v.z, angles.v.x, angles.v.y), pos);
}
