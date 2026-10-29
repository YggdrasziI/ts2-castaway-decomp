/*
 * Unit 0x020582E0-0x02058EB8: the world Unk020c3ba4 (0x118 bytes, static
 * object data_020c3ba4): the 41 lots (maps) it loads and unloads, the lot
 * definitions read from "build/data/lots/definitions.lots.nitro_xml" of
 * "lots.nitro_archive", the pool objects of the current lot, the two bit
 * sets of 41 lots (barriers and a second set) and their save and load.
 *
 * Bounds: hypothesis. __sinit 0x020AD2EC (.ctor entry 0x020B6E70) builds
 * data_020c3ba4 with 0x020582F8 and registers 0x0205837C as its destructor
 * (chain node 0x020C3B98). With `-str reuse`, the second copy of
 * "lot.lot.nitro_lot" (0x020BBBA0, read by 0x020582E0) shows that the lot
 * code before (0x02056E7C reads the first copy) is another file. The object
 * groups (unit_02058EB8.cpp) follow. `.rodata` is the palette colour of the
 * palette set. Real file name unknown.
 *
 * Functions other than the constructors and destructor keep C linkage:
 * other files call them by their addresses.
 */

#include "game/unk_archive.h"
#include "game/unk_datatree.h"
#include "game/unk_palset.h"
#include "game/unk_pool.h"
#include "game/unk_texanim.h"

typedef signed char s8;
typedef unsigned char u8;

struct Unk020a4c4c {
    u8 unk0[0x10];
    u32 flags;
};

/* The save block of the world. */
struct Unk02058ce8Block {
    u32 magic;
    u32 size;
    int count;
    int map;
};

/* A lot definition (0x0C bytes). */
struct Unk020589ac {
    Unk020589ac();

    u8 id;
    s8 links[3];
    u32 hash;
    u32 flags;
};

/* A lot (0x38 bytes, built by the lot code at 0x02056380). */
class Unk02058788 {
public:
    Unk02058788(int map, Unk02093648 *archive, bool current);
    ~Unk02058788();

    u8 unk0[0x38];
};

/* The parts of a lot object (only the count and the part keys). */
struct Unk02058900Def {
    u8 unk0[0x24];
    int count;
    int parts[1];
};

/* An object shown with the pool objects of a group. */
struct Unk02058900Obj {
    u8 unk0;
    u8 unk1;
    int group;
    Unk02058900Def *def;
};

/* The pool objects of a group: the keys of the models shown. */
struct Unk020c3ba4Group {
    Unk020c3ba4Group() {
        current = 0;
        for (int i = 0; i < 8; i++) {
            items[i] = -1;
            models[i] = 0;
        }
    }

    int items[8];
    int models[8];
    Unk02058900Obj *current;
};

class Unk020c3ba4 {
public:
    Unk020c3ba4();
    ~Unk020c3ba4();

    Unk02093648 *archive;
    Unk020c3ba4Group groups[1];
    int unk48;
    int unk4c;
    int unk50;
    int unk54[1];
    Unk02058788 *maps[41];
    s8 map;
    Unk0206fac8 *palset;
    Unk020705e4 *texanim;
    Unk020589ac *records;
    u32 recordCount;
    Unk0209a11c *barriers;
    Unk0209a11c *unk114;
};

/* A scene object (0x4C bytes): only its link. */
struct Unk0205fd7cItem {
    u8 unk0[0x40];
    Unk0205fd7cItem *next;
};

class Unk020c3fd4;

/* The model library of unit_0208A0A8.cpp: only the function used here. */
class Unk0208a0a8 {
public:
    Unk02089f38 *func_0208a4c8(int key);
};

extern Unk0208a0a8 *data_020c7d24;

Unk020c3ba4 data_020c3ba4;

