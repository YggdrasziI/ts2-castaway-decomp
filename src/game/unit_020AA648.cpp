/*
 * Unit 0x020AA648-0x020ACAB4: the loader of the layouts: a layout file is a data tree whose children
 * are sprites, each kind with its own child hash; every sprite is read through a table of hashed
 * field names and then linked to the sprites it names. Bounds: hypothesis (the functions called from
 * func_020aba38, down to the last field reader). All names are placeholders. Real file name unknown.
 * Not complete: the twelve sprite readers (95.56 %) and func_020ab57c (95.08 %) miss a second test
 * of the count before their loop, with the registers it shifts.
 */
#include "game/unk_datatree.h"
#include "game/unk_screen.h"

/* A named value of a sprite (type: which reader of the node returns it). */
struct Unk020ab57cField {
    Unk020ab57cField(u32 hash, int type) : hash(hash), type(type) {}

    u32 hash;
    int type;
};

extern "C" {
int func_020aa034(Unk020a9d58 *l, int type);
void func_020a9dc4(Unk020a9d58 *l, int type, int count);
void func_020a7aec(void *s, int id);
void func_020a7b08(Unk020a7af4 *names, u32 hash, int id);
void func_020a7bec(void *s, int v);
void func_020a7d30(Unk020a7c90 *s, int v);
void func_020a7d4c(Unk020a7c90 *s, int v);
void func_020a7d60(Unk020a7c90 *s, int v);
void func_020a7dd4(void *s, int v);
void func_020a7df0(void *s, int v);
void func_020a6980(void *s, u32 v);
void func_020a69ac(void *s, int v);
void func_020a6a64(void *s, int v);
void func_020a6a78(void *s, int v);
int func_020a6a8c(void *s);
void func_020a6e44(void *s, int v);
int func_020a6e58(void *s);
void func_020a6e60(void *s, int v);
void func_020a6e7c(void *s, int v);
void func_020a6ebc(void *s, int v);
void func_020a6efc(void *s, int v);
void func_020a7150(void *s, int v);
int func_020a7164(void *s);
void func_020a716c(void *s, int v);
void func_020a7188(void *s, int v);
void func_020a71a4(void *s, int v);
void func_020a71d4(void *s, int v);
void func_020a7214(void *s, int v);
void func_020a7254(void *s, int v);
void func_020a7268(void *s, int v);
void func_020a727c(void *s, int v);
void func_020a72d0(void *s, int v);
void func_020a7a30(void *s, int v);
void func_020a7a4c(void *s, int v);
void func_020a7a68(void *s, int v);
void func_020a7a84(void *s, int v);
void func_020a8048(void *s, int v);
void func_020a8064(void *s, int v);
void func_020a8078(void *s, int v);
void func_020a808c(void *s, int v);
void func_020a80a0(void *s, int v);
void func_020a82a8(void *s, int v);
void func_020a82e0(void *s, int v);
void func_020a8320(void *s, int v);
void func_020a8360(void *s, int v);
void func_020a8374(void *s, int v);
void func_020a8390(void *s, int v);
void func_020a83a4(void *s, int v);
void func_020a83b8(void *s, int v);
void func_020a83d4(void *s, int v);
void func_020a9008(void *s, int v);
void func_020a901c(void *s, int v);
void func_020a9030(void *s, int v);
void func_020a90b4(void *s, int v);
void func_020a90c8(void *s, int v);
void func_020a90dc(void *s, int v);
void func_020a9168(void *s, int v);
void func_020a9184(void *s, int v);
void func_020a9198(void *s, int v);
void func_020a91ac(void *s, int v);
void func_020a91ec(void *s, int v);
void func_020a922c(void *s, int v);
void func_020a9240(void *s, int v);
void func_020a9254(void *s, int v);
void func_020a928c(void *s, int v);
void func_020a9990(void *s, int v);
int func_020a99a4(void *s);
void func_020a99ac(void *s, int v);
void func_020a99c8(void *s, int v);
void func_020a99e4(void *s, int v);
void func_020a9a00(void *s, int v);
void func_020a9a14(void *s, int v);
void func_020ab57c(const Unk0209674c *node, const Unk020ab57cField *fields, int *values, int count);
void func_020ab680(const Unk0209674c *node, void *s, Unk020a7af4 *names, int id);
int func_020abac0(const Unk0209674c *node, Unk020a9d58 *l, Unk020a7af4 *names);
int func_020abccc(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020abd68(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020abe74(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020abf44(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac128(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac290(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac3ec(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac4a4(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac570(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac5e8(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac7c4(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020ac9dc(const Unk0209674c *node, void *s, Unk020a7af4 *names);
int func_020aa6ac(const Unk0209674c *node, Unk020a9d58 *l, Unk020a7af4 *names);
void func_020ab738(const Unk0209674c *node, Unk020a7c90 *s);
void func_020ab88c(const Unk0209674c *node, void *s);
}

typedef void *(*Unk020aa040Func)(Unk020a9d58 *layout, int type, int index);

#define GET(l, type, index) ((Unk020aa040Func)func_020aa040)(l, type, index)

extern "C" int func_020aa648(const Unk0209674c *node, u32 hash) {
    int count = node->func_020967ec();
    int found = 0;
    for (int i = 0; i < count; i++) {
        Unk0209674c child = node->func_02096774(i);
        if (hash == child.func_02096800()) {
            found++;
        }
    }
    return found;
}

#define READ_SPRITES(name, reader)                                                                     \
    extern "C" int name(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names) { \
        int count = func_020aa648(node, hash);                                                         \
        if (count > 0) {                                                                               \
            int total = node->func_020967ec();                                                         \
            int ok = 0;                                                                                \
            func_020a9dc4(l, type, count);                                                             \
            int i = ok;                                                                                \
            int index = i;                                                                             \
            if (total > 0) {                                                                           \
                for (; i < total; i++) {                                                               \
                    Unk0209674c child = node->func_02096774(i);                                        \
                    void *s = GET(l, type, index);                                                     \
                    if (hash == child.func_02096800()) {                                               \
                        func_020ab680(&child, s, names, index | (type << 16));                         \
                        ok = (ok | reader(&child, s, names)) != 0;                                     \
                        index++;                                                                       \
                    }                                                                                  \
                }                                                                                      \
            }                                                                                          \
            return ok;                                                                                 \
        }                                                                                              \
        return 1;                                                                                      \
    }

extern "C" {
int func_020aa9ac(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aaaa8(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aaba4(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aaca0(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aad9c(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aae98(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020aaf94(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020ab090(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020ab18c(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020ab288(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020ab384(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
int func_020ab480(const Unk0209674c *node, Unk020a9d58 *l, u32 hash, int type, Unk020a7af4 *names);
}

extern "C" int func_020aa6ac(const Unk0209674c *node, Unk020a9d58 *l, Unk020a7af4 *names) {
    switch ((int)node->func_02096800()) {
    case 0x156dfd76:
        return func_020aa9ac(node, l, 0xef8166b4, 0, names);
    case 0x3ddfdc00:
        return func_020aaaa8(node, l, 0x2b3e6dd7, 5, names);
    case 0x047fc6b5:
        return func_020aaaa8(node, l, 0x2b3e6dd7, 6, names);
    case 0x544c6dc1:
        return func_020aaba4(node, l, 0x96474d87, 2, names);
    case 0x6e5a83a1:
        return func_020aaca0(node, l, 0x905e8af8, 1, names);
    case 0x65ff0a85:
        return func_020aad9c(node, l, 0x709e735d, 3, names);
    case (int)0xa152d9cc:
        return func_020aae98(node, l, 0x3fa580bc, 7, names);
    case 0x52e3cd9b:
        return func_020aaf94(node, l, 0xc5c2cf6e, 8, names);
    case (int)0xf31fed81:
        return func_020ab090(node, l, 0x962e39c9, 9, names);
    case 0x2c34e48c:
        return func_020ab18c(node, l, 0x3aa00da6, 10, names);
    case (int)0xe46a09e1:
        return func_020ab288(node, l, 0x9774c086, 11, names);
    case (int)0xc774e57c:
        return func_020ab384(node, l, 0xbf6a1324, 4, names);
    case (int)0x98cccc18:
        return func_020ab480(node, l, 0xdb82455d, 12, names);
    }
    return 1;
}

READ_SPRITES(func_020aa9ac, func_020abccc)
READ_SPRITES(func_020aaaa8, func_020abd68)
READ_SPRITES(func_020aaba4, func_020abe74)
READ_SPRITES(func_020aaca0, func_020abf44)
READ_SPRITES(func_020aad9c, func_020ac128)
READ_SPRITES(func_020aae98, func_020ac290)
READ_SPRITES(func_020aaf94, func_020ac3ec)
READ_SPRITES(func_020ab090, func_020ac4a4)
READ_SPRITES(func_020ab18c, func_020ac570)
READ_SPRITES(func_020ab288, func_020ac5e8)
READ_SPRITES(func_020ab384, func_020ac7c4)
READ_SPRITES(func_020ab480, func_020ac9dc)

extern "C" void func_020ab57c(const Unk0209674c *node, const Unk020ab57cField *fields, int *values, int count) {
    int total = node->func_020967ec();
    int i = 0;
    if (total > 0) {
        for (i = 0; i < total; i++) {
            Unk0209674c child = node->func_02096774(i);
            if (child.func_02096864()) {
            u32 hash = child.func_02096800();
            for (int j = 0; j < count; j++) {
                if (hash == fields[j].hash) {
                    switch (fields[j].type) {
                    case 0:
                        values[j] = child.func_020968a0();
                        break;
                    case 1:
                        values[j] = child.func_02096910();
                        break;
                    case 2:
                        values[j] = child.func_02096948();
                        break;
                    case 3:
                        values[j] = child.func_020968d8();
                        break;
                    }
                }
            }
        }
    }
    }
}

extern "C" void func_020ab680(const Unk0209674c *node, void *s, Unk020a7af4 *names, int id) {
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x11b24, 3), Unk020ab57cField(0x4eec847, 0)};
    int v[2] = {0, 0};
    func_020ab57c(node, fields, v, 2);
    if (v[0] != 0 && names != 0) {
        func_020a7b08(names, v[0], id);
    }
    func_020a7aec(s, v[1]);
}

extern "C" void func_020ab738(const Unk0209674c *node, Unk020a7c90 *s) {
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0x58, 1),       Unk020ab57cField(0x59, 1),       Unk020ab57cField(0x2b3e6dd7, 0),
        Unk020ab57cField(0xe12aac9e, 2), Unk020ab57cField(0x7e49d73c, 0), Unk020ab57cField(0xe24c2e2a, 0),
    };
    int v[6] = {0, 0, 0, 0, -1, -1};
    func_020ab57c(node, fields, v, 6);
    func_020a7c90(s, v[0]);
    func_020a7cac(s, v[1]);
    func_020a7d30(s, v[2]);
    func_020a7cf0(s, v[3] == 1);
    func_020a7d4c(s, v[4]);
    func_020a7d60(s, v[5]);
}

extern "C" void func_020ab88c(const Unk0209674c *node, void *s) {
    func_020ab738(node, (Unk020a7c90 *)s);
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0xc763ec20, 3), Unk020ab57cField(0xc3392e48, 0)};
    int v[2] = {0, 0};
    func_020ab57c(node, fields, v, 2);
    func_020a6980(s, v[0]);
    func_020a69ac(s, v[1]);
}

#define LINK(name, get, set)                                                  \
    extern "C" void name(Unk020a9d58 *l, Unk020a7af4 *names, void *s) {       \
        u32 hash = get(s);                                                    \
        if (hash != (u32)-1) {                                                \
            set(s, (u16)func_020a7b50(names, hash));                          \
        }                                                                     \
    }

LINK(func_020ab938, func_020a99a4, func_020a9990)
LINK(func_020ab978, func_020a7164, func_020a7150)
LINK(func_020ab9b8, func_020a6e58, func_020a6e44)
LINK(func_020ab9f8, func_020a6a8c, func_020a6a78)

extern "C" int func_020aba38(Unk02093648 *archive, u32 hash, Unk020a9d58 *layout, Unk020a7af4 *names) {
    int ok;
    int id = archive->func_02093e9c(hash);
    Unk02096348 *file = (Unk02096348 *)archive->func_02093a9c(id);
    if (file == 0) {
        return 0;
    }
    Unk0209674c root = file->func_02096980();
    ok = 0;
    if (root.func_02096800() == 0xf89bd893) {
        ok = func_020abac0(&root, layout, names);
    }
    archive->func_02093c58(id);
    return ok;
}

extern "C" {
void func_020abb6c(Unk020a9d58 *l, Unk020a7af4 *names, int type);
void func_020abbc4(Unk020a9d58 *l, Unk020a7af4 *names, int type);
void func_020abc1c(Unk020a9d58 *l, Unk020a7af4 *names, int type);
void func_020abc74(Unk020a9d58 *l, Unk020a7af4 *names, int type);
}

extern "C" int func_020abac0(const Unk0209674c *node, Unk020a9d58 *l, Unk020a7af4 *names) {
    int count = node->func_020967ec();
    for (int i = 0; i < count; i++) {
        Unk0209674c child = node->func_02096774(i);
        func_020aa6ac(&child, l, names);
    }
    if (names != 0) {
        func_020abb6c(l, names, 7);
        func_020abbc4(l, names, 2);
        func_020abc1c(l, names, 3);
        func_020abc74(l, names, 4);
    }
    return 1;
}

#define LINK_ALL(name, link)                                                  \
    extern "C" void name(Unk020a9d58 *l, Unk020a7af4 *names, int type) {      \
        int count = func_020aa034(l, type);                                   \
        for (int i = 0; i < count; i++) {                                     \
            link(l, names, GET(l, type, i));                                  \
        }                                                                     \
    }

LINK_ALL(func_020abb6c, func_020ab9b8)
LINK_ALL(func_020abbc4, func_020ab9f8)
LINK_ALL(func_020abc1c, func_020ab938)
LINK_ALL(func_020abc74, func_020ab978)

extern "C" int func_020abccc(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0xc763ec20, 3), Unk020ab57cField(0x29aa4e06, 3)};
    int v[2] = {0, 0};
    func_020ab57c(node, fields, v, 2);
    func_020a7dd4(s, v[0]);
    func_020a7df0(s, v[1]);
    return 1;
}

extern "C" int func_020abd68(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0xc763ec20, 3), Unk020ab57cField(0x165c9d5c, 0), Unk020ab57cField(0xc98e0096, 0),
        Unk020ab57cField(0x5e80b4e1, 0), Unk020ab57cField(0xc3392e48, 0),
    };
    int v[5] = {0, 0, 0, 0, 0};
    func_020ab57c(node, fields, v, 5);
    func_020a8048(s, v[0]);
    func_020a8064(s, v[1]);
    func_020a8078(s, v[2]);
    func_020a808c(s, v[3]);
    func_020a80a0(s, v[4]);
    return 1;
}

extern "C" int func_020abe74(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ab88c(node, s);
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x4c43f955, 0), Unk020ab57cField(0x697a20bc, 3)};
    int v[2] = {0, -1};
    func_020ab57c(node, fields, v, 2);
    func_020a6a64(s, v[0]);
    if (v[1] != -1 && names != 0) {
        func_020a6a78(s, v[1]);
    }
    return 1;
}

extern "C" int func_020abf44(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ab88c(node, s);
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0xda5d73e6, 2), Unk020ab57cField(0xda5d73e7, 2), Unk020ab57cField(0xd88fb3ae, 0),
        Unk020ab57cField(0x141f8, 0),    Unk020ab57cField(0x141f9, 0),    Unk020ab57cField(0x4c43f955, 0),
        Unk020ab57cField(0x96474d87, 0), Unk020ab57cField(0xb49d9f6f, 2), Unk020ab57cField(0x1cfc398f, 2),
    };
    int v[9] = {0, 0, 0, 0x100, 0x100, 0, 0, 0, 0};
    func_020ab57c(node, fields, v, 9);
    func_020a91ac(s, v[0] == 1);
    func_020a91ec(s, v[1] == 1);
    func_020a9168(s, v[2]);
    func_020a9184(s, v[3]);
    func_020a9198(s, v[4]);
    func_020a922c(s, v[5]);
    func_020a9240(s, v[6]);
    func_020a9254(s, v[7] == 1);
    func_020a928c(s, v[8] == 1);
    return 1;
}

extern "C" int func_020ac128(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ab738(node, (Unk020a7c90 *)s);
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0xef8166b4, 3), Unk020ab57cField(0xc763ec20, 0), Unk020ab57cField(0xb0cad4ef, 1),
        Unk020ab57cField(0xb1dd53bd, 1), Unk020ab57cField(0x96474d87, 0), Unk020ab57cField(0x4c43f955, 0),
    };
    int v[6] = {-1, 0, 0x100000, 0xc0000, 0, 0};
    func_020ab57c(node, fields, v, 6);
    func_020a99ac(s, v[1]);
    func_020a99c8(s, v[2]);
    func_020a99e4(s, v[3]);
    func_020a9a00(s, v[4]);
    func_020a9a14(s, v[5]);
    if (v[0] != -1 && names != 0) {
        func_020a9990(s, v[0]);
    }
    return 1;
}

extern "C" int func_020ac290(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0x905e8af8, 3), Unk020ab57cField(0xada6ffac, 0), Unk020ab57cField(0xd69c8299, 2),
        Unk020ab57cField(0xe12aac9e, 2), Unk020ab57cField(0xd4c3832a, 2),
    };
    int v[5] = {-1, 0, 0, 0, 0};
    func_020ab57c(node, fields, v, 5);
    func_020a6e60(s, v[1]);
    func_020a6ebc(s, v[2] == 1);
    func_020a6e7c(s, v[3] == 1);
    func_020a6efc(s, v[4] == 1);
    if (v[0] != -1 && names != 0) {
        func_020a6e44(s, v[0]);
    }
    return 1;
}

extern "C" int func_020ac3ec(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x58, 1), Unk020ab57cField(0x59, 1), Unk020ab57cField(0x5a, 1)};
    int v[3] = {0, 0, 0};
    func_020ab57c(node, fields, v, 3);
    func_020a9008(s, v[0]);
    func_020a901c(s, v[1]);
    func_020a9030(s, v[2]);
    return 1;
}

extern "C" int func_020ac4a4(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ac3ec(node, s, names);
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x141f8, 1), Unk020ab57cField(0x141f9, 1), Unk020ab57cField(0x141fa, 1)};
    int v[3] = {0x1000, 0x1000, 0x1000};
    func_020ab57c(node, fields, v, 3);
    func_020a90b4(s, v[0]);
    func_020a90c8(s, v[1]);
    func_020a90dc(s, v[2]);
    return 1;
}

