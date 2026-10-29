/*
 * Unit 0x02072D94-0x02073878: Unk02072d94, a game state (base Unk0206fab0,
 * include/game/unk_catalog.h, id 2) driven by phases: a pointer to member
 * function (0x0C) that func_02073000 calls every frame, set by func_020734a8,
 * which also raises the "phase changed" flag (0x14) for the first frame of the
 * new phase. func_02072e40 opens "ROM_Euro/source/archives/screens.nitro_archive",
 * builds the 0x8DC-byte screen object (unit_02047A8C.cpp) and places three pairs of
 * scene objects (keys data_020af1ac, height from the game settings); the phases
 * read the screen's result (its func_0204a880) and pick the next state
 * (nextId, 0x15C) or the next phase; func_0207319c releases everything.
 *
 * Bounds: hypothesis. 0x02072D94 follows unit_02072BEC.cpp; 0x02073878 is the
 * constructor of the next state. `.rodata`: the key pairs 0x020AF1AC-0x020AF1C4,
 * only used here. `.data`: the archive path pointer (0x020BC9C4), the pointer to
 * member constants of the phase changes (0x020BC9C8-0x020BCA28), the vtable with
 * its header, this file's copy of the base vtable and the path string (to
 * 0x020BCA90). Real file name unknown.
 *
 * Every function matches and the `.data` bytes were checked in the object (objdiff
 * does not pair the anonymous constants), but the file cannot link as complete
 * yet: the first copy of the base vtable (0x020BC8FC) is still assembly and
 * clashes with this file's copy (notes/MATCHING.md, unsolved patterns).
 */

#include "game/unk_catalog.h"
#include "game/unk_pool.h"
#include "game/unk_texture.h"
#include "game/unk_oam.h"
#include "game/unk_archive.h"
#include "game/unk_vector.h"

typedef signed char s8;

struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
};

struct Unk020d60c8Unk0 {
    int unk0;
    int unk4;
    int unk8;
};

struct Unk020a5538 {
    u8 unk0[0x60];
    int unk60;
};

/* The game settings (data_020d60c8): fields used here. */
struct Unk020d60c8 {
    Unk020d60c8Unk0 *unk0;
    int unk4;
    u32 unk8;
    u8 unkc[0x104];
    s8 unk110[3];
    u8 unk113[0x21];
    int unk134;
    u8 unk138[0x1c];
    Unk020a5538 *unk154;
    void *texts;
    u8 unk15c;
};

/* A record returned by func_0209f8d0. */
struct Unk0209f8d0 {
    u8 unk0[0x48];
    u8 unk48;
    int unk4c;
    int unk50;
};

/* The screen object of unit_02047A8C.cpp. */
class Unk02047a8c {
public:
    Unk02047a8c(Unk02093648 *archive);
    virtual ~Unk02047a8c();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();

    int func_0204a670();
    int func_0204a880();
    void func_0204a888(int mode);

    u8 unk4[0x168];
    int unk16c;
    u8 unk170[0x76c];
};

/* A position wrapped in a struct: assigned with a block copy. */
struct Unk0205fae8Pos {
    Unk02098ff0 v;
};

/* A scene object found by func_0205fae8. */
class Unk0205fae8 {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk0205fae8Pos func_04();
};

struct Unk0205f098 {
    int unk0;
    int unk4;
};

/* A pair of object keys. */
struct Unk020af1ac {
    u32 a;
    u32 b;
};

/* A scene object, from the lists of func_0205fd7c. */
class Unk02061d08Item {
public:
    static void operator delete(void *p);
    ~Unk02061d08Item();

    u8 unk0[0x40];
    Unk02061d08Item *next;
};

class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbe8();
    static Unk0208db14 *func_0208dbf8();
    void func_0208e4ec();
};

