/*
 * Unit 0x02041B10-0x02043FBC: the outfit screen (Unk02041b10, 0x35B4 bytes,
 * vtable 0x020B9774) on the screens' root Unk020a07d4, built by the game state
 * of unit_02071D94.cpp. Six part tabs choose the part of the outfit, six item
 * buttons the item (filled from the catalog Unk020724cc), a slider the colour
 * (part 1); two buttons switch between the player's two outfits, which the
 * screen keeps and applies to the player. A name button opens the keyboard
 * (Unk0204d698) to rename the player; a done button closes the screen.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * the class with vtable 0x020B9728 (0x02041AF8); this class's inline slots end
 * the file before the pages' owner (unit_02043FBC.cpp). `.data` is this
 * class's vtable with its header. Real file name unknown.
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* The player (data_020c43a8): only the fields used here. */
class Unk020c43a8 {
public:
    int unk0[3];
    void *sim;
    u8 unk10[0x158];
    char name[1];
};

/* The set of items seen (data_020d60c8.collection): only the field used here. */
class Unk0206b630 {
public:
    bool func_0206b630(int value);

    u8 unk0[0x1400];
    int unk1400;
};

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

/* An object definition. */
struct Unk0205cf00;

/* An inventory entry. */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
};

/* The object definition database. */
struct Unk020c3fc4;

/* The random generator. */
struct Unk020a20f0;

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
    void func_0204e9f4();
    void func_0204ea00(const char *text);

    u8 unk4[0x74];
    int result;
    u8 unk7c[0x28fc];
    char text[0x40];
    int length;
    int maxLength;
    int lastKey;
    bool screen;
};

/* The slider widget of unit_02051DA0.cpp. */
class Unk02051da0 : public Unk020b9e88 {
public:
    Unk02051da0();
    ~Unk02051da0();
    void func_02051ec4(Unk020a7c90 *track, Unk020a7c90 *knob, int padX, int padY, bool horizontal, bool flag);
    void func_08();
    bool func_0c(bool done);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);
    int func_020521a8();
    void func_020527a0(int v);

    inline void func_range(int min, int max, int offset) {
        this->min = min;
        this->max = max;
        this->offset = offset;
    }

    u16 flags;
    Unk020b9e88Touch touch;
    int value;
    int min;
    int max;
    int offset;
    Unk02098e70 last;
    int deadZone;
    Unk02098bc8 bounds;
    Unk02098bc8 range;
    Unk02098bc8 hit;
    Unk020a7c90 *track;
    Unk020a7c90 *knob;
};

extern Unk020c43a8 data_020c43a8;
extern Unk020d60c8 data_020d60c8;
extern Unk020d6240 data_020d6240;
extern Unk020a20f0 data_020d62a4;
extern Unk020c3fc4 data_020c3fc4;
extern u8 data_020bfc9c[];

