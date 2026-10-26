/*
 * Texture types of unit_0208C050.cpp: the texture resource file (Unk02095fdc), the
 * texture entries (Unk0208c050), the slots of the textures in use (Unk0208c630),
 * the search tree (Unk0208d254) and the manager (Unk020c7f48), shared with the ITCM
 * code of unit_01FFAAC4.cpp. Layouts come from the code; all names are placeholders.
 */
#ifndef GAME_UNK_TEXTURE_H
#define GAME_UNK_TEXTURE_H

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

Unk020c7f48 *func_0208c578();

#endif
