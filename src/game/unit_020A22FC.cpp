/*
 * Unit 0x020A22FC-0x020A3A44: the sound manager (the strings of its error messages at
 * 0x020BD8A0-0x020BDA20, singleton data_020d6c68, created by main). It owns a NitroSystem sound
 * archive and heap, twelve sound effect handles, a music handle, four delayed sound elements
 * and four 0x10400-byte load slots. Bounds: hypothesis (the callers of the singleton; `.rodata`
 * is the table searched by hash, 374 entries; `.bss` holds the singleton, the alarm-like
 * object and the 0x3C-byte file header). The dsd names are kept (C linkage) for the callers.
 * Layouts come from the code; all names are placeholders. Real file name unknown.
 */
#include "game/unk_catalog.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

struct Unk020a22fcPlayer {
    u8 unk0[0x2c];
    u8 active;
    u8 unk2d[0xb];
    u16 unk38;
    u16 unk3a;
};

struct Unk020a22fcEntry {
    u8 type;
    u8 unk1;
    int id;
};

struct Unk020a22fcList {
    u32 count;
    Unk020a22fcEntry entries[1];
};

struct Unk020a22fcSound {
    int hash;
    u16 group;
    u16 id;
    int unk8;
};

struct Unk020a22fcSlot {
    Unk020a22fcSlot() : buffer(0), used(false), owner(0) {}

    void *buffer;
    void *heap;
    bool used;
    int owner;
};

class Unk020a22fcElement {
public:
    Unk020a22fcElement() {}
    ~Unk020a22fcElement() {}

    short delay;
    int sound;
    u32 flags;
    int handle;
    u32 speed;
    int volume;
    int owner;
    int unk1c;
    Unk020a22fcSlot *slot;
};

class Unk020a267c {
public:
    Unk020a267c(const char *path, u32 size);

    void *heap;
    void *buffer;
    u8 archive[0x90];
    Unk020a22fcPlayer *handles[12];
    Unk020a22fcPlayer *music;
    u8 stream[4];
    int musicId;
    int unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    int unke4;
    Unk020a22fcElement elements[4];
    int unk178;
    int unk17c;
    u8 volumes[0x20];
    bool slotsReady;
    bool unk1a1;
    Unk020a22fcSlot slots[4];
    int heapLevel;
};

struct Unk020a22fcFile {
    u32 id : 24;
    u32 unk : 8;
};

struct Unk020a22fcHeader {
    u8 unk0[0x38];
    int count;
};

