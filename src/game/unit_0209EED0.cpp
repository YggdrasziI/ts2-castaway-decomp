/*
 * Unit 0x0209EED0-0x020A0014: the application object Unk020d60c8 (static object data_020d60c8,
 * 0x164 bytes, with its `__sinit`): the save data of three slots written to the card, the
 * language, the volumes, the collection, the buffers of the heaps and the current game state.
 * It starts the game, runs the current state each frame and creates the next one.
 *
 * Bounds: hypothesis (the static initializer 0x020AE43C calls the constructor 0x0209EED0,
 * before it the code is NitroSystem; 0x020A0014 starts the text table). `.data` is the debug
 * format and the paths of the text files, up to the archive path of the text table; `.bss` is
 * the chain node, the object and the static of func_0209f880. Layouts come from the code; all
 * names are placeholders. Real file name unknown.
 */
typedef signed char s8;
typedef unsigned long u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef long long s64;

#include "game/unk_sortedset.h"

extern "C" {
void func_020897b4(const char *fmt, ...);
}

bool func_02097248(int key);

/* A save slot. */
struct Unk0209f8d0 {
    Unk0209f8d0() {
        unk0 = 0;
        unk4 = 0;
        unk6 = 0;
        unk7 = 0;
        unk48 = 0;
        unk8[0] = 0;
    }

    u32 unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u8 unk8[0x40];
    u8 unk48;
    int unk4c;
    int unk50;
};

/* What the card holds. */
struct Unk0209f0ac {
    Unk0209f0ac() : language(-1) {
        for (u32 i = 0; i < 3; i++) {
            recency[i] = -1;
        }
    }

    int language;
    Unk0209f8d0 records[3];
    s8 recency[3];
};

/* The save of the objects read when a slot is loaded. */
class Unk020a4c0c {
public:
    Unk020a4c0c(int size);

    void *unk0;
    int unk4;
    int count;
    int unkc;
    int flags;
};

/* The card. */
class Unk020a4f30 {
public:
    Unk020a4f30(const void *config);

    u8 unk0[0x18];
    int unk18;
    u8 unk1c[0x30];
    int unk4c;
    u8 unk50[0x10];
    int result;
    u8 unk64[0];
};

/* The game states (Unk0206fab0). */
class Unk020d60c8State {
public:
    virtual ~Unk020d60c8State();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10(bool active);

    int id;
    int next;
};

class Unk02072bec : public Unk020d60c8State {
public:
    Unk02072bec();

    int unkc;
    int unk10;
};

class Unk02072d94 : public Unk020d60c8State {
public:
    Unk02072d94();

    u8 unkc[0x17c];
};

class Unk02071d94 : public Unk020d60c8State {
public:
    Unk02071d94();

    u8 unkc[0x120];
};

class Unk02073878 : public Unk020d60c8State {
public:
    Unk02073878();

    u8 unkc[0x28];
};

class Unk0206bcf0 : public Unk020d60c8State {
public:
    Unk0206bcf0();
    void func_0206f6fc();
    void func_0206f7e4();
    void func_0206fa30();

    u8 unkc[0x224];
};

class Unk020a0014 {
public:
    Unk020a0014(const u32 *name);
    ~Unk020a0014();

    u8 unk0[0x108];
};

class Unk0208adc0 {
public:
    static void func_0208b40c(int size);
};

enum Unk0207cd78Result {
    UNK_0207CD78_DONE,
    UNK_0207CD78_BUSY
};

struct Unk0207cd78Date {
    int unk0[4];
};

struct Unk0207cd78Time {
    int unk0[3];
};

class Unk020d60c8 {
public:
    Unk020d60c8();
    ~Unk020d60c8();

    Unk020a4c0c *saves;
    Unk0206b630 *collection;
    int flags;
    int unkc;
    Unk0209f0ac save;
    Unk0207cd78Date date;
    Unk0207cd78Time time;
    u16 hours;
    u8 minutes;
    int slot;
    int music;
    int effects;
    Unk020d60c8State *state;
    u8 *heap144;
    void *heap148;
    u8 *heap14c;
    u8 *heap150;
    Unk020a4f30 *card;
    Unk020a0014 *texts;
    u8 unk15c;
    int language;
};

struct Unk020bfc3c {
    u8 enabled;
};

struct Unk020081dc {
    ~Unk020081dc();

    u8 unk0[0x28];
    int unk28;
};

struct Unk0202071c {
    Unk0202071c() {}

    u32 value;
};

struct Unk0205cf00 {
    u8 unk0[0xc];
    int unkc;
};

