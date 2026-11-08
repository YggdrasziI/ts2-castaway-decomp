/*
 * Unit 0x02055EF8-0x020582E0: the lot Unk02058788 (0x38 bytes, one per map
 * of the world, unit_020582E0.cpp) and the path finder Unk02055ef8 of its
 * tile layers. A lot reads its lot file (rooms of tile layers, textures,
 * models, objects) from the lots archive, builds the tile layers of each
 * room, spawns its scene objects, converts between cells and world
 * positions, finds the cell where a lot link leads, and tests and changes
 * tile flags. The debug strings name the lot class "cLot"
 * ("cLot::IsMaskAvailable : ..." in func_02057d54).
 *
 * Bounds: hypothesis. The path finder constructor 0x02055EF8 opens the range
 * (__sinit 0x020AD2A0, .ctor entry 0x020B6E6C, builds the two path finders
 * data_020c3b48 and data_020c3b70; `.bss` 0x020C3B20 before them is used by
 * the code before); the world (unit_020582E0.cpp) follows. `.data` holds the
 * strings, the lot link masks and a table of four-direction orders that no
 * code reads. Real file name unknown.
 *
 * Functions other than the constructors and destructors keep C linkage:
 * other files call them by their addresses.
 *
 * Not complete: four functions are close but differ (see the comment above
 * each one); all data sections match.
 */

#include "game/unk_archive.h"
#include "game/unk_pool.h"
#include "game/unk_rect.h"
#include "game/unk_texanim.h"
#include "game/unk_texture.h"
#include "game/unk_vector.h"

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef long long s64;

class Unk0209543c;

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

/* A tile position or a footprint size. */
struct Unk020680d4Xy {
    Unk020680d4Xy() {}
    Unk020680d4Xy(s16 x, s16 y) {
        this->x = x;
        this->y = y;
    }

    bool func_valid() const {
        return x >= 0 && y >= 0;
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
    Unk020680d4Cell(s8 a, s8 b, s16 c, s16 x, s16 y) : pos(a, b, c) {
        xy.x = x;
        xy.y = y;
    }
    Unk020680d4Cell(Unk020593e4 p, Unk020680d4Xy d) : pos(p), xy(d) {}

    Unk020680d4Cell func_add(Unk020680d4Xy d) const {
        return Unk020680d4Cell(pos.unk3, pos.unk2, pos.unk0, xy.x + d.x, xy.y + d.y);
    }

    Unk020593e4 pos;
    Unk020680d4Xy xy;
};

struct Unk020680d4Dir {
    Unk020680d4Dir() {}
    Unk020680d4Dir(int v) : v(v) {}

    int v;
};

/* The definition of a scene object (unit_0205F16C.cpp): only its origin. */
struct Unk0205cf00 {
    s16 x;
    s16 y;
};

/* The interface shared with the sim. */
class Unk020680d4Base {
public:
    virtual void func_00() = 0;
    virtual void func_04() = 0;
    virtual void func_08() = 0;
    virtual void func_0c() = 0;
    virtual void func_10() = 0;
    virtual Unk020680d4Cell func_14() = 0;
    virtual void func_18() = 0;
    virtual Unk020680d4Dir func_1c() = 0;
};

/* A scene object (0x4C bytes, unit_0205D8D8.cpp). */
class Unk02061d08Item : public Unk020680d4Base {
public:
    static void *operator new(unsigned long size);
    static void operator delete(void *p);

    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    ~Unk02061d08Item();

    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
    u8 unk2c[0x14];
    Unk02061d08Item *next;
    u8 unk44[4];
    Unk02061d08Item *found;
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

/* A node of the path finder (0x14 bytes). */
struct Unk02055ef8Node {
    Unk02055ef8Node() {}

    Unk02055ef8Node *parent;
    Unk02055ef8Node *prev;
    Unk02055ef8Node *next;
    int cost;
    u16 x;
    u16 y;
};

/* The path finder of a tile layer (0x28 bytes). */
class Unk02055ef8 {
public:
    Unk02055ef8();
    ~Unk02055ef8();

    s8 id;
    Unk02055ef8Node *nodes;
    Unk02055ef8Node open;
    int width;
    int height;
    u32 *tiles;
};

/* The header of a lot file (block 0x100FF). */
struct Unk02053440 {
    int roomCount;
    int unk4;
    int unk8;
    int modelCount;
    int textureCount;
    int objectCount;
    int unk18;
    int unk1c;
};

/* A room of a lot file (block 0x10100). */
struct Unk0205346c {
    int layerCount;
    int unk4;
};

/* A tile layer of a lot file (block 0x10101, 0x6C bytes). */
struct Unk0205350c {
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s16 width;
    s16 height;
    u8 unkc[0x18];
    int count;
    int parts[8];
    int values[8];
};

/* An object of a lot file (block 0x10106, 0x10 bytes). */
struct Unk02053558 {
    u32 key;
    s16 layer;
    s8 room;
    u8 unk7;
    s16 x;
    s16 y;
    Unk020680d4Dir dir;
};

/* A record of the blocks 0x10107 and 0x10108 (only the key). */
struct Unk020534a0 {
    int key;
};

/* A lot file (the file class of unit_02093648.cpp with its blocks). */
class Unk0205356c : public Unk0209487c {
};

/* A tile of a layer: its flags. */
struct Unk02056938 {
    Unk02056938();

