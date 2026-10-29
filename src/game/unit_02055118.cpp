/*
 * Unit 0x02055118-0x02055EF8: the survival guide animation Unk02055118 of the
 * player (one object, at 0x14C of the class of unit_0206BCE0.cpp). A state
 * machine of 69 states plays an entity animation on the player's sim and an
 * object animation on the guide object ("build/data/objects/tools/
 * tool15_survival_guide"), chosen from a table of 67 name pairs; most names
 * are "tools/tool15_survival_guide/entity_survival_guide_..." and
 * ".../object_survival_guide_...", the last two "decorative_objects/
 * d32_telescope/entity_sim_ready" and "..._getoff". When an animation ends,
 * func_020553dc picks the next state (at random for some).
 *
 * Bounds: hypothesis. The constructor 0x02055118 follows the array helpers of
 * the code before (0x020550D8-0x02055104); the lot unit (0x02055EF8) follows.
 * `.bss` 0x020C3B20-0x020C3B30 holds the guards and values of the two
 * function-local statics of func_02055198 and func_02055220, just before the
 * `.bss` of the lot unit. `.data` 0x020BA2DC-0x020BB9B4 is the empty string,
 * the guide object name, the table and its strings ("cInventoryServer::
 * Release()" before it belongs to the code before). Real file name unknown.
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses.
 *
 * Not complete: func_02055220 is not at 100 % (comment above it).
 */

#include "game/unk_sim.h"

typedef signed char s8;
typedef unsigned char u8;

/* A visible object (0x38 bytes, unit_02060ADC.cpp): only the fields used here. */
class Unk02060d78 {
public:
    u32 flags;
    u8 unk4[0x2c];
    int unk30;
};

/* The visible objects (data_020c40cc, unit_02060ADC.cpp). */
class Unk020c40cc;

/* A scene object (unit_0205D8D8.cpp): only its visible object. */
struct Unk02061d08Item {
    u8 unk0[0x44];
    Unk02060d78 *visible;
};

/* The definition of a scene object (unit_0205F16C.cpp). */
struct Unk0205cf00;

/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4;

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0;

/* The definition given to func_020615f0 (0x34 bytes). */
struct Unk020615f0Def {
    int model;
    u32 xform;
    u32 anim;
    u8 unkc[0x14];
    u32 texanim;
    int unk24;
    int unk28;
    int unk2c;
    u32 flags;
};

/* The player (data_020c43a8, unit_02064984.cpp): only the fields used here. */
class Unk020c43a8 : public Unk020680d4Base {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);

    Unk020680d4Cell home;
    Unk020680d4 *sim;
    u8 unk10[0x28];
    u8 unk38;
    u8 unk39[0x39b];
    int unk3d4;
};

/* The survival guide animation of the player (0x18 bytes). */
class Unk02055118 {
public:
    Unk02055118();
    ~Unk02055118();

    int state;
    Unk02060d78 *obj;
    u8 shown;
    u8 unk9;
    u8 unka;
    int unkc;
    int unk10;
    s8 count;
};

