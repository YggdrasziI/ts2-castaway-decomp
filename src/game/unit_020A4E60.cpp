/*
 * Unit 0x020A4E60-0x020A5694: the save files in the backup memory. A global record and a number
 * of slots, each a 0x20-byte header (magic 'NTRO', CRC-32 of the configuration, data size and
 * CRC, CRC of the header) followed by the data. Loads and saves are asynchronous and advance
 * with func_020a5538. `.bss` is the CRC table, 256 words. Bounds: hypothesis (the users of the
 * table; the next function is unrelated 2D geometry). Layouts come from the code; all names are
 * placeholders. Real file name unknown.
 */
typedef unsigned short u16;
typedef unsigned long u32;

struct Unk020a4180 {
    void *fn[8];
    u16 flags;
    u16 lockId;
    int status;
};

struct Unk020a4f30Config {
    int type;
    int unk4;
    u32 mainSize;
    u32 slotCount;
    u32 slotSize;
};

struct Unk020a4e60Base {
    int magic;
    int size;
    u32 crc;
    u32 dataSize;
    u32 dataCrc;
    int unk14;
    int unk18;
    u32 headerCrc;
};

class Unk020a5154 : public Unk020a4e60Base {
public:
    Unk020a5154() {
        magic = 0x4e54524f;
        size = 0x20;
        crc = 0;
        dataSize = 0;
        dataCrc = 0;
        unk14 = 0;
        unk18 = 0;
        headerCrc = 0;
        addr = 0;
        dataAddr = 0;
        flags = 0;
    }

    /* Declared only: a sized class delete gives the array cookie of the original (hypothesis). */
    static void operator delete[](void *p, unsigned long size);

    int addr;
    int dataAddr;
    u32 flags;
};

class Unk020a4f30 {
public:
    Unk020a4f30(const void *config);

    Unk020a4f30Config config;
    u32 crc;
    u32 flags;
    Unk020a4180 *backup;
    Unk020a5154 *slots;
    Unk020a5154 main;
    Unk020a5154 *current;
    int op;
    void *readBuffer;
    void *writeBuffer;
    int result;
};

extern "C" {
Unk020a4180 *func_020a4180(void *p, int type);
int func_020a49e4(Unk020a4180 *p);
void func_020a4a00(Unk020a4180 *p);
void func_020a4a34(Unk020a4180 *p);
int func_020a4a70(Unk020a4180 *p);
bool func_020a4ad8(Unk020a4180 *p, int src, void *dst, u32 size);
void func_020a4b2c(Unk020a4180 *p, int src, void *dst, u32 size);
void func_020a4b9c(Unk020a4180 *p, int dst, const void *src, u32 size);
void func_0207954c(u32 *table, u32 poly);
u32 func_020794d0(const u32 *table, const void *data, u32 size);
bool func_020a4e8c(Unk020a4e60Base *h);
bool func_020a4f04(Unk020a4e60Base *h, const void *data);
void func_020a4e60(Unk020a4e60Base *h);
bool func_020a5208(Unk020a4f30 *p, u32 index);
bool func_020a5374(Unk020a4f30 *p, Unk020a5154 *e);
void func_020a5484(Unk020a4f30 *p, Unk020a5154 *e, void *buffer);
void func_020a54cc(Unk020a4f30 *p, Unk020a5154 *e, const void *data, u32 size);
}

u32 data_020d6d00[256];

extern "C" void func_020a4e60(Unk020a4e60Base *h) {
    h->headerCrc = 0;
    h->headerCrc = func_020794d0(data_020d6d00, h, 0x20);
}

extern "C" bool func_020a4e8c(Unk020a4e60Base *h) {
    Unk020a4e60Base copy;
    copy.magic = h->magic;
    copy.size = h->size;
    copy.crc = h->crc;
    copy.dataSize = h->dataSize;
    copy.dataCrc = h->dataCrc;
    copy.unk14 = h->unk14;
    copy.unk18 = h->unk18;
    copy.headerCrc = 0;
    return func_020794d0(data_020d6d00, &copy, 0x20) == h->headerCrc;
}

extern "C" bool func_020a4f04(Unk020a4e60Base *h, const void *data) {
    return func_020794d0(data_020d6d00, data, h->dataSize) == h->dataCrc;
}

Unk020a4f30::Unk020a4f30(const void *c)
    : config(*(const Unk020a4f30Config *)c), crc(0), flags(0), backup(0), slots(0), op(0), result(0) {
    func_0207954c(data_020d6d00, 0xedb88320);
    void *mem = operator new(0x28);
    if (mem != 0) {
        mem = func_020a4180(mem, config.type);
    }
    backup = (Unk020a4180 *)mem;
    if (!(backup->flags & 1)) {
        return;
    }
    crc = func_020794d0(data_020d6d00, this, 0x14);
    int capacity = func_020a49e4(backup);
    u32 slotBase = ((config.mainSize + 15) & ~15) + 0x20;
    int rest = capacity - slotBase;
    if (rest < 0) {
        return;
    }
    main.addr = 0;
    main.dataAddr = 0x20;
    main.crc = crc;
    u32 slotSize = ((config.slotSize + 15) & ~15) + 0x20;
    if ((int)(rest - slotSize * config.slotCount) < 0) {
        return;
    }
    slots = new Unk020a5154[config.slotCount];
    for (u32 i = 0; i < config.slotCount; i++) {
        slots[i].addr = slotBase + i * slotSize;
        slots[i].dataAddr = slots[i].addr + 0x20;
        slots[i].crc = crc;
    }
    func_020a4a00(backup);
    func_020a5374(this, &main);
    for (u32 i = 0; i < config.slotCount; i++) {
        func_020a5374(this, &slots[i]);
    }
    func_020a4a34(backup);
    flags |= 1;
}

