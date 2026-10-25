/*
 * Unit 0x02092640-0x02092704: an iterator (Unk02092640) over the 40-byte entries
 * of one of the two object managers (Unk020916a4 of unit_020916A4.cpp). It keeps
 * the first and the current entry and two halfwords; the second one selects the
 * manager. An entry counts while func_0208fd2c accepts it.
 *
 * Bounds: hypothesis. Before 0x02092640 lies the manager code; 0x02092704 starts unit_02092704.cpp. Real file name unknown.
 */

#include "game/unk_oam.h"

Unk02092640::Unk02092640() {
    first = 0;
    cur = 0;
    unk8 = 0;
    unkA = 0;
}

Unk02092640::Unk02092640(void *entry, int unk8, int unkA) {
    first = entry;
    cur = entry;
    this->unk8 = unk8;
    this->unkA = unkA;
}

void Unk02092640::func_0209266c() {
    cur = first;
}

void *Unk02092640::func_02092678() {
    void *e = cur;

    if (e == 0) {
        return 0;
    }
    if (unkA != 0) {
        cur = Unk020916a4::func_02091820()->func_0209250c((Unk0208f8b0 *)e);
    } else {
        cur = Unk020916a4::func_02091830()->func_0209250c((Unk0208f8b0 *)e);
    }
    if (((Unk0208f8b0 *)e)->func_0208fd2c()) {
        return e;
    }
    return 0;
}

bool Unk02092640::func_020926d4() {
    bool r = false;

    if (cur != 0) {
        if (((Unk0208f8b0 *)cur)->func_0208fd2c()) {
            r = true;
        }
    }
    return r;
}

u16 Unk02092640::func_020926fc() {
    return unk8;
}
