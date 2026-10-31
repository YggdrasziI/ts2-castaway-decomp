/*
 * Unit 0x0200AD70-0x0200B04C: the base of the fish, `Unk0200ad70`, its set-up from a
 * fish record and the accessors of that record. Bounds: hypothesis (from the
 * constructor to the class Unk0200b04c, `.data` is the vtable). The set-up, the
 * accessor and the view are written as plain functions; methods are as likely
 * (hypothesis). Layouts come from the code; all names are placeholders.
 */
#include "game/unk_screen.h"
#include "game/unk_fishing.h"

extern "C" {
void func_0200df54(Unk0200dd90 *e);
void func_0200e084(void *view, void *def, u32 key);
void func_0200e0b8(void *view);
int func_0200e0d0(void *view, u32 key);
int func_0200e0fc(void *def);
int func_0200e120(void *def);
int func_020a5700(Unk02098e70 *a, void *b, Unk02098e70 *c, int d);
int func_020a5878(Unk02098e70 *a, void *b, Unk02098e70 *c, int d);

void func_0200ada4(Unk02010920 *e, int *def);
int func_0200af10(Unk02010920 *e);
void *func_0200af18(void *view, void *def, u32 key);
void *func_0200af2c(void *view);
int func_0200af40(void *def);
Unk02098e70 func_0200af60(void *def);
u32 func_0200afc0(void *def);
int func_0200afd4(void *def);
int func_0200afe8(void *def);
int func_0200affc(void *def);
int func_0200b010(void *def);
int func_0200b024(void *def);
int func_0200b038(void *def);
}

Unk0200ad70::Unk0200ad70(int count) : Unk0200dd90(count) {
}

Unk0200ad70::~Unk0200ad70() {
}

extern "C" void func_0200ada4(Unk02010920 *e, int *def) {
    e->key = *def;
    func_0200df54(e);
    e->move.unk14 = func_0200e0fc(def);
    e->move.speed = func_0200e120(def);
    func_set(e->move.step, Unk02098e70(0));
    func_set(e->move.dir, e->move.step);
    switch (func_0200af40(def)) {
    case 0x1add4528:
        e->hit = func_020a5700;
        break;
    case 0x71acfd6d:
        e->hit = func_020a5878;
        break;
    }
    func_set(e->scale, func_0200af60(def));
    e->scale.x = 0x1000000 / e->scale.x;
    e->scale.y = 0x1000000 / e->scale.y;
    e->unkc0 = func_0200afe8(def);
    switch (e->unkc0) {
    case (int)0x97de12bf:
        e->sizes[0] = func_0200b024(def);
        e->sizes[1] = func_0200b038(def);
        break;
    case (int)0xcbd6cda5:
        e->sizes[0] = func_0200affc(def);
        e->sizes[1] = func_0200b010(def);
        break;
    default:
        for (int i = 0; i < 2; i++) {
            e->sizes[i] = 0;
        }
        break;
    }
}

extern "C" int func_0200af10(Unk02010920 *e) {
    return e->sizes[0];
}

extern "C" void *func_0200af18(void *view, void *def, u32 key) {
    func_0200e084(view, def, key);
    return view;
}

extern "C" void *func_0200af2c(void *view) {
    func_0200e0b8(view);
    return view;
}

extern "C" int func_0200af40(void *def) {
    int v = func_0200e0d0(def, 0x962e39c9);
    if (v == 0) {
        v = 0x1add4528;
    }
    return v;
}

extern "C" Unk02098e70 func_0200af60(void *def) {
    int w = func_0200e0d0(def, 0xb0cad4ef) / 2;
    int h = func_0200e0d0(def, 0xb1dd53bd) / 2;
    if (w == 0) {
        w = 8;
    }
    if (h == 0) {
        h = 0x10;
    }
    return Unk02098e70(w << 12, h << 12);
}

extern "C" u32 func_0200afc0(void *def) {
    return func_0200e0d0(def, 0x7881c23b);
}

extern "C" int func_0200afd4(void *def) {
    return func_0200e0d0(def, 0x2b3e6dd7);
}

extern "C" int func_0200afe8(void *def) {
    return func_0200e0d0(def, 0x0e3a40b3);
}

extern "C" int func_0200affc(void *def) {
    return func_0200e0d0(def, 0xf77c8c69);
}

extern "C" int func_0200b010(void *def) {
    return func_0200e0d0(def, 0x8be9b6bb);
}

extern "C" int func_0200b024(void *def) {
    return func_0200e0d0(def, 0xc0880469);
}

extern "C" int func_0200b038(void *def) {
    return func_0200e0d0(def, 0x48749bf8);
}
