/*
 * Unit 0x020A22FC-0x020A3A44: the sound manager (the strings of its error messages at
 * 0x020BD8A0-0x020BDA20, singleton data_020d6c68, created by main). It owns a NitroSystem sound
 * archive and heap, twelve sound effect handles, a music handle, four delayed sound elements
 * and four 0x10400-byte load slots. Bounds: hypothesis (the callers of the singleton; `.rodata`
 * is the table searched by hash, 374 entries; `.bss` holds the singleton, the alarm-like
 * object and the 0x3C-byte file header). The dsd names are kept (C linkage) for the callers.
 * Layouts come from the code; all names are placeholders. Real file name unknown.
 */
#include "game/unk_catalog.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

struct Unk020a22fcPlayer {
    u8 unk0[0x2c];
    u8 active;
    u8 unk2d[0xb];
    u16 unk38;
    u16 unk3a;
};

struct Unk020a22fcEntry {
    u8 type;
    u8 unk1;
    int id;
};

struct Unk020a22fcList {
    u32 count;
    Unk020a22fcEntry entries[1];
};

struct Unk020a22fcSound {
    int hash;
    u16 group;
    u16 id;
    int unk8;
};

struct Unk020a22fcSlot {
    Unk020a22fcSlot() : buffer(0), used(false), owner(0) {}

    void *buffer;
    void *heap;
    bool used;
    int owner;
};

class Unk020a22fcElement {
public:
    Unk020a22fcElement() {}
    ~Unk020a22fcElement() {}

    short delay;
    int sound;
    u32 flags;
    int handle;
    u32 speed;
    int volume;
    int owner;
    int unk1c;
    Unk020a22fcSlot *slot;
};

class Unk020a267c {
public:
    Unk020a267c(const char *path, u32 size);

    void *heap;
    void *buffer;
    u8 archive[0x90];
    Unk020a22fcPlayer *handles[12];
    Unk020a22fcPlayer *music;
    u8 stream[4];
    int musicId;
    int unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    int unke4;
    Unk020a22fcElement elements[4];
    int unk178;
    int unk17c;
    u8 volumes[0x20];
    bool slotsReady;
    bool unk1a1;
    Unk020a22fcSlot slots[4];
    int heapLevel;
};

struct Unk020a22fcFile {
    u32 id : 24;
    u32 unk : 8;
};

struct Unk020a22fcHeader {
    u8 unk0[0x38];
    int count;
};

