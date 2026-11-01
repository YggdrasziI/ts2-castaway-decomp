/*
 * Unit 0x0202FDDC-0x02033EE0: the object detail screen (Unk0202fddc, 0x648
 * bytes, vtable 0x020B93CC) on the screen base Unk0203c188, built by its owner
 * with a mode. It shows the object data_020b93bc.cur: its icon, title, text,
 * six stat lines read from its script, small kind icons and one or two action
 * buttons whose texts depend on the mode; a confirmation panel asks before
 * the actions that need it. A press runs the action of the mode through
 * func_02033728.
 *
 * Bounds: hypothesis. The start is the constructor, after func_0202fdc4; the
 * end is the object text screen (unit_02033EE0.cpp). `.rodata` holds the stat
 * order initializer; `.data` the current and next objects, this class's
 * vtable with its header and the formats of the text functions. Real file
 * name unknown.
 *
 * Not complete: six functions are below 100 % (comments above them); the last
 * two words of `.rodata` (0x020AE8BC 0x3C000, 0x020AE8C0 0x46, never loaded)
 * are local `static const` values, and objdiff scores `.data` 87.5 % (the three formats).
 * func_02031028 is the widget base slot func_1c, defined here as its kept copy
 * sits in this file; the widget vtables still reference it by that name.
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"
#include "game/unk_sim.h"
#include "game/unk_oam.h"
#include "game/unk_script.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* A text sprite (func_020a78cc): only the field tested here. */
class Unk020a78cc : public Unk020a7c90 {
public:
    u8 unk4[0x3c];
    void *canvas;
};

/* An object of the database. */
struct Unk0205cf00 {
    int unk0[3];
    int id;
    Unk020956f8 *script;
};

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

/* The parameter reader (unit_0205D4D8.cpp). */
struct Unk0205d6b8 {
    int values[6];
};

/* A view of an object's kinds (functions at 0x02010B8C). */
struct Unk02010b8c {
    int unk0[2];
};

/* The survival guide animation of the player (unit_02055118.cpp): opaque here. */
struct Unk02055118 {
    int state;
};

/* The main game state (func_0206bce0): only its guide. */
struct Unk0206bce0 {
    u8 unk0[0x14c];
    Unk02055118 guide;
};

/* The player (data_020c43a8, unit_02064984.cpp): only its interface. */
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

    u32 *func_tile(int x, int y) {
        return &tiles[y * info->width + x];
    }
};

struct Unk020c3fc4;
struct Unk020bfc9c;
struct Unk020d60c8;

extern "C" {
void *func_0202fdb0();
const char *func_020a00a0(void *texts, u32 id);
}

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    const char *func_text(u32 id) {
        return func_020a00a0(func_0202fdb0(), id);
    }

    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The object shown and the object to show next. */
struct Unk020b93bc {
    Unk0205cf00 *cur;
    Unk0205cf00 *pending;
};

extern Unk020c43a8 data_020c43a8;
extern Unk020c3ba4 data_020c3ba4;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020bfc9c data_020bfc9c;
extern Unk020d60c8 data_020d60c8;
extern u32 data_020be41c;
extern const int data_020ae7cc[];
extern const u32 data_020aefe8[];

