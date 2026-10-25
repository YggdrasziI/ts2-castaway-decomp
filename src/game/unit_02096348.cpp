/*
 * Unit 0x02096348-0x02096A74: a resource file class (Unk02096348) derived from the
 * file class of 0x02094xxx (Unk0209487c, vtable data_020bd348), and a node handle
 * (Unk0209674c). The file caches the blocks 0x40 (entry list), 0x41 (hashed
 * names), 0x45 (nodes) and 0x46 (0x8C-byte records); entries point into the
 * blocks 0x42 to 0x44 by type. Nodes have a name hash, a child list and a data
 * entry index.
 *
 * Bounds: hypothesis. Before 0x02096348 lie the destructors of the class with
 * vtable data_020bd52c, which close another file; the destructors 0x02096A44
 * and 0x02096A58 close this one, and 0x02096A74 starts the system
 * set-up. The vtable data_020bd54c is only used by the constructor. Real file name
 * unknown.
 */

#include "game/unk_file.h"

extern "C" u32 func_0209a32c(const u32 *str, u32 last, u32 end);
extern "C" u32 func_0209a3c4(u32 hash, const u32 *str);

struct Unk02096348Block40 {
    u32 count;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 nodeCount;
};

struct Unk02096348Entry {
    u32 hash;
    u32 offset : 24;
    u32 type : 8;
};

struct Unk02096348Record {
    u8 unk0[0x84];
    int count;
    int base;
};

struct Unk02096348Node {
    u32 hash;
    u32 children;
    u16 childCount;
    short entry;
};

class Unk0209674c;

class Unk02096348 : public Unk0209487c {
public:
    Unk02096348(void *data);
    ~Unk02096348();
    Unk02096348Block40 *func_0209638c();
    Unk02096348Entry *func_020963b4();
    Unk02096348Record *func_020963dc();
    Unk02096348Node *func_02096404();
    u32 func_0209642c();
    u32 func_02096444();
    int func_0209645c(const u32 *name, int sub);
    bool func_02096538(int index, u32 type);
    u8 *func_02096564(int index);
    int func_02096574(int index);
    int func_02096590(int index);
    int func_020965ac(int index);
    bool func_020965c8(int index);
    Unk02096348Entry *func_0209661c(int index);
    u8 *func_0209665c(int index, u32 type);
    Unk02096348Record *func_02096700(int index);
    Unk0209674c func_02096980();
    Unk02096348Node *func_020969b8(int index);
    int func_02096a00(int index, u32 n);

    Unk02096348Block40 *block40;
    Unk02096348Entry *block41;
    Unk02096348Record *block46;
    Unk02096348Node *block45;
    int lastIndex;
    u32 lastHash;
    u32 hashSeed;
};

class Unk0209674c {
public:
    Unk0209674c();
    Unk0209674c(Unk02096348 *file, Unk02096348Node *node, int index);
    Unk0209674c func_02096774(u32 n) const;
    int func_020967ec() const;
    u32 func_02096800() const;
    bool func_02096814(u32 hash) const;
    bool func_0209683c(const u32 *name) const;
    bool func_02096864() const;
    int func_0209688c() const;
    int func_020968a0() const;
    int func_020968d8() const;
    int func_02096910() const;
    bool func_02096948() const;

    int index;
    Unk02096348Node *node;
    Unk02096348 *file;
};

Unk02096348::Unk02096348(void *data) : Unk0209487c(data) {
    block40 = 0;
    block41 = 0;
    block46 = 0;
    block45 = 0;
    lastIndex = -1;
    lastHash = 0;
    hashSeed = 0;
}

Unk02096348Block40 *Unk02096348::func_0209638c() {
    if (block40 != 0) {
        return block40;
    }
    block40 = (Unk02096348Block40 *)func_02094d4c(0x40);
    return block40;
}

Unk02096348Entry *Unk02096348::func_020963b4() {
    if (block41 != 0) {
        return block41;
    }
    block41 = (Unk02096348Entry *)func_02094d4c(0x41);
    return block41;
}

Unk02096348Record *Unk02096348::func_020963dc() {
    if (block46 != 0) {
        return block46;
    }
    block46 = (Unk02096348Record *)func_02094d4c(0x46);
    return block46;
}

Unk02096348Node *Unk02096348::func_02096404() {
    if (block45 != 0) {
        return block45;
    }
    block45 = (Unk02096348Node *)func_02094d4c(0x45);
    return block45;
}

u32 Unk02096348::func_0209642c() {
    Unk02096348Block40 *b = func_0209638c();
    if (b == 0) {
        return 0;
    }
    return b->count;
}

u32 Unk02096348::func_02096444() {
    Unk02096348Block40 *b = func_0209638c();
    if (b == 0) {
        return 0;
    }
    return b->nodeCount;
}

int Unk02096348::func_0209645c(const u32 *name, int sub) {
    Unk02096348Entry *e;
    int count;
    u32 hash;
    int i;

    e = func_020963b4();
    if (e == 0) {
        return -1;
    }
    count = func_0209642c();
    hash = func_0209a3c4(hashSeed, name);
    if (hash == lastHash && lastIndex != -1 && sub == -1) {
        return lastIndex;
    }
    for (i = 0; i < count; i++) {
        if (e->hash == hash) {
            lastHash = hash;
            lastIndex = i;
            if (sub != -1) {
                Unk02096348Record *r = func_02096700(i);
                if (sub < 0 || sub >= r->count) {
                    return -1;
                }
                return r->base + sub;
            }
            return i;
        }
        e++;
    }
    return -1;
}

