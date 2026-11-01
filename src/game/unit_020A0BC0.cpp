/*
 * Unit 0x020A0BC0-0x020A18F0: the system object Unk020d6240 (static object data_020d6240,
 * 0x4C bytes, with its `__sinit`): input state, screen stack, pie menu, the screen archive,
 * the fonts, a background layer and the brightness fades of the two screens. Screen argument
 * of the fades: 0 = first, 1 = second, 2 = both.
 *
 * Bounds: hypothesis (the static initializer 0x020AE468 calls the constructor 0x020A0BC0; after
 * the screen stack; 0x020A18F0 starts the object of data_020d6298). `.data` is the archive and
 * font paths; `.bss` is the chain node and the object. Layouts come from the code; all names
 * are placeholders. Real file name unknown.
 */
#include "game/unk_archive.h"
#include "game/unk_vector.h"

typedef signed char s8;

class Unk02095140;

class Unk02091810Font {
public:
    virtual ~Unk02091810Font();
    virtual void func_08(Unk0209487c *map, Unk0209487c *font);
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual void func_20();
    virtual void func_24();
    virtual void func_28();
    virtual void func_2c();
    virtual void func_30();
    virtual Unk0209487c *func_34();
    virtual void func_38();
};

class Unk0208e570 : public Unk02091810Font {
public:
    Unk0208e570();

    u8 unk4[0xd4];
};

class Unk0208f16c : public Unk02091810Font {
public:
    Unk0208f16c();

    u8 unk4[0x14];
};

class Unk0201b6d4 {
public:
    Unk0201b6d4();
    ~Unk0201b6d4();
    void func_0201b940(int a);
    void func_0201baa4(int handled, int frame);
    void func_0201bcf8();

    u8 unk0[0x15c];
};

class Unk020a03e0 {
public:
    Unk020a03e0();
    ~Unk020a03e0() {}

    u8 unk0[0x5c];
};

class Unk020a07d8 {
public:
    Unk020a07d8();
    ~Unk020a07d8();

    u8 unk0[0x2c];
};

class Unk020916a4 {
public:
    static Unk020916a4 *func_02091820();
    static Unk020916a4 *func_02091830();
    void func_0209185c(bool a);
    void func_02091eb4(Unk02095140 *file, int a, int b);
};

class Unk0208d304 {
public:
    void func_0208d4b0(int a);
    int func_0208d548();
    void func_0208d7a0(bool a);
};

class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbe8();
    Unk0208d304 *func_0208de60();
    void func_0208df4c(Unk0208d304 *layer);
};

struct Unk020a0bc0Fade {
    Unk020a0bc0Fade() {
        active = 0;
        value = 0;
        max = 0x3c;
        state = 5;
        duration = 0x5a;
    }

    void func_set_max(short m) {
        max = m;
        if (value > max) {
            value = max;
        }
    }

    void func_finish() {
        value = max;
        state = 2;
    }

    bool func_moving() const {
        return state == 0 || state == 3;
    }

    void func_tick() {
        switch (state) {
        case 0:
            value++;
            if (value >= max) {
                value = max;
                state = 1;
            }
            break;
        case 3:
            value--;
            if (value <= 0) {
                value = 0;
                state = 4;
            }
            break;
        case 4:
            state = 5;
            break;
        case 1:
            state = 2;
            break;
        }
    }

    int func_level() const {
        return (func_fxdiv(value << 12, max << 12) * 17) >> 12;
    }

    u8 active;
    u8 unk1[3];
    short value;
    short max;
    int state;
    int duration;
};

class Unk020d6240 {
public:
    Unk020d6240();
    ~Unk020d6240();

    u8 initialized;
    Unk020a03e0 *input;
    Unk020a07d8 *stack;
    int unkc;
    Unk0201b6d4 *menu;
    Unk02093648 *archive;
    Unk02091810Font *fontA;
    Unk02091810Font *fontB;
    Unk0208d304 *layer;
    Unk020a0bc0Fade fade0;
    Unk020a0bc0Fade fade1;
    u8 unk44;
    s8 bright[2];
    s8 mask[2];
    u8 unk49;
};

