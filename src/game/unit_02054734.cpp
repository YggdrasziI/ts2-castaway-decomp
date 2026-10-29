/*
 * Unit 0x02054734-0x02054AB4: lists of the inventory. The save / load of one
 * inventory entry (Unk02054dc4, unit_02054AB4.cpp), the list Unk020547f8 of
 * entries linked by their next field (push, clear, find by index), and the
 * static list data_020bfc80 (Unk020bfc80) of 16-byte change records: an object
 * definition and the sum of its count changes of one sign (at most 33
 * records), with a flag telling whether the object is in the collection.
 *
 * Bounds: hypothesis. The static initializer 0x020AD210 builds data_020bfc80
 * and registers its destructor 0x02054AA0 (chain node 0x020BFC84); it comes
 * between the initializers of the bulb object 0x020AD1FC (code from
 * 0x02054330, the object data_020bfc68) and of the inventory server
 * 0x020AD244 (code from 0x02054AB4). The entry save / load at the start are
 * called only by the inventory server. `.bss` is the list and the chain node.
 * Real file name unknown.
 *
 * Functions other than the constructors and destructors keep C linkage: other
 * files call them by their addresses.
 */

typedef unsigned long u32;

class Unk0206b630 {
public:
    bool func_0206b6bc(int value);
};

/* An object definition: only the id at 0x0C is used here. */
struct Unk0205cf00 {
    int unk0[3];
    int unkc;
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

/* An inventory entry (16 bytes, unit_02054AB4.cpp). */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
    int unk8;
    Unk02054dc4 *next;
};

/* A list of inventory entries linked by their next field. */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk02054dc4 *head;
    int count;
};

/* A change record of data_020bfc80 (16 bytes). */
struct Unk020548b0Node {
    Unk020548b0Node(Unk0205cf00 *d, int n) : def(d), delta(n), next(0), flags(0) {}

    Unk0205cf00 *def;
    int delta;
    Unk020548b0Node *next;
    u32 flags;
};

class Unk020bfc80 {
public:
    Unk020bfc80() : head(0) {}
    ~Unk020bfc80();

    Unk020548b0Node *head;
};

extern Unk020c3fc4 data_020c3fc4;
extern Unk020d60c8 data_020d60c8;

extern "C" {

Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
int func_0205d340(Unk0205cf00 *def, u32 key);
void func_020a4d78(Unk020a4c4c *save, int version);
int *func_020a4c60(Unk020a4c4c *save, int size, int a);
void func_020a4d2c(Unk020a4c4c *save, int version);
int *func_020a4ce0(Unk020a4c4c *save, int size);

void func_02054734(Unk02054dc4 *e, Unk020a4c4c *save);
void func_02054788(Unk02054dc4 *e, Unk020a4c4c *save);
void func_0205483c(Unk020547f8 *list, Unk02054dc4 *e);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
void func_020548a0(Unk020547f8 *list);
void func_020548b0(Unk020bfc80 *p, Unk0205cf00 *def, int delta);
void func_02054a4c(Unk020bfc80 *p);
void func_02054a70(Unk020bfc80 *p);

}

Unk020bfc80 data_020bfc80;

void func_02054734(Unk02054dc4 *e, Unk020a4c4c *save) {
    func_020a4d78(save, 2);
    int *b = func_020a4c60(save, 0xc, 1);
    if (b == 0 || e->def == 0) {
        return;
    }
    b[0] = e->def->unkc;
    b[1] = e->count;
    b[2] = e->unk8;
}

void func_02054788(Unk02054dc4 *e, Unk020a4c4c *save) {
    func_020a4d2c(save, 2);
    int *b = func_020a4ce0(save, 0xc);
    if (b == 0) {
        return;
    }
    if (b[0] != 0) {
        e->def = func_0205f6f8(&data_020c3fc4, b[0]);
        e->count = b[1];
        e->unk8 = b[2];
    } else {
        e->def = 0;
        e->count = 0;
        e->unk8 = 0;
    }
}

Unk020547f8::Unk020547f8() {
    head = 0;
    count = 0;
}

Unk020547f8::~Unk020547f8() {
    Unk02054dc4 *n = head;
    while (n != 0) {
        Unk02054dc4 *next = n->next;
        n->next = 0;
        n = next;
    }
    head = 0;
    count = 0;
}

void func_0205483c(Unk020547f8 *list, Unk02054dc4 *e) {
    e->next = list->head;
    list->head = e;
    list->count++;
}

Unk02054dc4 *func_02054858(Unk020547f8 *list, int index) {
    if (index < 0 || index >= list->count) {
        return 0;
    }
    for (Unk02054dc4 *n = list->head; n != 0; n = n->next) {
        if (index == 0) {
            return n;
        }
        index--;
    }
    return 0;
}

void func_020548a0(Unk020547f8 *list) {
    list->head = 0;
    list->count = 0;
}

void func_020548b0(Unk020bfc80 *p, Unk0205cf00 *def, int delta) {
    if (func_0205d340(def, 0x798b86ac)) {
        return;
    }
    if (func_0205d340(def, 0x69a133c5)) {
        return;
    }
    if (func_0205d340(def, 0xf3e7bb67)) {
        return;
    }
    if (p->head == 0) {
        p->head = new Unk020548b0Node(def, delta);
        if (data_020d60c8.collection->func_0206b6bc(def->unkc)) {
            p->head->flags |= 1;
        } else {
            p->head->flags &= ~1;
        }
        return;
    }
    Unk020548b0Node *n = p->head;
    int count = 0;
    for (Unk020548b0Node *c = n; c != 0; c = c->next) {
        count++;
    }
    if (count > 0x20) {
        return;
    }
    Unk020548b0Node *prev = 0;
    for (; n != 0; n = n->next) {
        if (n->def == def) {
            if ((n->delta > 0 && delta > 0) || (n->delta < 0 && delta < 0)) {
                n->delta += delta;
                return;
            }
        }
        prev = n;
    }
    prev->next = new Unk020548b0Node(def, delta);
    if (data_020d60c8.collection->func_0206b6bc(def->unkc)) {
        prev->next->flags |= 1;
    } else {
        prev->next->flags &= ~1;
    }
}

void func_02054a4c(Unk020bfc80 *p) {
    Unk020548b0Node *n = p->head;
    if (n == 0) {
        return;
    }
    p->head = n->next;
    delete n;
}

void func_02054a70(Unk020bfc80 *p) {
    while (p->head != 0) {
        Unk020548b0Node *n = p->head;
        p->head = n->next;
        delete n;
    }
}

Unk020bfc80::~Unk020bfc80() {
    func_02054a70(this);
}
