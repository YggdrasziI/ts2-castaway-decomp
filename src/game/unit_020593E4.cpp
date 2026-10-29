/*
 * Unit 0x020593E4-0x020599A0: the map cell position Unk020593e4 (map index,
 * two coordinates) and the tile layer Unk02056ed0 (0x2C bytes, built with
 * __cxa_vec_new by the map code at 0x02056xxx): constructor, destructor,
 * and the functions that set, test and clear the flag bits of the tiles
 * covered by a footprint ("Cell [%d,%d]=%X Mask=%x" when a tile is taken).
 *
 * Bounds: hypothesis. The cell constructor 0x020593E4 follows the object
 * groups (unit_02058EB8.cpp) and the weather effects (unit_020599A0.cpp)
 * follow the bounds test 0x02059940. `.data` holds the message above.
 * Real file name unknown.
 *
 * Functions other than the constructors and destructor keep C linkage:
 * other files call them by their addresses.
 *
 * Not complete: func_020596b8, func_02059710, func_02059828 and
 * func_020598e4 are not at 100 % (comments above them).
 */

typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef unsigned char u8;

/* The first half of a map cell. */
class Unk020593e4 {
public:
    Unk020593e4();
    Unk020593e4(s8 unk3, s8 unk2, s16 unk0);

    s16 unk0;
    s8 unk2;
    s8 unk3;
};

/* A tile position or a footprint size. */
struct Unk020593e4Xy {
    bool func_valid() const {
        return x >= 0 && y >= 0;
    }

    s16 x;
    s16 y;
};

/* The size of a tile layer. */
struct Unk02056ed0Info {
    u8 unk0[8];
    s16 width;
    s16 height;
};

/* A tile layer (0x2C bytes): one word of flags per tile. */
class Unk02056ed0 {
public:
    Unk02056ed0();
    ~Unk02056ed0();

    u32 *func_tile(int x, int y) {
        return &tiles[y * info->width + x];
    }

    u8 unk0;
    u8 unk1;
    int unk4;
    Unk02056ed0Info *info;
    int unkc;
    u32 *tiles;
    Unk020593e4 cell;
    int unk18;
    int unk1c;
    int unk20;
    u8 unk24;
    int unk28;
};

struct Unk02059514Obj {
    u8 unk0[0x17];
    s8 unk17;
};

extern "C" {

void *func_02055f34(int id);
void func_02055f6c(void *p, int width, int height, u32 *tiles);
void func_02056070(void *p, int a, int b);
void func_020562fc(Unk02056ed0 *layer, void *p);
void func_020897b4(const char *fmt, ...);

bool func_02059418(const Unk020593e4 *cell);
void func_020594d0(Unk02056ed0 *layer, int id, int a, int b);
void func_02059514(Unk02056ed0 *layer, const Unk02059514Obj *o);
void func_02059534(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 mask);
void func_02059600(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size);
void func_020596b8(Unk02056ed0 *layer, const Unk020593e4Xy *pos, u32 bit);
bool func_02059710(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 flags, u32 mask);
void func_02059828(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 flags);
void func_020598e4(Unk02056ed0 *layer, const Unk020593e4Xy *pos, u32 bit);
bool func_02059940(Unk02056ed0 *layer, const Unk020593e4Xy *pos);

}

Unk020593e4::Unk020593e4() {
    unk0 = -1;
    unk2 = -1;
    unk3 = -1;
}

Unk020593e4::Unk020593e4(s8 unk3, s8 unk2, s16 unk0) {
    this->unk0 = unk0;
    this->unk2 = unk2;
    this->unk3 = unk3;
}

bool func_02059418(const Unk020593e4 *cell) {
    if (cell->unk3 < 0 || cell->unk3 >= 41) {
        return false;
    }
    return cell->unk2 != -1 && cell->unk0 != -1;
}

Unk02056ed0::Unk02056ed0() : unk0(0), unk1(0), unk4(-1), info(0), unkc(0), tiles(0), unk18(0), unk1c(0), unk20(0), unk24(0), unk28(0) {}

Unk02056ed0::~Unk02056ed0() {
    if (tiles != 0) {
        delete[] tiles;
        tiles = 0;
    }
}