class Unk0208a0a8 {
public:
    void func_0208aae0();
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern u8 data_020c4390[];
extern u8 data_020c40cc[];
extern u8 data_020c409c[];
extern u8 data_020c3ba4[];
extern u8 data_020c3fd4[];
extern u8 data_020c3fc4[];
extern Unk0208a0a8 *data_020c7d24;

void func_02096dac(int a, int b, int c, int d, int e, int f);

extern "C" {
void *func_020a2994();
void func_020a27f4(void *sound);
void func_020a35f0(void *sound, u32 hash, int unk);
void func_020a37e8(void *sound, int a);
void func_020a3734(void *sound, int frames);
Unk020d6240 *func_020a18e4();
void func_020a0cd8(Unk020d6240 *system);
void func_020a1070();
void func_020a10a8();
void func_020a10dc(Unk020d6240 *system, int dt);
void func_020a1138(Unk020d6240 *system, int a, int b);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a15a8(Unk020d6240 *system, int dt);
bool func_020a1280(Unk020d6240 *system, int a, int b);
int func_020a0b8c(void *p, Unk02047a8c *screen);
int func_0209f0a4(Unk020d60c8 *settings);
void func_0209f05c(Unk020d60c8 *settings, int a, int b);
Unk0209f8d0 *func_0209f8d0(Unk020d60c8 *settings, int a);
void func_0209f850(Unk020d60c8 *settings, int a);
void func_0209f880(Unk020d60c8 *settings, int a);
bool func_0209feb0(Unk020d60c8 *settings, int a);
void func_020a52ac(Unk020a5538 *p, int a, int b);
bool func_020a5538(Unk020a5538 *p);
int func_020a5248(Unk020a5538 *p, int a);
void func_02064270(void *p);
void func_020642cc(void *p);
void func_02060b24(void *p);
void func_02060b98(void *p);
void func_02060cdc(void *p);
void func_0206061c(void *p);
void func_02058380(void *p);
void *func_02058518(void *p, int a, int b);
void func_020585e0(void *p, int a);
void func_02058688(void *p);
void func_0205899c(void *p);
void func_02056b80(void *p);
void func_02056c7c(void *p);
Unk02061d08Item *func_0205fd7c(void *list, int type);
void func_0205fde4(void *list);
void func_0205f998(void *list);
void func_0205f9e4(void *list);
void func_0205f7f8(void *p);
void *func_0205f6f8(void *db, u32 key);
Unk0205fae8 *func_0205fae8(void *list, void *item, Unk0205f098 *ctx);
void func_0205f098(Unk0205f098 *ctx);
void func_0205f0a8(Unk0205f098 *ctx);
void func_0205e3f0(Unk02061d08Item *node);
void func_0205e4d0(Unk02061d08Item *node);
void func_0206a120(void *p);
void func_0206af98(void *p, int mode);
void func_0206c290(Unk020d6240 *system);
void func_0207a748();
void func_0207c224();
void func_01ff9924(Unk020c7d38 *pool);
void func_01ff9dbc(Unk020c7d38 *pool);
bool func_01ff9ee8(Unk020c7d38 *pool);
void func_01ffaac4(Unk020c7f48 *m);
void func_01ffadf8(Unk020916a4 *manager);
}

static const Unk020af1ac data_020af1ac[3] = {
    {0xbe895c5d, 0x4ab3f8e5},
    {0xbe895c5e, 0x4ab3f8e6},
    {0xbe895c5f, 0x4ab3f8e7},
};

const char *data_020bc9c4 = "ROM_Euro/source/archives/screens.nitro_archive";

class Unk02072d94 : public Unk0206fab0 {
public:
    typedef void (Unk02072d94::*Phase)();

    Unk02072d94();
    ~Unk02072d94();
    void func_02071e04();
    void func_02071fdc(int dt);
    void func_02072224();
    void func_020732c4(bool reset);
    void func_020734a8(Phase phase);
    void func_02073508();
    void func_02073590();
    void func_02073630();
    void func_020736bc();
    void func_020737b4();
    void func_02073844();

