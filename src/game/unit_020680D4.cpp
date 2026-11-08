/*
 * Unit 0x020680D4-0x02069EA8: Unk020680d4, a sim. It loads the archive
 * "ROM_Euro/source/archives/sim.nitro_archive", builds a transform set from its
 * skeleton file and up to five body parts (pool objects with a model file and
 * up to two textures, func_02069720), plays and blends its animations
 * (func_02069124), places the parts on the skeleton bones (func_0206869c) and
 * fades in and out. Its twelve virtual functions (position, rotation, map
 * cell, direction...) implement an interface whose vtable copy follows its own.
 *
 * Bounds: hypothesis. The constructor at 0x020680D4 and the destructor are the
 * only code loading the vtable (0x020BC7D0); the functions before 0x020680D4
 * use other vtables, and 0x02069EA8 starts unit_02069EA8.cpp. `.data`: the
 * constant 0x020BC7C4 (used by func_02069db4), the vtable with its header, the
 * interface vtable copy and the strings of the file in source order, up to
 * 0x020BC88C where the strings of unit_0206BCE0.cpp start. Real file name
 * unknown.
 *
 * The functions other than the constructor, the destructor and the virtual
 * functions keep C linkage and their addresses as names.
 *
 * Not complete: functions below 100 % carry a comment with the remaining
 * difference.
 */

#include "game/unk_sim.h"

extern "C" int strcmp(const char *a, const char *b);

class Unk02095d1c : public Unk0209487c {
public:
    int func_02095d70();
    void *func_02095d98();
};

/* A record of block 0x12 of the skeleton file (0x58 bytes). */
struct Unk020680d4Bone {
    int parent;
    u32 mask;
    Unk02098094 mtx;
    char name[0x10];
};

/* The outfit given to func_02069720 (functions at 0x0206486C-0x020648AC). */
struct Unk020648ac {
    int parts[5];
    int unk14[2];
    int colors[3];
};

struct Unk020a2118Hit {
    bool hit;
    u8 unk1[0x1f];
};

struct Unk0206bcf0Ray;

struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
};

/* The tile layer returned by func_02056ed0. */
struct Unk02056ed0 {
    int unk0;
    int unk4;
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;

    u32 *func_tile(int x, int y) {
        return &tiles[y * info->width + x];
    }
};

/* The game settings (data_020d60c8): only the field used here. */
struct Unk020d60c8 {
    u8 unk0[0x15c];
    u8 unk15c;
};

struct Unk020d6298;

/* The model library of unit_0208A0A8.cpp: only the functions used here. */
class Unk0208a0a8 {
public:
    void func_0208a0d4(Unk0209543c *file);
    Unk02089f38 *func_0208a4c8(int key);
    void func_0208a5d8(int key);
};

extern Unk0208a0a8 *data_020c7d24;

/* The game state of unit_0206BCE0.cpp: only its camera controller. */
struct Unk0206bcf0 {
    u8 unk0[0x10];
    Unk02069fec cam;
};

