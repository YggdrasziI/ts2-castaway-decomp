/*
 * Unit 0x02071D94-0x020724CC: Unk02071d94, a game state (base Unk0206fab0,
 * include/game/unk_catalog.h, id 3). func_02071e04 sets the screens up, builds
 * the item catalog (Unk020724cc) and the 0x35B4-byte scene object, starts the
 * music and the scene; func_02071fdc runs one frame (three sounds at frames 0x6D,
 * 0x7F and 0xB9 of the main animation while the scene's flag 0x100 is set, random
 * idle actions otherwise, then the pool drawing of the ITCM, the buffer swap and
 * the object managers) and asks for state 4 when the scene is over;
 * func_02072224 releases everything.
 *
 * Bounds: hypothesis. 0x02071D94 follows unit_020717B8.cpp; 0x020724CC is the
 * constructor of the catalog, which uses no state. `.data`: the vtable with its
 * header (0x020BC954) and this file's copy of the base vtable (0x020BC970); the
 * class at 0x02072BEC emits the next one. Real file name unknown.
 */

#include "game/unk_catalog.h"
#include "game/unk_pool.h"
#include "game/unk_texture.h"
#include "game/unk_anim.h"
#include "game/unk_oam.h"

class Unk02093648;

struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The outfit screen of unit_02041B10.cpp: only what is used here. */
class Unk02041b10 {
public:
    Unk02041b10(Unk02093648 *archive, Unk020c43a8 *player, Unk020724cc *catalog);
    virtual ~Unk02041b10();
    virtual void func_08();

    int unk4;
    int unk8;
    u32 flags;
    u8 unk10[0x35a4];
};

struct Unk020c43a8Data {
    u8 unk0[0x160];
    void *unk160;
};

/* The argument of Unk020c43a8::func_18: a one-word value built on the stack. */
struct Unk020c43a8Mode {
    Unk020c43a8Mode(int v) {
        value = v;
    }

    int value;
};

class Unk020c43a8 {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18(Unk020c43a8Mode mode);

    int unk4;
    int unk8;
    Unk020c43a8Data *unkc;
    u8 unk10[0x28];
    u8 unk38;
};

/* A scene object, from the lists of func_0205fd7c. */
class Unk02061d08Item {
public:
    static void operator delete(void *p);
    ~Unk02061d08Item();

