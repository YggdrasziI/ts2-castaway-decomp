/*
 * Unit 0x0203C2E8-0x0203ECD4: the item list screen (Unk0203c2e8, 0x11A0 bytes,
 * vtable 0x020B9658) on the screen base Unk0203c188, built by its owner
 * (0x020296C4). Five tabs pick a choice (data_020ae90c, ten keys); the
 * objects of the inventory that carry its key fill a list of records
 * (Unk0203ea70), shown twelve per page on a 4 x 3 grid of buttons with a
 * second grid for the page slides, a previous / next pair and a "nothing"
 * sprite when the list is empty. A press reports the object to the owner;
 * the first time, the choice also starts a step of the survival guide.
 * func_0203e314 sets the choice from a key (the owner calls it) and
 * data_020b9648 holds the object or the choice to show first.
 *
 * Bounds: hypothesis. The start is the constructor, after the screen base
 * (unit_0203C188.cpp); the end is the needs screen (unit_0203ECD4.cpp).
 * `.rodata` holds the choice keys and text ids and the key list initializer;
 * `.data` the first choice, this class's vtable with its header and the
 * formats of the text function; `.bss` the flag of a choice set by
 * func_0203e314. Real file name unknown.
 *
 * Not complete: five functions are below 100 % (comments above them); the
 * last word of `.rodata` (0x020AE968, 0x46, never loaded) is the size of the
 * name list, a local `static const` folded into the code; the one-byte flag
 * leaves `.bss` at 50 % (the original range is a word).
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"
#include "game/unk_sim.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An item of the object database: only the id is used here. */
struct Unk0205cf00 {
    int unk0[3];
    int id;
};

/* An inventory entry. */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
};

/* A list of inventory entries (unit_02054734.cpp). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk02054dc4 *head;
    int count;
};

/* A recipe of an object (unit_0205359C.cpp). */
struct Unk0205367c {
    Unk0205cf00 *def;
    Unk0205cf00 *items[6];
    u8 counts[5];
    bool flags[6];
    Unk0205cf00 *result;
};

/* The survival guide animation of the player (unit_02055118.cpp): only the fields used here. */
struct Unk02055118 {
    int state;
    void *obj;
    u8 shown;
    u8 unk9;
    u8 unka;
};

/* The main game state (func_0206bce0): only its guide. */
struct Unk0206bce0 {
    u8 unk0[0x14c];
    Unk02055118 guide;
};

/* The player (data_020c43a8, unit_02064984.cpp): only its interface. */
class Unk020c43a8 : public Unk020680d4Base {
public:
    virtual void func_00(Unk02098ff0 pos);
    virtual Unk02098ff0 func_04();
    virtual void func_08(Unk02098ff0 rot);
    virtual Unk02098ff0 func_0c();
    virtual void func_10(Unk020680d4Cell cell);
    virtual Unk020680d4Cell func_14();
    virtual void func_18(Unk020680d4Dir dir);
    virtual Unk020680d4Dir func_1c();
    virtual Unk020680d4Xy func_20();
    virtual bool func_24();
    virtual bool func_28();
    virtual bool func_2c(const Unk020680d4Cell &cell);
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The object or the choice shown first (set by the owner and func_0203e314). */
struct Unk020b9648 {
    Unk0205cf00 *def;
    int index;
};

/* A record of the list (0x10 bytes). */
class Unk0203ea70 {
public:
    Unk0203ea70();

