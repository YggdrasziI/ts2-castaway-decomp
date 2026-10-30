/*
 * Unit 0x02047A8C-0x0204A9F8: a menu screen (Unk02047a8c, 0x8DC bytes, vtable
 * 0x020B9AA4) built by the game state of unit_02072D94.cpp. It loads a top
 * layout chosen by the language and a bottom layout from the archive, lays
 * out a column of seven buttons (one per language, the current one hidden),
 * and steps between panels by mode (0x254): language list, survival guide
 * (the 0xAC-byte guide object of 0x0201D70C, opened with the slide timer at
 * 0x89C), a list of saved items picked by touching the 3D scene (three keys,
 * texts from the settings' records) and confirmation panels.
 *
 * Bounds: hypothesis. The start is the constructor, after the slots of the
 * class with vtable 0x020B9A44 (0x02047A88); the class's inline virtual
 * functions end the file before unit_0204A9F8.cpp. `.data` holds the four
 * format strings of the text callback, then this class's vtable with its
 * header. Real file name unknown.
 */

#include "game/unk_camera.h"
#include "game/unk_pool.h"
#include "game/unk_screen.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* The touch input. */
class Unk020a0774;

/* An object definition. */
class Unk0205cf00;

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
    void *unk8;
};

/* The saved items of the settings: a count at 0x0C, the mode at 0x60. */
struct Unk020d60c8Items {
    u8 unk0[0xc];
    u32 count;
    u8 unk10[0x50];
    int unk60;
};

/* The settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    void *unk0;
    int unk4;
    u32 flags;
    u8 unkc[0x148];
    Unk020d60c8Items *items;
};

/* A record of the settings (func_0209f8d0). */
struct Unk0209f8d0 {
    int unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    char name[1];
};

/* The credits screen of unit_0201D70C.cpp. */
class Unk0201d70c {
public:
    Unk0201d70c();
    virtual ~Unk0201d70c();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual bool func_14();
    virtual void func_18();

    u8 unk4[0xa8];
};

/* A scene object found under the touch point: its definition at 0x28. */
struct Unk0204a254Item {
    u8 unk0[0x28];
    Unk0205cf00 *def;
};

/* The objects found by func_0205fa30. */
struct Unk0205f098 {
    Unk0204a254Item *head;
    int count;
};

/* A ray from the camera. */
struct Unk0204a254Ray {
    struct Vec {
        Unk02098ff0 v;
    };

    inline void func_set(const Unk02098ff0 &pos, const Unk02098ff0 &dir) {
        this->pos = (const Vec &)pos;
        this->dir = (const Vec &)dir;
    }

    Vec pos;
    Vec dir;
};

/* A language: its top layout, its name text and its palette. */
struct Unk02047a8cLanguage {
    Unk02047a8cLanguage(u32 layout, u16 text, u8 palette) {
        this->layout = layout;
        this->text = text;
        this->palette = palette;
    }