extern "C" {
int OS_DisableInterrupts();
void OS_RestoreInterrupts(int state);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void MI_CpuFill8(void *dst, u8 value, u32 size);
void DC_StoreRange(void *start, u32 size);
void *NNSi_SndSeqArcGetSeqInfo(void *arc, int index);
void func_020897b4(const char *format, ...);
Unk020081dc func_020081dc(void *player);
int func_0209be08(void *lock);
void *NNS_SndArcGetFileAddress(int file);
void func_0209b9a0(int file, void *p);
void SND_DestroyWaveArc(void *p);
void *func_0207e074(void *p, int index);
void func_0207e0bc(void *p, int index, void *value);
void SND_InvalidateWaveData(void *start, void *end);
void func_0209b094(void *handle, int mask, int value);
void func_0209b064(void *handle, int value);
void func_0209b0c4(void *handle, int mask, int value);
void func_0209b134(void *handle, int value);
void func_0209b104(void *handle, int value);
void func_0209b020(void *handle, int a, int b);
void func_0209b144(void *handle, int value);
void func_0209b16c(void *handle);
void func_0209b1e0(void *handle, int fade);
void func_0209b2c8(int index, int value);
void func_0207c124();
void func_0207bff0(void *p);
void func_0207bf58(void *p, int a, int b, void (*callback)(), int d);
void func_0207beb8(void *p);
void func_0209a7bc();
void func_0209a788();
void *func_0209c424(void *buffer, u32 size);
void func_0209c03c(void *archive, const char *path, void *heap, int d);
void NNS_SndArcPlayerSetup(void *heap);
void func_0209e654(int count, void *heap);
void func_0209e56c(void *stream);
int func_0209e520(void *stream);
int func_0209c280(void *heap);
void func_0209c194(void *heap, int level);
int func_0209c188(void *heap);
void func_0209d0b8(int group, void *heap);
int func_0209ba04(int file, void *dst, u32 size, int offset);
void *func_0209bdf8();
void *func_0209c2d8(void *heap, u32 size, void *callback, void *a, int b);
int func_0207e0f4(void *p);
int func_0207e2f4(void *p, int a, int b, void *out);
Unk020a22fcList *func_0209bad8(int group);
int *func_0209bd30(int id);
int *func_0209bccc(int id);
int *func_0209bd94(int id);
Unk020a22fcFile *func_0209bc68(int id);
int func_0209cdf4(int id, int a, void *heap, int d, int e);
int func_0209cc94(int id, int a, void *heap, int d, void *e);
void NNS_SndArcLoadBank(int id, void *heap);
void func_0209d050(int id, int a, void *heap);
int NNS_SndArcPlayerStartSeqArc(void *handle, int a, int b);
int NNS_SndArcPlayerStartSeq(void *handle, int a);
void *func_0209ad38(void *handle, int a, int b);
void *func_0209ac14(int a, void *b);
void func_0209ad2c(void *p);
void func_0209acd0(void *a, void *b, int c, int d);

extern u8 data_020c43a8[];
/* Two-digit strings, not referenced by the code. */
extern const char data_020b59f4[100][4] = {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
    "60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
    "70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
    "90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
};

/* Sounds sorted by hash: hash, group, id, third value. */
extern const Unk020a22fcSound data_020b5b84[374] = {
    {(int)0x80785E4A, 0x3, 0x22, 0x25},
    {(int)0x816AA973, 0x4, 0x28, 0x29},
    {(int)0x8179AD73, 0x4, 0x29, 0x2A},
    {(int)0x8188B173, 0x4, 0x2A, 0x2B},
    {(int)0x8197B573, 0x4, 0x2B, 0x2C},
    {(int)0x82D70B47, 0x16, 0x2, 0x3},
    {(int)0x830FF455, 0x3, 0x18, 0x1B},
    {(int)0x84E75B77, 0x0, 0x6, 0x8},
    {(int)0x8540B13A, 0xD, 0x17, 0x18},
    {(int)0x8540B13C, 0xD, 0x18, 0x19},
    {(int)0x854BCC3F, 0x2, 0xB, 0x15},
    {(int)0x876DA727, 0x17, 0x1, 0x2},
    {(int)0x8918B7B9, 0xB, 0x28, 0x29},
    {(int)0x8918B7BA, 0xB, 0x29, 0x2A},
    {(int)0x8A135E52, 0x3, 0x8, 0xB},
    {(int)0x8EB3197D, 0x4, 0x3B, 0x3C},
    {(int)0x8EC21D7D, 0x4, 0x3C, 0x3D},
    {(int)0x8EDAE055, 0xB, 0xB, 0xC},
    {(int)0x8EDAE057, 0xB, 0xC, 0xD},
    {(int)0x90496B69, 0xA, 0x1, 0x2},
    {(int)0x91E3F4D2, 0xB, 0x5, 0x6},
    {(int)0x91E3F4D7, 0xB, 0x6, 0x7},
    {(int)0x92526783, 0x0, 0x10, 0x13},
    {(int)0x93B554F6, 0x4, 0x15, 0x16},
    {(int)0x93C458F6, 0x4, 0x16, 0x17},
    {(int)0x9445D842, 0x4, 0x3F, 0x40},
    {(int)0x955D5396, 0xA, 0x3A, 0x3B},
    {(int)0x96B3C954, 0x0, 0x2, 0x3},
    {(int)0x96FF786D, 0xB, 0xD, 0xE},
    {(int)0x96FF786E, 0xB, 0xE, 0xF},
    {(int)0x98E419B7, 0x2, 0x2A, 0x34},
    {(int)0x98FBAB0B, 0x3, 0x1, 0x2},
    {(int)0x9A60A723, 0x0, 0x1, 0x2},
    {(int)0x9A892F98, 0x1, 0x1, 0x4},
    {(int)0x9BFAEE54, 0xB, 0x1, 0x2},
    {(int)0x9BFAEE5A, 0xB, 0x2, 0x3},
    {(int)0x9CF9F588, 0xD, 0x1B, 0x1C},
    {(int)0x9CF9F589, 0xD, 0x1C, 0x1D},
    {(int)0x9CF9F58D, 0xD, 0x1D, 0x1E},
    {(int)0x9CF9F967, 0xD, 0x1E, 0x1F},
    {(int)0x9D16DC57, 0x2, 0xA, 0x14},
    {(int)0x9E2E4586, 0x4, 0x38, 0x39},
    {(int)0x9E593FE2, 0x2, 0xC, 0x16},
    {(int)0x9E59DB1D, 0x2, 0x0, 0x5},
    {(int)0x9E86892E, 0xB, 0x9, 0xA},
    {(int)0x9E868930, 0xB, 0xA, 0xB},
    {(int)0x9F5CEC9F, 0x3, 0x19, 0x1C},
    {(int)0xA0C11CC7, 0xA, 0xD, 0xE},
    {(int)0xA0C11CC8, 0xA, 0xE, 0xF},
    {(int)0xA0C6143A, 0x0, 0xF, 0x12},
    {(int)0xA25893C0, 0x4, 0x2D, 0x2E},
    {(int)0xA431626B, 0x4, 0x19, 0x1A},
    {(int)0xA440666B, 0x4, 0x1A, 0x1B},
    {(int)0xA466F959, 0xB, 0x1F, 0x20},
    {(int)0xA466F95A, 0xB, 0x20, 0x21},
    {(int)0xA570D631, 0xA, 0x1D, 0x1E},
    {(int)0xA570D632, 0xA, 0x1E, 0x1F},
    {(int)0xA6BAA0A1, 0x3, 0x26, 0x29},
    {(int)0xA8009236, 0xD, 0x19, 0x1A},
    {(int)0xA8009237, 0xD, 0x1A, 0x1B},
    {(int)0xA8454443, 0xA, 0x8, 0x9},
    {(int)0xA8454444, 0xA, 0x9, 0xA},
    {(int)0xA97EE4EE, 0xE, 0x4, 0x5},
    {(int)0xA9C99549, 0xB, 0x21, 0x22},
    {(int)0xA9C9954D, 0xB, 0x22, 0x23},
    {(int)0xA9C99550, 0xB, 0x23, 0x24},
    {(int)0xA9C99928, 0xB, 0x24, 0x25},
    {(int)0xABCD0BEE, 0x3, 0x2A, 0x2D},
    {(int)0xAC2C0571, 0x4, 0x13, 0x14},
    {(int)0xAC3B0971, 0x4, 0x14, 0x15},
    {(int)0xACEEBCA5, 0xA, 0x0, 0x1},
    {(int)0xAD38C537, 0x3, 0x9, 0xC},
    {(int)0xAD4B7BE5, 0xA, 0x3D, 0x3E},
    {(int)0xAD4B7BE6, 0xA, 0x3E, 0x3F},
    {(int)0xAEDC6DD7, 0x15, 0x2, 0x3},
    {(int)0xAF5D17FC, 0xA, 0x1B, 0x1C},
    {(int)0xAF5D17FD, 0xA, 0x1C, 0x1D},
    {(int)0xAF9CA282, 0x3, 0x10, 0x13},
    {(int)0xAFA98EB1, 0xB, 0x1C, 0x1D},
    {(int)0xAFA98EB2, 0xB, 0x1D, 0x1E},
    {(int)0xAFA98EB3, 0xB, 0x1E, 0x1F},
    {(int)0xB10454C9, 0x3, 0x1B, 0x1E},
    {(int)0xB2765490, 0x7, 0x0, 0x3},
    {(int)0xB322A271, 0xB, 0x16, 0x17},
    {(int)0xB322A273, 0xB, 0x17, 0x18},
    {(int)0xB441203A, 0x2, 0x17, 0x21},
    {(int)0xB441203E, 0x2, 0x18, 0x22},
    {(int)0xB4728CA0, 0xA, 0xF, 0x10},
    {(int)0xB4728CA1, 0xA, 0x10, 0x11},
    {(int)0xB49DF910, 0xD, 0x5, 0x6},
    {(int)0xB49DF913, 0xD, 0x6, 0x7},
    {(int)0xB58D17AC, 0x3, 0x0, 0x1},
    {(int)0xB6137B93, 0x19, 0x0, 0x3},
    {(int)0xB8F19CA0, 0x3, 0xC, 0xF},
    {(int)0xB90E5B27, 0xD, 0x11, 0x12},
    {(int)0xB90E5B28, 0xD, 0x12, 0x13},
    {(int)0xBA1AD4AD, 0x2, 0x1F, 0x29},
    {(int)0xBA1AD88C, 0x2, 0x20, 0x2A},
    {(int)0xBAD7B203, 0x3, 0x29, 0x2C},
    {(int)0xBAE8703F, 0x3, 0x2B, 0x2E},
    {(int)0xBB9D906F, 0x3, 0x27, 0x2A},
    {(int)0xBE776B91, 0x16, 0x1, 0x2},
    {(int)0xBF0BA657, 0x3, 0x28, 0x2B},
    {(int)0xC1613705, 0x4, 0x33, 0x34},
    {(int)0xC1703B05, 0x4, 0x36, 0x37},
    {(int)0xC46D1DC8, 0x4, 0x3A, 0x3B},
    {(int)0xC5C0B3EC, 0x1, 0x2, 0x5},
    {(int)0xC76F40DD, 0x3, 0x3, 0x5},
    {(int)0xC84E7BA6, 0xA, 0x3, 0x4},
    {(int)0xC9F14690, 0x13, 0x0, 0x1},
    {(int)0xCBFED1AD, 0x3, 0xD, 0x10},
    {(int)0xCFD3587B, 0xA, 0x2F, 0x30},
    {(int)0xCFD3587C, 0xA, 0x30, 0x31},
    {(int)0xD1D729F0, 0x4, 0xA, 0xB},
    {(int)0xD3257BF7, 0x2, 0x4, 0xE},
    {(int)0xD42412E1, 0x3, 0x6, 0x9},
    {(int)0xD5915ACE, 0xB, 0x18, 0x19},
    {(int)0xD5915ACF, 0xB, 0x19, 0x1A},
    {(int)0xD5915AD0, 0xB, 0x1A, 0x1B},
    {(int)0xD5915AD1, 0xB, 0x1B, 0x1C},
    {(int)0xD5BA527E, 0xA, 0x23, 0x24},
    {(int)0xD72D11DC, 0xA, 0x33, 0x34},
    {(int)0xD72D11DD, 0xA, 0x36, 0x37},
    {(int)0xD74A73AA, 0xD, 0x13, 0x14},
    {(int)0xD74A73AB, 0xD, 0x14, 0x15},
    {(int)0xD74A73AC, 0xD, 0x15, 0x16},
    {(int)0xD74A73AE, 0xD, 0x16, 0x17},
    {(int)0xD97320AE, 0x3, 0xF, 0x12},
    {(int)0xDD14E5FC, 0x4, 0x39, 0x3A},
    {(int)0xDDD7E42E, 0x3, 0x1A, 0x1D},
    {(int)0xDF539B39, 0xD, 0xD, 0xE},
    {(int)0xDF539B3A, 0xD, 0xE, 0xF},
    {(int)0xDF78F95F, 0x6, 0x0, 0x1},
    {(int)0xE119AC0A, 0x0, 0x7, 0x9},
    {(int)0xE5B86386, 0xB, 0x12, 0x13},
    {(int)0xE5B86388, 0xB, 0x13, 0x14},
    {(int)0xE946394F, 0x2, 0x1, 0xA},
    {(int)0xEA4E2639, 0xA, 0x39, 0x3A},
    {(int)0xEB3029DC, 0xB, 0x25, 0x26},
    {(int)0xEB3029DD, 0xB, 0x26, 0x27},
    {(int)0xEB3029DE, 0xB, 0x27, 0x28},
    {(int)0xEB3029E2, 0xB, 0x0, 0x1},
    {(int)0xEBE8C583, 0xA, 0x24, 0x25},
    {(int)0xEBE8C584, 0xA, 0x25, 0x26},
    {(int)0xEBE8C585, 0xA, 0x26, 0x27},
    {(int)0xEBE8C586, 0xA, 0x27, 0x28},
    {(int)0xEC0DA0E3, 0xC, 0x0, 0x1},
    {(int)0xEC0DA4BC, 0xC, 0x1, 0x2},
    {(int)0xEE74FCC5, 0x4, 0x11, 0x12},
    {(int)0xEE8400C5, 0x4, 0x12, 0x13},
    {(int)0xEEC9C2BC, 0xD, 0x1F, 0x20},
    {(int)0xEEC9C2BD, 0xD, 0x20, 0x21},
    {(int)0xEEC9C2BE, 0xD, 0x21, 0x22},
    {(int)0xEEC9C2BF, 0xD, 0x0, 0x1},
    {(int)0xEEFF43F5, 0xD, 0xB, 0xC},
    {(int)0xEEFF43F6, 0xD, 0xC, 0xD},
    {(int)0xF01E15D5, 0x2, 0x2, 0xB},
    {(int)0xF0897F3A, 0x3, 0x17, 0x1A},
    {(int)0xF2FC6653, 0x7, 0x2, 0x5},
    {(int)0xF2FC665A, 0x7, 0x1, 0x4},
    {(int)0xF30F7109, 0x3, 0x5, 0x8},
    {(int)0xF31B3204, 0x4, 0x3D, 0x3E},
    {(int)0xF32A3604, 0x4, 0x3E, 0x3F},
    {(int)0xF38D696E, 0x3, 0x12, 0x15},
    {(int)0xF479941B, 0x3, 0x1F, 0x22},
    {(int)0xF4A766D1, 0x16, 0x3, 0x4},
    {(int)0xF5304A2E, 0xB, 0xF, 0x10},
    {(int)0xF5304A31, 0xB, 0x10, 0x11},
    {(int)0xF557E3FF, 0x10, 0x2, 0x3},
    {(int)0xF55B8024, 0x3, 0x21, 0x24},
    {(int)0xF5BC302C, 0xB, 0x11, 0x12},
    {(int)0xFBCD25BA, 0xA, 0x15, 0x16},
    {(int)0xFBCD25BB, 0xA, 0x16, 0x17},
    {(int)0xFC20E272, 0x3, 0x4, 0x7},
    {(int)0xFD1D3820, 0x3, 0xB, 0xE},
    {(int)0xFE1C5E74, 0x3, 0xE, 0x11},
    {(int)0xFFF1D650, 0x8, 0x0, 0x9},
    {(int)0x00EE3DCF, 0xA, 0x1F, 0x20},
    {(int)0x00EE3DD0, 0xA, 0x20, 0x21},
    {(int)0x00EE3DD1, 0xA, 0x21, 0x22},
    {(int)0x00EE3DD2, 0xA, 0x22, 0x23},
    {(int)0x010DBAF9, 0x2, 0x27, 0x31},
    {(int)0x010DBAFB, 0x2, 0x28, 0x32},
    {(int)0x010DBAFD, 0x2, 0x29, 0x33},
    {(int)0x02692FDB, 0x0, 0x4, 0x5},
    {(int)0x0269EFF8, 0x7, 0x3, 0x6},
    {(int)0x03013000, 0x2, 0x3, 0xD},
    {(int)0x035A2F9B, 0x11, 0x0, 0x1},
    {(int)0x056FEDDC, 0x4, 0x17, 0x18},
    {(int)0x057EF1DC, 0x4, 0x18, 0x19},
    {(int)0x07A9587A, 0x12, 0x0, 0x1},
    {(int)0x08762527, 0x4, 0x6, 0x7},
    {(int)0x08852927, 0x4, 0x7, 0x8},
    {(int)0x08B8E034, 0x4, 0x2F, 0x30},
    {(int)0x08C7E434, 0x4, 0x30, 0x31},
    {(int)0x0AE5AA28, 0xA, 0x2E, 0x2F},
    {(int)0x0AF23706, 0xB, 0x14, 0x15},
    {(int)0x0AF23708, 0xB, 0x15, 0x16},
    {(int)0x0C0416B6, 0xA, 0x19, 0x1A},
    {(int)0x0C0416B7, 0xA, 0x1A, 0x1B},
    {(int)0x0D651690, 0x0, 0x5, 0x6},
    {(int)0x107AD6C3, 0xA, 0x17, 0x18},
    {(int)0x107AD6C4, 0xA, 0x18, 0x19},
    {(int)0x110100E2, 0x14, 0x0, 0x3},
    {(int)0x1166C5A4, 0x2, 0x2D, 0x37},
    {(int)0x121BF201, 0x4, 0x41, 0x42},
    {(int)0x122AF601, 0x4, 0x40, 0x41},
    {(int)0x14E06D78, 0x2, 0x10, 0x1A},
    {(int)0x14E3E0DC, 0xA, 0x44, 0x45},
    {(int)0x15C19FE5, 0x4, 0x37, 0x38},
    {(int)0x167F3C80, 0x3, 0xA, 0xD},
    {(int)0x16DC41F0, 0xB, 0x7, 0x8},
    {(int)0x16DC41F4, 0xB, 0x8, 0x9},
    {(int)0x17761679, 0x4, 0x31, 0x32},
    {(int)0x1783DD03, 0x15, 0x1, 0x2},
    {(int)0x17851A79, 0x4, 0x32, 0x33},
    {(int)0x185E88DF, 0xA, 0x28, 0x29},
    {(int)0x185E88E0, 0xA, 0x29, 0x2A},
    {(int)0x185E88E1, 0xA, 0x2A, 0x2B},
    {(int)0x185E88E2, 0xA, 0x2B, 0x2C},
    {(int)0x194C34DA, 0xA, 0x4, 0x5},
    {(int)0x194C34DB, 0xA, 0x5, 0x6},
    {(int)0x1AC42B95, 0x2, 0xD, 0x17},
    {(int)0x1C9F3A03, 0x3, 0x1C, 0x1F},
    {(int)0x1D6B32D4, 0x2, 0x14, 0x1E},
    {(int)0x1DB440C5, 0x4, 0x2, 0x3},
    {(int)0x1E500061, 0xA, 0xA, 0xB},
    {(int)0x1EE0C60C, 0x16, 0x5, 0x6},
    {(int)0x1FA10E51, 0x2, 0x16, 0x20},
    {(int)0x1FF3E786, 0x3, 0x23, 0x26},
    {(int)0x1FFE489D, 0x2, 0x13, 0x1D},
    {(int)0x219E0562, 0x3, 0x1E, 0x21},
    {(int)0x219E0563, 0x3, 0x1D, 0x20},
    {(int)0x2208AC98, 0x4, 0x0, 0x1},
    {(int)0x22E12B37, 0x15, 0x3, 0x4},
    {(int)0x2677B69B, 0x3, 0x24, 0x27},
    {(int)0x26D11224, 0x4, 0x1D, 0x1E},
    {(int)0x26E01624, 0x4, 0x1E, 0x1F},
    {(int)0x2769D564, 0x2, 0x1E, 0x28},
    {(int)0x285BFA4B, 0x4, 0x1F, 0x20},
    {(int)0x286AFE4B, 0x4, 0x20, 0x21},
    {(int)0x287A024B, 0x4, 0x21, 0x22},
    {(int)0x2889064B, 0x4, 0x22, 0x23},
    {(int)0x28959CF0, 0x10, 0x3, 0x4},
    {(int)0x2B1153AC, 0x2, 0xF, 0x19},
    {(int)0x2B1B4B57, 0x4, 0xD, 0xE},
    {(int)0x2B2A4F57, 0x4, 0xE, 0xF},
    {(int)0x2B54A9D1, 0x0, 0x8, 0xA},
    {(int)0x2C8CA60C, 0x0, 0xC, 0xE},
    {(int)0x2D01F45C, 0xA, 0x2D, 0x2E},
    {(int)0x2D1FEB94, 0x3, 0x16, 0x19},
    {(int)0x2D6C9F33, 0xA, 0xC, 0xD},
    {(int)0x2D6C9F34, 0xA, 0xB, 0xC},
    {(int)0x2D93FE29, 0x3, 0x15, 0x18},
    {(int)0x2E10CD7F, 0x0, 0xD, 0xF},
    {(int)0x2E337AF8, 0x17, 0x0, 0x1},
    {(int)0x336B7C12, 0x3, 0x25, 0x28},
    {(int)0x33C5007A, 0x4, 0x23, 0x24},
    {(int)0x33DD9B7C, 0x4, 0x2C, 0x2D},
    {(int)0x34311573, 0x10, 0x0, 0x1},
    {(int)0x34A644F7, 0x4, 0xF, 0x10},
    {(int)0x34B548F7, 0x4, 0x10, 0x11},
    {(int)0x356D8EAE, 0x4, 0x44, 0x45},
    {(int)0x381ABB7E, 0x3, 0x2, 0x4},
    {(int)0x3843B57C, 0xA, 0x42, 0x43},
    {(int)0x3843B57D, 0xA, 0x43, 0x44},
    {(int)0x3A4E0D26, 0xD, 0x7, 0x8},
    {(int)0x3A4E0D2A, 0xD, 0x8, 0x9},
    {(int)0x3B7A9A11, 0x15, 0x0, 0x1},
    {(int)0x3B95D895, 0xA, 0x3F, 0x40},
    {(int)0x3D7D601C, 0x2, 0xE, 0x18},
    {(int)0x3DCA96B0, 0x2, 0x2C, 0x36},
    {(int)0x3E3F9E46, 0x4, 0x2E, 0x2F},
    {(int)0x3E57DB4B, 0xA, 0x6, 0x7},
    {(int)0x3E57DB4C, 0xA, 0x7, 0x8},
    {(int)0x3EA5F097, 0x4, 0x24, 0x25},
    {(int)0x3EB4F497, 0x4, 0x25, 0x26},
    {(int)0x3EC3F897, 0x4, 0x26, 0x27},
    {(int)0x3ED2FC97, 0x4, 0x27, 0x28},
    {(int)0x40F3290B, 0x2, 0x9, 0x13},
    {(int)0x416B228D, 0xD, 0x1, 0x2},
    {(int)0x416B2293, 0xD, 0x2, 0x3},
    {(int)0x4351EDF4, 0x4, 0xC, 0xD},
    {(int)0x4360F1F4, 0x4, 0xB, 0xC},
    {(int)0x43934737, 0xA, 0x11, 0x12},
    {(int)0x43934738, 0xA, 0x12, 0x13},
    {(int)0x43E25BFD, 0x4, 0x8, 0x9},
    {(int)0x43F15FFD, 0x4, 0x9, 0xA},
    {(int)0x43F9FD12, 0x10, 0x1, 0x2},
    {(int)0x44455EBE, 0x4, 0x1B, 0x1C},
    {(int)0x445462BE, 0x4, 0x1C, 0x1D},
    {(int)0x4498EA6A, 0xF, 0x1, 0x2},
    {(int)0x4498EA6B, 0xF, 0x2, 0x3},
    {(int)0x4498EA6C, 0xF, 0x3, 0x4},
    {(int)0x4498EA6D, 0xF, 0x4, 0x5},
    {(int)0x4498EA6E, 0xF, 0x5, 0x6},
    {(int)0x4498EA6F, 0xF, 0x0, 0x1},
    {(int)0x46BCCFD5, 0xA, 0x13, 0x14},
    {(int)0x46BCCFD6, 0xA, 0x14, 0x15},
    {(int)0x46F3445E, 0xA, 0x2C, 0x2D},
    {(int)0x46F88E83, 0x18, 0x0, 0x4},
    {(int)0x47D206E2, 0x3, 0x14, 0x17},
    {(int)0x47DF0CDD, 0xE, 0x1, 0x2},
    {(int)0x48549723, 0xA, 0x3B, 0x3C},
    {(int)0x48549724, 0xA, 0x3C, 0x3D},
    {(int)0x491313FC, 0x2, 0x8, 0x12},
    {(int)0x491AECF4, 0x0, 0xA, 0xC},
    {(int)0x4989F7B6, 0x4, 0x34, 0x35},
    {(int)0x4998FBB6, 0x4, 0x35, 0x36},
    {(int)0x49E98B28, 0x5, 0x0, 0x1},
    {(int)0x4B4D78FE, 0xE, 0x0, 0x1},
    {(int)0x4B566FB0, 0xA, 0x41, 0x42},
    {(int)0x4B566FB1, 0xA, 0x40, 0x41},
    {(int)0x4B9D29C8, 0xA, 0x38, 0x39},
    {(int)0x4DF559B9, 0x2, 0x5, 0xF},
    {(int)0x4DF559BA, 0x2, 0x6, 0x10},
    {(int)0x4DF559BB, 0x2, 0x7, 0x11},
    {(int)0x4F4B61C4, 0x0, 0xE, 0x11},
    {(int)0x5215BE71, 0xD, 0x23, 0x24},
    {(int)0x5215BE72, 0xD, 0x22, 0x23},
    {(int)0x52C5BD52, 0x15, 0x4, 0x5},
    {(int)0x5439474E, 0x0, 0x9, 0xB},
    {(int)0x55ECECA0, 0x1, 0x0, 0x2},
    {(int)0x56E21F7C, 0x3, 0x7, 0xA},
    {(int)0x57F7511B, 0x3, 0x20, 0x23},
    {(int)0x5E1D9179, 0xD, 0x9, 0xA},
    {(int)0x5E1D917A, 0xD, 0xA, 0xB},
    {(int)0x61531656, 0x0, 0x3, 0x4},
    {(int)0x618D35F7, 0x2, 0x24, 0x2E},
    {(int)0x618D35FD, 0x2, 0x25, 0x2F},
    {(int)0x618D35FE, 0x2, 0x26, 0x30},
    {(int)0x6198E155, 0x3, 0x11, 0x14},
    {(int)0x626F047C, 0x0, 0xB, 0xD},
    {(int)0x6278FC62, 0x16, 0x0, 0x1},
    {(int)0x62F44199, 0x2, 0x11, 0x1B},
    {(int)0x65D9D3D5, 0xA, 0x2, 0x3},
    {(int)0x66024850, 0x4, 0x1, 0x2},
    {(int)0x672E672D, 0x0, 0x12, 0x15},
    {(int)0x67D37603, 0x0, 0x11, 0x14},
    {(int)0x69A84144, 0x2, 0x23, 0x2D},
    {(int)0x6C3989D2, 0x15, 0x5, 0x6},
    {(int)0x6CA10548, 0xB, 0x3, 0x4},
    {(int)0x6CA1054C, 0xB, 0x4, 0x5},
    {(int)0x6D4279E6, 0x2, 0x2B, 0x35},
    {(int)0x6D57B6BA, 0xA, 0x34, 0x35},
    {(int)0x6D57B6BB, 0xA, 0x35, 0x36},
    {(int)0x6EEDE0DD, 0x9, 0x0, 0x4},
    {(int)0x6F70EC95, 0xD, 0x3, 0x4},
    {(int)0x6F70EC9B, 0xD, 0x4, 0x5},
    {(int)0x6FB35C8E, 0x17, 0x2, 0x3},
    {(int)0x747EAA3A, 0x2, 0x15, 0x1F},
    {(int)0x74B3CF9C, 0x2, 0x19, 0x23},
    {(int)0x74B3D37D, 0x2, 0x1A, 0x24},
    {(int)0x74B3D75A, 0x2, 0x1B, 0x25},
    {(int)0x74B3D761, 0x2, 0x1C, 0x26},
    {(int)0x74B3DB3C, 0x2, 0x1D, 0x27},
    {(int)0x74EBA116, 0x4, 0x4, 0x5},
    {(int)0x74FAA516, 0x4, 0x5, 0x6},
    {(int)0x75922D82, 0x2, 0x12, 0x1C},
    {(int)0x77176556, 0x3, 0x13, 0x16},
    {(int)0x779A2016, 0x4, 0x3, 0x4},
    {(int)0x77E28A33, 0x4, 0x42, 0x43},
    {(int)0x77F18E33, 0x4, 0x43, 0x44},
    {(int)0x7889FE2F, 0xA, 0x31, 0x32},
    {(int)0x7889FE30, 0xA, 0x32, 0x33},
    {(int)0x794AADFF, 0x16, 0x4, 0x5},
    {(int)0x796596C6, 0x2, 0x21, 0x2B},
    {(int)0x796596CC, 0x2, 0x22, 0x2C},
    {(int)0x7B029BD3, 0xE, 0x3, 0x4},
    {(int)0x7C33842D, 0x0, 0x0, 0x1},
    {(int)0x7D29BB8B, 0xE, 0x2, 0x3},
    {(int)0x7E6FD0CC, 0xD, 0xF, 0x10},
    {(int)0x7E6FD0D3, 0xD, 0x10, 0x11},
    {(int)0x7F0A49B1, 0xA, 0x37, 0x38},
};

Unk020a267c *func_020a2994();
void func_020a29a4(Unk020a267c *p);
void func_020a29c8(Unk020a267c *p);
void func_020a23cc(Unk020a22fcElement *e, int index);
Unk020a22fcSlot *func_020a290c(Unk020a267c *p, int owner);
void func_020a2964(Unk020a267c *p, Unk020a22fcSlot *slot, bool release);
int func_020a2a00(Unk020a267c *p, int volume, int offset);
int func_020a2c14(Unk020a267c *p, int hash, int *group, int *id, int *unk);
int func_020a2ce8(Unk020a267c *p, int hash, int volume, bool immediate);
int func_020a2e34(Unk020a267c *p, int group);
int func_020a30bc(Unk020a267c *p, void *handle, int a, int b, int c, u8 *info, u8 *file, int d, int e);
int func_020a3188(Unk020a267c *p, int hash, void *heap);
int func_020a32ac(Unk020a267c *p, int hash, void *heap, int volume, bool immediate);
bool func_020a3478(Unk020a267c *p, int handle);
void func_020a34e4(Unk020a267c *p, int handle);
bool func_020a3514(Unk020a267c *p, int handle);
void func_020a3734(Unk020a267c *p, int fade);
void func_020a3798(Unk020a267c *p);
void func_020a3934(Unk020a267c *p, u8 index);
void func_020a38e8(Unk020a267c *p);
int func_020a39f0(Unk020a267c *p);
void func_020a3a1c(Unk020a267c *p);
void func_020a24b0(Unk020a22fcElement *e);
void func_020a25fc(Unk020a22fcElement *e);
void func_020a2630(Unk020a22fcElement *e, int volume, int unused);
void func_020a24fc(Unk020a22fcElement *e);
void func_020a2354(void *p, int unused, void *lock, int file);
void func_020a2374(void *p, u32 size, void *owner, int index);
void func_020a23bc();

}

