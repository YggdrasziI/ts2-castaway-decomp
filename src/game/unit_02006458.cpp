/*
 * Unit 0x02006458-0x020066B4: the action "Play Instrument": after a delay it starts a
 * microgame through the script interface and waits for its end. Bounds: hypothesis (from
 * the description of the action to its inline destructors; `.data` is the name and the
 * vtable, `.bss` the guard and the local description). Layouts come from the code; all
 * names are placeholders.
 */
#include "game/unk_sim.h"

/* What is shown of an action. */
struct Unk020064a4Desc {
    Unk020064a4Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

class Unk02002408 {
public:
    Unk02002408();
    virtual ~Unk02002408();
    void operator delete(void *p);
    virtual bool func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk020064a4Desc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk020064a4 : public Unk02002408 {
public:
    Unk020064a4();
    virtual ~Unk020064a4() {}
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk020064a4Desc *func_20();

    int unk20;
    int key;
    int param;
    s16 time;
    s16 id;
    u16 flags;
    s16 counter;
    u8 *unk34;
    int unk38;
    int unk3c;
};

struct Unk020064a4Arg {
    u32 key;
    int value;
};

class Unk0206bcf0 {
public:
    void func_0206f560(bool a);
    void func_0206f578(bool a);

    u8 unk0[0x144];
    int unk144;
};

extern "C" {
void func_0200264c(Unk02002408 *a);
void *func_02002438(Unk02002408 *a);
void func_020064e0(Unk020064a4 *o, s16 a, s16 b, int c, int d);
void func_0205e1b8(void *item, void *actor);
Unk0206bcf0 *func_0206bce0();
int func_020a5b58(int key, Unk020064a4Arg *args, int n);
int func_020a5bec();
int func_020a5c38();
}

const Unk020064a4Desc *Unk020064a4::func_20() {
    static Unk020064a4Desc desc(0xa, 0, 0x14, "Play Instrument");
    return &desc;
}

Unk020064a4::Unk020064a4() : unk20(0), flags(0), counter(0), unk34(0), unk38(0), unk3c(0) {}

void func_020064e0(Unk020064a4 *o, s16 a, s16 b, int c, int d) {
    o->id = a;
    o->time = b;
    o->key = c;
    o->param = d;
}

bool Unk020064a4::func_08() {
    return true;
}

int Unk020064a4::func_0c() {
    return 0;
}

int Unk020064a4::func_10() {
    if (flags & 1) {
        func_0205e1b8(func_02002438(this), 0);
    }
    return 1;
}

int Unk020064a4::func_14() {
    flags |= 1;
    func_0200264c(this);
    return 1;
}

int Unk020064a4::func_18() {
    if (func_0206bce0()->unk144 != 0) {
        return 0;
    }
    counter++;
    if (!(flags & 4)) {
        if (counter >= time) {
            Unk020064a4Arg args[4];
            args[0].key = 0xe6884a5d;
            args[0].value = param;
            args[1].key = 0x35c7a149;
            args[1].value = unk34 != 0 ? *(int *)(unk34 + 0x2c) : 0;
            args[2].key = 0xf89be826;
            args[2].value = unk38;
            args[3].key = 0xbf6ec11d;
            args[3].value = unk3c;
            if (func_020a5b58(key, args, 4) == 1) {
                func_0206bce0()->func_0206f560(true);
                func_0206bce0()->func_0206f578(true);
                flags |= 4;
            }
        }
    } else if (func_020a5bec() == 0) {
        flags |= 2;
    }
    if (!(flags & 2)) {
        return 0;
    }
    func_020a5c38();
    func_0206bce0()->func_0206f560(false);
    func_0206bce0()->func_0206f578(false);
    return 1;
}

void Unk020064a4::func_1c() {
}