    int icon;
    Unk0205cf00 *def;
    u32 flags;
    Unk0205cf00 *result;
};

struct Unk020c3fc4;
struct Unk020bfc9c;

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020bfc9c data_020bfc9c;
extern Unk020c3ba4 data_020c3ba4;
extern u32 data_020be41c;
extern const int data_020ae7cc[];

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0206bce0 *func_0206bce0();
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
int func_0205803c(Unk02058788 *map, Unk020680d4Cell *cell);
void func_02055220(Unk02055118 *p, int state, int count);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
Unk0205cf00 *func_02053be4(Unk0205367c *t);
Unk020081dc func_020081dc(Unk020c43a8 *p);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a7ce0(Unk020a7c90 *s);
void func_0203c254(int value, int index, int main);
void func_02029128(Unk0203c188Owner *owner, bool set);
void func_0202918c(Unk0203c188Owner *owner);
void func_020291e4(Unk0203c188Owner *owner);
void func_0202923c(Unk0203c188Owner *owner);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
int func_02082a2c(char *buf, const char *fmt, ...);
void *func_020a00a0(void *texts, u32 id);
void *func_0202fdb0(Unk020d6240 *system);
bool func_0203e314(u32 key);
}

static const u32 data_020ae934[10] = {0xcc2, 0xe4c, 0xe7e, 0xcc1, 0xe4d, 0xe4c, 0xc84, 0xcc3, 0x9b1, 0xca2};
static const int data_020ae90c[10] = {
    0xbc035ef3, 0x799b1313, 0x66e2a1dc, 0x9017163a, 0xa5333669,
    0xe74b1633, 0xad4b65f7, 0x5f291f8d, 0xe780812c, 0x2dfa05df,
};

Unk020b9648 data_020b9648 = {0, -1};
bool data_020be428;

class Unk0203c2e8 : public Unk0203c188 {
public:
    Unk0203c2e8(Unk0203c188Owner *owner);
    virtual ~Unk0203c2e8();
    virtual void func_08();
    virtual void func_1c();
    virtual bool func_30();
    virtual bool func_14();
    virtual bool func_28();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_3c(bool done);
    virtual void func_38(bool active);
    virtual void func_18();
    virtual bool func_34() {
        return true;
    }
    virtual bool func_2c() {
        return fade.func_hidden();
    }

    void func_0203d414();
    void func_0203d5f0();
    void func_0203e37c(Unk02050640 *buttons, int page);
    void func_0203e4e4(int page);
    void func_0203eb74(Unk02051704 *panel);
    void func_0203ebc0(Unk02051704 *panel);
    void func_0203ec0c(Unk02051704 *panel);
    void func_0203ec60(Unk02051704 *panel);

    short page;
    short choice;
    short selected;
    int count;
    Unk0203ea70 *records;
    int pages;
    Unk020a9d58 *layout;
    Unk02050640 grid[12];
    Unk02050640 grid2[12];
    Unk02050640 tabs[5];
    Unk02050640 next;
    Unk02050640 prev;
    Unk020a7c90 *empty;
    Unk02051704 panel102c;
    Unk02051704 panel1088;
    Unk02051704 panel10e4;
    char text[0x60];
};

static void *func_0203ea8c(u32 id, void *user);

static inline bool func_owned(Unk0205cf00 *def) {
    return func_02054dc4(&data_020bfc9c, def, 0) != 0;
}

/*
 * 98.43 %: the u16 index truncations after func_020a7b50 go through r1 where
 * the original uses r0 (and the reverse) in four places, as in the other
 * screen constructors, and in the grid loop the original gives the counter
 * r8 and x r7 (here r7 and r8). Tried: the row counter declared before the
 * loop (98.57 %), the counter stepped in the loop header.
 */
