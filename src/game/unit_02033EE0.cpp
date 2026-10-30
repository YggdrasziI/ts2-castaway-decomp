/*
 * Unit 0x02033EE0-0x02035FEC: the object text screen (Unk02033ee0, 0xA6C
 * bytes, vtable 0x020B9428) on the screen base Unk0203c188, built by its
 * owner (0x02029688 and 0x020296AC, the second one opening the object to show
 * first at once). The objects are the inventory entries of key 0x798B86AC,
 * read as records (Unk02035718) and shown four per page in two lists
 * (Unk02035d2c, the second one slides in on a page change), each button with
 * a name and a mark that follows the record's opened flag (set when the
 * inventory count is above 1). A press opens the object: its title, a palette
 * loaded for its picture and its text, split in pages, in an info panel; the
 * previous / next pair turns the pages of the list or of the text, and the
 * back button returns to the list. Opening sets the inventory count to 2.
 * func_02035fc0 sets data_020b941c and the id of the object to show first
 * (data_020be424).
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots
 * 0x02033EB0-0x02033ED0 of the screen with vtable 0x020B93CC; the end is the
 * tabbed object list screen (unit_02035FEC.cpp). `.data` holds the object set
 * by func_02035fc0, this class's vtable with its header and the formats of
 * the text functions; `.bss` the id of the object to show first. Real file
 * name unknown.
 *
 * Not complete: the constructor is below 100 % (comment above it).
 */

#include "game/unk_screen.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* A text sprite (func_020a78cc): only the fields used here. */
class Unk020a78cc : public Unk020a7c90 {
public:
    u8 unk4[0x3c];
    Unk02090308 *canvas;
};

/* A font of a layout (func_020aa040 type 0): only the font. */
struct Unk020aa040Font {
    u8 unk0[0x14];
    Unk02092830Font *font;
};

/* The game settings (data_020d60c8): only the text table is named. */
struct Unk020d60c8 {
    u8 unk0[0x158];
    void *texts;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* An object of the database. */
struct Unk0205cf00;

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

/* A record of the list (0xC bytes). */
class Unk02035718 {
public:
    Unk02035718();

    int id;
    bool opened;
    Unk0205cf00 *def;
};

/* A list of four buttons with their names and marks (0x2E8 bytes). */
class Unk02035d2c {
public:
    Unk02035d2c() : bg(0) {}

    void func_02035d2c();
    void func_02035d44();
    void func_02035d5c();
    void func_02035dac();
    void func_02035dfc();
    void func_02035e44();
    void func_02035e8c(bool show);
    void func_02035ea0();

    Unk02051704 panel;
    Unk02050640 buttons[4];
    Unk0204f798 marks;
    Unk020a7c90 *names[4];
    Unk020a7c90 *bg;
};

struct Unk020bfc9c;

extern Unk020d60c8 data_020d60c8;
extern Unk020bfc9c data_020bfc9c;

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
const char *func_020a00a0(void *texts, int id);
int func_0205d134(Unk0205cf00 *item, u32 key);
int func_0205d1b4(Unk0205cf00 *item, u32 key);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
Unk02054dc4 *func_02054dc4(Unk020bfc9c *p, Unk0205cf00 *def, int a);
void func_0202918c(Unk0203c188Owner *owner);
void func_020291e4(Unk0203c188Owner *owner);
void func_0202923c(Unk0203c188Owner *owner);
int func_02082a2c(char *buf, const char *fmt, ...);
char *func_02082e90(const char *s, const char *sub);
int func_020833ac(const char *s);
int func_02082c0c(const char *s);
char *strncpy(char *dst, const char *src, unsigned long n);
char *strcpy(char *dst, const char *src);
u16 func_020a7164(Unk020a78cc *t);
void func_020a716c(Unk020a7c90 *s, int text);
int func_020a7180(Unk020a78cc *t);
void func_020a71a4(Unk020a78cc *t, int x);
int func_020a72c8(Unk020a78cc *t);
void func_020a72d0(Unk020a78cc *t, int value);
int func_020a731c(Unk020a78cc *t);
int func_020a705c(int align);
int func_020a709c(int align);
int func_020a793c(Unk020a78cc *t, int page, Unk020a7c90 *font, const char *fmt, ...);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a7ce0(Unk020a7c90 *s);
int func_020a7d44(Unk020a7c90 *s);
u32 func_020a7de8(Unk020a7c90 *s);
void func_02035fc0(Unk0205cf00 *def);
}

#pragma explicit_zero_data on
Unk0205cf00 *data_020b941c = 0;
#pragma explicit_zero_data reset

