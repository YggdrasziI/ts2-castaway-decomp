/*
 * Unit 0x02013258-0x02013F8C: the instrument microgame `Unk02013258` (its strings
 * name the ocarina and conch animations and sounds).
 *
 * Bounds: hypothesis. The start follows the deleting destructor of the previous
 * class, the end is the microgame base unit. Its `.data` starts after the last
 * string of the previous unit and ends with its two sound names. Real file name
 * unknown.
 */

#include "game/unk_microgame.h"

class Unk02013258 : public Unk020a5ccc {
public:
    typedef void (Unk02013258::*State)();

    Unk02013258(Unk02093648 *file, int a, int b);
    virtual ~Unk02013258();
    virtual void func_10(bool a);
    virtual void func_14();
    virtual bool func_18();
    virtual void func_1c();

    void func_0201351c(int anim, int a, int force, int b);
    void func_020139f4();
    void func_02013b04();
    void func_02013f04();
    void func_02013f3c(State s);

    Unk020a9d58 layout;
    u8 shown;
    Unk020a7c90 *sprites[8];
    Unk020a7c90 *bars[11];
    Unk02050640 button;
    State state;
    int handle;
    int volume;
    u8 unk198[0x20];
    u32 kind;
    int pitch;
    int target;
    int index;
    u32 hash;
    u32 hash2;
    u32 hash3;
    int anim;
    int saved;
};

struct Unk02013258Arg {
    u32 key;
    int value;
};

struct Unk02013258Note {
    int speed;
    int mask;
    u32 keys;
};

struct Unk02013258Kind {
    u32 count;
    Unk02013258Note *notes;
    int up;
    int down;
};

extern "C" {
void func_020667f8(void *a, int b);
void func_020a62f0(void *g);
void func_020a6114(void *g, u32 a, u32 b);
void func_020a6340(void *g, u32 hash, const char *name, int a, int b);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a7d30(Unk020a7c90 *s, int x);
void func_020a8048(Unk020a7c90 *s, u32 hash);
void func_020aa42c(Unk020a9d58 *l);
Unk020a7c90 *func_020aa04c(Unk020a9d58 *l, u32 id);
void func_020aa1c0(Unk020a9d58 *l, Unk02098e70 *p, int touched);
int func_020a60bc();
int func_020a2994();
void func_020a34e4(int a, int h);
void func_020a3550(int a, int h, int v);
void func_020a35a4(int a, int h, int v);
int func_020a2ce8(int sound, u32 hash, int volume, int unk);
void func_020a3f84(void *a, int b);
void func_0209f880(void *a, int b);
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
Unk020a5ccc *func_02013f58(Unk02093648 *file, int a, int b);
extern u8 data_020c43a8[];
extern u8 data_020d60c8[];
extern u8 data_020d6cdc[];
}
int *func_02097a4c();
int func_020978dc(int a);
bool func_02097248(int key);

static Unk02013258Note data_020b7d8c[] = {{0, 0, 1}};

extern Unk02013258Note data_020b7dd8[];
extern Unk02013258Note data_020b7e2c[];

Unk02013258Kind data_020b7d98[] = {
    {7, data_020b7dd8, 10, 6},
    {13, data_020b7e2c, 10, 6},
    {1, data_020b7d8c, 10, 12},
    {1, data_020b7d8c, 10, 12},
};

Unk02013258Note data_020b7dd8[] = {
    {0x10000, 0, 0}, {0, 1, 3},        {0x80, 2, 5},       {0x100, 4, 9},
    {0x1c0, 8, 0x11}, {0x240, 0x10, 0x21}, {0x300, 0x18, 0x41},
};

Unk02013258Note data_020b7e2c[] = {
    {0x10000, 0, 0},     {0, 1, 3},           {0x40, 2, 5},        {0x80, 4, 9},
    {0xc0, 8, 0x11},     {0x100, 0x11, 0x23}, {0x140, 0x12, 0x25}, {0x180, 0x14, 0x29},
    {0x1c0, 0x18, 0x31}, {0x200, 0x21, 0x43}, {0x240, 0x22, 0x45}, {0x280, 0x24, 0x49},
    {0x2c0, 0x28, 0x51},
};

static const u32 data_020ae67c[4] = {0x185f14a4, 0x7b71a24c, 0x7ec30c1c, 0x8efb0072};

