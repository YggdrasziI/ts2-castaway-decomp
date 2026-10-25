/*
 * Unit with no code at 0x020B8888 (.data): two 16-entry tables of 20.12 values
 * and two {table, count} objects built by its static initializer
 * (__sinit_020ad0ac). Nothing in this unit reads them; the static initializer
 * 0x020AD18C of another unit reads data_020be37c.
 *
 * Bounds: hypothesis. A separate unit because the pie menu code that follows
 * (unit_0201B6D4.cpp) never uses these objects, and because in one translation
 * unit with it mwccarm places its 4-byte pointer data_020b8908 before the tables
 * (objects defined before the first function are laid out by size) and reaches
 * data_020be384 through data_020be374, where the original loads data_020be384
 * directly. Before 0x020B8888 lies the "Treasure Map microgame" string of the
 * previous unit; data_020b8908 starts the pie menu's .data. Real file name
 * unknown.
 */

/* A 16-entry table and its length. */
struct Unk020be374 {
    Unk020be374(int *table, int count) {
        this->table = table;
        this->count = count;
    }

    int *table;
    int count;
};

int data_020b88c8[16] = {
    -0xC0000, -0x98000, -0x75000, -0x57000, -0x3C000, -0x25000, -0x13000, -0x4000,
    0x5000, 0xB000, 0xD000, 0xC000, 0x8000, 0x4000, 0x1000, 0,
};
int data_020b8888[16] = {
    0xC0000, 0x98000, 0x75000, 0x55000, 0x3A000, 0x23000, 0x11000, 0x2000,
    -0x7000, -0xE000, -0x10000, -0xE000, -0xA000, -0x5000, -0x1000, 0,
};
Unk020be374 data_020be37c(data_020b88c8, 16);
Unk020be374 data_020be374(data_020b8888, 16);
