/*
 * ITCM unit 0x01FF9924-0x01FFA2D0: drawing of the object pool (Unk020c7d38,
 * include/game/unk_pool.h). func_01ff9924 fills the back record array: for each
 * object in use, its model, a copy of its element set, its world matrix (from the
 * object's angles and position, optionally followed by one of the pool's frames)
 * times the camera's view matrix, and its rotation. func_01ff9dbc swaps the
 * record arrays and the light rows and starts sending the records; func_01ff9f00
 * loads one record's matrix and the four lights into the geometry engine and
 * sends its model with func_01ff8c64, whose callback func_01ffa180 sends the
 * next one. func_01ffa1e0 sorts the drawing order by priority (unk24), then by
 * object index.
 *
 * Bounds: hypothesis. Before 0x01FF9924 lies unit_01FF9098.cpp (element set);
 * 0x01FFA2D0 after works on the transform set (Unk0208be3c). The camera
 * fields of the pool (0x54-0x158) have the layout of Unk020899a4
 * (include/game/unk_camera.h) and are read through it. The functions keep C
 * linkage and their addresses as names. No data. Real file name unknown.
 * Not complete: func_01ff9924 84.41 %, func_01ffa1e0 99.00 % (comments above
 * them).
 */

#include "game/unk_pool.h"
#include "game/unk_camera.h"
#include "game/unk_model.h"

typedef volatile u32 vu32;

extern "C" {
extern const s16 data_020af1e8[];

void func_02078b7c(const Unk02097b6c *mtx);
int func_01ff9098(Unk0208adc0 *set, const Unk0208adc0 *src, u32 *buffer, int maxWords);
void func_01ff9128(Unk0208adc0 *set, const Unk0208adc0 *src);
void func_01ff9624(Unk0208adc0 *set);
void func_01ffaa28(Unk0208be3c *xform);
void func_01ffa1e0(Unk020c7d38 *pool);
void func_01ff8d84(Unk02089f38 *model, Unk0208be3c *xform);
void func_01ff8c38(Unk02089f38 *model, const Unk02098094 *mtx);
int func_01ff8c64(Unk02089f38 *model, int async, void (*callback)(int), int arg);

void func_01ff9f00(Unk020c7d38 *pool);
void func_01ffa180(Unk020c7d38 *pool);
}

static inline Unk020899a4 *func_camera(Unk020c7d38 *pool) {
    return (Unk020899a4 *)&pool->unk54;
}

static inline Unk02098094 func_view(const Unk020899a4 *cam) {
    Unk02098094 view;
    view.func_0209873c(Unk02098094(Unk02098ff0(-cam->pos.x, -cam->pos.y, -cam->pos.z)),
                       Unk02098094(Unk02097b6c::func_02097f78(cam->angles.v.z, cam->angles.v.x, cam->angles.v.y)
                                       .func_02097cec()));
    return view;
}

static inline Unk02098094 func_mul(const Unk02098094 &a, const Unk02098094 &b) {
    Unk02098094 m;
    m.func_0209873c(a, b);
    return m;
}

static inline Unk02097b6c func_mul(const Unk02097b6c &a, const Unk02097b6c &b) {
    Unk02097b6c m;
    m.func_02097c6c(a, b);
    return m;
}

static inline Unk0208b554Frame *func_frame(Unk020c7d38 *pool, int index) {
    if (index < 0) {
        return 0;
    }
    return &pool->frames[index];
}

static inline int func_sin(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2];
}

static inline int func_cos(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2 + 1];
}

static inline void func_identity() {
    *(vu32 *)0x04000454 = 0;
}

static inline void func_translate(int x, int y, int z) {
    *(vu32 *)0x04000470 = x;
    *(vu32 *)0x04000470 = y;
    *(vu32 *)0x04000470 = z;
}

static inline void func_load33(const Unk02097b6c &m) {
    func_02078b7c(&m);
}

/* The light record copied to the stack by func_01ff9f00. */
struct Unk01ff9f00Light {
    Unk01ff9f00Light() {
        unk0c = 0;
        unk0e = 0;
        unk10 = 0;
        unk12 = 0;
    }

    Unk02098ff0 dir;
    s16 unk0c;
    s16 unk0e;
    s16 unk10;
    s16 unk12;
};