Unk02013258::Unk02013258(Unk02093648 *file, int a, int b)
    : Unk020a5ccc(file, a, b), layout(file, 0), shown(0), state(0), handle(-1), volume(0), kind(0), pitch(0),
      target(0), index(0), hash(0), hash2(0), hash3(0), anim(4) {
    int i;
    for (i = 0; i < 8; i++) {
        sprites[i] = 0;
    }
    Unk02013258Arg *args = (Unk02013258Arg *)a;
    for (i = 0; i < b; i++) {
        if (args[i].key == 0xe6884a5d) {
            switch (args[i].value) {
            case (int)0x01c75aa4:
                kind = 3;
                hash = 0xeac2a4e3;
                hash2 = 0x6565dfa6;
                hash3 = 0x8027c8af;
                break;
            case (int)0xad3db900:
                kind = 2;
                hash = 0xbe7b5c71;
                hash2 = 0xf073389b;
                hash3 = 0x306c94ca;
                break;
            case (int)0x5fc7c74d:
                kind = 0;
                hash = 0x55663e7f;
                hash2 = 0x860585bd;
                hash3 = 0xdcf449c0;
                break;
            case (int)0xbec827ce:
                kind = 1;
                hash = 0x4445acb9;
                hash2 = 0xb74b6cd1;
                hash3 = 0xd11f553c;
                break;
            }
        }
    }
}

Unk02013258::~Unk02013258() {
    func_020a62f0(this);
    data_020c43a8[0x38] = 0;
    func_020667f8(data_020c43a8, 0xa);
}

void Unk02013258::func_10(bool a) {
    func_020aa06c(&layout, a);
    shown = a;
}

void Unk02013258::func_0201351c(int anim, int a, int force, int b) {
    static const char *data_020b7ec8[] = {
        "idle_ocarina",     "play_ocarina",     "putback_ocarina",     "takeout_ocarina",
        "idle_adv_ocarina", "play_adv_ocarina", "putback_adv_ocarina", "takeout_adv_ocarina",
        "idle_conch",       "play_conch",       "putback_conch",       "takeout_conch",
        "idle_spconch",     "play_spconch",     "putback_spconch",     "takeout_spconch",
    };
    if (!force && this->anim == anim) {
        return;
    }
    func_020a6340(this, hash, data_020b7ec8[anim + kind * 4], a, b);
    this->anim = anim;
}

void Unk02013258::func_14() {
    Unk020a7af4Entry entries[0x28];
    Unk020a7af4 names(entries, 0x28);
    func_020aa42c(&layout);
    func_020aba38(file, 0x8f33eb93, &layout, &names);
    Unk020a7c90 *s0 = func_020aa040(&layout, 2, func_020a7b50(&names, 0x96474d87));
    Unk020a7c90 *s1 = func_020aa040(&layout, 6, func_020a7b50(&names, 0xf1096b4b));
    func_020a6980(s0, data_020ae67c[kind]);
    func_020a8048(s1, data_020ae67c[kind]);
    button.func_02050838(func_020aa040(&layout, 0xb, func_020a7b50(&names, 0xc2f94842)), false);
    button.func_02050c48(0, 1, -1);
    if (kind == 0) {
        sprites[0] = func_020aa04c(&layout, func_020a7b50(&names, 0x4e4667c8));
        sprites[1] = func_020aa04c(&layout, func_020a7b50(&names, 0x4e4667c9));
        sprites[2] = func_020aa04c(&layout, func_020a7b50(&names, 0x4e4667ca));
        sprites[3] = func_020aa04c(&layout, func_020a7b50(&names, 0x4e4667cb));
        sprites[4] = func_020aa04c(&layout, func_020a7b50(&names, 0x4e4667cc));
    }
    if (kind == 1) {
        int id = (u16)func_020a7b50(&names, 0x98ccd8b7);
        for (u32 i = 0; i < 8; i++) {
            sprites[i] = func_020aa040(&layout, 1, id++);
        }
    }
    if (kind == 3) {
        int id;
        int y;
        int i;
        u32 x;
        id = (u16)func_020a7b50(&names, 0x06c3333b);
        bars[0] = func_020aa040(&layout, 1, id++);
        x = func_020a7ca4(bars[0]);
        y = func_020a7cc0(bars[0]) + 0x10000;
        func_020a7cf0(bars[0], true);
        for (i = 1; i < 11; i++) {
            bars[i] = func_020aa040(&layout, 1, id++);
            func_020a7c90(bars[i], x);
            func_020a7cac(bars[i], y);
            y += 0x10000;
            func_020a7cf0(bars[i], true);
            func_020a69ac(bars[i], 0);
            func_020a7d30(bars[i], 2);
        }
    }
    for (int i = 0; i < 8; i++) {
        if (sprites[i] != 0) {
            func_020a7cf0(sprites[i], false);
        }
    }
    if (shown == 1) {
        func_020aa06c(&layout, true);
    }
    func_02013f3c(&Unk02013258::func_020139f4);
}

bool Unk02013258::func_18() {
    int *touch = func_02097a4c();
    Unk02098e70 pos(touch[0] << 12, touch[1] << 12);
    func_020aa1c0(&layout, &pos, func_020978dc(0));
    func_020aa158(&layout);
    button.func_08();
    button.func_0c(false);
    if (button.touch.flags & 8) {
        func_0201351c(2, 0, 1, 0);
        func_1c();
        return false;
    }
    if (state == 0) {
        return false;
    }
    (this->*state)();
    return true;
}

