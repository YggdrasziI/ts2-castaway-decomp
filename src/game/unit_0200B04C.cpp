/*
 * Unit 0x0200B04C-0x0200B23C: the sprite animation `Unk0200b04c`. Bounds: hypothesis
 * (from its constructor to the first helper of the next code). Start, stop and step
 * are written as plain functions; methods are as likely (hypothesis). Layouts come
 * from the code; all names are placeholders.
 */
#include "game/unk_file.h"
#include "game/unk_resource.h"
#include "game/unk_fishing.h"

extern "C" {
void func_0200b120(Unk0200b04c *a);
int func_0200b09c(Unk0200b04c *a, Unk02095140 *file);
int func_0200b150(Unk0200b04c *a, int f);
}

Unk0200b04c::Unk0200b04c() : frame(0), mode(0), loops(0), cur(0), file(0) {
    func_set_dir(UNK_0200B04C_UP);
}

Unk0200b04c::~Unk0200b04c() {
    func_0200b120(this);
}

extern "C" int func_0200b09c(Unk0200b04c *a, Unk02095140 *file) {
    if (a->file != 0) {
        func_0200b120(a);
    }
    Unk02095140 *p;
    a->file = file;
    p = a->file;
    if (p == 0) {
        return 0;
    }
    p->func_02094f9c();
    a->count = a->file->func_02095180()->count;
    a->cur = a->func_start();
    a->frame = 0;
    a->loops = 0;
    a->playing.v |= 1;
    return a->cur;
}

extern "C" void func_0200b120(Unk0200b04c *a) {
    if (a->file != 0) {
        a->file->func_02094fb8();
        a->file = 0;
        a->playing.v &= ~1;
    }
}

extern "C" int func_0200b150(Unk0200b04c *a, int f) {
    if (!a->playing.func_get()) {
        return 0;
    }
    if (a->frame == 3) {
        Unk0200b04cDir next = a->func_dir() == UNK_0200B04C_UP ? UNK_0200B04C_DOWN : UNK_0200B04C_UP;
        int cur = a->cur;
        if (cur == a->func_end(next)) {
            if (a->mode & 2) {
                a->playing.v ^= 2;
            }
            if (a->mode & 1) {
                a->cur = a->func_start();
                a->loops++;
            } else {
                func_0200b120(a);
            }
        } else {
            a->cur += next == UNK_0200B04C_DOWN ? 1 : -1;
        }
        a->frame = 0;
    } else {
        a->frame++;
    }
    return a->cur;
}
