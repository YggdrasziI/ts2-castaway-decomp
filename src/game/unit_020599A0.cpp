/*
 * Unit 0x020599A0-0x0205AF94: the weather effects Unk020599a0 (0xA1C bytes,
 * the object at 0x214 of the main game state). It reads the effects and the
 * weathers of "weather_effects.nitro_archive" (a data tree: one group of
 * effects, one group of weathers that point to an effect by name hash),
 * shows the current weather with two pool objects (the weather and a
 * flash), fades them in and out, picks a new weather each hour from the
 * effects whose chance and delay allow it, and saves and loads its state.
 *
 * Bounds: hypothesis. The constructor 0x020599A0 opens the range (the three
 * functions before it are called from the map code at 0x02057xxx); the
 * script command table (unit_0205AF94.cpp) follows. `.data` holds the
 * archive path. Real file name unknown.
 *
 * Functions other than the constructors and destructors keep C linkage:
 * other files call them by their addresses.
 *
 * Not complete: func_02059d10 and func_0205a6cc (see the notes above them);
 * `.data` at 99.1 % (the padding after the path).
 */

#include "game/unk_archive.h"
#include "game/unk_datatree.h"
#include "game/unk_pool.h"

struct Unk020a4c4c;
struct Unk020d6240;
struct Unk020c43a8;
struct Unk020d6298;
struct Unk020bfc3c;

/* A pool object with its model, texture and animation (unit_02071020.cpp). */
class Unk02071020 {
public:
    Unk02071020(Unk02093648 *container, Unk0208b554Item *item, u32 texture, u32 model, u32 anim);
    ~Unk02071020();
    void func_02071120(u32 hash);
    void func_020711e8(u32 hash);
    void func_020713f8(u32 hash);
    void func_02071494(u16 value);
    void func_020714b0(bool on);
    void func_020714e0(const s16 *rgb);
    void func_02071518(u32 value);
    u32 func_0207155c();
    void func_02071564();
    void func_02071680();
    void func_020716dc();
    void func_02071740();
    void func_0207179c(u32 bit, bool on);

    u8 unk0[0x58];
};

/* A date and time (func_0202071c, func_020a1a4c). */
struct Unk0202071c {
    Unk0202071c() {}

    u32 value;
};

extern "C" {
void func_020a1a4c(Unk0202071c *t, int a, int b, int c, int d, int year);
}

/* An effect (0x18 bytes): its hours between two weathers and its chance. */
struct Unk020599a0Effect {
    Unk020599a0Effect();
    ~Unk020599a0Effect();

    bool func_flag(u32 mask) const {
        return (flags & mask) != 0;
    }

    u32 hash;
    u16 hours;
    u32 chance;
    u32 flags;
    u32 count;
    Unk0202071c last;
};

/* A weather (0x18 bytes): its resources, effect and duration range. */
struct Unk020599a0Weather {
    Unk020599a0Weather();

    u32 texture;
    u32 model;
    u32 anim;
    int unkc;
    Unk020599a0Effect *effect;
    u16 minHours;
    u16 maxHours;
};

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0 {
    Unk020a20f0() {
        index = 0x271;
    }

    u32 state[624];
    int index;
};

/* A colour. */
struct Unk0205ae10Color {
    Unk0205ae10Color() : r(0), g(0), b(0) {}

    s16 r;
    s16 g;
    s16 b;
    s16 a;
};

struct Unk0207ce4c {
    int unk0;
    int unk4;
    int seed;
};

/* The saved hour, duration and visibility. */
struct Unk0205a5c8Block {
    u16 hour;
    u16 duration;
    bool visible;
};

class Unk020599a0 {
public:
    Unk020599a0();
    ~Unk020599a0();

    bool func_fadingIn() const {
        return state == 2 || state == 1;
    }
    bool func_fadedOut() const {
        return state == 5 || state == 4;
    }
    void func_setFade(s16 n) {
        fadeMax = n;
        if (fade > n) {
            fade = n;
        }
    }

