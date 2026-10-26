/*
 * Unit 0x0208C050-0x0208D304: texture entries and their manager. An entry
 * (Unk0208c050, 0x2C bytes) keeps a texture resource file (Unk02095fdc), the
 * container it came from, its TEXIMAGE_PARAM word and two blocks of the texture
 * (heap 4) and palette (heap 5) VRAM heaps; it allocates them, copies the texel
 * and palette data to VRAM, and reads or writes the palette. The manager
 * (Unk020c7f48, one static object data_020c7f48 returned by func_0208c578) owns
 * the array of entries, a binary search tree (Unk0208d254) from a file key to
 * the entry index, and a per-frame list of slots (Unk0208c630) of the entries in
 * use.
 *
 * Bounds: hypothesis. Before 0x0208C050 lie the two empty functions and the two
 * accessors of unit_0208BE3C.cpp; 0x0208D304 starts unit_0208D304.cpp. __sinit_020ae2e4 builds data_020c7f48
 * and registers func_0208c5ac as its destructor (chain node data_020c7f3c). Real
 * file name unknown.
 *
 * The tree functions emitted out of line after func_0208c700 (func_0208c90c ...
 * func_0208c9b4) are inline functions defined after that function: it calls them
 * (hypothesis from the emission order). The other searches inline a second copy
 * of the lookup defined in the class body (find), and the tree's constructor is an
 * inline one calling the initializer func_0208d254: the same tree code as in
 * unit_0208A0A8.cpp.
 * Not complete: func_0208c700 does not match yet (see above it).
 */

#include "game/unk_archive.h"
#include "game/unk_heap.h"

struct Unk02095fdcBlock1 {
    u32 unk0;
    int unk4;
};

class Unk02095fdc : public Unk0209487c {
public:
    Unk02095fdc(void *data);
    ~Unk02095fdc();
    Unk02095fdcBlock1 *func_02096014();
    void *func_0209603c();
    u32 func_02096064();
    void *func_0209608c();
    int func_020960d4();

    Unk02095fdcBlock1 *block1;
    void *block3;
    void *block2;
    u32 block2Size;
    u32 flags;
};

extern "C" {
Unk020c8440 *func_020999e8(int id);
void *func_020993b0(Unk020c8440 *heap, u32 size, Unk02099210Handle *handle);
void func_02099654(Unk020c8440 *heap, Unk02099210Handle *handle);
u32 func_020997a4(Unk020c8440 *heap);
void func_0207914c();
void func_020791a4(const void *data, u32 offset, u32 size);
void func_02079218();
void func_02079260();
void func_020792d0(const void *data, u32 offset, u32 size);
void func_02079434();
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
}

/* One texture (0x2C bytes). */
class Unk0208c050 {
public:
    Unk0208c050();
    void func_0208c084(Unk02095fdc *file, int key, Unk02093648 *container, bool flag);
    int func_0208c0f4();
    u32 func_0208c110();
    int func_0208c134();
    int func_0208c16c();
    int func_0208c184();
    int func_0208c19c();
    int func_0208c1a4();
    void func_0208c208();
    void func_0208c260();
    void func_0208c2d8();
    void func_0208c348();
    void func_0208c398();
    void func_0208c3e0();
    void func_0208c434();
    int func_0208c48c(u16 *dest, int count);
    void func_0208c50c(const u16 *src, int start, int count);

    int format() { return (param & 0x1c000000) >> 26; }

    int texOffset;
    int plttOffset;
    Unk02099210Handle texBlock;
    Unk02099210Handle plttBlock;
    Unk02095fdc *file;
    Unk02093648 *container;
    u32 param;
    int key;
    s16 refs;
    s16 flags;
};

/* One texture in use this frame (0x1C bytes). */
struct Unk0208c630 {
    Unk0208c630() {
        entry = 0;
        texData = 0;
        texSize = 0;
        texOffset = 0;
        plttData = 0;
        plttSize = 0;
        plttOffset = 0;
    }

