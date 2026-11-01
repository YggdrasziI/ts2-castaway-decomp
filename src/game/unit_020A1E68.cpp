/*
 * Unit 0x020A1E68-0x020A1F20: two angle helpers: the shortest way from one 16-bit angle to
 * another, scaled, and a point at a distance in the direction of an angle. Bounds: hypothesis
 * (after the clock, before the random numbers; no data). All names are placeholders. Real
 * file name unknown.
 */
#include "game/unk_vector.h"

typedef unsigned short u16;

extern "C" {
extern const short data_020af1e8[];
}

extern "C" u16 func_020a1e68(int from, int to, int factor) {
    int diff = (u16)to - (u16)from;
    int distance = diff < 0 ? -diff : diff;
    if (distance >= 0x8000) {
        distance = -(0xffff - distance);
    }
    int step = (distance * factor) >> 12;
    if (diff < 0) {
        step = -step;
    }
    return from + step;
}

extern "C" void func_020a1eb4(Unk02098ff0Base *pos, Unk02098ff0Base *out, short angle, int distance) {
    int i = (u16)angle >> 4;
    out->x = pos->x + func_fxmul(data_020af1e8[i * 2], distance);
    out->z = pos->z + func_fxmul(data_020af1e8[i * 2 + 1], distance);
    out->y = 0;
}
