/*
 * Unit 0x0204EE14-0x0204F798: an image element (Unk0204ee14, vtable 0x020B9D94)
 * on the screen element base Unk020b9b80 (game/unk_element.h). It shows one
 * image file of the archive either as a background layer (mode 1) or as a grid
 * of up to six objects (mode 0), on the main or the sub screen, and moves a
 * fixed-capacity array of child elements with it. The file also holds a free
 * function drawing a text description into a canvas.
 *
 * Bounds: hypothesis. The start is the constructor, after the functions of the
 * keyboard screen (vtable 0x020B9BDC, whose file ends with the string "test");
 * 0x0204F798 starts unit_0204F798.cpp. `.data` is this class's vtable, then the
 * unused copy of the base vtable. Real file name unknown.
 *
 * The base's slots 7 to 14 and 16 are not named yet: the vtables do not match
 * and the file cannot be complete.
 */

#include "game/unk_archive.h"
#include "game/unk_canvas.h"
#include "game/unk_element.h"
#include "game/unk_resource.h"

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0[5];
    Unk02093648 *archive;
    Unk02092830Font *font18;
    Unk02092830Font *font1c;
};

/* The settings (data_020d60c8): only used through their accessor here. */
struct Unk020d60c8;

extern Unk020d60c8 data_020d60c8;

extern "C" {
Unk020d6240 *func_020a18e4();
int func_0209f0a4(Unk020d60c8 *settings);
}

/* A pixel value as 20.12 fixed point, rounded. */
#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

static inline Unk02093648 *func_archive() {
    return func_020a18e4()->archive;
}

/* One background layer (unit_0208D304.cpp): only the fields used here. */
class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
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
    void func_0208e058(Unk02095140 *file, int index, int mask);
};