extern "C" {
int OS_DisableInterrupts();
void OS_RestoreInterrupts(int state);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void MI_CpuFill8(void *dst, u8 value, u32 size);
void DC_StoreRange(void *start, u32 size);
void *NNSi_SndSeqArcGetSeqInfo(void *arc, int index);
void func_020897b4(const char *format, ...);
Unk020081dc func_020081dc(void *player);
int func_0209be08(void *lock);
void *NNS_SndArcGetFileAddress(int file);
void func_0209b9a0(int file, void *p);
void func_0207e4ec(void *p);
void *func_0207e074(void *p, int index);
void func_0207e0bc(void *p, int index, void *value);
void SND_InvalidateWaveData(void *start, void *end);
void func_0209b094(void *handle, int mask, int value);
void func_0209b064(void *handle, int value);
void func_0209b0c4(void *handle, int mask, int value);
void func_0209b134(void *handle, int value);
void func_0209b104(void *handle, int value);
void func_0209b020(void *handle, int a, int b);
void func_0209b144(void *handle, int value);
void func_0209b16c(void *handle);
void func_0209b1e0(void *handle, int fade);
void func_0209b2c8(int index, int value);
void func_0207c124();
void func_0207bff0(void *p);
void func_0207bf58(void *p, int a, int b, void (*callback)(), int d);
void func_0207beb8(void *p);
void func_0209a7bc();
void func_0209a788();
void *func_0209c424(void *buffer, u32 size);
void func_0209c03c(void *archive, const char *path, void *heap, int d);
void NNS_SndArcPlayerSetup(void *heap);
void func_0209e654(int count, void *heap);
void func_0209e56c(void *stream);
int func_0209e520(void *stream);
int func_0209c280(void *heap);
void func_0209c194(void *heap, int level);
int func_0209c188(void *heap);
void func_0209d0b8(int group, void *heap);
int func_0209ba04(int file, void *dst, u32 size, int offset);
void *func_0209bdf8();
void *func_0209c2d8(void *heap, u32 size, void *callback, void *a, int b);
int func_0207e0f4(void *p);
int func_0207e2f4(void *p, int a, int b, void *out);
Unk020a22fcList *func_0209bad8(int group);
int *func_0209bd30(int id);
int *func_0209bccc(int id);
int *func_0209bd94(int id);
Unk020a22fcFile *func_0209bc68(int id);
int func_0209cdf4(int id, int a, void *heap, int d, int e);
int func_0209cc94(int id, int a, void *heap, int d, void *e);
void func_0209d080(int id, void *heap);
void func_0209d050(int id, int a, void *heap);
int NNS_SndArcPlayerStartSeqArc(void *handle, int a, int b);
int NNS_SndArcPlayerStartSeq(void *handle, int a);
void *func_0209ad38(void *handle, int a, int b);
void *func_0209ac14(int a, void *b);
void func_0209ad2c(void *p);
void func_0209acd0(void *a, void *b, int c, int d);

extern u8 data_020c43a8[];
extern const char data_020bd8a0[];
extern const char data_020bd8e0[];
extern const char data_020bd908[];
extern const char data_020bd978[];
extern const char data_020bd994[];
extern const char data_020bd9f8[];
extern const Unk020a22fcSound data_020b5b84[374];

Unk020a267c *func_020a2994();
void func_020a29a4(Unk020a267c *p);
void func_020a29c8(Unk020a267c *p);
void func_020a23cc(Unk020a22fcElement *e, int index);
Unk020a22fcSlot *func_020a290c(Unk020a267c *p, int owner);
void func_020a2964(Unk020a267c *p, Unk020a22fcSlot *slot, bool release);
int func_020a2a00(Unk020a267c *p, int volume, int offset);
int func_020a2c14(Unk020a267c *p, int hash, int *group, int *id, int *unk);
int func_020a2ce8(Unk020a267c *p, int hash, int volume, bool immediate);
int func_020a2e34(Unk020a267c *p, int group);
int func_020a30bc(Unk020a267c *p, void *handle, int a, int b, int c, u8 *info, u8 *file, int d, int e);
int func_020a3188(Unk020a267c *p, int hash, void *heap);
int func_020a32ac(Unk020a267c *p, int hash, void *heap, int volume, bool immediate);
bool func_020a3478(Unk020a267c *p, int handle);
void func_020a34e4(Unk020a267c *p, int handle);
bool func_020a3514(Unk020a267c *p, int handle);
void func_020a3734(Unk020a267c *p, int fade);
void func_020a3798(Unk020a267c *p);
void func_020a3934(Unk020a267c *p, u8 index);
void func_020a38e8(Unk020a267c *p);
int func_020a39f0(Unk020a267c *p);
void func_020a3a1c(Unk020a267c *p);
void func_020a24b0(Unk020a22fcElement *e);
void func_020a25fc(Unk020a22fcElement *e);
void func_020a2630(Unk020a22fcElement *e, int volume, int unused);
void func_020a24fc(Unk020a22fcElement *e);
void func_020a2354(void *p, int unused, void *lock, int file);
void func_020a2374(void *p, u32 size, void *owner, int index);
void func_020a23bc();

}

static Unk020a267c *data_020d6c68;
static u8 data_020d6c6c[0x28];
static Unk020a22fcHeader data_020d6c94;