extern "C" {
Unk020d6240 *func_020a18e4();
void func_020a11f8(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
void func_020a1494(Unk020d6240 *system, int a, int b);
int func_0209f0a4(Unk020d60c8 *settings);
Unk0206bce0 *func_0206bce0();
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
void func_02055220(Unk02055118 *p, int state, int count);
void func_02055dd8(Unk02055118 *p);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
Unk0205cf00 *func_0205f714(Unk020c3fc4 *db, int key, Unk0205cf00 *rec);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
int func_0205d1b4(Unk0205cf00 *item, u32 key);
int func_0205d234(Unk0205cf00 *item, u32 key, u32 key2);
int func_0205d39c(Unk0205cf00 *def, int key);
Unk0205d6b8 *func_0205d608(Unk0205d6b8 *p, Unk020956f8 *script);
void func_0205d6dc(Unk0205d6b8 *p);
int func_0205d6fc(Unk0205d6b8 *p, int i);
int func_0205d704(Unk0205d6b8 *p);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
void func_02054cf0(Unk020bfc9c *p, Unk02054dc4 *e, int a);
void func_02054cb4(Unk020bfc9c *p, int id, int a);
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
bool func_02053940(Unk0205367c *t);
void func_020539b0(Unk0205367c *t);
int func_02053b84(Unk0205367c *t);
Unk0205cf00 *func_02053bd8(Unk0205367c *t, int index);
Unk0205cf00 *func_02053be4(Unk0205367c *t);
Unk020081dc func_020081dc(Unk020c43a8 *p);
void func_020662c8(Unk020c43a8 *p, int i, int n);
void func_020670fc(Unk020c43a8 *p, Unk020081dc *outfit);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
Unk02010b8c *func_02010b8c(Unk02010b8c *p, Unk0205cf00 *def);
Unk02010b8c *func_02010ba8(Unk02010b8c *p);
int func_02010bbc(Unk02010b8c *p);
bool func_02010bf8(Unk02010b8c *p);
bool func_02010c2c(Unk02010b8c *p);
void func_020a6980(Unk020a7c90 *s, u32 hash);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
u16 func_020a7164(Unk020a7c90 *t);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a78cc(Unk020a7c90 *t, Unk020a7c90 *font, const char *fmt, ...);
void func_020a7ce0(Unk020a7c90 *s);
int func_020a7d1c(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
void func_0203c254(int value, int index, int main);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
int sprintf(char *buf, const char *fmt, ...);
void func_02033718(Unk0205cf00 *def);
Unk0205cf00 *func_02033e88();
void func_02033ea0(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk020b93bc data_020b93bc = {0, 0};
#pragma explicit_zero_data reset

class Unk0202fddc : public Unk0203c188 {
public:
    Unk0202fddc(Unk0203c188Owner *owner, int mode);
    virtual ~Unk0202fddc();
    virtual bool func_30();
    virtual bool func_14();
    virtual bool func_28();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_3c(bool done);
    virtual void func_38(bool active);
    virtual bool func_34();
    virtual bool func_2c();
    virtual void func_1c();

    void func_0203161c();
    void func_020322b4(Unk0205cf00 *def, bool flag);
    void func_02032e24(Unk0205cf00 *def);
    bool func_02033454(int key, Unk0205cf00 *def, int id);
    bool func_02033544(int id, int key);
    void func_020335d4();
    void func_02033728(int index);

    Unk020a07d4Timer fade2;
    Unk0205cf00 *def;
    int count;
    int mode;
    Unk020a9d58 *layout;
    Unk02051704 panel;
    Unk02051704 confirm;
    Unk02051704 kinds;
    Unk02051704 stats;
    Unk020a7c90 *s19c;
    Unk020a7c90 *s1a0;
    Unk020a7c90 *s1a4;
    Unk020a7c90 *s1a8;
    int text;
    Unk020a7c90 *s1b0;
    Unk020a7c90 *s1b4;
    Unk0204f798 marks;
    short limit;
    short value;
    int counter;
    Unk020a7c90 *s228;
    Unk020a7c90 *s22c;
    Unk020a7c90 *s230;
    Unk020a7c90 *s234;
    Unk020a7c90 *s238;
    Unk020a7c90 *s23c;
    Unk0205367c *recipe;
    Unk02051704 icons;
    int buttonCount;
    int keys[2];
    Unk02050640 buttons[2];
    Unk02050640 back;
    char num[0x20];
    Unk02050640 yes;
    Unk02050640 no;
    Unk02050640 ok;
    Unk020a7c90 *s5e4;
    Unk020a7c90 *s5e8;
    Unk02051704 compare;
};

static void *func_02033628(u32 id, void *user);

/*
 * 97.79 %: some name lookups truncate their index through r0 where the
 * original uses r1 or the reverse (see the unsolved patterns).
 */
Unk0202fddc::Unk0202fddc(Unk0203c188Owner *owner, int mode)
    : Unk0203c188(owner), def(0), count(0), mode(mode), recipe(0) {
    if (mode == 0x1b) {
        def = data_020b93bc.cur;
        data_020b93bc.cur = data_020b93bc.pending;
    } else if (data_020b93bc.pending != 0) {
        def = data_020b93bc.pending;
    }
    data_020b93bc.pending = 0;
    Unk02054dc4 *e = func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0);
    if (e != 0) {
        count = e->count;
    }
    static const int size = 0x46;
    Unk020a7af4Entry entries[size];
    Unk020a7af4 names(entries, size);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xd362de45, layout, &names);
    func_020a9db8(layout, func_02033628, this);

    panel.func_20(0xffeba000, -0x23000);
    panel.func_14(-0x23000, 0);
    panel.func_02051804(0x1f);
    panel.func_020518a8(8);
    stats.func_02051804(0xe);
    for (int i = 0; i < 6; i++) {
        stats.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x8f8b9a98 + i)));
        stats.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x9cebe37c + i)));
    }
    stats.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x9774c086)));
    stats.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc40c9901)));
    panel.func_020518fc(&stats);
    s1b4 = func_020aa040(layout, 1, func_020a7b50(&names, 0x21bf24fa));
    panel.func_02051858(s1b4);
    s228 = func_020aa040(layout, 4, func_020a7b50(&names, 0xb1b7dbfb));
    panel.func_02051858(s228);
    panel.func_02051858(s22c = func_020aa040(layout, 4, func_020a7b50(&names, 0x62ee430b)));
    marks.func_0204f8a0(1);
    marks.func_0204f8f4(func_020aa040(layout, 1, func_020a7b50(&names, 0x05c5aa2d)));
    panel.func_020518fc(&marks);
    kinds.func_02051804(3);
    kinds.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xc7e1f5b0)));
    kinds.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x85b4a356)));
    kinds.func_02051858(s1a8 = func_020aa040(layout, 4, func_020a7b50(&names, 0x96c99379)));
    panel.func_020518fc(&kinds);
    s230 = func_020aa040(layout, 4, func_020a7b50(&names, 0xe0343c1b));
    panel.func_02051858(s230);
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));
    s1a0 = func_020aa040(layout, 1, func_020a7b50(&names, 0x085ee8a8));
    panel.func_02051858(s1a0);
    panel.func_02051858(s19c = func_020aa040(layout, 3, func_020a7b50(&names, 0x7f2d5c79)));
    panel.func_02051858(s1a4 = func_020aa040(layout, 1, func_020a7b50(&names, 0x5451bab4)));
    s234 = func_020aa040(layout, 4, func_020a7b50(&names, 0x4fc8d2db));
    s23c = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xf0e1a0a2));
    s238 = func_020aa040(layout, 1, func_020a7b50(&names, 0x7937ad0a));
    panel.func_02051858(s234);
    panel.func_02051858(s23c);
    panel.func_02051858(s238);

    u32 hash = 0xa152d989;
    int n = 1;
    if (mode == 0x13 && func_0209f0a4(&data_020d60c8) == 4) {
        hash = 0x25ae32f3;
        n = 2;
    }
    s5e8 = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x25ae32f3));
    for (int i = 0; i < 2; i++) {
        buttons[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, hash + i)), false);
        buttons[i].func_02050c48(0, n, -1);
        buttons[i].func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x145c07e4 + i)));
        buttons[i].func_02050914(1);
        buttons[i].func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0x0ec6c1b0 + i)));
        panel.func_020518fc(&buttons[i]);
    }

    Unk020a7c90 *s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc2f94842));
    back.func_02050838(s, false);
    back.func_02050c48(0, 1, -1);
    back.func_20(func_020a7ca4(s) - s->func_10(), func_020a7ca4(s));
    back.func_02050914(2);
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x060bbd76)));
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x15f3ba51)));

    Unk020a7c90 *bg = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xf961d5fc));
    s5e4 = func_020aa040(layout, 4, func_020a7b50(&names, 0x15945575));
    confirm.func_14(-0x23000, func_020a7cc0(bg));
    confirm.func_24(0xc0000, func_020a7cc0(bg));
    confirm.func_02051804(2);
    confirm.func_020518a8(2);
    confirm.func_02051858(bg);
    confirm.func_02051858(s5e4);
    confirm.func_020518fc(&yes);
    confirm.func_020518fc(&no);
    confirm.func_18(false);

    compare.func_02051804(4);
    compare.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x1ac4aa49)));
    compare.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x1ac4aa4a)));
    compare.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x2cbb15e7)));
    compare.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x0675e7d9)));
    compare.func_18(false);
    panel.func_020518fc(&compare);

    icons.func_02051804(5);
    for (int i = 0; i < 3; i++) {
        icons.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xf1851a9d + i)));
    }
    icons.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xe492c2c3)));
    icons.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x31aa90b5)));
    icons.func_18(false);
    panel.func_020518fc(&icons);

    yes.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x14990c0b)), false);
    yes.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x512265ac)));
    yes.func_02050914(1);
    yes.func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0x1420eff5)));
    yes.func_02050c48(0, 1, -1);
    yes.func_02050c64(0, 1, 2);

    no.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xd4674b2a)), false);
    no.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x905700b4)));
    no.func_02050914(1);
    no.func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0xd3ef2f14)));
    no.func_02050c48(0, 1, -1);
    no.func_02050c64(0, 1, 2);

    ok.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x63b94c03)), true);
    ok.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xee1a47e2)));
    ok.func_02050914(1);
    ok.func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0x63412fed)));
    ok.func_02050c48(0, 1, -1);
    ok.func_02050c64(0, 1, 2);
    ok.func_18(false);
}

