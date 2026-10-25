/*
 * Unit 0x0201B6D4-0x0201C460: a pie menu (Unk0201b6d4). It holds up to 10 items
 * (a text id, an enabled flag, the text width and a touch rectangle), the dialog
 * font (the Japanese one, Unk0208f16c, when the language is 7, else Unk0208e570),
 * a background drawn as a frame of 16 x 16 tiles in an object grid canvas
 * (Unk02090308), and two pointer objects that follow the touched item and swing
 * with the angle at 0x24 of data_020be384. Opening and closing play the
 * "GROUP_SE_COMMON SE_OPEN_PIE_MENU" sound; closing on an item plays
 * "GROUP_SE_COMMON SE_SURVIVAL_GUIDE_SELECT_ITEM". The font interface's deleting
 * destructor is emitted here (0x0201B92C), the copy the link keeps.
 *
 * Bounds: hypothesis. Before 0x0201B6D4 lies the code of the file whose .data ends
 * with the "Treasure Map microgame" string; 0x0201C460 starts a class with the
 * vtable data_020b8ac0. The .data (pointer data_020b8908, then the strings) follows
 * the tables of unit_020B8888.cpp; data_020be384 is this file's only .bss object
 * (the original loads it through its own symbol). Real file name unknown.
 * Not complete: func_0201baa4 differs in register allocation (see above it).
 */

#include "game/unk_archive.h"
#include "game/unk_canvas.h"
#include "game/unk_font.h"
#include "game/unk_resource.h"

extern "C" {
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
}

/* The game object (data_020d6240): the touch input and the archive. */
class Unk020a0774;

struct Unk020d6240 {
    int unk0;
    Unk020a0774 *input;
    int unk8[3];
    Unk02093648 *archive;
};

/* The game settings (data_020d60c8): only the text table is named. */
struct Unk020d60c8 {
    u8 unk0[0x158];
    void *texts;
};

struct Unk020a07a4Point {
    Unk020a07a4Point() {}

    int x;
    int y;
};

extern Unk020d6240 data_020d6240;
extern Unk020d60c8 data_020d60c8;
extern const short data_020af1e8[];

extern "C" {
Unk020d6240 *func_020a18e4();
int func_0209f0a4(Unk020d60c8 *settings);
const char *func_020a00a0(void *texts, int id);
bool func_020a0774(Unk020a0774 *input, int index);
bool func_020a078c(Unk020a0774 *input, int index);
Unk020a07a4Point func_020a07a4(Unk020a0774 *input, int index);
void *func_020a2994();
void func_020a2ce8(void *sound, u32 hash, int volume, int unk);
}

/* The swing of the pointers: only the angle is used here. */
struct Unk020be384 {
    int unk0[9];
    u16 angle;
};

Unk020be384 data_020be384;

/* One item: touch rectangle, text id, enabled flag and text width. */
struct Unk0201b6d4Item {
    Unk0201b6d4Item() {
        textId = 0;
        enabled = 0;
        width = 0;
    }

    Unk02098bc8 rect;
    int textId;
    u8 enabled;
    u32 width;
};

/* One entry of the list given to func_0201b964. */
struct Unk0201b964Entry {
    int textId;
    int unk4;
    int unk8;
};

class Unk0201b6d4 {
public:
    Unk0201b6d4();
    ~Unk0201b6d4();
    void func_0201b940(int unk);
    void func_0201b964(const Unk0201b964Entry *entries, u32 n, u32 enabledMask);
    int func_0201baa4(int close, int swing);
    void func_0201bcf8();
    void func_0201be00();
    void func_0201c10c();
    int func_0201c198();
    int func_0201c208();
    void func_0201c2c4(int x, int y);
    void func_0201c2d8();
    void func_0201c3c8();

    Unk0201b6d4Item items[10];
    u32 itemCount;
    int x;
    int y;
    Unk02092830Font *font;
    Unk0208f8b0 *pointers[2];
    Unk02095140 *background;
    int unk134;
    u32 maxWidth;
    int pointerY;
    u32 flags;
    u32 timer;
    int selected;
    u16 input;
    u8 threshold;
    u8 counter;
    Unk02090308 *canvas;
    int cols;
    int rows;
};

