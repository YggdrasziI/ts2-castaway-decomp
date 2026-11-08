/*
 * Unit 0x0205F16C-0x0205F80C: the object definition database Unk020c3fc4 (one
 * static object data_020c3fc4). It reads every script file of
 * "object_definitions.nitro_archive", sorts them by key with a merge sort and
 * keeps one 0x1C-byte record per definition (key, script, flags, resource
 * group, sizes and position read from the script's value blocks); records are
 * found by key with a binary search.
 *
 * Bounds: hypothesis. The static initializer (0x020AE16C) builds
 * data_020c3fc4 and registers its destructor (chain node 0x020C3FB8); the
 * constructor 0x0205F16C is the first function, the code before works on the
 * search lists of scene objects. unit_0205F80C.cpp follows. `.data` holds the
 * archive path (unit_02060274.cpp has its own copy). Real file name unknown.
 *
 * Not complete: func_0205f328 is not at 100 % (comment above it).
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses.
 */

#include "game/unk_objres.h"
#include "game/unk_script.h"

/* An object definition (0x1C bytes). */
struct Unk0205cf00 {
    Unk0205cf00();
    ~Unk0205cf00() {}

    s16 x;
    s16 y;
    s16 unk4;
    s16 unk6;
    int unk8;
    int key;
    Unk020956f8 *script;
    u32 flags;
    int group;
};

/* A key and the index of its file in the archive, sorted by key. */
struct Unk0205f314 {
    Unk0205f314() : key(0), index(-1) {}

    void func_set(const Unk0205f314 &o) {
        key = o.key;
        index = o.index;
    }

    int key;
    int index;
};

class Unk020c3fc4 {
public:
    Unk020c3fc4();
    ~Unk020c3fc4();

    int refs;
    Unk0205cf00 *records;
    int count;
    Unk02093648 *archive;
};

extern "C" {

void func_02060acc(Unk020c409c *o);
int func_020606a0(Unk020c409c *o, int id);
void func_0206066c(Unk020c409c *o, int group);
void func_020608d8(Unk020c409c *o);
void func_02099afc(int id);
void func_02099b28(void);
int func_0205d340(Unk0205cf00 *def, int key);
void func_0205f280(Unk0205f314 *a, int n);
int func_0205f6a4(Unk020c3fc4 *db, int key);

}

Unk020c3fc4 data_020c3fc4;

Unk020c3fc4::Unk020c3fc4() {
    refs = 0;
    records = 0;
    count = 0;
}

Unk020c3fc4::~Unk020c3fc4() {}

