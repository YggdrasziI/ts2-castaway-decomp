/*
 * Unit 0x02094824-0x02095140: the file class Unk0209487c (include/game/unk_file.h),
 * base of the resource file classes of 0x02095xxx-0x02096xxx. A file is either read
 * from the file system by path (header, entries, then its blocks on demand) or
 * set up over data already in memory. Blocks with a negative tag form a second
 * group. Two counters (0x30, 0x32) keep the loaded data from being freed.
 *
 * Bounds: hypothesis. 0x02094824 is the first function that uses the vtable
 * data_020bd348; 0x02095140 starts unit_02095140.cpp. The tail call at 0x02095134
 * is placed here as the last function before the next class. The .data range holds
 * the error string and the vtable. Real file name unknown.
 * Not complete: func_020949b8 and func_02094bc0 do not match yet (see above them).
 */

#include "game/unk_file.h"

class Unk020c80b0 {
public:
    void func_0209982c(const char *name);
    void func_02099830();
};

Unk020c80b0 *func_02099834();

extern "C" {
void FS_InitFile(Unk0209487cFile *file);
int FS_ConvertPathToFileID(Unk0209487cFileId *id, const char *path);
int FS_OpenFileFast(Unk0209487cFile *file, Unk0209487cFileId id);
int FS_ReadFile(Unk0209487cFile *file, void *dst, u32 size);
int FS_CloseFile(Unk0209487cFile *file);
int FS_SeekFile(Unk0209487cFile *file, int offset, int whence);
void DC_FlushRange(const void *start, u32 size);
void func_020897b4(const char *fmt, ...);
void FS_Init(int x);
}

Unk0209487c::Unk0209487c(const char *path) {
    header = 0;
    entries = 0;
    block = 0;
    block2 = 0;
    dataOffset = 0;
    unk18 = 0;
    blockStart = 0;
    block2Start = 0;
    blockSize = 0;
    block2Size = 0;
    flags = 0;
    refCount = 0;
    unk32 = 0;
    func_020949b8(path);
}

Unk0209487c::Unk0209487c(void *data) {
    header = 0;
    entries = 0;
    block = 0;
    block2 = 0;
    dataOffset = 0;
    unk18 = 0;
    blockStart = 0;
    block2Start = 0;
    blockSize = 0;
    block2Size = 0;
    flags = 0;
    refCount = 0;
    unk32 = 0;
    func_02094bc0(data);
}

Unk0209487c::~Unk0209487c() {
    if (flags & 1) {
        func_02094c28();
    }
}

/*
 * 98.98 %: the original reads header->count again at the bottom of the entry loop
 * (it keeps only the header pointer in a register); this one keeps the count.
 */
void Unk0209487c::func_020949b8(const char *path) {
    Unk0209487cFile file;
    bool ok;
    int i;

    if (flags & 1) {
        return;
    }
    if (path == 0) {
        return;
    }
    func_02099834()->func_0209982c(path);
    FS_InitFile(&file);
    ok = FS_ConvertPathToFileID(&fileId, path);
    if (!ok) {
        func_020897b4("    File %s", path);
    }
    if (ok) {
        ok = FS_OpenFileFast(&file, fileId);
        if (ok) {
            header = new Unk0209487cHeader;
            if (header != 0) {
                DC_FlushRange(header, 0xc);
                FS_ReadFile(&file, header, 0xc);
                if (header->magic == 0x4f52544e) {
                    entries = new Unk0209487cEntry[header->count];
                    if (entries != 0) {
                        DC_FlushRange(entries, header->count * 0xc);
                        FS_ReadFile(&file, entries, header->count * 0xc);
                        flags |= 1;
                    }
                    dataOffset = (header->count + 1) * 0xc;
                    for (i = 0; i < header->count; i++) {
                        if (entries[i].tag < 0) {
                            unk18 = entries[i].offset;
                            break;
                        }
                    }
                } else {
                    delete header;
                    header = 0;
                }
            }
        }
        if (ok) {
            FS_CloseFile(&file);
        }
    }
    func_02099834()->func_02099830();
}

/*
 * 93.85 %: the original reloads flags and stores header and entries together with
 * one stmib after the flags; this one stores header first.
 */
void Unk0209487c::func_02094bc0(void *data) {
    if (flags & 1) {
        return;
    }
    if (data == 0) {
        return;
    }
    header = (Unk0209487cHeader *)data;
    flags |= 0xb;
    entries = (Unk0209487cEntry *)((u8 *)data + 0xc);
    dataOffset = (header->count + 1) * 0xc;
    block = (u8 *)data + dataOffset;
    blockStart = dataOffset;
    blockSize = header->size - dataOffset;
}