void func_020594d0(Unk02056ed0 *layer, int id, int a, int b) {
    void *p = func_02055f34(id);
    func_02055f6c(p, layer->info->width, layer->info->height, layer->tiles);
    func_02056070(p, a, b);
}

void func_02059514(Unk02056ed0 *layer, const Unk02059514Obj *o) {
    func_020562fc(layer, func_02055f34(o->unk17));
}

void func_02059534(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 mask) {
    if (!pos->func_valid()) {
        return;
    }
    if (pos->x + size->x > layer->info->width) {
        return;
    }
    if (pos->y + size->y > layer->info->height) {
        return;
    }
    int bit = 0;
    int x;
    int y;
    for (y = pos->y; y < pos->y + size->y; y++) {
        for (x = pos->x; x < pos->x + size->x; x++) {
            if (mask & (1 << bit)) {
                *layer->func_tile(x, y) |= 2;
            }
            bit++;
        }
    }
}

void func_02059600(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size) {
    if (!pos->func_valid()) {
        return;
    }
    if (pos->x + size->x > layer->info->width) {
        return;
    }
    if (pos->y + size->y > layer->info->height) {
        return;
    }
    for (int y = pos->y; y < pos->y + size->y; y++) {
        for (int x = pos->x; x < pos->x + size->x; x++) {
            *layer->func_tile(x, y) |= 4;
        }
    }
}

/* 96.82 %: the original indexes the tile with mla, ours with smlabb (the
 * coordinates and the width are shorts; tried: int locals, direct indexing,
 * a width local, a tiles local). */
void func_020596b8(Unk02056ed0 *layer, const Unk020593e4Xy *pos, u32 bit) {
    if (!func_02059940(layer, pos)) {
        return;
    }
    if (bit < 4 || bit > 11) {
        return;
    }
    *layer->func_tile(pos->x, pos->y) |= 1 << bit;
}

/* 82.86 %: ours hoists `y * width` out of the inner loop and spills the
 * start column; the original reloads the width for the tile test, keeps the
 * bounds-check width on the stack for the message and the start column in a
 * register. The single `return false` of the bounds tests comes from the
 * combined condition (71 % with separate tests). Tried: width / info locals,
 * the test and message forms, nested tests, declaration orders. */
bool func_02059710(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 flags, u32 mask) {
    if (!pos->func_valid() || pos->x + size->x > layer->info->width || pos->y + size->y > layer->info->height) {
        return false;
    }
    int x;
    int y;
    int bit = 0;
    for (y = pos->y; y < pos->y + size->y; y++) {
        for (x = pos->x; x < pos->x + size->x; x++) {
            if ((mask & (1 << bit)) && (*layer->func_tile(x, y) & flags)) {
                if (mask != 0xffffffff) {
                    func_020897b4("Cell [%d,%d]=%X Mask=%x", x, y, *layer->func_tile(x, y), mask);
                }
                return false;
            }
            bit++;
        }
    }
    return true;
}

/* 98.51 %: row and row-end registers swapped (r12 / lr); tried: a mask
 * local, flags inverted in place, x / y declared before the loops. */
void func_02059828(Unk02056ed0 *layer, const Unk020593e4Xy *pos, const Unk020593e4Xy *size, u32 flags) {
    if (!pos->func_valid()) {
        return;
    }
    if (pos->x + size->x > layer->info->width) {
        return;
    }
    if (pos->y + size->y > layer->info->height) {
        return;
    }
    for (int y = pos->y; y < pos->y + size->y; y++) {
        for (int x = pos->x; x < pos->x + size->x; x++) {
            *layer->func_tile(x, y) &= ~flags;
        }
    }
}

/* 96.96 %: smlabb instead of mla, as in func_020596b8. */
void func_020598e4(Unk02056ed0 *layer, const Unk020593e4Xy *pos, u32 bit) {
    if (!func_02059940(layer, pos)) {
        return;
    }
    if (bit < 4 || bit > 11) {
        return;
    }
    *layer->func_tile(pos->x, pos->y) &= ~(1 << bit);
}

bool func_02059940(Unk02056ed0 *layer, const Unk020593e4Xy *pos) {
    return pos->func_valid() && pos->x < layer->info->width && pos->y < layer->info->height;
}
