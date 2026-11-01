/*
 * Unit 0x02060274-0x02060ADC: the object resource manager Unk020c409c (one
 * static object data_020c409c). It opens "objectslocked.nitro_archive" and
 * "object_resources.nitro_archive", groups the files of the second one by the
 * object definition of "object_definitions.nitro_archive" that shares their
 * key, then loads (models, textures and their palettes) and releases the files
 * of a group as the objects using it come and go.
 *
 * Bounds: hypothesis. The code before works on another object (41 lists at
 * 0x0C, a 0x4C-byte pool); unit_02060ADC.cpp follows. The static initializer
 * (0x020AE1AC) builds data_020c409c and registers its destructor (chain node
 * 0x020C4090). `.data` holds the three archive paths; the file before has its
 * own copy of "object_definitions.nitro_archive". Real file name unknown.
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses.
 */

#include "game/unk_objres.h"
#include "game/unk_sim.h"
#include "game/unk_texture.h"
#include "game/unk_palset.h"

class Unk0209543c;

/* The model library of unit_0208A0A8.cpp: only the functions used here. */
class Unk0208a0a8 {
public:
    void func_0208a0d4(Unk0209543c *file);
    void func_0208a108(Unk02093648 *container);
    void func_0208aa90(Unk0209543c *file);
};

/* A file of the resource archive while it is grouped (16 bytes). */
struct Unk020605d0 {
    Unk020605d0() : key(0), index(0), next(0), def(-1) {}

    int key;
    int index;
    Unk020605d0 *next;
    int def;
};

extern "C" {
void func_020602b0(Unk020c409c *o);
void func_0206061c(Unk020c409c *o);
void func_0206066c(Unk020c409c *o, int group);
int func_020606a0(Unk020c409c *o, int id);
void func_020606e0(Unk020c409c *o, int group);
void func_020608a8(Unk020c409c *o, int group);
void func_020608d8(Unk020c409c *o);
void func_02060acc(Unk020c409c *o);
}

extern Unk020c3ba4 data_020c3ba4;
extern Unk0208a0a8 *data_020c7d24;

Unk020c409c data_020c409c;

Unk020c409c::Unk020c409c() {
    texFirst = -1;
    texCount = 0;
    groupCount = 0;
    groups = 0;
    entries = 0;
    unk14 = 0;
    resources = 0;
    locked = 0;
    keep = true;
}

Unk020c409c::~Unk020c409c() {}

/*
 * 99.03 %: registers. The original keeps the definitions archive in r8, the
 * file array in r9, the group loop counter in r6 and the definition in r7;
 * this code is one register off for each (declaration orders, loop forms and
 * the compare order tried).
 */
void func_020602b0(Unk020c409c *o) {
    o->locked = new Unk02093648("ROM_Euro/source/archives/objectslocked.nitro_archive");
    o->locked->func_02094df4();
    o->resources = new Unk02093648("ROM_Euro/source/archives/object_resources.nitro_archive");
    o->resources->func_02094df4();
    int fileCount = o->resources->func_020939ec();
    Unk02093648 *defs = new Unk02093648("ROM_Euro/source/archives/object_definitions.nitro_archive");
    defs->func_02094df4();
    o->groups = new Unk020605fc[defs->func_020939ec()];
    o->entries = new Unk020605ec[fileCount];
    Unk020605d0 *files = new Unk020605d0[fileCount];

    int count = 0;
    o->resources->func_02094098();
    while (o->resources->func_02094104()) {
        int index = o->resources->func_02094158();
        Unk02093648Entry *e = o->resources->func_02094050(index);
        Unk020605d0 *same = 0;
        int key = e->unk4;
        for (int i = 0; i < count; i++) {
            if (key == files[i].key) {
                same = &files[i];
                break;
            }
        }
        files[count].key = key;
        files[count].index = index;
        if (same != 0) {
            Unk020605d0 *p;
            for (p = same; p->next != 0; p = p->next) {
            }
            p->next = &files[count];
        } else {
            files[count].next = 0;
        }
        count++;
    }

    int groupCount = 0;
    int entry = 0;
    for (int i = 0; i < count; i++) {
        if (files[i].key == 0) {
            continue;
        }
        int def = -1;
        defs->func_02094098();
        while (defs->func_02094104()) {
            int index = defs->func_02094158();
            if (defs->func_02094050(index)->unk4 == files[i].key) {
                def = index;
                break;
            }
        }
        files[i].def = def;
        if (def < 0) {
            files[i].key = 0;
            continue;
        }
        o->groups[groupCount].first = entry;
        o->groups[groupCount].id = def;
        Unk020605d0 *f = &files[i];
        do {
            f->def = def;
            o->entries[entry].index = f->index;
            o->entries[entry].tex = -1;
            entry++;
            o->groups[groupCount].count++;
            f->key = 0;
            f = f->next;
        } while (f != 0);
        groupCount++;
    }
    o->groupCount = groupCount;
    delete[] files;
    delete defs;
}

