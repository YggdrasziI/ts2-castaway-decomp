/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void MI_CpuFillU32(u32 v, void *d, u32 n);
typedef struct { char *head; char *tail; } Frm;
static inline u16 Opt(Frm *h) { return (u16)(*(u32 *)((char *)h - 4) & 0xff); }
static inline void Fill(Frm *h, void *a, u32 n) { if (Opt(h) & 1) { MI_CpuFillU32(0, a, n); } }
char *func_0209ee14(Frm *h, u32 size, int align)
{
    char *block = (char *)(((align - 1) + (u32)h->head) & ~(align - 1));
    char *end = (char *)(size + (u32)block);
    if (end > h->tail) {
        return 0;
    }
    Fill(h, h->head, end - h->head);
    h->head = end;
    return block;
}