Unk0202fddc::~Unk0202fddc() {
    func_020335d4();
    delete layout;
}

bool Unk0202fddc::func_30() {
    return func_28() && !func_14() && panel.func_38() && (confirm.func_38() || confirm.func_3c()) && !(flags & 0x10);
}

bool Unk0202fddc::func_14() {
    return (flags & 4) != 0;
}

bool Unk0202fddc::func_28() {
    return fade.func_shown();
}

bool Unk0202fddc::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0203161c();
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_34(0x22);
        panel.func_28(0x22);
        back.func_34(0x22);
        back.func_28(0x22);
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x22);
        back.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0202fddc::func_10() {
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
        back.func_30(0x22);
        back.func_2c(0x22);
        confirm.func_1c(0, 0);
        confirm.func_20(-0x146000, -0x23000);
        confirm.func_30(0x22);
        confirm.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk020b9e88::func_1c(Unk020b9e88Track *x, Unk020b9e88Track *y) {
    trackX = x;
    trackY = y;
}

/*
 * 99.72 %: `down` takes r7 and the loop's two pointers r8, r9; the original has
 * the pointers in r7, r8 and `down` in r9.
 */
bool Unk0202fddc::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = yes.func_0c(done);
    if (yes.touch.flags & 8) {
        func_02033728(0);
    }
    done = no.func_0c(done);
    if (no.touch.flags & 8) {
        confirm.func_2c(0x19);
    }
    bool last = ok.func_0c(done);
    if (ok.touch.flags & 8) {
        func_020292c0(owner, mode);
        func_02028eec(owner, mode, data_020b93bc.cur, 0);
    }
    int i;
    bool down;
    if (last || !confirm.func_3c()) {
        down = true;
    } else {
        down = false;
    }
    for (i = 0; i < buttonCount; i++) {
        down = buttons[i].func_0c(down);
        if (buttons[i].touch.flags & 8) {
            if (mode == 0 || (mode == 0x11 && i == 0)) {
                confirm.func_34(0x19);
                confirm.func_28(0x19);
                confirm.func_18(true);
            } else if (mode == 1 || (mode == 0x1b && func_020a7d1c(s1a4))) {
                fade2.timer = fade2.duration;
                fade2.state = 3;
                func_020a1494(func_020a18e4(), 0, 0x10);
                func_020a11f8(func_020a18e4(), 0, 1);
            } else if (mode == 0x19 || mode == 0x13 || mode == 8) {
                if (func_02053940(recipe)) {
                    func_02033728(i);
                } else {
                    confirm.func_34(0x19);
                    confirm.func_28(0x19);
                    confirm.func_18(true);
                }
            } else if (mode == 2) {
                if (keys[0] == 0) {
                    confirm.func_34(0x19);
                    confirm.func_28(0x19);
                    confirm.func_18(true);
                } else {
                    func_02033728(i);
                }
            } else {
                func_02033728(i);
            }
        }
    }
    if (confirm.func_3c()) {
        last = down;
    }
    done = back.func_0c(last);
    if (back.touch.flags & 8) {
        if (mode == 0x1b) {
            data_020b93bc.pending = data_020b93bc.cur;
            data_020b93bc.cur = def;
        }
        func_020292c0(owner, mode);
        func_02028eec(owner, mode, data_020b93bc.cur, 0);
    }
    return done;
}

void Unk0202fddc::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    if (fade2.state == 4) {
        func_02033728(0);
        func_020a122c(func_020a18e4());
        fade2.state = 0;
    }
    fade.func_step();
    fade2.func_step();
    if (fade.state == 1) {
        func_40(false);
    }
    if (flags & 0x10) {
        if (++counter >= limit) {
            counter = 0;
            value++;
            func_020a7ce0(s1b0);
            if (value == 100) {
                flags &= ~0x10;
                marks.func_18(false);
            }
        }
    }
    panel.func_08();
    confirm.func_08();
    back.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_020335d4();
    }
}

static inline Unk020c43a8 *func_player() {
    return &data_020c43a8;
}

static inline Unk0205367c *func_recipe() {
    Unk0205367c *t = (Unk0205367c *)operator new(0x2c);
    if (t != 0) {
        t = func_0205367c(t, data_020b93bc.cur);
    }
    return t;
}

/*
 * 98.69 %: the comparison of an outfit part with the object id reads
 * `cmp id, part` here and `cmp part, id` in the original (operand order, int /
 * u32 id tried); registers of the formatted text at the end of case 0x17.
 */
