/*
 * Resource file class of unit_0209543C.cpp (Unk0209543c): a file class that also
 * implements the interface Unk020bd014. Its two reference functions are defined in
 * unit_0208A0A8.cpp. All names are placeholders.
 */
#ifndef GAME_UNK_BLOCKFILE_H
#define GAME_UNK_BLOCKFILE_H

#include "game/unk_file.h"
#include "game/unk_blocks.h"

class Unk0209543c : public Unk0209487c, public Unk020bd014 {
public:
    Unk0209543c(void *data);
    ~Unk0209543c();
    virtual void *func_020954b4();
    virtual u32 func_020954dc();
    virtual Unk0209543cBlockB *func_0209548c();
    virtual void *func_020954f8();
    virtual int func_02095520();
    virtual void *func_02095558();
    virtual int func_02095580();
    virtual void *func_020955b8();
    virtual int func_020955e0();
    virtual void func_0208a1ec();
    virtual void func_0208aa84();

    Unk0209543cBlockB *blockB;
    void *blockE;
    void *block10;
    void *blockC;
    void *block64;
};

#endif
