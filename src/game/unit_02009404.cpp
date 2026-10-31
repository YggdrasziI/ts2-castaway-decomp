/*
 * Unit 0x02009404-0x02009794: the action "Sim Animation" and its two derived classes:
 * the player's sim plays an animation, then the second class changes the needs, and
 * the third one walks to a cell first. Bounds: hypothesis (from the description of the
 * action to the deleting destructors; `.data` is the name and three vtables, `.bss` the
 * guard, the local description and the local reference). Layouts come from the code;
 * all names are placeholders.
 *
 * Not complete: all at 100 %, but the base D1 is the kept copy 0x02007C84, in a file
 * that is still assembly ("Multiply-defined").
 */
#include "game/unk_sim.h"

/* The player. */
class Unk02009734Player {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 unk4[8];
    void *sim;
    u8 unk10[0x28];
    u8 unk38;
};

/* What is shown of an action. */
struct Unk02009734Desc {
    Unk02009734Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

class Unk02002408 {
public:
    virtual ~Unk02002408();
    void operator delete(void *p);
    virtual bool func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk02009734Desc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk02007c84 : public Unk02002408 {
public:
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02009734Desc *func_20();

    bool playing;
    int key;
    bool loop;
};

class Unk02009764 : public Unk02007c84 {
public:
    virtual int func_18();

    int amounts[6];
};

class Unk02009734 : public Unk02009764 {
public:
    virtual int func_14();
    virtual int func_18();

    Unk020680d4Cell cell;
};

extern "C" {
void func_0200264c(Unk02002408 *a);
int func_02002abc(Unk02002408 *a, Unk020680d4Cell cell, u8 b);
int func_020691c4(void *sim);
void func_020662c8(Unk02009734Player *p, int i, int n);
void func_020667f8(Unk02009734Player *p, int a);
bool func_02066748(Unk02009734Player *p, int key, int a, int b, int c, int d);
void func_0200953c(int *amounts);
extern Unk02009734Player data_020c43a8;
}

static inline bool func_differs(const Unk020680d4Cell &a, Unk020680d4Cell b) {
    return a != b;
}

const Unk02009734Desc *Unk02007c84::func_20() {
    static Unk02009734Desc desc(0, 0, 0xf, "Sim Animation");
    return &desc;
}

bool Unk02007c84::func_08() {
    return true;
}

int Unk02007c84::func_0c() {
    return 0;
}

int Unk02007c84::func_10() {
    if (playing) {
        data_020c43a8.unk38 = 0;
        func_020667f8(&data_020c43a8, 0xa);
    }
    return 1;
}

int Unk02007c84::func_14() {
    func_0200264c(this);
    if (func_02066748(&data_020c43a8, key, 0, loop ? 0xa : 0, 0, 0)) {
        playing = true;
    }
    return 1;
}

int Unk02007c84::func_18() {
    return func_020691c4(data_020c43a8.sim) != 0;
}

void Unk02007c84::func_1c() {
    if (playing) {
        data_020c43a8.unk38 = 0;
        func_020667f8(&data_020c43a8, 0xa);
    }
}

void func_0200953c(int *amounts) {
    for (u32 i = 0; i < 6; i++) {
        func_020662c8(&data_020c43a8, i, amounts[i]);
    }
}

int Unk02009764::func_18() {
    if (Unk02007c84::func_18() != 1) {
        return 0;
    }
    func_0200953c(amounts);
    return 1;
}

int Unk02009734::func_14() {
    static Unk02009734Player &player = data_020c43a8;
    if (func_differs(cell, player.func_14())) {
        return func_02002abc(this, cell, 1);
    }
    if (func_02066748(&player, key, 0, 0xa, 0, 0)) {
        func_0200264c(this);
        playing = true;
    }
    return 1;
}

int Unk02009734::func_18() {
    if (Unk02007c84::func_18() != 1) {
        return 0;
    }
    func_0200953c(amounts);
    return 1;
}
