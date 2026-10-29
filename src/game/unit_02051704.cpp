/*
 * Unit 0x02051704-0x02051DA0: a panel widget (Unk02051704, vtable 0x020BA054)
 * on the widget base Unk020b9e88 (game/unk_widget.h): a rectangle, an array of
 * sprites and an array of child widgets, both allocated with a fixed capacity
 * and filled in order. Moving the panel moves its sprites and children by the
 * same offset; showing it shows them; its update runs the base update, then
 * the children's.
 *
 * Bounds: hypothesis. The previous widget (a button: fields 0x64-0x80, vtable
 * 0x020B9F9C) ends with 0x020514F0 at the constructor 0x02051704 of this class;
 * 0x02051DA0 starts unit_02051DA0.cpp. `.data` is the vtable of this class,
 * then the unused copy of the base vtable. Real file name unknown.
 *
 * The rectangle accessor func_10 is inline: the vtable points to its kept copy
 * 0x0202A52C (`add r0, r0, #0x34`) in a far file. The base's slots 7 to 20 are
 * not named yet (see game/unk_widget.h): the vtables do not match and the file
 * cannot be complete.
 */

#include "game/unk_widget.h"

typedef unsigned int u32;

class Unk02051704 : public Unk020b9e88 {
public:
    Unk02051704();
    ~Unk02051704();
    void func_02051804(u32 count);
    void func_02051858(Unk020a7c90 *sprite);
    void func_02051880();
    void func_020518a8(u32 count);
    void func_020518fc(Unk020b9e88 *child);
    void func_02051924();
    void func_14(int x, int y);
    void func_18(bool show);
    Unk020a7c90 *func_02051ad0(int index);
    void func_02051adc(Unk020b9e88 *child, int index);
    void func_02051ae8(Unk020a7c90 *sprite, int index);
    void func_08();

    Unk02098bc8 *func_10() {
        return &rect;
    }

    Unk02098bc8 rect;
    u32 spriteCap;
    u32 spriteCount;
    Unk020a7c90 **sprites;
    u32 childCap;
    u32 childCount;
    Unk020b9e88 **children;
};

Unk02051704::Unk02051704()
    : Unk020b9e88(true), rect(0, 0, 0, 0), spriteCap(0), spriteCount(0), sprites(0), childCap(0), childCount(0),
      children(0) {}

Unk02051704::~Unk02051704() {
    func_02051880();
    func_02051924();
}

void Unk02051704::func_02051804(u32 count) {
    if (sprites != 0) {
        return;
    }
    spriteCap = count;
    sprites = new Unk020a7c90 *[count];
    for (u32 i = 0; i < spriteCap; i++) {
        sprites[i] = 0;
    }
}

void Unk02051704::func_02051858(Unk020a7c90 *sprite) {
    if (spriteCount < spriteCap) {
        sprites[spriteCount] = sprite;
        spriteCount++;
    }
}

void Unk02051704::func_02051880() {
    if (sprites != 0) {
        delete[] sprites;
    }
    sprites = 0;
    spriteCount = 0;
}

void Unk02051704::func_020518a8(u32 count) {
    if (children != 0) {
        return;
    }
    childCap = count;
    children = new Unk020b9e88 *[count];
    for (u32 i = 0; i < childCap; i++) {
        children[i] = 0;
    }
}

void Unk02051704::func_020518fc(Unk020b9e88 *child) {
    if (childCount < childCap) {
        children[childCount] = child;
        childCount++;
    }
}

void Unk02051704::func_02051924() {
    if (children != 0) {
        delete[] children;
    }
    children = 0;
    childCount = 0;
}

void Unk02051704::func_14(int x, int y) {
    int dx = x - rect.x;
    int dy = y - rect.y;
    rect.x = x;
    rect.y = y;
    for (u32 i = 0; i < spriteCap; i++) {
        if (sprites[i] != 0) {
            func_020a7c90(sprites[i], dx + func_020a7ca4(sprites[i]));
            func_020a7cac(sprites[i], dy + func_020a7cc0(sprites[i]));
        }
    }
    for (u32 i = 0; i < childCap; i++) {
        Unk020b9e88 *child = children[i];
        if (child != 0) {
            children[i]->func_14(dx + child->func_10()->x, dy + child->func_10()->y);
        }
    }
}

void Unk02051704::func_18(bool show) {
    for (u32 i = 0; i < spriteCap; i++) {
        if (sprites[i] != 0) {
            func_020a7cf0(sprites[i], show);
        }
    }
    for (u32 i = 0; i < childCap; i++) {
        if (children[i] != 0) {
            children[i]->func_18(show);
        }
    }
}

Unk020a7c90 *Unk02051704::func_02051ad0(int index) {
    return sprites[index];
}

void Unk02051704::func_02051adc(Unk020b9e88 *child, int index) {
    children[index] = child;
}

void Unk02051704::func_02051ae8(Unk020a7c90 *sprite, int index) {
    sprites[index] = sprite;
}

void Unk02051704::func_08() {
    func_update();
    for (u32 i = 0; i < childCap; i++) {
        if (children[i] != 0) {
            children[i]->func_08();
        }
    }
}