    u8 unk0[0x40];
    Unk02061d08Item *next;
    int unk44;
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
extern Unk020c43a8 data_020c43a8;
extern u8 data_020c4390[];
extern u8 data_020c40cc[];
extern u8 data_020c409c[];
extern u8 data_020c3ba4[];
extern u8 data_020c3fd4[];
extern u8 data_020c3fc4[];
extern u8 data_020d62a4[];
extern Unk0208a0a8 *data_020c7d24;

void func_02096dac(int a, int b, int c, int d, int e, int f);

extern "C" {
void *func_020a2994();
void func_020a28ac(void *sound);
void func_020a28d8(void *sound);
void func_020a35f0(void *sound, u32 hash, int unk);
int func_020a2ce8(void *sound, u32 hash, int volume, int unk);
void func_020a3734(void *sound, int frames);
void func_020a34e4(void *sound, int handle);
Unk020d6240 *func_020a18e4();
void func_020a0cd8(Unk020d6240 *system);
void func_020a1070();
void func_020a10a8();
void func_020a10dc(Unk020d6240 *system, int dt);
void func_020a1138(Unk020d6240 *system, int a, int b);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a15a8(Unk020d6240 *system, int dt);
int func_020a0b8c(void *p);
u32 func_020a1f84(void *random);
void func_02064270(void *p);
void func_020642cc(void *p);
void func_02060b24(void *p);
void func_02060b98(void *p);
void func_02060cdc(void *p);
void func_0206061c(void *p);
void func_02058380(void *p);
void *func_02058518(void *p, int a, int b);
void func_02058688(void *p);
void func_0205899c(void *p);
void func_02056b80(void *p);
void func_02056c7c(void *p);
Unk02061d08Item *func_0205fd7c(void *list, int type);
void func_0205fde4(void *list);
void func_0205f7f8(void *p);
void func_0205e3f0(Unk02061d08Item *node);
void func_0205e4d0(Unk02061d08Item *node);
void func_0206a120(void *p);
void func_0206af98(void *p, int mode);
void func_0206c290(Unk020d6240 *system);
void func_02064cfc(Unk020c43a8 *owner, int a, Unk020724cc *catalog);
void func_02064ca0(Unk020c43a8 *owner);
void func_02065db8(Unk020c43a8 *owner);
void func_02065e80(Unk020c43a8 *owner);
void func_02065b80(Unk020c43a8 *owner, int dt);
void func_020667f8(Unk020c43a8 *owner, int a);
void func_02066748(Unk020c43a8 *owner, int action, int a, int b, int c, int d);
Unk020081dc func_020081dc(Unk020c43a8 *owner);
int func_020691c4();
Unk020897c0 *func_02063d84(void *p);
void func_0207a748();
void OS_WaitVBlankIntr();
void func_01ff9924(Unk020c7d38 *pool);
void func_01ff9dbc(Unk020c7d38 *pool);
bool func_01ff9ee8(Unk020c7d38 *pool);
void func_01ffaac4(Unk020c7f48 *m);
void func_01ffadf8(Unk020916a4 *manager);
}

class Unk02071d94 : public Unk0206fab0 {
public:
    Unk02071d94();
    ~Unk02071d94();
    void func_02071e04();
    void func_02072224();
    void func_02071fdc(int dt);
    void func_02072398();

