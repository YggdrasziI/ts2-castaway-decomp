/*
 * Unit 0x0208A0A8-0x0208AC48: the model library (Unk0208a0a8, one object pointed
 * to by data_020c7d24). It maps a key (word 0 of a resource file's header block) to
 * a slot holding the key, the model built from the file (Unk02089f38), the file
 * and its flags, through a binary search tree (Unk0208ab98) from the key to the
 * slot index. The slots and the tree are created with the first model and freed
 * with the last one.
 *
 * The file also defines the two reference functions of the resource file class
 * Unk0209543c (0x0208A1EC and 0x0208AA84, include/game/unk_blockfile.h).
 *
 * The tree is the same code as the one of unit_0208C050.cpp (Unk0208d254): same
 * layout, constructor, destructor and inline functions, emitted here again
 * (hypothesis: one template or header used by both files). The inline functions
 * emitted out of line after func_0208a5d8 are defined after it, as there.
 *
 * Bounds: hypothesis. Before 0x0208A0A8, func_0208a094 ends the model of
 * unit_02089F38.cpp; the inline node constructor func_0208ac30 ends this file and
 * unit_0208AC48.cpp follows. No data of its own found yet (data_020c7d24 stays in
 * the original binary). Real file name unknown.
 *
 * The tree's lookup exists twice: contains / get inline a copy defined in the class
 * body, while the removal calls func_0208aa14, defined after it. The tree's
 * constructor is an inline one that calls the initializer func_0208ab98 (which
 * returns *this): that is why func_0208a1f8 keeps the operator new result in a
 * register instead of storing the call's return value.
 * Not complete: func_0208a5d8 does not match yet (comment above it).
 */

#include "game/unk_blockfile.h"
#include "game/unk_archive.h"
#include "game/unk_model.h"

/* A node of the search tree: key and child indices (-1: none). */
struct Unk0208ac30 {
    Unk0208ac30() {
        key = 0;
        left = -1;
        right = -1;
    }
    inline void func_0208a96c();
    inline Unk0208ac30 &operator=(const Unk0208ac30 &other);

    int key;
    int left;
    int right;
};

/* Binary search tree from a key to a value, nodes in an array (0x1C bytes). */
class Unk0208ab98 {
public:
    Unk0208ab98(u32 capacity) {
        func_0208ab98(capacity);
    }
    ~Unk0208ab98();
    Unk0208ab98 &func_0208ab98(u32 capacity);
    inline void func_0208a984(int from, int to);
    inline int func_0208aa14(int key);

    int find(int key) {
        int i;
        Unk0208ac30 *node;

        if (count == 0) {
            return -1;
        }
        if (key == cacheKey) {
            return cacheIndex;
        }
        i = 0;
        node = nodes;
        do {
            if (key == node->key) {
                break;
            }
            if (key < node->key) {
                i = node->left;
            } else if (key > node->key) {
                i = node->right;
            }
            if (i != -1) {
                node = &nodes[i];
            }
        } while (i != -1);
        cacheKey = key;
        cacheIndex = i;
        return i;
    }

    bool contains(int key) { return find(key) != -1; }

    int get(int key) {
        int i = find(key);
        if (i == -1) {
            return values[0];
        }
        return values[i];
    }

    bool insert(int key, int value) {
        int i;
        Unk0208ac30 *node;
        bool left;

        if (count >= capacity) {
            return false;
        }
        i = count == 0 ? -1 : 0;
        node = i == -1 ? 0 : nodes;
        while (i != -1) {
            if (key == node->key) {
                return false;
            }
            if (key < node->key) {
                left = true;
                i = node->left;
            } else if (key > node->key) {
                i = node->right;
                left = false;
            }
            if (i != -1) {
                node = &nodes[i];
            }
        }
        if (node != 0) {
            if (left) {
                node->left = count;
            } else {
                node->right = count;
            }
        }
        nodes[count].key = key;
        values[count] = value;
        cacheKey = 0;
        cacheIndex = -1;
        count++;
        return true;
    }

    Unk0208ac30 *nodes;
    int *values;
    int count;
    u32 capacity;
    bool owner;
    int cacheKey;
    int cacheIndex;
};

/* One slot (0x10 bytes); flag 1: the library loaded the file. */
struct Unk0208a4b0 {
    Unk0208a4b0() {
        key = 0;
        model = 0;
        file = 0;
        flags = 0;
    }

