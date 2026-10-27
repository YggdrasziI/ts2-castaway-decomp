/*
 * Unit 0x0206B77C-0x0206BCE0: Unk0206b8cc, a timed queue. Its nodes
 * (Unk0206b95c) are allocated as one array and kept on a free list; each one
 * holds an item id, a key, a due time and an order. func_0206b998 queues an
 * item, func_0206ba1c drops the nodes of an item, func_0206bae4 advances the
 * 15-bit clock and runs up to four due nodes (func_0205ece8 on the item found
 * by id), func_0206bbdc / func_0206bc48 save and load the queue.
 *
 * Bounds: hypothesis. 0x0206B77C (sorted insert) is the first function using
 * the node layout; the functions before it work on a sorted array of 0x1404
 * bytes. 0x0206BCE0 starts unit_0206BCE0.cpp. Real file name unknown.
 */

#include "game/unk_queue.h"

typedef unsigned char u8;

class Unk0206bcf0Item {
public:
    u8 unk0[0x2c];
    int unk2c;
};

/* A saved node (func_0206b828 / func_0206b87c). */
struct Unk0206b828Rec {
    u16 time;
    u16 order;
    int id;
    int key;
};

/* The saved queue header (func_0206bbdc / func_0206bc48). */
struct Unk0206bbdcRec {
    s16 count;
    s16 time;
};

extern "C" {
void func_020a4d78(Unk020a4c4c *save, int a);
void func_020a4d2c(Unk020a4c4c *save, int a);
void *func_020a4c60(Unk020a4c4c *save, int size, int a);
void *func_020a4ce0(Unk020a4c4c *save, int size);
Unk0206bcf0Item *func_0205fbf4(void *list, int id);
void func_0205ece8(Unk0206bcf0Item *item, int key);
}

extern u8 data_020c3fd4[];

static inline Unk0206b95c *pop(Unk0206b95c **list) {
    Unk0206b95c *node = *list;
    if (node != 0) {
        *list = node->next;
        node->next = 0;
    }
    return node;
}

/* True when b comes after a. */
static inline bool later(const Unk0206b95c *a, const Unk0206b95c *b) {
    bool r = true;
    if (b->time <= a->time) {
        if (b->time != a->time || b->order <= a->order) {
            r = false;
        }
    }
    return r;
}

Unk0206b95c *Unk0206b95c::func_0206b77c(Unk0206b95c *node) {
    if (later(this, node)) {
        Unk0206b95c *prev = this;
        Unk0206b95c *cur = next;
        while (cur != 0 && later(cur, node)) {
            prev = cur;
            cur = cur->next;
        }
        node->next = prev->next;
        prev->next = node;
        return this;
    }
    node->next = this;
    return node;
}

void Unk0206b95c::func_0206b828(Unk020a4c4c *save) {
    func_020a4d78(save, 2);
    Unk0206b828Rec *rec = (Unk0206b828Rec *)func_020a4c60(save, sizeof(Unk0206b828Rec), 1);
    if (rec != 0) {
        rec->time = time;
        rec->order = order;
        rec->id = id;
        rec->key = key;
    }
}

void Unk0206b95c::func_0206b87c(Unk020a4c4c *save) {
    func_020a4d2c(save, 2);
    Unk0206b828Rec *rec = (Unk0206b828Rec *)func_020a4ce0(save, sizeof(Unk0206b828Rec));
    if (rec != 0) {
        time = rec->time;
        order = rec->order;
        id = rec->id;
        key = rec->key;
    }
}

static inline void release(Unk0206b8cc *q, Unk0206b95c *node) {
    node->reset();
    node->next = q->free;
    q->free = node;
}

static inline void insert(Unk0206b8cc *q, Unk0206b95c *node) {
    if (q->head == 0) {
        q->head = node;
    } else {
        q->head = q->head->func_0206b77c(node);
    }
}

Unk0206b8cc::Unk0206b8cc(int count) : nodes(0), count(count), head(0), free(0), time(0) {
    nodes = new Unk0206b95c[this->count];
    for (int i = this->count - 1; i >= 0; i--) {
        release(this, &nodes[i]);
    }
}

Unk0206b8cc::~Unk0206b8cc() {
    delete[] nodes;
    nodes = 0;
}

void Unk0206b8cc::func_0206b998(const Unk0206b998Req *req) {
    if (req->item == 0) {
        return;
    }
    Unk0206b95c *node = pop(&free);
    if (node == 0) {
        return;
    }
    u16 now = time;
    node->id = req->item->unk2c;
    node->key = req->key;
    node->time = req->delay + now;
    node->order = req->order;
    insert(this, node);
}

void Unk0206b8cc::func_0206ba1c(const Unk0206bcf0Item *item) {
    Unk0206b95c *node;
    for (node = head; node != 0; node = head) {
        if (node->id != item->unk2c) {
            break;
        }
        release(this, pop(&head));
    }
    Unk0206b95c *cur;
    if (node == 0 || (cur = node->next) == 0) {
        return;
    }
    do {
        if (cur->id != item->unk2c) {
            node = cur;
            cur = cur->next;
        } else {
            Unk0206b95c *next = cur->next;
            node->next = next;
            release(this, cur);
            cur = next;
        }
    } while (cur != 0);
}

void Unk0206b8cc::func_0206bae4() {
    time++;
    if (time > 0x7fff) {
        time &= 0x7fff;
        for (Unk0206b95c *node = head; node != 0; node = node->next) {
            if (node->time > 0x7fff) {
                node->time &= 0x7fff;
            } else {
                node->time = 0;
            }
        }
    }
    Unk0206b95c *node;
    for (int n = 4; n > 0 && (node = head) != 0 && time >= node->time; n--) {
        node = pop(&head);
        if (node != 0) {
            Unk0206bcf0Item *item = func_0205fbf4(data_020c3fd4, node->id);
            if (item != 0) {
                func_0205ece8(item, node->key);
            }
            release(this, node);
        }
    }
}

void Unk0206b8cc::func_0206bbdc(Unk020a4c4c *save) {
    Unk0206b95c *node;
    func_020a4d78(save, 2);
    Unk0206bbdcRec *rec = (Unk0206bbdcRec *)func_020a4c60(save, sizeof(Unk0206bbdcRec), 1);
    if (rec == 0) {
        return;
    }
    rec->time = time;
    for (node = head; node != 0; node = node->next) {
        rec->count++;
        node->func_0206b828(save);
    }
}

void Unk0206b8cc::func_0206bc48(Unk020a4c4c *save) {
    int i;
    func_020a4d2c(save, 2);
    Unk0206bbdcRec *rec = (Unk0206bbdcRec *)func_020a4ce0(save, sizeof(Unk0206bbdcRec));
    if (rec == 0) {
        return;
    }
    time = rec->time;
    for (i = 0; i < rec->count; i++) {
        Unk0206b95c *node = pop(&free);
        node->func_0206b87c(save);
        insert(this, node);
    }
}
