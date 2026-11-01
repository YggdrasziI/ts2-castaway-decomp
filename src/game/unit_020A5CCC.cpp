/*
 * Unit 0x020A5CCC-0x020A6588: the base of the game modes and its helpers: random numbers, a random
 * point on or off screen, the actor shown by a microgame (its skeleton file and animations) and the
 * ".Distance.Min" / ".Force.Max" values of a layout. Bounds: hypothesis (0x020A6588 starts the screen
 * class of the mode, `.data` ends with the vtable, whose four empty slots are the pure functions).
 * All names are placeholders. Real file name unknown. Not complete: func_020a5f28 is the same code
 * but for its registers (the original keeps the margin in r4, its shifts in r5, the result in r6).
 */
#include "game/unk_action.h"
#include "game/unk_anim.h"
#include "game/unk_archive.h"
#include "game/unk_microgame.h"
#include "game/unk_objres.h"
#include "game/unk_screen.h"
#include "game/unk_sim.h"
#include "game/unk_vector.h"
#include "game/unk_xform.h"

struct Unk020d6240;

/* The player, as a global object. */
class Unk020a5cccPlayer {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08();
    virtual Unk02098ff0 func_0c();

    u8 unk4[8];
    Unk020680d4 *sim;
};

/* A model in the world, only what is used here. */
struct Unk02060d78 {
    u32 flags;
    void *anims;
    int unk8;
};

