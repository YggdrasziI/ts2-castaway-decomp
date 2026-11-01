/*
 * Unit 0x0201E2B0-0x02021CBC: the live mode screen (Unk0201e300, 0x1280 bytes,
 * vtable 0x020B8D6C), named by its string "Starting LiveModeBase Screen" and
 * its files under build/data/screens/livemode/; a window of the main game state
 * (unit_0206BCE0.cpp). Six queued object keys, the inventory, survival and
 * plus / minus keys, six need meters and a seventh meter with an alarm sound, a
 * panel with a gauge showing need changes, the clock, clouds, two flying
 * sprites and a sky palette blended by the hour.
 *
 * Bounds: hypothesis. The start is func_0201e2b0, before the constructor (it
 * is called only here and follows the inline slots of unit_0201DD90.cpp, so
 * the file name keeps the constructor's address); the end is unit_02021CBC.cpp. `.rodata` holds the key and
 * need tables of the constructor and two unused constants, `.data` the strings
 * and the vtable with its header, `.bss` the instance and the two blended
 * palettes. Real file name unknown.
 *
 * It holds the kept copies of the inline slots 8 to 12, 14, 15 and 16 of the
 * element base and of the key's func_10: defined inline here, in the order the
 * compiler emits them, reversed from their first use by each function. So
 * the base vtable is not emitted with them.
 *
 * Not complete: 36 of 54 functions at 100 % (comments above the others), `.data`
 * and `.bss` at 100 %. The `.rodata` words 4 and 0x46 at 0x020AE77C, never
 * loaded, are local `static const` sizes of the two name lists.
 */

#include "game/unk_screen.h"
#include "game/unk_sim.h"
#include "game/unk_element.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"
#include "game/unk_resource.h"

typedef signed char s8;

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The key class of unit_0204BEEC.cpp: only what is used here. */
class Unk0204beec : public Unk020b9b80 {
public:
    Unk0204beec();
    ~Unk0204beec();
    void func_0204c0f8(bool main);
    void func_0204c11c(const u32 *name);
    void func_0204c1b8(int priority);
    void func_0204c1c4(int w, int h);
    void func_0204c1d0(int count);
    void func_0204c264(int hAlign, int vAlign);
    void func_0204c280(const char *fmt, ...);
    void func_0204c440();
    void func_0204c4c4(short a, short b, short c, short d);
    void func_0204c500(short a, short b, short c, short d, short e, short f);
    void func_0204cfa8();
    void func_0204d3c0(int frame);

    bool func_04(bool locked);
    void func_00();
    void func_08();
    void func_0c(int priority);
    void func_14(int x, int y);

    Unk02098bc8 *func_10() {
        return &rect;
    }

    inline void func_active(bool on) {
        if (on) {
            flags |= 0x10;
        } else {
            flags &= ~0x10;
        }
    }

    Unk020b9e88Touch touch;
    Unk020b9e88Touch inside;
    Unk0209487c *file;
    Unk0208f8b0 *objects[6];
    int textId;
    Unk02090308 canvas;
    int textX;
    int textY;
    int hAlign;
    int vAlign;
    Unk02092830Font *font;
    Unk02098bc8 rect;
    int resource;
    s8 look[16];
    u16 flags;
    s8 priority;
    s8 color;
    u8 animation;
    u8 count;
    s8 oamPriority;
    int angle;
};

/* An entry of the object queue on the screen (0xF4 bytes). */
class Unk0201eb88 {
public:
    Unk0201eb88() : unk0(0), unke8(0), unkec(0), unkf0(0) {}

    u32 unk0;
    Unk0204beec key;
    int unke8;
    int unkec;
    u8 unkf0;
};

/* An icon of Unk02064330 (unit_02064330.cpp). */
class Unk02064730;

/* The icon set of unit_02064330.cpp. */
class Unk02064330 {
public:
    Unk02064330();
    ~Unk02064330();

    u8 unk0[0x154];
};

/* A need shown in the gauge panel. */
struct Unk0201e300Need {
    int need;
    int mask;
    int frame;
    int value;
    u8 changed;
};

/* A cloud. */
struct Unk0201e300Cloud {
    Unk020a7c90 *sprite;
    int speed;
    int x;
};

typedef void (*Unk020a80bcLoad)(void *data, u32 offset, u32 size);

class Unk0205cf00;

/* The change list of unit_02054734.cpp. */
struct Unk020548b0Node {
    Unk0205cf00 *def;
    int delta;
    Unk020548b0Node *next;
    u32 flags;
};

class Unk020bfc80 {
public:
    Unk020548b0Node *head;
};

/* An object held by the player. */
class Unk0201e300Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual void func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual int *func_20();

    u32 flags;
    u8 unk8[0xc];
    Unk0201e300Item *next;
};

/* The player (data_020c43a8): only the fields used here. */
class Unk020c43a8 {
public:
    u8 unk0[0xa4];
    int unka4;
    u8 unka8[0x32c];
    Unk0201e300Item *items;
};

class Unk020599a0;
class Unk02027994;

/* A need of the player. */
struct Unk02066488 {
    int unk0;
    int value;
};

/* The game clock. */
struct Unk020d6298 {
    int unk0;
    u32 time;
};

/* The main game state (unit_0206BCE0.cpp): only what is used here. */
class Unk0206bcf0 {
public:
    bool func_0206f0ec(int type, int b, int c);

    u8 unk0[0x144];
    Unk02027994 *unk144;
    u8 unk148[0xcc];
    Unk020599a0 *unk214;
    u8 unk218[4];
    void *unk21c;
    u8 unk220[0xc];
    u32 unk22c;
};