struct Unk020d60c8;
struct Unk020a0014;

extern "C" {
void G2x_SetBlendBrightness_(volatile u16 *reg, int mask, int bright);
int func_0209f0a4(Unk020d60c8 *settings);
const char *func_020a00a0(Unk020a0014 *texts, int id);
void func_020a04d4(Unk020a03e0 *input);
bool func_020a07f8(Unk020a07d8 *stack, int frame);
bool func_020a0b8c(Unk020a07d8 *stack, void *screen);
void func_020a0f0c(Unk020d6240 *o);
void func_020a10a8();
void func_020a123c(Unk020d6240 *o, int screen, int done);
void func_020a15a8(Unk020d6240 *o, int frame);
void func_020a3e7c(void *p);
void func_020a3eb4(void *p);
extern Unk020d60c8 data_020d60c8;
extern u8 data_020d6cdc[];
}

Unk020d6240 data_020d6240;

Unk020d6240::Unk020d6240()
    : initialized(0), input(0), stack(0), menu(0), archive(0), fontA(0), fontB(0), layer(0),
      unk44(0) {
    bright[0] = 0;
    bright[1] = 0;
    mask[0] = 0;
    mask[1] = 0;
    unk49 = 1;
    fade0.func_set_max(fade0.duration);
    fade0.func_finish();
    fade1.func_set_max(fade1.duration);
    fade1.func_finish();
}

Unk020d6240::~Unk020d6240() {
    func_020a10a8();
    if (initialized) {
        func_020a0f0c(&data_020d6240);
    }
}

