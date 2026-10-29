/*
 * Unit 0x020471B0-0x02047A8C: a small screen (Unk020471b0, 0x144 bytes, vtable
 * 0x020B9A44) built by the game state of unit_02072BEC.cpp. It loads a bottom
 * and a top layout from the archive of the system, shows a first panel with
 * one text (or the text id the caller sets at 0x13C) and, once that panel is
 * done, a second panel holding an animated sprite widget that blinks while a
 * counter runs (frames 0x1E to 0xAE).
 *
 * Bounds: hypothesis. The start is the constructor, after the slots of the
 * class with vtable 0x020B99E8 (0x020471AC); the class's inline virtual
 * functions end the file before unit_02047A8C.cpp. `.data` is this class's
 * vtable with its header. Real file name unknown.
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

extern Unk020d6240 data_020d6240;

extern "C" {
Unk020d6240 *func_020a18e4();
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
void func_020a11f8(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a716c(Unk020a7c90 *s, int text);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
}

class Unk020471b0 : public Unk020a07d4 {
public:
    Unk020471b0();
    virtual ~Unk020471b0();
    virtual void func_08();
    virtual bool func_0c();
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18() {
        flags |= 2;
    }
    virtual void func_1c() {
        flags &= ~2;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28();
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual bool func_30();
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done) {
        return true;
    }

    void func_020476e4();
    void func_02047764();

    u32 flags;
    Unk020a07d4Timer fade;
    Unk020a9d58 *bottom;
    Unk020a9d58 *top;
    int counter;
    Unk02051704 panel1c;
    Unk02051704 panel78;
    Unk0204f798 widget;
    int text;
    Unk020a7c90 *message;
};

/*
 * 98.81 %: one instruction scheduled differently; the original sets r1 to 1
 * after the store of the widget flags, here it is set before the `bic`
 * (local, inline setter and reuse of the field tried).
 */
Unk020471b0::Unk020471b0() : flags(0), bottom(0), top(0), counter(0), text(0) {
    Unk020a7af4Entry bottomEntries[10];
    Unk020a7af4Entry topEntries[10];
    Unk020a7af4 bottomNames(bottomEntries, 10);
    Unk020a7af4 topNames(topEntries, 10);
    Unk02093648 *archive = func_020a18e4()->archive;

    bottom = new Unk020a9d58(archive, 1);
    func_020aba38(archive, 0xe69c219f, bottom, &bottomNames);
    func_020a9db8(bottom, func_020a154c, 0);
    top = new Unk020a9d58(archive, 0);
    func_020aba38(archive, 0x5585fd88, top, &topNames);
    func_020a9db8(top, func_020a154c, 0);
    panel1c.func_02051804(2);
    panel1c.func_02051858(func_020aa040(top, 4, func_020a7b50(&topNames, 0x6ed164d4)));
    panel1c.func_02051858(func_020aa040(bottom, 2, func_020a7b50(&bottomNames, 0x516e4073)));
    panel1c.func_34(0x55);
    message = func_020aa040(top, 4, func_020a7b50(&topNames, 0x2b777355));
    widget.func_0204fdcc(false);
    widget.flags &= ~4;
    widget.delay = 1;
    widget.func_0204f8a0(1);
    widget.func_0204f8f4(func_020aa040(bottom, 2, func_020a7b50(&bottomNames, 0xb29e8427)));
    panel78.func_020518a8(1);
    panel78.func_02051804(1);
    panel78.func_020518fc(&widget);
    panel78.func_02051858(func_020aa040(top, 4, func_020a7b50(&topNames, 0xdc831a1d)));
    panel78.func_34(0x55);
}

Unk020471b0::~Unk020471b0() {
    func_02047764();
    delete bottom;
    delete top;
}

void Unk020471b0::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

bool Unk020471b0::func_0c() {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_020476e4();
    fade.func_duration(0xf);
    fade.timer = 0;
    fade.state = 0;
    func_020a1494(func_020a18e4(), 2, 0xf);
    func_020a122c(func_020a18e4());
    return false;
}

bool Unk020471b0::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0xf);
    fade.timer = fade.duration;
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0xf);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

bool Unk020471b0::func_30() {
    if (func_28() && !func_14()) {
        return true;
    }
    return false;
}

bool Unk020471b0::func_14() {
    return (flags & 2) != 0;
}

bool Unk020471b0::func_28() {
    return fade.func_shown();
}

void Unk020471b0::func_020476e4() {
    func_02047764();
    if (text == 0) {
        panel1c.func_28(0x55);
    } else {
        func_020a7cf0(panel1c.func_02051ad0(0), false);
        func_020a716c(message, text);
        func_020a7cf0(message, true);
    }
    func_020aa06c(bottom, true);
    func_020aa06c(top, true);
    flags |= 1;
}

void Unk020471b0::func_02047764() {
    if (!(flags & 1)) {
        return;
    }
    func_020aa06c(bottom, false);
    func_020aa06c(top, false);
    flags &= ~1;
}

void Unk020471b0::func_38(bool active) {
    if (fade.func_hidden() | !active) {
        return;
    }
    fade.func_step();
    if (panel1c.func_40()) {
        panel1c.func_30(0xf);
        panel1c.func_2c(0xf);
        func_020a1494(func_020a18e4(), 2, 0xf);
        func_020a11f8(func_020a18e4(), 2, 1);
    } else if (panel1c.func_44()) {
        panel1c.func_18(false);
        panel78.func_18(true);
        panel78.func_34(0xf);
        panel78.func_28(0xf);
        func_020a1494(func_020a18e4(), 2, 0xf);
        func_020a122c(func_020a18e4());
    } else if (panel78.func_40()) {
        widget.flags |= 4;
        func_020a2ce8(func_020a2994(), 0x49e98b28, 0x7f, 0);
    }
    if (panel78.func_38()) {
        if (counter < 0x1e || counter > 0xae) {
            widget.flags |= 4;
        } else {
            widget.flags &= ~4;
        }
        counter++;
    }
    if (widget.flags & 2) {
        func_18();
    }
    panel1c.func_08();
    panel78.func_08();
    func_020aa158(bottom);
    func_020aa158(top);
    if (fade.state == 4) {
        func_02047764();
    }
}
