/*
 * Unit 0x02069EA8-0x0206B4D4: the camera controller Unk02069fec
 * (include/game/unk_camctl.h), a member of the game states.
 *
 * func_0206a120 sets it up from the current map's camera records: in a map
 * with flag 4 the camera follows a point kept inside four planes around the
 * map's range (mode 1, func_0206a850), otherwise it is turned with the buttons
 * (mode 0). func_0206af98 runs it once per frame and blends the field of view
 * started by func_0206b3c4 / func_0206b4a8; func_02069ea8 keeps the camera
 * angles inside the field-of-view limits.
 *
 * Bounds: hypothesis. 0x02069EA8 is the first function using the class layout
 * (the functions before it work on other objects); unit_0206B4D4.cpp starts
 * after func_0206b4c8. Real file name unknown.
 *
 * 0x0206A7DC-0x0206A850 are out-of-line copies of inline functions that
 * func_0206a120 does not inline (the plane assignment, func_0206a7fc,
 * func_0206a81c and the implicit constructors of the two map records):
 * mwccarm emits them right after the function, in order of first use. Calls
 * to func_020130d8 (a vector constructor), func_0200ca68, func_0200cad0,
 * func_0200cab0 and func_0200ca88 are the same kind of copies, kept by an
 * earlier file; they are declared here by their dsd names.
 *
 * Not complete: functions below 100 % carry a comment with the remaining
 * difference.
 */

#include "game/unk_camctl.h"
#include "game/unk_pool.h"

typedef unsigned short u16;

/* A vector of a camera record; the wrapper makes its copies block copies. */
struct Unk0206a07cVec {
    Unk0206a07cVec() {}
    Unk0206a07cVec(int x, int y, int z) : v(x, y, z) {}

    Unk02098ff0 v;
};

/* A camera record of a map (func_02058134, 0x24 bytes). */
struct Unk0206a07c {
    int unk0;
    int unk4;
    int unk8;
    Unk0206a07cVec unkc;
    Unk0206a07cVec unk18;
};

/* A range record of a map (func_02058194, 0x10 bytes). */
struct Unk0206a0e4 {
    Unk0206a0e4() {}

    int unk0;
    int unk4;
    int unk8;
    int unkc;
};

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4(signed char unk3, signed char unk2, short unk0);

    short unk0;
    signed char unk2;
    signed char unk3;
};

struct Unk020589ac {
    int unk0;
    int unk4;
    unsigned long flags;
};

struct Unk020c3ba4 {
    int unk0;
    unsigned char unk4[0xf8];
    signed char map;
};

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    int unk0;
    int unk4;
    unsigned long flags;
    unsigned char unkc[0x150];
    unsigned char unk15c;
};

class Unk020c43a8 {
public:
    virtual void func_00();
    virtual Unk02098ff0 func_04();
};

extern "C" {
void *func_02058788(Unk020c3ba4 *world, int map);
void func_02056ed0(void *map, const Unk020593e4 *cell);
Unk020589ac *func_020589ac(Unk020c3ba4 *world, int map);
Unk0206a07c *func_02058134(void *map, unsigned long key);
Unk0206a0e4 *func_02058194(void *map, unsigned long key);
Unk020c43a8 *func_0200f168();
void func_0200ca68(Unk02098e70 *dst, const Unk02098e70 *src);
int func_0200cad0(int a, int b);
int func_0200cab0(int angle);
int func_0200ca88(int angle);
Unk02098ff0 func_020130d8(int x, int y, int z);
void func_02066f14(Unk02098ff0 *out, Unk020c43a8 *p);
int func_020a1e68(int a, int b, int f);

void func_02069ea8(Unk02069fec *p);
void func_0206a07c(Unk0206a07c *r);
void func_0206a0e4(Unk0206a0e4 *r, void *map, unsigned long key, const Unk0206a07c *rec);
void func_0206a120(Unk02069fec *p);
void func_0206a850(Unk02069fec *p, int mode);
Unk020987d8 *func_0206af40(Unk02069fec *p, int i);
void func_0206af60(Unk02069fec *p, int i, const Unk020987d8 *plane);
void func_0206af98(Unk02069fec *p, int mode);
void func_0206b30c(Unk02069fec *p, int pitch, int yaw);
void func_0206b32c(Unk02069fec *p, int d);
void func_0206b348(Unk02069fec *p, int d);
void func_0206b364(Unk02069fec *p, int angle);
int func_0206b3c4(Unk02069fec *p, int angle);
void func_0206b4a8(Unk02069fec *p, int angle);
void func_0206b4c8(Unk02069fec *p);
}

