/*
 * Unit 0x0205AF94-0x0205C700: the script command table. The static
 * initializer (0x020AD318) builds the action context data_020c3cc8 and fills
 * a table of 81 commands, each one the hash of its name and the function that
 * runs it on the parameter node of a script step; func_0205afc8 finds a
 * command by hash and runs it. The commands defined here read and change the
 * inventory and the collection, queue script events, create scene objects,
 * test the lot, the time of day, the sim abilities and the music, save the
 * game and set registers; the others are in unit_02061D08.cpp and in the code
 * before 0x02003000.
 *
 * Bounds: hypothesis. The constructor of the context (0x0205AF94) is the
 * first function and its destructor (0x0205C6FC) the last one; the object
 * definition record (unit_0205C700.cpp) follows. `.data` holds the command
 * names in table order, `.bss` the registration node of the context, the
 * context and the table. Real file name unknown.
 *
 * Not complete: func_0205b7e0 and func_0205c3f4 are not at 100 % (comments
 * above them), and the last name ("SimUseBush") lacks the padding byte that
 * ends the original `.data` (99.97 %; the bytes of all 81 names match).
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses. func_0205bc88 and func_0205c548 return
 * an int (no 16-bit truncation in the original), so the table casts them.
 */

#include "game/unk_script.h"
#include "game/unk_queue.h"
#include "game/unk_sortedset.h"

typedef signed char s8;

struct Unk02058788;
struct Unk020a4c4c;
class Unk02060d78;

/* The first half of a map cell (constructor 0x020593E4). */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    bool operator==(Unk020593e4 o) const {
        return unk3 == o.unk3 && unk2 == o.unk2 && unk0 == o.unk0;
    }

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

struct Unk020680d4Xy {
    Unk020680d4Xy() {}

    bool operator==(Unk020680d4Xy o) const {
        return x == o.x && y == o.y;
    }

    s16 x;
    s16 y;
};

/* A map cell: its tile coordinates are -1 when it is not set. */
struct Unk020680d4Cell {
    Unk020680d4Cell() {
        xy.x = -1;
        xy.y = -1;
    }

    bool operator==(Unk020680d4Cell o) const {
        return pos == o.pos && xy == o.xy;
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

/* A direction (0 to 3; 4 when not set). */
struct Unk020680d4Dir {
    Unk020680d4Dir() {}

    int v;
};

struct Unk0205d8d8Vec {
    int x;
    int y;
    int z;
};

/* The definition of a scene object (unit_0205F16C.cpp). */
struct Unk0205cf00 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    int unk8;
    int key;
    Unk020956f8 *script;
    u32 flags;
    int group;
};

/* The action queue of an object. */
struct Unk0205da00Queue {
    void *owner;
    u32 flags;
    int unk8;
    void *head;
};

/* The interface shared with the sim. */
class Unk020680d4Base {
public:
    virtual void func_00(Unk0205d8d8Vec pos) = 0;
    virtual Unk0205d8d8Vec func_04() = 0;
    virtual void func_08(Unk0205d8d8Vec rot) = 0;
    virtual Unk0205d8d8Vec func_0c() = 0;
    virtual void func_10(Unk020680d4Cell cell) = 0;
    virtual Unk020680d4Cell func_14() = 0;
    virtual void func_18(Unk020680d4Dir dir) = 0;
    virtual Unk020680d4Dir func_1c() = 0;
};

/* A scene object (0x4C bytes, unit_0205D8D8.cpp). */
class Unk02061d08Item : public Unk020680d4Base {
public:
    static void *operator new(unsigned long size);
    static void operator delete(void *p);

    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);

    virtual void func_00(Unk0205d8d8Vec pos);
    virtual Unk0205d8d8Vec func_04();
    virtual void func_08(Unk0205d8d8Vec rot);
    virtual Unk0205d8d8Vec func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();

    Unk0205da00Queue queue;
    u32 flags;
    Unk020680d4Cell cell;
    Unk020680d4Dir dir;
    int reg;
    Unk0205cf00 *def;
    u32 id;
    s16 vars[4];
    u32 key;
    Unk02061d08Item *prev;
    Unk02061d08Item *next;
    Unk02060d78 *visible;
    Unk02061d08Item *found;
};

/* The owner of a parameter node: a script instance. */
class Unk02099c0cOwner {
public:
    virtual bool func_00(u32 type);
    virtual void func_04();
    virtual void func_08(int index, s16 value);

    Unk020956f8 *script;
    int unk8;
    Unk02061d08Item *item;
};

/* The parameters of a script step (unit_02099C0C.cpp). */
class Unk02099c0c {
public:
    bool func_02099c0c(int *value, int key);
    int func_02099c58(int key);

    Unk02099c0cOwner *owner;
    u16 next;
    u16 unk6;
};

/* The action context (data_020c3cc8). */
class Unk020c3cc8 {
public:
    Unk020c3cc8();
    ~Unk020c3cc8();

    int unk0;
    Unk02061d08Item *actor;
    int unk8;
    Unk02061d08Item *target;
    struct Unk020c43a8 *player;
    int unk14;
    u8 result;
    int regs[4];
};

