/*
 * Unit 0x020116E0-0x02013258: the jam microgame `Unk020116e0`: a simon game on the
 * ocarina, three notes to repeat over four rounds (its strings name the ocarina
 * jam tracks and sounds).
 *
 * Bounds: hypothesis. The start follows the deleting destructor of the Icon View
 * screen, the end is the constructor of the instrument microgame. Real file name
 * unknown.
 *
 * Not complete. The whole class is defined in its body, which gives the original
 * function order (states, factory, D1, virtuals, D0) whatever the member order;
 * func_18 is outside only for `#pragma dont_inline`, which has no effect in the
 * class body. The pointer to member constants come out in the original order with
 * func_10 / func_14 first and func_020122e0 before func_020121d8 in the class (their
 * bodies are parsed last member first) and the unused object before the table.
 */

#include "game/unk_microgame.h"
#include "game/unk_camera.h"
#include "game/unk_matrix.h"
#include "game/unk_objscript.h"
#include "game/unk_pool.h"
#include "game/unk_script.h"
#include "game/unk_sim.h"


class Unk02060d78;

class Unk0205cf00 {
public:
    u8 unk0[0x10];
    Unk020956f8 *script;
};

class Unk02061d08Item {
public:
    Unk02061d08Item(Unk0205cf00 *def, const Unk020680d4Cell &cell, Unk020680d4Dir dir);
    ~Unk02061d08Item();
    void *operator new(unsigned long size);
    void operator delete(void *p);
    virtual void func_00();
    virtual void func_04();
    virtual void func_08();
    virtual void func_0c();
    virtual void func_10();
    virtual Unk020680d4Cell func_14();
    virtual void func_18();
    virtual Unk020680d4Dir func_1c();

    u8 unk4[0x10];
    int flags;
    u8 unk18[0x10];
    Unk0205cf00 *def;
    u8 unk2c[0x18];
    Unk02060d78 *anim;
    u8 unk48[4];
};

struct Unk020116e0Sound {
    int unk0;
    int unk4;
};

struct Unk020116e0Zero {
    int x;
    int y;
    int z;
};

struct Unk020116e0Arg {
    int key;
    int value;
};

struct Unk020116e0Note {
    int id;
    int speed;
    int frame;
    u32 mask;
};

extern "C" {
void func_020667f8(void *a, int b);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a7b88(Unk020a7af4 *n);
bool func_020a7d1c(Unk020a7c90 *s);
void func_020a7d30(Unk020a7c90 *s, int x);
void func_020a922c(Unk020a7c90 *s, int x);
void func_020aa42c(Unk020a9d58 *l);
Unk020a7c90 *func_020aa04c(Unk020a9d58 *l, u32 id);
int func_020a2994();
Unk020116e0Sound *func_020a290c(int a, int b);
void func_020a2964(int a, Unk020116e0Sound *b, int c);
void func_020a3188(int a, u32 h, int b);
int func_020a32ac(int a, u32 h, int b, int c, int d);
void func_020a34e4(int a, int h);
void func_020a3550(int a, int h, int v);
void func_020a35a4(int a, int h, int v);
void func_020a3858(int a, u32 h, int b, int c, int d);
int func_020a2ce8(int sound, u32 hash, int volume, int unk);
int func_020a5ef0(int a, int b);
void func_0209f880(void *a, int b);
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
Unk0205cf00 *func_0205f6f8(void *db, int id);
Unk02061d08Item *func_0205fbf4(void *m, int id);
Unk02099c78Block *func_0205cea4(Unk0205cf00 *def, int index);
void func_0205e038(Unk02061d08Item *item, Unk02099c78Block *block, void *p);
void func_0205e1b8(Unk02061d08Item *item, void *p);
void func_0205e3f0(Unk02061d08Item *item);
bool func_020691c4(void *sim);
Unk020680d4Vec func_020613f0(Unk02060d78 *e, const char *name, Unk020116e0Zero offset);
Unk020680d4Vec func_0206920c(void *p, const char *name, Unk020116e0Zero offset);
Unk020a5ccc *func_02012574(Unk02093648 *file, int a, int b);
extern u8 data_020be370[];
extern u8 data_020c3fc4[];
extern u8 data_020c3fd4[];
extern u8 data_020c43a8[];
extern u8 data_020d60c8[];
extern u8 data_020d6cdc[];
}
bool func_02097248(int key);