extern "C" {
void func_0205515c(Unk02055118 *p, Unk02061d08Item *item);
void func_02055198(Unk02055118 *p);
void func_02055220(Unk02055118 *p, int state, int count);
bool func_02055334(Unk02055118 *p, Unk02063d84 *anim);
int func_02055394(Unk02055118 *p, int lo, int hi);
int func_020553c0(Unk02055118 *p);
void func_020553dc(Unk02055118 *p);
void func_020559cc(Unk02055118 *p);
void func_02055bc0(Unk02055118 *p);
void func_02055c3c(Unk02055118 *p);
Unk02063d84 *func_02055c60(Unk02055118 *p, int state, int part, bool loop);
bool func_02055cb8(Unk02055118 *p);
void func_02055d78(Unk02055118 *p);
void func_02055dd8(Unk02055118 *p);

void *func_02054dc4(void *p, Unk0205cf00 *def, int a);
void func_0205d35c(Unk0205cf00 *def);
void func_0205d37c(Unk0205cf00 *def);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, u32 key);
Unk02060d78 *func_02060c90(Unk020c40cc *s);
void func_02060fc8(Unk02060d78 *e);
void func_020610a0(Unk02060d78 *e);
void func_020610d8(Unk02060d78 *e, Unk020680d4Vec pos);
void func_0206110c(Unk02060d78 *e, Unk020680d4Vec rot);
void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames);
void func_020615f0(Unk02060d78 *e, Unk020615f0Def *def);
Unk020897c0 *func_02063d84(Unk02063d84 *a);
Unk02063d84 *func_02063e2c(u32 key, int mode);
bool func_02066748(Unk020c43a8 *p, int anim, bool loop, int time, bool hide, int angle);
void func_020667f8(Unk020c43a8 *p, int time);
void func_02068688(Unk020680d4 *sim, bool on);
void func_02069124(Unk020680d4 *sim, Unk02063d84 *anim, int time, int hide);
u32 func_0209a32c(const char *str, u32 last, u32 end);
u32 func_0209a3c4(u32 hash, const char *str);
u32 func_020a1f84(Unk020a20f0 *random);
Unk020615f0Def func_0205cd6c(Unk0205cf00 *def, int key);
}

extern Unk020c43a8 data_020c43a8;
extern Unk020c40cc data_020c40cc;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020a20f0 data_020d62a4;
extern u8 data_020bfc9c[];

/* The guide object, then the entity and object animations of each state. */
const char *data_020ba2e0 = "build/data/objects/tools/tool15_survival_guide";