extern "C" {

extern const u8 data_020aefa4[4] = {0x70, 0x70, 0xdf, 0x00};

extern Unk020c3fd4 data_020c3fd4;

u32 func_0209a3c4(u32 hash, const char *str);
Unk0205fd7cItem *func_0205fd7c(Unk020c3fd4 *m, int map);
void func_0205dfcc(Unk0205fd7cItem *item);
void func_02056e00(Unk02058788 *map);
void func_020a4dc4(Unk020a4c4c *save, void *data, int size);
void func_020a4d78(Unk020a4c4c *save, int a);
Unk02058ce8Block *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4e14(Unk020a4c4c *save, void *data, int size);
void func_020a4d2c(Unk020a4c4c *save, int a);
Unk02058ce8Block *func_020a4ce0(Unk020a4c4c *save, int size);

u32 func_020582e0(Unk020589ac *rec);
void func_02058380(Unk020c3ba4 *w);
Unk02058788 *func_02058518(Unk020c3ba4 *w, int map, bool current);
void func_020585a0(Unk020c3ba4 *w, int map);
void func_020585e0(Unk020c3ba4 *w, int map);
void func_02058688(Unk020c3ba4 *w);
Unk02058788 *func_02058788(Unk020c3ba4 *w, int map);
void func_020587ac(Unk020c3ba4 *w, int slot, int model, int value);
int func_02058874(Unk020c3ba4 *w, int group);
void func_020588a4(Unk020c3ba4 *w, int item);
void func_020588d4(Unk020c3ba4 *w);
int func_020588f4(Unk020c3ba4 *w, int slot);
void func_02058900(Unk020c3ba4 *w, Unk02058900Obj *o);
void func_0205899c(Unk020c3ba4 *w);
Unk020589ac *func_020589ac(Unk020c3ba4 *w, int id);
u32 func_020589f4(u32 hash);
void func_02058a2c(Unk020c3ba4 *w);
bool func_02058cc8(Unk020c3ba4 *w, u32 index);
void func_02058cd8(Unk020c3ba4 *w, u32 index, bool value);
void func_02058ce8(Unk020c3ba4 *w, Unk020a4c4c *save);
void func_02058dd4(Unk020c3ba4 *w, Unk020a4c4c *save);

}

u32 func_020582e0(Unk020589ac *rec) {
    return func_0209a3c4(rec->hash, "lot.lot.nitro_lot");
}

Unk020c3ba4::Unk020c3ba4() {
    unk50 = 0;
    map = -1;
    palset = 0;
    texanim = 0;
    records = 0;
    recordCount = 0;
    barriers = 0;
    unk114 = 0;
    for (int i = 0; i < 41; i++) {
        maps[i] = 0;
    }
}

Unk020c3ba4::~Unk020c3ba4() {}

void func_02058380(Unk020c3ba4 *w) {
    w->barriers = new Unk0209a11c(41);
    w->barriers->func_0209a27c(0, 41, false);
    w->unk114 = new Unk0209a11c(41);
    w->unk114->func_0209a27c(0, 41, false);
    Unk020c7d38 *pool = &data_020c7d38;
    w->palset = new Unk0206fac8(0x60, data_020aefa4, 1);
    w->texanim = new Unk020705e4(0x1e);
    for (int i = 0; i < 41; i++) {
        w->maps[i] = 0;
    }
    w->unk50 = 0;
    w->archive = new Unk02093648("ROM_Euro/source/archives/lots.nitro_archive");
    w->archive->func_02094df4();
    func_02058a2c(w);
    w->unk54[0] = -1;
    w->unk48 = pool->func_0208bbf4(0);
    pool->func_0208bc68(w->unk48, false);
    w->unk4c = pool->func_0208bbf4(0);
    pool->func_0208bc68(w->unk4c, false);
    for (int i = 0; i < 8; i++) {
        w->groups[0].items[i] = pool->func_0208bbf4(0);
        w->groups[0].models[i] = 0;
        func_020587ac(w, i, 0, 0x7fff);
    }
}

