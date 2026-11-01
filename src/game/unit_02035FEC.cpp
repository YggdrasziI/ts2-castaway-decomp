/*
 * Unit 0x02035FEC-0x02038BCC: the tabbed object list screen (Unk02035fec,
 * 0x11FC bytes, vtable 0x020B94F4) on the screen base Unk0203c188, built by
 * its owner with a mode (0 to 4, 0x020293CC to 0x020296FC). The mode picks
 * the title, up to five tabs with their texts, palette and colours, and per
 * tab up to six keys taken from data_020b9480 (three groups of the twenty
 * keys of data_020ae7cc). The objects of the current tab are read from the
 * inventory as records (Unk020388ac), shown twelve per page on a 4 x 3 grid
 * of buttons with a second grid for the page slides, the count of each
 * object, a previous / next pair and a "nothing" sprite whose text follows
 * the mode and the tab. In mode 1 the keys also need the kind of the
 * player, and the objects the player wears get a mark. A press reports the
 * object to the owner; a tab press switches the list. func_02038b38 sets
 * data_020b947c, the object to show first; func_02038b48 gives the group of
 * data_020b9480 that holds a key of an object.
 *
 * Bounds: hypothesis. The start is the constructor, after func_02035fc0
 * (called by the owner of the screen with vtable 0x020B9428); the end is the
 * object list screen (unit_02038BCC.cpp). `.rodata` holds the colour list
 * initializer and an unreferenced word 0x50 (the size of the name list, as
 * in unit_0203C2E8.cpp); `.data` the object shown first, the key groups
 * (filled by the static initializer 0x020AD0D8), this class's vtable with
 * its header and the formats of the text function. Real file name unknown.
 *
 * The last word of `.rodata` (0x020AE8D8, 0x50, never loaded) is a local `static
 * const`, as in unit_0203C2E8.cpp.
 */

#include "game/unk_screen.h"
#include "game/unk_catalog.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An object of the database: only its id. */
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

/* The owner of the screens: only the word tested before the guide step. */
struct Unk0203c188OwnerState {
    u8 unk0[0x62c];
    void *unk62c;
};

/* The survival guide animation of the player (unit_02055118.cpp): only the fields used here. */
struct Unk02055118 {
    int state;
    void *obj;
    u8 shown;
    u8 unk9;
};

/* The main game state (func_0206bce0): only its guide. */
struct Unk0206bce0 {
    u8 unk0[0x14c];
    Unk02055118 guide;
};

/* A record of the list (0x10 bytes). */
class Unk020388ac {
public:
    Unk020388ac();

    int icon;
    int count;
    Unk0205cf00 *def;
    u32 flags;
};

struct Unk020bfc9c;