void Unk0202fddc::func_0203161c() {
    if (flags & 2) {
        return;
    }
    fade2.func_duration(0x11);
    fade2.timer = fade2.duration;
    fade2.state = 2;
    if (count == 0) {
        func_020a7cf0(s19c, false);
    }
    int icon = 0;
    buttonCount = icon;
    int kinds[2] = {0, 0};
    int ids[2] = {0, 0};
    char buf[0x100] = {0};
    Unk0205cf00 *def = data_020b93bc.cur;
    bool flag = false;
    switch (mode) {
    case 0:
        icon = flag;
        if (!func_0205d340(def, 0xef816a84)) {
            buttonCount = flag;
        } else {
            buttonCount = 1;
            keys[0] = 0x07ede381;
            ids[0] = 0xd4d;
            kinds[0] = flag;
        }
        {
            Unk020680d4Cell cell = func_player()->func_14();
            if (cell.pos.unk3 != -1) {
                Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
                if ((*layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000) == 0x8000) {
                    buttonCount = 0;
                    func_020a7cf0(s234, true);
                    func_020a716c(s234, 0xfe9);
                    func_020a7cac(s234, 0x8c000);
                }
            }
        }
        break;
    case 1: {
        buttonCount = 1;
        icon = 2;
        keys[0] = 0x07ede381;
        ids[0] = 0xd4e;
        kinds[0] = icon;
        Unk020081dc outfit = func_020081dc(&data_020c43a8);
        for (int i = 0; i < 6; i++) {
            if (outfit.parts.v[i] == data_020b93bc.cur->id && (u32)(i - 2) <= 1) {
                ids[0] = 0xeef;
                if (func_0209f0a4(&data_020d60c8) == 5) {
                    buttons[0].func_02050838(s5e8, false);
                    buttons[0].func_02050c48(0, 2, -1);
                }
                break;
            }
        }
        {
            Unk020680d4Cell cell = func_player()->func_14();
            if (cell.pos.unk3 != -1) {
                Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
                if ((*layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000) == 0x8000) {
                    buttonCount = 0;
                    func_020a7cf0(s234, true);
                    func_020a716c(s234, 0xfea);
                    func_020a7cac(s234, 0x8c000);
                }
            }
        }
        break;
    }
    case 0x11:
        icon = 2;
        buttonCount = icon;
        ids[0] = 0xd55;
        ids[1] = 0xd56;
        kinds[0] = 0x10;
        kinds[1] = 0x12;
        marks.delay = 9;
        limit = 4;
        break;
    case 0x1b:
        buttonCount = 1;
        ids[0] = 0xd56;
        kinds[0] = 0x12;
        icon = 2;
        break;
    case 2:
        icon = 4;
        if (func_0205d340(def, 0xe9c77f61)) {
            buttonCount = 1;
            ids[0] = 0xd4f;
            kinds[0] = 5;
            keys[0] = flag;
            func_020a716c(s5e4, 0x10d3);
            confirm.func_02051adc(&ok, flag);
            confirm.func_02051adc(0, 1);
            Unk020680d4Cell cell = func_player()->func_14();
            if (cell.pos.unk3 != -1) {
                Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
                if (!(*layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000)) {
                    kinds[0] = icon;
                    keys[0] = 0x07ede381;
                }
            }
        }
        break;
    case 0x1a:
        buttonCount = 1;
        icon = 6;
        break;
    case 0xb:
        icon = 2;
        func_020a6980(back.func_02050a40(flag), 0x99de9fbc);
        buttonCount = 1;
        keys[0] = 0x07ede381;
        ids[0] = 0xd50;
        kinds[0] = 6;
        break;
    case 0xa:
        buttonCount = 1;
        keys[0] = 0x07ede381;
        ids[0] = 0xd52;
        kinds[0] = 0xa;
        icon = 4;
        break;
    case 0xc:
        buttonCount = 1;
        keys[0] = 0x07ede381;
        ids[0] = 0xd53;
        kinds[0] = 0xc;
        icon = 4;
        break;
    case 8:
        func_020a7cf0(s19c, flag);
        icon = 0xc;
        if (func_0205d340(data_020b93bc.cur, 0x3d9aefc0)) {
            buttonCount = 1;
            ids[0] = 0xd51;
            kinds[0] = 8;
            recipe = func_recipe();
            if (!func_02053940(recipe)) {
                kinds[0] = 9;
                buttons[0].func_02050c48(0, -1, -1);
                func_020a716c(s5e4, 0x10b3);
                confirm.func_02051adc(&ok, 0);
                confirm.func_02051adc(0, 1);
            }
            def = func_02053be4(recipe);
            flag = recipe->flags[5];
        } else {
            data_020b93bc.cur = this->def;
        }
        break;
    case 0x19:
        func_020a7cf0(s19c, flag);
        icon = 0xc;
        if (func_0205d340(data_020b93bc.cur, 0x3d9aefc0)) {
            buttonCount = 1;
            ids[0] = 0xd51;
            kinds[0] = 8;
            recipe = func_recipe();
            if (!func_02053940(recipe)) {
                kinds[0] = 9;
                buttons[0].func_02050c48(0, -1, -1);
                func_020a716c(s5e4, 0x10b3);
                confirm.func_02051adc(&ok, 0);
                confirm.func_02051adc(0, 1);
            }
            def = func_02053be4(recipe);
            flag = recipe->flags[5];
            if (def != 0 && (func_0205d340(def, data_020ae7cc[8]) || func_0205d340(def, data_020ae7cc[9]))) {
                if (func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0)->count > 1) {
                    buttonCount = 0;
                    sprintf(buf, func_020a18e4()->func_text(0xfe6));
                    func_020a7cf0(s234, true);
                    func_020a7cac(s234, 0x8c000);
                }
            }
        } else {
            data_020b93bc.cur = this->def;
        }
        break;
    case 0x13:
        func_020a7cf0(s19c, flag);
        icon = 0xe;
        func_020a6980(back.func_02050a40(flag), 0xb988a2f6);
        if (func_0205d340(data_020b93bc.cur, 0x3d9aefc0)) {
            buttonCount = 1;
            ids[0] = 0xd54;
            kinds[0] = icon;
            recipe = func_recipe();
            if (!func_02053940(recipe)) {
                kinds[0] = 0xf;
                buttons[0].func_02050c48(0, -1, -1);
                func_020a716c(s5e4, 0x10b3);
                confirm.func_02051adc(&ok, 0);
                confirm.func_02051adc(0, 1);
            }
            def = func_02053be4(recipe);
            flag = recipe->flags[5];
        } else {
            data_020b93bc.cur = this->def;
        }
        break;
    case 0xd:
    case 0x16:
    case 0x18:
        func_020a7cf0(s19c, flag);
        icon = 0xe;
        data_020b93bc.cur = this->def;
        break;
    case 0x17:
        func_020a7cf0(s19c, flag);
        icon = 0xc;
        if (func_0205d340(data_020b93bc.cur, 0x3d9aefc0)) {
            recipe = func_recipe();
            def = func_02053be4(recipe);
            int textId = 0;
            int key = 0;
            flag = recipe->flags[5];
            if (func_0205d340(data_020b93bc.cur, 0xbc035ef3)) {
                textId = 0xd63;
                key = 0x1c016;
            } else if (func_0205d340(data_020b93bc.cur, 0x799b1313)) {
                textId = 0xd64;
                key = 0x2701d;
            } else if (func_0205d340(data_020b93bc.cur, 0x66e2a1dc)) {
                textId = 0xd65;
                key = 0x48016;
            } else if (func_0205d340(data_020b93bc.cur, 0x9017163a)) {
                textId = 0xd66;
                key = 0x28016;
            } else if (func_0205d340(data_020b93bc.cur, 0x89e11752)) {
                textId = 0xd67;
                key = 0x34016;
            }
            if (textId != 0) {
                Unk020d6240 *system2 = func_020a18e4();
                Unk020d6240 *system = func_020a18e4();
                const char *fmt = system->func_text(0xd62);
                sprintf(buf, fmt, system2->func_text(textId));
                func_020a7cf0(s234, true);
                func_020a7cf0(s23c, true);
                func_020a7cf0(s238, true);
                func_020a6980(s238, func_0206446c(key));
                func_020a69ac(s238, func_020644bc(key));
                int palette = func_020644b0(key);
                Unk02093648 *archive = func_020a18e4()->archive;
                Unk0209487c *file = func_020a18e4()->archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(s238)));
                Unk020916a4 *oam = Unk020916a4::func_02091830();
                int index = func_020a69cc(s238);
                oam->func_0209201c((Unk02095140 *)file, index, palette << 4, func_020a7d44(s238) << 4, 0x10);
                archive = func_020a18e4()->archive;
                func_020a18e4()->archive->func_02093c58(archive->func_02093e9c(func_020a69a4(s238)));
            }
        } else {
            data_020b93bc.cur = this->def;
        }
        break;
    }
    func_020a69ac(back.func_02050a40(0), icon);
    if (mode == 0x1a) {
        func_020a6980(buttons[0].sprite, 0x929195c3);
        buttons[0].func_02050c64(0, 1, 2);
        func_020a716c(buttons[0].func_02050a40(0), 0x74);
        buttons[0].func_18(true);
    } else {
        for (int i = 0; i < buttonCount; i++) {
            buttons[i].func_18(true);
            buttons[i].func_02050c64(kinds[i], -1, kinds[i] + 1);
            func_020a716c(buttons[i].func_02050a40(0), ids[i]);
        }
    }
    if (def != 0) {
        func_02032e24(def);
        func_020322b4(def, flag);
    }
    if (func_020a7d1c(s234)) {
        func_020a78cc(s234, func_020aa040(layout, 0, func_020a7164(s234)), buf);
    }
    flags |= 2;
}

