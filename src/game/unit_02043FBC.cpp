/*
 * Unit 0x02043FBC-0x020450D4: the owner of the pages (Unk02044234, 0x22C
 * bytes, vtable 0x020B97BC, declared in include/game/unk_screen.h), built by
 * the main game state of unit_0206BCE0.cpp with its first page. It shows six
 * motive meters and a panel with a back button and a text set by the pages,
 * builds the five pages (unit_020450D4.cpp to unit_02046B7C.cpp) and replaces
 * the current one when a page sets nextPage. A key sequence entered while L
 * and R are held adds 100 to each motive.
 *
 * Bounds: hypothesis. The start is the mask of released buttons the sequence
 * reads, after the inline slots of the class at 0x02043xxx (0x02043FB8); the
 * owner's inline slots (0x020450B0-0x020450D0) end the file before the first
 * page, unit_020450D4.cpp. `.data` is the owner's vtable and the sequence's
 * two vtables, with their headers. Real file name unknown.
 *
 * The inline slots 5, 10, 11 and 17 of the page base are kept here, each
 * after the first function that calls it.
 *
 * Not complete although every function and `.data` match: the owner's
 * inline slots are emitted in slot order (func_1c, func_20, func_24,
 * func_34) where the original has func_34 first.
 */

#include "game/unk_screen.h"

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The main game state (unit_0206BCE0.cpp): only the field used here. */
struct Unk0206bcf0 {
    int unk0;
    int unk4;
    int unk8;
};

/* The player (data_020c43a8). */
struct Unk020c43a8;

/* The five pages: only their size and constructor. */
class Unk02045bac : public Unk020465bc {
public:
    Unk02045bac(Unk02044234 *owner);
    virtual ~Unk02045bac();

    u8 unkf8[0x190];
};

class Unk02046104 : public Unk020465bc {
public:
    Unk02046104(Unk02044234 *owner);
    virtual ~Unk02046104();

    u8 unkf8[0x10c];
};

class Unk020450d4 : public Unk020465bc {
public:
    Unk020450d4(Unk02044234 *owner);
    virtual ~Unk020450d4();

    u8 unkf8[0x10c];
};

class Unk020455a0 : public Unk020465bc {
public:
    Unk020455a0(Unk02044234 *owner);
    virtual ~Unk020455a0();

    u8 unkf8[0x198];
};

class Unk02046b7c : public Unk020465bc {
public:
    Unk02046b7c(Unk02044234 *owner);
    virtual ~Unk02046b7c();

    u8 unkf8[0x118];
};

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;

bool func_02097248(int button);
bool func_02097298(int button);
bool func_020972c0(int button);

