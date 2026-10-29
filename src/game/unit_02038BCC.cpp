/*
 * Unit 0x02038BCC-0x0203B3B8: the object list screen (Unk02038bcc, 0xF5C
 * bytes, vtable 0x020B9558) on the screen base Unk0203c188, built by its
 * owner with a mode (0 to 4, 0x020298B8 to 0x02029A24). The mode picks the
 * title and the keys of the listed objects: one key (0, 1, 4), seven keys
 * (2), or in mode 3 the first of twenty keys (data_020ae7cc) carried by
 * data_020b954c, whose objects are taken from the object database, with
 * whether the collection holds them, the food kinds also with their count in
 * the inventory. The records (Unk0203a44c) are shown twelve per page on a
 * 4 x 3 grid of buttons with a second grid for the page slides, the count of
 * each object, a previous / next pair, a back button and a "nothing" sprite
 * when the list is empty. A press reports the object to the owner.
 * func_0203b388 sets data_020b954c, the object to show first.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots
 * 0x02038BA8 / 0x02038BB0 of the screen with vtable 0x020B94F4; the end is
 * the text pager screen (unit_0203B3B8.cpp). `.rodata` holds the key list
 * initializer, the palette cleared by func_0203b220 and an unreferenced word
 * 0x46 (the size of the name list, as in unit_0203C2E8.cpp); `.data` the
 * object shown first, this class's vtable with its header and the formats of
 * the text function. Real file name unknown.
 *
 * Not complete: three functions are below 100 % (comments above them); the
 * last word of `.rodata` (0x020AE908, 0x46, never loaded) is not reproduced,
 * as in unit_0203C2E8.cpp.
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"
#include "game/unk_oam.h"
#include "game/unk_sortedset.h"

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

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* The game settings (data_020d60c8): only the collection is named. */
struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
};

/* A record of the list (0xC bytes). */
class Unk0203a44c {
public:
    Unk0203a44c();

    int icon;
    int count;
    Unk0205cf00 *def;
};