extern "C" {
Unk020081dc func_020081dc(Unk020c43a8 *p);
void func_020670fc(Unk020c43a8 *p, Unk020081dc *outfit);
void func_0206702c(Unk020c43a8 *p);
void func_020664a0(Unk020c43a8 *p, const char *name);
bool func_02066748(Unk020c43a8 *p, int anim, bool loop, int time, bool hide, int angle);
bool func_020691c4(void *sim);
Unk020d6240 *func_020a18e4();
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
void func_020a11f8(Unk020d6240 *system, int a, int b);
bool func_020a1280(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a0744(void *input, int index);
u32 func_020a1f84(Unk020a20f0 *random);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_0209a474(const char *a, const char *b);
void func_02054b30(void *p);
void func_02054ab4(void *p);
int func_02054c1c(void *p, Unk0205cf00 *def, int a);
Unk02054dc4 *func_02054dc4(void *p, Unk0205cf00 *def, int a);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_0203c254(int value, int index, int a);
}

class Unk02041b10 : public Unk020a07d4 {
public:
    Unk02041b10(Unk02093648 *archive, Unk020c43a8 *player, Unk020724cc *catalog);
    virtual ~Unk02041b10();
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual void func_1c() {
        flags &= ~2;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28();
    virtual bool func_30();

    void func_02042c28();
    void func_02042d2c();
    void func_02043978(int mode);
    int func_020439dc(int part);
    void func_02043a38();
    void func_02043b74();
    void func_02043b94();
    void func_02043f0c();

    Unk020a07d4Timer fade;
    u32 flags;
    Unk020a9d58 layout;
    Unk0204d698 keyboard;
    Unk020c43a8 *player;
    Unk020724cc *catalog;
    signed char part;
    signed char item;
    signed char color;
    int outfit;
    Unk020081dc outfits[2];
    Unk02050640 tabs[6];
    Unk02050640 outfit0;
    Unk02050640 outfit1;
    Unk02050640 name;
    Unk02050640 done;
    Unk02051704 panelTabs;
    Unk02051704 panelItems;
    Unk02050640 items[6];
    Unk02051da0 slider;
    Unk020a7c90 *colorSprite;
    Unk020a7c90 *cursor;
    Unk02051704 panelConfirm;
    Unk02050640 yes;
    Unk02050640 no;
    int mode;
};

/*
 * 98.34 %: the icon positions of the two outfit buttons swap which add goes
 * through a move (the original moves r0 into r1 before the 0x8000 add of x and
 * adds 0x4000 to y directly; here the reverse; an inline helper for both calls
 * gave the same code); one u16 index truncation goes through the other
 * register.
 */
Unk02041b10::Unk02041b10(Unk02093648 *archive, Unk020c43a8 *player, Unk020724cc *catalog)
    : flags(0), layout(archive, 0), player(player), catalog(catalog), part(4), item(0), color(0), outfit(3),
      mode(0) {
    outfit = func_020a1f84(&data_020d62a4) & 1;
    Unk020a7af4Entry entries[0x46];
    Unk020a7af4 names(entries, 0x46);

    func_020aba38(archive, 0x743a4e2a, &layout, &names);
    func_020a9db8(&layout, func_020a154c, 0);
    keyboard.maxLength = 15;
    { u32 i_ = func_020a7b50(&names, 0x57cd1f42); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); done.func_02050838(s_, false); }
    done.func_02050c48(0, 1, -1);
    done.func_24(0xc1000, done.func_10()->y);
    { u32 i_ = func_020a7b50(&names, 0xbb88ca9b); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); name.func_02050838(s_, false); }
    name.func_02050c48(0, 1, -1);
    name.func_24(0xc1000, name.func_10()->y);

    u32 i_s = func_020a7b50(&names, 0x7b86638c); Unk020a7c90 *s = func_020aa040(&layout, 0xb, i_s);
    outfit0.func_02050838(s, false);
    outfit0.func_02050c48(1, 1, -1);
    outfit0.func_02050a64(true, true);
    outfit0.func_02050c80(0, 0);
    u32 i_icon = func_020a7b50(&names, 0x28d57b1f); Unk020a7c90 *icon = func_020aa040(&layout, 1, i_icon);
    func_020a7c90(icon, func_020a7ca4(s) + 0x8000);
    func_020a7cac(icon, func_020a7cc0(s) + 0x4000);
    outfit0.func_020508a4(icon);
    outfit0.func_02050c64(2, 3, -1);
    outfit0.func_02050c94(3, 3);

    { u32 i_ = func_020a7b50(&names, 0x29e2667b); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); s = s_; }
    outfit1.func_02050838(s, false);
    outfit1.func_02050c48(1, 1, -1);
    outfit1.func_02050a64(true, true);
    outfit1.func_02050c80(0, 0);
    { u32 i_ = func_020a7b50(&names, 0xcd60d809); Unk020a7c90 *s_ = func_020aa040(&layout, 1, i_); icon = s_; }
    func_020a7c90(icon, func_020a7ca4(s) + 0x8000);
    func_020a7cac(icon, func_020a7cc0(s) + 0x4000);
    outfit1.func_020508a4(icon);
    outfit1.func_02050c64(0, 1, -1);
    outfit1.func_02050c94(1, 1);

    panelTabs.func_14(0, 0);
    panelTabs.func_20(-0x8a000, 0);
    panelTabs.func_02051804(1);
    panelTabs.func_020518a8(8);
    { u32 i_ = func_020a7b50(&names, 0x24443f74); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); panelTabs.func_02051858(s_); }
    panelTabs.func_020518fc(&outfit0);
    panelTabs.func_020518fc(&outfit1);
    for (int i = 0; i < 6; i++) {
        int x = FX32((i % 2) * 38 + 7);
        int y = FX32((i / 2) * 38 + 25);
        { u32 i_ = func_020a7b50(&names, 0x30abe9f2 + i); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); tabs[i].func_02050838(s_, false); }
        tabs[i].func_02050c48(0, 1, -1);
        tabs[i].func_02050a64(true, true);
        tabs[i].func_02050c80(2, 3);
        tabs[i].func_14(x, y);
        u32 i_icon = func_020a7b50(&names, 0xe69db0da + i); Unk020a7c90 *icon = func_020aa040(&layout, 1, i_icon);
        func_020a7c90(icon, x);
        func_020a7cac(icon, y);
        tabs[i].func_020508a4(icon);
        panelTabs.func_020518fc(&tabs[i]);
    }

    { u32 i_ = func_020a7b50(&names, 0xc18d4c99); Unk020a7c90 *s_ = func_020aa040(&layout, 2, i_); s = s_; }
    panelItems.func_14(func_020a7ca4(s), 0);
    panelItems.func_20(0, func_020a7ca4(s));
    panelItems.func_02051804(3);
    panelItems.func_020518a8(7);
    panelItems.func_02051858(s);
    { u32 i_ = func_020a7b50(&names, 0x869f32b9); Unk020a7c90 *s_ = func_020aa040(&layout, 1, i_); cursor = s_; }
    panelItems.func_02051858(cursor);
    for (int i = 0; i < 6; i++) {
        int x = FX32((i % 2) * 38 + 0xb0);
        int y = FX32((i / 2) * 38 + 25);
        { u32 i_ = func_020a7b50(&names, 0x94f941aa + i); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); items[i].func_02050838(s_, false); }
        items[i].func_02050a64(true, true);
        items[i].func_14(x, y);
        items[i].func_02050bf0(i + 9, -1, -1, -1, -1, -1);
        panelItems.func_020518fc(&items[i]);
    }
    { u32 i_ = func_020a7b50(&names, 0xdb82455d); Unk020a7c90 *s_ = func_020aa040(&layout, 1, i_); colorSprite = s_; }
    panelItems.func_02051858(colorSprite);
    u32 i_track = func_020a7b50(&names, 0xa2ea5a79); Unk020a7c90 *track = func_020aa040(&layout, 0xb, i_track);
    slider.func_02051ec4(func_020aa040(&layout, 0xb, func_020a7b50(&names, 0xb40bef04)), track, -0x3000, 0x2000,
                         false, false);
    slider.func_range(0, FX32(this->catalog->func_020726bc(5) - 1), -0x3000);
    panelItems.func_020518fc(&slider);
    for (int i = 0; i < 2; i++) {
        this->catalog->func_02072a78(i, &outfits[i]);
    }
    func_020670fc(&data_020c43a8, &outfits[outfit]);

    { u32 i_ = func_020a7b50(&names, 0xbad53d0c); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); yes.func_02050838(s_, false); }
    yes.func_02050c48(0, 1, -1);
    yes.func_02050914(1);
    { u32 i_ = func_020a7b50(&names, 0x1420eff5); Unk020a7c90 *s_ = func_020aa040(&layout, 4, i_); yes.func_02050968(s_); }
    { u32 i_ = func_020a7b50(&names, 0xfa09d814); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); no.func_02050838(s_, false); }
    no.func_02050c48(0, 1, -1);
    no.func_02050914(1);
    { u32 i_ = func_020a7b50(&names, 0xd3ef2f14); Unk020a7c90 *s_ = func_020aa040(&layout, 4, i_); no.func_02050968(s_); }
    { u32 i_ = func_020a7b50(&names, 0xf961d5fc); Unk020a7c90 *s_ = func_020aa040(&layout, 0xb, i_); s = s_; }
    panelConfirm.func_14(0, func_020a7cc0(s));
    panelConfirm.func_24(0xc1000, func_020a7cc0(s));
    panelConfirm.func_02051804(2);
    panelConfirm.func_020518a8(2);
    panelConfirm.func_02051858(s);
    { u32 i_ = func_020a7b50(&names, 0x15945575); Unk020a7c90 *s_ = func_020aa040(&layout, 4, i_); panelConfirm.func_02051858(s_); }
    panelConfirm.func_020518fc(&yes);
    panelConfirm.func_020518fc(&no);
    panelConfirm.func_34(0x11);
    panelConfirm.func_18(true);
}

