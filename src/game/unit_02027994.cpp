/*
 * Unit 0x02027994-0x02029B80: the survival guide (Unk02027994, 0x630 bytes,
 * vtable 0x020B9218), the owner of the guide pages. Its strings name it
 * (GROUP_SE_COMMON SE_OPEN_SURVIVAL_GUIDE at 0x020B91C0 and SE_CLOSE at
 * 0x020B91E8). It draws the eight tabs, the back button, the panel and the six
 * need meters, and func_020292e4 builds the page of the current mode.
 *
 * Bounds: hypothesis. The start is the constructor, after the screen ending at
 * func_0202798c; the end is the object text screen (unit_02029B80.cpp). `.data`
 * holds the two sound names and this class's vtable with its header, `.bss` the
 * page to open on data_020be418. Real file name unknown.
 *
 * It holds the kept copies of the widget base slots 12, 13, 16 and 17 (0x02028C7C,
 * 0x020283A4, 0x02028E58, 0x02028E6C) and of the button's func_10 (0x02029B54),
 * after their first users: written as plain definitions, as slot 7 in
 * unit_0202FDDC.cpp.
 *
 * The pages see this class as Unk0203c188Owner, and call the functions below by
 * their C names.
 *
 * Not complete: func_020299ec is below 100 % (comment above it).
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"
#include "game/unk_sim.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An object of the database. */
struct Unk0205cf00;
struct Unk020be420;

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

    u32 *func_tile(u32 x, u32 y) {
        return &tiles[y * info->width + x];
    }
};

/* The survival guide animation of the player (unit_02055118.cpp): opaque here. */
struct Unk02055118 {
    int state;
};

/* The main game state (func_0206bce0): only its guide. */
struct Unk0206bcf0 {
    void func_0206ea00(int a, int b);

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

/* The game settings (data_020d60c8): only the field used here. */
struct Unk020d60c8 {
    u8 unk0[0x15c];
    u8 unk15c;
};

/* The object or the choice to show first (unit_0203C2E8.cpp). */
struct Unk020b9648 {
    Unk0205cf00 *def;
    int index;
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3ba4 data_020c3ba4;
extern Unk020b9648 data_020b9648;

bool func_02097298(int key);

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
u32 func_0209a32c(const u32 *name, int a, int b);
Unk0206bcf0 *func_0206bce0();
void func_0205515c(Unk02055118 *p, int a);
void func_02055198(Unk02055118 *p);
void func_02055220(Unk02055118 *p, int state, int count);
int func_0206647c(Unk020c43a8 *p, int i);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
Unk0205cf00 *func_02033e88();
bool func_0203e314(u32 key);
int func_02038b48(Unk0205cf00 *def);
void func_02038b38(Unk0205cf00 *def);
bool func_0205d340(Unk0205cf00 *def, u32 key);
void func_0202cdc0(Unk0205cf00 *def);
void func_02035fc0(Unk0205cf00 *def);
void func_0202e0dc(Unk0205cf00 *def);
void func_02033718(Unk0205cf00 *def);
void func_0202fd18(Unk0205cf00 *def);
void func_0202fd28(Unk020be420 *p);
void func_0202ae50(Unk0205cf00 *def);
void func_0203b388(Unk0205cf00 *def);
}

/* The pages (only their constructors and sizes are needed). */
class Unk02021cbc {
public:
    Unk02021cbc(Unk0203c188Owner *owner, u32 hash);
    u8 unk0[0x198];
};

class Unk02035fec {
public:
    Unk02035fec(Unk0203c188Owner *owner, int mode);
    u8 unk0[0x11fc];
};

class Unk0203b3b8 {
public:
    Unk0203b3b8(Unk0203c188Owner *owner, int mode);
    u8 unk0[0x28c];
};

class Unk0202aef4 {
public:
    Unk0202aef4(Unk0203c188Owner *owner);
    u8 unk0[0x8ec];
};

class Unk02038bcc {
public:
    Unk02038bcc(Unk0203c188Owner *owner, int mode);
    u8 unk0[0xf5c];
};

class Unk02033ee0 {
public:
    Unk02033ee0(Unk0203c188Owner *owner, bool mode);
    u8 unk0[0xa6c];
};

class Unk0203c2e8 {
public:
    Unk0203c2e8(Unk0203c188Owner *owner);
    u8 unk0[0x11a0];
};

class Unk0203ecd4 {
public:
    Unk0203ecd4(Unk0203c188Owner *owner);
    u8 unk0[0x428];
};

class Unk02029b80 {
public:
    Unk02029b80(Unk0203c188Owner *owner);
    u8 unk0[0x314];
};

class Unk0202cdf0 {
public:
    Unk0202cdf0(Unk0203c188Owner *owner, bool a, int b);
    u8 unk0[0x7b0];
};

class Unk0202fddc {
public:
    Unk0202fddc(Unk0203c188Owner *owner, int back);
    u8 unk0[0x648];
};

class Unk0202e0ec {
public:
    Unk0202e0ec(Unk0203c188Owner *owner, int mode);
    u8 unk0[0x6d4];
};

class Unk0203fa44 {
public:
    Unk0203fa44(Unk0203c188Owner *owner);
    u8 unk0[0x7b0];
};

class Unk02027994 : public Unk020a07d4 {
public:
    Unk02027994(int type);
    virtual ~Unk02027994();
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
    virtual bool func_30();
    virtual bool func_34();
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_02028260();
    void func_02028580();
    void func_020299ec(int page);

