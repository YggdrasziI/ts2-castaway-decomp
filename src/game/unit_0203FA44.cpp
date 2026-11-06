/*
 * Unit 0x0203FA44-0x02041B10: the save slot screen (Unk0203fa44, 0x7B0 bytes,
 * vtable 0x020B9728) on the screen base Unk0203c188, built by its owner
 * (0x02029978). Three slot buttons show, for each saved game, its name, a
 * number and a percentage, or a text of the table (0xF95) and "--" when the
 * slot is empty; six panels hold them and three pairs of buttons, and a
 * sprite panel waits for func_0209fa80 / func_020a5538 (role unknown). The
 * text of the layout comes from func_02041870, which formats the slot fields
 * into the 0x60-byte buffer at 0x750.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots
 * 0x0203FA24 / 0x0203FA2C of the class whose vtable ends at 0x020B96FC; the
 * end is the
 * outfit screen (unit_02041B10.cpp). `.data` holds the format strings of the
 * text function and this class's vtable with its header. Real file name
 * unknown.
 */

#include "game/unk_screen.h"

/* A save slot record (func_0209f8d0): only the fields used here. */
struct Unk0209f8d0 {
    int unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    char name[1];
};

/* The saved games of the settings: only the fields used here. */
struct Unk020d60c8Items {
    u8 unk0[0xc];
    u32 count;
    u8 unk10[8];
    u32 flags;
    u8 unk1c[0x44];
    int unk60;
};

/* The settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    void *unk0;
    u8 unk4[0x150];
    Unk020d60c8Items *items;
    void *texts;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The main game state (func_0206bce0): only the field set here. */
struct Unk0206bce0 {
    int unk0;
    int unk4;
    int next;
};

extern Unk020d60c8 data_020d60c8;
extern Unk020d6240 data_020d6240;

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0206bce0 *func_0206bce0();
void func_020290f0(Unk0203c188Owner *owner, bool show);
void func_02028ec8(Unk0203c188Owner *owner, u8 a, int b);
void func_0202923c(Unk0203c188Owner *owner);
bool func_020a5248(Unk020d60c8Items *items, int index);
bool func_020a5538(Unk020d60c8Items *items);
void func_020a4c4c(void *p);
bool func_0209fa80(Unk020d60c8 *settings, int index);
Unk0209f8d0 *func_0209f8d0(Unk020d60c8 *settings, int index);
int sprintf(char *buf, const char *fmt, ...);
void *func_020a00a0(void *texts, u32 id);
void *func_0202fdb0(Unk020d6240 *system);
}

class Unk0203fa44 : public Unk0203c188 {
public:
    Unk0203fa44(Unk0203c188Owner *owner);
    virtual ~Unk0203fa44();
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

    void func_02040fa0();
    void func_02040fd0();
    bool func_02041abc(int slot);

    Unk020a9d58 *layout;
    Unk02050640 button18;
    Unk02050640 button9c;
    Unk02051704 panel120;
    Unk02050640 button17c;
    Unk02050640 button200;
    Unk02051704 panel284;
    Unk02051704 panel2e0;
    Unk02050640 slots[3];
    Unk02050640 button4c8;
    Unk02050640 button54c;
    Unk02051704 panel5d0;
    Unk02051704 panel62c;
    Unk0204f798 sprite;
    Unk02051704 panel6f0;
    int slot;
    char text[0x60];
};

static void *func_02041870(u32 id, void *user);

/*
 * 99.85 %: registers of the slot loop only. The original gives x r4, the name
 * list r6 and the counter r7; here x is r7, the name list r4 and the counter r6
 * (the slot base, r5, matches since the slot pointer local). Tried: const x / y /
 * slot, unsigned x / y, one sprite local, x and y declared before the loop, the
 * counter outside the loop, tools/permute.py (180 s, best score 28). One local
 * per sprite gives the original's reuse of x's register by the last sprite.
 */