struct Unk020a6438Rect {
    Unk020a6438Rect(int a, int b, int c, int d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    int a, b, c, d;
};

extern "C" {
void *func_0201ba94();
void func_0205d35c(Unk0205cf00 *def);
void func_0205d37c(Unk0205cf00 *def);
Unk02060d78 *func_02060c90(void *s);
void func_02060fc8(Unk02060d78 *e);
void func_020610d8(Unk02060d78 *e, Unk02098ff0 pos);
void func_0206110c(Unk02060d78 *e, Unk02098ff0 rot);
void func_02061140(Unk02060d78 *e, Unk0209487c *model);
void func_020611e8(Unk02060d78 *e, Unk0208be3c *xform);
void func_02061298(Unk02060d78 *e, Unk02063d84 *anim, bool blend, int frames);
Unk02063d84 *func_02063e2c(u32 key, int mode);
void func_02069124(void *sim, Unk02063d84 *anim, int a, int b);
Unk020897c0 *func_02063d84(void *anims);
void *func_0206c2a4(Unk020d6240 *system);
const char *func_020a00a0(void *texts, u32 id);
void func_020a0b0c(void *list, void *object);
void func_020a122c(Unk020d6240 *system);
u32 func_020a1f84(void *random);
int func_020a20bc(void *random, int min, int max);
u32 func_0209a3c4(u32 hash, const char *str);
int func_020a7c00(Unk020a7c90 *s);
void *func_020a6084(u32 id, void *user);
extern u8 data_020c3fc4[];
extern u8 data_020c40cc[];
extern u8 data_020c4390[];
extern Unk020a5cccPlayer data_020c43a8;
extern const s16 data_020af1e8[];
extern u8 data_020d6298[];
extern u8 data_020d62a4[];
}

static void *data_020d710c;

struct Unk02098e70Wrap {
    Unk02098e70 v;
};

static inline void func_set(Unk02098e70 &d, const Unk02098e70 &s) {
    *(Unk02098e70Wrap *)&d = *(Unk02098e70Wrap *)&s;
}

static inline void *func_random() {
    if (data_020d710c == 0) {
        data_020d710c = data_020d62a4;
    }
    return data_020d710c;
}

Unk020a5ccc::Unk020a5ccc(Unk02093648 *file, int a, int b)
    : file(file), player(&data_020c43a8), item(0), flags(0), def(0), model(0), entity(0) {
    func_020a0b0c(func_0206c2a4((Unk020d6240 *)func_020a18e4()), &screen);
}

Unk020a5ccc::~Unk020a5ccc() {}

extern "C" int func_020a5d7c(Unk020a5ccc *game) {
    if (!(game->flags & 2)) {
        game->func_14();
    }
    if (game->screen.flags & 8) {
        game->screen.flags &= ~8;
        switch (game->screen.state) {
        case 1:
            game->screen.state = 2;
            game->screen.flags |= 8;
            break;
        case 2:
            game->func_10(true);
            func_020a1494(func_020a18e4(), 2, 0x10);
            func_020a122c((Unk020d6240 *)func_020a18e4());
            break;
        case 3:
            game->func_10(false);
            if ((game->flags & 1) == 1) {
                return 0;
            }
            break;
        }
    } else if (!(game->flags & 1)) {
        if (!game->func_18()) {
            game->screen.func_18();
            game->flags |= 1;
        }
    }
    if (!(game->flags & 2)) {
        game->flags |= 2;
    }
    return 1;
}

void Unk020a5ccc::func_020a5ea4(Unk020a9d58 *layout) {
    func_020a9db8(layout, func_020a6084, this);
}

extern "C" u32 func_020a5ec0() {
    return func_020a1f84(func_random());
}

extern "C" int func_020a5ef0(int min, int max) {
    return func_020a20bc(func_random(), min, max);
}

extern "C" Unk02098e70 func_020a5f28(int inside, int margin) {
    Unk02098e70 point;
    int m = margin >> 12;
    if (inside == 1) {
        point.x = func_020a5ef0(m, 0x100 - m);
        point.y = func_020a5ef0(m, 0xc0 - m);
    } else {
        int x = func_020a5ef0(0, (m << 2) + 0x100) - (m << 1);
        int y = func_020a5ef0(0, (m << 2) + 0xc0) - (m << 1);
        bool onX = x >= -m && x < m + 0x100;
        bool onY = y >= -m && y < m + 0xc0;
        if (onX & onY) {
            if (func_020a5ec0() & 1) {
                point.x = x > 0x80 ? m + 0x100 : -m;
                point.y = y;
            } else {
                point.x = x;
                point.y = y > 0x60 ? m + 0xc0 : -m;
            }
        } else {
            func_set(point, Unk02098e70(x, y));
        }
    }
    point.x <<= 12;
    point.y <<= 12;
    return point;
}

extern "C" Unk0209487c *func_020a6038(Unk020a5ccc *game, u32 hash) {
    return game->file->func_02093a9c(game->file->func_02093e9c(hash));
}

extern "C" void func_020a6058(Unk020a5ccc *game, Unk0209487c *file) {
    game->file->func_02093c58(game->file->func_02093f5c(file));
}

const char *Unk020a5ccc::func_0c(u32 id) {
    return "Unhandled";
}

extern "C" void *func_020a6084(u32 id, void *user) {
    if (id & 0x8000000) {
        return (void *)((Unk020a5ccc *)user)->func_0c(id & ~0xf8000000);
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

extern "C" bool func_020a60bc() {
    Unk020680d4 *sim = data_020c43a8.sim;
    if (sim == 0) {
        return false;
    }
    return func_02063d84(sim->anim)->func_01ff8aa0();
}

extern "C" int func_020a60e8() {
    Unk020680d4 *sim = data_020c43a8.sim;
    if (sim == 0) {
        return 0;
    }
    return func_02063d84(sim->anim)->func_02089998();
}

extern "C" void func_020a6114(Unk020a5ccc *game, u32 hash, int mode) {
    Unk02093648 *archive = data_020c409c.resources;
    Unk020a5cccPlayer *player = &data_020c43a8;
    game->model = archive->func_02093a9c(archive->func_02093e9c(func_0209a3c4(hash, "/skeleton.nitro_skeleton")));
    game->def = func_0205f6f8(data_020c3fc4, hash);
    game->entity = func_02060c90(data_020c40cc);
    func_0205d35c(game->def);
    int index = (u16)player->func_0c().y >> 4;
    int cos = data_020af1e8[index * 2 + 1];
    int sin = data_020af1e8[index * 2];
    int count = game->def->unk6;
    Unk02098ff0 pos = player->func_04();
    if (count - 1 != 0) {
        pos.x += func_fxmul(sin, 0x800);
        pos.z += func_fxmul(cos, 0x800);
    }
    func_020610d8(game->entity, pos);
    func_0206110c(game->entity, player->func_0c());
    func_02061140(game->entity, (Unk0209487c *)mode);
    func_020611e8(game->entity, new Unk0208be3c((Unk02095d1c *)game->model, 0));
    Unk02060d78 *entity = game->entity;
    entity->anims = data_020c4390;
    entity->unk8 = 0;
    game->entity->flags |= 1;
}

extern "C" void func_020a62dc(Unk020a5ccc *game, Unk02060d78 **item) {
    if (item != 0) {
        game->item = item;
        game->entity = item[0x11];
    }
}

extern "C" void func_020a62f0(Unk020a5ccc *game) {
    if (game->def != 0) {
        Unk02093648 *archive = data_020c409c.resources;
        func_02060fc8(game->entity);
        archive->func_02093c3c(game->model);
        func_0205d37c(game->def);
        game->def = 0;
        game->entity = 0;
        game->model = 0;
    }
}

extern "C" void func_020a6340(Unk020a5ccc *game, u32 hash, const char *name, int once, int frames) {
    u32 actor = func_0209a3c4(hash, "entity_");
    u32 object = func_0209a3c4(hash, "object_");
    actor = func_0209a3c4(actor, name);
    object = func_0209a3c4(object, name);
    void *sim = data_020c43a8.sim;
    if (frames == 0) {
        func_02069124(sim, 0, 0, 0);
    }
    Unk02063d84 *anim = func_02063e2c(actor, once ? 1 : 2);
    if (anim != 0 && sim != 0) {
        func_02069124(sim, anim, frames, 0);
    }
    if (game->def != 0 || game->item != 0) {
        func_02061298(game->entity, func_02063e2c(object, once ? 1 : 2), false, 0x10);
    }
}

extern "C" Unk020a6438Rect func_020a6438(Unk020a5ccc *game, Unk020a9d58 *l, Unk020a7af4 *names, u32 hash) {
    u32 distanceMin = func_0209a3c4(hash, ".Distance.Min");
    u32 distanceMax = func_0209a3c4(hash, ".Distance.Max");
    u32 forceMin = func_0209a3c4(hash, ".Force.Min");
    u32 forceMax = func_0209a3c4(hash, ".Force.Max");
    Unk020a7c90 *a = func_020aa040(l, 10, func_020a7b50(names, distanceMin));
    Unk020a7c90 *c = func_020aa040(l, 10, func_020a7b50(names, distanceMax));
    Unk020a7c90 *b = func_020aa040(l, 10, func_020a7b50(names, forceMin));
    Unk020a7c90 *d = func_020aa040(l, 10, func_020a7b50(names, forceMax));
    return Unk020a6438Rect(func_020a7c00(a), func_020a7c00(b), func_020a7c00(c), func_020a7c00(d));
}

extern "C" bool func_020a655c() {
    return (int)((*(u32 *)(data_020d6298 + 4) & 0x7c0) >> 6) < 6;
}

bool Unk020a5ccc::func_08() {
    return false;
}
