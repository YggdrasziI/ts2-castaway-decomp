/*
 * Unit 0x0202402C-0x02026F84: the paint screen (Unk0202402c, 0x53E8 bytes,
 * vtable 0x020B9100). Its file names say so (build/data/screens/paintscreen/ at
 * 0x020B8F08 to 0x020B90C8). A 128 x 128 canvas of four-bit pixels, with tools
 * (brush, fill, stamp, eraser, colour picker), brush sizes, a colour palette
 * with one swatch per pigment the player owns, a drawer of stamps, undo and
 * accept buttons.
 *
 * Bounds: hypothesis. The start is the constructor, after the last inline slot
 * of unit_020238EC.cpp; the end is the transition (unit_02026F84.cpp). `.rodata` holds the three local tables, `.data` the file
 * names, the vtable with its header and the warning of the fill stack. Real
 * file name unknown.
 *
 * It holds the kept copy 0x0202558C of the element base slot 7, after its first
 * user: defined inline here, so the base vtable is not emitted with it.
 *
 * Not complete: 22 / 32 functions. The gaps are register allocation and
 * scheduling, listed above func_020244f8; `.data` is 99.76 %, the warning string
 * of the fill stack being a local of its inline.
 */

#include "game/unk_screen.h"
#include "game/unk_element.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"

typedef signed char s8;

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* An object of the database. */
struct Unk0205cf00;

/* An inventory entry. */
struct Unk02054dc4 {
    Unk0205cf00 *def;
};

/* A list of inventory entries (unit_02054734.cpp). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    Unk02054dc4 *head;
    int count;
};

struct Unk020bfc9c;

/* The survival guide animation of the player (unit_02055118.cpp): opaque here. */
struct Unk02055118 {
    u8 unk0[9];
    u8 unk9;
    u8 unka;
};

/* The main game state (func_0206bce0): only what is used here. */
class Unk0206bcf0 {
public:
    void func_0206f560(bool on);
    void func_0206f578(bool on);

    u8 unk0[0x14c];
    Unk02055118 guide;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* A touch position. */
struct Unk020a07a4Point {
    int x;
    int y;
};

/* A list of loaded files (0x8 bytes). */
class Unk020a3f8c {
public:
    Unk020a3f8c();
    ~Unk020a3f8c();

    u32 unk0[2];
};

/* One background layer (unit_0208D304.cpp): only the fields used here. */
class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
    int func_0208d4c8();
    void func_0208d7a0(bool visible);

    int x;
    int y;
};

/* The background manager of one screen (unit_0208D304.cpp). */
class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dc08(int main);
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    void func_0208df4c(Unk0208d304 *layer);
    void func_0208e1b0(Unk02095140 *file, int index, u32 src, u32 dst, u32 n);
};

/* The key class of unit_0204BEEC.cpp: only what is used here. */
class Unk0204beec : public Unk020b9b80 {
public:
    Unk0204beec();
    ~Unk0204beec();
    void func_0204c0f8(bool main);
    void func_0204c11c(const u32 *name);
    void func_0204c1c4(int w, int h);
    void func_0204c1dc(bool toggle);
    void func_0204c1f4(bool on);
    void func_0204c218(bool lock);
    void func_0204c23c(short a, short b, short c, short d);
    void func_0204c4c4(short a, short b, short c, short d);
    void func_0204c540(int a, int b, int c);
    void func_0204c55c(int a, int b);
    void func_0204cfa8();
    void func_0204d3c0(int frame);

    bool func_04(bool locked);
    void func_00();
    void func_08();
    void func_0c(int priority);
    void func_14(int x, int y);

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk020b9e88Touch touch;
    Unk020b9e88Touch inside;
    Unk0209487c *file;
    Unk0208f8b0 *objects[6];
    int textId;
    Unk02090308 canvas;
    int textX;
    int textY;
    int hAlign;
    int vAlign;
    Unk02092830Font *font;
    Unk02098bc8 rect;
    int resource;
    s8 look[16];
    u16 flags;
    s8 priority;
    s8 color;
    u8 animation;
    u8 count;
    s8 oamPriority;
    int angle;
};

/* The drawer of unit_0204EE14.cpp. */
class Unk0204ee14 : public Unk020b9b80 {
public:
    Unk0204ee14();
    ~Unk0204ee14();
    void func_00();
    bool func_04(bool locked);
    void func_08();
    void func_0c(int objPriority);
    void func_0204f4a0(int mode, const u32 *name);
    void func_0204f4e4(int priority);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_0204f60c(int capacity);
    void func_0204f61c(Unk020b9b80 *child);