extern "C" u32 func_0209a32c(const u32 *str, u32 last, u32 end);

typedef u16 (*Unk0205af98Func)(Unk02099c0c *node);

/* A command: the hash of its name and its function. */
struct Unk0205af98Entry {
    Unk0205af98Entry(const char *name, Unk0205af98Func func) : key(func_0209a32c((const u32 *)name, 0, 0)), func(func) {}

    u32 key;
    Unk0205af98Func func;
};

/* The player (data_020c43a8). */
struct Unk020c43a8 {
    u8 unk0[0x1de];
    u16 level;
    u8 unk1e0[0x1e8];
    u8 list[0xc];
};

/* The search lists of scene objects (constructor 0x0205F098). */
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

/* A count of objects of the inventory (constructor 0x020547F8). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    void *head;
    int count;
};

struct Unk02054dc4 {
    int unk0;
    int count;
};

/* The template checks of func_0205367c (0x2C bytes). */
struct Unk0205367c {
    u8 unk0[0x2c];
};

class Unk0209a11c {
public:
    void func_0209a1c4(u32 index, bool value);
};

/* The world (data_020c3ba4). */
struct Unk020c3ba4 {
    int unk0;
    u8 unk4[0x54];
    Unk02058788 *maps[41];
    s8 map;
    u8 unkfd[0x17];
    Unk0209a11c *barriers;

    void func_setBarrier(u32 index, bool value) {
        barriers->func_0209a1c4(index, value);
    }
};

/* The main game state: only the fields used here. */
class Unk0206bcf0 {
public:
    void func_0206f6fc();

    u8 unk0[8];
    int state;
    Unk0206b8cc *queue;
    u8 unk10[0x10c];
    void *guide;
    u8 unk120[0xf0];
    void *lots;
    void *weather;
};

struct Unk020a5538;

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8Save {
    u8 unk0[0xc];
    u32 count;
    u8 unk10[8];
    u32 flags;
};

struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
    u8 unk8[0x14c];
    Unk020d60c8Save *save;
};

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

/* The time read by func_0202071c. */
struct Unk0202071c {
    Unk0202071c() {}

    u32 value;
};

struct Unk020d6298;

/* The music state (data_020bfc3c). */
struct Unk020bfc3c {
    u8 unk0[0xc];
    u8 unkc;
};

struct Unk020a2994 {
    u8 unk0[0xd0];
    int unkd0;
};

/* An action of data_020be184 on an object. */
struct Unk0205b6c4Obj {
    u8 unk0[0x18];
    void *unk18;
    u8 unk1c[4];
    int unk20;
    u8 unk24;
    u8 unk25;
};

extern Unk020c3ba4 data_020c3ba4;
extern Unk020c43a8 data_020c43a8;
extern Unk020d60c8 data_020d60c8;
extern Unk020d6298 data_020d6298;
extern Unk020a20f0 data_020d62a4;
extern Unk020bfc3c data_020bfc3c;
extern u8 data_020be184[];
extern u8 data_020c4770[];
/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4 {
    int refs;
    Unk0205cf00 *records;
    int count;
    void *archive;
};

extern Unk020c3fc4 data_020c3fc4;
extern u8 data_020c3fd4[];
extern u8 data_020bfc9c[];
extern const int data_020aefa8[];