/*
 * Not in the ROM. The compiler sorts a file's data objects by size starting
 * from the uninitialized ones, so one object defined here, dead-stripped by the
 * linker, gives the original order of the pointer to member constants
 * (hypothesis: the original's object, its name and type are unknown; any small
 * uninitialized object gives the same order).
 */
int unused_020116e0;

Unk020116e0Note data_020b7c6c[7] = {
    {0, -1, 0, 0},       {1, 0, 0, 1},        {2, 0x80, 1, 2},     {3, 0x100, 3, 4},
    {4, 0x1c0, 2, 8},    {5, 0x240, 4, 0x10}, {6, 0x300, 5, 0x18},
};

inline Unk02098ff0 func_020130cc(const Unk02098ff0 &a, const Unk02098ff0 &b) {
    return a.func_0209911c(b);
}

class Unk020116e0 : public Unk020a5ccc {
public:
    Unk020116e0(Unk02093648 *file, int a, int b)
        : Unk020a5ccc(file, a, b), layout0(file, 0), layout1(file, 1), shown(0), names0(entries0, 0x28),
          names1(entries1, 0x28), sprite(0), state(0), round(0), handle(-1), jam(-1), volume(0), timer(0x96),
          showing(0), done(0), jamming(0), actor(0), item(0), script(0), unk4c0(0), blowing(0), free(0), mode(2) {
        *(int *)data_020be370 = 0;
        sounds[0] = 0;
        sounds[1] = 0;
        Unk020116e0Arg *args = (Unk020116e0Arg *)a;
        for (int i = 0; i < b; i++) {
            switch (args[i].key) {
            case (int)0xe6884a5d:
                if (args[i].value == 0x0458a04d) {
                    jamming = 1;
                    sounds[1] = func_020a290c(func_020a2994(), 2);
                }
                break;
            case 0x35c7a149:
                actor = func_0205fbf4(data_020c3fd4, args[i].value);
                actor->flags |= 0x4000;
                break;
            case (int)0xf89be826:
                script = args[i].value;
                break;
            case (int)0xbf6ec11d:
                unk4c0 = args[i].value;
                break;
            }
        }
        sounds[0] = func_020a290c(func_020a2994(), 2);
    }

    virtual ~Unk020116e0() {
        if (item != 0) {
            delete item;
            item = 0;
        }
        for (int i = 0; i < 2; i++) {
            if (sounds[i] != 0) {
                func_020a2964(func_020a2994(), sounds[i], 1);
                sounds[i] = 0;
            }
        }
    }

    void func_play(u32 hash) {
        Unk0205cf00 *def = actor->def;
        func_0205e038(actor, func_0205cea4(def, def->script->func_0209599c(hash)), data_020c43a8);
        def = item->def;
        func_0205e038(item, func_0205cea4(def, def->script->func_0209599c(hash)), 0);
    }

    int func_key() {
        int key = 0;
        if (func_02097248(0)) {
            key = 1;
        }
        if (func_02097248(1)) {
            key = 2;
        }
        if (func_02097248(0xb)) {
            key = 3;
        }
        if (func_02097248(0xa)) {
            key = 4;
        }
        if (func_02097248(9)) {
            key = 5;
        }
        if (func_02097248(8)) {
            key = 6;
        }
        if (key != 0) {
            pressed = 1;
        } else {
            pressed = 0;
        }
        for (u32 i = 0; i < 5; i++) {
            if (data_020b7c6c[key].mask & (1 << i)) {
                func_020a7cf0(keys[i], true);
            } else {
                func_020a7cf0(keys[i], false);
            }
        }
        return key;
    }

    void func_hideNotes() {
        for (int i = 0; i < 3; i++) {
            func_020a7cf0(notes[i], false);
            func_020a7d30(notes[i], 0);
        }
    }

    void func_hideKeys() {
        for (u32 i = 0; i < 5; i++) {
            func_020a7cf0(keys[i], false);
        }
    }

    void func_showNote() {
        count = 0;
        volume = 0x7f;
        func_020a7cf0(notes[step], true);
        func_020a69ac(notes[step], data_020b7c6c[seq[step]].frame);
        int h = handle;
        if (h != -1) {
            func_020a3550(func_020a2994(), h, volume);
            func_020a35a4(func_020a2994(), handle, data_020b7c6c[seq[step]].speed);
        }
        showing = 1;
    }

    virtual void func_10(bool a) {
        func_020aa06c(&layout0, a);
        func_020aa06c(&layout1, a);
        shown = a;
    }

