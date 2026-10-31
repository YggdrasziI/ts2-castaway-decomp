/*
 * Unit 0x0201C460-0x0201D6CC: the conversation balloon (Unk0201c460, 0x88 bytes,
 * vtable 0x020B8AC0), named by its file
 * build/data/screens/conversation/conversationparts.nitro_map. Attached to the
 * player's head (unit_02064984.cpp) or to a visible object (unit_0205D8D8.cpp,
 * unit_02060ADC.cpp), it walks the nodes of a script file: each one shows one or
 * two icons in a framed canvas with a tail, near the projected head of its
 * speaker, for a time.
 *
 * Bounds: hypothesis. The start is the constructor, after the first screens of
 * unit_0201B6D4.cpp; the end is the credits screen (unit_0201D70C.cpp). The root's
 * func_30 is defined here, at the end of the file. `.rodata` holds the frame and
 * random icon tables, `.data` the file name and the vtable with its header,
 * `.bss` the frame index. Real file name unknown.
 *
 * Not complete: func_0201d24c is below 100 % (comment above it).
 */

#include "game/unk_camera.h"
#include "game/unk_canvas.h"
#include "game/unk_datatree.h"
#include "game/unk_oam.h"
#include "game/unk_screen.h"
#include "game/unk_sim.h"

class Unk02064730;

/* The icon set of unit_02064330.cpp. */
class Unk02064330 {
public:
    Unk02064330();
    ~Unk02064330();

    u8 unk0[0x154];
};

class Unk020a3f8c {
public:
    Unk020a3f8c();
    ~Unk020a3f8c();

    int unk0;
    Unk02093648 *archive;
};

/* The main game state (func_0206bce0): only what is used here. */
struct Unk0206bcf0 {
    u8 unk0[0x21c];
    int unk21c;
    u8 unk220[0xc];
    u32 unk22c;
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
extern u8 data_020d62a4[];

extern "C" {
Unk020d6240 *func_020a18e4();
int func_020a0b8c(void *list, void *object);
void func_020a0b0c(void *list, void *object);
void func_020a3fb0(Unk020a3f8c *files, Unk02093648 *archive);
Unk02095140 *func_020a4008(Unk020a3f8c *files, const char *name);
Unk02096348 *func_020a4040(Unk020a3f8c *files, int index);
void func_020a20f0(void *random);
u32 func_020a1f84(void *random);
void *func_020a2994();
void *func_020a3858(void *sound, u32 hash, int a, int b, int c);
void func_020643b8(Unk02064330 *set, int screen);
void func_020643c4(Unk02064330 *set);
void func_020643ec(Unk02064330 *set);
void func_02064444(Unk02064330 *set);
Unk02064730 *func_020644cc(Unk02064330 *set, int key, int palette, int priority);
void func_0206471c(Unk02064730 *e, int x, int y);
Unk0206bcf0 *func_0206bce0();
}

class Unk0201c460 : public Unk020a07d4 {
public:
    Unk0201c460(u32 key);
    virtual ~Unk0201c460();
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

    void func_0201c74c();
    void func_0201c844();
    void func_0201c8cc();
    void func_0201c934();
    void func_0201cb1c();
    void func_0201cf6c(Unk020680d4Vec pos, Unk020680d4Vec offset);
    Unk02098ff0 func_0201d0c0(Unk020680d4Vec v);
    void func_0201d24c();

    inline bool func_finished() const {
        return (flags & 0x10) != 0;
    }