Unk0203c2e8::Unk0203c2e8(Unk0203c188Owner *owner)
    : Unk0203c188(owner), page(0), choice(0), selected(-1), count(0), records(0), pages(0) {
    static const int size = 0x46;
    Unk020a7af4Entry entries[size];
    Unk020a7af4 names(entries, size);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xfa1f6daf, layout, &names);
    func_020a9db8(layout, func_0203ea8c, this);

    panel102c.func_14(-0x23000, 0);
    panel102c.func_020518a8(0xc);
    panel102c.func_02051804(3);
    panel102c.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xb0943cd7)));
    panel102c.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xdefd2411)));
    empty = func_020aa040(layout, 4, func_020a7b50(&names, 0x57d14c35));
    panel1088.func_14(-0x23000, 0);
    panel1088.func_020518a8(0xc);
    panel1088.func_02051804(2);
    panel1088.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x96b55b60)));
    panel1088.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xcbddf485)));

    int i = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            int x = FX32(col * 40);
            int y = FX32(row * 50);
            grid[i].flags |= 2;
            grid[i].func_02050914(1);
            grid2[i].flags |= 2;
            grid2[i].func_02050914(1);
            if (i < 10) {
                Unk020a7c90 *s = func_020aa040(layout, 1, func_020a7b50(&names, 0x6c1fca95 + i));
                func_020a7c90(s, x + 0x4e000);
                func_020a7cac(s, y + 0x3c000);
                grid[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x109be2e7 + i)), false);
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                grid[i].func_02050968(s);
                Unk020a7c90 *s2 = func_020aa040(layout, 1, func_020a7b50(&names, 0xbd41f24f + i));
                func_020a7c90(s2, x + 0x4e000);
                func_020a7cac(s2, y + 0x3c000);
                grid2[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x6d7e2970 + i)), false);
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                grid2[i].func_02050968(s2);
            } else {
                Unk020a7c90 *s = func_020aa040(layout, 1, func_020a7b50(&names, 0xfb3106f9 + i));
                func_020a7c90(s, x + 0x4e000);
                func_020a7cac(s, y + 0x3c000);
                grid[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x5c0f4364 + i)), false);
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                grid[i].func_02050968(s);
                Unk020a7c90 *s2 = func_020aa040(layout, 1, func_020a7b50(&names, 0x5f8af8ef + i));
                func_020a7c90(s2, x + 0x4e000);
                func_020a7cac(s2, y + 0x3c000);
                grid2[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x48e09799 + i)), false);
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                grid2[i].func_02050968(s2);
            }
            panel102c.func_020518fc(&grid[i]);
            panel1088.func_020518fc(&grid2[i]);
            i++;
        }
    }

    for (int j = 0; j < 5; j++) {
        tabs[j].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x326d005c + j)), false);
        tabs[j].func_02050c48(0, 1, -1);
        tabs[j].func_02050c64(j * 2, -1, j * 2 + 1);
        tabs[j].flags |= 2;
        tabs[j].func_14(0, FX32(31 + j * 30));
        Unk020a7c90 *icon = func_020aa040(layout, 1, func_020a7b50(&names, 0xc29281eb + j));
        func_020a69ac(icon, j);
        func_020a7c90(icon, 0x18000);
        func_020a7cac(icon, FX32(35 + j * 30));
        tabs[j].func_020508a4(icon);
    }

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));
    next.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));
    panel10e4.func_14(0, next.func_10()->y);
    panel10e4.func_24(0xc0000, panel10e4.func_10()->y);
    panel10e4.func_020518a8(2);
    panel10e4.func_02051804(2);
    panel10e4.func_020518fc(&prev);
    panel10e4.func_020518fc(&next);
    panel10e4.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x79be6d8f)));
    panel10e4.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x03398ecd)));
}

Unk0203c2e8::~Unk0203c2e8() {
    func_0203d5f0();
    delete layout;
}

void Unk0203c2e8::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0203c2e8::func_1c() {
    flags &= ~4;
}

bool Unk0203c2e8::func_30() {
    return func_28() && !func_14() && panel102c.func_38();
}

bool Unk0203c2e8::func_14() {
    return (flags & 4) != 0;
}

bool Unk0203c2e8::func_28() {
    return fade.func_shown();
}