/* 98 %: lock, state and file in other registers. */
extern "C" void func_020a22fc(void *p, void *lock, int file) {
    if (lock == 0) {
        return;
    }
    int state = OS_DisableInterrupts();
    lock = (void *)func_0209be08(lock);
    if (p == NNS_SndArcGetFileAddress(file)) {
        func_0209b9a0(file, 0);
    }
    func_0209be08(lock);
    OS_RestoreInterrupts(state);
}

extern "C" void func_020a2354(void *p, int unused, void *lock, int file) {
    func_020a22fc(p, lock, file);
    func_0207e4ec(p);
}

extern "C" void func_020a2374(void *p, u32 size, void *owner, int index) {
    if (p == func_0207e074(owner, index)) {
        func_0207e0bc(owner, index, 0);
    }
    SND_InvalidateWaveData(p, (u8 *)p + size);
}

extern "C" void func_020a23bc() {
    func_020a29a4(func_020a2994());
}

extern "C" void func_020a23cc(Unk020a22fcElement *e, int owner) {
    e->delay = -1;
    e->flags = 0;
    e->sound = 0;
    e->handle = -1;
    e->owner = owner;
}

extern "C" bool func_020a23ec(Unk020a22fcElement *e, int sound, bool loop, int delay, bool streamed) {
    Unk020a22fcSlot *slot = func_020a290c(func_020a2994(), 4);
    if (slot != 0) {
        e->slot = slot;
        e->delay = delay;
        e->sound = sound;
        e->speed = 0x400;
        e->handle = -1;
        e->unk1c = -1;
        e->unk1c = func_020a3188(func_020a2994(), e->sound, e->slot->heap);
        if (e->unk1c == -1) {
            func_020a2964(func_020a2994(), slot, true);
            return false;
        }
        e->flags |= 6;
        if (streamed) {
            e->flags |= 0xc0;
        }
        if (loop) {
            e->flags |= 8;
        }
        return true;
    }
    return false;
}

extern "C" void func_020a24b0(Unk020a22fcElement *e) {
    e->flags = 0x100;
    int handle = e->handle;
    if (handle != -1) {
        if (func_020a3514(func_020a2994(), handle)) {
            func_020a34e4(func_020a2994(), e->handle);
            e->handle = -1;
        }
    }
}

extern "C" void func_020a24fc(Unk020a22fcElement *e) {
    Unk020a267c *p = func_020a2994();
    if (e->flags & 0x100) {
        return;
    }
    if (!(e->flags & 2)) {
        return;
    }
    if (e->flags & 0x20) {
        if (e->flags & 8) {
            return;
        }
        if (e->handle == -1) {
            return;
        }
        if (func_020a3514(p, e->handle)) {
            return;
        }
        func_020a24b0(e);
        return;
    }
    if (e->delay < 0) {
        return;
    }
    e->delay -= e->speed >> 8;
    if (e->delay > 0) {
        return;
    }
    if (e->sound != 0) {
        if (e->flags & 4) {
            e->handle = func_020a32ac(p, e->sound, e->slot->heap, 0x7f, false);
        } else {
            e->handle = func_020a2ce8(p, e->sound, 0x7f, false);
        }
        e->flags |= 0x20;
    }
    e->delay = -1;
}

extern "C" void func_020a25fc(Unk020a22fcElement *e) {
    e->handle = -1;
    e->flags = 0;
    func_020a2964(func_020a2994(), e->slot, true);
    e->slot = 0;
}

extern "C" void func_020a2630(Unk020a22fcElement *e, int volume, int unused) {
    if (!(e->flags & 2)) {
        return;
    }
    e->volume = volume;
    int handle = e->handle;
    if (handle != -1) {
        func_0209b094(&func_020a2994()->handles[handle >> 16], 0xffff, e->volume);
    }
}

