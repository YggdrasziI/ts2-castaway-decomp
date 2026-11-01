/*
 * Unit 0x020916A4-0x02092640: the object (OAM) manager of each screen
 * (include/game/unk_oam.h). func_020916a4 sets the object mapping of both display
 * controllers and builds the two managers (main screen at 0x07000000, sub screen at
 * 0x07000400). A manager owns 128 entries of 40 bytes and 128 list nodes: free
 * nodes, used nodes sorted by priority and nodes waiting to be released. It also
 * hands out the 32 affine parameter sets (a bitmask of the sets in use, a user
 * count per set) and loads object palettes through the main or sub screen loader
 * (GX_LoadOBJPltt / GXS_LoadOBJPltt).
 *
 * Bounds: hypothesis. func_02091654 just before uses the manager from outside;
 * 0x02092640 starts unit_02092640.cpp (the entry iterator). Only this code uses the
 * two manager pointers of .bss 0x020c7f6c. Real file name unknown.
 * Not complete: one function does not match yet (see above it).
 */

#include "game/unk_resource.h"
#include "game/unk_oam.h"

extern "C" {
void func_01ffab9c(Unk0208f8b0 *entry, int unk);
void func_01ffadf8(Unk020916a4 *manager);
void GXS_LoadOBJPltt(void *data, u32 offset, u32 size);
void GX_LoadOBJPltt(void *data, u32 offset, u32 size);
int func_02097b08(int x);
extern const short data_020af1e8[];
}

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)

Unk020916a4 *data_020c7f6c[2];

void func_020916a4() {
    REG_DISPCNT = (REG_DISPCNT & 0xffcfffef) | 0x10;
    REG_DB_DISPCNT = (REG_DB_DISPCNT & 0xffcfffef) | 0x10;
    data_020c7f6c[0] = new Unk020916a4((void *)0x07000000, 6, 1);
    data_020c7f6c[1] = new Unk020916a4((void *)0x07000400, 7, 0);
}

Unk020916a4::Unk020916a4(void *oam, int unk820, int main)
    : used(0), free(0), tail(0), pending(0), count(0), minPriority(0xffff), maxPriority(0),
      oam(oam), main(main), unk81c_1(0), unk820(unk820), affineMask(0) {}

Unk020916a4 *Unk020916a4::func_02091820() {
    return data_020c7f6c[0];
}

Unk020916a4 *Unk020916a4::func_02091830() {
    return data_020c7f6c[1];
}

Unk020916a4 *Unk020916a4::func_02091840(int main) {
    if (main) {
        return data_020c7f6c[0];
    }
    return data_020c7f6c[1];
}

void Unk020916a4::func_0209185c(bool show) {
    volatile u32 *reg = main ? &REG_DISPCNT : &REG_DB_DISPCNT;

    if (show) {
        *reg |= 0x1000;
        return;
    }
    *reg &= ~0x1000;
}

Unk0208f8b0 *Unk020916a4::func_0209189c(u16 priority) {
    Unk020916a4Node *n;
    Unk0208f8b0 *e;

    if (!func_02092620()) {
        func_02092554();
    }
    n = free;
    if (n == 0) {
        return 0;
    }
    free = n->next;
    if (priority <= minPriority || tail == 0) {
        n->next = used;
        used = n;
        if (tail == 0) {
            tail = n;
        }
    } else if (priority > maxPriority) {
        tail->next = n;
        tail = n;
        n->next = 0;
    } else {
        Unk020916a4Node *p;
        Unk020916a4Node *prev;
        Unk020916a4Node *head;

        head = used;
        prev = 0;
        p = head;

        while (p != 0) {
            if (p->priority >= priority) {
                break;
            }
            prev = p;
            p = p->next;
        }
        if (prev == 0) {
            n->next = head;
            used = n;
        } else {
            n->next = prev->next;
            prev->next = n;
        }
        if (n->next == 0) {
            tail = n;
        }
    }
    if (priority < minPriority) {
        minPriority = priority;
    }
    if (priority > maxPriority) {
        maxPriority = priority;
    }
    n->priority = priority;
    count++;
    e = &entries[n->index];
    e->func_0208f9dc();
    return e;
}