    u32 layout;
    u16 text;
    u8 palette;
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern Unk020c7d38 data_020c7d38;
extern u8 data_020c3fd4[];

void *func_0201ba94();
int *func_02097a4c();

extern "C" {
Unk020d6240 *func_020a18e4();
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
void func_020a11f8(Unk020d6240 *system, int a, int b);
bool func_020a1280(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a075c(Unk020a0774 *input, int index);
Unk02098e70 func_020a07bc(Unk020a0774 *input, int index);
int func_0209f0a4(Unk020d60c8 *settings);
Unk0209f8d0 *func_0209f8d0(Unk020d60c8 *settings, int index);
void *func_020a00a0(void *texts, u32 id);
int func_02082a2c(char *buf, const char *fmt, ...);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a72d0(Unk020a7c90 *s, int value);
int func_020a7c00(Unk020a7c90 *s);
bool func_020a5208(Unk020d60c8Items *items, int index);
bool func_020a5248(Unk020d60c8Items *items, int index);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
void func_0205f098(Unk0205f098 *list);
void func_0205f0a8(Unk0205f098 *list);
void func_0205f10c(Unk0205f098 *list, Unk0204a254Item **out, int count);
void func_0205fa30(void *objects, Unk0204a254Ray ray, Unk0205f098 *out);
bool func_0205d340(Unk0205cf00 *def, u32 key);
}

class Unk02047a8c : public Unk020a07d4 {
public:
    Unk02047a8c(Unk02093648 *archive);
    virtual ~Unk02047a8c();
    virtual void func_08();
    virtual bool func_0c(short);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c() {
        flags &= ~2;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28();
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual bool func_30();
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_020492d8();
    void func_02049418();
    bool func_0204a254(bool done);
    void func_0204a554(int index);
    int func_0204a670();
    int func_0204a880();
    void func_0204a888(int mode);
    bool func_0204a890();
    void func_0204a8f4();

    u32 count;
    Unk020a07d4Timer fade;
    u32 flags;
    Unk020a9d58 bottom;
    Unk020a9d58 top;
    Unk020a7c90 *title;
    Unk02051704 panel110;
    int selected;
    Unk02051704 panel170;
    Unk02050640 *languages;
    Unk02050640 button1d0;
    int mode;
    Unk02050640 button258;
    Unk02050640 button2dc;
    Unk02051704 panel360;
    Unk02051704 panel3bc;
    Unk020a7c90 *frame;
    Unk02050640 button41c;
    Unk02050640 button4a0;
    Unk02050640 button524;
    Unk02051704 panel5a8;
    Unk020a7c90 *message;
    Unk02050640 button608;
    Unk02050640 button68c;
    Unk02050640 button710;
    Unk02050640 button794;
    Unk02050640 button818;
    Unk020a07d4Timer slide;
    Unk0201d70c *guide;
    Unk020a7c90 *image;
    Unk020a7c90 *imageFrame;
    u32 imageAnim;
    char text[0x20];
    int languageY;
    int languageStep;
};

static void *func_0204a754(u32 id, void *user);

static inline Unk020a7c90 *func_get(Unk020a9d58 *layout, int type, Unk020a7af4 *names, u32 hash) {
    return func_020aa040(layout, type, func_020a7b50(names, hash));
}

/*
 * 99.55 %: registers only; the archive and the language index are kept in
 * r5 / r6 instead of r7 / r8, and the button loop counters swap with them.
 */
Unk02047a8c::Unk02047a8c(Unk02093648 *archive)
    : count(0), flags(0), bottom(archive, 1), top(archive, 0), selected(-1), mode(-1), guide(0) {
    count = 7;
    Unk02047a8cLanguage languages[9] = {
        Unk02047a8cLanguage(0x67f4ee43, 0x61f, 7),  Unk02047a8cLanguage(0x82c405b0, 0x620, 1),
        Unk02047a8cLanguage(0x934483b2, 0x621, 2),  Unk02047a8cLanguage(0x75a4fa05, 0x622, 3),
        Unk02047a8cLanguage(0x09a24406, 0x623, 4),  Unk02047a8cLanguage(0x622bd8a4, 0x624, 5),
        Unk02047a8cLanguage(0x2da1ee0e, 0x10f7, 6), Unk02047a8cLanguage(0x62d04ff0, 0x122e, 8),
        Unk02047a8cLanguage(0x704fa789, 0x122f, 9),
    };
    this->languages = new Unk02050640[count];
    int language = func_0209f0a4(&data_020d60c8);
    Unk020a7af4Entry topEntries[10];
    Unk020a7af4Entry bottomEntries[0x50];
    Unk020a7af4 topNames(topEntries, 10);
    Unk020a7af4 bottomNames(bottomEntries, 0x50);
    Unk020a7c90 *s;

    func_020aba38(archive, languages[language].layout, &top, &topNames);
    func_020aba38(archive, 0x71776caa, &bottom, &bottomNames);
    func_020a9db8(&top, func_020a154c, 0);
    func_020a9db8(&bottom, func_0204a754, this);
    image = func_get(&top, 2, &topNames, 0xa66b4084);
    imageAnim = func_020a69a4(image);
    imageFrame = func_get(&top, 4, &topNames, 0x10ebb679);

    panel110.func_02051804(3);
    title = func_get(&bottom, 4, &bottomNames, 0x0fe5b4aa);
    panel110.func_02051858(title);
    s = func_get(&bottom, 0xb, &bottomNames, 0xf0d9e82d);
    panel110.func_02051858(s);
    panel110.func_02051858(func_get(&bottom, 1, &bottomNames, 0x63a458c9));
    panel110.func_18(true);
    panel110.func_24(-s->func_14() - func_020a7cc0(s) - 0x3000, 0);
    panel110.func_34(0xf);

    panel170.func_24(0xc0000, 0);
    panel170.func_020518a8(count);
    int x = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0xe18ac5e6));
    int y = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0xe18ac5e7));
    int step = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0xf9cab171));
    int iconX = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0x2cfb0be0));
    int iconY = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0x2cfb0be1));
    int textX = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0xe9bfe635));
    int textY = func_020a7c00(func_get(&bottom, 0xa, &bottomNames, 0xe9bfe636));
    languageY = y;
    languageStep = step;
    for (int i = 0; i < (int)count; i++) {
        s = func_get(&bottom, 0xb, &bottomNames, 0xe18ac5be + i);
        func_020a7c90(s, x);
        func_020a7cac(s, y);
        this->languages[i].func_02050838(s, false);
        this->languages[i].func_02050c48(0, 3, -1);
        s = func_get(&bottom, 1, &bottomNames, 0x46316624 + i);
        func_020a69ac(s, languages[i].palette);
        func_020a7c90(s, x + iconX);
        func_020a7cac(s, y + iconY);
        this->languages[i].func_020508a4(s);
        this->languages[i].func_02050914(1);
        s = func_get(&bottom, 4, &bottomNames, 0xd4575fc9 + i);
        func_020a716c(s, languages[i].text);
        func_020a7c90(s, x + textX);
        func_020a7cac(s, y + textY);
        this->languages[i].func_02050968(s);
        panel170.func_020518fc(&this->languages[i]);
    }
    func_0204a8f4();
    panel170.func_34(0xf);
    panel170.func_18(false);

    button1d0.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x65e98aee), false);
    button1d0.func_20(0x100000, button1d0.func_10()->x);
    button1d0.func_02050c48(0, 3, -1);
    s = func_get(&bottom, 1, &bottomNames, 0xb8c9a9b8);
    func_020a69ac(s, languages[language].palette);
    button1d0.func_020508a4(s);
    button1d0.func_34(0xf);

    button818.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x108bd540), false);
    button818.func_20(0x100000, button818.func_10()->x);
    button818.func_02050c48(0, 3, -1);
    button818.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x9dee12ed));
    button818.func_34(0xf);

    button258.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x535e8d70), true);
    button258.func_02050c48(0, 4, 4);
    button258.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x8e77ce04));
    button258.func_02050914(1);
    button258.func_02050968(func_get(&bottom, 4, &bottomNames, 0x034bf9e5));

    button2dc.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x2ff749d1), true);
    button2dc.func_02050c48(0, 4, 4);
    button2dc.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x5e51c549));
    button2dc.func_02050914(1);
    button2dc.func_02050968(func_get(&bottom, 4, &bottomNames, 0x6fea248b));

    s = func_get(&bottom, 0xb, &bottomNames, 0xfbbf3f4e);
    panel360.func_14(func_020a7ca4(s), func_020a7cc0(s));
    panel360.func_24(0xc0000, func_020a7cc0(s));
    panel360.func_02051804(3);
    panel360.func_020518a8(2);
    panel360.func_02051858(s);
    panel360.func_02051858(func_get(&bottom, 0xb, &bottomNames, 0x8d62e29e));
    panel360.func_02051858(func_get(&bottom, 4, &bottomNames, 0x80d07cce));
    panel360.func_020518fc(&button258);
    panel360.func_020518fc(&button2dc);
    panel360.func_34(0xf);

    button41c.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x58c384a2), true);
    button41c.func_02050c48(0, 1, -1);
    button41c.func_02050ad0(0x02692fdb);
    button4a0.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x21ab9ba6), true);
    button4a0.func_02050c48(2, 3, -1);
    button524.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x47d08ff5), true);
    button524.func_02050c48(4, 5, -1);
    frame = func_get(&bottom, 0xb, &bottomNames, 0x5d9537a6);
    panel3bc.func_02051804(0xf);
    panel3bc.func_020518a8(3);
    panel3bc.func_020518fc(&button41c);
    panel3bc.func_020518fc(&button4a0);
    panel3bc.func_020518fc(&button524);
    panel3bc.func_02051858(func_get(&bottom, 1, &bottomNames, 0x4af0009d));
    panel3bc.func_02051858(func_get(&bottom, 1, &bottomNames, 0xc0800c1b));
    panel3bc.func_02051858(func_get(&bottom, 4, &bottomNames, 0x3ff0ee81));
    panel3bc.func_02051858(func_get(&bottom, 4, &bottomNames, 0x3b2542ec));
    panel3bc.func_02051858(func_get(&bottom, 4, &bottomNames, 0xdc920b28));
    panel3bc.func_02051858(func_get(&bottom, 4, &bottomNames, 0x81cdf1fb));
    for (int i = 0; i < 4; i++) {
        panel3bc.func_02051858(func_get(&bottom, 0xb, &bottomNames, 0x5d9537a6 + i));
    }
    for (int i = 0; i < 5; i++) {
        panel3bc.func_02051858(func_get(&bottom, 4, &bottomNames, 0xab4d9c63 + i));
    }

    button608.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0x14990c0b), true);
    button608.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x512265ac));
    button608.func_02050914(1);
    button608.func_02050968(func_get(&bottom, 4, &bottomNames, 0x1420eff5));
    button608.func_02050c48(0, 1, -1);
    button608.func_02050c64(0, 1, 2);

    button68c.func_02050838(func_get(&bottom, 0xb, &bottomNames, 0xd4674b2a), true);
    button68c.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x905700b4));
    button68c.func_02050914(1);
    button68c.func_02050968(func_get(&bottom, 4, &bottomNames, 0xd3ef2f14));
    button68c.func_02050c48(0, 1, -1);
    button68c.func_02050c64(0, 1, 2);

    s = func_get(&bottom, 0xb, &bottomNames, 0xf961d5fc);
    panel5a8.func_14(0, func_020a7cc0(s));
    panel5a8.func_24(0xc0000, func_020a7cc0(s));
    panel5a8.func_02051804(2);
    panel5a8.func_020518a8(3);
    message = func_get(&bottom, 4, &bottomNames, 0x56e7630e);
    panel5a8.func_02051858(message);
    panel5a8.func_02051858(s);
    panel5a8.func_020518fc(&button608);
    panel5a8.func_020518fc(&button68c);
    panel5a8.func_34(0xf);

    s = func_get(&bottom, 0xb, &bottomNames, 0xc2f94842);
    button710.func_14(func_020a7ca4(s), func_020a7cc0(s));
    button710.func_24(func_020a7cc0(s) - s->func_14() - 0x3000, func_020a7cc0(s));
    button710.func_02050838(s, true);
    button710.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x060bbd76));
    button710.func_02050c48(1, -1, -1);
    button710.func_02050c64(6, 7, -1);
    button710.func_34(0xf);

    s = func_get(&bottom, 0xb, &bottomNames, 0x502f60ce);
    button794.func_14(func_020a7ca4(s), func_020a7cc0(s));
    button794.func_24(func_020a7cc0(s) - s->func_14() - 0x3000, func_020a7cc0(s));
    button794.func_02050838(s, true);
    button794.func_020508a4(func_get(&bottom, 1, &bottomNames, 0x37aada25));
    button794.func_02050c48(1, -1, -1);
    button794.func_02050c64(6, 7, -1);
    button794.func_34(0xf);
}