Unk0203fa44::Unk0203fa44(Unk0203c188Owner *owner) : Unk0203c188(owner) {
    Unk020a7af4Entry entries[0x50];
    Unk020a7af4 names(entries, 0x50);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x26a65582, layout, &names);
    func_020a9db8(layout, func_02041870, this);

    sprite.delay = 6;
    sprite.func_0204f8a0(1);
    sprite.func_0204fa10(0, 0x18);
    sprite.func_0204f8f4(func_sprite(layout, 1, func_020a7b50(&names, 0x863c720d)));
    panel62c.func_14(-0x23000, 0);
    panel62c.func_20(-0x146000, -0x23000);
    panel62c.func_02051804(5);
    panel62c.func_020518a8(1);
    panel62c.func_020518fc(&sprite);
    panel62c.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x1d479ca6)));
    panel62c.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x2381cd6e)));
    panel62c.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x058b1ad7)));
    panel62c.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0xfe3bcc49)));
    panel62c.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0x7c2fb3c7)));
    panel62c.func_18(false);
    panel62c.func_34(0x22);

    button4c8.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x110170ed)), false);
    button4c8.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0x65a9516c)));
    button4c8.func_02050914(1);
    button4c8.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0x108954d7)));
    button4c8.func_02050c48(0, 1, -1);
    button4c8.func_02050c64(0, 1, 2);
    button4c8.func_14(0x3b000, 0x90000);
    button54c.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xc4ea7b20)), false);
    button54c.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0x8cb0d9b6)));
    button54c.func_02050914(1);
    button54c.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0xc4725f0a)));
    button54c.func_02050c48(0, 1, -1);
    button54c.func_02050c64(0, 1, 2);
    button54c.func_14(0x7e000, 0x90000);
    panel5d0.func_14(-0x23000, 0);
    panel5d0.func_20(-0x146000, -0x23000);
    panel5d0.func_020518a8(2);
    panel5d0.func_02051804(4);
    panel5d0.func_020518fc(&button4c8);
    panel5d0.func_020518fc(&button54c);
    panel5d0.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xa703c4b9)));
    panel5d0.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xdc9d191d)));
    panel5d0.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0xd669f73d)));
    panel5d0.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xecd39a59)));
    panel5d0.func_34(0x22);

    button18.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x510a3667)), false);
    button18.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0x87a68b24)));
    button18.func_02050914(1);
    button18.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0x50921a51)));
    button18.func_02050c48(0, 1, -1);
    button18.func_02050c64(0, 1, 2);
    button18.func_14(0x3b000, 0x90000);
    button9c.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xf855d81b)), false);
    button9c.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0xccb92710)));
    button9c.func_02050914(1);
    button9c.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0xf7ddbc05)));
    button9c.func_02050c48(0, 1, -1);
    button9c.func_02050c64(0, 1, 2);
    button9c.func_14(0x7e000, 0x90000);
    panel120.func_14(-0x23000, 0);
    panel120.func_20(-0x146000, -0x23000);
    panel120.func_020518a8(2);
    panel120.func_02051804(4);
    panel120.func_020518fc(&button18);
    panel120.func_020518fc(&button9c);
    panel120.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xda6f21b4)));
    panel120.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x1ca56696)));
    panel120.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x7accadae)));
    panel120.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0x18bfd716)));
    panel120.func_30(0x22);
    panel120.func_18(true);

    button17c.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x3e7897ed)), false);
    button17c.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0x93607207)));
    button17c.func_02050914(1);
    button17c.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0x3e007bd7)));
    button17c.func_02050c48(0, 1, -1);
    button17c.func_02050c64(0, 1, 2);
    button17c.func_14(0x3b000, 0x90000);
    button200.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xc706bea9)), false);
    button200.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0xba368c96)));
    button200.func_02050914(1);
    button200.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0xc68ea293)));
    button200.func_02050c48(0, 1, -1);
    button200.func_02050c64(0, 1, 2);
    button200.func_14(0x7e000, 0x90000);
    panel284.func_14(-0x23000, 0);
    panel284.func_20(-0x146000, -0x23000);
    panel284.func_020518a8(2);
    panel284.func_02051804(4);
    panel284.func_020518fc(&button17c);
    panel284.func_020518fc(&button200);
    panel284.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xa9200481)));
    panel284.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x0a13c81c)));
    panel284.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x61c5b098)));
    panel284.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xa9bb5f93)));
    panel284.func_34(0x22);

    panel2e0.func_14(-0x23000, 0);
    panel2e0.func_20(-0x146000, -0x23000);
    panel2e0.func_020518a8(3);
    panel2e0.func_02051804(2);
    for (int i = 0; i < 3; i++) {
        Unk02050640 *slot = &slots[i];
        slot->func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xcadc45ff + i)), false);
        slot->func_02050c48(0, 3, -1);
        slot->func_02050914(7);
        int x = slot->func_10()->x;
        int y = slot->func_10()->y;
        Unk020a7c90 *s1 = func_sprite(layout, 4, func_020a7b50(&names, 0x9e34ffc6 + i));
        func_020a7c90(s1, x + 0xa000);
        func_020a7cac(s1, y + 0x3000);
        slot->func_02050968(s1);
        Unk020a7c90 *s2 = func_sprite(layout, 0xb, func_020a7b50(&names, 0xdd3e7fe1 + i));
        func_020a7c90(s2, x + 0xa000);
        func_020a7cac(s2, y + 0x11000);
        slot->func_02050968(s2);
        Unk020a7c90 *s3 = func_sprite(layout, 0xb, func_020a7b50(&names, 0x954f8f5d + i));
        func_020a7c90(s3, x + 0x73000);
        func_020a7cac(s3, y + 0x16000);
        slot->func_02050968(s3);
        Unk020a7c90 *s4 = func_sprite(layout, 4, func_020a7b50(&names, 0x81c58176 + i));
        func_020a7c90(s4, x + 0x1a000);
        func_020a7cac(s4, y + 0x13000);
        slot->func_02050968(s4);
        Unk020a7c90 *s5 = func_sprite(layout, 4, func_020a7b50(&names, 0x95e99c6c + i));
        func_020a7c90(s5, x + 0x77000);
        func_020a7cac(s5, y + 0x13000);
        slot->func_02050968(s5);
        Unk020a7c90 *s6 = func_sprite(layout, 4, func_020a7b50(&names, 0xa8bac962 + i));
        func_020a7c90(s6, x + 0x1a000);
        func_020a7cac(s6, y + 0x1e000);
        slot->func_02050968(s6);
        Unk020a7c90 *s7 = func_sprite(layout, 4, func_020a7b50(&names, 0x4baf5053 + i));
        func_020a7c90(s7, x + 0x77000);
        func_020a7cac(s7, y + 0x1e000);
        slot->func_02050968(s7);
        panel2e0.func_020518fc(slot);
    }
    panel2e0.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x4c28c567)));
    panel2e0.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0xf15efd54)));
    panel2e0.func_34(0x22);

    panel6f0.func_14(-0x23000, 0);
    panel6f0.func_20(-0x146000, -0x23000);
    panel6f0.func_02051804(4);
    panel6f0.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xb2647c15)));
    panel6f0.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0xf3639ddb)));
    panel6f0.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0xcd14a000)));
    panel6f0.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0x10b581c2)));
    panel6f0.func_34(0x22);

    func_020290f0(this->owner, false);
    func_02028ec8(this->owner, 0, 0);
    this->owner->flagsb8 |= 8;
}

