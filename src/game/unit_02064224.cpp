/*
 * Unit 0x02064224-0x02064330: the object animation archive holder
 * Unk020c4390 (one static object data_020c4390). Its debug strings name it
 * "RenderResources::cObject" (0x020BC520, 0x020BC584); the placeholder name
 * is kept. It opens "ROM_Euro/source/archives/object_animations.nitro_archive"
 * once (Initialise) and deletes it on release.
 *
 * Bounds: hypothesis. The code before works on another object (pairs at
 * 0x100, count at 0x204); unit_02064330.cpp follows, whose strings come after
 * this file's vtables. The static initializer (0x020AE260) builds
 * data_020c4390 and registers its destructor (chain node 0x020C4384). The
 * vtable is followed by the all-zero vtable copy of its interface. Real file
 * name unknown.
 *
 * Initialise and Release keep C linkage: other files call them by their
 * addresses.
 */

#include "game/unk_objanim.h"

extern "C" {
void func_020897b4(const char *fmt, ...);
void func_02063e50(int id);
}

extern "C" {
void func_02064270(Unk020c4390 *o);
void func_020642cc(Unk020c4390 *o);
}

Unk020c4390 data_020c4390;

Unk020c4390::Unk020c4390() {
    loaded = 0;
    archive = 0;
}

Unk020c4390::~Unk020c4390() {
    if (loaded) {
        func_020642cc(this);
    }
}

void func_02064270(Unk020c4390 *o) {
    func_020897b4("RenderResources::cObject::Initialise()");
    if (o->loaded) {
        return;
    }
    o->archive = new Unk02093648("ROM_Euro/source/archives/object_animations.nitro_archive");
    o->archive->func_02094df4();
    o->loaded = 1;
}

void func_020642cc(Unk020c4390 *o) {
    func_020897b4("RenderResources::cObject::Release()");
    if (o->archive != 0) {
        delete o->archive;
    }
    o->archive = 0;
    o->loaded = 0;
}

void Unk020c4390::func_04(int id) {
    func_02063e50(id);
}

void Unk020c4390::func_0c() {}

void Unk020c4390::func_08() {}

int Unk020c4390::func_10() {
    return 0;
}

void Unk020c4390::func_00() {}