bool Unk0203c2e8::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0203d414();
    if (flags & 8) {
        fade.func_duration(0x22);
        if (selected >= 0) {
            for (int j = 0; j < 5; j++) {
                tabs[j].func_28(0x22);
            }
        }
        if (pages > 1) {
            panel10e4.func_28(0x22);
        }
        func_0203ec0c(&panel102c);
    } else {
        fade.func_duration(0x10);
        if (selected >= 0) {
            for (int j = 0; j < 5; j++) {
                tabs[j].func_30(0x22);
            }
        }
        if (pages > 1) {
            panel10e4.func_30(0x22);
        }
        panel102c.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    Unk02058788 *map = func_02058788(&data_020c3ba4, data_020c3ba4.map);
    Unk020c43a8 *player = &data_020c43a8;
    Unk020680d4Cell cell = player->func_14();
    if (func_0205803c(map, &cell) == 1) {
        Unk02055118 *guide = &func_0206bce0()->guide;
        if (guide != 0 && !guide->shown && guide->state == 0) {
            switch (data_020ae90c[choice]) {
            case (int)0xbc035ef3:
                guide->unk9 = 1;
                func_02055220(guide, 0x13, 0);
                break;
            case (int)0xe74b1633:
                guide->unk9 = 0;
                func_02055220(guide, 0x21, 0);
                break;
            case (int)0x799b1313:
                guide->unk9 = 1;
                func_02055220(guide, 0x29, 0);
                break;
            case (int)0x66e2a1dc:
                guide->unk9 = 0;
                func_02055220(guide, 0x31, 0);
                break;
            case (int)0x9017163a:
                guide->unk9 = 1;
                guide->unka = 1;
                func_02055220(guide, 0xb, 0);
                break;
            case (int)0x89e11752:
                guide->unk9 = 0;
                func_02055220(guide, 0x37, 0);
                break;
            }
        }
    }
    return false;
}

bool Unk0203c2e8::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        for (int j = 0; j < 5; j++) {
            tabs[j].func_20(-0x31000, tabs[j].func_10()->x);
            tabs[j].func_30(0x22);
            tabs[j].func_2c(0x22);
        }
        panel10e4.func_2c(0x22);
        func_0203ec60(&panel102c);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk0203c2e8::func_0203d414() {
    if (flags & 2) {
        return;
    }
    if (data_020b9648.index >= 0) {
        choice = data_020b9648.index;
    } else if (data_020b9648.def != 0) {
        for (int i = 0; i < 10; i++) {
            if (func_0205d340(data_020b9648.def, data_020ae90c[i])) {
                choice = i;
                break;
            }
        }
    }
    if (choice < 5) {
        selected = choice;
    } else if (choice == 5) {
        selected = 1;
    }
    func_0203e4e4(0);
    func_02029128(owner, data_020be428);
    for (int j = 0; j < 5; j++) {
        if (selected == j) {
            tabs[j].func_20(-0x31000, 0);
        } else {
            tabs[j].func_20(-0x31000, -0x12000);
        }
        tabs[j].func_34(0x22);
        if (j != selected) {
            if (data_020be428) {
                tabs[j].flags |= 8;
            } else {
                tabs[j].flags &= ~8;
            }
        }
    }
    panel10e4.func_34(0x22);
    func_020a7ce0(panel10e4.func_02051ad0(0));
    func_020a7ce0(panel10e4.func_02051ad0(1));
    func_0203eb74(&panel102c);
    panel102c.func_34(0x22);
    func_020aa06c(layout, true);
    flags |= 2;
}

/*
 * 97.78 %: the original builds -1 with mvn, here it is derived from the zero
 * stored in the flag (sub r2, r1, #1). Tried: other spellings of the zero
 * and of -1.
 */
void Unk0203c2e8::func_0203d5f0() {
    if (!(flags & 2)) {
        return;
    }
    data_020be428 = false;
    data_020b9648.index = -1;
    func_020aa06c(layout, false);
    if (records != 0) {
        delete[] records;
        records = 0;
    }
    count = 0;
    flags &= ~2;
}

