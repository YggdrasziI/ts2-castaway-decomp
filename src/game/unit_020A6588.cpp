/*
 * Unit 0x020A6588-0x020A690C: the screen of a game mode: fades in and out on a counter, then reports
 * to the mode through its flags ("Start", "Microgame screen being hidden", "ForceDismiss",
 * "ClearDismissed"). Bounds: hypothesis (from the constructor to the class at 0x020A690C; `.data` is
 * the strings and the vtable). All names are placeholders. Real file name unknown.
 */
#include "game/unk_action.h"
#include "game/unk_microgame.h"

struct Unk020d6240;

extern "C" {
void func_020897b4(const char *format, ...);
void func_020a11f8(int system, int a, int b);
u8 func_020a14d8(int system);
void func_020a14e0(int system, bool on);
}

Unk020a6588::Unk020a6588() : unk4(0), unk6(0x3c), unk8(5), flags(0), state(1) {}

Unk020a6588::~Unk020a6588() {}

void Unk020a6588::func_08() {
    func_020897b4("Start");
}

bool Unk020a6588::func_0c(short a) {
    if (func_28() == true) {
        return true;
    }
    if (unk8 == 0) {
        return false;
    }
    unkc = a;
    if (unk4 > (unk6 = 0x10)) {
        unk4 = 0x10;
    }
    unk8 = 0;
    int system = func_020a18e4();
    if (func_020a14d8(system) == 1) {
        func_020a14e0(system, 0);
    }
    if (!(flags & 4)) {
        state = 1;
        flags |= 0xc;
    }
    flags |= 1;
    return false;
}

bool Unk020a6588::func_10() {
    int system = func_020a18e4();
    if (func_2c() == true) {
        return true;
    }
    if (unk8 == 3) {
        return false;
    }
    unk6 = 0x10;
    if (unk4 > 0x10) {
        unk4 = 0x10;
    }
    unk8 = 3;
    func_020897b4("Microgame screen being hidden");
    func_020a1494(system, 2, 0x10);
    func_020a11f8(system, 2, 1);
    flags &= ~1;
    return false;
}

bool Unk020a6588::func_14() {
    return (flags & 2) != 0;
}

void Unk020a6588::func_18() {
    func_020897b4("ForceDismiss");
    flags |= 2;
}

void Unk020a6588::func_1c() {
    func_020897b4("ClearDismissed");
    flags &= ~2;
}

bool Unk020a6588::func_28() {
    return unk8 == 2 || unk8 == 1;
}

bool Unk020a6588::func_2c() {
    return unk8 == 5 || unk8 == 4;
}

bool Unk020a6588::func_34() {
    return false;
}

void Unk020a6588::func_38(int a) {
    if (func_2c() == true || a == 0) {
        return;
    }
    switch (unk8) {
    case 0:
        unk4++;
        if (unk4 >= unk6) {
            unk4 = unk6;
            unk8 = 1;
        }
        break;
    case 3:
        unk4--;
        if (unk4 <= 0) {
            unk4 = 0;
            unk8 = 4;
        }
        break;
    case 4:
        unk8 = 5;
        break;
    case 1:
        unk8 = 2;
        break;
    }
    if (unk8 == 4) {
        int system = func_020a18e4();
        if (func_14() == true && func_020a14d8(system) == 0) {
            func_020a14e0(system, 1);
        }
        if (flags & 4) {
            state = 3;
            flags = (flags | 8) & ~4;
        }
    }
}

bool Unk020a6588::func_3c() {
    return true;
}

bool Unk020a6588::func_20() {
    return false;
}

void Unk020a6588::func_24() {}