static inline void func_icon(Unk02093648 *archive, Unk020a7c90 *const &s, int key) {
    func_020a6980(s, func_0206446c(key));
    func_020a69ac(s, func_020644bc(key));
    int palette = func_020644b0(key);
    Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(s)));
    Unk020916a4 *oam = Unk020916a4::func_02091830();
    int index = func_020a69cc(s);
    oam->func_0209201c((Unk02095140 *)file, index, palette << 4, func_020a7d44(s) << 4, 0x10);
    archive->func_02093c3c(file);
}

/*
 * 92.20 %: register allocation. The original keeps eight values in registers
 * (e r4, flag r5, shown r6, archive r7, icon r8, script r11) and spills the
 * inline temporaries to the stack, frame 0x11C against 0x110 here. Sixteen
 * declaration orders and int / bool locals tried; the split of `shown` and
 * `got` is a hypothesis (one register in the original).
 */
void Unk0202fddc::func_020322b4(Unk0205cf00 *def, bool flag) {
    int showIcon;
    int showKinds;
    Unk02054dc4 *e;
    bool shown;
    int icon;
    Unk020956f8 *script;
    Unk02093648 *archive = func_020a18e4()->archive;
    int base = 0xd57;
    int order[6] = {0, 1, 2, 3, 4, 5};
    int ids[6] = {base, base + 1, base + 2, base + 3, base + 4, base + 5};
    int values[6] = {0, 0, 0, 0, 0, 0};
    e = func_02054dc4(&data_020bfc9c, def, 0);
    script = def->script;
    shown = true;
    showIcon = shown;
    showKinds = shown;
    icon = func_0205d134(def, 0x9d5bba8e);
    if (icon == -1) {
        icon = 0;
    }
    func_020a716c(s230, func_0205d134(def, 0xbe33d1b8));
    text = func_0205d1b4(def, 0x90dbc63c);
    if (text == 0) {
        text = func_0205d134(def, 0x6a4a2934);
    }
    if (mode == 0x1b) {
        showIcon = false;
        shown = showIcon;
        showKinds = showIcon;
        func_020a7cf0(s19c, showIcon);
        Unk020081dc outfit = func_020081dc(&data_020c43a8);
        for (int i = 0; i < 6; i++) {
            if (outfit.parts.v[i] == def->id) {
                func_020a7cf0(s1a4, true);
                break;
            }
        }
        func_icon(archive, s1a0, icon);
        int value = 0;
        if (e != 0) {
            value = e->count - 1;
        }
        func_0203c254(value, func_020a7d44(s1a0), 0);
        compare.func_18(true);
        func_020a7cf0(stats.func_02051ad0(0xc), true);
        Unk020a7c90 *s = compare.func_02051ad0(0);
        int prev = func_0205d134(this->def, 0x9d5bba8e);
        if (prev == -1) {
            prev = 0;
        }
        func_icon(archive, s, prev);
        s = compare.func_02051ad0(1);
        func_icon(archive, s, icon);
        func_0203c254(func_0205d234(this->def, 0x03e0cdc7, 0x2b3e6dd7), func_020a7d44(s), 0);
    } else if (flag) {
        icon = 0x1a004;
        func_020a716c(s230, 0xd71);
        shown = false;
        text = 0xe51;
    } else if (func_0205d340(def, data_020ae7cc[7]) || func_0205d340(def, data_020ae7cc[10])) {
        order[0] = 2;
        order[1] = 3;
        order[2] = -1;
        order[3] = -1;
        order[4] = -1;
        order[5] = -1;
        func_020a7cf0(s19c, false);
        if (mode != 0x1a && mode != 0x17 && mode != 0x19) {
            Unk020081dc outfit = func_020081dc(&data_020c43a8);
            for (int i = 0; i < 6; i++) {
                if (outfit.parts.v[i] == def->id) {
                    func_020a7cf0(s1a4, true);
                    break;
                }
            }
        }
    } else if (func_0205d340(def, data_020ae7cc[8]) || func_0205d340(def, data_020ae7cc[9])) {
        order[0] = 2;
        order[1] = 3;
        order[2] = -1;
        order[3] = -1;
        order[4] = -1;
        order[5] = -1;
        func_020a7cf0(s19c, false);
        Unk020081dc outfit = func_020081dc(&data_020c43a8);
        for (int i = 0; i < 6; i++) {
            if (outfit.parts.v[i] == def->id) {
                func_020a7cf0(s1a4, true);
                break;
            }
        }
        showIcon = false;
        func_icon(archive, s1a0, icon);
        bool colored = true;
        int value;
        if (e != 0) {
            value = e->count - 1;
        } else {
            value = func_0205d134(def, 0x2b3e6dd7);
        }
        if (recipe != 0) {
            if (func_02053bd8(recipe, 5)->id == def->id) {
                value = func_0205d134(def, 0x2b3e6dd7);
                colored = false;
            }
        }
        func_0203c254(value, func_020a7d44(s1a0), 0);
        if (mode == 0x1a || mode == 0x17 || mode == 0x19) {
            func_020a7cf0(s1a4, false);
            colored = false;
        }
        if (e != 0 && colored) {
            func_020a716c(s228, 0xe5f);
            func_020a7cf0(s228, true);
            func_020a716c(s22c, 0x800004);
            func_020a7cf0(s22c, true);
            s1b0 = s22c;
            func_020a7cf0(s1b4, true);
            this->value = func_fxmul(func_fxdiv(FX32(e->unk8), 0xff000), 0x64000) >> 12;
        }
    }
    func_020a6980(s1a0, func_0206446c(icon));
    func_020a69ac(s1a0, func_020644bc(icon));
    if (showIcon) {
        int palette = func_020644b0(icon);
        Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(s1a0)));
        Unk020916a4 *oam = Unk020916a4::func_02091830();
        int index = func_020a69cc(s1a0);
        oam->func_0209201c((Unk02095140 *)file, index, palette << 4, func_020a7d44(s1a0) << 4, 0x10);
        archive->func_02093c3c(file);
    }
    bool got = false;
    if (shown) {
        if (script != 0) {
            Unk0205d6b8 params;
            func_0205d608(&params, script);
            if (func_0205d704(&params) != 6) {
                got = true;
                for (int i = 0; i < 6; i++) {
                    if (order[i] >= 0) {
                        func_020a716c(stats.func_02051ad0(i * 2), ids[order[i]]);
                        values[i] = func_0205d6fc(&params, order[i]);
                    }
                }
            }
            func_0205d6dc(&params);
        }
    }
    if (got) {
        showKinds = false;
        stats.func_18(true);
        for (int i = 0; i < 6; i++) {
            if (order[i] < 0) {
                func_020a7cf0(stats.func_02051ad0(i * 2), false);
                func_020a7cf0(stats.func_02051ad0(i * 2 + 1), false);
            }
        }
    }
    if (showKinds) {
        kinds.func_18(true);
        func_020a7c90(s1a0, 0x31000);
        func_020a7cac(s1a0, 0x1c000);
        func_020a7c90(s19c, 0x31000);
        func_020a7cac(s19c, 0x40000);
    }
    panel.func_34(0x22);
    back.func_34(0x22);
    confirm.func_34(0x19);
    func_020aa06c(layout, true);
    if (got) {
        for (int i = 0; i < 6; i++) {
            Unk020a78cc *s = (Unk020a78cc *)stats.func_02051ad0(i * 2 + 1);
            if (s->canvas != 0 && order[i] >= 0) {
                if (values[i] > 0) {
                    func_020a78cc(s, func_020aa040(layout, 0, func_020a7164(s)), "+%d", values[i]);
                } else {
                    func_020a78cc(s, func_020aa040(layout, 0, func_020a7164(s)), "%d", values[i]);
                }
            }
        }
    }
    if (showKinds) {
        Unk020d6240 *system = func_020a18e4();
        Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(s1a8));
        func_020a78cc(s1a8, font, system->func_text(text));
    }
}

