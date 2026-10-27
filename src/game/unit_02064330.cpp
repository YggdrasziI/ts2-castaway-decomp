/*
 * Unit 0x02064330-0x020647B0: the icon set Unk02064330, sixteen 0x14-byte
 * entries Unk02064730, each showing one icon of the files
 * "build/data/icons/<n>.nitro_map" as an object of one screen.
 *
 * Bounds: hypothesis. The code before (0x02064224-0x02064330) belongs to the
 * class whose strings and vtable sit at 0x020BC520-0x020BC5E0, before this
 * file's strings (0x020BC5E0-0x020BC620, only used here); the outfit functions
 * of unit_020647B0.cpp follow. Real file name unknown.
 *
 * The icon key packs the icon file number (bits 0-11), the palette slot of the
 * file (bits 12-15) and the frame in the file (bits 16-27).
 *
 * Functions other than the constructors and destructors keep C linkage: other
 * files call them by their addresses.
 */

#include "game/unk_archive.h"
#include "game/unk_oam.h"
#include "game/unk_resource.h"

/* The game object (data_020d6240): only the archive is used here. */
struct Unk020d6240 {
    int unk0[5];
    Unk02093648 *archive;
};

class Unk02064730 {
public:
    Unk02064730();
    ~Unk02064730() {}

    int unk0;
    u32 file : 12;
    u32 palette : 4;
    u32 frame : 12;
    u8 used;
    u8 screen;
    Unk0208f8b0 *obj;
    Unk02093648 *archive;
};

class Unk02064330 {
public:
    Unk02064330();
    ~Unk02064330();

    Unk02064730 entries[16];
    u8 loaded;
    int palette;
    Unk02093648 *archive;
    u8 screen;
    int priority;
};

extern "C" {
Unk020d6240 *func_020a18e4();
int func_02082a04(char *buf, int size, const char *format, ...);
u32 func_0209a32c(const u32 *str, u32 last, u32 end);

void func_020643b8(Unk02064330 *set, int screen);
void func_020643c4(Unk02064330 *set);
void func_020643ec(Unk02064330 *set);
void func_02064444(Unk02064330 *set);
u32 func_0206446c(int key);
int func_020644b0(int key);
int func_020644bc(int key);
Unk02064730 *func_020644cc(Unk02064330 *set, int key, int palette, int priority);
void func_0206471c(Unk02064730 *e, int x, int y);
void func_02064754(Unk02064730 *e);
}

Unk02064330::Unk02064330() {
    loaded = 0;
    palette = 0;
    archive = 0;
    screen = 0;
    priority = 0;
}

Unk02064330::~Unk02064330() {
    func_02064444(this);
}

void func_020643b8(Unk02064330 *set, int screen) {
    set->screen = screen;
}

void func_020643c4(Unk02064330 *set) {
    for (u32 i = 0; i < 16; i++) {
        func_02064754(&set->entries[i]);
    }
}

void func_020643ec(Unk02064330 *set) {
    if (set->loaded) {
        return;
    }
    set->archive = func_020a18e4()->archive;
    for (u32 i = 0; i < 16; i++) {
        set->entries[i].used = 0;
        set->entries[i].obj = 0;
    }
    set->loaded = 1;
}

void func_02064444(Unk02064330 *set) {
    if (!set->loaded) {
        return;
    }
    func_020643c4(set);
    set->loaded = 0;
}

u32 func_0206446c(int key) {
    char buf[256];
    func_02082a04(buf, 256, "build/data/icons/%d.nitro_map", key & 0xfff);
    return func_0209a32c((const u32 *)buf, 0, 0);
}

int func_020644b0(int key) {
    return (key >> 12) & 0xf;
}

int func_020644bc(int key) {
    return (key >> 16) & 0xfff;
}

Unk02064730 *func_020644cc(Unk02064330 *set, int key, int palette, int priority) {
    for (int i = 0; i != 16; i++) {
        if (!set->entries[i].used) {
            set->entries[i].used = 1;
            set->entries[i].screen = set->screen;
            set->entries[i].file = key & 0xfff;
            set->entries[i].palette = key >> 12;
            set->entries[i].frame = key >> 16;
            char buf[256];
            func_02082a04(buf, 256, "build/data/icons/%d.nitro_map", set->entries[i].file);
            Unk02095140 *file = (Unk02095140 *)set->archive->func_02093c18((const u32 *)buf);
            if (file == 0 || !file->func_020951a8(set->entries[i].frame)) {
                set->entries[i].file = 0;
                set->entries[i].palette = 5;
                set->entries[i].frame = 0;
                file = (Unk02095140 *)set->archive->func_02093c18((const u32 *)"build/data/icons/0.nitro_map");
            }
            set->entries[i].obj = Unk020916a4::func_02091840(set->screen)->func_020919e4((int)file, priority);
            set->entries[i].archive = set->archive;
            if (palette != -1) {
                Unk020916a4::func_02091840(set->screen)->func_0209201c(file, 0, set->entries[i].palette << 4, palette << 4, 0x10);
                set->entries[i].palette = palette;
            } else {
                Unk020916a4::func_02091840(set->screen)->func_0209201c(file, 0, set->entries[i].palette << 4, set->entries[i].palette << 4, 0x10);
            }
            set->entries[i].obj->unk0 = 0x100000;
            set->entries[i].obj->unk4 = 0xc0000;
            set->entries[i].obj->func_0208fb80(set->priority);
            set->entries[i].obj->func_0208faac(set->entries[i].frame);
            set->entries[i].obj->func_0208fb98(set->palette + set->entries[i].palette);
            return &set->entries[i];
        }
    }
    return 0;
}

void func_0206471c(Unk02064730 *e, int x, int y) {
    e->obj->unk0 = x;
    e->obj->unk4 = y;
}

Unk02064730::Unk02064730() {
    unk0 = -1;
    used = 0;
    screen = 0;
    obj = 0;
}

void func_02064754(Unk02064730 *e) {
    if (!e->used) {
        return;
    }
    e->used = 0;
    if (e->obj == 0) {
        return;
    }
    Unk02095140 *file = e->obj->unk1c;
    Unk020916a4::func_02091840(e->screen)->func_02091c68(e->obj);
    e->archive->func_02093c58(e->archive->func_02093f5c(file));
}
