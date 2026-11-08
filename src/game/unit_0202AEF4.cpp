/*
 * Unit 0x0202AEF4-0x0202CDF0: the category screen (Unk0202aef4, 0x8EC bytes,
 * vtable 0x020B92BC) on the screen base Unk0203c188. It lists twenty object
 * categories, four per page, with the collected and total objects of each; a
 * press opens the category. It opens on the page of data_020b92b0.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots of
 * the previous screen (unit_02029B80.cpp); the end is the recipe screen
 * (unit_0202CDF0.cpp). `.data` holds the current object, this class's vtable
 * with its header and the three count formats. Real file name unknown.
 *
 * It holds the kept copy 0x0202C050 of the widget base slot 20, right after
 * func_30, its first user: written as a plain definition, as slot 7 in
 * unit_0202FDDC.cpp.
 *
 * Not complete: two functions are below 100 % (comments above them).
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"
#include "game/unk_sortedset.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An object of the database: only the id is used here. */
struct Unk0205cf00 {
    int unk0[3];
    int id;
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

struct Unk020c43a8;
struct Unk020c3fc4;

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern Unk020c43a8 data_020c43a8;
extern Unk020c3fc4 data_020c3fc4;
extern const int data_020ae7cc[];
extern const int data_020ae81c[];

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
const char *func_020a00a0(void *texts, u32 id);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
Unk0205cf00 *func_0205f714(Unk020c3fc4 *db, int key, Unk0205cf00 *rec);
bool func_0205d340(Unk0205cf00 *item, u32 key);
Unk020081dc func_020081dc(Unk020c43a8 *p);
bool func_0206757c(Unk020c43a8 *p, int mask);
void func_02067178(Unk020c43a8 *p, int hash);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a7ce0(Unk020a7c90 *s);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
void func_0202918c(Unk0203c188Owner *owner);
void func_020291e4(Unk0203c188Owner *owner);
void func_0202923c(Unk0203c188Owner *owner);
int sprintf(char *buf, const char *fmt, ...);
void func_0202cdc0(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b92b0 = 0;
#pragma explicit_zero_data reset

/* A category of the list (0x14 bytes). */
struct Unk0202aef4Entry {
    Unk0202aef4Entry() {
        icon = 0;
        text = 0;
        key = 0;
        found = 0;
        total = 0;
    }

    Unk0202aef4Entry(int icon, int text, int key) {
        this->icon = icon;
        this->text = text;
        this->key = key;
        found = 0;
        total = 0;
    }

    int icon;
    int text;
    int key;
    int found;
    int total;
};

class Unk0202aef4 : public Unk0203c188 {
public:
    Unk0202aef4(Unk0203c188Owner *owner);
    virtual ~Unk0202aef4();
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
    virtual bool func_34();
    virtual bool func_2c();

    void func_0202c290();
    void func_0202c430();
    void func_0202ca5c(Unk02050640 *list, int page);
    void func_0202cc80(Unk02051704 *p);
    void func_0202cccc(Unk02051704 *p);
    void func_0202cd18(Unk02051704 *p);
    void func_0202cd6c(Unk02051704 *p);

    Unk0202aef4Entry entries[20];
    int pageCount;
    short page;
    Unk020a9d58 *layout;
    Unk02050640 buttons[4];
    Unk02050640 buttons2[4];
    Unk02050640 next;
    Unk02050640 prev;
    Unk02050640 back;
    char num[0x20];
    Unk02051704 panel;
    Unk02051704 panel2;
    Unk02051704 pager;
    Unk02051704 panel3;
};

static inline u32 func_outfit_key() {
    Unk020081dc outfit = func_020081dc(&data_020c43a8);
    return outfit.unk28 == 0 ? 0x85fba6e5 : 0x1e49458c;
}

static void *func_0202cb98(u32 id, void *user);

/*
 * 90.75 %: the frame size matches. The original materializes the table's
 * constants early in r3-r6 and loads each text and key on its own, and its stack
 * slots are ordered otherwise (the outfit below the name list, the three offsets
 * first). Tried: direct stores, an inline setter, temporaries, pointer and zero
 * locals (all the same code); the offsets as locals at several scopes, the outfit
 * in a block or an inline helper. The table set-up shares its basic block with the
 * seven member constructor calls before it and is scheduled partly in register
 * pressure mode; the original fills each load delay with the constant of a later
 * entry, which no selection rule picks with the constants generated in entry
 * order. A block split forced at the table start, alone or with a second one
 * inside the table, does not get closer.
 */
Unk0202aef4::Unk0202aef4(Unk0203c188Owner *owner)
    : Unk0203c188(owner), pageCount(0), page(0) {
    entries[0] = Unk0202aef4Entry(9, data_020ae81c[0], data_020ae7cc[0]);
    entries[1] = Unk0202aef4Entry(10, data_020ae81c[1], data_020ae7cc[1]);
    entries[2] = Unk0202aef4Entry(11, data_020ae81c[2], data_020ae7cc[2]);
    entries[3] = Unk0202aef4Entry(12, data_020ae81c[3], data_020ae7cc[3]);
    entries[4] = Unk0202aef4Entry(13, data_020ae81c[4], data_020ae7cc[4]);
    entries[5] = Unk0202aef4Entry(14, data_020ae81c[5], data_020ae7cc[5]);
    entries[6] = Unk0202aef4Entry(15, data_020ae81c[6], data_020ae7cc[6]);
    entries[7] = Unk0202aef4Entry(16, data_020ae81c[7], data_020ae7cc[7]);
    entries[8] = Unk0202aef4Entry(17, data_020ae81c[8], data_020ae7cc[8]);
    entries[9] = Unk0202aef4Entry(18, data_020ae81c[9], data_020ae7cc[9]);
    entries[10] = Unk0202aef4Entry(19, data_020ae81c[10], data_020ae7cc[10]);
    entries[11] = Unk0202aef4Entry(0, data_020ae81c[11], data_020ae7cc[11]);
    entries[12] = Unk0202aef4Entry(2, data_020ae81c[12], data_020ae7cc[12]);
    entries[13] = Unk0202aef4Entry(6, data_020ae81c[13], data_020ae7cc[13]);
    entries[14] = Unk0202aef4Entry(7, data_020ae81c[14], data_020ae7cc[14]);
    entries[15] = Unk0202aef4Entry(1, data_020ae81c[15], data_020ae7cc[15]);
    entries[16] = Unk0202aef4Entry(8, data_020ae81c[16], data_020ae7cc[16]);
    entries[17] = Unk0202aef4Entry(3, data_020ae81c[17], data_020ae7cc[17]);
    entries[18] = Unk0202aef4Entry(5, data_020ae81c[19], data_020ae7cc[19]);
    entries[19] = Unk0202aef4Entry(4, data_020ae81c[18], data_020ae7cc[18]);

    Unk020c3fc4 *db = &data_020c3fc4;
    Unk0206b630 *collection = data_020d60c8.collection;
    for (int i = 0; i < 20; i++) {
        if ((u32)(i - 7) <= 3) {
            u32 key = func_outfit_key();
            int total = 0;
            int found = 0;
            Unk0205cf00 *def = func_0205f714(db, entries[i].key, 0);
            while (def != 0) {
                if (func_0205d340(def, key) && !func_0205d340(def, 0x654b481d)
                    && !func_0205d340(def, 0x291d04a3) && !func_0205d340(def, 0x51a12c57)) {
                    if (collection->func_0206b6bc(def->id)) {
                        found++;
                    }
                    total++;
                }
                def = func_0205f714(db, entries[i].key, def);
            }
            entries[i].found = found;
            entries[i].total = total;
        } else {
            int total = 0;
            int found = 0;
            Unk0205cf00 *def = func_0205f714(db, entries[i].key, 0);
            while (def != 0) {
                if (!func_0205d340(def, 0x51a12c57)) {
                    if (collection->func_0206b6bc(def->id)) {
                        found++;
                    }
                    total++;
                }
                def = func_0205f714(db, entries[i].key, def);
            }
            entries[i].found = found;
            entries[i].total = total;
        }
    }

    Unk020a7af4Entry nameEntries[0x46];
    Unk020a7af4 names(nameEntries, 0x46);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x7f120996, layout, &names);
    func_020a9db8(layout, func_0202cb98, this);

    panel.func_14(-0x23000, 0);
    panel.func_020518a8(4);
    panel.func_02051804(2);
    panel.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xdefd2411)));
    panel.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xb0943cd7)));
    panel2.func_14(-0x23000, 0);
    panel2.func_020518a8(4);
    panel2.func_02051804(2);
    panel2.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0xcbddf485)));
    panel2.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x96b55b60)));

    int row = 0;
    int n = row;
    for (; row < 2; row++) {
        for (int col = 0; col < 2; col++) {
            int x = FX32(col * 0x5c) + 0x37000;
            int y = FX32(row * 0x4e) + 0x24000;
            buttons[n].func_02050bb4(n, -1, -1, -1);
            buttons[n].flags |= 2;
            buttons[n].func_02050914(2);
            buttons2[n].func_02050bb4(n + 4, -1, -1, -1);
            buttons2[n].flags |= 2;
            buttons2[n].func_02050914(2);

            buttons[n].func_02050838(
                func_020aa040(layout, 0xb, func_020a7b50(&names, 0x109be2e7 + n)), false);
            buttons[n].func_14(x, y);
            Unk020a7c90 *s1 = func_020aa040(layout, 4, func_020a7b50(&names, 0x31095e70 + n));
            int x1 = x - 0xa000;
            func_020a7c90(s1, x1);
            func_020a7cac(s1, y + 0x30000);
            buttons[n].func_02050968(s1);
            Unk020a7c90 *s2 = func_020aa040(layout, 4, func_020a7b50(&names, 0xf46eb883 + n));
            int x2 = x - 0x2a000;
            func_020a7c90(s2, x2);
            int y2 = y - 0xe000;
            func_020a7cac(s2, y2);
            buttons[n].func_02050968(s2);

            buttons2[n].func_02050838(
                func_020aa040(layout, 0xb, func_020a7b50(&names, 0x6d7e2970 + n)), false);
            buttons2[n].func_14(x, y);
            Unk020a7c90 *s3 = func_020aa040(layout, 4, func_020a7b50(&names, 0x1ddb2ae4 + n));
            func_020a7c90(s3, x1);
            func_020a7cac(s3, y + 0x30000);
            buttons2[n].func_02050968(s3);
            Unk020a7c90 *s4 = func_020aa040(layout, 4, func_020a7b50(&names, 0x5150ff2b + n));
            func_020a7c90(s4, x2);
            func_020a7cac(s4, y2);
            buttons2[n].func_02050968(s4);

            panel.func_020518fc(&buttons[n]);
            panel2.func_020518fc(&buttons2[n]);
            n++;
        }
    }

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    Unk020a7c90 *sprite = func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a));
    prev.func_020508a4(sprite);
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

    panel3.func_14(-0x23000, 0);
    panel3.func_02051804(3);
    panel3.func_020518a8(1);
    panel3.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x36d9d2f2)));
    panel3.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xf72b9981)));
    panel3.func_02051858(func_020aa040(layout, 4, func_020a7b50(&names, 0x96c99379)));
    back.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x63b94c03)), false);
    back.func_02050c48(0, 1, -1);
    back.func_02050c64(0, 1, 2);
    back.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xee1a47e2)));
    back.func_02050914(1);
    back.func_02050968(func_020aa040(layout, 4, func_020a7b50(&names, 0x63412fed)));
    panel3.func_020518fc(&back);

    if (!func_0206757c(&data_020c43a8, 0x400)) {
        flags |= 0x40;
    }
}