    Unk02093648 *archive;
    Unk020599a0Effect *effects;
    int effectCount;
    Unk020599a0Weather *weathers;
    int weatherCount;
    Unk02071020 *sky;
    Unk0208b554Item *skyItem;
    Unk0208b554Item *flashItem;
    Unk02071020 *flash;
    Unk020a20f0 random;
    Unk020599a0Weather *current;
    s16 fade;
    s16 fadeMax;
    int state;
    int startTime;
    int skyTarget;
    int flashTarget;
    int flashTime;
    int flashDelay;
    u8 active;
    u8 flashing;
    u8 clear;
    int skyLevel;
    int flashLevel;
    u16 hour;
    u16 duration;
    bool visible;
};

class Unk0206bcf0 {
public:
    void func_0206f67c();
    void func_0206f6d0();

    u8 unk0[0x21c];
    int unk21c;
    u8 unk220[8];
    int time;
};

extern Unk020c7d38 data_020c7d38;
extern Unk020c43a8 data_020c43a8;
extern Unk020d6298 data_020d6298;
extern Unk020bfc3c data_020bfc3c;

extern "C" {

Unk0206bcf0 *func_0206bce0();
bool func_0206757c(Unk020c43a8 *p, int mask);
Unk0202071c func_0202071c(Unk020d6298 *clock);
Unk020d6240 *func_020a18e4();
bool func_020a1344(Unk020d6240 *system, int a);
bool func_020a1280(Unk020d6240 *system, int a, int b);
void func_020a1568(Unk020d6240 *system, int a, int b, int c);
int func_020a1e1c(Unk0202071c *a, Unk0202071c *b);
void func_02052e54(Unk020bfc3c *p);
u32 func_020a1f84(Unk020a20f0 *random);
void func_020a1f3c(Unk020a20f0 *random, int seed);
int func_020a20bc(Unk020a20f0 *random, int min, int max);
void func_0207ce4c(Unk0207ce4c *out);
void func_020a4dc4(Unk020a4c4c *save, void *data, int size);
void func_020a4d78(Unk020a4c4c *save, int a);
Unk0205a5c8Block *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4e14(Unk020a4c4c *save, void *data, int size);
void func_020a4d2c(Unk020a4c4c *save, int a);
Unk0205a5c8Block *func_020a4ce0(Unk020a4c4c *save, int size);

void func_0205a484(Unk020599a0 *p);
void func_0205a548(Unk020599a0 *p);
bool func_0205a7e8(Unk020599a0 *p, Unk02093648 *archive, u32 hash);
Unk020599a0Effect *func_0205adbc(Unk020599a0 *p, u32 hash);
Unk0205ae10Color func_0205ae10(Unk020599a0 *p, int t);
void func_0205aee0(Unk020599a0 *p, int time);

}

static inline int func_fxmulr(int a, int b) {
    return ((s64)a * b + 0x800) >> 12;
}

static inline void func_release(Unk02071020 *o) {
    o->func_02071740();
    o->func_020716dc();
    o->func_02071680();
}

Unk020599a0::Unk020599a0()
    : effects(0), effectCount(0), weathers(0), weatherCount(0), sky(0), flashItem(0), current(0), fade(0),
      fadeMax(0x3c), state(5), startTime(0), skyTarget(-2), flashTarget(-2), flashTime(-1), flashDelay(0), active(0),
      flashing(0), clear(0), skyLevel(1), flashLevel(1), hour(0xffff), duration(0), visible(1) {
    archive = new Unk02093648("ROM_Euro/source/archives/weather_effects.nitro_archive");
    archive->func_02094df4();
    if (func_0205a7e8(this, archive, 0x4850e52c)) {
        Unk020c7d38 *pool = &data_020c7d38;
        skyItem = pool->func_0208bcfc(pool->func_0208bbf4(0));
        sky = new Unk02071020(archive, skyItem, 0, 0, 0);
        flashItem = pool->func_0208bcfc(pool->func_0208bbf4(0));
        flash = new Unk02071020(archive, flashItem, 0, 0, 0);
        flash->func_020714b0(false);
        func_0205a484(this);
        Unk0207ce4c t;
        func_0207ce4c(&t);
        func_020a1f3c(&random, t.seed);
    }
}