Unk02047a8c::~Unk02047a8c() {
    func_02049418();
    delete[] languages;
}

void Unk02047a8c::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

bool Unk02047a8c::func_0c(short) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_020492d8();
    fade.func_duration(0x14);
    fade.timer = 0;
    fade.state = 0;
    func_020a1494(func_020a18e4(), 2, 0x14);
    func_020a122c(func_020a18e4());
    return false;
}

bool Unk02047a8c::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x14);
    fade.timer = fade.duration;
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x14);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

bool Unk02047a8c::func_30() {
    bool ready = false;
    bool shown = false;
    bool idle = false;
    if (func_28() && !func_14() && !panel360.func_50() && !panel170.func_50() && !panel5a8.func_50()) {
        if (!slide.func_moving()) {
            idle = true;
        }
    }
    if (idle) {
        if (!button818.func_50()) {
            shown = true;
        }
    }
    if (shown) {
        if (func_020a1280(func_020a18e4(), 2, 0)) {
            ready = true;
        }
    }
    return ready;
}

bool Unk02047a8c::func_14() {
    return (flags & 2) != 0;
}

bool Unk02047a8c::func_28() {
    return fade.func_shown();
}

void Unk02047a8c::func_020492d8() {
    func_02049418();
    slide.func_duration(0x10);
    slide.timer = 0;
    slide.state = 5;
    if (data_020d60c8.flags & 2) {
        panel360.func_18(true);
        panel360.func_30(0xf);
        button1d0.func_30(0xf);
    } else {
        panel170.func_18(true);
        func_0204a8f4();
        panel170.func_30(0xf);
        button794.func_30(0xf);
        button818.func_30(0xf);
    }
    bool none = !func_0204a890();
    if (none) {
        button2dc.flags |= 8;
    } else {
        button2dc.flags &= ~8;
    }
    func_020aa06c(&top, true);
    func_020aa06c(&bottom, true);
    flags |= 1;
}