Unk0208f8b0 *Unk020916a4::func_020919e4(int unk, u16 priority) {
    Unk0208f8b0 *e = func_0209189c(priority);

    if (e != 0) {
        e->func_0208f90c((Unk02095140 *)unk);
    }
    return e;
}

void Unk020916a4::func_02091a0c(Unk0208f8b0 *entry, u16 priority) {
    Unk020916a4Node *p;
    Unk020916a4Node *prev;
    Unk020916a4Node *q;

    prev = 0;
    p = used;
    while (p != 0) {
        if (&entries[p->index] == entry) {
            break;
        }
        prev = p;
        p = p->next;
    }
    if (p == 0) {
        return;
    }
    p->priority = priority;
    if (prev != 0) {
        prev->next = p->next;
    } else {
        used = p->next;
    }
    prev = 0;
    q = used;
    while (q != 0) {
        if (q->priority >= priority) {
            break;
        }
        prev = q;
        q = q->next;
    }
    p->next = q;
    if (prev != 0) {
        prev->next = p;
    } else {
        used = p;
    }
}

Unk02092640 Unk020916a4::func_02091ab0(int n, u16 priority) {
    Unk0208f8b0 *first;
    Unk0208f8b0 *e;
    Unk0208f8b0 *prev;
    int i;

    if (n < 1 || n > func_020924fc()) {
        return Unk02092640(0, 0, 0);
    }
    first = 0;
    prev = 0;
    for (i = 0; i < n; i++) {
        e = func_0209189c(priority);
        if (i == 0) {
            first = e;
        }
        e->func_0208fd44(1);
        if (i == n - 1) {
            e->func_0208fd74(1);
        }
        if (prev != 0) {
            prev->func_0208fd9c(e->func_0208fdcc());
        }
        prev = e;
    }
    return Unk02092640(first, n, main ? 1 : 0);
}

Unk02092640 Unk020916a4::func_02091b9c(int n, int unk, u16 priority) {
    Unk02092640 it = func_02091ab0(n, priority);

    while (it.func_020926d4()) {
        ((Unk0208f8b0 *)it.func_02092678())->func_0208f90c((Unk02095140 *)unk);
    }
    it.func_0209266c();
    return it;
}

void Unk020916a4::func_02091bec(Unk02092640 &it) {
    Unk0208f8b0 *e;

    it.func_0209266c();
    while (it.func_020926d4()) {
        e = (Unk0208f8b0 *)it.func_02092678();
        e->func_0208fd44(0);
        e->func_0208fd9c(0);
        e->func_0208fd74(0);
        func_02091c68(e);
    }
}

void Unk020916a4::func_02091c68(Unk0208f8b0 *entry) {
    Unk020916a4Node *p;
    Unk020916a4Node *prev;

    if (entry->func_0208fd2c()) {
        return;
    }
    p = used;
    prev = 0;
    while (p != 0) {
        if (&entries[p->index] == entry) {
            break;
        }
        prev = p;
        p = p->next;
    }
    if (p == 0) {
        return;
    }
    if (prev != 0) {
        prev->next = p->next;
    } else {
        used = p->next;
    }
    if (entry->unk20 != 0) {
        entry->func_0208fa60();
        p->next = pending;
        pending = p;
    } else {
        if (entry->func_0208fcf0()) {
            func_0209241c(entry);
        }
        entry->func_0208fa14(unk820);
        p->next = free;
        free = p;
        count--;
    }
    if (p == tail) {
        tail = prev;
    }
}

void Unk020916a4::func_02091d58() {
    u32 mask;
    Unk020916a4Affine *a;

    if (count == 0) {
        return;
    }
    while (used != 0) {
        func_02091c68(&entries[used->index]);
    }
    func_01ffadf8(this);
    mask = affineMask;
    if (mask == 0) {
        return;
    }
    a = affines;
    do {
        if (mask & 1) {
            func_02092490(a);
        }
        mask >>= 1;
        a++;
    } while (mask != 0);
}