    Unk020a07d4Timer fade;
    u32 flags;
    u8 unk10;
    int type;
    int page;
    int next;
    int prev;
    Unk0203c188 *screen;
    Unk0203c188 *old;
    int pending;
    Unk020a9d58 *layout1;
    Unk020a9d58 *layout0;
    Unk02050640 button;
    Unk02051704 panel;
    Unk02050640 tabs[8];
    Unk0204eb78 meters[6];
    u8 unk628;
    int unk62c;
};

extern "C" {
Unk0205cf00 *func_02028ebc();
void func_02028ec8(Unk02027994 *o, u8 a, int b);
void func_02028edc(Unk02027994 *o, u32 key);
void func_02028eec(Unk02027994 *o, int mode, Unk0205cf00 *def, Unk020be420 *p);
void func_020290f0(Unk02027994 *o, bool show);
void func_02029128(Unk02027994 *o, bool on);
void func_0202918c(Unk02027994 *o);
void func_020291e4(Unk02027994 *o);
void func_0202923c(Unk02027994 *o);
void func_020292c0(Unk02027994 *o, int page);
void func_020292e4(Unk02027994 *o);
}

int data_020be418;

static inline Unk020c43a8 *func_player() {
    return &data_020c43a8;
}

Unk02027994::Unk02027994(int type)
    : flags(0), unk10(0), type(type), page(type), next(type), prev(-1), screen(0), old(0), pending(-1), unk628(0),
      unk62c(0) {
    {
        Unk020a7af4Entry entries[0x1e];
        Unk020a7af4 names(entries, 0x1e);

        layout0 = new Unk020a9d58(func_020a18e4()->archive, 0);
        func_020aba38(func_020a18e4()->archive, 0x06c236ef, layout0, &names);
        func_020a9db8(layout0, func_020a154c, 0);

        button.func_02050838(func_020aa040(layout0, 0xb, func_020a7b50(&names, 0xc2f94842)), false);
        button.func_020508a4(func_020aa040(layout0, 1, func_020a7b50(&names, 0x060bbd76)));
        button.func_02050c48(0, 1, -1);
        button.func_02050c64(0, -1, 2);

        for (int i = 0; i < 8; i++) {
            tabs[i].func_02050838(func_020aa040(layout0, 0xb, func_020a7b50(&names, 0x14d9f436 + i)), false);
            tabs[i].func_02050c48(0, 1, -1);
            tabs[i].func_02050c64(i * 2, -1, i * 2 + 1);
            tabs[i].func_020508a4(func_020aa040(layout0, 1, func_020a7b50(&names, 0x18d3d038 + i)));
        }

        Unk020a7c90 *sprite = func_020aa040(layout0, 2, func_020a7b50(&names, 0x4d1ce715));
        func_020a7c90(sprite, -0x23000);
        panel.func_14(-0x23000, func_020a7cc0(sprite));
        panel.func_02051804(1);
        panel.func_02051858(sprite);
    }
    {
        Unk020a7af4Entry entries[0x1e];
        Unk020a7af4 names(entries, 0x1e);

        layout1 = new Unk020a9d58(func_020a18e4()->archive, 1);
        func_020aba38(func_020a18e4()->archive, 0x2794b249, layout1, &names);

        for (int i = 0; i < 6; i++) {
            meters[i].func_0204ebd4(1);
            meters[i].func_0204ebe4(func_020aa040(layout1, 1, func_020a7b50(&names, 0x1f19df27 + i)));
            meters[i].func_0204ec10(func_020aa040(layout1, 1, func_020a7b50(&names, 0xc56fae8c + i)));
            meters[i].func_0204ebdc(func_020aa040(layout1, 1, func_020a7b50(&names, 0x0e5f7d4a + i)));
        }
    }
}

Unk02027994::~Unk02027994() {
    func_02028580();
    delete screen;
    delete old;
    delete layout1;
    delete layout0;
}

bool Unk02027994::func_30() {
    bool done;
    if (screen == 0) {
        done = false;
    } else {
        done = screen->func_30();
    }
    if (func_28() && !func_14() && done) {
        return true;
    }
    return false;
}

bool Unk02027994::func_14() {
    return (flags & 4) != 0;
}

void Unk02027994::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
    if (type == 0xf) {
        type = data_020be418;
        page = data_020be418;
        next = data_020be418;
        data_020be418 = 0;
    }
    func_020292e4(this);
    screen->func_40(false);
    func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_OPEN_SURVIVAL_GUIDE", 0, 0), 0x7f, 0);
    func_020a14e0(func_020a18e4(), 0);
    Unk0206bcf0 *game = func_0206bce0();
    if (unk628) {
        func_0205515c(&game->guide, unk62c);
    }
}

