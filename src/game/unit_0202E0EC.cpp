/*
 * Unit 0x0202E0EC-0x0202FDDC: a paged text screen for an object (Unk0202e0ec,
 * 0x6D4 bytes, vtable 0x020B9370) on the screen base Unk0203c188, built by its
 * owner with a mode. It shows the object data_020b9364, or the text of
 * data_020be420 when that is set, splits the text in pages with two page
 * buttons, and offers two icon buttons to open the objects named by the
 * object's script.
 *
 * Bounds: hypothesis. The start is the constructor, after func_0202e0dc; the
 * end is the object detail screen (unit_0202FDDC.cpp). `.rodata` holds the two
 * initializers of func_0202f2ac; `.data` the current object, this class's
 * vtable with its header and the two page formats. Real file name unknown.
 *
 * Not complete: two functions are below 100 % (comments above them); the words
 * 0x020AE89C 5 and 0x020AE8A0 0x32 of `.rodata`, never loaded, are not
 * reproduced (unused file-scope constants do not emit them).
 */

#include "game/unk_screen.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"
#include "game/unk_resource.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"
#include "game/unk_text.h"

/* A text sprite (func_020a78cc). */
class Unk020a78cc : public Unk020a7c90 {
public:
    u8 unk4[0x3c];
    Unk02090308 *canvas;
};

/* A font of a layout (func_020aa040 type 0): only the font. */
struct Unk020aa040Font {
    u8 unk0[0x14];
    Unk02092830Font *font;
};

/* An object of the database. */
struct Unk0205cf00 {
    int unk0[4];
    Unk020956f8 *script;
};

/* A recipe of an object (unit_0205359C.cpp). */
struct Unk0205367c {
    Unk0205cf00 *def;
    Unk0205cf00 *items[6];
    u8 counts[5];
    bool flags[6];
    Unk0205cf00 *result;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

struct Unk020c3fc4;
struct Unk020d6298;
struct Unk020be420;

extern Unk020d6240 data_020d6240;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020d6298 data_020d6298;
extern Unk020be420 *data_020be420;
extern u32 data_020be41c;
extern const u32 data_020ae7cc[];

void *func_0201ba94();
extern "C" {
Unk0202071c func_0202071c(Unk020d6298 *clock);
Unk020d6240 *func_020a18e4();
const char *func_020a00a0(void *texts, u32 id);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
int func_0205d1b4(Unk0205cf00 *item, u32 key);
int func_0205ec0c(Unk020be420 *p);
int func_0205ecc0(Unk020be420 *p, u32 key);
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
Unk0205cf00 *func_02053be4(Unk0205367c *t);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a6980(Unk020a7c90 *s, u32 hash);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
u16 func_020a7164(Unk020a7c90 *t);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a71a4(Unk020a7c90 *t, int x);
void func_020a727c(Unk020a7c90 *t, int value);
int func_020a72c8(Unk020a7c90 *t);
int func_020a731c(Unk020a7c90 *t);
int func_020a705c(int align);
int func_020a709c(int align);
void func_020a78cc(Unk020a7c90 *t, Unk020a7c90 *font, const char *fmt, ...);
int func_020a793c(Unk020a7c90 *t, int page, Unk020a7c90 *font, const char *fmt, ...);
void func_020a7ce0(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
void func_0203c254(int value, int index, int main);
void func_02029128(Unk0203c188Owner *owner, int a);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
void func_02028edc(Unk0203c188Owner *owner, u32 value);
int func_02082a2c(char *buf, const char *fmt, ...);
void func_02033ea0(Unk0205cf00 *def);
void func_0202fd18(Unk0205cf00 *def);
void func_0202fd28(Unk020be420 *p);
void *func_0202fdb0();
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b9364 = 0;
#pragma explicit_zero_data reset

class Unk0202e0ec : public Unk0203c188 {
public:
    Unk0202e0ec(Unk0203c188Owner *owner, int mode);
    virtual ~Unk0202e0ec();
    virtual void func_08();
    virtual void func_1c();
    virtual bool func_30();
    virtual bool func_14();
    virtual bool func_28();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_3c(bool done);
    virtual void func_38(bool active);
    virtual void func_18();
    virtual bool func_34();
    virtual bool func_2c();

    void func_0202f2ac();
    void func_0202f89c();

    int mode;
    Unk020a9d58 *layout;
    Unk02050640 button;
    Unk02051704 panel;
    Unk02051704 sub1;
    Unk02051704 sub2;
    Unk02051704 pager;
    Unk02050640 next;
    Unk02050640 prev;
    Unk02050640 back;
    Unk02050640 item;
    Unk02050640 tool;
    Unk0205cf00 *toolDef;
    Unk0205cf00 *itemDef;
    char text[0x200];
    Unk020a7c90 *title;
    char num[0x20];
    short page;
    short pages;
};

static void *func_0202fd38(u32 id, void *user);

/*
 * 98.46 %: registers of the second icon block (key r5, sprite r4, palette r8 in
 * the original), some name lookups truncate through r0 where the original uses
 * r1 or the reverse, and a few instructions are scheduled differently. Tried:
 * declaration order of that block, reusing `key`, a local for mode - 3.
 */
Unk0202e0ec::Unk0202e0ec(Unk0203c188Owner *owner, int mode)
    : Unk0203c188(owner), mode(mode), toolDef(0), itemDef(0) {
    Unk020a7af4Entry entries[0x32];
    Unk020a7af4 names(entries, 0x32);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xfbd7d1b9, layout, &names);
    func_020a9db8(layout, func_0202fd38, this);

    panel.func_14(-0x23000, 0);
    panel.func_20(0xffeba000, -0x23000);
    panel.func_020518a8(6);
    panel.func_02051804(0xf);
    title = func_020aa040(layout, 4, func_020a7b50(&names, 0x96c99379));
    panel.func_02051858(title);
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));