    Unk020724cc *catalog;
    Unk02041b10 *scene;
    int idle;
    int step;
    int music;
    Unk02069fec unk20;
};

Unk02071d94::Unk02071d94() : Unk0206fab0(3), catalog(0), scene(0), idle(3), step(0), music(-1) {
}

Unk02071d94::~Unk02071d94() {
}

void Unk02071d94::func_02071e04() {
    func_020a28ac(func_020a2994());
    func_02096dac(7, 0x20, 0x10, 0x180, 0x40, 8);
    func_020a0cd8(&data_020d6240);
    func_020a1070();
    func_020a1138(func_020a18e4(), 2, 1);
    func_020a14e0(func_020a18e4(), 0);
    catalog = new Unk020724cc(&data_020c43a8);
    func_02064270(data_020c4390);
    func_02060b24(data_020c40cc);
    func_0206061c(data_020c409c);
    func_02058380(data_020c3ba4);
    void *p = func_02058518(data_020c3ba4, 0x28, 1);
    func_02056b80(p);
    func_02056c7c(p);
    for (Unk02061d08Item *n = func_0205fd7c(data_020c3fd4, 0x28); n != 0; n = n->next) {
        if (n->unk44 == 0) {
            func_0205e3f0(n);
        }
    }
    func_0206a120(&unk20);
    func_02064cfc(&data_020c43a8, -1, catalog);
    func_02065db8(&data_020c43a8);
    scene = new Unk02041b10(func_020a18e4()->archive, &data_020c43a8, catalog);
    scene->func_08();
    void *sound = func_020a2994();
    func_020a28d8(sound);
    func_020a35f0(sound, 0xfff1d650, 0);
    music = func_020a2ce8(sound, 0x47df0cdd, 0x7f, 0);
    Unk020c43a8 *owner = &data_020c43a8;
    owner->unk38 = 1;
    owner->func_18(Unk020c43a8Mode(2));
}

/* 99.93 %: the last test of the scene flags loads the scene into r1, here r0. */
void Unk02071d94::func_02071fdc(int dt) {
    if (dt == 0) {
        return;
    }
    Unk020c7d38 *pool = &data_020c7d38;
    func_020a10dc(func_020a18e4(), dt);
    if (!(scene->flags & 0x100)) {
        func_02072398();
    } else {
        int frame = func_02063d84(data_020c43a8.unkc->unk160)->func_02089998() >> 12;
        if (frame == 0x6d && step == 0) {
            func_020a2ce8(func_020a2994(), 0x7b029bd3, 0x7f, 0);
            step++;
        }
        if (frame == 0x7f && step == 1) {
            if (func_020081dc(&data_020c43a8).unk28 == 1) {
                func_020a2ce8(func_020a2994(), 0xa97ee4ee, 0x7f, 0);
            } else {
                func_020a2ce8(func_020a2994(), 0x4b4d78fe, 0x7f, 0);
            }
            step++;
        }
        if (frame == 0xb9 && step == 2) {
            func_020a2ce8(func_020a2994(), 0x7d29bb8b, 0x7f, 0);
            step++;
        }
    }
    func_02060cdc(data_020c40cc);
    func_02065b80(&data_020c43a8, dt);
    func_0205899c(data_020c3ba4);
    func_0206af98(&unk20, (scene->flags & 0x100) ? 7 : 6);
    func_01ff9924(pool);
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    *(volatile u32 *)0x4000540 = 3;
    OS_WaitVBlankIntr();
    func_01ffaac4(func_0208c578());
    func_01ff9dbc(pool);
    Unk0208db14::func_0208dbe8()->func_0208e4ec();
    Unk0208db14::func_0208dbf8()->func_0208e4ec();
    func_01ffadf8(Unk020916a4::func_02091820());
    func_01ffadf8(Unk020916a4::func_02091830());
    func_020a15a8(func_020a18e4(), dt);
    func_0205f7f8(data_020c3fc4);
    if (!(scene->flags & 4)) {
        return;
    }
    if (func_020a0b8c(data_020d6240.unk8) == 0) {
        next = 4;
    }
}

void Unk02071d94::func_02072224() {
    Unk020c7d38 *pool = &data_020c7d38;
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    data_020c43a8.unk38 = 0;
    func_020667f8(&data_020c43a8, 10);
    func_02065e80(&data_020c43a8);
    func_02064ca0(&data_020c43a8);
    for (Unk02061d08Item *n = func_0205fd7c(data_020c3fd4, 0x28); n != 0;) {
        Unk02061d08Item *cur = n;
        n = n->next;
        func_0205e4d0(cur);
        delete cur;
    }
    func_0205fde4(data_020c3fd4);
    func_0205f7f8(data_020c3fc4);
    func_02060b98(data_020c40cc);
    func_02058688(data_020c3ba4);
    func_020642cc(data_020c4390);
    func_020a3734(func_020a2994(), 0x3c);
    int h = music;
    if (h != -1) {
        func_020a34e4(func_020a2994(), h);
        music = -1;
    }
    func_020a10a8();
    data_020c7d38.func_0208b9dc();
    data_020c7d24->func_0208aae0();
    func_0208c578()->func_0208ca24();
    delete scene;
    delete catalog;
    func_0206c290(func_020a18e4());
}

void Unk02071d94::func_02072398() {
    u8 *random = data_020d62a4;
    Unk020c43a8 *owner = &data_020c43a8;
    if (owner->unkc == 0) {
        return;
    }
    if (!func_020691c4()) {
        return;
    }
    if (--idle > 0) {
        owner->unk38 = 0;
        func_020667f8(owner, 10);
        func_020667f8(owner, 10);
        owner->unk38 = 1;
        return;
    }
    idle = func_020a1f84(random) % 3 + 2;
    int action;
    if (func_020081dc(owner).unk28 == 1) {
        action = func_020a1f84(random) % 3 + 0x3f;
    } else {
        action = (func_020a1f84(random) & 3) + 0x3b;
    }
    func_02066748(owner, action, 0, 10, 0, 0);
}
