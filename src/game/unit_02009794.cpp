/*
 * Unit 0x02009794-0x02009848: the action "Simple Slave": it does nothing itself and
 * ends on a flag of the base. Bounds: hypothesis (from the description of the action
 * to its deleting destructor; `.data` is the name and the vtable, `.bss` the guard and
 * the local description). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_script.h"

/* What is shown of an action. */
struct Unk02009818Desc {
    Unk02009818Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02009818Desc *func_20() = 0;

    u32 flags;
};

class Unk02009818 : public Unk02002408 {
public:
    virtual ~Unk02009818();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02009818Desc *func_20();
};

const Unk02009818Desc *Unk02009818::func_20() {
    static Unk02009818Desc desc(4, 0, 2, "Simple Slave");
    return &desc;
}

bool Unk02009818::func_08() {
    return true;
}

int Unk02009818::func_0c() {
    return 0;
}

int Unk02009818::func_10() {
    return 1;
}

int Unk02009818::func_14() {
    return 1;
}

int Unk02009818::func_18() {
    return (flags & 0x20) ? 1 : 0;
}

void Unk02009818::func_1c() {
}

Unk02009818::~Unk02009818() {
}
