/*
 * Unit 0x02052814-0x02053204: the ambient sound list Unk020bfc3c (one static
 * object data_020bfc3c, 0x2C bytes, with its registered destructor). It reads
 * an "Ambient" data tree file from an archive ("Config" sets a value below 16,
 * each "Sounds" / "Sound" node gives a hash, a frequency, a high frequency and
 * a start / end hour), keeps one 0x34-byte record per sound in a linked list,
 * and each update starts, repeats or stops the sounds by the hour of the
 * clock. It saves the sound heap state when it loads a file and restores it
 * when it clears the list ("Couldn't restore sound heap").
 *
 * Bounds: hypothesis. The static initializer 0x020AD1D0 builds data_020bfc3c
 * with the constructor 0x02052814, which opens the range: the code before it
 * (0x02051DA0-0x02052814) is a class with vtable data_020BA10C, whose `.data`
 * ends at 0x020BA1BC where this file's strings start. 0x02053204 starts a file
 * factory (unit_02053204.cpp), with no call to or from this code. `.data` is
 * the strings,
 * `.bss` the destructor chain node and the object. Real file name unknown.
 *
 * Functions other than the constructors and destructors keep C linkage: other
 * files call them by their addresses.
 */

#include "game/unk_archive.h"
#include "game/unk_datatree.h"

/* The sound system (func_020a2994): only the field used here. */
struct Unk020a2994 {
    int unk0;
};

/* The time read by func_0202071c. */
struct Unk0202071c {
    Unk0202071c() {}

    u32 value;
};

struct Unk020d6298;

/* The random generator (0x9C4 bytes). */
struct Unk020a20f0;

/* The world (data_020c3ba4, unit_020582E0.cpp): only the field used here. */
struct Unk020c3ba4 {
    Unk02093648 *archive;
};

/* One sound of the list (0x34 bytes). */
struct Unk02053180 {
    Unk02053180();
    ~Unk02053180();

    Unk02053180 *next;
    Unk02053180 *prev;
    int unk8;
    int id;
    int handle;
    u32 counter;
    u32 delay;
    int freq;
    int freqHigh;
    int start;
    int end;
    bool ambient;
    u32 hash;
};

class Unk020bfc3c {
public:
    Unk020bfc3c();
    ~Unk020bfc3c();

    bool enabled;
    Unk02053180 *head;
    Unk02053180 *tail;
    bool high;
    int playing;
    int nextId;
    u32 unk18;
    int volume;
    int heap;
    u32 file;
    u32 fileHigh;
};

extern Unk020d6298 data_020d6298;
extern Unk020a20f0 data_020d62a4;
extern Unk020c3ba4 data_020c3ba4;

extern "C" {

Unk020a2994 *func_020a2994();
int func_0209c188(int heap);
void func_020a37e8(Unk020a2994 *sound, int heap);
void func_020a34e4(Unk020a2994 *sound, int handle);
int func_020a3514(Unk020a2994 *sound, int handle);
void func_020a3584(Unk020a2994 *sound, int kind, int value);
int func_020a32ac(Unk020a2994 *sound, u32 hash, int a, int volume, int b);
void func_020a3188(Unk020a2994 *sound, u32 hash, int a);
int func_020a20bc(Unk020a20f0 *random, int min, int max);
Unk0202071c func_0202071c(Unk020d6298 *clock);
void func_020897b4(const char *format, ...);

void func_0205285c(Unk020bfc3c *p);
void func_02052898(Unk020bfc3c *p);
void func_020528b4(Unk020bfc3c *p);
void func_020528d8(Unk020bfc3c *p, u32 value);
void func_020528e4(Unk020bfc3c *p);
void func_0205292c(Unk020bfc3c *p, int volume);
void func_02052974(Unk020bfc3c *p, u32 file, Unk02093648 *archive);
void func_020529b4(Unk020bfc3c *p, u32 file, Unk02093648 *archive);
void func_02052a00(Unk020bfc3c *p, bool high);
/* The integer value of the n-th child of a data tree node. */
static inline int func_value(Unk02096348 *tree, const Unk0209674c &node, u32 n) {
    Unk0209674c v = node.func_02096774(n);
    return tree->func_02096574(v.func_0209688c());
}

/* Whether the n-th child of a data tree node has this name. */
static inline bool func_named(const Unk0209674c &node, u32 n, const char *name) {
    Unk0209674c c = node.func_02096774(n);
    return c.func_0209683c((const u32 *)name);
}

void func_02052a74(Unk020bfc3c *p, u32 file, Unk02093648 *archive);
void func_02052e54(Unk020bfc3c *p);
void func_02052e8c(Unk020bfc3c *p);
void func_02053034(Unk020bfc3c *p, u32 hash, bool ambient, int freq, int freqHigh, int start, int end);
void func_02053100(Unk020bfc3c *p);
bool func_020531a8(Unk02053180 *s, u32 hour);

}

