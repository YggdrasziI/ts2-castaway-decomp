/*
 * File class of 0x02094xxx (vtable data_020bd348), the base of the resource file
 * classes of 0x02095xxx-0x02096xxx. Only the members that the derived classes
 * reach are declared; all names are placeholders.
 */
#ifndef GAME_UNK_FILE_H
#define GAME_UNK_FILE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

/* One block of the file: its tag, size and offset. */
struct Unk0209487cEntry {
    int tag;
    u32 size;
    u32 offset;
};

class Unk0209487c {
public:
    Unk0209487c(void *data);
    virtual ~Unk0209487c();
    virtual bool func_02094d18();
    virtual bool func_02094df4();
    virtual void func_02094f0c();
    virtual void func_02095000();

    int func_02094f88();
    void *func_02094d4c(int tag);
    u32 func_02094ddc(int tag);
    void func_02094f9c();
    void func_02094fb8();
    Unk0209487cEntry *func_02095030(int tag);

    u8 unk4[0x38];
};

#endif