void Unk0209487c::func_02094c28() {
    if (!(flags & 1)) {
        return;
    }
    if (func_02094fd8() || unk32 != 0) {
        return;
    }
    if (!(flags & 8)) {
        if (func_02094f88()) {
            return;
        }
        if (header != 0) {
            delete header;
        }
        if (entries != 0) {
            delete[] entries;
        }
        if (block != 0) {
            delete[] block;
        }
        if (block2 != 0) {
            delete[] block2;
        }
    }
    entries = 0;
    header = 0;
    block = 0;
    block2 = 0;
    flags = 0;
}

u32 Unk0209487c::func_02094cc8() {
    if (func_02094d18()) {
        return header->size;
    }
    return 0;
}

int Unk0209487c::func_02094cf0() {
    if (func_02094d18()) {
        return header->count;
    }
    return 0;
}

bool Unk0209487c::func_02094d18() {
    if (!(flags & 1) || header == 0) {
        return false;
    }
    return header->magic == 0x4f52544e;
}

void *Unk0209487c::func_02094d4c(int tag) {
    Unk0209487cEntry *e;
    int start;
    int size;
    u8 *data;

    if (!func_02094f88()) {
        return 0;
    }
    e = func_02095030(tag);
    if (e != 0) {
        if (tag < 0) {
            start = block2Start;
            size = block2Size;
            data = block2;
        } else {
            start = blockStart;
            size = blockSize;
            data = block;
        }
        if (data == 0) {
            return 0;
        }
        if (e->offset < start || e->offset >= start + size) {
            return 0;
        }
        return data + e->offset - start;
    }
    return 0;
}

u32 Unk0209487c::func_02094ddc(int tag) {
    Unk0209487cEntry *e = func_02095030(tag);

    if (e != 0) {
        return e->size;
    }
    return 0;
}

bool Unk0209487c::func_02094df4() {
    return func_02094e04(-1);
}

bool Unk0209487c::func_02094e04(int tag) {
    Unk0209487cFile file;
    Unk0209487cEntry *e;
    u32 size;
    int offset;
    bool ok;

    if (!(flags & 1)) {
        return false;
    }
    if (func_02094f88()) {
        return false;
    }
    FS_InitFile(&file);
    ok = FS_OpenFileFast(&file, fileId);
    if (ok) {
        e = 0;
        if (tag >= 0) {
            e = func_02095030(tag);
            if (e == 0) {
                return false;
            }
        }
        offset = dataOffset;
        if (e != 0) {
            size = e->size;
            offset = e->offset;
        } else {
            size = func_02095100();
        }
        block = new u8[size];
        if (block != 0) {
            FS_SeekFile(&file, offset, 0);
            DC_FlushRange(block, size);
            FS_ReadFile(&file, block, size);
            blockStart = offset;
            blockSize = size;
            flags |= 2;
        }
    }
    return ok;
}

void Unk0209487c::func_02094f0c() {
    if (func_02094fd8()) {
        return;
    }
    if (!func_02094f88()) {
        return;
    }
    if (flags & 8) {
        return;
    }
    if (block != 0) {
        delete[] block;
    }
    if (block2 != 0) {
        delete[] block2;
    }
    block = 0;
    block2 = 0;
    blockStart = 0;
    block2Start = 0;
    blockSize = 0;
    block2Size = 0;
    flags &= ~2;
}

int Unk0209487c::func_02094f88() {
    return (flags & 2) != 0;
}

void Unk0209487c::func_02094f9c() {
    if ((flags & 3) == 3) {
        refCount++;
    }
}

void Unk0209487c::func_02094fb8() {
    if (!(flags & 1)) {
        return;
    }
    if (refCount > 0) {
        refCount--;
    }
}

bool Unk0209487c::func_02094fd8() {
    return refCount != 0;
}

Unk0209487cFileId Unk0209487c::func_02094fec() {
    return fileId;
}

void Unk0209487c::func_02095000() {
    if ((flags & 0xa) == 2) {
        func_02094f0c();
    }
    func_02094c28();
}

Unk0209487cEntry *Unk0209487c::func_02095030(int tag) {
    int i;

    if (!(flags & 1)) {
        return 0;
    }
    for (i = 0; i < func_02094cf0(); i++) {
        if (tag == entries[i].tag) {
            return &entries[i];
        }
    }
    return 0;
}

int Unk0209487c::func_02095098() {
    int sum;
    int i;

    if (!(flags & 1)) {
        return 0;
    }
    sum = 0;
    for (i = 0; i < func_02094cf0(); i++) {
        if (entries[i].tag < 0) {
            sum += entries[i].size;
        }
    }
    return sum;
}

int Unk0209487c::func_02095100() {
    int size;

    if (!(flags & 1)) {
        return 0;
    }
    size = func_02095098();
    return header->size - dataOffset - size;
}

extern "C" void func_02095134(int x) {
    FS_Init(x);
}
