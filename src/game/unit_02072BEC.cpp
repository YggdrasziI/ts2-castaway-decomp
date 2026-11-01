/*
 * Unit 0x02072BEC-0x02072D94: Unk02072bec, a game state (base Unk0206fab0,
 * include/game/unk_catalog.h, id 1). func_02072c38 sets the screens up and
 * creates its 0x144-byte screen object (unit_020471B0.cpp), func_02072cd8 runs one
 * frame and asks for state 2 when the screen is over, func_02072d60 deletes the
 * screen object.
 *
 * Bounds: hypothesis. 0x02072BEC follows the item catalog; 0x02072D94 is the
 * constructor of the next state. `.data`: the vtable with its header
 * (0x020BC98C) and this file's copy of the base vtable (0x020BC9A8). Real file
 * name unknown.
 *
 * Every function and `.data` match, but the file cannot link as complete yet:
 * the first copy of the base vtable (0x020BC8FC) is still assembly and clashes
 * with this file's copy (notes/MATCHING.md, unsolved patterns). The callee
 * signatures are read from the call sites (func_020a0b8c gets the screen object
 * in r1).
 */

#include "game/unk_catalog.h"
#include "game/unk_oam.h"

struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

/* The screen object of unit_020471B0.cpp. */
class Unk020471b0 {
public:
    Unk020471b0();
    virtual ~Unk020471b0();
    virtual void func_08();

    unsigned char unk4[0x138];
    int unk13c;
    int unk140;
};

class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbe8();
    static Unk0208db14 *func_0208dbf8();
    void func_0208e4ec();
};

extern Unk020d6240 data_020d6240;

void func_02096dac(int a, int b, int c, int d, int e, int f);

extern "C" {
Unk020d6240 *func_020a18e4();
void func_020a0cd8(Unk020d6240 *system);
void func_020a10dc(Unk020d6240 *system, int dt);
void func_020a1138(Unk020d6240 *system, int a, int b);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a15a8(Unk020d6240 *system, int dt);
bool func_020a1280(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *p, Unk020471b0 *screen);
void func_0206c290(Unk020d6240 *system);
void OS_WaitVBlankIntr();
void func_01ffadf8(Unk020916a4 *manager);
}

class Unk02072bec : public Unk0206fab0 {
public:
    Unk02072bec();
    ~Unk02072bec();
    void func_02071e04();
    void func_02072224();
    void func_02071fdc(int dt);

    Unk020471b0 *screen;
    int mode;
};

Unk02072bec::Unk02072bec() : Unk0206fab0(1), screen(0), mode(0) {
}

Unk02072bec::~Unk02072bec() {
}

void Unk02072bec::func_02071e04() {
    func_02096dac(0, 0, 3, 4, 0x70, 8);
    func_020a0cd8(&data_020d6240);
    func_020a1138(func_020a18e4(), 2, 1);
    func_020a14e0(func_020a18e4(), 0);
    screen = new Unk020471b0();
    if (mode == 1) {
        screen->unk13c = 0x1074;
    }
    screen->func_08();
}

void Unk02072bec::func_02071fdc(int dt) {
    if (dt == 0) {
        return;
    }
    OS_WaitVBlankIntr();
    func_020a10dc(func_020a18e4(), dt);
    Unk0208db14::func_0208dbe8()->func_0208e4ec();
    Unk0208db14::func_0208dbf8()->func_0208e4ec();
    func_01ffadf8(Unk020916a4::func_02091820());
    func_01ffadf8(Unk020916a4::func_02091830());
    func_020a15a8(func_020a18e4(), dt);
    if (func_020a0b8c(data_020d6240.unk8, screen) != 0) {
        return;
    }
    if (func_020a1280(func_020a18e4(), 2, 1)) {
        next = 2;
    }
}

void Unk02072bec::func_02072224() {
    delete screen;
    screen = 0;
    func_0206c290(func_020a18e4());
}