Unk0203fa44::~Unk0203fa44() {
    func_02040fd0();
    delete layout;
    if (flags & 0x20) {
        func_0206bce0()->next = 2;
    }
}

void Unk0203fa44::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0203fa44::func_1c() {
    flags &= ~4;
}

bool Unk0203fa44::func_30() {
    return func_28() && !func_14() && !panel120.func_50() && !panel2e0.func_50() && !panel284.func_50() &&
           !panel5d0.func_50() && !panel62c.func_50() && !panel6f0.func_50() && !(flags & 0x40);
}

bool Unk0203fa44::func_14() {
    return (flags & 4) != 0;
}

bool Unk0203fa44::func_28() {
    return fade.func_shown();
}

bool Unk0203fa44::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_02040fa0();
    fade.func_duration(0x10);
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0203fa44::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk0203fa44::func_02040fa0() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk0203fa44::func_02040fd0() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}

bool Unk0203fa44::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button18.func_0c(done);
    if (button18.touch.flags & 8) {
        func_0202923c(this->owner);
        panel120.func_2c(0x22);
    }
    done = button9c.func_0c(done);
    if (button9c.touch.flags & 8) {
        this->owner->func_18();
    }
    for (int i = 0; i < 3; i++) {
        done = slots[i].func_0c(done);
        if (slots[i].touch.flags & 8) {
            Unk020d60c8Items *items = data_020d60c8.items;
            if ((items->flags & 1) && (u32)i < items->count) {
                this->owner->flagsb8 |= 8;
                slot = i;
                if (func_020a5248(items, i)) {
                    panel2e0.func_2c(0x22);
                    func_0202923c(this->owner);
                } else {
                    flags |= 0x100;
                    panel2e0.func_2c(0x22);
                    func_0202923c(this->owner);
                }
            }
        }
    }
    done = button17c.func_0c(done);
    if (button17c.touch.flags & 8) {
        flags |= 0x100;
        panel284.func_2c(0x22);
        func_0202923c(this->owner);
    }
    done = button200.func_0c(done);
    if (button200.touch.flags & 8) {
        panel284.func_2c(0x22);
        func_0202923c(this->owner);
    }
    done = button4c8.func_0c(done);
    if (button4c8.touch.flags & 8) {
        this->owner->func_18();
    }
    done = button54c.func_0c(done);
    if (button54c.touch.flags & 8) {
        this->owner->func_18();
        flags |= 0x20;
    }
    return done;
}

