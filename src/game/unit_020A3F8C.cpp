/*
 * Unit 0x020A3F8C-0x020A414C: the sub-files of a container file loaded so far, one bit per
 * sub-file, unloaded together. Bounds: hypothesis (after the microphone; the next function
 * starts the file system wrapper; no data). All names are placeholders. Real file name
 * unknown.
 */
#include "game/unk_archive.h"
#include "game/unk_pool.h"

class Unk020a3f8c {
public:
    Unk020a3f8c();
    ~Unk020a3f8c();

    Unk0209a11c *bits;
    Unk02093648 *archive;
};

extern "C" {
Unk0209487c *func_020a4040(Unk020a3f8c *p, int index);
void func_020a4098(Unk020a3f8c *p);
void func_020a4108(Unk020a3f8c *p);
}

Unk020a3f8c::Unk020a3f8c() : bits(0), archive(0) {}

Unk020a3f8c::~Unk020a3f8c() {
    func_020a4108(this);
}

extern "C" void func_020a3fb0(Unk020a3f8c *p, Unk02093648 *archive) {
    p->archive = archive;
    delete p->bits;
    p->bits = new Unk0209a11c(p->archive->func_020939ec());
}

extern "C" Unk0209487c *func_020a4008(Unk020a3f8c *p, const u32 *name) {
    if (p->archive == 0) {
        return 0;
    }
    if (name == 0) {
        return 0;
    }
    return func_020a4040(p, p->archive->func_02093e30(name));
}

extern "C" Unk0209487c *func_020a4040(Unk020a3f8c *p, int index) {
    if (p->archive == 0) {
        return 0;
    }
    if (!p->bits->func_0209a188(index)) {
        p->bits->func_0209a1c4(index, true);
        p->archive->func_02093a9c(index);
    }
    return p->archive->func_02093a58(index);
}

extern "C" void func_020a4098(Unk020a3f8c *p) {
    if (p->archive == 0) {
        return;
    }
    for (int i = 0; i < p->archive->func_020939ec(); i++) {
        if (p->bits->func_0209a188(i)) {
            p->archive->func_02093c58(i);
            p->bits->func_0209a1c4(i, false);
        }
    }
}

extern "C" void func_020a4108(Unk020a3f8c *p) {
    if (p->archive != 0) {
        func_020a4098(p);
    }
    delete p->bits;
    p->bits = 0;
    p->archive = 0;
}