class Unk0201e300 : public Unk020a07d4 {
public:
    Unk0201e300();
    virtual ~Unk0201e300();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14() {
        return (flags & 2) != 0;
    }
    virtual void func_18();
    virtual void func_1c() {
        flags &= ~2;
    }
    virtual bool func_20() {
        return false;
    }
    virtual void func_24() {}
    virtual bool func_28() {
        return fade.func_shown();
    }
    virtual bool func_2c() {
        return fade.func_hidden();
    }
    virtual bool func_34() {
        return false;
    }
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    u32 flags;
    Unk020a07d4Timer fade;
    int unk10;
    Unk0201eb88 entries[6];
    int entryCount;
    Unk02064330 icons;
    Unk02064730 *icon;
    Unk02064730 *nextIcon;
    Unk020a07d4Timer queueFade;
    Unk0204beec keyA;
    Unk0204beec keyB;
    Unk0204beec keyC;
    Unk0204beec keyD;
    Unk0204beec keyE;
    Unk0204beec keyF;
    int shown;
    Unk0201e300Need needs[4];
    Unk0205007c gauge;
    Unk020a7c90 *gaugeIcon;
    Unk02051704 panel;
    Unk020a07d4Timer panelFade;
    Unk020a9d58 *layout2;
    Unk020a9d58 *layout1;
    Unk020a7c90 *clock;
    Unk020a7c90 *sprites1[6];
    Unk020a80bcLoad loads1[6];
    Unk020a7c90 *sprites2[6];
    Unk020a80bcLoad loads2[6];
    Unk020a7c90 *sky;
    Unk020a7c90 *birds[2];
    Unk0201e300Cloud clouds[10];
    Unk0201e300Cloud *active[3];
    u16 palettes1[6][0x20];
    u16 palettes2[6][0x10];
    u16 *from1;
    u16 *from2;
    u16 *to1;
    u16 *to2;
    int period;
    Unk0204eb78 meters[6];
    Unk0204eb78 alarm;
    Unk0204f798 anim;
    u8 unk1278;
    int sound;
};

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;
extern Unk020bfc80 data_020bfc80;
extern Unk020d6298 data_020d6298;
extern u8 data_020c4770[];
extern u8 data_020d62a4[];