Unk02041b10::~Unk02041b10() {
    func_02042d2c();
}

void Unk02041b10::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

bool Unk02041b10::func_30() {
    return func_28() && !func_14() && func_020a1280(func_020a18e4(), 0, 0) && !(flags & 4) &&
           !panelConfirm.func_50();
}

bool Unk02041b10::func_14() {
    return (flags & 2) != 0;
}

bool Unk02041b10::func_28() {
    return fade.func_shown();
}

bool Unk02041b10::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_02042c28();
    fade.func_duration(0x11);
    fade.timer = 0;
    fade.state = 0;
    flags |= 0x200;
    return false;
}

bool Unk02041b10::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x11);
    fade.timer = fade.duration;
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x11);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

void Unk02041b10::func_02042c28() {
    if (flags & 1) {
        return;
    }
    bool first;
    {
        Unk020081dc o = func_020081dc(&data_020c43a8);
        first = o.unk28 == 0;
    }
    if (first) {
        outfit0.func_02050aac(true);
    } else {
        outfit1.func_02050aac(true);
    }
    func_02043f0c();
    func_02043b94();
    tabs[part].func_02050aac(true);
    panelTabs.func_30(0x11);
    panelItems.func_30(0x11);
    func_020aa06c(&layout, true);
    keyboard.func_0c(0);
    keyboard.result = 0;
    flags |= 1;
}