class Unk0204ee14 : public Unk020b9b80 {
public:
    Unk0204ee14();
    ~Unk0204ee14();
    void func_00() {
        func_update();
    }
    bool func_04();
    void func_08();
    void func_0c(int objPriority);
    void func_0204f4a0(int mode, const u32 *name);
    void func_0204f4d8(int mode, int resource);
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

Unk0204ee14::Unk0204ee14()
    : flags(0), rect(0, 0, 0, 0), children(0), capacity(8), count(0), resource(-1), priority(-1), mask(-1),
      mode(1), columns(1), rows(0), layer(0) {
    for (int i = 0; i < 6; i++) {
        objects[i] = 0;
    }
}

Unk0204ee14::~Unk0204ee14() {
    func_08();
}

bool Unk0204ee14::func_04() {
    return 0;
}

void Unk0204ee14::func_08() {
    if (children != 0) {
        delete[] children;
    }
    children = 0;
    capacity = 8;
    count = 0;
    if (!(flags & 1)) {
        return;
    }
    bool sub = (flags & 2) != 0;
    Unk0208d304 *layer = this->layer;
    if (layer != 0) {
        Unk0208db14::func_0208dc08(sub)->func_0208df4c(layer);
    }
    this->layer = 0;
    for (int i = 0; i < 6; i++) {
        Unk0208f8b0 *object = objects[i];
        if (object != 0) {
            Unk020916a4::func_02091840(sub)->func_02091c68(object);
            objects[i] = 0;
        }
    }
    if (resource != -1) {
        func_archive()->func_02093c58(resource);
    }
    resource = -1;
    flags &= ~1;
}

/*
 * 99.48 %: registers of the file and the grid counters (original: file r5,
 * row r6, index r7, column r8). Tried: all declaration orders of the
 * counters, size and object locals, a combined early return, static_cast.
 */
void Unk0204ee14::func_0c(int objPriority) {
    if (flags & 1) {
        return;
    }
    if (resource == -1) {
        return;
    }
    Unk02095140 *file = (Unk02095140 *)func_archive()->func_02093a9c(resource);
    if (mode == 1) {
        layer = Unk0208db14::func_0208dc08((flags & 2) != 0)->func_0208dc44(file, (flags & 4) != 0, -1, 0);
        layer->func_0208d7a0(true);
        layer->func_0208d4b0(priority);
        layer->x = rect.x;
        layer->y = rect.y;
        int mask = this->mask;
        if (mask != -1) {
            Unk0208db14::func_0208dc08((flags & 2) != 0)->func_0208e058(file, 0, mask);
        }
    } else if (mode == 0) {
        int k = 0;
        int col;
        for (int row = 0; row < rows; row++) {
            for (col = 0; col < columns; col++) {
                objects[k] = Unk020916a4::func_02091840((flags & 2) != 0)->func_020919e4((int)file, priority);
                objects[k]->func_0208fb80(objPriority);
                objects[k]->unk0 = rect.x + FX32(col * (1 << (objects[0]->unk10_0 + 3)));
                objects[k]->unk4 = rect.y + FX32(row * (1 << (objects[0]->unk10_2 + 3)));
                k++;
            }
        }
    }
    flags |= 1;
}

void Unk0204ee14::func_0204f4a0(int mode, const u32 *name) {
    func_0204f4d8(mode, func_archive()->func_02093db0(name, 9));
}

void Unk0204ee14::func_0204f4d8(int mode, int resource) {
    this->resource = resource;
    this->mode = mode;
}

void Unk0204ee14::func_0204f4e4(int priority) {
    this->priority = priority;
    if (layer != 0) {
        layer->func_0208d4b0(priority);
    }
}

Unk02098bc8 *Unk0204ee14::func_10() {
    return &rect;
}

void Unk0204ee14::func_14(int x, int y) {
    int dx = x - rect.x;
    int dy = y - rect.y;
    rect.x = x;
    rect.y = y;
    if (layer != 0) {
        layer->x += dx;
        layer->y += dy;
    }
    for (int i = 0; i < 6; i++) {
        if (objects[i] != 0) {
            objects[i]->unk0 += dx;
            objects[i]->unk4 += dy;
        }
    }
    if (children == 0) {
        return;
    }
    for (int i = 0; i < capacity; i++) {
        Unk020b9b80 *child = children[i];
        if (child != 0) {
            int cx = child->func_10()->x;
            int cy = child->func_10()->y;
            child->func_14(dx + cx, dy + cy);
        }
    }
}

void Unk0204ee14::func_0204f60c(int capacity) {
    if (children == 0) {
        this->capacity = capacity;
    }
}

void Unk0204ee14::func_0204f61c(Unk020b9b80 *child) {
    if (children == 0) {
        children = new Unk020b9b80 *[capacity];
        for (int i = 0; i < capacity; i++) {
            children[i] = 0;
        }
    }
    if (count >= capacity) {
        return;
    }
    for (int i = 0; i < capacity; i++) {
        if (children[i] == 0) {
            children[i] = child;
            count++;
            return;
        }
    }
}

/* A text description: position, size, alignment, screen and the text. */
struct Unk0204f6c0Text {
    int x;
    int y;
    u32 w;
    u32 h;
    int hAlign;
    int vAlign;
    const char *text;
    u16 unk1c;
    u16 unk1e;
    u16 screen;
};

extern "C" bool func_0204f6c0(Unk02090308 *canvas, Unk0204f6c0Text *desc, int pages) {
    if (desc->text != 0) {
        canvas->func_0209088c();
        canvas->func_020905c4(desc->screen != 0);
        canvas->func_02090898(desc->unk1c);
        canvas->func_020905d4(desc->unk1e);
        canvas->func_020908e0(desc->hAlign, desc->vAlign);
        int w = desc->w >> 5;
        int h = desc->h >> 5;
        if (w <= 0) {
            w = 1;
        }
        if (h <= 0) {
            h = 1;
        }
        canvas->func_0209066c(w, h);
        canvas->func_02090878(desc->x << 12, desc->y << 12);
        Unk020d6240 *system = func_020a18e4();
        Unk02092830Font *font = func_0209f0a4(&data_020d60c8) == 7 ? system->font1c : system->font18;
        return canvas->func_02090b08(pages, font, desc->text);
    }
    return true;
}