    int textId = 0xd7b;
    sub1.func_02051804(2);
    sub1.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x9774c086)));
    sub1.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc40c9901)));
    sub1.func_18(false);
    panel.func_020518fc(&sub1);

    sub2.func_02051804(6);
    sub2.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x8df9f519)));
    sub2.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x8df9f51a)));
    sub2.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xc871ce68)));
    sub2.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xc871ce69)));
    sub2.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x0050864a)));
    sub2.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x0050864b)));
    sub2.func_18(false);
    panel.func_020518fc(&sub2);

    int key;
    int count = 0;
    int music = -1;
    if ((u32)(mode - 3) <= 1) {
        Unk0205367c recipe;
        func_0205367c(&recipe, data_020b9364);
        Unk0205cf00 *result = func_02053be4(&recipe);
        key = func_0205d134(result, 0x9d5bba8e);
        if (key == -1) {
            key = 0;
        }
        count = func_0205d134(result, 0xbe33d1b8);
        if (func_0205d340(result, data_020ae7cc[8]) || func_0205d340(result, data_020ae7cc[9])) {
            music = func_0205d134(result, 0x2b3e6dd7);
        }
    } else {
        key = func_0205d134(data_020b9364, 0x9d5bba8e);
    }
    if (key < 0) {
        key = 0;
    }

    Unk020a7c90 *icon = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc372e8bd));
    func_020a6980(icon, func_0206446c(key));
    func_020a69ac(icon, func_020644bc(key));
    int palette = func_020644b0(key);
    Unk02093648 *archive = func_020a18e4()->archive;
    Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(icon)));
    Unk020916a4::func_02091830()->func_0209201c((Unk02095140 *)file, func_020a69cc(icon), palette << 4,
                                                func_020a7d44(icon) << 4, 0x10);
    archive->func_02093c3c(file);
    if (music >= 0) {
        func_0203c254(music, func_020a7d44(icon), 0);
    }

    item.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x611a4b02)), false);
    item.func_02050c48(0, 1, -1);
    item.func_020508a4(icon);
    item.func_18(true);
    panel.func_020518fc(&item);

    int id = func_0205d1b4(data_020b9364, 0xc0e2b298);
    if (id != 0) {
        itemDef = func_0205f6f8(&data_020c3fc4, id);
    }
    func_020a7cf0(item.sprite, itemDef != 0);

    bool small = false;
    if (mode == 2) {
        textId = func_0205d134(data_020b9364, 0xbe33d1b8);
        small = true;
        func_02029128(this->owner, small);
    } else if ((u32)(mode - 3) <= 1) {
        textId = mode == 3 ? 0x1079 : 0x1078;
        small = true;
        func_020a7cac(title, 0x22000);
        func_020a7cac(icon, 0x51000);
        Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x70672481));
        func_020a7cac(s, func_020a7cc0(icon) - 0x11000);
        func_020a7cf0(s, small);
        func_020a716c(s, count);
        panel.func_02051858(s);
    }
    if (small) {
        item.func_18(false);
        item.func_02050838(icon, false);
        item.func_02050c48(-1, -1, -1);
        item.func_020508a4(0);
        item.func_18(true);
        item.flags |= 8;
    }

    id = func_0205d1b4(data_020b9364, 0x0d933e26);
    if (id != 0) {
        toolDef = func_0205f6f8(&data_020c3fc4, id);
        int toolKey = func_0205d134(toolDef, 0x9d5bba8e);
        if (toolKey == -1) {
            toolKey = 0;
        }
        tool.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x611a4b03)), false);
        tool.func_02050c48(0, 1, -1);
        Unk020a7c90 *s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc372e8be));
        tool.func_020508a4(s);
        func_020a6980(s, func_0206446c(toolKey));
        func_020a69ac(s, func_020644bc(toolKey));
        int toolPalette = func_020644b0(toolKey);
        Unk02093648 *a = func_020a18e4()->archive;
        Unk02093648 *b = func_020a18e4()->archive;
        Unk0209487c *f = b->func_02093a9c(a->func_02093e9c(func_020a69a4(s)));
        Unk020916a4::func_02091830()->func_0209201c((Unk02095140 *)f, func_020a69cc(s), toolPalette << 4,
                                                    func_020a7d44(s) << 4, 0x10);
        a = func_020a18e4()->archive;
        b = func_020a18e4()->archive;
        b->func_02093c58(a->func_02093e9c(func_020a69a4(s)));
        tool.func_18(true);
        func_020a7cf0(tool.sprite, mode == 1);
        panel.func_020518fc(&tool);
        textId = 0xd7a;
    } else {
        int y = mode == 2 ? 0x1c000 : item.func_10()->y;
        item.func_14(0x6a000, y);
        tool.flags |= 8;
    }

    Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0xe0343c1b));
    func_020a716c(s, textId);
    panel.func_02051858(s);

    button.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x63b94c03)), false);
    button.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xee1a47e2)));
    button.func_02050914(1);
    button.func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0x63412fed)));
    button.func_02050c48(0, 1, -1);
    button.func_02050c64(0, 1, 2);
    button.flags |= 2;
    panel.func_020518fc(&button);

    s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc2f94842));
    back.func_02050838(s, false);
    back.func_02050c48(0, 1, -1);
    back.func_20(func_020a7ca4(s) - s->func_10(), func_020a7ca4(s));
    back.func_02050914(2);
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x15f3ba51)));
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x060bbd76)));
    back.func_18(mode == 1);

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));

    next.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));

    pager.func_14(0, next.func_10()->y);
    pager.func_24(0xc0000, pager.func_10()->y);
    pager.func_020518a8(2);
    pager.func_02051804(2);
    pager.func_020518fc(&prev);
    pager.func_020518fc(&next);
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x79be6d8f)));
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x03398ecd)));
}