void Unk0202fddc::func_02032e24(Unk0205cf00 *def) {
    Unk020c3fc4 *db;
    bool found;
    int n;
    int id = def->id;
    n = 0;
    Unk02010b8c view;
    int list[3];
    if (func_0205d340(def, 0xef276208)) {
        func_02010b8c(&view, def);
        if (func_02010c2c(&view) && func_02010bf8(&view)) {
            list[0] = 2;
        } else if (func_02010c2c(&view)) {
            list[0] = 0;
        } else {
            list[0] = 1;
        }
        int key = func_02010bbc(&view);
        n += 3;
        if (key == 0x9e3e1df3 || key == 0x70623103) {
            list[1] = 4;
        } else {
            list[1] = 3;
        }
        if (key == 0x9e3e1df3 || key == 0x694ac647) {
            list[2] = 5;
        } else {
            list[2] = 6;
        }
        func_02010ba8(&view);
    }
    if (func_0205d340(def, 0xc07f23df) || func_0205d340(def, 0xf9462fe2) || func_0205d340(def, 0xcf78e68b)) {
        list[n] = 0xb;
        n++;
    }
    if (func_0205d340(def, 0xc17e54bd)) {
        list[n] = 0xc;
        n++;
    }
    if (func_0205d340(def, 0x2514c1ab)) {
        list[n] = 0xe;
        n++;
    }
    if (func_0205d340(def, 0x31b3a4ac)) {
        list[n] = 0x11;
        n++;
    }
    if (func_0205d340(def, 0xc17e4108)) {
        list[n] = 0x10;
        n++;
    }
    if (func_0205d340(def, 0x03e0cdc7)) {
        list[n] = 0xd;
        n++;
    }
    db = &data_020c3fc4;
    found = false;
    if (func_0205d340(def, 0x3b4942ae)) {
        list[n] = 0xf;
        n++;
        found = true;
    }
    if (!found && func_0205d340(def, 0xc4656ed7)) {
        Unk0205cf00 *rec = 0;
        while ((rec = func_0205f714(db, 0x1e474fc5, rec)) != 0 && !found) {
            if (func_0205d340(rec, 0x146126e3) && func_02033454(0xc6fb63e3, rec, id)) {
                list[n] = 0xf;
                found = true;
                n++;
            }
        }
    }
    if (!found && func_0205d340(def, 0xc4656ed7)) {
        Unk0205cf00 *rec = 0;
        while ((rec = func_0205f714(db, 0x071d9208, rec)) != 0 && !found) {
            if (func_0205d340(rec, 0x146126e3) && func_02033454(0xcb5a6942, rec, id)) {
                list[n] = 0xf;
                found = true;
                n++;
            }
        }
    }
    if (!found &&
        (func_0205d340(def, 0x0eb64f04) || func_0205d340(def, 0x8768cec0) || func_0205d340(def, 0xfbc8ffaa) ||
         func_0205d340(def, 0xc4656ed7))) {
        Unk0205cf00 *rec = 0;
        while ((rec = func_0205f714(db, 0x16bc2f6e, rec)) != 0 && !found) {
            if (func_0205d340(rec, 0x146126e3) && func_02033454(0xcb5a6942, rec, id)) {
                list[n] = 0xf;
                found = true;
                n++;
            }
        }
    }
    if (!found && (func_0205d340(def, 0xe3549bc4) || func_0205d340(def, 0x8768cec0))) {
        Unk0205cf00 *rec = 0;
        while ((rec = func_0205f714(db, 0x3b4942ae, rec)) != 0 && !found) {
            if (func_0205d340(rec, 0x146126e3) && func_02033454(0xe613e6d9, rec, id)) {
                list[n] = 0xf;
                found = true;
                n++;
            }
        }
    }
    bool used = false;
    if (func_02033544(id, 0xad4b65f7)) {
        list[n] = 7;
        n++;
        used = true;
    }
    if (!used && func_02033544(id, 0x5f291f8d)) {
        list[n] = 8;
        n++;
        used = true;
    }
    if (!used && func_02033544(id, 0xe780812c)) {
        list[n] = 9;
        n++;
        used = true;
    }
    if (!used && func_02033544(id, 0x2dfa05df)) {
        list[n] = 0xa;
        n++;
    }
    if (n > 0) {
        icons.func_18(true);
    }
    for (int i = 0; i < n; i++) {
        func_020a69ac(icons.func_02051ad0(i), list[i]);
    }
    if (n >= 3) {
        return;
    }
    for (; n < 3; n++) {
        func_020a7cf0(icons.func_02051ad0(n), false);
    }
}

