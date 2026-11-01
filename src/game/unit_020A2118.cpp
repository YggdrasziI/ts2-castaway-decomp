/*
 * Unit 0x020A2118-0x020A22FC: intersection of a ray with an axis-aligned box. Bounds: hypothesis
 * (after the random numbers, before the sound code; no data). The first three words of the box
 * are its origin, the next three its size; each pair of opposite faces is tried in turn. All
 * names are placeholders. Real file name unknown.
 */
#include "game/unk_vector.h"

struct Unk020a2118Ray {
    Unk02098ff0 pos;
    Unk02098ff0 dir;
};

/* The block copy of a vector comes from the implicit assignment of a struct containing it. */
struct Unk020a2118Copy {
    Unk02098ff0 v;
};

struct Unk020a2118Box {
    int pos[3];
    int size[3];
};

struct Unk020a2118Hit {
    bool hit;
    int t;
    Unk02098ff0 pos;
    int normal[3];
};

static inline Unk02098ff0 func_scale(const Unk02098ff0 &v, int t) {
    return Unk02098ff0(func_fxmul(v.x, t), func_fxmul(v.y, t), func_fxmul(v.z, t));
}

/*
 * 97.93 %: the first `mov #0` of `outside` comes before the block copy in ours, and j is in r10
 * instead of r9 (declaration orders, types and copy forms tried).
 */
extern "C" bool func_020a2118(Unk020a2118Hit *hit, Unk020a2118Ray *ray, Unk020a2118Box *box) {
    Unk02098ff0 local = ray->pos.func_02099150(*(Unk02098ff0 *)box);
    hit->hit = false;
    for (int i = 0; i < 3; i++) {
        int d = (&ray->dir.x)[i];
        if (d == 0) {
            continue;
        }
        bool negative = false;
        if (d < 0) {
            int t = box->size[i] - (&local.x)[i];
            if (t > 0) {
                continue;
            }
            hit->t = func_fxdiv(t, d);
        } else {
            int t = (&local.x)[i];
            if (t > 0) {
                continue;
            }
            hit->t = func_fxdiv(-t, d);
            negative = true;
        }
        Unk02098ff0 point = local.func_0209911c(func_scale(ray->dir, hit->t));
        *(Unk020a2118Copy *)&hit->pos = *(Unk020a2118Copy *)&point;
        bool outside = false;
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                int v = (&hit->pos.x)[j];
                if (v < 0) {
                    outside = true;
                }
                if (v > box->size[j]) {
                    outside = true;
                }
            }
        }
        if (outside) {
            continue;
        }
        hit->hit = true;
        hit->pos.x += box->pos[0];
        hit->pos.y += box->pos[1];
        hit->pos.z += box->pos[2];
        for (int k = 0; k < 3; k++) {
            if (k == i) {
                hit->normal[k] = negative ? -0x1000 : 0x1000;
            } else {
                hit->normal[k] = 0;
            }
        }
        return true;
    }
    return false;
}