extern "C" {
Unk0208be3cEntry *func_01ffa94c(Unk0208be3c *xform);
Unk0208be3cEntry *func_01ffa954(Unk0208be3c *xform, int index);
int func_01ffa9b0(Unk0208be3c *xform, const char *name);
void func_01ffa2d0(Unk0208be3c *xform, Unk020897c0 *anim);
void func_01ffa364(Unk0208be3c *xform, Unk020897c0 *anim, int t, u32 mask);
void func_01ffa838(Unk0208be3c *xform);
void func_01ff924c(Unk0208adc0 *set, const Unk0208af38 *src, u32 mask);
int func_01ff9180(Unk0208adc0 *set, int id, const Unk0208af38 *src);
void func_01ff9128(Unk0208adc0 *set, const Unk0208adc0 *src);
bool func_01ff9ee8(Unk020c7d38 *pool);
void func_0207a748();
Unk020897c0 *func_02063d84(Unk02063d84 *a);
void func_02063d94(Unk02063d84 *a, int speed, int b);
void func_02063e50(Unk02063d84 *a);
int func_0206486c(Unk020648ac *outfit, int i);
int func_02064894(Unk020648ac *outfit, int i);
int func_020648ac(Unk020648ac *outfit);
u32 func_0209a32c(const char *str, u32 last, u32 end);
Unk0202071c func_0202071c(Unk020d6298 *clock);
Unk0202071c func_020a1c08(const Unk0202071c *t, int minutes);
void func_020a2118(Unk020a2118Hit *hit, Unk0206bcf0Ray *ray, Unk020680d4Box *box);
Unk0206bcf0 *func_0206bce0();
int func_0206b3c4(Unk02069fec *p, int angle);
void func_0206b4a8(Unk02069fec *p, int angle);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int index);
bool func_02057e18(Unk02058788 *map, const Unk020680d4Cell *cell);
void func_02057df8(Unk02058788 *map, const Unk020680d4Cell *cell, u8 a);
void func_02057d34(Unk02058788 *map, const Unk020680d4Cell *cell, u8 a);
Unk02098ff0 func_02057b5c(Unk02058788 *map, const Unk020680d4Cell *cell);
Unk02056ed0 *func_02056ed0(Unk02058788 *map, const Unk020680d4Cell *cell);

void func_02068400(Unk020680d4 *p);
void func_0206849c(Unk020680d4 *p);
void func_020684f4(Unk020680d4 *p, Unk020648ac *outfit);
void func_020685e0(Unk020680d4 *p);
void func_02068688(Unk020680d4 *p, bool on);
void func_0206869c(Unk020680d4 *p, bool place);
bool func_02068d04(const Unk0202071c *a, const Unk0202071c *b);
void func_02069090(Unk020680d4 *p, int i, const char *name, Unk020680d4Vec offset);
void func_02069100(Unk020680d4 *p, Unk02063d84 **slot);
void func_02069124(Unk020680d4 *p, Unk02063d84 *anim, int time, bool hide);
bool func_020691c4(Unk020680d4 *p);
Unk020680d4Vec func_0206920c(Unk020680d4 *p, const char *name, Unk020680d4Vec offset);
bool func_020693d8(Unk020680d4 *p, Unk0206bcf0Ray *ray);
void func_020695f0(Unk020680d4 *p);
void func_0206961c(Unk020680d4 *p);
void func_02069720(Unk020680d4 *p, Unk020648ac *outfit);
void func_02069d4c(Unk020680d4 *p, int angle, bool b);
void func_02069db4(Unk020680d4 *p);
}

bool func_02097248(int button);

extern Unk020c3ba4 data_020c3ba4;
extern Unk020d60c8 data_020d60c8;
extern Unk020d6298 data_020d6298;

int data_020bc7c4 = 10;

static inline Unk02098094 func_mul(const Unk02098094 &a, const Unk02098094 &b) {
    Unk02098094 m;
    m.func_0209873c(a, b);
    return m;
}

static inline Unk02098ff0 func_add(const Unk02098ff0 &a, const Unk02098ff0 &b) {
    return a.func_0209911c(b);
}

static inline Unk02098ff0 func_scale(const Unk02098ff0 &v, int t) {
    return Unk02098ff0(func_fxmul(v.x, t), func_fxmul(v.y, t), func_fxmul(v.z, t));
}

static inline void func_addTo(Unk02098ff0 &a, const Unk02098ff0 &b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
}