void *func_0201ba94();

/*
 * Inline helpers (hypothesis): the original recomputes these from the loop counter
 * at every iteration; written inline, mwccarm does not turn them into a running
 * sum as it does for `(i << 4) + 0x10` in the loop body.
 */
static inline int func_itemTop(int i) {
    return i * 16 + 16;
}

static inline int func_itemOffset(int i) {
    return i << 16;
}

const char *data_020b8908 = "build/data/screens/piemenu/pointer.nitro_map";

Unk0201b6d4::Unk0201b6d4() {
    Unk0209487c *file;
    int id;

    itemCount = 0;
    x = 0;
    y = 0;
    font = 0;
    background = 0;
    pointerY = 0xC0000;
    flags = 0;
    selected = 0x15;
    input = 0;
    threshold = 0;
    counter = 0;
    if (func_0209f0a4(&data_020d60c8) != 7) {
        font = new Unk0208e570;
        file = func_020a18e4()->archive->func_02093c18(
            (const u32 *)"build/data/screens/fonts/dialog.nitro_map");
        id = func_020a18e4()->archive->func_02093e30(
            (const u32 *)"build/data/screens/fonts/dialog.font.nitro_xml");
    } else {
        font = new Unk0208f16c;
        file = func_020a18e4()->archive->func_02093c18(
            (const u32 *)"build/data/screens/fonts/japanese.nitro_map");
        id = func_020a18e4()->archive->func_02093e30(
            (const u32 *)"build/data/screens/fonts/japanese.font.nitro_xml");
    }
    font->func_08((Unk02095140 *)file, (Unk02096348 *)func_020a18e4()->archive->func_02093a9c(id));
    func_020a18e4()->archive->func_02093c58(id);
    background = (Unk02095140 *)func_020a18e4()->archive->func_02093c18(
        (const u32 *)"build/data/screens/piemenu/background.nitro_map");
    canvas = new Unk02090308;
    flags |= 1;
    func_0201c208();
}

Unk0201b6d4::~Unk0201b6d4() {
    Unk02095140 *file;
    Unk02093648 *archive;

    func_0201c10c();
    archive = func_020a18e4()->archive;
    if (font != 0) {
        file = font->func_34();
        delete font;
        archive->func_02093c58(archive->func_02093f5c(file));
    }
    font = 0;
    delete canvas;
    canvas = 0;
    archive->func_02093c58(archive->func_02093f5c(background));
}

void Unk0201b6d4::func_0201b940(int unk) {
    if (unk) {
        flags |= 0x20;
    } else {
        flags &= ~0x20;
    }
    flags &= ~0x40;
}

void Unk0201b6d4::func_0201b964(const Unk0201b964Entry *entries, u32 n, u32 enabledMask) {
    u32 i;

    itemCount = 0;
    maxWidth = 0;
    for (i = 0; i < n; entries++, i++) {
        if (entries->textId == 0) {
            continue;
        }
        items[itemCount].textId = entries->textId;
        items[itemCount].enabled = (enabledMask & (1 << itemCount)) ? 1 : 0;
        Unk02092830 layout(func_020a00a0(func_0201ba94(), items[itemCount].textId), font);
        Unk02098bc8 size = layout.func_02092db0(0, 0, 0x100, 0xC0, 0, 0);
        items[itemCount].width = size.w;
        if (items[itemCount].width > maxWidth) {
            maxWidth = items[itemCount].width;
        }
        if (itemCount > 10) {
            break;
        }
        itemCount++;
    }
    selected = 0x15;
    func_0201c2d8();
}

void *func_0201ba94() {
    return data_020d60c8.texts;
}

/*
 * 99.80 %: in the swing block the original loads the angle into r0 and keeps
 * pointerY / pointers[1] in r3 / r2; ours uses r1 for the angle (declarations, scopes,
 * types, index forms, inline helpers, variable reuse and access paths tried).
 */
