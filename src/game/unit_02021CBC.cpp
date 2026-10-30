/*
 * Unit 0x02021CBC-0x020238EC: the map page of the survival guide (Unk02021cbc,
 * 0x198 bytes, vtable 0x020B8E7C), on the screen base Unk0203c188 and built by
 * the survival guide (unit_02027994.cpp). The strings prove the file format:
 * a data tree with a "MapScreen" root, a "Header" (map "Filename", "Size") and
 * "Icons" ("Icon" with "filename", "x", "y", "frame", "destination"). The page
 * scrolls a tiled map with two scroll bars or by dragging, and shows one button
 * per lot; a released button whose lot index is valid goes to that lot. Three
 * lots change frames from the inventory.
 *
 * Bounds: hypothesis. The start is the constructor, after the screen ending at
 * 0x02021CBC; the end is unit_020238EC.cpp. `.rodata` holds the key table and four
 * unused constants, `.data` the strings, the vtable with its header.
 * Real file name unknown.
 *
 * Not complete: func_3c and func_0202278c are below 100 % (comments above them).
 *
 * It holds the kept copies of the inline slots of Unk0203c188 (func_40 after the
 * first update, the others at the end): defined inline here, so the base vtable
 * is not emitted with them.
 */

#include "game/unk_screen.h"
#include "game/unk_sim.h"
#include "game/unk_element.h"
#include "game/unk_canvas.h"
#include "game/unk_oam.h"
#include "game/unk_datatree.h"
#include "game/unk_resource.h"

typedef signed char s8;

#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

/* A list of inventory entries (unit_02054734.cpp). */
class Unk020547f8 {
public:
    Unk020547f8();
    ~Unk020547f8();

    void *head;
    int count;
};

struct Unk020bfc9c;

/* A map of the world (unit_02055EF8.cpp): only the field used here. */
struct Unk02058788 {
    u8 unk0[0x24];
    int lot;
};

/* A lot record (unit_02055EF8.cpp). */
struct Unk020589ac {
    int unk0;
    u32 hash;
};

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    void *unk8;
    int unkc[2];
    Unk02093648 *archive;
};

/* One background layer (unit_0208D304.cpp): only the fields used here. */
class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
    void func_0208d7a0(bool visible);
};

/* The background manager of one screen (unit_0208D304.cpp). */
class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbf8();
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    void func_0208df4c(Unk0208d304 *layer);
};

/* The key class of unit_0204BEEC.cpp: only what is used here. */
class Unk0204beec : public Unk020b9b80 {
public:
    Unk0204beec();
    ~Unk0204beec();
    void func_0204c0f8(bool main);
    void func_0204c144(u32 hash);
    void func_0204c16c(int priority);
    void func_0204c1b8(int priority);
    void func_0204c1c4(int w, int h);
    void func_0204c4c4(short a, short b, short c, short d);
    void func_0204c540(int a, int b, int c);

    bool func_04(bool locked);
    void func_00();
    void func_08();
    void func_0c(int priority);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);

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

/* The scroll bar of unit_02051DA0.cpp. */
class Unk02051da0 : public Unk020b9e88 {
public:
    Unk02051da0();
    ~Unk02051da0();
    void func_02051ec4(Unk020a7c90 *track, Unk020a7c90 *knob, int padX, int padY, bool horizontal, bool flag);
    void func_08();
    bool func_0c(bool done);
    Unk02098bc8 *func_10();
    void func_14(int x, int y);
    void func_18(bool show);
    int func_02052184();
    void func_020527a0(int v);

    u16 flags;
    Unk020b9e88Touch touch;
    int value;
    int min;
    int max;
    int offset;
    Unk02098e70 last;
    int deadZone;
    Unk02098bc8 bounds;
    Unk02098bc8 range;
    Unk02098bc8 hit;
    Unk020a7c90 *track;
    Unk020a7c90 *knob;
};

/* A lot button on the map. */
class Unk02023388 {
public:
    Unk02023388() : hash(0), frame(0), x(0), y(0), visible(0) {}

    Unk0204beec key;
    u32 hash;
    int frame;
    int x;
    int y;
    u8 visible;
};

