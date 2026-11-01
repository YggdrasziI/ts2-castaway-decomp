/*
 * Unit 0x02093648-0x020947C4: a container file class (Unk02093648) derived from the
 * file class Unk0209487c and read by path. Block 0x0E holds the count of sub-files,
 * block 0x0F one 20-byte entry per sub-file and block 0x10 the offset of their data.
 * A sub-file is read on demand, typed from its first block tag (func_020941e8),
 * created by the factory func_02094598 and reference-counted (field 0x32 of the
 * file class). An optional hook object (data_020bd2d4, set once by func_020947a4)
 * can type and create the sub-files that the factory does not know.
 *
 * Bounds: hypothesis. 0x02093648 is the constructor that follows the destructors of
 * unit_02093544.cpp; 0x020947C4 starts unit_020947C4.cpp. The factory is a member
 * of this class (it is called with this) and the hook is only used here. The .data
 * range holds the hook, a pointer to the string "NameOf() Unavailable" (not
 * referenced by the code), the vtable and the string. Real file name unknown.
 * Not complete: func_02094df4, func_020938d4 and func_02093a9c do not match yet
 * (see above them).
 */

#include "game/unk_archive.h"
#include "game/unk_datatree.h"
#include "game/unk_resource.h"
#include "game/unk_script.h"

/* The hook object: only two slots of its vtable are used here. */
class Unk020bd2d4 {
public:
    virtual void func_0();
    virtual void func_4();
    virtual int func_8(int tag);
    virtual Unk0209487c *func_c(void *data, int type);
};

/* The resource file classes the factory creates, with their sizes. */
class Unk02093544 : public Unk0209487c {
public:
    Unk02093544(void *data);
    ~Unk02093544();
    u8 unk3c[0x10];
};

class Unk020947c4 : public Unk0209487c {
public:
    Unk020947c4(void *data);
    ~Unk020947c4();
    u8 unk3c[0xc];
};

class Unk0209543c : public Unk0209487c {
public:
    Unk0209543c(void *data);
    ~Unk0209543c();
    u8 unk3c[0x18];
};

class Unk02095b88 : public Unk0209487c {
public:
    Unk02095b88(void *data);
    ~Unk02095b88();
    u8 unk3c[0x18];
};

class Unk02095d1c : public Unk0209487c {
public:
    Unk02095d1c(void *data);
    ~Unk02095d1c();
    u8 unk3c[0x8];
};

class Unk02095df0 : public Unk0209487c {
public:
    Unk02095df0(void *data);
    ~Unk02095df0();
    u8 unk3c[0x10];
};

class Unk02095fdc : public Unk0209487c {
public:
    Unk02095fdc(void *data);
    ~Unk02095fdc();
    u8 unk3c[0x14];
};

class Unk0209612c : public Unk0209487c {
public:
    Unk0209612c(void *data);
    ~Unk0209612c();
    u8 unk3c[0x28];
};

class Unk020962ec : public Unk0209487c {
public:
    Unk020962ec(void *data);
    ~Unk020962ec();
    u8 unk3c[0x8];
};

extern "C" {
void FS_InitFile(Unk0209487cFile *file);
int FS_OpenFileFast(Unk0209487cFile *file, Unk0209487cFileId id);
int FS_ReadFile(Unk0209487cFile *file, void *dst, u32 size);
int FS_CloseFile(Unk0209487cFile *file);
int FS_SeekFile(Unk0209487cFile *file, int offset, int whence);
void DC_FlushRange(const void *start, u32 size);
void func_02099afc(int id);
void func_02099b28(void);
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
}

int func_020941e8(int tag);

/* The hook and a name string that the code does not read. */
struct Unk02093648Hook {
    Unk020bd2d4 *hook;
    const char *name;
};

Unk02093648Hook data_020bd2d4 = {0, "NameOf() Unavailable"};