extern "C" {
Unk020d6240 *func_020a18e4();
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
void func_020a1138(Unk020d6240 *system, int a, int b);
void func_020a122c(Unk020d6240 *system);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020897b4(const char *fmt, ...);
void func_020a80bc(Unk020a7c90 *s, Unk020a80bcLoad load);
Unk020a80bcLoad func_020a80c4(Unk020a7c90 *s);
void func_020a6980(Unk020a7c90 *s, u32 hash);
u32 func_020a69a4(Unk020a7c90 *s);
void func_020a69ac(Unk020a7c90 *s, int palette);
int func_020a69cc(Unk020a7c90 *s);
int func_020a7d1c(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
int func_020a20bc(void *random, int min, int max);
void *func_020a2994();
void *func_020a3858(void *sound, u32 hash, int a, int b, int c);
int func_020a2ce8(void *sound, u32 hash, int volume, int unk);
int func_020a3514(void *sound, int handle);
void GXS_LoadOBJPltt(void *data, u32 offset, u32 size);
void GXS_LoadBGPltt(void *data, u32 offset, u32 size);
void DC_FlushRange(void *data, u32 size);

Unk0206bcf0 *func_0206bce0();
void func_02028eec(Unk02027994 *o, int mode, Unk0205cf00 *def, void *p);
u32 func_02059cf8(Unk020599a0 *p);
bool func_0205d340(Unk0205cf00 *def, u32 key);
int func_0205d134(Unk0205cf00 *def, u32 key);
void func_02007d94(void *list);
int func_02007dbc(void *list);
void func_02054a4c(Unk020bfc80 *p);
void func_02054a70(Unk020bfc80 *p);
int func_0201e2b0(Unk020548b0Node *n);
Unk02066488 *func_02066488(Unk020c43a8 *p, int need);
int func_0206647c(Unk020c43a8 *p, int need);
bool func_0206757c(Unk020c43a8 *p, int mask);
void func_0206471c(Unk02064730 *e, int x, int y);
void func_02064754(Unk02064730 *e);
void func_020643b8(Unk02064330 *set, int screen);
void func_020643c4(Unk02064330 *set);
void func_020643ec(Unk02064330 *set);
void func_02064444(Unk02064330 *set);
Unk02064730 *func_020644cc(Unk02064330 *set, int key, int palette, int priority);

Unk0202071c func_0202071c(Unk020d6298 *clock);
void func_0201ef54(Unk0201e300 *p);
void func_0201f838(Unk0201e300 *p);
void func_02020938(Unk0201e300 *p, int need);
void func_02020978(Unk0201e300 *p);
void func_020209e4(Unk0201e300 *p);
void func_02020dc0(Unk0201e300 *p);
void func_02020f24(Unk0201e300 *p);
void func_02020fb8(Unk0201e300 *p);
void func_02021090(Unk0201e300 *p);
void func_020211cc(void *data, u32 offset, u32 size);
void func_0202120c(void *data, u32 offset, u32 size);
void func_0202124c(void *data, u32 offset, u32 size);
void func_0202128c(void *data, u32 offset, u32 size);
void func_020212cc(void *data, u32 offset, u32 size);
void func_0202130c(void *data, u32 offset, u32 size);
void func_0202134c(void *data, u32 offset, u32 size);
void func_0202138c(void *data, u32 offset, u32 size);
void func_020213cc(void *data, u32 offset, u32 size);
void func_0202140c(void *data, u32 offset, u32 size);
void func_0202144c(void *data, u32 offset, u32 size);
void func_0202148c(void *data, u32 offset, u32 size);
void func_020214cc(Unk0201e300 *p, int t);
void func_020216e0(Unk0201e300 *p, int from, int to);
void func_0202171c(Unk0201e300 *p);
void func_02021888(Unk0201e300 *p);
}

Unk0201e300 *data_020be3b0;
u16 data_020be3b4[0x20];
u16 data_020be3f4[0x10];

int func_0201e2b0(Unk020548b0Node *n) {
    int id = 0x76034;
    if (!func_0205d340(n->def, 0x3d9aefc0)) {
        id = func_0205d134(n->def, 0x9d5bba8e);
        if (id == -1) {
            id = 0;
        }
    }
    return id;
}

/*
 * 98.47 %: registers of the cloud and need loops; the original reloads the need
 * index from the stack table after each store and keeps the third table address
 * loaded earlier.
 */
Unk0201e300::Unk0201e300()
    : flags(0), unk10(1), icon(0), nextIcon(0), shown(-1), layout1(0), clock(0), from1(0), from2(0), to1(0), to2(0),
      period(-1), unk1278(0), sound(-1) {
    u32 keys1[6] = {0x3a23a541, 0x6b69d7a8, 0x3b4fe5be, 0xd65832df, 0xcb4c0704, 0x40ee9c8e};
    u32 keys2[6] = {0x28694930, 0xf7864cb9, 0x299589ad, 0x89a1412f, 0x1927bce7, 0x59da5497};
    u32 keys3[10] = {0xc7425c2, 0xc7425c3, 0xc7425c4, 0xc7425c5, 0xc7425c6,
                     0xc7425c7, 0xc7425c8, 0xc7425c9, 0xc7425ca, 0xc7425cb};
    static const int size1 = 0x46;
    static const int size2 = 4;
    Unk020a7af4Entry entries1[size1];
    Unk020a7af4 names1(entries1, size1);
    Unk020a7af4Entry entries2[size2];

    data_020be3b0 = this;
    layout1 = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x974a9fac, layout1, &names1);
    func_020a9db8(layout1, func_020a154c, 0);

    Unk020a7af4 names2(entries2, size2);
    layout2 = new Unk020a9d58(func_020a18e4()->archive, 1);
    func_020aba38(func_020a18e4()->archive, 0x179c14aa, layout2, &names2);
    func_020a9db8(layout2, func_020a154c, 0);

    sky = func_020aa040(layout1, 2, func_020a7b50(&names1, 0x9e2bd6e4));
    birds[0] = func_020aa040(layout1, 0xb, func_020a7b50(&names1, 0x1bccc05));
    birds[1] = func_020aa040(layout1, 0xb, func_020a7b50(&names1, 0x1bccc06));

    for (u32 i = 0; i < 6; i++) {
        sprites1[i] = func_020aa040(layout1, 6, func_020a7b50(&names1, keys1[i]));
        sprites2[i] = func_020aa040(layout1, 5, func_020a7b50(&names1, keys2[i]));
        loads1[i] = func_020a80c4(sprites1[i]);
        loads2[i] = func_020a80c4(sprites2[i]);
    }

    func_020a80bc(sprites1[0], func_020211cc);
    func_020a80bc(sprites1[1], func_0202120c);
    func_020a80bc(sprites1[2], func_0202124c);
    func_020a80bc(sprites1[3], func_0202128c);
    func_020a80bc(sprites1[4], func_020212cc);
    func_020a80bc(sprites1[5], func_0202130c);
    func_020a80bc(sprites2[0], func_0202134c);
    func_020a80bc(sprites2[1], func_0202138c);
    func_020a80bc(sprites2[2], func_020213cc);
    func_020a80bc(sprites2[3], func_0202140c);
    func_020a80bc(sprites2[4], func_0202144c);
    func_020a80bc(sprites2[5], func_0202148c);

    for (u32 i = 0; i < 10; i++) {
        Unk0201e300Cloud *cloud = &clouds[i];
        cloud->sprite = func_020aa040(layout1, 0xb, func_020a7b50(&names1, keys3[i]));
        cloud->x = func_020a7ca4(cloud->sprite);
        cloud->speed = 0;
    }
    for (u32 i = 0; i < 3; i++) {
        active[i] = 0;
    }

    clock = func_020aa040(layout1, 1, func_020a7b50(&names1, 0xedb999d));
    anim.func_0204f8a0(1);
    anim.func_0204f8f4(func_020aa040(layout1, 1, func_020a7b50(&names1, 0x1a389d46)));
    anim.delay = 9;

    for (int i = 0; i < 6; i++) {
        meters[i].func_0204ebd4(0);
        meters[i].func_0204ebe4(func_020aa040(layout1, 1, func_020a7b50(&names1, 0x1f19df27 + i)));
        meters[i].func_0204ec10(func_020aa040(layout1, 1, func_020a7b50(&names1, 0xc56fae8c + i)));
        meters[i].func_0204ebdc(func_020aa040(layout1, 1, func_020a7b50(&names1, 0xe5f7d4a + i)));
    }

    alarm.func_0204ebd4(3);
    alarm.func_0204ebe4(func_020aa040(layout1, 1, func_020a7b50(&names1, 0x52d6f)));
    alarm.func_0204ec10(func_020aa040(layout1, 1, func_020a7b50(&names1, 0x478e6f3)));

    int frames[4] = {3, 0, 2, 1};
    int indices[4] = {0, 1, 2, 3};
    int masks[4] = {0x40, 0x80, 0x100, 0x200};
    for (int i = 0; i < 4; i++) {
        needs[i].need = indices[i];
        needs[i].mask = masks[i];
        needs[i].value = func_02066488(&data_020c43a8, indices[i])->value;
        needs[i].frame = frames[i];
        needs[i].changed = 0;
    }

    gauge.func_0205012c(func_020aa040(layout2, 1, func_020a7b50(&names2, 0x1b447166)));
    gauge.delay = 5;
    gauge.func_02050600(0, 0x186a0000);
    panel.func_020518a8(1);
    panel.func_02051804(1);
    panel.func_020518fc(&gauge);
    gaugeIcon = func_020aa040(layout2, 1, func_020a7b50(&names2, 0x40a1e86b));
    panel.func_02051858(gaugeIcon);
    panel.func_18(false);
    panelFade.func_duration(0x6e);
    panelFade.timer = 0;
    panelFade.state = 5;
}

Unk0201e300::~Unk0201e300() {
    if (flags & 1) {
        func_0201f838(this);
    }
    delete layout2;
    delete layout1;
}

void Unk0201e300::func_08() {
    if (func_020a0b8c(data_020d6240.unk8, this) == 0) {
        func_020a0b0c(data_020d6240.unk8, this);
        func_020897b4("Starting LiveModeBase Screen");
    }
}

