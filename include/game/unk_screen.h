/*
 * The screens built on archive layouts (unit_0203FA44.cpp to
 * unit_0204A9F8.cpp): their empty base, the screen base Unk0203c188 and its
 * owner, the owner and the base of the pages,
 * the layout and name list classes of the engine, their show / hide timer and
 * what they use of the button, panel and animated sprite widgets
 * (unit_02050640.cpp, unit_02051704.cpp, unit_0204F798.cpp) and of the sprite
 * meter (unit_0204EB78.cpp). Layouts come from the code; all names are
 * placeholders.
 */
#ifndef GAME_UNK_SCREEN_H
#define GAME_UNK_SCREEN_H

#include "game/unk_archive.h"
#include "game/unk_widget.h"

/* An entry of a name list (8 bytes). */
struct Unk020a7af4Entry {
    u32 unk0;
    u32 unk4;
};

/* A name list over a caller's buffer, filled when a layout is loaded. */
class Unk020a7af4 {
public:
    Unk020a7af4(Unk020a7af4Entry *entries, int count);
    ~Unk020a7af4();

    Unk020a7af4Entry *entries;
    int count;
    int used;
};

class Unk020a7aa0;
class Unk020a6dd8;

typedef void *(*Unk020a9d58Text)(u32 id, void *user);

/* A layout of one screen (0x7C bytes): the sprites of each of its thirteen types. */
class Unk020a9d58 {
public:
    Unk020a9d58(Unk02093648 *archive, int screen);
    ~Unk020a9d58();

    Unk020a7aa0 **items[13];
    int counts[13];
    Unk02093648 *archive;
    Unk020a9d58Text text;
    void *user;
    volatile u32 flags;
    Unk020a6dd8 *button;
};

/*
 * The abstract root of the screens. It has no vtable in the binary and its
 * only function is the base destructor 0x020A07D4 (`bx lr`): a pure virtual
 * destructor with a body, an abstract class whose implicit constructor stores
 * no vptr (the derived constructors store only their own). Slot 12, func_30
 * (`return func_28() && !func_14();`), is 0x0201D6CC, slot 12 of the screens
 * that do not override it: an inline function whose kept copy sits after the
 * inline slots of the first screen (0x0201C598). It is declared non-inline
 * here: while that copy is assembly, the copies every file would emit clash
 * with it at link time. The pure slots 2 to 11 are a hypothesis: no copy of
 * them exists.
 */
class Unk020a07d4 {
public:
    virtual ~Unk020a07d4() = 0;
    virtual void func_08() = 0;
    virtual bool func_0c(short a) = 0;
    virtual bool func_10() = 0;
    virtual bool func_14() = 0;
    virtual void func_18() = 0;
    virtual void func_1c() = 0;
    virtual bool func_20() = 0;
    virtual void func_24() = 0;
    virtual bool func_28() = 0;
    virtual bool func_2c() = 0;
    virtual bool func_30();
};

/*
 * The object that owns the screens on Unk0203c188 (it keeps the current one at
 * 0x24 and builds it with new): the survival guide Unk02027994
 * (unit_02027994.cpp), only what the screens use.
 */
class Unk0203c188Owner {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();

    u8 unk4[0xb4];
    u16 flagsb8;
};

class Unk0209487c;

class Unk02050640 : public Unk020b9e88 {
public:
    Unk02050640();
    ~Unk02050640();
    void func_02050838(Unk020a7c90 *sprite, bool flag);
    void func_020508a4(Unk020a7c90 *icon);
    void func_020508ac(u32 hash);
    void func_02050914(u32 count);
    void func_02050968(Unk020a7c90 *sprite);
    int func_02050a24();
    Unk020a7c90 *func_02050a40(int index);
    void func_02050a4c(int a);
    void func_02050a64(bool toggle, bool lock);
    void func_02050aac(bool on);
    void func_02050ad0(u32 sound);
    void func_02050bb4(short a, short b, short c, short d);
    void func_02050bf0(short a, short b, short c, short d, short e, short f);
    void func_02050c48(int a, int b, int c);
    void func_02050c64(int a, int b, int c);
    void func_02050c80(short a, short b);
    void func_02050c94(short a, short b);
    void func_020514f0();
    void func_08();
    bool func_0c(bool done);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);

    Unk020b9e88Touch touch;
    Unk020b9e88Touch touch2;
    Unk0209487c *file;
    Unk020a7c90 *sprite;
    Unk020a7c90 *icon;
    u32 spriteCap;
    u32 spriteCount;
    Unk020a7c90 **sprites;
    Unk02098bc8 rect;
    signed char unk64;
    signed char unk65[0x14];
    u32 sound;
    u16 flags;
};

