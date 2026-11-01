/* NitroSystem SND: reads part of a wave file of the archive; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;

typedef struct {
    u32 offset;
    u32 size;
    u32 pad[2];
} Entry;

typedef struct {
    u32 pad[2];
    u32 count;
    Entry entries[1];
} Table;

typedef struct {
    unsigned char pad[0x34];
    unsigned char file[0x50];
    Table *table;
} Arc;

extern Arc *data_020d5210;
extern int FS_SeekFile(void *file, int offset, int origin);
extern int FS_ReadFile(void *file, void *dst, u32 size);

int func_0209ba04(u32 id, void *dst, u32 size, u32 offset) {
    Arc *arc = data_020d5210;
    Table *table = arc->table;
    Entry *entry;
    u32 left;
    if (id >= table->count) {
        return -1;
    }
    entry = &table->entries[id];
    left = entry->size - offset;
    if (size > left) {
        size = left;
    }
    if (!FS_SeekFile(arc->file, entry->offset + offset, 0)) {
        return -1;
    }
    return FS_ReadFile(arc->file, dst, size);
}