int Unk0201b6d4::func_0201baa4(int close, int swing) {
    if (close) {
        func_0201c208();
        return close;
    }
    if ((flags & 2) && timer > 10 && func_020a0774(data_020d6240.input, 0)) {
        func_0201c208();
        return close;
    }
    if ((flags & 2) && timer > 10) {
        if (func_020a078c(data_020d6240.input, 0)) {
            Unk020a07a4Point p = func_020a07a4(data_020d6240.input, 0);
            u32 sel;
            u32 i;
            int s;

            p.x <<= 12;
            p.y <<= 12;
            sel = 0x15;
            for (i = 0; i < itemCount; i++) {
                if (items[i].rect.func_02098bf4(p.x, p.y)) {
                    sel = i;
                }
            }
            if (sel == 0x15) {
                pointerY = 0xC0000;
            } else {
                pointerY = y - (rows << 15) + (func_itemTop(sel) << 12);
            }
            pointers[0]->unk4 = pointerY;
            pointers[0]->unk0 = x - (cols << 15) - 0xD000;
            u16 a = data_020be384.angle;
            pointers[1]->unk4 = pointerY;
            s = data_020af1e8[(a >> 4) * 2];
            pointers[1]->unk0 = x + (cols << 15) - 0x14000;
            if (s <= 0) {
                s = -s;
            }
            pointers[0]->unk0 -= s << 4;
            pointers[1]->unk0 += s << 4;
            if (swing) {
                data_020be384.angle += 700;
            }
            if (sel != selected) {
                selected = sel;
                close = 1;
            }
        } else {
            selected = 0x15;
            pointerY = 0xC0000;
            pointers[0]->unk4 = pointerY;
            pointers[0]->unk0 = x - (cols << 15) - 0xD000;
            pointers[1]->unk4 = pointerY;
            pointers[1]->unk0 = x + (cols << 15) - 0x14000;
        }
    }
    return close;
}

void Unk0201b6d4::func_0201bcf8() {
    int held;
    int pressed;

    if (flags & 2) {
        if (timer < 1000) {
            timer++;
        }
    }
    if (flags & 2) {
        input |= 0x10;
    } else {
        input &= ~0x10;
    }
    held = (input & 0x10) ? 1 : 0;
    pressed = (input & 2) ? 1 : 0;
    if (held) {
        if (counter < 0xFF) {
            counter++;
        }
        if (counter < threshold) {
            held = 0;
        }
    } else {
        counter = 0;
    }
    input = 0;
    if (pressed) {
        if (!held) {
            input |= 8;
        }
    }
    if (held && !pressed) {
        input |= 4;
    }
    if (held) {
        input |= 3;
    }
}

void Unk0201b6d4::func_0201be00() {
    Unk0209487c *file;
    int i;
    int w;
    int h;

    if (flags & 0x10) {
        func_0201c10c();
    }
    file = func_020a18e4()->archive->func_02093c18((const u32 *)data_020b8908);
    for (i = 0; i < 2; i++) {
        pointers[i] = Unk020916a4::func_02091840((flags & 1) != 0)->func_020919e4((int)file, 0);
        pointers[i]->unk4 = 0xC0000;
        pointers[i]->func_0208faac(i);
        pointers[i]->func_0208fb98(14);
        pointers[i]->func_0208fb80(0);
    }
    canvas->func_020905c4((flags & 1) ? 1 : 0);
    canvas->func_02090898(0);
    canvas->func_020908ac(1);
    w = cols >> 1;
    if (w << 1 != cols) {
        w++;
    }
    h = rows >> 1;
    if (h << 1 != rows) {
        h++;
    }
    canvas->func_0209066c(w, h);
    canvas->func_020905d4(15);
    if (background != 0) {
        int r;
        int c;

        for (r = 0; r != rows; r++) {
            for (c = 0; c != cols; c++) {
                int tile = 4;
                int draw = 1;

                if (r == 0) {
                    tile = 1;
                } else if (r == rows - 2) {
                    tile = 7;
                }
                if (c == 0) {
                    tile = 3;
                } else if (c == cols - 2) {
                    tile = 5;
                }
                if (r == 1 || c == 1 || c == cols - 1 || r == rows - 1) {
                    draw = 0;
                }
                if (c == 0 && r == 0) {
                    tile = 0;
                }
                if (c == cols - 2 && r == 0) {
                    tile = 2;
                }
                if (c == 0 && r == rows - 2) {
                    tile = 6;
                }
                if (c == cols - 2 && r == rows - 2) {
                    tile = 8;
                }
                if (draw) {
                    canvas->func_020906e4(background, c * 16, r * 16, tile);
                }
            }
        }
    }
    canvas->func_02090878(x - (cols << 15), y - (rows << 15));
    canvas->func_020908e0(1, 0);
    for (u32 j = 0; j < itemCount; j++) {
        Unk02098bc8 rect(0, func_itemTop(j), cols << 4, 0x10);
        canvas->func_020908bc(&rect);
        canvas->func_020909c8(font, func_020a00a0(func_0201ba94(), items[j].textId));
    }
    func_0201c3c8();
    flags |= 0x10;
}