bool Unk0201e300::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    unk10 = a;
    fade.func_duration(0x10);
    fade.state = 0;
    func_0201ef54(this);
    if (!(flags & 0x40)) {
        flags |= 0x20;
    }
    return false;
}

bool Unk0201e300::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (!(flags & 8)) {
        fade.func_duration(0x10);
        fade.state = 3;
        func_020a1494(func_020a18e4(), 2, 0x10);
        func_020a11f8(func_020a18e4(), 2, 1);
    } else {
        func_0201f838(this);
        fade.timer = 0;
        fade.state = 5;
        func_020a1138(func_020a18e4(), 2, 1);
        return true;
    }
    return false;
}

void func_0201ef54(Unk0201e300 *p) {
    if (p->flags & 1) {
        return;
    }
    func_020aa06c(p->layout2, true);
    func_020aa06c(p->layout1, true);
    p->period = -1;
    func_020a14e0(func_020a18e4(), 1);

    Unk02093648 *archive = func_020a18e4()->archive;
    Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(0xcfc22ac6));
    Unk020916a4::func_02091840(1)->func_0209201c((Unk02095140 *)file, 0, 0xf0, 0x80, 0x10);
    archive->func_02093c3c(file);

    for (int i = 0; i < 6; i++) {
        Unk0204beec *key = &p->entries[i].key;
        key->func_0204c11c((const u32 *)"build/data/screens/livemode/icons_queue.nitro_map");
        key->func_0204c4c4(2, -1, 0, -1);
        key->func_0204c1c4(0x10000, 0x10000);
        key->func_0204c0f8(true);
        key->func_0204c1b8(i + 0x3c);
    }
    p->entries[0].key.func_0204cfa8();

    p->queueFade.func_duration(0x73);
    p->queueFade.timer = p->queueFade.duration;
    p->queueFade.state = 2;
    func_020643b8(&p->icons, 1);
    func_020643ec(&p->icons);

    p->keyB.func_0204c11c((const u32 *)"build/data/screens/livemode/inventory.nitro_map");
    p->keyB.func_0204c4c4(3, -1, 0, -1);
    p->keyB.func_14(0x2000, 0);
    p->keyB.func_0204c1d0(2);
    p->keyB.func_0204c0f8(true);
    p->keyB.func_0204c1b8(0x42);
    p->keyB.func_0c(0);
    p->keyB.func_20(-0x2b000, 0);
    p->keyB.func_30(0x20);

    p->keyC.func_0204c11c((const u32 *)"build/data/screens/livemode/icon_bg.nitro_map");
    p->keyC.func_0204c4c4(0xd, -1, 0, -1);
    p->keyC.func_14(0x1e000, 0);
    p->keyC.func_0204c0f8(true);
    p->keyC.func_0204d3c0(1);
    p->keyC.func_0204c1b8(0x41);
    p->keyC.func_0c(0);
    p->keyC.func_0204cfa8();
    p->keyC.func_20(-0x2b000, 0);
    p->keyC.func_30(0x20);

    p->keyD.func_0204c11c((const u32 *)"build/data/screens/livemode/icon_bg.nitro_map");
    p->keyD.func_14(0x1e000, 0);
    p->keyD.func_0204c1c4(0x24000, 0x24000);
    p->keyD.func_0204c0f8(true);
    p->keyD.func_0204d3c0(0);
    p->keyD.func_0204c1b8(0x3f);
    p->keyD.func_0204c4c4(0xd, -1, 0, -1);
    p->keyD.func_0c(0);
    p->keyD.func_20(-0x2b000, 0);
    p->keyD.func_30(0x20);

    p->keyE.func_0204c11c((const u32 *)"build/data/screens/livemode/cancel.nitro_map");
    p->keyE.func_0204c4c4(3, 4, 0, 1);
    p->keyE.func_14(0x1c000, 0x20000);
    p->keyE.func_0204c1c4(0x8000, 0x8000);
    p->keyE.func_0204c0f8(true);
    p->keyE.func_0204c1b8(0x3d);
    p->keyE.func_0c(0);
    p->keyE.func_0204cfa8();
    p->keyE.func_20(p->keyE.func_10()->y - 0x2b000, p->keyE.func_10()->y);
    p->keyE.func_30(0x20);

    p->keyF.func_0204c11c((const u32 *)"build/data/screens/livemode/plus_minus.nitro_map");
    p->keyF.func_0204c4c4(3, -1, 0, -1);
    p->keyF.func_14(0x5000, 0x20000);
    p->keyF.func_0204c1c4(0x14000, 0x8000);
    p->keyF.textX = 0x8000;
    p->keyF.textY = -0x3000;
    p->keyF.func_0204c440();
    p->keyF.func_0204c0f8(true);
    p->keyF.func_0204c264(0, 0);
    p->keyF.func_0204c1b8(0x3d);
    p->keyF.func_0c(0);
    p->keyF.func_0204cfa8();
    p->keyF.func_20(p->keyF.func_10()->y - 0x2b000, p->keyF.func_10()->y);
    p->keyF.func_30(0x20);

    p->keyA.func_0204c11c((const u32 *)"build/data/screens/livemode/survival.nitro_map");
    p->keyA.func_0204c500(3, 4, 5, 0, 1, 2);
    p->keyA.func_14(0x2000, 0x1000);
    p->keyA.func_0204c1c4(0x18000, 0x1b000);
    p->keyA.func_0204c0f8(true);
    p->keyA.func_0204c1b8(0x3c);
    p->keyA.func_0c(0);
    p->keyA.func_0204cfa8();

    if (p->unk1278 != 0) {
        func_02020fb8(p);
    }
    p->flags |= 1;
}

