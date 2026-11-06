/* NitroSDK gx_load3d.c: GX_LoadTex, the texture image load split across two VRAM
 * banks. Heroes of Mana's GX_LoadTex (CC0, its own code), retyped for this ROM: the
 * bank state is three separate words here. The two copy inlines are written here.
 * File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned char u8;
typedef unsigned int u32;

extern void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, void *callback, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

extern u32 data_020c571c; /* first bank start */
extern u32 data_020c572c; /* second bank start, 0 without one */
extern u32 data_020c5730; /* size of the first bank */
extern u32 data_020bcb74; /* GX DMA channel, -1 for the CPU */

static inline void Copy32(u32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != (u32)-1 && size > 0x30) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MIi_CpuCopy32(src, dest, size);
    }
}

static inline void Copy32Async(u32 dmaNo, const void *src, void *dest, u32 size) {
    if (dmaNo != (u32)-1) {
        MI_DmaCopy32Async(dmaNo, src, dest, size, 0, 0);
    } else {
        MIi_CpuCopy32(src, dest, size);
    }
}

void func_020792d0(const void *src, u32 destSlotAddr, u32 size) {
    void *dest;

    if (data_020c572c == 0) {
        dest = (void *)(data_020c571c + destSlotAddr);
    } else if (destSlotAddr + size < data_020c5730) {
        dest = (void *)(data_020c571c + destSlotAddr);
    } else if (destSlotAddr >= data_020c5730) {
        dest = (void *)(data_020c572c + destSlotAddr - data_020c5730);
    } else {
        void *dest2 = (void *)data_020c572c;
        u32 size1 = data_020c5730 - destSlotAddr;
        Copy32(data_020bcb74, src, (void *)(data_020c571c + destSlotAddr), size1);
        Copy32Async(data_020bcb74, (u8 *)src + size1, dest2, size - size1);
        return;
    }
    Copy32Async(data_020bcb74, src, dest, size);
}
