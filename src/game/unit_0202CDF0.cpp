/*
 * Unit 0x0202CDF0-0x0202E0EC: the recipe screen (Unk0202cdf0, 0x7B0 bytes,
 * vtable 0x020B931C) on the screen base Unk0203c188, built by its owner with a
 * flag and a mode. It shows the recipe of the object data_020b9310: the result,
 * up to five ingredients as two rows of buttons with the owned and needed
 * counts; a press on an ingredient opens that object.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * the previous screen (unit_0202AEF4.cpp); the end is the paged text screen
 * (unit_0202E0EC.cpp). `.data` holds the current object, this class's vtable
 * with its header and the count format. Real file name unknown.
 *
 * Not complete: two functions are below 100 % (comments above them), and
 * objdiff scores `.data` 99.40 % (the count format, a literal section).
 */

#include "game/unk_screen.h"
#include "game/unk_archive.h"

/* An object of the database. */
struct Unk0205cf00;

/* An inventory entry. */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
    u32 unk8;
};

/* A recipe of an object (unit_0205359C.cpp). */
struct Unk0205367c {
    Unk0205cf00 *def;
    Unk0205cf00 *items[6];
    u8 counts[5];
    bool flags[6];
    Unk0205cf00 *result;
};

/* The sprites of a row of ingredients (unit_0205359C.cpp). */
struct Unk02053bf8 {
    Unk02053bf8() {
        for (u32 i = 0; i < 6; i++) {
            icons[i] = 0;
        }
        for (int i = 0; i < 5; i++) {
            counts[i] = 0;
        }
        for (int i = 0; i < 4; i++) {
            plus[i] = 0;
        }
    }

    Unk020a7c90 *icons[6];
    Unk020a7c90 *counts[5];
    Unk020a7c90 *plus[4];
    Unk020a7c90 *arrow;
};

/* The system (data_020d6240): only the archive. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

struct Unk020bfc9c;
struct Unk020d60c8;

extern Unk020bfc9c data_020bfc9c;
extern Unk020d60c8 data_020d60c8;
extern u32 data_020be41c;

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
const char *func_020a00a0(void *texts, u32 id);
int func_0205d134(Unk0205cf00 *item, u32 key);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
u32 func_02053914(Unk0205367c *t);
Unk0205cf00 *func_02053bd8(Unk0205367c *t, int index);
Unk0205cf00 *func_02053be4(Unk0205367c *t);
void func_02053bf8(Unk02053bf8 *ui, Unk0205367c *t, Unk02098e70 *pos, bool plus);
int func_0209f0a4(Unk020d60c8 *settings);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a788c(Unk020a7c90 *t, int x, int y, Unk0209487c *file, int index);
void func_020a7d30(Unk020a7c90 *s, int frame);
void func_02029128(Unk0203c188Owner *owner, int a);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
int func_02082a2c(char *buf, const char *fmt, ...);
void func_02033ea0(Unk0205cf00 *def);
bool func_0203e314(u32 key);
void func_0202e0dc(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b9310 = 0;
#pragma explicit_zero_data reset

class Unk0202cdf0 : public Unk0203c188 {
public:
    Unk0202cdf0(Unk0203c188Owner *owner, bool flag, int mode);
    virtual ~Unk0202cdf0();
    virtual bool func_30();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_3c(bool done);
    virtual void func_38(bool active);

    void func_0202df0c();
    void func_0202dffc();

    int mode;
    Unk020a9d58 *layout;
    Unk0205367c *recipe;
    Unk02053bf8 ui1;
    Unk02053bf8 ui2;
    Unk02051704 panel;
    Unk02051704 panel2;
    Unk02050640 button;
    Unk02050640 back;
    Unk02050640 buttons[5];
    Unk02050640 buttons2[5];
    Unk020a7c90 *sprite;
    Unk020a7c90 *title;
    char num[0x20];
};

static void *func_0202e038(u32 id, void *user);

static inline Unk0205367c *func_recipe() {
    Unk0205367c *t = (Unk0205367c *)operator new(0x2c);
    if (t != 0) {
        t = func_0205367c(t, data_020b9310);
    }
    return t;
}

/*
 * 99.81 %: in the button loop the index and the array offset are swapped (r8, r9
 * in the original). Tried: the index declared before the loop.
 */
