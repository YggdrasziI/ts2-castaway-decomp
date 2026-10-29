/*
 * Unit 0x02073878-0x02073ED0: Unk02073878, a game state (base Unk0206fab0,
 * include/game/unk_catalog.h, id 4; func_020738ec also tests id 5) driven by
 * phases (a pointer to member function at 0x0C, set by func_02073c00; the
 * "phase changed" flag at 0x1C is set after the call when the phase moved).
 * func_020738ec opens "ROM_Euro/source/archives/screens.nitro_archive", builds
 * the 0x484-byte screen object (unit_0204A9F8.cpp, two page ranges by id) and the 0xAC-byte
 * guide object (func_0201d70c); the phases step the screen through its opening,
 * wait for its result or a timeout (0x190 frames), play
 * "GROUP_SE_COMMON SE_OPEN_SURVIVAL_GUIDE" and close; func_02073a4c picks the
 * next state (2 or 6) once both objects are done.
 *
 * Bounds: hypothesis. 0x02073878 follows unit_02072D94.cpp; from 0x02073ED0 the
 * code is NitroSDK (interrupt-guarded locks, `bx lr` returns). `.data`: the
 * archive path pointer (0x020BCA90), the pointer to member constants
 * (0x020BCA94-0x020BCAD4), the vtable with its header, this file's copy of the
 * base vtable and the two strings (to 0x020BCB64). Real file name unknown.
 *
 * Every function matches and the `.data` bytes were checked in the object (objdiff
 * does not pair the anonymous constants), but the file cannot link as complete
 * yet: the first copy of the base vtable (0x020BC8FC) is still assembly and
 * clashes with this file's copy (notes/MATCHING.md, unsolved patterns).
 */

#include "game/unk_catalog.h"
#include "game/unk_oam.h"
#include "game/unk_archive.h"

struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

/* The screen object of unit_0204A9F8.cpp. */
class Unk0204a9f8 {
public:
    Unk0204a9f8(Unk02093648 *archive, int first, int last);
    virtual ~Unk0204a9f8();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();

    void func_0204b79c();
    void func_0204b7d0();
    void func_0204b95c();
    void func_0204b970();

    bool func_isOpen() {
        return unk36c == 2 || unk36c == 1;
    }

    bool func_isClosed() {
        return unk36c == 5 || unk36c == 4;
    }

    int unk4;
    int unk8;
    u32 unkc;
    u8 unk10[0x35c];
    int unk36c;
    int unk370;
    int unk374;
    u8 unk378[0x34];
    u16 unk3ac;
    u8 unk3ae[0x82];
    u16 unk430;
    u8 unk432[0x52];
};

/* The guide object, built by func_0201d70c. */
class Unk0201d70c {
public:
    virtual ~Unk0201d70c();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
};

struct Unk020a2994 {
    u8 unk0[0xd0];
    int unkd0;
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
Unk020a2994 *func_020a2994();
void func_020a2ce8(Unk020a2994 *sound, u32 hash, int volume, int unk);
void func_020a35f0(Unk020a2994 *sound, u32 hash, int unk);
void func_020a37e8(Unk020a2994 *sound, int a);
void func_020a3734(Unk020a2994 *sound, int frames);
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
Unk020d6240 *func_020a18e4();
void func_020a0cd8(Unk020d6240 *system);
void func_020a10dc(Unk020d6240 *system, int dt);
void func_020a1138(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a15a8(Unk020d6240 *system, int dt);
bool func_020a1280(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *p, void *object);
Unk0201d70c *func_0201d70c(void *mem);
void func_0206c290(Unk020d6240 *system);
void func_0207c224();
void func_01ffadf8(Unk020916a4 *manager);
}

const char *data_020bca90 = "ROM_Euro/source/archives/screens.nitro_archive";

class Unk02073878 : public Unk0206fab0 {
public:
    typedef void (Unk02073878::*Phase)();

    Unk02073878();
    ~Unk02073878();
    void func_02071e04();
    void func_02071fdc(int dt);
    void func_02072224();
    void func_02073c00(Phase phase);
    void func_02073c54();
    void func_02073d08();
    void func_02073dac();
    void func_02073e34();
    void func_02073e7c();

