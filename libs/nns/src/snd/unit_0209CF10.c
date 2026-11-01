/* NitroSystem SND: loads each group entry of a sound archive by its type; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned char u8;

typedef struct {
    u8 type;
    u8 flags;
    unsigned short pad;
    int id;
} Entry;

typedef struct {
    unsigned int count;
    Entry entries[1];
} Group;

extern Group *func_0209bad8(int id);
extern int func_0209cbec(int id, int flags, void *heap, int a, int b);
extern int func_0209cc94(int id, int flags, void *heap, int a, int b);
extern int func_0209cdf4(int id, int flags, void *heap, int a, int b);
extern int func_0209ce64(int id, int flags, void *heap, int a, int b);

int func_0209cf10(int id, void *heap) {
    int result;
    Group *group = func_0209bad8(id);
    unsigned int i;
    if (group == 0) {
        return 1;
    }
    for (i = 0; i < group->count; i++) {
        Entry *entry = &group->entries[i];
        switch (entry->type) {
        case 0:
            result = func_0209ce64(entry->id, entry->flags, heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;
        case 3:
            result = func_0209cdf4(entry->id, entry->flags, heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;
        case 1:
            result = func_0209cc94(entry->id, entry->flags, heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;
        case 2:
            result = func_0209cbec(entry->id, entry->flags, heap, 1, 0);
            if (result != 0) {
                return result;
            }
            break;
        }
    }
    return 0;
}
