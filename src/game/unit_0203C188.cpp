/*
 * Unit 0x0203C188-0x0203C2E8: the screen base Unk0203c188
 * (include/game/unk_screen.h, vtable 0x020B9604): its constructor, its
 * destructors, the default func_08 (once the system no longer lists the
 * screen, it clears its flag 4 and lists it again) and func_18 (sets flag 4);
 * then func_0203c254, which copies six colours of the palette file 0xA0F588A4
 * (a pair of rows picked by `value`) into palette `index` of an OAM.
 *
 * Bounds: hypothesis. The start is the constructor, after the functions of the
 * class with vtable 0x020B95B4; 0x0203C2E8 starts the screen with vtable
 * 0x020B9658, the first code to call this constructor. func_0203c254 is put
 * here because it sits before that constructor; other screens call it.
 * `.data` is data_020b95f8, set by the static initializer 0x020AD18C
 * (`.init` / `.ctor`), then the vtable with its header (pure slots 3, 4, 14
 * and 15 are null). The word belongs here rather than to the previous file:
 * mwccarm puts the const object before the vtable of its own file.
 * Real file name unknown.
 *
 * The inline slots of the class are kept in far files (see the header):
 * declared non-inline, they are not emitted here.
 */

#include "game/unk_screen.h"
#include "game/unk_oam.h"

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* A 16-entry table and its length (unit_020B8888.cpp). */
struct Unk020be374 {
    int *table;
    int count;
};

extern Unk020d6240 data_020d6240;
extern Unk020be374 data_020be37c;

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_0203c254(int value, int index, int main);
}

/*
 * Set by the static initializer and never read: a const object with a
 * dynamic initializer, which mwccarm puts in `.data` before the vtable.
 */
extern const int data_020b95f8 = data_020be37c.count;

Unk0203c188::Unk0203c188(Unk0203c188Owner *owner) : flags(0) {
    this->owner = owner;
}

Unk0203c188::~Unk0203c188() {}

void Unk0203c188::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0203c188::func_18() {
    flags |= 4;
}

void func_0203c254(int value, int index, int main) {
    Unk02093648 *archive = func_020a18e4()->archive;
    Unk0209487c *file = archive->func_02093a9c(archive->func_02093e9c(0xa0f588a4));
    Unk020916a4::func_02091840(main)->func_0209201c((Unk02095140 *)file, 0, (value >> 1) * 16 + 3 + (value % 2) * 6,
                                                    index * 16 + 1, 6);
    archive->func_02093c3c(file);
}