/* 99.33 %: script, id and the constant 1 take r6, r4, r5 (r4, r5, r6 in the original). */
bool Unk0202fddc::func_02033454(int key, Unk0205cf00 *def, int id) {
    Unk020956f8 *script = def->script;
    bool found = false;
    Unk02099c78Block *block = script->func_020957ec(key);
    if (block == 0) {
        return found;
    }
    Unk02099c78Op *ops = script->func_02095794();
    for (int i = 0; i < block->count && !found; i++) {
        Unk02099c78Op op = ops[block->start + i];
        if (op.arg == 0xe13d12b8) {
            Unk02099c78Value *values = &script->func_02095ab0()[op.a];
            int j = 0;
            int n = op.b;
            for (; j < n && !found; j++) {
                Unk02099c78Value value = values[j];
                if (value.unk0 == 0x35c7a149 && id == value.unk4) {
                    found = true;
                }
            }
        }
    }
    return found;
}

bool Unk0202fddc::func_02033544(int id, int key) {
    Unk020c3fc4 *db = &data_020c3fc4;
    Unk0205cf00 *rec = func_0205f714(db, key, 0);
    while (rec != 0) {
        Unk0205367c t;
        func_0205367c(&t, rec);
        if (id == func_02053bd8(&t, 5)->id && t.flags[5] == 0) {
            return true;
        }
        rec = func_0205f714(db, key, rec);
    }
    return false;
}

void Unk0202fddc::func_020335d4() {
    if (!(flags & 2)) {
        return;
    }
    if (recipe != 0) {
        operator delete(recipe);
        recipe = 0;
    }
    data_020b93bc.cur = 0;
    func_020aa06c(layout, false);
    flags &= ~2;
}

static void *func_02033628(u32 id, void *user) {
    Unk0202fddc *self = (Unk0202fddc *)user;
    switch (id - 0x800000) {
    case 3:
        sprintf(self->num, "%d", self->count);
        return self->num;
    case 4:
        sprintf(self->num, "%d%", self->value);
        static const int frames = 0x3c000;
        func_020a69ac(self->s1b4, func_fxmul(func_fxdiv(FX32(self->value), 0x64000), frames) >> 12);
        return self->num;
    }
    return (void *)func_020a18e4()->func_text(id);
}

void func_02033718(Unk0205cf00 *def) {
    data_020b93bc.cur = def;
}