    u32 flags;
};

/* A tile layer (0x2C bytes). */
class Unk02056ed0 {
public:
    Unk02056ed0();
    ~Unk02056ed0();

    Unk02056938 *func_tile(u32 x, u32 y) {
        return &tiles[y * info->width + x];
    }

    u8 unk0;
    u8 unk1;
    int unk4;
    Unk0205350c *info;
    u32 count;
    Unk02056938 *tiles;
    Unk020593e4 cell;
    int unk18;
    int unk1c;
    int unk20;
    u8 unk24;
    int unk28;
};

/* A room of a lot: its file record and its tile layers. */
struct Unk02058788Room {
    Unk0205346c *info;
    Unk02056ed0 *layers;
};

/* A lot (0x38 bytes). */
class Unk02058788 {
public:
    Unk02058788(int map, Unk02093648 *archive, bool current);
    ~Unk02058788();

    Unk02058788Room *rooms;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unka;
    Unk02098bc8 rect;
    Unk02093648 *archive;
    Unk0205356c *file;
    int map;
    Unk020593e4 cell;
    int *textures;
    u32 effects;
    int unk34;
};

/* A lot definition of the world (0x0C bytes). */
struct Unk020589ac {
    u8 id;
    s8 links[3];
    u32 hash;
    u32 flags;
};

/* The world (data_020c3ba4, unit_020582E0.cpp): only the fields used here. */
struct Unk020c3ba4 {
    u8 unk0[0xfc];
    s8 map;
    u8 unkfd[7];
    Unk020705e4 *texanim;
    u8 unk108[0xc];
    Unk0209a11c *unk114;
};

/* The links of a lot to its neighbours. */
struct Unk02056f6c {
    u32 masks[3];
    int map;
};

/* The lot link masks, then a table of four-direction orders that no code reads. */
struct Unk020bb9f0 {
    u32 masks[37];
    int orders[8][4];
};

/* A ray: origin and direction. */
struct Unk0205809c {
    Unk02098ff0 pos;
    Unk02098ff0 dir;
};

/* The model library of unit_0208A0A8.cpp: only the functions used here. */
class Unk0208a0a8 {
public:
    void func_0208a0d4(Unk0209543c *file);
    void func_0208aa90(Unk0209543c *file);
};

class Unk020c3fd4;
struct Unk020c3fc4;

extern Unk0208a0a8 *data_020c7d24;

Unk02055ef8 data_020c3b48;
Unk02055ef8 data_020c3b70;

extern "C" {

extern Unk020c3ba4 data_020c3ba4;
extern Unk020c3fd4 data_020c3fd4;
extern Unk020c3fc4 data_020c3fc4;

Unk020bb9f0 data_020bb9f0 = {
    {
        0x00000000, 0x40000001, 0x40000002, 0x80000001, 0x80000002, 0x80000004, 0x40000004, 0x40000008,
        0x80000008, 0x00000000, 0x80000010, 0x80000020, 0x80000040, 0x80000080, 0x40000010, 0x40000020,
        0x40000040, 0x40000080, 0x40000100, 0x40000200, 0x80000100, 0x40000400, 0x40000800, 0x40001000,
        0x80000200, 0x80000400, 0x80000800, 0x00000000, 0x80001000, 0x40002000, 0x40004000, 0x40008000,
        0x40010000, 0x40020000, 0x40040000, 0x00000000, 0x40080000,
    },
    {
        {0, 1, 3, 2}, {0, 3, 1, 2}, {2, 1, 3, 0}, {2, 3, 1, 0},
        {1, 0, 2, 3}, {3, 0, 2, 1}, {1, 2, 0, 3}, {3, 2, 0, 1},
    },
};

void func_020897b4(const char *fmt, ...);
int func_02097a6c(s64 x);
int func_02077c60(int a, int b);
u32 func_0209a3c4(u32 hash, const char *str);
Unk02053440 *func_02053440(Unk0205356c *file);
Unk0205346c *func_0205346c(Unk0205356c *file, int room);
Unk020534a0 *func_020534a0(Unk0205356c *file, int index);
Unk020534a0 *func_020534d8(Unk0205356c *file, int index);
Unk0205350c *func_0205350c(Unk0205356c *file, int layer, Unk0205346c *room);
u32 *func_02053538(Unk0205356c *file, Unk0205350c *layer);
Unk02053558 *func_02053558(Unk0205356c *file);
int func_0205f6a4(Unk020c3fc4 *db, u32 key);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, u32 key);
int func_0205d340(Unk0205cf00 *def, u32 key);
Unk02061d08Item *func_0205fd7c(Unk020c3fd4 *m, int map);
Unk02061d08Item *func_0205fb4c(Unk020c3fd4 *m, u32 key, Unk0205f098 *out, int map);
Unk020680d4Xy func_020619a8(Unk02061d08Item *item, Unk020680d4Xy p, Unk020680d4Dir dir);
Unk020589ac *func_020589ac(Unk020c3ba4 *w, int id);
u32 func_020582e0(Unk020589ac *rec);
void func_020587ac(Unk020c3ba4 *w, int slot, int model, int value);
int func_020588f4(Unk020c3ba4 *w, int slot);
bool func_02059418(const Unk020593e4 *cell);
void func_020594d0(Unk02056ed0 *layer, int id, const Unk020680d4Xy *from, const Unk020680d4Xy *to);
Unk020680d4Xy func_02059514(Unk02056ed0 *layer);
void func_02059534(Unk02056ed0 *layer, const Unk020680d4Xy *pos, const Unk020680d4Xy *size, u32 mask);
void func_02059600(Unk02056ed0 *layer, const Unk020680d4Xy *pos, const Unk020680d4Xy *size);
void func_020596b8(Unk02056ed0 *layer, const Unk020680d4Xy *pos, u32 bit);
bool func_02059710(Unk02056ed0 *layer, const Unk020680d4Xy *pos, const Unk020680d4Xy *size, u32 flags, u32 mask);
void func_02059828(Unk02056ed0 *layer, const Unk020680d4Xy *pos, const Unk020680d4Xy *size, u32 flags);
void func_020598e4(Unk02056ed0 *layer, const Unk020680d4Xy *pos, u32 bit);
bool func_02059940(Unk02056ed0 *layer, const Unk020680d4Xy *pos);

Unk02055ef8 *func_02055f34(int id);
void func_02055f6c(Unk02055ef8 *p, int width, int height, u32 *tiles);
void func_02055fe4(Unk02055ef8 *p);
void func_02056070(Unk02055ef8 *p, const Unk020680d4Xy *from, const Unk020680d4Xy *to);
Unk020680d4Xy func_020562fc(Unk02055ef8 *p);
int func_02056354(Unk02055ef8Node *n, int x, int y);
void func_02056b80(Unk02058788 *lot);
void func_02056c7c(Unk02058788 *lot);
void func_02056e00(Unk02058788 *lot);
u32 func_02056e7c(u32 hash);
Unk02056ed0 *func_02056ed0(Unk02058788 *lot, const Unk020680d4Cell *c);
Unk02056ed0 *func_02056f14(Unk02058788 *lot, const Unk020680d4Cell *c);
void func_02056f34(Unk02058788 *lot, const Unk020680d4Cell *c, u32 flags);
bool func_02056f6c(Unk02056f6c *q);
bool func_020573a4(Unk02058788 *lot, Unk020680d4Cell *out, int map);
bool func_020577a4(Unk02058788 *lot, Unk020680d4Cell *out);
Unk020680d4Cell func_02057a54(Unk02058788 *lot, const Unk02098ff0 *v);
Unk02098ff0 func_02057b5c(Unk02058788 *lot, const Unk020680d4Cell *c);
Unk020680d4Cell func_02057bb8(Unk02058788 *lot, const Unk020680d4Cell *from, const Unk020680d4Cell *to);
void func_02057cec(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 mask);
void func_02057d14(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size);
void func_02057d34(Unk02058788 *lot, const Unk020680d4Cell *c, u32 bit);
bool func_02057d54(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 flags, u32 mask);
void func_02057dd0(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 flags);
void func_02057df8(Unk02058788 *lot, const Unk020680d4Cell *c, u32 bit);
bool func_02057e18(Unk02058788 *lot, const Unk020680d4Cell *c);
bool func_02057ed8(Unk02058788 *lot, const Unk020680d4Cell *c);
bool func_02057f90(Unk02058788 *lot, const Unk020680d4Cell *c);
int func_0205803c(Unk02058788 *lot, const Unk020680d4Cell *c);
bool func_0205809c(Unk02058788 *lot, Unk020680d4Cell *out, const Unk0205809c *ray);
Unk020534a0 *func_02058134(Unk02058788 *lot, int key);
Unk020534a0 *func_02058194(Unk02058788 *lot, int key);
void func_020581f4(Unk02058788 *lot, u32 flags);

}

/* The cell of the origin of a scene object. */
static inline Unk020680d4Cell func_origin(Unk02061d08Item *item) {
    Unk020680d4Xy origin(item->def->x, item->def->y);
    Unk020680d4Xy rel = func_020619a8(item, origin, item->func_1c());
    return item->func_14().func_add(rel);
}

static inline bool func_known(Unk020c3fc4 *db, u32 key) {
    return func_0205f6a4(db, key) != -1;
}

Unk02055ef8::Unk02055ef8() {
    id = -1;
    nodes = 0;
}

Unk02055ef8::~Unk02055ef8() {
    if (nodes != 0) {
        delete[] nodes;
        nodes = 0;
    }
}

Unk02055ef8 *func_02055f34(int id) {
    if (data_020c3b48.id == id) {
        return &data_020c3b48;
    }
    if (data_020c3b70.id != id) {
        data_020c3b70.id = id;
    }
    return &data_020c3b70;
}

void func_02055f6c(Unk02055ef8 *p, int width, int height, u32 *tiles) {
    if (p->width != width || p->height != height || p->tiles != tiles) {
        p->width = width;
        p->height = height;
        p->tiles = tiles;
        if (p->nodes != 0) {
            delete[] p->nodes;
        }
        p->nodes = new Unk02055ef8Node[p->width * p->height];
    }
    func_02055fe4(p);
}

void func_02055fe4(Unk02055ef8 *p) {
    int x;
    int y;
    for (y = 0; y < p->height; y++) {
        for (x = 0; x < p->width; x++) {
            Unk02055ef8Node *n = &p->nodes[y * p->width + x];
            n->parent = 0;
            n->prev = 0;
            n->next = 0;
            n->cost = 0x270f000;
            n->x = x;
            n->y = y;
        }
    }
}

void func_02056070(Unk02055ef8 *p, const Unk020680d4Xy *from, const Unk020680d4Xy *to) {
    func_02055fe4(p);
    p->open.next = &p->nodes[from->y * p->width + from->x];
    p->open.next->prev = &p->open;
    p->open.next->cost = func_02056354(p->open.next, to->x, to->y);
    for (;;) {
        Unk02055ef8Node *cur = p->open.next;
        if (cur == 0) {
            return;
        }
        if (cur->x == to->x && cur->y == to->y) {
            return;
        }
        for (int dx = -1; dx <= 1; dx++) {
            if (cur->x == 0 && dx == -1) {
                continue;
            }
            if (cur->x == p->width - 1 && dx == 1) {
                continue;
            }
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (cur->y == 0 && dy == -1) {
                    continue;
                }
                if (cur->y == p->height - 1 && dy == 1) {
                    continue;
                }
                Unk02055ef8Node *n = &p->nodes[(cur->y + dy) * p->width + (cur->x + dx)];
                if (n->prev != 0) {
                    continue;
                }
                if (p->tiles[n->y * p->width + n->x] & 3) {
                    continue;
                }
                if (n->cost == -1) {
                    continue;
                }
                n->cost = func_02056354(n, to->x, to->y) + func_02056354(n, from->x, from->y);
                if (p->tiles[n->y * p->width + n->x] & 0xff0) {
                    n->cost += 0x64000;
                }
                n->parent = cur;
                for (Unk02055ef8Node *it = p->open.next; it != 0;) {
                    if (n->cost < it->cost) {
                        n->prev = it->prev;
                        n->next = it;
                        n->prev->next = n;
                        n->next->prev = n;
                        it = 0;
                    } else if (it->next == 0) {
                        it->next = n;
                        n->prev = it;
                        n->next = 0;
                        it = 0;
                    } else {
                        it = it->next;
                    }
                }
            }
        }
        cur->cost = -1;
        cur->prev->next = cur->next;
        if (cur->next != 0) {
            cur->next->prev = cur->prev;
        }
        cur->prev = 0;
        cur->next = 0;
    }
}