extern "C" {
u32 func_02043fbc();
void func_02044f14(Unk02044234 *owner, int text);
Unk020d6240 *func_020a18e4();
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
void func_020a11f8(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a716c(Unk020a7c90 *s, int text);
void *func_020a2994();
void func_0209b178(int a, int b);
Unk0206bcf0 *func_0206bce0();
void func_020662c8(Unk020c43a8 *p, int i, int n);
int func_0206647c(Unk020c43a8 *p, int i);
}

/* The released buttons A, B, Right, Left, Up, Down, R and L as a mask. */
u32 func_02043fbc() {
    u32 keys = 0;
    keys |= func_020972c0(0) ? 1 : 0;
    keys |= func_020972c0(1) ? 2 : 0;
    keys |= func_020972c0(4) ? 4 : 0;
    keys |= func_020972c0(5) ? 8 : 0;
    keys |= func_020972c0(6) ? 0x10 : 0;
    keys |= func_020972c0(7) ? 0x20 : 0;
    keys |= func_020972c0(8) ? 0x40 : 0;
    keys |= func_020972c0(9) ? 0x80 : 0;
    return keys;
}

void Unk02044088::func_02044088(int a, int b, int c, int d, int e) {
    count = 0;
    index = 0;
    if (a == 0) {
        return;
    }
    keys[0] = a;
    count++;
    if (b == 0) {
        return;
    }
    keys[1] = b;
    count++;
    if (c == 0) {
        return;
    }
    keys[2] = c;
    count++;
    if (d == 0) {
        return;
    }
    keys[3] = d;
    count++;
    if (e == 0) {
        return;
    }
    keys[4] = e;
    count++;
}

bool Unk02044088::func_02044118(int keys) {
    if (index == -1) {
        if ((keys & 0x80) && (keys & 0x40)) {
            index = 0;
        }
    } else if (func_02097248(9) && func_02097248(8) && keys != 0) {
        if (keys == this->keys[index]) {
            index++;
            if (index >= count) {
                func_00();
                index = -1;
                return true;
            }
        } else {
            index = -1;
        }
    }
    return false;
}

void Unk020441c8::func_00() {
    func_020662c8(&data_020c43a8, 0, 100);
    func_020662c8(&data_020c43a8, 1, 100);
    func_020662c8(&data_020c43a8, 4, 100);
    func_020662c8(&data_020c43a8, 2, 100);
    func_020662c8(&data_020c43a8, 3, 100);
    func_020662c8(&data_020c43a8, 5, 100);
}

Unk02044234::Unk02044234(int page)
    : flags(0), unk30(0), unk34(page), page(page), nextPage(page), unk40(-1), unk44(0), current(0), unk4c(0) {
    {
        Unk020a7af4Entry entries[0x1e];
        Unk020a7af4 names(entries, 0x1e);

        layout54 = new Unk020a9d58(func_020a18e4()->archive, 0);
        func_020aba38(func_020a18e4()->archive, 0x9a8de0a8, layout54, &names);
        func_020a9db8(layout54, func_020a154c, 0);
        button.func_02050838(func_020aa040(layout54, 0xb, func_020a7b50(&names, 0xc2f94842)), false);
        button.func_02050c48(0, 1, -1);
        Unk020a7c90 *s = func_020aa040(layout54, 2, func_020a7b50(&names, 0x4d1ce715));
        func_020a7c90(s, -0x23000);
        panel.func_14(-0x23000, func_020a7cc0(s));
        panel.func_20(-0x146000, -0x23000);
        panel.func_02051804(3);
        panel.func_02051858(s);
        text = func_020aa040(layout54, 4, func_020a7b50(&names, 0xa01737f8));
        panel.func_02051858(text);
        panel.func_02051858(func_020aa040(layout54, 0xb, func_020a7b50(&names, 0xb0943cd7)));
    }
    {
        Unk020a7af4Entry entries[0x1e];
        Unk020a7af4 names(entries, 0x1e);

        layout50 = new Unk020a9d58(func_020a18e4()->archive, 1);
        func_020aba38(func_020a18e4()->archive, 0x2794b249, layout50, &names);
        for (int i = 0; i < 6; i++) {
            meters[i].func_0204ebd4(1);
            meters[i].func_0204ebe4(func_020aa040(layout50, 1, func_020a7b50(&names, 0x1f19df27 + i)));
            meters[i].func_0204ec10(func_020aa040(layout50, 1, func_020a7b50(&names, 0xc56fae8c + i)));
            meters[i].func_0204ebdc(func_020aa040(layout50, 1, func_020a7b50(&names, 0x0e5f7d4a + i)));
        }
        meters[3].func_0204ebd4(2);
        meters[4].func_0204ebd4(2);
        meters[5].func_0204ebd4(2);
    }
    sequence.func_02044088(0x20, 0x10, 4, 1, 8);
}

Unk02044234::~Unk02044234() {
    func_02044a94();
    delete current;
    delete layout50;
    delete layout54;
    if (unk44) {
        func_0206bce0()->unk8 = 2;
    }
}

bool Unk02044234::func_30() {
    bool ready;
    if (current == 0) {
        ready = false;
    } else if (current->func_28() && !current->func_14()) {
        ready = true;
    } else {
        ready = false;
    }
    return func_28() && !func_14() && panel.func_38() && ready;
}

bool Unk02044234::func_14() {
    return (flags & 4) != 0;
}

void Unk02044234::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
    func_02044f24();
    func_020a14e0(func_020a18e4(), 0);
    func_020a2994();
    func_0209b178(10, 0);
    func_020a2994();
    func_0209b178(11, 0);
}