extern "C" {

Unk0206bcf0 *func_0206bce0();
int func_0205f6a4(Unk020c3fc4 *db, int id);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
Unk02054dc4 *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_02054c1c(void *p, Unk0205cf00 *def, int a);
void func_02054cf0(void *p, Unk02054dc4 *e, int a);
void func_02054d94(void *p, Unk020547f8 *out, const int *keys, int n, int a);
int func_0205d8b0(int value, Unk0206b630 *set);
int func_0205ecc0(Unk02061d08Item *item, int key);
void func_020a20f0(Unk020a20f0 *random);
u32 func_020a1f84(Unk020a20f0 *random);
void *func_02007c98(void *p, int kind, int b);
void func_02007e48(void *list, void *o);
void func_02004848(void *o, int a, int key, int b);
int func_020591e4(void *lots, int key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
int func_0205d340(Unk0205cf00 *def, u32 key);
void func_0205dfcc(Unk02061d08Item *item);
void func_0205e3f0(Unk02061d08Item *item);
void func_0205e1b8(Unk02061d08Item *item, Unk020c43a8 *p);
void func_02059c5c(void *weather, int key);
Unk0202071c func_0202071c(Unk020d6298 *clock);
Unk02061d08Item *func_0205fae8(void *list, Unk0205cf00 *def, Unk0205f098 *out);
Unk02061d08Item *func_0205fb4c(void *list, int key, Unk0205f098 *out, int a);
void func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
bool func_02053940(Unk0205367c *t);
void func_020539b0(Unk0205367c *t);
int func_0209fa80(Unk020d60c8 *settings, int slot);
bool func_020a5538(Unk020d60c8Save *save);
void func_0207a748();
void func_02067178(Unk020c43a8 *p, int hash);
bool func_02067364(Unk020c43a8 *p, int hash);
void func_02067560(Unk020c43a8 *p, u32 n);
void func_02021090(void *guide);
void func_02053100(Unk020bfc3c *p);
void func_02052898(Unk020bfc3c *p);
void func_02052a00(Unk020bfc3c *p, int a);
Unk020a2994 *func_020a2994();
void func_020a35f0(Unk020a2994 *sound, u32 hash, int unk);
void func_020a3734(Unk020a2994 *sound, int frames);
int func_0206647c(Unk020c43a8 *p, int index);
void func_020662c8(Unk020c43a8 *p, int a, int b);

int func_0205b0d0(int a, int b);
bool func_0205c564(bool *out, int v);
Unk02061d08Item *func_0205c5e0(Unk02099c0c *node);
void func_0205aff0(Unk020c3cc8 *c, int i, int v);

u16 func_0205b098(Unk02099c0c *node);
u16 func_0205b0b4(Unk02099c0c *node);
u16 func_0205b0f8(Unk02099c0c *node);
u16 func_0205b204(Unk02099c0c *node);
u16 func_0205b29c(Unk02099c0c *node);
u16 func_0205b3e0(Unk02099c0c *node);
u16 func_0205b51c(Unk02099c0c *node);
u16 func_0205b698(Unk02099c0c *node);
u16 func_0205b6c4(Unk02099c0c *node);
u16 func_0205b7e0(Unk02099c0c *node);
u16 func_0205bb98(Unk02099c0c *node);
u16 func_0205bbe0(Unk02099c0c *node);
int func_0205bc88(Unk02099c0c *node);
u16 func_0205bcb8(Unk02099c0c *node);
u16 func_0205bf04(Unk02099c0c *node);
u16 func_0205bf6c(Unk02099c0c *node);
u16 func_0205bfb4(Unk02099c0c *node);
u16 func_0205c06c(Unk02099c0c *node);
u16 func_0205c0a4(Unk02099c0c *node);
u16 func_0205c0dc(Unk02099c0c *node);
u16 func_0205c120(Unk02099c0c *node);
u16 func_0205c1a4(Unk02099c0c *node);
u16 func_0205c230(Unk02099c0c *node);
u16 func_0205c290(Unk02099c0c *node);
u16 func_0205c2d8(Unk02099c0c *node);
u16 func_0205c330(Unk02099c0c *node);
u16 func_0205c378(Unk02099c0c *node);
u16 func_0205c3ac(Unk02099c0c *node);
u16 func_0205c3d0(Unk02099c0c *node);
u16 func_0205c3f4(Unk02099c0c *node);
u16 func_0205c4ac(Unk02099c0c *node);
u16 func_0205c50c(Unk02099c0c *node);
int func_0205c548(Unk02099c0c *node);
u16 func_0205c620(Unk02099c0c *node);
u16 func_0205c680(Unk02099c0c *node);

u16 func_02001fdc(Unk02099c0c *node);
u16 func_020020dc(Unk02099c0c *node);
u16 func_02002144(Unk02099c0c *node);
u16 func_0200228c(Unk02099c0c *node);
u16 func_020022cc(Unk02099c0c *node);
u16 func_02061d08(Unk02099c0c *node);
u16 func_02061e00(Unk02099c0c *node);
u16 func_02061e90(Unk02099c0c *node);
u16 func_02061f38(Unk02099c0c *node);
u16 func_0206207c(Unk02099c0c *node);
u16 func_02062104(Unk02099c0c *node);
u16 func_02062120(Unk02099c0c *node);
u16 func_02062138(Unk02099c0c *node);
u16 func_02062154(Unk02099c0c *node);
u16 func_02062184(Unk02099c0c *node);
u16 func_020621a0(Unk02099c0c *node);
u16 func_020621d0(Unk02099c0c *node);
u16 func_020622a4(Unk02099c0c *node);
u16 func_020623bc(Unk02099c0c *node);
u16 func_0206241c(Unk02099c0c *node);
u16 func_02062438(Unk02099c0c *node);
u16 func_020624a8(Unk02099c0c *node);
u16 func_020624c4(Unk02099c0c *node);
u16 func_02062620(Unk02099c0c *node);
u16 func_0206267c(Unk02099c0c *node);
u16 func_0206275c(Unk02099c0c *node);
u16 func_020627ac(Unk02099c0c *node);
u16 func_02062814(Unk02099c0c *node);
u16 func_02062864(Unk02099c0c *node);
u16 func_0206297c(Unk02099c0c *node);
u16 func_020629fc(Unk02099c0c *node);
u16 func_02062a48(Unk02099c0c *node);
u16 func_02062b34(Unk02099c0c *node);
u16 func_02062c58(Unk02099c0c *node);
u16 func_02062d20(Unk02099c0c *node);
u16 func_02062e54(Unk02099c0c *node);
u16 func_02062f00(Unk02099c0c *node);
u16 func_0206302c(Unk02099c0c *node);
u16 func_0206308c(Unk02099c0c *node);
u16 func_020630f8(Unk02099c0c *node);
u16 func_0206344c(Unk02099c0c *node);
u16 func_02063590(Unk02099c0c *node);
u16 func_020637f0(Unk02099c0c *node);
u16 func_02063934(Unk02099c0c *node);
u16 func_02063b60(Unk02099c0c *node);
u16 func_02063b94(Unk02099c0c *node);

}

#define CMD(name, func) Unk0205af98Entry(name, func)

Unk020c3cc8 data_020c3cc8;

Unk0205af98Entry data_020c3cf4[81] = {
    CMD("ValidateFalse", func_0205b098),
    CMD("ValidateTrue", func_0205b0b4),
    CMD("ValidateChangeLot", func_02061d08),
    CMD("PerformChangeLot", func_02061e00),
    CMD("UpgradeRequirementCheck", func_020630f8),
    CMD("UpgradeSelf", func_02063590),
    CMD("UpgradeOther", func_020637f0),
    CMD("ValidatePlayMicroGame", func_020624a8),
    CMD("PerformPlayMicroGame", func_020624c4),
    CMD("ValidatePlayInstrument", func_0206241c),
    CMD("PerformPlayInstrument", func_02062438),
    CMD("ValidateInvokePainting", func_02062138),
    CMD("PerformInvokePainting", func_02062154),
    CMD("ValidateKeyboardTest", func_02062104),
    CMD("PerformKeyboardTest", func_02062120),
    CMD("ValidateInvokeTelescope", func_02062184),
    CMD("PerformInvokeTelescope", func_020621a0),
    CMD("ValidatePickupObject", func_020622a4),
    CMD("ValidateSelectRandomClothing", func_02062f00),
    CMD("PerformSelectRandomClothing", func_0206302c),
    CMD("AffectMotive", func_02062620),
    CMD("ValidateMotive", func_0206267c),
    CMD("AdvanceTime", func_020022cc),
    CMD("Sleep", func_02062d20),
    CMD("AffectRelationship", func_0206275c),
    CMD("CheckRelationship", func_020627ac),
    CMD("ValidateCrafting", func_02062864),
    CMD("PerformCrafting", func_0206297c),
    CMD("PerformUpgradeCrafting", func_02062e54),
    CMD("CheckInventory", func_0205b0f8),
    CMD("CheckCollection", func_0205b204),
    CMD("AddToCollection", func_0205b3e0),
    CMD("AddToInventory", func_0205b29c),
    CMD("AddScriptEvent", func_0205b51c),
    CMD("RemoveScriptEvent", func_0205b698),
    CMD("SetSimStartPosition", func_020629fc),
    CMD("PlayerAnimation", func_02062a48),
    CMD("InspirationActionAdd_T", func_02062b34),
    CMD("InspirationActionAdd_H", func_02062c58),
    CMD("PerformInteractWithObject", func_0205b6c4),
    CMD("DisplayReminder", func_02061e90),
    CMD("SetRelationshipReminder", func_02062814),
    CMD("PerformPlantSeeds", func_020623bc),
    CMD("UpgradeImmediate", func_0206344c),
    CMD("PerformShakeTree", func_0206308c),
    CMD("GenerateObject", func_0205b7e0),
    CMD("DoWeatherEffect", func_0205bb98),
    CMD("ChangeDefaultState", func_0205bbe0),
    CMD("CheckLotForObjects", func_0205bcb8),
    CMD("IsDaytime", (Unk0205af98Func)func_0205bc88),
    CMD("NotifyObjects", func_020621d0),
    CMD("TemplateComponentsInInventory", func_0205bf04),
    CMD("RemoveTemplateComponents", func_0205bf6c),
    CMD("UseToolOnObject", func_02063934),
    CMD("SetLotBarrier", func_0205bfb4),
    CMD("PlayCastawayRandomIdle", func_0205c06c),
    CMD("SetCastawayStateAnimation", func_0205c0a4),
    CMD("SaveGame", func_0205c1a4),
    CMD("SetObjectRegister", func_0205c0dc),
    CMD("CheckObjectRegister", func_0205c120),
    CMD("PerformPlaceObject", func_0205c230),
    CMD("SetSimAbility", func_0205c290),
    CMD("GetSimAbility", func_0205c2d8),
    CMD("LevelUpSim", func_0205c330),
    CMD("IsSimAtLevel", func_0205c378),
    CMD("ShowSurvivalGuide", func_0205c3ac),
    CMD("CompleteGame", func_0205c3d0),
    CMD("ValidateGiveGift", func_02061f38),
    CMD("GiveGift", func_0206207c),
    CMD("RandomiseCounter", func_0205c3f4),
    CMD("PlayMusic", func_0205c4ac),
    CMD("StopMusic", func_0205c50c),
    CMD("IsMusicPlaying", (Unk0205af98Func)func_0205c548),
    CMD("Echo", func_020020dc),
    CMD("PlaySound", func_02002144),
    CMD("StopSoundEffects", func_0200228c),
    CMD("AwardMineableObject", func_02001fdc),
    CMD("SetRegister", func_0205c620),
    CMD("PerformWaterPlant", func_02063b94),
    CMD("ValidateWaterPlant", func_02063b60),
    CMD("SimUseBush", func_0205c680),
};

static inline bool func_isItemIn(Unk020c3fc4 *db, int id) {
    return func_0205f6a4(db, id) != -1;
}

static inline bool func_isItem(int id) {
    return func_0205f6a4(&data_020c3fc4, id) != -1;
}

Unk020c3cc8::Unk020c3cc8() {}

extern "C" {

Unk0205af98Entry *func_0205af98(u32 key) {
    for (u32 i = 0; i < 81; i++) {
        if (key == data_020c3cf4[i].key) {
            return &data_020c3cf4[i];
        }
    }
    return 0;
}

u16 func_0205afc8(u32 key, Unk02099c0c *node) {
    Unk0205af98Entry *e = func_0205af98(key);
    if (e == 0) {
        return 0;
    }
    return e->func(node);
}

void func_0205aff0(Unk020c3cc8 *c, int i, int v) {
    if (i < 0 || i >= 4) {
        return;
    }
    c->regs[i] = v;
}

int func_0205b00c(Unk020c3cc8 *c, int i) {
    if (i < 0 || i >= 4) {
        return 0;
    }
    return c->regs[i];
}

void func_0205b030(Unk020c3cc8 *c) {
    c->unk0 = -1;
    c->actor = 0;
    c->unk8 = 0;
    c->target = 0;
    c->player = 0;
    c->result = 0;
}

void func_0205b058(Unk020c3cc8 *c, int a, Unk02061d08Item *actor, int b) {
    c->unk0 = a;
    c->actor = actor;
    c->unk8 = b;
    c->target = 0;
    c->player = 0;
    c->result = 0;
}

void func_0205b074(Unk020c3cc8 *c, int a, Unk02061d08Item *target, Unk020c43a8 *player) {
    c->unk0 = a;
    c->actor = 0;
    c->unk8 = 0;
    c->target = target;
    c->player = player;
    c->result = 0;
}

u16 func_0205b098(Unk02099c0c *node) {
    data_020c3cc8.result = 0;
    return node->next;
}

u16 func_0205b0b4(Unk02099c0c *node) {
    data_020c3cc8.result = 1;
    return node->next;
}

int func_0205b0d0(int a, int b) {
    int r = 1;
    if (a == b) {
        r |= 4;
    } else {
        r |= 2;
    }
    if (a > b) {
        r |= 0x10;
    }
    if (a < b) {
        r |= 8;
    }
    return r;
}

u16 func_0205b0f8(Unk02099c0c *node) {
    int count;
    int r = 1;
    int id = node->func_02099c58(0x35c7a149);
    int key = node->func_02099c58(0xfdec430b);
    Unk020c3fc4 *db = &data_020c3fc4;
    if (!node->func_02099c0c(&count, 0x73eb14d3)) {
        count = 0;
    }
    if (id != 0) {
        if (func_isItemIn(db, id)) {
            Unk02054dc4 *e = func_02054dc4(data_020bfc9c, func_0205f6f8(db, id), 0);
            r = func_0205b0d0(e != 0 ? e->count : 0, count);
        }
    } else {
        Unk020547f8 list;
        func_02054d94(data_020bfc9c, &list, &key, 1, 1);
        r = func_0205b0d0(list.count, count);
    }
    return r;
}

u16 func_0205b204(Unk02099c0c *node) {
    int r = 1;
    int id = node->func_02099c58(0x35c7a149);
    if (func_isItem(id)) {
        int count;
        if (!node->func_02099c0c(&count, 0x73eb14d3)) {
            count = 0;
        }
        r = func_0205b0d0(func_0205d8b0(id, data_020d60c8.collection), count);
    }
    return r;
}

u16 func_0205b29c(Unk02099c0c *node) {
    int id = node->func_02099c58(0x35c7a149);
    int count;
    if (!node->func_02099c0c(&count, 0x73eb14d3)) {
        int key;
        if (node->func_02099c0c(&key, 0x971e15d6)) {
            count = 1;
            Unk02061d08Item *item = func_0205c5e0(node);
            if (item != 0) {
                count = func_0205ecc0(item, key);
            }
        } else {
            count = 1;
        }
    }
    Unk020c3fc4 *db = &data_020c3fc4;
    if (func_isItemIn(db, id) && count != 0) {
        Unk0205cf00 *def = func_0205f6f8(db, id);
        void *inv = data_020bfc9c;
        for (int i = 0; i < (count > 0 ? count : -count); i++) {
            if (count > 0) {
                func_02054c1c(inv, def, 0);
            } else {
                Unk02054dc4 *e = func_02054dc4(inv, def, 0);
                if (e == 0) {
                    break;
                }
                func_02054cf0(inv, e, 0);
            }
        }
    }
    return node->next;
}

u16 func_0205b3e0(Unk02099c0c *node) {
    Unk0206b630 *set = data_020d60c8.collection;
    int id = node->func_02099c58(0x35c7a149);
    int count;
    if (!node->func_02099c0c(&count, 0x73eb14d3)) {
        count = 1;
    }
    if (func_isItem(id)) {
        for (int i = 0; i < count; i++) {
            set->func_0206b630(id);
        }
    }
    return node->next;
}

bool func_0205b480(int *out, int key) {
    switch (key) {
    case 0xea979fd1:
        *out = 0;
        return true;
    case 0x63863388:
        *out = 50;
        return true;
    case 0xe2887272:
        *out = 100;
        return true;
    case 0x0476de97:
        *out = 150;
        return true;
    }
    return false;
}

u16 func_0205b51c(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return node->next;
    }
    Unk0206b998Req req;
    int delay;
    int order;
    int offset = 0;
    if (node->func_02099c0c(&offset, 0x60621b1d)) {
        Unk020a20f0 random;
        func_020a20f0(&random);
        offset = func_020a1f84(&random) % offset;
    }
    if (node->func_02099c0c(&delay, 0x7d935a5b)) {
        req.delay = delay + offset;
    } else if (node->func_02099c0c(&delay, 0x18347334)) {
        req.delay = (delay + offset) * 60;
    }
    if (node->func_02099c0c(&order, 0x4c43f955)) {
        req.order = order;
    } else if (node->func_02099c0c(&order, 0xb46145c2)) {
        if (func_0205b480(&order, order)) {
            req.order = order;
        }
    }
    req.key = node->func_02099c58(0x67f8d0e1);
    req.item = (Unk0206bcf0Item *)item;
    func_0206bce0()->queue->func_0206b998(&req);
    return node->next;
}

u16 func_0205b698(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0) {
        func_0206bce0()->queue->func_0206ba1c((Unk0206bcf0Item *)item);
    }
    return node->next;
}

