/*
 * Unit 0x020970E0-0x020973BC: button state. data_020c7f80 keeps the held, released
 * and pressed masks of the twelve buttons (KEYINPUT plus the X / Y bits that the
 * ARM7 copies to 0x027FFFA8) and a flag word; data_020c7f8c keeps, per button, a
 * press counter (reset to 1 after more than 16 idle frames), the held frames and the
 * idle frames. With flag bit 0 set, the queries swap the buttons for the other hand
 * (A / Right, B / Down, X / Up, Y / Left, L / R).
 *
 * Bounds: hypothesis. Before 0x020970E0 lies graphics setup code (VRAM banks);
 * func_020973bc after it sets up other objects. __sinit_020ae310 builds the counter
 * array with func_020973a8. Real file name unknown.
 */

typedef unsigned short u16;

struct Unk020c7f80 {
    u16 held;
    u16 released;
    u16 pressed;
    int flags;
};

class Unk020c7f8c {
public:
    Unk020c7f8c();

    int presses;
    int heldFrames;
    int idleFrames;
};

Unk020c7f80 data_020c7f80;
Unk020c7f8c data_020c7f8c[14];

bool func_02097248(int button);
bool func_02097270(int button);
bool func_02097298(int button);
bool func_020972c0(int button);
bool func_020972e8();
int func_02097304(int button);

void func_020970e0() {
    data_020c7f80.held = 0;
    data_020c7f80.released = 0;
    data_020c7f80.pressed = 0;
    data_020c7f80.flags = 0;
}

void func_02097100() {
    u16 old;
    u16 keys;
    Unk020c7f8c *p;
    int i;
    u16 cur;

    keys = ((*(volatile u16 *)0x4000130 | *(volatile u16 *)0x27fffa8) ^ 0x2fff) & 0x2fff;
    old = data_020c7f80.held;
    data_020c7f80.held = keys & ~0x1000;
    data_020c7f80.held |= ((*(volatile u16 *)0x27fffa8 & 0x8000) >> 15) ? 0x1000 : 0;
    cur = data_020c7f80.held;
    data_020c7f80.pressed = cur & ~old;
    data_020c7f80.released = old & ~cur;

    p = data_020c7f8c;
    for (i = 0; i < 14; i++) {
        if (func_02097298(i)) {
            p->heldFrames = 0;
            if (p->idleFrames <= 0x10) {
                p->presses++;
            } else {
                p->presses = 1;
            }
        }
        if (func_020972c0(i)) {
            p->idleFrames = 0;
        }
        if (!func_02097298(i) && func_02097248(i)) {
            p->heldFrames++;
        }
        if (!func_020972c0(i) && func_02097270(i)) {
            p->idleFrames++;
        }
        p++;
    }
}

bool func_02097248(int button) {
    return data_020c7f80.held & (1 << func_02097304(button));
}

bool func_02097270(int button) {
    return !(data_020c7f80.held & (1 << func_02097304(button)));
}

bool func_02097298(int button) {
    return data_020c7f80.pressed & (1 << func_02097304(button));
}

bool func_020972c0(int button) {
    return data_020c7f80.released & (1 << func_02097304(button));
}

bool func_020972e8() {
    return data_020c7f80.flags & 1;
}

int func_02097304(int button) {
    if (func_020972e8()) {
        switch (button) {
        case 0:
            button = 4;
            break;
        case 1:
            button = 7;
            break;
        case 10:
            button = 6;
            break;
        case 11:
            button = 5;
            break;
        case 6:
            button = 10;
            break;
        case 7:
            button = 1;
            break;
        case 5:
            button = 11;
            break;
        case 4:
            button = 0;
            break;
        case 9:
            button = 8;
            break;
        case 8:
            button = 9;
            break;
        }
    }
    return button;
}

Unk020c7f8c::Unk020c7f8c() {
    presses = 0;
    heldFrames = 0;
    idleFrames = 0;
}