Unk020680d4Xy func_020562fc(Unk02055ef8 *p) {
    Unk02055ef8Node *n = p->open.next;
    Unk02055ef8Node *parent;
    if (n != 0 && (parent = n->parent) != 0) {
        while (parent->parent != 0) {
            n = parent;
            parent = parent->parent;
        }
        return Unk020680d4Xy(n->x, n->y);
    }
    return Unk020680d4Xy(-1, -1);
}

int func_02056354(Unk02055ef8Node *n, int x, int y) {
    int dx = x - n->x;
    int dy = y - n->y;
    return func_02097a6c((u32)((dx * dx + dy * dy) << 12));
}

/* Not complete (93.79 %): the original has a 0x30-byte frame instead of 0x34 and
 * its registers are shifted by one. Its effects loop loads &data_020c7d38 from the
 * pool at each call (ours keeps it in a register and spills the layer offset), and
 * it stores data_020c3b48.id through the symbol where ours goes through the `.bss`
 * anchor; moving the definitions below the first users changes the `.bss` order.
 * The bounds loop walks the rooms through `room` like the original. */
Unk02058788::Unk02058788(int map, Unk02093648 *archive, bool current)
    : unk4(0), unk6(0), unk8(0), unka(0), textures(0) {
    Unk020c3ba4 *world = &data_020c3ba4;
    Unk02058788Room *room;
    Unk0205346c *info;
    this->map = map;
    Unk020589ac *rec = func_020589ac(world, map);
    this->archive = archive;
    /* The original tests the file for null before the cast. */
    void *f = this->archive->func_02093a9c(this->archive->func_02093e9c(func_020582e0(rec)));
    file = f != 0 ? (Unk0205356c *)f : 0;
    Unk02053440 *header = func_02053440(file);
    if (current) {
        cell = Unk020593e4(map, 0, 0);
    } else {
        cell = Unk020593e4();
    }
    rooms = new Unk02058788Room[header->roomCount];
    if (current) {
        int n = header->textureCount;
        textures = new int[n];
        u32 *keys = (u32 *)file->func_02094d4c(0x10104);
        for (int i = 0; i < n; i++) {
            int index = this->archive->func_02093e9c(keys[i]);
            if (index != -1) {
                Unk0209487c *f = this->archive->func_02093a9c(index);
                textures[i] = func_0208c578()->func_0208cec4((Unk02095fdc *)f, true);
                this->archive->func_02093c58(index);
            }
        }
        n = header->modelCount;
        u32 *models = (u32 *)file->func_02094d4c(0x10105);
        for (int i = 0; i < n; i++) {
            int index = this->archive->func_02093e9c(models[i]);
            if (index != -1) {
                data_020c7d24->func_0208a0d4((Unk0209543c *)this->archive->func_02093a9c(index));
            }
        }
    }
    for (int r = 0; r < header->roomCount; r++) {
        room = &rooms[r];
        info = func_0205346c(file, r);
        room->layers = new Unk02056ed0[info->layerCount];
        room->info = info;
        for (int l = 0; l < info->layerCount; l++) {
            Unk02056ed0 *layer = &room->layers[l];
            layer->unk0 = 1;
            layer->info = func_0205350c(file, l, info);
            layer->count = layer->info->width * layer->info->height;
            layer->tiles = new Unk02056938[layer->count];
            layer->cell.unk3 = this->map;
            layer->cell.unk2 = r;
            layer->cell.unk0 = l;
            u32 *src = func_02053538(file, layer->info);
            for (u32 i = 0; i < layer->count; i++) {
                layer->tiles[i].flags = src[i];
            }
            if (current) {
                for (int k = 0; k < layer->info->count; k++) {
                    func_020587ac(world, k, layer->info->parts[k], layer->info->values[k]);
                }
            }
        }
    }
    if (current) {
        u32 hash = func_0209a3c4(rec->hash, "lot.effects.ecode");
        int index = this->archive->func_02093e9c(hash);
        effects = 0;
        if (header->roomCount > 0 && index != -1 && func_0205346c(file, 0)->layerCount > 0) {
            effects = hash;
            for (int l = 0; l < info->layerCount; l++) {
                for (int k = 0; k < room->layers[l].info->count; k++) {
                    world->texanim->func_02070688(this->archive, effects, data_020c7d38.func_0208bcfc(func_020588f4(world, k)));
                }
            }
        }
        data_020c3b48.id = this->map;
    }
    int minX = 0x7fffffff;
    int minY = 0x7fffffff;
    int maxX = 0x80000000;
    int maxY = 0x80000000;
    for (int r = 0; r < header->roomCount; r++) {
        room = &rooms[r];
        for (int l = 0; l < room->info->layerCount; l++) {
            Unk0205350c *i = room->layers[l].info;
            if (i->x0 < minX) {
                minX = i->x0;
            }
            if (i->y0 < minY) {
                minY = i->y0;
            }
            if (i->x1 > maxX) {
                maxX = i->x1;
            }
            if (i->y1 > maxY) {
                maxY = i->y1;
            }
        }
    }
    rect.x = minX;
    rect.y = minY;
    rect.w = maxX - minX;
    rect.h = maxY - minY;
}