extern Unk020d6240 data_020d6240;
extern Unk020c3ba4 data_020c3ba4;
extern Unk020bfc9c data_020bfc9c;

Unk02098e70Base *func_02097a4c();

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
bool func_020a075c(void *input, int index);
bool func_020a078c(void *input, int index);
Unk02058788 *func_02058788(Unk020c3ba4 *world, int map);
Unk020589ac *func_020589ac(Unk020c3ba4 *world, int id);
bool func_02058cc8(Unk020c3ba4 *world, int id);
u32 func_02056e7c(u32 hash);
u32 func_0209a3c4(u32 hash, const char *str);
int func_02077b3c(int a, int b);
void func_02054d94(Unk020bfc9c *p, Unk020547f8 *out, const u32 *keys, u32 n, u32 min);
}

static inline Unk02093648 *func_archive() {
    return func_020a18e4()->archive;
}

class Unk02021cbc : public Unk0203c188 {
public:
    Unk02021cbc(Unk0203c188Owner *owner, u32 hash);
    virtual ~Unk02021cbc();
    virtual void func_08();
    virtual bool func_0c(short a);
    virtual bool func_10();
    virtual void func_38(bool active);
    virtual bool func_3c(bool done);

    void func_02021f94();
    void func_020220ec();
    void func_02022718();
    void func_0202278c(u32 hash);
    void func_02022c40();
    void func_02022d80();
    void func_02023108();
    void func_020231d8(Unk02096348 *file);
    void func_020233b8(Unk02096348 *file, const Unk0209674c &node);
    void func_02023600(Unk02096348 *file, const Unk0209674c &node);

    Unk020a9d58 *layout;
    Unk02051da0 scrollX;
    Unk02051da0 scrollY;
    Unk0208d304 *background;
    int x;
    int y;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    int columns;
    int rows;
    int tileCount;
    Unk0208f8b0 **tiles;
    Unk02095140 *mapFile;
    int mapIndex;
    int iconCount;
    Unk02023388 *icons;
    Unk02095140 *iconFile;
    int iconIndex;
    u32 iconHash;
    u32 hash;
    int lastX;
    int lastY;
    int dragged;
    int current;
    int counter;
};

Unk02021cbc::Unk02021cbc(Unk0203c188Owner *owner, u32 hash)
    : Unk0203c188(owner), background(0), x(0), y(0), width(0), height(0), tileWidth(0), tileHeight(0), columns(0),
      rows(0), tileCount(0), tiles(0), mapFile(0), mapIndex(-1), iconCount(0), icons(0), iconFile(0), iconIndex(-1),
      iconHash(0), hash(hash), lastX(-1), lastY(-1), dragged(0), current(0), counter(0) {
    Unk020a7af4Entry entries[0x1e];
    Unk020a7af4 names(entries, 0x1e);
    layout = new Unk020a9d58(func_020a18e4()->archive, 0);
    func_020aba38(func_020a18e4()->archive, 0x6173d227, layout, &names);
    func_020a9db8(layout, func_020a154c, 0);
    Unk020a7c90 *knob = func_020aa040(layout, 0xb, func_020a7b50(&names, 0x2e3da297));
    scrollX.func_02051ec4(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x6f4589a7)), knob, 0, 0, true, false);
    knob = func_020aa040(layout, 0xb, func_020a7b50(&names, 0xdf7d3b52));
    scrollY.func_02051ec4(func_020aa040(layout, 0xb, func_020a7b50(&names, 0x224e439d)), knob, 0, 0, false, false);
}

Unk02021cbc::~Unk02021cbc() {
    func_020220ec();
    delete layout;
}

void Unk02021cbc::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

void Unk02021cbc::func_02021f94() {
    func_020220ec();
    Unk02093648 *archive = func_020a18e4()->archive;
    func_0202278c(hash);
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(
        archive->func_02093e30((const u32 *)"build/data/screens/survivalguide/guide_background_map.nitro_map"));
    background = Unk0208db14::func_0208dbf8()->func_0208dc44(file, 1, -1, 0);
    background->func_0208d4b0(2);
    background->func_0208d7a0(true);
    Unk020916a4::func_02091830()->func_0209201c(iconFile, 0, 0x10, 0xf0, 0x10);
    int max = FX32(0xb5 - height);
    scrollY.min = 0x9000;
    scrollY.max = max;
    scrollY.func_020527a0(x);
    max = FX32(0xd2 - width);
    scrollX.min = 0xa000;
    scrollX.max = max;
    scrollX.func_020527a0(y);
    func_020aa06c(layout, true);
    flags |= 2;
}

