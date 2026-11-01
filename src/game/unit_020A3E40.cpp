/*
 * Unit 0x020A3E40-0x020A3F8C: blowing into the microphone (the string "MicrophoneBlow PM_SetAmp
 * issue.." at 0x020BDA20), static object data_020d6cdc with its `__sinit`. The bit 0 of `flags`
 * is set while the level stays above the threshold, with five low readings tolerated. Bounds:
 * hypothesis (the static initializer calls the constructor 0x020A3E40). Layouts come from the
 * code; all names are placeholders. Real file name unknown.
 */
typedef unsigned long u32;

class Unk020a3e40 {
public:
    Unk020a3e40();
    ~Unk020a3e40();

    bool on;
    u32 threshold;
    int unk8;
    bool blowing;
    bool unkd;
    int unk10;
    u32 lowCount;
    u32 flags;
    u32 level;
};

extern "C" {
void func_0207f390();
void func_0207ff64();
int func_0207f968(int a);
int func_0207f270(int a, short *out);
u32 func_02080574(int value);
void func_020897b4(const char *format, ...);
}

Unk020a3e40::Unk020a3e40()
    : on(false), threshold(6000), unk8(0), blowing(false), unkd(false), unk10(0), lowCount(0), flags(0), level(0) {}

Unk020a3e40::~Unk020a3e40() {}

Unk020a3e40 data_020d6cdc;

extern "C" void func_020a3e7c(Unk020a3e40 *p) {
    func_0207f390();
    func_0207ff64();
    if (func_0207f968(1) != 0) {
        func_020897b4("MicrophoneBlow PM_SetAmp issue..");
    }
    p->on = true;
}

extern "C" void func_020a3eb4(Unk020a3e40 *p) {
    if (!p->on) {
        return;
    }
    short sample;
    if (func_0207f270(3, &sample) != 0) {
        return;
    }
    p->level = func_02080574(sample);
    if (p->level > p->threshold) {
        p->lowCount = 0;
        if (p->flags & 1) {
            p->blowing = false;
        } else {
            p->flags |= 1;
            p->blowing = true;
        }
    } else if (p->flags & 1) {
        if (++p->lowCount > 5) {
            p->flags &= ~1;
            p->blowing = false;
        }
    }
}

extern "C" void func_020a3f84(Unk020a3e40 *p, u32 threshold) {
    p->threshold = threshold;
}
