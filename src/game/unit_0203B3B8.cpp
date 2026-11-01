/*
 * Unit 0x0203B3B8-0x0203C188: the text pager screen (Unk0203b3b8, 0x28C
 * bytes, vtable 0x020B95B4) on the screen base Unk0203c188, built by its
 * owner (0x02029464 with mode 0, 0x02029578 with mode 1). The mode picks the
 * title and the text (0xCC5 / 0xFE7 or 0xCCB / 0xFE8); the text is laid out
 * in a text sprite and shown one page at a time, with a previous / next pair
 * in a second panel shown only when there is more than one page. The back
 * button reports the mode to the owner.
 *
 * Bounds: hypothesis. The start is the constructor, after the inline slots
 * 0x0203B398 / 0x0203B3A0 of the screen with vtable 0x020B9558; the end is the
 * screen base (unit_0203C188.cpp). `.data` holds the page formats of the
 * text function and this class's vtable with its header; the word after it,
 * data_020b95f8, is the screen base's. Real file name unknown.
 *
 * Not complete: the constructor is below 100 % (comment above it).
 */

#include "game/unk_screen.h"
#include "game/unk_canvas.h"

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

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;

void *func_0201ba94();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
const char *func_020a00a0(void *texts, int id);
void *func_0202fdb0(Unk020d6240 *system);
int sprintf(char *buf, const char *fmt, ...);
void func_020292c0(Unk0203c188Owner *owner, int a);
u16 func_020a7164(Unk020a78cc *t);
void func_020a716c(Unk020a7c90 *s, int text);
int func_020a72c8(Unk020a78cc *t);
int func_020a731c(Unk020a78cc *t);
int func_020a705c(int align);
int func_020a709c(int align);
int func_020a793c(Unk020a78cc *t, int page, Unk020a7c90 *font, const char *fmt, ...);
void func_020a7ce0(Unk020a7c90 *s);
}

static void *func_0203c0f0(u32 id, void *user);

class Unk0203b3b8 : public Unk0203c188 {
public:
    Unk0203b3b8(Unk0203c188Owner *owner, int mode);
    virtual ~Unk0203b3b8();
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

    void func_0203bc24();
    void func_0203bdbc();

    int mode;
    Unk020a9d58 *layout;
    Unk02050640 back;
    Unk02051704 panel;
    Unk02051704 pager;
    Unk02050640 next;
    Unk02050640 prev;
    int textId;
    Unk020a78cc *text;
    char buf[0x20];
    short page;
    short pages;
};

Unk0203b3b8::Unk0203b3b8(Unk0203c188Owner *owner, int mode) : Unk0203c188(owner), mode(mode) {
    textId = 0;
    Unk020a7af4Entry entries[0x32];
    Unk020a7af4 names(entries, 0x32);

    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0xa9103d96, layout, &names);
    func_020a9db8(layout, func_0203c0f0, this);

    panel.func_14(-0x23000, 0);
    panel.func_20(-0x146000, -0x23000);
    panel.func_020518a8(4);
    panel.func_02051804(0xf);
    back.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x63b94c03)), false);
    back.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0xee1a47e2)));
    back.func_02050914(1);
    back.func_02050968(func_sprite(layout, 4, func_020a7b50(&names, 0x63412fed)));
    back.func_02050c48(0, 1, -1);
    back.func_02050c64(0, 1, 2);
    back.flags |= 2;
    panel.func_020518fc(&back);

    int title = 0;
    switch (this->mode) {
    case 0:
        textId = 0xfe7;
        title = 0xcc5;
        break;
    case 1:
        textId = 0xfe8;
        title = 0xccb;
        break;
    }
    Unk020a7c90 *s = func_sprite(layout, 4, func_020a7b50(&names, 0xe0343c1b));
    func_020a716c(s, title);
    panel.func_02051858(s);
    panel.func_02051858(func_sprite(layout, 0xb, func_020a7b50(&names, 0xea7a08ce)));
    text = (Unk020a78cc *)func_sprite(layout, 4, func_020a7b50(&names, 0x96c99379));
    panel.func_02051858(text);

    prev.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0x260323f0)), false);
    prev.func_02050c48(0, 1, -1);
    prev.func_02050c64(0, 1, 2);
    prev.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0xcc3efd4a)));
    next.func_02050838(func_sprite(layout, 0xb, func_020a7b50(&names, 0xcba0dc91)), false);
    next.func_02050c48(2, 3, -1);
    next.func_02050c64(3, 4, 5);
    next.func_020508a4(func_sprite(layout, 1, func_020a7b50(&names, 0x8f6a6fb5)));

    pager.func_14(0, next.func_10()->y);
    pager.func_24(0xc0000, pager.func_10()->y);
    pager.func_020518a8(2);
    pager.func_02051804(2);
    pager.func_020518fc(&prev);
    pager.func_020518fc(&next);
    pager.func_02051858(func_sprite(layout, 3, func_020a7b50(&names, 0x79be6d8f)));
    pager.func_02051858(func_sprite(layout, 3, func_020a7b50(&names, 0x03398ecd)));
}