Unk02056938::Unk02056938() {
    flags = 0;
}

/* 99.72 %: register allocation in the model loop (declaration order searched). */
Unk02058788::~Unk02058788() {
    Unk020705e4 *texanim;
    Unk02053440 *header;
    int m;
    Unk020c3ba4 *world;
    Unk02058788Room *room;
    Unk02056ed0 *layer;
    u32 *models;
    Unk0208a0a8 *library;
    int k;
    int r;
    int index;
    int n;
    if (map == data_020c3ba4.map) {
        header = func_02053440(file);
        if (effects != 0 && header->roomCount > 0 && header->unk4 > 0) {
            world = &data_020c3ba4;
            func_0205346c(file, 0);
            layer = rooms[0].layers;
            for (k = 0; k < layer->info->count; k++) {
                texanim = world->texanim;
                texanim->func_0207072c(archive, effects, data_020c7d38.func_0208bcfc(func_020588f4(world, k)));
            }
        }
        n = header->textureCount;
        file->func_02094d4c(0x10104);
        for (int i = 0; i < n; i++) {
            func_0208c578()->func_0208c700(textures[i]);
        }
        delete[] textures;
        textures = 0;
        m = header->modelCount;
        models = (u32 *)file->func_02094d4c(0x10105);
        for (int i = 0; i < m; i++) {
            index = archive->func_02093e9c(models[i]);
            if (index != -1) {
                library = data_020c7d24;
                library->func_0208aa90((Unk0209543c *)archive->func_02093a58(index));
                archive->func_02093c58(index);
            }
        }
    }
    if (rooms != 0) {
        for (r = 0; r < func_02053440(file)->roomCount; r++) {
            room = &rooms[r];
            if (room->layers != 0) {
                delete[] room->layers;
                room->layers = 0;
            }
        }
        delete[] rooms;
        rooms = 0;
    }
    archive->func_02093c58(archive->func_02093f5c(file));
}

