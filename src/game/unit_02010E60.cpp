/*
 * Fishing microgames: the water tile under the player, the fish speed, the tint of
 * three palettes by the water colour, the frames of the water sprites, the catch.
 * The bounds are a hypothesis from the data: the word table follows the vtable of
 * unit_02010920.cpp, and mwccarm lays such a table out before the vtable of a file;
 * `.bss` gets the object first and the local static after it only with a function
 * before `func_02010efc` in the file. Layouts come from the code; all names are
 * placeholders.
 */
#include "game/unk_screen.h"
#include "game/unk_fishing.h"
#include "game/unk_sim.h"
#include "game/unk_plane.h"

extern "C" int func_02077c60(int a, int b);

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
int func_020a69cc(Unk020a7c90 *s);
int func_020a69d4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a80bc(Unk020a7c90 *s, Unk020a80bcLoad load);
Unk020a80bcLoad func_020a80c4(Unk020a7c90 *s);
extern Unk020c43a8 data_020c43a8;
extern Unk020c3ba4 data_020c3ba4;
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
extern u8 data_020bfc9c[];
int func_020a655c();
int func_02097acc(int x);
int func_020a7a44(Unk020a7c90 *s);
int func_020a7a60(Unk020a7c90 *s);
int func_020a7a7c(Unk020a7c90 *s);
int func_02054c1c(void *p, void *def, int a);
void *func_0206bce0();
Unk020987d8 *func_0206af40(void *p, int i);
void func_0206af60(void *p, int i, const Unk020987d8 *plane);
void DC_FlushRange(const void *start, u32 size);
int func_02011188(int *v);
void func_020111ac(const u16 *src, u32 offset, u32 size);
}

#pragma explicit_zero_data on
static const u16 *data_020b7bb4[3] = {0, 0, 0};
#pragma explicit_zero_data reset

/* The water colour, the three tinted palettes, the loader they replace. */
static struct {
    int color[3];
    u16 palettes[3][16];
    Unk020a80bcLoad load;
} data_020be2f8;

static inline Unk020c43a8 *func_player() {
    return &data_020c43a8;
}

extern "C" u32 func_02010e60() {
    Unk020680d4Cell cell = func_player()->func_14();
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    u32 v = *layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000;
    bool water = true;
    if (v != 0x4000 && v != 0xc000) {
        water = false;
    }
    if (water) {
        return v == 0xc000 ? 0x70623103 : 0x9e3e1df3;
    }
    return 0x694ac647;
}

extern "C" int func_02010efc() {
    static int data_020be368 = func_02097acc(0x6400) + 0x20;
    return data_020be368;
}

extern "C" void func_02010f40(Unk020a9d58 *l, Unk020a7af4 *n, Unk020a7c90 *s) {
    u32 hash = func_020a655c() == 1 ? 0x23aea99b : 0xcf5cbee8;
    Unk020a7c90 *c = func_020aa040(l, 0xc, func_020a7b50(n, hash));
    data_020be2f8.color[0] = func_020a7a44(c) << 4;
    data_020be2f8.color[1] = func_020a7a60(c) << 4;
    data_020be2f8.color[2] = func_020a7a7c(c) << 4;
    data_020be2f8.load = func_020a80c4(s);
    for (int i = 0; i < 3; i++) {
        data_020b7bb4[i] = 0;
        func_020a80bc(s, (Unk020a80bcLoad)func_020111ac);
        s = (Unk020a7c90 *)((u8 *)s + 0x2c);
    }
}

extern "C" void func_02011010() {
    void *game = func_0206bce0();
    Unk02098ff0 pos = func_player()->func_04();
    Unk020987d8 plane = *func_0206af40((u8 *)game + 0x10, 0);
    func_0206af60((u8 *)game + 0x10, 0, &plane);
}

extern "C" void func_02011074(Unk020a7c90 **a, Unk020a7c90 **b, int *timer) {
    if (--*timer == 3) {
        int f = func_020a69cc(a[0]);
        int count = func_020a69d4(a[0]);
        f++;
        if (f == count) {
            f = 0;
        }
        for (int i = 0; i < 4; i++) {
            func_020a69ac(a[i], f);
        }
    } else if (*timer == 0) {
        int f = func_020a69cc(b[0]);
        int count = func_020a69d4(b[0]);
        f++;
        if (f == count) {
            f = 0;
        }
        for (int i = 0; i < 4; i++) {
            func_020a69ac(b[i], f);
        }
        *timer = 6;
    }
}

extern "C" void func_02011128(int *counts, void **kinds) {
    void *inv = data_020bfc9c;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < counts[i]; j++) {
            func_02054c1c(inv, kinds[i], 0);
        }
    }
}

extern "C" int func_02011188(int *v) {
    int sum = v[0];
    for (int i = 1; i < 3; i++) {
        sum += v[i];
    }
    return sum;
}

static inline int func_mul(int a, int b) {
    return (int)(((s64)a * b + 0x800) >> 12);
}

extern "C" void func_020111ac(const u16 *src, u32 offset, u32 size) {
    u16 *out = 0;
    int free = -1;
    for (int i = 0; i < 3; i++) {
        if (data_020b7bb4[i] == src) {
            out = data_020be2f8.palettes[i];
            break;
        }
        if (data_020b7bb4[i] == 0) {
            free = i;
        }
    }
    if (out == 0) {
        data_020b7bb4[free] = src;
        out = data_020be2f8.palettes[free];
    }
    int inv = 0;
    int avg = func_mul(data_020be2f8.color[0] + data_020be2f8.color[1] + data_020be2f8.color[2], 0x555);
    if (avg != 0) {
        inv = func_02077c60(0x1000, avg);
    }
    int r = func_mul(data_020be2f8.color[0] * 2, inv);
    int g = func_mul(data_020be2f8.color[1] * 2, inv);
    int b = func_mul(data_020be2f8.color[2] * 2, inv);
    for (int i = 0; i < 16; i++, src++) {
        u32 c = *src;
        u32 sr = c << 27;
        u32 lr = sr >> 20;
        u32 sg = (int)c >> 5 << 27;
        u32 lg = sg >> 20;
        u32 sb = (int)c >> 10 << 27;
        u32 lb = sb >> 20;
        int lum = func_mul(lb, 0x1d3) + (func_mul(lr, 0x4c9) + func_mul(lg, 0x964));
        lum = func_mul(lum, 0x555);
        u16 nr = (int)(func_mul(lum, r) + lr) >> 8;
        u32 ng = (u32)(((int)(func_mul(lum, g) + lg) >> 1) << 9) >> 16;
        u32 nb = (u32)(((int)(func_mul(lum, b) + lb) >> 1) << 9) >> 16;
        if (i == 0) {
            out[i] = c;
        } else {
            out[i] = nb << 10 | ng << 5 | nr;
        }
    }
    DC_FlushRange(out, size);
    data_020be2f8.load((void *)out, offset, size);
}