Unk02093648::Unk02093648(const char *path) : Unk0209487c(path) {
    subEntries = 0;
    unk40 = 0;
    files = 0;
    datas = 0;
    unk4c = 0;
    count = 0;
    dataOffset2 = 0;
    types = 0;
    iterIndex = -1;
    iterType = 0;
    heap = 0;
    heap2 = -1;
}

Unk02093648::~Unk02093648() {
    func_02095000();
}

/*
 * 98.72 %: with count volatile (see the class), count is read again for the last
 * new[]; the original reuses the value of the loop test.
 */
bool Unk02093648::func_02094df4() {
    int *p;
    Unk0209487cEntry *e;
    int i;
    int n;

    func_02094e04(0xe);
    p = (int *)func_02094d4c(0xe);
    if (p == 0) {
        return false;
    }
    n = *p;
    count = n;
    if (n == 0) {
        func_02094f0c();
        return false;
    }
    e = func_02095030(0x10);
    if (e == 0) {
        return false;
    }
    dataOffset2 = e->offset;
    func_02099afc(heap);
    Unk0209487c::func_02094f0c();
    func_02094e04(0xf);
    subEntries = (Unk02093648Entry *)func_02094d4c(0xf);
    if (subEntries == 0) {
        func_02099b28();
        return false;
    }
    files = new Unk0209487c *[count];
    datas = new u8 *[count];
    unk4c = new void *[count];
    for (i = 0; i < count; i++) {
        files[i] = 0;
        datas[i] = 0;
        unk4c[i] = 0;
    }
    types = new int[count];
    func_020938d4();
    func_02099b28();
    return true;
}

void Unk02093648::func_02094f0c() {
    if (!(flags & 1)) {
        return;
    }
    if (!func_02094f88()) {
        return;
    }
    if (func_02094fd8()) {
        return;
    }
    if (files != 0) {
        delete[] files;
    }
    files = 0;
    if (datas != 0) {
        delete[] datas;
    }
    datas = 0;
    if (unk4c != 0) {
        delete[] unk4c;
    }
    unk4c = 0;
    if (types != 0) {
        delete[] types;
    }
    Unk0209487c::func_02094f0c();
}

/*
 * 99.15 %: the loop index and the sub-file position swap registers (r7 / r6).
 */
void Unk02093648::func_020938d4() {
    int pos;
    int i;
    Unk0209487cFile file;
    bool ok;

    if (types == 0) {
        return;
    }
    FS_InitFile(&file);
    ok = FS_OpenFileFast(&file, func_02094fec());
    if (!ok) {
        return;
    }
    Unk0209487cEntry first;
    for (i = 0; i < getCount(); i++) {
        pos = dataOffset2 + subEntries[i].offset;
        DC_FlushRange(&first, 0xc);
        FS_SeekFile(&file, pos + 0xc, 0);
        FS_ReadFile(&file, &first, 0xc);
        types[i] = func_020941e8(first.tag);
    }
    if (ok) {
        FS_CloseFile(&file);
    }
}

void Unk02093648::func_020939d8(int heap, int heap2) {
    this->heap = heap;
    if (heap2 < 0) {
        heap2 = -1;
    }
    this->heap2 = heap2;
}

int Unk02093648::func_020939ec() {
    if (func_02094f88()) {
        return count;
    }
    return 0;
}

int Unk02093648::func_02093a08(int type) {
    int n;
    int i;

    if (!func_02094f88()) {
        return 0;
    }
    n = 0;
    for (i = 0; i < getCount(); i++) {
        if (type == types[i]) {
            n++;
        }
    }
    return n;
}

Unk0209487c *Unk02093648::func_02093a58(int index) {
    if (!func_02094f88()) {
        return 0;
    }
    if (index >= count || index < 0) {
        return 0;
    }
    return files[index];
}

/*
 * 99.47 %: register allocation of the data pointer, size, base and offset; best
 * declaration order of 720 tried.
 */