void Unk0201b6d4::func_0201c10c() {
    if (!(flags & 0x10)) {
        return;
    }
    if (flags & 1) {
        Unk020916a4::func_02091820()->func_02091c68(pointers[0]);
        Unk020916a4::func_02091820()->func_02091c68(pointers[1]);
    } else {
        Unk020916a4::func_02091830()->func_02091c68(pointers[0]);
        Unk020916a4::func_02091830()->func_02091c68(pointers[1]);
    }
    canvas->func_0209088c();
    pointers[0] = 0;
    pointers[1] = 0;
    func_020a18e4()->archive->func_02093d14((const u32 *)data_020b8908);
    flags &= ~0x10;
}

int Unk0201b6d4::func_0201c198() {
    timer = 0;
    if (!(flags & 2)) {
        func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_OPEN_PIE_MENU", 0, 0),
                      0x7F, 0);
    }
    func_0201be00();
    flags |= 2;
    selected = 0x15;
    return 1;
}

int Unk0201b6d4::func_0201c208() {
    int valid;

    if (!(flags & 2)) {
        return 1;
    }
    func_0201c10c();
    flags &= ~2;
    valid = 0;
    if (selected >= 0 && selected < 10) {
        valid = 1;
    }
    if (!valid) {
        selected = 0x14;
        func_020a2ce8(func_020a2994(), func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_OPEN_PIE_MENU", 0, 0),
                      0x7F, 0);
    } else {
        func_020a2ce8(func_020a2994(),
                      func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_SURVIVAL_GUIDE_SELECT_ITEM", 0, 0),
                      0x7F, 0);
    }
    return 1;
}

void Unk0201b6d4::func_0201c2c4(int x, int y) {
    this->x = x;
    this->y = y;
    func_0201c2d8();
}

/* w is reused for the top of the items: a separate variable colors differently. */
void Unk0201b6d4::func_0201c2d8() {
    int w;
    int h;
    int left;
    u32 i;

    cols = ((maxWidth + 0x28) >> 4) + 1;
    rows = ((itemCount << 4) + 0x20) >> 4;
    if (rows <= 3) {
        rows = 4;
    }
    w = cols << 15;
    h = rows << 15;
    if (x < w) {
        x = w;
    }
    if (y < h) {
        y = h;
    }
    if (x > 0x100000 - w) {
        x = 0x100000 - w;
    }
    if (y > 0xC0000 - h) {
        y = 0xC0000 - h;
    }
    left = x - w + 0x14000;
    w = y - h + 0x10000;
    for (i = 0; i != itemCount; i++) {
        items[i].rect.x = left;
        items[i].rect.y = w + func_itemOffset(i);
        items[i].rect.w = (((cols - 1) << 4) - 0x14) << 12;
        items[i].rect.h = 0x10000;
    }
}

void Unk0201b6d4::func_0201c3c8() {
    Unk02095140 *bg = background;
    Unk0208f8b0 *p;

    if (bg != 0) {
        Unk020916a4::func_02091840((flags & 1) ? 1 : 0)->func_0209201c(bg, 0, 0, 0xF0, 0x10);
    }
    p = pointers[0];
    if (p == 0) {
        return;
    }
    Unk020916a4::func_02091840((flags & 1) ? 1 : 0)->func_0209201c(p->unk1c, 0, 0, 0xE0, 0x10);
}