bool Unk02027994::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    unk10 = a;
    fade.func_duration(0x10);
    fade.timer = 0;
    fade.state = 0;
    func_02028260();
    flags |= 0x400;
    return false;
}

bool Unk02027994::func_28() {
    return fade.func_shown();
}

bool Unk02027994::func_2c() {
    bool done = false;
    if (fade.func_hidden() && screen->func_2c()) {
        done = true;
    }
    return done;
}

bool Unk02027994::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.timer = fade.duration;
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a11f8(func_020a18e4(), 2, 1);
    func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_CLOSE_SURVIVAL_GUIDE", 0, 0), 0x7f, 0);
    return false;
}

void Unk02027994::func_02028260() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout1, true);
    func_020aa06c(layout0, true);
    for (int i = 0; i < 8; i++) {
        int x = i * 2 + 0xdf;
        int y = i * 0x18 - 2;
        int fx = FX32(x);
        int fy = FX32(y);
        tabs[i].func_14(fx, fy);
        tabs[i].func_02050a4c(i + 1);
        func_020a7c90(tabs[i].icon, fx);
        func_020a7cac(tabs[i].icon, fy + 0x8000);
    }
    func_020299ec(type);
    if (type == 4) {
        func_0202918c(this);
        panel.func_34(0x22);
    }
    flags |= 2;
}

void Unk020b9e88::func_34(int value) {
    duration = value;
    if (timer > duration) {
        timer = duration;
    }
    timer = 0;
    state = 5;
    Unk020b9e88Track *track = trackX;
    if (track != 0) {
        int x = func_sample(track, timer, duration);
        func_14(x, func_10()->y);
    }
    track = trackY;
    if (track != 0) {
        int y = func_sample(track, timer, duration);
        func_14(func_10()->x, y);
    }
}

void Unk02027994::func_02028580() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout1, false);
    func_020aa06c(layout0, false);
    flags &= ~2;
}

bool Unk02027994::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    bool first = done;
    if (!done && page == 4 && type == 4) {
        u8 flag = data_020d60c8.unk15c;
        if ((flag && func_02097298(6)) || (!flag && func_02097298(10))) {
            done = true;
            func_18();
        }
    }
    if (!done && func_02097298(2) && page != 4 && page != 0x12) {
        done = true;
        func_18();
    }
    if (flags & 8) {
        done = true;
    }
    for (int i = 0; i < 8; i++) {
        done = tabs[i].func_0c(done);
        if ((tabs[i].touch.flags & 8) && page != i) {
            next = i;
            if (i == 4) {
                old = (Unk0203c188 *)new Unk02021cbc((Unk0203c188Owner *)this, 0x4c6bad83);
                old->func_08();
                old->func_40(true);
            }
            if (page == 4) {
                func_0202923c(this);
                screen->func_40(true);
                screen->func_18();
                old = screen;
                screen = 0;
                func_020292e4(this);
            }
            func_020299ec(i);
        }
    }
    if ((flags & 8) && !first) {
        done = false;
    }
    done = button.func_0c(done);
    if (button.touch.flags & 8) {
        func_18();
    }
    return done;
}