static Unk020a267c *data_020d6c68;
static u32 data_020d6c6c[10];
static Unk020a22fcHeader data_020d6c94;

extern "C" void func_020a22fc(void *p, void *lock, int file) {
    void *old;
    if (lock == 0) {
        return;
    }
    int state = OS_DisableInterrupts();
    old = (void *)func_0209be08(lock);
    if (p == NNS_SndArcGetFileAddress(file)) {
        func_0209b9a0(file, 0);
    }
    func_0209be08(old);
    OS_RestoreInterrupts(state);
}

extern "C" void func_020a2354(void *p, int unused, void *lock, int file) {
    func_020a22fc(p, lock, file);
    SND_DestroyWaveArc(p);
}

extern "C" void func_020a2374(void *p, u32 size, void *owner, int index) {
    if (p == func_0207e074(owner, index)) {
        func_0207e0bc(owner, index, 0);
    }
    SND_InvalidateWaveData(p, (u8 *)p + size);
}

extern "C" void func_020a23bc() {
    func_020a29a4(func_020a2994());
}

extern "C" void func_020a23cc(Unk020a22fcElement *e, int owner) {
    e->delay = -1;
    e->flags = 0;
    e->sound = 0;
    e->handle = -1;
    e->owner = owner;
}

extern "C" bool func_020a23ec(Unk020a22fcElement *e, int sound, bool loop, int delay, bool streamed) {
    Unk020a22fcSlot *slot = func_020a290c(func_020a2994(), 4);
    if (slot != 0) {
        e->slot = slot;
        e->delay = delay;
        e->sound = sound;
        e->speed = 0x400;
        e->handle = -1;
        e->unk1c = -1;
        e->unk1c = func_020a3188(func_020a2994(), e->sound, e->slot->heap);
        if (e->unk1c == -1) {
            func_020a2964(func_020a2994(), slot, true);
            return false;
        }
        e->flags |= 6;
        if (streamed) {
            e->flags |= 0xc0;
        }
        if (loop) {
            e->flags |= 8;
        }
        return true;
    }
    return false;
}

