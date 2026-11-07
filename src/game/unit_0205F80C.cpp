/*
 * Unit 0x0205F80C-0x02060274: the scene object manager Unk020c3fd4 (one static
 * object data_020c3fd4). It owns a pool of 256 scene objects (0x4C bytes each)
 * chained in a free list, one list of live objects per map (41 maps, indexed by
 * the map of the object's cell) and a list of removed objects waiting to be
 * freed; it saves and loads the lists.
 *
 * Bounds: hypothesis. The static initializer 0x020AE198 only calls the
 * constructor 0x0205F80C on data_020c3fd4 (no destructor registered); the
 * object ends at 0x020C4090, where unit_02060274.cpp's `.bss` starts, and
 * unit_02060274.cpp follows in `.text`. Before 0x0205F80C: two counter helpers
 * of data_020c3fc4 (another static object) and a call into
 * unit_02060274.cpp, left out. Real file name unknown.
 *
 * Functions other than the constructor keep C linkage: other files call them
 * by their addresses. The scene object members are named from the code they
 * produce: `new T[n]` with a class operator new[] calls __cxa_vec_newinit,
 * `delete[]` calls __cxa_vec_delete2, `new T(save)` calls the class operator
 * new and the constructor only when it returned an object.
 */

#include "game/unk_sim.h"
#include "game/unk_objscript.h"
#include "game/unk_script.h"

struct Unk020a4c4c;

/* The definition of a scene object. */
struct Unk0205cf00 {
    u8 unk0[0x10];
    Unk020956f8 *script;
    u32 flags;
};

/* A scene object (0x4C bytes), allocated from the manager's pool. */
class Unk02061d08Item {
public:
    static void *operator new[](unsigned long size);
    static void operator delete[](void *p);
    static void *operator new(unsigned long size);
    static void operator delete(void *p);

    Unk02061d08Item();
    Unk02061d08Item(Unk020a4c4c *save);
    ~Unk02061d08Item();

    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();

    u8 unk4[0xc];
    int unk10;
    u32 flags;
    Unk020680d4Cell cell;
    u8 unk20[8];
    Unk0205cf00 *def;
    u32 id;
    u8 unk30[0xc];
    Unk02061d08Item *prev;
    Unk02061d08Item *next;
    u8 unk44[8];

    void func_setFlag(u32 mask, bool on) {
        flags &= ~mask;
        if (on) {
            flags |= mask;
        }
    }
    bool func_flag(u32 mask) const {
        return (flags & mask) != 0;
    }
};

/* The objects found by a search (constructor 0x0205F098). */
struct Unk0205f098 {
    int unk0;
};

/* A ray, passed by value. */
struct Unk0205fa30Ray {
    Unk02098ff0 pos;
    Unk02098ff0 dir;
};

/* The hit filled by func_0205ebd4. */
struct Unk0205ebd4 {
    u8 unk0[0x20];
};

class Unk020c3fd4 {
public:
    Unk020c3fd4();

    Unk02061d08Item *pool;
    Unk02061d08Item *removed;
    Unk02061d08Item *free;
    Unk02061d08Item *lists[41];
    int unkb0;
    int unkb4;
    int unkb8;
};

struct Unk02058788;

extern "C" {

extern u8 data_020c3fc4[];
extern Unk020c3ba4 data_020c3ba4;

void func_0205f7d8(void *p);
void func_0205f7e8(void *p);
int func_0205f990(Unk020c3fd4 *m);
void func_0205fc2c(Unk020c3fd4 *m);
void func_0205fcf0(Unk020c3fd4 *m, Unk02061d08Item *item);
Unk02061d08Item *func_0205fd7c(Unk020c3fd4 *m, int map);
void func_02007d30(void *p);
void func_02007e38(void *p);
int func_0205d340(Unk0205cf00 *def, u32 key);
void func_0205f0bc(Unk0205f098 *out);
void func_0205f0f0(Unk0205f098 *out, Unk02061d08Item *item);
bool func_0205ebd4(Unk02061d08Item *item, Unk0205fa30Ray *ray, Unk0205ebd4 *hit);
void func_0205ed90(Unk02061d08Item *item, Unk020a4c4c *save);
void func_0205e3f0(Unk02061d08Item *item);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
void func_020581f4(Unk02058788 *map, int a);
void func_020585a0(Unk020c3ba4 *world, int map);
void func_020a4d78(Unk020a4c4c *save, int a);
int *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4dc4(Unk020a4c4c *save, void *data, int size);
void func_020a4d2c(Unk020a4c4c *save, int a);
int *func_020a4ce0(Unk020a4c4c *save, int size);
void func_020a4e14(Unk020a4c4c *save, void *data, int size);

}

Unk020c3fd4 data_020c3fd4;

