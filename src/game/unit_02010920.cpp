/*
 * Code shared by the fishing microgames (unit_020142E0.cpp, unit_02018668.cpp): the
 * fish base Unk02010920, the view of a fish record of the database and the draw of
 * the fish of a place. `func_02010b8c` / `func_02010ba8` are written as plain
 * functions; a constructor and a destructor are as likely (hypothesis). The two
 * file names are arrays because string literals land after the vtable. Layouts come
 * from the code; all names are placeholders.
 */
#include "game/unk_screen.h"
#include "game/unk_fishing.h"
#include "game/unk_sim.h"
#include "game/unk_plane.h"

extern "C" int func_02077c60(int a, int b);

/* The view of a fish record: the record, then one word. */
struct Unk02010b8c {
    void *def;
    int unk4;
};

class Unk020c43a8 : public Unk020680d4Base {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);
};

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
};

/* The tile layer returned by func_02056ed0. */
struct Unk02056ed0 {
    int unk0;
    int unk4;
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;

    u32 *func_tile(u32 x, u32 y) {
        return &tiles[y * info->width + x];
    }
};

typedef void (*Unk020a80bcLoad)(void *data, u32 offset, u32 size);

extern "C" {
void func_020a6980(Unk020a7c90 *s, u32 hash);
int func_020a69cc(Unk020a7c90 *s);
int func_020a69d4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a80bc(Unk020a7c90 *s, Unk020a80bcLoad load);
Unk020a80bcLoad func_020a80c4(Unk020a7c90 *s);
extern Unk020c3ba4 data_020c3ba4;
extern const s16 data_020af1e8[];
extern u8 data_020d62a4[];
extern u8 data_020c3fc4[];
extern Unk020c43a8 data_020c43a8;
extern u8 data_020bfc9c[];

void func_0200ada4(Unk02010920 *e, void *def);
void func_0200af18(void *view, void *def, u32 key);
void func_0200af2c(void *view);
u32 func_0200afc0(void *def);
int func_0200e0bc(void *view);
int func_0200e0d0(void *view, u32 key);
int func_0200e0fc(void *def);
int func_0200e120(void *def);
u32 func_0209a3c4(u32 h, const char *s);
int func_020a5ec0();
int func_020a5ef0(int a, int b);
int func_020a655c();
int func_02097acc(int x);
void *func_0205f714(void *db, u32 key, void *rec);
u32 func_020a1f84(void *random);
int func_020a7a44(Unk020a7c90 *s);
int func_020a7a60(Unk020a7c90 *s);
int func_020a7a7c(Unk020a7c90 *s);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
int func_02054c1c(void *p, void *def, int a);
void *func_0206bce0();
Unk020987d8 *func_0206af40(void *p, int i);
void func_0206af60(void *p, int i, const Unk020987d8 *plane);
void DC_FlushRange(const void *start, u32 size);

Unk02010b8c *func_02010b8c(Unk02010b8c *p, void *def);
Unk02010b8c *func_02010ba8(Unk02010b8c *p);
int func_02010bbc(Unk02010b8c *p);
int func_02010bd0(Unk02010b8c *p);
int func_02010be4(Unk02010b8c *p);
bool func_02010bf8(Unk02010b8c *p);
bool func_02010c2c(Unk02010b8c *p);
int func_02010c60(void *p);
int func_02010efc();
int func_02011188(int *v);
}

static const u32 data_020ae678[1] = {0xef276208};

static char data_020b7b84[] = "swim.nitro_map";
static char data_020b7b94[] = "turn.nitro_map";

Unk02010920::Unk02010920(int count) : Unk0200ad70(count) {
}

Unk02010920::~Unk02010920() {
}

static inline int func_sin(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2];
}

static inline int func_cos(int angle) {
    return data_020af1e8[((u16)angle >> 4) * 2 + 1];
}

