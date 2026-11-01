/*
 * Unit 0x02029B80-0x0202AEF4: an object text screen (Unk02029b80, 0x314 bytes,
 * vtable 0x020B9264) on the screen base Unk0203c188. It shows the name, the icon
 * and the paged text of the object data_020b9258, with a button to the object
 * of the player's slot for this object's kind.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * the survival guide (unit_02027994.cpp); the end is the category screen
 * (unit_0202AEF4.cpp). `.data` holds the current object, this class's vtable
 * with its header and the two page formats. Real file name unknown.
 *
 * It holds the kept copies 0x0202A518 of the widget base slot 9 and 0x0202A52C of
 * the panel's func_10, right after the constructor, their first user: written
 * as plain definitions, as slot 7 in unit_0202FDDC.cpp.
 *
 * Not complete: the constructor is below 100 % (comment above it).
 */

#include "game/unk_screen.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"
#include "game/unk_resource.h"
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
struct Unk0205cf00;

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

struct Unk020c43a8;
struct Unk020c3fc4;

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3fc4 data_020c3fc4;

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
const char *func_020a00a0(void *texts, u32 id);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
int func_0206716c(Unk020c43a8 *p, int kind);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a6980(Unk020a7c90 *s, u32 hash);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
u16 func_020a7164(Unk020a7c90 *t);
void func_020a716c(Unk020a7c90 *s, int text);
int func_020a793c(Unk020a7c90 *t, int page, Unk020a7c90 *font, const char *fmt, ...);
void func_020a7ce0(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
int sprintf(char *buf, const char *fmt, ...);
void func_0202ae50(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b9258 = 0;
#pragma explicit_zero_data reset

class Unk02029b80 : public Unk0203c188 {
public:
    Unk02029b80(Unk0203c188Owner *owner);
    virtual ~Unk02029b80();
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

    void func_0202a92c();
    void func_0202aac8();

    Unk020a9d58 *layout;
    Unk02051704 panel;
    Unk02051704 pager;
    Unk02050640 next;
    Unk02050640 prev;
    int textId;
    Unk020a7c90 *text;
    Unk020a7c90 *slot;
    Unk02050640 back;
    Unk02050640 item;
    Unk0205cf00 *def;
    char num[0x20];
    short page;
    short pages;
};

static void *func_0202ae60(u32 id, void *user);

/*
 * 98.96 %: the label `s` is in r7 and `first` / `kind` in r5 / r6 in the original
 * (rotated here), three name lookups truncate through the other of r0 / r1, and
 * the rectangle of next.func_10() moves to r1 before the pager's vtable load, as
 * in unit_0203B3B8.cpp. Tried: `kind` first (the best), bool `first`, early
 * declarations, rectangle locals and references.
 */
Unk02029b80::Unk02029b80(Unk0203c188Owner *owner) : Unk0203c188(owner), def(0) {
    Unk020a7af4Entry entries[0x1e];
    Unk020a7af4 names(entries, 0x1e);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x62834f7a, layout, &names);
    func_020a9db8(layout, func_0202ae60, this);

    panel.func_14(-0x23000, 0);
    panel.func_20(0xffeba000, -0x23000);
    panel.func_020518a8(2);
    panel.func_02051804(0x14);
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));
    Unk020a7c90 *title = func_020aa040(layout, 4, func_020a7b50(&names, 0xe0343c1b));
    func_020a716c(title, func_0205d134(data_020b9258, 0xbe33d1b8));
    panel.func_02051858(title);

    Unk020a7c90 *icon = func_020aa040(layout, 1, func_020a7b50(&names, 0x7e1684d9));
    int key = func_0205d134(data_020b9258, 0x9d5bba8e);
    if (key == -1) {
        key = 0;
    }
    func_020a6980(icon, func_0206446c(key));
    func_020a69ac(icon, func_020644bc(key));
    int palette = func_020644b0(key);
    Unk02093648 *a = func_020a18e4()->archive;
    Unk02093648 *b = func_020a18e4()->archive;
    Unk0209487c *file = b->func_02093a9c(a->func_02093e9c(func_020a69a4(icon)));
    Unk020916a4::func_02091830()->func_0209201c((Unk02095140 *)file, func_020a69cc(icon), palette << 4,
                                                func_020a7d44(icon) << 4, 0x10);
    a = func_020a18e4()->archive;
    b = func_020a18e4()->archive;
    b->func_02093c58(a->func_02093e9c(func_020a69a4(icon)));
    panel.func_02051858(icon);
    panel.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x6b44a2aa)));

    slot = func_020aa040(layout, 1, func_020a7b50(&names, 0x94f941aa));
    item.func_02050914(3);
    item.flags |= 2;
    item.func_02050c48(0, 1, -1);
    item.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x70df4097)), false);
    item.func_02050968(slot);
    item.func_02050968(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x9774c086)));
    Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x981fc873));
    item.func_02050968(s);
    panel.func_020518fc(&item);

    int kind = 0;
    int first = 1;
    if (func_0205d340(data_020b9258, 0x0e2508ee)) {
        first = kind;
    } else if (func_0205d340(data_020b9258, 0x4089a7c6)) {
        kind = first;
    } else if (func_0205d340(data_020b9258, 0x61aadad6)) {
        kind = 2;
        first = 0;
    } else if (func_0205d340(data_020b9258, 0xaaba8051)) {
        kind = 3;
        first = 0;
    }
    if (first) {
        func_020a716c(s, 0xe1a);
    } else {
        func_020a716c(s, 0xe19);
    }

    int id = func_0206716c(&data_020c43a8, kind);
    if (id != 0) {
        Unk0205cf00 *other = func_0205f6f8(&data_020c3fc4, id);
        Unk02093648 *archive;
        int otherKey = func_0205d134(other, 0x9d5bba8e);
        if (otherKey == -1) {
            otherKey = 0;
        }
        short otherPalette = func_020644bc(otherKey);
        func_020a6980(slot, func_0206446c(otherKey));
        func_020a69ac(slot, otherPalette);
        archive = func_020a18e4()->archive;
        Unk0209487c *otherFile = archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(slot)));
        Unk020916a4 *oam = Unk020916a4::func_02091830();
        int index = func_020644b0(otherKey);
        oam->func_0209201c((Unk02095140 *)otherFile, otherPalette, index << 4,
                           func_020a7d44(slot) << 4, 0x10);
        archive->func_02093c3c(otherFile);
        item.func_18(true);
        def = other;
    } else {
        item.func_18(false);
        item.flags |= 8;
    }

    panel.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xbc89d65c)));
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x32504d44)));
    text = func_020aa040(layout, 4, func_020a7b50(&names, 0x96c99379));
    panel.func_02051858(text);
    textId = func_0205d134(data_020b9258, 0x6a4a2934);

    s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc2f94842));
    back.func_02050838(s, false);
    back.func_02050c48(0, 1, -1);
    back.func_20(func_020a7ca4(s) - s->func_10(), func_020a7ca4(s));
    back.func_02050914(2);
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x15f3ba51)));
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x060bbd76)));

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));
    next.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));

    Unk02098bc8 *rect = next.func_10();
    pager.func_14(0, rect->y);
    rect = pager.func_10();
    pager.func_24(0xc0000, rect->y);
    pager.func_020518a8(2);
    pager.func_02051804(2);
    pager.func_020518fc(&prev);
    pager.func_020518fc(&next);
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x79be6d8f)));
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x03398ecd)));
}