void Unk02021cbc::func_020220ec() {
    if (!(flags & 2)) {
        return;
    }
    func_02022c40();
    Unk0208db14::func_0208dbf8()->func_0208df4c(background);
    background = 0;
    Unk02093648 *archive = func_020a18e4()->archive;
    archive->func_02093c58(
        archive->func_02093e30((const u32 *)"build/data/screens/survivalguide/guide_background_map.nitro_map"));
    func_020aa06c(layout, false);
    flags &= ~2;
}

void Unk02021cbc::func_38(bool active) {
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
    func_02022d80();
    scrollX.func_08();
    scrollY.func_08();
    func_020aa158(layout);
    if (fade.state == 4) {
        func_020220ec();
    }
}

inline void Unk0203c188::func_40(bool a) {
    if (a) {
        flags |= 8;
    } else {
        flags &= ~8;
    }
}

bool Unk02021cbc::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_02021f94();
    if (flags & 8) {
        fade.func_duration(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = 0;
    fade.state = 0;
    return false;
}

bool Unk02021cbc::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    if (flags & 8) {
        fade.func_duration(0x22);
    } else {
        fade.func_duration(0x10);
    }
    fade.timer = fade.duration;
    fade.state = 3;
    return false;
}

/*
 * 99.41 %: the result of the second scroll bar and the loop offset swap r7 and r6.
 * Tried: other declaration orders of the index and of the result, an int result.
 */
bool Unk02021cbc::func_3c(bool done) {
    if (!func_30()) {
        done = true;
    }
    int i;
    done = scrollX.func_0c(done);
    if (scrollX.touch.flags & 1) {
        x = scrollX.func_02052184();
    }
    bool used = scrollY.func_0c(done);
    if (scrollY.touch.flags & 1) {
        y = scrollY.func_02052184();
    }
    bool held = false;
    bool drag = dragged > 10;
    bool locked = drag || used;
    if (func_020a078c(data_020d6240.input, 1)) {
        int px = func_02097a4c()->x;
        int py = func_02097a4c()->y;
        if (px < 10 || px > 0xd2 || py < 9 || py > 0xb5 || (px <= 0x1a && py <= 0x17)) {
            locked = true;
            drag = true;
        }
    }
    for (i = 0; i < iconCount; i++) {
        if (icons[i].visible) {
            locked = icons[i].key.func_04(locked);
            if (!held) {
                held = (icons[i].key.touch.flags & 1) != 0;
            }
            if (icons[i].key.touch.flags & 8) {
                int lot = func_02056e7c(icons[i].hash);
                if (lot < 0x29) {
                    owner->func_18();
                    *(int *)(owner->unk4 + 0x28) = lot;
                    break;
                }
            }
        }
    }
    if (locked && !drag) {
        used = true;
    }
    if (func_020a075c(data_020d6240.input, 1)) {
        lastX = func_02097a4c()->x;
        lastY = func_02097a4c()->y;
    }
    if (func_020a078c(data_020d6240.input, 1) && !used) {
        int px = func_02097a4c()->x;
        int py = func_02097a4c()->y;
        if (px >= 10 && px <= 0xd2 && py >= 9 && py <= 0xb5 && (px > 0x1a || py > 0x17)) {
            int dx = px - lastX;
            int dy = py - lastY;
            used = true;
            if (dx > 1) {
                dx -= 1;
            } else if (dx < -1) {
                dx += 1;
            } else {
                dx = 0;
            }
            if (dy > 1) {
                dy -= 1;
            } else if (dy < -1) {
                dy += 1;
            } else {
                dy = 0;
            }
            if (dx != 0 || dy != 0) {
                dragged += dx > 0 ? dx : -dx;
                dragged += dy > 0 ? dy : -dy;
                x += FX32(dx);
                y += FX32(dy);
                lastX = px;
                lastY = py;
            }
        } else {
            lastX = px;
            lastY = py;
        }
    } else {
        dragged = 0;
    }
    return used;
}

