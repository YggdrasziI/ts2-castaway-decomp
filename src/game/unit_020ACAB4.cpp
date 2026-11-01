/*
 * Unit 0x020ACAB4-0x020ACC60: the last game code: a pull between two points, scaled by a ramp over a
 * distance range, and the movement block of the scene elements, with its friction. Bounds:
 * hypothesis (the end is the end of .text). All names are placeholders. Real file name unknown.
 */
#include "game/unk_screen.h"
#include "game/unk_fishing.h"

/* A ramp: the value goes from near to far over the distances from min to max. */
struct Unk020acab4Range {
    int min;
    int near;
    int max;
    int far;
};

extern "C" Unk02098e70 func_020acab4(const Unk02098e70 *a, const Unk02098e70 *b, const Unk020acab4Range *r) {
    Unk02098e70 d = b->func_02098fcc(*a);
    int len = (int)d.func_02098e94();
    if (len >= r->min && len < r->max) {
        Unk02098e70 v;
        int t = 0x1000 - 0x1000 / (0x1000 / (r->max - r->min));
        int farPart = func_fxmul(r->far, 0x1000 - t);
        int nearPart = func_fxmul(r->near, t);
        int f = nearPart + farPart;
        v = d;
        return v.func_02098ec0(f);
    }
    const Unk02098e70 &zero = Unk02098e70(0);
    return zero;
}

Unk020acb90::Unk020acb90(int speed, int a) : dir(0), step(0), speed(a), unk14(speed) {}

Unk020acb90::~Unk020acb90() {}

extern "C" void func_020acbc8(Unk020acb90 *m) {
    Unk02098e70 add((m->step.x * m->unk14) >> 12, (m->step.y * m->unk14) >> 12);
    m->dir.x += add.x;
    m->dir.y += add.y;
    Unk02098e70 sub((m->dir.x * m->speed) >> 12, (m->dir.y * m->speed) >> 12);
    m->dir.x -= sub.x;
    m->dir.y -= sub.y;
}