extern Unk020d6240 data_020d6240;
extern Unk020c43a8 data_020c43a8;
extern Unk020bfc9c data_020bfc9c;
extern const int data_020ae7cc[20];

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_0205d340(Unk0205cf00 *item, u32 key);
int func_0205d134(Unk0205cf00 *item, u32 key);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
Unk020081dc func_020081dc(Unk020c43a8 *p);
u32 func_0206446c(int key);
int func_020644b0(int key);
short func_020644bc(int key);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a716c(Unk020a7c90 *s, int text);
void func_020a7ce0(Unk020a7c90 *s);
void func_020a7d30(Unk020a7c90 *s, int color);
void *func_020a8388(Unk020a7c90 *s);
void func_020a9240(Unk020a7c90 *s, void *frame);
void func_0203c254(int value, int index, int main);
void func_02029128(Unk0203c188Owner *owner, bool set);
void func_0202918c(Unk0203c188Owner *owner);
void func_020291e4(Unk0203c188Owner *owner);
void func_0202923c(Unk0203c188Owner *owner);
void func_020292c0(Unk0203c188Owner *owner, int a);
void func_02028eec(Unk0203c188Owner *owner, int a, Unk0205cf00 *def, void *item);
Unk0206bce0 *func_0206bce0();
void func_02055220(Unk02055118 *p, int state, int count);
int sprintf(char *buf, const char *fmt, ...);
const char *func_020a00a0(void *texts, int id);
void func_02038b38(Unk0205cf00 *def);
int func_02038b48(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b947c = 0;
#pragma explicit_zero_data reset

static const u32 data_020b9480[3][9] = {
    {data_020ae7cc[0], data_020ae7cc[1], data_020ae7cc[2], data_020ae7cc[3], data_020ae7cc[4], data_020ae7cc[5],
     data_020ae7cc[6]},
    {data_020ae7cc[7], data_020ae7cc[8], data_020ae7cc[9], data_020ae7cc[10]},
    {data_020ae7cc[11], data_020ae7cc[12], data_020ae7cc[13], data_020ae7cc[14], data_020ae7cc[15],
     data_020ae7cc[16], data_020ae7cc[17], data_020ae7cc[18], data_020ae7cc[19]},
};

class Unk02035fec : public Unk0203c188 {
public:
    Unk02035fec(Unk0203c188Owner *owner, int mode);
    virtual ~Unk02035fec();
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
    virtual void func_44() {}

    void func_02037000();
    void func_020374c4();
    void func_0203815c(Unk02050640 *buttons, int page);
    void func_02038344(short first);
    void func_020389f8(Unk02051704 *panel);
    void func_02038a44(Unk02051704 *panel);
    void func_02038a90(Unk02051704 *panel);
    void func_02038ae4(Unk02051704 *panel);

    int mode;
    Unk020388ac *records;
    int count;
    int pages;
    short page;
    short tabCount;
    short tab;
    Unk020a9d58 *layout;
    Unk02050640 grid[12];
    Unk02050640 grid2[12];
    Unk02050640 tabs[5];
    u32 keys[5][6];
    int tabTexts[5];
    int title;
    Unk02050640 next;
    Unk02050640 prev;
    char text[0x20];
    Unk020a7c90 *mark;
    Unk02050640 *marked;
    Unk020a7c90 *empty;
    Unk02051704 panel;
    Unk02051704 panel2;
    Unk02051704 pager;
};

static void *func_020388c8(u32 id, void *user);

Unk02035fec::Unk02035fec(Unk0203c188Owner *owner, int mode)
    : Unk0203c188(owner), mode(mode), records(0), count(0), pages(0), page(0), tabCount(0), tab(0), marked(0) {
    static const int size = 0x50;
    Unk020a7af4Entry entries[size];
    Unk020a7af4 names(entries, size);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x7b0ccdee, layout, &names);
    func_020a9db8(layout, func_020388c8, this);

    panel.func_14(-0x23000, 0);
    panel.func_020518a8(0xc);
    panel.func_02051804(3);
    { u32 i_ = func_020a7b50(&names, 0xdefd2411); Unk020a7c90 *s_ = func_020aa040(layout, 4, i_); panel.func_02051858(s_); }
    { u32 i_ = func_020a7b50(&names, 0xb0943cd7); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); panel.func_02051858(s_); }
    { u32 i_ = func_020a7b50(&names, 0x57d14c35); Unk020a7c90 *s_ = func_020aa040(layout, 4, i_); empty = s_; }
    panel2.func_14(-0x23000, 0);
    panel2.func_020518a8(0xc);
    panel2.func_02051804(2);
    { u32 i_ = func_020a7b50(&names, 0xcbddf485); Unk020a7c90 *s_ = func_020aa040(layout, 4, i_); panel2.func_02051858(s_); }
    { u32 i_ = func_020a7b50(&names, 0x96b55b60); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); panel2.func_02051858(s_); }

    int x;
    int row = 0;
    int i = row;
    for (; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            x = FX32(col * 40);
            int y = FX32(row * 50);
            grid[i].flags |= 2;
            grid[i].func_02050914(2);
            grid2[i].flags |= 2;
            grid2[i].func_02050914(2);
            if (i < 10) {
                { u32 i_ = func_020a7b50(&names, 0x109be2e7 + i); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); grid[i].func_02050838(s_, false); }
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                u32 i_s = func_020a7b50(&names, 0x31095e70 + i); Unk020a7c90 *s = func_020aa040(layout, 4, i_s);
                func_020a7c90(s, x + 0x36000);
                func_020a7cac(s, y + 0x3f000);
                grid[i].func_02050968(s);
                { u32 i_ = func_020a7b50(&names, 0x6d7e2970 + i); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); grid2[i].func_02050838(s_, false); }
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                u32 i_s2 = func_020a7b50(&names, 0x1ddb2ae4 + i); Unk020a7c90 *s2 = func_020aa040(layout, 4, i_s2);
                func_020a7c90(s2, x + 0x36000);
                func_020a7cac(s2, y + 0x3f000);
                grid2[i].func_02050968(s2);
            } else {
                { u32 i_ = func_020a7b50(&names, 0x5c0f4364 + i); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); grid[i].func_02050838(s_, false); }
                grid[i].func_14(x + 0x36000, y + 0x1e000);
                u32 i_s = func_020a7b50(&names, 0x044df6c0 + i); Unk020a7c90 *s = func_020aa040(layout, 4, i_s);
                func_020a7c90(s, x + 0x36000);
                func_020a7cac(s, y + 0x3f000);
                grid[i].func_02050968(s);
                { u32 i_ = func_020a7b50(&names, 0x48e09799 + i); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); grid2[i].func_02050838(s_, false); }
                grid2[i].func_14(x + 0x36000, y + 0x1e000);
                u32 i_s2 = func_020a7b50(&names, 0xb14637e3 + i); Unk020a7c90 *s2 = func_020aa040(layout, 4, i_s2);
                func_020a7c90(s2, x + 0x36000);
                func_020a7cac(s2, y + 0x3f000);
                grid2[i].func_02050968(s2);
            }
            grid[i].func_02050968(0);
            grid2[i].func_02050968(0);
            panel.func_020518fc(&grid[i]);
            panel2.func_020518fc(&grid2[i]);
            i++;
        }
    }

    for (int i = 0; i < 5; i++) {
        { u32 i_ = func_020a7b50(&names, 0x326d005c + i); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); tabs[i].func_02050838(s_, false); }
        tabs[i].func_02050c48(0, 1, -1);
        tabs[i].flags |= 2;
        tabs[i].func_14(0, FX32(31 + i * 30));
        tabs[i].func_02050914(1);
        u32 i_s = func_020a7b50(&names, 0xc29281eb + i); Unk020a7c90 *s = func_020aa040(layout, 1, i_s);
        func_020a7c90(s, 0x18000);
        func_020a7cac(s, FX32(36 + i * 30));
        tabs[i].func_02050968(s);
    }

    { u32 i_ = func_020a7b50(&names, 0x260323f0); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); prev.func_02050838(s_, false); }
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    { u32 i_ = func_020a7b50(&names, 0xcc3efd4a); Unk020a7c90 *s_ = func_020aa040(layout, 1, i_); prev.func_020508a4(s_); }
    { u32 i_ = func_020a7b50(&names, 0xcba0dc91); Unk020a7c90 *s_ = func_020aa040(layout, 0xb, i_); next.func_02050838(s_, false); }
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    { u32 i_ = func_020a7b50(&names, 0x8f6a6fb5); Unk020a7c90 *s_ = func_020aa040(layout, 1, i_); next.func_020508a4(s_); }
    pager.func_14(0, next.func_10()->y);
    pager.func_24(0xc0000, pager.func_10()->y);
    pager.func_020518a8(2);
    pager.func_02051804(2);
    pager.func_020518fc(&prev);
    pager.func_020518fc(&next);
    { u32 i_ = func_020a7b50(&names, 0x79be6d8f); Unk020a7c90 *s_ = func_020aa040(layout, 3, i_); pager.func_02051858(s_); }
    { u32 i_ = func_020a7b50(&names, 0x03398ecd); Unk020a7c90 *s_ = func_020aa040(layout, 3, i_); pager.func_02051858(s_); }
    { u32 i_ = func_020a7b50(&names, 0x5451bab4); Unk020a7c90 *s_ = func_020aa040(layout, 1, i_); mark = s_; }
}