Unk0209487c *Unk02093648::func_02093a9c(int index) {
    u8 *data;
    int h;

    if (!func_02094f88()) {
        return 0;
    }
    if (index >= count || index < 0) {
        return 0;
    }
    data = datas[index];
    if (data == 0) {
        Unk0209487cFile file;
        bool ok;
        Unk02093648Entry *e;
        int base;
        int offset;
        int size;

        FS_InitFile(&file);
        ok = FS_OpenFileFast(&file, func_02094fec());
        if (!ok) {
            return 0;
        }
        e = &subEntries[index];
        size = e->end - e->start;
        base = dataOffset2;
        offset = e->offset;
        func_02099afc(heap);
        data = new u8[size];
        func_02099b28();
        datas[index] = data;
        if (data != 0) {
            DC_FlushRange(data, size);
            FS_SeekFile(&file, base + offset, 0);
            FS_ReadFile(&file, data, size);
        }
        if (ok) {
            FS_CloseFile(&file);
        }
    }
    if (files[index] == 0) {
        h = heap2;
        if (h < 0) {
            h = heap;
        }
        func_02099afc(h);
        files[index] = func_02094598(data, types[index]);
        func_02099b28();
    }
    files[index]->unk32++;
    return files[index];
}

Unk0209487c *Unk02093648::func_02093c18(const u32 *name) {
    int i = func_02093e30(name);

    if (i < 0) {
        return 0;
    }
    return func_02093a9c(i);
}

void Unk02093648::func_02093c3c(Unk0209487c *file) {
    func_02093c58(func_02093f5c(file));
}

void Unk02093648::func_02093c58(int index) {
    Unk0209487c *f;

    if (!func_02094f88()) {
        return;
    }
    if (index >= count) {
        return;
    }
    if (index < 0) {
        return;
    }
    f = files[index];
    if (f == 0) {
        return;
    }
    if (f->unk32 > 0) {
        f->unk32--;
    }
    if (f->unk32 != 0) {
        return;
    }
    delete f;
    files[index] = 0;
    if (datas[index] != 0) {
        delete[] datas[index];
        datas[index] = 0;
    }
    if (unk4c[index] != 0) {
        delete[] (u8 *)unk4c[index];
        unk4c[index] = 0;
    }
}

void Unk02093648::func_02093d14(const u32 *name) {
    int i;

    if (!func_02094f88()) {
        return;
    }
    i = func_02093e30(name);
    if (i < 0) {
        return;
    }
    func_02093c58(i);
}