static inline int func_clamp(int v, int min, int max) {
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

static inline int func_format(Unk02095fdc *file) {
    return (file->func_02096014()->unk0 & 0x1c000000) >> 26;
}

static inline bool func_isPal16(Unk02095fdc *file) {
    return func_format(file) == 4;
}
enum Unk020680d4Bool { UNK_020680D4_FALSE, UNK_020680D4_TRUE };

static inline Unk020680d4Bool func_isPal16e(Unk02095fdc *file) {
    return func_format(file) == 4 ? UNK_020680D4_TRUE : UNK_020680D4_FALSE;
}

static inline bool func_isWall(u32 kind) {
    return kind == 0x8000 || kind == 0x4000 || kind == 0xc000;
}

static inline bool func_done(Unk02063d84 *a) {
    return a->anim->func_01ff8a8c() || a->anim->func_01ff8aa0();
}

static inline Unk020680d4Vec &func_vec(Unk02098ff0 &v) {
    return (Unk020680d4Vec &)v;
}

static inline Unk020680d4Vec &func_vec(int &v) {
    return (Unk020680d4Vec &)v;
}

static inline const Unk020680d4Vec &func_vec(const Unk02098ff0 &v) {
    return (const Unk020680d4Vec &)v;
}

/*
 * 96.61 %: the original keeps a byte offset for the parts loop (str [base,
 * offset]) next to the part pointer, and one more saved register; this build
 * steps a pointer.
 */
Unk020680d4::Unk020680d4()
    : id(0), dir(4), flags(4), time(-1), archive(0), alpha(0x1f), alphaTo(0x1f), count(0),
      scale(0x1000, 0x1000, 0x1000), xform(0), anim(0), speed(0x1000), blend(0), prevAnim(0), unk174(0),
      unk178(0), unk17c(0), unk180(0) {
    for (int i = 0; i < 5; i++) {
        Unk020680d4Part *part = &parts[i];
        parts[i].index = data_020c7d38.func_0208bbf4(0);
        data_020c7d38.func_0208bc68(part->index, false);
        part->frame = id * 5 + i;
    }
    body.index = data_020c7d38.func_0208bbf4(0);
    archive = new Unk02093648("ROM_Euro/source/archives/sim.nitro_archive");
    archive->func_02094df4();
    Unk02095d1c *file = (Unk02095d1c *)archive->func_02093a9c(archive->func_02093e9c(0x46357938));
    xform = new Unk0208be3c(file, 0);
    int n = file->func_02095d70();
    Unk020680d4Bone *bone = (Unk020680d4Bone *)file->func_02095d98();
    for (int i = 0; i < n; i++) {
        if (strcmp(bone->name, "rootbone") != 0) {
            bone->mask = 2;
        } else {
            bone->mask = 0;
        }
        bone++;
    }
}

Unk020680d4::~Unk020680d4() {
    func_020685e0(this);
    func_02069100(this, &anim);
    func_02069100(this, &prevAnim);
    int i;
    Unk020680d4Part *part = parts;
    for (i = 0; i < 5; i++, part++) {
        if (part->index != -1) {
            Unk0208b554Item *item = data_020c7d38.func_0208bcfc(part->index);
            item->func_0208ac48(0);
            item->func_0208ad38(0);
        }
    }
    delete xform;
    xform = 0;
    archive->func_02093c58(archive->func_02093e9c(0x46357938));
    delete archive;
    archive = 0;
}

extern "C" {
void func_02068400(Unk020680d4 *p) {
    if (data_020c7d24->func_0208a4c8(0x950be33e) == 0) {
        return;
    }
    int tex = func_0208c578()->func_0208ccc0(0x33b9d81d);
    if (tex < 0) {
        return;
    }
    Unk020c7d38 *pool;
    int index = p->body.index;
    pool = &data_020c7d38;
    if (index == -1) {
        return;
    }
    pool->func_0208bcfc(index)->func_0208ac48(0x950be33e);
    pool->func_0208bd58(index, 0x83ff);
    func_0208c578()->func_0208cc70(tex)->refs++;
}

void func_0206849c(Unk020680d4 *p) {
    if (p->body.index == -1) {
        return;
    }
    data_020c7d38.func_0208bcfc(p->body.index)->func_0208ac48(0);
    int tex = func_0208c578()->func_0208ccc0(0x33b9d81d);
    func_0208c578()->func_0208cc70(tex)->refs--;
}

void func_020684f4(Unk020680d4 *p, Unk020648ac *outfit) {
    if (p->flags & 2) {
        return;
    }
    p->flags |= 2;
    func_02068400(p);
    func_02069720(p, outfit);
    Unk020c7d38 *pool = &data_020c7d38;
    for (int i = 0; i < p->count; i++) {
        pool->func_0208bc68(p->parts[i].index, true);
    }
    pool->func_0208bc68(p->body.index, true);
    p->func_00(p->func_04());
    p->func_08(p->func_0c());
}

void func_020685e0(Unk020680d4 *p) {
    if (!(p->flags & 2)) {
        return;
    }
    p->flags &= ~2;
    Unk020c7d38 *pool = &data_020c7d38;
    for (int i = 0; i < p->count; i++) {
        pool->func_0208bc68(p->parts[i].index, false);
    }
    pool->func_0208bc68(p->body.index, false);
    while (func_01ff9ee8(pool)) {
        func_0207a748();
    }
    func_0206961c(p);
    func_0206849c(p);
}

void func_02068688(Unk020680d4 *p, bool on) {
    p->alphaTo = on ? 0x1f : 0;
}

void func_0206869c(Unk020680d4 *p, bool place) {
    Unk0208adc0 *set = data_020c7d38.func_0208bcfc(p->body.index)->func_0208ad18();
    Unk0208af38 e;
    p->alpha += p->alphaTo - p->alpha > 0 ? 1 : -1;
    p->alpha = func_clamp(p->alpha, 0, 0x1f);
    if (p->flags & 0x10) {
        if (data_020d60c8.unk15c) {
            if (func_02097248(11) || func_02097248(0) || func_02097248(10) || func_02097248(1)) {
                func_020695f0(p);
            }
        } else {
            if (func_02097248(5) || func_02097248(4) || func_02097248(6) || func_02097248(7)) {
                func_020695f0(p);
            }
        }
    }
    Unk020c7d38 *pool = &data_020c7d38;
    pool->func_0208bc68(p->body.index, p->alpha > 0);
    e.func_0208b278(p->alpha);
    func_01ff924c(set, &e, 0x1f0000);
    if (p->anim != 0) {
        func_02063d94(p->anim, p->speed, 0);
        if (p->prevAnim != 0) {
            func_02063d94(p->prevAnim, p->speed, 0);
            p->blend -= p->blendStep;
            if (p->blend <= 0) {
                p->blend = 0;
                func_02063e50(p->prevAnim);
                p->prevAnim = 0;
            }
        }
        bool shown = (p->flags & 2) != 0;
        if (p->xform != 0 && shown) {
            func_01ffa2d0(p->xform, func_02063d84(p->anim));
            if (p->prevAnim != 0) {
                func_01ffa364(p->xform, func_02063d84(p->prevAnim), p->blend, 2);
            }
            func_01ffa838(p->xform);
            for (int i = 0; i < p->count; i++) {
                Unk020680d4Part *part = &p->parts[i];
                if (!(part->flags & 1)) {
                    continue;
                }
                pool->func_0208bcfc(part->index);
                if (!(part->flags & 2)) {
                    part->bone = func_01ffa9b0(p->xform, part->name);
                    if (part->bone != -1) {
                        part->flags |= 2;
                    }
                }
                if (place && (part->flags & 2)) {
                    Unk0208be3cEntry *entry = func_01ffa954(p->xform, part->bone);
                    Unk02098ff0 rot = p->func_0c();
                    Unk02098094 world(Unk02097b6c::func_02097f78(rot.z, rot.x, rot.y), p->func_04());
                    Unk02098094 m = entry->mtx;
                    Unk020680d4Vec s(0x1000, -0x1000, -0x1000);
                    m = func_mul(Unk02098094(Unk02097b6c::func_02097c2c(s.v)), m);
                    m.func_020982bc(func_add(m.func_020982a8(), Unk02097b6c(m).func_02097d38(part->offset.v)));
                    s = func_vec(data_020c7d38.func_0208bcfc(p->parts[0].index)->func_0208ad18()->scale.v);
                    m = func_mul(m, Unk02098094(Unk02097b6c::func_02097c2c(s.v)));
                    m = func_mul(m, world);
                    pool->func_0208be18(part->frame)->mtx = Unk02097b6c(m);
                    func_vec(pool->func_0208be18(part->frame)->pos) = func_vec(m.func_020982a8());
                    pool->func_0208be28(part->index, part->frame);
                    func_vec(pool->func_0208bcfc(part->index)->pos) = Unk020680d4Vec(0, 0, 0);
                    func_vec(pool->func_0208bcfc(part->index)->unk0c) = Unk020680d4Vec(0, 0, 0);
                    func_vec(pool->func_0208bcfc(part->index)->func_0208ad18()->scale.v) =
                        Unk020680d4Vec(0x1000, 0x1000, 0x1000);
                }
            }
        }
        if (func_done(p->anim)) {
            if (p->flags & 8) {
                func_02068688(p, true);
                p->flags &= ~8;
            }
            if (p->flags & 0x40) {
                func_02069db4(p);
            }
        }
    }
    if (p->flags & 0x20) {
        Unk0202071c now = func_0202071c(&data_020d6298);
        Unk0202071c due;
        due.value = p->time;
        if (func_02068d04(&now, &due)) {
            func_0206b4a8(&func_0206bce0()->cam, p->unk18);
            p->flags &= ~0x20;
        }
    }
    p->flags |= 4;
}

}

extern "C" bool func_02068d04(const Unk0202071c *a, const Unk0202071c *b) {
    return a->value >= b->value;
}

void Unk020680d4::func_00(Unk02098ff0 pos) {
    Unk020c7d38 *pool = &data_020c7d38;
    for (int i = 0; i < 5; i++) {
        func_vec(pool->func_0208bcfc(parts[i].index)->pos) = func_vec(pos);
    }
    Unk02098ff0 r = pos.func_0209911c(Unk02098ff0(0, 0xf6, 0));
    func_vec(pool->func_0208bcfc(body.index)->pos) = func_vec(r);
}

void Unk020680d4::func_08(Unk02098ff0 rot) {
    Unk020c7d38 *pool = &data_020c7d38;
    for (int i = 0; i < 5; i++) {
        func_vec(pool->func_0208bcfc(parts[i].index)->unk0c) = func_vec(rot);
    }
    func_vec(pool->func_0208bcfc(body.index)->unk0c) = func_vec(rot);
}

/*
 * 98.24 %: the first test reads the map index again after the compare, and the
 * tile index uses smlabb where the original uses mla.
 */
void Unk020680d4::func_10(Unk020680d4Cell c) {
    Unk020c3ba4 *world = &data_020c3ba4;
    int map = world->map;
    if (cell.pos.unk3 == map && world->maps[map] != 0 &&
        func_02057e18(world->maps[map], &cell)) {
        func_02057df8(func_02058788(world, world->map), &cell, id + 4);
    }
    if (c.pos.unk3 == world->map && world->maps[world->map] != 0 && func_02057e18(world->maps[world->map], &c)) {
        func_02057d34(func_02058788(world, world->map), &c, id + 4);
    }
    cell = c;
    Unk02098ff0 pos = func_02057b5c(func_02058788(world, world->map), &c);
    pos.x += 0x800;
    pos.z += 0x800;
    Unk02056ed0 *layer = func_02056ed0(func_02058788(world, world->map), &c);
    u32 *tile = &layer->tiles[(u32)c.xy.y * layer->info->width + c.xy.x];
    bool wall = true;
    u32 kind = *tile & 0xc000;
    if (kind != 0x8000 && kind != 0x4000 && kind != 0xc000) {
        wall = false;
    }
    func_02068688(this, !wall);
    func_00(pos);
}

void Unk020680d4::func_18(Unk020680d4Dir dir) {
    this->dir.v = dir.v;
    func_08(Unk02098ff0(0, dir.v << 14, 0));
}

Unk02098ff0 Unk020680d4::func_04() {
    return data_020c7d38.func_0208bcfc(parts[0].index)->pos;
}

Unk02098ff0 Unk020680d4::func_0c() {
    return func_vec(data_020c7d38.func_0208bcfc(parts[0].index)->unk0c).v;
}

Unk020680d4Cell Unk020680d4::func_14() {
    return cell;
}

Unk020680d4Dir Unk020680d4::func_1c() {
    return dir;
}

extern "C" {
void func_02069090(Unk020680d4 *p, int i, const char *name, Unk020680d4Vec offset) {
    if (i < 0 && i >= 5) {
        return;
    }
    Unk020680d4Part *part = &p->parts[i];
    part->flags = 1;
    part->name = name;
    part->offset = offset;
    data_020c7d38.func_0208bcfc(p->parts[i].index)->func_0208ad38(0);
}

void func_02069100(Unk020680d4 *p, Unk02063d84 **slot) {
    if (*slot != 0) {
        func_02063e50(*slot);
        *slot = 0;
    }
}

void func_02069124(Unk020680d4 *p, Unk02063d84 *anim, int time, bool hide) {
    if (hide) {
        func_02068688(p, false);
        p->flags |= 8;
    }
    if (p->anim != 0) {
        if (time <= 0) {
            func_02069100(p, &p->anim);
            p->blend = 0;
            p->prevAnim = 0;
        } else {
            func_02069100(p, &p->prevAnim);
            p->prevAnim = p->anim;
            p->blend = 0x1000;
            p->blendStep = 0x1000 / time;
        }
    } else {
        p->blend = 0;
        func_02069100(p, &p->prevAnim);
    }
    p->anim = anim;
}

bool func_020691c4(Unk020680d4 *p) {
    Unk02063d84 *a = p->anim;
    if (a != 0) {
        return func_done(a);
    }
    return true;
}

/*
 * 88.45 %: the stack slots of the temporaries (the original orders them
 * matrix result, vector, matrix, offset...) and the scheduling of the
 * fixed-point scaling differ.
 */
Unk020680d4Vec func_0206920c(Unk020680d4 *p, const char *name, Unk020680d4Vec offset) {
    if (p->xform != 0) {
        Unk0208be3cEntry *entry = func_01ffa954(p->xform, func_01ffa9b0(p->xform, name));
        if (entry == 0) {
            return Unk020680d4Vec(0, 0, 0);
        }
        Unk020680d4Vec v = func_vec(entry->mtx.func_020982a8());
        Unk02098ff0 o = Unk02097b6c(entry->mtx).func_02097d38(offset.v);
        v.v = func_scale(Unk02098ff0(v.v.x + o.x, v.v.y + o.y, v.v.z + o.z), 0x1000);
        Unk02097b6c r = Unk02097b6c::func_02097e5c(p->func_0c().y);
        v = func_vec(r.func_02097d38(v.v));
        Unk02098ff0 pos = p->func_04();
        v.v.x += pos.x;
        v.v.y += pos.y;
        v.v.z += pos.z;
        return v;
    }
    return Unk020680d4Vec(0, 0, 0);
}

bool func_020693d8(Unk020680d4 *p, Unk0206bcf0Ray *ray) {
    Unk020a2118Hit hit;
    if (p->flags & 4) {
        if (p->xform == 0) {
            return false;
        }
        Unk020680d4Vec min(0, 0, 0);
        Unk020680d4Vec max(0, 0, 0);
        int n;
        int focus;
        int i;
        Unk0208be3cEntry *entry = func_01ffa94c(p->xform);
        n = p->xform->func_0208c040();
        focus = func_01ffa9b0(p->xform, "focus_point");
        for (i = 0; i < n; i++, entry++) {
            if (i == focus) {
                continue;
            }
            Unk020680d4Vec t = func_vec(entry->mtx.func_020982a8());
            min.v.x = min.v.x > t.v.x ? t.v.x : min.v.x;
            min.v.y = min.v.y > t.v.y ? t.v.y : min.v.y;
            min.v.z = min.v.z > t.v.z ? t.v.z : min.v.z;
            t.v.x -= min.v.x;
            t.v.y -= min.v.y;
            t.v.z -= min.v.z;
            max.v.x = max.v.x < t.v.x ? t.v.x : max.v.x;
            max.v.y = max.v.y < t.v.y ? t.v.y : max.v.y;
            max.v.z = max.v.z < t.v.z ? t.v.z : max.v.z;
        }
        func_addTo(min.v, p->func_04());
        p->box = Unk020680d4Box(min, max);
        func_020a2118(&hit, ray, &p->box);
        p->flags &= ~4;
    }
    return hit.hit;
}
}

Unk020680d4Xy Unk020680d4::func_20() {
    return Unk020680d4Xy(1, 1);
}

bool Unk020680d4::func_24() {
    return true;
}

bool Unk020680d4::func_28() {
    return true;
}

extern "C" {
void func_020695f0(Unk020680d4 *p) {
    p->time = func_0202071c(&data_020d6298).value;
}

void func_0206961c(Unk020680d4 *p) {
    Unk020c7f48 *textures = func_0208c578();
    Unk0208a0a8 *library = data_020c7d24;
    Unk0206fac8 *palettes = data_020c3ba4.palettes;
    for (int i = 0; i < p->count; i++) {
        Unk020680d4Part *part = &p->parts[i];
        if (part->index != -1) {
            data_020c7d38.func_0208bcfc(part->index)->func_0208ad80();
        }
        if (part->file != 0) {
            int key = part->file->func_020955e0();
            palettes->func_0206ff5c(library->func_0208a4c8(key));
            library->func_0208a5d8(key);
            p->archive->func_02093c3c(part->file);
            part->file = 0;
        }
        for (int j = 0; j < 2; j++) {
            if (part->tex[j] != -1) {
                textures->func_0208c700(part->tex[j]);
                part->tex[j] = -1;
            }
        }
    }
}

/*
 * 97.48 %: spill slots and registers. The two later 16-colour tests are
 * materialised as 0 / 1 through the enum helper.
 */
void func_02069720(Unk020680d4 *p, Unk020648ac *outfit) {
    Unk020c7f48 *textures = func_0208c578();
    Unk0208a0a8 *library = data_020c7d24;
    Unk0206fac8 *palettes = data_020c3ba4.palettes;
    func_0206961c(p);
    p->count = 0;
    Unk0208af38 e;
    u32 hair = func_0209a32c("hair01", 0, 0);
    int colorsIndex = -1;
    Unk02095fdc *colors = 0;
    bool any = false;
    for (int i = 0; i < 3; i++) {
        bool valid = false;
        int c = outfit->colors[i];
        if (c != colorsIndex && c < 15) {
            valid = true;
        }
        any |= valid;
    }
    if (any) {
        colorsIndex = p->archive->func_02093e9c(0x14d10825);
        colors = (Unk02095fdc *)p->archive->func_02093a9c(colorsIndex);
    }
    int skin = func_020648ac(outfit);
    Unk02095fdc *skinFile = 0;
    int skinIndex = 0;
    if (skin != 0) {
        skinIndex = p->archive->func_02093e9c(skin);
        skinFile = (Unk02095fdc *)p->archive->func_02093a9c(skinIndex);
    }
    s16 rgb[4];
    rgb[0] = 0xff;
    rgb[1] = 0xff;
    rgb[2] = 0xff;
    rgb[3] = 0xff;
    e.func_0208b378(rgb);
    s16 rgb2[4];
    rgb2[0] = 0xff;
    rgb2[1] = 0xff;
    rgb2[2] = 0xff;
    rgb2[3] = 0xff;
    e.func_0208b294(rgb2);
    for (int i = 0; i < 5; i++) {
        Unk020680d4Part *part = &p->parts[p->count];
        if (outfit->parts[i] == 0) {
            continue;
        }
        bool pal16 = false;
        Unk020680d4Vec zero(0, 0, 0);
        part->file = 0;
        part->tex[0] = -1;
        part->tex[1] = -1;
        part->flags = 0;
        part->bone = -1;
        part->offset = zero;
        part->name = 0;
        data_020c7d38.func_0208be28(part->index, -1);
        int texIndex = p->archive->func_02093e9c(func_02064894(outfit, i));
        if (texIndex != -1) {
            Unk02095fdc *tex = (Unk02095fdc *)p->archive->func_02093a9c(texIndex);
            if (func_isPal16(tex)) {
                pal16 = true;
            }
            if (pal16 && skinFile != 0 && func_isPal16e(skinFile)) {
                u8 *src = (u8 *)skinFile->func_0209608c();
                u8 *dst = (u8 *)tex->func_0209608c();
                if (src != 0 && dst != 0) {
                    u16 *s = (u16 *)(src + 0x20);
                    u16 *d = (u16 *)(dst + 0x20);
                    for (int k = 0; k < 0x40; k++) {
                        *d++ = *s++;
                    }
                }
            }
            if (i < 3 && pal16 && colors != 0 && func_isPal16e(colors)) {
                u16 *s = (u16 *)((u8 *)colors->func_0209608c() + outfit->colors[i] * 0x20);
                u16 *d = (u16 *)((u8 *)tex->func_0209608c() + 0xa0);
                if (s != 0 && d != 0) {
                    for (int k = 0; k < 0x10; k++) {
                        *d++ = *s++;
                    }
                }
            }
            part->tex[0] = textures->func_0208cec4(tex, true);
            if (tex != 0) {
                p->archive->func_02093c58(texIndex);
            }
        } else {
            part->tex[0] = -1;
        }
        Unk0208c050 *texture;
        if (part->tex[0] == -1) {
            texture = 0;
        } else {
            texture = textures->func_0208cc70(part->tex[0]);
        }
        part->file = (Unk0209543c *)p->archive->func_02093a9c(p->archive->func_02093e9c(func_0206486c(outfit, i)));
        int key = 0;
        if (part->file != 0) {
            library->func_0208a0d4(part->file);
            key = part->file->func_020955e0();
        }
        Unk0208b554Item *item = data_020c7d38.func_0208bcfc(part->index);
        if (part->file != 0) {
            item->func_0208ac48(key);
            if (texture != 0) {
                e.func_0208b3ec(texture->func_0208c19c());
                func_01ff924c(item->func_0208ad18(), &e, 0x600100);
            }
            item->func_0208ad38(i == 3 ? 0 : (int)p->xform);
        }
        if (part->file != 0 && i == 4) {
            int index = p->archive->func_02093e9c(func_02064894(outfit, 5));
            Unk02095fdc *tex = (Unk02095fdc *)p->archive->func_02093a9c(index);
            part->tex[1] = tex == 0 ? -1 : textures->func_0208cec4(tex, true);
            if (item->func_0208ad18()->func_0208b060(hair)) {
                Unk0208af38 h = item->func_0208ad18()->func_0208b0cc(hair);
                h.func_0208b3ec(textures->func_0208d1b0(part->tex[1]));
                func_01ff9180(item->func_0208ad18(), hair, &h);
            }
            if (tex != 0) {
                p->archive->func_02093c58(index);
            }
        }
        Unk02089f38 *model = 0;
        if (part->file != 0) {
            model = library->func_0208a4c8(part->file->func_020955e0());
        }
        if (model != 0) {
            func_01ff9128(model->func_0208a048(), item->func_0208ad18());
            if (texture != 0) {
                palettes->func_0206fea8(model);
            }
        }
        data_020c7d38.func_0208bc68(part->index, model != 0);
        if (i == 3) {
            func_02069090(p, p->count, "head", Unk020680d4Vec(0, 0, 0));
        }
        p->count++;
    }
    if (skinFile != 0) {
        p->archive->func_02093c58(skinIndex);
    }
    if (colors != 0) {
        p->archive->func_02093c58(colorsIndex);
    }
}

void func_02069d4c(Unk020680d4 *p, int angle, bool b) {
    if (!(p->flags & 0x10)) {
        Unk0206bcf0 *state = func_0206bce0();
        bool busy = state->cam.state != 0;
        int r = func_0206b3c4(&state->cam, angle);
        if (!busy) {
            p->unk18 = r;
        }
        p->flags = (p->flags & ~0x20) | 0x10;
    }
    if (b) {
        p->flags |= 0x40;
    }
}

void func_02069db4(Unk020680d4 *p) {
    if (!(p->flags & 0x10)) {
        return;
    }
    p->flags &= ~0x10;
    p->flags |= 0x20;
    Unk0202071c now = func_0202071c(&data_020d6298);
    p->time = func_020a1c08(&now, data_020bc7c4).value;
}
}

bool Unk020680d4::func_2c(const Unk020680d4Cell &c) {
    return c == cell;
}
