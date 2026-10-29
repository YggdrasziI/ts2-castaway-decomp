/*
 * Unit 0x02053408-0x0205359C: the lot file class Unk0205356c (0x50 bytes),
 * derived from the file class Unk0209487c, and its block accessors: the header
 * (block 0x100FF), the rooms (0x10100, 8 bytes each), the records of the blocks
 * 0x10107 (0x24 bytes) and 0x10108 (0x10 bytes), the first four cached in the
 * object; the tile layers (0x10101, 0x6C bytes, from a room's offset), a layer's
 * tiles (0x10102) and the objects (0x10106).
 *
 * Bounds: hypothesis. The file factory before it (0x02053204-0x02053408)
 * creates this class for the kind 3000 and ends with the implicit destructors
 * it emits; this file ends with the destructors of its class (D1 0x0205356C,
 * then D0 0x02053580: an explicit destructor defined last; the implicit one
 * links them as D0, then D1); 0x0205359C starts unit_0205359C.cpp. `.data` is
 * the vtable. Real file name unknown.
 *
 * The accessors keep C linkage: the lot code calls them by their addresses.
 */

#include "game/unk_file.h"

/* The header of a lot file (block 0x100FF). */
struct Unk02053440;

/* A room of a lot file (block 0x10100): only the layer offset is used here. */
struct Unk0205346c {
    int layerCount;
    int layers;
};

/* A tile layer of a lot file (block 0x10101, 0x6C bytes): only the tile offset. */
struct Unk0205350c {
    u8 unk0[0x68];
    u32 tiles;
};

/* A record of the blocks 0x10107 (0x24 bytes) and 0x10108 (0x10 bytes). */
struct Unk020534a0;

/* An object of a lot file (block 0x10106). */
struct Unk02053558;

class Unk0205356c : public Unk0209487c {
public:
    Unk0205356c(void *data);
    ~Unk0205356c();

    Unk02053440 *header;
    u8 *rooms;
    int unk44;
    u8 *records;
    u8 *records2;
};

extern "C" {

Unk02053440 *func_02053440(Unk0205356c *file);
Unk0205346c *func_0205346c(Unk0205356c *file, int room);
Unk020534a0 *func_020534a0(Unk0205356c *file, int index);
Unk020534a0 *func_020534d8(Unk0205356c *file, int index);
Unk0205350c *func_0205350c(Unk0205356c *file, int layer, Unk0205346c *room);
u32 *func_02053538(Unk0205356c *file, Unk0205350c *layer);
Unk02053558 *func_02053558(Unk0205356c *file);

}

Unk0205356c::Unk0205356c(void *data) : Unk0209487c(data) {
    header = 0;
    rooms = 0;
    unk44 = 0;
    records = 0;
    records2 = 0;
}

Unk02053440 *func_02053440(Unk0205356c *file) {
    if (file->header == 0) {
        file->header = (Unk02053440 *)file->func_02094d4c(0x100ff);
    }
    return file->header;
}

Unk0205346c *func_0205346c(Unk0205356c *file, int room) {
    if (file->rooms == 0) {
        file->rooms = (u8 *)file->func_02094d4c(0x10100);
    }
    return (Unk0205346c *)(file->rooms + room * 8);
}

Unk020534a0 *func_020534a0(Unk0205356c *file, int index) {
    if (file->records == 0) {
        file->records = (u8 *)file->func_02094d4c(0x10107);
    }
    return (Unk020534a0 *)(file->records + index * 0x24);
}

Unk020534a0 *func_020534d8(Unk0205356c *file, int index) {
    if (file->records2 == 0) {
        file->records2 = (u8 *)file->func_02094d4c(0x10108);
    }
    return (Unk020534a0 *)(file->records2 + index * 0x10);
}

Unk0205350c *func_0205350c(Unk0205356c *file, int layer, Unk0205346c *room) {
    u8 *layers = (u8 *)file->func_02094d4c(0x10101);
    return (Unk0205350c *)(layers + room->layers + layer * 0x6c);
}

u32 *func_02053538(Unk0205356c *file, Unk0205350c *layer) {
    u8 *tiles = (u8 *)file->func_02094d4c(0x10102);
    return (u32 *)(tiles + layer->tiles);
}

Unk02053558 *func_02053558(Unk0205356c *file) {
    return (Unk02053558 *)file->func_02094d4c(0x10106);
}

Unk0205356c::~Unk0205356c() {}