    u32 flags;
    Unk02098bc8 rect;
    Unk020b9b80 **children;
    int capacity;
    int count;
    int resource;
    int priority;
    int mask;
    int mode;
    int columns;
    int rows;
    Unk0208f8b0 *objects[6];
    Unk0208d304 *layer;
};

/* A position on the fill stack. */
struct Unk0202402cPoint {
    short x;
    short y;
};

extern Unk020d6240 data_020d6240;
extern Unk020bfc9c data_020bfc9c;
extern const u32 data_020ae7e0[];

bool func_02097248(int key);
bool func_020972c0(int key);

extern "C" {
Unk020d6240 *func_020a18e4();
bool func_020a14d8(Unk020d6240 *system);
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a075c(void *input, int index);
bool func_020a078c(void *input, int index);
Unk020a07a4Point func_020a07a4(void *input, int index);
Unk020a07a4Point func_020a07bc(void *input, int index);
void func_020a122c(Unk020d6240 *system);
void func_020a14e0(Unk020d6240 *system, int a);
void func_020a1494(Unk020d6240 *system, int a, int b);
void func_020a11f8(Unk020d6240 *system, int a, int b);
bool func_020a1280(Unk020d6240 *system, int a, int b);
void func_020a3fb0(Unk020a3f8c *files, Unk02093648 *archive);
Unk02095140 *func_020a4008(Unk020a3f8c *files, const char *name);
void func_020a4098(Unk020a3f8c *files);
void func_020a4108(Unk020a3f8c *files);
Unk0206bcf0 *func_0206bce0();
void func_0205515c(Unk02055118 *p, int a);
void func_02055220(Unk02055118 *p, int state, int count);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
Unk02054dc4 *func_02054858(Unk020547f8 *list, int index);
int func_0205d234(Unk0205cf00 *item, u32 key, u32 key2);
void func_02099b90(u32 data, void *dest, u32 size);
void func_020897b4(const char *fmt, ...);
void func_01ffadf8(Unk020916a4 *oam);
}

class Unk0202402c : public Unk020a07d4 {
public:
    Unk0202402c();
    virtual ~Unk0202402c();
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

    void func_020244f8();
    void func_020255a0();
    void func_02025df4(u8 c);
    void func_02025f84(int t);
    void func_02026160();
    void func_02026370();
    void func_0202640c();
    void func_020264a8(u8 c);
    void func_02026584();
    void func_020266d4(int x0, int y0, int x1, int y1, u8 c);
    void func_020267ec(short x, short y, int old);
    void func_02026c40(int x, int y, u8 c);
    u8 func_02026d18(int x, int y);
    int func_02026de4(Unk0208f8b0 *entry, int x, int y);
    void func_02026e4c(int x, int y, int c);

    inline void func_push(short x, short y) {
        if (count >= capacity) {
            func_020897b4("Optimize: stack reserve value should be more than %i", capacity);
            capacity += 0x20;
            Unk0202402cPoint *grown = new Unk0202402cPoint[capacity];
            for (u32 i = 0; i < count; i++) {
                Unk0202402cPoint &p = stack[i];
                grown[i].x = p.x;
                grown[i].y = p.y;
            }
            delete[] stack;
            stack = grown;
        }
        stack[count].x = x;
        stack[count].y = y;
        count++;
    }

    inline bool func_pop(short &x, short &y) {
        if (count == 0) {
            return false;
        }
        count--;
        x = stack[count].x;
        y = stack[count].y;
        return true;
    }

    Unk020a07d4Timer fade;
    u32 flags;
    u8 unk10;
    Unk020a3f8c files;
    Unk0208d304 *layer1;
    Unk0208d304 *layer0;
    Unk0204beec accept;
    Unk0204beec undo;
    Unk0204ee14 drawer;
    Unk0204beec cursor;
    Unk0204beec stamps[15];
    Unk0204beec paletteTiny[15];
    Unk0204beec paletteBug[15];
    Unk0204beec tools[4];
    Unk0204beec brushes[5];
    Unk0208f8b0 *brushSprite;
    Unk02090308 canvas;
    Unk02098bc8 rect;
    int lastX;
    int lastY;
    u8 stamp;
    u8 brushSize;
    u8 color;
    int tool;
    u32 snapshot[0x800];
    u32 capacity;
    u32 count;
    Unk0202402cPoint *stack;
    int unk53e4;
};

Unk0202402c::Unk0202402c()
    : flags(0), unk10(1), layer0(0), rect(0x38, 0x14, 0x80, 0x80), lastX(0x3e8), lastY(0x3e8), brushSize(0), color(1),
      tool(-1), capacity(0), count(0), stack(0), unk53e4(0) {}