bool Unk02044234::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    unk30 = a;
    fade.func_duration(0x10);
    fade.timer = 0;
    fade.state = 0;
    func_02044a44();
    flags |= 0x10;
    return false;
}

bool Unk02044234::func_28() {
    return fade.func_shown();
}

bool Unk02044234::func_2c() {
    return fade.func_hidden() && current->func_2c();
}

bool Unk02044234::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.timer = fade.duration;
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

void Unk02044234::func_02044a44() {
    if (flags & 2) {
        return;
    }
    panel.func_30(0x1c);
    func_020aa06c(layout50, true);
    func_020aa06c(layout54, true);
    flags |= 2;
}

void Unk02044234::func_02044a94() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout50, false);
    func_020aa06c(layout54, false);
    flags &= ~2;
}

bool Unk02044234::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    if (!done && func_02097298(3)) {
        done = true;
        func_18();
    }
    done = button.func_0c(done);
    if (button.touch.flags & 8) {
        func_18();
    }
    sequence.func_02044118(func_02043fbc());
    return done;
}

void Unk02044234::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    button.func_08();
    panel.func_08();
    meters[0].func_0204ec2c(func_0206647c(&data_020c43a8, 0) / 39062);
    meters[1].func_0204ec2c(func_0206647c(&data_020c43a8, 1) / 39062);
    meters[2].func_0204ec2c(func_0206647c(&data_020c43a8, 4) / 39062);
    meters[3].func_0204ec2c(func_0206647c(&data_020c43a8, 2) / 39062);
    meters[4].func_0204ec2c(func_0206647c(&data_020c43a8, 3) / 39062);
    meters[5].func_0204ec2c(func_0206647c(&data_020c43a8, 5) / 39062);
    for (int i = 0; i < 6; i++) {
        meters[i].func_0204ec44();
    }
    if (flags & 8) {
        if (panel.func_44()) {
            panel.func_28(0x1c);
        }
        if (panel.func_40()) {
            flags &= ~8;
        }
    }
    func_020aa158(layout50);
    func_020aa158(layout54);
    if (unk4c != 0 && !func_020a0b8c(data_020d6240.unk8, unk4c)) {
        delete unk4c;
        unk4c = 0;
    }
    if (page != nextPage) {
        if (func_30()) {
            current->func_44(true);
            current->func_18();
            func_02045050();
        }
        if (!func_020a0b8c(data_020d6240.unk8, current)) {
            func_02044f24();
        }
    }
    if (flags & 0x10) {
        func_020a1494(func_020a18e4(), 2, 0x10);
        func_020a122c(func_020a18e4());
        flags &= ~0x10;
    }
    if (fade.state == 4) {
        func_02044a94();
    }
}

void Unk02044234::func_18() {
    flags |= 4;
    current->func_44(false);
    current->func_18();
}

void func_02044f14(Unk02044234 *owner, int text) {
    func_020a716c(owner->text, text);
}

void Unk02044234::func_02044f24() {
    delete current;
    current = 0;
    unk40 = page;
    switch (page = nextPage) {
    case 0:
        current = new Unk02045bac(this);
        break;
    case 1:
        current = new Unk02046104(this);
        break;
    case 2:
        current = new Unk020450d4(this);
        break;
    case 3:
        current = new Unk020455a0(this);
        break;
    case 4:
        current = new Unk02046b7c(this);
        break;
    }
    if (page != unk40) {
        current->func_44(true);
    }
    current->func_08();
}

void Unk02044234::func_02045050() {
    flags |= 8;
    panel.func_20(-0x146000, -0x23000);
    panel.func_30(0x1c);
    panel.func_2c(0x1c);
}