int data_020be424;

class Unk02033ee0 : public Unk0203c188 {
public:
    Unk02033ee0(Unk0203c188Owner *owner, bool open);
    virtual ~Unk02033ee0();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_30();
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_020354ec();
    void func_02035734();
    void func_0203577c(Unk02035718 *rec);
    void func_02035c04(Unk02035d2c *list, int page);

    int selected;
    int count;
    Unk02035718 *records;
    u16 pages;
    u16 page;
    short textPage;
    short textPages;
    int textId;
    Unk020a78cc *text;
    Unk020a78cc *title;
    char buf[0x200];
    Unk020a9d58 *layout;
    Unk02051704 info;
    Unk02035d2c list;
    Unk02035d2c list2;
    Unk02050640 back;
    Unk02050640 next;
    Unk02050640 prev;
    Unk02051704 pager;
    char num[0x20];
};

static void *func_02035ef4(u32 id, void *user);

/*
 * 98.98 %: some name lookups truncate their index through r0 where the
 * original uses r1 or the reverse (see the unsolved patterns), with the
 * second list's panel address computed one instruction apart; in the button
 * loop the counter, the name sprite, the button offset and the three y
 * values take rotated callee-saved registers (r8, r9, r4, r5-r7 here; r4,
 * r5, r6, r7-r9 in the original). Tried for the loop: every declaration
 * order of the counter and the three sprites (top or before the loop),
 * explicit y counters, the index written first. The y local of the pager
 * gave the original's direct read of next.func_10()->y (98.43 % -> 98.98 %).
 */
Unk02033ee0::Unk02033ee0(Unk0203c188Owner *owner, bool open)
    : Unk0203c188(owner), selected(-1), count(0), records(0), pages(0), page(0), textPage(0), textPages(0),
      textId(0) {
    if (open) {
        flags |= 0x40;
    }
    Unk020a7af4Entry entries[0x46];
    Unk020a7af4 names(entries, 0x46);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x0a4366c1, layout, &names);
    func_020a9db8(layout, func_02035ef4, this);

    list.panel.func_14(-0x23000, 0);
    list.panel.func_02051804(0x16);
    list.panel.func_020518a8(1);
    Unk020a7c90 *bg = func_020aa040(layout, 4, func_020a7b50(&names, 0xdefd2411));
    Unk020a7c90 *frame = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xb0943cd7));
    list.panel.func_02051858(bg);
    list.panel.func_02051858(frame);
    list.bg = bg;
    info.func_02051804(3);
    info.func_02051858(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc6580252)));
    text = (Unk020a78cc *)func_020aa040(layout, 4, func_020a7b50(&names, 0xc9353639));
    info.func_02051858(text);
    title = (Unk020a78cc *)func_020aa040(layout, 4, func_020a7b50(&names, 0xe4b93912));
    info.func_02051858(title);
    list.panel.func_020518fc(&info);
    list.marks.func_0204f8a0(4);
    list.marks.delay = 9;

    list2.panel.func_14(-0x23000, 0);
    list2.panel.func_02051804(0xf);
    bg = func_020aa040(layout, 4, func_020a7b50(&names, 0xcbddf485));
    frame = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x96b55b60));
    list2.panel.func_02051858(bg);
    list2.panel.func_02051858(frame);
    list2.bg = bg;
    list2.marks.func_0204f8a0(4);
    list2.marks.delay = 9;

    for (int i = 0; i < 4; i++) {
        Unk020a7c90 *f = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xc8f8d0b5 + i));
        Unk020a7c90 *s = func_020aa040(layout, 4, func_020a7b50(&names, 0x31095e70 + i));
        Unk020a7c90 *m = func_020aa040(layout, 1, func_020a7b50(&names, 0x7534711d + i));
        list.panel.func_02051858(f);
        list.panel.func_02051858(s);
        list.panel.func_02051858(m);
        list.buttons[i].func_02050c48(0, 3, -1);
        list.buttons[i].func_02050838(f, false);
        list.buttons[i].func_14(0x21000, FX32(0x1b + i * 0x25));
        list.buttons[i].flags |= 2;
        list.names[i] = s;
        func_020a7c90(s, 0x33000);
        func_020a7cac(s, FX32(0x1d + i * 0x25));
        list.marks.func_0204f8f4(m);
        func_020a7c90(m, 0x25000);
        func_020a7cac(m, FX32(0x26 + i * 0x25));

        f = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x85f802d8 + i));
        s = func_020aa040(layout, 4, func_020a7b50(&names, 0x1ddb2ae4 + i));
        m = func_020aa040(layout, 1, func_020a7b50(&names, 0x71414fa7 + i));
        list2.panel.func_02051858(f);
        list2.panel.func_02051858(s);
        list2.panel.func_02051858(m);
        list2.buttons[i].func_02050c48(0, 3, -1);
        list2.buttons[i].func_02050838(f, false);
        list2.buttons[i].func_14(0x21000, FX32(0x1b + i * 0x25));
        list2.buttons[i].flags |= 2;
        list2.names[i] = s;
        func_020a7c90(s, 0x33000);
        func_020a7cac(s, FX32(0x1d + i * 0x25));
        list2.marks.func_0204f8f4(m);
        func_020a7c90(m, 0x25000);
        func_020a7cac(m, FX32(0x26 + i * 0x25));
    }

    prev.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));
    next.func_02050838(func_020aa040(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_020aa040(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));
    int y = next.func_10()->y;
    pager.func_14(0, y);
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
}