bool Unk0203c2e8::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = prev.func_0c(done);
    done = next.func_0c(done);
    int k = page * 12;
    for (int i = 0; k < count && i < 12; i++) {
        done = grid[i].func_0c(done);
        if (grid[i].touch.flags & 8) {
            int state = 0x17;
            if (data_020be428) {
                if (choice <= 5) {
                    state = 0x19;
                } else {
                    state = 0x13;
                }
                data_020be41c = data_020ae90c[choice];
            }
            func_020292c0(owner, state);
            func_02028eec(owner, state, records[k].def, 0);
        }
        k++;
    }
    if (prev.touch.flags & 8) {
        panel1088.func_18(true);
        func_0203e37c(grid2, page);
        func_0203ebc0(&panel1088);
        panel1088.func_30(0x22);
        for (int i = 0; i < 12; i++) {
            grid2[i].func_02050bf0(grid[i].unk64, -1, -1, -1, -1, -1);
        }
        page--;
        flags |= 0x10;
        func_020a7ce0(panel10e4.func_02051ad0(0));
    }
    if (next.touch.flags & 8) {
        page++;
        panel1088.func_18(true);
        func_0203e37c(grid2, page);
        func_0203ebc0(&panel1088);
        panel1088.func_30(0x22);
        func_0202918c(owner);
        func_0203eb74(&panel102c);
        func_020a7ce0(panel10e4.func_02051ad0(0));
    }
    for (int j = 0; j < 5; j++) {
        done = tabs[j].func_0c(done);
        if ((tabs[j].touch.flags & 8) && j != selected) {
            func_40(true);
            tabs[selected].func_20(-0x12000, 0);
            tabs[selected].func_30(0x22);
            tabs[selected].func_2c(0x22);
            selected = j;
            choice = j;
            tabs[selected].func_20(-0x12000, 0);
            tabs[selected].func_34(0x22);
            tabs[selected].func_28(0x22);
            func_0202923c(owner);
            func_0203ec60(&panel102c);
            panel10e4.func_2c(0x22);
        }
    }
    return done;
}

/*
 * 98.62 %: in the four mirrored copy loops the original gives the record
 * index r8 and the two button pointers r9 / r10 (here r10, r8 / r9), and
 * schedules the index sum one register over. The mirrored column is a second
 * counter stepped in the loop header (91.6 % with `3 - col`).
 */
void Unk0203c2e8::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    if (fade.state == 1) {
        func_40(false);
    }
    if (page < 1) {
        prev.flags |= 8;
    } else {
        prev.flags &= ~8;
    }
    if (page >= pages - 1) {
        next.flags |= 8;
    } else {
        next.flags &= ~8;
    }
    panel102c.func_08();
    panel1088.func_08();
    panel10e4.func_08();
    for (int j = 0; j < 5; j++) {
        tabs[j].func_08();
    }
    if (flags & 0x10) {
        func_020aa158(layout);
        flags &= ~0x10;
        panel102c.func_18(true);
        func_0203e37c(grid, page);
        func_0203ebc0(&panel102c);
        func_020291e4(owner);
        return;
    }
    if (fade.func_shown()) {
        if (panel102c.func_38() && grid2[0].func_02050a24()) {
            panel1088.func_18(false);
        }
        if (panel102c.func_40()) {
            panel1088.func_18(false);
        }
        if (flags & 8) {
            if (panel102c.func_44()) {
                panel102c.func_18(false);
                func_0203e4e4(0);
                func_0203ec0c(&panel102c);
            } else if (panel102c.func_40()) {
                func_40(false);
            }
        } else if (panel102c.func_4c()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    if (grid2[n].func_10()->x >= panel102c.func_10()->x) {
                        grid2[n].func_18(false);
                        int m = c + row * 4;
                        int k = page * 12 + m;
                        if (grid[m].unk64 < 0) {
                            grid[m].func_02050bf0(grid2[n].unk64, -1, -1, -1, -1, -1);
                            if (k < count) {
                                grid[m].func_020514f0();
                                if (records[k].result != 0 &&
                                    (func_0205d340(records[k].result, data_020ae7cc[8]) ||
                                     func_0205d340(records[k].result, data_020ae7cc[9]))) {
                                    func_0203c254(func_0205d134(records[k].result, 0x2b3e6dd7), grid[m].unk64, 0);
                                }
                            }
                        }
                    }
                }
            }
        } else if (panel102c.func_48()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    if (grid[n].func_10()->x >= 0x100000) {
                        grid[n].func_18(false);
                        int m = c + row * 4;
                        int k = page * 12 + m;
                        if (grid2[m].unk64 < 0) {
                            grid2[m].func_02050bf0(grid[n].unk64, -1, -1, -1, -1, -1);
                            if (k < count) {
                                grid2[m].func_020514f0();
                                if (records[k].result != 0 &&
                                    (func_0205d340(records[k].result, data_020ae7cc[8]) ||
                                     func_0205d340(records[k].result, data_020ae7cc[9]))) {
                                    func_0203c254(func_0205d134(records[k].result, 0x2b3e6dd7), grid2[m].unk64, 0);
                                }
                            }
                        }
                    }
                }
            }
        } else if (panel102c.func_44()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    grid2[c + row * 4].func_02050bf0(grid[n].unk64, -1, -1, -1, -1, -1);
                }
            }
            panel102c.func_18(true);
            func_0203e37c(grid, page);
            func_0203ebc0(&panel102c);
            panel102c.func_30(0x22);
            for (int i = 0; i < 12; i++) {
                grid[i].func_02050bf0(grid2[i].unk64, -1, -1, -1, -1, -1);
            }
            panel102c.func_08();
        } else if (panel102c.func_40()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    grid[c + row * 4].func_02050bf0(grid2[n].unk64, -1, -1, -1, -1, -1);
                }
            }
        }
    }
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0203d5f0();
    }
}

