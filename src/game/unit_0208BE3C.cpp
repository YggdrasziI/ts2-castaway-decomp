/*
 * Unit 0x0208BE3C-0x0208C050: a set of transforms (Unk0208be3c) read from a
 * resource file (Unk02095d1c, count from block 0x11). It allocates, on the heap
 * given to the constructor, one entry per item (Unk0208be3cEntry: position,
 * rotation quaternion and 4x4 matrix) and one more 4x4 matrix per item, all set to
 * the identity.
 *
 * Bounds: hypothesis. The function before 0x0208BE3C (func_0208be28) works on
 * another object (fields 0x18 and 0x3C); 0x0208C050 starts unit_0208C050.cpp. The
 * two empty functions 0x0208C038 / 0x0208C03C are the inline element constructors
 * passed to __cxa_vec_new. Real file name unknown.
 * Not complete: func_0208befc does not match yet (comment above it).
 */

#include "game/unk_file.h"
#include "game/unk_matrix.h"

class Unk02095d1c : public Unk0209487c {
public:
    Unk02095d1c(void *data);
    ~Unk02095d1c();
    int func_02095d70();
};

class Unk020988d8 {
public:
    Unk020988d8() {}
    void func_020988d8();

    int x;
    int y;
    int z;
    int w;
};

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
}

/* One matrix of the second array (0x40 bytes). */
struct Unk0208be3cMtx {
    Unk0208be3cMtx() {}

    Unk02098094 m;
};

/* One transform (0x5C bytes). */
struct Unk0208be3cEntry {
    Unk0208be3cEntry() {}

    Unk02098ff0 pos;
    Unk020988d8 rot;
    Unk02098094 mtx;
};

class Unk0208be3c {
public:
    Unk0208be3c(Unk02095d1c *file, u16 heap);
    ~Unk0208be3c();
    void func_0208befc();
    int func_0208c040();
    Unk0208be3cMtx *func_0208c048();

    Unk0208be3cEntry *entries;
    Unk0208be3cMtx *mtxs;
    Unk02095d1c *file;
    int count;
    u16 unk10;
    u16 heap;
};

Unk0208be3c::Unk0208be3c(Unk02095d1c *file, u16 heap) {
    entries = 0;
    mtxs = 0;
    this->file = file;
    count = 0;
    unk10 = 0;
    this->heap = heap;
    if (this->file == 0) {
        return;
    }
    if (!this->file->func_02094d18()) {
        return;
    }
    count = this->file->func_02095d70();
    func_0208befc();
}

Unk0208be3c::~Unk0208be3c() {
    if (entries != 0) {
        delete[] entries;
    }
    entries = 0;
    if (mtxs != 0) {
        delete[] mtxs;
    }
    mtxs = 0;
    if (file != 0) {
        file->func_02094fb8();
        file = 0;
    }
}

/*
 * 92.28 %: the original builds the zero position in a stack temporary (0x94) and
 * copies it with one ldm / stm; here the three zeros are stored straight into the
 * entry, so the frame is 0xC bytes smaller and the registers shift. An aggregate
 * temporary keeps the frame but is copied member by member (91.58 %); named
 * temporaries, inline return / setter helpers, casts and plain or derived member
 * types were tried.
 */
void Unk0208be3c::func_0208befc() {
    int n = count;
    func_02099afc(heap);
    entries = new Unk0208be3cEntry[n];
    mtxs = new Unk0208be3cMtx[n];
    func_02099b28();
    Unk0208be3cEntry *entry = entries;
    Unk0208be3cMtx *mtx = mtxs;
    while (n-- != 0) {
        Unk02098ff0 pos(0, 0, 0);
        entry->pos = pos;
        Unk020988d8 rot;
        rot.func_020988d8();
        entry->rot = rot;
        entry->mtx = Unk02098094::func_02098254();
        mtx->m = Unk02098094::func_02098254();
        entry++;
        mtx++;
    }
    file->func_02094f9c();
}

int Unk0208be3c::func_0208c040() {
    return count;
}

Unk0208be3cMtx *Unk0208be3c::func_0208c048() {
    return mtxs;
}