inline void Unk020b9b80::func_30(int duration) {
    this->duration = duration;
    if (timer > this->duration) {
        timer = this->duration;
    }
    timer = 0;
    state = 5;
    Unk020b9e88Track *track = trackX;
    if (track != 0) {
        int x = Unk020b9e88::func_sample(track, timer, this->duration);
        func_14(x, func_10()->y);
    }
    track = trackY;
    if (track != 0) {
        int y = Unk020b9e88::func_sample(track, timer, this->duration);
        func_14(func_10()->x, y);
    }
}

inline void Unk020b9b80::func_20(int a, int b) {
    valuesY[0] = a;
    valuesY[1] = b;
    trackY = &keysY;
}

void func_0201f838(Unk0201e300 *p) {
    p->flags &= ~0x80;
    if (!(p->flags & 1)) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        p->entries[i].key.func_08();
    }
    func_02020978(p);
    func_020aa06c(p->layout2, false);
    func_020aa06c(p->layout1, false);
    if (p->keyB.func_34() && (p->keyD.func_34() || p->keyD.func_38()) && data_020bfc80.head != 0) {
        func_02054a4c(&data_020bfc80);
    }
    p->keyA.func_08();
    p->keyB.func_08();
    p->keyC.func_08();
    p->keyD.func_08();
    p->keyE.func_08();
    p->keyF.func_08();
    p->icon = 0;
    p->nextIcon = 0;
    func_020643c4(&p->icons);
    func_02064444(&p->icons);
    p->flags &= ~1;
}

inline bool Unk020b9b80::func_38() {
    return func_hidden();
}

inline bool Unk020b9b80::func_34() {
    return func_shown();
}

bool Unk0201e300::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    if (entryCount != 0) {
        done = entries[0].key.func_04(done);
        if (entries[0].key.touch.flags & 4) {
            flags |= 4;
        } else if (entries[0].key.inside.flags & 8) {
            flags &= ~4;
        } else if (entries[0].key.touch.flags & 8) {
            flags &= ~4;
            func_02007d94(data_020c4770);
        }
    } else {
        flags &= ~4;
    }

    done = keyA.func_04(done);
    if (keyA.touch.flags & 4) {
        flags |= 4;
    } else if (keyA.inside.flags & 8) {
        flags &= ~4;
    } else if (keyA.touch.flags & 8) {
        flags &= ~4;
        func_0206bce0()->func_0206f0ec(0, 1, 0);
    }

    done = keyE.func_04(done);
    if (keyE.touch.flags & 4) {
        flags |= 4;
    } else if (keyE.inside.flags & 8) {
        flags &= ~4;
    } else if (keyE.touch.flags & 8) {
        flags &= ~4;
        queueFade.timer = queueFade.duration;
        queueFade.state = 2;
        func_02054a70(&data_020bfc80);
        keyB.func_28(0x20);
        keyD.func_28(0x20);
        keyE.func_28(0x20);
        keyF.func_28(0x20);
        keyC.func_28(0x20);
    }

    done = keyD.func_04(done);
    if (keyD.touch.flags & 4) {
        flags |= 4;
    } else if (keyD.inside.flags & 8) {
        flags &= ~4;
    } else if (keyD.touch.flags & 8) {
        flags &= ~4;
        Unk020548b0Node *n = data_020bfc80.head;
        if (n != 0 && n->delta > 0) {
            func_0206bce0()->func_0206f0ec(0xf, 1, 0);
            Unk02027994 *guide = func_0206bce0()->unk144;
            if (guide != 0) {
                func_02028eec(guide, 0xf, n->def, 0);
            }
        }
    }
    return done;
}

inline void Unk020b9b80::func_28(int duration) {
    this->duration = duration;
    if (timer > this->duration) {
        timer = this->duration;
    }
    state = 3;
}

