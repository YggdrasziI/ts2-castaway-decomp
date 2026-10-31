/*
 * Unit 0x02007C98-0x020080C0: the list of actions of an object: a singly linked list
 * with insertion, removal and iteration helpers, and the creation of a linked pair of
 * actions. Bounds: hypothesis (after the destructor at 0x02007C84, up to the first
 * action of the next file; no data of its own). Layouts come from the code; all names
 * are placeholders.
 */
#include "game/unk_script.h"

class Unk02007c98Node {
public:
    virtual ~Unk02007c98Node();

    u32 flags;
    u8 unk8[8];
    void *list;
    Unk02007c98Node *next;
    Unk02007c98Node *link;
    int unk1c;
};

struct Unk02007c98List {
    u8 unk0[8];
    Unk02007c98Node *current;
    Unk02007c98Node *head;
};

extern "C" {
extern u8 data_020be184[];
Unk02007c98Node *func_02007340(void *pool, int kind);
void func_020072ec(void *pool, Unk02007c98Node *n);
bool func_02002490(Unk02007c98Node *n);
void func_020026d0(Unk02007c98Node *n);
void func_02002784(Unk02007c98Node *n);

void func_02007d04(void *pool, Unk02007c98Node *n);
Unk02007c98Node *func_02007fc0(Unk02007c98List *l, Unk02007c98Node *n, bool free);
void func_02007e48(Unk02007c98List *l, Unk02007c98Node *n);
void func_02007ea4(Unk02007c98List *l, Unk02007c98Node *n);
void func_02007f00(Unk02007c98List *l, Unk02007c98Node *n, Unk02007c98Node *before);
bool func_02008080(Unk02007c98List *l, Unk02007c98Node *n);
void func_020080ac(Unk02007c98List *l, Unk02007c98Node *n);
void func_020080b4(Unk02007c98List *l, Unk02007c98Node *n);

Unk02007c98Node *func_02007c98(void *pool, int kind, int linked) {
    Unk02007c98Node *a = func_02007340(pool, kind);
    if (a == 0) {
        return 0;
    }
    Unk02007c98Node *b = func_02007340(pool, linked);
    if (b == 0) {
        func_02007d04(pool, a);
        return 0;
    }
    a->link = b;
    a->flags |= 0x400;
    b->link = a;
    b->flags |= 4;
    return a;
}

void func_02007d04(void *pool, Unk02007c98Node *n) {
    n->~Unk02007c98Node();
    func_020072ec(pool, n);
}

void func_02007d30(Unk02007c98List *l) {
    Unk02007c98Node *n = l->head;
    while (n != 0) {
        if (n->flags & 0x100) {
            n = func_02007fc0(l, n, true);
        } else {
            if (func_02002490(n)) {
                n->flags |= 0x100;
            }
            return;
        }
    }
}

void func_02007d94(Unk02007c98List *l) {
    for (Unk02007c98Node *n = l->head; n != 0; n = n->next) {
        func_02002784(n);
    }
}

bool func_02007dbc(Unk02007c98List *l) {
    for (Unk02007c98Node *n = l->head; n != 0; n = n->next) {
        if (n->flags & 0x40) {
            return false;
        }
    }
    return true;
}

int func_02007dec(Unk02007c98List *l) {
    int count = 0;
    for (Unk02007c98Node *n = l->head; n != 0; n = n->next) {
        count++;
    }
    return count;
}

void func_02007e10(Unk02007c98List *l) {
    for (Unk02007c98Node *n = l->head; n != 0; n = n->next) {
        func_020026d0(n);
    }
}

void func_02007e38(Unk02007c98List *l) {
    l->head = 0;
    l->current = 0;
}

void func_02007e48(Unk02007c98List *l, Unk02007c98Node *n) {
    if (n == 0) {
        return;
    }
    if (func_02008080(l, n)) {
        return;
    }
    func_020080ac(l, n);
    Unk02007c98Node *t = l->head;
    if (t == 0) {
        l->head = n;
        return;
    }
    while (t->next != 0) {
        t = t->next;
    }
    t->next = n;
}

void func_02007ea4(Unk02007c98List *l, Unk02007c98Node *n) {
    if (n == 0) {
        return;
    }
    if (func_02008080(l, n)) {
        return;
    }
    n->next = l->head;
    l->head = n;
    func_020080ac(l, n);
}

void func_02007edc(Unk02007c98List *l, Unk02007c98Node *n, int v) {
    n->unk1c = v;
    func_02007ea4(l, n);
}

void func_02007eec(Unk02007c98List *l, Unk02007c98Node *n, int v, Unk02007c98Node *before) {
    n->unk1c = v;
    func_02007f00(l, n, before);
}

void func_02007f00(Unk02007c98List *l, Unk02007c98Node *n, Unk02007c98Node *before) {
    if (n == 0) {
        return;
    }
    if (func_02008080(l, n)) {
        return;
    }
    Unk02007c98Node *p = l->head;
    if (p == before) {
        n->next = p;
        l->head = n;
        func_020080ac(l, n);
        return;
    }
    Unk02007c98Node *q = p->next;
    while (q != before) {
        if (q == 0) {
            break;
        }
        p = q;
        q = q->next;
    }
    if (q == before) {
        n->next = q;
        p->next = n;
        func_020080ac(l, n);
    }
}

void func_02007f84(Unk02007c98List *l, Unk02007c98Node *n, Unk02007c98Node *after) {
    Unk02007c98Node *t;
    for (t = l->head; t != 0 && t != after; t = t->next) {
    }
    if (t == 0 || (after = t->next) == 0) {
        func_02007e48(l, n);
    } else {
        func_02007f00(l, n, after);
    }
}

Unk02007c98Node *func_02007fc0(Unk02007c98List *l, Unk02007c98Node *n, bool free) {
    Unk02007c98Node *p = l->head;
    if (p == 0) {
        return 0;
    }
    Unk02007c98Node *next = n->next;
    if (p == n) {
        l->head = next;
        n->next = 0;
    } else {
        Unk02007c98Node *q = p->next;
        while (q != n) {
            if (p == 0) {
                return 0;
            }
            p = q;
            q = q->next;
        }
        if (q != n) {
            return 0;
        }
        p->next = q->next;
        n->next = 0;
    }
    func_020080b4(l, n);
    if (free) {
        func_020072ec(data_020be184, n);
    }
    return next;
}

void func_02008064(Unk02007c98List *l, Unk02007c98Node *n) {
    if (n == 0) {
        return;
    }
    if (l->current == 0 || l->current == n) {
        l->current = n;
    }
}

bool func_02008080(Unk02007c98List *l, Unk02007c98Node *n) {
    for (Unk02007c98Node *t = l->head; t != 0; t = t->next) {
        if (t == n) {
            return true;
        }
    }
    return false;
}

void func_020080ac(Unk02007c98List *l, Unk02007c98Node *n) {
    n->list = l;
}

void func_020080b4(Unk02007c98List *l, Unk02007c98Node *n) {
    n->list = 0;
}
}
