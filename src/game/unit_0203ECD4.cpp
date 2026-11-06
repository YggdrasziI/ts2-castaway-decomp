/*
 * Unit 0x0203ECD4-0x0203FA44: the needs screen (Unk0203ecd4, vtable 0x020B96B8)
 * on the screen base Unk0203c188, built by its owner (0x02029708). For four
 * motives of the player (data_020ae97c) it shows a button with the icon of the
 * item tied to the motive (data_020af000) and a gauge of the motive's value
 * with its percentage; a motive's button is greyed out (flag 8) when
 * func_0206757c fails for its mask. Five more icons light up for the objects of
 * the inventory that carry the keys data_020ae98c. A press reports the item, or
 * the item stored for the motive (func_0206716c), to the owner.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots
 * 0x0203ECB4 / 0x0203ECBC of the screen with vtable 0x020B9658; the end is the
 * save slot screen (unit_0203FA44.cpp). `.rodata` holds the mask initializer and
 * the motive and key tables; `.data` the percentage format and this class's
 * vtable with its header (the strings before it are the previous screen's).
 * Real file name unknown.
 *
 * Not complete: the constructor is below 100 % (comment above it) and the last
 * word of `.rodata` (0x020AE9A0, 0x1E, never loaded) is the name list size, a
 * local `static const` folded into the code. Ending the file at 0x020AE9A0 drops the word from the
 * link and shifts the rest of `.rodata`.
 */

#include "game/unk_screen.h"
#include "game/unk_oam.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An item of the object database: only the id is used here. */
struct Unk0205cf00 {
    int unk0[3];
    int id;
};

/* An inventory entry. */
struct Unk02054dc4 {
    Unk0205cf00 *def;
};

/* A list of inventory entries (unit_02054734.cpp). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk02054dc4 *head;
    int count;
};

/* A motive counter of the player: only the value (0 to 10000000) is used here. */
struct Unk02064bf8 {
    int unk0;
    int value;
};

/* A text sprite (func_020a78cc): only the field tested here. */
class Unk020a78cc : public Unk020a7c90 {
public:
    u8 unk4[0x3c];
    int unk40;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

class Unk020c43a8;
struct Unk020c3fc4;
struct Unk020bfc9c;

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020bfc9c data_020bfc9c;
extern const int data_020af000[];

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
bool func_0206757c(Unk020c43a8 *p, int mask);
Unk02064bf8 *func_02066488(Unk020c43a8 *p, int i);
int func_0206716c(Unk020c43a8 *p, int i);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
u16 func_020a7164(Unk020a78cc *t);
void func_020a78cc(Unk020a78cc *t, Unk020a7c90 *s, const char *fmt, ...);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
}

static const int data_020ae97c[4] = {0, 1, 2, 3};
static const u32 data_020ae98c[5] = {0x9574bbe0, 0x9574bbe1, 0x9574bbe2, 0x9574bbe3, 0x9574bbe4};

class Unk0203ecd4 : public Unk0203c188 {
public:
    Unk0203ecd4(Unk0203c188Owner *owner);
    virtual ~Unk0203ecd4();
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
    virtual bool func_34() {
        return true;
    }
    virtual bool func_2c() {
        return fade.func_hidden();
    }

    void func_0203f5d0();
    void func_0203f7a8();
    Unk0205cf00 *func_0203f9c8(Unk0205cf00 *item);

    Unk020a9d58 *layout;
    Unk0205007c gauges[4];
    Unk02050640 buttons[4];
    Unk02051704 panel;
    Unk0205cf00 *items[4];
    Unk020a7c90 *icons[5];
};

/*
 * 99.97 %: one u16 index truncation (lookup 0xf64ae6c7) goes through r0 instead
 * of r1, as in the other screen constructors. The u32 button counter fixed the
 * loop registers and the archives declared before id its stack slot. Tried at
 * the lookup: func_sprite, a sprite local, a u16 index block; permute.py 140 s.
 */