/* 99.60 %: the "%d" literal and the func_0202071c call are shown as different; the instructions are the same. */
void Unk0201e300::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    queueFade.func_step();
    fade.func_step();
    func_02020dc0(this);
    anim.func_08();

    Unk020c43a8 *player = &data_020c43a8;
    keyA.func_active(func_02007dbc(data_020c4770) == 0);
    keyA.func_00();

    if (keyB.func_40()) {
        func_020643c4(&icons);
        icon = 0;
        nextIcon = 0;
    } else if (keyD.func_40() && keyB.func_34()) {
        if (data_020bfc80.head == 0) {
            func_02020f24(this);
        } else {
            keyD.func_2c(0x20);
            Unk020548b0Node *n = data_020bfc80.head;
            func_02064754(icon);
            icon = func_020644cc(&icons, func_0201e2b0(n), 6, 0x3e);
            func_0206471c(icon, keyD.func_10()->x + 0x2000, keyD.func_10()->y);
        }
    }

    if (keyB.func_38() && data_020bfc80.head != 0) {
        icon = func_020644cc(&icons, func_0201e2b0(data_020bfc80.head), 6, 0x3e);
        keyB.func_24(0x20);
        keyD.func_24(0x20);
        keyC.func_24(0x20);
        keyE.func_24(0x20);
        keyF.func_24(0x20);
    }

    if (keyD.func_34() && keyB.func_34()) {
        Unk020548b0Node *n = data_020bfc80.head;
        if (n == 0) {
            func_02020f24(this);
        } else {
            if (queueFade.func_shown()) {
                queueFade.state = 3;
                if (unk1278 == 0) {
                    Unk0205cf00 *def = n->def;
                    if (func_0205d340(def, 0x99a2c231)) {
                        func_020a3858(func_020a2994(), 0x82d70b47, 0, 0, 0);
                    } else if (func_0205d340(def, 0x3d9aefc0) && !func_0205d340(def, 0x69a133c5)) {
                        func_020a3858(func_020a2994(), 0xf4a766d1, 0, 0, 0);
                    } else if (n->flags & 1) {
                        func_020a2ce8(func_020a2994(), 0x2b54a9d1, 0x7f, 0);
                    } else {
                        func_020a2ce8(func_020a2994(), 0xa0c6143a, 0x7f, 0);
                    }
                }
            }
            if (queueFade.state == 4) {
                queueFade.timer = queueFade.duration;
                queueFade.state = 2;
                if (n != 0) {
                    if (n->next == 0) {
                        func_02054a4c(&data_020bfc80);
                        func_02020f24(this);
                    } else {
                        if (nextIcon != 0) {
                            func_02064754(nextIcon);
                        }
                        func_02054a4c(&data_020bfc80);
                        keyD.func_28(0x16);
                        nextIcon = func_020644cc(&icons, func_0201e2b0(n->next), 7, 0x40);
                        func_0206471c(nextIcon, keyC.func_10()->x + 0x2000, keyC.func_10()->y);
                    }
                }
            }
        }
    }

    Unk020548b0Node *n = data_020bfc80.head;
    if (n != 0) {
        if (n->delta < 0) {
            keyF.func_0204d3c0(1);
        } else {
            keyF.func_0204d3c0(0);
        }
        keyF.func_0204c280("%d", n->delta);
        int next = 0;
        if (n->next != 0) {
            keyC.func_0204d3c0(1);
            next = 1;
        } else {
            keyC.func_0204d3c0(next);
        }
        if (keyD.state == 3 || keyD.func_38()) {
            if (n->delta < 0) {
                keyC.func_0204d3c0(next + 2);
            } else if (n->flags & 1) {
                keyC.func_0204d3c0(next);
            } else {
                keyC.func_0204d3c0(next + 4);
            }
        } else if (n->delta < 0) {
            keyD.func_0204d3c0(2);
        } else if (n->flags & 1) {
            keyD.func_0204d3c0(0);
        } else {
            keyD.func_0204d3c0(4);
        }
    }

    keyB.func_00();
    keyC.func_00();
    keyD.func_00();
    keyE.func_00();
    keyF.func_00();

    if (icon != 0) {
        func_0206471c(icon, keyD.func_10()->x + 0x2000, keyD.func_10()->y);
    }
    if (nextIcon != 0) {
        func_0206471c(nextIcon, keyC.func_10()->x + 0x2000, keyC.func_10()->y);
    }

    if (!(flags & 0x10)) {
        func_020a69ac(clock, (func_0202071c(&data_020d6298).value & 0x7c0) >> 6);
    }

    meters[0].func_0204ec2c(func_0206647c(player, 0) / 39062);
    meters[1].func_0204ec2c(func_0206647c(player, 1) / 39062);
    meters[2].func_0204ec2c(func_0206647c(player, 4) / 39062);
    meters[3].func_0204ec2c(func_0206647c(player, 2) / 39062);
    meters[4].func_0204ec2c(func_0206647c(player, 3) / 39062);
    meters[5].func_0204ec2c(func_0206647c(player, 5) / 39062);
    for (int i = 0; i < 6; i++) {
        meters[i].func_0204ec44();
    }

    alarm.func_0204ec2c(player->unka4 / 39062);
    alarm.func_0204ec44();

    int playing = 0;
    int handle = sound;
    if (handle != -1) {
        playing = func_020a3514(func_020a2994(), handle);
    }
    if (alarm.func_0204ec18()) {
        if (playing == 0) {
            sound = func_020a2ce8(func_020a2994(), 0x672e672d, 0x7f, 0);
        }
    } else if (playing == 0) {
        sound = -1;
    }

    func_020209e4(this);
    func_02021888(this);
    func_020aa158(layout2);
    func_020aa158(layout1);

    if (flags & 0x20) {
        func_020a1494(func_020a18e4(), 2, 0x10);
        func_020a122c(func_020a18e4());
        flags &= ~0x20;
    }
    if (flags & 1) {
        flags |= 0x80;
    }
    if (fade.state == 4) {
        func_0201f838(this);
    }
}

inline Unk0202071c func_0202071c(Unk020d6298 *clock) {
    Unk0202071c t;
    t.value = clock->time;
    return t;
}

inline void Unk020b9b80::func_24(int duration) {
    this->duration = duration;
    if (timer > this->duration) {
        timer = this->duration;
    }
    state = 0;
}

inline void Unk020b9b80::func_2c(int duration) {
    this->duration = duration;
    if (timer > this->duration) {
        timer = this->duration;
    }
    timer = this->duration;
    state = 2;
    Unk020b9e88Track *track = trackX;
    if (track != 0) {
        int x = Unk020b9e88::func_sample(track, timer, this->duration);
        func_14(x, func_10()->y);
    }
    track = trackY;
    if (track != 0) {
        int y = Unk020b9e88::func_sample(track, timer, this->duration);
        func_14(func_10()->x, y);
    }
}

inline bool Unk020b9b80::func_40() {
    return state == 4;
}

void func_02020938(Unk0201e300 *p, int need) {
    for (int i = 0; i < 4; i++) {
        if (need == p->needs[i].need) {
            p->needs[i].changed = 1;
            return;
        }
    }
}

void func_02020978(Unk0201e300 *p) {
    p->panel.func_18(false);
    p->panelFade.timer = 0;
    p->panelFade.state = 5;
    p->shown = -1;
    for (int i = 0; i < 4; i++) {
        p->needs[i].value = func_02066488(&data_020c43a8, p->needs[i].need)->value;
    }
}

