/*
 * Unit 0x0208BE3C-0x0208C050: a set of transforms (Unk0208be3c) read from a
 * resource file (Unk02095d1c, count from block 0x11). It allocates, on the heap
 * given to the constructor, one entry per item (Unk0208be3cEntry: position,
 * rotation quaternion and 4x4 matrix) and one more 4x4 matrix per item, all set to
 * the identity.
 *
 * Bounds: hypothesis. The function before 0x0208BE3C (func_0208be28) belongs to
 * the object pool of unit_0208B554.cpp; 0x0208C050 starts unit_0208C050.cpp. The
 * two empty functions 0x0208C038 / 0x0208C03C are the inline element constructors
 * passed to __cxa_vec_new. Real file name unknown.
 */

#include "game/unk_file.h"
#include "game/unk_xform.h"

class Unk02095d1c : public Unk0209487c {
public:
    Unk02095d1c(void *data);
    ~Unk02095d1c();
    int func_02095d70();
};

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
}

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

void Unk0208be3c::func_0208befc() {
    int n = count;
    func_02099afc(heap);
    entries = new Unk0208be3cEntry[n];
    mtxs = new Unk0208be3cMtx[n];
    func_02099b28();
    Unk0208be3cEntry *entry = entries;
    Unk0208be3cMtx *mtx = mtxs;
    while (n-- != 0) {
        Unk0208be3cPos pos(0, 0, 0);
        Unk020988d8 rot;
        entry->pos = pos;
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
