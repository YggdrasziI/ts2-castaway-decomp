/* NitroSystem FND frame heap: allocation from the tail of the heap head (head at +0,
 * tail at +4; the option byte of the common header just before says whether to clear
 * the block). Heroes of Mana's source (CC0), retyped for this ROM. File bounds are a
 * hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef unsigned short u16;
typedef int s32;

void MI_CpuFillU32(u32 value, void *dest, u32 size);

typedef struct Heap {
    u32 head;
    u32 tail;
} Heap;

void *func_0209eda0(Heap *h, u32 size, s32 align) {
    u32 tail = h->tail;
    u32 aligned = ~(align - 1) & (tail - size);
    u32 len;
    if (aligned < h->head) {
        return 0;
    }
    len = tail - aligned;
    if ((u16)(((u32 *)h)[-1] & 0xff) & 1) {
        MI_CpuFillU32(0, (void *)aligned, len);
    }
    h->tail = aligned;
    return (void *)aligned;
}