const char *data_020ba2e4[67][2] = {
    {"", ""},
    {"tools/tool15_survival_guide/entity_survival_guide_surv01_takeout", "tools/tool15_survival_guide/object_survival_guide_surv01_takeout"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv03_readguide", "tools/tool15_survival_guide/object_survival_guide_surv03_readguide"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv02_turnpage", "tools/tool15_survival_guide/object_survival_guide_surv02_turnpage"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv04_turnbook", "tools/tool15_survival_guide/object_survival_guide_surv04_turnbook"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv06_oneleg", "tools/tool15_survival_guide/object_survival_guide_surv06_oneleg"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv05_scratchdrop", "tools/tool15_survival_guide/object_survival_guide_surv05_scratchdrop"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv07_closebook", "tools/tool15_survival_guide/object_survival_guide_surv07_closebook"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv08_eat", "tools/tool15_survival_guide/object_survival_guide_surv08_eat"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv09_eat2", "tools/tool15_survival_guide/object_survival_guide_surv09_eat2"},
    {"tools/tool15_survival_guide/entity_survival_guide_surv10_eat3", "tools/tool15_survival_guide/object_survival_guide_surv10_eat3"},
    {"items/it16_object_crafting/entity_crafting_station_crobj01", "items/it16_object_crafting/object_crafting_station_crobj01"},
    {"items/it16_object_crafting/entity_crafting_station_crobj02", "items/it16_object_crafting/object_crafting_station_crobj02"},
    {"items/it16_object_crafting/entity_crafting_station_crobj03", "items/it16_object_crafting/object_crafting_station_crobj03"},
    {"items/it16_object_crafting/entity_crafting_station_crobj04", "items/it16_object_crafting/object_crafting_station_crobj04"},
    {"items/it16_object_crafting/entity_crafting_station_crobj05", "items/it16_object_crafting/object_crafting_station_crobj05"},
    {"items/it16_object_crafting/entity_crafting_station_crobj06", "items/it16_object_crafting/object_crafting_station_crobj06"},
    {"items/it16_object_crafting/entity_crafting_station_crobj07", "items/it16_object_crafting/object_crafting_station_crobj07"},
    {"items/it16_object_crafting/entity_crafting_station_crobj08", "items/it16_object_crafting/object_crafting_station_crobj08"},
    {"items/it15_food_crafting/entity_move_to_kneeldown", "items/it15_food_crafting/object_move_to_kneeldown"},
    {"items/it15_food_crafting/entity_busy_cook", "items/it15_food_crafting/object_busy_cook"},
    {"items/it15_food_crafting/entity_busy_cook2", "items/it15_food_crafting/object_busy_cook2"},
    {"items/it15_food_crafting/entity_get_food1", "items/it15_food_crafting/object_get_food1"},
    {"items/it15_food_crafting/entity_get_food2", "items/it15_food_crafting/object_get_food2"},
    {"items/it15_food_crafting/entity_knife_out", "items/it15_food_crafting/object_knife_out"},
    {"items/it15_food_crafting/entity_chopping", "items/it15_food_crafting/object_chopping"},
    {"items/it15_food_crafting/entity_knife_in", "items/it15_food_crafting/object_knife_in"},
    {"items/it15_food_crafting/entity_food_done", "items/it15_food_crafting/object_food_done"},
    {"items/it15_food_crafting/entity_move_to_basepose", "items/it15_food_crafting/object_move_to_basepose"},
    {"items/it15_food_crafting/entity_cancel_food", "items/it15_food_crafting/object_cancel_food"},
    {"items/it15_food_crafting/entity_hammer_out", "items/it15_food_crafting/object_hammer_out"},
    {"items/it15_food_crafting/entity_hammer_in", "items/it15_food_crafting/object_hammer_in"},
    {"items/it15_food_crafting/entity_hammering", "items/it15_food_crafting/object_hammering"},
    {"fire/f3_firepit_slab/fire_full/entity_crslab01_kneel_down", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab03_poke", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab04_burn_hand", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab05_waft", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab02_takeout_item", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab06_food_finished", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab07_gets_up", ""},
    {"fire/f3_firepit_slab/fire_full/entity_crslab08_cancel_food", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot01_kneeldown", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot03_busy", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot04_burn_hand", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot05_stir", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot06_taste", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot02_takeout_item", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot07_food_done", ""},
    {"fire/f4_firepit_pot/fire_full/entity_crpot08_shrug", ""},
    {"items/it18_clothing_station/crclothes01_step_up", ""},
    {"items/it18_clothing_station/crclothes02_busyidle1", ""},
    {"items/it18_clothing_station/crclothes03_busyidle2", ""},
    {"items/it18_clothing_station/crclothes04_hurthand", ""},
    {"items/it18_clothing_station/crclothes05_finish", ""},
    {"items/it18_clothing_station/crclothes06_step_down", ""},
    {"items/it17_dye_station/dye_station_crdye01", ""},
    {"items/it17_dye_station/dye_station_crdye02", ""},
    {"items/it17_dye_station/dye_station_crdye04", ""},
    {"items/it17_dye_station/dye_station_crdye03", ""},
    {"items/it17_dye_station/dye_station_crdye05", ""},
    {"items/it17_dye_station/dye_station_crdye06", ""},
    {"items/it24_easel/stepup", ""},
    {"items/it24_easel/feat101-paintidle", ""},
    {"items/it24_easel/feat102-painting", ""},
    {"items/it24_easel/stepdown", ""},
    {"decorative_objects/d32_telescope/entity_sim_ready", ""},
    {"decorative_objects/d32_telescope/entity_sim_getoff", ""},
};

static inline Unk020c43a8 *func_player() {
    return &data_020c43a8;
}

static inline Unk020680d4Vec &func_vec(Unk02098ff0 &v) {
    return (Unk020680d4Vec &)v;
}

static inline bool func_owned(u32 key) {
    if (func_02054dc4(data_020bfc9c, func_0205f6f8(&data_020c3fc4, key), 0)) {
        return true;
    }
    return false;
}

Unk02055118::Unk02055118() : state(0), obj(0), shown(0), unk9(1), unka(0), unkc(0), unk10(-1), count(-1) {}

Unk02055118::~Unk02055118() {}

void func_0205515c(Unk02055118 *p, Unk02061d08Item *item) {
    if (item != 0) {
        p->obj = item->visible;
        func_02055220(p, 0, -1);
    } else {
        p->state = 0x44;
        p->count = 0;
    }
}

void func_02055198(Unk02055118 *p) {
    static Unk020c43a8 &data_020c3b24 = *func_player();
    if (data_020c3b24.unk38) {
        data_020c3b24.unk38 = 0;
        func_020667f8(&data_020c3b24, 10);
    }
    func_02055d78(p);
    p->unka = 0;
    func_02068688(data_020c43a8.sim, true);
    func_02055220(p, 0, -1);
}

/* 95.75 %: the original loads 0 for the part argument into r2 before the
 * guard test, keeps the static's value in r1 and reloads it for the sim;
 * ours keeps it in r2. Tried: a pointer static (wrong guard order), a class
 * static holding the pointer, a static in an inline accessor (one shared
 * static), a part local, a loop flag local, the anim and sim locals declared
 * first, a second anim local, the sim read inside the test. */
void func_02055220(Unk02055118 *p, int state, int count) {
    p->state = state;
    p->count = count;
    if (state == 0) {
        return;
    }
    static Unk020c43a8 &data_020c3b2c = *func_player();
    if (data_020c3b2c.unk38 == 0) {
        data_020c3b2c.unk38 = 1;
    }
    Unk020680d4 *sim = data_020c3b2c.sim;
    Unk02063d84 *anim = func_02055c60(p, state, 0, count == -1);
    if (anim != 0) {
        sim->speed = 0x1000;
        func_02069124(sim, anim, 10, p->unka);
    }
    if (p->obj == 0 || p->unk9 == 0) {
        return;
    }
    anim = func_02055c60(p, state, 1, count == -1);
    if (anim != 0) {
        p->obj->unk30 = 0x1000;
        func_02061298(p->obj, anim, false, 16);
    }
    func_02055bc0(p);
}

bool func_02055334(Unk02055118 *p, Unk02063d84 *anim) {
    if (anim != 0 && (anim->anim->func_01ff8a8c() || anim->anim->func_01ff8aa0())) {
        if (p->count == 0) {
            return true;
        }
        func_02055220(p, p->state, p->count - 1);
        return false;
    }
    return false;
}

int func_02055394(Unk02055118 *p, int lo, int hi) {
    return lo + func_020a1f84(&data_020d62a4) % (u32)(hi - lo + 1);
}

int func_020553c0(Unk02055118 *p) {
    return (func_020a1f84(&data_020d62a4) & 7) + 2;
}

void func_020553dc(Unk02055118 *p) {
    Unk020c43a8 *player = &data_020c43a8;
    Unk020a20f0 *random = &data_020d62a4;
    Unk020680d4 *sim = player->sim;
    if (sim == 0 || p->state == 0) {
        return;
    }
    Unk02063d84 *anim = sim->anim;
    bool done = func_02055334(p, anim);
    int s;
    switch (p->state) {
    case 68:
        if (!done) {
            return;
        }
        if (player->unk3d4 != 0) {
            return;
        }
        player->unk38 = 1;
        if (p->obj != 0 || p->shown != 0) {
            func_02055d78(p);
        }
        p->shown = func_02055cb8(p);
        p->unk9 = p->shown;
        func_02055220(p, 1, 0);
        return;
    case 1:
        if (!done) {
            return;
        }
        func_02055220(p, 2, func_020553c0(p));
        return;
    case 2:
        if (!done) {
            return;
        }
        s = func_02055394(p, 4, 6);
        func_02063d84(anim)->func_01ff8a80();
        func_02055220(p, s, 0);
        return;
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
        if (!done) {
            return;
        }
        func_02055220(p, 2, func_020553c0(p));
        return;
    case 7:
        if (!done) {
            return;
        }
        func_02055198(p);
        return;
    case 11:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        if (!done) {
            return;
        }
        func_02055220(p, 12, -1);
        return;
    case 24:
        if (!done) {
            return;
        }
        func_02055220(p, 25, func_020a1f84(random) % 3);
        return;
    case 25:
        if (!done) {
            return;
        }
        func_02055220(p, 26, 0);
        return;
    case 30:
        if (!done) {
            return;
        }
        func_02055220(p, 32, func_020a1f84(random) & 1);
        return;
    case 32:
        if (!done) {
            return;
        }
        func_02055220(p, 31, 0);
        return;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 26:
    case 27:
    case 31: {
        if (!done) {
            return;
        }
        bool a = func_owned(0x0cc8fc7d);
        bool b = func_owned(0xd48c3ad3);
        u32 r = func_020a1f84(random) % 3;
        if (r == 0 && a) {
            func_02055220(p, 24, 0);
            return;
        }
        if (r == 1 && b) {
            func_02055220(p, 30, 0);
            return;
        }
        u32 flip = func_020a1f84(random);
        func_02055220(p, func_02055394(p, 20, 23), flip & 1);
        return;
    }
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
        if (!done) {
            return;
        }
        s = func_02055394(p, 0x22, 0x24);
        if (s == 0x22) {
            func_02055220(p, s, func_020553c0(p));
        } else {
            func_02055220(p, s, 0);
        }
        return;
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
        if (!done) {
            return;
        }
        s = func_02055394(p, 0x2a, 0x2d);
        if (s == 0x2a) {
            func_02055220(p, s, func_020553c0(p));
        } else {
            func_02055220(p, s, 0);
        }
        return;
    case 49:
    case 50:
    case 51:
    case 52:
        if (!done) {
            return;
        }
        s = func_02055394(p, 0x32, 0x34);
        if (s == 0x32 || s == 0x33) {
            func_02055220(p, s, func_020553c0(p));
        } else {
            func_02055220(p, s, 0);
        }
        return;
    case 55:
    case 56:
    case 57:
        if (!done) {
            return;
        }
        s = func_02055394(p, 0x38, 0x3a);
        if (s == 0x3a) {
            func_02055220(p, s, 0);
        } else {
            func_02055220(p, s, func_020553c0(p));
        }
        return;
    case 58:
        if (!done) {
            return;
        }
        s = func_02055394(p, 0x38, 0x39);
        func_02055220(p, s, func_020553c0(p));
        return;
    case 18:
    case 28:
    case 29:
    case 39:
    case 40:
    case 47:
    case 48:
    case 53:
    case 54:
    case 59:
    case 60:
    case 64:
    case 66:
        if (!done) {
            return;
        }
        func_02055198(p);
        return;
    case 61:
    case 62:
        if (!done) {
            return;
        }
        func_02055220(p, 0x3f, func_020553c0(p));
        return;
    case 63:
        if (!done) {
            return;
        }
        func_02055220(p, 0x3e, func_020553c0(p));
        return;
    }
}

/* Whether bit `i` (at most `n`) of `mask` is set: the state sets of func_020559cc. */
static inline bool func_bit(u32 i, u32 n, u32 mask) {
    return i <= n && (mask & (1 << i)) != 0;
}

static inline bool func_in(int s, int base, u32 n, u32 mask) {
    bool in = func_bit(s - base, n, mask);
    return in;
}

static inline bool func_start_a(int s) {
    return func_in(s, 1, 0x12, 0x40401) || func_in(s, 0x21, 0x1c, 0x10410101);
}

static inline bool func_start(int s) {
    return func_start_a(s) || func_in(s, 0x42, 2, 5);
}

static inline bool func_end(int s) {
    return func_in(s, 7, 0x16, 0x600801) || func_in(s, 0x27, 0x1b, 0xa30c303);
}

void func_020559cc(Unk02055118 *p) {
    int s = p->state;
    if (func_start(s)) {
        if (p->shown && p->obj != 0) {
            func_020610a0(p->obj);
        }
        func_02055198(p);
        return;
    }
    if (func_end(s)) {
        return;
    }
    if (s >= 0x41) {
        func_02055220(p, 0x42, 0);
    } else if (s >= 0x3d) {
        func_02055220(p, 0x40, 0);
    } else if (s >= 0x37) {
        func_02055220(p, 0x3c, 0);
    } else if (s >= 0x31) {
        func_02055220(p, 0x36, 0);
    } else if (s >= 0x29) {
        func_02055220(p, 0x30, 0);
    } else if (s >= 0x21) {
        func_02055220(p, 0x28, 0);
    } else if (s >= 0x13) {
        func_02055220(p, 0x1d, 0);
    } else if (s >= 0xb) {
        func_02055220(p, 0x12, 0);
    } else {
        func_02055220(p, 7, 0);
    }
}

void func_02055bc0(Unk02055118 *p) {
    Unk020680d4 *sim;
    if (p->shown == 0 || (sim = data_020c43a8.sim) == 0) {
        return;
    }
    Unk02098ff0 pos = sim->func_04();
    func_020610d8(p->obj, func_vec(pos));
    Unk02098ff0 rot = sim->func_0c();
    func_0206110c(p->obj, func_vec(rot));
}

void func_02055c3c(Unk02055118 *p) {
    func_player()->func_18(Unk020680d4Dir(2));
}

Unk02063d84 *func_02055c60(Unk02055118 *p, int state, int part, bool loop) {
    if (state >= 0x43) {
        state = 2;
    }
    const char *name = data_020ba2e4[state][part];
    if (name != "") {
        u32 key = func_0209a3c4(0xb73757c2, name);
        return func_02063e2c(key, loop ? 1 : 2);
    }
    return 0;
}

bool func_02055cb8(Unk02055118 *p) {
    if (p->obj == 0) {
        func_02055c3c(p);
        p->obj = func_02060c90(&data_020c40cc);
        if (p->obj != 0) {
            if (p->obj->flags & 1) {
                func_02060fc8(p->obj);
            }
            Unk0205cf00 *def = func_0205f6f8(&data_020c3fc4, func_0209a32c(data_020ba2e0, 0, 0));
            func_0205d35c(def);
            const Unk020615f0Def &d = func_0205cd6c(def, 0);
            func_020615f0(p->obj, (Unk020615f0Def *)&d);
            func_02055bc0(p);
            p->obj->flags |= 1;
        }
    }
    return p->obj != 0;
}

void func_02055d78(Unk02055118 *p) {
    if (p->shown && p->obj != 0) {
        func_02060fc8(p->obj);
        func_0205d37c(func_0205f6f8(&data_020c3fc4, func_0209a32c(data_020ba2e0, 0, 0)));
    }
    p->obj = 0;
    p->shown = 0;
}

void func_02055dd8(Unk02055118 *p) {
    u32 r = func_020a1f84(&data_020d62a4) % 3;
    if (p->shown) {
        switch (r) {
        case 1:
            func_02055220(p, 9, 0);
            return;
        case 2:
            func_02055220(p, 10, 0);
            return;
        default:
            func_02055220(p, 8, 0);
            return;
        }
    }
    switch (r) {
    case 1:
        func_02066748(&data_020c43a8, 0x48, false, 10, false, 0);
        return;
    case 2:
        func_02066748(&data_020c43a8, 0x49, false, 10, false, 0);
        return;
    default:
        func_02066748(&data_020c43a8, 0x47, false, 10, false, 0);
        return;
    }
}