    virtual void func_14() {
        func_020aa42c(&layout0);
        func_020a7b88(&names0);
        func_020aba38(file, 0x4199cdf0, &layout0, &names0);
        unk3cc = func_020aa04c(&layout0, func_020a7b50(&names0, 0x96474d87));
        func_020aa42c(&layout1);
        func_020a7b88(&names1);
        func_020aba38(file, 0x74b712a6, &layout1, &names1);
        button.func_02050838(func_020aa040(&layout0, 0xb, func_020a7b50(&names0, 0xc2f94842)), false);
        button.func_02050c48(0, 1, -1);
        keys[0] = func_020aa04c(&layout0, func_020a7b50(&names0, 0x67365de5));
        keys[1] = func_020aa04c(&layout0, func_020a7b50(&names0, 0x67365de6));
        keys[2] = func_020aa04c(&layout0, func_020a7b50(&names0, 0x67365de7));
        keys[3] = func_020aa04c(&layout0, func_020a7b50(&names0, 0x67365de8));
        keys[4] = func_020aa04c(&layout0, func_020a7b50(&names0, 0x67365de9));
        notes[0] = func_020aa04c(&layout1, func_020a7b50(&names1, 0x4e4667c8));
        notes[1] = func_020aa04c(&layout1, func_020a7b50(&names1, 0x4e4667c9));
        notes[2] = func_020aa04c(&layout1, func_020a7b50(&names1, 0x4e4667ca));
        func_020a7c90(sprite = func_020aa04c(&layout1, func_020a7b50(&names1, 0x4ace1535)), 0);
        func_020a7cac(sprite, 0);
        func_020a7cf0(sprite, 0);
        int i;
        for (i = 0; i < 3; i++) {
            func_020a7cf0(notes[i], false);
        }
        for (i = 0; i < 5; i++) {
            if (keys[i] != 0) {
                func_020a7cf0(keys[i], false);
            }
        }
        if (shown == 1) {
            func_020aa06c(&layout0, true);
            func_020aa06c(&layout1, true);
        }
        state = &Unk020116e0::func_020116e0;
    }