void Unk02013258::func_1c() {
    int h = handle;
    if (h != -1) {
        func_020a34e4(func_020a2994(), h);
        handle = -1;
    }
    func_0209f880(data_020d60c8, saved);
}

void Unk02013258::func_020139f4() {
    volume = 0;
    if (handle == -1) {
        if (kind >= 2) {
            handle = func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_OCARINA SE_CONCHLOOP", 0, 0), 0x7f, 0);
        } else {
            handle = func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_OCARINA SE_OCARINA", 0, 0), 0x7f, 0);
        }
        func_020a3550(func_020a2994(), handle, volume);
    }
    func_020a3f84(data_020d6cdc, 0x1770);
    func_020a6114(this, hash2, hash3);
    func_0201351c(3, 0, 1, 0);
    func_02013f3c(&Unk02013258::func_02013b04);
    saved = *(int *)(data_020d60c8 + 0x13c);
    func_0209f880(data_020d60c8, saved >> 2);
}

void Unk02013258::func_02013b04() {
    if (anim == 2) {
        return;
    }
    if (anim == 3 && func_020a60bc() == 0) {
        return;
    }
    bool blow = false;
    u32 keys = 0;
    if (kind != 2) {
        if (func_02097248(0)) {
            keys = 2;
        }
        if (func_02097248(1)) {
            keys = 4;
        }
        if (func_02097248(0xb)) {
            keys = 8;
        }
        if (func_02097248(0xa)) {
            keys = 0x10;
        }
        if (func_02097248(9)) {
            if (kind == 0) {
                keys = 0x20;
            } else {
                keys |= 0x20;
            }
        }
        if (func_02097248(8)) {
            if (kind == 0) {
                keys = 0x40;
            } else {
                keys |= 0x40;
            }
        }
    }
    if (*(u32 *)(data_020d6cdc + 0x18) & 1) {
        keys |= 1;
    }
    if (kind == 2 || kind == 3) {
        if (keys & 1) {
            blow = true;
        }
    } else {
        if (keys >= 2) {
            if (keys & 1) {
                blow = true;
            }
        }
        if (kind == 1 && (keys == 0x21 || keys == 0x41 || keys == 0x61)) {
            blow = false;
        }
    }
    if (kind == 3) {
        if (func_020978dc(0) != 0) {
            int x = func_02097a4c()[0];
            int y = func_02097a4c()[1];
            if (x > 0xd0) {
                if (y < 0x18) {
                    y = 0x18;
                }
                if (y > 0xa8) {
                    y = 0xa8;
                }
                target = 0x60 - y;
            }
        }
        pitch += (target * 4 - pitch) / 6;
        index = 5 - pitch / 4 / 11;
        if (index < 0) {
            index = 0;
        }
        if (index > 10) {
            index = 10;
        }
        for (u32 i = 0; i < 11; i++) {
            func_020a69ac(bars[i], 0);
        }
        func_020a69ac(bars[index], 2);
        if (index - 1 > 0) {
            func_020a69ac((&bars[index])[-1], 1);
        }
        if (index + 1 < 11) {
            func_020a69ac((&bars[index])[1], 1);
        }
    }
    func_02013f04();
    int mask = 0;
    int found = 0;
    for (u32 i = 0; i != data_020b7d98[kind].count; i++) {
        if (keys == data_020b7d98[kind].notes[i].keys) {
            mask = data_020b7d98[kind].notes[i].mask;
            found = i;
            break;
        }
    }
    if (mask != 0) {
        for (u32 i = 0; i < 8; i++) {
            if (mask & (1 << i)) {
                func_020a69ac(sprites[i], i);
                func_020a7cf0(sprites[i], true);
            }
        }
    }
    if (blow) {
        func_0201351c(1, 1, 0, 0);
        volume += data_020b7d98[kind].up;
        if (volume > 0x7f) {
            volume = 0x7f;
        }
    } else {
        volume -= data_020b7d98[kind].down;
        if (volume < 0) {
            volume = 0;
            func_0201351c(0, 1, 0, 0);
        }
    }
    int h = handle;
    if (h == -1) {
        return;
    }
    func_020a3550(func_020a2994(), h, volume);
    if (kind == 3) {
        func_020a35a4(func_020a2994(), handle, pitch);
        return;
    }
    int speed = data_020b7d98[kind].notes[found].speed;
    if (speed != 0x10000) {
        func_020a35a4(func_020a2994(), handle, speed);
    }
}

void Unk02013258::func_02013f04() {
    for (int i = 0; i < 8; i++) {
        if (sprites[i] != 0) {
            func_020a7cf0(sprites[i], false);
        }
    }
}

void Unk02013258::func_02013f3c(State s) {
    state = s;
}

Unk020a5ccc *func_02013f58(Unk02093648 *file, int a, int b) {
    return new Unk02013258(file, a, b);
}
