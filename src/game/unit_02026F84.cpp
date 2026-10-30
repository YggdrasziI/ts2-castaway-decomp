/*
 * Unit 0x02026F84-0x02027994: a full-screen transition (Unk02027044, 0x644 bytes,
 * vtable 0x020B9180), built by the main game state (unit_0206BCE0.cpp). A sprite
 * follows a sine arc across the screen, the 256 colours of two layout palettes
 * blend, a second sprite goes back, then the screen fades out. The clock (hour at
 * least 6) picks which palette and sprite come first; a press of input 1 skips
 * the rest once the world palettes have nothing pending. That this is a day /
 * night transition is a hypothesis.
 *
 * Bounds: hypothesis. The start is the two palette load callbacks given to
 * func_020a80bc by the constructor, after the last inline slot func_02026f80 of
 * the paint screen; the end is the survival guide (unit_02027994.cpp). `.data`
 * holds this class's vtable with its header, `.bss` the instance the callbacks
 * use. Real file name unknown.
 *
 * Not complete: func_02027644 is below 100 % (comment above it).
 */

#include "game/unk_screen.h"
#include "game/unk_sim.h"

struct Unk020d6298 {
    int func_hour() const {
        return (unk4 & 0x7c0) >> 6;
    }

    int unk0;
    u32 unk4;
};

/* The main game state (func_0206bce0): only what is used here. */
class Unk0206bcf0 {
public:
    void func_0206f560(bool on);
    void func_0206f578(bool on);
    void func_0206f62c();
    void func_0206f654();
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

typedef void (*Unk020a80bcLoad)(const u16 *src, u32 unk, u32 size);

extern Unk020d6240 data_020d6240;
extern Unk020d6298 data_020d6298;
extern Unk020c3ba4 data_020c3ba4;
extern const short data_020af1e8[];

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a075c(void *input, int index);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
bool func_020a1280(Unk020d6240 *system, int a, int b);
void func_020a80bc(Unk020a7c90 *s, Unk020a80bcLoad load);
Unk020a80bcLoad func_020a80c4(Unk020a7c90 *s);
Unk0206bcf0 *func_0206bce0();
void func_02054360(void *p);
void DC_FlushRange(const void *start, u32 size);
void func_020790f0(const void *src, u32 offset, u32 size);
void func_02079088(void *data, u32 offset, u32 size);
void func_02026f84(const u16 *src, u32 unk, u32 size);
void func_02027004(const u16 *src, u32 unk, u32 size);
}

extern void *data_020bfc68;

class Unk02027044 : public Unk020a07d4 {
public:
    Unk02027044();
    virtual ~Unk02027044();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual bool func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_34();
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_0202758c();
    int func_02027610(int x);
    bool func_02027644();
    void func_020278ac();
    void func_02027904();

    u32 flags;
    int state;
    int step;
    u8 late;
    int count;
    Unk020a9d58 *layout1;
    Unk020a9d58 *layout0;
    Unk020a7c90 *sprite0;
    Unk020a7c90 *sprite1;
    Unk020a7c90 *bg0;
    Unk020a7c90 *bg1;
    Unk020a80bcLoad load0;
    Unk020a80bcLoad load1;
    u16 from[0x100];
    u16 to[0x100];
    u16 blend[0x100];
    int mix;
    int speed;
    Unk0206fac8 *palettes;
};

Unk02027044 *data_020be414;

static inline int func_mix(int a, int b, int inv, int t) {
    int v = (b * t + a * inv) >> 5;
    if (v < 0) {
        return 0;
    }
    if (v > 0x1f) {
        return 0x1f;
    }
    return v;
}

void func_02026f84(const u16 *src, u32 unk, u32 size) {
    for (u32 i = 0; i < size / 2; i++) {
        data_020be414->from[i] = src[i];
    }
    data_020be414->load0(src, unk, size);
    data_020be414->load1(src, unk, size);
}