bool func_02097248(int button);

extern Unk020c3ba4 data_020c3ba4;
extern Unk020d60c8 data_020d60c8;
extern Unk020c43a8 data_020c43a8;
extern short data_020af1e8[];

static inline Unk020899a4 *func_camera() {
    return (Unk020899a4 *)&data_020c7d38.unk54;
}

static inline int func_fxmulr(int a, int b) {
    return (int)(((s64)a * b + 0x800) >> 12);
}

/* A block copy of a vector (ldm / stm), through the record's wrapper. */
static inline void func_copy(Unk02098ff0 &dst, const Unk02098ff0 &src) {
    *(Unk0206a07cVec *)&dst = *(const Unk0206a07cVec *)&src;
}

static inline int func_abs(int x) {
    return x > 0 ? x : -x;
}

/* Brings the angle cur within lim of ref (16-bit angles). */
static inline int func_limit(int cur, int ref, int lim) {
    int d = (u16)ref - (u16)cur;
    if (d != 0 && func_abs(d) > lim) {
        if (d < 0) {
            return (u16)(ref + lim);
        }
        return (u16)(ref - lim);
    }
    return cur;
}

void func_02069ea8(Unk02069fec *p) {
    Unk020899a4 *cam = func_camera();

    if (cam->fov > p->fovMax) {
        cam->func_02089b48(p->fovMax);
    } else if (cam->fov < p->fovMin) {
        cam->func_02089b48(p->fovMin);
    }
    int fov = cam->fov;
    int vfov = (fov << 8) / 0xc0;
    cam->angles.v.x = func_limit(cam->angles.v.x, p->angles.v.x, (p->fovMax - fov) >> 1);
    if ((p->unk100 - vfov) >> 1 > 0) {
        cam->angles.v.y = func_limit(cam->angles.v.y, p->angles.v.y, (p->unk100 - vfov) >> 1);
    }
    p->saved = cam->angles;
    p->fov = cam->fov;
}

Unk02069fec::Unk02069fec()
    : pos(0, 0, 0), angles(0, 0, 0), saved(0, 0, 0), mode(0), flags(0), state(0), timer(0) {
    fov = 0x1555400;
    fovTo = 0;
    fovT = 0;
    unk100 = 0x1fffe00;
    fovMax = 0x1fffe00;
    fovMin = 0x1555400;
}

void func_0206a07c(Unk0206a07c *r) {
    r->unk8 = 0x1555;
    r->unk4 = 0x1555;
    r->unkc = Unk0206a07cVec(0, 0x5000, 0x14000);
    r->unk18 = Unk0206a07cVec(0, 0, 0);
}

void func_0206a0e4(Unk0206a0e4 *r, void *map, unsigned long key, const Unk0206a07c *rec) {
    Unk0206a07c *found = func_02058134(map, key);
    r->unk4 = found != 0 ? found->unkc.v.x : 0;
    r->unk8 = 0;
    r->unkc = rec->unk18.v.z;
}

static inline bool func_near(const Unk02098ff0 &a, const Unk02098ff0 &b) {
    return func_abs(a.x - b.x) < 4 && func_abs(a.y - b.y) < 4 && func_abs(a.z - b.z) < 4;
}

extern "C" inline int func_0206a7fc(int t, int a, int b) {
    return a + func_fxmulr(t, b - a);
}

extern "C" inline void func_0206a81c(int *fov, int *eye, int *target, const Unk0206a07c *rec) {
    *fov = rec->unk4;
    eye[0] = rec->unkc.v.y;
    eye[1] = rec->unkc.v.z;
    target[0] = rec->unk18.v.y;
    target[1] = rec->unk18.v.z;
}

static inline void func_setPlane(Unk020987d8 *dst, Unk02098ff0 n, Unk02098ff0 pt) {
    *dst = Unk020987d8(n.func_02099088(), pt);
}

static inline Unk020987d8 func_makePlane(int nx, int nz, int px, int pz) {
    Unk02098ff0 pt = func_020130d8(px, 0, pz);
    Unk02098ff0 n = func_020130d8(nx, 0, nz);
    return Unk020987d8(n.func_02099088(), pt);
}