Unk020c3fd4::Unk020c3fd4() {
    pool = 0;
    removed = 0;
    free = 0;
    unkb0 = 0;
    unkb8 = 1;
    for (u32 i = 0; i < 41; i++) {
        lists[i] = 0;
    }
}

extern "C" {

/*
 * The pool chain needs the u32 counter with a signed compare and an element
 * pointer local: without the local the byte offset update is scheduled late,
 * and an int counter gives an mla for the previous element.
 */
void func_0205f844(Unk020c3fd4 *m) {
    func_0205f7d8(data_020c3fc4);
    m->unkb0 = 0;
    m->free = 0;
    for (u32 i = 0; i < 41; i++) {
        m->lists[i] = 0;
    }
    m->unkb8 = 1;
    m->pool = new Unk02061d08Item[256];
    m->unkb0 = 0;
    for (u32 i = 0; (int)i < 256; i++) {
        Unk02061d08Item *item = &m->pool[i];
        item->prev = &m->pool[i - 1];
        item->next = &m->pool[i + 1];
    }
    m->pool[0].prev = 0;
    m->pool[255].next = 0;
    m->free = m->pool;
    func_0205f990(m);
}

void func_0205f934(Unk020c3fd4 *m) {
    func_0205fc2c(m);
    delete[] m->pool;
    m->pool = 0;
    m->free = 0;
    m->unkb0 = 0;
    m->unkb8 = 0;
    func_0205f7e8(data_020c3fc4);
}

int func_0205f990(Unk020c3fd4 *m) {
    return 1;
}

void func_0205f998(Unk020c3fd4 *m) {
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = m->lists[i]; item != 0; item = item->next) {
            if (!(item->flags & 1)) {
                func_02007d30(item->unk4);
            }
        }
    }
}

void func_0205f9e4(Unk020c3fd4 *m) {
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = m->lists[i]; item != 0; item = item->next) {
            if (!(item->flags & 1)) {
                func_02007e38(item->unk4);
            }
        }
    }
}

int func_0205fa30(Unk020c3fd4 *m, Unk0205fa30Ray ray, Unk0205f098 *out) {
    func_0205f0bc(out);
    if (func_02058788(&data_020c3ba4, data_020c3ba4.map) == 0) {
        return 0;
    }
    for (Unk02061d08Item *item = m->lists[data_020c3ba4.map]; item != 0; item = item->next) {
        Unk0205ebd4 hit;
        if (func_0205ebd4(item, &ray, &hit) && !(item->def->flags & 1)) {
            func_0205f0f0(out, item);
        }
    }
    return out->unk0;
}

int func_0205fae8(Unk020c3fd4 *m, Unk0205cf00 *def, Unk0205f098 *out) {
    func_0205f0bc(out);
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = m->lists[i]; item != 0; item = item->next) {
            if (item->def == def) {
                func_0205f0f0(out, item);
            }
        }
    }
    return out->unk0;
}

int func_0205fb4c(Unk020c3fd4 *m, u32 key, Unk0205f098 *out, int map) {
    func_0205f0bc(out);
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = m->lists[i]; item != 0; item = item->next) {
            if (func_0205d340(item->def, key)) {
                if (map == -1 || map == item->func_14().pos.unk3) {
                    func_0205f0f0(out, item);
                }
            }
        }
    }
    return out->unk0;
}

Unk02061d08Item *func_0205fbf4(Unk020c3fd4 *m, u32 id) {
    if (id == 0) {
        return 0;
    }
    u32 index = id >> 24;
    if (index < 256) {
        Unk02061d08Item *item = &m->pool[index];
        if (item->id == id) {
            return item;
        }
    }
    return 0;
}

void func_0205fc2c(Unk020c3fd4 *m) {
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = m->lists[i]; item != 0;) {
            Unk02061d08Item *cur = item;
            item = item->next;
            delete cur;
        }
    }
    for (Unk02061d08Item *item = m->removed; item != 0; item = m->removed) {
        delete item;
    }
}

void func_0205fcac(Unk020c3fd4 *m, Unk02061d08Item *item) {
    int map = item->cell.pos.unk3;
    if (map < 0) {
        return;
    }
    if (map >= 41) {
        return;
    }
    func_0205fcf0(m, item);
    item->next = m->lists[map];
    m->lists[map] = item;
    if (item->next != 0) {
        item->next->prev = item;
    }
}

void func_0205fcf0(Unk020c3fd4 *m, Unk02061d08Item *item) {
    int map = item->cell.pos.unk3;
    bool valid = false;
    if (map >= 0 && map < 41) {
        valid = true;
    }
    if (item->prev == 0) {
        if (valid && m->lists[map] == item) {
            m->lists[map] = item->next;
        }
        if (m->free == item) {
            m->free = item->next;
        }
        if (m->removed == item) {
            m->removed = item->next;
        }
    } else {
        item->prev->next = item->next;
    }
    if (item->next != 0) {
        item->next->prev = item->prev;
    }
    item->next = 0;
    item->prev = 0;
}