    int speaker;
    bool hidden;
    u32 count;
    int mode;
    Unk020a07d4Timer fade;
    int x;
    int y;
    u32 cols;
    Unk020680d4Vec anchor0;
    Unk020680d4Vec anchor1;
    u32 flags;
    Unk02090308 *canvas;
    Unk0208f8b0 *tails[2];
    Unk02096348 *file;
    u8 next;
    int timer;
    u32 age;
    u32 tail;
    Unk020a3f8c files;
    Unk02064730 *icons[4];
    Unk02064330 *set;
};

static const int data_020ae6a4[4] = {0, 1, 9, 0xa};
static const int data_020ae6b4[16] = {
    0x2702b, 0x3402b, 0x4d02b, 0x6502b, 0x7402b, 0x8302b, 0x9402b, 0xa402b,
    0xb302b, 0xc802b, 0xda02b, 0xe402b, 0xfb02b, 0x502c,  0x1402c, 0xd4015,
};
static int data_020be3ac;

Unk0201c460::Unk0201c460(u32 key)
    : speaker(0), hidden(true), count(0), mode(0), cols(6), anchor0(0, 0, 0), anchor1(0, 0, 0), flags(0), canvas(0),
      file(0), next(0), timer(0), age(0), tail(0) {
    set = 0;
    func_020a3fb0(&files, func_020a18e4()->archive);
    func_020a20f0(data_020d62a4);
    for (u32 i = 0; i < 4; i++) {
        icons[i] = 0;
    }
    for (u32 i = 0; i < 2; i++) {
        tails[i] = 0;
    }
    file = func_020a4040(&files, files.archive->func_02093ef4(key, 7));
    set = new Unk02064330;
    func_020643ec(set);
    func_020643b8(set, 1);
}

Unk0201c460::~Unk0201c460() {
    func_0201c844();
    if (set != 0) {
        func_02064444(set);
        delete set;
        set = 0;
    }
}

void Unk0201c460::func_08() {
    if (!func_020a0b8c(data_020d6240.unk8, this)) {
        func_020a0b0c(data_020d6240.unk8, this);
    }
}

bool Unk0201c460::func_0c(short a) {
    if (fade.func_shown()) {
        return true;
    }
    if (fade.func_opening()) {
        return false;
    }
    func_0201c74c();
    fade.func_duration(0);
    fade.state = 0;
    return false;
}

bool Unk0201c460::func_10() {
    if (fade.func_hidden()) {
        return true;
    }
    if (fade.func_closing()) {
        return false;
    }
    fade.func_duration(0);
    fade.state = 3;
    return false;
}

void Unk0201c460::func_0201c74c() {
    func_0201c844();
    if (canvas == 0) {
        canvas = new Unk02090308;
        canvas->func_020905c4(1);
        canvas->func_020908ac(3);
    }
    Unk02095140 *parts = func_020a4008(&files, "build/data/screens/conversation/conversationparts.nitro_map");
    tails[0] = Unk020916a4::func_02091820()->func_020919e4((int)parts, 3);
    tails[1] = Unk020916a4::func_02091820()->func_020919e4((int)parts, 3);
    tails[0]->func_0208faac(7);
    tails[1]->func_0208faac(8);
    for (int i = 0; i < 2; i++) {
        tails[i]->func_0208fb98(2);
        tails[i]->unk0 = 0;
        tails[i]->unk4 = 0xc0000;
    }
    timer = 0;
    next = 0;
    flags = (flags | 1) & ~4;
}

void Unk0201c460::func_0201c844() {
    if (!(flags & 1)) {
        return;
    }
    func_0201c8cc();
    if (canvas != 0) {
        canvas->func_0209088c();
        delete canvas;
        canvas = 0;
    }
    for (int i = 0; i < 2; i++) {
        Unk020916a4::func_02091820()->func_02091c68(tails[i]);
        tails[i] = 0;
    }
    flags &= ~1;
}

void Unk0201c460::func_0201c8cc() {
    if (canvas != 0) {
        canvas->func_0209088c();
    }
    for (u32 i = 0; i < 4; i++) {
        icons[i] = 0;
    }
    for (u32 i = 0; i < 2; i++) {
        tails[i]->unk0 = 0x100000;
    }
    func_020643c4(set);
    hidden = true;
}

void Unk0201c460::func_0201c934() {
    if (canvas == 0) {
        return;
    }
    Unk02095140 *parts = func_020a4008(&files, "build/data/screens/conversation/conversationparts.nitro_map");
    canvas->func_0209088c();
    u32 w = cols >> 1;
    if (cols > w * 2) {
        w++;
    }
    canvas->func_0209066c(w, 3);
    canvas->func_02090878(x, y);
    canvas->func_020905d4(2);
    for (u32 i = 0; i != cols; i++) {
        if (i == 0) {
            canvas->func_020906e4(parts, 0, 0, 0);
        } else if (i == cols - 1) {
            canvas->func_020906e4(parts, i * 0x10, 0, 2);
        } else {
            canvas->func_020906e4(parts, i * 0x10, 0, 1);
        }
    }
    if (mode == 0) {
        switch (tail) {
        case 0:
            canvas->func_020906e4(parts, 0x10, 0, 4);
            break;
        case 1:
            canvas->func_020906e4(parts, (cols - 2) * 0x10, 0, 3);
            break;
        case 2:
            canvas->func_020906e4(parts, 0x10, 0x30, speaker == 0 ? 5 : 6);
            break;
        case 3:
            canvas->func_020906e4(parts, (cols - 2) * 0x10, 0x30, 6);
            break;
        }
    }
    if (mode == 1) {
        func_0201cb1c();
    }
    hidden = false;
}

void Unk0201c460::func_0201cb1c() {
    if (tail == 0 || tail == 2) {
        tails[0]->unk0 = x + 0xf000;
        tails[1]->unk0 = x + 0x14000;
    } else {
        tails[0]->unk0 = x + (((cols << 4) - 0x19) << 12);
        tails[1]->unk0 = x + (((cols << 4) - 0x1e) << 12);
    }
    if (tail <= 1) {
        tails[0]->unk4 = y - 0xa000;
        tails[1]->unk4 = y - 0x14000;
    } else {
        tails[0]->unk4 = y + 0x3c000;
        tails[1]->unk4 = y + 0x50000;
    }
    if (++age < 10) {
        tails[0]->unk4 = 0xc0000;
        tails[0]->unk0 = 0x100000;
    }
    if (age >= 0x14) {
        return;
    }
    for (u32 i = 0; i != count; i++) {
        func_0206471c(icons[i], 0x100000, 0xc0000);
    }
    canvas->func_02090878(0x100000, 0xc0000);
}

void Unk0201c460::func_38(bool active) {
    if (func_0206bce0()->unk21c != 0) {
        if ((flags & 1) && !hidden) {
            func_0201c8cc();
        }
        flags |= 4;
        return;
    }
    if (fade.func_hidden()) {
        return;
    }
    if (func_0206bce0()->unk22c & 1) {
        return;
    }
    if (file == 0) {
        return;
    }
    fade.func_step();
    if ((flags & 1) && file->func_02094f88() && !(flags & 4)) {
        if (timer == 0) {
            if (!hidden) {
                func_0201c8cc();
            }
            if (func_finished()) {
                flags |= 4;
            } else {
                func_0201d24c();
            }
        } else {
            timer--;
        }
        if (!hidden) {
            switch (speaker) {
            case 0:
                x = anchor0.v.x;
                y = anchor0.v.y;
                break;
            case 1:
                x = anchor1.v.x;
                y = anchor1.v.y;
                break;
            }
            if (mode != 1) {
                if (y < -0x8000 && y > -0x30000) {
                    y = -0x8000;
                }
                if (x < 0 && (x > (count == 1) ? -0x30000 : -0x60000)) {
                    x = 0;
                }
                if (y > 0x98000 && y < 0xc0000) {
                    y = 0x98000;
                }
                if (x > (count == 1 ? 0xd0000 : 0xa0000) && x < 0x100000) {
                    x = count == 1 ? 0xd0000 : 0xa0000;
                }
            }
            for (u32 i = 0; i != count; i++) {
                func_0206471c(icons[i], x + 0xa000 + i * 0x28000, y + 0xe000);
            }
            canvas->func_02090878(x, y);
            if (mode == 1) {
                func_0201cb1c();
            }
        }
    }
    if (fade.state == 4) {
        func_0201c844();
    }
}

void Unk0201c460::func_18() {
    flags |= 2;
}

void Unk0201c460::func_0201cf6c(Unk020680d4Vec pos, Unk020680d4Vec offset) {
    if (mode == 1) {
        anchor0 = (const Unk020680d4Vec &)func_0201d0c0(pos);
        anchor0.v.x -= 0x16000;
        anchor0.v.y -= 0x60000;
        anchor1 = (const Unk020680d4Vec &)func_0201d0c0(offset);
        anchor1.v.x -= 0x1e000;
        anchor1.v.y -= 0x68000;
    } else {
        anchor0 = (const Unk020680d4Vec &)func_0201d0c0(pos);
        anchor0.v.x -= 0xa000;
        anchor0.v.y -= 0x48000;
        anchor1 = (const Unk020680d4Vec &)func_0201d0c0(offset);
        anchor1.v.x -= 0x1e000;
        anchor1.v.y -= 0x50000;
    }
}

Unk02098ff0 Unk0201c460::func_0201d0c0(Unk020680d4Vec v) {
    Unk02098094 clip;
    Unk02098094 view;
    Unk020899a4 *camera = (Unk020899a4 *)&data_020c7d38.unk54;
    Unk02097b6c rotation = Unk02097b6c::func_02097f78(camera->angles.v.z, camera->angles.v.x, camera->angles.v.y);
    Unk02097b6c inverse = rotation.func_02097cec();
    Unk02098094 rotate(inverse);
    Unk02098ff0 back(-camera->pos.x, -camera->pos.y, -camera->pos.z);
    Unk02098094 translate(back);
    view.func_0209873c(translate, rotate);
    clip.func_0209873c(view, camera->proj);
    Unk02098ff0 p = clip.func_020983ac(v.v);
    p.y = -p.y;
    p.x += 0x1000;
    p.y += 0x1000;
    p.z += 0x1000;
    p.x = func_fxmul(p.x, 0x800);
    p.y = func_fxmul(p.y, 0x800);
    p.z = func_fxmul(p.z, 0x800);
    p.x = func_fxmul(p.x, 0x100000);
    p.y = func_fxmul(p.y, 0xc0000);
    return p;
}

/*
 * 98.29 %: the two stores of the stack locals `found` and `side` come after the
 * following field copies; the original puts them before. Tried: statement orders,
 * chained assignments, declaration orders, int and u32 locals.
 */
void Unk0201c460::func_0201d24c() {
    Unk0209674c root = file->func_02096980();
    int found = 0;
    u32 side;
    count = 0;
    while (next < root.func_020967ec() && !found) {
        Unk0209674c node = root.func_02096774(next);
        if (!node.func_02096864()) {
            if (node.func_02096814(0x6c32238)) {
                speaker = 0;
                found = 1;
                x = anchor0.v.x;
                side = 2;
                y = anchor0.v.y;
            } else if (node.func_02096814(0x3a283a11)) {
                found = 1;
                speaker = 1;
                x = anchor1.v.x;
                side = 2;
                y = anchor1.v.y;
            } else if (node.func_02096814(0x2de73b4e)) {
                mode = 1;
            }
            if (found) {
                age = 0;
                timer = 0x5a;
                for (int i = 0; i < node.func_020967ec(); i++) {
                    Unk0209674c child = node.func_02096774(i);
                    if (child.func_02096864()) {
                        int index = child.func_0209688c();
                        bool valid = file->func_02096538(index, 1);
                        if (child.func_02096814(0x9d5bba8e) && valid) {
                            int key = file->func_02096574(index);
                            if (key == -1) {
                                key = data_020ae6b4[(func_020a1f84(data_020d62a4) & 7) + speaker * 8];
                            }
                            icons[count] = func_020644cc(set, key, data_020ae6a4[data_020be3ac], 2);
                            data_020be3ac++;
                            if (data_020be3ac >= 4) {
                                data_020be3ac = 0;
                            }
                            func_0206471c(icons[count], x + 0xa000, y + 0xe000);
                            count++;
                        }
                        if (child.func_02096814(0xa7ab6bbd)) {
                            if (valid) {
                                int key = file->func_02096574(index);
                                if (key == -1) {
                                    key = data_020ae6b4[(func_020a1f84(data_020d62a4) & 7) + speaker * 8];
                                }
                                icons[count] = func_020644cc(set, key, data_020ae6a4[data_020be3ac], 2);
                                data_020be3ac++;
                                if (data_020be3ac >= 4) {
                                    data_020be3ac = 0;
                                }
                                func_0206471c(icons[count], x + 0x32000, y + 0xe000);
                                count++;
                            }
                        } else if (child.func_02096814(0x8b23574f)) {
                            if (valid) {
                                int time = file->func_02096574(index);
                                if (time > 0) {
                                    timer = time;
                                }
                            }
                        } else if (child.func_02096814(0x2ea70208)) {
                            u32 hash = file->func_02096590(index);
                            func_020a3858(func_020a2994(), hash, 0, 1, 0);
                        }
                    }
                }
            }
            if (count != 0) {
                cols = 6;
                if (count == 1) {
                    cols = 3;
                }
                tail = side;
                func_0201c934();
            }
        }
        next++;
    }
    if (root.func_020967ec() == next) {
        flags |= 0x10;
    }
}

bool Unk0201c460::func_34() {
    return true;
}

bool Unk0201c460::func_3c(bool done) {
    return done;
}

bool Unk0201c460::func_28() {
    return fade.func_shown();
}

bool Unk0201c460::func_2c() {
    return fade.func_hidden();
}

bool Unk0201c460::func_14() {
    return (flags & 2) != 0;
}

void Unk0201c460::func_1c() {
    flags &= ~2;
}

bool Unk0201c460::func_20() {
    return (flags & 0x20) != 0;
}

void Unk0201c460::func_24() {
    flags |= 0x20;
}

/* Inline, or the root's vtable is emitted here. */
inline bool Unk020a07d4::func_30() {
    return func_28() && !func_14();
}
