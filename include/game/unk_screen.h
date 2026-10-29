/*
 * The screens built on archive layouts (unit_020450D4.cpp to
 * unit_0204A9F8.cpp): their empty base, the base of the pages, the layout and
 * name list classes of the engine, their show / hide timer and what they use
 * of the button, panel and animated sprite widgets (unit_02050640.cpp,
 * unit_02051704.cpp, unit_0204F798.cpp). Layouts come from the code; all
 * names are placeholders.
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

    u32 unk0[3];
};

/* A layout of one screen (0x7C bytes). */
class Unk020a9d58 {
public:
    Unk020a9d58(Unk02093648 *archive, int screen);
    ~Unk020a9d58();

    u8 unk0[0x7c];
};

/* The empty base of the screens: an out-of-line destructor and no vtable. */
class Unk020a07d4 {
public:
    ~Unk020a07d4();
};

class Unk02050640 : public Unk020b9e88 {
public:
    Unk02050640();
    ~Unk02050640();
    void func_02050838(Unk020a7c90 *sprite, bool flag);
    void func_020508a4(Unk020a7c90 *icon);
    void func_02050914(u32 count);
    void func_02050968(Unk020a7c90 *sprite);
    void func_02050ad0(u32 sound);
    void func_02050c48(short a, short b, short c);
    void func_02050c64(short a, short b, short c);
    void func_08();
    bool func_0c(bool done);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);

    Unk020b9e88Touch touch;
    u8 unk38[0x48];
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
    void func_18(bool show);
    void func_14(int x, int y);
    void func_08();
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

typedef void *(*Unk020a9d58Text)(u32 id, void *user);

extern "C" {
void func_020aba38(Unk02093648 *archive, u32 hash, Unk020a9d58 *layout, Unk020a7af4 *names);
void func_020a9db8(Unk020a9d58 *layout, Unk020a9d58Text text, void *user);
void *func_020a154c(u32 id, void *user);
u32 func_020a7b50(Unk020a7af4 *names, u32 hash);
Unk020a7c90 *func_020aa040(Unk020a9d58 *layout, int type, u16 index);
void func_020aa06c(Unk020a9d58 *layout, bool shown);
void func_020aa158(Unk020a9d58 *layout);
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
 * The owner of the pages (a window of unit_0206BCE0.cpp): the slot the pages
 * call and the next page.
 */
class Unk02044234 {
public:
    virtual ~Unk02044234();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();

    u8 unk4[0x38];
    int nextPage;
    int unk40;
    u8 unk44;
};

/*
 * The base of the pages built by Unk02044234 (vtable 0x020B998C, functions
 * 0x020465BC-0x02046B7C). Its inline slots 7, 8, 9 and 13 are emitted by
 * every page; the kept copies are those of the first page,
 * unit_020450D4.cpp. Slots 5, 10, 11, 12 and 17 point to functions of other
 * files (0x0201D6CC, 0x02044830 to 0x02044EC0) whose classes are unknown:
 * they are declared here non-inline under slot names, so the vtables do not
 * match there.
 */
class Unk020465bc : public Unk020a07d4 {
public:
    Unk020465bc(Unk02044234 *owner);
    virtual ~Unk020465bc();
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
    virtual bool func_34() {
        return true;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);
    virtual void func_40();
    virtual void func_44(bool a);
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