extern "C" {

/*
 * The outer test divides again each time: it reads the first lo from a copy,
 * so the division is not hoisted (a span local is). The inline copy helper
 * gives the reload of the key after the compare.
 */
void func_0205f184(Unk0205f314 *src, Unk0205f314 *dst, int width, int lo, int hi) {
    int mid = lo + width;
    if (mid > hi) {
        mid = hi;
    }
    int n = 0;
    int lo0 = lo;
    while (n <= (hi - lo0 + 1) / (width * 2)) {
        int end = mid + width - 1;
        if (end > hi) {
            end = hi;
        }
        for (int k = lo; k <= end; k++) {
            if (src[lo].key <= src[mid].key) {
                dst[k].func_set(src[lo]);
                src[lo].key = 0x7fffffff;
                lo++;
            } else {
                dst[k].func_set(src[mid]);
                src[mid].key = 0x7fffffff;
                mid++;
                if (mid > end) {
                    mid = end;
                }
            }
        }
        lo = end + 1;
        mid = lo + width;
        if (mid > hi) {
            mid = hi;
        }
        n++;
    }
}

void func_0205f280(Unk0205f314 *a, int n) {
    Unk0205f314 *tmp = new Unk0205f314[n];
    for (int width = 1; width <= n; width *= 4) {
        func_0205f184(a, tmp, width, 0, n - 1);
        func_0205f184(tmp, a, width * 2, 0, n - 1);
    }
    delete[] tmp;
}

/*
 * 99.10 %: locals declared first in this order (searched); both counters unsigned,
 * compared as int, give the original registers and signed branches. Left: in the
 * first value loop the counter step is scheduled before the start reload in the
 * original (condition orders, counter types, a second block local tried).
 */
void func_0205f328(Unk020c3fc4 *db) {
    Unk0205cf00 *rec;
    Unk0205f314 *keys;
    u32 k;
    Unk020956f8 *file;
    int size;
    int index;
    Unk02093648Entry *entry;
    Unk02099c78Value *values;
    u32 j;
    Unk02099c78Block *block;
    int i;
    func_02060acc(&data_020c409c);
    db->archive = new Unk02093648("ROM_Euro/source/archives/object_definitions.nitro_archive");
    db->archive->func_020939d8(11, -1);
    db->archive->func_02094df4();
    db->count = db->archive->func_02093a08(11);
    func_02099afc(11);
    db->records = new Unk0205cf00[db->count];
    func_02099b28();
    db->archive->func_020940c0(11);
    i = 0;
    keys = new Unk0205f314[db->count];
    while (db->archive->func_02094104()) {
        if (i >= db->count) {
            break;
        }
        keys[i].index = db->archive->func_02094158();
        keys[i].key = db->archive->func_02094050(keys[i].index)->unk4;
        i++;
    }
    db->count = i;
    func_0205f280(keys, i);
    size = 0;
    for (j = 0; (int)j < db->count; j++) {
        index = keys[j].index;
        rec = &db->records[j];
        file = (Unk020956f8 *)db->archive->func_02093a9c(index);
        rec->group = func_020606a0(&data_020c409c, index);
        entry = db->archive->func_02094050(index);
        rec->script = file;
        rec->key = entry->unk4;
        size += file->func_02094cc8() - file->func_02095098();
        for (k = 0; (int)k < (int)j; k++) {
            if (db->records->key == rec->key) {
                break;
            }
        }
        values = file->func_02095ab0();
        if (file->func_02095b08(0x200011da)) {
            rec->flags |= 1;
        }
        if (file->func_02095b08(0x8c4c7c53)) {
            func_0206066c(&data_020c409c, rec->group);
        }
        block = (Unk02099c78Block *)file->func_02095a3c(0x148eaa19);
        if (block != 0) {
            for (int v = block->start; v < block->start + block->count; v++) {
                switch (values[v].unk0) {
                case 0xb0cad4ef:
                    rec->unk4 = values[v].unk4;
                    break;
                case 0xb1dd53bd:
                    rec->unk6 = values[v].unk4;
                    break;
                case 0x85fbc20b:
                    rec->unk8 = values[v].unk4;
                    break;
                }
            }
            block = (Unk02099c78Block *)file->func_02095a3c(0x38a838d2);
            if (block != 0) {
                for (int v = block->start; v < block->start + block->count; v++) {
                    switch (values[v].unk0) {
                    case 0x58:
                        rec->x = values[v].unk4;
                        break;
                    case 0x59:
                        rec->y = values[v].unk4;
                        break;
                    }
                }
            }
            file->func_0209576c();
            file->func_0209599c(0x7a90e673);
        }
    }
    delete[] keys;
}

int func_0205f6a4(Unk020c3fc4 *db, int key) {
    int lo = 0;
    int hi = db->count - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (key < db->records[mid].key) {
            hi = mid - 1;
        } else if (key > db->records[mid].key) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int key) {
    return &db->records[func_0205f6a4(db, key)];
}

Unk0205cf00 *func_0205f714(Unk020c3fc4 *db, int key, Unk0205cf00 *rec) {
    rec = rec != 0 ? rec + 1 : db->records;
    for (; rec < db->records + db->count && !func_0205d340(rec, key); rec++) {
    }
    if (rec == db->records + db->count) {
        rec = 0;
    }
    return rec;
}

int func_0205f780(Unk020c3fc4 *db, int key) {
    int n = 0;
    for (int i = 0; i < db->count; i++) {
        if (func_0205d340(&db->records[i], key)) {
            n++;
        }
    }
    return n;
}

void func_0205f7d8(Unk020c3fc4 *db) {
    db->refs++;
}

void func_0205f7e8(Unk020c3fc4 *db) {
    db->refs--;
}

void func_0205f7f8(Unk020c3fc4 *db) {
    func_020608d8(&data_020c409c);
}

}