Unk02058788 *func_02058518(Unk020c3ba4 *w, int map, bool current) {
    if (w->maps[map] == 0) {
        w->maps[map] = new Unk02058788(map, w->archive, current);
        if (current) {
            w->map = map;
            w->palset->func_02070010(!(func_020589ac(w, map)->flags & 8));
        }
    }
    return w->maps[map];
}

void func_020585a0(Unk020c3ba4 *w, int map) {
    if (w->maps[map] == 0) {
        return;
    }
    for (Unk0205fd7cItem *item = func_0205fd7c(&data_020c3fd4, map); item != 0; item = item->next) {
        func_0205dfcc(item);
    }
}

void func_020585e0(Unk020c3ba4 *w, int map) {
    if (w->maps[map] == 0) {
        return;
    }
    func_02056e00(w->maps[map]);
    func_020588d4(w);
    if (map == w->map) {
        for (int i = 0; i < 8; i++) {
            func_020587ac(w, i, 0, 0x7fff);
        }
    }
    delete w->maps[map];
    w->maps[map] = 0;
    if (map == w->map) {
        w->map = -1;
    }
}

void func_02058688(Unk020c3ba4 *w) {
    for (int i = 0; i < 41; i++) {
        if (w->maps[i] != 0) {
            func_020585e0(w, i);
        }
    }
    delete[] w->records;
    w->records = 0;
    w->recordCount = 0;
    delete w->texanim;
    w->texanim = 0;
    delete w->palset;
    w->palset = 0;
    delete w->barriers;
    w->barriers = 0;
    delete w->unk114;
    w->unk114 = 0;
    if (w->archive != 0) {
        delete w->archive;
        w->archive = 0;
    }
}

Unk02058788 *func_02058788(Unk020c3ba4 *w, int map) {
    if (map < 0 || map >= 41) {
        return 0;
    }
    return w->maps[map];
}

void func_020587ac(Unk020c3ba4 *w, int slot, int model, int value) {
    Unk020c3ba4Group *g = w->groups;
    int item = g->items[slot];
    if (model != 0) {
        w->palset->func_0206fea8(data_020c7d24->func_0208a4c8(model));
    } else if (g->models[slot] != 0) {
        w->palset->func_0206ff5c(data_020c7d24->func_0208a4c8(g->models[slot]));
    }
    Unk020c7d38 *pool = &data_020c7d38;
    pool->func_0208bcfc(item)->func_0208ac48(model);
    if (model != 0) {
        pool->func_0208bd58(item, value);
    }
    pool->func_0208bc68(item, model != 0);
    g->models[slot] = model;
}

int func_02058874(Unk020c3ba4 *w, int group) {
    if (group < 0 || group >= 1) {
        return -1;
    }
    w->unk54[group] = w->unk50;
    w->unk50 = group;
    return -1;
}

void func_020588a4(Unk020c3ba4 *w, int item) {
    data_020c7d38.func_0208bcfc(item)->func_0208ac48(0);
    data_020c7d38.func_0208bc68(item, false);
}

void func_020588d4(Unk020c3ba4 *w) {
    if (w->unk54[0] == -101) {
        func_02058900(w, w->groups[0].current);
    }
}

int func_020588f4(Unk020c3ba4 *w, int slot) {
    return w->groups[0].items[slot];
}

void func_02058900(Unk020c3ba4 *w, Unk02058900Obj *o) {
    if (o == 0) {
        return;
    }
    if (o->group >= 0 && o->group < 1) {
        Unk020c3ba4Group *g = &w->groups[o->group];
        for (int i = 0; i < o->def->count; i++) {
            if (o->def->parts[i] != 0) {
                func_020588a4(w, g->items[i]);
            }
        }
        g->current = 0;
        o->group = func_02058874(w, o->group);
    }
    o->unk1 = 0;
}

void func_0205899c(Unk020c3ba4 *w) {
    w->texanim->func_020707cc();
}

