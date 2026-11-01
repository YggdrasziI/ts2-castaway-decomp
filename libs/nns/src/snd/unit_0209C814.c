/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void *NNS_SndArcGetFileAddress(u32 id);
extern int func_0209ba04(u32 id, void *dst, int size, int offset);
extern void *func_0209bdf8(void);
extern void *func_0209c2d8(void *heap, u32 size, void *cb, u32 a, u32 b);
extern void func_0209b9a0(u32 id, void *p);
extern void func_0209c6d8(void *p, u32 size, u32 a, u32 b);
extern void MI_CpuCopy8(const void *s, void *d, u32 n);
extern void MI_CpuFill8(void *d, int v, u32 n);
extern void DC_StoreRange(const void *p, u32 n);
typedef struct { char h[0x38]; u32 count; u32 offset[1]; } Arc;
extern Arc data_020d5214;
Arc *func_0209c814(u32 id, void *heap, int set)
{
    Arc *arc;
    u32 fileSize;
    u32 count;
    u32 table;
    int result;
    arc = NNS_SndArcGetFileAddress(id);
    if (arc == 0) {
        if (func_0209ba04(id, &data_020d5214, 0x3c, 0) != 0x3c) {
            return 0;
        }
        count = data_020d5214.count;
        table = count * 4;
        fileSize = table * 2 + 0x3c;
        if (heap == 0) {
            return 0;
        }
        arc = func_0209c2d8(heap, fileSize + 0x20, func_0209c6d8, set ? (u32)func_0209bdf8() : 0, id);
        if (arc == 0) {
            return 0;
        }
        result = func_0209ba04(id, arc, table + 0x3c, 0);
        if (result != table + 0x3c) {
            return 0;
        }
        MI_CpuCopy8(arc->offset, &arc->offset[arc->count], table);
        MI_CpuFill8(arc->offset, 0, table);
        DC_StoreRange(arc, fileSize);
        if (set) {
            func_0209b9a0(id, arc);
        }
    }
    return arc;
}