void func_02027004(const u16 *src, u32 unk, u32 size) {
    for (u32 i = 0; i < size / 2; i++) {
        data_020be414->to[i] = src[i];
    }
}

Unk02027044::Unk02027044() : flags(0), state(0), step(0), count(0), mix(0), speed(0), palettes(data_020c3ba4.palettes) {
    late = data_020d6298.func_hour() >= 6;
    data_020be414 = this;

    Unk020a7af4Entry entries1[0x1e];
    Unk020a7af4 names1(entries1, 0x1e);
    Unk020a7af4Entry entries0[0x1e];
    Unk020a7af4 names0(entries0, 0x1e);

    layout1 = new Unk020a9d58(func_020a18e4()->archive, 1);
    func_020aba38(func_020a18e4()->archive, 0x6bd705b7, layout1, &names1);
    func_020a9db8(layout1, func_020a154c, 0);
    layout0 = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x3876ffb5, layout0, &names0);
    func_020a9db8(layout0, func_020a154c, 0);

    bg0 = func_020aa040(layout1, 6, func_020a7b50(&names1, 0x6b69d7a8));
    bg1 = func_020aa040(layout0, 6, func_020a7b50(&names0, 0xcb4c0704));
    load0 = func_020a80c4(bg0);
    load1 = func_020a80c4(bg1);

    if (late) {
        sprite1 = func_020aa040(layout1, 1, func_020a7b50(&names1, 0x1ea4e5bb));
        sprite0 = func_020aa040(layout1, 1, func_020a7b50(&names1, 0x6183214b));
        func_020a80bc(bg1, func_02026f84);
        func_020a80bc(bg0, func_02027004);
    } else {
        sprite0 = func_020aa040(layout1, 1, func_020a7b50(&names1, 0x1ea4e5bb));
        sprite1 = func_020aa040(layout1, 1, func_020a7b50(&names1, 0x6183214b));
        func_020a80bc(bg0, func_02026f84);
        func_020a80bc(bg1, func_02027004);
    }
    func_0206bce0()->func_0206f560(true);
    func_0206bce0()->func_0206f578(true);
    func_02054360(&data_020bfc68);
}

Unk02027044::~Unk02027044() {}

void Unk02027044::func_08() {
    void *list = data_020d6240.unk8;
    if (!func_020a0b8c(list, this)) {
        func_020a0b0c(list, this);
    }
}

bool Unk02027044::func_0c(short a) {
    func_020278ac();
    state = 1;
    return false;
}

bool Unk02027044::func_10() {
    state = 8;
    return false;
}

bool Unk02027044::func_28() {
    return !func_2c();
}

bool Unk02027044::func_2c() {
    return state == 8 || state == 0;
}

void Unk02027044::func_38(bool active) {
    if (!active) {
        return;
    }
    if (!(flags & 1)) {
        return;
    }
    if (flags & 2) {
        return;
    }
    switch (state) {
    case 1: {
        Unk020d6240 *system = func_020a18e4();
        func_02027644();
        func_020a1494(system, 2, 0x10);
        func_020a11f8(system, 2, 0);
        state = 2;
        break;
    }
    case 2:
        if (func_020a1280(func_020a18e4(), 2, 0)) {
            state = 3;
        }
        break;
    case 3:
        if (func_02027644()) {
            state = 6;
        }
        break;
    case 6: {
        Unk020d6240 *system = func_020a18e4();
        func_020a1494(system, 2, 0x10);
        func_020a11f8(system, 2, 1);
        state = 7;
        break;
    }
    case 7:
        if (func_020a1280(func_020a18e4(), 2, 1)) {
            func_02027904();
            delete layout1;
            layout1 = 0;
            delete layout0;
            layout0 = 0;
            func_0206bce0()->func_0206f560(false);
            func_0206bce0()->func_0206f578(false);
            state = 8;
            flags |= 2;
            func_0202758c();
            return;
        }
        break;
    case 8:
        break;
    }
    func_0202758c();
    func_020aa158(layout1);
    func_020aa158(layout0);
}