class Unk02051704 : public Unk020b9e88 {
public:
    Unk02051704();
    ~Unk02051704();
    void func_02051804(unsigned int count);
    void func_02051858(Unk020a7c90 *sprite);
    void func_020518a8(unsigned int count);
    void func_020518fc(Unk020b9e88 *child);
    Unk020a7c90 *func_02051ad0(int index);
    void func_02051adc(Unk020b9e88 *child, int index);
    void func_02051ae8(Unk020a7c90 *sprite, int index);
    void func_08();
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);

    u8 unk34[0x28];
};

class Unk0204f798 : public Unk020b9e88 {
public:
    Unk0204f798();
    ~Unk0204f798();
    void func_0204f8a0(int n);
    void func_0204f8f4(Unk020a7c90 *sprite);
    void func_0204fa10(int first, int last);
    void func_18(bool show);
    void func_14(int x, int y);
    void func_08();
    Unk020a7c90 *func_0204fda8(int index);
    void func_0204fdb4();
    void func_0204fdcc(bool loop);
    Unk02098bc8 *func_10();

    Unk02098bc8 rect;
    unsigned int capacity;
    unsigned int count;
    Unk020a7c90 **sprites;
    int flags;
    int counter;
    int delay;
    int step;
    int first;
    int last;
};

/* A scaled sprite meter (unit_0204EB78.cpp). */
class Unk0204eb78 {
public:
    Unk0204eb78();
    ~Unk0204eb78();
    void func_0204ebd4(int mode);
    void func_0204ebdc(Unk020a7c90 *arrow);
    void func_0204ebe4(Unk020a7c90 *sprite);
    void func_0204ec10(Unk020a7c90 *blink);
    bool func_0204ec18();
    void func_0204ec2c(int target);
    void func_0204ec44();

    Unk020a7c90 *sprite;
    Unk020a7c90 *blink;
    Unk020a7c90 *arrow;
    Unk02098bc8 rect;
    short value;
    short target;
    int mode;
    int counter;
};

extern "C" {
int func_020aba38(Unk02093648 *archive, u32 hash, Unk020a9d58 *layout, Unk020a7af4 *names);
void func_020a9db8(Unk020a9d58 *layout, Unk020a9d58Text text, void *user);
void *func_020a154c(u32 id, void *user);
u32 func_020a7b50(Unk020a7af4 *names, u32 hash);
Unk020a7c90 *func_020aa040(Unk020a9d58 *layout, int type, u16 index);
void func_020aa06c(Unk020a9d58 *layout, bool shown);
void func_020aa158(Unk020a9d58 *layout);
}

/*
 * A sprite of a layout by its index. The local and the `u32` index are needed:
 * written as a direct call, the index truncations of long constructors go
 * through the other one of r0 / r1. Real form unknown.
 */
static inline Unk020a7c90 *func_sprite(Unk020a9d58 *layout, int type, u32 index) {
    Unk020a7c90 *sprite = func_020aa040(layout, type, index);
    return sprite;
}

/* A show / hide timer: 0 opening, 1 opened, 2 shown, 3 closing, 4 closed, 5 hidden. */
struct Unk020a07d4Timer {
    Unk020a07d4Timer() {
        timer = 0;
        duration = 0x3c;
        state = 5;
    }

    inline void func_step() {
        switch (state) {
        case 0:
            timer++;
            if (timer >= duration) {
                timer = duration;
                state = 1;
            }
            break;
        case 3:
            timer--;
            if (timer <= 0) {
                timer = 0;
                state = 4;
            }
            break;
        case 4:
            state = 5;
            break;
        case 1:
            state = 2;
            break;
        }
    }

    inline void func_duration(short duration) {
        this->duration = duration;
        if (timer > this->duration) {
            timer = this->duration;
        }
    }

    inline bool func_hidden() const {
        return state == 5 || state == 4;
    }

    inline bool func_shown() const {
        return state == 2 || state == 1;
    }

    inline bool func_opening() const {
        return state == 0;
    }

    inline bool func_opened() const {
        return state == 1;
    }

    inline bool func_closing() const {
        return state == 3;
    }

    inline bool func_moving() const {
        return state == 0 || state == 3;
    }

