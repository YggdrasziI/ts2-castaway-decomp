/*
 * Unit 0x020450D4-0x020455A0: a page (Unk020450d4, 0x204 bytes, vtable
 * 0x020B981C) on the page base Unk020465bc, built by the owner Unk02044234
 * for its page 2. It loads one layout from the system archive and two
 * buttons: the first sets the owner's flag 0x44 and calls its slot 6, the
 * second goes back to page 0. The file also holds the kept copies of the
 * page base's inline slots (0x0204557C to 0x0204559C).
 *
 * Bounds: hypothesis. The start is the constructor, after the owner's
 * functions (0x020450D0); the base's inline slots end the file before
 * unit_020455A0.cpp. `.data` is this class's vtable with its header. Real
 * file name unknown.
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

extern "C" {
Unk020d6240 *func_020a18e4();
void func_02044f14(Unk02044234 *owner, int text);
}

class Unk020450d4 : public Unk020465bc {
public:
    Unk020450d4(Unk02044234 *owner);
    virtual ~Unk020450d4();
    virtual bool func_3c(bool done);
    virtual void func_40() {}
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    Unk020a9d58 *layout;
    Unk02050640 buttons[2];
};

/*
 * 99.94 %: registers only; one name lookup truncates its index through the
 * other register of r0 / r1 than the original, as in the other pages.
 */
Unk020450d4::Unk020450d4(Unk02044234 *owner) : Unk020465bc(owner) {
    Unk020a7af4Entry entries[0x14];
    Unk020a7af4 names(entries, 0x14);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xe3138240, layout, &names);
    func_020a9db8(layout, func_020a154c, 0);
    buttons[0].func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f2)), false);
    buttons[0].func_02050c48(0, 3, -1);
    buttons[1].func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f3)), false);
    buttons[1].func_02050c48(0, 3, -1);
    panel18.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f2)));
    panel18.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0x47a09f3)));
    panel18.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x5f667363)));
    panel18.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x5f667364)));
    panel18.func_02051858(func_sprite(layout, 4, func_020a7b50(&names, 0x23134734)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xd497feae)));
    panel18.func_02051858(func_sprite(layout, 1, func_020a7b50(&names, 0xd497feaf)));
    func_02044f14(this->owner, 0x715);
}

Unk020450d4::~Unk020450d4() {
    func_02046920();
    delete layout;
}

bool Unk020450d4::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    for (u32 i = 0; i < 2; i++) {
        done = buttons[i].func_0c(done);
    }
    if (buttons[0].touch.flags & 8) {
        owner->unk44 = 1;
        owner->func_18();
    } else if (buttons[1].touch.flags & 8) {
        owner->nextPage = 0;
    }
    return done;
}

void Unk020450d4::func_48() {
    for (u32 i = 0; i < 2; i++) {
        buttons[i].func_08();
    }
    func_020aa158(layout);
}

void Unk020450d4::func_4c() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk020450d4::func_50() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}
