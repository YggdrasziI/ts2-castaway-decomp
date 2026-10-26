/*
 * ITCM unit 0x01FF84D0-0x01FF8BEC: the ITCM functions of the animation
 * (Unk020897c0, include/game/unk_anim.h). func_01ff84f0 samples every track at
 * a frame: it moves each key cursor to the key at or before the frame and writes
 * the rotation (spherical interpolation, Unk020988d8) and the two vectors (linear
 * interpolation) towards the next frame's keys into the element array, which it
 * allocates on first use. func_01ff8ab4 advances the time by the frame rate, with
 * a loop mode and a finished flag. The others are accessors.
 *
 * Bounds: hypothesis. 0x01FF84D0 follows the NitroSDK functions of the ITCM;
 * 0x01FF8BEC after works on the pool objects of unit_0208B554.cpp. No data. Real
 * file name unknown.
 * Not complete: func_01ff84f0 is at 97.57 % (comment above it).
 */

#include "game/unk_anim.h"

static inline Unk02098ff0 func_scaled(const Unk02098ff0 &v, int t) {
    return Unk02098ff0(func_fxmul(v.x, t), func_fxmul(v.y, t), func_fxmul(v.z, t));
}

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
}

void Unk020897c0::func_01ff84d0(u32 frame, int t) {
    u32 next = frame + 1;
    if (next == unk18) {
        next = 0;
    }
    func_01ff84f0(frame, next, t);
}

/*
 * 97.57 %: only the rotation key search differs. The original keeps the frame in
 * r6, the index in r0 and a separate byte offset (i * 12) next to the key pointer
 * (`ldr r11, [r1, #0xc]!` then `add r11, r3, r2`); ours walks the pointer alone.
 * Index and frame locals, int / u32 indices, pointer walks and other loop forms
 * were tried. The two vector tracks match.
 */
void Unk020897c0::func_01ff84f0(u32 frame, u32 next, int t) {
    if (file == 0) {
        return;
    }
    if (frame >= unk18 || next >= unk18) {
        return;
    }
    if (unk44 == 0) {
        func_02099afc(heap);
        unk44 = new Unk020897c0Elem[unk1c];
        func_02099b28();
    }
    unk04 = frame;
    unk08 = next;
    unk20 = t;
    Unk020897c0Track *first = unk38;
    Unk020897c0Track *cur = unk48;
    for (int n = 0; n < unk1c; n++) {
        u32 i;
        u32 j;

        Unk020897c0VecKey *keys = unk40;
        u32 f = unk04;
        i = cur->pos;
        if (keys[i].frame < f || (keys[i].frame > f && (i = first->pos) < cur->pos)) {
            while (keys[i + 1].frame <= f) {
                i++;
                if (keys[i].frame == f) {
                    break;
                }
            }
            cur->pos = i;
        }
        if (unk04 > unk08) {
            j = first->pos;
        } else {
            int step = 0;
            if (unk40[i].frame < (u32)unk08 && unk08 == unk40[i + 1].frame) {
                step = 1;
            }
            j = i + step;
        }
        if (j == i || t == 0) {
            unk44[n].setPos(unk40[i].value);
        } else {
            unk44[n].setPos(unk40[i].value.func_0209911c(func_scaled(unk40[j].value.func_02099150(unk40[i].value), t)));
        }

        keys = unk40;
        f = unk04;
        i = cur->scale;
        if (keys[i].frame < f || (keys[i].frame > f && (i = first->scale) < cur->scale)) {
            while (keys[i + 1].frame <= f) {
                i++;
                if (keys[i].frame == f) {
                    break;
                }
            }
            cur->scale = i;
        }
        if (unk04 > unk08) {
            j = first->scale;
        } else {
            int step = 0;
            if (unk40[i].frame < (u32)unk08 && unk08 == unk40[i + 1].frame) {
                step = 1;
            }
            j = i + step;
        }
        if (j == i || t == 0) {
            unk44[n].setScale(unk40[i].value);
        } else {
            unk44[n].setScale(unk40[i].value.func_0209911c(func_scaled(unk40[j].value.func_02099150(unk40[i].value), t)));
        }

        Unk020897c0RotKey *rkeys = unk3c;
        u32 rf = unk04;
        u32 ri = cur->rot;
        if (rkeys[ri].frame < rf || (rkeys[ri].frame > rf && (ri = first->rot) < cur->rot)) {
            while (rkeys[ri + 1].frame <= rf) {
                ri++;
                if (rkeys[ri].frame == rf) {
                    break;
                }
            }
            cur->rot = ri;
        }
        i = ri;
        if (unk04 > unk08) {
            j = first->rot;
        } else {
            int step = 0;
            if (unk3c[i].frame < (u32)unk08 && unk08 == unk3c[i + 1].frame) {
                step = 1;
            }
            j = i + step;
        }
        rkeys = unk3c;
        if (j == i || t == 0) {
            Unk020897c0RotKey *k = &rkeys[i];
            Unk020988d8 *rot = &unk44[n].rot;
            rot->x = k->x;
            rot->y = k->y;
            rot->z = k->z;
            rot->w = k->w;
        } else {
            Unk020897c0RotKey *ka = &rkeys[i];
            Unk020897c0RotKey *kb = &rkeys[j];
            Unk020988d8 qa;
            qa.x = ka->x;
            qa.y = ka->y;
            qa.z = ka->z;
            qa.w = ka->w;
            Unk020988d8 qb;
            qb.x = kb->x;
            qb.y = kb->y;
            qb.z = kb->z;
            qb.w = kb->w;
            unk44[n].rot = qa.func_02098a5c(qb, t);
        }
        first++;
        cur++;
    }
}

Unk020897c0Elem *Unk020897c0::func_01ff8a4c() {
    if (file == 0) {
        return 0;
    }
    return unk44;
}

int Unk020897c0::func_01ff8a60() {
    return unk1c;
}

int Unk020897c0::func_01ff8a68() {
    return unk18;
}

void Unk020897c0::func_01ff8a70(u16 mode) {
    unk32 = mode;
}

u16 Unk020897c0::func_01ff8a78() {
    return unk32;
}

void Unk020897c0::func_01ff8a80() {
    unk14 = 0;
}

bool Unk020897c0::func_01ff8a8c() {
    return unk14 > 0;
}

bool Unk020897c0::func_01ff8aa0() {
    return unk30 & 1;
}

void Unk020897c0::func_01ff8ab4(int dt, int hold) {
    if (unk30 & 2) {
        return;
    }
    int old = unk24;
    unk24 = old + ((unk28 * dt) >> 12);
    if (unk24 >= (unk18 - unk2c) << 12) {
        unk30 |= 1;
    }
    bool looped = false;
    switch (unk32) {
    case 0:
        if (old < unk10 << 12) {
            while (unk24 >= unk10 << 12) {
                unk24 -= (unk10 - unk0c) << 12;
                unk14++;
            }
            looped = true;
        }
        break;
    case 1:
        if (unk24 < unk10 << 12 && unk24 >= unk0c << 12) {
            unk24 += (unk10 - unk0c) << 12;
            unk14++;
        }
        break;
    case 2:
        break;
    }
    if (!looped) {
        int last = unk18 - 1;
        if (unk24 >= last << 12) {
            unk24 = last << 12;
            unk30 |= 1;
        }
    }
    if (hold != 0) {
        return;
    }
    func_01ff84d0(unk24 >> 12, unk24 & 0xfff);
}
