#ifndef GAME_UNK_LAYOUTSPRITE_H
#define GAME_UNK_LAYOUTSPRITE_H

#include "game/unk_archive.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"
#include "game/unk_resource.h"
#include "game/unk_screen.h"

/*
 * The sprite classes of a layout. Layouts come from the code; all names are placeholders.
 */
/* The sprite layer of the screen. */
class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
    int func_0208d4c8();
    void func_0208d7a0(bool visible);
    int func_0208d808();
    int func_0208d814();

    int x;
    int y;
    int unk8;
    Unk0209487c *file;
};

class Unk0208db14 {
public:
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    void func_0208df4c(Unk0208d304 *layer);
};

class Unk020a7aa0 {
public:
    Unk020a7aa0();
    virtual ~Unk020a7aa0();
    virtual void func_08(Unk020a9d58 *layout, int on) = 0;
    virtual void func_0c(Unk020a9d58 *layout) = 0;

    u32 flags;
    int unk8;
};

struct Unk020a8f84Vec {
    int x;
    int y;
    int z;
};

class Unk020a8f84 : public Unk020a7aa0 {
public:
    Unk020a8f84();
    virtual ~Unk020a8f84();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    Unk020a8f84Vec pos;
};

class Unk020a7c10 : public Unk020a7aa0 {
public:
    Unk020a7c10();
    virtual ~Unk020a7c10();
    virtual int func_10() = 0;
    virtual int func_14() = 0;

    int x;
    int y;
    int unk14;
    int cellX;
    int cellY;
};

class Unk020a690c : public Unk020a7c10 {
public:
    Unk020a690c();
    virtual ~Unk020a690c();

    int frame;
    u32 hash;
    int count;
};

class Unk020a6a00 : public Unk020a690c {
public:
    Unk020a6a00();
    virtual ~Unk020a6a00();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);
    virtual int func_10();
    virtual int func_14();

    int priority;
    int parent;
    Unk0208d304 *layer;
};

class Unk020a6dd8 : public Unk020a7aa0 {
public:
    Unk020a6dd8();
    virtual ~Unk020a6dd8();
    virtual void func_08(Unk020a9d58 *layout, int on);
    virtual void func_0c(Unk020a9d58 *layout);

    int unkc;
    int unk10;
    int first;
    int count;
};

extern "C" {
Unk02093648 *func_020aa064(Unk020a9d58 *l);
Unk0208db14 *func_020aa410(Unk020a9d58 *l);
bool func_020a7ad8(Unk020a7aa0 *s);
bool func_020a7d1c(Unk020a7c10 *s);
u32 func_020a69a4(Unk020a690c *s);
void func_020a69ac(Unk020a690c *s, int frame);
int func_020a69cc(Unk020a690c *s);
void func_020a6bcc(Unk020a6a00 *s, Unk020a9d58 *l);
void func_020a6d38(Unk020a6a00 *s, Unk020a9d58 *l);
bool func_020a6ea8(Unk020a6dd8 *s);
bool func_020a6ee8(Unk020a6dd8 *s);
bool func_020a6f28(Unk020a6dd8 *s);
}


/* The index goes unchanged here, where the other units truncate it to 16 bits. */
typedef Unk020a7c90 *(*Unk020aa040Func)(Unk020a9d58 *layout, int type, int index);

#endif