extern "C" {
Unk020081dc func_020081dc(void *player);
Unk0202071c func_0202071c(void *clock);
void func_02054ab4(void *p);
void func_0205292c(Unk020bfc3c *p, int volume);
Unk0205cf00 *func_0205f714(void *db, u32 type, Unk0205cf00 *def);
bool func_0205d340(Unk0205cf00 *def, u32 key);
void func_0205f328(void *p);
void func_0205f844(void *p);
void func_020602b0(void *p);
Unk0206bcf0 *func_0206bce0();
int func_02077c60(int a, int b);
void func_0207a748();
int func_0207c2f8(u8 *info);
Unk0207cd78Result func_0207cd78(Unk0207cd78Date *date, Unk0207cd78Time *time);
s64 func_0207d0d0(Unk0207cd78Date *date, Unk0207cd78Time *time);
void func_0207f680(int a, int b, int c);
void *func_020999e8(int a);
void func_02099a0c(void *p, int size, int a, int b, int c);
void func_020a18f0(void *p);
void func_020a1f20();
u32 func_020a1aa4(Unk0202071c *p);
void *func_020a2994();
void func_020a3584(void *audio, int channel, int volume);
void func_020a39a8(void *audio, int a, int b);
void func_020a4c4c(Unk020a4c0c *p);
void func_020a5194(Unk020a4f30 *card, void *data);
void func_020a51cc(Unk020a4f30 *card, void *data, int size);
int func_020a5288(Unk020a4f30 *card);
void func_020a531c(Unk020a4f30 *card, int slot, void *data, int size);
int func_020a5538(Unk020a4f30 *card);
void func_0209f05c(Unk020d60c8 *o, int language, int chosen);
int func_0209f408(Unk020d60c8 *o, int next);
void func_0209f6a4(Unk020d60c8 *o);
void func_0209f748(Unk020d60c8 *o);
void func_0209f74c(Unk020d60c8 *o, int slot);
void func_0209f810(Unk020d60c8 *o);
void func_0209f850(Unk020d60c8 *o, int volume);
void func_0209f880(Unk020d60c8 *o, int volume);
void func_0209f8e0(Unk020d60c8 *o);
extern u8 data_020ae7cc[];
extern u8 data_020b59b0[];
extern Unk020bfc3c data_020bfc3c;
extern u8 data_020bfc9c[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020c409c[];
extern u8 data_020c43a8[];
extern u8 data_020c4510[];
extern u8 data_020d6298[];
}


Unk020d60c8 data_020d60c8;

Unk020d60c8::Unk020d60c8() : saves(0), collection(0), flags(1), unkc(-1) {
    hours = 0;
    minutes = 0;
    slot = -1;
    music = 0x7f;
    effects = 0x60;
    state = 0;
    heap144 = 0;
    heap148 = 0;
    heap14c = 0;
    card = 0;
    texts = 0;
    unk15c = 0;
    language = -1;
    u8 info[0x50];
    func_0207c2f8(info);
    switch (info[0]) {
    case 2:
        func_0209f05c(this, 1, 1);
        break;
    case 3:
        func_0209f05c(this, 3, 1);
        break;
    case 4:
        func_0209f05c(this, 2, 1);
        break;
    case 5:
        func_0209f05c(this, 4, 1);
        break;
    case 1:
        func_0209f05c(this, 0, 1);
        break;
    case 0:
    default:
        func_0209f05c(this, 0, 0);
        break;
    }
}

Unk020d60c8::~Unk020d60c8() {}

extern "C" void func_0209f05c(Unk020d60c8 *o, int language, int chosen) {
    int value;
    switch (language) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        value = language;
        break;
    default:
        value = 0;
        break;
    }
    o->save.language = value;
    if (chosen) {
        o->flags |= 2;
    }
}

extern "C" int func_0209f0a4(Unk020d60c8 *o) {
    return o->save.language;
}

extern "C" void func_0209f0ac(Unk020d60c8 *o) {
    o->state = 0;
    int next = 1;
    func_0209f6a4(o);
    o->saves = new Unk020a4c0c(0x14000);
    func_020a18f0(data_020d6298);
    func_020602b0(data_020c409c);
    func_0205f328(data_020c3fc4);
    func_02054ab4(data_020bfc9c);
    o->collection = new Unk0206b630;
    func_0205f844(data_020c3fd4);
    func_020a1f20();
    o->music = 0x7f;
    o->card = new Unk020a4f30(data_020b59b0);
    if (!(o->card->unk18 & 1)) {
        next = 7;
    } else if ((o->card->unk4c & 1) && func_020a5288(o->card)) {
        Unk0209f0ac save;
        func_020a5194(o->card, &save);
        while (func_020a5538(o->card)) {
            func_0207a748();
        }
        if (o->card->result == 2) {
            o->save = save;
            func_0209f05c(o, o->save.language, 1);
        } else if (o->card->result == 3) {
            next = 7;
        }
    } else {
        func_0209f748(o);
    }
    func_0209f408(o, next);
}