Unk0202402c::~Unk0202402c() {
    func_020255a0();
    if (stack != 0) {
        delete[] stack;
    }
}

void Unk0202402c::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
    if (unk53e4 != 0) {
        Unk02055118 *guide = &func_0206bce0()->guide;
        func_0205515c(guide, unk53e4);
        guide->unk9 = 0;
        guide->unka = 1;
        func_02055220(guide, 0x3d, 0);
    }
}

bool Unk0202402c::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    unk10 = 1;
    func_020244f8();
    fade.func_duration(0x10);
    fade.state = 0;
    return false;
}

bool Unk0202402c::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0x10);
    fade.state = 3;
    func_020a1494(func_020a18e4(), 2, 0x10);
    func_020a11f8(func_020a18e4(), 2, 1);
    return false;
}

/*
 * 96.70 %: `this` is spilled like the original, but the main screen flag and the
 * loop counters take other stack slots and registers (the row height and the
 * small swatch height are not rebuilt per row). The flags are cleared by an
 * aggregate initializer (element stores give sp-relative adds). Tried: a real
 * loop (worse),
 * `row * 0x13 + 8` (moves `this` to r11, 78 %), the branches of the flag test
 * swapped.
 *
 * Other gaps: func_020266d4 90.29 % (`this` spilled instead of the colour),
 * func_02026c40 91.76 %, func_02026d18 91.57 %, func_02026e4c 94.62 % and
 * func_02026de4 70.00 % (scheduling of the tile index; locals, term orders,
 * `8 << n`, divisions and a word local tried),
 * func_02026584 97.88 %, func_020267ec 98.55 %, func_38 99.23 %, func_3c 99.36 %.
 */
