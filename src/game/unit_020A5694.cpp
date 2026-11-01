/*
 * Unit 0x020A5694-0x020A5948: hit tests of a point in a rotated ellipse or box, used as callbacks
 * by unit_0200AD70.cpp. The point is rotated into the shape, scaled by its inverse size and
 * tested against the unit circle or square. Bounds: hypothesis (between the save files and the
 * microgame table; no data). All names are placeholders. Real file name unknown.
 */
#include "game/unk_vector.h"

typedef unsigned short u16;

extern "C" {
extern const short data_020af1e8[];
int func_020a5694(const Unk02098e70 *p, const Unk02098e70 *scale);
int func_020a57d0(const Unk02098e70 *p, const Unk02098e70 *scale);
}

static inline int func_round(int a, int b) {
    return (int)(((s64)a * b + 0x800) >> 12);
}

extern "C" int func_020a5694(const Unk02098e70 *p, const Unk02098e70 *scale) {
    Unk02098e70 v(func_round(p->x, scale->x), func_round(p->y, scale->y));
    return v.func_02098e94() <= 0x1000;
}

extern "C" int func_020a5700(const Unk02098e70 *p, const Unk02098e70 *scale, const Unk02098e70 *center, int angle) {
    int i = (u16)-angle >> 4;
    int s = data_020af1e8[i * 2];
    Unk02098e70 d = p->func_02098fcc(*center);
    int c = data_020af1e8[i * 2 + 1];
    Unk02098e70 v(func_round(d.x, c) + func_round(d.y, -s), func_round(d.x, s) + func_round(d.y, c));
    return func_020a5694(&v, scale);
}

extern "C" int func_020a57d0(const Unk02098e70 *p, const Unk02098e70 *scale) {
    Unk02098e70 v(func_round(p->x, scale->x), func_round(p->y, scale->y));
    return v.x >= -0x1000 && v.x <= 0x1000 && v.y >= -0x1000 && v.y <= 0x1000;
}

extern "C" int func_020a5878(const Unk02098e70 *p, const Unk02098e70 *scale, const Unk02098e70 *center, int angle) {
    int i = (u16)-angle >> 4;
    int s = data_020af1e8[i * 2];
    Unk02098e70 d = p->func_02098fcc(*center);
    int c = data_020af1e8[i * 2 + 1];
    Unk02098e70 v(func_round(d.x, c) + func_round(d.y, -s), func_round(d.x, s) + func_round(d.y, c));
    return func_020a57d0(&v, scale);
}