struct Unk020c43a8;
struct Unk020c3fc4;
struct Unk020bfc9c;

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3fc4 data_020c3fc4;
extern Unk020bfc9c data_020bfc9c;
extern const int data_020ae7cc[];
extern const int data_020ae81c[];

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0205cf00 *func_0205f714(Unk020c3fc4 *db, int key, Unk0205cf00 *rec);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
int func_0205d1b4(Unk0205cf00 *def, int key);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
Unk020081dc func_020081dc(Unk020c43a8 *p);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a7ce0(Unk020a7c90 *s);
void func_0203c254(int value, int index, int main);
void func_02029128(Unk0203c188Owner *owner, bool set);
void func_0202918c(Unk0203c188Owner *owner);
void func_020291e4(Unk0203c188Owner *owner);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
Unk0205cf00 *func_02028ebc();
void func_02033ea0(Unk0205cf00 *item);
int func_02082a2c(char *buf, const char *fmt, ...);
const char *func_020a00a0(void *texts, int id);
void func_0203b388(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b954c = 0;
#pragma explicit_zero_data reset

class Unk02038bcc : public Unk0203c188 {
public:
    Unk02038bcc(Unk0203c188Owner *owner, int mode);
    virtual ~Unk02038bcc();
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

    void func_02039a08();
    void func_0203a464();
    void func_0203afd0(Unk02050640 *buttons, int page);
    void func_0203b220(int index);
    void func_0203b248(Unk02051704 *panel);
    void func_0203b294(Unk02051704 *panel);
    void func_0203b2e0(Unk02051704 *panel);
    void func_0203b334(Unk02051704 *panel);

    Unk0205cf00 *item;
    int title;
    int mode;
    Unk0203a44c *records;
    int count;
    int pages;
    short page;
    u32 key;
    Unk020a9d58 *layout;
    Unk02050640 grid[12];
    Unk02050640 grid2[12];
    Unk02050640 next;
    Unk02050640 prev;
    Unk02050640 back;
    char text[0x20];
    Unk020a7c90 *empty;
    Unk02051704 panel;
    Unk02051704 panel2;
    Unk02051704 pager;
};

static void *func_0203b148(u32 id, void *user);

/* The objects listed in mode 3 for the food keys. */
static inline bool func_listed(Unk0205cf00 *def, u32 kind) {
    return func_0205d340(def, kind) && !func_0205d340(def, 0x654b481d) && !func_0205d340(def, 0x291d04a3) &&
           !func_0205d340(def, 0x51a12c57);
}

/*
 * 97.78 %: in the grid loop the original keeps the button index in r8 and the
 * name result in r7, here the other way round; two address computations of
 * the second grid are also scheduled one instruction apart. Tried: the row
 * and index declared in other orders or in the loop header.
 */
Unk02038bcc::Unk02038bcc(Unk0203c188Owner *owner, int mode)
    : Unk0203c188(owner), item(0), title(0), mode(mode), records(0), count(0), pages(0), page(0) {
    Unk020a7af4Entry entries[0x46];
    Unk020a7af4 names(entries, 0x46);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x4b2e9833, layout, &names);
    func_020a9db8(layout, func_0203b148, this);

    panel.func_14(-0x23000, 0);
    panel.func_020518a8(0xc);
    panel.func_02051804(3);
    panel.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xdefd2411)));
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xb0943cd7)));
    empty = func_020aa040(layout, 4, func_020a7b50(&names, 0x57d14c35));
    panel2.func_14(-0x23000, 0);
    panel2.func_020518a8(0xc);
    panel2.func_02051804(2);
    panel2.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xcbddf485)));
    panel2.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x96b55b60)));

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
                grid[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x109be2e7 + i)), false);
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x31095e70 + i));
                func_020a7c90(s, x + 0x36000);
                func_020a7cac(s, y + 0x3f000);
                grid[i].func_02050968(s);
                grid2[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x6d7e2970 + i)), false);
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                Unk020a7c90 *s2 = func_020aa040(layout, 4, func_020a7b50(&names, 0x1ddb2ae4 + i));
                func_020a7c90(s2, x + 0x36000);
                func_020a7cac(s2, y + 0x3f000);
                grid2[i].func_02050968(s2);
            } else {
                grid[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x5c0f4364 + i)), false);
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x044df6c0 + i));
                func_020a7c90(s, x + 0x36000);
                func_020a7cac(s, y + 0x3f000);
                grid[i].func_02050968(s);
                grid2[i].func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x48e09799 + i)), false);
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                Unk020a7c90 *s2 = func_020aa040(layout, 4, func_020a7b50(&names, 0xb14637e3 + i));
                func_020a7c90(s2, x + 0x36000);
                func_020a7cac(s2, y + 0x3f000);
                grid2[i].func_02050968(s2);
            }
            panel.func_020518fc(&grid[i]);
            panel2.func_020518fc(&grid2[i]);
            i++;
        }
    }

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));
    next.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));
    pager.func_14(0, next.func_10()->y);
    pager.func_24(0xc0000, pager.func_10()->y);
    pager.func_020518a8(2);
    pager.func_02051804(2);
    pager.func_020518fc(&prev);
    pager.func_020518fc(&next);
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x79be6d8f)));
    pager.func_02051858(func_020aa040(layout, 3, func_020a7b50(&names, 0x03398ecd)));

    Unk020a7c90 *s = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc2f94842));
    back.func_02050838(s, false);
    back.func_02050c48(0, 1, -1);
    back.func_20(func_020a7ca4(s) - s->func_10(), func_020a7ca4(s));
    back.func_02050914(2);
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x15f3ba51)));
    back.func_02050968(func_020aa040(layout, 1, func_020a7b50(&names, 0x060bbd76)));
    if (this->mode == 3) {
        back.func_18(true);
    } else if (this->mode == 4) {
        back.func_18(true);
    } else {
        back.func_18(false);
    }
}