/* 99.79 %: the two angles are swapped between r5 and r6. */
extern "C" void func_02010954(Unk02010920 *e, void *def) {
    func_0200ada4(e, def);
    int x = 0x1000 - func_0200e0fc(def);
    e->move.unk14 = (int)(((s64)x << 13) >> 12) + 0x800;
    e->move.speed = func_0200e120(def);
    u16 b;
    u16 a = func_020a5ec0();
    b = a + 0x8000 + (func_020a5ef0(0, 0x4000) - 0x2000);
    int d = func_02010efc();
    Unk02098e70 c(0x80000, 0x60000);
    func_set(e->unkb0, c.func_02098fa8(Unk02098e70(d * func_sin(a), d * func_cos(a))));
    func_set(e->unka0, c.func_02098fa8(Unk02098e70(d * func_sin(b), d * func_cos(b))));
    func_set(e->unka8, e->unka0.func_02098fcc(e->unkb0).func_02098eec());
    func_set(e->pos, e->unkb0);
    func_set(e->target, e->unka0);
    u32 key = func_0200afc0(def);
    e->anims[0] = func_0209a3c4(key, data_020b7b84);
    e->anims[1] = func_0209a3c4(key, data_020b7b94);
    e->bait = func_02010c60(def) - 1;
}

bool Unk02010920::func_04(int i, bool force) {
    if (!force && index == i) {
        return false;
    }
    index = i;
    Unk020a7c90 **s = (Unk020a7c90 **)func_00();
    func_020a6980(s[0], anims[index]);
    func_020a6980(s[1], anims[index]);
    return true;
}

extern "C" Unk02010b8c *func_02010b8c(Unk02010b8c *p, void *def) {
    func_0200af18(p, def, 0xef276208);
    return p;
}

extern "C" Unk02010b8c *func_02010ba8(Unk02010b8c *p) {
    func_0200af2c(p);
    return p;
}

extern "C" int func_02010bbc(Unk02010b8c *p) {
    return func_0200e0d0(p, 0x6e48cc6d);
}

extern "C" int func_02010bd0(Unk02010b8c *p) {
    return func_0200e0d0(p, 0x01d87374);
}

extern "C" int func_02010be4(Unk02010b8c *p) {
    return func_0200e0d0(p, 0x496b4289);
}

extern "C" bool func_02010bf8(Unk02010b8c *p) {
    int v = func_0200e0d0(p, 0x1349d333);
    return v == (int)0xe24515eb || v == 0x03d1a6ec;
}

extern "C" bool func_02010c2c(Unk02010b8c *p) {
    int v = func_0200e0d0(p, 0x1349d333);
    return v == 0x583e30a2 || v == 0x03d1a6ec;
}

extern "C" int func_02010c60(void *p) {
    return func_0200e0d0(p, 0x03e0cdc7);
}

/* 97.28 %: same code, registers differ (declaration orders and types searched). */
extern "C" int func_02010c74(int depth, int mode, int lang, void **out, int n) {
    void *recs[50];
    int chances[50];
    Unk02010b8c view;
    void *rec;
    u32 key = data_020ae678[0];
    int count = 0;
    rec = func_0205f714(data_020c3fc4, key, 0);
    for (; rec != 0; rec = func_0205f714(data_020c3fc4, key, rec)) {
        func_02010b8c(&view, rec);
        if (!func_0200e0bc(&view)) {
            func_02010ba8(&view);
            continue;
        }
        if (func_02010bd0(&view) > depth) {
            func_02010ba8(&view);
            continue;
        }
        if (mode != func_02010bbc(&view)) {
            func_02010ba8(&view);
            continue;
        }
        if (lang != 0) {
            if (!func_02010bf8(&view)) {
                func_02010ba8(&view);
                continue;
            }
        } else {
            if (!func_02010c2c(&view)) {
                func_02010ba8(&view);
                continue;
            }
        }
        chances[count] = func_02010be4(&view);
        recs[count++] = rec;
        if (count == 50) {
            func_02010ba8(&view);
            break;
        }
        func_02010ba8(&view);
    }
    int limit = n;
    if (count <= n) {
        limit = count;
    }
    int i = 0;
    while (i < limit) {
        u32 r = func_020a1f84(data_020d62a4) % count;
        void *pick = recs[r];
        if (pick != 0) {
            int chance = chances[r];
            bool ok = true;
            for (int j = 0; j < chance; j++) {
                if (!(func_020a1f84(data_020d62a4) & 1)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                out[i] = pick;
                recs[r] = 0;
                i++;
            }
        }
    }
    return limit;
}