Unk0202aef4::~Unk0202aef4() {
    func_0202c430();
    delete layout;
}

void Unk0202aef4::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0202aef4::func_1c() {
    flags &= ~4;
}

bool Unk0202aef4::func_30() {
    return func_28() && !func_14() && !panel.func_50() && !panel2.func_50() && !panel3.func_50();
}

bool Unk020b9e88::func_50() {
    return state == 0 || state == 3;
}

bool Unk0202aef4::func_14() {
    return (flags & 4) != 0;
}

bool Unk0202aef4::func_28() {
    return fade.func_shown();
}

bool Unk0202aef4::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0202c290();
    if (flags & 8) {
        fade.func_duration(0x22);
        if (!(flags & 0x40)) {
            if (pageCount > 1) {
                pager.func_28(0x22);
            }
            func_0202cd18(&panel);
        } else {
            func_0202cd18(&panel3);
        }
    } else {
        fade.func_duration(0x10);
        if (!(flags & 0x40)) {
            if (pageCount > 1) {
                pager.func_30(0x22);
            }
            panel.func_30(0x22);
        } else {
            panel3.func_30(0x22);
        }
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0202aef4::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        if (!(flags & 0x40)) {
            pager.func_2c(0x22);
            func_0202cd6c(&panel);
        } else {
            func_0202cd6c(&panel3);
        }
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk0202aef4::func_0202c290() {
    if (flags & 2) {
        return;
    }
    int found = 0;
    if (data_020b92b0 != 0) {
        for (int i = 0; i < 20; i++) {
            if (func_0205d340(data_020b92b0, entries[i].key)) {
                found = i;
            }
        }
    }
    data_020b92b0 = 0;
    pageCount = 5;
    page = found / 4;
    pager.func_34(0x22);
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    panel.func_18(true);
    panel2.func_18(false);
    func_0202ca5c(buttons, page);
    func_0202cc80(&panel);
    panel.func_34(0x22);
    if (flags & 0x40) {
        panel3.func_18(true);
        func_0202cc80(&panel3);
        panel3.func_34(0x22);
        panel.func_18(false);
    }
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk0202aef4::func_0202c430() {
    if (flags & 2) {
        func_020aa06c(layout, false);
        flags &= ~2;
    }
}

bool Unk0202aef4::func_3c(bool done) {
    if (!func_30() || !(flags & 2)) {
        done = true;
    }
    int i;
    int n;
    done = prev.func_0c(done);
    done = next.func_0c(done);
    n = 0;
    for (i = page * 4; i < 20 && n < 4; i++, n++) {
        done = buttons[n].func_0c(done);
        if (buttons[n].touch.flags & 8) {
            func_02028eec(owner, 0x1a, func_0205f714(&data_020c3fc4, entries[i].key, 0), 0);
            func_020292c0(owner, 0x1a);
        }
    }
    if (prev.touch.flags & 8) {
        panel2.func_18(true);
        func_0202ca5c(buttons2, page);
        func_0202cccc(&panel2);
        panel2.func_30(0x22);
        flags |= 0x30;
    }
    if (next.touch.flags & 8) {
        page++;
        panel2.func_18(true);
        func_0202ca5c(buttons2, page);
        func_0202cccc(&panel2);
        panel2.func_30(0x22);
        func_0202918c(owner);
        func_0202cc80(&panel);
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        func_0202923c(owner);
        func_0202cd6c(&panel3);
        func_02067178(&data_020c43a8, 0xce6c7716);
    }
    return done;
}

void Unk0202aef4::func_38(bool active) {
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
    if (flags & 0x20) {
        if (flags & 0x10) {
            func_0202cccc(&panel);
            func_020291e4(owner);
            flags &= ~0x10;
        } else {
            page--;
            func_020a7ce0(pager.func_02051ad0(0));
            func_0202ca5c(buttons, page);
            flags &= ~0x20;
        }
    }
    if (page < 1) {
        prev.flags |= 8;
    } else {
        prev.flags &= ~8;
    }
    if (page >= pageCount - 1) {
        next.flags |= 8;
    } else {
        next.flags &= ~8;
    }
    panel.func_08();
    panel2.func_08();
    pager.func_08();
    panel3.func_08();
    if (fade.func_shown()) {
        if (panel.func_38()) {
            panel2.func_18(false);
        }
        if (!(flags & 8) && panel.func_44()) {
            panel.func_18(true);
            func_0202ca5c(buttons, page);
            func_0202cccc(&panel);
            panel.func_30(0x22);
            panel.func_08();
        }
    }
    if (panel3.func_44()) {
        panel3.func_18(false);
        panel.func_18(true);
        func_0202cd18(&panel);
        if (pageCount > 1) {
            pager.func_28(0x22);
        }
        flags &= ~0x40;
    }
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0202c430();
    }
}

void Unk0202aef4::func_18() {
    flags |= 4;
}

void Unk0202aef4::func_0202ca5c(Unk02050640 *list, int page) {
    int n = 0;
    for (int i = page * 4; i < 20 && n < 4; i++, n++) {
        int icon = entries[i].icon;
        if (icon < 0x10) {
            list[n].func_020508ac(0xa4a8e6e3);
        } else {
            list[n].func_020508ac(0x10974931);
            icon -= 0x10;
        }
        list[n].func_02050c48(icon, -1, -1);
        list[n].func_02050bf0(-1, -1, -1, icon, -1, -1);
        list[n].func_020514f0();
        list[n].func_18(true);
        func_020a7ce0(list[n].func_02050a40(0));
        func_020a716c(list[n].func_02050a40(1), entries[i].text);
    }
    if (n < 4) {
        for (; n < 4; n++) {
            list[n].func_18(false);
        }
    }
}

static void *func_0202cb98(u32 id, void *user) {
    Unk0202aef4 *screen = (Unk0202aef4 *)user;
    int n = id - 0x800000;
    if (n > 0 && n < 0xd) {
        int index = n < 7 ? n - 1 : n - 7;
        int found = 0;
        int total = 0;
        index += screen->page * 4;
        if (index < 20) {
            found = screen->entries[index].found;
            total = screen->entries[index].total;
        }
        sprintf(screen->num, "%d/%d", found, total);
        return screen->num;
    }
    if (n == 0x1d) {
        sprintf(screen->num, "%d", screen->page + 1);
        return screen->num;
    }
    if (n == 0x1e) {
        sprintf(screen->num, "/%d", screen->pageCount);
        return screen->num;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

void Unk0202aef4::func_0202cc80(Unk02051704 *p) {
    p->func_20(0x100000, -0x23000);
    p->func_30(0x22);
    p->func_2c(0x22);
}

void Unk0202aef4::func_0202cccc(Unk02051704 *p) {
    p->func_20(0x100000, -0x23000);
    p->func_34(0x22);
    p->func_28(0x22);
}

void Unk0202aef4::func_0202cd18(Unk02051704 *p) {
    p->func_20(0xffeba000, -0x23000);
    p->func_34(0x22);
    p->func_28(0x22);
}

void Unk0202aef4::func_0202cd6c(Unk02051704 *p) {
    p->func_20(0xffeba000, -0x23000);
    p->func_30(0x22);
    p->func_2c(0x22);
}

void func_0202cdc0(Unk0205cf00 *def) {
    data_020b92b0 = def;
}

bool Unk0202aef4::func_34() {
    return true;
}

bool Unk0202aef4::func_2c() {
    return fade.func_hidden();
}