/* Mode 1: the camera follows a point kept inside four planes. */
static inline void func_setupFollow(Unk02069fec *p, void *map) {
    p->mode = 1;
    p->flags = 0x30;
    p->timer = 0;
    Unk0206a07c *a = func_02058134(map, 0xd88296f5);
    Unk0206a07c *b = func_02058134(map, 0xcbc0c737);
    Unk0206a07c def;
    func_0206a07c(&def);
    if (a == 0) {
        a = &def;
    }
    if (b == 0) {
        b = &def;
    }
    Unk0206a0e4 *c = func_02058194(map, 0xfa550a17);
    Unk0206a0e4 *d = func_02058194(map, 0x2e27f4f6);
    Unk0206a0e4 defC;
    if (c == 0) {
        c = &defC;
        func_0206a0e4(c, map, 0x5761da99, b);
    }
    Unk0206a0e4 defD;
    if (d == 0) {
        d = &defD;
        func_0206a0e4(d, map, 0x545be97e, a);
    }
    if (b->unk18.v.z > b->unkc.v.z) {
        p->rangeX.x = c->unk4;
        p->rangeX.y = d->unk4;
        p->rangeZ.x = c->unkc;
        p->rangeZ.y = d->unkc;
        func_0206a81c(&p->fovA, p->eyeA, p->targetA, b);
        func_0206a81c(&p->fovB, p->eyeB, p->targetB, a);
    } else {
        p->rangeX.x = d->unk4;
        p->rangeX.y = c->unk4;
        p->rangeZ.x = d->unkc;
        p->rangeZ.y = c->unkc;
        func_0206a81c(&p->fovA, p->eyeA, p->targetA, a);
        func_0206a81c(&p->fovB, p->eyeB, p->targetB, b);
    }
    if (p->rangeX.x > p->rangeX.y) {
        Unk02098e70 v(p->rangeX.y, p->rangeX.x);
        func_0200ca68(&p->rangeX, &v);
    }
    if (p->rangeZ.x > p->rangeZ.y) {
        Unk02098e70 v(p->rangeZ.y, p->rangeZ.x);
        func_0200ca68(&p->rangeZ, &v);
    }
    p->unk7c = 0x1000;
    Unk02098ff0 o = func_0200f168()->func_04();
    p->unk80 = o.x;
    p->unk84 = o.z;
    p->unk7c = 0;
    p->center.x = func_0206a7fc(0x800, p->rangeX.x, p->rangeX.y);
    p->center.y = func_0206a7fc(0x800, p->rangeZ.x, p->rangeZ.y);
    p->half.x = func_0200cad0(p->rangeX.y - p->rangeX.x, 0x800);
    p->half.y = func_0200cad0(p->rangeZ.y - p->rangeZ.x, 0x800);
    Unk02098ff0 middle = func_020130d8(p->center.x, 0x19a, p->center.y);
    Unk02098ff0 extent = func_020130d8(p->half.x, 0, p->half.y);
    int s = func_0200cab0(0x1000);
    int k = func_0200ca88(0x1000);
    {
        Unk02098ff0 pt = func_020130d8(p->center.x - p->half.x, 0, p->center.y - p->half.y);
        Unk02098ff0 n = func_020130d8(k, 0, s);
        p->planes[2] = Unk020987d8(n.func_02099088(), pt);
    }
    {
        Unk02098ff0 pt = func_020130d8(p->center.x + p->half.x, 0, p->center.y - p->half.y);
        Unk02098ff0 n = func_020130d8(-k, 0, s);
        p->planes[3] = Unk020987d8(n.func_02099088(), pt);
    }
    {
        Unk02098ff0 pt = func_020130d8(p->center.x, 0, p->center.y - p->half.y);
        Unk02098ff0 n = func_020130d8(0, 0, 0x1000);
        p->planes[0] = Unk020987d8(n, pt);
    }
    {
        Unk02098ff0 pt = func_020130d8(p->center.x, 0, p->center.y + p->half.y);
        Unk02098ff0 n = func_020130d8(0, 0, -0x1000);
        p->planes[1] = Unk020987d8(n, pt);
    }
    func_0200ca68(&p->focus, &p->center);
    func_0200ca68(&p->goal, &p->focus);
    p->unkec = 0;
    Unk020899a4 *cam = (Unk020899a4 *)&data_020c7d38.unk54;
    Unk02098ff0Base last = cam->pos;
    for (int i = 0; i < 50; i++) {
        func_0206af98(p, -1);
        int dx = last.x - cam->pos.x;
        if (dx <= 0) {
            dx = -dx;
        }
        bool same = false;
        bool xy = false;
        if (dx < 4) {
            int dy = last.y - cam->pos.y;
            if (dy <= 0) {
                dy = -dy;
            }
            if (dy < 4) {
                xy = true;
            }
        }
        if (xy) {
            int dz = last.z - cam->pos.z;
            if (dz <= 0) {
                dz = -dz;
            }
            if (dz < 4) {
                same = true;
            }
        }
        if (same) {
            return;
        }
        *(Unk020899a4Angles *)&last = *(Unk020899a4Angles *)&cam->pos;
    }
}