u16 func_0205b6c4(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return node->next;
    }
    Unk0205b6c4Obj *o = (Unk0205b6c4Obj *)func_02007c98(data_020be184, 0xb, 2);
    if (o != 0) {
        int key;
        if (node->func_02099c0c(&key, 0x23087f3e)) {
            key = item->def->script->func_0209599c(key);
        } else {
            key = data_020c3cc8.unk0;
        }
        int a;
        bool once = node->func_02099c0c(&a, 0x445595ed);
        int b;
        if (node->func_02099c0c(&b, 0x062c9e6b)) {
            func_02004848(o, key, b, !once);
        } else {
            o->unk20 = key;
        }
        if (node->func_02099c58(0x29a80a1e) != 0) {
            o->unk25 = 0;
        }
        func_02007e48(&item->queue, o);
        func_02007e48(data_020c4770, o->unk18);
    }
    return node->next;
}

/*
 * 99.77 %: the created object and the script of its definition swap
 * registers (r4 / r6) in the copy of the four variables; the code is the same
 * otherwise.
 */
u16 func_0205b7e0(Unk02099c0c *node) {
    int id;
    int dirKey;
    int found = 0;
    int lot = 0;
    if (node->func_02099c0c(&lot, 0x9afdb420)) {
        found = func_020591e4(func_0206bce0()->lots, lot);
        if (found != 0 && func_isItem(found)) {
            Unk0205cf00 *def = func_0205f6f8(&data_020c3fc4, found);
            func_02054c1c(data_020bfc9c, def, func_0205d1b4(def, 0x09f9ae87));
            if (func_0205d340(def, 0x58ab4927) || func_0205d340(def, 0xe654e4e9)) {
                Unk02054dc4 *e = func_02054dc4(data_020bfc9c, def, 0);
                e->count = func_0205d1b4(def, 0x2b3e6dd7) + 1;
            }
        } else {
            found = 0;
        }
    } else {
        id = node->func_02099c58(0x6ab6646f);
        dirKey = node->func_02099c58(0x272910bb);
        bool copy = node->func_02099c58(0x0999564b) != 0;
        if (id == 0) {
            void *lots = func_0206bce0()->lots;
            id = func_020591e4(lots, node->func_02099c58(0xd3c1f9b1));
            Unk0205cf00 *def = func_0205f6f8(&data_020c3fc4, id);
            if (func_0205d340(def, data_020aefa8[3])) {
                id = 0x460f017f;
            } else if (func_0205d340(def, data_020aefa8[6])) {
                id = 0xf16d589d;
            }
        }
        Unk02061d08Item *src = func_0205c5e0(node);
        if (func_isItem(id) && src != 0) {
            Unk020680d4Dir dir = src->func_1c();
            if (dirKey != 0) {
                switch (dirKey) {
                case 0xd82a09e8:
                    dir.v = 0;
                    break;
                case 0xfa6fc214:
                    dir.v = 1;
                    break;
                case 0x30a71683:
                    dir.v = 2;
                    break;
                case 0x1202d214:
                    dir.v = 3;
                    break;
                }
            }
            Unk020680d4Cell cell = src->func_14();
            int x;
            if (node->func_02099c0c(&x, 0x58)) {
                cell.xy.x = x;
            }
            int y;
            if (node->func_02099c0c(&y, 0x59)) {
                cell.xy.y = y;
            }
            Unk02061d08Item *o = new Unk02061d08Item(func_0205f6f8(&data_020c3fc4, id), cell, dir);
            func_0205dfcc(o);
            if (data_020c3ba4.maps[src->func_14().pos.unk3] != 0) {
                func_0205e3f0(o);
            }
            if (copy) {
                Unk02099c78Var *var = src->def->script->func_0209585c();
                Unk020956f8 *script = o->def->script;
                s16 *vars = o->vars;
                for (int i = 0; i < 4; i++, var++) {
                    int v = func_0205ecc0(src, var->unk0);
                    int index = script->func_020958bc(var->unk0);
                    if (index >= 0) {
                        vars[index] = v;
                    }
                }
            }
        }
    }
    return func_0205b0d0(found, 0);
}