void Unk02041b10::func_02042d2c() {
    if (!(flags & 1)) {
        return;
    }
    func_02054b30(data_020bfc9c);
    func_02054ab4(data_020bfc9c);
    data_020d60c8.collection->unk1400 = 0;
    Unk020081dc o = func_020081dc(player);
    Unk0206b630 *collection = data_020d60c8.collection;
    for (int i = 0; i < 2; i++) {
        collection->func_0206b630(o.parts.v[i]);
    }
    catalog->func_02072ba0();
    o = func_020081dc(player);
    u8 *inventory = data_020bfc9c;
    Unk020c3fc4 *db = &data_020c3fc4;
    if (o.parts.v[0] != 0 && o.colors.v[0] != -1) {
        Unk0205cf00 *def = func_0205f6f8(db, o.parts.v[0]);
        func_02054c1c(inventory, def, 0xff);
        int count = o.colors.v[0] + 1;
        func_02054dc4(inventory, def, 0)->count = count;
    }
    if (o.parts.v[1] != 0 && o.colors.v[1] != -1) {
        Unk0205cf00 *def = func_0205f6f8(db, o.parts.v[1]);
        func_02054c1c(inventory, def, 0xff);
        int count = o.colors.v[1] + 1;
        func_02054dc4(inventory, def, 0)->count = count;
    }
    func_020aa06c(&layout, false);
    keyboard.func_08();
    flags &= ~1;
}