    void func_020116e0() {
        volume = 0;
        if (handle == -1) {
            u32 h = func_0209a32c((const u32 *)"GROUP_SE_OCARINA SE_OCARINA", 0, 0);
            if (sounds[0] != 0) {
                func_020a3188(func_020a2994(), h, sounds[0]->unk4);
                handle = func_020a32ac(func_020a2994(), h, sounds[0]->unk4, 0x7f, 0);
                func_020a3550(func_020a2994(), handle, volume);
            }
        }
        Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, 0x038c328d);
        item = new Unk02061d08Item(def, actor->func_14(), actor->func_1c());
        func_0205e3f0(item);
        timer = 0x96;
        state = &Unk020116e0::func_020118dc;
        saved = *(int *)(data_020d60c8 + 0x13c);
        func_0209f880(data_020d60c8, saved >> 2);
        func_play(0xe5e8cd73);
        if (jamming == 1 && jam == -1) {
            u32 h = func_0209a32c((const u32 *)"GROUP_JAMTRACKS SE_OCARINA_JAM", 0, 0);
            Unk020116e0Sound *s = sounds[1];
            if (s != 0) {
                func_020a3188(func_020a2994(), h, s->unk4);
            }
        }
    }

    void func_020118dc() {
        if (!func_020691c4(*(void **)(data_020c43a8 + 0xc))) {
            return;
        }
        if (jamming == 1) {
            func_play(0xa7e2c7c5);
            state = &Unk020116e0::func_02011a4c;
            if (jam == -1) {
                u32 h = func_0209a32c((const u32 *)"GROUP_JAMTRACKS SE_OCARINA_JAM", 0, 0);
                jam = func_020a32ac(func_020a2994(), h, sounds[1]->unk4, 0x7f, 0);
            }
        } else {
            func_play(0xc1fbcf52);
            state = &Unk020116e0::func_02011b54;
        }
    }

    void func_02011a4c() {
        free = 1;
        int key = func_key();
        if (key != 0) {
            func_020a35a4(func_020a2994(), handle, data_020b7c6c[key].speed);
        }
    }

    void func_02011b54() {
        free = 0;
        blowing = 0;
        if (--timer != 0) {
            return;
        }
        seq[0] = func_020a5ef0(1, 7);
        seq[1] = func_020a5ef0(1, 7);
        seq[2] = func_020a5ef0(1, 7);
        step = 0;
        func_hideNotes();
        mode = 0;
        func_showNote();
        state = &Unk020116e0::func_02011de0;
        func_play(0xdace7027);
    }

    void func_02011d14() {
        if (--timer != 0) {
            return;
        }
        func_showNote();
        state = &Unk020116e0::func_02011de0;
    }

    void func_02011de0() {
        mode = 0;
        if (!showing) {
            return;
        }
        blowing = 1;
        if (++count != 0x3c) {
            return;
        }
        showing = 0;
        blowing = 0;
        if (++step == 3) {
            free = 1;
            state = &Unk020116e0::func_02011f40;
            func_play(0xea4c8132);
            count = 0;
            step = 0;
            if (round != 0) {
                func_hideNotes();
            }
        } else {
            timer = 0x2d;
            state = &Unk020116e0::func_02011d14;
        }
    }

    void func_02011f40() {
        mode = 1;
        int key = func_key();
        if (blowing) {
            if (++count > 0xf) {
                func_020a7d30(notes[step], 1);
                note = key;
                state = &Unk020116e0::func_020122e0;
            }
            if (key == 0) {
                return;
            }
            func_020a69ac(notes[step], data_020b7c6c[key].frame);
            func_020a7cf0(notes[step], true);
            func_020a35a4(func_020a2994(), handle, data_020b7c6c[key].speed);
            if (key == seq[step]) {
                return;
            }
            state = &Unk020116e0::func_020121d8;
            func_play(0xaabd5d4c);
            func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_ERROR", 0, 0), 0x7f, 0);
            func_020a7d30(notes[step], 2);
            func_hideKeys();
        } else if (volume == 0 && count != 0) {
            count--;
        }
    }

    void func_020122e0() {
        int key = func_key();
        if (key == note) {
            return;
        }
        step++;
        count = 0;
        if (step == 3) {
            if (++round == 4) {
                timer = 0;
                func_play(0x09c2c3bc);
                func_020a3858(func_020a2994(), 0xbe776b91, 0, 0, 0);
                state = &Unk020116e0::func_02012558;
            } else {
                step = 0;
                state = &Unk020116e0::func_02011b54;
                func_play(0x09c2c3bc);
                timer = 0x64;
            }
        } else {
            state = &Unk020116e0::func_02011f40;
        }
        func_hideKeys();
    }

    void func_020121d8() {
        volume = 0;
        func_020a3550(func_020a2994(), handle, volume);
        step = 0;
        if (!func_020691c4(*(void **)(data_020c43a8 + 0xc))) {
            return;
        }
        state = &Unk020116e0::func_02011b54;
        func_play(0xc1fbcf52);
        timer = 0x64;
        mode = 2;
        func_hideNotes();
    }

    void func_02012558() {
        if (++timer == 200) {
            done = 1;
        }
    }

    /* Projects a world position to the screen (same code as func_0201d0c0). */
    Unk02098ff0 func_02012ee0(Unk020680d4Vec v) {
        Unk02098094 clip;
        Unk02098094 view;
        Unk020899a4 *camera = (Unk020899a4 *)&data_020c7d38.unk54;
        Unk02097b6c rotation = Unk02097b6c::func_02097f78(camera->angles.v.z, camera->angles.v.x, camera->angles.v.y);
        Unk02097b6c inverse = rotation.func_02097cec();
        Unk02098094 rotate(inverse);
        Unk02098ff0 back(-camera->pos.x, -camera->pos.y, -camera->pos.z);
        Unk02098094 translate(back);
        view.func_0209873c(translate, rotate);
        clip.func_0209873c(view, camera->proj);
        Unk02098ff0 p = clip.func_020983ac(v.v);
        p.y = -p.y;
        p.x += 0x1000;
        p.y += 0x1000;
        p.z += 0x1000;
        p.x = func_fxmul(p.x, 0x800);
        p.y = func_fxmul(p.y, 0x800);
        p.z = func_fxmul(p.z, 0x800);
        if (p.x < 0) {
            p.x = 0;
        }
        if (p.x > 0x1000) {
            p.x = 0x1000;
        }
        if (p.y < 0) {
            p.y = 0;
        }
        if (p.y > 0x1000) {
            p.y = 0x1000;
        }
        if (p.z < 0) {
            p.z = 0;
        }
        if (p.z > 0x1000) {
            p.z = 0x1000;
        }
        p.x = func_fxmul(p.x, 0x100000);
        p.y = func_fxmul(p.y, 0xc0000);
        return p;
    }

    virtual bool func_18();

    virtual void func_1c() {
        int h = handle;
        if (h != -1) {
            func_020a34e4(func_020a2994(), h);
            handle = -1;
        }
        func_0209f880(data_020d60c8, saved);
        actor->flags &= ~0x4000;
        func_0205e1b8(actor, data_020c43a8);
        func_020667f8(data_020c43a8, 0xa);
        if (done == 1 || jamming == 1) {
            if (script != 0) {
                Unk02061c04 runner(actor);
                runner.func_02099ce0(script);
            }
        }
    }

    Unk020a9d58 layout0;
    Unk020a9d58 layout1;
    u8 shown;
    Unk020a7af4Entry entries0[0x28];
    Unk020a7af4Entry entries1[0x28];
    Unk020a7af4 names0;
    Unk020a7af4 names1;
    Unk020a7c90 *unk3cc;
    Unk020a7c90 *notes[3];
    Unk020a7c90 *keys[5];
    Unk02050640 button;
    Unk020a7c90 *sprite;
    void (Unk020116e0::*state)();
    int round;
    int handle;
    int jam;
    int volume;
    int step;
    int seq[3];
    int timer;
    u8 showing;
    u8 pressed;
    u32 count;
    int done;
    int jamming;
    Unk02061d08Item *actor;
    Unk02061d08Item *item;
    int script;
    int unk4c0;
    u8 blowing;
    u8 free;
    int mode;
    int note;
    int saved;
    Unk020680d4Vec pos2;
    Unk020680d4Vec pos1;
    Unk020116e0Sound *sounds[2];
};