void Unk02021cbc::func_02022718() {
    Unk02023388 *icon = &icons[current];
    if (!(icon->key.flags & 2)) {
        return;
    }
    if (icon->key.touch.flags & 1) {
        return;
    }
    if (++counter <= 6) {
        return;
    }
    int next = icon->key.objects[0]->func_0208faa4() + 1;
    if (next > 0x5b) {
        next = 0x58;
    }
    icon->key.func_0204c540(next, 0x5c, -1);
    counter = 0;
}

/*
 * 99.56 %: the original saves `hash` before `this` and loads the world address
 * twice for the first call. Tried: a local map, a local record, an inline wrapper.
 */
void Unk02021cbc::func_0202278c(u32 hash) {
    int map = data_020c3ba4.map;
    Unk02058788 *record = func_02058788(&data_020c3ba4, map);
    u32 here = func_0209a3c4(func_020589ac(&data_020c3ba4, record->lot)->hash, "lot.lot.nitro_lot");
    int index = func_archive()->func_02093e9c(hash);
    if (index == -1) {
        return;
    }
    Unk0209487c *file = func_archive()->func_02093a9c(index);
    if (file == 0) {
        return;
    }
    func_020231d8((Unk02096348 *)file);
    func_archive()->func_02093c58(index);
    if (mapIndex != -1) {
        mapFile = (Unk02095140 *)func_archive()->func_02093a9c(mapIndex);
        tileCount = mapFile->func_02095180()->count;
        tileWidth = mapFile->func_02095180()->width << 3;
        tileHeight = mapFile->func_02095180()->height << 3;
        if (width > 0) {
            int n = width;
            if (tileWidth != 0) {
                n = func_02077b3c(n, tileWidth);
            }
            columns = n;
        }
        if (height > 0) {
            int n = height;
            if (tileHeight != 0) {
                n = func_02077b3c(n, tileHeight);
            }
            rows = n;
        }
        tiles = new Unk0208f8b0 *[tileCount];
        for (int i = 0; i < tileCount; i++) {
            tiles[i] = 0;
        }
    }
    if (iconIndex != -1) {
        iconFile = (Unk02095140 *)func_archive()->func_02093a9c(iconIndex);
        int w = iconFile->func_02095180()->width << 3;
        int h = iconFile->func_02095180()->height << 3;
        for (int i = 0; i < iconCount; i++) {
            if (func_02058cc8(&data_020c3ba4, i)) {
                icons[i].visible = 1;
                icons[i].x -= w << 11;
                icons[i].y -= h << 11;
                icons[i].key.func_0204c144(iconHash);
                icons[i].key.func_0204c16c(3);
                icons[i].key.func_0204c0f8(false);
                icons[i].key.func_0204c1c4(w << 12, h << 12);
                icons[i].key.func_14(icons[i].x, icons[i].y);
                icons[i].key.func_0204c4c4(0xf, -1, -1, -1);
                icons[i].key.func_0204c1b8(1);
                icons[i].key.func_0204c540(icons[i].frame, icons[i].frame + 1, -1);
                if (icons[i].hash == 0x12186b28) {
                    u32 keys[3] = {0x882ff256, 0x882ff257, 0x882ff258};
                    Unk020547f8 list;
                    func_02054d94(&data_020bfc9c, &list, keys, 3, 1);
                    if (list.count == 3) {
                        icons[i].key.func_0204c540(0x52, 0x53, -1);
                    }
                } else if (icons[i].hash == 0x3dba27ab) {
                    u32 key = 0x3e7837a9;
                    Unk020547f8 list;
                    func_02054d94(&data_020bfc9c, &list, &key, 1, 1);
                    if (list.count > 0) {
                        icons[i].key.func_0204c540(0x54, 0x55, -1);
                    }
                } else if (icons[i].hash == 0xbe59689a) {
                    u32 key = 0x99a2c231;
                    Unk020547f8 list;
                    func_02054d94(&data_020bfc9c, &list, &key, 1, 1);
                    if (list.count == 5) {
                        icons[i].key.func_0204c540(0x56, 0x57, -1);
                    }
                }
                if (here == icons[i].hash) {
                    current = i;
                    icons[i].key.func_0204c540(0x58, 0x5c, -1);
                }
            }
        }
    }
    func_02023108();
    func_02022d80();
}