void Unk02041b10::func_38(bool active) {
    if (fade.func_hidden()) {
        return;
    }
    if (!active) {
        return;
    }
    fade.func_step();
    if ((flags & 0x100) && func_020691c4(data_020c43a8.sim)) {
        func_02043b74();
    }
    if (mode == 1 && keyboard.result != 0) {
        if (keyboard.result == 1 && !func_0209a474(player->name, keyboard.text)) {
            func_020664a0(player, keyboard.text);
            flags |= 0x80;
        }
        keyboard.result = 0;
        func_02043978(0);
    }
    if ((flags & 0x40) && func_020a1280(func_020a18e4(), 0, 1)) {
        catalog->func_020727e8(5, color);
        func_020a11f8(func_020a18e4(), 0, 0);
        flags &= ~0x40;
    }
    if ((flags & 8) && func_020a1280(func_020a18e4(), 0, 1)) {
        catalog->func_020727e8(func_020439dc(part), item);
        func_020a11f8(func_020a18e4(), 0, 0);
        flags &= ~8;
    }
    if ((flags & 0x10) && panelItems.func_44()) {
        items[item].func_02050aac(false);
        func_02043b94();
        panelItems.func_28(0x11);
        flags &= ~0x10;
    }
    if ((flags & 0x20) && panelTabs.func_44()) {
        func_020670fc(player, &outfits[outfit]);
        if (!(flags & 0x80)) {
            func_0206702c(player);
            keyboard.func_0204ea00(player->name);
        }
        items[item].func_02050aac(false);
        func_02043f0c();
        func_02043b94();
        panelTabs.func_28(0x11);
        panelItems.func_28(0x11);
        func_020a11f8(func_020a18e4(), 0, 0);
        flags &= ~0x20;
    }
    if (panelConfirm.func_44() && (flags & 0x400)) {
        func_02043978(1);
        flags &= ~0x400;
    }
    panelTabs.func_08();
    panelItems.func_08();
    done.func_08();
    name.func_08();
    keyboard.func_00();
    panelConfirm.func_08();
    func_020a69ac(colorSprite, slider.func_020521a8());
    func_020aa158(&layout);
    if (flags & 0x200) {
        func_020a1494(func_020a18e4(), 2, 0x11);
        func_020a122c(func_020a18e4());
        flags &= ~0x200;
    }
    if (fade.state == 4) {
        func_02042d2c();
    }
}

void Unk02041b10::func_18() {
    flags |= 2;
}

bool Unk02041b10::func_3c(bool done) {
    if (!func_30() || (flags & 0x100)) {
        done = true;
    }
    if (mode == 1) {
        keyboard.func_04(done);
        done = true;
    } else {
        keyboard.func_04(true);
    }
    done = yes.func_0c(done);
    if (yes.touch.flags & 8) {
        panelConfirm.func_2c(0x11);
        flags |= 0x400;
    }
    done = no.func_0c(done);
    if (no.touch.flags & 8) {
        flags |= 0x80;
        func_02043a38();
    }
    if (!panelConfirm.func_3c()) {
        done = true;
    }
    if (!done && func_020a0744(data_020d6240.input, 6)) {
        func_02043a38();
        done = true;
    }
    done = this->done.func_0c(done);
    if (this->done.touch.flags & 8) {
        func_02043a38();
    }
    done = name.func_0c(done);
    if (name.touch.flags & 8) {
        func_02043978(1);
    }
    if (outfit0.flags & 0x10) {
        outfit0.func_0c(true);
    } else {
        done = outfit0.func_0c(done);
        if (outfit0.touch.flags & 8) {
            outfit1.func_02050aac(false);
            outfits[outfit] = func_020081dc(player);
            outfit = 0;
            panelTabs.func_2c(0x11);
            panelItems.func_2c(0x11);
            func_020a11f8(func_020a18e4(), 0, 1);
            flags |= 0x20;
        }
    }
    if (outfit1.flags & 0x10) {
        outfit1.func_0c(true);
    } else {
        done = outfit1.func_0c(done);
        if (outfit1.touch.flags & 8) {
            outfit0.func_02050aac(false);
            outfits[outfit] = func_020081dc(player);
            outfit = 1;
            panelTabs.func_2c(0x11);
            panelItems.func_2c(0x11);
            func_020a11f8(func_020a18e4(), 0, 1);
            flags |= 0x20;
        }
    }
    for (int i = 0; i < 6; i++) {
        done = tabs[i].func_0c(done);
        if ((tabs[i].touch.flags & 8) && i != part) {
            tabs[part].func_02050aac(false);
            part = i;
            panelItems.func_2c(0x11);
            flags |= 0x10;
        }
    }
    for (int i = 0; i < 6; i++) {
        done = items[i].func_0c(done);
        if ((items[i].touch.flags & 8) && i != item) {
            items[item].func_02050aac(false);
            item = i;
            func_020a7c90(cursor, items[i].func_10()->x);
            func_020a7cac(cursor, items[i].func_10()->y);
            func_020a11f8(func_020a18e4(), 0, 1);
            flags |= 8;
        }
    }
    done = slider.func_0c(done);
    if ((slider.touch.flags & 8) && slider.func_020521a8() != color) {
        color = slider.func_020521a8();
        func_020a11f8(func_020a18e4(), 0, 1);
        flags |= 0x40;
    }
    return done;
}

