/*
 * Unit 0x020987D8-0x020988D8: a plane (Unk020987d8: normal and distance, 20.12
 * fixed point): constructors, intersection with a line, signed distance of a
 * point.
 *
 * Bounds: hypothesis. Before 0x020987D8 lies a 4x4 matrix product (func_0209873c);
 * from 0x020988D8 come quaternion functions (identity, norm, matrix, slerp). Real
 * file name unknown.
 */

#include "game/unk_plane.h"

Unk020987d8::Unk020987d8() : normal(0, 0x1000, 0) {
    d = 0;
}

Unk020987d8::Unk020987d8(const Unk02098ff0 &normal, const Unk02098ff0 &point) : normal(normal) {
    d = -normal.func_02099184(point);
}

Unk02098ff0 Unk020987d8::func_02098824(const Unk02098ff0 &origin, const Unk02098ff0 &dir) const {
    int along = normal.func_02099184(dir);
    int t = func_fxdiv(-(d + normal.func_02099184(origin)), along);
    return origin.func_0209911c(Unk02098ff0(func_fxmul(dir.x, t), func_fxmul(dir.y, t), func_fxmul(dir.z, t)));
}

int Unk020987d8::func_020988c0(const Unk02098ff0 &point) const {
    return d + normal.func_02099184(point);
}