void Unk02047a8c::func_02049418() {
    if (!(flags & 1)) {
        return;
    }
    if (guide != 0) {
        delete guide;
        guide = 0;
    }
    func_020aa06c(&top, false);
    func_020aa06c(&bottom, false);
    flags &= ~1;
}

void Unk02047a8c::func_38(bool active) {
    if (fade.func_hidden() | !active) {
        return;
    }
    fade.func_step();
    slide.func_step();
    panel360.func_08();
    panel170.func_08();
    panel110.func_08();
    button1d0.func_08();
    panel3bc.func_08();
    panel5a8.func_08();
    button818.func_08();
    button710.func_08();
    button794.func_08();
    if (slide.func_opened()) {
        func_020a7cf0(imageFrame, false);
        guide = new Unk0201d70c;
        guide->func_08();
        func_020a1494(func_020a18e4(), 1, 0x10);
        func_020a122c(func_020a18e4());
        func_020a6980(image, 0xd6b07342);
    } else if (guide != 0 && fade.func_shown()) {
        if (slide.func_shown() && guide->func_14()) {
            slide.state = 3;
            func_020a1494(func_020a18e4(), 1, 0x10);
            func_020a11f8(func_020a18e4(), 1, 1);
        }
        if (!func_020a0b8c(data_020d6240.unk8, guide)) {
            func_020a7cf0(imageFrame, true);
            delete guide;
            guide = 0;
            func_020a1494(func_020a18e4(), 1, 0x10);
            func_020a122c(func_020a18e4());
            func_020a6980(image, imageAnim);
            if (mode == 2 && panel170.func_38()) {
                button818.func_28(0xf);
            }
        }
    }
    if (panel360.func_44()) {
        panel360.func_18(false);
    }
    if (panel170.func_44()) {
        panel170.func_18(false);
    }
    if (panel5a8.func_44()) {
        panel5a8.func_18(false);
    }
    if (panel360.func_44() && mode == 2) {
        panel170.func_18(true);
        func_0204a8f4();
        panel170.func_28(0xf);
        button794.func_28(0xf);
        button818.func_28(0xf);
    } else if (panel170.func_44()) {
        panel360.func_18(true);
        panel360.func_28(0xf);
        button1d0.func_28(0xf);
    } else if (panel5a8.func_44() && (mode == 5 || mode == 8)) {
        mode = 3;
    } else if (panel5a8.func_44() && mode == 1) {
        func_020a716c(title, 0xf2e);
        panel110.func_28(0xf);
        button710.func_28(0xf);
    } else if (panel110.func_40() && mode == 6) {
        mode = 4;
    } else if (panel110.func_44() && mode == 7) {
        panel110.func_28(0xf);
        panel5a8.func_18(true);
        button608.func_18(false);
        button68c.func_18(false);
        panel5a8.func_28(0xf);
        func_020a716c(title, 0xe18);
        func_020a716c(message, 0x1074);
        func_020a72d0(message, 0);
    } else if (panel110.func_44() && mode == 8) {
        panel110.func_28(0xf);
        panel5a8.func_18(true);
        panel5a8.func_28(0xf);
        func_020a716c(title, 0x1072);
        func_020a716c(message, 0x990);
        func_020a72d0(message, -1);
    }
    if (mode == 9) {
        selected = -1;
        func_020a716c(title, 0xf2e);
        panel110.func_28(0xf);
        button710.func_28(0xf);
        mode = 1;
    } else if (mode == 10) {
        func_020a716c(title, 0x1013);
        panel110.func_28(0xf);
        func_020a716c(message, 0x1073);
        func_020a72d0(message, 0);
        panel5a8.func_18(true);
        button608.func_18(false);
        button68c.func_18(false);
        panel5a8.func_28(0xf);
        mode = 5;
    } else if (mode == 11) {
        panel110.func_2c(0xf);
        if (data_020d60c8.items->unk60 == 4) {
            mode = 8;
        } else {
            mode = 7;
        }
    }
    func_020aa158(&top);
    func_020aa158(&bottom);
    if (fade.state == 4) {
        func_02049418();
    }
}