void Unk0202402c::func_020244f8() {
    if (flags & 1) {
        return;
    }
    func_020a14e0(func_020a18e4(), 0);
    bool main = func_020a14d8(func_020a18e4());
    func_020a3fb0(&files, func_020a18e4()->archive);

    Unk02095140 *file = func_020a4008(&files, "build/data/screens/paintscreen/painting_background.nitro_map");
    layer0 = Unk0208db14::func_0208dc08(main)->func_0208dc44(file, 1, -1, 0);
    layer0->func_0208d7a0(true);
    layer0->func_0208d4b0(2);
    Unk0208db14::func_0208dc08(main)->func_0208e1b0(file, 0, 0, 0, 0x90);

    file = func_020a4008(&files, "build/data/screens/paintscreen/painting_drawer.nitro_map");
    drawer.func_0204f4a0(1, (const u32 *)"build/data/screens/paintscreen/painting_drawer.nitro_map");
    drawer.mask = 0x7e00;
    drawer.func_14(-0x47000, 0);
    drawer.func_0204f4e4(0);
    if (main) {
        drawer.flags |= 2;
    } else {
        drawer.flags &= ~2;
    }
    drawer.flags &= ~4;
    drawer.func_0204f60c(0x1e);
    drawer.func_0c(1);
    drawer.func_1c(0, drawer.func_10()->x);
    drawer.func_30(0x10);
    layer1 = Unk0208db14::func_0208dc08(main)->func_0208dc44(file, 0, drawer.layer->func_0208d4c8(), 0);
    layer1->func_0208d7a0(true);
    layer1->func_0208d4b0(1);
    layer1->x = -0x3e000;

    func_020a4008(&files, "build/data/screens/paintscreen/stamps.nitro_map");
    cursor.func_0204c11c((const u32 *)"build/data/screens/paintscreen/stamps.nitro_map");
    cursor.func_0204c0f8(main);
    cursor.func_0204c4c4(7, -1, 0, -1);
    cursor.func_0204c1c4(0x10000, 0x10000);
    cursor.func_14(0xa000, 0xa0000);

    func_020a4008(&files, "build/data/screens/paintscreen/accept_button.nitro_map");
    accept.func_0204c11c((const u32 *)"build/data/screens/paintscreen/accept_button.nitro_map");
    accept.func_0204c0f8(main);
    accept.flags |= 0x200;
    accept.func_0204c4c4(2, -1, 0, 1);
    accept.func_0204c1c4(0x20000, 0x20000);
    accept.func_14(0xda000, 0xa9000);
    accept.flags |= 4;
    accept.func_0c(1);

    u8 owned[15] = {0};
    Unk020547f8 list;
    func_02054d94(&data_020bfc9c, &list, data_020ae7e0, 1, 1);
    bool any = list.count > 0;
    for (int i = 0; i < list.count; i++) {
        owned[func_0205d234(func_02054858(&list, i)->def, 0x03e0cdc7, 0x2b3e6dd7)] = 1;
    }

    Unk02095140 *palette = func_020a4008(&files, "build/data/screens/paintscreen/palette_bug.nitro_map");
    int i = 0;
    int frame = 0;
    int tinyY = 8;
    int y = 8;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 2 && i < 15; col++) {
            paletteBug[i].func_0204c11c((const u32 *)"build/data/screens/paintscreen/palette_bug.nitro_map");
            paletteBug[i].func_0204c0f8(main);
            paletteBug[i].func_0204c1dc(true);
            paletteBug[i].func_0204c218(true);
            paletteBug[i].func_0204c4c4((i >> 1) + 8, -1, i >> 1, -1);
            int half = i % 2;
            paletteBug[i].func_0204d3c0(half);
            paletteBug[i].func_0204c55c(half + 2, -1);
            paletteBug[i].func_0204c1c4(0x10000, 0x10000);
            int x = col * 0x14 + 0xd6;
            paletteBug[i].func_14(FX32(x), FX32(y));
            paletteBug[i].flags |= 4;
            if (owned[i] != 0) {
                paletteBug[i].func_0c(1);
            } else {
                paletteBug[i].flags |= 0x10;
            }
            paletteBug[i].func_0204cfa8();

            paletteTiny[i].func_0204c11c((const u32 *)"build/data/screens/paintscreen/palette_tiny.nitro_map");
            paletteTiny[i].func_0204c0f8(main);
            paletteTiny[i].func_0204c1dc(true);
            paletteTiny[i].func_0204c218(true);
            paletteTiny[i].func_0204c4c4(0, -1, 0, -1);
            paletteTiny[i].func_0204c540(frame, frame + 1, -1);
            paletteTiny[i].func_0204c55c(frame + 1, frame + 1);
            paletteTiny[i].func_0204c1c4(0x8000, 0x8000);
            paletteTiny[i].func_14(0x13d000, FX32(tinyY));
            paletteTiny[i].flags |= 4;
            if (owned[i] != 0) {
                paletteTiny[i].func_0c(0);
            } else {
                paletteTiny[i].flags |= 0x10;
            }
            drawer.func_0204f61c(&paletteTiny[i]);
            frame += 2;
            tinyY += 10;
            i++;
        }
        y += 0x13;
    }
    Unk020916a4::func_02091840(main)->func_0209201c(palette, 0, 0x90, 0, 0x10);

    func_020a4008(&files, "build/data/screens/paintscreen/stamps.nitro_map");
    i = 0;
    frame = 0;
    y = 8;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 2 && i < 15; col++) {
            stamps[i].func_0204c11c((const u32 *)"build/data/screens/paintscreen/stamps.nitro_map");
            stamps[i].func_0204c0f8(main);
            stamps[i].func_0204c4c4(7, -1, 0, -1);
            stamps[i].func_0204c1c4(0x10000, 0x10000);
            int x = col * 0x14 + 0x114;
            stamps[i].func_14(FX32(x), FX32(y));
            stamps[i].flags |= 4;
            stamps[i].func_0204c1dc(true);
            stamps[i].func_0204c218(true);
            stamps[i].func_0204c540(frame, frame + 1, -1);
            stamps[i].func_0204c55c(frame + 1, frame + 1);
            stamps[i].func_0c(0);
            drawer.func_0204f61c(&stamps[i]);
            frame += 2;
            i++;
        }
        y += 0x13;
    }
    stamps[0].func_0204cfa8();

    u8 toolY[4] = {0x0c, 0x2a, 0x49, 0x67};
    func_020a4008(&files, "build/data/screens/paintscreen/tool_icons.nitro_map");
    for (u8 t = 0; t < 4; t++) {
        tools[t].func_0204c11c((const u32 *)"build/data/screens/paintscreen/tool_icons.nitro_map");
        tools[t].func_0204c0f8(main);
        tools[t].func_0204c1dc(true);
        tools[t].func_0204c218(true);
        tools[t].func_0204c4c4(3, 4, 0, 1);
        tools[t].func_0204c23c(4, 4, 1, 1);
        tools[t].func_0204c1c4(0x14000, 0x14000);
        tools[t].func_14(0x2000, FX32(toolY[t]));
        tools[t].flags |= 4;
        tools[t].func_0204d3c0(t);
        tools[t].func_0c(1);
    }
    tools[0].func_0204cfa8();

    undo.func_0204c11c((const u32 *)"build/data/screens/paintscreen/tool_icons.nitro_map");
    undo.func_0204c0f8(main);
    undo.func_0204c4c4(3, 4, 0, 1);
    undo.func_0204c1c4(0x14000, 0x20000);
    undo.func_14(0x2000, 0x86000);
    undo.func_0204d3c0(4);
    undo.flags |= 4;
    undo.func_0c(1);

    int brushW[5] = {8, 9, 10, 13, 16};
    int brushX[5] = {51, 82, 111, 142, 176};
    func_020a4008(&files, "build/data/screens/paintscreen/paintbrushes.nitro_map");
    for (u8 b = 0; b < 5; b++) {
        brushes[b].func_0204c11c((const u32 *)"build/data/screens/paintscreen/paintbrushes.nitro_map");
        brushes[b].func_0204c0f8(main);
        brushes[b].func_0204c1dc(true);
        brushes[b].func_0204c218(true);
        brushes[b].func_0204c4c4(5, 6, 0, 1);
        brushes[b].func_0204c23c(6, 6, 1, 1);
        brushes[b].func_0204c1c4(FX32(brushW[b]), 0x18000);
        brushes[b].func_14(FX32(brushX[b]), 0xa9000);
        brushes[b].flags |= 4;
        brushes[b].func_0204d3c0(b);
        brushes[b].func_0c(1);
    }
    brushes[0].func_0204cfa8();

    canvas.func_0209066c(4, 4);
    canvas.func_02090898(2);
    canvas.func_020905d4(0);
    canvas.func_02090878(rect.x << 12, rect.y << 12);
    canvas.func_020905ac();

    file = func_020a4008(&files, "build/data/screens/paintscreen/brush.nitro_map");
    brushSprite = Unk020916a4::func_02091840(main)->func_020919e4((int)file, 0xc8);
    brushSprite->func_0208fb80(3);
    brushSprite->unk0 = 0xff000;
    brushSprite->unk4 = 0x5a000;
    lastX = 0x3e8;
    lastY = 0x3e8;
    stamp = 0;
    brushSize = 0;
    color = 1;
    tool = -1;
    func_02099b90(0, snapshot, 0x2000);
    if (capacity == 0) {
        stack = new Unk0202402cPoint[0x80];
        capacity = 0x80;
    }
    if (any) {
        int first = -1;
        for (int c = 0; c < 15; c++) {
            if (owned[c] != 0) {
                first = c;
                break;
            }
        }
        color = first + 1;
        func_02025df4(color);
        paletteBug[color - 1].func_0204c1f4(true);
        paletteTiny[color - 1].func_0204c1f4(true);
        brushes[brushSize].func_0204c1f4(true);
        stamps[stamp].func_0204c1f4(true);
    } else {
        flags |= 8;
    }
    flags |= 1;
}

