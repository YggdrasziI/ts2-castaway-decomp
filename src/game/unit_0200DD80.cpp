/*
 * Unit 0x0200DD80-0x0200E144: the scene element `Unk0200dd90` made of up to five
 * sprite parts, and the view of a database record. Bounds: hypothesis (the two first
 * functions are the part destructor and constructor of this class; the end is the
 * first state of the fire microgame). The functions are written as plain functions
 * where methods are as likely (hypothesis). All names are placeholders.
 */
#include "game/unk_screen.h"
#include "game/unk_fishing.h"

struct Unk0200e084 {
    void *def;
    u32 key;
};

extern "C" {
int func_0205d234(void *def, u32 key, u32 k);
int func_0205d2ac(void *def, u32 key);
Unk02098e70 func_020acab4(const Unk02098e70 *a, const Unk02098e70 *b, void *r);
void func_020acbc8(Unk02098e70 *v);
void func_020a69ac(Unk020a7c90 *s, int f);
void func_020a7d30(Unk020a7c90 *s, int x);

void func_0200de30(Unk0200dd90 *e);
void func_0200df10(Unk0200dd90 *e, bool a, int b);
void func_0200df54(Unk0200dd90 *e);
Unk0200dd90Part *func_0200dfc8(Unk0200dd90 *e, int i);
bool func_0200dfd8(Unk0200dd90 *e, const Unk02098e70 *v, int d);
void func_0200e010(Unk0200dd90 *e, const Unk02098e70 *v, void *r, int a);
Unk0200e084 *func_0200e084(Unk0200e084 *v, void *def, u32 key);
void func_0200e0b8(Unk0200e084 *v);
bool func_0200e0bc(Unk0200e084 *v);
int func_0200e0d0(Unk0200e084 *v, u32 key);
int func_0200e0fc(Unk0200e084 *v);
int func_0200e120(Unk0200e084 *v);
}

Unk0200dd90Part::~Unk0200dd90Part() {
}

Unk0200dd90Part::Unk0200dd90Part() : flags(0) {
}

Unk0200dd90::Unk0200dd90(int n) : count(n), move(0x1000, 0), pos(0) {
    func_0200df54(this);
}

Unk0200dd90::~Unk0200dd90() {
}

extern "C" void func_0200de30(Unk0200dd90 *e) {
    Unk020a7c90 **s = (Unk020a7c90 **)e->func_00();
    Unk0200dd90Part *p = e->parts;
    for (int i = 0; i < e->count; i++, p++) {
        Unk02098e70 v;
        func_set(v, p->pos);
        Unk020a7c90 *t = s[i];
        if (!(p->flags & 1)) {
            v.x += e->pos.x;
            v.y += e->pos.y;
        }
        if (p->unk10 != -1) {
            func_020a69ac(t, p->unk10);
        }
        if (p->unk14 != -1) {
            func_020a7d30(t, p->unk14);
        }
        func_020a7c90(t, v.x);
        func_020a7cac(t, v.y);
        func_020a7cf0(t, p->flag);
    }
}

Unk02098e70 *Unk0200dd90::func_0200df08() {
    return &pos;
}

extern "C" void func_0200df10(Unk0200dd90 *e, bool a, int b) {
    Unk0200dd90Part *p;
    int n = e->count;
    p = e->parts;
    for (; n > 0; n--, p++) {
        if (b || !(p->flags & 2)) {
            p->flag = a;
        }
    }
}

extern "C" void func_0200df54(Unk0200dd90 *e) {
    Unk0200dd90Part *p;
    int n = e->count;
    p = e->parts;
    for (; n > 0; n--, p++) {
        func_set(p->pos, Unk02098e70(0));
        p->flag = 0;
        p->flags = 0;
        p->unk10 = -1;
        p->unk14 = -1;
    }
}

extern "C" Unk0200dd90Part *func_0200dfc8(Unk0200dd90 *e, int i) {
    return &e->parts[i];
}

extern "C" bool func_0200dfd8(Unk0200dd90 *e, const Unk02098e70 *v, int d) {
    return (int)v->func_02098fcc(e->pos).func_02098e94() < d;
}

extern "C" void func_0200e010(Unk0200dd90 *e, const Unk02098e70 *v, void *r, int a) {
    func_set(e->move.step, func_020acab4(&e->pos, v, r));
    func_020acbc8(&e->move.dir);
    if (a == 1) {
        e->pos.x += e->move.dir.x;
        e->pos.y += e->move.dir.y;
    }
}

extern "C" Unk0200e084 *func_0200e084(Unk0200e084 *v, void *def, u32 key) {
    v->def = def;
    v->key = key;
    if (v->def != 0 && !func_0205d2ac(v->def, key)) {
        v->def = 0;
    }
    return v;
}

extern "C" void func_0200e0b8(Unk0200e084 *v) {
}

extern "C" bool func_0200e0bc(Unk0200e084 *v) {
    return v->def != 0;
}

extern "C" int func_0200e0d0(Unk0200e084 *v, u32 key) {
    if (!func_0200e0bc(v)) {
        return 0;
    }
    return func_0205d234(v->def, v->key, key);
}

extern "C" int func_0200e0fc(Unk0200e084 *v) {
    return (func_0200e0d0(v, 0x85fbc213) * 0x28f5c) >> 12;
}

extern "C" int func_0200e120(Unk0200e084 *v) {
    return (func_0200e0d0(v, 0x4056abec) * 0x28f5c) >> 12;
}
