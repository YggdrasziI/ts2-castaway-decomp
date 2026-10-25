/*
 * Container file class of unit_02093648.cpp (Unk02093648): sub-files found by
 * name, shared with its users. Layout from the code; all names are placeholders.
 */
#ifndef GAME_UNK_ARCHIVE_H
#define GAME_UNK_ARCHIVE_H

#include "game/unk_file.h"

/* One sub-file: name hash, data offset (from the offset of block 0x10) and size. */
struct Unk02093648Entry {
    u32 hash;
    int unk4;
    int offset;
    int end;
    int start;
};

class Unk02093648 : public Unk0209487c {
public:
    Unk02093648(const char *path);
    ~Unk02093648();
    virtual bool func_02094df4();
    virtual void func_02094f0c();

    void func_020938d4();
    void func_020939d8(int heap, int heap2);
    int func_020939ec();
    int func_02093a08(int type);
    Unk0209487c *func_02093a58(int index);
    Unk0209487c *func_02093a9c(int index);
    Unk0209487c *func_02093c18(const u32 *name);
    void func_02093c3c(Unk0209487c *file);
    void func_02093c58(int index);
    void func_02093d14(const u32 *name);
    int func_02093d4c(int type, int start);
    int func_02093db0(const u32 *name, int type);
    int func_02093e30(const u32 *name);
    int func_02093e9c(u32 hash);
    int func_02093ef4(u32 hash, int type);
    int func_02093f5c(Unk0209487c *file);
    int func_02093fbc(int index);
    bool func_02094000(int index);
    Unk02093648Entry *func_02094050(int index);
    void func_02094098();
    void func_020940c0(int type);
    bool func_02094104();
    Unk0209487c *func_02094134();
    int func_02094158();
    Unk0209487c *func_02094598(void *data, int type);
    int getCount() { return count; }

    Unk02093648Entry *subEntries;
    int unk40;
    Unk0209487c **files;
    u8 **datas;
    void **unk4c;
    /*
     * Hypothesis: volatile. The search loops read count again at each test while
     * keeping the other members in registers; volatile reproduces that (seven
     * functions 95 % -> 100 %), every non-volatile loop form tried does not.
     */
    volatile int count;
    int dataOffset2;
    int *types;
    int iterIndex;
    int iterType;
    s16 heap;
    s16 heap2;
};

#endif