/* 98.72 %: this, index and e take r5, r4, r8 (r6, r5, r4 in the original). */
void Unk0202fddc::func_02033728(int index) {
    Unk02054dc4 *e = func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0);
    switch (mode) {
    case 0: {
        if (data_020b93bc.cur->script->func_020957ec(keys[index]) != 0) {
            func_0205d39c(data_020b93bc.cur, keys[index]);
        }
        Unk0205d6b8 params;
        func_0205d608(&params, data_020b93bc.cur->script);
        for (int i = 0; i < 6; i++) {
            func_020662c8(&data_020c43a8, i, func_0205d6fc(&params, i));
        }
        Unk02054dc4 *entry = func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0);
        func_02054cf0(&data_020bfc9c, entry, 0);
        if (entry->count != 0) {
            confirm.func_2c(0x19);
            if (count != entry->count) {
                count = entry->count;
                func_020a7ce0(s19c);
            }
        } else {
            count = 0;
            func_020a7ce0(s19c);
            buttons[index].flags |= 8;
            func_020292c0(owner, mode);
            func_02028eec(owner, mode, data_020b93bc.cur, 0);
        }
        func_02055dd8(&func_0206bce0()->guide);
        func_0205d6dc(&params);
        return;
    }
    case 1: {
        Unk020081dc outfit = func_020081dc(&data_020c43a8);
        for (int i = 0; i < 6; i++) {
            if (func_0205d340(data_020b93bc.cur, data_020aefe8[i])) {
                if ((u32)i <= 1) {
                    outfit.colors.v[i] = e->count - 1;
                    outfit.parts.v[i] = data_020b93bc.cur->id;
                } else if (outfit.parts.v[i] == data_020b93bc.cur->id) {
                    if (i == 3) {
                        outfit.parts.v[i] = 0;
                    } else if (i == 2) {
                        outfit.parts.v[i] = 0x79a1e22e;
                    }
                } else {
                    outfit.parts.v[i] = data_020b93bc.cur->id;
                }
                break;
            }
        }
        func_020670fc(&data_020c43a8, &outfit);
        func_020292c0(owner, mode);
        func_02028eec(owner, mode, data_020b93bc.cur, 0);
        return;
    }
    case 0x1b: {
        Unk02054dc4 *entry = func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0);
        entry->count = func_0205d234(def, 0x03e0cdc7, 0x2b3e6dd7) + 1;
        func_02054cb4(&data_020bfc9c, def->id, 0);
        func_020292c0(owner, 0x11);
        func_02028eec(owner, 0x11, data_020b93bc.cur, 0);
        func_0205d39c(func_0205f6f8(&data_020c3fc4, 0x8194f606), 0x7cac1ac7);
        if (!func_020a7d1c(s1a4)) {
            return;
        }
        Unk020081dc outfit = func_020081dc(&data_020c43a8);
        for (int i = 0; i < 6; i++) {
            if (func_0205d340(data_020b93bc.cur, data_020aefe8[i])) {
                outfit.colors.v[i] = entry->count - 1;
                break;
            }
        }
        func_020670fc(&data_020c43a8, &outfit);
        return;
    }
    case 0x11:
        if (index == 0) {
            confirm.func_2c(0x19);
            func_02054dc4(&data_020bfc9c, data_020b93bc.cur, 0)->unk8 = 0xff;
            func_0205d39c(func_0205f6f8(&data_020c3fc4, 0x8194f606), 0xda0ea3b9);
            if (value != 100) {
                counter = 0;
                marks.func_0204fdb4();
                marks.func_18(true);
                flags |= 0x10;
            }
        } else {
            data_020b93bc.pending = data_020b93bc.cur;
            func_020292c0(owner, 0x1b);
        }
        return;
    case 0x1a:
        func_020292c0(owner, mode);
        func_02028eec(owner, mode, data_020b93bc.cur, 0);
        return;
    case 0x19:
        if (data_020be41c == 0xbc035ef3) {
            switch (func_02053b84(recipe)) {
            case 0x0cc8fc7d:
                func_02055220(&func_0206bce0()->guide, 0x19, 1);
                break;
            case 0xd48c3ad3:
                func_02055220(&func_0206bce0()->guide, 0x20, 1);
                break;
            default:
                func_02055220(&func_0206bce0()->guide, 0x15, 0);
                break;
            }
        } else if (data_020be41c == 0x9017163a) {
            switch (func_02053b84(recipe)) {
            case 0x57eb1cd7:
                func_02055220(&func_0206bce0()->guide, 0xe, 0);
                break;
            case 0x291e57a4:
                func_02055220(&func_0206bce0()->guide, 0x10, 2);
                break;
            case 0x0cc8fc7d:
                func_02055220(&func_0206bce0()->guide, 0xf, 1);
                break;
            case 0xd48c3ad3:
                func_02055220(&func_0206bce0()->guide, 0xd, 1);
                break;
            case 0xf229ab99:
                func_02055220(&func_0206bce0()->guide, 0xe, 0);
                break;
            default:
                func_02055220(&func_0206bce0()->guide, 0xc, 0);
                break;
            }
        }
        func_020539b0(recipe);
        func_020292c0(owner, 0x1d);
        func_02028eec(owner, 0x1d, data_020b93bc.cur, 0);
        return;
    case 0x13:
        func_020539b0(recipe);
        func_020292c0(owner, 0x1e);
        func_02028eec(owner, 0x1e, data_020b93bc.cur, 0);
        return;
    case 8:
    case 0xa:
    case 0xb:
    case 0xc:
        data_020b93bc.pending = data_020b93bc.cur;
        owner->func_18();
        return;
    case 2:
        if (data_020b93bc.cur->script->func_020957ec(keys[index]) != 0) {
            func_0205d39c(data_020b93bc.cur, keys[index]);
        }
        owner->func_18();
        return;
    }
}

Unk0205cf00 *func_02033e88() {
    Unk0205cf00 *def = data_020b93bc.pending;
    data_020b93bc.pending = 0;
    return def;
}

void func_02033ea0(Unk0205cf00 *def) {
    data_020b93bc.pending = def;
}

bool Unk0202fddc::func_34() {
    return true;
}

bool Unk0202fddc::func_2c() {
    return fade.func_hidden();
}

void Unk0202fddc::func_1c() {
    flags &= ~4;
}