inline void Unk020b9b80::func_1c(int x, int y) {
    valuesX[0] = x;
    valuesX[1] = y;
    trackX = &keysX;
}

void Unk0202402c::func_020255a0() {
    if (!(flags & 1)) {
        return;
    }
    int main = func_020a14d8(func_020a18e4());
    Unk0208db14::func_0208dc08(main)->func_0208df4c(layer0);
    Unk0208db14::func_0208dc08(main)->func_0208df4c(layer1);
    layer0 = 0;
    accept.func_08();
    undo.func_08();
    drawer.func_08();
    cursor.func_08();
    for (u8 i = 0; i < 15; i++) {
        stamps[i].func_08();
    }
    for (u8 i = 0; i < 15; i++) {
        paletteBug[i].func_08();
        paletteTiny[i].func_08();
    }
    for (u8 i = 0; i < 4; i++) {
        tools[i].func_08();
    }
    for (u8 i = 0; i < 5; i++) {
        brushes[i].func_08();
    }
    Unk020916a4::func_02091840(main)->func_02091c68(brushSprite);
    brushSprite = 0;
    canvas.func_0209088c();
    func_020a4098(&files);
    func_020a4108(&files);
    delete[] stack;
    stack = 0;
    count = 0;
    capacity = 0;
    func_0206bce0()->func_0206f578(false);
    func_0206bce0()->func_0206f560(false);
    flags &= ~1;
}

