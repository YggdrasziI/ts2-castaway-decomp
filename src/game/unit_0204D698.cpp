/*
 * Unit 0x0204D698-0x0204EB78: the keyboard screen (Unk0204d698, vtable
 * 0x020B9BDC) on the screen element base Unk020b9b80 (game/unk_element.h). It
 * slides in and out with its own fade timer, lays out 39 keys (Unk0204beec of
 * unit_0204BEEC.cpp) over a board background chosen by the language and the
 * layout (letters, shifted letters, symbols, accented letters and their shifted
 * set, two kana sets), edits a UTF-8 text of up to 63 bytes (key 30 erases the
 * last character, 31 is space, 32 shifts, 33-35 switch layouts, 37 / 38 close
 * with a result) and shows it with a blinking cursor in a text field.
 *
 * Bounds: hypothesis. The start is the constructor, after the base's kept
 * functions that end unit_0204BEEC.cpp; 0x0204EB78 starts unit_0204EB78.cpp.
 * `.rodata` holds the eleven character tables of the layouts, `.data` the
 * const text field rectangle (built by the static initializer), this class's
 * vtable, the format strings and the board paths; `.bss` the cursor blink
 * counter. Real file name unknown.
 *
 * The base's slots 7 to 14 and 16 are not named yet: the vtable does not match
 * and the file cannot be complete.
 */

#include "game/unk_archive.h"
#include "game/unk_canvas.h"
#include "game/unk_element.h"
#include "game/unk_resource.h"

typedef signed char s8;

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
extern const short data_020af1e8[];

extern "C" {
Unk020d6240 *func_020a18e4();
int func_0209f0a4(Unk020d60c8 *settings);
void OS_WaitVBlankIntr();
u32 func_0209a418(const u8 *str, u32 ch);
u32 func_0209a550(const u8 *str);
u32 func_0209a5d8(const u8 *str, int *length);
}

static inline Unk02093648 *func_archive() {
    return func_020a18e4()->archive;
}

static inline Unk02092830Font *func_font() {
    Unk020d6240 *system = func_020a18e4();
    return func_0209f0a4(&data_020d60c8) == 7 ? system->font1c : system->font18;
}

/* One background layer (unit_0208D304.cpp): only the fields used here. */
class Unk0208d304 {
public:
    void func_0208d4b0(int priority);
    void func_0208d7a0(bool visible);

    int x;
    int y;
    u16 bgcnt;
    u16 bits;
    Unk02095140 *file;
};

/* The background manager of one screen (unit_0208D304.cpp). */
class Unk0208db14 {
public:
    static Unk0208db14 *func_0208dbe8();
    static Unk0208db14 *func_0208dbf8();
    static Unk0208db14 *func_0208dc08(int main);
    Unk0208d304 *func_0208dc44(Unk02095140 *file, int flag, int charBase, int index);
    void func_0208df4c(Unk0208d304 *layer);
    void func_0208e058(Unk02095140 *file, int index, int mask);
    void func_0208e4ec();
};

/* The text field of unit_02090CCC.cpp. */
class Unk02090ccc : public Unk02092704 {
public:
    Unk02090ccc();
    ~Unk02090ccc();
    void func_02090d80(int screen);
    void func_02090d9c(Unk02092830Font *font, const char *fmt, ...);
    void func_02091654();

    u32 chars[0x80];
    u16 tiles[0x80];
    u32 infos[0x80];
    u16 lineWidths[0x80];
    u16 length;
    u16 lineCount;
    u16 allocated;
    u16 maxLength;
    u16 screen;
    u16 priority;
    u16 unk628;
    s16 spacing;
    int unk62c;
    Unk02092640 it;
};

/* The key class of unit_0204BEEC.cpp: only what is used here. */
class Unk0204beec : public Unk020b9b80 {
public:
    Unk0204beec();
    ~Unk0204beec();
    void func_0204c0f8(bool main);
    void func_0204c1c4(int w, int h);

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

/* The slide timer: the same states as the base's show / hide timer. */
struct Unk0204d698Fade {
    Unk0204d698Fade() {
        timer = 0;
        duration = 0x3c;
        state = 5;
    }

