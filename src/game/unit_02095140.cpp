/*
 * Unit 0x02095140-0x0209543C: a resource file class (Unk02095140) derived from the
 * file class Unk0209487c. Block 0x20 holds the entry count; the blocks 0x24, 0x25
 * and 0x26 hold one 8-byte entry per index, whose second word (low two bits
 * cleared) is an offset into the blocks 0x21, 0x22 and 0x23.
 *
 * Bounds: hypothesis. Before 0x02095140 lies the end of the file class code
 * (0x02094xxx); the destructors close this file and 0x0209543C starts a class with
 * two bases. The vtable data_020bd360 is only used by the constructor. Real file
 * name unknown.
 */

#include "game/unk_resource.h"

Unk02095140::Unk02095140(void *data) : Unk0209487c(data) {
    header = 0;
    block22 = 0;
    block21 = 0;
    block23 = 0;
    block24 = 0;
    block25 = 0;
    block26 = 0;
}

Unk02095140Header *Unk02095140::func_02095180() {
    if (header != 0) {
        return header;
    }
    header = (Unk02095140Header *)func_02094d4c(0x20);
    return header;
}

bool Unk02095140::func_020951a8(int index) {
    Unk02095140Header *h = func_02095180();

    if (h == 0) {
        return false;
    }
    if (index < 0 || index >= h->count) {
        return false;
    }
    return true;
}

u8 *Unk02095140::func_020951e4(int index) {
    if (block21 == 0) {
        block21 = (u8 *)func_02094d4c(0x21);
    }
    if (index != 0) {
        Unk02095140Entry *e = func_0209526c(index);
        if (e == 0) {
            return 0;
        }
        return block21 + (e->offset & ~3);
    }
    return block21;
}

u32 Unk02095140::func_02095244(int index) {
    Unk02095140Entry *e = func_0209526c(index);

    if (e != 0) {
        return e->size;
    }
    return func_02094ddc(0x21);
}

Unk02095140Entry *Unk02095140::func_0209526c(int index) {
    if (block24 == 0) {
        block24 = (Unk02095140Entry *)func_02094d4c(0x24);
    }
    if (!func_020951a8(index)) {
        return 0;
    }
    return &block24[index];
}

u8 *Unk02095140::func_020952b0(int index) {
    if (block22 == 0) {
        block22 = (u8 *)func_02094d4c(0x22);
    }
    if (index != 0) {
        Unk02095140Entry *e = func_02095310(index);
        if (e == 0) {
            return 0;
        }
        return block22 + (e->offset & ~3);
    }
    return block22;
}

Unk02095140Entry *Unk02095140::func_02095310(int index) {
    if (block25 == 0) {
        block25 = (Unk02095140Entry *)func_02094d4c(0x25);
    }
    if (!func_020951a8(index)) {
        return 0;
    }
    return &block25[index];
}

u8 *Unk02095140::func_02095354(int index) {
    if (block23 == 0) {
        block23 = (u8 *)func_02094d4c(0x23);
    }
    if (block23 != 0) {
        Unk02095140Entry *e = func_020953b4(index);
        if (e != 0) {
            return block23 + (e->offset & ~3);
        }
    }
    return block23;
}

Unk02095140Entry *Unk02095140::func_020953b4(int index) {
    if (block26 == 0) {
        block26 = (Unk02095140Entry *)func_02094d4c(0x26);
    }
    if (block26 == 0 || !func_020951a8(index)) {
        return 0;
    }
    return &block26[index];
}

Unk02095140::~Unk02095140() {}