    int key;
    Unk02089f38 *model;
    Unk0209543c *file;
    u32 flags;
};

class Unk0208a0a8 {
public:
    Unk0208a0a8();
    void func_0208a0c4(u32 capacity);
    void func_0208a0d4(Unk0209543c *file);
    void func_0208a108(Unk02093648 *container);
    void func_0208a158(Unk0209543c *file, int key);
    Unk0208a4b0 *func_0208a1f8(int key);
    Unk02089f38 *func_0208a4c8(int key);
    void func_0208a5d8(int key);
    void func_0208aa90(Unk0209543c *file);
    void func_0208aae0();
    bool func_0208ab28();
    static void func_0208ab3c(Unk0208a0a8 *library);

    u32 capacity;
    u32 count;
    Unk0208a4b0 *slots;
    Unk0208ab98 *map;
};

extern Unk0208a0a8 *data_020c7d24;

Unk0208a0a8::Unk0208a0a8() {
    capacity = 0x100;
    count = 0;
    slots = 0;
    map = 0;
}

void Unk0208a0a8::func_0208a0c4(u32 capacity) {
    if (map != 0) {
        this->capacity = capacity;
    }
}

void Unk0208a0a8::func_0208a0d4(Unk0209543c *file) {
    if (file == 0) {
        return;
    }
    func_0208a158(file, file->func_020955e0());
}

void Unk0208a0a8::func_0208a108(Unk02093648 *container) {
    container->func_020940c0(4);
    while (container->func_02094104()) {
        func_0208a0d4((Unk0209543c *)container->func_02094134());
    }
}

void Unk0208a0a8::func_0208a158(Unk0209543c *file, int key) {
    Unk0208a4b0 *slot;
    bool loaded;
    Unk02089f38 *model;

    if (file == 0) {
        return;
    }
    slot = func_0208a1f8(key);
    if (slot == 0) {
        return;
    }
    if (slot->file != 0) {
        return;
    }
    file->func_0208a1ec();
    loaded = false;
    if (file->func_02094f88() == 0) {
        loaded = true;
        file->func_02094df4();
    }
    model = new Unk02089f38(file);
    slot->key = key;
    slot->model = model;
    slot->file = file;
    slot->flags = loaded;
}

void Unk0209543c::func_0208a1ec() {
    func_02094f9c();
}

