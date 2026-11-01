/*
 * Unit 0x02046B7C-0x020471B0: a page (Unk02046b7c, 0x210 bytes, vtable
 * 0x020B99E8) on the page base Unk020465bc, built by the owner Unk02044234
 * for its page 4. It loads one layout from the system archive, two buttons
 * that pick one of two settings (data_020d60c8 0x13C and 0x138), and while a
 * button is held, sets that setting from the touch position (0 to 0x1000)
 * and moves its marker sprite.
 *
 * Bounds: hypothesis. The start is the constructor, after the base's
 * functions (the shared layout helper 0x02046A94 ends them); the inline
 * func_40 (0x020471AC) ends the file before unit_020471B0.cpp. `.data` is
 * this class's vtable with its header. Real file name unknown.
 */

#include "game/unk_screen.h"

/* The system (data_020d6240): only the archive. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The settings (data_020d60c8): only the two values set here. */
struct Unk020d60c8 {
    u8 unk0[0x138];
    int unk138;
    int unk13c;
};

extern Unk020d60c8 data_020d60c8;

int *func_02097a4c();
bool func_020978dc(int screen);

extern "C" {
Unk020d6240 *func_020a18e4();
void *func_020a2994();
int func_020a29e8(void *sound, int volume, int value);
void func_0209f850(Unk020d60c8 *settings, int value);
void func_0209f880(Unk020d60c8 *settings, int value);
void func_02044f14(Unk02044234 *owner, int text);
}

class Unk02046b7c : public Unk020465bc {
public:
    Unk02046b7c(Unk02044234 *owner);
    virtual ~Unk02046b7c();
    virtual bool func_3c(bool done);
    virtual void func_40() {}
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    void func_02047030();

    Unk020a9d58 *layout;
    Unk02050640 buttons[2];
    Unk020a7c90 *marker0;
    Unk020a7c90 *marker1;
    int selected;
};

Unk02046b7c::Unk02046b7c(Unk02044234 *owner) : Unk020465bc(owner), selected(-1) {
    Unk020a7af4Entry entries[0x14];
    Unk020a7af4 names(entries, 0x14);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xce9d22f3, layout, &names);
    func_020a9db8(layout, func_020a154c, 0);
    func_02046a94(layout, &names);
    buttons[0].func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f3)), false);
    buttons[1].func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f4)), false);
    marker0 = func_sprite(layout, 1, func_020a7b50(&names, 0x8afe805c));
    marker1 = func_sprite(layout, 1, func_020a7b50(&names, 0x8afe805d));
    panel18.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f3)));
    panel18.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f4)));
    panel18.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x5f667364)));
    panel18.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x5f667365)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0x8afe805c)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0x8afe805d)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xd497feaf)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xd497feb0)));
    func_02044f14(this->owner, 0x718);
    func_02047030();
}

Unk02046b7c::~Unk02046b7c() {
    func_02046920();
    delete layout;
}

bool Unk02046b7c::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button74.func_0c(done);
    for (u32 i = 0; i < 2; i++) {
        done = buttons[i].func_0c(done);
    }
    if (button74.touch.flags & 8) {
        owner->nextPage = 1;
    } else if (selected == -1) {
        if (buttons[0].touch.flags & 1) {
            selected = 0;
        } else if (buttons[1].touch.flags & 1) {
            selected = 1;
        }
    } else if (!func_020978dc(0)) {
        selected = -1;
    }
    return done;
}

void Unk02046b7c::func_02047030() {
    func_020a7c90(marker0, data_020d60c8.unk13c * 0x1100 + 0x36000);
    func_020a7c90(marker1, data_020d60c8.unk138 * 0x1100 + 0x36000);
}

void Unk02046b7c::func_48() {
    for (u32 i = 0; i < 2; i++) {
        buttons[i].func_08();
    }
    button74.func_08();
    if (selected != -1) {
        int value = (func_02097a4c()[0] - 0x36) * 0x1e;
        if (value < 0) {
            value = 0;
        } else if (value > 0x1000) {
            value = 0x1000;
        }
        int volume = func_020a29e8(func_020a2994(), 0x7f, value);
        switch (selected) {
        case 0:
            func_0209f880(&data_020d60c8, volume);
            func_02047030();
            break;
        case 1:
            func_0209f850(&data_020d60c8, volume);
            func_02047030();
            break;
        }
    }
    func_020aa158(layout);
}

void Unk02046b7c::func_4c() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk02046b7c::func_50() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}