void func_020209e4(Unk0201e300 *p) {
    for (int i = 0; i < 4; i++) {
        int value = func_02066488(&data_020c43a8, p->needs[i].need)->value;
        if (value == p->needs[i].value && p->needs[i].changed == 0) {
            continue;
        }
        int delta = value - p->needs[i].value;
        if (p->shown < 0) {
            if (delta > 100010 || delta < -100010 || p->needs[i].changed != 0) {
                if (func_0206757c(&data_020c43a8, p->needs[i].mask)) {
                    p->panel.func_18(true);
                    int frame = p->needs[i].frame;
                    func_020a69ac(p->gaugeIcon, frame);
                    Unk02093648 *archive = func_020a18e4()->archive;
                    Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(func_020a69a4(p->gaugeIcon)));
                    Unk020916a4 *oam = Unk020916a4::func_02091820();
                    int index = func_020a69cc(p->gaugeIcon);
                    oam->func_0209201c((Unk02095140 *)file, index, frame << 4, func_020a7d44(p->gaugeIcon) << 4, 0x10);
                    archive->func_02093c3c(file);
                    int old = p->needs[i].value / 100;
                    p->gauge.func_020501f8(FX32(old));
                    p->panelFade.timer = p->panelFade.duration;
                    p->panelFade.state = 2;
                    int target = value / 100;
                    p->shown = i;
                    p->gauge.func_020501a8(FX32(target));
                }
            }
            p->needs[i].value = value;
            p->needs[i].changed = 0;
        } else if (p->shown == i) {
            if (delta >= 100010 || delta <= -100010) {
                int target = value / 100;
                p->gauge.func_020501a8(FX32(target));
            }
            p->needs[i].value = value;
            p->needs[i].changed = 0;
        } else if (delta < 100010 && delta > -100010) {
            p->needs[i].value = value;
        }
    }

    if (p->shown >= 0 && p->gauge.func_0205060c()) {
        if (p->panelFade.func_shown()) {
            p->panelFade.state = 3;
        } else if (p->panelFade.func_hidden()) {
            p->panel.func_18(false);
            p->shown = -1;
        }
    }
    p->panelFade.func_step();
    p->panel.func_08();
}

/* 97.93 %: registers of the counter, frame and entry in the second loop. */
void func_02020dc0(Unk0201e300 *p) {
    int i;
    if (!(p->flags & 1)) {
        return;
    }
    p->entryCount = 0;
    for (int i = 0; i < 6; i++) {
        p->entries[i].key.func_14(0x100000, 0xc0000);
    }
    Unk0201eb88 *entry;
    Unk0201e300Item *item = data_020c43a8.items;
    for (i = 0; i < 6 && item != 0; i++) {
        int frame = item->func_20()[0];
        entry = &p->entries[p->entryCount];
        if (frame != -1 && !(item->flags & 0x10)) {
            if (!(entry->key.flags & 2)) {
                entry->key.func_0c(0);
            }
            entry->key.func_0204d3c0(frame);
            int x = p->entryCount * 3;
            entry->key.func_14(FX32(x) + 0xe6000, 0x8000);
            entry->key.func_00();
            p->entryCount++;
        }
        item = item->next;
    }
}

void Unk0201e300::func_18() {
    flags |= 2;
}

void func_02020f24(Unk0201e300 *p) {
    p->keyB.func_28(0x20);
    p->keyD.func_28(0x20);
    p->keyE.func_28(0x20);
    p->keyF.func_28(0x20);
    p->keyC.func_28(0x20);
    p->queueFade.timer = p->queueFade.duration;
    p->queueFade.state = 2;
}

void func_02020fb8(Unk0201e300 *p) {
    p->unk1278 = 1;
    p->keyB.func_14(-0x64000, 0);
    p->keyC.func_14(-0x64000, 0);
    p->keyD.func_14(-0x64000, 0);
    p->keyE.func_14(-0x64000, 0);
    p->keyF.func_14(-0x64000, 0);
    p->keyA.func_14(-0x64000, 0);
}

void func_02021090(Unk0201e300 *p) {
    p->unk1278 = 0;
    p->keyB.func_14(0x2000, 0);
    p->keyC.func_14(0x1e000, 0);
    p->keyD.func_14(0x1e000, 0);
    p->keyE.func_14(0x1c000, 0x20000);
    p->keyF.func_14(0x5000, 0x20000);
    p->keyA.func_14(0x2000, 0x1000);
    func_02054a70(&data_020bfc80);
    p->keyB.func_30(0x20);
    p->keyD.func_30(0x20);
    p->keyE.func_30(0x20);
    p->keyF.func_30(0x20);
    p->keyC.func_30(0x20);
}

/* 97.50 % each: counter and limit registers r12 / lr swapped. */
#define LOAD(name, dst)                                  \
    void name(void *data, u32 offset, u32 size) {        \
        u32 n = size >> 1;                               \
        for (u32 i = 0; i < n; i++) {                    \
            data_020be3b0->dst[i] = ((u16 *)data)[i];    \
        }                                                \
    }

LOAD(func_020211cc, palettes1[0])
LOAD(func_0202120c, palettes1[1])
LOAD(func_0202124c, palettes1[2])
LOAD(func_0202128c, palettes1[3])
LOAD(func_020212cc, palettes1[4])
LOAD(func_0202130c, palettes1[5])
LOAD(func_0202134c, palettes2[0])
LOAD(func_0202138c, palettes2[1])
LOAD(func_020213cc, palettes2[2])
LOAD(func_0202140c, palettes2[3])
LOAD(func_0202144c, palettes2[4])
LOAD(func_0202148c, palettes2[5])

static inline int func_channel(int v) {
    if (v < 0) {
        return 0;
    }
    if (v > 0x1f) {
        return 0x1f;
    }
    return v;
}

/* 92.28 %: registers of the first loop. */
void func_020214cc(Unk0201e300 *p, int t) {
    if (p->from1 == 0 || p->to1 == 0 || p->from2 == 0 || p->to2 == 0) {
        return;
    }
    if (t > 0x1000) {
        t = 0x1000;
    }
    int b = t >> 7;
    int a = 0x20 - b;
    u16 c0;
    u16 c1;
    int g0;
    int b0;
    int r0;
    int g1;
    int b1;
    int r1;
    for (u32 i = 0; i < 0x20; i++) {
        c0 = p->from1[i];
        c1 = p->to1[i];
        g0 = c0 >> 5 & 0x1f;
        b0 = c0 & 0x1f;
        r0 = c0 >> 10 & 0x1f;
        g1 = c1 >> 5 & 0x1f;
        b1 = c1 & 0x1f;
        r1 = c1 >> 10 & 0x1f;
        int red = func_channel((r1 * b + r0 * a) >> 5);
        int green = func_channel((g1 * b + g0 * a) >> 5);
        int blue = func_channel((b1 * b + b0 * a) >> 5);
        data_020be3b4[i] = blue | (red << 10 | green << 5);
    }
    DC_FlushRange(data_020be3b4, 0x40);
    GXS_LoadBGPltt(data_020be3b4, 0xe0, 0x40);
    for (u32 i = 0; i < 0x10; i++) {
        c0 = p->from2[i];
        c1 = p->to2[i];
        g0 = c0 >> 5 & 0x1f;
        b0 = c0 & 0x1f;
        r0 = c0 >> 10 & 0x1f;
        g1 = c1 >> 5 & 0x1f;
        b1 = c1 & 0x1f;
        r1 = c1 >> 10 & 0x1f;
        int red = func_channel((r1 * b + r0 * a) >> 5);
        int green = func_channel((g1 * b + g0 * a) >> 5);
        int blue = func_channel((b1 * b + b0 * a) >> 5);
        data_020be3f4[i] = blue | (red << 10 | green << 5);
    }
    DC_FlushRange(data_020be3f4, 0x20);
    GXS_LoadOBJPltt(data_020be3f4, 0xa0, 0x20);
}