    Phase phase;
    int unk14;
    int unk18;
    u8 changed;
    Unk02093648 *archive;
    Unk0204a9f8 *screen;
    int step;
    int timer;
    Unk0201d70c *guide;
};

Unk02073878::Unk02073878() : Unk0206fab0(4), phase(0), changed(0), archive(0), screen(0), timer(0x190) {
}

Unk02073878::~Unk02073878() {
}

void Unk02073878::func_02071e04() {
    func_02096dac(0, 0, 1, 4, 0x10, 8);
    func_020a0cd8(&data_020d6240);
    func_020a1138(func_020a18e4(), 2, 1);
    archive = new Unk02093648(data_020bca90);
    archive->func_02094df4();
    func_020a14e0(func_020a18e4(), 1);
    if (id == 4) {
        screen = new Unk0204a9f8(archive, 0, 6);
    } else {
        screen = new Unk0204a9f8(archive, 7, 0xe);
    }
    screen->func_08();
    Unk0201d70c *g = (Unk0201d70c *)operator new(0xac);
    if (g != 0) {
        g = func_0201d70c(g);
    }
    guide = g;
    if (id == 5) {
        guide->func_08();
        func_020a37e8(func_020a2994(), 1);
        func_020a35f0(func_020a2994(), 0x6eede0dd, 0);
    }
    func_02073c00(&Unk02073878::func_02073d08);
}

void Unk02073878::func_02071fdc(int dt) {
    Phase old = phase;
    func_020a10dc(func_020a18e4(), dt);
    (this->*phase)();
    changed = phase != old;
    if (dt == 0) {
        return;
    }
    func_0207c224();
    Unk0208db14::func_0208dbe8()->func_0208e4ec();
    Unk0208db14::func_0208dbf8()->func_0208e4ec();
    func_01ffadf8(Unk020916a4::func_02091820());
    func_01ffadf8(Unk020916a4::func_02091830());
    func_020a15a8(func_020a18e4(), dt);
    if (func_020a0b8c(data_020d6240.unk8, screen) != 0) {
        return;
    }
    if (func_020a0b8c(data_020d6240.unk8, guide) != 0) {
        return;
    }
    if (!func_020a1280(func_020a18e4(), 2, 1)) {
        return;
    }
    next = (screen->unkc & 8) ? 2 : 6;
    if (func_020a2994()->unkd0 == 0) {
        return;
    }
    func_020a3734(func_020a2994(), 0);
}

void Unk02073878::func_02072224() {
    delete guide;
    delete screen;
    delete archive;
    func_0206c290(func_020a18e4());
}

void Unk02073878::func_02073c00(Phase phase) {
    if (this->phase != phase) {
        this->phase = phase;
    }
}

void Unk02073878::func_02073c54() {
    if (changed) {
        step = 0;
    }
    switch (step) {
    case 0:
        screen->func_0204b95c();
        break;
    case 1:
        screen->func_0204b7d0();
        break;
    case 5:
        screen->func_0204b970();
        if (id == 5 && screen->unk370 == screen->unk374) {
            func_02073c00(&Unk02073878::func_02073e7c);
        } else {
            func_02073c00(&Unk02073878::func_02073d08);
        }
        break;
    }
    step++;
}

void Unk02073878::func_02073d08() {
    if (!screen->func_isOpen()) {
        return;
    }
    timer--;
    if (!(screen->unk3ac & 8) && !(screen->unk430 & 8) && timer > 0) {
        return;
    }
    timer = 0x190;
    if (screen->unk370 == screen->unk374) {
        func_02073c00(&Unk02073878::func_02073e34);
    } else {
        func_02073c00(&Unk02073878::func_02073dac);
    }
}

void Unk02073878::func_02073dac() {
    if (changed) {
        Unk020a2994 *sound = func_020a2994();
        func_020a2ce8(sound, func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_OPEN_SURVIVAL_GUIDE", 0, 0), 0x7f, 0);
        screen->unk36c = 3;
    }
    if (screen->func_isClosed()) {
        func_02073c00(&Unk02073878::func_02073c54);
    }
}

void Unk02073878::func_02073e34() {
    if (!changed) {
        return;
    }
    func_020a11f8(func_020a18e4(), 2, 1);
    screen->func_18();
    guide->func_18();
    /* The original keeps a pointer to member constant to func_02073e7c that no
     * code loads (0x020BCAC4), between the ones of func_02073dac and
     * func_02073e7c: a phase change the compiler dropped. Its real form is
     * unknown; this dead branch emits the constant at the same place. */
    if (0) {
        func_02073c00(&Unk02073878::func_02073e7c);
    }
}

void Unk02073878::func_02073e7c() {
    if (screen->func_isOpen()) {
        screen->func_0204b79c();
    }
    if (screen->unkc & 4) {
        func_02073c00(&Unk02073878::func_02073e34);
    }
}