Unk0202e0ec::~Unk0202e0ec() {
    func_0202f89c();
    delete layout;
}

void Unk0202e0ec::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0202e0ec::func_1c() {
    flags &= ~4;
}

bool Unk0202e0ec::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk0202e0ec::func_14() {
    return (flags & 4) != 0;
}

bool Unk0202e0ec::func_28() {
    return fade.func_shown();
}

bool Unk0202e0ec::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0202f2ac();
    if (flags & 8) {
        fade.func_duration(0x22);
        if (pages > 1) {
            pager.func_34(0x22);
            pager.func_28(0x22);
        }
        panel.func_34(0x22);
        panel.func_28(0x22);
        if (back.func_02050a24()) {
            back.func_28(0x22);
        }
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x22);
        if (pages > 1) {
            pager.func_30(0x22);
        }
        if (back.func_02050a24()) {
            back.func_30(0x22);
        }
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0202e0ec::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_2c(0x22);
        pager.func_2c(0x22);
        back.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

/*
 * 99.20 %: registers only. The original has value r5, id r6, keys r7, font r8;
 * value and `dated` share one register there. Tried: declaration orders of these
 * locals, one variable for both.
 */
void Unk0202e0ec::func_0202f2ac() {
    if (flags & 2) {
        return;
    }
    void *texts;
    int value;
    int id;
    Unk020a7c90 *font;
    if (mode == 3) {
        id = 0x107a;
    } else if (mode == 4) {
        id = 0x107b;
    } else if (data_020be420 != 0) {
        id = func_0205ec0c(data_020be420);
    } else {
        id = func_0205d134(data_020b9364, 0x6a4a2934);
        if (mode == 1) {
            func_020a727c(title, -1);
        }
    }
    bool dated = false;
    if (mode == 2) {
        if (func_0205d340(data_020b9364, 0x1e474fc5) || func_0205d340(data_020b9364, 0x16bc2f6e)
            || func_0205d340(data_020b9364, 0x3b4942ae) || func_0205d340(data_020b9364, 0x071d9208)) {
            dated = true;
            sub2.func_18(dated);
            sub1.func_18(dated);
            item.func_14(0x31000, 0x22000);
            func_020a7cac(title, 0x56000);
            func_020a71a4(title, 0x2a000);
        }
    }
    panel.func_34(0x22);
    pager.func_34(0x22);
    back.func_34(0x22);
    func_020aa06c(layout, true);
    texts = func_0201ba94();
    font = func_020aa040(layout, 0, func_020a7164(title));
    value = 0;
    if (dated) {
        u32 keys[5] = {0x97006df8, 0xfaa14499, 0x67c64c17, 0x887c10c0, 0x146126e3};
        u32 ids[5] = {0xe60, 0xe61, 0xe62, 0xe63, 0xe63};
        int i;
        for (i = 0; i < 5; i++) {
            if (func_0205d340(data_020b9364, keys[i])) {
                break;
            }
        }
        if (i >= 5) {
            i = 0;
        }
        func_020a78cc(sub2.func_02051ad0(0), font, func_020a00a0(texts, ids[i]));
        Unk020a7c90 *line = sub2.func_02051ad0(1);
        if (i < 3) {
            Unk02099c78Var *var = data_020b9364->script->func_02095888(0xe03edad9);
            if (var != 0 && func_0205ecc0(data_020be420, 0xe03edad9) >= var->max) {
                id = 0xe6f;
                func_020a78cc(line, font, func_020a00a0(texts, id + 8));
            } else {
                id = 0xe6e;
                func_020a78cc(line, font, func_020a00a0(texts, id + 0xa));
            }
            func_020a69ac(sub2.func_02051ad0(3), 1);
        } else {
            Unk0202071c now = func_0202071c(&data_020d6298);
            int hour = (now.value & 0x7c0) >> 6;
            int left = 0;
            Unk02099c78Var *var = data_020b9364->script->func_02095888(0x109966ff);
            if (var != 0) {
                left = var->max - func_0205ecc0(data_020be420, 0x109966ff) - 1;
            }
            if (hour >= 0 && hour < 6) {
                left = left * 24 + 6 - hour;
            } else {
                left = left * 24 + 0x1e - hour;
            }
            int fmt = left > 1 ? 0xe74 : 0xe75;
            if (i == 3) {
                func_020a78cc(line, font, func_020a00a0(texts, fmt), left);
                id = 0xe70;
            } else if (func_0205d340(data_020b9364, 0x3b4942ae)) {
                id = 0xfa2;
            } else {
                Unk02099c78Var *v = data_020b9364->script->func_02095888(0xfe40865d);
                value = func_0205ecc0(data_020be420, 0xfe40865d);
                if (v != 0 && value >= v->max) {
                    func_020a78cc(line, font, func_020a00a0(texts, 0xe76));
                    id = 0xe73;
                } else {
                    func_020a78cc(line, font, func_020a00a0(texts, fmt), left);
                    id = value > 1 ? 0xe72 : 0xe71;
                }
            }
            func_020a69ac(sub2.func_02051ad0(3), 2);
        }
    }
    func_02082a2c(text, func_020a00a0(texts, id), value);
    int height = title->func_14() >> 12;
    Unk02092830 lines(text, ((Unk020aa040Font *)font)->font);
    int hAlign = func_020a705c(func_020a72c8(title));
    int vAlign = func_020a709c(func_020a731c(title));
    pages = lines.func_0209303c(hAlign, vAlign, title->func_10() >> 12, height, 0, 0);
    page = 0;
    func_020a793c(title, 0, font, text);
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    data_020be420 = 0;
    flags |= 2;
}

