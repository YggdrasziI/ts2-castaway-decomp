/*
 * Unit 0x02004938-0x02004FBC: the action "Motive Failure": the player collapses when a
 * motive runs out, the screen fades, time passes and scripts of the scene run. Bounds:
 * hypothesis (from the description of the action, last vtable slot, to the function before
 * the move actions; `.rodata` is the three animation keys, `.data` the name, the table of
 * animations and the vtable, `.bss` the guard and the local description). Layouts come from
 * the code; all names are placeholders.
 */
#include "game/unk_sim.h"

class Unk0205cf00;

class Unk02058788;

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
    s16 height;
};

class Unk02056ed0 {
public:
    u8 unk0[8];
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;
};

class Unk02061d08Item;

class Unk0205f098;

extern "C" {
void func_0205f098(Unk0205f098 *list);
void func_0205f0a8(Unk0205f098 *list);
}

class Unk0205f098 {
public:
    Unk0205f098() {
        func_0205f098(this);
    }
    ~Unk0205f098() {
        func_0205f0a8(this);
    }

    Unk02061d08Item *head;
    int count;
};

/* The player. */
class Unk02004984Player {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 unk4[8];
    void *sim;
    u8 unk10[0x13c];
    bool busy;
};

/* What is shown of an action. */
struct Unk02004984Desc {
    Unk02004984Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

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
    virtual const Unk02004984Desc *func_20() = 0;

    u8 unk4[0x1c];
};

class Unk02004984 : public Unk02002408 {
public:
    Unk02004984();
    virtual ~Unk02004984();
    virtual bool func_08();
    virtual int func_0c();
    virtual int func_10();
    virtual int func_14();
    virtual int func_18();
    virtual void func_1c();
    virtual const Unk02004984Desc *func_20();
    void func_02004e70(int next);
    void func_02004e90(bool a);
    void func_02004f54(u32 key);

    Unk02004984Player *player;
    int kind;
    int motive;
    int state;
    bool skip;
    u32 script;
};

struct Unk02004984Screen {
    u8 unk0[4];
    u32 flags;
};

class Unk0206bcf0 {
public:
    /* An enum keeps the `movne` / `moveq` order of the original. */
    enum Unk0206bcf0Idle { Unk0206bcf0Busy, Unk0206bcf0Free };

    Unk0206bcf0Idle func_idle() {
        return unk144 != 0 ? Unk0206bcf0Busy : Unk0206bcf0Free;
    }

    void func_0206e104(int n);
    void func_0206ea00(int a, int b);
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
    void func_0206f578(bool a);

    u8 unk0[0x11c];
    Unk02004984Screen *screen;
    u8 unk120[0x24];
    int unk144;
    u8 unk148[0xdc];
    int unk224;
    u8 unk228[4];
    u32 unk22c;
};

extern "C" {
void func_0200264c(Unk02002408 *a);
void func_02002670(Unk02002408 *a);
void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
int func_0205465c(void *p, Unk0205cf00 *def, bool a);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);
Unk02058788 *func_02058788(void *world, int map);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
void func_0205e184(Unk02061d08Item *item, u32 key, int a);
Unk0205cf00 *func_0205f6f8(void *db, u32 id);
Unk02061d08Item *func_0205fb4c(void *list, u32 key, Unk0205f098 *out, int a);
void func_02065a60(Unk02004984Player *p, u32 key, int a);
void func_02066374(Unk02004984Player *p, int a);
int func_0206647c(Unk02004984Player *p, int a);
bool func_02066748(Unk02004984Player *p, int key, int a, int b, int c, int d);
void func_020667f8(Unk02004984Player *p, int a);
Unk0206bcf0 *func_0206bce0();
bool func_020691c4(void *sim);
void func_020a11f8(int system, int a, int b);
int func_020a1280(int system, int a, int b);
void func_020a1494(int system, int a, int b);
int func_020a18e4();
u32 func_020a1f84(void *random);
void *func_020a2994();
void func_020a3858(void *audio, u32 key, int a, int b, int c);
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020bfc68[];
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern Unk02004984Player data_020c43a8;
extern u8 data_020d62a4[];
}

const Unk02004984Desc *Unk02004984::func_20() {
    static Unk02004984Desc desc(5, 0, 0x17, "Motive Failure");
    return &desc;
}

static u16 data_020b731c[6][2] = {{0x20, 0x25}, {0x21, 0x26}, {0, 0}, {0x22, 0x27}, {0x23, 0x28}, {0x24, 0x29}};