void Unk02047a8c::func_18() {
    flags |= 2;
}

bool Unk02047a8c::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button258.func_0c(done);
    if (button258.touch.flags & 8) {
        mode = 0;
        func_18();
    }
    done = button2dc.func_0c(done);
    if (button2dc.touch.flags & 8) {
        button1d0.func_2c(0xf);
        panel360.func_2c(0xf);
        func_020a716c(title, 0xf2e);
        panel110.func_28(0xf);
        button710.func_28(0xf);
        mode = 1;
    }
    done = button1d0.func_0c(done);
    if (button1d0.touch.flags & 8) {
        panel360.func_2c(0xf);
        button1d0.func_2c(0xf);
        mode = 2;
    }
    for (u32 i = 0; i < count; i++) {
        done = languages[i].func_0c(done);
    }
    done = button710.func_0c(button794.func_0c(done));
    if (button710.touch.flags & 8) {
        panel110.func_2c(0xf);
        button710.func_2c(0xf);
        panel3bc.func_18(false);
        bool none = !func_0204a890();
        if (none) {
            button2dc.flags |= 8;
        } else {
            button2dc.flags &= ~8;
        }
        panel360.func_18(true);
        panel360.func_28(0xf);
        button1d0.func_28(0xf);
        selected = -1;
        mode = -1;
    }
    done = button41c.func_0c(done);
    if (button41c.touch.flags & 8) {
        selected = -1;
        panel3bc.func_18(false);
        func_020a716c(title, 0xf2e);
        panel110.func_28(0xf);
    }
    done = button4a0.func_0c(done);
    if (button4a0.touch.flags & 8) {
        panel3bc.func_18(false);
        func_020a716c(message, 0x689);
        func_020a72d0(message, -1);
        panel5a8.func_18(true);
        panel5a8.func_28(0xf);
        button710.func_2c(0xf);
        mode = 5;
    }
    done = button524.func_0c(done);
    if (button524.touch.flags & 8) {
        panel3bc.func_18(false);
        button710.func_2c(0xf);
        func_020a716c(title, 0xe16);
        panel110.func_28(0xf);
        mode = 6;
    }
    done = button608.func_0c(done);
    if (button608.touch.flags & 8) {
        panel5a8.func_2c(0xf);
        panel110.func_2c(0xf);
    }
    done = button68c.func_0c(done);
    if (button68c.touch.flags & 8) {
        panel5a8.func_2c(0xf);
        panel110.func_2c(0xf);
        selected = -1;
        mode = 1;
    }
    done = button818.func_0c(done);
    if ((button818.touch.flags & 8) && slide.func_hidden()) {
        button818.func_2c(0xf);
        slide.state = 0;
        func_020a1494(func_020a18e4(), 1, 0x10);
        func_020a11f8(func_020a18e4(), 1, 1);
    }
    return func_0204a254(done);
}