extern "C" void func_020a24b0(Unk020a22fcElement *e) {
    e->flags = 0x100;
    int handle = e->handle;
    if (handle != -1) {
        if (func_020a3514(func_020a2994(), handle)) {
            func_020a34e4(func_020a2994(), e->handle);
            e->handle = -1;
        }
    }
}

extern "C" void func_020a24fc(Unk020a22fcElement *e) {
    Unk020a267c *p = func_020a2994();
    if (e->flags & 0x100) {
        return;
    }
    if (!(e->flags & 2)) {
        return;
    }
    if (e->flags & 0x20) {
        if (e->flags & 8) {
            return;
        }
        if (e->handle == -1) {
            return;
        }
        if (func_020a3514(p, e->handle)) {
            return;
        }
        func_020a24b0(e);
        return;
    }
    if (e->delay < 0) {
        return;
    }
    e->delay -= e->speed >> 8;
    if (e->delay > 0) {
        return;
    }
    if (e->sound != 0) {
        if (e->flags & 4) {
            e->handle = func_020a32ac(p, e->sound, e->slot->heap, 0x7f, false);
        } else {
            e->handle = func_020a2ce8(p, e->sound, 0x7f, false);
        }
        e->flags |= 0x20;
    }
    e->delay = -1;
}

extern "C" void func_020a25fc(Unk020a22fcElement *e) {
    e->handle = -1;
    e->flags = 0;
    func_020a2964(func_020a2994(), e->slot, true);
    e->slot = 0;
}

