/*
 * Unit 0x020238EC-0x0202402C: a screen with one layout, one button and a view
 * moved by the touch screen (Unk020238ec, 0xBC bytes, vtable 0x020B8EC8), built
 * by the main game state (unit_0206BCE0.cpp). The clock (hour below 6) picks one
 * of two layouts. While input 1 is held, the position of the first sprite moves
 * against an offset from 0x80 given by func_02097a4c, scaled and clamped by two
 * values read from the layout. What it shows is unknown.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * Unk0203c188 in unit_02021CBC.cpp; the end is the paint screen
 * (unit_0202402C.cpp). `.data` holds the vtable with its header. Real file name
 * unknown.
 *
 * Not complete: the constructor is below 100 % (comment above it).
 */

#include "game/unk_screen.h"

struct Unk020d6298 {
    int func_hour() const {
        return (unk4 & 0x7c0) >> 6;
    }

    int unk0;
    u32 unk4;
};

/* The survival guide animation of the player (unit_02055118.cpp): opaque here. */
struct Unk02055118 {
    u8 unk0[9];
    u8 unk9;
};

/* The main game state (func_0206bce0): only what is used here. */
class Unk0206bcf0 {
public:
    void func_0206f560(bool on);
    void func_0206f578(bool on);

    u8 unk0[0x14c];
    Unk02055118 guide;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The sprite whose position this screen moves. */
class Unk020238ecSprite : public Unk020a7c90 {
public:
    u8 unk4[0x30];
    Unk02098e70Base *position;
};

extern Unk020d6240 data_020d6240;
extern Unk020d6298 data_020d6298;

Unk02098e70Base *func_02097a4c();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a078c(void *input, int index);
Unk02098e70 func_020a07bc(void *input, int index);
void func_020a122c(Unk020d6240 *system);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
Unk02098e70Base *func_020a9044(Unk020a7c90 *s);
void func_020aa1c0(Unk020a9d58 *layout, Unk02098e70 *point, bool pressed);
Unk0206bcf0 *func_0206bce0();
void func_0205515c(Unk02055118 *p, int a);
void func_02055220(Unk02055118 *p, int state, int count);
}

class Unk020238ec : public Unk020a07d4 {
public:
    Unk020238ec();
    virtual ~Unk020238ec();
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

    void func_02023b8c();
    void func_02023be0();

    u32 flags;
    Unk020a07d4Timer fade;
    short unk10;
    Unk020a9d58 *layout;
    Unk020238ecSprite *sprite;
    Unk020a7c90 *sprite2;
    Unk02098e70Base *position;
    Unk02050640 button;
    Unk02098e70Base speed;
    Unk02098e70Base limit;
    int unkb8;
};

/*
 * 94.69 %: the two copies from the layout are scheduled differently (the original
 * loads the next hash after both stores, and narrows it through r1). Tried: a
 * local pointer, field by field copies, a local sprite, Unk02098e70 fields and
 * inline helpers (the last ones worse).
 */
Unk020238ec::Unk020238ec() : flags(0), unk10(0), layout(0), sprite(0), sprite2(0), position(0), unkb8(0) {
    Unk020a7af4Entry entries[0x14];
    Unk020a7af4 names(entries, 0x14);
    Unk02093648 *archive = func_020a18e4()->archive;
    if (layout == 0) {
        layout = new Unk020a9d58(archive, 0);
    }
    if (data_020d6298.func_hour() < 6) {
        func_020aba38(archive, 0xe7fcaee3, layout, &names);
    } else {
        func_020aba38(archive, 0x8c4e4cb1, layout, &names);
    }
    sprite = (Unk020238ecSprite *)func_sprite(layout, 2, func_020a7b50(&names, 0xc6ae8606));
    sprite2 = func_sprite(layout, 2, func_020a7b50(&names, 0x5fc4ca01));
    button.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xc2f94842)), false);
    button.func_02050c48(0, 1, -1);
    limit = *func_020a9044(func_sprite(layout, 8, func_020a7b50(&names, 0x6f0e712e)));
    speed = *func_020a9044(func_sprite(layout, 8, func_020a7b50(&names, 0xa1f1d1e7)));
}

Unk020238ec::~Unk020238ec() {
    func_02023b8c();
    delete layout;
}

void Unk020238ec::func_02023b8c() {
    if (!(flags & 1)) {
        return;
    }
    func_020aa06c(layout, false);
    func_020a14e0(func_020a18e4(), 1);
    func_0206bce0()->func_0206f578(false);
    func_0206bce0()->func_0206f560(false);
    flags &= ~1;
}

void Unk020238ec::func_02023be0() {
    if (flags & 1) {
        return;
    }
    func_020aa06c(layout, true);
    func_020a14e0(func_020a18e4(), 0);
    flags |= 1;
}

void Unk020238ec::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
    if (unkb8 != 0) {
        Unk02055118 *guide = &func_0206bce0()->guide;
        func_0205515c(guide, unkb8);
        guide->unk9 = 0;
        func_02055220(guide, 0x41, 0);
    }
}

void Unk020238ec::func_38(bool active) {
    if (!active) {
        return;
    }
    fade.func_step();
    button.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_02023b8c();
    }
}

bool Unk020238ec::func_3c(bool done) {
    void *input = data_020d6240.input;
    if (func_020a078c(input, 1)) {
        Unk02098e70 point = func_020a07bc(input, 1);
        func_020aa1c0(layout, &point, true);
        if (position != 0) {
            position->x -= (func_02097a4c()->x - 0x80) * speed.x;
            if (position->x > limit.x) {
                position->x = limit.x;
            }
            if (position->x < -limit.x) {
                position->x = -limit.x;
            }
            position->y -= (func_02097a4c()->y - 0x80) * speed.y;
            if (position->y > limit.y) {
                position->y = limit.y;
            }
            if (position->y < -limit.y) {
                position->y = -limit.y;
            }
        } else {
            position = sprite->position;
        }
    } else {
        Unk02098e70 point(0, 0);
        func_020aa1c0(layout, &point, false);
    }
    button.func_0c(done);
    if (button.touch.flags & 8) {
        func_18();
    }
    return true;
}

bool Unk020238ec::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.state = 0;
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a122c(func_020a18e4());
    func_02023be0();
    return false;
}

bool Unk020238ec::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

void Unk020238ec::func_18() {
    flags |= 2;
}

bool Unk020238ec::func_34() {
    return false;
}

bool Unk020238ec::func_28() {
    return fade.func_shown();
}

bool Unk020238ec::func_2c() {
    return fade.func_hidden();
}

bool Unk020238ec::func_14() {
    return (flags & 2) != 0;
}

void Unk020238ec::func_1c() {
    flags &= ~2;
}

bool Unk020238ec::func_20() {
    return false;
}

void Unk020238ec::func_24() {}