extern "C" int func_020ac570(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x67b6f7f3, 1)};
    int v[1] = {0};
    func_020ab57c(node, fields, v, 1);
    func_020a7bec(s, v[0]);
    return 1;
}

extern "C" int func_020ac5e8(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ab88c(node, s);
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0x5e80b4e1, 0), Unk020ab57cField(0x2e0887aa, 0), Unk020ab57cField(0xb0cad4ef, 1),
        Unk020ab57cField(0xb1dd53bd, 1), Unk020ab57cField(0xda5d73e6, 2), Unk020ab57cField(0xda5d73e7, 2),
        Unk020ab57cField(0x4c43f955, 0), Unk020ab57cField(0x96474d87, 0), Unk020ab57cField(0xb49d9f6f, 2),
    };
    int v[9] = {1, 1, 0, 0, 0, 0, 0, 0, 0};
    func_020ab57c(node, fields, v, 9);
    func_020a8390(s, v[0]);
    func_020a83a4(s, v[1]);
    func_020a83b8(s, v[2]);
    func_020a83d4(s, v[3]);
    func_020a82e0(s, v[4] != 0);
    func_020a8320(s, v[5] != 0);
    func_020a8360(s, v[6]);
    func_020a8374(s, v[7]);
    func_020a82a8(s, v[8] == 1);
    return 1;
}