void Unk020916a4::func_02091de0(Unk0208f8b0 *a, Unk0208f8b0 *b) {
    Unk020916a4Node *head = used;
    Unk020916a4Node *p;
    bool same;

    for (p = head; p != 0; p = p->next) {
        if (&entries[p->index] == a) {
            break;
        }
    }
    if (p == 0) {
        return;
    }
    for (p = head; p != 0; p = p->next) {
        if (&entries[p->index] == b) {
            break;
        }
    }
    if (p == 0) {
        return;
    }
    same = true;
    if (a->unk18 != -1 && a->unk14 != a->unk18) {
        same = false;
    }
    if (!same) {
        func_01ffab9c(a, unk820);
    }
    if (b->unk20 != 0) {
        b->func_0208fe80(unk820);
    }
    b->func_0208fed4(a);
}

void Unk020916a4::func_02091eb4(Unk02095140 *file, int index, int mask) {
    u8 *data;
    u32 m;
    u32 offset;
    u32 size;

    if (!file->func_02094f88()) {
        return;
    }
    m = (u16)mask;
    if (m == 0xffff) {
        if (main) {
            GX_LoadOBJPltt(file->func_02095354(index), 0, 0x200);
        } else {
            GXS_LoadOBJPltt(file->func_02095354(index), 0, 0x200);
        }
        return;
    }
    data = file->func_02095354(index);
    offset = 0;
    if (main) {
        while (m != 0) {
            size = 0;
            while (!(m & 1)) {
                m >>= 1;
                offset += 0x20;
            }
            while (m & 1) {
                m >>= 1;
                size += 0x20;
            }
            GX_LoadOBJPltt(data + offset, offset, size);
            offset += size;
        }
    } else {
        while (m != 0) {
            size = 0;
            while (!(m & 1)) {
                m >>= 1;
                offset += 0x20;
            }
            while (m & 1) {
                m >>= 1;
                size += 0x20;
            }
            GXS_LoadOBJPltt(data + offset, offset, size);
            offset += size;
        }
    }
}

static inline void func_load(int main, void *data, u32 offset, u32 size) {
    if (main) {
        GX_LoadOBJPltt(data, offset, size);
    } else {
        GXS_LoadOBJPltt(data, offset, size);
    }
}

/* 99.03 %: the stack argument dst is loaded into r3 instead of r2 (best of the forms tried). */
void Unk020916a4::func_0209201c(Unk02095140 *file, int index, u32 src, u32 dst, u32 n) {
    u16 *data;

    if (!file->func_02094f88()) {
        return;
    }
    data = (u16 *)file->func_02095354(index);
    if (src + n > 0x100 || dst + n > 0x100) {
        return;
    }
    data += src;
    n *= 2;
    if (main) {
        GX_LoadOBJPltt(data, dst * 2, n);
    } else {
        GXS_LoadOBJPltt(data, dst * 2, n);
    }
}

void Unk020916a4::func_02092098(void *data, u32 dst, u32 n) {
    if (dst + n > 0x100) {
        return;
    }
    if (main) {
        GX_LoadOBJPltt(data, dst * 2, n * 2);
    } else {
        GXS_LoadOBJPltt(data, dst * 2, n * 2);
    }
}

Unk020916a4Affine *Unk020916a4::func_020920dc() {
    u32 mask = affineMask;
    int i;

    if (mask == 0xffffffff) {
        return 0;
    }
    i = 0;
    while (mask & 1) {
        mask >>= 1;
        i++;
    }
    affineMask |= 1 << i;
    affines[i].pa = 0x100;
    affines[i].pb = 0;
    affines[i].pc = 0;
    affines[i].pd = 0x100;
    return &affines[i];
}

void Unk020916a4::func_02092160(Unk0208f8b0 *entry, Unk020916a4Affine *affine) {
    if (!func_020924c0(affine)) {
        return;
    }
    if (entry->func_0208fcf0()) {
        func_0209241c(entry);
    }
    entry->func_0208fcd8(1);
    entry->func_0208fd04(affine->index);
    affine->refCount++;
}