extern "C" bool func_020a5194(Unk020a4f30 *p, void *buffer) {
    if (p->flags & 2) {
        return false;
    }
    if (!(p->main.flags & 1)) {
        return false;
    }
    func_020a5484(p, &p->main, buffer);
    return true;
}

extern "C" bool func_020a51cc(Unk020a4f30 *p, const void *data, u32 size) {
    if (p->flags & 2) {
        return false;
    }
    if (size > p->config.mainSize) {
        return false;
    }
    func_020a54cc(p, &p->main, data, size);
    return true;
}

extern "C" bool func_020a5208(Unk020a4f30 *p, u32 index) {
    if (!(p->flags & 1)) {
        return false;
    }
    if (index >= p->config.slotCount) {
        return false;
    }
    return (p->slots[index].flags & 1) != 0;
}

extern "C" u32 func_020a5248(Unk020a4f30 *p, u32 index) {
    if (!(p->flags & 1)) {
        return 0;
    }
    if (index < p->config.slotCount && (p->slots[index].flags & 1)) {
        return p->slots[index].dataSize;
    }
    return 0;
}

extern "C" u32 func_020a5288(Unk020a4f30 *p) {
    if (!(p->flags & 1)) {
        return 0;
    }
    return (p->main.flags & 1) ? p->main.dataSize : 0;
}

extern "C" bool func_020a52ac(Unk020a4f30 *p, u32 index, void *buffer) {
    if (p->flags & 2) {
        return false;
    }
    if (!(p->flags & 1)) {
        return false;
    }
    if (index < p->config.slotCount) {
        if (!func_020a5208(p, index)) {
            return false;
        }
        func_020a5484(p, &p->slots[index], buffer);
        return true;
    }
    return false;
}

extern "C" bool func_020a531c(Unk020a4f30 *p, u32 index, const void *data, u32 size) {
    if (p->flags & 2) {
        return false;
    }
    if (!(p->flags & 1)) {
        return false;
    }
    if (index >= p->config.slotCount) {
        return false;
    }
    if (size > p->config.slotSize) {
        return false;
    }
    func_020a54cc(p, &p->slots[index], data, size);
    return true;
}

extern "C" bool func_020a5374(Unk020a4f30 *p, Unk020a5154 *e) {
    if (p->flags & 2) {
        return false;
    }
    Unk020a4e60Base h;
    h.magic = 0x4e54524f;
    h.size = 0x20;
    h.crc = 0;
    h.dataSize = 0;
    h.dataCrc = 0;
    h.unk14 = 0;
    h.unk18 = 0;
    h.headerCrc = 0;
    if (func_020a4ad8(p->backup, e->addr, &h, 0x20)) {
        if (!func_020a4e8c(&h)) {
            return false;
        }
        if (h.size != 0x20) {
            return false;
        }
        if (h.crc != p->crc) {
            return false;
        }
        e->magic = h.magic;
        e->size = h.size;
        e->crc = h.crc;
        e->dataSize = h.dataSize;
        e->dataCrc = h.dataCrc;
        e->unk14 = h.unk14;
        e->unk18 = h.unk18;
        e->headerCrc = h.headerCrc;
        e->flags |= 1;
        return true;
    }
    return false;
}

extern "C" void func_020a5484(Unk020a4f30 *p, Unk020a5154 *e, void *buffer) {
    p->readBuffer = buffer;
    p->current = e;
    func_020a4a00(p->backup);
    func_020a4b2c(p->backup, e->dataAddr, p->readBuffer, e->dataSize);
    p->flags |= 2;
    p->op = 1;
}

extern "C" void func_020a54cc(Unk020a4f30 *p, Unk020a5154 *e, const void *data, u32 size) {
    p->writeBuffer = (void *)data;
    p->current = e;
    e->dataSize = size;
    e->dataCrc = func_020794d0(data_020d6d00, data, size);
    func_020a4e60(e);
    func_020a4a00(p->backup);
    func_020a4b9c(p->backup, e->addr, e, 0x20);
    p->flags |= 2;
    p->op = 2;
}

extern "C" bool func_020a5538(Unk020a4f30 *p) {
    if (!(p->flags & 2)) {
        return false;
    }
    if (func_020a4a70(p->backup) != 0) {
        return true;
    }
    switch (p->op) {
    case 1:
        if (p->backup->status == 2) {
            if (func_020a4f04(p->current, p->readBuffer)) {
                p->result = 2;
            } else {
                p->current->flags |= 4;
                p->result = 4;
            }
        } else {
            p->result = 3;
        }
        break;
    case 2:
        if (p->backup->status == 2) {
            func_020a4b9c(p->backup, p->current->dataAddr, p->writeBuffer, p->current->dataSize);
            p->op = 3;
            return true;
        }
        p->result = 3;
        p->current->flags |= 4;
    case 3:
        if (p->backup->status == 2) {
            p->result = 2;
            p->current->flags &= ~4;
            p->current->flags |= 1;
        } else {
            p->result = 3;
            p->current->flags |= 4;
        }
        break;
    }
    func_020a4a34(p->backup);
    p->flags &= ~2;
    return false;
}