Unk02038bcc::~Unk02038bcc() {
    func_0203a464();
    delete layout;
}

void Unk02038bcc::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk02038bcc::func_1c() {
    flags &= ~4;
}

bool Unk02038bcc::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk02038bcc::func_14() {
    return (flags & 4) != 0;
}

bool Unk02038bcc::func_28() {
    return fade.func_shown();
}

bool Unk02038bcc::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_02039a08();
    if (flags & 8) {
        fade.func_duration(0x22);
        if (pages > 1) {
            pager.func_28(0x22);
        }
        back.func_28(0x22);
        func_0203b2e0(&panel);
    } else {
        fade.func_duration(0x10);
        if (pages > 1) {
            pager.func_30(0x22);
        }
        back.func_30(0x22);
        panel.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk02038bcc::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        pager.func_2c(0x22);
        back.func_2c(0x22);
        func_0203b334(&panel);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

/*
 * 94.42 %: the original keeps data_020ae7cc[8] in r11 through the first count
 * loop of mode 3 and reloads &data_020c3fc4 from the pool; here the address
 * is kept in r11 and the key is spilled, so the frame is 4 bytes larger and
 * r3 is saved. Comparing the key list's first word rather than `key` gained
 * 0.4 %.
 */
void Unk02038bcc::func_02039a08() {
    if (flags & 2) {
        return;
    }
    if (mode != 3) {
        func_02029128(owner, true);
    }
    int sel = 0;
    u32 keys[12] = {0};
    int n = 1;
    switch (mode) {
    case 0:
        title = 0xd61;
        keys[0] = 0xe4c371f7;
        break;
    case 1:
        title = 0xd5d;
        keys[0] = data_020ae7cc[13];
        break;
    case 2:
        title = 0xddc;
        keys[0] = data_020ae7cc[0];
        keys[1] = data_020ae7cc[1];
        keys[2] = data_020ae7cc[2];
        keys[3] = data_020ae7cc[3];
        keys[4] = data_020ae7cc[4];
        keys[5] = data_020ae7cc[5];
        keys[6] = data_020ae7cc[6];
        n = 7;
        break;
    case 3:
        for (; sel < 20; sel++) {
            if (func_0205d340(data_020b954c, data_020ae7cc[sel])) {
                keys[0] = data_020ae7cc[sel];
                title = data_020ae81c[sel];
                break;
            }
        }
        break;
    case 4:
        item = func_02028ebc();
        func_020a69ac(back.func_02050a40(1), 2);
        title = 0xef2;
        keys[0] = data_020ae7cc[5];
        break;
    }
    key = keys[0];
    func_020a716c(panel.func_02051ad0(0), title);
    func_020a716c(panel2.func_02051ad0(0), title);
    sel = 0;
    if (mode == 3) {
        if (keys[0] == data_020ae7cc[8] || keys[0] == data_020ae7cc[9] || keys[0] == data_020ae7cc[10] || keys[0] == data_020ae7cc[7]) {
            u32 kind = func_020081dc(&data_020c43a8).unk28 == 0 ? 0x85fba6e5 : 0x1e49458c;
            Unk0205cf00 *def;
            for (def = func_0205f714(&data_020c3fc4, keys[0], 0); def != 0; def = func_0205f714(&data_020c3fc4, keys[0], def)) {
                if (func_listed(def, kind)) {
                    count++;
                }
            }
            if (count > 0) {
                records = new Unk0203a44c[count];
            }
            int j = 0;
            int first = 0;
            if (keys[0] == data_020ae7cc[8] || keys[0] == data_020ae7cc[9]) {
                u32 ks[3] = {keys[0], kind, 0x654b481d};
                Unk020547f8 list;
                func_02054d94(&data_020bfc9c, &list, ks, 3, 3);
                if (list.head != 0) {
                    Unk0205cf00 *d = list.head->def;
                    first = d->id;
                    int icon = func_0205d134(d, 0x9d5bba8e);
                    if (icon == -1) {
                        icon = 0;
                    }
                    records[0].icon = icon;
                    records[0].count = func_02054858(&list, 0)->count;
                    j++;
                    records[0].def = d;
                }
            }
            for (def = func_0205f714(&data_020c3fc4, keys[0], 0); def != 0; def = func_0205f714(&data_020c3fc4, keys[0], def)) {
                if (func_listed(def, kind)) {
                    if (first != func_0205d1b4(def, 0x2a9ad5eb) || first == 0) {
                        int icon = func_0205d134(def, 0x9d5bba8e);
                        if (icon == -1) {
                            icon = 0;
                        }
                        records[j].icon = icon;
                        records[j].count = data_020d60c8.collection->func_0206b6bc(def->id);
                        records[j].def = def;
                        if (records[j].count == 1 && (keys[0] == data_020ae7cc[8] || keys[0] == data_020ae7cc[9])) {
                            Unk02054dc4 *e = func_02054dc4(&data_020bfc9c, def, 0);
                            if (e != 0) {
                                records[j].count = e->count;
                            } else {
                                records[j].count = func_0205d134(def, 0x2b3e6dd7) + 1;
                            }
                        }
                        if (def == data_020b954c) {
                            sel = j;
                        }
                        j++;
                    }
                }
            }
        } else {
            Unk0206b630 *collection = data_020d60c8.collection;
            Unk0205cf00 *def;
            for (def = func_0205f714(&data_020c3fc4, keys[0], 0); def != 0; def = func_0205f714(&data_020c3fc4, keys[0], def)) {
                if (!func_0205d340(def, 0x51a12c57)) {
                    count++;
                }
            }
            if (count > 0) {
                records = new Unk0203a44c[count];
            }
            int j = 0;
            for (def = func_0205f714(&data_020c3fc4, keys[0], 0); def != 0; def = func_0205f714(&data_020c3fc4, keys[0], def)) {
                if (!func_0205d340(def, 0x51a12c57)) {
                    int icon = func_0205d134(def, 0x9d5bba8e);
                    if (icon == -1) {
                        icon = 0;
                    }
                    records[j].icon = icon;
                    records[j].count = collection->func_0206b6bc(def->id);
                    records[j].def = def;
                    if (def == data_020b954c) {
                        sel = j;
                    }
                    j++;
                }
            }
        }
    } else {
        Unk020547f8 list;
        func_02054d94(&data_020bfc9c, &list, keys, n, 1);
        count = list.count;
        if (count > 0) {
            records = new Unk0203a44c[count];
        }
        int target = data_020b954c == 0 ? 0 : data_020b954c->id;
        for (int j = 0; j < count; j++) {
            int icon = func_0205d134(func_02054858(&list, j)->def, 0x9d5bba8e);
            if (icon == -1) {
                icon = 0;
            }
            records[j].icon = icon;
            records[j].count = func_02054858(&list, j)->count;
            records[j].def = func_02054858(&list, j)->def;
            if (target == records[j].def->id) {
                sel = j;
            }
        }
    }
    data_020b954c = 0;
    if (count > 0 || mode != 0) {
        func_020a7cf0(empty, false);
        panel.func_02051ae8(0, 2);
    } else {
        func_020a7c90(empty, panel.func_10()->x + 0x4f000);
        func_020a7cf0(empty, true);
        panel.func_02051ae8(empty, 2);
    }
    pages = count / 12;
    if (count % 12 > 0) {
        pages++;
    }
    page = sel / 12;
    pager.func_34(0x22);
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    if (pages > 1) {
        pager.func_28(0x22);
    }
    panel.func_18(true);
    panel2.func_18(false);
    func_0203afd0(grid, page);
    for (int i = 0; i < 12; i++) {
        grid[i].func_02050bf0(i, -1, -1, -1, -1, -1);
        if (grid[i].func_02050a24()) {
            grid[i].func_020514f0();
            if (mode == 3) {
                int c = records[page * 12 + i].count;
                if (c == 0) {
                    func_0203b220(grid[i].unk64);
                } else if (key == data_020ae7cc[8] || key == data_020ae7cc[9]) {
                    func_0203c254(c - 1, grid[i].unk64, 0);
                }
            }
        }
    }
    func_0203b248(&panel);
    panel.func_34(0x22);
    back.func_34(0x22);
    func_020aa06c(layout, true);
    flags |= 2;
}

Unk0203a44c::Unk0203a44c() {
    icon = -1;
    count = 0;
    def = 0;
}

void Unk02038bcc::func_0203a464() {
    if (!(flags & 2)) {
        return;
    }
    if (records != 0) {
        delete[] records;
    }
    records = 0;
    func_020aa06c(layout, false);
    flags &= ~2;
}

bool Unk02038bcc::func_3c(bool done) {
    if (!func_30() || !(flags & 2)) {
        done = true;
    }
    done = prev.func_0c(done);
    done = next.func_0c(done);
    int k = page * 12;
    for (int i = 0; k < count && i < 12; i++) {
        done = grid[i].func_0c(done);
        if (grid[i].touch.flags & 8) {
            func_02028eec(owner, 0x15, records[k].def, 0);
            func_020292c0(owner, 0x15);
            if (mode == 4) {
                func_02033ea0(item);
            }
        }
        k++;
    }
    if (prev.touch.flags & 8) {
        panel2.func_18(true);
        func_0203afd0(grid2, page);
        func_0203b294(&panel2);
        panel2.func_30(0x22);
        for (int i = 0; i < 12; i++) {
            grid2[i].func_02050bf0(grid[i].unk64, -1, -1, -1, -1, -1);
        }
        flags |= 0x10;
    }
    if (next.touch.flags & 8) {
        page++;
        panel2.func_18(true);
        func_0203afd0(grid2, page);
        func_0203b294(&panel2);
        panel2.func_30(0x22);
        func_0202918c(owner);
        func_0203b248(&panel);
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        switch (mode) {
        case 3:
            if (records != 0) {
                func_02028eec(owner, 3, records[0].def, 0);
            }
            func_020292c0(owner, 3);
            break;
        case 4:
            func_02028eec(owner, 0x11, item, 0);
            func_020292c0(owner, 0x11);
            break;
        }
    }
    return done;
}

/*
 * 99.22 %: in the mirrored loop of the func_44 branch the original computes
 * the grid index in r2 and schedules its mla before the stack arguments;
 * here it uses r1 and the mla follows the stores. The same loop matches in
 * the func_40 branch. Tried: the index as `row * 4 + c`, an index, short or
 * pointer local.
 */
void Unk02038bcc::func_38(bool active) {
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
    panel.func_08();
    panel2.func_08();
    pager.func_08();
    back.func_08();
    if (flags & 0x10) {
        func_020aa158(layout);
        flags &= ~0x10;
        page--;
        func_020a7ce0(pager.func_02051ad0(0));
        panel.func_18(true);
        func_0203afd0(grid, page);
        func_0203b294(&panel);
        panel.func_08();
        func_020291e4(owner);
        return;
    }
    if (fade.func_shown()) {
        if (panel.func_38() && grid2[0].func_02050a24()) {
            panel2.func_18(false);
        }
        if (panel.func_40()) {
            panel2.func_18(false);
        }
        if (!(flags & 8)) {
            if (panel.func_4c()) {
                int n = 0;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                        if (grid2[n].func_10()->x >= panel.func_10()->x) {
                            grid2[n].func_18(false);
                            int m = c + row * 4;
                            int k = page * 12 + m;
                            if (grid[m].unk64 < 0) {
                                grid[m].func_02050bf0(grid2[n].unk64, -1, -1, -1, -1, -1);
                                if (k < count) {
                                    grid[m].func_020514f0();
                                    if (mode == 3) {
                                        int v = records[k].count;
                                        if (v == 0) {
                                            func_0203b220(grid[m].unk64);
                                        } else if (key == data_020ae7cc[8] || key == data_020ae7cc[9]) {
                                            func_0203c254(v - 1, grid[m].unk64, 0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (panel.func_48()) {
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
                                    if (mode == 3) {
                                        int v = records[k].count;
                                        if (v == 0) {
                                            func_0203b220(grid2[m].unk64);
                                        } else if (key == data_020ae7cc[8] || key == data_020ae7cc[9]) {
                                            func_0203c254(v - 1, grid2[m].unk64, 0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else if (panel.func_44()) {
                int n = 0;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                        grid2[c + row * 4].func_02050bf0(grid[n].unk64, -1, -1, -1, -1, -1);
                    }
                }
                panel.func_18(true);
                func_0203afd0(grid, page);
                func_0203b294(&panel);
                panel.func_30(0x22);
                for (int i = 0; i < 12; i++) {
                    grid[i].func_02050bf0(grid2[i].unk64, -1, -1, -1, -1, -1);
                }
                panel.func_08();
            } else if (panel.func_40()) {
                int n = 0;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                        grid[c + row * 4].func_02050bf0(grid2[n].unk64, -1, -1, -1, -1, -1);
                    }
                }
            }
        }
    }
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0203a464();
    }
}

void Unk02038bcc::func_18() {
    flags |= 4;
}

void Unk02038bcc::func_0203afd0(Unk02050640 *buttons, int page) {
    int i;
    int k = page * 12;
    for (i = 0; k < count && i < 12; k++, i++) {
        buttons[i].func_020508ac(func_0206446c(records[k].icon));
        buttons[i].func_02050c48(func_020644bc(records[k].icon), -1, -1);
        buttons[i].func_02050bb4(-1, -1, func_020644b0(records[k].icon), -1);
        if (records[k].count <= 0) {
            buttons[i].flags |= 8;
        } else {
            buttons[i].flags &= ~8;
        }
        buttons[i].func_18(true);
        if (records[k].count < 2 || mode == 3) {
            func_020a7cf0(buttons[i].func_02050a40(0), false);
        } else {
            func_020a7ce0(buttons[i].func_02050a40(0));
        }
    }
    for (; i < 12; i++) {
        buttons[i].func_18(false);
    }
}

static void *func_0203b148(u32 id, void *user) {
    Unk02038bcc *self = (Unk02038bcc *)user;
    int k = id - 0x800000;
    if (k > 0 && k < 0x19) {
        int c = 0;
        int index;
        if (k < 0xd) {
            index = k - 1;
        } else {
            index = k - 0xd;
        }
        int n = self->page * 12 + index;
        if (n < self->count) {
            c = self->records[n].count;
        }
        func_02082a2c(self->text, "%d", c);
        return self->text;
    } else if (k == 0x19) {
        func_02082a2c(self->text, "%d", self->page + 1);
        return self->text;
    } else if (k == 0x1a) {
        func_02082a2c(self->text, "/%d", self->pages);
        return self->text;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

static const u16 data_020ae8e8[16] = {0};

void Unk02038bcc::func_0203b220(int index) {
    Unk020916a4::func_02091830()->func_02092098((void *)data_020ae8e8, index * 16 + 1, 0xf);
}

void Unk02038bcc::func_0203b248(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}

void Unk02038bcc::func_0203b294(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk02038bcc::func_0203b2e0(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk02038bcc::func_0203b334(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}

void func_0203b388(Unk0205cf00 *def) {
    data_020b954c = def;
}
