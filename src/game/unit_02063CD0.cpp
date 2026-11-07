/*
 * Unit 0x02063CD0-0x02064224: the played animations Unk02063d84
 * (include/game/unk_animinst.h) and their manager Unk020c417c (one static
 * object data_020c417c). An animation is the ".nitro_animation" file of a key
 * in an archive, with the sound bank of the same key (".sounds.nitro_xml")
 * when the archive has one. The manager counts the animation files in use per
 * archive and shares the sound banks by name hash (at most 32), releasing
 * them when the last animation goes.
 *
 * Bounds: hypothesis. The code before works on the item database and other
 * statics; unit_02064224.cpp follows. The static initializer (0x020AE204)
 * clears the two tables and counts of data_020c417c (no destructor). The two
 * strings are only used here. Real file name unknown.
 *
 * Functions other than the constructor and destructor keep C linkage: other
 * files call them by their addresses.
 */

#include "game/unk_animinst.h"
#include "game/unk_objanim.h"

extern "C" {
void func_02099afc(int id);
void func_02099b28(void);
u32 func_0209a3c4(u32 hash, const char *str);
Unk020a3d2c *func_020a3d2c(Unk020a3d2c *p, Unk020897c0 *anim, Unk020a3a44 *bank);
void func_020a3d50(Unk020a3d2c *p);
void func_020a3d74(Unk020a3d2c *p);
Unk020a3a44 *func_020a3a44(Unk020a3a44 *p, Unk0209487c *file);
void func_020a3a70(Unk020a3a44 *p);
void func_020a3a90(Unk020a3a44 *p);
}

/* The sound player of an animation (0xC bytes): only its bank is read. */
class Unk020a3d2c {
public:
    ~Unk020a3d2c() {
        func_020a3d50(this);
    }

    int unk0;
    Unk020a3a44 *bank;
    int unk8;
};

/* A sound bank (0x14 bytes) with its use count at 0x10. */
class Unk020a3a44 {
public:
    ~Unk020a3a44() {
        func_020a3a70(this);
    }

    int unk0[4];
    int count;
};

/* One animation file in use and its archive. */
struct Unk020c417cFile {
    Unk020c417cFile() : archive(0), file(0) {}

    Unk02093648 *archive;
    Unk0209487c *file;
};

/* One sound bank and the hash of its name. */
struct Unk020c417cBank {
    Unk020c417cBank() : hash(0), bank(0) {}

    u32 hash;
    Unk020a3a44 *bank;
};

class Unk020c417c {
public:
    Unk020c417c() : fileCount(0), bankCount(0) {}

    Unk020c417cFile files[32];
    Unk020c417cBank banks[32];
    int fileCount;
    int bankCount;
};

extern "C" {
Unk020897c0 *func_02063d84(Unk02063d84 *a);
Unk020a3d2c *func_02063d8c(Unk02063d84 *a);
void func_02063d94(Unk02063d84 *a, int speed, int hold);
void func_02063db8(Unk02063d84 *a, int loop);
Unk02063d84 *func_02063dd4(Unk02093648 *archive, u32 key, int mode);
Unk02063d84 *func_02063e2c(u32 key, int mode);
void func_02063e50(Unk02063d84 *a);
Unk02063d84 *func_02063e68(Unk020c417c *m, Unk02093648 *archive, u32 key);
void func_02063f5c(Unk020c417c *m, Unk02063d84 *a);
Unk020a3a44 *func_02064074(Unk020c417c *m, Unk02093648 *archive, u32 key);
void func_02064164(Unk020c417c *m, Unk020a3a44 *bank);
}

Unk020c417c data_020c417c;

Unk02063d84::Unk02063d84(Unk02093544 *file, Unk020a3a44 *bank) {
    unk0 = 0;
    anim = 0;
    anim = new Unk020897c0(file, 9);
    if (bank != 0) {
        Unk020a3d2c *p = (Unk020a3d2c *)operator new(0xc);
        if (p != 0) {
            p = func_020a3d2c(p, anim, bank);
        }
        unk0 = p;
    }
}

Unk02063d84::~Unk02063d84() {
    delete anim;
    delete unk0;
}

Unk020897c0 *func_02063d84(Unk02063d84 *a) {
    return a->anim;
}

Unk020a3d2c *func_02063d8c(Unk02063d84 *a) {
    return a->unk0;
}

void func_02063d94(Unk02063d84 *a, int speed, int hold) {
    a->anim->func_01ff8ab4(speed, hold);
    if (a->unk0 != 0) {
        func_020a3d74(a->unk0);
    }
}