bool Unk02047a8c::func_0204a254(bool done) {
    if (done || mode != 1) {
        return done;
    }
    Unk020a0774 *input = data_020d6240.input;
    if (func_020a075c(input, 1)) {
        Unk0204a254Ray ray;
        int *screen = func_02097a4c();
        Unk020899a4 *camera = (Unk020899a4 *)&data_020c7d38.unk54;
        Unk02098e70 pt = func_020a07bc(input, 1);
        if (selected != -1) {
            Unk02098bc8 rect(func_020a7ca4(frame), func_020a7cc0(frame), frame->func_10(), frame->func_14());
            if (!rect.func_02098bf4(pt.x, pt.y)) {
                selected = -1;
                panel3bc.func_18(false);
                panel110.func_28(0xf);
            }
            return true;
        }
        Unk02098ff0 dir = camera->func_02089cac(screen[0] << 12, screen[1] << 12);
        dir.func_02099048(0xa000);
        ray.func_set(camera->pos, dir);
        Unk0205f098 list;
        func_0205f098(&list);
        func_0205fa30(data_020c3fd4, ray, &list);
        if (list.count != 0) {
            Unk0204a254Item *items[6];
            int found = -1;
            func_0205f10c(&list, items, list.count);
            for (int i = 0; found == -1 && i < list.count; i++) {
                if (func_0205d340(items[i]->def, 0xa3ad0e06)) {
                    found = 0;
                } else if (func_0205d340(items[i]->def, 0xa3ad0e06 + 1)) {
                    found = 1;
                } else if (func_0205d340(items[i]->def, 0xa3ad0e06 + 2)) {
                    found = 2;
                }
            }
            if (found == -1) {
                func_0205f0a8(&list);
                return done;
            }
            Unk020d60c8Items *saved = data_020d60c8.items;
            if (found != selected && func_020a5208(saved, found) && func_020a5248(saved, found)) {
                selected = found;
                done = true;
                func_0204a554(found);
                panel3bc.func_18(done);
                panel110.func_2c(0xf);
                func_020a2ce8(func_020a2994(), 0x626f047c, 0x7f, 0);
            }
        }
        func_0205f0a8(&list);
    }
    return done;
}

