/*
 * Unit 0x0206B4D4-0x0206B630: Unk0206b4d4, one object entry of the main screen.
 * The constructor takes an entry for the archive file 0x916074CD (palette 3,
 * priority 3, at 0x5000 / 0xA4000, frame 0) and loads its palette; the
 * destructor releases the entry and the file; func_0206b5e4 shows frame 1
 * while func_020a14d8 holds and bit 2 of the settings flags is set.
 *
 * Bounds: hypothesis. The functions before 0x0206B4D4 work on another object
 * (fields 0x24-0x88); unit_0206B630.cpp starts after func_0206b5e4. Real file
 * name unknown.
 */

#include "game/unk_icon.h"
#include "game/unk_archive.h"
#include "game/unk_oam.h"

struct Unk020d6240 {
    u8 unk0[0x14];
    Unk02093648 *archive;
};

/* The game settings (data_020d60c8): only the flags are named. */
struct Unk020d60c8 {
    u8 unk0[8];
    u32 flags;
};

extern "C" {
Unk020d6240 *func_020a18e4();
bool func_020a14d8(Unk020d6240 *system);
}

extern Unk020d60c8 data_020d60c8;

Unk0206b4d4::Unk0206b4d4() {
    entry = 0;
    Unk02093648 *archive = func_020a18e4()->archive;
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(0x916074cd));
    Unk020916a4 *manager = Unk020916a4::func_02091820();
    entry = manager->func_020919e4((int)file, 0);
    if (entry != 0) {
        entry->func_0208fb98(3);
        entry->func_0208fb80(3);
        entry->unk0 = 0x5000;
        entry->unk4 = 0xa4000;
        entry->func_0208faac(0);
        manager->func_0209201c(file, 0, 0, 0x30, 0x10);
    }
}

Unk0206b4d4::~Unk0206b4d4() {
    if (entry != 0) {
        Unk020916a4::func_02091820()->func_02091c68(entry);
        Unk02093648 *archive = func_020a18e4()->archive;
        archive->func_02093c58(archive->func_02093e9c(0x916074cd));
    }
}

void Unk0206b4d4::func_0206b5e4() {
    if (entry == 0) {
        return;
    }
    entry->func_0208faac(func_020a14d8(func_020a18e4()) == 1 && (data_020d60c8.flags & 4) ? 1 : 0);
}