u16 func_0205bb98(Unk02099c0c *node) {
    int key;
    if (!node->func_02099c0c(&key, 0x3c1b826b)) {
        key = 0xa8e91b4e;
    }
    func_02059c5c(func_0206bce0()->weather, key);
    return node->next;
}

u16 func_0205bbe0(Unk02099c0c *node) {
    int state;
    if (node->func_02099c0c(&state, 0xcbb8fa02)) {
        int v = 0;
        bool restart = false;
        if (node->func_02099c0c(&v, 0xf76b6600)) {
            func_0205c564(&restart, v);
        }
        Unk02061d08Item *item = func_0205c5e0(node);
        if (item != 0) {
            item->key = state;
            if (restart && item->visible != 0) {
                item->flags &= ~0x1000;
                func_0205e1b8(item, 0);
            }
        }
    }
    return node->next;
}

int func_0205bc88(Unk02099c0c *node) {
    Unk0202071c t = func_0202071c(&data_020d6298);
    return (int)((t.value & 0x7c0) >> 6) >= 6 ? 5 : 3;
}

u16 func_0205bcb8(Unk02099c0c *node) {
    Unk02061d08Item *src = func_0205c5e0(node);
    if (src == 0) {
        return func_0205b0d0(0, 1);
    }
    s8 map = src->func_14().pos.unk3;
    int key = node->func_02099c58(0xfdec430b);
    if (key == 0x04dfe34d) {
        return func_0205b0d0(map == data_020c3ba4.map, 1);
    }
    int id = node->func_02099c58(0x35c7a149);
    int n;
    bool same = node->func_02099c0c(&n, 0x8854582f);
    Unk0205f098 list;
    n = 0;
    Unk02061d08Item *o;
    if (id != 0) {
        o = func_0205fae8(data_020c3fd4, func_0205f6f8(&data_020c3fc4, id), &list);
    } else {
        o = func_0205fb4c(data_020c3fd4, key, &list, map);
    }
    for (; o != 0; o = o->found) {
        if (!same || o->func_14() == src->func_14()) {
            n++;
        }
    }
    u16 r = func_0205b0d0(n, node->func_02099c58(0x73eb14d3));
    return r;
}