Unk02061d08Item *func_0205fd7c(Unk020c3fd4 *m, int map) {
    if (map < 0 || map >= 41) {
        return 0;
    }
    return m->lists[map];
}

void func_0205fda0(Unk020c3fd4 *m, Unk02061d08Item *item) {
    if (item == 0) {
        return;
    }
    if (item->flags & 0x400) {
        return;
    }
    func_0205fcf0(m, item);
    item->flags |= 0x400;
    item->next = m->removed;
    if (item->next != 0) {
        item->next->prev = item;
    }
    m->removed = item;
}

void func_0205fde4(Unk020c3fd4 *m) {
    bool freed = false;
    func_0205f990(m);
    for (Unk02061d08Item *item = m->removed; item != 0;) {
        if (item->unk10 == 0) {
            Unk02061d08Item *next = item->next;
            if (m->removed == item) {
                m->removed = next;
            }
            delete item;
            item = next;
            freed = true;
        } else {
            item = item->next;
        }
    }
    if (freed && func_02058788(&data_020c3ba4, data_020c3ba4.map) != 0) {
        /* The original reads the map twice: volatile read, a hypothesis. */
        int map = *(volatile s8 *)&data_020c3ba4.map;
        func_020581f4(func_02058788(&data_020c3ba4, data_020c3ba4.map), 6);
        func_020585a0(&data_020c3ba4, map);
    }
    func_0205f990(m);
}

void func_0205fea0(Unk020c3fd4 *m, int key) {
    for (int i = 0; i < 41; i++) {
        for (Unk02061d08Item *item = func_0205fd7c(m, i); item != 0;) {
            Unk02061d08Item *next = item->next;
            Unk02061c04 runner(item);
            if (item->def->script->func_020957ec(key)) {
                runner.func_02099ce0(key);
            }
            item = next;
        }
    }
}

void func_0205ff28(Unk020c3fd4 *m, int key) {
    for (Unk02061d08Item *item = func_0205fd7c(m, data_020c3ba4.map); item != 0;) {
        Unk02061d08Item *cur = item;
        item = item->next;
        Unk02061c04 runner(cur);
        if (cur->def->script->func_020957ec(key)) {
            runner.func_02099ce0(key);
        }
    }
}

void func_0205ffa4(Unk020c3fd4 *m, Unk020a4c4c *save) {
    func_0205f990(m);
    func_020a4d78(save, 2);
    int *header = func_020a4c60(save, 8, 1);
    if (header == 0) {
        header[0] = m->unkb8;
    }
    header[1] = 41;
    for (int i = 0; i < 41; i++) {
        func_020a4d78(save, 2);
        Unk02061d08Item *item;
        int *count = func_020a4c60(save, 4, 1);
        for (item = m->lists[i]; item != 0; item = item->next) {
            if (!(item->flags & 0x400)) {
                (*count)++;
                u32 index = item->id >> 24;
                func_020a4dc4(save, &index, 4);
                func_0205ed90(item, save);
            }
        }
    }
}

void func_02060080(Unk020c3fd4 *m, Unk020a4c4c *save) {
    func_020a4d2c(save, 2);
    int *header = func_020a4ce0(save, 8);
    m->free = 0;
    for (int i = 0; i < 256; i++) {
        m->pool[i].prev = 0;
        m->pool[i].next = 0;
        m->pool[i].func_setFlag(0x800, true);
    }
    for (int i = 0; i < 41; i++) {
        m->lists[i] = 0;
        func_020a4d2c(save, 2);
        int j;
        int *count = func_020a4ce0(save, 4);
        for (j = 0; j < *count; j++) {
            int index;
            func_020a4e14(save, &index, 4);
            m->pool[index].func_setFlag(0x800, false);
            m->free = &m->pool[index];
            new Unk02061d08Item(save);
        }
    }
    m->unkb8 = header[0];
    for (int i = 0; i < 256; i++) {
        if (m->pool[i].func_flag(0x800)) {
            m->pool[i].func_setFlag(0x800, false);
            m->pool[i].next = m->free;
            if (m->free != 0) {
                m->free->prev = &m->pool[i];
            }
            m->free = &m->pool[i];
        }
    }
    func_0205f990(m);
    Unk020c3ba4 *world = &data_020c3ba4;
    for (Unk02061d08Item *item = func_0205fd7c(m, world->map); item != 0; item = item->next) {
        func_0205e3f0(item);
    }
    func_020585a0(world, world->map);
}

}
