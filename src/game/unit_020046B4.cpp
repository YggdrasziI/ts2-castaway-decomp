/*
 * Unit 0x020046B4-0x020047FC: the action "Immediate": it runs a block of the object script
 * at once, without walking to the object. Bounds: hypothesis (from the description of the
 * action, to the description of "Action Interact"; `.data` is the name and the vtable,
 * `.bss` the guard and the local description). Layouts come from the code; all names are
 * placeholders.
 */
typedef unsigned char u8;

class Unk0205cf00;

class Unk02060d78;

struct Unk02099c78Block;

class Unk02061d08Item {
public:
    u8 unk0[0x28];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *visible;
};

/* What is shown of an action. */
struct Unk020047ccDesc {
    Unk020047ccDesc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk020047ccDesc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk020047cc : public Unk02002408 {
public:
    virtual ~Unk020047cc();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk020047ccDesc *func_20();

    int block;
    bool started;
    bool stop;
};

extern "C" {
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, void *actor);
void func_0205e1b8(Unk02061d08Item *item, void *actor);
bool func_0206135c(Unk02060d78 *e);
}

const Unk020047ccDesc *Unk020047cc::func_20() {
    static Unk020047ccDesc desc(4, 0, 4, "Immediate");
    return &desc;
}

bool Unk020047cc::func_08() {
    return true;
}

int Unk020047cc::func_0c() {
    return 0;
}

int Unk020047cc::func_10() {
    if (started) {
        func_0205e1b8(func_02002438(this), 0);
    }
    return 1;
}

int Unk020047cc::func_14() {
    Unk02061d08Item *a = func_02002438(this);
    Unk02061d08Item *o = func_02002438(this);
    func_0205e038(o, func_0205cea4(a->def, block), 0);
    started = true;
    func_0200264c(this);
    return 1;
}

int Unk020047cc::func_18() {
    if (!func_0206135c(func_02002438(this)->visible)) {
        return 0;
    }
    if (stop) {
        func_0205e1b8(func_02002438(this), 0);
    }
    return 1;
}

void Unk020047cc::func_1c() {
}

Unk020047cc::~Unk020047cc() {
}