int Unk02093648::func_02093d4c(int type, int start) {
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    if (start < 0) {
        return -1;
    }
    for (i = start; i < getCount(); i++) {
        if (type == types[i]) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093db0(const u32 *name, int type) {
    u32 hash;
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    hash = func_0209a32c(name, 0x7f, 0);
    for (i = 0; i < getCount(); i++) {
        if (type == types[i] && hash == subEntries[i].hash) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093e30(const u32 *name) {
    u32 hash;
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    hash = func_0209a32c(name, 0x7f, 0);
    for (i = 0; i < getCount(); i++) {
        if (hash == subEntries[i].hash) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093e9c(u32 hash) {
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    for (i = 0; i < getCount(); i++) {
        if (hash == subEntries[i].hash) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093ef4(u32 hash, int type) {
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    for (i = 0; i < getCount(); i++) {
        if (hash == subEntries[i].hash && type == types[i]) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093f5c(Unk0209487c *file) {
    int i;

    if (!func_02094f88()) {
        return -1;
    }
    if (file == 0) {
        return -1;
    }
    for (i = 0; i < getCount(); i++) {
        if (file == files[i]) {
            return i;
        }
    }
    return -1;
}

int Unk02093648::func_02093fbc(int index) {
    if (!func_02094f88()) {
        return 0x10;
    }
    if (index >= count || index < 0) {
        return 0x10;
    }
    return types[index];
}

bool Unk02093648::func_02094000(int index) {
    if (!func_02094f88()) {
        return false;
    }
    if (index >= count || index < 0) {
        return false;
    }
    return files[index] != 0;
}

Unk02093648Entry *Unk02093648::func_02094050(int index) {
    if (!func_02094f88()) {
        return 0;
    }
    if (index >= count || index < 0) {
        return 0;
    }
    return &subEntries[index];
}

void Unk02093648::func_02094098() {
    if (!func_02094f88()) {
        return;
    }
    iterIndex = 0;
    iterType = -1;
}

void Unk02093648::func_020940c0(int type) {
    if (!func_02094f88()) {
        return;
    }
    iterIndex = func_02093d4c(type, 0);
    if (iterIndex != -1) {
        iterType = type;
    } else {
        iterType = 0;
    }
}

bool Unk02093648::func_02094104() {
    if (func_02094f88()) {
        return iterType != 0;
    }
    return false;
}

Unk0209487c *Unk02093648::func_02094134() {
    int i = func_02094158();

    if (i < 0) {
        return 0;
    }
    return func_02093a9c(i);
}

int Unk02093648::func_02094158() {
    int cur;

    if (!func_02094f88()) {
        return 0;
    }
    if (iterType == 0) {
        return -1;
    }
    cur = iterIndex;
    if (iterType == -1) {
        iterIndex = cur + 1;
    } else if (cur >= count - 1) {
        iterIndex = -1;
    } else {
        iterIndex = func_02093d4c(iterType, cur + 1);
    }
    if (iterIndex >= count || iterIndex == -1) {
        iterIndex = 0;
        iterType = 0;
    }
    return cur;
}

int func_020941e8(int tag) {
    int type;

    if (tag < 0) {
        return 0x10;
    }
    switch (tag) {
    case 1:
    case 2:
    case 3:
        return 2;
    case 11:
    case 12:
    case 14:
    case 16:
        return 4;
    case 19:
    case 20:
    case 21:
    case 22:
        return 3;
    case 17:
    case 18:
        return 5;
    case 0x2000:
    case 0x2001:
        return 6;
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
        return 9;
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
        return 7;
    case 0x400:
    case 0x401:
    case 0x402:
    case 0x403:
    case 0x404:
    case 0x405:
    case 0x406:
        return 11;
    case 0x800:
    case 0x801:
    case 0x802:
    case 0x803:
    case 0x804:
    case 0x805:
    case 0x806:
        return 12;
    case 0xc00:
    case 0xc01:
    case 0xc02:
        return 13;
    case 0x2400:
    case 0x2401:
    case 0x2402:
    case 0x2403:
    case 0x2404:
    case 0x2405:
        return 14;
    case 0x2800:
    case 0x2801:
    case 0x2802:
    case 0x2803:
        return 15;
    }
    if (data_020bd2d4.hook != 0) {
        type = data_020bd2d4.hook->func_8(tag);
        if (type != 1) {
            if (type < 0x400) {
                type = 1;
            }
            return type;
        }
    }
    return 1;
}

Unk0209487c *Unk02093648::func_02094598(void *data, int type) {
    Unk0209487c *f;

    switch (type) {
    default:
        if (data_020bd2d4.hook != 0) {
            f = data_020bd2d4.hook->func_c(data, type);
            if (f != 0) {
                return f;
            }
        }
        return new Unk0209487c(data);
    case 1:
    case 16:
        return new Unk0209487c(data);
    case 4:
        return new Unk0209543c(data);
    case 5:
        return new Unk02095d1c(data);
    case 2:
        return new Unk02095fdc(data);
    case 3:
        return new Unk02093544(data);
    case 6:
        return new Unk020962ec(data);
    case 9:
        return new Unk02095140(data);
    case 7:
        return new Unk02096348(data);
    case 11:
        return new Unk020956f8(data);
    case 12:
        return new Unk0209612c(data);
    case 13:
        return new Unk020947c4(data);
    case 14:
        return new Unk02095b88(data);
    case 15:
        return new Unk02095df0(data);
    }
}

void func_020947a4(Unk020bd2d4 *hook) {
    if (hook == 0) {
        return;
    }
    if (data_020bd2d4.hook == 0) {
        data_020bd2d4.hook = hook;
    }
}