Unk02033ee0::~Unk02033ee0() {
    func_02035734();
    delete layout;
}

bool Unk02033ee0::func_30() {
    return func_28() && !func_14() && list.panel.func_38();
}

bool Unk02033ee0::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_020354ec();
    if (flags & 8) {
        fade.func_duration(0x22);
        list.func_02035dac();
        if (pages > 1) {
            pager.func_28(0x22);
        }
    } else {
        fade.func_duration(0x10);
        list.func_02035e44();
        list.func_02035d2c();
        if (!(flags & 0x40)) {
            if (pages > 1) {
                pager.func_30(0x22);
            }
        } else {
            if (textPages > 1) {
                pager.func_30(0x22);
            }
            back.func_30(0x22);
        }
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk02033ee0::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        list.func_02035d5c();
        pager.func_2c(0x22);
        back.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

bool Unk02033ee0::func_3c(bool done) {
    if (!func_30() || !(flags & 2)) {
        done = true;
    }
    done = prev.func_0c(done);
    done = next.func_0c(done);
    done = back.func_0c(done);
    for (int i = 0; i < 4; i++) {
        done = list.buttons[i].func_0c(done);
        if (list.buttons[i].touch.flags & 8) {
            selected = i + page * 4;
            func_40(true);
            func_0202923c(owner);
            list.func_02035d5c();
            pager.func_2c(0x22);
        }
    }
    if (prev.touch.flags & 8) {
        if (selected < 0) {
            func_02035c04(&list2, page);
            list2.func_02035e44();
            list2.func_02035d2c();
            page--;
            func_020291e4(owner);
            list.func_02035e44();
            flags |= 0x30;
            func_020a7ce0(pager.func_02051ad0(0));
        } else {
            textPage--;
            text->canvas->func_0209088c();
            func_020a793c(text, textPage, func_020aa040(layout, 0, func_020a7164(text)), buf);
            func_020a7ce0(pager.func_02051ad0(0));
        }
    }
    if (next.touch.flags & 8) {
        if (selected < 0) {
            page++;
            func_0202918c(owner);
            list.func_02035dfc();
            func_02035c04(&list2, page);
            list2.func_02035e44();
            list2.func_02035d2c();
            func_020a7ce0(pager.func_02051ad0(0));
        } else {
            textPage++;
            text->canvas->func_0209088c();
            func_020a793c(text, textPage, func_020aa040(layout, 0, func_020a7164(text)), buf);
            func_020a7ce0(pager.func_02051ad0(0));
        }
    }
    if (back.touch.flags & 8) {
        func_0202923c(owner);
        list.func_02035d5c();
        back.func_2c(0x22);
        pager.func_2c(0x22);
        selected = -1;
    }
    return done;
}

void Unk02033ee0::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    fade.func_step();
    if (fade.state == 1) {
        if (!(flags & 0x40)) {
            func_40(false);
        } else {
            func_40(true);
            flags &= ~0x40;
        }
    }
    if (selected < 0) {
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
    } else {
        if (textPage < 1) {
            prev.flags |= 8;
        } else {
            prev.flags &= ~8;
        }
        if (textPage >= textPages - 1) {
            next.flags |= 8;
        } else {
            next.flags &= ~8;
        }
    }
    list.func_02035ea0();
    list2.func_02035ea0();
    pager.func_08();
    next.func_08();
    prev.func_08();
    back.func_08();
    if (flags & 0x20) {
        func_020aa158(layout);
        flags &= ~0x20;
        return;
    }
    if (flags & 0x10) {
        func_02035c04(&list, page);
        flags &= ~0x10;
    }
    if (list.panel.func_38() && !list2.panel.func_3c()) {
        list2.func_02035dfc();
        list2.func_02035d44();
        list2.func_02035e8c(false);
    }
    if (fade.func_shown()) {
        if (!(flags & 8)) {
            if (list.panel.func_44()) {
                func_02035c04(&list, page);
                list.func_02035d2c();
            }
        } else {
            if (list.panel.func_44()) {
                if (selected < 0) {
                    func_02035c04(&list, page);
                    func_020a7ce0(pager.func_02051ad0(0));
                    func_020a7ce0(pager.func_02051ad0(1));
                    if (pages > 1) {
                        pager.func_28(0x22);
                    }
                } else {
                    func_0203577c(&records[selected]);
                    back.func_28(0x22);
                }
                list.func_02035dac();
            }
            if (list.panel.func_40() && selected < 0) {
                func_40(false);
            }
        }
    }
    func_020aa158(layout);
    if (fade.state == 4) {
        func_02035734();
    }
}