Unk0203b3b8::~Unk0203b3b8() {
    func_0203bdbc();
    delete layout;
}

void Unk0203b3b8::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_1c();
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk0203b3b8::func_1c() {
    flags &= ~4;
}

bool Unk0203b3b8::func_30() {
    return func_28() && !func_14() && panel.func_38();
}

bool Unk0203b3b8::func_14() {
    return (flags & 4) != 0;
}

bool Unk0203b3b8::func_28() {
    return fade.func_shown();
}

bool Unk0203b3b8::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0203bc24();
    if (flags & 8) {
        fade.func_duration(0x22);
        if (pages > 1) {
            pager.func_34(0x22);
            pager.func_28(0x22);
        }
        panel.func_34(0x22);
        panel.func_28(0x22);
    } else {
        fade.func_duration(0x10);
        panel.func_30(0x22);
        if (pages > 1) {
            pager.func_30(0x22);
        }
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk0203b3b8::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
        panel.func_2c(0x22);
        pager.func_2c(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

void Unk0203b3b8::func_0203bc24() {
    if (flags & 2) {
        return;
    }
    panel.func_34(0x22);
    pager.func_34(0x22);
    func_020aa06c(layout, true);
    void *texts = func_0201ba94();
    u32 height;
    Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
    height = text->func_14() >> 12;
    Unk02092830 lines(func_020a00a0(texts, textId), ((Unk020aa040Font *)font)->font);
    int hAlign = func_020a705c(func_020a72c8(text));
    int vAlign = func_020a709c(func_020a731c(text));
    Unk02098bc8 size = lines.func_02092db0(hAlign, vAlign, text->func_10() >> 12, height, 0, 0);
    page = 0;
    pages = (u32)size.h / height;
    if ((u32)size.h % height != 0) {
        pages++;
    }
    func_020a793c(text, page, font, func_020a00a0(texts, textId));
    func_020a7ce0(pager.func_02051ad0(0));
    func_020a7ce0(pager.func_02051ad0(1));
    flags |= 2;
}

void Unk0203b3b8::func_0203bdbc() {
    if (!(flags & 2)) {
        return;
    }
    func_020aa06c(layout, false);
    flags &= ~2;
}

bool Unk0203b3b8::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = back.func_0c(done);
    if (back.touch.flags & 8) {
        func_020292c0(this->owner, mode);
    }
    done = prev.func_0c(done);
    if (prev.touch.flags & 8) {
        page--;
        text->canvas->func_0209088c();
        void *texts = data_020d60c8.texts;
        Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
        func_020a793c(text, page, font, func_020a00a0(texts, textId));
        func_020a7ce0(pager.func_02051ad0(0));
    }
    done = next.func_0c(done);
    if (next.touch.flags & 8) {
        page++;
        text->canvas->func_0209088c();
        void *texts = data_020d60c8.texts;
        Unk020a7c90 *font = func_020aa040(layout, 0, func_020a7164(text));
        func_020a793c(text, page, font, func_020a00a0(texts, textId));
        func_020a7ce0(pager.func_02051ad0(0));
    }
    return done;
}

void Unk0203b3b8::func_38(bool active) {
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
    pager.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_0203bdbc();
    }
}

void Unk0203b3b8::func_18() {
    flags |= 4;
}

static void *func_0203c0f0(u32 id, void *user) {
    Unk0203b3b8 *self = (Unk0203b3b8 *)user;
    u32 k = id - 0x800000;
    if (k == 1) {
        sprintf(self->buf, "%d", self->page + 1);
        return self->buf;
    } else if (k == 2) {
        sprintf(self->buf, "/%d", self->pages);
        return self->buf;
    }
    return (void *)func_020a00a0(func_0202fdb0(func_020a18e4()), id);
}
