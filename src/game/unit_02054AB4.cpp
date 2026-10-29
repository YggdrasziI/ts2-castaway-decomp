/*
 * Unit 0x02054AB4-0x02055118: the inventory server Unk020bfc9c, one static
 * object data_020bfc9c ("cInventoryServer" in its debug strings). It holds a
 * word (1000 after Initialise(), checked and changed by the cost of an object
 * definition when an object is added or removed) and 1000 entries of 16 bytes
 * (an object definition, a count, a word and a link used by the lists of
 * Unk020547f8). It adds, finds and removes objects, fills a list with the
 * objects matching keys of their scripts, and saves / loads its state.
 *
 * Bounds: hypothesis. Initialise() 0x02054AB4 opens the range: the functions
 * before it (lists of Unk020547f8 and of data_020bfc80, entry save / load) are
 * built by the static initializer 0x020AD210, which comes before this unit's
 * static initializer (0x020AD244) in `.init`. The initializer builds
 * data_020bfc9c and registers its destructor (chain node 0x020BFC90); the
 * entry constructor and destructor emitted after the destructor are the inline
 * ones it passes to __cxa_vec_ctor. The survival guide unit (0x02055118)
 * follows. `.data` is the two debug strings, `.bss` the chain node and the
 * object, up to the `.bss` of the survival guide unit. The two autoload list
 * words of BuildInfo (0x02000B64) are addresses inside this `.bss` (0x020C1100,
 * 0x020C1118): their relocations target data_020bfc9c plus an offset. Real file
 * name unknown.
 *
 * Functions other than the constructor and destructors keep C linkage: other
 * files call them by their addresses.
 */

typedef unsigned long u32;

class Unk020956f8 {
public:
    bool func_02095b08(int key);
    void *func_02095a3c(int key);
    void *func_02095ab0();
};

class Unk0206b630 {
public:
    bool func_0206b630(int value);
};

/* An object definition: only the id at 0x0C and the script at 0x10 are used here. */
struct Unk0205cf00 {
    int unk0[3];
    int unkc;
    Unk020956f8 *script;
};

/*
 * A run of 8-byte script values (block 0x404 layout). func_02054dfc re-reads
 * count at every loop test; volatile gives that reload.
 */
struct Unk02054dfcRun {
    int unk0;
    short start;
    volatile short count;
};

struct Unk02054dfcValue {
    int key;
    int value;
};

/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4;

/* The game settings (data_020d60c8): only the fields used here. */
struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
};

/* A save stream. */
struct Unk020a4c4c;

/* An inventory entry (16 bytes). */
class Unk02054dc4 {
public:
    Unk02054dc4() : def(0), count(0), unk8(0) {}
    ~Unk02054dc4() {}

    Unk0205cf00 *def;
    int count;
    int unk8;
    Unk02054dc4 *next;
};

