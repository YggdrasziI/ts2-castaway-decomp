/*
 * Unit 0x02004250-0x0200434C: the action "Display Task Reminder": the player stops and the
 * game state shows a reminder until it is idle again. Bounds: hypothesis (from the
 * description of the action, to the description of "Give Gift"; `.data` is the name and the
 * vtable, `.bss` the guard and the local description). Layouts come from the code; all
 * names are placeholders.
 */
typedef unsigned char u8;
typedef unsigned long u32;

/* What is shown of an action. */
struct Unk0200429cDesc {
    Unk0200429cDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk0200429cDesc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk0200429c : public Unk02002408 {
public:
    Unk0200429c();
    virtual ~Unk0200429c();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk0200429cDesc *func_20();

    u32 key;
};

class Unk0206bcf0 {
public:
    /* An enum keeps the `movne` / `moveq` order of the original. */
    enum Unk0206bcf0Idle { Unk0206bcf0Busy, Unk0206bcf0Free };

    Unk0206bcf0Idle func_idle() {
        return unk144 != 0 ? Unk0206bcf0Busy : Unk0206bcf0Free;
    }

    bool func_0206f4e4(u32 key);

    u8 unk0[0x144];
    int unk144;
};

extern "C" {
void *func_02002414(Unk02002408 *a);
void func_020667f8(void *actor, int a);
Unk0206bcf0 *func_0206bce0();
}

const Unk0200429cDesc *Unk0200429c::func_20() {
    static Unk0200429cDesc desc(5, 0, 0x1f, "Display Task Reminder");
    return &desc;
}

Unk0200429c::Unk0200429c() {
}

Unk0200429c::~Unk0200429c() {
}

bool Unk0200429c::func_08() {
    return true;
}

int Unk0200429c::func_0c() {
    return 0;
}

int Unk0200429c::func_10() {
    return 1;
}

int Unk0200429c::func_14() {
    func_020667f8(func_02002414(this), 0xa);
    func_0206bce0()->func_0206f4e4(key);
    return 1;
}

int Unk0200429c::func_18() {
    return func_0206bce0()->func_idle();
}

void Unk0200429c::func_1c() {
}