void Unk02047a8c::func_0204a554(int index) {
    panel3bc.func_18(false);
    panel3bc.func_18(true);
    panel3bc.func_14(FX32(index * 0x1c), panel3bc.func_10()->y);
    func_020a69ac(panel3bc.func_02051ad0(0), index);
    func_020a7c90(panel3bc.func_02051ad0(1), FX32(index * 0x60 + 0x1c));
}

int Unk02047a8c::func_0204a670() {
    int result = -1;
    if (button794.touch.flags & 8) {
        result = func_0209f0a4(&data_020d60c8);
    }
    for (u32 i = 0; i < count && result < 0; i++) {
        if (languages[i].touch.flags & 8) {
            result = i;
        }
    }
    if (result >= 0) {
        if (guide != 0) {
            guide->func_18();
        }
        mode = -1;
        panel170.func_2c(0xf);
        button794.func_2c(0xf);
        button818.func_2c(0xf);
        return result;
    }
    return -1;
}

static void *func_0204a754(u32 id, void *user) {
    Unk02047a8c *self = (Unk02047a8c *)user;
    switch (id) {
    case 0x800001:
        return func_0209f8d0(&data_020d60c8, self->selected)->name;
    case 0x800002: {
        u8 minutes = func_0209f8d0(&data_020d60c8, self->selected)->unk6;
        if (minutes < 10) {
            func_02082a2c(self->text, "%d:0%d", func_0209f8d0(&data_020d60c8, self->selected)->unk4, minutes);
        } else {
            func_02082a2c(self->text, "%d:%d", func_0209f8d0(&data_020d60c8, self->selected)->unk4, minutes);
        }
        return self->text;
    }
    case 0x800003:
        func_02082a2c(self->text, "%d", func_0209f8d0(&data_020d60c8, self->selected)->unk0);
        return self->text;
    case 0x800004:
        func_02082a2c(self->text, "%d%", func_0209f8d0(&data_020d60c8, self->selected)->unk7);
        return self->text;
    default:
        return func_020a00a0(func_0201ba94(), id);
    }
}

int Unk02047a8c::func_0204a880() {
    return mode;
}

void Unk02047a8c::func_0204a888(int mode) {
    this->mode = mode;
}

bool Unk02047a8c::func_0204a890() {
    u32 i;
    Unk020d60c8Items *saved = data_020d60c8.items;
    for (i = 0; i < saved->count; i++) {
        if (func_020a5208(saved, i) && func_020a5248(saved, i)) {
            return true;
        }
    }
    return false;
}

void Unk02047a8c::func_0204a8f4() {
    int language = func_0209f0a4(&data_020d60c8);
    int y = languageY + panel170.func_10()->y;
    for (int i = 0; i < (int)count; i++) {
        if (language == i) {
            languages[i].func_18(false);
        } else {
            languages[i].func_18(true);
            languages[i].func_14(languages[i].func_10()->x, y);
            y += languageStep;
        }
    }
}