Unk020a267c::Unk020a267c(const char *path, u32 size)
    : musicId(0), unkd4(0), slotsReady(false), unk1a1(false), heapLevel(0) {
    func_0207c124();
    func_0207bff0(data_020d6c6c);
    func_0209a7bc();
    buffer = new u8[size];
    heap = func_0209c424(buffer, size);
    func_0209c03c(archive, path, heap, 0);
    NNS_SndArcPlayerSetup(heap);
    func_0209b16c(&music);
    func_0209e654(10, heap);
    func_0209e56c(stream);
    for (u8 i = 0; i < 12; i++) {
        func_0209b16c(&handles[i]);
    }
    func_020a29c8(this);
    func_0209c280(heap);
    for (u8 i = 0; i < 4; i++) {
        func_020a23cc(&elements[i], i);
    }
    for (u32 i = 0; i < 0x20; i++) {
        volumes[i] = 0x7f;
    }
    unk178 = 0;
    unk17c = 0;
}

extern "C" void func_020a27f4(Unk020a267c *p) {
    if (data_020d6c68 == 0) {
        return;
    }
    if (p->slotsReady) {
        return;
    }
    for (u32 i = 0; i < 4; i++) {
        p->slots[i].buffer = new u8[0x10400];
        p->slots[i].heap = func_0209c424(p->slots[i].buffer, 0x10400);
    }
    p->slotsReady = true;
}

extern "C" void func_020a2864(const char *path, u32 size) {
    if (data_020d6c68 != 0) {
        return;
    }
    data_020d6c68 = new Unk020a267c(path, size);
}

extern "C" void func_020a28ac() {
    func_0207bf58(data_020d6c6c, 0x60, 0x14, func_020a23bc, 0);
}

extern "C" void func_020a28d8() {
    func_0207beb8(data_020d6c6c);
}

extern "C" void func_020a28ec(Unk020a267c *p) {
    func_0209d0b8(0, p->heap);
    func_0209c280(p->heap);
}

extern "C" Unk020a22fcSlot *func_020a290c(Unk020a267c *p, int owner) {
    if (!p->slotsReady) {
        return 0;
    }
    for (u32 i = 0; i != 4; i++) {
        if (!p->slots[i].used) {
            p->slots[i].used = true;
            p->slots[i].owner = owner;
            return &p->slots[i];
        }
    }
    return 0;
}

extern "C" void func_020a2964(Unk020a267c *p, Unk020a22fcSlot *slot, bool release) {
    if (slot == 0) {
        return;
    }
    func_0209c194(slot->heap, 0);
    if (release) {
        slot->used = false;
    }
}

extern "C" Unk020a267c *func_020a2994() {
    return data_020d6c68;
}

extern "C" void func_020a29a4(Unk020a267c *p) {
    func_020a38e8(p);
    func_020a3a1c(p);
    func_020a3798(p);
    func_0209a788();
}

extern "C" void func_020a29c8(Unk020a267c *p) {
    p->unke0 = 0x1000;
    p->unkdc = 0;
    p->unkd8 = 0;
    p->unke4 = 0x100;
}

extern "C" int func_020a29e8(Unk020a267c *p, int volume, int factor) {
    int v = (volume * factor) >> 12;
    if (v < 0) {
        v = 0;
    }
    if (v > 0x7f) {
        v = 0x7f;
    }
    return v;
}

extern "C" int func_020a2a00(Unk020a267c *p, int volume, int offset) {
    volume += offset;
    if (volume < -0x8000) {
        volume = -0x8000;
    }
    if (volume > 0x7fff) {
        volume = 0x7fff;
    }
    return volume;
}