Unk0203ecd4::Unk0203ecd4(Unk0203c188Owner *owner) : Unk0203c188(owner) {
    for (int i = 0; i < 4; i++) {
        items[i] = func_0205f6f8(&data_020c3fc4, data_020af000[data_020ae97c[i]]);
    }
    static const int size = 0x1e;
    Unk020a7af4Entry entries[size];
    Unk020a7af4 names(entries, size);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x1cf74cf8, layout, &names);
    func_020a9db8(layout, func_020a154c, this);

    panel.func_14(-0x23000, 0);
    panel.func_20(-0x146000, -0x23000);
    panel.func_020518a8(8);
    panel.func_02051804(0xf);
    panel.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xe0343c1b)));
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xf64ae6c7)));
    for (int i = 0; i < 5; i++) {
        icons[i] = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x9574bbdf + i));
        panel.func_02051858(icons[i]);
    }

    Unk020547f8 list;
    int key = 0x99a2c231;
    func_02054d94(&data_020bfc9c, &list, &key, 1, 1);
    for (int i = 0; i < list.count; i++) {
        Unk02054dc4 *e = func_02054858(&list, i);
        for (int j = 0; j < 5; j++) {
            if (func_0205d340(e->def, data_020ae98c[j])) {
                func_020a7cf0(icons[j], true);
                break;
            }
        }
    }

    int masks[4] = {0x40, 0x80, 0x100, 0x200};
    for (u32 i = 0; (int)i < 4; i++) {
        bool on = func_0206757c(&data_020c43a8, masks[i]);
        buttons[i].func_02050914(2);
        if (!on) {
            buttons[i].flags |= 8;
        } else {
            buttons[i].flags &= ~8;
        }
        buttons[i].flags |= 2;
        buttons[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xe03396f0 + i)), false);
        Unk020a7c90 *icon = func_020aa040(layout, 1, func_020a7b50(&names, 0x145c07e4 + i));
        buttons[i].func_020508a4(icon);
        func_020a7cf0(icon, on);
        Unk02093648 *archive;
        Unk02093648 *archive2;
        int id = func_0205d134(items[i], 0x9d5bba8e);
        if (id == -1) {
            id = 0;
        }
        short palette = func_020644bc(id);
        u32 hash = func_0206446c(id);
        func_020a6980(icon, hash);
        func_020a69ac(icon, palette);
        archive = func_020a18e4()->archive;
        archive2 = func_020a18e4()->archive;
        Unk0209487c *file = archive2->func_02093a9c(archive->func_02093e9c(hash));
        Unk020916a4 *oam = Unk020916a4::func_02091830();
        int bank = func_020644b0(id);
        oam->func_0209201c((Unk02095140 *)file, palette, bank << 4, func_020a7d44(icon) << 4, 0x10);
        func_020a18e4()->archive->func_02093c3c(file);
        Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x3231727a + i));
        func_020a7cf0(s, on);
        buttons[i].func_02050968(s);
        gauges[i].func_0205012c(func_020aa040(layout, 1, func_020a7b50(&names, 0x05f13df0 + i)));
        gauges[i].func_02050600(0, 0x186a0000);
        gauges[i].func_18(on);
        panel.func_020518fc(&buttons[i]);
        panel.func_020518fc(&gauges[i]);
    }
}

Unk0203ecd4::~Unk0203ecd4() {
    func_0203f7a8();
    delete layout;
}

void Unk0203ecd4::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0203ecd4::func_1c() {
    flags &= ~4;
}

bool Unk0203ecd4::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk0203ecd4::func_14() {
    return (flags & 4) != 0;
}

bool Unk0203ecd4::func_28() {
    return fade.func_shown();
}

bool Unk0203ecd4::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0203f5d0();
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_34(0x22);
        panel.func_28(0x22);
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0203ecd4::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk0203ecd4::func_0203f5d0() {
    if (flags & 2) {
        return;
    }
    panel.func_34(0x22);
    func_020aa06c(layout, true);
    for (int i = 0; i < 4; i++) {
        Unk020a78cc *text = (Unk020a78cc *)buttons[i].func_02050a40(0);
        if (text->unk40 != 0) {
            int value = func_02066488(&data_020c43a8, data_020ae97c[i])->value;
            func_020a78cc(text, func_020aa040(layout, 0, func_020a7164(text)), "%d%", (value * 100 + 50000) / 10000000);
            gauges[i].func_020501f8(FX32(func_02066488(&data_020c43a8, data_020ae97c[i])->value / 100));
            if (func_020a69cc(gauges[i].sprite) <= 0xd) {
                buttons[i].func_02050c48(1, -1, -1);
            }
        }
    }
    flags |= 2;
}

void Unk0203ecd4::func_0203f7a8() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}

bool Unk0203ecd4::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    for (int i = 0; i < 4; i++) {
        done = buttons[i].func_0c(done);
        if (buttons[i].touch.flags & 8) {
            Unk0205cf00 *def = func_0203f9c8(items[i]);
            if (def == 0) {
                func_020292c0(this->owner, 0x14);
                func_02028eec(this->owner, 0x14, items[i], 0);
            } else {
                func_020292c0(this->owner, 0x16);
                func_02028eec(this->owner, 0x16, def, 0);
            }
        }
    }
    return done;
}

void Unk0203ecd4::func_38(bool active) {
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
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0203f7a8();
    }
}

void Unk0203ecd4::func_18() {
    flags |= 4;
}

Unk0205cf00 *Unk0203ecd4::func_0203f9c8(Unk0205cf00 *item) {
    for (int i = 0; i < 4; i++) {
        int v = data_020af000[i];
        if (v == item->id) {
            int id = func_0206716c(&data_020c43a8, i);
            if (id == 0) {
                return 0;
            }
            return func_0205f6f8(&data_020c3fc4, id);
        }
    }
    return 0;
}