extern "C" void func_020a2630(Unk020a22fcElement *e, int volume, int unused) {
    if (!(e->flags & 2)) {
        return;
    }
    e->volume = volume;
    int handle = e->handle;
    if (handle != -1) {
        func_0209b094(&func_020a2994()->handles[handle >> 16], 0xffff, e->volume);
    }
}

Unk020a267c::Unk020a267c(const char *path, u32 size)
    : musicId(0), unkd4(0), slotsReady(false), unk1a1(false), heapLevel(0) {
    func_0207c124();
    func_0207bff0(data_020d6c6c);
    func_0209a7bc();
    buffer = new u8[size];
    heap = func_0209c424(buffer, size);
    func_0209c03c(archive, path, heap, 0);
    NNS_SndArcPlayerSetup(heap);
    func_0209b16c(&music);
    func_0209e654(10, heap);
    func_0209e56c(stream);
    for (u8 i = 0; i < 12; i++) {
        func_0209b16c(&handles[i]);
    }
    func_020a29c8(this);
    func_0209c280(heap);
    for (u8 i = 0; i < 4; i++) {
        func_020a23cc(&elements[i], i);
    }
    for (u32 i = 0; i < 0x20; i++) {
        volumes[i] = 0x7f;
    }
    unk178 = 0;
    unk17c = 0;
}