void func_02063db8(Unk02063d84 *a, int loop) {
    u16 mode;
    if (loop) {
        mode = 0;
    } else {
        mode = 2;
    }
    a->anim->func_01ff8a70(mode);
}

Unk02063d84 *func_02063dd4(Unk02093648 *archive, u32 key, int mode) {
    Unk02063d84 *a = func_02063e68(&data_020c417c, archive, key);
    if (a != 0) {
        func_02063db8(a, !(mode & 2) || (mode & 1));
    }
    return a;
}

Unk02063d84 *func_02063e2c(u32 key, int mode) {
    return func_02063dd4(data_020c4390.archive, key, mode);
}

void func_02063e50(Unk02063d84 *a) {
    func_02063f5c(&data_020c417c, a);
}

Unk02063d84 *func_02063e68(Unk020c417c *m, Unk02093648 *archive, u32 key) {
    if (archive == 0) {
        return 0;
    }
    int index = archive->func_02093ef4(func_0209a3c4(key, ".nitro_animation"), 3);
    if (index < 0) {
        return 0;
    }
    Unk0209487c *file = archive->func_02093a9c(index);
    int found = -1;
    for (int i = 0; i < m->fileCount; i++) {
        if (m->files[i].file == file) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        m->files[m->fileCount].archive = archive;
        m->files[m->fileCount].file = file;
        m->fileCount++;
    }
    func_02099afc(9);
    Unk02063d84 *a = new Unk02063d84((Unk02093544 *)file, func_02064074(m, archive, key));
    func_02099b28();
    return a;
}

void func_02063f5c(Unk020c417c *m, Unk02063d84 *a) {
    if (a == 0) {
        return;
    }
    int i;
    Unk0209487c *file = (Unk0209487c *)func_02063d84(a)->file;
    Unk020a3a44 *bank = 0;
    if (func_02063d8c(a) != 0) {
        bank = func_02063d8c(a)->bank;
    }
    delete a;
    if (bank != 0) {
        func_02064164(m, bank);
    }
    for (i = 0; i < m->fileCount; i++) {
        Unk020c417cFile &f = m->files[i];
        if (f.file == file) {
            int index = f.archive->func_02093f5c(file);
            f.archive->func_02093c58(index);
            if (f.archive->func_02094000(index)) {
                return;
            }
            m->fileCount--;
            if (i == m->fileCount) {
                return;
            }
            if (m->fileCount <= 0) {
                return;
            }
            f = m->files[m->fileCount];
            m->files[m->fileCount].archive = 0;
            m->files[m->fileCount].file = 0;
            return;
        }
    }
}

Unk020a3a44 *func_02064074(Unk020c417c *m, Unk02093648 *archive, u32 key) {
    if (archive == 0) {
        return 0;
    }
    key = func_0209a3c4(key, ".sounds.nitro_xml");
    int index = archive->func_02093ef4(key, 7);
    if (index < 0) {
        return 0;
    }
    int n = m->bankCount;
    for (int i = 0; i < n; i++) {
        Unk020c417cBank &b = m->banks[i];
        if (b.hash == key) {
            func_020a3a90(b.bank);
            return m->banks[i].bank;
        }
    }
    if (n >= 32) {
        return 0;
    }
    m->bankCount++;
    Unk020c417cBank &e = m->banks[n];
    Unk0209487c *file = archive->func_02093a9c(index);
    e.hash = key;
    Unk020a3a44 *bank = (Unk020a3a44 *)operator new(0x14);
    if (bank != 0) {
        bank = func_020a3a44(bank, file);
    }
    e.bank = bank;
    archive->func_02093c58(index);
    return e.bank;
}

/* The counter is unsigned with a signed compare: an int counter swaps the
 * counter and element pointer registers. */
void func_02064164(Unk020c417c *m, Unk020a3a44 *bank) {
    for (u32 i = 0; (int)i < m->bankCount; i++) {
        Unk020c417cBank &b = m->banks[i];
        if (b.bank == bank) {
            if (b.bank->count > 0) {
                continue;
            }
            delete m->banks[i].bank;
            m->banks[i].hash = 0;
            m->banks[i].bank = 0;
            m->bankCount--;
            if (i == m->bankCount) {
                return;
            }
            if (m->bankCount <= 0) {
                return;
            }
            b = m->banks[m->bankCount];
            Unk020c417cBank &last = m->banks[m->bankCount];
            last.hash = 0;
            last.bank = 0;
            return;
        }
    }
}