Unk020599a0Effect::~Unk020599a0Effect() {}

Unk020599a0::~Unk020599a0() {
    func_0205a548(this);
    delete flash;
    if (effects != 0) {
        delete[] effects;
    }
    if (weathers != 0) {
        delete[] weathers;
    }
    delete sky;
    archive->func_02094f0c();
    delete archive;
}

extern "C" {

void func_02059c10(Unk020599a0 *p, bool on) {
    if (p->current != 0) {
        if (p->sky != 0) {
            p->sky->func_020714b0(on);
        }
        if (p->flash != 0) {
            p->flash->func_020714b0(on);
        }
    }
    p->visible = on;
}

void func_02059c5c(Unk020599a0 *p, u32 hash) {
    for (int i = 0; i < p->effectCount; i++) {
        if (hash == p->effects[i].hash) {
            Unk020599a0Effect &e = p->effects[i];
            e.flags |= 4;
            return;
        }
    }
}

void func_02059cb0(Unk020599a0 *p, bool on) {
    if (p->sky != 0) {
        p->sky->func_0207179c(1, on);
        p->flash->func_0207179c(1, on);
    }
    p->flash->func_0207179c(1, on);
}

u32 func_02059cf8(Unk020599a0 *p) {
    if (p->current == 0) {
        return 0;
    }
    return p->current->effect->hash;
}

/*
 * 96.59 %: the state tests are materialized as a bool (the fade test from a
 * flag set to true and cleared, as the original); the state stays in r1 there
 * and is not reloaded in the original. The effect flag test with constant registers; the weather pick
 * loop loads the count before the table, and the fade setter schedules its
 * constants differently.
 */
void func_02059d10(Unk020599a0 *p, bool paused) {
    if (!func_0206757c(&data_020c43a8, 0x20)) {
        return;
    }
    Unk0202071c now = func_0202071c(&data_020d6298);
    int time = func_0206bce0()->time;
    Unk020d6240 *system = func_020a18e4();
    bool busy = func_020a1344(system, 0) || func_020a1280(system, 0, 1);
    if (p->sky != 0) {
        p->sky->func_02071564();
        p->flash->func_02071564();
        if (p->flashing) {
            if (busy) {
                p->fade = 0;
                p->state = 5;
                p->flash->func_02071518(30);
            }
            if (p->func_fadingIn() && p->state != 1) {
                p->func_setFade(24);
                p->state = 3;
            } else {
                p->flash->func_02071518(p->flash->func_0207155c() + 1);
                Unk0205ae10Color c =
                    func_0205ae10(p, ((unsigned long long)(p->flash->func_0207155c() << 12) * 0x84 + 0x800) >> 12);
                p->flash->func_020714e0(&c.r);
                if (p->flash->func_0207155c() == 31) {
                    if (p->func_fadedOut() && p->state != 4) {
                        p->flashing = 0;
                    }
                }
            }
        } else if (p->current != 0 && !paused && !busy && p->func_fadedOut() && func_0206bce0()->unk21c == 0 &&
                   p->visible && p->clear && p->current->effect->hash == 0xcc4ecea4 &&
                   time - p->flashTime > p->flashDelay) {
            p->flashing = 1;
            p->flash->func_02071518(1);
            func_02052e54(&data_020bfc3c);
            p->func_setFade(3);
            p->state = 0;
            p->flashTime = time;
            p->flashDelay = func_020a1f84(&p->random) % 900 + 300;
        }
        if (p->current != 0 && !paused && time - p->startTime > 150) {
            bool clear = p->skyTarget < 1 && p->flashTarget < 1;
            p->clear = clear;
            if (clear) {
                Unk0202071c last = p->current->effect->last;
                if (func_020a1e1c(&now, &last) >= p->duration && time - p->startTime > 0x41a) {
                    p->skyTarget = 1;
                    p->flashTarget = 1;
                }
            } else {
                if (p->skyTarget > 0) {
                    int level = p->sky->func_0207155c();
                    int n = level + (p->skyTarget - level >= 0 ? 1 : -1);
                    p->sky->func_02071518(n);
                    if (n == p->skyTarget) {
                        if (p->skyTarget == 1) {
                            func_0206bce0()->func_0206f6d0();
                            p->sky->func_02071518(1);
                            func_release(p->sky);
                            p->skyTarget = -2;
                        } else {
                            func_0206bce0()->func_0206f67c();
                            p->skyTarget = -1;
                        }
                    }
                }
                if (p->flashTarget > 0) {
                    int level = p->flash->func_0207155c();
                    int n = level + (p->flashTarget - level >= 0 ? 1 : -1);
                    p->flash->func_02071518(n);
                    if (n == p->flashTarget) {
                        if (p->flashTarget != 1) {
                            p->flashTarget = -1;
                        } else {
                            p->flash->func_020714b0(false);
                            p->flashTarget = -2;
                        }
                    }
                }
                if (p->skyTarget == -2 && p->flashTarget == -2) {
                    p->current = 0;
                }
            }
        }
        if (!paused && !busy) {
            int s = p->state;
            bool fading = true;
            if (s != 0 && s != 3) {
                fading = false;
            }
            if (fading) {
                int level = (func_fxdiv(p->fade << 12, p->fadeMax << 12) * 17) >> 12;
                if (level > 16) {
                    level = 16;
                }
                func_020a1568(system, 0, 0x3f, level);
            } else if (s == 4) {
                func_020a1568(system, 0, 0x3f, 0);
            } else if (s == 1) {
                func_020a1568(system, 0, 0x3f, 16);
            }
            switch (p->state) {
            case 0:
                p->fade++;
                if (p->fade >= p->fadeMax) {
                    p->fade = p->fadeMax;
                    p->state = 1;
                }
                break;
            case 3:
                p->fade--;
                if (p->fade <= 0) {
                    p->fade = 0;
                    p->state = 4;
                }
                break;
            case 4:
                p->state = 5;
                break;
            case 1:
                p->state = 2;
                break;
            }
        }
    }
    if (p->hour == (now.value & 0x7c0) >> 6) {
        return;
    }
    p->hour = (now.value & 0x7c0) >> 6;
    if (p->current != 0) {
        return;
    }
    for (int i = 0; i < p->effectCount; i++) {
        Unk020599a0Effect *e = &p->effects[i];
        if (e->count < 1 || !e->func_flag(2)) {
            continue;
        }
        if (e->flags & 8) {
            e->last = now;
            e->flags &= ~8;
        }
        Unk0202071c last = e->last;
        int minutes = func_020a1e1c(&now, &last);
        if (!(e->flags & 4)) {
            if (minutes / 60 <= e->hours) {
                continue;
            }
            if (func_020a1f84(&p->random) >= e->chance) {
                continue;
            }
        }
        u32 pick = func_020a1f84(&p->random) % e->count;
        p->current = 0;
        e->flags &= ~4;
        u32 n = 0;
        Unk020599a0Weather *w = p->weathers;
        for (int j = 0; j < p->weatherCount; j++, w++) {
            if (w->effect == e) {
                if (n++ == pick) {
                    p->current = w;
                    break;
                }
            }
        }
        p->duration = func_020a20bc(&p->random, p->current->minHours << 12, p->current->maxHours << 12) >> 12;
        p->duration = p->duration * 60;
        p->duration = p->duration + 30;
        func_0205aee0(p, time);
        e->last = now;
        return;
    }
}

void func_0205a484(Unk020599a0 *p) {
    if (p->active) {
        return;
    }
    if (p->current != 0 && p->sky != 0) {
        p->sky->func_02071120(p->current->model);
        p->sky->func_020711e8(p->current->texture);
        p->sky->func_020713f8(p->current->anim);
        p->sky->func_02071518(p->skyLevel);
        p->sky->func_020714b0(false);
    }
    p->flash->func_02071120(0x6c195890);
    p->flash->func_020711e8(0xe7c4c630);
    p->flash->func_02071518(p->flashLevel);
    p->flash->func_02071494(0xf7ff);
    p->flash->func_020714b0(false);
    p->active = 1;
}

void func_0205a548(Unk020599a0 *p) {
    if (!p->active) {
        return;
    }
    if (p->sky != 0) {
        p->skyLevel = p->sky->func_0207155c();
        func_release(p->sky);
    }
    p->flashLevel = p->flash->func_0207155c();
    func_release(p->flash);
    p->active = 0;
}

void func_0205a5c8(Unk020599a0 *p, Unk020a4c4c *save) {
    for (int i = 0; i < p->effectCount; i++) {
        func_020a4dc4(save, &p->effects[i].flags, 4);
        Unk0202071c last = p->effects[i].last;
        func_020a4dc4(save, &last, 4);
    }
    func_020a4d78(save, 2);
    Unk0205a5c8Block *b = func_020a4c60(save, 6, 1);
    b->hour = p->hour;
    b->duration = p->duration;
    b->visible = p->visible;
    int index = -1;
    if (p->current != 0) {
        index = p->current - p->weathers;
    }
    func_020a4dc4(save, &index, 4);
}

/*
 * 98.21 %: the original frame is 0xC bytes with one more stack slot; the
 * effect loop's temporary keeps a different slot.
 */
void func_0205a6cc(Unk020599a0 *p, Unk020a4c4c *save) {
    int index;
    Unk0202071c last;
    Unk0205a5c8Block *b;
    int i;
    for (i = 0; i < p->effectCount; i++) {
        func_020a4e14(save, &p->effects[i].flags, 4);
        func_020a4e14(save, &last, 4);
        p->effects[i].last = last;
    }
    func_020a4d2c(save, 2);
    b = func_020a4ce0(save, 6);
    p->hour = b->hour;
    p->duration = b->duration;
    p->visible = b->visible;
    index = -1;
    func_020a4e14(save, &index, 4);
    p->current = 0;
    if (index > -1 && index < p->weatherCount) {
        p->current = &p->weathers[index];
    }
    func_0205aee0(p, func_0206bce0()->time);
}

bool func_0205a7e8(Unk020599a0 *p, Unk02093648 *archive, u32 hash) {
    int index = archive->func_02093e9c(hash);
    if (index < 0) {
        return false;
    }
    Unk0209674c root = ((Unk02096348 *)archive->func_02093a9c(index))->func_02096980();
    if (root.func_02096814(0x2d28df8b)) {
        for (int i = 0; i < root.func_020967ec(); i++) {
            Unk0209674c group = root.func_02096774(i);
            switch ((int)group.func_02096800()) {
            case 0xafa54672: {
                p->effects = new Unk020599a0Effect[group.func_020967ec()];
                int j;
                p->effectCount = j = 0;
                for (; j < group.func_020967ec(); j++) {
                    Unk0209674c node = group.func_02096774(j);
                    if (!node.func_02096814(0x3c1b826b)) {
                        continue;
                    }
                    Unk020599a0Effect *e = &p->effects[p->effectCount++];
                    for (int k = 0; k < node.func_020967ec(); k++) {
                        Unk0209674c v = node.func_02096774(k);
                        switch ((int)v.func_02096800()) {
                        case 0x11b44:
                            e->hash = v.func_020968d8();
                            break;
                        case 0x31d26b6f:
                            if (v.func_02096948()) {
                                e->flags |= 2;
                            } else {
                                e->flags &= ~2;
                            }
                            break;
                        case 0xada42534:
                            e->hours = v.func_020968a0();
                            break;
                        case 0xaa1bdc89:
                            e->chance = v.func_02096910();
                            break;
                        case 0xde30c57e:
                            if (v.func_02096948()) {
                                e->flags |= 1;
                            } else {
                                e->flags &= ~1;
                            }
                            break;
                        }
                    }
                }
                break;
            }
            case 0xecf6eb1b: {
                p->weathers = new Unk020599a0Weather[group.func_020967ec()];
                int j;
                p->weatherCount = j = 0;
                for (; j < group.func_020967ec(); j++) {
                    Unk0209674c node = group.func_02096774(j);
                    if (!node.func_02096814(0xc1456902)) {
                        continue;
                    }
                    Unk020599a0Weather *w = &p->weathers[p->weatherCount++];
                    for (int k = 0; k < node.func_020967ec(); k++) {
                        Unk0209674c v = node.func_02096774(k);
                        switch ((int)v.func_02096800()) {
                        case 0x11b44:
                            w->unkc = v.func_020968d8();
                            break;
                        case 0x3c1b826b:
                            w->effect = func_0205adbc(p, v.func_020968d8());
                            if (w->effect != 0) {
                                w->effect->count++;
                            }
                            break;
                        case 0x275ea3a5:
                            w->texture = v.func_020968d8();
                            break;
                        case 0x8637d208:
                            w->model = v.func_020968d8();
                            break;
                        case 0xe332c28f:
                            w->anim = v.func_020968d8();
                            break;
                        case 0xbc99e279:
                            w->minHours = v.func_020968a0();
                            break;
                        case 0xbc99c383:
                            w->maxHours = v.func_020968a0();
                            break;
                        }
                    }
                }
                break;
            }
            }
        }
    }
    for (int i = 0; i < p->effectCount; i++) {
        Unk020599a0Effect *e = &p->effects[i];
        e->chance = 0xffffffff - func_fxmulr(func_02077c60(e->chance, e->hours << 12), 0xfffff);
    }
    archive->func_02093c58(index);
    return p->effectCount > 0 && p->weatherCount > 0;
}

}