extern "C" void func_020a27f4(Unk020a267c *p) {
    if (data_020d6c68 == 0) {
        return;
    }
    if (p->slotsReady) {
        return;
    }
    for (u32 i = 0; i < 4; i++) {
        p->slots[i].buffer = new u8[0x10400];
        p->slots[i].heap = func_0209c424(p->slots[i].buffer, 0x10400);
    }
    p->slotsReady = true;
}

extern "C" void func_020a2864(const char *path, u32 size) {
    if (data_020d6c68 != 0) {
        return;
    }
    data_020d6c68 = new Unk020a267c(path, size);
}

extern "C" void func_020a28ac() {
    func_0207bf58(data_020d6c6c, 0x60, 0x14, func_020a23bc, 0);
}

extern "C" void func_020a28d8() {
    func_0207beb8(data_020d6c6c);
}

extern "C" void func_020a28ec(Unk020a267c *p) {
    func_0209d0b8(0, p->heap);
    func_0209c280(p->heap);
}

extern "C" Unk020a22fcSlot *func_020a290c(Unk020a267c *p, int owner) {
    if (!p->slotsReady) {
        return 0;
    }
    for (u32 i = 0; i != 4; i++) {
        if (!p->slots[i].used) {
            p->slots[i].used = true;
            p->slots[i].owner = owner;
            return &p->slots[i];
        }
    }
    return 0;
}

extern "C" void func_020a2964(Unk020a267c *p, Unk020a22fcSlot *slot, bool release) {
    if (slot == 0) {
        return;
    }
    func_0209c194(slot->heap, 0);
    if (release) {
        slot->used = false;
    }
}

extern "C" Unk020a267c *func_020a2994() {
    return data_020d6c68;
}

extern "C" void func_020a29a4(Unk020a267c *p) {
    func_020a38e8(p);
    func_020a3a1c(p);
    func_020a3798(p);
    func_0209a788();
}

extern "C" void func_020a29c8(Unk020a267c *p) {
    p->unke0 = 0x1000;
    p->unkdc = 0;
    p->unkd8 = 0;
    p->unke4 = 0x100;
}

extern "C" int func_020a29e8(Unk020a267c *p, int volume, int factor) {
    int v = (volume * factor) >> 12;
    if (v < 0) {
        v = 0;
    }
    if (v > 0x7f) {
        v = 0x7f;
    }
    return v;
}

extern "C" int func_020a2a00(Unk020a267c *p, int volume, int offset) {
    volume += offset;
    if (volume < -0x8000) {
        volume = -0x8000;
    }
    if (volume > 0x7fff) {
        volume = 0x7fff;
    }
    return volume;
}

extern "C" void *func_020a2a2c(Unk020a267c *p, int file, void *heap, bool lock) {
    u32 total;
    void *data = NNS_SndArcGetFileAddress(file);
    if (data == 0) {
        if (func_0209ba04(file, &data_020d6c94, 0x3c, 0) != 0x3c) {
            return 0;
        }
        u32 size = data_020d6c94.count << 2;
        total = size << 1;
        if (heap == 0) {
            return 0;
        }
        void *locked;
        if (lock) {
            locked = func_0209bdf8();
        } else {
            locked = 0;
        }
        data = func_0209c2d8(heap, total + 0x5c, (void *)func_020a2354, locked, file);
        if (data == 0) {
            return 0;
        }
        int got = func_0209ba04(file, data, size + 0x3c, 0);
        if (got != size + 0x3c) {
            return 0;
        }
        Unk020a22fcHeader *header = (Unk020a22fcHeader *)data;
        MI_CpuCopy8((u8 *)data + 0x3c, (u8 *)data + 0x3c + (header->count << 2), size);
        MI_CpuFill8((u8 *)data + 0x3c, 0, size);
        DC_StoreRange(data, total + 0x3c);
        if (lock) {
            func_0209b9a0(file, data);
        }
    }
    return data;
}