extern "C" void func_0209f2e8(Unk020d60c8 *o) {
    if (o->state != 0) {
        if ((o->unk15c != 0 && func_02097248(8)) || (o->unk15c == 0 && func_02097248(9))) {
            o->flags |= 4;
            o->flags &= ~1;
            o->state->func_10(o->flags & 1);
            o->flags |= 1;
            func_020a39a8(func_020a2994(), 0x300, 3);
        } else {
            o->flags &= ~4;
            func_020a39a8(func_020a2994(), 0, 1);
        }
        o->state->func_10(o->flags & 1);
        if (o->state->next != 0) {
            func_0209f408(o, o->state->next);
        }
    }
    if (!(o->card->unk18 & 2) && func_02097248(0xc)) {
        func_0207f680(0xc, 0x8000, 0);
    }
}

extern "C" int func_0209f408(Unk020d60c8 *o, int next) {
    int id = 0;
    if (o->state != 0) {
        id = o->state->id;
        o->state->func_0c();
        delete o->state;
        o->state = 0;
    }
    if (o->save.language != o->language) {
        func_0209f8e0(o);
        o->language = o->save.language;
    }
    if (next != 6) {
        func_0209f850(o, 0x7f);
        func_0209f880(o, 0x60);
    }
    switch (next) {
    case 0:
        break;
    case 1:
        o->state = new Unk02072bec;
        o->state->func_08();
        break;
    case 2:
        o->state = new Unk02072d94;
        o->state->func_08();
        break;
    case 3:
        o->state = new Unk02071d94;
        o->state->func_08();
        break;
    case 4:
        o->state = new Unk02073878;
        o->state->func_08();
        break;
    case 5:
        o->state = new Unk02073878;
        o->state->id = 5;
        o->state->func_08();
        break;
    case 6: {
        o->state = new Unk0206bcf0;
        o->state->func_08();
        Unk0207cd78Result busy;
        busy = UNK_0207CD78_BUSY;
        while (busy == UNK_0207CD78_BUSY) {
            busy = func_0207cd78(&o->date, &o->time);
        }
        if (o->saves->count > 0) {
            ((Unk0206bcf0 *)o->state)->func_0206f7e4();
            o->hours = o->save.records[o->slot].unk4;
            o->minutes = o->save.records[o->slot].unk6;
            if (o->saves->flags & 4) {
                func_0209f408(o, 2);
            } else {
                func_020a4c4c(o->saves);
            }
        } else {
            ((Unk0206bcf0 *)o->state)->func_0206fa30();
            o->hours = 0;
            o->minutes = 0;
            o->slot = -1;
        }
        break;
    }
    case 7:
        o->state = new Unk02072bec;
        ((Unk02072bec *)o->state)->unk10 = 1;
        o->state->func_08();
        break;
    }
    return id;
}

extern "C" void func_0209f6a4(Unk020d60c8 *o) {
    o->heap144 = new u8[0x2000];
    func_02099a0c(o->heap144, 0x2000, 2, 1, 0xa);
    o->heap148 = func_020999e8(0xa);
    Unk0208adc0::func_0208b40c(0xa);
    o->heap14c = new u8[0x6000];
    func_02099a0c(o->heap14c, 0x6000, 2, 1, 9);
    o->heap150 = new u8[0xa1400];
    func_02099a0c(o->heap150, 0xa1400, 2, 1, 0xb);
}

extern "C" void func_0209f748(Unk020d60c8 *o) {}

extern "C" void func_0209f74c(Unk020d60c8 *o, int slot) {
    u32 i;
    s8 *recency = o->save.recency;
    s8 *p = &recency[slot];
    switch (recency[slot]) {
    case 1:
        for (i = 0; i < 3; i++) {
            if (o->save.recency[i] == 0) {
                o->save.recency[i] = 1;
            }
        }
        *p = 0;
        break;
    case -1:
    case 2:
        for (i = 0; i < 3; i++) {
            if (*(u8 *)&o->save.recency[i] <= 1) {
                o->save.recency[i] = o->save.recency[i] + 1;
            }
        }
        *p = 0;
        break;
    case 0:
        break;
    }
    func_020897b4("Slot recency = %i, %i, %i", o->save.recency[0], o->save.recency[1],
                  o->save.recency[2]);
}

extern "C" void func_0209f810(Unk020d60c8 *o) {
    func_020a51cc(o->card, &o->save, 0x104);
    while (func_020a5538(o->card)) {
        func_0207a748();
    }
}

extern "C" void func_0209f850(Unk020d60c8 *o, int volume) {
    o->music = volume;
    func_020a3584(func_020a2994(), 0, volume);
    func_020a3584(func_020a2994(), 10, volume);
}