void func_02056b80(Unk02058788 *lot) {
    int n = func_02053440(lot->file)->objectCount;
    Unk02053558 *o = func_02053558(lot->file);
    Unk020c3fc4 *db = &data_020c3fc4;
    for (int i = 0; i < n; i++, o++) {
        if (func_known(db, o->key) && !func_0205d340(func_0205f6f8(db, o->key), 0xc877a973)) {
            new Unk02061d08Item(func_0205f6f8(db, o->key), Unk020680d4Cell(lot->map, o->room, o->layer, o->x, o->y),
                                o->dir);
        }
    }
}

void func_02056c7c(Unk02058788 *lot) {
    int n = func_02053440(lot->file)->objectCount;
    Unk02053558 *o = func_02053558(lot->file);
    Unk020c3fc4 *db = &data_020c3fc4;
    for (int i = 0; i < n; i++, o++) {
        if (func_known(db, o->key) && func_0205d340(func_0205f6f8(db, o->key), 0xc877a973)) {
            Unk020680d4Cell c(lot->map, o->room, o->layer, o->x, o->y);
            switch (o->key) {
            case 0xcee1b0f3:
                func_02056f34(lot, &c, 0x1000);
                break;
            case 0xcee1b0f4:
                func_02056f34(lot, &c, 0x2000);
                break;
            case 0xcee1b0f5:
                func_02056f34(lot, &c, 0x3000);
                break;
            default:
                new Unk02061d08Item(func_0205f6f8(db, o->key), c, o->dir);
                break;
            }
        }
    }
}

void func_02056e00(Unk02058788 *lot) {
    Unk02061d08Item *item = func_0205fd7c(&data_020c3fd4, lot->map);
    while (item != 0) {
        if (func_0205d340(item->def, 0xc877a973)) {
            delete item;
            item = func_0205fd7c(&data_020c3fd4, lot->map);
        } else {
            item = item->next;
        }
    }
}