void Unk02021cbc::func_02022c40() {
    if (tiles != 0) {
        for (int i = 0; i < tileCount; i++) {
            Unk0208f8b0 *tile = tiles[i];
            if (tile != 0) {
                Unk020916a4::func_02091830()->func_02091c68(tile);
                tiles[i] = 0;
            }
        }
        tileCount = 0;
        delete[] tiles;
        tiles = 0;
    }
    if (mapIndex != -1) {
        func_archive()->func_02093c58(mapIndex);
        mapFile = 0;
    }
    for (int i = 0; i < iconCount; i++) {
        icons[i].key.func_08();
    }
    if (icons != 0) {
        delete[] icons;
    }
    icons = 0;
    iconCount = 0;
    if (iconIndex != -1) {
        func_archive()->func_02093c58(iconIndex);
        iconFile = 0;
    }
}

void Unk02021cbc::func_02022d80() {
    if (tiles == 0) {
        return;
    }
    for (int i = 0; i < iconCount; i++) {
        Unk02098bc8 *r = icons[i].key.func_10();
        if (r->x > 0xd2000 || r->y > 0xb5000 || r->x + r->w <= 0xa000 || r->y + r->h <= 0x9000) {
            icons[i].key.func_08();
        } else {
            icons[i].key.func_0c(3);
        }
    }
    func_02022718();
    if (x > 0xa000) {
        x = 0xa000;
    }
    if (y > 0x9000) {
        y = 0x9000;
    }
    int w = width;
    if (x + FX32(w) < 0xd2000) {
        x = -FX32(w) + 0xd2000;
    }
    int h = height;
    if (y + FX32(h) < 0xb5000) {
        y = -FX32(h) + 0xb5000;
    }
    scrollX.func_020527a0(x);
    scrollY.func_020527a0(y);
    int col = 0;
    int row = 0;
    for (int i = 0; i < tileCount; i++) {
        int px = x + ((col * tileWidth) << 12);
        int py = y + ((row * tileHeight) << 12);
        if (px > 0xd2000 || py > 0xb5000 || px + (tileWidth << 12) <= 0xa000 || py + (tileHeight << 12) <= 0x9000) {
            Unk0208f8b0 *tile = tiles[i];
            if (tile != 0) {
                Unk020916a4::func_02091830()->func_02091c68(tile);
                tiles[i] = 0;
            }
        } else {
            if (tiles[i] == 0) {
                tiles[i] = Unk020916a4::func_02091830()->func_020919e4((int)mapFile, i + 10);
                if (tiles[i] != 0) {
                    tiles[i]->func_0208fb98(0xc);
                    tiles[i]->func_0208fb80(3);
                    tiles[i]->func_0208faac(i);
                }
            }
            if (tiles[i] != 0) {
                tiles[i]->unk0 = px;
                tiles[i]->unk4 = py;
            }
        }
        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }
    for (int i = 0; i < iconCount; i++) {
        icons[i].key.func_14(x + icons[i].x, y + icons[i].y);
        icons[i].key.func_00();
    }
}

void Unk02021cbc::func_02023108() {
    Unk020589ac *lot = func_020589ac(&data_020c3ba4, data_020c3ba4.map);
    int cx = 0;
    int cy = 0;
    int w = 0;
    int h = 0;
    if (iconFile != 0) {
        w = iconFile->func_02095180()->width << 3;
        h = iconFile->func_02095180()->height << 3;
    }
    if (lot != 0) {
        u32 key = func_0209a3c4(lot->hash, "lot.lot.nitro_lot");
        for (int i = 0; i < iconCount; i++) {
            if (key == icons[i].hash) {
                cx = icons[i].x + (w << 11);
                cy = icons[i].y + (h << 11);
                break;
            }
        }
    }
    x = 0x80000 - cx;
    y = 0x60000 - cy;
}