u16 func_0205bf04(Unk02099c0c *node) {
    Unk0205367c t;
    func_0205367c(&t, func_0205f6f8(&data_020c3fc4, node->func_02099c58(0xf7d71823)));
    if (func_02053940(&t)) {
        data_020c3cc8.result = 1;
    } else {
        data_020c3cc8.result = 0;
    }
    return node->next;
}

u16 func_0205bf6c(Unk02099c0c *node) {
    Unk0205367c t;
    func_0205367c(&t, func_0205f6f8(&data_020c3fc4, node->func_02099c58(0xf7d71823)));
    func_020539b0(&t);
    return node->next;
}

u16 func_0205bfb4(Unk02099c0c *node) {
    int index;
    if (node->func_02099c0c(&index, 0x0476de94)) {
        int v;
        if (node->func_02099c0c(&v, 0x50684949)) {
            bool on = v == 1 || v == 0x1eaf3839;
            bool off = v == 0 || v == 0x9aa00852;
            if (on || off) {
                data_020c3ba4.func_setBarrier(index, on && !off);
            }
        }
    }
    return node->next;
}

u16 func_0205c06c(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0 && (item->flags & 0x2000)) {
        item->flags |= 0x1000;
        func_0205e1b8(item, 0);
    }
    return node->next;
}