void Unk02041b10::func_02043978(int mode) {
    switch (this->mode) {
    case 0:
        break;
    case 1:
        keyboard.func_0204e9f4();
        break;
    }
    this->mode = mode;
    switch (mode) {
    case 0:
        break;
    case 1:
        keyboard.func_0204ea00(player->name);
        keyboard.func_0204e9d8();
        break;
    }
}

int Unk02041b10::func_020439dc(int part) {
    switch (part) {
    case 0:
        return 3;
    case 1:
        return 4;
    case 2:
        return 8;
    case 3:
        return 0;
    case 4:
        return 1;
    case 5:
        return 2;
    }
    return 7;
}

void Unk02041b10::func_02043a38() {
    if (!(flags & 0x80)) {
        panelConfirm.func_28(0x11);
        return;
    }
    if (panelConfirm.func_38()) {
        panelConfirm.func_30(0x1e);
        panelConfirm.func_2c(0x1e);
    }
    panelTabs.func_30(0x1e);
    panelTabs.func_2c(0x1e);
    panelItems.func_30(0x1e);
    panelItems.func_2c(0x1e);
    done.func_2c(0x1e);
    name.func_2c(0x1e);
    func_02066748(&data_020c43a8, 0x42, false, 0, true, 0);
    flags |= 0x100;
}

void Unk02041b10::func_02043b74() {
    flags |= 4;
    func_18();
}

void Unk02041b10::func_02043b94() {
    func_020a18e4();
    int kind = func_020439dc(part);
    int i;
    int count = catalog->func_020726bc(kind);
    for (i = 0; i < count; i++) {
        int id = catalog->func_02072710(kind, i);
        items[i].func_18(true);
        items[i].func_020508ac(func_0206446c(id));
        items[i].func_02050c48(func_020644bc(id), -1, -1);
        items[i].func_02050bf0(-1, -1, -1, func_020644b0(id), -1, -1);
        items[i].func_020514f0();
        items[i].func_08();
        if ((u8)(signed char)(part - 3) <= 1) {
            func_0203c254(catalog->func_0207278c(kind, i), items[i].unk64, 0);
        }
        if (catalog->func_020728c4(kind, i)) {
            item = i;
            func_020a7c90(cursor, items[i].func_10()->x);
            func_020a7cac(cursor, items[i].func_10()->y);
        }
    }
    for (i = count; i < 6; i++) {
        items[i].func_18(false);
    }
    if (part == 1) {
        slider.func_18(true);
        func_020a7cf0(colorSprite, true);
        for (int i = 0; i < catalog->func_020726bc(5); i++) {
            if (catalog->func_020728c4(5, i)) {
                color = i;
                slider.func_020527a0(FX32(i));
                func_020a69ac(colorSprite, i);
                return;
            }
        }
    } else {
        slider.func_18(false);
        func_020a7cf0(colorSprite, false);
    }
}

void Unk02041b10::func_02043f0c() {
    int i;
    u32 hash = 0xd05c0070;
    if (func_020081dc(&data_020c43a8).unk28 == 1) {
        hash = 0xa4d707c1;
    }
    for (i = 0; i < 6; i++) {
        func_020a6980(tabs[i].icon, hash);
    }
}