/* 98.49 %: the original reads the count through the anchor data_020d6c68 + 0x64, registers. */
extern "C" void *func_020a2a2c(Unk020a267c *p, int file, void *heap, bool lock) {
    void *data = NNS_SndArcGetFileAddress(file);
    if (data == 0) {
        if (func_0209ba04(file, &data_020d6c94, 0x3c, 0) != 0x3c) {
            return 0;
        }
        u32 size = data_020d6c94.count << 2;
        u32 total = size << 1;
        if (heap == 0) {
            return 0;
        }
        void *locked;
        if (lock) {
            locked = func_0209bdf8();
        } else {
            locked = 0;
        }
        data = func_0209c2d8(heap, total + 0x5c, (void *)func_020a2354, locked, file);
        if (data == 0) {
            return 0;
        }
        if (size + 0x3c != func_0209ba04(file, data, size + 0x3c, 0)) {
            return 0;
        }
        Unk020a22fcHeader *header = (Unk020a22fcHeader *)data;
        MI_CpuCopy8((u8 *)data + 0x3c, (u8 *)data + 0x3c + (header->count << 2), size);
        MI_CpuFill8((u8 *)data + 0x3c, 0, size);
        DC_StoreRange(data, total + 0x3c);
        if (lock) {
            func_0209b9a0(file, data);
        }
    }
    return data;
}

/* 99.27 %: offset and size registers swapped. */
extern "C" bool func_020a2b38(Unk020a267c *p, u8 *table, u32 index, int file, void *heap) {
    u32 count = func_0207e0f4(table);
    if (index > count) {
        return false;
    }
    if (func_0207e074(table, index) != 0) {
        return true;
    }
    int *entry = (int *)table + (*(int *)(table + 0x38) + index);
    int offset = entry[0xf];
    u32 end = index < count - 1 ? entry[0x10] : *(int *)(table + 8);
    u32 size = end - offset;
    if (heap == 0) {
        return false;
    }
    void *data = func_0209c2d8(heap, size + 0x20, (void *)func_020a2374, table, index);
    if (data == 0) {
        return false;
    }
    if (size != func_0209ba04(file, data, size, offset)) {
        return false;
    }
    DC_StoreRange(data, size);
    func_0207e0bc(table, index, data);
    return true;
}

extern "C" int func_020a2c14(Unk020a267c *p, int hash, int *group, int *id, int *unk) {
    int lo = 0;
    int hi = 0x175;
    do {
        int mid = lo + ((hi - lo) >> 1);
        const Unk020a22fcSound *s = &data_020b5b84[mid];
        if (hash > s->hash) {
            lo = mid + 1;
        } else if (hash < s->hash) {
            hi = mid - 1;
        } else {
            *group = s->group;
            *id = s->id;
            *unk = s->unk8;
            return 1;
        }
    } while (lo <= hi);
    *group = -1;
    *id = -1;
    *unk = 0;
    return 0;
}

/* 99.47 %: the result is selected directly into r0 in the original. */
extern "C" int func_020a2c9c(Unk020a267c *p) {
    int i = 0;
    bool found = false;
    while (!found && i < 12) {
        Unk020a22fcPlayer *player = p->handles[i];
        if (player == 0 || player->active == 0) {
            found = true;
        } else {
            i++;
        }
    }
    if (i == 12) {
        i = -1;
    }
    return i;
}

/* 99.2 %: p and hash registers swapped. */
extern "C" int func_020a2ce8(Unk020a267c *p, int hash, int volume, bool immediate) {
    int group;
    int id;
    int unk;
    int index = func_020a2c9c(p);
    if (index == -1) {
        func_020897b4(data_020bd8a0);
        return -1;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4(data_020bd8e0, hash);
        return -1;
    }
    hash = func_020a2e34(p, group);
    void *handle = &p->handles[index];
    if (NNS_SndArcPlayerStartSeqArc(handle, hash, id) != 0) {
        func_0209b0c4(handle, 0xffff, volume);
        if (immediate) {
            func_0209b094(handle, 0xffff, 0);
            func_0209b064(handle, 0x100);
        } else {
            func_0209b094(handle, 0xffff, func_020a2a00(p, 0, p->unkd8));
            func_0209b064(handle, p->unke4);
        }
        return (index << 16) + (hash << 8) + id;
    }
    func_020897b4(data_020bd908);
    return -1;
}