void Unk02027994::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    button.func_08();
    panel.func_08();
    for (int i = 0; i < 8; i++) {
        tabs[i].func_08();
    }
    meters[0].func_0204ec2c(func_0206647c(&data_020c43a8, 0) / 39062);
    meters[1].func_0204ec2c(func_0206647c(&data_020c43a8, 1) / 39062);
    meters[2].func_0204ec2c(func_0206647c(&data_020c43a8, 4) / 39062);
    meters[3].func_0204ec2c(func_0206647c(&data_020c43a8, 2) / 39062);
    meters[4].func_0204ec2c(func_0206647c(&data_020c43a8, 3) / 39062);
    meters[5].func_0204ec2c(func_0206647c(&data_020c43a8, 5) / 39062);
    for (int i = 0; i < 6; i++) {
        meters[i].func_0204ec44();
    }
    if (flags & 0x10) {
        if (flags & 0x200) {
            panel.func_28(0x22);
            flags &= ~0x200;
        }
        if (panel.func_44() && next != 4) {
            if (page == next) {
                panel.func_28(0x22);
            } else {
                flags |= 0x200;
            }
        }
        if (panel.func_40()) {
            flags &= ~0x10;
        }
    } else if (panel.func_44()) {
        panel.func_30(0x22);
    }
    func_020aa158(layout1);
    func_020aa158(layout0);
    if (old != 0 && !func_020a0b8c(data_020d6240.unk8, old)) {
        delete old;
        old = 0;
    }
    if (page != next) {
        if (func_30()) {
            screen->func_40(true);
            screen->func_18();
            func_0202923c(this);
        }
        if (!func_020a0b8c(data_020d6240.unk8, screen)) {
            func_020292e4(this);
            Unk0206bcf0 *game = func_0206bce0();
            if (game->guide.state == 2) {
                func_02055220(&game->guide, 3, 0);
            }
        }
    }
    if (flags & 0x400) {
        if (!(flags & 0x20)) {
            func_020a1494(func_020a18e4(), 0, 0x10);
            func_020a11f8(func_020a18e4(), 0, 0);
        }
        if (!(flags & 0x40)) {
            func_020a1494(func_020a18e4(), 1, 0x10);
            func_020a11f8(func_020a18e4(), 1, 0);
        }
        flags &= ~0x400;
    }
    if (fade.state == 4) {
        func_02028580();
        int id = pending;
        if (id != -1) {
            func_0206bce0()->func_0206ea00(id, 1);
            func_02055198(&func_0206bce0()->guide);
            pending = -1;
        }
    }
}

void Unk020b9e88::func_30(int value) {
    duration = value;
    if (timer > duration) {
        timer = duration;
    }
    timer = duration;
    state = 2;
    Unk020b9e88Track *track = trackX;
    if (track != 0) {
        int x = func_sample(track, timer, duration);
        func_14(x, func_10()->y);
    }
    track = trackY;
    if (track != 0) {
        int y = func_sample(track, timer, duration);
        func_14(func_10()->x, y);
    }
}

bool Unk020b9e88::func_40() {
    return state == 1;
}

bool Unk020b9e88::func_44() {
    return state == 4;
}

void Unk02027994::func_18() {
    flags |= 4;
    screen->func_40(false);
    screen->func_18();
}

Unk0205cf00 *func_02028ebc() {
    return func_02033e88();
}

void func_02028ec8(Unk02027994 *o, u8 a, int b) {
    o->unk628 = a;
    o->unk62c = b;
}

void func_02028edc(Unk02027994 *o, u32 key) {
    func_0203e314(key);
}