u32 func_02056e7c(u32 hash) {
    u32 i = 0;
    while (hash != func_0209a3c4(func_020589ac(&data_020c3ba4, i)->hash, "lot.lot.nitro_lot") && i < 41) {
        i++;
    }
    return i;
}

Unk02056ed0 *func_02056ed0(Unk02058788 *lot, const Unk020680d4Cell *c) {
    if (lot->rooms == 0) {
        func_020897b4("Segments are null");
    }
    return &lot->rooms[c->pos.unk2].layers[c->pos.unk0];
}

Unk02056ed0 *func_02056f14(Unk02058788 *lot, const Unk020680d4Cell *c) {
    return &lot->rooms[c->pos.unk2].layers[c->pos.unk0];
}

void func_02056f34(Unk02058788 *lot, const Unk020680d4Cell *c, u32 flags) {
    Unk02056ed0 *layer = func_02056ed0(lot, c);
    layer->func_tile(c->xy.x, c->xy.y)->flags |= flags;
}

bool func_02056f6c(Unk02056f6c *q) {
    switch (q->map) {
    case 1:
        q->masks[0] = 0x40001e08;
        q->masks[1] = 0x600fe1f6;
        q->masks[2] = 0;
        return true;
    case 2:
        q->masks[0] = 0x20000000;
        q->masks[1] = 0x40001e0b;
        q->masks[2] = 0x400fe1f4;
        return true;
    case 3:
        q->masks[0] = 0x80001fff;
        q->masks[1] = 0x10000000;
        q->masks[2] = 0x80000008;
        return true;
    case 4:
        q->masks[0] = 0x80001ff4;
        q->masks[1] = 0x90000009;
        q->masks[2] = 0;
        return true;
    case 5:
        q->masks[0] = 0x9000000b;
        q->masks[1] = 0x80001ff0;
        q->masks[2] = 0;
        return true;
    case 6:
        q->masks[0] = 0x60001e0b;
        q->masks[1] = 0x400fe1f4;
        q->masks[2] = 0;
        return true;
    case 7:
        q->masks[0] = 0x600fe1f7;
        q->masks[1] = 0x40000200;
        q->masks[2] = 0;
        return true;
    case 10:
        q->masks[0] = 0x80001ff0;
        q->masks[1] = 0x9000000f;
        q->masks[2] = 0;
        return true;
    case 11:
        q->masks[0] = 0x9000001f;
        q->masks[1] = 0x80001fc0;
        q->masks[2] = 0;
        return true;
    case 12:
        q->masks[0] = 0x9000003f;
        q->masks[1] = 0x80001f80;
        q->masks[2] = 0;
        return true;
    case 13:
        q->masks[0] = 0x80001f00;
        q->masks[1] = 0x9000007f;
        q->masks[2] = 0;
        return true;
    case 14:
        q->masks[0] = 0x60001e0f;
        q->masks[1] = 0x40080020;
        q->masks[2] = 0x4007e1c0;
        return true;
    case 15:
        q->masks[0] = 0x6007ffdf;
        q->masks[1] = 0x40080000;
        q->masks[2] = 0;
        return true;
    case 16:
        q->masks[0] = 0x60081e3f;
        q->masks[1] = 0x4007e180;
        q->masks[2] = 0;
        return true;
    case 17:
        q->masks[0] = 0x60081e7f;
        q->masks[1] = 0x4007e100;
        q->masks[2] = 0;
        return true;
    case 18:
        q->masks[0] = 0x60081fff;
        q->masks[1] = 0x4007e000;
        q->masks[2] = 0;
        return true;
    case 19:
        q->masks[0] = 0x600fe3ff;
        q->masks[1] = 0x40001c00;
        q->masks[2] = 0;
        return true;
    case 20:
        q->masks[0] = 0x900001ff;
        q->masks[1] = 0x80001e00;
        q->masks[2] = 0;
        return true;
    case 21:
        q->masks[0] = 0x600fe3ff;
        q->masks[1] = 0x40001800;
        q->masks[2] = 0;
        return true;
    case 22:
        q->masks[0] = 0x600fe7ff;
        q->masks[1] = 0x40001000;
        q->masks[2] = 0;
        return true;
    case 24:
        q->masks[0] = 0x80001c00;
        q->masks[1] = 0x900001ff;
        q->masks[2] = 0;
        return true;
    case 25:
        q->masks[0] = 0x80000800;
        q->masks[1] = 0x900003ff;
        q->masks[2] = 0x80001000;
        return true;
    case 29:
        q->masks[0] = 0x60081fff;
        q->masks[1] = 0x40018000;
        q->masks[2] = 0x40040000;
        return true;
    case 31:
        q->masks[0] = 0x600c3fff;
        q->masks[1] = 0x40010000;
        q->masks[2] = 0;
        return true;
    }
    return false;
}

/* Not complete (94.01 %): the original keeps lot and out on the stack, reuses the
 * cell coordinates of the valid test and keeps (link + 1) unshifted. The const view
 * of the layer in the inner loop test gives the reload of the width. */