extern "C" int func_020a2e34(Unk020a267c *p, int group) {
    Unk020a22fcList *list = func_0209bad8(group);
    int result = -1;
    u32 i = 0;
    if (list->count != 0) {
    Unk020a22fcEntry *entry = list->entries;
    do {
        switch (entry->type) {
        case 3:
            if (NNS_SndArcGetFileAddress(*func_0209bd30(entry->id)) == 0) {
                func_0209cdf4(entry->id, entry->unk1, p->heap, 1, 0);
            }
            result = entry->id;
            break;
        case 1:
            if (NNS_SndArcGetFileAddress(*func_0209bccc(entry->id)) == 0) {
                func_0209cc94(entry->id, entry->unk1, p->heap, 1, 0);
            }
            break;
        }
        i++;
        entry++;
    } while (i != list->count);
    }
    return result;
}

extern "C" void func_020a2f04(Unk020a267c *p, int id, void *heap) {
    func_0209bd30(id);
    func_0209d080(id, heap);
}

extern "C" void func_020a2f28(Unk020a267c *p, int id, void *heap) {
    int *entry = func_0209bccc(id);
    Unk020a22fcFile *info = func_0209bc68(*(u16 *)(entry + 1));
    func_020a2a2c(p, info->id, heap, true);
    func_0209d050(id, 2, heap);
}

extern "C" void func_020a2f7c(Unk020a267c *p, int id, int index, void *heap) {
    u16 out[6];
    int *entry = func_0209bccc(id);
    u8 *table = (u8 *)NNS_SndArcGetFileAddress(*entry);
    if (table == 0) {
        return;
    }
    Unk020a22fcFile *info = func_0209bc68(*(u16 *)(entry + 1));
    u8 *data = (u8 *)NNS_SndArcGetFileAddress(info->id);
    if (func_0207e2f4(table, index, 0, out) == 0) {
        return;
    }
    func_020a2b38(p, data, out[1], info->id, heap);
}

extern "C" int func_020a3018(Unk020a267c *p, void *handle, int id, int index) {
    if (func_020a2c9c(p) == -1) {
        return 0;
    }
    int *entry = func_0209bd30(id);
    if (entry == 0) {
        return 0;
    }
    u8 *file = (u8 *)NNS_SndArcGetFileAddress(*entry);
    if (file == 0) {
        return 0;
    }
    u8 *info = (u8 *)NNSi_SndSeqArcGetSeqInfo(file, index);
    if (info == 0) {
        return 0;
    }
    return func_020a30bc(p, handle, info[9], *(u16 *)(info + 4), info[8], info, file, id, index);
}

extern "C" int func_020a30bc(Unk020a267c *p, void *handle, int a, int b, int c, u8 *info, u8 *file, int d, int e) {
    int out;
    void *seq = func_0209ad38(handle, a, c);
    if (seq == 0) {
        return 0;
    }
    if (func_0209cc94(b, 2, func_0209ac14(a, seq), 0, &out) != 0) {
        func_0209ad2c(seq);
        return 0;
    }
    func_0209acd0(seq, file + *(int *)(file + 0x18), *(int *)info, out);
    func_0209b134(handle, info[6]);
    func_0209b104(handle, info[7]);
    func_0209b020(handle, d, e);
    return 1;
}

/* Replaces group 10 by group 4 when the player's outfit has no value at 0x28. */
static inline void func_group(int *group) {
    if (*group == 10) {
        bool none = func_020081dc(data_020c43a8).unk28 == 0;
        if (none) {
            *group = 4;
        }
    }
}

