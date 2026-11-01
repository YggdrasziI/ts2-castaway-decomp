/* NitroSDK DMA functions. Written from the ROM, compared with khdays (CC0). File bounds are a
 * hypothesis. Functions are emitted in reverse source order. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/mi.h"

extern int OS_DisableInterrupts(void);
extern int OS_RestoreInterrupts(int state);
extern void OS_Terminate(void);
extern void func_0207a128(u32 dmaNo, MIDmaCallback callback, void *arg);
extern void func_01ff8114(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff8174(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff81ac(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff8220(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);
void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 timing);
void MI_WaitDma(u32 dmaNo);

#define DMA_CNT(n) (&((vu32 *)0x040000B0)[(n) * 3 + 2])
#define DMA_REGS(n) ((vu32 *)(0x040000B0 + (n) * 12))
#define DMA_FILL(n) (*(vu32 *)(0x040000E0 + (n) * 4))

void MI_DmaFill32(u32 dmaNo, void *dest, u32 data, u32 size)
{
    vu32 *cnt;
    int e;

    if (size == 0) {
        return;
    }
    cnt = DMA_CNT(dmaNo);
    while (*cnt & 0x80000000) {
    }
    e = OS_DisableInterrupts();
    DMA_FILL(dmaNo) = data;
    func_01ff8114(dmaNo, 0x040000E0 + dmaNo * 4, (u32)dest, (size >> 2) | 0x85000000);
    OS_RestoreInterrupts(e);
    while (*cnt & 0x80000000) {
    }
}

void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    vu32 *cnt;

    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, 0);
    if (size == 0) {
        return;
    }
    cnt = DMA_CNT(dmaNo);
    while (*cnt & 0x80000000) {
    }
    func_01ff81ac(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32(size));
    while (*cnt & 0x80000000) {
    }
}

void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size)
{
    vu32 *cnt;

    if (size == 0) {
        return;
    }
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, 0);
    cnt = DMA_CNT(dmaNo);
    while (*cnt & 0x80000000) {
    }
    func_01ff81ac(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY16(size));
    while (*cnt & 0x80000000) {
    }
}

void MI_DmaFill32Async(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg)
{
    int e;

    if (size == 0) {
        if (callback != NULL) {
            callback(arg);
        }
    } else {
        MI_WaitDma(dmaNo);
        if (callback != NULL) {
            func_0207a128(dmaNo, callback, arg);
            e = OS_DisableInterrupts();
            DMA_FILL(dmaNo) = data;
            func_01ff8174(dmaNo, 0x040000E0 + dmaNo * 4, (u32)dest, (size >> 2) | 0xC5000000);
            OS_RestoreInterrupts(e);
        } else {
            e = OS_DisableInterrupts();
            DMA_FILL(dmaNo) = data;
            func_01ff8174(dmaNo, 0x040000E0 + dmaNo * 4, (u32)dest, (size >> 2) | 0x85000000);
            OS_RestoreInterrupts(e);
        }
    }
}

void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg)
{
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, 0);
    if (size == 0) {
        if (callback != NULL) {
            callback(arg);
        }
    } else {
        MI_WaitDma(dmaNo);
        if (callback != NULL) {
            func_0207a128(dmaNo, callback, arg);
            func_01ff8220(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32_IF(size));
        } else {
            func_01ff8220(dmaNo, (u32)src, (u32)dest, MI_CNT_COPY32(size));
        }
    }
}

void MI_WaitDma(u32 dmaNo)
{
    int e = OS_DisableInterrupts();
    vu32 *cnt = DMA_CNT(dmaNo);

    while (*cnt & 0x80000000) {
    }
    if (dmaNo == 0) {
        vu32 *p = DMA_REGS(dmaNo);
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    OS_RestoreInterrupts(e);
}

void MI_StopDma(u32 dmaNo)
{
    int e = OS_DisableInterrupts();
    vu16 *cnt = &((vu16 *)0x040000B0)[dmaNo * 6 + 5];

    *cnt &= ~0x3a00;
    *cnt &= ~0x8000;
    {
        u16 dummy = *cnt;
    }
    {
        u16 dummy = *cnt;
    }
    if (dmaNo == 0) {
        vu32 *p = DMA_REGS(dmaNo);
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    OS_RestoreInterrupts(e);
}

void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 timing)
{
    int i;
    vu32 *cntp = (vu32 *)0x040000B8;

    for (i = 0; i < 3; i++, cntp += 3) {
        u32 cnt;

        if (i == dmaNo) {
            continue;
        }
        cnt = *cntp;
        if (cnt & 0x80000000) {
            cnt &= 0x38000000;
            if (cnt == timing) {
                continue;
            }
        } else {
            continue;
        }
        if (cnt == 0x08000000 && timing == 0x10000000) {
            continue;
        }
        if (cnt == 0x10000000 && timing == 0x08000000) {
            continue;
        }
        if (cnt == 0x18000000 || cnt == 0x20000000 || cnt == 0x28000000 || cnt == 0x30000000
            || cnt == 0x38000000 || cnt == 0x08000000 || cnt == 0x10000000) {
            OS_Terminate();
        }
    }
}

void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir)
{
    if (dmaNo == 0) {
        u32 start = src & 0xff000000;
        u32 end;

        switch (dir) {
        case 0:
            end = src + size;
            break;
        case 0x800000:
            end = src - size;
            break;
        default:
            end = src;
            break;
        }
        end &= 0xff000000;
        if (start == 0x04000000 || start >= 0x08000000 || end == 0x04000000 || end >= 0x08000000) {
            OS_Terminate();
        }
    }
}

void MI_SetWramBank(u8 bank)
{
    *(vu8 *)0x04000247 = bank;
}
