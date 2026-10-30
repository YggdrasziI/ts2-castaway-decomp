/*
 * Unit 0x0201D70C-0x0201DD90: the credits screen (Unk0201d70c, 0xAC bytes, vtable
 * 0x020B8B40), named by its file build/data/screens/credits/credits.credits.nitro_xml;
 * built by unit_02047A8C.cpp and unit_02073878.cpp. Eight text canvases scroll up
 * (faster while a key is held); each one that leaves the top wraps around with
 * the next node of the file, until the nodes run out.
 *
 * Bounds: hypothesis. The start is the constructor, after the root's func_30; the
 * end is unit_0201DD90.cpp. `.data` holds the file name and the vtable with its
 * header. Real file name unknown.
 */

#include "game/unk_canvas.h"
#include "game/unk_datatree.h"
#include "game/unk_screen.h"

/* A text and where to draw it, read by func_0204f6c0 (unit_0204EE14.cpp). */
struct Unk0201d70cText {
    Unk0201d70cText() : rect(0, 0, 0x40, 0x40), hAlign(0), vAlign(0), text(0), unk1c(0), unk1e(0), screen(0) {}

    Unk02098bc8 rect;
    int hAlign;
    int vAlign;
    const char *text;
    u16 unk1c;
    u16 unk1e;
    u16 screen;
};

/* A line: the only caller of the canvas base constructor (0x02090308). */
class Unk0201d70cLine : public Unk02090308 {};

struct Unk0201d70cPoint {
    int x;
    int y;
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

void *func_0201ba94();
bool func_02097248(int key);

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
const char *func_020a00a0(void *texts, int id);
bool func_0204f6c0(Unk02090308 *canvas, Unk0201d70cText *desc, int pages);
}

class Unk0201d70c : public Unk020a07d4 {
public:
    Unk0201d70c();
    virtual ~Unk0201d70c();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual bool func_14();
    virtual void func_18();
    virtual void func_1c();
    virtual bool func_20();
    virtual void func_24();
    virtual bool func_28();
    virtual bool func_2c();
    virtual bool func_34();
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_0201d83c();
    void func_0201d8c0();
    void func_0201d978(int line, int index);
    void func_0201da88();

    u32 flags;
    Unk020a07d4Timer fade;
    Unk02093648 *archive;
    Unk0201d70cLine *lines[8];
    Unk0201d70cPoint points[8];
    Unk0201d70cText desc;
    Unk02096348 *file;
    Unk0209674c root;
    u16 next;
};

Unk0201d70c::Unk0201d70c() : flags(0), archive(0) {
    next = 0;
    desc.rect.w = 0xc0;
    desc.rect.h = 0x20;
    desc.unk1c = 1;
    desc.unk1e = 0xf;
    desc.hAlign = 0;
    for (u32 i = 0; i < 8; i++) {
        lines[i] = 0;
        points[i].x = 0;
        points[i].y = (i * 0x1e) << 12;
    }
}

Unk0201d70c::~Unk0201d70c() {
    func_0201d83c();
}

void Unk0201d70c::func_0201d83c() {
    if (!(flags & 1)) {
        return;
    }
    for (u32 i = 0; i < 8; i++) {
        if (lines[i] != 0) {
            delete lines[i];
            lines[i] = 0;
        }
    }
    archive->func_02093d14((const u32 *)"build/data/screens/credits/credits.credits.nitro_xml");
    archive->func_02094fb8();
    archive = 0;
    flags &= ~1;
}

void Unk0201d70c::func_0201d8c0() {
    if (flags & 1) {
        return;
    }
    archive = func_020a18e4()->archive;
    archive->func_02094f9c();
    file = (Unk02096348 *)archive->func_02093c18(
        (const u32 *)"build/data/screens/credits/credits.credits.nitro_xml");
    root = file->func_02096980();
    flags |= 1;
}

void Unk0201d70c::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
    next = 0;
}

void Unk0201d70c::func_0201d978(int line, int index) {
    Unk0201d70cPoint *p = points;
    Unk0209674c node = root.func_02096774(index);
    int type = node.func_02096800();
    switch (type) {
    case (int)0xe0343c1b:
        p[line].x = 0x5000;
        break;
    case (int)0xe2887272:
        p[line].x = 0x2d000;
        break;
    case 0x4ccc5ace:
        p[line].x = 0x19000;
        break;
    }
    if (node.func_020967ec() == 0 || type == 0x42ff5154) {
        return;
    }
    void *texts = func_0201ba94();
    desc.text = func_020a00a0(texts, file->func_02096574(node.func_02096774(0).func_0209688c()));
    desc.screen = 0;
    Unk0201d70cLine *canvas = new Unk0201d70cLine;
    lines[line] = canvas;
    func_0204f6c0(canvas, &desc, 0);
}

void Unk0201d70c::func_0201da88() {
    if (flags == 0) {
        return;
    }
    for (u32 i = 0; i < 8; i++) {
        Unk0201d70cPoint *p = &points[i];
        if (func_02097248(9) || func_02097248(8)) {
            p->y -= 0x1800;
        } else {
            p->y -= 0x800;
        }
        if (p->y < -0x10000) {
            if (next == root.func_020967ec()) {
                func_18();
            } else {
                if (lines[i] != 0) {
                    delete lines[i];
                    lines[i] = 0;
                }
                p->y += 0xf0000;
                func_0201d978(i, next);
                next++;
            }
        }
        if (lines[i] != 0) {
            lines[i]->func_02090878(p->x, p->y);
        }
    }
}

void Unk0201d70c::func_38(bool active) {
    if (!active) {
        return;
    }
    fade.func_step();
    func_0201da88();
    if (fade.state == 4) {
        func_0201d83c();
    }
}

bool Unk0201d70c::func_3c(bool done) {
    return done;
}

bool Unk0201d70c::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.state = 0;
    func_0201d8c0();
    return false;
}

bool Unk0201d70c::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.state = 3;
    return false;
}

void Unk0201d70c::func_18() {
    flags |= 2;
}

bool Unk0201d70c::func_34() {
    return true;
}

bool Unk0201d70c::func_28() {
    return fade.func_shown();
}

bool Unk0201d70c::func_2c() {
    return fade.func_hidden();
}

bool Unk0201d70c::func_14() {
    return (flags & 2) != 0;
}

void Unk0201d70c::func_1c() {
    flags &= ~2;
}

bool Unk0201d70c::func_20() {
    return false;
}

void Unk0201d70c::func_24() {}