bool Unk02096348::func_02096538(int index, u32 type) {
    Unk02096348Entry *e = func_0209661c(index);
    if (e == 0) {
        return false;
    }
    return type == e->type;
}

u8 *Unk02096348::func_02096564(int index) {
    return func_0209665c(index, 0);
}

int Unk02096348::func_02096574(int index) {
    int *p = (int *)func_0209665c(index, 1);
    if (p != 0) {
        return *p;
    }
    return 0;
}

int Unk02096348::func_02096590(int index) {
    int *p = (int *)func_0209665c(index, 5);
    if (p != 0) {
        return *p;
    }
    return 0;
}

int Unk02096348::func_020965ac(int index) {
    int *p = (int *)func_0209665c(index, 2);
    if (p != 0) {
        return *p;
    }
    return 0;
}

bool Unk02096348::func_020965c8(int index) {
    Unk02096348Entry *e = func_0209661c(index);
    u32 *p = (u32 *)func_0209665c(index, 3);
    if (p == 0) {
        return false;
    }
    return (*p & (1 << (e->offset & 0x1f))) != 0;
}

Unk02096348Entry *Unk02096348::func_0209661c(int index) {
    int count = func_0209642c();
    Unk02096348Entry *e;

    if (index < 0 || index >= count) {
        return 0;
    }
    e = func_020963b4();
    if (e != 0) {
        return &e[index];
    }
    return 0;
}

u8 *Unk02096348::func_0209665c(int index, u32 type) {
    Unk02096348Entry *e = func_0209661c(index);
    int tag;
    u8 *block;
    int offset;

    if (e == 0) {
        return 0;
    }
    if (type != e->type) {
        return 0;
    }
    tag = -1;
    switch (e->type) {
    case 1:
    case 2:
    case 5:
        tag = 0x43;
        break;
    case 0:
    case 4:
        tag = 0x44;
        break;
    case 3:
        tag = 0x42;
        break;
    }
    block = (u8 *)func_02094d4c(tag);
    if (block == 0) {
        return 0;
    }
    offset = e->offset;
    if (tag == 0x42) {
        offset = (offset & ~0x1f) >> 3;
    }
    return block + offset;
}

Unk02096348Record *Unk02096348::func_02096700(int index) {
    Unk02096348Record *r = func_020963dc();
    int count = func_0209642c();

    if (r == 0) {
        return 0;
    }
    if (index < 0 || index >= count) {
        return 0;
    }
    return &r[index];
}

Unk0209674c::Unk0209674c() {
    index = -1;
    node = 0;
    file = 0;
}

Unk0209674c::Unk0209674c(Unk02096348 *file, Unk02096348Node *node, int index) {
    this->index = index;
    this->node = node;
    this->file = file;
}

Unk0209674c Unk0209674c::func_02096774(u32 n) const {
    int child;

    if (node == 0) {
        return Unk0209674c();
    }
    if (node->childCount == 0) {
        return Unk0209674c();
    }
    if (n >= node->childCount) {
        return Unk0209674c();
    }
    child = file->func_02096a00(index, n);
    return Unk0209674c(file, file->func_020969b8(child), child);
}

int Unk0209674c::func_020967ec() const {
    if (node != 0) {
        return node->childCount;
    }
    return 0;
}

u32 Unk0209674c::func_02096800() const {
    if (node != 0) {
        return node->hash;
    }
    return 0;
}

bool Unk0209674c::func_02096814(u32 hash) const {
    if (node != 0) {
        return node->hash == hash;
    }
    return false;
}

bool Unk0209674c::func_0209683c(const u32 *name) const {
    return func_02096814(func_0209a32c(name, 0, 0));
}

bool Unk0209674c::func_02096864() const {
    if (node != 0) {
        return node->entry >= 0;
    }
    return false;
}

int Unk0209674c::func_0209688c() const {
    if (node != 0) {
        return node->entry;
    }
    return -1;
}

int Unk0209674c::func_020968a0() const {
    int entry = func_0209688c();
    if (entry == -1) {
        return 0;
    }
    if (file == 0) {
        return 0;
    }
    return file->func_02096574(entry);
}

int Unk0209674c::func_020968d8() const {
    int entry = func_0209688c();
    if (entry == -1) {
        return 0;
    }
    if (file == 0) {
        return 0;
    }
    return file->func_02096590(entry);
}

int Unk0209674c::func_02096910() const {
    int entry = func_0209688c();
    if (entry == -1) {
        return 0;
    }
    if (file == 0) {
        return 0;
    }
    return file->func_020965ac(entry);
}

bool Unk0209674c::func_02096948() const {
    int entry = func_0209688c();
    if (entry == -1) {
        return false;
    }
    if (file == 0) {
        return false;
    }
    return file->func_020965c8(entry);
}

Unk0209674c Unk02096348::func_02096980() {
    Unk02096348Node *root = func_02096404();
    if (root == 0) {
        return Unk0209674c();
    }
    return Unk0209674c(this, root, 0);
}

Unk02096348Node *Unk02096348::func_020969b8(int index) {
    Unk02096348Node *n = func_02096404();
    int count;

    if (n == 0) {
        return 0;
    }
    count = func_02096444();
    if (index < 0 || index >= count) {
        return 0;
    }
    return &n[index];
}

int Unk02096348::func_02096a00(int index, u32 n) {
    Unk02096348Node *node = func_020969b8(index);

    if (node == 0) {
        return 0;
    }
    if (n >= node->childCount) {
        return 0;
    }
    return ((int *)((u8 *)func_02096404() + node->children))[n];
}

Unk02096348::~Unk02096348() {}