Unk02004984::Unk02004984() {
    player = &data_020c43a8;
    kind = 0;
    motive = 0;
    state = 0;
    skip = false;
    script = 0;
    func_0200264c(this);
    player->busy = true;
}

Unk02004984::~Unk02004984() {
}

bool Unk02004984::func_08() {
    return true;
}

int Unk02004984::func_0c() {
    return 0;
}

int Unk02004984::func_10() {
    player->busy = false;
    return 1;
}

int Unk02004984::func_14() {
    if (func_0206647c(player, motive) > 0) {
        func_02002670(this);
        return 2;
    }
    func_0206bce0()->func_0206f578(true);
    Unk020680d4Cell cell = player->func_14();
    Unk02056ed0 *layer = func_02056ed0(func_02058788(&data_020c3ba4, data_020c3ba4.map), &cell);
    u32 *tiles = layer->tiles;
    u32 i = (u32)cell.xy.y * layer->info->width + (u32)cell.xy.x;
    skip = (tiles[i] & 0xc000) == 0x8000;
    u32 type = tiles[i] & 0xc000;
    int water = 1;
    if (type != 0x4000 && type != 0xc000) {
        water = 0;
    }
    if (data_020b731c[motive][water] == 0) {
        skip = true;
    }
    if (!skip) {
        func_02066748(player, data_020b731c[motive][water], 0, 0xa, 0, 0x14000);
        if (kind == 2) {
            func_020a3858(func_020a2994(), 0x6278fc62, 0, 0, 0);
            func_0206bce0()->unk22c |= 0x2000;
        }
    }
    state = 1;
    return 1;
}

int Unk02004984::func_18() {
    Unk0206bcf0 *game = func_0206bce0();
    switch (state) {
    case 0:
        return 1;
    case 1:
        if (skip || func_020691c4(player->sim)) {
            switch (kind) {
            case 1:
                func_02004e90(false);
                func_02004e70(6);
                break;
            case 2:
                func_020a1494(func_020a18e4(), 2, 0x10);
                func_020a11f8(func_020a18e4(), 2, 1);
                state = 2;
                break;
            default:
                state = 7;
                break;
            }
        }
        break;
    case 2:
        if (func_020a1280(func_020a18e4(), 2, 1)) {
            func_0206bce0()->screen->flags |= 8;
            state = 3;
        }
        break;
    case 3:
        game->func_0206e104(0x1e0);
        if (data_020c3ba4.map != 2) {
            game->func_0206ea00(2, 0);
        }
        func_02065a60(player, 0x1adc021f, 1);
        func_02004e90(true);
        state = 4;
        break;
    case 4:
        if (game->unk224 <= 0 && (func_0206bce0()->screen->flags & 0x80)) {
            func_02004e70(5);
        }
        break;
    case 5:
        state = 6;
        func_0206bce0()->screen->flags &= ~8;
        func_020a1494(func_020a18e4(), 2, 0x20);
        func_020a11f8(func_020a18e4(), 2, 0);
        break;
    case 6:
        if (func_020691c4(player->sim)) {
            state = 7;
        }
        break;
    case 7:
        if (script != 0) {
            Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, script);
            int key = func_0205d1b4(def, 0x798b86ac);
            Unk0205cf00 *d = func_0205f6f8(data_020c3fc4, key);
            if (func_02054dc4(data_020bfc9c, d, 0) == 0) {
                if (func_0205465c(data_020bfc68, def, true)) {
                    func_0206bce0()->func_0206f3e8(d, 0, 1, 1);
                    state = 8;
                }
                break;
            }
            return 1;
        }
        return 1;
    case 8:
        return func_0206bce0()->func_idle();
    }
    return 0;
}

void Unk02004984::func_02004e70(int next) {
    func_02066374(player, motive);
    state = next;
}

void Unk02004984::func_02004e90(bool a) {
    if (a) {
        u32 keys[3] = {0x6c4f1d75, 0x6c4f1d76, 0x6c4f1d77};
        func_02004f54(keys[func_020a1f84(data_020d62a4) % 3]);
    } else {
        func_020667f8(player, 0xa);
    }
}

void Unk02004984::func_1c() {
    player->busy = false;
    func_0206bce0()->func_0206f578(false);
    func_0206bce0()->unk22c &= ~0x2000;
    func_02004f54(0x7a90e673);
}

void Unk02004984::func_02004f54(u32 key) {
    int map = data_020c3ba4.map;
    Unk0205f098 list;
    func_0205fb4c(data_020c3fd4, 0x17a64cc0, &list, map);
    if (list.count > 0) {
        func_0205e184(list.head, key, 0);
    }
}