void Unk020b9e88::func_24(int x, int y) {
    valuesY[0] = x;
    valuesY[1] = y;
    trackY = &keysY;
}

Unk02098bc8 *Unk02051704::func_10() {
    return (Unk02098bc8 *)unk34;
}

Unk02029b80::~Unk02029b80() {
    func_0202aac8();
    delete layout;
}

void Unk02029b80::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk02029b80::func_1c() {
    flags &= ~4;
}

bool Unk02029b80::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk02029b80::func_14() {
    return (flags & 4) != 0;
}

bool Unk02029b80::func_28() {
    return fade.func_shown();
}

bool Unk02029b80::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0202a92c();
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_34(0x22);
        panel.func_28(0x22);
        if (pages > 1) {
            pager.func_34(0x22);
            pager.func_28(0x22);
        }
        back.func_34(0x22);
        back.func_28(0x22);
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x22);
        if (pages > 1) {
            pager.func_30(0x22);
        }
        back.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk02029b80::func_10() {
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
        back.func_30(0x22);
        back.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk02029b80::func_0202a92c() {
    if (flags & 2) {
        return;
    }
    panel.func_34(0x22);
    pager.func_34(0x22);
    back.func_34(0x22);
    func_020aa06c(layout, true);
    int height = text->func_14() >> 12;
    Unk020aa040Font *font = (Unk020aa040Font *)func_020aa040(layout, 0, func_020a7164(text));
    Unk02092830 lines(func_020a00a0(func_0201ba94(), textId), font->font);
    Unk02098bc8 size = lines.func_02092db0(0, 0, text->func_10() >> 12, height, 0, 0);
    page = 0;
    pages = (u32)size.h / height;
    if ((u32)size.h % height != 0) {
        pages++;
    }
    Unk020a7c90 *f = func_020aa040(layout, 0, func_020a7164(text));
    func_020a793c(text, page, f, func_020a00a0(func_0201ba94(), textId));
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    flags |= 2;
}

void Unk02029b80::func_0202aac8() {
    if (flags & 2) {
        func_020aa06c(layout, false);
        flags &= ~2;
    }
}

bool Unk02029b80::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        func_020292c0(owner, 7);
    }
    done = item.func_0c(done);
    if (item.touch.flags & 8) {
        func_020292c0(owner, 0x16);
        func_02028eec(owner, 0x16, def, 0);
    }
    done = prev.func_0c(done);
    if (prev.touch.flags & 8) {
        page--;
        ((Unk020a78cc *)text)->canvas->func_0209088c();
        Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
        func_020a793c(text, page, font, func_020a00a0(func_0201ba94(), textId));
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = next.func_0c(done);
    if (next.touch.flags & 8) {
        page++;
        ((Unk020a78cc *)text)->canvas->func_0209088c();
        Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
        func_020a793c(text, page, font, func_020a00a0(func_0201ba94(), textId));
        func_020a7ce0(pager.func_02051ad0(0));
    }
    return done;
}

void Unk02029b80::func_38(bool active) {
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
    back.func_08();
    pager.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0202aac8();
    }
}

void Unk02029b80::func_18() {
    flags |= 4;
}

void func_0202ae50(Unk0205cf00 *def) {
    data_020b9258 = def;
}

static void *func_0202ae60(u32 id, void *user) {
    Unk02029b80 *screen = (Unk02029b80 *)user;
    int n = id - 0x800000;
    if (n == 1) {
        sprintf(screen->num, "%d", screen->page + 1);
        return screen->num;
    }
    if (n == 2) {
        sprintf(screen->num, "/%d", screen->pages);
        return screen->num;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

bool Unk02029b80::func_34() {
    return true;
}

bool Unk02029b80::func_2c() {
    return fade.func_hidden();
}