void func_02028eec(Unk02027994 *o, int mode, Unk0205cf00 *def, Unk020be420 *p) {
    if (def == 0) {
        return;
    }
    switch (mode) {
    case 15: {
        int found = 1;
        switch (func_02038b48(def)) {
        case 0:
            data_020be418 = 0;
            break;
        case 1:
            data_020be418 = found;
            break;
        case 2:
            data_020be418 = 2;
            break;
        default:
            found = 0;
            break;
        }
        if (found) {
            func_02038b38(def);
            return;
        }
        if (func_0205d340(def, 0x99a2c231)) {
            data_020be418 = 7;
            return;
        }
        if (func_0205d340(def, 0x3d9aefc0) && !func_0205d340(def, 0x69a133c5)) {
            data_020be418 = 6;
            data_020b9648.def = def;
            return;
        }
        data_020be418 = 0;
        return;
    }
    case 0:
    case 1:
    case 2:
    case 17:
        func_02038b38(def);
        return;
    case 3:
        func_0202cdc0(def);
        return;
    case 6:
    case 16:
        data_020b9648.def = def;
        return;
    case 5:
    case 9:
        func_02035fc0(def);
        return;
    case 8:
    case 19:
    case 23:
    case 24:
    case 25:
        func_0202e0dc(def);
        return;
    case 21:
        func_02033718(def);
        return;
    case 13:
    case 14:
    case 22:
    case 29:
    case 30:
        func_0202fd18(def);
        func_0202fd28(p);
        return;
    case 20:
        func_0202ae50(def);
        return;
    case 10:
    case 11:
    case 12:
    case 26:
    case 27:
        func_0203b388(def);
        return;
    }
}

void func_020290f0(Unk02027994 *o, bool show) {
    for (int i = 0; i < 8; i++) {
        o->tabs[i].func_18(show);
    }
}

void func_02029128(Unk02027994 *o, bool on) {
    if (on) {
        o->flags |= 8;
    } else {
        o->flags &= ~8;
    }
    for (int i = 0; i < 8; i++) {
        if (i != o->page) {
            if (on) {
                o->tabs[i].flags |= 8;
            } else {
                o->tabs[i].flags &= ~8;
            }
        }
    }
}

void func_0202918c(Unk02027994 *o) {
    o->flags &= ~0x10;
    o->panel.func_20(0x100000, -0x23000);
    o->panel.func_30(0x22);
    o->panel.func_2c(0x22);
}

void func_020291e4(Unk02027994 *o) {
    o->flags &= ~0x10;
    o->panel.func_20(0x100000, -0x23000);
    o->panel.func_34(0x22);
    o->panel.func_28(0x22);
}

void func_0202923c(Unk02027994 *o) {
    o->flags |= 0x10;
    o->panel.func_20(0xffeba000, -0x23000);
    if (o->page == 4) {
        o->panel.func_34(0x22);
        o->flags |= 0x200;
    } else {
        o->panel.func_30(0x22);
        o->panel.func_2c(0x22);
    }
}

void func_020292c0(Unk02027994 *o, int page) {
    if (page != -1) {
        o->next = page;
    } else {
        o->func_18();
    }
}

