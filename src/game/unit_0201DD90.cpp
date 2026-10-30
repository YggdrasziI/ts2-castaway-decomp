/*
 * Unit 0x0201DD90-0x0201E2B0: a screen around the keyboard (Unk0201dd90, 0x29E8
 * bytes, vtable 0x020B8BD8), a window of the main game state
 * (unit_0206BCE0.cpp). It loads the backdrop
 * build/data/screens/survivalguide/backdrop.nitro_map on one background layer
 * and logs "Starting Survival Guide". When the keyboard gives a result, the
 * screen asks to close and clears the text. What the text is used for is
 * unknown.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * the screen before it; the end is func_0201e2b0, called only by the live mode
 * screen (unit_0201E300.cpp). `.data` holds the strings and the vtable with its
 * header. Real file name unknown.
 */

#include "game/unk_screen.h"

class Unk02095140;

class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
    void func_0208d7a0(bool visible);
};

class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbf8();
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    void func_0208df4c(Unk0208d304 *layer);
    void func_0208e058(Unk02095140 *file, int index, int mask);
};

/* The file list on the stack or in a screen: opaque here. */
class Unk020a3f8c {
public:
    Unk020a3f8c();
    ~Unk020a3f8c();

    u8 unk0[8];
};

/* The keyboard screen of unit_0204D698.cpp (0x29C8 bytes): only what is used here. */
class Unk0204d698 {
public:
    Unk0204d698();
    ~Unk0204d698();
    virtual void func_00();
    virtual bool func_04(bool locked);
    virtual void func_08();
    virtual void func_0c(int priority);
    void func_0204e9d8();
    void func_0204ea00(const char *text);

    u8 unk4[0x74];
    int result;
    u8 unk7c[0x294c];
};

/* The main game state (func_0206bce0): only what is used here. */
class Unk0206bcf0 {
public:
    void func_0206f578(bool on);
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

extern Unk020d6240 data_020d6240;

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a122c(Unk020d6240 *system);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
void func_020a3fb0(Unk020a3f8c *files, Unk02093648 *archive);
Unk02095140 *func_020a4008(Unk020a3f8c *files, const char *name);
void func_020897b4(const char *fmt, ...);
Unk0206bcf0 *func_0206bce0();
}

class Unk0201dd90 : public Unk020a07d4 {
public:
    Unk0201dd90();
    virtual ~Unk0201dd90();
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

    void func_0201de58();
    void func_0201dec4();

    u32 flags;
    Unk020a07d4Timer fade;
    u16 unk10;
    Unk0208d304 *layer;
    Unk020a3f8c files;
    Unk0204d698 keyboard;
};

Unk0201dd90::Unk0201dd90() : flags(0), unk10(0), layer(0) {}

Unk0201dd90::~Unk0201dd90() {
    func_0201de58();
}

void Unk0201dd90::func_0201de58() {
    if (!(flags & 1)) {
        return;
    }
    Unk0208d304 *old = layer;
    if (old != 0) {
        Unk0208db14::func_0208dbf8()->func_0208df4c(old);
    }
    layer = 0;
    keyboard.func_08();
    func_020a14e0(func_020a18e4(), 1);
    func_0206bce0()->func_0206f578(false);
    flags &= ~1;
}

void Unk0201dd90::func_0201dec4() {
    if (flags & 1) {
        return;
    }
    func_020a3fb0(&files, func_020a18e4()->archive);
    Unk02095140 *file = func_020a4008(&files, "build/data/screens/survivalguide/backdrop.nitro_map");
    unk10 = 1;
    if (file != 0) {
        Unk0208d304 *old = layer;
        if (old != 0) {
            Unk0208db14::func_0208dbf8()->func_0208df4c(old);
        }
        layer = Unk0208db14::func_0208dbf8()->func_0208dc44(file, 1, -1, 0);
        if (layer != 0) {
            layer->func_0208d7a0(true);
            layer->func_0208d4b0(unk10);
        }
        Unk0208db14::func_0208dbf8()->func_0208e058(file, 0, 0xffff);
    }
    keyboard.func_0c(0);
    func_020a14e0(func_020a18e4(), 0);
    flags |= 1;
}

void Unk0201dd90::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
        func_020897b4("Starting Survival Guide");
    }
}

void Unk0201dd90::func_38(bool active) {
    if (!active) {
        return;
    }
    fade.func_step();
    keyboard.func_00();
    if (keyboard.result != 0) {
        func_18();
        keyboard.result = 0;
        keyboard.func_0204ea00("");
    }
    if (fade.state == 4) {
        func_0201de58();
    }
}

bool Unk0201dd90::func_3c(bool done) {
    if (!func_30()) {
        keyboard.func_04(true);
    } else {
        keyboard.func_04(done);
    }
    return true;
}

bool Unk0201dd90::func_0c(short a) {
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
    func_0201dec4();
    keyboard.result = 0;
    keyboard.func_0204e9d8();
    return false;
}

bool Unk0201dd90::func_10() {
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

void Unk0201dd90::func_18() {
    flags |= 2;
}

bool Unk0201dd90::func_34() {
    return false;
}

bool Unk0201dd90::func_28() {
    return fade.func_shown();
}

bool Unk0201dd90::func_2c() {
    return fade.func_hidden();
}

bool Unk0201dd90::func_14() {
    return (flags & 2) != 0;
}

void Unk0201dd90::func_1c() {
    flags &= ~2;
}

bool Unk0201dd90::func_20() {
    return false;
}

void Unk0201dd90::func_24() {}