Unk0202cdf0::Unk0202cdf0(Unk0203c188Owner *owner, bool flag, int mode)
    : Unk0203c188(owner), mode(mode) {
    if (flag) {
        flags |= 0x10;
    }
    recipe = func_recipe();
    Unk020a7af4Entry entries[0x46];
    Unk020a7af4 names(entries, 0x46);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x0afede48, layout, &names);
    func_020a9db8(layout, func_0202e038, this);

    panel.func_20(0xffeba000, -0x23000);
    panel.func_14(-0x23000, 0);
    panel.func_02051804(8);
    panel.func_020518a8(6);
    title = func_020aa040(layout, 4, func_020a7b50(&names, 0xe0343c1b));
    if (recipe->flags[5]) {
        func_020a716c(title, 0xd71);
    } else {
        Unk0205cf00 *result = func_02053be4(recipe);
        if (result != 0) {
            func_020a716c(title, func_0205d134(result, 0xbe33d1b8));
        } else {
            func_020a716c(title, 0);
        }
    }
    panel.func_02051858(title);
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));
    panel.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xc0e2b298)));

    sprite = func_020aa040(layout, 4, func_020a7b50(&names, 0x994b8a5a));
    panel2.func_14(func_020a7ca4(sprite), func_020a7cc0(sprite));
    panel2.func_24(0xc0000, func_020a7cc0(sprite));
    panel2.func_14(0, 0x64000);
    panel2.func_24(0xc0000, 0x64000);
    panel2.func_02051804(2);
    panel2.func_020518a8(5);
    panel2.func_02051858(sprite);
    panel2.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x9138150d)));

    ui1.icons[5] = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x0beb7dd1));
    ui2.icons[5] = 0;
    for (int i = 0; i < 5; i++) {
        ui1.icons[i] = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x0beb7dcc + i));
        ui1.counts[i] = func_020aa040(layout, 3, func_020a7b50(&names, 0x058211b1 + i));
        ui2.icons[i] = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc549b291 + i));
        ui2.counts[i] = func_020aa040(layout, 3, func_020a7b50(&names, 0x527f8819 + i));
    }
    for (int i = 0; i < 4; i++) {
        Unk020a7c90 *plus = func_020aa040(layout, 1, func_020a7b50(&names, 0x60612b79 + i));
        ui1.plus[i] = plus;
        panel.func_02051858(plus);
    }
    Unk020a7c90 *arrow = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x5a9e6405));
    ui1.arrow = arrow;
    panel.func_02051858(arrow);

    Unk020a7c90 *s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc2f94842));
    back.func_02050838(s, false);
    back.func_02050c48(0, 1, -1);
    back.func_20(func_020a7ca4(s) - s->func_10(), func_020a7ca4(s));
    back.func_02050914(2);
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x15f3ba51)));
    Unk020a7c90 *icon = func_020aa040(layout, 1, func_020a7b50(&names, 0x060bbd76));
    back.func_02050968(icon);
    if (this->mode == 0x10) {
        func_020a6980(icon, 0xb988a2f6);
        func_020a69ac(icon, 0xe);
    } else if (this->mode == 7) {
        func_020a69ac(icon, 0xe);
    } else if (this->mode == 8) {
        back.func_18(false);
        func_02029128(this->owner, 1);
    }

    Unk02098e70 pos1(0x2000, 0xc000);
    Unk02098e70 pos2(0x2000, 0x64000);
    func_02053bf8(&ui1, recipe, &pos1, true);
    func_02053bf8(&ui2, recipe, &pos2, false);

    for (int i = 0; i < 5; i++) {
        buttons[i].func_02050838(ui1.icons[i], false);
        buttons[i].func_02050914(1);
        buttons[i].func_02050968(ui1.counts[i]);
        if (recipe->flags[i]) {
            buttons[i].flags |= 8;
        } else {
            buttons[i].flags &= ~8;
        }
        panel.func_020518fc(&buttons[i]);
        buttons2[i].func_02050838(ui2.icons[i], false);
        buttons2[i].func_02050914(1);
        buttons2[i].func_02050968(ui2.counts[i]);
        if (recipe->flags[i]) {
            buttons2[i].flags |= 8;
        } else {
            buttons2[i].flags &= ~8;
        }
        panel2.func_020518fc(&buttons2[i]);
    }
    panel.func_020518fc(&button);

    icon = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xa8e45f9f));
    func_020a7c90(icon, func_020a7ca4(ui1.icons[5]) - 0x2000);
    func_020a7cac(icon, func_020a7cc0(ui1.icons[5]) - 0x2000);
    button.func_02050838(icon, false);
    button.func_02050c48(0, 1, -1);
    button.flags |= 2;
    button.func_020508a4(ui1.icons[5]);
    button.func_02050914(1);
    if (flag && (this->mode == 6 || this->mode == 0x10 || this->mode == 8)) {
        Unk020a7c90 *t = func_020aa040(layout, 4, func_020a7b50(&names, 0xa86c4389));
        func_020a7cf0(t, true);
        func_020a7c90(t, func_020a7ca4(icon) - 0xd000);
        func_020a7cac(t, func_020a7cc0(icon) - 0xe000);
        button.func_02050968(t);
        if (this->mode == 0x10) {
            func_020a716c(t, 0x2e3);
            if (func_0209f0a4(&data_020d60c8) == 4 && func_02053914(recipe) > 2) {
                func_020a7c90(t, func_020a7ca4(icon) - 0x12000);
            }
        }
    }
    if (this->mode == 7) {
        func_020a7cf0(icon, false);
    }

    for (u32 i = 0; i < func_02053914(recipe); i++) {
        int have = 0;
        int need = recipe->counts[i];
        Unk02054dc4 *e = func_02054dc4(&data_020bfc9c, func_02053bd8(recipe, i), 0);
        if (e != 0) {
            have = e->count;
        }
        if (have < need) {
            func_020a7d30(ui2.counts[i], 7);
        } else {
            func_020a7d30(ui2.counts[i], 6);
        }
    }
}