void func_020292e4(Unk02027994 *o) {
    delete o->screen;
    o->screen = 0;
    o->prev = o->page;
    o->page = o->next;
    Unk0203c188Owner *owner = (Unk0203c188Owner *)o;
    switch (o->page) {
    case 0:
        if (o->flags & 0x80) {
            o->screen = (Unk0203c188 *)new Unk02035fec(owner, 0);
        } else {
            Unk020680d4Cell cell = func_player()->func_14();
            if (cell.pos.unk3 == -1) {
                o->screen = (Unk0203c188 *)new Unk02035fec(owner, 0);
            } else {
                Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
                if ((*layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000) == 0x8000) {
                    o->screen = (Unk0203c188 *)new Unk0203b3b8(owner, 0);
                    o->page = 0x1c;
                    o->next = 0x1c;
                    o->flags |= 0x80;
                } else {
                    o->screen = (Unk0203c188 *)new Unk02035fec(owner, 0);
                }
            }
        }
        break;
    case 1:
        if (o->flags & 0x100) {
            o->screen = (Unk0203c188 *)new Unk02035fec(owner, 1);
        } else {
            Unk020680d4Cell cell = func_player()->func_14();
            if (cell.pos.unk3 == -1) {
                o->screen = (Unk0203c188 *)new Unk02035fec(owner, 1);
            } else {
                Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
                if ((*layer->func_tile(cell.xy.x, cell.xy.y) & 0xc000) == 0x8000) {
                    o->screen = (Unk0203c188 *)new Unk0203b3b8(owner, 1);
                    o->page = 0x1c;
                    o->next = 0x1c;
                    o->flags |= 0x100;
                } else {
                    o->screen = (Unk0203c188 *)new Unk02035fec(owner, 1);
                }
            }
        }
        break;
    case 2:
        o->screen = (Unk0203c188 *)new Unk02035fec(owner, 2);
        break;
    case 3:
        o->screen = (Unk0203c188 *)new Unk0202aef4(owner);
        break;
    case 26:
        o->screen = (Unk0203c188 *)new Unk02038bcc(owner, 3);
        break;
    case 4:
        if (!(o->flags & 2)) {
            o->screen = (Unk0203c188 *)new Unk02021cbc(owner, 0x4c6bad83);
            break;
        }
        o->screen = o->old;
        o->old = 0;
        return;
    case 5:
        o->screen = (Unk0203c188 *)new Unk02033ee0(owner, false);
        break;
    case 9:
        o->screen = (Unk0203c188 *)new Unk02033ee0(owner, true);
        break;
    case 6:
    case 16:
        o->screen = (Unk0203c188 *)new Unk0203c2e8(owner);
        break;
    case 17:
        o->screen = (Unk0203c188 *)new Unk02035fec(owner, 4);
        break;
    case 7:
        o->screen = (Unk0203c188 *)new Unk0203ecd4(owner);
        break;
    case 20:
        o->screen = (Unk0203c188 *)new Unk02029b80(owner);
        break;
    case 23:
        o->screen = (Unk0203c188 *)new Unk0202cdf0(owner, false, 6);
        break;
    case 24:
        o->screen = (Unk0203c188 *)new Unk0202cdf0(owner, false, 7);
        break;
    case 25:
        o->screen = (Unk0203c188 *)new Unk0202cdf0(owner, true, 6);
        break;
    case 19:
        o->screen = (Unk0203c188 *)new Unk0202cdf0(owner, true, 0x10);
        break;
    case 8:
        o->screen = (Unk0203c188 *)new Unk0202cdf0(owner, true, 8);
        break;
    case 21:
        o->screen = (Unk0203c188 *)new Unk0202fddc(owner, o->prev);
        break;
    case 13:
        o->screen = (Unk0203c188 *)new Unk0202e0ec(owner, 0);
        break;
    case 22:
        o->screen = (Unk0203c188 *)new Unk0202e0ec(owner, 1);
        break;
    case 14:
        o->screen = (Unk0203c188 *)new Unk0202e0ec(owner, 2);
        break;
    case 29:
        o->screen = (Unk0203c188 *)new Unk0202e0ec(owner, 3);
        break;
    case 30:
        o->screen = (Unk0203c188 *)new Unk0202e0ec(owner, 4);
        break;
    case 10:
        o->screen = (Unk0203c188 *)new Unk02038bcc(owner, 0);
        break;
    case 11:
        o->screen = (Unk0203c188 *)new Unk02038bcc(owner, 1);
        break;
    case 12:
        o->screen = (Unk0203c188 *)new Unk02038bcc(owner, 2);
        break;
    case 27:
        o->screen = (Unk0203c188 *)new Unk02038bcc(owner, 4);
        break;
    case 18:
        o->screen = (Unk0203c188 *)new Unk0203fa44(owner);
        break;
    }
    o->screen->func_40(true);
    o->screen->func_08();
}

/*
 * 96.22 %: the original updates the tab pointer before the position and the
 * index, and keeps the second loop's position and pointer in r9 / r10 (r7 / r8
 * here). The position is not reduced to a shifted induction variable only when
 * it is computed from the index. Tried: a pointer local in the loop, a reference
 * parameter, the position inside FX32.
 */
static inline void func_place(Unk02050640 *tab, int n) {
    int x = n * 2 + 0xdf;
    int fx = FX32(x);
    tab->func_02050a4c(n + 1);
    tab->func_14(fx, tab->func_10()->y);
}

void Unk02027994::func_020299ec(int page) {
    if ((u32)page >= 8) {
        page = 0;
    }
    int i = page;
    int n = 0;
    for (; i < 8; i++) {
        func_place(&tabs[i], n);
        n++;
    }
    n = 7;
    for (i = page - 1; i >= 0; i--) {
        func_place(&tabs[i], n);
        n--;
    }
}

Unk02098bc8 *Unk02050640::func_10() {
    return &rect;
}

bool Unk02027994::func_34() {
    return false;
}

void Unk02027994::func_1c() {
    flags &= ~4;
}

bool Unk02027994::func_20() {
    return false;
}

void Unk02027994::func_24() {}
