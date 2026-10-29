/*
 * Unit 0x020465BC-0x02046B7C: the page base Unk020465bc (0xF8 bytes, vtable
 * 0x020B998C, declared in include/game/unk_screen.h) of the pages built by
 * Unk02044234 (unit_020450D4.cpp to unit_02046B7C.cpp): a show / hide timer
 * whose duration depends on flag 8, a panel slid in and out with it, a back
 * button, and the empty slots the pages override.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline func_40
 * of unit_02046104.cpp; the layout helper 0x02046A94 ends the file before
 * unit_02046B7C.cpp. `.data` is the vtable with its header. Real file name
 * unknown.
 *
 * Not complete although every function and `.data` match: its inline slots
 * 7, 8, 9 and 13 have their kept copies in unit_020450D4.cpp, still assembly,
 * so this file's copies would be defined twice at link time.
 */

#include "game/unk_screen.h"

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

extern Unk020d6240 data_020d6240;

extern "C" {
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
}

Unk020465bc::Unk020465bc(Unk02044234 *owner) : flags(0) {
    this->owner = owner;
    panel18.func_14(-0x23000, 0);
    panel18.func_20(-0x146000, -0x23000);
    panel18.func_02051804(0x10);
}

Unk020465bc::~Unk020465bc() {
    func_02046920();
}

void Unk020465bc::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
        func_02046960();
    }
}

bool Unk020465bc::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    unka = a;
    func_020468d4();
    if (flags & 8) {
        fade.func_duration(0x1c);
        panel18.func_34(0x1c);
        panel18.func_28(0x1c);
        panel18.func_08();
    } else {
        fade.func_duration(0x10);
        panel18.func_30(0x1c);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk020465bc::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x1c);
        panel18.func_30(0x1c);
        panel18.func_2c(0x1c);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk020465bc::func_020468d4() {
    if (flags & 2) {
        return;
    }
    panel18.func_34(0x1c);
    func_4c();
    flags |= 2;
}

void Unk020465bc::func_4c() {}

void Unk020465bc::func_02046920() {
    if (!(flags & 2)) {
        return;
    }
    func_50();
    flags &= ~2;
}

void Unk020465bc::func_50() {}

bool Unk020465bc::func_3c(bool done) {
    return done;
}

void Unk020465bc::func_40() {}

void Unk020465bc::func_02046960() {
    panel18.func_08();
}

void Unk020465bc::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    if (fade.func_opened()) {
        flags &= ~8;
    }
    func_40();
    fade.func_step();
    func_02046960();
    func_48();
    if (fade.state == 4) {
        func_02046920();
    }
}

void Unk020465bc::func_48() {}

void Unk020465bc::func_18() {
    flags |= 4;
}

void Unk020465bc::func_02046a94(Unk020a9d58 *layout, Unk020a7af4 *names) {
    button74.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(names, 0x9dfd65a5)), false);
    button74.func_020508a4(func_020aa040(layout, 1, func_020a7b50(names, 0xb0080e84)));
    button74.func_02050c48(0, 1, -1);
    panel18.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(names, 0x9dfd65a5)));
    panel18.func_02051858(func_020aa040(layout, 1, func_020a7b50(names, 0xb0080e84)));
}