extern "C" void func_020a0cd8(Unk020d6240 *o) {
    if (o->initialized) {
        return;
    }
    *(volatile u16 *)0x4000304 &= ~0x8000;
    Unk020916a4::func_02091820()->func_0209185c(true);
    Unk020916a4::func_02091830()->func_0209185c(true);
    o->initialized = 1;
    o->archive = new Unk02093648("ROM_Euro/source/archives/screens.nitro_archive");
    o->archive->func_02094df4();
    o->input = new Unk020a03e0;
    o->stack = new Unk020a07d8;
    func_020a3e7c(data_020d6cdc);
    o->menu = new Unk0201b6d4;
    o->menu->func_0201b940(0);
    if (func_0209f0a4(&data_020d60c8) != 7) {
        o->fontA = new Unk0208e570;
        Unk0209487c *map = o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/dialog.nitro_map");
        o->fontA->func_08(map, o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/dialog.font.nitro_xml"));
        o->archive->func_02093d14((const u32 *)"build/data/screens/fonts/dialog.font.nitro_xml");
        Unk020916a4::func_02091830()->func_02091eb4((Unk02095140 *)map, 0, 0x8000);
        o->fontB = new Unk0208e570;
        map = o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/dialog.nitro_map");
        o->fontB->func_08(map, o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/dialog.font.nitro_xml"));
        o->archive->func_02093d14((const u32 *)"build/data/screens/fonts/dialog.font.nitro_xml");
    } else {
        o->fontA = 0;
        o->fontB = new Unk0208f16c;
        Unk0209487c *map = o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/japanese.nitro_map");
        o->fontB->func_08(map, o->archive->func_02093c18((const u32 *)"build/data/screens/fonts/japanese.font.nitro_xml"));
        o->archive->func_02093d14((const u32 *)"build/data/screens/fonts/japanese.font.nitro_xml");
        Unk020916a4::func_02091830()->func_02091eb4((Unk02095140 *)map, 0, 0x8000);
    }
}

extern "C" void func_020a0f0c(Unk020d6240 *o) {
    if (!o->initialized) {
        return;
    }
    delete o->input;
    o->input = 0;
    delete o->stack;
    o->stack = 0;
    delete o->menu;
    o->menu = 0;
    if (o->fontA != 0) {
        Unk0209487c *file = o->fontA->func_34();
        o->fontA->func_38();
        delete o->fontA;
        o->archive->func_02093c58(o->archive->func_02093f5c(file));
    }
    o->fontA = 0;
    if (o->fontB != 0) {
        Unk0209487c *file = o->fontB->func_34();
        o->fontB->func_38();
        delete o->fontB;
        o->archive->func_02093c58(o->archive->func_02093f5c(file));
    }
    o->fontB = 0;
    delete o->archive;
    o->archive = 0;
    o->initialized = 0;
}

extern "C" void func_020a1070() {
    func_020a10a8();
    data_020d6240.layer = Unk0208db14::func_0208dbe8()->func_0208de60();
    data_020d6240.layer->func_0208d7a0(true);
    data_020d6240.layer->func_0208d4b0(3);
}

extern "C" void func_020a10a8() {
    Unk0208d304 *layer = data_020d6240.layer;
    if (layer != 0) {
        Unk0208db14::func_0208dbe8()->func_0208df4c(layer);
    }
    data_020d6240.layer = 0;
}

extern "C" void func_020a10dc(Unk020d6240 *o, int frame) {
    if (!o->initialized) {
        return;
    }
    func_020a04d4(o->input);
    o->menu->func_0201baa4(func_020a07f8(o->stack, frame), frame);
    if (frame != 0) {
        func_020a3eb4(data_020d6cdc);
        o->menu->func_0201bcf8();
    }
}

extern "C" void func_020a1138(Unk020d6240 *o, int screen, int out) {
    if (screen == 0 || screen == 2) {
        o->fade0.active = out == 0;
    }
    if ((u32)(screen - 1) <= 1) {
        o->fade1.active = out == 0;
    }
    o->fade0.func_finish();
    o->fade1.func_finish();
    if (screen == 0 || screen == 2) {
        o->mask[0] = 0x3f;
        o->bright[0] = out != 0 ? -0x10 : 0x10;
    }
    if ((u32)(screen - 1) <= 1) {
        o->mask[1] = 0x3f;
        o->bright[1] = out != 0 ? -0x10 : 0x10;
    }
    func_020a15a8(o, 1);
}

extern "C" void func_020a11f8(Unk020d6240 *o, int screen, int done) {
    if (screen == 0 || screen == 2) {
        o->fade0.active = 0;
    }
    if ((u32)(screen - 1) <= 1) {
        o->fade1.active = 0;
    }
    func_020a123c(o, screen, done);
}

extern "C" void func_020a122c(Unk020d6240 *o) {
    o->fade0.state = 3;
    o->fade1.state = 3;
}

extern "C" void func_020a123c(Unk020d6240 *o, int screen, int done) {
    if (screen == 0 || screen == 2) {
        if (done != 0) {
            o->fade0.state = 0;
        } else {
            o->fade0.state = 3;
        }
    }
    if ((u32)(screen - 1) <= 1) {
        if (done != 0) {
            o->fade1.state = 0;
        } else {
            o->fade1.state = 3;
        }
    }
}

extern "C" bool func_020a1280(Unk020d6240 *o, int screen, int in) {
    switch (screen) {
    case 0:
        if (in != 0) {
            return o->fade0.state == 2 || o->fade0.state == 1;
        }
        return o->fade0.state == 5 || o->fade0.state == 4;
    case 1:
        if (in != 0) {
            return o->fade1.state == 2 || o->fade1.state == 1;
        }
        return o->fade1.state == 5 || o->fade1.state == 4;
    case 2:
        return func_020a1280(o, 0, in) && func_020a1280(o, 1, in);
    }
    return true;
}

extern "C" bool func_020a1344(Unk020d6240 *o, int screen) {
    switch (screen) {
    case 0:
        return o->fade0.func_moving();
    case 1:
        return o->fade1.func_moving();
    case 2:
        return func_020a1344(o, 0) || func_020a1344(o, 1);
    }
    return true;
}

extern "C" bool func_020a13d4(Unk020d6240 *o, int screen, int in) {
    switch (screen) {
    case 0:
        if (in != 0) {
            return o->fade0.state == 0;
        }
        return o->fade0.state == 3;
    case 1:
        if (in != 0) {
            return o->fade1.state == 0;
        }
        return o->fade1.state == 3;
    case 2:
        return func_020a13d4(o, 0, in) || func_020a13d4(o, 1, in);
    }
    return true;
}

extern "C" void func_020a1494(Unk020d6240 *o, int screen, int max) {
    if (screen == 0 || screen == 2) {
        o->fade0.func_set_max(max);
    }
    if ((u32)(screen - 1) <= 1) {
        o->fade1.func_set_max(max);
    }
}

extern "C" u8 func_020a14d8(Unk020d6240 *o) {
    return o->unk49;
}

extern "C" void func_020a14e0(Unk020d6240 *o, bool on) {
    if (on) {
        *(volatile u16 *)0x4000304 &= ~0x8000;
        o->unk49 = 1;
    } else {
        *(volatile u16 *)0x4000304 |= 0x8000;
        o->unk49 = 0;
    }
}

extern "C" bool func_020a1524(void *screen) {
    return !func_020a0b8c(data_020d6240.stack, screen);
}

extern "C" const char *func_020a154c(int id) {
    return func_020a00a0(((Unk020a0014 **)&data_020d60c8)[0x158 / 4], id);
}

extern "C" void func_020a1568(Unk020d6240 *o, int screen, int mask, int bright) {
    if (screen == 0 || screen == 2) {
        o->mask[0] = mask;
        o->bright[0] = bright;
    }
    if ((u32)(screen - 1) <= 1) {
        o->mask[0] = mask;
        o->bright[0] = bright;
    }
}

extern "C" void func_020a15a8(Unk020d6240 *o, int frame) {
    if (frame == 0) {
        return;
    }
    if (o->mask[0] == 0) {
        o->fade0.func_tick();
        int mask = 0;
        int skip = -1;
        if (o->unk44 != 0 && o->layer != 0) {
            skip = o->layer->func_0208d548();
        }
        for (u32 i = 0; i < 6; i++) {
            if (i != skip) {
                mask |= 1 << i;
            }
        }
        bool moving = true;
        int state = o->fade0.state;
        if (state != 0 && state != 3) {
            moving = false;
        }
        if (moving) {
            int level = o->fade0.func_level();
            o->mask[0] = mask;
            if (level > 0x10) {
                level = 0x10;
            }
            if (o->fade0.active == 0) {
                level = -level;
            }
            o->bright[0] = level;
        } else if (state == 4) {
            o->mask[0] = mask;
            o->bright[0] = 0;
        } else if (state == 1) {
            o->mask[0] = mask;
            o->bright[0] = o->fade0.active != 0 ? 0x10 : -0x10;
        }
    }
    if (o->mask[1] == 0) {
        o->fade1.func_tick();
        bool moving = true;
        int state = o->fade1.state;
        if (state != 0 && state != 3) {
            moving = false;
        }
        if (moving) {
            int level = o->fade1.func_level();
            o->mask[1] = 0x3f;
            if (level > 0x10) {
                level = 0x10;
            }
            if (o->fade1.active == 0) {
                level = -level;
            }
            o->bright[1] = level;
        } else if (state == 4) {
            o->mask[1] = 0x3f;
            o->bright[1] = 0;
        } else if (state == 1) {
            o->mask[1] = 0x3f;
            o->bright[1] = o->fade1.active != 0 ? 0x10 : -0x10;
        }
    }
    if (o->mask[0] > 0) {
        G2x_SetBlendBrightness_((volatile u16 *)0x4000050, o->mask[0], o->bright[0]);
    }
    if (o->mask[1] > 0) {
        G2x_SetBlendBrightness_((volatile u16 *)0x4001050, o->mask[1], o->bright[1]);
    }
    o->mask[0] = 0;
    o->mask[1] = 0;
}

extern "C" Unk020d6240 *func_020a18e4() {
    return &data_020d6240;
}