Unk02035fec::~Unk02035fec() {
    func_020374c4();
    delete layout;
}

void Unk02035fec::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk02035fec::func_1c() {
    flags &= ~4;
}

bool Unk02035fec::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk02035fec::func_14() {
    return (flags & 4) != 0;
}

bool Unk02035fec::func_28() {
    return fade.func_shown();
}

bool Unk02035fec::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_02037000();
    if (flags & 8) {
        fade.func_duration(0x22);
        for (int i = 0; i < tabCount; i++) {
            tabs[i].func_28(0x22);
        }
        if (pages > 1) {
            pager.func_28(0x22);
        }
        func_02038a90(&panel);
    } else {
        fade.func_duration(0x10);
        for (int i = 0; i < tabCount; i++) {
            tabs[i].func_30(0x22);
        }
        if (pages > 1) {
            pager.func_30(0x22);
        }
        panel.func_30(0x22);
    }
    fade.timer = 0;
    fade.state = 0;
    if (mode == 1 && ((Unk0203c188OwnerState *)owner)->unk62c != 0) {
        Unk02055118 *guide = &func_0206bce0()->guide;
        if (!guide->shown) {
            guide->unk9 = 0;
            func_02055220(guide, 0x37, 0);
        }
    }
    return false;
}

bool Unk02035fec::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        for (int i = 0; i < tabCount; i++) {
            tabs[i].func_20(-0x31000, tabs[i].func_10()->x);
            tabs[i].func_30(0x22);
            tabs[i].func_2c(0x22);
        }
        pager.func_2c(0x22);
        func_02038ae4(&panel);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk02035fec::func_02037000() {
    int t;
    bool found;
    int k;
    int base;
    if (flags & 2) {
        return;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            keys[i][j] = 0;
        }
    }
    int colors[5] = {0xe, 0xe, 0xe, 0xe, 0xe};
    int palette = 0;
    base = palette;
    tabCount = 0;
    switch (mode) {
    case 0:
        title = 0xcc5;
        tabTexts[0] = 0xcc6;
        tabTexts[1] = 0xcc7;
        tabTexts[2] = 0xcc8;
        tabTexts[3] = 0xcc9;
        colors[2] = 0xd;
        tabCount = 4;
        palette = 0x0cab8e7b;
        keys[0][0] = data_020b9480[0][0];
        keys[1][0] = data_020b9480[0][1];
        keys[1][1] = data_020b9480[0][2];
        keys[2][0] = data_020b9480[0][3];
        keys[2][1] = data_020b9480[0][4];
        keys[2][2] = data_020b9480[0][5];
        keys[3][0] = data_020b9480[0][6];
        break;
    case 1:
        title = 0xccb;
        tabTexts[0] = 0xccc;
        tabTexts[1] = 0xccd;
        tabTexts[2] = 0xcce;
        tabTexts[3] = 0xccf;
        tabTexts[4] = 0;
        colors[0] = 0xd;
        colors[3] = 0xd;
        tabCount = 4;
        palette = 0xaf5a1f17;
        keys[0][0] = data_020b9480[1][0];
        keys[1][0] = data_020b9480[1][1];
        keys[2][0] = data_020b9480[1][2];
        keys[3][0] = data_020b9480[1][3];
        break;
    case 4:
        title = 0xccb;
        tabTexts[0] = 0xccd;
        tabTexts[1] = 0xcce;
        tabTexts[2] = 0xccf;
        tabTexts[3] = 0;
        tabTexts[4] = 0;
        colors[2] = 0xd;
        base = 2;
        tabCount = 2;
        keys[0][0] = data_020b9480[1][1];
        keys[1][0] = data_020b9480[1][2];
        palette = 0xaf5a1f17;
        this->mode = 1;
        func_02029128(owner, true);
        break;
    case 2:
        title = 0xdd2;
        tabTexts[0] = 0xdd4;
        tabTexts[1] = 0xdd3;
        tabTexts[2] = 0xdd5;
        tabTexts[3] = 0xdd6;
        tabTexts[4] = 0;
        colors[0] = 0xd;
        colors[1] = 0xd;
        colors[2] = 0xd;
        colors[3] = 0xd;
        tabCount = 4;
        palette = 0x99de9fbc;
        keys[0][0] = data_020b9480[2][0];
        keys[0][1] = data_020b9480[2][1];
        keys[1][0] = data_020b9480[2][2];
        keys[2][0] = data_020b9480[2][3];
        keys[2][1] = data_020b9480[2][4];
        keys[3][0] = data_020b9480[2][5];
        keys[3][1] = data_020b9480[2][6];
        keys[3][2] = data_020b9480[2][7];
        keys[3][3] = data_020b9480[2][8];
        break;
    }
    found = false;
    tab = 0;
    if (data_020b947c != 0) {
        for (t = 0; t < tabCount && !found; t++) {
            for (k = 0; k < 6 && !found; k++) {
                if (keys[t][k] == 0) {
                    break;
                }
                if (func_0205d340(data_020b947c, keys[t][k])) {
                    found = true;
                    tab = t;
                }
            }
        }
    }
    for (int i = 0; i < tabCount; i++) {
        if (tab == i) {
            tabs[i].func_20(-0x31000, 0);
        } else {
            tabs[i].func_20(-0x31000, -0x12000);
        }
        Unk020a7c90 *s = tabs[i].func_02050a40(0);
        func_020a6980(s, palette);
        func_020a69ac(s, base);
        func_020a7d30(tabs[i].func_02050a40(0), colors[i]);
        tabs[i].func_18(true);
        tabs[i].func_34(0x22);
        base += 2;
    }
    pager.func_34(0x22);
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    pager.func_34(0x22);
    func_02038344(0);
    func_020389f8(&panel);
    panel.func_34(0x22);
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk02035fec::func_020374c4() {
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

bool Unk02035fec::func_3c(bool done) {
    if (!func_30() || !(flags & 2)) {
        done = true;
    }
    done = prev.func_0c(done);
    done = next.func_0c(done);
    int k = page * 12;
    for (int i = 0; k < count && i < 12; i++) {
        done = grid[i].func_0c(done);
        if (grid[i].touch.flags & 8) {
            func_020292c0(owner, 0x15);
            func_02028eec(owner, 0x15, records[k].def, 0);
        }
        k++;
    }
    if (prev.touch.flags & 8) {
        panel2.func_18(true);
        func_0203815c(grid2, page);
        func_02038a44(&panel2);
        panel2.func_30(0x22);
        for (int i = 0; i < 12; i++) {
            grid2[i].func_02050bf0(grid[i].unk64, -1, -1, -1, -1, -1);
        }
        flags |= 0x10;
    }
    if (next.touch.flags & 8) {
        page++;
        panel2.func_18(true);
        func_0203815c(grid2, page);
        func_02038a44(&panel2);
        panel2.func_30(0x22);
        func_0202918c(owner);
        func_020389f8(&panel);
        func_020a7ce0(pager.func_02051ad0(0));
    }
    for (int i = 0; i < tabCount; i++) {
        done = tabs[i].func_0c(done);
        if ((tabs[i].touch.flags & 8) && i != tab) {
            func_40(true);
            tabs[tab].func_20(-0x12000, 0);
            tabs[tab].func_30(0x22);
            tabs[tab].func_2c(0x22);
            tab = i;
            tabs[tab].func_20(-0x12000, 0);
            tabs[tab].func_34(0x22);
            tabs[tab].func_28(0x22);
            func_0202923c(owner);
            func_02038ae4(&panel);
            pager.func_2c(0x22);
        }
    }
    return done;
}

void Unk02035fec::func_38(bool active) {
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
    for (int i = 0; i < tabCount; i++) {
        tabs[i].func_08();
    }
    if (flags & 0x10) {
        func_020aa158(layout);
        flags &= ~0x10;
        page--;
        func_020a7ce0(pager.func_02051ad0(0));
        panel.func_18(true);
        func_0203815c(grid, page);
        func_02038a44(&panel);
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
        if (flags & 8) {
            if (panel.func_44()) {
                func_02038344(0);
                func_02038a90(&panel);
            } else if (panel.func_40()) {
                func_40(false);
            }
        } else if (panel.func_4c()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    if (grid2[n].func_10()->x >= panel.func_10()->x) {
                        grid2[n].func_18(false);
                        int m = c + row * 4;
                        int k = page * 12 + m;
                        if (grid[m].unk64 < 0) {
                            int v = grid2[n].unk64;
                            grid[m].func_02050bf0(v, -1, -1, -1, -1, -1);
                            if (k < count) {
                                grid[m].func_020514f0();
                                if (mode == 1 && (keys[tab][0] == data_020ae7cc[8] || keys[tab][0] == data_020ae7cc[9])) {
                                    func_0203c254(records[k].count - 1, grid[m].unk64, 0);
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
                            int v = grid[n].unk64;
                            grid2[m].func_02050bf0(v, -1, -1, -1, -1, -1);
                            if (k < count) {
                                grid2[m].func_020514f0();
                                if (mode == 1 && (keys[tab][0] == data_020ae7cc[8] || keys[tab][0] == data_020ae7cc[9])) {
                                    func_0203c254(records[k].count - 1, grid2[m].unk64, 0);
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
                    int v = grid[n].unk64;
                    grid2[c + row * 4].func_02050bf0(v, -1, -1, -1, -1, -1);
                }
            }
            panel.func_18(true);
            func_0203815c(grid, page);
            func_02038a44(&panel);
            panel.func_30(0x22);
            for (int i = 0; i < 12; i++) {
                grid[i].func_02050bf0(grid2[i].unk64, -1, -1, -1, -1, -1);
            }
            panel.func_08();
        } else if (panel.func_40()) {
            int n = 0;
            for (int row = 0; row < 3; row++) {
                for (int col = 0, c = 3; col < 4; col++, c--, n++) {
                    int v = grid2[n].unk64;
                    grid[c + row * 4].func_02050bf0(v, -1, -1, -1, -1, -1);
                }
            }
        }
    }
    func_020aa158(layout);
    if (fade.state == 4) {
        func_020374c4();
    }
}

void Unk02035fec::func_18() {
    flags |= 4;
}

void Unk02035fec::func_0203815c(Unk02050640 *buttons, int page) {
    int i;
    int k = page * 12;
    for (i = 0; k < count && i < 12; k++, i++) {
        buttons[i].func_020508ac(func_0206446c(records[k].icon));
        buttons[i].func_02050c48(func_020644bc(records[k].icon), -1, -1);
        buttons[i].func_02050bb4(-1, -1, func_020644b0(records[k].icon), -1);
        buttons[i].sprites[1] = 0;
        buttons[i].func_18(true);
        if (mode != 1) {
            if (records[k].count <= 0) {
                buttons[i].flags |= 8;
            } else {
                buttons[i].flags &= ~8;
            }
            func_020a7ce0(buttons[i].func_02050a40(0));
        } else {
            func_020a7cf0(buttons[i].func_02050a40(0), false);
            if (records[k].flags & 1) {
                if (marked != 0) {
                    marked->sprites[1] = 0;
                }
                marked = &buttons[i];
                buttons[i].sprites[1] = mark;
                func_020a9240(mark, func_020a8388(buttons[i].sprite));
                func_020a7cf0(mark, true);
                func_020a7c90(mark, func_020a7ca4(buttons[i].sprite) + 0x1c000);
                func_020a7cac(mark, func_020a7cc0(buttons[i].sprite) + 0x1c000);
            }
        }
    }
    for (; i < 12; i++) {
        buttons[i].sprites[1] = 0;
        buttons[i].func_18(false);
    }
}

void Unk02035fec::func_02038344(short first) {
    u32 min = 1;
    if (mode == 1) {
        u32 kind = func_020081dc(&data_020c43a8).unk28 == 0 ? 0x85fba6e5 : 0x1e49458c;
        min = 2;
        for (int i = 0; i < tabCount; i++) {
            keys[i][1] = kind;
        }
    }
    int n = 0;
    for (int i = 0; i < 6; i++) {
        if (keys[tab][i] != 0) {
            n++;
        }
    }
    Unk020547f8 list;
    func_02054d94(&data_020bfc9c, &list, keys[tab], n, min);
    count = list.count;
    if (records != 0) {
        delete[] records;
        records = 0;
    }
    if (count > 0) {
        func_020a7cf0(empty, false);
        panel.func_02051ae8(0, 2);
    } else {
        func_020a7c90(empty, panel.func_10()->x + 0x59000);
        func_020a7cf0(empty, true);
        panel.func_02051ae8(empty, 2);
        if (mode == 0) {
            func_020a716c(empty, 0x10f0);
        } else if (mode == 2) {
            if (tab == 0) {
                func_020a716c(empty, 0x10f1);
            } else if (tab == 1) {
                func_020a716c(empty, 0x10f2);
            } else if (tab == 2) {
                func_020a716c(empty, 0x10f3);
            } else {
                func_020a716c(empty, 0x10f4);
            }
        } else if (mode == 1) {
            func_020a716c(empty, 0x10b6);
        }
    }
    if (count > 0) {
        records = new Unk020388ac[count];
    }
    Unk020081dc outfit = func_020081dc(&data_020c43a8);
    int sel = -1;
    for (int j = 0; j < count; j++) {
        int icon = func_0205d134(func_02054858(&list, j)->def, 0x9d5bba8e);
        if (icon == -1) {
            icon = 0;
        }
        records[j].icon = icon;
        records[j].count = func_02054858(&list, j)->count;
        records[j].def = func_02054858(&list, j)->def;
        if (records[j].def == data_020b947c) {
            sel = j;
        }
        if (mode == 1) {
            for (int k = 0; k < 6; k++) {
                if (outfit.parts.v[k] == records[j].def->id) {
                    records[j].flags |= 1;
                }
            }
        }
    }
    data_020b947c = 0;
    pages = count / 12;
    if (count % 12 > 0) {
        pages++;
    }
    if (sel < 0) {
        page = first;
    } else {
        page = sel / 12;
    }
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    if (pages > 1) {
        pager.func_28(0x22);
    }
    panel.func_18(true);
    panel2.func_18(false);
    func_020a7ce0(panel.func_02051ad0(0));
    func_020a7cf0(mark, false);
    func_0203815c(grid, page);
    int i;
    int k = page * 12;
    for (i = 0; i < 12; i++, k++) {
        grid[i].func_02050bf0(i, -1, -1, -1, -1, -1);
        if (grid[i].func_02050a24()) {
            grid[i].func_020514f0();
            if (mode == 1 && (keys[tab][0] == data_020ae7cc[8] || keys[tab][0] == data_020ae7cc[9])) {
                func_0203c254(records[k].count - 1, grid[i].unk64, 0);
            }
        }
    }
}

Unk020388ac::Unk020388ac() {
    icon = -1;
    count = 0;
    def = 0;
    flags = 0;
}

static void *func_020388c8(u32 id, void *user) {
    Unk02035fec *self = (Unk02035fec *)user;
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
        sprintf(self->text, "%d", c);
        return self->text;
    } else if (k == 0x19) {
        sprintf(self->text, "%d", self->page + 1);
        return self->text;
    } else if (k == 0x1a) {
        sprintf(self->text, "/%d", self->pages);
        return self->text;
    } else if (k == 0x1b || k == 0x1c) {
        const char *title = func_020a00a0(func_0201ba94(), self->title);
        const char *tab = func_020a00a0(func_0201ba94(), self->tabTexts[self->tab]);
        sprintf(self->text, "%s - %s", title, tab);
        return self->text;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

void Unk02035fec::func_020389f8(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}

void Unk02035fec::func_02038a44(Unk02051704 *panel) {
    panel->func_20(0x100000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk02035fec::func_02038a90(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_34(0x22);
    panel->func_28(0x22);
}

void Unk02035fec::func_02038ae4(Unk02051704 *panel) {
    panel->func_20(-0x146000, -0x23000);
    panel->func_30(0x22);
    panel->func_2c(0x22);
}

void func_02038b38(Unk0205cf00 *def) {
    data_020b947c = def;
}

int func_02038b48(Unk0205cf00 *def) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (data_020b9480[i][j] == 0) {
                break;
            }
            if (func_0205d340(def, data_020b9480[i][j])) {
                return i;
            }
        }
    }
    return -1;
}
