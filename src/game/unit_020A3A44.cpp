/*
 * Unit 0x020A3A44-0x020A3E40: the sound events of an animation. A bank, read from a data tree
 * file, holds the sound hashes and the (frame, sound) events; a player plays them while its
 * animation advances. Bounds: hypothesis (between the sound manager and the microphone; no
 * data). The two data tree keys are not known strings. All names are placeholders. Real file
 * name unknown.
 */
#include "game/unk_anim.h"
#include "game/unk_datatree.h"

class Unk020a3a44Event {
public:
    Unk020a3a44Event() : unk4(-1) {}

    u16 frame;
    u16 sound;
    int unk4;
};

class Unk020a3a44 {
public:
    int *sounds;
    int soundCount;
    Unk020a3a44Event *events;
    int eventCount;
    int refs;
};

class Unk020a3d2c {
public:
    Unk020897c0 *anim;
    Unk020a3a44 *bank;
    int index;
};

extern "C" {
void *func_020a2994();
void *func_020a3858(void *p, int sound, bool loop, bool streamed, int delay);
void func_020a3ad0(Unk020a3a44 *p, Unk02096348 *file);
void func_020a3a90(Unk020a3a44 *p);
void func_020a3aa0(Unk020a3a44 *p);
int func_020a3ab0(Unk020a3a44 *p, int index);
int func_020a3abc(Unk020a3a44 *p);
Unk020a3a44Event *func_020a3ac4(Unk020a3a44 *p, int index);
void func_020a3d68(Unk020a3d2c *p);
void func_020a3dfc(Unk020a3d2c *p, Unk020a3a44Event *e);
}

extern "C" Unk020a3a44 *func_020a3a44(Unk020a3a44 *p, Unk02096348 *file) {
    p->sounds = 0;
    p->soundCount = 0;
    p->events = 0;
    p->eventCount = 0;
    p->refs = 0;
    func_020a3ad0(p, file);
    return p;
}

extern "C" Unk020a3a44 *func_020a3a70(Unk020a3a44 *p) {
    delete[] p->sounds;
    delete[] p->events;
    return p;
}

extern "C" void func_020a3a90(Unk020a3a44 *p) {
    p->refs++;
}

extern "C" void func_020a3aa0(Unk020a3a44 *p) {
    p->refs--;
}

extern "C" int func_020a3ab0(Unk020a3a44 *p, int index) {
    return p->sounds[index];
}

extern "C" int func_020a3abc(Unk020a3a44 *p) {
    return p->eventCount;
}

extern "C" Unk020a3a44Event *func_020a3ac4(Unk020a3a44 *p, int index) {
    return &p->events[index];
}

/*
 * 93.04 %: stack slots (the event item is at 0x50, before the temporaries of the sound
 * case, in the original) and the registers that follow from them.
 */
extern "C" void func_020a3ad0(Unk020a3a44 *p, Unk02096348 *file) {
    Unk0209674c root = file->func_02096980();
    if (!root.func_02096814(0xb93f2a30)) {
        return;
    }
    for (u32 i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c node = root.func_02096774(i);
        switch (node.func_02096800()) {
        case 0x0ae75527:
            p->soundCount = file->func_02096574(node.func_02096774(0).func_0209688c());
            if (p->soundCount > 0) {
                p->sounds = new int[p->soundCount];
                for (int j = 1; j < node.func_020967ec(); j++) {
                    Unk0209674c item = node.func_02096774(j);
                    p->sounds[j - 1] = file->func_02096590(item.func_02096774(0).func_0209688c());
                }
            }
            break;
        case 0x089d4d6d:
            p->eventCount = file->func_02096574(node.func_02096774(0).func_0209688c());
            p->events = new Unk020a3a44Event[p->eventCount];
            for (int j = 1; j < node.func_020967ec(); j++) {
                Unk020a3a44Event *events = p->events;
                int k = j - 1;
                Unk020a3a44Event *e = &events[k];
                Unk0209674c item = node.func_02096774(j);
                events[k].frame = file->func_02096574(item.func_02096774(0).func_0209688c());
                e->sound = file->func_02096574(item.func_02096774(1).func_0209688c());
            }
            break;
        }
    }
}

extern "C" Unk020a3d2c *func_020a3d2c(Unk020a3d2c *p, Unk020897c0 *anim, Unk020a3a44 *bank) {
    p->anim = anim;
    p->bank = bank;
    p->index = 0;
    func_020a3a90(p->bank);
    return p;
}

extern "C" Unk020a3d2c *func_020a3d50(Unk020a3d2c *p) {
    func_020a3aa0(p->bank);
    return p;
}

extern "C" void func_020a3d68(Unk020a3d2c *p) {
    p->index = 0;
}

extern "C" void func_020a3d74(Unk020a3d2c *p) {
    if (func_020a3abc(p->bank) < 1) {
        return;
    }
    int frame = p->anim->func_02089998() >> 12;
    if (p->index >= func_020a3abc(p->bank)) {
        if (!p->anim->func_01ff8a8c()) {
            return;
        }
        if (frame != 0) {
            return;
        }
        func_020a3d68(p);
    }
    Unk020a3a44Event *e = func_020a3ac4(p->bank, p->index);
    if (frame < e->frame) {
        return;
    }
    func_020a3dfc(p, e);
    p->index++;
}

extern "C" void func_020a3dfc(Unk020a3d2c *p, Unk020a3a44Event *e) {
    void *manager = func_020a2994();
    func_020a3858(manager, func_020a3ab0(p->bank, e->sound), false, true, 0);
}
