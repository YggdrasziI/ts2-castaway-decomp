/*
 * What the files between `main` and the action base share: the action base (declared as
 * unit_020023AC.cpp defines it), the scene object, the player and the game. Layouts come
 * from the code; all names are placeholders.
 */
#ifndef GAME_UNK_ACTION_H
#define GAME_UNK_ACTION_H

#include "game/unk_script.h"
#include "game/unk_sim.h"

class Unk0205cf00 {
public:
    s16 w;
    s16 h;
    s16 unk4;
    s16 unk6;
    u8 unk8[8];
    Unk020956f8 *script;
};

struct Unk02058788 {
    u8 unk0[0x24];
    int unk24;
};

class Unk02061d08Item {
public:
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x24];
    Unk0205cf00 *def;
};

/* What is shown of an action. */
struct Unk02000ba0Desc {
    Unk02000ba0Desc(int a, int b, int c, const char *name) : a(a), b(b), c(c), name(name) {}

    int a;
    int b;
    int c;
    const char *name;
};

class Unk02002408 {
public:
    Unk02002408();
    virtual ~Unk02002408();
    void operator delete(void *p);
    virtual bool func_08() = 0;
    virtual int func_0c() = 0;
    virtual int func_10() = 0;
    virtual int func_14() = 0;
    virtual int func_18() = 0;
    virtual void func_1c() = 0;
    virtual const Unk02000ba0Desc *func_20() = 0;

    u8 unk4[0x14];
    Unk02002408 *owner;
    u8 unk1c[4];
};

/* The player. */
class Unk02000ba0Actor : public Unk020680d4Base {
public:
    u8 unk4[8];
    Unk020680d4 *sim;
};

struct Unk02000ba0Screen {
    u8 unk0[4];
    u32 flags;
};

class Unk0206bcf0 {
public:
    void func_0206dd24();
    void func_0206e104(int n);
    void func_0206ea00(int a, int b);
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
    void func_0206f560(bool a);

    u8 unk0[0x11c];
    Unk02000ba0Screen *screen;
    u8 unk120[0x24];
    void *guide;
    u8 unk148[0xc8];
    void *lots;
    u8 unk214[0x10];
    int unk224;
};

extern "C" {
Unk02000ba0Actor *func_02002414(Unk02002408 *a);
Unk02061d08Item *func_02002438(Unk02002408 *a);
void func_0200264c(Unk02002408 *a);
bool func_0200292c(Unk02002408 *a);
int func_0200294c(Unk02002408 *a, u8 b);
Unk0205cf00 *func_0205f6f8(void *db, int id);
void func_0205e184(Unk02061d08Item *item, u32 key, void *actor);
void func_0205ece8(Unk02061d08Item *item, int key);
bool func_020691c4(Unk020680d4 *sim);
Unk0206bcf0 *func_0206bce0();
void func_020a11f8(int system, int a, int b);
int func_020a1280(int system, int a, int b);
void func_020a1494(int system, int a, int b);
int func_020a18e4();
extern Unk020c3ba4 data_020c3ba4;
extern u8 data_020c3fc4[];
}

#endif