    Phase phase;
    u8 changed;
    Unk02093648 *archive;
    Unk02047a8c *screen;
    Unk02069fec unk20;
    s8 unk12c;
    u8 unk12d[0x2f];
    int nextId;
    u8 unk160;
    u8 unk161;
    Unk0205fae8Pos pos[3];
};

Unk02072d94::Unk02072d94() : Unk0206fab0(2), phase(0), changed(0), archive(0), screen(0) {
    unk12c = -1;
    nextId = 2;
    unk160 = 0;
    unk161 = 0;
}

Unk02072d94::~Unk02072d94() {
}

void Unk02072d94::func_02071e04() {
    func_02096dac(7, 0x20, 0x40, 0x180, 0x10, 8);
    func_020a0cd8(&data_020d6240);
    func_020a1070();
    func_020a1138(func_020a18e4(), 2, 1);
    archive = new Unk02093648(data_020bc9c4);
    archive->func_02094df4();
    func_020a14e0(func_020a18e4(), 1);
    screen = new Unk02047a8c(archive);
    unk161 = 1;
    func_02064270(data_020c4390);
    func_0206061c(data_020c409c);
    func_02060b24(data_020c40cc);
    func_02058380(data_020c3ba4);
    void *p = func_02058518(data_020c3ba4, 0x27, 1);
    func_02056b80(p);
    func_02056c7c(p);
    for (Unk02061d08Item *n = func_0205fd7c(data_020c3fd4, 0x27); n != 0; n = n->next) {
        func_0205e3f0(n);
    }
    func_020732c4(true);
    func_0206a120(&unk20);
    func_020a37e8(func_020a2994(), 1);
    func_020a35f0(func_020a2994(), 0x6eede0dd, 0);
    func_020a27f4(func_020a2994());
    if (data_020d60c8.unk8 & 2) {
        func_020734a8(&Unk02072d94::func_02073508);
    } else {
        func_020734a8(&Unk02072d94::func_02073590);
    }
}

void Unk02072d94::func_02071fdc(int dt) {
    if (dt == 0) {
        return;
    }
    u8 first = changed;
    Unk020c7d38 *pool = &data_020c7d38;
    func_020a10dc(func_020a18e4(), dt);
    (this->*phase)();
    if (first) {
        changed = 0;
    }
    func_0205f998(data_020c3fd4);
    func_02060cdc(data_020c40cc);
    func_0205899c(data_020c3ba4);
    func_0205fde4(data_020c3fd4);
    func_0206af98(&unk20, unk160 ? 6 : 7);
    func_01ff9924(pool);
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    *(volatile u32 *)0x4000540 = 3;
    func_0207c224();
    func_01ffaac4(func_0208c578());
    func_01ff9dbc(pool);
    Unk0208db14::func_0208dbe8()->func_0208e4ec();
    Unk0208db14::func_0208dbf8()->func_0208e4ec();
    func_01ffadf8(Unk020916a4::func_02091820());
    func_01ffadf8(Unk020916a4::func_02091830());
    func_020a15a8(func_020a18e4(), dt);
    func_0205f7f8(data_020c3fc4);
    if (func_020a0b8c(data_020d6240.unk8, screen) == 0 && func_020a1280(func_020a18e4(), 2, 1)) {
        if (!unk161) {
            next = nextId;
        }
    }
    if (!unk161) {
        return;
    }
    screen->func_08();
    unk161 = 0;
}

void Unk02072d94::func_02072224() {
    Unk020c7d38 *pool = &data_020c7d38;
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    func_0205f9e4(data_020c3fd4);
    for (Unk02061d08Item *n = func_0205fd7c(data_020c3fd4, 0x27); n != 0;) {
        Unk02061d08Item *cur = n;
        n = n->next;
        func_0205e4d0(cur);
        delete cur;
    }
    func_020585e0(data_020c3ba4, 0x27);
    func_0205fde4(data_020c3fd4);
    func_0205f7f8(data_020c3fc4);
    func_020642cc(data_020c4390);
    func_02058688(data_020c3ba4);
    func_02060b98(data_020c40cc);
    data_020c7d38.func_0208b9dc();
    func_020a10a8();
    data_020c7d24->func_0208aae0();
    func_0208c578()->func_0208ca24();
    delete screen;
    delete archive;
    func_0206c290(func_020a18e4());
}

void Unk02072d94::func_020732c4(bool reset) {
    Unk0205f098 ctx;
    func_0205f098(&ctx);
    Unk0205fae8 *a;
    Unk0205fae8 *b;
    for (u32 i = 0; i < 3; i++) {
        a = func_0205fae8(data_020c3fd4, func_0205f6f8(data_020c3fc4, data_020af1ac[i].a), &ctx);
        b = func_0205fae8(data_020c3fd4, func_0205f6f8(data_020c3fc4, data_020af1ac[i].b), &ctx);
        if (a == 0 || b == 0) {
            continue;
        }
        if (reset) {
            pos[i] = a->func_04();
        }
        int h = data_020d60c8.unk110[(int)i];
        if (h == -1) {
            a->func_00(pos[i].v.func_0209911c(Unk02098ff0(0, 0, 0x2000)));
            b->func_00(pos[i].v.func_0209911c(Unk02098ff0(0, 0, 0x2000)));
        } else {
            a->func_00(pos[i].v.func_0209911c(Unk02098ff0(0, 0, h << 11)));
            b->func_00(pos[i].v.func_0209911c(Unk02098ff0(0, 0, h << 11)));
        }
    }
    func_0205f0a8(&ctx);
}

void Unk02072d94::func_020734a8(Phase phase) {
    if (this->phase != phase) {
        this->phase = phase;
        changed = 1;
    }
}

void Unk02072d94::func_02073508() {
    if (changed) {
        unk160 = 0;
    }
    switch (screen->func_0204a880()) {
    case 0:
        func_020a3734(func_020a2994(), 0xf);
        nextId = 3;
        break;
    case 1:
        func_020734a8(&Unk02072d94::func_02073630);
        break;
    case 2:
        func_020734a8(&Unk02072d94::func_02073590);
        break;
    }
}

void Unk02072d94::func_02073590() {
    int r = screen->func_0204a670();
    if (r == -1) {
        return;
    }
    if (r == func_0209f0a4(&data_020d60c8)) {
        func_020734a8(&Unk02072d94::func_02073508);
        if (!(data_020d60c8.unk8 & 2)) {
            func_0209f05c(&data_020d60c8, r, 1);
        }
    } else {
        func_0209f05c(&data_020d60c8, r, 1);
        nextId = 2;
        screen->func_18();
        func_020a3734(func_020a2994(), 0xf);
    }
}

void Unk02072d94::func_02073630() {
    if (changed) {
        unk160 = 1;
    }
    switch (screen->func_0204a880()) {
    case -1:
        func_020734a8(&Unk02072d94::func_02073508);
        break;
    case 3:
        func_020734a8(&Unk02072d94::func_020737b4);
        break;
    case 4:
        func_020734a8(&Unk02072d94::func_020736bc);
        break;
    }
}

void Unk02072d94::func_020736bc() {
    Unk020a5538 *a = data_020d60c8.unk154;
    Unk020d60c8Unk0 *b = data_020d60c8.unk0;
    if (changed) {
        b->unk8 = 0;
        func_020a52ac(a, screen->unk16c, b->unk0);
    }
    if (func_020a5538(a)) {
        return;
    }
    if (a->unk60 == 2) {
        nextId = 6;
        func_020734a8(&Unk02072d94::func_02073844);
        b->unk8 = func_020a5248(a, screen->unk16c);
        data_020d60c8.unk134 = screen->unk16c;
        Unk0209f8d0 *r = func_0209f8d0(&data_020d60c8, screen->unk16c);
        data_020d60c8.unk15c = r->unk48;
        func_0209f850(&data_020d60c8, r->unk4c);
        func_0209f880(&data_020d60c8, r->unk50);
    } else {
        screen->func_0204a888(0xb);
        func_020734a8(&Unk02072d94::func_02073630);
    }
}

void Unk02072d94::func_020737b4() {
    switch (screen->func_0204a880()) {
    case 3:
        if (func_0209feb0(&data_020d60c8, screen->unk16c)) {
            screen->func_0204a888(9);
            func_020732c4(false);
            func_020734a8(&Unk02072d94::func_02073630);
        } else {
            screen->func_0204a888(0xa);
        }
        break;
    case 1:
        func_020734a8(&Unk02072d94::func_02073630);
        break;
    }
}

void Unk02072d94::func_02073844() {
    if (!changed) {
        return;
    }
    func_020a3734(func_020a2994(), 0xf);
    screen->func_18();
}