/* A list of inventory entries linked by their next field (constructor 0x020547F8). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk02054dc4 *head;
    int count;
};

class Unk020bfc9c {
public:
    Unk020bfc9c() : unk0(0) {}
    ~Unk020bfc9c();

    int unk0;
    Unk02054dc4 entries[1000];
};

extern Unk020c3fc4 data_020c3fc4;
extern Unk020d60c8 data_020d60c8;
extern unsigned char data_020bfc68[];
extern unsigned char data_020bfc80[];

extern "C" {

void func_020897b4(const char *fmt, ...);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
void func_0205359c(Unk0205cf00 *def);
int func_0205465c(void *p, Unk0205cf00 *def, int a);
void func_020548b0(void *list, Unk0205cf00 *def, int delta);
void func_0205483c(Unk020547f8 *list, Unk02054dc4 *e);
void func_020548a0(Unk020547f8 *list);
void func_02054734(Unk02054dc4 *e, Unk020a4c4c *save);
void func_02054788(Unk02054dc4 *e, Unk020a4c4c *save);
void func_020a4d78(Unk020a4c4c *save, int version);
int *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4d2c(Unk020a4c4c *save, int version);
int *func_020a4ce0(Unk020a4c4c *save, int size);

void func_02054ab4(Unk020bfc9c *p);
void func_02054b30(Unk020bfc9c *p);
Unk02054dc4 *func_02054b50(Unk020bfc9c *p);
int func_02054b80(Unk020bfc9c *p, Unk0205cf00 *def, int a);
int func_02054c1c(Unk020bfc9c *p, Unk0205cf00 *def, int a);
void func_02054cb4(Unk020bfc9c *p, int id, Unk020547f8 *list);
void func_02054cf0(Unk020bfc9c *p, Unk02054dc4 *e, Unk020547f8 *list);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
int func_02054dfc(Unk020bfc9c *p, Unk0205cf00 *def, int remove);
void func_02054ebc(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min);
void func_02054f40(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min);
int func_02054fbc(Unk020bfc9c *p, Unk02054dc4 *e, const int *keys, u32 n, u32 min);
void func_0205501c(Unk020bfc9c *p, Unk020a4c4c *save);
void func_0205507c(Unk020bfc9c *p, Unk020a4c4c *save);

}

Unk020bfc9c data_020bfc9c;

void func_02054ab4(Unk020bfc9c *p) {
    func_020897b4("cInventoryServer::Initialise()");
    for (u32 i = 0; i < 1000; i++) {
        p->entries[i].def = 0;
        p->entries[i].count = 0;
        p->entries[i].unk8 = 0;
        p->entries[i].next = 0;
    }
    for (u32 j = 0; j < 999; j++) {
        p->entries[j].next = &p->entries[j + 1];
    }
    p->entries[999].next = 0;
    p->unk0 = 1000;
}

void func_02054b30(Unk020bfc9c *p) {
    func_020897b4("cInventoryServer::Release()");
    p->unk0 = 0;
}

Unk02054dc4 *func_02054b50(Unk020bfc9c *p) {
    for (int i = 0; i < 1000; i++) {
        if (p->entries[i].count == 0) {
            return &p->entries[i];
        }
    }
    return 0;
}

int func_02054b80(Unk020bfc9c *p, Unk0205cf00 *def, int a) {
    if (!func_02054dfc(p, def, 1)) {
        return 0;
    }
    Unk02054dc4 *e = func_02054b50(p);
    if (e == 0) {
        return 0;
    }
    e->def = def;
    e->count = 1;
    e->unk8 = a;
    e->next = 0;
    func_020548b0(data_020bfc80, def, 1);
    if (data_020d60c8.collection->func_0206b630(def->unkc)) {
        func_0205465c(data_020bfc68, def, 1);
        func_0205359c(def);
    }
    return 1;
}

int func_02054c1c(Unk020bfc9c *p, Unk0205cf00 *def, int a) {
    bool add = true;
    if (a == 0) {
        Unk02054dc4 *e = p->entries;
        for (int i = 0; i < 1000; i++, e++) {
            if (e->count != 0 && e->unk8 == 0 && e->def == def) {
                func_020548b0(data_020bfc80, def, 1);
                e->count++;
                add = false;
                break;
            }
        }
    }
    if (!add) {
        return 1;
    }
    return func_02054b80(p, def, a);
}

void func_02054cb4(Unk020bfc9c *p, int id, Unk020547f8 *list) {
    func_02054cf0(p, func_02054dc4(p, func_0205f6f8(&data_020c3fc4, id), 0), list);
}

void func_02054cf0(Unk020bfc9c *p, Unk02054dc4 *e, Unk020547f8 *list) {
    func_02054dfc(p, e->def, 0);
    func_020548b0(data_020bfc80, e->def, -1);
    if (--e->count > 0) {
        return;
    }
    if (list != 0) {
        Unk02054dc4 *prev = 0;
        for (Unk02054dc4 *n = list->head; n != 0; n = n->next) {
            if (n == e) {
                if (prev == 0) {
                    list->head = n->next;
                } else {
                    prev->next = n->next;
                }
                list->count--;
                break;
            }
            prev = n;
        }
    }
    e->def = 0;
    e->count = 0;
    e->unk8 = 0;
    e->next = 0;
}

void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min) {
    if (min > n) {
        min = n;
    }
    if (out->head == 0) {
        func_02054ebc(p, out, keys, n, min);
    } else {
        func_02054f40(p, out, keys, n, min);
    }
}

Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a) {
    Unk02054dc4 *e = p->entries;
    for (int i = 0; i < 1000; i++, e++) {
        if (e->count != 0 && e->def == def) {
            return e;
        }
    }
    return 0;
}

int func_02054dfc(Unk020bfc9c *p, Unk0205cf00 *def, int remove) {
    Unk02054dfcRun *run = (Unk02054dfcRun *)def->script->func_02095a3c(0x22d6e5e0);
    if (run == 0) {
        return 1;
    }
    Unk02054dfcValue *values = (Unk02054dfcValue *)def->script->func_02095ab0() + run->start;
    for (u32 i = 0; i < run->count; i++) {
        if (values[i].key == 0x75e0ef33) {
            Unk02054dfcValue *v = &values[i];
            if (remove) {
                if (p->unk0 < v->value) {
                    return 0;
                }
                p->unk0 -= v->value;
                return 1;
            }
            p->unk0 += v->value;
            return 1;
        }
    }
    return 1;
}

void func_02054ebc(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min) {
    out->~Unk020547f8();
    int i;
    Unk02054dc4 *e = p->entries;
    for (i = 0; i < 1000; i++, e++) {
        if (e->count != 0) {
            if (min == 0 || func_02054fbc(p, e, keys, n, min)) {
                func_0205483c(out, e);
            }
        }
    }
}

void func_02054f40(Unk020bfc9c *p, Unk020547f8 *out, const int *keys, u32 n, u32 min) {
    Unk02054dc4 *e = out->head;
    func_020548a0(out);
    while (e != 0) {
        Unk02054dc4 *next = e->next;
        e->next = 0;
        if (min == 0 || func_02054fbc(p, e, keys, n, min)) {
            func_0205483c(out, e);
        }
        e = next;
    }
}

int func_02054fbc(Unk020bfc9c *p, Unk02054dc4 *e, const int *keys, u32 n, u32 min) {
    u32 i;
    u32 hits;
    int found = 0;
    i = 0;
    hits = 0;
    for (; i < n; i++) {
        if (e->def->script->func_02095b08(keys[i])) {
            if (++hits == min) {
                found = 1;
                break;
            }
        }
    }
    return found;
}

void func_0205501c(Unk020bfc9c *p, Unk020a4c4c *save) {
    func_020a4d78(save, 2);
    int *b = func_020a4c60(save, 4, 1);
    if (b == 0) {
        return;
    }
    *b = p->unk0;
    for (int i = 0; i < 1000; i++) {
        func_02054734(&p->entries[i], save);
    }
}

void func_0205507c(Unk020bfc9c *p, Unk020a4c4c *save) {
    func_020a4d2c(save, 2);
    int *b = func_020a4ce0(save, 4);
    if (b == 0) {
        return;
    }
    p->unk0 = *b;
    for (int i = 0; i < 1000; i++) {
        func_02054788(&p->entries[i], save);
    }
}

Unk020bfc9c::~Unk020bfc9c() {}