void Unk0202e0ec::func_0202f89c() {
    if (flags & 2) {
        func_020aa06c(layout, false);
        flags &= ~2;
    }
}

bool Unk0202e0ec::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = item.func_0c(done);
    if (item.touch.flags & 8) {
        if (func_0205d340(itemDef, 0x1b2e08fb)) {
            func_020292c0(owner, 0x18);
            func_02028eec(owner, 0x18, itemDef, 0);
        } else {
            func_020292c0(owner, 0x15);
            func_02028eec(owner, 0x15, itemDef, 0);
            func_02033ea0(data_020b9364);
        }
    }
    done = tool.func_0c(done);
    if (tool.touch.flags & 8) {
        func_020292c0(owner, 0x14);
        func_02028eec(owner, 0x14, toolDef, 0);
    }
    done = button.func_0c(done);
    if (button.touch.flags & 8) {
        if ((u32)(mode - 3) <= 1) {
            func_020292c0(owner, 6);
            func_02028eec(owner, 6, data_020b9364, 0);
            func_02028edc(owner, data_020be41c);
        } else {
            owner->func_18();
        }
    }
    done = prev.func_0c(done);
    if (prev.touch.flags & 8) {
        page--;
        ((Unk020a78cc *)title)->canvas->func_0209088c();
        func_020a793c(title, page, func_020aa040(layout, 0, func_020a7164(title)), text);
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = next.func_0c(done);
    if (next.touch.flags & 8) {
        page++;
        ((Unk020a78cc *)title)->canvas->func_0209088c();
        func_020a793c(title, page, func_020aa040(layout, 0, func_020a7164(title)), text);
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        func_020292c0(owner, 7);
    }
    return done;
}

