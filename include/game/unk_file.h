/*
 * File class of 0x02094824-0x02095140 (vtable data_020bd348), the base of the
 * resource file classes of 0x02095xxx-0x02096xxx. The file starts with a 12-byte
 * header (magic 0x4F52544E, size, block count) followed by one 12-byte entry per
 * block; entries with a negative tag form a second group of blocks. All names are
 * placeholders.
 */
#ifndef GAME_UNK_FILE_H
#define GAME_UNK_FILE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short s16;

struct Unk0209487cHeader {
    Unk0209487cHeader() {
        magic = 0;
        size = 0;
        count = 0;
    }

    u32 magic;
    u32 size;
    int count;
};

/* One block of the file: its tag, size and offset. */
struct Unk0209487cEntry {
    Unk0209487cEntry() {
        tag = 0;
        size = 0;
        offset = 0;
    }

    int tag;
    u32 size;
    int offset;
};

/* The 8 bytes kept at 0x34 and passed by value to FS_OpenFileFast. */
struct Unk0209487cFileId {
    void *unk0;
    u32 unk4;
};

/* The 0x48-byte file object of the file system functions (FS_InitFile...). */
struct Unk0209487cFile {
    u32 unk[0x12];
};

class Unk0209487c {
public:
    Unk0209487c(const char *path);
    Unk0209487c(void *data);
    virtual ~Unk0209487c();
    virtual bool func_02094d18();
    virtual bool func_02094df4();
    virtual void func_02094f0c();
    virtual void func_02095000();

    void func_020949b8(const char *path);
    void func_02094bc0(void *data);
    void func_02094c28();
    u32 func_02094cc8();
    int func_02094cf0();
    void *func_02094d4c(int tag);
    u32 func_02094ddc(int tag);
    bool func_02094e04(int tag);
    int func_02094f88();
    void func_02094f9c();
    void func_02094fb8();
    bool func_02094fd8();
    Unk0209487cFileId func_02094fec();
    Unk0209487cEntry *func_02095030(int tag);
    int func_02095098();
    int func_02095100();

    Unk0209487cHeader *header;
    Unk0209487cEntry *entries;
    u8 *block;
    u8 *block2;
    int dataOffset;
    int unk18;
    int blockStart;
    int block2Start;
    int blockSize;
    int block2Size;
    u32 flags;
    s16 refCount;
    s16 unk32;
    Unk0209487cFileId fileId;
};

#endif
