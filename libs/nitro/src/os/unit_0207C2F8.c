/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef struct { u8 language, color, month, day; u16 nick[10]; u16 nickLen; u16 comment[26]; u16 commentLen; } Info;
typedef struct { u8 a[2]; u8 color : 4; u8 : 4; u8 month, day; u8 pad; u16 nick[10]; u8 nickLen; u8 b; u16 comment[26]; u8 commentLen; u8 c[0x13]; u16 lang : 3; u16 : 13; } Cfg;
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
void func_0207c2f8(Info *info) {
    Cfg *p = (Cfg *)0x027ffc80;
    info->language = p->lang;
    info->color = p->color;
    info->month = p->month;
    info->day = p->day;
    info->nickLen = p->nickLen;
    info->commentLen = p->commentLen;
    MIi_CpuCopy16(p->nick, info->nick, 0x14);
    MIi_CpuCopy16(p->comment, info->comment, 0x34);
}