extern "C" bool func_020a2b38(Unk020a267c *p, u8 *table, u32 index, int file, void *heap) {
    u32 size;
    u32 count = func_0207e0f4(table);
    u32 end;
    if (index > count) {
        return false;
    }
    if (func_0207e074(table, index) != 0) {
        return true;
    }
    int *entry = (int *)table + (*(int *)(table + 0x38) + index);
    int offset = entry[0xf];
    end = index < count - 1 ? entry[0x10] : *(int *)(table + 8);
    size = end - offset;
    if (0 == heap) {
        return false;
    }
    void *data = func_0209c2d8(heap, size + 0x20, (void *)func_020a2374, table, index);
    if (data == 0) {
        return false;
    }
    if (size != func_0209ba04(file, data, size, offset)) {
        return false;
    }
    DC_StoreRange(data, size);
    func_0207e0bc(table, index, data);
    return true;
}

extern "C" int func_020a2c14(Unk020a267c *p, int hash, int *group, int *id, int *unk) {
    int lo = 0;
    int hi = 0x175;
    do {
        int mid = lo + ((hi - lo) >> 1);
        const Unk020a22fcSound *s = &data_020b5b84[mid];
        if (hash > s->hash) {
            lo = mid + 1;
        } else if (hash < s->hash) {
            hi = mid - 1;
        } else {
            *group = s->group;
            *id = s->id;
            *unk = s->unk8;
            return 1;
        }
    } while (lo <= hi);
    *group = -1;
    *id = -1;
    *unk = 0;
    return 0;
}

extern "C" int func_020a2c9c(Unk020a267c *p) {
    int i = 0;
    bool found = false;
    while (!found && i < 12) {
        Unk020a22fcPlayer *player = p->handles[i];
        if (player == 0 || player->active == 0) {
            found = true;
        } else {
            i++;
        }
    }
    if (i == 12) {
        return -1;
    }
    return i;
}

extern "C" int func_020a2ce8(Unk020a267c *p, int hash, int volume, bool immediate) {
    int group;
    int id;
    int unk;
    int index = func_020a2c9c(p);
    if (index == -1) {
        func_020897b4("  - Could not start playing sound effect, all channels full.");
        return -1;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4("Could not find sound to match hash %i", hash);
        return -1;
    }
    int seq = func_020a2e34(p, group);
    void *handle = &p->handles[index];
    if (NNS_SndArcPlayerStartSeqArc(handle, seq, id) != 0) {
        func_0209b0c4(handle, 0xffff, volume);
        if (immediate) {
            func_0209b094(handle, 0xffff, 0);
            func_0209b064(handle, 0x100);
        } else {
            func_0209b094(handle, 0xffff, func_020a2a00(p, 0, p->unkd8));
            func_0209b064(handle, p->unke4);
        }
        return (index << 16) + (seq << 8) + id;
    }
    func_020897b4("  - Could not start playing sound effect, Nitro error. Check if sound effect exists and archive built properly.");
    return -1;
}

extern "C" int func_020a2e34(Unk020a267c *p, int group) {
    Unk020a22fcList *list = func_0209bad8(group);
    int result = -1;
    u32 i = 0;
    if (list->count != 0) {
    Unk020a22fcEntry *entry = list->entries;
    do {
        switch (entry->type) {
        case 3:
            if (NNS_SndArcGetFileAddress(*func_0209bd30(entry->id)) == 0) {
                func_0209cdf4(entry->id, entry->unk1, p->heap, 1, 0);
            }
            result = entry->id;
            break;
        case 1:
            if (NNS_SndArcGetFileAddress(*func_0209bccc(entry->id)) == 0) {
                func_0209cc94(entry->id, entry->unk1, p->heap, 1, 0);
            }
            break;
        }
        i++;
        entry++;
    } while (i != list->count);
    }
    return result;
}

extern "C" void func_020a2f04(Unk020a267c *p, int id, void *heap) {
    func_0209bd30(id);
    NNS_SndArcLoadBank(id, heap);
}

extern "C" void func_020a2f28(Unk020a267c *p, int id, void *heap) {
    int *entry = func_0209bccc(id);
    Unk020a22fcFile *info = func_0209bc68(*(u16 *)(entry + 1));
    func_020a2a2c(p, info->id, heap, true);
    func_0209d050(id, 2, heap);
}

extern "C" void func_020a2f7c(Unk020a267c *p, int id, int index, void *heap) {
    u16 out[6];
    int *entry = func_0209bccc(id);
    u8 *table = (u8 *)NNS_SndArcGetFileAddress(*entry);
    if (table == 0) {
        return;
    }
    Unk020a22fcFile *info = func_0209bc68(*(u16 *)(entry + 1));
    u8 *data = (u8 *)NNS_SndArcGetFileAddress(info->id);
    if (func_0207e2f4(table, index, 0, out) == 0) {
        return;
    }
    func_020a2b38(p, data, out[1], info->id, heap);
}

extern "C" int func_020a3018(Unk020a267c *p, void *handle, int id, int index) {
    if (func_020a2c9c(p) == -1) {
        return 0;
    }
    int *entry = func_0209bd30(id);
    if (entry == 0) {
        return 0;
    }
    u8 *file = (u8 *)NNS_SndArcGetFileAddress(*entry);
    if (file == 0) {
        return 0;
    }
    u8 *info = (u8 *)NNSi_SndSeqArcGetSeqInfo(file, index);
    if (info == 0) {
        return 0;
    }
    return func_020a30bc(p, handle, info[9], *(u16 *)(info + 4), info[8], info, file, id, index);
}

extern "C" int func_020a30bc(Unk020a267c *p, void *handle, int a, int b, int c, u8 *info, u8 *file, int d, int e) {
    int out;
    void *seq = func_0209ad38(handle, a, c);
    if (seq == 0) {
        return 0;
    }
    if (func_0209cc94(b, 2, func_0209ac14(a, seq), 0, &out) != 0) {
        func_0209ad2c(seq);
        return 0;
    }
    func_0209acd0(seq, file + *(int *)(file + 0x18), *(int *)info, out);
    func_0209b134(handle, info[6]);
    func_0209b104(handle, info[7]);
    func_0209b020(handle, d, e);
    return 1;
}

/* Replaces group 10 by group 4 when the player's outfit has no value at 0x28. */
static inline void func_group(int *group) {
    if (*group == 10) {
        bool none = func_020081dc(data_020c43a8).unk28 == 0;
        if (none) {
            *group = 4;
        }
    }
}

extern "C" int func_020a3188(Unk020a267c *p, int hash, void *heap) {
    int group;
    int id;
    int unk;
    if (heap == 0) {
        heap = p->heap;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4("Could not find sound to match hash %i", hash);
        return -1;
    }
    func_group(&group);
    Unk020a22fcList *list = func_0209bad8(group);
    u32 i = 0;
    if (list->count != 0) {
    Unk020a22fcEntry *entry = list->entries;
    do {
        switch (entry->type) {
        case 3:
            func_020a2f04(p, entry->id, heap);
            break;
        case 1:
            func_020a2f28(p, entry->id, heap);
            func_020a2f7c(p, entry->id, unk, heap);
            break;
        }
        i++;
        entry++;
    } while (i != list->count);
    }
    return group;
}