    inline void func_step() {
        switch (state) {
        case 0:
            timer++;
            if (timer >= duration) {
                timer = duration;
                state = 1;
            }
            break;
        case 3:
            timer--;
            if (timer <= 0) {
                timer = 0;
                state = 4;
            }
            break;
        case 4:
            state = 5;
            break;
        case 1:
            state = 2;
            break;
        }
    }

    inline void func_reset(short duration) {
        timer = 0;
        state = 5;
        this->duration = duration;
        if (timer > this->duration) {
            timer = this->duration;
        }
    }

    inline bool func_hidden() const {
        return state == 5 || state == 4;
    }

    inline bool func_shown() const {
        return state == 2 || state == 1;
    }

    short timer;
    short duration;
    int state;
};

/* The characters of the 29 letter keys per layout, as UTF-8 bytes. */
static const u32 data_020aea74[11][29] = {
    {
        0xa0c3, 0xa1c3, 0xa2c3, 0xa4c3, 0xa3c3, 0xa6c3, 0xa8c3, 0xa9c3, 0xaac3, 0xabc3,
        0xacc3, 0xadc3, 0xaec3, 0xafc3, 0xb2c3, 0xb3c3, 0xb4c3, 0xb6c3, 0xb5c3, 0,
        0x9cc2, 0xb9c3, 0xbac3, 0xbbc3, 0xbcc3, 0xa7c3, 0xb1c3, 0x9fc3, 0,
    },
    {
        'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', '-', 'Y', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.',
    },
    {
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '{', '}', '[', ']', '<',
        '>', ',', '.', '?', ':', ';', '(', ')', '@', '!', '-', '+', '=', '*',
    },
    {
        'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '-', 'W', 'X', 'C', 'V',
        'B', 'N', ',', '.', 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
    },
    {
        'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '-', 'w', 'x', 'c', 'v',
        'b', 'n', ',', '.', 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
    },
    {
        0x80c3, 0x81c3, 0x82c3, 0x84c3, 0x83c3, 0x86c3, 0x88c3, 0x89c3, 0x8ac3, 0x8bc3,
        0x8cc3, 0x8dc3, 0x8ec3, 0x8fc3, 0x92c3, 0x93c3, 0x94c3, 0x96c3, 0x95c3, 0,
        0x8cc2, 0x99c3, 0x9ac3, 0x9bc3, 0x9cc3, 0x87c3, 0x91c3, 0x9fc3, 0,
    },
    {
        'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', '-', 'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',
    },
    {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', '-', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.',
    },
    {
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', '-', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',
    },
    {
        0x9b83e3, 0x9e83e3, 0x9f83e3, 0xa083e3, 0xa183e3, 0xa283e3, 0xa483e3, 0xa683e3,
        0xa883e3, 0xa983e3, 0xaa83e3, 0xab83e3, 0xac83e3, 0xad83e3, 0xaf83e3, 0xb283e3,
        0xb383e3, 0x9b82e3, 0x9c82e3, 0xa182e3, 0xa382e3, 0xa582e3, 0xa782e3, 0xa982e3,
        0xa383e3, 0xa583e3, 0xa783e3, 0x8383e3, '-',
    },
    {
        0xa282e3, 0xa482e3, 0xa682e3, 0xa882e3, 0xaa82e3, 0xab82e3, 0xad82e3, 0xaf82e3,
        0xb182e3, 0xb382e3, 0xb582e3, 0xb782e3, 0xb982e3, 0xbb82e3, 0xbd82e3, 0xbf82e3,
        0x8183e3, 0x8483e3, 0x8683e3, 0x8883e3, 0x8a83e3, 0x8b83e3, 0x8c83e3, 0x8d83e3,
        0x8e83e3, 0x8f83e3, 0x9283e3, 0x9583e3, 0xb881e3,
    },
};

/* The rectangle of the text field. */
static const Unk02098bc8 data_020b9bc4(0x18000, 0x88000, 0xd0000, 0x28000);

/* The cursor blink counter. */
static u32 data_020bfc2c;

class Unk0204d698 : public Unk020b9b80 {
public:
    Unk0204d698();
    ~Unk0204d698();
    void func_0204d8a4();
    void func_0204dbb4();
    bool func_04(bool locked);
    void func_00();
    void func_0204e470(int layout);
    void func_0c(int priority);
    void func_08();
    void func_0204e9d8();
    void func_0204e9f4();
    void func_0204ea00(const char *text);
    const u32 *func_0204ea84();
    Unk02098bc8 *func_10();
    void func_14(int x, int y);