Unk020bfc3c data_020bfc3c;

Unk020bfc3c::Unk020bfc3c() {
    enabled = false;
    head = 0;
    tail = 0;
    high = false;
    playing = 0;
    nextId = 0;
    unk18 = 4;
    volume = 0x7f;
    heap = -1;
    file = 0;
    fileHigh = 0;
}

Unk020bfc3c::~Unk020bfc3c() {}

void func_0205285c(Unk020bfc3c *p) {
    if (p->enabled) {
        return;
    }
    p->enabled = true;
    p->high = false;
    p->file = 0;
    p->fileHigh = 0;
    p->head = 0;
    p->tail = 0;
    func_02052898(p);
}

void func_02052898(Unk020bfc3c *p) {
    p->heap = func_0209c188(func_020a2994()->unk0);
}

void func_020528b4(Unk020bfc3c *p) {
    if (!p->enabled) {
        return;
    }
    func_02053100(p);
    p->enabled = false;
}

void func_020528d8(Unk020bfc3c *p, u32 value) {
    if (value < 0x10) {
        p->unk18 = value;
    }
}

void func_020528e4(Unk020bfc3c *p) {
    if (!p->enabled) {
        return;
    }
    for (Unk02053180 *s = p->head; s != 0; s = s->next) {
        int handle = s->handle;
        if (handle != -1) {
            func_020a34e4(func_020a2994(), handle);
            s->handle = -1;
        }
    }
}

void func_0205292c(Unk020bfc3c *p, int volume) {
    if (!p->enabled) {
        return;
    }
    Unk02053180 *s = p->head;
    func_020a3584(func_020a2994(), 0xb, volume);
    for (; s != 0; s = s->next) {
    }
    p->volume = volume;
}

void func_02052974(Unk020bfc3c *p, u32 file, Unk02093648 *archive) {
    if (!p->enabled || file == 0 || archive == 0) {
        return;
    }
    func_02053100(p);
    p->file = file;
    func_02052a74(p, file, archive);
}

void func_020529b4(Unk020bfc3c *p, u32 file, Unk02093648 *archive) {
    if (!p->enabled || file == 0 || archive == 0) {
        return;
    }
    func_02053100(p);
    p->high = true;
    p->fileHigh = file;
    func_02052a74(p, file, archive);
}

void func_02052a00(Unk020bfc3c *p, bool high) {
    Unk02093648 *archive;
    if (!p->enabled || (archive = data_020c3ba4.archive) == 0) {
        return;
    }
    if (high) {
        if (p->fileHigh == 0) {
            return;
        }
        func_020529b4(p, p->fileHigh, archive);
    } else {
        if (p->file == 0) {
            return;
        }
        p->high = false;
        func_02053100(p);
        func_02052974(p, p->file, archive);
    }
}

void func_02052a74(Unk020bfc3c *p, u32 file, Unk02093648 *archive) {
    func_02052898(p);
    file = archive->func_02093e9c(file);
    Unk02096348 *tree = (Unk02096348 *)archive->func_02093a9c(file);
    Unk0209674c root = tree->func_02096980();
    if (root.func_0209683c((const u32 *)"Ambient")) {
        for (int i = 0; i != root.func_020967ec(); i++) {
            Unk0209674c node = root.func_02096774(i);
            if (node.func_0209683c((const u32 *)"Config")) {
                Unk0209674c config = node.func_02096774(0);
                func_020528d8(p, func_value(tree, config, 0));
            }
            if (node.func_0209683c((const u32 *)"Sounds")) {
                int count = node.func_020967ec();
                for (int j = 0; j != count; j++) {
                    Unk0209674c sound = node.func_02096774(j);
                    if (sound.func_0209683c((const u32 *)"Sound")) {
                        u32 hash = 0;
                        int freq = 0;
                        int freqHigh = 0;
                        int start = -1;
                        int end = -1;
                        for (int k = 0; k != sound.func_020967ec(); k++) {
                            if (func_named(sound, k, "Hash")) {
                                hash = func_value(tree, sound, k);
                            }
                            if (func_named(sound, k, "Frequency")) {
                                freq = func_value(tree, sound, k);
                            }
                            if (func_named(sound, k, "FrequencyHigh")) {
                                freqHigh = func_value(tree, sound, k);
                            }
                            if (func_named(sound, k, "StartTime")) {
                                start = func_value(tree, sound, k);
                            }
                            if (func_named(sound, k, "EndTime")) {
                                end = func_value(tree, sound, k);
                            }
                        }
                        if (freq == 0) {
                            func_02053034(p, hash, true, 0, freqHigh, start, end);
                        } else {
                            func_02053034(p, hash, false, freq, freqHigh, start, end);
                        }
                    }
                }
            }
        }
    }
    archive->func_02093c58(file);
}