extern "C" void func_0209f880(Unk020d60c8 *o, int volume) {
    o->effects = volume;
    static Unk020bfc3c &sounds = data_020bfc3c;
    if (data_020bfc3c.enabled) {
        func_0205292c(&sounds, volume);
    }
}

extern "C" Unk0209f8d0 *func_0209f8d0(Unk020d60c8 *o, int slot) {
    return &o->save.records[slot];
}

extern "C" void func_0209f8e0(Unk020d60c8 *o) {
    delete o->texts;
    switch (o->save.language) {
    case 0:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_english.text.nitro_text");
        return;
    case 1:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_french.text.nitro_text");
        return;
    case 2:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_italian.text.nitro_text");
        return;
    case 3:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_german.text.nitro_text");
        return;
    case 4:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_spanish.text.nitro_text");
        return;
    case 5:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_dutch.text.nitro_text");
        return;
    case 6:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_portuguese.text.nitro_text");
        return;
    case 7:
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_japanese.text.nitro_text");
        return;
    default:
        o->flags &= ~2;
        o->texts = new Unk020a0014((const u32 *)"build/data/text/main_english.text.nitro_text");
        return;
    }
}

/* FX32_CONST of an unsigned value, then FX_Div when the divisor is not 0. */
#define FIXED(x) ((int)((x) > 0 ? (x) * 4096 + 0.5f : (x) * 4096 - 0.5f))

extern "C" void func_0209fa80(Unk020d60c8 *o, int slot) {
    func_0206bce0()->func_0206f6fc();
    Unk0207cd78Date date;
    Unk0207cd78Time time;
    Unk0207cd78Result busy;
    busy = UNK_0207CD78_BUSY;
    while (busy == UNK_0207CD78_BUSY) {
        busy = func_0207cd78(&date, &time);
    }
    s64 seconds = func_0207d0d0(&date, &time);
    s64 elapsed = (seconds - func_0207d0d0(&o->date, &o->time)) / 60;
    seconds = elapsed + o->minutes;
    Unk0209f8d0 *record = &o->save.records[slot];
    Unk0202071c now = func_0202071c(data_020d6298);
    o->save.records[slot].unk0 = func_020a1aa4(&now);
    record->unk4 = seconds / 60 + o->hours;
    record->unk6 = seconds % 60;
    void *db;
    Unk0206b630 *collection;
    u32 found;
    u32 total;
    found = 0;
    db = data_020c3fc4;
    total = 0;
    collection = data_020d60c8.collection;
    for (int i = 0; i < 0x14; i++) {
        if ((u32)(i - 7) <= 3) {
            u32 key = func_020081dc(data_020c43a8).unk28 == 0 ? 0x85fba6e5 : 0x1e49458c;
            Unk0205cf00 *def;
            u32 type = ((u32 *)data_020ae7cc)[i];
            def = func_0205f714(db, type, 0);
            while (def != 0) {
                if (func_0205d340(def, key) && !func_0205d340(def, 0x654b481d) &&
                    !func_0205d340(def, 0x291d04a3) && !func_0205d340(def, 0x51a12c57)) {
                    if (collection->func_0206b6bc(def->unkc)) {
                        found++;
                    }
                    total++;
                }
                def = func_0205f714(db, type, def);
            }
        } else {
            Unk0205cf00 *def;
            u32 type = ((u32 *)data_020ae7cc)[i];
            def = func_0205f714(db, type, 0);
            while (def != 0) {
                if (!func_0205d340(def, 0x51a12c57)) {
                    if (collection->func_0206b6bc(def->unkc)) {
                        found++;
                    }
                    total++;
                }
                def = func_0205f714(db, type, def);
            }
        }
    }
    int percent = FIXED(total) != 0 ? func_02077c60(FIXED(found * 100), FIXED(total))
                                    : FIXED(found * 100);
    record->unk7 = percent >> 12;
    const u8 *name = data_020c4510;
    for (int j = 0; j < 0x40; j++) {
        record->unk8[j] = name[j];
    }
    record->unk48 = o->unk15c;
    record->unk4c = o->music;
    record->unk50 = o->effects;
    func_0209f74c(o, slot);
    func_0209f810(o);
    func_020a531c(o->card, slot, o->saves->unk0, o->saves->count);
}

extern "C" bool func_0209feb0(Unk020d60c8 *o, int slot) {
    for (u32 i = 0; i < 3; i++) {
        if (i != slot && o->save.recency[i] > o->save.recency[slot]) {
            o->save.recency[i] = o->save.recency[i] - 1;
        }
    }
    o->save.recency[slot] = -1;
    Unk0209f8d0 empty;
    o->save.records[slot] = empty;
    func_0209f810(o);
    func_020a531c(o->card, slot, 0, 0);
    while (func_020a5538(o->card)) {
        func_0207a748();
    }
    return o->card->result == 2;
}