Unk0208a4b0 *Unk0208a0a8::func_0208a1f8(int key) {
    int index;
    u32 i;

    if (key == 0) {
        return 0;
    }
    if (map == 0) {
        map = new Unk0208ab98(capacity);
        slots = new Unk0208a4b0[capacity];
    }
    if (!map->contains(key)) {
        if (count >= capacity) {
            return 0;
        }
        index = -1;
        for (i = 0; i < capacity; i++) {
            if (slots[i].model == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return 0;
        }
        if (!map->insert(key, index)) {
            return 0;
        }
        count++;
    }
    return &slots[map->get(key)];
}

Unk02089f38 *Unk0208a0a8::func_0208a4c8(int key) {
    if (map == 0) {
        return 0;
    }
    if (!map->contains(key)) {
        return 0;
    }
    return slots[map->get(key)].model;
}

/*
 * 96.68 %: the original computes next * 12 once for the two node accesses of the
 * successor relink and loads the removed node's children with two ldr (ldmib
 * here); the registers of this, the key, the tree and the index differ with it.
 * The same tree code is 96.34 % in unit_0208C050.cpp (func_0208c700). Tried: the
 * removal as an inline tree method (95.41 %), child load order and node pointer
 * forms, and local declaration orders (this one is the best found).
 */
void Unk0208a0a8::func_0208a5d8(int key) {
    Unk0208ab98 *m;
    u32 i;
    int last;
    Unk0208a4b0 *slot;
    int next;
    int left;
    Unk02089f38 *model;
    int parent;

    if (map == 0) {
        return;
    }
    if (!map->contains(key)) {
        return;
    }
    slot = &slots[map->get(key)];
    if (!(slot->flags & 2) && slot->file == 0) {
        return;
    }
    if (slot->file != 0) {
        slot->file->func_0208aa84();
        if (slot->flags & 1) {
            slot->file->func_02094f0c();
        }
        slot->file = 0;
        model = slot->model;
        if (model != 0) {
            delete model;
        }
        slot->model = 0;
    }
    if (slot->flags & 2) {
        slot->model = 0;
        slot->file = 0;
        slot->flags = 0;
    }
    slot->key = 0;
    slot->model = 0;
    slot->file = 0;
    slot->flags = 0;
    m = map;
    i = m->func_0208aa14(key);
    if (i >= 0) {
        left = m->nodes[i].left;
        next = m->nodes[i].right;
        if (left != -1) {
            if (next == -1) {
                next = left;
            } else {
                parent = -1;
                while (m->nodes[next].left != -1) {
                    Unk0208ac30 *n = &m->nodes[next];
                    parent = next;
                    next = n->left;
                }
                if (parent == -1) {
                    m->nodes[next].left = left;
                } else {
                    m->nodes[parent].left = m->nodes[next].right;
                    m->nodes[next].left = m->nodes[i].left;
                    m->nodes[next].right = m->nodes[i].right;
                }
            }
        }
        if (next != -1) {
            m->nodes[i] = m->nodes[next];
            m->values[i] = m->values[next];
            i = next;
        } else {
            m->func_0208a984(i, -1);
        }
        last = --m->count;
        if (i < last) {
            m->nodes[i] = m->nodes[last];
            m->values[i] = m->values[m->count];
            m->func_0208a984(m->count, i);
            i = m->count;
        }
        m->nodes[i].func_0208a96c();
        m->values[i] = 0;
        m->cacheKey = 0;
        m->cacheIndex = -1;
    }
    count--;
    if (func_0208ab28()) {
        if (map != 0) {
            delete map;
        }
        if (slots != 0) {
            delete[] slots;
        }
        slots = 0;
        map = 0;
    }
}

inline void Unk0208ac30::func_0208a96c() {
    key = 0;
    left = -1;
    right = -1;
}

inline void Unk0208ab98::func_0208a984(int from, int to) {
    int i;

    for (i = 0; i < count; i++) {
        if (from == nodes[i].left) {
            nodes[i].left = to;
            return;
        }
        if (from == nodes[i].right) {
            nodes[i].right = to;
            return;
        }
    }
}

inline Unk0208ac30 &Unk0208ac30::operator=(const Unk0208ac30 &other) {
    key = other.key;
    left = other.left;
    right = other.right;
    return *this;
}

inline int Unk0208ab98::func_0208aa14(int key) {
    int i;
    Unk0208ac30 *node;
    Unk0208ac30 *base;

    if (count == 0) {
        return -1;
    }
    if (key == cacheKey) {
        return cacheIndex;
    }
    base = nodes;
    i = 0;
    node = base;
    do {
        if (key == node->key) {
            break;
        }
        if (key < node->key) {
            i = node->left;
        } else if (key > node->key) {
            i = node->right;
        }
        if (i != -1) {
            node = &base[i];
        }
    } while (i != -1);
    cacheKey = key;
    cacheIndex = i;
    return i;
}

void Unk0209543c::func_0208aa84() {
    func_02094fb8();
}

void Unk0208a0a8::func_0208aa90(Unk0209543c *file) {
    u32 i;

    if (map == 0) {
        return;
    }
    for (i = 0; i < capacity; i++) {
        if (slots[i].file == file) {
            func_0208a5d8(slots[i].key);
            return;
        }
    }
}

void Unk0208a0a8::func_0208aae0() {
    u32 i;

    for (i = 0; i < capacity && count != 0; i++) {
        if (slots[i].key != 0) {
            func_0208a5d8(slots[i].key);
        }
    }
}

bool Unk0208a0a8::func_0208ab28() {
    return count == 0;
}

void Unk0208a0a8::func_0208ab3c(Unk0208a0a8 *library) {
    if (library != 0) {
        data_020c7d24 = library;
    }
}

Unk0208ab98::~Unk0208ab98() {
    if (owner) {
        if (values != 0) {
            delete[] values;
        }
        if (nodes != 0) {
            delete[] nodes;
        }
    }
    values = 0;
    nodes = 0;
}

Unk0208ab98 &Unk0208ab98::func_0208ab98(u32 capacity) {
    Unk0208ac30 *p;
    u32 i;

    count = 0;
    this->capacity = capacity;
    owner = true;
    cacheKey = 0;
    cacheIndex = -1;
    values = new int[capacity];
    nodes = new Unk0208ac30[capacity];
    p = nodes;
    i = this->capacity;
    while (i--) {
        p->func_0208a96c();
        p++;
    }
    return *this;
}