void Unk02033ee0::func_020354ec() {
    if (flags & 2) {
        return;
    }
    Unk020547f8 entries;
    u32 key = 0x798b86ac;
    func_02054d94(&data_020bfc9c, &entries, &key, 1, 1);
    count = entries.count;
    records = new Unk02035718[count];
    int sel = 0;
    int j = 0;
    for (int i = count - 1; i >= 0; i--, j++) {
        Unk02054dc4 *e = func_02054858(&entries, i);
        records[j].def = e->def;
        records[j].id = func_0205d134(records[j].def, 0xbe33d1b8);
        if (e->count > 1) {
            records[j].opened = true;
        }
        if (data_020be424 == records[j].id) {
            sel = j;
        }
    }
    pages = count / 4;
    if (count % 4 != 0) {
        pages++;
    }
    page = sel / 4;
    selected = -1;
    data_020be424 = 0;
    pager.func_34(0x22);
    back.func_34(0x22);
    func_02035c04(&list, page);
    list.func_02035dfc();
    list.func_02035d44();
    list2.func_02035dfc();
    list2.func_02035d44();
    list2.func_02035e8c(false);
    func_020aa06c(layout, true);
    if (flags & 0x40) {
        selected = sel;
        func_0203577c(&records[sel]);
    }
    flags |= 2;
}

Unk02035718::Unk02035718() {
    id = -1;
    opened = false;
    def = 0;
}