/*
 * 96.60 %: the stack slots differ (original, ascending: the two case blocks, the
 * two head positions, then each zero vector and its result).
 */
#pragma dont_inline on
inline bool Unk020116e0::func_18() {
    func_020aa158(&layout0);
    func_020aa158(&layout1);
    button.func_08();
    button.func_0c(false);
    if ((button.touch.flags & 8) || done != 0) {
        func_1c();
        return false;
    }
    if (free) {
        if (pressed && (*(u32 *)(data_020d6cdc + 0x18) & 1)) {
            blowing = 1;
        } else {
            blowing = 0;
        }
    }
    if (blowing) {
        volume += 5;
        if (volume > 0x7f) {
            volume = 0x7f;
        }
    } else {
        volume -= 10;
        if (volume < 0) {
            volume = 0;
        }
    }
    int h = handle;
    if (h != -1) {
        func_020a3550(func_020a2994(), h, volume);
    }
    if (state == 0) {
        return false;
    }
    Unk020116e0Zero head = (const Unk020116e0Zero &)func_020613f0(actor->anim, "head", (Unk020116e0Zero){0, 0, 0});
    Unk020116e0Zero head2 = (const Unk020116e0Zero &)func_0206920c(*(void **)(data_020c43a8 + 0xc), "head", (Unk020116e0Zero){0, 0, 0});
    if (sprite != 0) {
        switch (mode) {
        case 0: {
            func_020a7cf0(sprite, true);
            pos1 = (const Unk020680d4Vec &)func_02012ee0((const Unk020680d4Vec &)func_020130cc((const Unk02098ff0 &)head, Unk02098ff0(0, 0x800, 0)));
            pos1.v.x -= 0x14000;
            pos1.v.y -= 0x16000;
            func_020a7c90(sprite, pos1.v.x);
            func_020a7cac(sprite, pos1.v.y);
            break;
        }
        case 1: {
            func_020a7cf0(sprite, true);
            pos2 = (const Unk020680d4Vec &)func_02012ee0((const Unk020680d4Vec &)func_020130cc((const Unk02098ff0 &)head2, Unk02098ff0(0, 0x800, 0)));
            pos2.v.x -= 0x14000;
            pos2.v.y -= 0x16000;
            func_020a7c90(sprite, pos2.v.x);
            func_020a7cac(sprite, pos2.v.y);
            break;
        }
        case 2:
            func_020a7cf0(sprite, false);
            break;
        }
    }
    func_020a922c(sprite, 1);
    if (func_020a7d1c(sprite)) {
        u32 i = 0;
        int x = 0;
        for (; i < 3; i++) {
            func_020a7c90(notes[i], x + (func_020a7ca4(sprite) + 0x7000));
            func_020a7cac(notes[i], func_020a7cc0(sprite) + 0xa000);
            func_020a922c(notes[i], 0);
            x += 0x12000;
        }
    }
    (this->*state)();
    return true;
}
#pragma dont_inline reset

Unk020a5ccc *func_02012574(Unk02093648 *file, int a, int b) {
    return new Unk020116e0(file, a, b);
}
