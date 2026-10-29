/*
 * Unit 0x02045BAC-0x02046104: a page (Unk02045bac, 0x288 bytes, vtable
 * 0x020B98D4) on the page base Unk020465bc, built by the owner Unk02044234
 * for its page 0. It loads one layout from the system archive and three
 * buttons: the first calls the owner's slot 6, the others open pages 1
 * and 2.
 *
 * Bounds: hypothesis. The start is the constructor, after the functions of
 * the page at 0x020455A0; the inline func_40 (0x02046100) ends the file
 * before unit_02046104.cpp. `.data` is this class's vtable with its header.
 * Real file name unknown.
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

class Unk02045bac : public Unk020465bc {
public:
    Unk02045bac(Unk02044234 *owner);
    virtual ~Unk02045bac();
    virtual bool func_3c(bool done);
    virtual void func_40() {}
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    Unk020a9d58 *layout;
    Unk02050640 buttons[3];
};

/*
 * 99.90 %: registers only; two name lookups truncate their index through
 * the other register of r0 / r1 than the original, as in unit_02046104.cpp.
 */
Unk02045bac::Unk02045bac(Unk02044234 *owner) : Unk020465bc(owner) {
    Unk020a7af4Entry entries[0x14];
    Unk020a7af4 names(entries, 0x14);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xff248a8f, layout, &names);
    func_020a9db8(layout, func_020a154c, 0);
    buttons[0].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f2)), false);
    buttons[0].func_02050c48(0, 3, -1);
    buttons[1].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f3)), false);
    buttons[1].func_02050c48(0, 3, -1);
    buttons[2].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f4)), false);
    buttons[2].func_02050c48(0, 3, -1);
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f2)));
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f3)));
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x47a09f4)));
    panel18.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x5f667363)));
    panel18.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x5f667364)));
    panel18.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x5f667365)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xd497feae)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xd497feaf)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(&names, 0xd497feb0)));
    func_02044f14(this->owner, 0x710);
}

Unk02045bac::~Unk02045bac() {
    func_02046920();
    delete layout;
}

bool Unk02045bac::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    for (u32 i = 0; i < 3; i++) {
        done = buttons[i].func_0c(done);
    }
    if (buttons[0].touch.flags & 8) {
        owner->func_18();
    } else if (buttons[1].touch.flags & 8) {
        owner->nextPage = 1;
    } else if (buttons[2].touch.flags & 8) {
        owner->nextPage = 2;
    }
    return done;
}

void Unk02045bac::func_48() {
    for (u32 i = 0; i < 3; i++) {
        buttons[i].func_08();
    }
    func_020aa158(layout);
}

void Unk02045bac::func_4c() {
    if (flags & 2) {
        return;
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk02045bac::func_50() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}