extern "C" int func_020a3188(Unk020a267c *p, int hash, void *heap) {
    int group;
    int id;
    int unk;
    if (heap == 0) {
        heap = p->heap;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4(data_020bd8e0, hash);
        return -1;
    }
    func_group(&group);
    Unk020a22fcList *list = func_0209bad8(group);
    u32 i = 0;
    if (list->count != 0) {
    Unk020a22fcEntry *entry = list->entries;
    do {
        switch (entry->type) {
        case 3:
            func_020a2f04(p, entry->id, heap);
            break;
        case 1:
            func_020a2f28(p, entry->id, heap);
            func_020a2f7c(p, entry->id, unk, heap);
            break;
        }
        i++;
        entry++;
    } while (i != list->count);
    }
    return group;
}

/* 98.58 %: count and entry registers swapped, one extra `moveq r0, r4` in ours. */
extern "C" int func_020a32ac(Unk020a267c *p, int hash, void *heap, int volume, bool immediate) {
    int result = -1;
    int group;
    int id;
    int unk;
    int index = func_020a2c9c(p);
    if (index == result) {
        func_020897b4(data_020bd8a0);
        return result;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4(data_020bd8e0, hash);
        return result;
    }
    func_group(&group);
    Unk020a22fcList *list = func_0209bad8(group);
    u32 count = list->count;
    u32 i = 0;
    if (count != 0) {
        Unk020a22fcEntry *entry = list->entries;
        do {
            if (entry->type == 3) {
                result = entry->id;
            }
            i++;
            entry++;
        } while (i != count);
    }
    if (result == -1) {
        return result;
    }
    void *handle = &p->handles[index];
    if (func_020a3018(p, handle, result, id) != 0) {
        func_0209b0c4(handle, 0xffff, volume);
        if (immediate) {
            func_0209b094(handle, 0xffff, 0);
            func_0209b064(handle, 0x100);
        } else {
            func_0209b094(handle, 0xffff, func_020a2a00(p, 0, p->unkd8));
            func_0209b064(handle, p->unke4);
        }
        return (index << 16) + (result << 8) + id;
    }
    func_020897b4(data_020bd908);
    return -1;
}

/* 94.63 %: lr / r12 swapped, r0 kept as the 0 result in the original. */
extern "C" bool func_020a3478(Unk020a267c *p, int handle) {
    u8 index = handle >> 16;
    if (handle < 0 || index >= 12) {
        return false;
    }
    Unk020a22fcPlayer *player = p->handles[index];
    bool result = false;
    bool same = false;
    if (player != 0) {
        same = (u8)(handle >> 8) == player->unk38;
    }
    if (same) {
        result = (handle & 0xff) == player->unk3a;
    }
    return result;
}

extern "C" void func_020a34e4(Unk020a267c *p, int handle) {
    if (func_020a3514(p, handle)) {
        func_0209b1e0(&p->handles[handle >> 16], 0);
    }
}

extern "C" bool func_020a3514(Unk020a267c *p, int handle) {
    bool result = false;
    if (func_020a3478(p, handle)) {
        result = p->handles[handle >> 16]->active != 0;
    }
    return result;
}

extern "C" void func_020a3550(Unk020a267c *p, int handle, int value) {
    if (func_020a3478(p, handle)) {
        func_0209b144(&p->handles[handle >> 16], value);
    }
}

extern "C" void func_020a3584(Unk020a267c *p, int index, int value) {
    p->volumes[index] = value;
    func_0209b2c8(index, value);
}

extern "C" void func_020a35a4(Unk020a267c *p, int handle, int volume) {
    if (func_020a3478(p, handle)) {
        func_0209b094(&p->handles[handle >> 16], 0xffff, func_020a2a00(p, volume, p->unkd8));
    }
}