static inline int func_inverse(u16 scale) {
    if (scale < 3) {
        return 0x7fff0;
    }
    return func_02097b08(scale << 4);
}

void Unk020916a4::func_020921c4(Unk0208f8b0 *entry, int angle, int scaleX, int scaleY) {
    Unk020916a4Affine *a;
    int sx;
    int sy;
    int sin;
    int cos;

    if (!entry->func_0208fcf0()) {
        a = func_020920dc();
        if (a == 0) {
            return;
        }
        func_02092160(entry, a);
    } else {
        a = &affines[entry->func_0208fd1c()];
    }
    sx = func_inverse(scaleX);
    sy = func_inverse(scaleY);
    cos = data_020af1e8[((u16)angle >> 4) * 2 + 1];
    sin = data_020af1e8[((u16)angle >> 4) * 2];
    a->pa = (sx * cos) >> 16;
    a->pb = (sx * sin) >> 16;
    a->pc = (-sy * sin) >> 16;
    a->pd = (sy * cos) >> 16;
}

void Unk020916a4::func_020922cc(Unk0208f8b0 *entry, int angle, int scaleX, int scaleY,
                                int flip) {
    Unk020916a4Affine *a;
    int sx;
    int sy;
    int sin;
    int cos;

    if (!entry->func_0208fcf0()) {
        a = func_020920dc();
        if (a == 0) {
            return;
        }
        func_02092160(entry, a);
    } else {
        a = &affines[entry->func_0208fd1c()];
    }
    sx = func_inverse(scaleX);
    sy = func_inverse(scaleY);
    cos = data_020af1e8[((u16)angle >> 4) * 2 + 1];
    sin = data_020af1e8[((u16)angle >> 4) * 2];
    a->pa = (sx * cos) >> 16;
    a->pb = (sx * sin) >> 16;
    a->pc = (-sy * sin) >> 16;
    a->pd = (sy * cos) >> 16;
    if (flip & 1) {
        a->pa = -a->pa;
        a->pb = -a->pb;
    }
    if (flip & 2) {
        a->pc = -a->pc;
        a->pd = -a->pd;
    }
}

void Unk020916a4::func_0209241c(Unk0208f8b0 *entry) {
    Unk020916a4Affine *a;

    if (!entry->func_0208fcf0()) {
        return;
    }
    entry->func_0208fcd8(0);
    a = &affines[entry->func_0208fd1c()];
    a->refCount--;
    entry->func_0208fd04(0);
    if (a->refCount == 0) {
        func_02092490(a);
    }
}

void Unk020916a4::func_02092490(Unk020916a4Affine *affine) {
    if (affineMask & (1 << affine->index)) {
        affineMask &= ~(1 << affine->index);
        affine->refCount = 0;
    }
}

bool Unk020916a4::func_020924c0(Unk020916a4Affine *affine) {
    int offset = (u8 *)affine - (u8 *)affines;

    if (offset < 0 || offset >= sizeof(affines)) {
        return false;
    }
    return (affineMask & (1 << affine->index)) != 0;
}

int Unk020916a4::func_020924fc() {
    return 0x80 - count;
}

Unk0208f8b0 *Unk020916a4::func_0209250c(Unk0208f8b0 *entry) {
    Unk0208f8b0 *next = 0;

    if (entry->func_0208fd2c() && !entry->func_0208fd5c()) {
        next = &entries[entry->func_0208fd8c()];
    }
    return next;
}

void Unk020916a4::func_02092554() {
    int i;
    int j;

    used = 0;
    tail = 0;
    free = &nodes[0];
    for (i = 0; i < 0x7f; i++) {
        nodes[i].index = i;
        nodes[i].next = &nodes[i + 1];
    }
    nodes[0x7f].index = 0x7f;
    nodes[0x7f].next = 0;
    for (j = 0; j < 0x80; j++) {
        entries[j].func_0208fdb4(j);
        entries[j].unk10_13 = main ? 1 : 0;
    }
    for (i = 0; i < 0x20; i++) {
        affines[i].index = i;
    }
}

bool Unk020916a4::func_02092620() {
    return used != 0 || free != 0;
}