    Unk0208c050 *entry;
    void *texData;
    u32 texSize;
    int texOffset;
    void *plttData;
    u32 plttSize;
    int plttOffset;
};

/* A node of the search tree: key and child indices (-1: none). */
struct Unk0208d2ec {
    Unk0208d2ec() {
        key = 0;
        left = -1;
        right = -1;
    }
    inline void func_0208c90c();
    inline Unk0208d2ec &operator=(const Unk0208d2ec &other);

    int key;
    int left;
    int right;
};

/* Binary search tree from a key to a value, nodes in an array (0x1C bytes). */
class Unk0208d254 {
public:
    Unk0208d254(u32 capacity) {
        func_0208d254(capacity);
    }
    ~Unk0208d254();
    Unk0208d254 &func_0208d254(u32 capacity);
    inline void func_0208c924(int from, int to);
    inline int func_0208c9b4(int key);

    int find(int key) {
        int i;
        Unk0208d2ec *node;

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
        Unk0208d2ec *node;
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

    Unk0208d2ec *nodes;
    int *values;
    int count;
    u32 capacity;
    bool owner;
    int cacheKey;
    int cacheIndex;
};

struct Unk0208cdc4Result {
    Unk0208cdc4Result(int first, int count) {
        this->first = first;
        this->count = count;
    }

    int first;
    int count;
};

/* The texture manager (0x1C bytes). */
class Unk020c7f48 {
public:
    Unk020c7f48();
    ~Unk020c7f48();
    void func_0208c5c0();
    void func_0208c654();
    void func_0208c700(int id);
    void func_0208ca24();
    void func_0208ca84(int capacity);
    void func_0208ca9c(int capacity);
    void func_0208caa8(int id);
    Unk0208c050 *func_0208cc70(int id);
    int func_0208ccc0(int key);
    Unk0208cdc4Result func_0208cdc4(Unk02093648 *container, bool load);
    int func_0208cec4(Unk02095fdc *file, bool load);
    int func_0208cefc(Unk02095fdc *file, int key, bool load);
    int func_0208cf6c(Unk02095fdc *file, Unk02093648 *container, int key, bool flag);
    int func_0208d1b0(int id);

    bool isValid(int id) {
        if (id < 0 || id >= entryCapacity) {
            return false;
        }
        return entries[id].key != 0;
    }