/* Mode 0: the camera is turned with the buttons. */
static inline void func_setupFree(Unk02069fec *p, void *map) {
    p->mode = 0;
    p->flags = 0xf;
    Unk0206a07c *a = func_02058134(map, 0x6a2e6685);
    Unk0206a07c *b = func_02058134(map, 0x4cc2c87a);
    Unk0206a07c def;
    func_0206a07c(&def);
    if (a == 0) {
        a = &def;
    }
    if (b == 0) {
        b = &def;
    }
    p->fovMax = a->unk4;
    int deg = (int)(((s64)a->unk4 * 0x1680000 + 0x80000) >> 20);
    p->unk100 = (u16)(((s64)func_fxmulr(a->unk8, deg) * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
    p->fovMin = b->unk4;
    *(Unk0206a07cVec *)&p->pos = a->unkc;
    *(Unk0206a07cVec *)&p->target = a->unk18;
    if (p->fovMin > p->fovMax) {
        p->fovMin = p->fovMax;
    }
    if (p->fovMin * 4 / 3 > p->unk100) {
        p->fovMin = p->unk100 * 3 / 4;
    }
    Unk020899a4 *cam = func_camera();
    (Unk02098ff0Base &)cam->pos = p->pos;
    cam->func_020899a4(p->target, 0);
    cam->func_02089b48(p->fovMax);
    p->angles = cam->angles;
    p->saved = p->angles;
    p->fov = p->fovMax;
    p->timer = 0;
}

/* 95.04 %: stack layout of the plane temporaries (the original puts each
 * plane below its normal and point, as for a right-to-left evaluation of the
 * constructor's out-of-line vector arguments) and the copy of the camera
 * position in the settle loop (an out-of-line assignment here, ldm / stm in
 * the original). */
void func_0206a120(Unk02069fec *p) {
    void *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    Unk020593e4 info(data_020c3ba4.map, 0, 0);
    func_02056ed0(map, &info);
    if (func_020589ac(&data_020c3ba4, data_020c3ba4.map)->flags & 4) {
        func_setupFollow(p, map);
    } else {
        func_setupFree(p, map);
    }
}

/* 93.81 %: stack frame 0xC bytes smaller than the original (temporaries
 * placed differently), the focus x loaded twice for the eye and the target,
 * and the registers of the interpolation. */
void func_0206a850(Unk02069fec *p, int mode) {
    Unk02098e70 dir(0);
    bool slow = (data_020d60c8.flags & 4) != 0;
    int speed = slow ? 0x800 : 0x1000;

    if (!(p->state & 1) && (p->flags & 0x20)) {
        switch (mode) {
        case 4:
        case 5:
            break;
        case 6:
            dir.y = 0x1000;
            break;
        case 7:
            dir.y = -0x1000;
            break;
        default:
            if (data_020d60c8.unk15c) {
                dir.x = -(func_02097248(11) << 12) + (func_02097248(0) << 12);
                dir.y = -(func_02097248(1) << 12) + (func_02097248(10) << 12);
            } else {
                dir.x = -(func_02097248(5) << 12) + (func_02097248(4) << 12);
                dir.y = -(func_02097248(7) << 12) + (func_02097248(6) << 12);
            }
            break;
        }
        if ((int)dir.func_02098e94() != 0) {
            if (p->unkec < 0xe6 && p->unkec != 0) {
                Unk02098ff0 focus(p->focus.x, 0, p->focus.y);
                Unk020c43a8 *obj = &data_020c43a8;
                Unk02098ff0 o = obj->func_04();
                Unk02098ff0 move(dir.x, 0, dir.y);
                Unk02098ff0 to = o.func_02099150(focus);
                if (to.func_02099088().func_02099184(move.func_02099088()) > 0x800) {
                    p->unkec = 0;
                } else {
                    p->unkec = 0xf0;
                }
            } else {
                p->unkec = 0xf0;
            }
            dir.func_02098eec();
            Unk02098e70 step(dir.x * 0x333 >> 12, dir.y * 0x333 >> 12);
            Unk02098e70 scaled(step.x * speed >> 12, step.y * speed >> 12);
            p->goal.x += scaled.x;
            p->goal.y += scaled.y;
        }
    }
    if (p->unkec == 0) {
        Unk020c43a8 *obj = &data_020c43a8;
        Unk02098ff0 o = obj->func_04();
        p->goal.x = o.x;
        p->goal.y = o.z;
    } else if (p->unkec > 0 && (data_020d60c8.flags & 1)) {
        p->unkec -= slow ? 2 : 1;
        p->unkec = p->unkec < 0 ? 0 : p->unkec;
    }

    Unk02098ff0 point(p->goal.x, 0, p->goal.y);
    Unk02098ff0 move(dir.x, 0, dir.y);
    int limit = -0xc00;
    for (int i = 0; i < 4; i++) {
        if (p->planes[i].func_020988c0(point) < 0) {
            if (p->planes[i].normal.func_02099184(move) < limit) {
                func_copy(point, p->planes[i].func_02098824(point, move));
            } else {
                Unk02098ff0 push(func_fxmul(p->planes[i].normal.x, limit - 0x9400),
                                 func_fxmul(p->planes[i].normal.y, limit - 0x9400),
                                 func_fxmul(p->planes[i].normal.z, limit - 0x9400));
                func_copy(point, p->planes[i].func_02098824(point, push));
            }
        }
    }
    Unk02098e70 g(point.x, point.z);
    p->goal.x = g.x;
    p->goal.y = g.y;
    if ((int)p->goal.func_02098fcc(p->focus).func_02098e94() >= 0x19a) {
        Unk02098e70 delta = p->goal.func_02098fcc(p->focus);
        Unk02098e70 step(delta.x * 0xa4 >> 12, delta.y * 0xa4 >> 12);
        Unk02098e70 scaled(step.x * speed >> 12, step.y * speed >> 12);
        p->focus.x += scaled.x;
        p->focus.y += scaled.y;
    }

    Unk02098ff0 target;
    Unk02098ff0 eye;
    target.x = p->focus.x;
    eye.x = p->focus.x;
    int t = ((p->focus.y - p->rangeZ.x) << 12) / (p->rangeZ.y - p->rangeZ.x);
    if (t < 0) {
        t = 0;
    } else if (t > 0x1000) {
        t = 0x1000;
    }
    int fov;
    if (t == 0) {
        eye.y = p->eyeA[0];
        eye.z = p->eyeA[1];
        target.y = p->targetA[0];
        target.z = p->targetA[1];
        fov = p->fovA;
    } else {
        int u = 0x1000 - t;
        if (u == 0) {
            eye.y = p->eyeB[0];
            eye.z = p->eyeB[1];
            target.y = p->targetB[0];
            target.z = p->targetB[1];
            fov = p->fovA;
        } else {
            eye.y = p->eyeB[0] + func_fxmulr(u, p->eyeA[0] - p->eyeB[0]);
            eye.z = p->eyeB[1] + func_fxmulr(u, p->eyeA[1] - p->eyeB[1]);
            target.y = p->targetB[0] + func_fxmulr(u, p->targetA[0] - p->targetB[0]);
            target.z = p->targetB[1] + func_fxmulr(u, p->targetA[1] - p->targetB[1]);
            fov = p->fovB + func_fxmulr(u, p->fovA - p->fovB);
        }
    }
    Unk020899a4 *cam = func_camera();
    cam->func_02089b48(fov);
    cam->pos = eye;
    cam->func_020899a4(target, 0);
}

Unk020987d8 *func_0206af40(Unk02069fec *p, int i) {
    if (i < 0) {
        i = 0;
    } else if (i >= 4) {
        i = 0;
    }
    return &p->planes[i];
}

void func_0206af60(Unk02069fec *p, int i, const Unk020987d8 *plane) {
    if (i < 0) {
        i = 0;
    } else if (i >= 4) {
        i = 0;
    }
    p->planes[i] = *plane;
}

static inline int func_cos(u16 angle) {
    return data_020af1e8[(angle >> 4) * 2 + 1];
}

void func_0206af98(Unk02069fec *p, int mode) {
    switch (p->mode) {
    case 0: {
        if ((p->flags & 1) && !(p->state & 1) && !(p->state & 2)) {
            bool slow = (data_020d60c8.flags & 4) != 0;
            if (func_02097248(6)) {
                p->fov -= slow ? 0x19 : 0x32;
            }
            if (func_02097248(7)) {
                p->fov += slow ? 0x19 : 0x32;
            }
        }
        if (p->flags & 8) {
            unsigned char alt = data_020d60c8.unk15c;
            int shift = (data_020d60c8.flags & 4) ? 5 : 6;
            if ((alt && func_02097248(11)) || (!alt && func_02097248(5))) {
                func_0206b32c(p, -(1 << shift));
            }
            if ((alt && func_02097248(0)) || (!alt && func_02097248(4))) {
                func_0206b32c(p, 1 << shift);
            }
        }
        Unk020899a4 *cam = func_camera();
        func_copy(cam->pos, p->pos);
        cam->func_02089b48(p->fov);
        if (p->timer > 0) {
            p->timer--;
            cam->angles = p->saved;
        } else {
            Unk02098ff0 v;
            func_02066f14(&v, &data_020c43a8);
            cam->func_020899a4(v, 0);
        }
        if (p->flags & 2) {
            Unk020899a4 *c = func_camera();
            c->angles.v.x = func_020a1e68(p->saved.v.x, c->angles.v.x, 0x78);
            c->angles.v.y = func_020a1e68(p->saved.v.y, c->angles.v.y, 0x78);
            c->angles.v.z = func_020a1e68(p->saved.v.z, c->angles.v.z, 0x78);
        }
        if (p->flags & 4) {
            func_02069ea8(p);
        }
        break;
    }
    case 1:
        func_0206a850(p, mode);
        break;
    }
    if (!(p->state & 2) && !(p->state & 1)) {
        return;
    }
    if (p->state & 1) {
        func_0206b4c8(p);
        p->unkec = 0;
    }
    int t = p->fovT;
    if (t >= 0x1000) {
        if (p->state & 2) {
            p->state &= ~2;
        }
        func_camera()->func_02089b48(p->fovTo);
        return;
    }
    func_camera()->func_02089b48(p->fovFrom + func_fxmulr(t, p->fovTo - p->fovFrom));
    p->fovT += func_fxmulr(func_fxmulr(func_cos(func_fxmulr(func_fxmulr(p->fovT, 0x800), 0xffff000) >> 12), 0x800) + 0x900, 0x7b);
}

void func_0206b30c(Unk02069fec *p, int pitch, int yaw) {
    func_0206b32c(p, pitch);
    func_0206b348(p, yaw);
}

void func_0206b32c(Unk02069fec *p, int d) {
    if (d != 0) {
        p->saved.v.y += d;
    }
    p->timer = 0x2d;
}

void func_0206b348(Unk02069fec *p, int d) {
    if (d != 0) {
        p->saved.v.x += d;
    }
    p->timer = 0x2d;
}

void func_0206b364(Unk02069fec *p, int angle) {
    p->fovFrom = func_camera()->fov;
    p->fovTo = func_fxmulr(func_02077c60(angle, 0x168000), 0xffff000) >> 12;
    p->fovT = 0;
}

static inline float func_fx2f(int x) {
    return (float)x / 4096.0f;
}

int func_0206b3c4(Unk02069fec *p, int angle) {
    func_0206b364(p, angle);
    p->state &= ~2;
    p->state |= 1;
    int fx = p->fovFrom << 12;
#define DEG(x) (func_fx2f(x) * 360.0f / 65535.0f)
    return (int)(DEG(fx) > 0 ? DEG(fx) * 4096.0f + 0.5f : DEG(fx) * 4096.0f - 0.5f);
#undef DEG
}

void func_0206b4a8(Unk02069fec *p, int angle) {
    func_0206b364(p, angle);
    p->state = (p->state | 2) & ~1;
}

void func_0206b4c8(Unk02069fec *p) {
    p->timer = 0;
}