extern "C" void func_020a35f0(Unk020a267c *p, int hash, int mode) {
    int group;
    int id;
    int unk;
    if (func_020a2c14(p, hash, &group, &id, &unk)) {
        if (p->musicId == hash) {
            return;
        }
        func_020a3734(p, 0);
        p->heapLevel = func_0209c188(p->heap);
        bool started;
        switch (mode) {
        case 1:
            if (NNS_SndArcGetFileAddress(*func_0209bd94(id)) == 0) {
                func_020897b4(data_020bd978);
                func_0209d0b8(group, p->heap);
            }
            started = NNS_SndArcPlayerStartSeq(&p->music, id) != 0;
            break;
        case 0:
            started = NNS_SndArcPlayerStartSeqArc(&p->music, func_020a2e34(p, group), id) != 0;
            break;
        }
        if (started) {
            func_0209b094(&p->music, 0xffff, p->unkdc);
            func_0209b064(&p->music, p->unke4);
            p->musicId = hash;
            func_0209c280(p->heap);
            return;
        }
        func_020897b4(data_020bd994);
        return;
    }
    func_020897b4(data_020bd9f8, hash);
}

extern "C" void func_020a3734(Unk020a267c *p, int fade) {
    if (p->musicId == 0 || p->music->active == 0) {
        return;
    }
    if (fade == 0) {
        func_0209b1e0(&p->music, 0);
        p->musicId = 0;
        func_0209c194(p->heap, p->heapLevel);
    } else {
        func_0209b1e0(&p->music, fade);
        p->unk1a1 = true;
    }
}

extern "C" void func_020a3798(Unk020a267c *p) {
    if (!p->unk1a1 || p->musicId == 0) {
        return;
    }
    if (p->music != 0) {
        return;
    }
    p->musicId = 0;
    func_0209c194(p->heap, p->heapLevel);
    p->unk1a1 = false;
}

extern "C" void func_020a37e8(Unk020a267c *p, u32 level) {
    if ((u32)func_0209c188(p->heap) >= level) {
        func_0209c194(p->heap, level);
    }
}

extern "C" Unk020a22fcElement *func_020a3814(Unk020a267c *p) {
    for (u32 i = 0; i != 4; i++) {
        if (!(p->elements[i].flags & 2) && !(p->elements[i].flags & 0x100)) {
            return &p->elements[i];
        }
    }
    return 0;
}

extern "C" Unk020a22fcElement *func_020a3858(Unk020a267c *p, int sound, bool loop, bool streamed, int delay) {
    Unk020a22fcElement *e = func_020a3814(p);
    if (e != 0 && func_020a23ec(e, sound, loop, delay, streamed)) {
        return e;
    }
    return 0;
}

extern "C" void func_020a389c(Unk020a267c *p, int owner) {
    for (u8 i = 0; i < 4; i++) {
        Unk020a22fcElement *e = &p->elements[i];
        if ((e->flags & 2) && (owner == 0 || owner == e->owner)) {
            func_020a24b0(e);
        }
    }
}

extern "C" void func_020a38e8(Unk020a267c *p) {
    Unk020a22fcElement *e;
    for (u8 i = 0; i < 4; i++) {
        e = &p->elements[i];
        func_020a24fc(e);
        if (e->flags & 0x100) {
            func_020a3934(p, i);
        }
    }
}

extern "C" void func_020a3934(Unk020a267c *p, u8 index) {
    int unk = p->elements[index].unk1c;
    bool last = true;
    for (u8 i = 0; i < 4; i++) {
        if (i != index) {
            Unk020a22fcElement *e = &p->elements[i];
            if ((e->flags & 2) && unk == e->unk1c) {
                last = false;
            }
        }
    }
    if (last) {
        func_020a25fc(&p->elements[index]);
    }
}

extern "C" void func_020a39a8(Unk020a267c *p, int volume, int unused) {
    for (u8 i = 0; i < 4; i++) {
        Unk020a22fcElement *e = &p->elements[i];
        if (e->flags & 0x80) {
            func_020a2630(e, volume, unused);
        }
    }
}

extern "C" int func_020a39f0(Unk020a267c *p) {
    if (p->unkd4 != 0 && func_0209e520(p->stream) != 0) {
        return 1;
    }
    return 0;
}

extern "C" void func_020a3a1c(Unk020a267c *p) {
    if (p->unkd4 != 0 && func_020a39f0(p) == 0) {
        p->unkd4 = 0;
    }
}