u16 func_0205c0a4(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0 && (item->flags & 0x2000)) {
        item->flags &= ~0x1000;
        func_0205e1b8(item, 0);
    }
    return node->next;
}

u16 func_0205c0dc(Unk02099c0c *node) {
    int v;
    if (node->func_02099c0c(&v, 0x35c7a149)) {
        Unk02061d08Item *item = func_0205c5e0(node);
        if (item != 0) {
            item->reg = v;
        }
    }
    return node->next;
}

u16 func_0205c120(Unk02099c0c *node) {
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item == 0) {
        return func_0205b0d0(0, 1);
    }
    int v;
    if (node->func_02099c0c(&v, 0x35c7a149)) {
        return func_0205b0d0(v, item->reg);
    }
    return func_0205b0d0(0, item->reg == 0);
}

u16 func_0205c1a4(Unk02099c0c *node) {
    Unk020d60c8Save *save = data_020d60c8.save;
    if (save->flags & 1) {
        int slot;
        if (node->func_02099c0c(&slot, 0xe3bdde94) && slot >= 0 && (u32)slot < save->count &&
            func_0209fa80(&data_020d60c8, slot)) {
            while (func_020a5538(save)) {
                func_0207a748();
            }
        }
    }
    return node->next;
}

u16 func_0205c230(Unk02099c0c *node) {
    Unk0205b6c4Obj *o = (Unk0205b6c4Obj *)func_02007c98(data_020be184, 0x13, 2);
    if (o != 0) {
        o->unk20 = data_020c3cc8.unk0;
        func_02007e48(&data_020c3cc8.target->queue, o);
        func_02007e48(data_020c3cc8.player->list, o->unk18);
    }
    return node->next;
}