void Unk02021cbc::func_020231d8(Unk02096348 *file) {
    if (file == 0) {
        return;
    }
    Unk0209674c root = file->func_02096980();
    if (!root.func_0209683c((const u32 *)"MapScreen")) {
        return;
    }
    for (int i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c child;
        child = root.func_02096774(i);
        if (child.func_0209683c((const u32 *)"Header")) {
            func_020233b8(file, child);
        } else if (child.func_0209683c((const u32 *)"Icons")) {
            int n = 0;
            Unk0209674c entry;
            for (int j = 0; j < child.func_020967ec(); j++) {
                entry = child.func_02096774(j);
                if (entry.func_0209683c((const u32 *)"Icon")) {
                    n++;
                }
            }
            if (n > 0) {
                iconCount = n;
                icons = new Unk02023388[n];
                func_02023600(file, child);
            }
        }
    }
}

void Unk02021cbc::func_020233b8(Unk02096348 *file, const Unk0209674c &node) {
    Unk0209674c child;
    Unk0209674c entry;
    u32 name = 0;
    int w = 0;
    int h = 0;
    for (int i = 0; i < node.func_020967ec(); i++) {
        child = node.func_02096774(i);
        if (child.func_0209683c((const u32 *)"Filename")) {
            for (int j = 0; j < child.func_020967ec(); j++) {
                entry = child.func_02096774(j);
                if (entry.func_0209683c((const u32 *)"map")) {
                    name = file->func_02096590(entry.func_0209688c());
                }
            }
        } else if (child.func_0209683c((const u32 *)"Size")) {
            for (int j = 0; j < child.func_020967ec(); j++) {
                entry = child.func_02096774(j);
                if (entry.func_0209683c((const u32 *)"width")) {
                    w = file->func_02096574(entry.func_0209688c());
                } else if (entry.func_0209683c((const u32 *)"height")) {
                    h = file->func_02096574(entry.func_0209688c());
                }
            }
        }
    }
    mapIndex = func_archive()->func_02093e9c(name);
    width = w;
    height = h;
}

void Unk02021cbc::func_02023600(Unk02096348 *file, const Unk0209674c &node) {
    Unk0209674c child;
    Unk0209674c entry;
    u32 name = 0;
    u32 destination = 0;
    int px = 0;
    int py = 0;
    int frame = 0;
    int n = 0;
    for (int i = 0; i < node.func_020967ec(); i++) {
        child = node.func_02096774(i);
        if (child.func_0209683c((const u32 *)"filename")) {
            name = file->func_02096590(child.func_0209688c());
        }
        if (child.func_0209683c((const u32 *)"Icon")) {
            for (int j = 0; j < child.func_020967ec(); j++) {
                entry = child.func_02096774(j);
                if (entry.func_0209683c((const u32 *)"x")) {
                    px = file->func_02096574(entry.func_0209688c());
                } else if (entry.func_0209683c((const u32 *)"y")) {
                    py = file->func_02096574(entry.func_0209688c());
                } else if (entry.func_0209683c((const u32 *)"frame")) {
                    frame = file->func_02096574(entry.func_0209688c());
                } else if (entry.func_0209683c((const u32 *)"destination")) {
                    destination = file->func_02096590(entry.func_0209688c());
                }
            }
            if (icons != 0) {
                icons[n].frame = frame;
                icons[n].hash = destination;
                icons[n].x = px << 12;
                icons[n].y = py << 12;
            }
            n++;
        }
    }
    iconIndex = func_archive()->func_02093e9c(name);
    iconHash = name;
}

inline bool Unk0203c188::func_34() {
    return true;
}

inline bool Unk0203c188::func_28() {
    return fade.func_shown();
}

inline bool Unk0203c188::func_2c() {
    return fade.func_hidden();
}

inline bool Unk0203c188::func_14() {
    return (flags & 4) != 0;
}

inline void Unk0203c188::func_1c() {
    flags &= ~4;
}

inline bool Unk0203c188::func_20() {
    return false;
}

inline void Unk0203c188::func_24() {}

extern const u32 data_020ae790[] = {0x5b, 0x58, 6, 0x1e};