bool Unk0202402c::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    done = accept.func_04(done);
    if (accept.touch.flags & 8) {
        func_18();
    }
    if (flags & 8) {
        done = true;
    }
    done = undo.func_04(done);
    if (undo.touch.flags & 8) {
        func_0202640c();
    }
    for (u8 i = 0; i < 15; i++) {
        done = stamps[i].func_04(done);
        if (stamps[i].touch.flags & 8) {
            stamps[stamp].func_0204c1f4(false);
            stamp = i;
            cursor.func_0204d3c0(i * 2);
        }
    }
    if (drawer.func_38()) {
        for (u8 i = 0; i < 15; i++) {
            done = paletteBug[i].func_04(done);
            if (paletteBug[i].touch.flags & 8) {
                func_02025df4(i + 1);
            }
        }
    } else if (drawer.func_34()) {
        for (u8 i = 0; i < 15; i++) {
            done = paletteTiny[i].func_04(done);
            if (paletteTiny[i].touch.flags & 8) {
                func_02025df4(i + 1);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        done = tools[i].func_04(done);
        if (tools[i].touch.flags & 8) {
            func_02025f84(i);
        }
    }
    for (int i = 0; i < 5; i++) {
        done = brushes[i].func_04(done);
        if (brushes[i].touch.flags & 8) {
            if (tool != 2) {
                func_02025f84(-1);
            }
            brushes[brushSize].func_0204c1f4(false);
            brushSize = i;
            brushes[brushSize].func_0204c1f4(true);
            brushSprite->func_0208faac(i);
        }
    }
    if (!done && func_020a078c(data_020d6240.input, 1)) {
        if (rect.func_02098bf4(func_020a07a4(data_020d6240.input, 1).x, func_020a07a4(data_020d6240.input, 1).y)) {
            func_02026160();
        } else {
            lastX = 0x3e8;
        }
        done = true;
    }
    if (cursor.flags & 2) {
        void *input = data_020d6240.input;
        if (!rect.func_02098bf4(func_020a07a4(input, 1).x, func_020a07a4(input, 1).y)
            || !func_020a078c(data_020d6240.input, 1)) {
            cursor.func_08();
        }
    }
    return done;
}

void Unk0202402c::func_38(bool active) {
    if (!active) {
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    if (fade.func_shown() || fade.func_opening()) {
        if (func_020a1280(func_020a18e4(), 0, 1) || func_020a1280(func_020a18e4(), 1, 1)) {
            func_020a122c(func_020a18e4());
        }
    }
    fade.func_step();
    accept.func_00();
    undo.func_00();
    drawer.func_00();
    for (u8 i = 0; i < 15; i++) {
        stamps[i].func_00();
    }
    for (u8 i = 0; i < 15; i++) {
        paletteBug[i].func_00();
        paletteTiny[i].func_00();
    }
    for (u8 i = 0; i < 4; i++) {
        tools[i].func_00();
    }
    for (u8 i = 0; i < 5; i++) {
        brushes[i].func_00();
    }
    if (fade.state == 4) {
        func_020255a0();
    }
}

void Unk0202402c::func_18() {
    if (func_020a0b8c(data_020d6240.unk8, this)) {
        flags |= 2;
    }
}

void Unk0202402c::func_02025df4(u8 c) {
    if (c < 1) {
        return;
    }
    paletteTiny[color - 1].func_0204c1f4(false);
    paletteBug[color - 1].func_0204c1f4(false);
    color = c;
    paletteTiny[color - 1].func_0204c1f4(true);
    paletteBug[color - 1].func_0204c1f4(true);
    for (int i = 0; i < 5; i++) {
        brushes[i].func_0204c4c4(5, 6, 0, color);
        brushes[i].func_0204c23c(6, 6, color, color);
    }
    brushes[0].func_0204cfa8();
    stamps[0].func_0204c4c4(7, -1, color - 1, -1);
    stamps[0].func_0204cfa8();
    if (tool == 2) {
        func_02025f84(-1);
        brushes[brushSize].func_0204c1f4(true);
    }
}

void Unk0202402c::func_02025f84(int t) {
    if (tool == 2) {
        paletteBug[color - 1].func_0204c1f4(true);
        for (int i = 0; i < 5; i++) {
            brushes[i].func_0204c4c4(5, 6, 0, color);
            brushes[i].func_0204c23c(6, 6, color, color);
        }
        brushes[0].func_0204cfa8();
    }
    if (tool != -1) {
        tools[tool].func_0204c1f4(false);
    }
    tool = t;
    brushes[brushSize].func_0204c1f4(false);
    if (t == 1) {
        drawer.func_24(0x10);
    } else {
        drawer.func_28(0x10);
    }
    if (t == 2) {
        paletteBug[color - 1].func_0204c1f4(false);
        brushes[brushSize].func_0204c1f4(true);
        for (int i = 0; i < 5; i++) {
            brushes[i].func_0204c4c4(5, 6, 0, 1);
            brushes[i].func_0204c23c(6, 6, 1, 1);
        }
        brushes[0].func_0204cfa8();
    }
}

void Unk0202402c::func_02026160() {
    switch (tool) {
    case -1:
        func_020264a8(color);
        return;
    case 0: {
        if (!func_020a075c(data_020d6240.input, 1)) {
            return;
        }
        func_02026370();
        int x = func_020a07a4(data_020d6240.input, 1).x - rect.x;
        int y = func_020a07a4(data_020d6240.input, 1).y - rect.y;
        int old = func_02026d18(x, y);
        func_020267ec(x, y, old);
        return;
    }
    case 3: {
        int x = func_020a07a4(data_020d6240.input, 1).x - rect.x;
        func_02025df4(func_02026d18(x, func_020a07a4(data_020d6240.input, 1).y - rect.y));
        return;
    }
    case 2:
        func_020264a8(0);
        return;
    case 1: {
        void *input = data_020d6240.input;
        cursor.func_14(func_020a07bc(input, 1).x - 0x8000, func_020a07bc(input, 1).y - 0x8000);
        if (!(cursor.flags & 2)) {
            cursor.func_0c(1);
            func_01ffadf8(Unk020916a4::func_02091830());
        }
        if (func_02097248(9)) {
            return;
        }
        if (func_02097248(8)) {
            return;
        }
        func_02026584();
        return;
    }
    }
}

void Unk0202402c::func_02026370() {
    int n = canvas.func_02090c8c(0)->func_0208fc74() >> 2;
    for (int i = 0; i < canvas.func_02090c84(); i++) {
        u32 *tiles = (u32 *)canvas.func_02090c8c(i)->unk20;
        for (int j = 0; j < n; j++) {
            snapshot[i * n + j] = tiles[j];
        }
    }
}

void Unk0202402c::func_0202640c() {
    int n = canvas.func_02090c8c(0)->func_0208fc74() >> 2;
    for (int i = 0; i < canvas.func_02090c84(); i++) {
        u32 *tiles = (u32 *)canvas.func_02090c8c(i)->unk20;
        for (int j = 0; j < n; j++) {
            tiles[j] = snapshot[i * n + j];
        }
    }
}

void Unk0202402c::func_020264a8(u8 c) {
    int x = func_020a07a4(data_020d6240.input, 1).x - rect.x;
    int y = func_020a07a4(data_020d6240.input, 1).y - rect.y;
    if (func_020a075c(data_020d6240.input, 1) || lastX == 0x3e8) {
        lastX = x - 8;
        lastY = y - 8;
        func_02026370();
    }
    func_020266d4(lastX, lastY, x - 8, y - 8, c);
    lastX = x - 8;
    lastY = y - 8;
}

void Unk0202402c::func_02026584() {
    int x = func_020a07a4(data_020d6240.input, 1).x - rect.x;
    int y = func_020a07a4(data_020d6240.input, 1).y - rect.y;
    int originX = x - 8;
    int originY = y - 8;
    if (func_020972c0(9) || func_020972c0(8) || func_020a075c(data_020d6240.input, 1)) {
        func_02026370();
    }
    int left = x - 8;
    if (x - 8 < 0) {
        left = 0;
    }
    int top = originY;
    if (y - 8 < 0) {
        top = 0;
    }
    int right = x + 8;
    if (right > 0x80) {
        right = 0x80;
    }
    int bottom = y + 8;
    if (bottom > 0x80) {
        bottom = 0x80;
    }
    for (int py = top; py < bottom; py++) {
        for (int px = left; px < right; px++) {
            if (func_02026de4(cursor.objects[0], px - originX, py - originY)) {
                func_02026e4c(px, py, color);
            }
        }
    }
}

void Unk0202402c::func_020266d4(int x0, int y0, int x1, int y1, u8 c) {
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepX;
    int stepY;
    if (dy < 0) {
        stepY = -1;
        dy = -dy;
    } else {
        stepY = 1;
    }
    if (dx < 0) {
        dx = -dx;
        stepX = -1;
    } else {
        stepX = 1;
    }
    dy <<= 1;
    dx <<= 1;
    func_02026c40(x0, y0, c);
    if (dx > dy) {
        int err = dy - (dx >> 1);
        if (x0 == x1) {
            return;
        }
        do {
            if (err >= 0) {
                y0 += stepY;
                err -= dx;
            }
            x0 += stepX;
            err += dy;
            func_02026c40(x0, y0, c);
        } while (x0 != x1);
    } else {
        int err = dx - (dy >> 1);
        if (y0 == y1) {
            return;
        }
        do {
            if (err >= 0) {
                x0 += stepX;
                err -= dy;
            }
            y0 += stepY;
            err += dx;
            func_02026c40(x0, y0, c);
        } while (y0 != y1);
    }
}

void Unk0202402c::func_020267ec(short x, short y, int old) {
    if (old == color) {
        return;
    }
    count = 0;
    func_push(x, y);
    while (func_pop(x, y)) {
        int py;
        for (py = y; py >= 0; py--) {
            if (func_02026d18(x, py) != old) {
                break;
            }
        }
        py++;
        int left = 0;
        int right = 0;
        for (; py < 0x80; py++) {
            if (func_02026d18(x, py) != old) {
                break;
            }
            func_02026e4c(x, py, color);
            if (!left && x > 0) {
                if (func_02026d18(x - 1, py) == old) {
                    func_push(x - 1, py);
                    left = 1;
                }
            } else if (left && x > 0) {
                if (func_02026d18(x - 1, py) != old) {
                    left = 0;
                }
            }
            if (!right && x < 0x7f) {
                if (func_02026d18(x + 1, py) == old) {
                    func_push(x + 1, py);
                    right = 1;
                }
            } else if (right && x < 0x7f) {
                if (func_02026d18(x + 1, py) != old) {
                    right = 0;
                }
            }
        }
    }
}

void Unk0202402c::func_02026c40(int x, int y, u8 c) {
    int originY;
    int bottom;
    int right;
    int originX;
    int px;
    originY = y;
    originX = x;
    bottom = y + 0x10;
    right = x + 0x10;
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (right > 0x80) {
        right = 0x80;
    }
    if (bottom > 0x80) {
        bottom = 0x80;
    }
    for (; y < bottom; y++) {
        for (px = x; px < right; px++) {
            if (func_02026de4(brushSprite, px - originX, y - originY)) {
                func_02026e4c(px, y, c);
            }
        }
    }
}

u8 Unk0202402c::func_02026d18(int x, int y) {
    canvas.func_02090c84();
    int cols = canvas.func_02090cbc();
    int rows = canvas.func_02090cc4();
    int cx = x >> 6;
    int cy = y >> 6;
    if (cx >= cols || cy >= rows) {
        return 0;
    }
    if (cx < 0) {
        cx = 0;
    }
    if (cy < 0) {
        cy = 0;
    }
    Unk0208f8b0 *entry = canvas.func_02090c8c(cy * cols + cx);
    if (entry == 0) {
        return 0;
    }
    int px = x - (cx << 6);
    int py = y - (cy << 6);
    u32 *tiles = (u32 *)entry->unk20;
    return (tiles[(px & ~7) + ((py >> 3) << 6) + py % 8] >> ((px % 8) * 4)) & 0xf;
}

int Unk0202402c::func_02026de4(Unk0208f8b0 *entry, int x, int y) {
    if (entry == 0) {
        return 0;
    }
    int width = 1 << (entry->unk10_0 + 3);
    u32 *tiles = (u32 *)entry->unk20;
    return (tiles[(x & ~7) + (y >> 3) * width + y % 8] >> ((x % 8) * 4)) & 0xf;
}

void Unk0202402c::func_02026e4c(int x, int y, int c) {
    canvas.func_02090c84();
    int cols = canvas.func_02090cbc();
    int rows = canvas.func_02090cc4();
    int cx = x >> 6;
    int cy = y >> 6;
    if (cx >= cols || cy >= rows) {
        return;
    }
    if (cx < 0) {
        cx = 0;
    }
    if (cy < 0) {
        cy = 0;
    }
    Unk0208f8b0 *entry = canvas.func_02090c8c(cy * cols + cx);
    if (entry == 0) {
        return;
    }
    int px = x - (cx << 6);
    int py = y - (cy << 6);
    u32 *tiles = (u32 *)entry->unk20;
    py = (px & ~7) + ((py >> 3) << 6) + py % 8;
    int shift = (px % 8) * 4;
    tiles[py] = (tiles[py] & ~(0xf << shift)) | (c << shift);
}

bool Unk0202402c::func_34() {
    return false;
}

bool Unk0202402c::func_28() {
    return fade.func_shown();
}

bool Unk0202402c::func_2c() {
    return fade.func_hidden();
}

bool Unk0202402c::func_14() {
    return (flags & 2) != 0;
}

void Unk0202402c::func_1c() {
    flags &= ~2;
}

bool Unk0202402c::func_20() {
    return false;
}

void Unk0202402c::func_24() {}