void Unk0202e0ec::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    if (fade.state == 1) {
        func_40(false);
    }
    if (page < 1) {
        prev.flags |= 8;
    } else {
        prev.flags &= ~8;
    }
    if (page >= pages - 1) {
        next.flags |= 8;
    } else {
        next.flags &= ~8;
    }
    panel.func_08();
    pager.func_08();
    back.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0202f89c();
    }
}

void Unk0202e0ec::func_18() {
    flags |= 4;
}

void func_0202fd18(Unk0205cf00 *def) {
    data_020b9364 = def;
}

void func_0202fd28(Unk020be420 *p) {
    data_020be420 = p;
}

static void *func_0202fd38(u32 id, void *user) {
    Unk0202e0ec *screen = (Unk0202e0ec *)user;
    u32 n = id - 0x800000;
    if (n == 1) {
        func_02082a2c(screen->num, "%d", screen->page + 1);
        return screen->num;
    }
    if (n == 2) {
        func_02082a2c(screen->num, "/%d", screen->pages);
        return screen->num;
    }
    func_020a18e4();
    return (void *)func_020a00a0(func_0202fdb0(), id);
}

void *func_0202fdb0() {
    return func_0201ba94();
}

bool Unk0202e0ec::func_34() {
    return true;
}

bool Unk0202e0ec::func_2c() {
    return fade.func_hidden();
}