void Unk02033ee0::func_02035734() {
    if (!(flags & 2)) {
        return;
    }
    if (records != 0) {
        delete[] records;
        records = 0;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}

/*
 * Copies the text id into p, each "%%" followed by a value up to ";" being
 * replaced by the byte func_020833ac reads from it. An inline helper taking
 * the id by reference: written in place, or with the id by value, the
 * callee-saved registers of func_0203577c rotate.
 */
static inline void func_parse(char *p, const int &id) {
    *p = 0;
    const char *src = func_020a00a0(func_0201ba94(), id);
    char *mark = func_02082e90(src, "%%");
    while (mark != 0) {
        int len = mark - src;
        strncpy(p, src, len);
        src += len + 2;
        p += len;
        *p = func_020833ac(src);
        p++;
        mark = func_02082e90(src, "%%");
        char *end = func_02082e90(src, ";");
        if (end == 0) {
            break;
        }
        src = end + 1;
    }
    if (func_02082c0c(src) == 0) {
        *p = 0;
    } else {
        strcpy(p, src);
    }
}

void Unk02033ee0::func_0203577c(Unk02035718 *rec) {
    list.func_02035e8c(false);
    info.func_18(true);
    rec->opened = true;
    func_02054dc4(&data_020bfc9c, rec->def, 0)->count = 2;
    func_020a716c(title, rec->id);
    int palette = func_0205d1b4(rec->def, 0x2b3e6dd7);
    if (palette == 0) {
        palette = 1;
    }
    Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
    Unk02093648 *archive = func_020a18e4()->archive;
    int index = archive->func_02093e9c(func_020a7de8(font));
    Unk0209487c *file = func_020a18e4()->archive->func_02093a9c(index);
    Unk020916a4 *oam = Unk020916a4::func_02091830();
    oam->func_0209201c((Unk02095140 *)file, 0, palette << 4, func_020a7d44(text) << 4, 0x10);
    func_020a18e4()->archive->func_02093c3c(file);

    textId = func_0205d134(rec->def, 0x6a4a2934);
    int height = title->func_14() >> 12;
    font = func_020aa040(layout, 0, func_020a7164(title));
    void *texts = data_020d60c8.texts;
    Unk02092830 lines(func_020a00a0(texts, func_020a7180(title)), ((Unk020aa040Font *)font)->font);
    int hAlign = func_020a705c(func_020a72c8(title));
    int vAlign = func_020a709c(func_020a731c(title));
    Unk02098bc8 size = lines.func_02092db0(hAlign, vAlign, title->func_10() >> 12, height, 0, 0);
    int n = (u32)size.h / height;
    if (n < 2) {
        func_020a7cac(info.func_02051ad0(0), 0x10000);
        func_020a7cac(text, 0x18000);
        func_020a71a4(text, 0x8f000);
    } else {
        func_020a7cac(info.func_02051ad0(0), 0x1c000);
        func_020a7cac(text, 0x24000);
        func_020a71a4(text, 0x83000);
    }
    func_020aa158(layout);

    func_parse(buf, textId);

    int h = text->func_14();
    font = func_020aa040(layout, 0, func_020a7164(text));
    Unk02092830 body(buf, ((Unk020aa040Font *)font)->font);
    Unk02092b94 split = body.func_02092b78(text->func_10() >> 12, 0);
    font = func_020aa040(layout, 0, func_020a7164(text));
    int step = ((Unk020aa040Font *)font)->font->func_24();
    textPages = 1;
    int y = 0;
    while (split.func_02092d3c()) {
        y += step;
        if (y > h >> 12) {
            textPages++;
            y = step;
        }
        split.func_02092d54();
    }
    textPage = 0;
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    if (textPages > 1) {
        pager.func_28(0x22);
        func_020a72d0(text, -1);
    } else {
        func_020a72d0(text, 0);
    }
    func_020a793c(text, textPage, func_020aa040(layout, 0, func_020a7164(text)), buf);
}

void Unk02033ee0::func_02035c04(Unk02035d2c *list, int page) {
    list->func_02035e8c(true);
    info.func_18(false);
    int i = 0;
    int k = page * 4;
    for (; i < 4 && k < count; k++, i++) {
        func_020a716c(list->names[i], records[k].id);
        if (records[k].opened) {
            func_020a6980(list->marks.func_0204fda8(i), 0xa3324797);
        } else {
            func_020a6980(list->marks.func_0204fda8(i), 0xb97aebe5);
        }
    }
    if (i >= 4) {
        return;
    }
    for (; i < 4; i++) {
        list->buttons[i].func_18(false);
        func_020a7cf0(list->marks.func_0204fda8(i), false);
        func_020a7cf0(list->names[i], false);
    }
}

void Unk02035d2c::func_02035d2c() {
    panel.func_30(0x22);
}

void Unk02035d2c::func_02035d44() {
    panel.func_34(0x22);
}

void Unk02035d2c::func_02035d5c() {
    panel.func_20(-0x146000, -0x23000);
    panel.func_30(0x22);
    panel.func_2c(0x22);
}

void Unk02035d2c::func_02035dac() {
    panel.func_20(-0x146000, -0x23000);
    panel.func_34(0x22);
    panel.func_28(0x22);
}

void Unk02035d2c::func_02035dfc() {
    panel.func_20(0x100000, -0x23000);
    panel.func_30(0x22);
    panel.func_2c(0x22);
}

void Unk02035d2c::func_02035e44() {
    panel.func_20(0x100000, -0x23000);
    panel.func_34(0x22);
    panel.func_28(0x22);
}

void Unk02035d2c::func_02035e8c(bool show) {
    panel.func_18(show);
}

void Unk02035d2c::func_02035ea0() {
    for (int i = 0; i < 4; i++) {
        buttons[i].func_08();
    }
    marks.func_08();
    panel.func_08();
}

static void *func_02035ef4(u32 id, void *user) {
    Unk02033ee0 *self = (Unk02033ee0 *)user;
    switch (id - 0x800000) {
    case 1:
        if (self->selected < 0) {
            func_02082a2c(self->num, "%d", self->page + 1);
        } else {
            func_02082a2c(self->num, "%d", self->textPage + 1);
        }
        return self->num;
    case 2:
        if (self->selected < 0) {
            func_02082a2c(self->num, "/%d", self->pages);
        } else {
            func_02082a2c(self->num, "/%d", self->textPages);
        }
        return self->num;
    }
    return (void *)func_020a00a0(func_0201ba94(), id);
}

void func_02035fc0(Unk0205cf00 *def) {
    data_020b941c = def;
    data_020be424 = func_0205d134(def, 0xbe33d1b8);
}