Unk020589ac *func_020589ac(Unk020c3ba4 *w, int id) {
    for (u32 i = 0; i < w->recordCount; i++) {
        if (id == w->records[i].id) {
            return &w->records[i];
        }
    }
    return 0;
}

u32 func_020589f4(u32 hash) {
    switch ((int)hash) {
    case 0x252fd4ca:
        return 4;
    case 0xa5ce7d08:
        return 2;
    default:
        return 2;
    }
}

void func_02058a2c(Unk020c3ba4 *w) {
    int index = w->archive->func_02093e30((const u32 *)"build/data/lots/definitions.lots.nitro_xml");
    Unk02096348 *file = (Unk02096348 *)w->archive->func_02093a9c(index);
    Unk0209674c root = file->func_02096980();
    int count = root.func_020967ec();
    w->records = new Unk020589ac[count];
    w->recordCount = count;
    for (int i = 0; i < count; i++) {
        Unk020589ac *rec = &w->records[i];
        Unk0209674c node = root.func_02096774(i);
        u32 flags = 0;
        for (int j = 0; j < node.func_020967ec(); j++) {
            Unk0209674c v = node.func_02096774(j);
            switch ((int)v.func_02096800()) {
            case 0x11b44:
                rec->id = file->func_02096574(v.func_0209688c());
                break;
            case 0xd7cdaada:
                flags |= func_020589f4(v.func_020968d8());
                break;
            case 0x421b2a85:
                if (v.func_020968d8() == 0x2deceb33) {
                    flags |= 8;
                }
                break;
            case 0x348a45e8:
                rec->hash = v.func_020968d8();
                break;
            case 0x88b0d82a:
                for (int k = 0; k < 3; k++) {
                    Unk0209674c link = v.func_02096774(k);
                    rec->links[k] = file->func_02096574(link.func_0209688c());
                }
                break;
            case 0x636bcc82:
                flags |= 0x10;
                break;
            }
        }
        w->records[i].flags = flags;
    }
    w->archive->func_02093c58(index);
}

Unk020589ac::Unk020589ac() {
    id = 0;
    for (u32 i = 0; i < 3; i++) {
        links[i] = -1;
    }
    hash = 0;
    flags = 0;
}

bool func_02058cc8(Unk020c3ba4 *w, u32 index) {
    return w->barriers->func_0209a188(index);
}

void func_02058cd8(Unk020c3ba4 *w, u32 index, bool value) {
    w->barriers->func_0209a1c4(index, value);
}

void func_02058ce8(Unk020c3ba4 *w, Unk020a4c4c *save) {
    func_020a4d78(save, 2);
    Unk02058ce8Block *b = func_020a4c60(save, 0x10, 1);
    if (b == 0) {
        save->flags |= 0xc;
        return;
    }
    int map = w->map;
    b->magic = 0x4c4f5453;
    b->size = 0x10;
    b->count = 41;
    b->map = map;
    int i = 0;
    int n = w->barriers->size >> 5;
    for (i = 0; i < n; i++) {
        u32 v = w->barriers->bits != 0 ? w->barriers->bits[i] : 0;
        func_020a4dc4(save, &v, 4);
        v = w->unk114->bits != 0 ? w->unk114->bits[i] : 0;
        func_020a4dc4(save, &v, 4);
    }
}

void func_02058dd4(Unk020c3ba4 *w, Unk020a4c4c *save) {
    int i;
    int n;
    func_020a4d2c(save, 2);
    Unk02058ce8Block *b = func_020a4ce0(save, 0x10);
    if (b == 0 || b->magic != 0x4c4f5453 || b->size != 0x10 || b->count != 41) {
        save->flags |= 0xc;
        return;
    }
    n = w->barriers->size >> 5;
    for (i = 0; i < n; i++) {
        u32 v;
        func_020a4e14(save, &v, 4);
        w->barriers->func_0209a2c4(v, i);
        func_020a4e14(save, &v, 4);
        w->unk114->func_0209a2c4(v, i);
    }
    func_02058518(w, b->map, true);
}