u16 func_0205c290(Unk02099c0c *node) {
    int v = 0;
    if (node->func_02099c0c(&v, 0xfa453f47)) {
        func_02067178(&data_020c43a8, v);
    }
    return node->next;
}

u16 func_0205c2d8(Unk02099c0c *node) {
    int v = 0;
    return func_0205b0d0(1, node->func_02099c0c(&v, 0xfa453f47) && func_02067364(&data_020c43a8, v) ? 1 : 0);
}

u16 func_0205c330(Unk02099c0c *node) {
    int v;
    if (node->func_02099c0c(&v, 0xa06ae0e3)) {
        func_02067560(&data_020c43a8, (u16)v);
    }
    return node->next;
}

u16 func_0205c378(Unk02099c0c *node) {
    u16 level = data_020c43a8.level;
    return func_0205b0d0(level, node->func_02099c58(0xa06ae0e3));
}

u16 func_0205c3ac(Unk02099c0c *node) {
    void *guide = func_0206bce0()->guide;
    if (guide != 0) {
        func_02021090(guide);
    }
    return node->next;
}

u16 func_0205c3d0(Unk02099c0c *node) {
    Unk0206bcf0 *game = func_0206bce0();
    game->func_0206f6fc();
    game->state = 5;
    return node->next;
}

/*
 * 98.80 %: the script owner and its script swap registers (r5 / r6); the
 * code is the same otherwise.
 */
u16 func_0205c3f4(Unk02099c0c *node) {
    int key;
    Unk02099c0cOwner *owner;
    if (node->func_02099c0c(&key, 0x971e15d6) && (owner = node->owner) != 0) {
        Unk020956f8 *script = owner->script;
        int index = script->func_020958bc(key);
        if (index >= 0) {
            Unk02099c78Var *var = &script->func_0209585c()[index];
            s16 range = var->max - var->min;
            if (range > 0) {
                owner->func_08(index, var->min + (s16)(func_020a1f84(&data_020d62a4) % range));
            }
        }
    }
    return node->next;
}

u16 func_0205c4ac(Unk02099c0c *node) {
    int key;
    if (node->func_02099c0c(&key, 0xbb45e533)) {
        func_02053100(&data_020bfc3c);
        func_020a35f0(func_020a2994(), key, 0);
        func_02052898(&data_020bfc3c);
        func_02052a00(&data_020bfc3c, data_020bfc3c.unkc);
    }
    return node->next;
}

u16 func_0205c50c(Unk02099c0c *node) {
    if (func_020a2994()->unkd0 != 0) {
        func_020a3734(func_020a2994(), 0);
        func_02052a00(&data_020bfc3c, data_020bfc3c.unkc);
    }
    return node->next;
}

int func_0205c548(Unk02099c0c *node) {
    return func_020a2994()->unkd0 != 0 ? 4 : 2;
}

bool func_0205c564(bool *out, int v) {
    bool off = v == 0 || v == 0xe8b6eebf || v == 0x9aa00852;
    bool on = v == 1 || v == 0x64378dc5 || v == 0x1eaf3839;
    *out = on || !off;
    return on || off;
}

Unk02061d08Item *func_0205c5e0(Unk02099c0c *node) {
    if (node->owner != 0 && node->owner->func_00(0xdbbf2534)) {
        return node->owner->item;
    }
    return 0;
}

u16 func_0205c620(Unk02099c0c *node) {
    int i;
    if (node->func_02099c0c(&i, 0xa92d7f89)) {
        int v;
        if (node->func_02099c0c(&v, 0x67b6f7f3)) {
            func_0205aff0(&data_020c3cc8, i, v);
        }
    }
    return node->next;
}

u16 func_0205c680(Unk02099c0c *node) {
    Unk020c43a8 *p = &data_020c43a8;
    int n = 10000000 - func_0206647c(p, 5);
    n /= 1000000;
    func_020662c8(p, 3, -(n != 0 ? n * 5 : 5));
    func_020662c8(p, 5, 100);
    func_020662c8(p, 2, 15);
    return node->next;
}

}

Unk020c3cc8::~Unk020c3cc8() {}