void Unk02027044::func_0202758c() {
    if (palettes == 0) {
        return;
    }
    switch (count) {
    case 0:
        if (late) {
            func_0206bce0()->func_0206f62c();
        } else {
            func_0206bce0()->func_0206f654();
        }
        break;
    case 1:
        palettes->func_0207001c(!late);
        break;
    default:
        palettes->func_0207005c();
        break;
    }
    count++;
}

bool Unk02027044::func_3c(bool done) {
    return true;
}

int Unk02027044::func_02027610(int x) {
    return 0x46000 - (data_020af1e8[((u16)((x / 256) * 8) >> 4) * 2] << 5);
}

/*
 * 99.45 %: the index, the inverse weight and the red channel rotate through lr,
 * r9 and r10 (r10, lr and r9 here). The rest is identical. The index is an
 * `unsigned int` (not u32). Tried: earlier declarations of the index, of the
 * weights and of the channels.
 */
bool Unk02027044::func_02027644() {
    if (palettes == 0) {
        return true;
    }
    if (func_020a075c(data_020d6240.input, 1) && palettes->pending < 1) {
        step = 3;
    }
    switch (step) {
    case 0:
        speed += 0xa4;
        func_020a7c90(sprite0, speed + func_020a7ca4(sprite0));
        func_020a7cac(sprite0, func_02027610(func_020a7ca4(sprite0)));
        if (func_020a7ca4(sprite0) >= 0x100000) {
            step = 1;
        }
        break;
    case 1: {
        mix += 0x29;
        if (mix > 0x1000) {
            mix = 0x1000;
            step = 2;
        }
        int t = mix >> 7;
        int inv = 0x20 - t;
        for (unsigned int i = 0; i < 0x100; i++) {
            int a = from[i];
            int b = to[i];
            int ar = (a >> 10) & 0x1f;
            int br = (b >> 10) & 0x1f;
            int ag = (a >> 5) & 0x1f;
            int bg = (b >> 5) & 0x1f;
            int ab = a & 0x1f;
            int bb = b & 0x1f;
            int r = func_mix(ar, br, inv, t);
            int g = func_mix(ag, bg, inv, t);
            int c = func_mix(ab, bb, inv, t);
            blend[i] = (r << 10) | (g << 5) | c;
        }
        DC_FlushRange(blend, 0x200);
        func_020790f0(blend, 0, 0x200);
        func_02079088(blend, 0, 0x200);
        break;
    }
    case 2:
        speed -= 0xa4;
        if (speed < 0) {
            speed = 0;
            step = 3;
        }
        func_020a7c90(sprite1, speed + func_020a7ca4(sprite1));
        func_020a7cac(sprite1, func_02027610(func_020a7ca4(sprite1)));
        break;
    case 3:
        return true;
    }
    return false;
}

void Unk02027044::func_020278ac() {
    if (flags & 1) {
        return;
    }
    func_020aa06c(layout1, true);
    func_020aa06c(layout0, true);
    func_020a7c90(sprite1, -0x40000);
    func_020a14e0(func_020a18e4(), 0);
    flags |= 1;
}

void Unk02027044::func_02027904() {
    if (!(flags & 1)) {
        return;
    }
    func_020aa06c(layout1, false);
    func_020aa06c(layout0, false);
    func_020a14e0(func_020a18e4(), 1);
    flags &= ~1;
}

bool Unk02027044::func_14() {
    return (flags & 2) != 0;
}

void Unk02027044::func_18() {
    flags |= 2;
}

void Unk02027044::func_1c() {
    flags &= ~2;
}

bool Unk02027044::func_20() {
    return false;
}

void Unk02027044::func_24() {}

bool Unk02027044::func_34() {
    return false;
}