void func_020216e0(Unk0201e300 *p, int from, int to) {
    p->from1 = p->palettes1[from];
    p->to1 = p->palettes1[to];
    p->from2 = p->palettes2[from];
    p->to2 = p->palettes2[to];
}

void func_0202171c(Unk0201e300 *p) {
    Unk02098e70 start[2] = {Unk02098e70(-0xb4000, -0x80000), Unk02098e70(0xc8000, -0x50000)};
    Unk020a7c90 *s;
    if (func_02059cf8(func_0206bce0()->unk214)) {
        for (u32 i = 0; i < 2; i++) {
            s = p->birds[i];
            if (func_020a7d1c(s) == 0) {
                func_020a7cf0(s, true);
                func_020a7c90(s, start[i].x);
                func_020a7cac(s, start[i].y);
            }
            int y = func_020a7cc0(s);
            if (y < start[i].y + 0x80000) {
                if (start[i].x < 0) {
                    func_020a7c90(s, func_020a7ca4(s) + 0x1000);
                } else {
                    func_020a7c90(s, func_020a7ca4(s) - 0x1000);
                }
                func_020a7cac(s, y + 0x1000);
            }
        }
    } else {
        for (u32 i = 0; i < 2; i++) {
            s = p->birds[i];
            if (func_020a7d1c(s) != 0) {
                int x = func_020a7ca4(s) + 0x1000;
                func_020a7c90(s, x);
                if (x >= 0x100000) {
                    func_020a7cf0(s, false);
                }
            }
        }
    }
}

/*
 * 94.74 %: the original branches around `minute += 0x3c` and loads 0x22 after it,
 * ours is a conditional sequence (unsigned types, locals, an empty else, a stack
 * struct and inline helpers tried). The pragma keeps the two func_0202071c calls
 * of the original.
 */
#pragma dont_inline on
void func_02021888(Unk0201e300 *p) {
    int hour = (func_0202071c(&data_020d6298).value & 0x7c0) >> 6;
    int minute = func_0202071c(&data_020d6298).value & 0x3f;

    Unk0201e300Cloud *cloud;
    for (u32 i = 0; i < 3; i++) {
        cloud = p->active[i];
        if (cloud == 0) {
            bool used;
            do {
                used = false;
                cloud = &p->clouds[func_020a20bc(data_020d62a4, 0, 10)];
                for (u32 j = 0; j < 3; j++) {
                    if (cloud == p->active[j]) {
                        used = true;
                    }
                }
            } while (used);
            func_020a7c90(cloud->sprite, cloud->x);
            cloud->speed = func_020a20bc(data_020d62a4, 0xcd, 0x266);
            func_020a7cf0(cloud->sprite, true);
            p->active[i] = cloud;
        }
        func_020a7c90(cloud->sprite, cloud->speed + func_020a7ca4(cloud->sprite));
        if (func_020a7ca4(cloud->sprite) > 0x100000) {
            func_020a7cf0(cloud->sprite, false);
            p->active[i] = 0;
        }
    }

    func_0202171c(p);

    Unk0206bcf0 *state = func_0206bce0();
    if ((state->unk22c & 0x400) != 0 || state->unk21c != 0) {
        DC_FlushRange(data_020be3b4, 0x40);
        GXS_LoadBGPltt(data_020be3b4, 0xe0, 0x40);
        DC_FlushRange(data_020be3f4, 0x20);
        GXS_LoadOBJPltt(data_020be3f4, 0xa0, 0x20);
        return;
    }

    switch (p->period) {
    case -1:
        if (((data_020d6298.time & 0x7c0) >> 6) >= 6) {
            p->period = 0;
            func_020a6980(p->sky, 0xb7eae51);
            func_020216e0(p, 0, 1);
        } else {
            p->period = 3;
            func_020a6980(p->sky, 0x1bf6c080);
            func_020216e0(p, 3, 4);
        }
        break;
    case 0:
        if (hour >= 8) {
            p->period = 1;
            func_020214cc(p, 0x1000);
        } else {
            if (hour == 7) {
                minute += 0x3c;
            }
            func_020214cc(p, minute * 0x22);
        }
        break;
    case 1:
        if (hour >= 0x16) {
            p->period = 2;
            func_020216e0(p, 1, 2);
        }
        break;
    case 2:
        if (hour < 0x18) {
            if (hour == 0x17) {
                minute += 0x3c;
            }
            func_020214cc(p, minute * 0x22);
        }
        break;
    case 3:
        if (hour >= 2) {
            p->period = 4;
            func_020214cc(p, 0x1000);
        } else {
            if (hour == 1) {
                minute += 0x3c;
            }
            func_020214cc(p, minute * 0x22);
        }
        break;
    case 4:
        if (hour >= 4) {
            p->period = 5;
            func_020216e0(p, 4, 5);
        }
        break;
    case 5:
        if (hour < 6) {
            if (hour == 5) {
                minute += 0x3c;
            }
            func_020214cc(p, minute * 0x22);
        }
        break;
    }
}
#pragma dont_inline reset
