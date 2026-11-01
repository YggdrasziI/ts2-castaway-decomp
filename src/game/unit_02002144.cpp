/*
 * Unit 0x02002144-0x020023AC: three commands of the script table (names from the table of
 * `unit_0205AF94.cpp`): "PlaySound", "StopSoundEffects" and "AdvanceTime". Bounds:
 * hypothesis (the inline functions of unit_02001FDC.cpp end at 0x02002144,
 * to the class operators of the action base; no data). Layouts come from the code; all
 * names are placeholders.
 */
typedef unsigned short u16;
typedef unsigned long u32;

class Unk02061d08Item {
public:
    int unk0;
    unsigned char list[4];
};

/* The parameters of a script step (unit_02099C0C.cpp). */
class Unk02099c0c {
public:
    bool func_02099c0c(int *value, int key);
    int func_02099c58(int key);

    void *owner;
    u16 next;
};

struct Unk02002144Sound {
    unsigned char unk0[0x18];
    int unk18;
};

struct Unk020022ccNext {
    unsigned char unk0[0x18];
    void *owner;
};

extern "C" {
u16 func_02002144(Unk02099c0c *node);
u16 func_0200228c(Unk02099c0c *node);
u16 func_020022cc(Unk02099c0c *node);
void func_02000e70(Unk020022ccNext *next, Unk02061d08Item *item, int a, int b, int c, int d, int e);
Unk020022ccNext *func_02007c98(void *pool, int kind, int linked);
void func_02007ea4(void *list, void *o);
void func_0205c564(bool *out, int value);
Unk02061d08Item *func_0205c5e0(Unk02099c0c *node);
void *func_020a2994();
int func_020a2ce8(void *sound, int hash, int volume, int unk);
Unk02002144Sound *func_020a3858(void *sound, int hash, bool a, bool b, int c);
void func_020a389c(void *sound, int handle);
extern unsigned char data_020be184[];
extern unsigned char data_020c4770[];
}

u16 func_02002144(Unk02099c0c *node) {
    int hash = node->func_02099c58(0xc02b2ac5);
    int value = 0;
    bool loaded = true;
    if (node->func_02099c0c(&value, 0x129229bc)) {
        func_0205c564(&loaded, value);
    }
    bool loop = false;
    int value2 = 0;
    if (node->func_02099c0c(&value2, 0x4c9e6a90)) {
        func_0205c564(&loop, value2);
    }
    bool pan = true;
    int value3 = 0;
    if (node->func_02099c0c(&value3, 0xf4fc829f)) {
        func_0205c564(&pan, value3);
    }
    int handle = 0;
    node->func_02099c0c(&handle, 0x4eec847);
    if (hash != 0) {
        if (loaded) {
            Unk02002144Sound *s = func_020a3858(func_020a2994(), hash, loop, pan, 0);
            if (s != 0) {
                s->unk18 = handle;
            }
        } else {
            func_020a2ce8(func_020a2994(), hash, 0x7f, 0);
        }
    }
    return node->next;
}

u16 func_0200228c(Unk02099c0c *node) {
    int handle = 0;
    node->func_02099c0c(&handle, 0x4eec847);
    if (handle != 0) {
        func_020a389c(func_020a2994(), handle);
    }
    return node->next;
}

u16 func_020022cc(Unk02099c0c *node) {
    int a = node->func_02099c58(0xbbb0caef);
    int d = node->func_02099c58(0xb2b663fb);
    int e = node->func_02099c58(0x7285597c);
    int b = node->func_02099c58(0x8c75aba3);
    int c = node->func_02099c58(0x8e032298);
    Unk02061d08Item *item = func_0205c5e0(node);
    if (item != 0) {
        Unk020022ccNext *next = func_02007c98(data_020be184, 0x1d, 2);
        if (next == 0) {
            return node->next;
        }
        func_02000e70(next, item, a, b, c, d, e);
        func_02007ea4(item->list, next);
        func_02007ea4(data_020c4770, next->owner);
    }
    return node->next;
}