    Unk0208c050 *entries;
    Unk0208c630 *slots;
    int slotCapacity;
    int entryCapacity;
    int entryCount;
    int slotCount;
    Unk0208d254 *map;
};

Unk020c7f48 data_020c7f48;

Unk0208c050::Unk0208c050() {
    texOffset = -1;
    plttOffset = -1;
    texBlock.ptr = 0;
    plttBlock.ptr = 0;
    file = 0;
    container = 0;
    param = 0;
    key = 0;
    refs = 0;
    flags = 0;
}

void Unk0208c050::func_0208c084(Unk02095fdc *file, int key, Unk02093648 *container, bool flag) {
    if (key == 0 || file == 0) {
        return;
    }
    this->file = file;
    file->func_02094f9c();
    this->container = container;
    flags = 0;
    if (flag) {
        flags |= 1;
    }
    texOffset = -1;
    plttOffset = -1;
    refs = 0;
    this->key = key;
    param = this->file->func_02096014()->unk0;
}

int Unk0208c050::func_0208c0f4() {
    if (file == 0) {
        return 0;
    }
    return file->func_02094f88();
}

u32 Unk0208c050::func_0208c110() {
    if (texOffset != -1) {
        return param | ((u32)(texOffset << 13) >> 16);
    }
    return param;
}

int Unk0208c050::func_0208c134() {
    if (plttOffset != -1) {
        return plttOffset >> (format() == 2 ? 3 : 4);
    }
    return 0;
}

int Unk0208c050::func_0208c16c() {
    return 8 << ((param & 0x700000) >> 20);
}

int Unk0208c050::func_0208c184() {
    return 8 << ((param & 0x3800000) >> 23);
}

int Unk0208c050::func_0208c19c() {
    return key;
}

int Unk0208c050::func_0208c1a4() {
    switch (format()) {
    case 4:
        return 0x200;
    case 1:
        return 0x40;
    case 6:
        return 0x10;
    case 2:
        return 8;
    case 3:
        return 0x20;
    }
    return 0;
}

void Unk0208c050::func_0208c208() {
    if (texOffset != -1) {
        return;
    }
    if (file == 0) {
        return;
    }
    func_0208c260();
    func_0208c3e0();
    if (format() == 7) {
        return;
    }
    func_0208c2d8();
    func_0208c434();
}

void Unk0208c050::func_0208c260() {
    u32 size;
    Unk020c8440 *heap;
    void *block;

    if (texOffset != -1) {
        return;
    }
    if (file == 0) {
        return;
    }
    if (file->func_0209603c() == 0) {
        return;
    }
    size = file->func_02096064();
    texOffset = -1;
    heap = func_020999e8(4);
    block = func_020993b0(heap, size, &texBlock);
    if (block == 0) {
        return;
    }
    texOffset = (u32)block - func_020997a4(heap);
}

void Unk0208c050::func_0208c2d8() {
    void *data;
    u32 size;
    Unk020c8440 *heap;
    void *block;

    if (file == 0) {
        return;
    }
    data = file->func_0209608c();
    size = file->func_02094ddc(3);
    plttOffset = -1;
    if (data == 0) {
        return;
    }
    heap = func_020999e8(5);
    block = func_020993b0(heap, size, &plttBlock);
    if (block == 0) {
        return;
    }
    plttOffset = (u32)block - func_020997a4(heap);
}

void Unk0208c050::func_0208c348() {
    if (texOffset >= 0) {
        func_02099654(func_020999e8(4), &texBlock);
    }
    if (plttOffset >= 0) {
        func_02099654(func_020999e8(5), &plttBlock);
    }
    texOffset = -1;
    plttOffset = -1;
}

void Unk0208c050::func_0208c398() {
    if (file != 0) {
        file->func_02094fb8();
        if (container != 0) {
            container->func_02093c58(container->func_02093f5c(file));
        }
    }
    file = 0;
    container = 0;
}

void Unk0208c050::func_0208c3e0() {
    void *data;
    u32 size;

    if (texOffset == -1) {
        return;
    }
    data = file->func_0209603c();
    size = file->func_02096064();
    if (data == 0) {
        return;
    }
    func_02079434();
    func_020792d0(data, texOffset, size);
    func_02079260();
}

void Unk0208c050::func_0208c434() {
    void *data;
    u32 size;

    if (plttOffset == -1) {
        return;
    }
    data = file->func_0209608c();
    size = file->func_02094ddc(3);
    if (data == 0) {
        return;
    }
    func_02079218();
    func_020791a4(data, plttOffset, size);
    func_0207914c();
}

int Unk0208c050::func_0208c48c(u16 *dest, int count) {
    if (dest == 0) {
        return 0;
    }
    if (texOffset == -1) {
        return 0;
    }
    if (count < 0) {
        count = func_0208c1a4() >> 1;
    } else if (count > func_0208c1a4() >> 1) {
        count = func_0208c1a4() >> 1;
    }
    if (count != 0) {
        func_02079218();
        MIi_CpuCopy16(plttBlock.ptr, dest, count * 2);
        func_0207914c();
    }
    return count;
}

void Unk0208c050::func_0208c50c(const u16 *src, int start, int count) {
    int size;

    if (texOffset == -1) {
        return;
    }
    size = func_0208c1a4();
    if (count < 0) {
        count = (size >> 1) - start;
    }
    if (start < 0) {
        return;
    }
    if (start + count > size >> 1) {
        return;
    }
    if (count == 0) {
        return;
    }
    func_02079218();
    MIi_CpuCopy16(src, (u16 *)plttBlock.ptr + start, count * 2);
    func_0207914c();
}

Unk020c7f48 *func_0208c578() {
    return &data_020c7f48;
}

Unk020c7f48::Unk020c7f48() {
    entries = 0;
    slots = 0;
    slotCapacity = 0x20;
    entryCapacity = 0x100;
    entryCount = 0;
    slotCount = 0;
}

Unk020c7f48::~Unk020c7f48() {
    func_0208c654();
}

void Unk020c7f48::func_0208c5c0() {
    entries = new Unk0208c050[entryCapacity];
    entryCount = 0;
    map = new Unk0208d254(entryCapacity);
    slots = new Unk0208c630[slotCapacity];
}

void Unk020c7f48::func_0208c654() {
    Unk0208d254 *m;
    int i;

    if (slots != 0) {
        for (i = 0; i < slotCount; i++) {
            Unk0208c050 *entry = slots[i].entry;
            if (entry != 0) {
                entry->refs--;
            }
        }
        delete[] slots;
    }
    slots = 0;
    slotCount = 0;
    if (entries != 0) {
        delete[] entries;
    }
    entries = 0;
    m = map;
    if (m != 0) {
        delete m;
    }
    map = 0;
    entryCount = 0;
}

/*
 * 96.34 %: the original loads the left and right children of the removed node with
 * two ldr (here one ldmib), recomputes next * 12 after the successor loop and colors
 * the registers differently. Written as an inline tree method it was 88.7 %.
 */
void Unk020c7f48::func_0208c700(int id) {
    Unk0208d254 *m;
    int i;
    int left;
    int next;
    Unk0208c050 *entry;
    int parent;
    int last;

    if (!isValid(id)) {
        return;
    }
    entry = &entries[id];
    m = map;
    i = m->func_0208c9b4(entry->key);
    if (i >= 0) {
        left = m->nodes[i].left;
        next = m->nodes[i].right;
        if (left != -1) {
            if (next == -1) {
                next = left;
            } else {
                parent = -1;
                while (m->nodes[next].left != -1) {
                    Unk0208d2ec *n = &m->nodes[next];
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
            m->func_0208c924(i, -1);
        }
        last = --m->count;
        if (i < last) {
            m->nodes[i] = m->nodes[last];
            m->values[i] = m->values[m->count];
            m->func_0208c924(m->count, i);
            i = m->count;
        }
        m->nodes[i].func_0208c90c();
        m->values[i] = 0;
        m->cacheKey = 0;
        m->cacheIndex = -1;
    }
    entry->key = 0;
    entryCount--;
    entry->func_0208c348();
    entry->func_0208c398();
}

inline void Unk0208d2ec::func_0208c90c() {
    key = 0;
    left = -1;
    right = -1;
}

inline void Unk0208d254::func_0208c924(int from, int to) {
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

inline Unk0208d2ec &Unk0208d2ec::operator=(const Unk0208d2ec &other) {
    key = other.key;
    left = other.left;
    right = other.right;
    return *this;
}

inline int Unk0208d254::func_0208c9b4(int key) {
    int i;
    Unk0208d2ec *node;
    Unk0208d2ec *base;

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

void Unk020c7f48::func_0208ca24() {
    int i;

    for (i = 0; i < entryCapacity && entryCount > 0; i++) {
        if (entries[i].key != 0) {
            func_0208c700(i);
        }
    }
    func_0208c654();
}

void Unk020c7f48::func_0208ca84(int capacity) {
    if (capacity == 0) {
        return;
    }
    if (entries == 0) {
        entryCapacity = capacity;
    }
}

void Unk020c7f48::func_0208ca9c(int capacity) {
    if (capacity != 0) {
        slotCapacity = capacity;
    }
}

void Unk020c7f48::func_0208caa8(int id) {
    Unk0208c050 *entry;

    if (entries == 0) {
        return;
    }
    if (!isValid(id)) {
        return;
    }
    if (slotCount >= slotCapacity) {
        return;
    }
    entry = &entries[id];
    if (entry->texOffset == -1) {
        entry->func_0208c260();
        if (entry->format() != 7) {
            entry->func_0208c2d8();
        }
    }
    entry->refs++;
    if (entry->func_0208c0f4() == 0 || entry->texOffset == -1) {
        return;
    }
    slots[slotCount] = Unk0208c630();
    slots[slotCount].entry = entry;
    slots[slotCount].texData = entry->file->func_0209603c();
    slots[slotCount].texSize = entry->file->func_02096064();
    slots[slotCount].texOffset = entry->texOffset;
    if (entry->plttOffset != -1) {
        slots[slotCount].plttData = entry->file->func_0209608c();
        slots[slotCount].plttSize = entry->file->func_02094ddc(3);
        slots[slotCount].plttOffset = entry->plttOffset;
    }
    slotCount++;
}

Unk0208c050 *Unk020c7f48::func_0208cc70(int id) {
    if (!isValid(id)) {
        return 0;
    }
    return &entries[id];
}

int Unk020c7f48::func_0208ccc0(int key) {
    if (map == 0) {
        return -1;
    }
    if (!map->contains(key)) {
        return -1;
    }
    return map->get(key);
}

Unk0208cdc4Result Unk020c7f48::func_0208cdc4(Unk02093648 *container, bool load) {
    int first;
    int count;
    int index;
    Unk02095fdc *file;
    int id;

    if (container == 0) {
        return Unk0208cdc4Result(-1, 0);
    }
    container->func_020940c0(2);
    first = -1;
    count = 0;
    while (container->func_02094104()) {
        index = container->func_02094158();
        file = (Unk02095fdc *)container->func_02093a9c(index);
        id = func_0208cf6c(file, container, file->func_020960d4(), load);
        if (id != -1) {
            count++;
            if (first == -1) {
                first = id;
            }
            if (load) {
                entries[id].func_0208c208();
                entries[id].func_0208c398();
            }
        } else {
            container->func_02093c58(index);
        }
    }
    return Unk0208cdc4Result(first, count);
}

int Unk020c7f48::func_0208cec4(Unk02095fdc *file, bool load) {
    if (file == 0) {
        return -1;
    }
    return func_0208cefc(file, file->func_020960d4(), load);
}

int Unk020c7f48::func_0208cefc(Unk02095fdc *file, int key, bool load) {
    int id;

    if (file == 0) {
        return -1;
    }
    id = func_0208cf6c(file, 0, key, load);
    if (id != -1 && load) {
        entries[id].func_0208c208();
        entries[id].func_0208c398();
    }
    return id;
}

int Unk020c7f48::func_0208cf6c(Unk02095fdc *file, Unk02093648 *container, int key, bool flag) {
    int id;
    int i;

    if (entries == 0) {
        func_0208c5c0();
    }
    if (file->func_02094f88() == 0) {
        return -1;
    }
    if (key == 0) {
        return -1;
    }
    if (map->find(key) != -1) {
        return -1;
    }
    if (entryCount >= entryCapacity) {
        return -1;
    }
    id = -1;
    for (i = 0; i < entryCapacity; i++) {
        if (entries[i].func_0208c19c() == 0) {
            id = i;
            break;
        }
    }
    if (!map->insert(key, id)) {
        return -1;
    }
    entryCount++;
    entries[id].func_0208c084(file, key, container, flag);
    return id;
}

int Unk020c7f48::func_0208d1b0(int id) {
    if (!isValid(id)) {
        return 0;
    }
    return entries[id].func_0208c19c();
}

Unk0208d254::~Unk0208d254() {
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

Unk0208d254 &Unk0208d254::func_0208d254(u32 capacity) {
    Unk0208d2ec *p;
    u32 i;

    count = 0;
    this->capacity = capacity;
    owner = true;
    cacheKey = 0;
    cacheIndex = -1;
    values = new int[capacity];
    nodes = new Unk0208d2ec[capacity];
    p = nodes;
    i = this->capacity;
    while (i--) {
        p->func_0208c90c();
        p++;
    }
    return *this;
    return *this;
}