void func_02052e54(Unk020bfc3c *p) {
    Unk02053180 *s;
    if (!p->enabled || (s = p->head) == 0) {
        return;
    }
    do {
        if (s->freq == -1) {
            s->counter = 1;
        }
        s = s->next;
    } while (s != 0);
}

void func_02052e8c(Unk020bfc3c *p) {
    if (!p->enabled) {
        return;
    }
    Unk0202071c now = func_0202071c(&data_020d6298);
    u32 hour = (now.value & 0x7c0) >> 6;
    int playing = 0;
    for (Unk02053180 *s = p->head; s != 0; s = s->next) {
        int handle = s->handle;
        if (handle != -1) {
            if (func_020a3514(func_020a2994(), handle) == 0) {
                s->handle = -1;
            } else if (s->ambient) {
                if (!func_020531a8(s, hour)) {
                    playing++;
                } else {
                    func_020a34e4(func_020a2994(), s->handle);
                    s->handle = -1;
                }
            } else {
                playing++;
            }
        } else if (!func_020531a8(s, hour)) {
            if (s->ambient) {
                s->handle = func_020a32ac(func_020a2994(), s->hash, 0, 0x7f, 0);
                if (s->handle != -1) {
                    playing++;
                }
            } else {
                bool play = false;
                if (s->freq == -1) {
                    if (s->counter != 0) {
                        play = true;
                    }
                } else if (++s->counter > s->delay) {
                    play = true;
                }
                if (play) {
                    s->delay = s->freqHigh != 0 ? func_020a20bc(&data_020d62a4, s->freq, s->freqHigh) : s->freq;
                    s->counter = 0;
                    s->handle = func_020a32ac(func_020a2994(), s->hash, 0, 0x7f, 0);
                }
            }
        }
    }
    p->playing = playing;
}

void func_02053034(Unk020bfc3c *p, u32 hash, bool ambient, int freq, int freqHigh, int start, int end) {
    if (!p->enabled) {
        return;
    }
    Unk02053180 *s = new Unk02053180;
    s->id = p->nextId++;
    if (p->head == 0) {
        p->head = s;
        p->tail = s;
        s->prev = 0;
        s->next = 0;
    } else if (p->tail != 0) {
        s->prev = p->tail;
        s->next = 0;
        p->tail->next = s;
        p->tail = s;
    }
    s->freq = freq;
    s->freqHigh = freqHigh;
    s->delay = freq;
    s->ambient = ambient;
    s->hash = hash;
    s->start = start;
    s->end = end;
    func_020a3188(func_020a2994(), hash, 0);
}

void func_02053100(Unk020bfc3c *p) {
    if (!p->enabled) {
        return;
    }
    func_020528e4(p);
    Unk02053180 *s = p->head;
    while (s != 0) {
        p->head = s->next;
        delete s;
        s = p->head;
    }
    int heap = p->heap;
    if (heap != -1) {
        func_020a37e8(func_020a2994(), heap);
    } else {
        func_020897b4("Couldn't restore sound heap");
    }
}

Unk02053180::Unk02053180() {
    unk8 = 0;
    id = 0;
    handle = -1;
    counter = 0;
    delay = 0;
    freqHigh = 0;
}

Unk02053180::~Unk02053180() {}

bool func_020531a8(Unk02053180 *s, u32 hour) {
    int start = s->start;
    int end;
    if (start == -1 || (end = s->end) == -1) {
        return false;
    }
    if (start > end) {
        if (hour > start) {
            return false;
        }
        if (hour < end) {
            return false;
        }
    } else if (hour > start) {
        if (hour < end) {
            return false;
        }
    }
    return true;
}