void Unk0203fa44::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    if (panel120.func_44()) {
        panel120.func_18(false);
    }
    if (panel284.func_44()) {
        panel284.func_18(false);
    }
    if (panel2e0.func_44()) {
        panel2e0.func_18(false);
    }
    if (panel5d0.func_44()) {
        panel5d0.func_18(false);
    }
    if (panel6f0.func_44()) {
        panel6f0.func_18(false);
    }
    if (panel62c.func_44()) {
        panel62c.func_18(false);
    }
    if (panel120.func_44()) {
        panel2e0.func_18(true);
        panel2e0.func_28(0x22);
    } else if ((panel284.func_44() || panel2e0.func_44()) && (flags & 0x100)) {
        panel62c.func_18(true);
        panel62c.func_28(0x22);
        flags &= ~0x100;
    } else if (panel2e0.func_44() && !(flags & 0x10)) {
        panel284.func_18(true);
        panel284.func_28(0x22);
    } else if ((panel284.func_44() || panel6f0.func_44()) && !(flags & 0x10)) {
        panel2e0.func_18(true);
        panel2e0.func_28(0x22);
    } else if (panel62c.func_40()) {
        if (!func_02041abc(slot)) {
            panel62c.func_2c(0x22);
        }
    } else if (panel62c.func_44() && (flags & 0x80)) {
        panel6f0.func_18(true);
        panel6f0.func_28(0x22);
        flags &= ~0x80;
    } else if (panel62c.func_44() && (flags & 0x10)) {
        panel5d0.func_18(true);
        panel5d0.func_28(0x22);
    } else if (panel2e0.func_40()) {
        this->owner->flagsb8 &= ~8;
    }
    if (flags & 0x40) {
        Unk020d60c8Items *items = data_020d60c8.items;
        if (!func_020a5538(items)) {
            if (items->unk60 == 2) {
                flags &= ~0x40;
                flags |= 0x10;
            } else {
                flags &= ~0x40;
                flags |= 0x80;
                panel62c.func_2c(0x22);
                func_0202923c(this->owner);
            }
            func_020a4c4c(data_020d60c8.unk0);
        }
    }
    if (flags & 0x10) {
        if (panel62c.func_38()) {
            panel62c.func_2c(0x22);
            func_0202923c(this->owner);
        }
    }
    panel120.func_08();
    panel2e0.func_08();
    panel284.func_08();
    panel5d0.func_08();
    panel6f0.func_08();
    panel62c.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_02040fd0();
    }
}

void Unk0203fa44::func_18() {
    flags |= 4;
}

static void *func_02041870(u32 id, void *user) {
    Unk0203fa44 *self = (Unk0203fa44 *)user;
    switch (id) {
    case 0x800001:
        if (func_020a5248(data_020d60c8.items, 0)) {
            sprintf(self->text, "1. %s", func_0209f8d0(&data_020d60c8, 0)->name);
        } else {
            sprintf(self->text, "1. %s", func_020a00a0(data_020d60c8.texts, 0xf95));
        }
        return self->text;
    case 0x800002:
        if (func_020a5248(data_020d60c8.items, 1)) {
            sprintf(self->text, "2. %s", func_0209f8d0(&data_020d60c8, 1)->name);
        } else {
            sprintf(self->text, "2. %s", func_020a00a0(data_020d60c8.texts, 0xf95));
        }
        return self->text;
    case 0x800003:
        if (func_020a5248(data_020d60c8.items, 2)) {
            sprintf(self->text, "3. %s", func_0209f8d0(&data_020d60c8, 2)->name);
        } else {
            sprintf(self->text, "3. %s", func_020a00a0(data_020d60c8.texts, 0xf95));
        }
        return self->text;
    case 0x800004:
    case 0x800005:
    case 0x800006:
        if (func_020a5248(data_020d60c8.items, id - 0x800004)) {
            sprintf(self->text, "%d", func_0209f8d0(&data_020d60c8, id - 0x800004)->unk0);
        } else {
            sprintf(self->text, "--");
        }
        return self->text;
    case 0x800007:
    case 0x800008:
    case 0x800009:
        if (func_020a5248(data_020d60c8.items, id - 0x800007)) {
            sprintf(self->text, "%d%", func_0209f8d0(&data_020d60c8, id - 0x800007)->unk7);
        } else {
            sprintf(self->text, "--");
        }
        return self->text;
    default:
        return func_020a00a0(func_0202fdb0(func_020a18e4()), id);
    }
}

bool Unk0203fa44::func_02041abc(int slot) {
    if (func_0209fa80(&data_020d60c8, slot)) {
        flags |= 0x40;
        return true;
    }
    flags |= 0x80;
    return false;
}