    Unk0204d698Fade fade;
    Unk020b9e88Touch touch;
    Unk0208d304 *layer;
    Unk0208d304 *layerTop;
    Unk0208f8b0 *object48;
    int layout;
    Unk0208f8b0 *cursor0;
    Unk0208f8b0 *cursor1;
    Unk0208f8b0 *cursor2;
    Unk02098bc8 rect;
    short unk6c;
    short unk6e;
    int priority;
    u32 flags;
    int result;
    Unk0204beec keys[39];
    Unk02090ccc field;
    const char *prompt;
    char text[0x40];
    int length;
    int maxLength;
    int lastKey;
    bool screen;
};

Unk0204d698::Unk0204d698()
    : layer(0), object48(0), layout(0), cursor0(0), cursor1(0), cursor2(0), unk6c(-1), unk6e(-1), flags(0), prompt(0), length(0), maxLength(0x3f),
      lastKey(-1), screen(false) {
    rect.x = 0;
    rect.y = 0;
    rect.w = 0x100000;
    rect.h = 0xc0000;
    for (int i = 0; i < 39; i++) {
        keys[i].func_0204c0f8(screen);
        keys[i].flags |= 4;
    }
    func_0204d8a4();
    fade.func_reset(0xf);
    for (u32 i = 0; i <= 0x3f; i++) {
        text[i] = 0;
    }
}

Unk0204d698::~Unk0204d698() {
    func_08();
}

/* 96.96 %: the registers of the loop counters, x and the key pointer differ. */
void Unk0204d698::func_0204d8a4() {
    int y;
    int x;
    int k = 0;
    int i;
    int wide = 0;
    if (func_0209f0a4(&data_020d60c8) == 1) {
        bool letters = layout == 1 || layout == 0;
        if (letters) {
            wide = 1;
        }
    }
    y = 0x18000;
    x = 0xa000;
    for (i = 0; i < 10; i++, k++) {
        keys[k].func_0204c1c4(0x13000, 0x13000);
        keys[k].func_14(x, y);
        x += 0x18000;
    }
    if (wide) {
        y += 0x30000;
    } else {
        y += 0x18000;
    }
    x = 0x16000;
    for (i = 0; i < 9; i++, k++) {
        keys[k].func_0204c1c4(0x13000, 0x13000);
        keys[k].func_14(x, y);
        x += 0x18000;
    }
    if (wide) {
        y -= 0x18000;
    } else {
        y += 0x18000;
    }
    x = 0xa000;
    for (i = 0; i < 10; i++, k++) {
        keys[k].func_0204c1c4(0x13000, 0x13000);
        keys[k].func_14(x, y);
        x += 0x18000;
    }
    if (wide) {
        y += 0x18000;
    }
    keys[29].func_0204c1c4(0x23000, 0x13000);
    keys[29].func_14(0x1a000, y + 0x18000);
    keys[29].flags |= 0x10;
    keys[30].func_0204c1c4(0x23000, 0x13000);
    keys[30].func_14(0x42000, y + 0x18000);
    keys[31].func_0204c1c4(0x5b000, 0x13000);
    keys[31].func_14(0x6a000, y + 0x18000);
    keys[32].func_0204c1c4(0x23000, 0x13000);
    keys[32].func_14(0xca000, y + 0x18000);
    x = 0x5d000;
    for (i = 33; i <= 36; i++) {
        keys[i].func_0204c1c4(0x23000, 0x13000);
        keys[i].func_14(x, y + 0x30000);
        x += 0x28000;
    }
    keys[36].flags |= 0x10;
    keys[37].func_0204c1c4(0x3b000, 0x13000);
    keys[37].func_14(0x72000, 0x98000);
    keys[38].func_0204c1c4(0x3b000, 0x13000);
    keys[38].func_14(0xb2000, 0x98000);
}

void Unk0204d698::func_0204dbb4() {
    int t = func_fxdiv(fade.timer << 12, fade.duration << 12);
    int angle = func_fxmul(0x1000 - t, 0x8000);
    int c = data_020af1e8[((u16)angle >> 4) * 2 + 1];
    int y = func_fxmul((0x1000 - c) >> 1, 0xc0000);
    if (layerTop != 0) {
        layerTop->y = y;
    }
    int off = 0;
    if (layer != 0) {
        off = -(y + layer->y);
        layer->y = -y;
    }
    if (object48 != 0) {
        object48->unk4 += off;
    }
    field.func_0209276c(data_020b9bc4.x, y + data_020b9bc4.y);
}

bool Unk0204d698::func_04(bool locked) {
    int i;
    if (!locked && fade.func_shown()) {
        for (i = 0; i < 39; i++) {
            locked = keys[i].func_04(locked);
        }
        return true;
    }
    for (int j = 0; j < 39; j++) {
        keys[j].func_04(true);
    }
    if (!fade.func_hidden()) {
        locked = true;
    }
    return locked;
}

/* 99.06 %: two register swaps (the result and the touch argument). The blink
 * counter is unsigned (movhi / bls in the original). */
void Unk0204d698::func_00() {
    if (!(flags & 2)) {
        return;
    }
    fade.func_step();
    cursor0->func_0208faac(0);
    cursor1->func_0208faac(0);
    cursor2->func_0208faac(0);
    for (int i = 0; i < 39; i++) {
        if (keys[i].touch.flags & 4) {
            lastKey = i;
        }
        if (keys[i].touch.flags & 8) {
            u32 ch = 0;
            u32 n = 1;
            if (i >= 0 && i <= 0x1c) {
                ch = func_0204ea84()[i];
                if (ch & 0xff00) {
                    n = 2;
                }
                if (ch & 0xff0000) {
                    n = 3;
                }
                if (ch & 0xff000000) {
                    n = 4;
                }
            } else if (i == 0x1f) {
                ch = ' ';
            }
            if (ch != 0) {
                if ((int)func_0209a418((const u8 *)text, 0) < maxLength) {
                    func_0209a550((const u8 *)&ch);
                    const u8 *bytes = (const u8 *)&ch;
                    for (u32 j = 0; j < n; j++) {
                        text[length++] = *bytes++;
                    }
                    flags |= 4;
                }
                if (layout == 1) {
                    func_0204e470(0);
                }
                if (layout == 4) {
                    func_0204e470(3);
                }
            }
            if (i == 0x20) {
                switch (layout) {
                case 1:
                    func_0204e470(0);
                    break;
                case 0:
                    func_0204e470(1);
                    break;
                case 4:
                    func_0204e470(3);
                    break;
                case 3:
                    func_0204e470(4);
                    break;
                case 6:
                    func_0204e470(5);
                    break;
                case 5:
                    func_0204e470(6);
                    break;
                }
            } else if (i == 0x1e) {
                if (length > 0) {
                    int count = func_0209a418((const u8 *)text, 0);
                    int pos = 0;
                    if (count > 0) {
                        int size;
                        for (int c = 0; c < count - 1; c++) {
                            func_0209a5d8((const u8 *)text + pos, &size);
                            pos += size;
                        }
                        func_0209a5d8((const u8 *)text + pos, &size);
                        length -= size;
                        for (int b = pos; b < pos + size; b++) {
                            text[b] = 0;
                        }
                    }
                    flags |= 4;
                }
            } else if (i == 0x25 || i == 0x26) {
                result = i == 0x26 ? 1 : 2;
                func_0204e9f4();
            } else if (i == 0x21) {
                if (layout != 0 && layout != 1) {
                    func_0204e470(0);
                }
            } else if (i == 0x22) {
                if (layout != 2) {
                    func_0204e470(2);
                }
            } else if (i == 0x23) {
                if (layout != 3) {
                    func_0204e470(3);
                }
            }
        }
        if (keys[i].touch.flags & 1) {
            Unk020b9b80 *key = &keys[i];
            cursor0->unk0 = key->func_10()->x;
            cursor0->unk4 = key->func_10()->y;
            cursor1->unk0 = key->func_10()->x + 0x20000;
            cursor1->unk4 = key->func_10()->y;
            cursor2->unk0 = key->func_10()->x + 0x40000;
            cursor2->unk4 = key->func_10()->y;
            if (i >= 0x21 && i <= 0x24) {
                cursor0->func_0208faac(2);
                cursor1->func_0208faac(3);
            } else if (i == 0x1d || i == 0x1e || i == 0x20) {
                cursor0->func_0208faac(2);
                cursor1->func_0208faac(3);
            } else if (i == 0x1f) {
                cursor0->func_0208faac(4);
                cursor1->func_0208faac(6);
                cursor2->func_0208faac(5);
            } else if (i == 0x25 || i == 0x26) {
                cursor0->func_0208faac(4);
                cursor1->func_0208faac(5);
            } else {
                cursor0->func_0208faac(1);
            }
        }
    }
    if (++data_020bfc2c > 10) {
        data_020bfc2c = 0;
    }
    if (prompt != 0) {
        if (data_020bfc2c > 5) {
            field.func_02090d9c(func_font(), "%s%s\x07", prompt, text);
        } else {
            field.func_02090d9c(func_font(), "%s%s\x04", prompt, text);
        }
    } else {
        if (data_020bfc2c > 5) {
            field.func_02090d9c(func_font(), "%s\x07", text);
        } else {
            field.func_02090d9c(func_font(), "%s\x04", text);
        }
    }
    flags &= ~4;
    func_0204dbb4();
}

/* 99.46 %: the archive and layer registers are swapped. */
void Unk0204d698::func_0204e470(int layout) {
    if (!(flags | 2)) {
        return;
    }
    this->layout = layout;
    Unk02093648 *archive = func_archive();
    Unk0208d304 *layer = this->layer;
    if (layer != 0) {
        Unk02095140 *old = layer->file;
        Unk0208db14::func_0208dc08(screen)->func_0208df4c(layer);
        archive->func_02093c58(archive->func_02093f5c(old));
    }
    int id;
    if (func_0209f0a4(&data_020d60c8) == 3) {
        id = archive->func_02093e30((const u32 *)"build/data/screens/keyboard/german_boards.nitro_map");
    } else if (func_0209f0a4(&data_020d60c8) == 1) {
        id = archive->func_02093e30((const u32 *)"build/data/screens/keyboard/french_boards.nitro_map");
    } else {
        id = archive->func_02093e30((const u32 *)"build/data/screens/keyboard/boards.nitro_map");
    }
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(id);
    if (file != 0) {
        OS_WaitVBlankIntr();
        this->layer = Unk0208db14::func_0208dc08(screen)->func_0208dc44(file, 0, -1, this->layout);
        Unk0208db14::func_0208dc08(screen)->func_0208e058(file, 0, 0x1000);
        if (this->layer != 0) {
            this->layer->func_0208d4b0(priority);
            this->layer->func_0208d7a0(true);
        }
        Unk0208db14::func_0208dbe8()->func_0208e4ec();
        Unk0208db14::func_0208dbf8()->func_0208e4ec();
    }
    func_0204d8a4();
    for (int i = 0; i <= 0x1c; i++) {
        if (func_0204ea84()[i] == 0) {
            keys[i].flags |= 0x10;
        } else {
            keys[i].flags &= ~0x10;
        }
    }
}

void Unk0204d698::func_0c(int priority) {
    if (flags & 2) {
        return;
    }
    this->priority = priority;
    Unk02093648 *archive = func_archive();
    Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(
        archive->func_02093e30((const u32 *)"build/data/screens/keyboard/boards_top.nitro_map"));
    if (file != 0) {
        layerTop = Unk0208db14::func_0208dc08(screen == 0)->func_0208dc44(file, 0, -1, 0);
        Unk0208db14::func_0208dc08(screen == 0)->func_0208e058(file, 0, 0x800);
        layerTop->func_0208d4b0(0);
        layerTop->func_0208d7a0(true);
    }
    func_0204e470(0);
    file = (Unk02095140 *)archive->func_02093a9c(
        archive->func_02093e30((const u32 *)"build/data/screens/keyboard/keyoverlay.nitro_map"));
    if (file != 0) {
        cursor0 = Unk020916a4::func_02091840(screen)->func_020919e4((int)file, 0);
        cursor1 = Unk020916a4::func_02091840(screen)->func_020919e4((int)file, 0);
        cursor2 = Unk020916a4::func_02091840(screen)->func_020919e4((int)file, 0);
        cursor0->func_0208fb98(0xf);
        cursor1->func_0208fb98(0xf);
        cursor2->func_0208fb98(0xf);
        Unk020916a4::func_02091840(screen)->func_0209201c(file, 0, 0xc0, 0xf0, 7);
    }
    field.func_02090d80(screen == 0);
    field.func_020927c0(&data_020b9bc4);
    field.func_02092808(2, 8);
    field.func_02090d9c(func_font(), "test");
    flags |= 2;
    layer->y = -0xc0000;
    func_0204dbb4();
}

void Unk0204d698::func_08() {
    Unk02095140 *old_;
    Unk02095140 *old;
    Unk02093648 *archive;
    Unk0208d304 *layer;
    Unk02093648 *archive_;
    Unk0208f8b0 *object;
    if (!(2 & flags)) {
        /* Found by tools/permute.py: the locals declared first, an unused local here and the
         * test written 2 & flags give the original registers. */
        Unk02095140 *unused;
        return;
    }
    archive = func_archive();
    archive_ = archive;
    layer = this->layer;
    if (layer != 0) {
        old = layer->file;
        Unk0208db14::func_0208dc08(screen)->func_0208df4c(layer);
        archive->func_02093c58(archive->func_02093f5c(old));
    }
    this->layer = 0;
    layer = layerTop;
    if (layer != 0) {
        Unk02095140 *old = layer->file;
        Unk0208db14::func_0208dc08(screen == 0)->func_0208df4c(layer);
        archive->func_02093c58(archive->func_02093f5c(old));
    }
    layerTop = 0;
    object = object48;
    if (object != 0) {
        old_ = object->unk1c;
        Unk020916a4::func_02091830()->func_02091c68(object);
        archive_->func_02093c58(archive_->func_02093f5c(old_));
    }
    object48 = 0;
    object = cursor0;
    if (object != 0) {
        Unk020916a4::func_02091840(screen)->func_02091c68(object);
    }
    cursor0 = 0;
    object = cursor1;
    if (object != 0) {
        Unk020916a4::func_02091840(screen)->func_02091c68(object);
    }
    cursor1 = 0;
    object = cursor2;
    if (object != 0) {
        Unk020916a4::func_02091840(screen)->func_02091c68(object);
    }
    cursor2 = 0;
    archive->func_02093c58(archive->func_02093e30((const u32 *)"build/data/screens/keyboard/keyoverlay.nitro_map"));
    field.func_02091654();
    flags &= ~2;
}

void Unk0204d698::func_0204e9d8() {
    lastKey = -1;
    result = 0;
    fade.state = 0;
}

void Unk0204d698::func_0204e9f4() {
    fade.state = 3;
}

void Unk0204d698::func_0204ea00(const char *text) {
    length = 0;
    int i;
    for (i = 0; i <= 0x3f; i++) {
        this->text[i] = 0;
    }
    for (i = 0; i < 0x3f; i++) {
        u8 c = text[i];
        if (c == 0) {
            break;
        }
        this->text[i] = c;
        length++;
    }
    flags |= 4;
}

const u32 *Unk0204d698::func_0204ea84() {
    switch (layout) {
    case 1:
        if (func_0209f0a4(&data_020d60c8) == 3) {
            return data_020aea74[1];
        }
        return func_0209f0a4(&data_020d60c8) == 1 ? data_020aea74[3] : data_020aea74[7];
    case 0:
        if (func_0209f0a4(&data_020d60c8) == 3) {
            return data_020aea74[6];
        }
        return func_0209f0a4(&data_020d60c8) == 1 ? data_020aea74[4] : data_020aea74[8];
    case 2:
        return data_020aea74[2];
    case 4:
        return data_020aea74[5];
    case 3:
        return data_020aea74[0];
    case 6:
        return data_020aea74[9];
    case 5:
        return data_020aea74[10];
    }
    return data_020aea74[8];
}

Unk02098bc8 *Unk0204d698::func_10() {
    return &rect;
}

void Unk0204d698::func_14(int x, int y) {}
