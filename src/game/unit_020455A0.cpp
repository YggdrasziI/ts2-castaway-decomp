/*
 * Unit 0x020455A0-0x02045BAC: a page (Unk020455a0, 0x290 bytes, vtable
 * 0x020B9878) on the page base Unk020465bc, built by the owner Unk02044234
 * for its page 3. It loads one layout from the system archive and two
 * buttons that set a flag of the settings (data_020d60c8 0x15C) to 0 or 1;
 * two sprites show which one is set. The base's button goes back to page 1.
 *
 * Bounds: hypothesis. The start is the constructor, after the functions of
 * the page at 0x020450D4 and the inline slots kept there (0x0204557C to
 * 0x0204559C); the inline func_40 (0x02045BA8) ends the file before
 * unit_02045BAC.cpp. `.data` is this class's vtable with its header. Real
 * file name unknown.
 *
 * `.data` does not match: nine slots of the vtable point to the functions of
 * other files that the page base declares under slot names (see
 * include/game/unk_screen.h).
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

/* The settings (data_020d60c8): only the flag set here. */
struct Unk020d60c8 {
    u8 unk0[0x15c];
    bool unk15c;
};

extern Unk020d60c8 data_020d60c8;

extern "C" {
Unk020d6240 *func_020a18e4();
void func_02044f14(Unk02044234 *owner, int text);
}

class Unk020455a0 : public Unk020465bc {
public:
    Unk020455a0(Unk02044234 *owner);
    virtual ~Unk020455a0();
    virtual bool func_3c(bool done);
    virtual void func_40() {}
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    void func_02045b58();

    Unk020a9d58 *layout;
    Unk02050640 buttons[3];
    Unk020a7c90 *mark0;
    Unk020a7c90 *mark1;
};

/*
 * 98.90 %: registers only; four name lookups truncate their index through
 * the other register of r0 / r1 than the original, as in the other pages.
 */
Unk020455a0::Unk020455a0(Unk02044234 *owner) : Unk020465bc(owner) {
    Unk020a7af4Entry entries[0x14];
    Unk020a7af4 names(entries, 0x14);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xaa66769c, layout, &names);
    func_020a9db8(layout, func_020a154c, 0);
    func_02046a94(layout, &names);
    buttons[1].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f2)), false);
    buttons[1].func_02050c48(0, 3, -1);
    buttons[2].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f3)), false);
    buttons[2].func_02050c48(0, 3, -1);
    mark0 = func_020aa040(layout, 1, func_020a7b50(&names, 0xf6d8f6b3));
    mark1 = func_020aa040(layout, 1, func_020a7b50(&names, 0x74b54aa6));
    func_02045b58();
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f2)));
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f3)));
    panel18.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x5f667363)));
    panel18.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x5f667364)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xb0080e84)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xf6d8f6b3)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0x74b54aa6)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xd497feae)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xd497feaf)));
    func_02044f14(this->owner, 0x717);
}

Unk020455a0::~Unk020455a0() {
    func_02046920();
    delete layout;
}

bool Unk020455a0::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = button74.func_0c(done);
    for (u32 i = 0; i < 3; i++) {
        done = buttons[i].func_0c(done);
    }
    if (button74.touch.flags & 8) {
        owner->nextPage = 1;
    } else if (buttons[1].touch.flags & 8) {
        data_020d60c8.unk15c = false;
        func_02045b58();
    } else if (buttons[2].touch.flags & 8) {
        data_020d60c8.unk15c = true;
        func_02045b58();
    }
    return done;
}

void Unk020455a0::func_48() {
    for (u32 i = 0; i < 3; i++) {
        buttons[i].func_08();
    }
    button74.func_08();
    func_020aa158(layout);
}

void Unk020455a0::func_4c() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk020455a0::func_50() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}

void Unk020455a0::func_02045b58() {
    if (data_020d60c8.unk15c) {
        func_020a7cf0(mark0, false);
        func_020a7cf0(mark1, true);
    } else {
        func_020a7cf0(mark0, true);
        func_020a7cf0(mark1, false);
    }
}