    short timer;
    short duration;
    int state;
};

/*
 * A base of the screens owned by Unk0203c188Owner (vtable 0x020B9604,
 * unit_0203C188.cpp). Its inline slots are emitted by every file that
 * needs them and the first copies are kept in unit_02021CBC.cpp: func_34 and
 * func_28 to func_24 at 0x02023884-0x020238EC, func_40 at 0x0202227C. They are
 * declared non-inline here, so the derived files do not emit copies that would
 * clash with them. Slots 3, 4, 14 and 15 are pure (null in the base vtable).
 */
class Unk0203c188 : public Unk020a07d4 {
public:
    Unk0203c188(Unk0203c188Owner *owner);
    virtual ~Unk0203c188();
    virtual void func_08();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual bool func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_34();
    virtual void func_38(bool active) = 0;
    virtual bool func_3c(bool done) = 0;
    virtual void func_40(bool a);

    u16 flags;
    Unk0203c188Owner *owner;
    Unk020a07d4Timer fade;
};

class Unk020465bc;

/* An object the owner deletes once the system no longer lists it. */
class Unk02044234Child {
public:
    virtual ~Unk02044234Child();
};

/*
 * A key sequence of the owner (unit_02043FBC.cpp): up to five masks of
 * released buttons to enter in order while L and R are held (button indices
 * of unit_020970E0.cpp); slot 0 runs once the sequence is complete.
 */
class Unk02044088 {
public:
    Unk02044088() {
        count = 0;
        index = 0;
    }

    virtual void func_00() = 0;

    void func_02044088(int a, int b, int c, int d, int e);
    bool func_02044118(int keys);

    int keys[5];
    int count;
    int index;
};

/* The owner's sequence: adds 100 to each of the player's six motives. */
class Unk020441c8 : public Unk02044088 {
public:
    virtual void func_00();
};

/*
 * The owner of the pages (0x22C bytes, vtable 0x020B97BC, unit_02043FBC.cpp),
 * a window of unit_0206BCE0.cpp: a show / hide timer, six motive meters, a
 * panel with a back button and the text of the page, and the current page,
 * replaced when a page sets nextPage.
 */
class Unk02044234 : public Unk020a07d4 {
public:
    Unk02044234(int page);
    virtual ~Unk02044234();
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c() {
        flags &= ~4;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_30();

    void func_02044a44();
    void func_02044a94();
    void func_02044f24();
    void func_02045050();

    Unk020a07d4Timer fade;
    Unk020441c8 sequence;
    u32 flags;
    u8 unk30;
    int unk34;
    int page;
    int nextPage;
    int unk40;
    u8 unk44;
    Unk020465bc *current;
    Unk02044234Child *unk4c;
    Unk020a9d58 *layout50;
    Unk020a9d58 *layout54;
    Unk02050640 button;
    Unk020a7c90 *text;
    Unk02051704 panel;
    Unk0204eb78 meters[6];
};

/*
 * The base of the pages built by Unk02044234 (vtable 0x020B998C, functions
 * 0x020465BC-0x02046B7C). Its inline slots are emitted by every file that
 * needs them and the first copy is kept: slots 5, 10, 11 and 17 in the
 * owner's file (0x02044830 to 0x02044EC0, each next to the owner function
 * that first calls it), slots 7, 8, 9 and 13 in the first page,
 * unit_020450D4.cpp. Slot 12 is the root's func_30 (0x0201D6CC).
 */
class Unk020465bc : public Unk020a07d4 {
public:
    Unk020465bc(Unk02044234 *owner);
    virtual ~Unk020465bc();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14() {
        return (flags & 4) != 0;
    }
    virtual void func_18();
    virtual void func_1c() {
        flags &= ~4;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28() {
        return fade.func_shown();
    }
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual bool func_34() {
        return true;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);
    virtual void func_40();
    virtual void func_44(bool a) {
        if (a) {
            flags |= 8;
        } else {
            flags &= ~8;
        }
    }
    virtual void func_48();
    virtual void func_4c();
    virtual void func_50();

    void func_020468d4();
    void func_02046920();
    void func_02046960();
    void func_02046a94(Unk020a9d58 *layout, Unk020a7af4 *names);

    int unk4;
    u16 flags;
    short unka;
    Unk02044234 *owner;
    Unk020a07d4Timer fade;
    Unk02051704 panel18;
    Unk02050640 button74;
};

#endif