Unk0202cdf0::~Unk0202cdf0() {
    func_0202dffc();
    delete layout;
    delete recipe;
}

bool Unk0202cdf0::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk0202cdf0::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0202df0c();
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_34(0x22);
        panel.func_28(0x22);
        panel2.func_34(0x22);
        panel2.func_28(0x22);
        back.func_34(0x22);
        back.func_28(0x22);
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x10);
        panel2.func_30(0x10);
        back.func_30(0x10);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0202cdf0::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_30(0x22);
        panel.func_2c(0x22);
        panel2.func_30(0x22);
        panel2.func_2c(0x22);
        back.func_30(0x22);
        back.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

/*
 * 99.85 %: the argument `done` stays in r9 here; the original has it in r4,
 * moved to r9 by the first button. Tried: a separate local, the index declared
 * first.
 */
bool Unk0202cdf0::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button.func_0c(done);
    if (button.touch.flags & 8) {
        func_020292c0(owner, 0x15);
        func_02028eec(owner, 0x15, data_020b9310, 0);
    }
    for (int i = 0; i < 5; i++) {
        done = buttons2[i].func_0c(buttons[i].func_0c(done));
        if ((buttons[i].touch.flags & 8) || (buttons2[i].touch.flags & 8)) {
            func_020292c0(owner, 0x15);
            func_02028eec(owner, 0x15, func_02053bd8(recipe, i), 0);
            func_02033ea0(data_020b9310);
        }
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        func_020292c0(owner, mode);
        if (mode != 7) {
            func_02028eec(owner, mode, data_020b9310, 0);
        }
        if (flags & 0x10) {
            func_0203e314(data_020be41c);
        }
    }
    return done;
}

void Unk0202cdf0::func_38(bool active) {
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
    panel.func_08();
    panel2.func_08();
    back.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0202dffc();
    }
}

void Unk0202cdf0::func_0202df0c() {
    if (flags & 2) {
        return;
    }
    panel2.func_34(0x22);
    panel.func_34(0x22);
    back.func_34(0x22);
    func_020aa06c(layout, true);
    Unk02093648 *a = func_020a18e4()->archive;
    Unk02093648 *b = func_020a18e4()->archive;
    Unk0209487c *file = b->func_02093a9c(a->func_02093e9c(0x3ae82eff));
    int i = 0;
    int n = i;
    int j;
    int x;
    for (int y = i; i < 3; i++, y += 0x20) {
        j = 0;
        for (x = j; j < 7; j++, x += 0x20, n++) {
            func_020a788c(sprite, x, y, file, n);
        }
    }
    flags |= 2;
}

void Unk0202cdf0::func_0202dffc() {
    if (flags & 2) {
        data_020b9310 = 0;
        func_020aa06c(layout, false);
        flags &= ~2;
    }
}

static void *func_0202e038(u32 id, void *user) {
    Unk0202cdf0 *screen = (Unk0202cdf0 *)user;
    int n = id - 0x800000;
    if (n > 0 && n < 6) {
        func_02082a2c(screen->num, "%d", screen->recipe->counts[n - 1]);
        return screen->num;
    }
    if (n > 5) {
        int have = 0;
        Unk02054dc4 *e = func_02054dc4(&data_020bfc9c, func_02053bd8(screen->recipe, n - 6), 0);
        if (e != 0) {
            have = e->count;
        }
        func_02082a2c(screen->num, "%d", have);
        return screen->num;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

void func_0202e0dc(Unk0205cf00 *def) {
    data_020b9310 = def;
}