Unk020599a0Weather::Unk020599a0Weather() : texture(0), model(0), anim(0), unkc(0), effect(0), minHours(0), maxHours(0) {}

Unk020599a0Effect::Unk020599a0Effect() : hash(0), hours(0), chance(0), flags(0xb), count(0) {
    func_020a1a4c(&last, 1, 1, 1, 1, 1975);
}

extern "C" {

Unk020599a0Effect *func_0205adbc(Unk020599a0 *p, u32 hash) {
    if (p->effects == 0) {
        return 0;
    }
    for (int i = 0; i < p->effectCount; i++) {
        if (hash == p->effects[i].hash) {
            return &p->effects[i];
        }
    }
    return 0;
}

Unk0205ae10Color func_0205ae10(Unk020599a0 *p, int t) {
    Unk0205ae10Color c;
    t = func_fxmulr(t, func_fxmulr(t, t));
    int inv = 0x1000 - t;
    int base = func_fxmulr(t, 0xff000);
    c.a = 0xff;
    c.r = base >> 12;
    c.g = (base + func_fxmulr(inv, 0xb4000)) >> 12;
    c.b = (base + func_fxmulr(inv, 0xff000)) >> 12;
    return c;
}

void func_0205aee0(Unk020599a0 *p, int time) {
    if (p->current == 0 || p->sky == 0 || p->flash == 0) {
        return;
    }
    p->startTime = time;
    p->sky->func_02071120(p->current->model);
    p->sky->func_020711e8(p->current->texture);
    p->sky->func_020713f8(p->current->anim);
    p->sky->func_02071518(1);
    p->sky->func_020714b0(p->visible);
    p->flash->func_020714b0(p->visible);
    p->flash->func_02071518(1);
    p->skyTarget = 31;
    p->flashTarget = p->current->effect->hash != 0xcc4ecea4 ? 15 : 31;
}

}