static inline void func_light(int id, const Unk02098ff0 &dir, const Unk01ff9f00Light &c) {
    int r = c.unk0c;
    int g = c.unk0e;
    int b = c.unk10;
    u32 vec = (id << 30) + (((dir.x >> 3) & 0x3ff) + (((dir.y >> 3) & 0x3ff) << 10) + (((dir.z >> 3) & 0x3ff) << 20));
    if (r > 0xff) {
        r = 0xff;
    }
    if (r < 0) {
        r = 0;
    }
    if (g > 0xff) {
        g = 0xff;
    }
    if (g < 0) {
        g = 0;
    }
    if (b > 0xff) {
        b = 0xff;
    }
    if (b < 0) {
        b = 0;
    }
    u32 col = (id << 30) + (u16)((r >> 3) + ((g >> 3) << 5) + ((b >> 3) << 10));
    *(vu32 *)0x040004CC = col;
    *(vu32 *)0x040004C8 = vec;
}

/* Copies a vector as one block (ldm / stm), as the original does here. */
static inline void func_copy(Unk02098ff0 &dst, const Unk02098ff0 &src) {
    *(Unk0208adc0Scale *)&dst = *(const Unk0208adc0Scale *)&src;
}

extern "C" {

/*
 * 84.41 %: register allocation and scheduling of the rotation matrix. The
 * original loads the six sine / cosine values first (cosine before sine), keeps
 * s0 * s1 and s0 * c1 in registers without spilling, keeps the loop counter on
 * the stack and selects the frame with a branch (ours: conditional execution).
 * Stack layout and the rest of the code match. Tried: sine / cosine types (int,
 * s16) and declaration orders, the products as locals or inline, five store
 * orders, loop counter forms, the frame selection as ?:, if / else or an inline.
 */
void func_01ff9924(Unk020c7d38 *pool) {
    if (pool->count == 0) {
        return;
    }
    if (pool->flags & 2) {
        func_01ffa1e0(pool);
    }
    pool->unk4 = 0;
    int back = pool->unk15a ^ 1;
    u32 *buffer = pool->buffers[back];
    int words = pool->bufferWords;
    Unk0208b554Record *rec = pool->records[back];
    Unk020899a4 *cam = func_camera(pool);
    Unk02098094 view = func_view(cam);
    for (int i = 0; i < pool->capacity; i++) {
        u16 id = pool->unk20[i];
        if (!pool->used.func_0209a188(id)) {
            continue;
        }
        if (pool->unk4 >= pool->recordCount) {
            return;
        }
        Unk0208b554Item *item = &pool->items[id];
        Unk02089f38 *model = item->func_0208ac64();
        if (model == 0) {
            continue;
        }
        rec->model = model;
        model->func_0208a084();
        Unk0208adc0 *set = item->func_0208ad18();
        bool skip = false;
        if ((set->flags & 2) && !(set->flags & 4)) {
            skip = true;
        }
        if (!skip) {
            func_01ff9624(set);
        }
        if (!pool->active.func_0209a188(id)) {
            item->func_0208ad40();
        }
        pool->active.func_0209a1c4(id, true);
        int n = func_01ff9098(&rec->set, set, buffer, words);
        buffer += n;
        words -= n;
        Unk0208be3c *xform = (Unk0208be3c *)item->unk38;
        if (xform != 0) {
            func_01ffaa28(xform);
        }
        rec->xform = xform;
        int frame = pool->unk3c[id];
        int s0 = func_sin(item->unk0c);
        int c0 = func_cos(item->unk0c);
        int s1 = func_sin(item->unk10);
        int c1 = func_cos(item->unk10);
        int s2 = func_sin(item->unk14);
        int c2 = func_cos(item->unk14);
        Unk02097b6c rot;
        rot.m[2][1] = -s0;
        rot.m[0][0] = (s2 * (s0 * s1 >> 12) >> 12) + (c2 * c1 >> 12);
        rot.m[1][0] = (c2 * (s0 * s1 >> 12) >> 12) + (-s2 * c1 >> 12);
        rot.m[2][2] = c0 * c1 >> 12;
        rot.m[2][0] = c0 * s1 >> 12;
        rot.m[0][1] = s2 * c0 >> 12;
        rot.m[1][1] = c2 * c0 >> 12;
        rot.m[0][2] = (s2 * (s0 * c1 >> 12) >> 12) + (c2 * -s1 >> 12);
        rot.m[1][2] = (c2 * (s0 * c1 >> 12) >> 12) + (s2 * s1 >> 12);
        Unk02097b6c worldRot;
        Unk02098094 world;
        if (frame < 0) {
            world = Unk02098094(rot, item->pos);
            worldRot = rot.func_02097cec();
        } else {
            Unk0208b554Frame *f = func_frame(pool, frame);
            world = func_mul(Unk02098094(rot, item->pos), Unk02098094(f->mtx, f->pos));
            worldRot = func_mul(rot, f->mtx).func_02097cec();
        }
        world.func_020985b0(view);
        rec->mtx = world;
        rec->rot = worldRot;
        rec++;
        pool->unk4++;
    }
}

void func_01ff9dbc(Unk020c7d38 *pool) {
    if (pool->flags & 1) {
        return;
    }
    func_camera(pool)->func_02089ba4();
    pool->unk15a ^= 1;
    for (int i = 0; i < 4; i++) {
        Unk0208b554Light *dst = &pool->lights[1][i];
        *dst = pool->lights[0][i];
        func_copy(dst->dir, dst->dir.func_02099088().func_clamp());
    }
    pool->unk40 = 0;
    int n = pool->unk4;
    pool->unk8 = n;
    if (n == 0) {
        return;
    }
    pool->flags |= 1;
    func_01ff9f00(pool);
}

bool func_01ff9ee8(Unk020c7d38 *pool) {
    return pool->flags & 1;
}

void func_01ff9f00(Unk020c7d38 *pool) {
    if (pool->unk8 == 0) {
        return;
    }
    Unk0208b554Record *rec = &pool->records[pool->unk15a][pool->unk40];
    Unk02089f38 *model = rec->model;
    Unk02098ff0 t = rec->mtx.func_020982a8();
    func_identity();
    func_translate(t.x, t.y, t.z);
    func_load33(Unk02097b6c(rec->mtx));
    for (int i = 0; i < 4; i++) {
        Unk01ff9f00Light l;
        const Unk0208b554Light *src = &pool->lights[1][i];
        func_copy(l.dir, src->dir);
        l.unk0c = src->unk0c;
        l.unk0e = src->unk0e;
        l.unk10 = src->unk10;
        l.unk12 = src->unk12;
        Unk02098ff0 d = rec->rot.func_02097d38(l.dir).func_clamp();
        func_light(i, d, l);
    }
    pool->unk40++;
    pool->unk8--;
    func_01ff8d84(model, rec->xform);
    func_01ff9128(model->func_0208a048(), &rec->set);
    func_01ff8c38(model, &rec->mtx);
    func_01ff8c64(model, 1, (void (*)(int))func_01ffa180, (int)pool);
}

void func_01ffa180(Unk020c7d38 *pool) {
    if (pool->unk40 > 0) {
        (pool->records[pool->unk15a] + pool->unk40)[-1].model->func_0208a094();
    }
    if (pool->unk8 != 0) {
        func_01ff9f00(pool);
    } else {
        pool->flags &= ~1;
    }
}

/*
 * 99.00 %: register allocation (the original keeps the count in lr and the
 * unk24 array in r12, ours the reverse). Tried: per-loop counters, the
 * comparison through inline helpers, nested or split ifs, local array
 * pointers, loop forms and declaration orders.
 */
void func_01ffa1e0(Unk020c7d38 *pool) {
    for (int i = 0; i < pool->count; i++) {
        pool->unk20[i] = i;
    }
    for (int i = 0; i < pool->count; i++) {
        int best = i;
        int j = i;
        for (; j < pool->count; j++) {
            if (pool->unk24[pool->unk20[best]] > pool->unk24[pool->unk20[j]] ||
                (pool->unk24[pool->unk20[best]] == pool->unk24[pool->unk20[j]] &&
                 pool->items[pool->unk20[best]].index > pool->items[pool->unk20[j]].index)) {
                best = j;
            }
        }
        u16 t = pool->unk20[i];
        pool->unk20[i] = pool->unk20[best];
        pool->unk20[best] = t;
    }
    pool->flags &= ~2;
}
}