void Unk0203c2e8::func_18() {
    flags |= 4;
}

bool func_0203e314(u32 key) {
    data_020b9648.index = -1;
    for (int i = 0; i < 10; i++) {
        if (key == data_020ae90c[i]) {
            data_020b9648.index = i;
            break;
        }
    }
    data_020be428 = data_020b9648.index != -1;
    return data_020be428;
}

/*
 * 98.92 %: the original keeps the record index in r8 and the button in r9
 * (here the reverse). Tried: pointer and index forms, the declaration and
 * step orders.
 */
void Unk0203c2e8::func_0203e37c(Unk02050640 *buttons, int page) {
    int k = page * 12;
    int i;
    for (i = 0; k < count && i < 12; i++, k++) {
        buttons[i].func_020508ac(func_0206446c(records[k].icon));
        buttons[i].func_02050c48(func_020644bc(records[k].icon), -1, -1);
        buttons[i].func_02050bb4(-1, -1, func_020644b0(records[k].icon), -1);
        if (records[k].flags & 2) {
            buttons[i].flags |= 8;
        } else {
            buttons[i].flags &= ~8;
        }
        buttons[i].func_18(true);
        if (records[k].flags & 1) {
            func_020a69ac(buttons[i].func_02050a40(0), 0);
        } else {
            func_020a7cf0(buttons[i].func_02050a40(0), false);
        }
    }
    for (; i < 12; i++) {
        buttons[i].func_18(false);
    }
}

/*
 * 99.44 %: in the record loop the original keeps the counter in r9 and the
 * definition in r4 (here the reverse), and in the last loop the keys, the
 * buttons and the index sit one register over.
 */
