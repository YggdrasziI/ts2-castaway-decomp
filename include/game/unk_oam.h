/*
 * Object entry of unit_0208F8B0.cpp, object (OAM) manager of unit_020916A4.cpp and
 * the iterator of unit_02092640.cpp.
 * Layouts come from the code; all names are placeholders.
 */
#ifndef GAME_UNK_OAM_H
#define GAME_UNK_OAM_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned long u32;

class Unk02095140;

/*
 * The 40-byte object entry of unit_0208F8B0.cpp: the OAM attributes it builds
 * (unk8: attributes 0 and 1, unkC: attribute 2), its size and flags, the file of
 * its pixels and the block allocated for them.
 */
class Unk0208f8b0 {
public:
    Unk0208f8b0();
    void func_0208f90c(Unk02095140 *file);
    void func_0208f9dc();
    void func_0208fa14(int heap);
    void func_0208fa60();
    int func_0208fa84();
    int func_0208faa4();
    void func_0208faac(int frame);
    void func_0208fadc(int size, int shape);
    void func_0208fb44(int color256);
    void func_0208fb6c(int mode);
    void func_0208fb80(int priority);
    void func_0208fb98(int palette);
    void func_0208fbac(int flip);
    void func_0208fbe0(int flip);
    static bool func_0208fc14(int width, int height, int *size, int *shape);
    int func_0208fc74();
    void func_0208fcd8(int affine);
    bool func_0208fcf0();
    void func_0208fd04(int index);
    int func_0208fd1c();
    bool func_0208fd2c();
    void func_0208fd44(int unk);
    bool func_0208fd5c();
    void func_0208fd74(int unk);
    int func_0208fd8c();
    void func_0208fd9c(int next);
    void func_0208fdb4(int index);
    int func_0208fdcc();
    void func_0208fddc();
    bool func_0208fe08(int heap);
    void func_0208fe80(int heap);
    void func_0208fed4(Unk0208f8b0 *other);
    void func_0208ff24(u32 data);

    u32 unk0;
    u32 unk4;
    u32 unk8;
    u16 unkC;
    u32 unk10_0 : 2;
    u32 unk10_2 : 2;
    u32 unk10_4 : 7;
    u32 unk10_11 : 1;
    u32 unk10_12 : 1;
    u32 unk10_13 : 1;
    u32 unk10_14 : 7;
    u32 unk10_21 : 1;
    u32 unk10_22 : 10;
    int unk14;
    int unk18;
    Unk02095140 *unk1c;
    void *unk20;
    u32 unk24;
};

/* Iterator over a chain of entries (unit_02092640.cpp). */
class Unk02092640 {
public:
    Unk02092640();
    Unk02092640(void *entry, int unk8, int unkA);
    void func_0209266c();
    void *func_02092678();
    bool func_020926d4();
    u16 func_020926fc();

    void *first;
    void *cur;
    u16 unk8;
    u16 unkA;
};

/* One slot of the entry list, sorted by priority. */
struct Unk020916a4Node {
    Unk020916a4Node() : index(0), priority(0), next(0) {}

    u16 index;
    u16 priority;
    Unk020916a4Node *next;
};

/* One affine parameter set (2x2 matrix in 8.8) and its users. */
struct Unk020916a4Affine {
    Unk020916a4Affine() {
        index = 0;
        refCount = 0;
        pa = 0x100;
        pb = 0;
        pc = 0;
        pd = 0x100;
    }

    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    u16 index;
    s16 refCount;
};

class Unk020916a4 {
public:
    Unk020916a4(void *oam, int unk820, int main);
    static Unk020916a4 *func_02091820();
    static Unk020916a4 *func_02091830();
    static Unk020916a4 *func_02091840(int main);
    void func_0209185c(bool show);
    Unk0208f8b0 *func_0209189c(u16 priority);
    Unk0208f8b0 *func_020919e4(int unk, u16 priority);
    void func_02091a0c(Unk0208f8b0 *entry, u16 priority);
    Unk02092640 func_02091ab0(int n, u16 priority);
    Unk02092640 func_02091b9c(int n, int unk, u16 priority);
    void func_02091bec(Unk02092640 &it);
    void func_02091c68(Unk0208f8b0 *entry);
    void func_02091d58();
    void func_02091de0(Unk0208f8b0 *a, Unk0208f8b0 *b);
    void func_02091eb4(Unk02095140 *file, int index, int mask);
    void func_0209201c(Unk02095140 *file, int index, u32 src, u32 dst, u32 n);
    void func_02092098(void *data, u32 dst, u32 n);
    Unk020916a4Affine *func_020920dc();
    void func_02092160(Unk0208f8b0 *entry, Unk020916a4Affine *affine);
    void func_020921c4(Unk0208f8b0 *entry, int angle, int scaleX, int scaleY);
    void func_020922cc(Unk0208f8b0 *entry, int angle, int scaleX, int scaleY, int flip);
    void func_0209241c(Unk0208f8b0 *entry);
    void func_02092490(Unk020916a4Affine *affine);
    bool func_020924c0(Unk020916a4Affine *affine);
    int func_020924fc();
    Unk0208f8b0 *func_0209250c(Unk0208f8b0 *entry);
    void func_02092554();
    bool func_02092620();

    Unk0208f8b0 entries[0x80];
    Unk020916a4Node nodes[0x80];
    Unk020916a4Node *used;
    Unk020916a4Node *free;
    Unk020916a4Node *tail;
    Unk020916a4Node *pending;
    int count;
    u16 minPriority;
    u16 maxPriority;
    void *oam;
    u32 main : 1;
    u32 unk81c_1 : 31;
    int unk820;
    Unk020916a4Affine affines[0x20];
    u32 affineMask;
};

#endif