bool func_020573a4(Unk02058788 *lot, Unk020680d4Cell *out, int map) {
    Unk020589ac *rec = func_020589ac(&data_020c3ba4, lot->map);
    int link = -1;
    for (u32 i = 0; i < 3; i++) {
        if (map == rec->links[i]) {
            link = i;
            break;
        }
    }
    if (link == -1) {
        Unk02056f6c q;
        q.map = lot->map;
        if (func_02056f6c(&q)) {
            bool fromB = (data_020bb9f0.masks[q.map] & 0x80000000) != 0;
            u32 m = data_020bb9f0.masks[map];
            bool toB = (m & 0x80000000) != 0;
            u32 mask;
            if (toB && !fromB) {
                mask = 0x20000000;
            } else if (!toB && fromB) {
                mask = 0x10000000;
            } else {
                mask = m & ~0xc0000000;
            }
            for (int i = 0; i < 3; i++) {
                if (mask & q.masks[i]) {
                    func_020897b4("from %i to %i use lot link % i", map, lot->map, i);
                    link = i;
                    break;
                }
            }
        }
    }
    if (link == -1) {
        return false;
    }
    Unk0205f098 list;
    Unk02061d08Item *item = func_0205fb4c(&data_020c3fd4, 0x12d2c5be, &list, lot->map);
    if (item != 0) {
        Unk02056ed0 *layer = lot->rooms[0].layers;
        for (; item != 0; item = item->found) {
            Unk020680d4Cell c = func_origin(item);
            if (func_02059418(&c.pos) && c.xy.func_valid()) {
                Unk02056938 *tile = layer->func_tile(c.xy.x, c.xy.y);
                if (tile != 0 && (tile->flags & 0x3000) == ((link + 1) << 12)) {
                    out->pos = layer->cell;
                    out->xy = c.xy;
                    return true;
                }
            }
        }
    }
    for (u32 r = 0; r < func_02053440(lot->file)->roomCount; r++) {
        for (u32 l = 0; l < lot->rooms[r].info->layerCount; l++) {
            Unk02056ed0 *layer = &lot->rooms[r].layers[l];
            for (u32 y = 0; y < layer->info->height; y++) {
                for (u32 x = 0; x < ((const Unk02056ed0 *)layer)->info->width; x++) {
                    int want = (link + 1) << 12;
                    int flags = layer->func_tile(x, y)->flags & 0x3000;
                    if (flags == want) {
                        out->pos = layer->cell;
                        out->xy.y = y;
                        out->xy.x = x;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/* Not complete (97.38 %): stack slots of the inline origin temporaries. */
bool func_020577a4(Unk02058788 *lot, Unk020680d4Cell *out) {
    Unk0205f098 list;
    Unk02061d08Item *item = func_0205fb4c(&data_020c3fd4, 0x12d2c5be, &list, lot->map);
    if (item != 0) {
        Unk02056ed0 *layer = lot->rooms[0].layers;
        for (; item != 0; item = item->found) {
            Unk020680d4Cell c = func_origin(item);
            if (func_02059418(&c.pos) && c.xy.func_valid()) {
                if ((layer->func_tile(c.xy.x, c.xy.y)->flags & 3) == 0) {
                    out->pos = layer->cell;
                    out->xy = c.xy;
                    return true;
                }
            }
        }
    }
    for (u32 r = 0; r < func_02053440(lot->file)->roomCount; r++) {
        for (u32 l = 0; l < lot->rooms[r].info->layerCount; l++) {
            Unk02056ed0 *layer = &lot->rooms[r].layers[l];
            for (u32 y = 0; y < layer->info->height; y++) {
                for (u32 x = 0; x < layer->info->width; x++) {
                    Unk02056938 *tile = layer->func_tile(x, y);
                    if ((tile->flags & 3) == 0) {
                        out->pos = layer->cell;
                        out->xy.x = x;
                        out->xy.y = y;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/* Both counts are unsigned, compared as signed. */
Unk020680d4Cell func_02057a54(Unk02058788 *lot, const Unk02098ff0 *v) {
    u32 l;
    Unk020680d4Cell c;
    int x = v->x >> 12;
    int z = v->z >> 12;
    for (int r = 0; r < func_02053440(lot->file)->roomCount; r++) {
        u32 n = lot->rooms[r].info->layerCount;
        for (l = 0; (int)l < (int)n; l++) {
            Unk02056ed0 *layer = &lot->rooms[r].layers[l];
            if (x >= layer->info->x0 && x < layer->info->x1 && z >= layer->info->y0 && z < layer->info->y1) {
                c.pos.unk3 = lot->map;
                c.pos.unk2 = r;
                c.pos.unk0 = l;
                c.xy.x = x - layer->info->x0;
                c.xy.y = z - layer->info->y0;
                return c;
            }
        }
    }
    return c;
}

Unk02098ff0 func_02057b5c(Unk02058788 *lot, const Unk020680d4Cell *c) {
    Unk02056ed0 *layer = &lot->rooms[c->pos.unk2].layers[c->pos.unk0];
    Unk02098ff0 v;
    v.x = (layer->info->x0 + c->xy.x) << 12;
    v.y = 0;
    v.z = (layer->info->y0 + c->xy.y) << 12;
    return v;
}

Unk020680d4Cell func_02057bb8(Unk02058788 *lot, const Unk020680d4Cell *from, const Unk020680d4Cell *to) {
    if (!func_02057e18(lot, from) || !func_02057e18(lot, to)) {
        return Unk020680d4Cell();
    }
    if (!(to->pos == from->pos)) {
        return Unk020680d4Cell();
    }
    Unk02056ed0 *layer = func_02056ed0(lot, from);
    func_020594d0(layer, lot->map, &from->xy, &to->xy);
    Unk020680d4Xy step = func_02059514(layer);
    return Unk020680d4Cell(from->pos, step);
}

void func_02057cec(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 mask) {
    func_02059534(func_02056ed0(lot, c), &c->xy, size, mask);
}

void func_02057d14(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size) {
    func_02059600(func_02056ed0(lot, c), &c->xy, size);
}

void func_02057d34(Unk02058788 *lot, const Unk020680d4Cell *c, u32 bit) {
    func_020596b8(func_02056ed0(lot, c), &c->xy, bit);
}

bool func_02057d54(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 flags, u32 mask) {
    if (!func_02059418(&c->pos)) {
        func_020897b4("cLot::IsMaskAvailable : pos.roomID is not valid, returning false");
        return false;
    }
    Unk02056ed0 *layer = func_02056ed0(lot, c);
    if (layer == 0) {
        func_020897b4("cLot::IsMaskAvailable : room is NULL, returning false");
        return false;
    }
    return func_02059710(layer, &c->xy, size, flags, mask);
}

void func_02057dd0(Unk02058788 *lot, const Unk020680d4Cell *c, const Unk020680d4Xy *size, u32 flags) {
    func_02059828(func_02056ed0(lot, c), &c->xy, size, flags);
}

void func_02057df8(Unk02058788 *lot, const Unk020680d4Cell *c, u32 bit) {
    func_020598e4(func_02056ed0(lot, c), &c->xy, bit);
}

bool func_02057e18(Unk02058788 *lot, const Unk020680d4Cell *c) {
    if (!func_02059418(&c->pos) || !c->xy.func_valid()) {
        return false;
    }
    int r = c->pos.unk2;
    if (r < 0) {
        return false;
    }
    if (r >= func_02053440(lot->file)->roomCount) {
        return false;
    }
    if (c->pos.unk0 < 0) {
        return false;
    }
    if (c->pos.unk0 >= lot->rooms[r].info->layerCount) {
        return false;
    }
    if (lot->rooms[r].layers[c->pos.unk0].unk0 == 0) {
        return false;
    }
    return func_02059940(func_02056f14(lot, c), &c->xy);
}

bool func_02057ed8(Unk02058788 *lot, const Unk020680d4Cell *c) {
    if (c->pos.unk3 == -1) {
        return false;
    }
    if (!func_02059418(&c->pos) || !c->xy.func_valid()) {
        return false;
    }
    Unk02056ed0 *layer = func_02056f14(lot, c);
    if (c->xy.x < 0) {
        return false;
    }
    if (c->xy.y < 0) {
        return false;
    }
    if (c->xy.x >= layer->info->width) {
        return false;
    }
    if (c->xy.y >= layer->info->height) {
        return false;
    }
    return (layer->func_tile(c->xy.x, c->xy.y)->flags & 3) == 0;
}

bool func_02057f90(Unk02058788 *lot, const Unk020680d4Cell *c) {
    if (!func_02059418(&c->pos) || !c->xy.func_valid()) {
        return false;
    }
    Unk02056ed0 *layer = func_02056f14(lot, c);
    u32 link = layer->func_tile(c->xy.x, c->xy.y)->flags & 0x3000;
    if (link != 0) {
        int i = (link >> 12) - 1;
        return !data_020c3ba4.unk114->func_0209a188(func_020589ac(&data_020c3ba4, lot->map)->links[i]);
    }
    return false;
}

int func_0205803c(Unk02058788 *lot, const Unk020680d4Cell *c) {
    if (c->pos.unk3 == -1) {
        return 1;
    }
    Unk02056ed0 *layer = func_02056f14(lot, c);
    u32 kind = layer->func_tile(c->xy.x, c->xy.y)->flags & 0xc000;
    if (kind == 0x8000) {
        return 3;
    }
    if (kind == 0x4000 || kind == 0xc000) {
        return 2;
    }
    return 1;
}

bool func_0205809c(Unk02058788 *lot, Unk020680d4Cell *out, const Unk0205809c *ray) {
    Unk02098ff0 dir = ray->dir;
    int t = ray->pos.y;
    if (dir.y != 0) {
        t = func_02077c60(t, dir.y);
    }
    dir.func_02099048(t);
    Unk02098ff0 p = ray->pos.func_02099150(dir);
    *out = func_02057a54(lot, &p);
    return true;
}

Unk020534a0 *func_02058134(Unk02058788 *lot, int key) {
    int i = 0;
    int n = func_02053440(lot->file)->unk18;
    for (; i < n; i++) {
        if (key == func_020534a0(lot->file, i)->key) {
            return func_020534a0(lot->file, i);
        }
    }
    return 0;
}

Unk020534a0 *func_02058194(Unk02058788 *lot, int key) {
    int i = 0;
    int n = func_02053440(lot->file)->unk1c;
    for (; i < n; i++) {
        if (key == func_020534d8(lot->file, i)->key) {
            return func_020534d8(lot->file, i);
        }
    }
    return 0;
}

void func_020581f4(Unk02058788 *lot, u32 flags) {
    for (u32 r = 0; r < func_02053440(lot->file)->roomCount; r++) {
        for (u32 l = 0; l < lot->rooms[r].info->layerCount; l++) {
            Unk02056ed0 *layer = &lot->rooms[r].layers[l];
            for (u32 y = 0; y < layer->info->height; y++) {
                for (u32 x = 0; x < layer->info->width; x++) {
                    layer->tiles[y * layer->info->width + x].flags &= ~flags;
                }
            }
        }
    }
}
