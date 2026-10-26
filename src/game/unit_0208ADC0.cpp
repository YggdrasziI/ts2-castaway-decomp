/*
 * Unit 0x0208ADC0-0x0208B41C: a set of 0x24-byte elements (Unk0208adc0, classes in
 * include/game/unk_matset.h). The set is filled from the blocks of a resource
 * file seen through the interface Unk020bd014 (count, 0x34-byte records and the
 * data block their offsets point into) or copied from another set; its array is
 * allocated on the heap kept in data_020c7d28. Elements are read by index or by
 * id (word 0x18) and their packed words and halves are set from game code.
 *
 * Bounds: hypothesis. Before 0x0208ADC0 lie the functions of the 0x40-byte
 * objects of unit_0208B554.cpp, which hold a set at 0x20 (func_0208ad80 is the
 * last one); 0x0208B41C starts unit_0208B41C.cpp. .bss: data_020c7d28, set only by
 * func_0208b40c, between the .bss of those objects (0x020C7D24) and of
 * unit_0208B554.cpp. Real file name unknown.
 */

#include "game/unk_matset.h"
#include "game/unk_blocks.h"

typedef unsigned char u8;

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
void func_02099b84(const void *src, void *dest, u32 size);
void func_01ff9180(Unk0208adc0 *set, int id, Unk0208af38 *e);
}

int data_020c7d28;

static inline u16 func_rgb555(const s16 *rgb) {
    int r = rgb[0];
    int g = rgb[1];
    int b = rgb[2];
    if (r > 0xff) {
        r = 0xff;
    }
    if (r < 0) {
        r = 0;
    }
    if (g > 0xff) {
        g = 0xff;
    }
    if (g < 0) {
        g = 0;
    }
    if (b > 0xff) {
        b = 0xff;
    }
    if (b < 0) {
        b = 0;
    }
    return (r >> 3) + ((g >> 3) << 5) + ((b >> 3) << 10);
}

Unk0208adc0::Unk0208adc0() : scale(0x1000, 0x1000, 0x1000) {
    count = 0;
    elems = 0;
    flags = 0;
}

Unk0208adc0::~Unk0208adc0() {
    func_0208b020();
}

void Unk0208adc0::func_0208adf8(Unk020bd014 *src) {
    if (elems != 0) {
        func_0208b020();
    }
    count = src->func_02095520();
    scale = Unk0208adc0Scale(0x1000, 0x1000, 0x1000);
    if (count == 0) {
        elems = 0;
    } else {
        func_02099afc(data_020c7d28);
        elems = new Unk0208af38[count];
        func_02099b28();
    }
    Unk0208af38 *e = elems;
    if (e == 0) {
        return;
    }
    int n = count;
    Unk0208adf8Record *rec = (Unk0208adf8Record *)src->func_020954f8();
    u8 *data = (u8 *)src->func_020954b4();
    while (n-- != 0) {
        e->unk0 = *(u32 *)(data + rec->offset0);
        e->unk4 = *(u32 *)(data + rec->offset4);
        e->unk8 = *(u32 *)(data + rec->offset8);
        e->unk0c = rec->unk30 << 16;
        e->unk10 = 0;
        e->unk14 = rec->unk2c;
        e->unk18 = rec->id;
        rec++;
        e++;
    }
}

void Unk0208adc0::func_0208af70(const Unk0208adc0 &o) {
    if (elems != 0) {
        func_0208b020();
    }
    count = o.count;
    scale = o.scale;
    if (count == 0) {
        elems = 0;
    } else {
        func_02099afc(data_020c7d28);
        elems = new Unk0208af38[count];
        func_02099b28();
    }
    flags = (flags & ~2) | (o.flags & 2);
    if (elems == 0) {
        return;
    }
    func_02099b84(o.elems, elems, count * sizeof(Unk0208af38));
}

void Unk0208adc0::func_0208b020() {
    if (elems != 0 && !(flags & 1)) {
        delete[] elems;
    }
    flags = 0;
    elems = 0;
    count = 0;
}

int Unk0208adc0::func_0208b058() {
    return count;
}

bool Unk0208adc0::func_0208b060(int id) {
    int n = count;
    Unk0208af38 *e = elems;
    while (n-- != 0) {
        if (e->unk18 == id) {
            return true;
        }
        e++;
    }
    return false;
}

int Unk0208adc0::func_0208b09c(int index) {
    if (index < 0 || index >= count) {
        return 0;
    }
    return elems[index].unk18;
}

Unk0208af38 Unk0208adc0::func_0208b0cc(int id) {
    int n = count;
    Unk0208af38 *e = elems;
    while (n-- != 0) {
        if (e->unk18 == id) {
            return *e;
        }
        e++;
    }
    return Unk0208af38();
}

Unk0208af38 Unk0208adc0::func_0208b190(int index) {
    if (index < 0 || index >= count) {
        return Unk0208af38();
    }
    return elems[index];
}

void Unk0208adc0::func_0208b248(Unk0208af38 *e) {
    func_01ff9180(this, e->unk18, e);
}

void Unk0208af38::func_0208b25c(u32 value) {
    unk8 = (unk8 & ~0x3f000000) | ((value << 24) & 0x3f000000);
}

void Unk0208af38::func_0208b278(u32 value) {
    unk8 = (unk8 & ~0x1f0000) | ((value << 16) & 0x1f0000);
}

void Unk0208af38::func_0208b294(const s16 *rgb) {
    unk4 = (unk4 & 0x8000ffff) | (func_rgb555(rgb) << 16);
}

void Unk0208af38::func_0208b308(const s16 *rgb) {
    unk0 = (unk0 & ~0x7fff) | func_rgb555(rgb);
}

void Unk0208af38::func_0208b378(const s16 *rgb) {
    unk0 = (unk0 & 0x8000ffff) | (func_rgb555(rgb) << 16);
}

void Unk0208af38::func_0208b3ec(int value) {
    unk14 = value;
}

void Unk0208af38::func_0208b3f4(s16 a, s16 b) {
    unk20 = a;
    unk22 = b;
}

void Unk0208af38::func_0208b400(s16 a, s16 b) {
    unk1c = a;
    unk1e = b;
}

void Unk0208adc0::func_0208b40c(int heap) {
    data_020c7d28 = heap;
}