extern "C" int func_020a32ac(Unk020a267c *p, int hash, void *heap, int volume, bool immediate) {
    int result = -1;
    int group;
    int id;
    int unk;
    int index = func_020a2c9c(p);
    if (index == result) {
        func_020897b4("  - Could not start playing sound effect, all channels full.");
        return result;
    }
    if (!func_020a2c14(p, hash, &group, &id, &unk)) {
        func_020897b4("Could not find sound to match hash %i", hash);
        return result;
    }
    func_group(&group);
    Unk020a22fcList *list = func_0209bad8(group);
    u32 i = 0;
    int count = list->count;
    if (count != 0) {
        Unk020a22fcEntry *entry = list->entries;
        do {
            if (entry->type == 3) {
                result = entry->id;
            }
            i++;
            entry++;
        } while (i != count);
    }
    if (result == -1) {
        return -1;
    }
    void *handle = &p->handles[index];
    if (func_020a3018(p, handle, result, id) != 0) {
        func_0209b0c4(handle, 0xffff, volume);
        if (immediate) {
            func_0209b094(handle, 0xffff, 0);
            func_0209b064(handle, 0x100);
        } else {
            func_0209b094(handle, 0xffff, func_020a2a00(p, 0, p->unkd8));
            func_0209b064(handle, p->unke4);
        }
        return (index << 16) + (result << 8) + id;
    }
    func_020897b4("  - Could not start playing sound effect, Nitro error. Check if sound effect exists and archive built properly.");
    return -1;
}

/* 98.70 %: lr / r12 swapped (player and the first test). The result is set only
 * when the test holds (moveq #1 without movne #0). */
extern "C" bool func_020a3478(Unk020a267c *p, int handle) {
    u8 index = handle >> 16;
    if (handle < 0 || index >= 12) {
        return false;
    }
    Unk020a22fcPlayer *player = p->handles[index];
    bool result = false;
    bool same = false;
    if (player != 0) {
        same = (u8)(handle >> 8) == player->unk38;
    }
    if (same && (handle & 0xff) == player->unk3a) {
        result = true;
    }
    return result;
}

extern "C" void func_020a34e4(Unk020a267c *p, int handle) {
    if (func_020a3514(p, handle)) {
        func_0209b1e0(&p->handles[handle >> 16], 0);
    }
}

extern "C" bool func_020a3514(Unk020a267c *p, int handle) {
    bool result = false;
    if (func_020a3478(p, handle)) {
        result = p->handles[handle >> 16]->active != 0;
    }
    return result;
}

extern "C" void func_020a3550(Unk020a267c *p, int handle, int value) {
    if (func_020a3478(p, handle)) {
        func_0209b144(&p->handles[handle >> 16], value);
    }
}

extern "C" void func_020a3584(Unk020a267c *p, int index, int value) {
    p->volumes[index] = value;
    func_0209b2c8(index, value);
}

extern "C" void func_020a35a4(Unk020a267c *p, int handle, int volume) {
    if (func_020a3478(p, handle)) {
        func_0209b094(&p->handles[handle >> 16], 0xffff, func_020a2a00(p, volume, p->unkd8));
    }
}

extern "C" void func_020a35f0(Unk020a267c *p, int hash, int mode) {
    int group;
    int id;
    int unk;
    if (func_020a2c14(p, hash, &group, &id, &unk)) {
        if (p->musicId == hash) {
            return;
        }
        func_020a3734(p, 0);
        p->heapLevel = func_0209c188(p->heap);
        bool started;
        switch (mode) {
        case 1:
            if (NNS_SndArcGetFileAddress(*func_0209bd94(id)) == 0) {
                func_020897b4("  - Loading audio group.");
                func_0209d0b8(group, p->heap);
            }
            started = NNS_SndArcPlayerStartSeq(&p->music, id) != 0;
            break;
        case 0:
            started = NNS_SndArcPlayerStartSeqArc(&p->music, func_020a2e34(p, group), id) != 0;
            break;
        }
        if (started) {
            func_0209b094(&p->music, 0xffff, p->unkdc);
            func_0209b064(&p->music, p->unke4);
            p->musicId = hash;
            func_0209c280(p->heap);
            return;
        }
        func_020897b4("  - Could not start playing music, Nitro error. Check if music exists and archive built properly.");
        return;
    }
    func_020897b4("Could not find song to match hash %i", hash);
}

extern "C" void func_020a3734(Unk020a267c *p, int fade) {
    if (p->musicId == 0 || p->music->active == 0) {
        return;
    }
    if (fade == 0) {
        func_0209b1e0(&p->music, 0);
        p->musicId = 0;
        func_0209c194(p->heap, p->heapLevel);
    } else {
        func_0209b1e0(&p->music, fade);
        p->unk1a1 = true;
    }
}

extern "C" void func_020a3798(Unk020a267c *p) {
    if (!p->unk1a1 || p->musicId == 0) {
        return;
    }
    if (p->music != 0) {
        return;
    }
    p->musicId = 0;
    func_0209c194(p->heap, p->heapLevel);
    p->unk1a1 = false;
}

extern "C" void func_020a37e8(Unk020a267c *p, u32 level) {
    if ((u32)func_0209c188(p->heap) >= level) {
        func_0209c194(p->heap, level);
    }
}

extern "C" Unk020a22fcElement *func_020a3814(Unk020a267c *p) {
    for (u32 i = 0; i != 4; i++) {
        if (!(p->elements[i].flags & 2) && !(p->elements[i].flags & 0x100)) {
            return &p->elements[i];
        }
    }
    return 0;
}

extern "C" Unk020a22fcElement *func_020a3858(Unk020a267c *p, int sound, bool loop, bool streamed, int delay) {
    Unk020a22fcElement *e = func_020a3814(p);
    if (e != 0 && func_020a23ec(e, sound, loop, delay, streamed)) {
        return e;
    }
    return 0;
}

extern "C" void func_020a389c(Unk020a267c *p, int owner) {
    for (u8 i = 0; i < 4; i++) {
        Unk020a22fcElement *e = &p->elements[i];
        if ((e->flags & 2) && (owner == 0 || owner == e->owner)) {
            func_020a24b0(e);
        }
    }
}

extern "C" void func_020a38e8(Unk020a267c *p) {
    Unk020a22fcElement *e;
    for (u8 i = 0; i < 4; i++) {
        e = &p->elements[i];
        func_020a24fc(e);
        if (e->flags & 0x100) {
            func_020a3934(p, i);
        }
    }
}

extern "C" void func_020a3934(Unk020a267c *p, u8 index) {
    int unk = p->elements[index].unk1c;
    bool last = true;
    for (u8 i = 0; i < 4; i++) {
        if (i != index) {
            Unk020a22fcElement *e = &p->elements[i];
            if ((e->flags & 2) && unk == e->unk1c) {
                last = false;
            }
        }
    }
    if (last) {
        func_020a25fc(&p->elements[index]);
    }
}

extern "C" void func_020a39a8(Unk020a267c *p, int volume, int unused) {
    for (u8 i = 0; i < 4; i++) {
        Unk020a22fcElement *e = &p->elements[i];
        if (e->flags & 0x80) {
            func_020a2630(e, volume, unused);
        }
    }
}

extern "C" int func_020a39f0(Unk020a267c *p) {
    if (p->unkd4 != 0 && func_0209e520(p->stream) != 0) {
        return 1;
    }
    return 0;
}

extern "C" void func_020a3a1c(Unk020a267c *p) {
    if (p->unkd4 != 0 && func_020a39f0(p) == 0) {
        p->unkd4 = 0;
    }
}