void func_0206061c(Unk020c409c *o) {
    data_020c7d24->func_0208a108(o->locked);
    Unk0208cdc4Result r = func_0208c578()->func_0208cdc4(o->locked, true);
    o->texFirst = r.first;
    o->texCount = r.count;
}

void func_0206066c(Unk020c409c *o, int group) {
    if (group < 0 || group >= o->groupCount) {
        return;
    }
    o->groups[group].flags |= 4;
}

int func_020606a0(Unk020c409c *o, int id) {
    for (int i = 0; i < o->groupCount; i++) {
        if (id == o->groups[i].id) {
            return i;
        }
    }
    return -1;
}

void func_020606e0(Unk020c409c *o, int group) {
    int i;
    if (group < 0 || group >= o->groupCount) {
        return;
    }
    Unk020605fc *g = &o->groups[group];
    g->refs++;
    if (g->flags & 1) {
        return;
    }
    g->flags |= 1;
    if (o->keep) {
        g->flags |= 2;
    }
    Unk0208a0a8 *library = data_020c7d24;
    Unk020c7f48 *textures = func_0208c578();
    for (i = 0; i < g->count; i++) {
        int index = o->entries[i + g->first].index;
        switch (o->resources->func_02093fbc(index)) {
        case 4:
            library->func_0208a0d4((Unk0209543c *)o->resources->func_02093a9c(index));
            break;
        case 5:
            o->resources->func_02093a9c(index);
            break;
        }
    }
    for (int i = 0; i < g->count; i++) {
        int n = i + g->first;
        int index = o->entries[n].index;
        if (o->resources->func_02093fbc(index) == 2) {
            Unk02095fdc *file = (Unk02095fdc *)o->resources->func_02093a9c(index);
            o->entries[n].tex = textures->func_0208cec4(file, !o->keep);
            if (o->keep) {
                textures->func_0208caa8(o->entries[n].tex);
            }
            if (!(g->flags & 4)) {
                data_020c3ba4.palettes->func_0206fd2c(file);
            }
            if (!o->keep) {
                o->resources->func_02093c58(index);
            }
        }
    }
}

void func_020608a8(Unk020c409c *o, int group) {
    if (group < 0 || group >= o->groupCount) {
        return;
    }
    Unk020605fc *g = &o->groups[group];
    g->refs--;
}

/*
 * 98.32 %: the original loads the group flags after comparing the reference
 * count, into the register of the count; here it is loaded before the compare
 * into r1 (reads of both fields into locals, other compare forms and a
 * volatile count tried).
 */
void func_020608d8(Unk020c409c *o) {
    Unk0208a0a8 *library = data_020c7d24;
    Unk020c7f48 *textures = func_0208c578();
    for (int i = 0; i < o->groupCount; i++) {
        Unk020605fc *g = &o->groups[i];
        int flags = g->flags;
        if (g->refs > 0) {
            if (flags & 2) {
                g->flags &= ~2;
                int n = g->first;
                int end = n + g->count;
                for (; n < end; n++) {
                    int index = o->entries[n].index;
                    if (o->resources->func_02093fbc(index) == 2) {
                        textures->func_0208cc70(o->entries[n].tex)->func_0208c398();
                        o->resources->func_02093c58(index);
                    }
                }
            }
        } else if (flags & 1) {
            g->flags &= ~3;
            for (int n = g->first + g->count - 1; n >= g->first; n--) {
                int index = o->entries[n].index;
                switch (o->resources->func_02093fbc(index)) {
                case 4:
                    library->func_0208aa90((Unk0209543c *)o->resources->func_02093a58(index));
                    o->resources->func_02093c58(index);
                    break;
                case 2:
                    if (!(g->flags & 4)) {
                        data_020c3ba4.palettes->func_0206fe30(o->entries[n].tex);
                    }
                    textures->func_0208c700(o->entries[n].tex);
                    o->entries[n].tex = -1;
                    break;
                case 5:
                    o->resources->func_02093c58(index);
                    break;
                }
            }
        }
    }
}

void func_02060acc(Unk020c409c *o) {
    o->unk14++;
}