extern "C" int func_020ac7c4(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    func_020ab738(node, (Unk020a7c90 *)s);
    static const Unk020ab57cField fields[] = {
        Unk020ab57cField(0xb0cad4ef, 1), Unk020ab57cField(0xb1dd53bd, 1), Unk020ab57cField(0xda5d73e6, 2),
        Unk020ab57cField(0xda5d73e7, 2), Unk020ab57cField(0x4c43f955, 0), Unk020ab57cField(0x96474d87, 0),
        Unk020ab57cField(0x82ced7f4, 0), Unk020ab57cField(0xe6d1a702, 0), Unk020ab57cField(0xcbe8ecf7, 0),
        Unk020ab57cField(0xef8166b4, 3),
    };
    int v[10] = {0, 0, 0, 0, 0, 0, -1, -1, 0, -1};
    func_020ab57c(node, fields, v, 10);
    func_020a7188(s, v[0]);
    func_020a71a4(s, v[1]);
    func_020a71d4(s, v[2] == 1);
    func_020a7214(s, v[3] == 1);
    func_020a7268(s, v[4]);
    func_020a7254(s, v[5]);
    func_020a727c(s, v[6]);
    func_020a72d0(s, v[7]);
    func_020a716c(s, v[8]);
    if (v[9] != -1 && names != 0) {
        func_020a7150(s, v[9]);
    }
    return 1;
}

extern "C" int func_020ac9dc(const Unk0209674c *node, void *s, Unk020a7af4 *names) {
    static const Unk020ab57cField fields[] = {Unk020ab57cField(0x52, 0), Unk020ab57cField(0x47, 0), Unk020ab57cField(0x42, 0), Unk020ab57cField(0x41, 0)};
    int v[4] = {0, 0, 0, 0};
    func_020ab57c(node, fields, v, 4);
    func_020a7a30(s, v[0]);
    func_020a7a4c(s, v[1]);
    func_020a7a68(s, v[2]);
    func_020a7a84(s, v[3]);
    return 1;
}

/* Read by no relocated code: kept here because no gap can follow the last .rodata file. */
extern "C" {
extern const int data_020b6e08[15];
}

const int data_020b6e08[15] = {4, 10, 9, 1, 3, 3, 5, 6, 9, 2, 5, 2, 2, 6, 2};