void Unk0203c2e8::func_0203e4e4(int page) {
    this->page = page;
    u32 keys[3] = {0, 0x3d9aefc0, 0};
    int n = 2;
    keys[0] = data_020ae90c[choice];
    if (choice == 2 || choice == 9) {
        keys[2] = func_020081dc(&data_020c43a8).unk28 == 0 ? 0x85fba6e5 : 0x1e49458c;
        n = 3;
    }
    Unk020547f8 list;
    func_02054d94(&data_020bfc9c, &list, keys, n, n);
    count = list.count;
    if (records != 0) {
        delete[] records;
        records = 0;
    }
    if (count > 0) {
        func_020a7cf0(empty, false);
        panel102c.func_02051ae8(0, 2);
    } else {
        func_020a7c90(empty, panel102c.func_10()->x + 0x59000);
        func_020a7cf0(empty, true);
        panel102c.func_02051ae8(empty, 2);
    }
    if (count > 0) {
        records = new Unk0203ea70[count];
    }
    for (int i = 0; i < count; i++) {
        Unk0205cf00 *def;
        Unk02054dc4 *e = func_02054858(&list, i);
        def = e->def;
        records[i].def = def;
        Unk0205367c recipe;
        func_0205367c(&recipe, def);
        if (recipe.flags[5]) {
            records[i].icon = 0x1a004;
        } else {
            Unk0205cf00 *result = func_02053be4(&recipe);
            records[i].result = result;
            if (result != 0) {
                int icon = func_0205d134(result, 0x9d5bba8e);
                if (icon == -1) {
                    icon = 0;
                }
                records[i].icon = icon;
            } else {
                records[i].icon = 0;
            }
        }
        if (e->count > 1) {
            records[i].flags |= 1;
        }
        if (func_0205d340(def, 0x799b1313) && !func_0205d340(def, 0xe74b1633)) {
            if (!func_owned(func_0205f6f8(&data_020c3fc4, 0x6b42b6f8))) {
                records[i].flags |= 2;
                records[i].icon = 0x11040;
            }
        } else if (func_0205d340(def, 0xe74b1633)) {
            Unk0205cf00 *a = func_0205f6f8(&data_020c3fc4, 0xb56a1397);
            Unk0205cf00 *b = func_0205f6f8(&data_020c3fc4, 0x6b42b6f8);
            if (!func_owned(a) && !func_owned(b)) {
                records[i].flags |= 2;
                records[i].icon = 0x40;
            }
        }
        if (data_020b9648.def != 0 && data_020b9648.def->id == def->id) {
            this->page = i / 12;
        }
    }
    data_020b9648.def = 0;
    pages = count / 12;
    if (count % 12 != 0) {
        pages++;
    }
    if (pages > 1) {
        panel10e4.func_28(0x22);
    }
    func_020a7ce0(panel10e4.func_02051ad0(0));
    func_020a7ce0(panel10e4.func_02051ad0(1));
    panel102c.func_18(true);
    panel1088.func_18(false);
    func_0203e37c(grid, this->page);
    for (int i = 0; i < 12; i++) {
        grid[i].func_02050bf0(i, -1, -1, -1, -1, -1);
        if (grid[i].func_02050a24()) {
            grid[i].func_020514f0();
            int k = this->page * 12 + i;
            if (records[k].result != 0 &&
                (func_0205d340(records[k].result, data_020ae7cc[8]) || func_0205d340(records[k].result, data_020ae7cc[9]))) {
                func_0203c254(func_0205d134(records[k].result, 0x2b3e6dd7), grid[i].unk64, 0);
            }
        }
    }
}

Unk0203ea70::Unk0203ea70() {
    icon = -1;
    def = 0;
    flags = 0;
    result = 0;
}

static void *func_0203ea8c(u32 id, void *user) {
    Unk0203c2e8 *self = (Unk0203c2e8 *)user;
    switch (id) {
    case 0x800001:
        func_02082a2c(self->text, "%d", self->page + 1);
        return self->text;
    case 0x800002:
        func_02082a2c(self->text, "/%d", self->pages);
        return self->text;
    case 0x800003:
    case 0x800004:
        if (self->choice <= 5) {
            return func_020a00a0(func_0201ba94(), data_020ae934[self->choice]);
        } else {
            void *a = func_020a00a0(func_0202fdb0(func_020a18e4()), 0xe00);
            func_02082a2c(self->text, "%s - %s", a, func_020a00a0(func_0201ba94(), data_020ae934[self->choice]));
            return self->text;
        }
    case 0x800000:
    default:
        return func_020a00a0(func_0201ba94(), id);
    }
}

void Unk0203c2e8::func_0203eb74(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}

void Unk0203c2e8::func_0203ebc0(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk0203c2e8::func_0203ec0c(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk0203c2e8::func_0203ec60(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}
