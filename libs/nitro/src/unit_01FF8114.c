/* NitroSDK DMA parameter setting functions placed in ITCM (MI).
 *
 * Bounds 0x01FF8114-0x01FF831C (hypothesis: the EA function 0x01FF8000 before; the
 * IRQ handler 0x01FF831C after). Four functions write the source, destination and
 * control words of a DMA channel (with or without disabling interrupts, with or
 * without the extra reads and the reset of channel 0); func_01ff8270 sends a
 * buffer to the geometry FIFO in chunks of 0x1D8 bytes. Built with the SDK
 * compiler (1.2). Written for this project; no reference matches these functions,
 * so their names and the file name are unknown.
 */

typedef unsigned int u32;
typedef volatile u32 vu32;

extern int OS_DisableInterrupts(void);
extern int OS_RestoreInterrupts(int);
extern void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);

#define REG_DMA_SRC(n) (*(vu32 *)(0x040000B0 + (n) * 12))
#define DMA_REGS(n) ((vu32 *)(0x040000B0 + (n) * 12))

void func_01ff8220(u32 dmaNo, u32 src, u32 dest, u32 ctrl);

void func_01ff8270(u32 dmaNo, const void *src, u32 size)
{
    vu32 *ctrl;

    if (size == 0)
    {
        return;
    }
    MIi_CheckDma0SourceAddress(dmaNo, (u32)src, size, 0);
    ctrl = &((vu32 *)0x040000B0)[dmaNo * 3 + 2];
    while (*ctrl & 0x80000000)
    {
    }
    while (size > 0)
    {
        u32 n = size > 0x1d8 ? 0x1d8 : size;
        func_01ff8220(dmaNo, (u32)src, 0x04000400, 0x84400000 | (n >> 2));
        size -= n;
        src = (const char *)src + n;
    }
    while (*ctrl & 0x80000000)
    {
    }
}

void func_01ff8220(u32 dmaNo, u32 src, u32 dest, u32 ctrl)
{
    int e = OS_DisableInterrupts();
    vu32 *p = DMA_REGS(dmaNo);
    *p = src;
    *(p + 1) = dest;
    *(p + 2) = ctrl;
    (void)OS_RestoreInterrupts(e);
}

void func_01ff81ac(u32 dmaNo, u32 src, u32 dest, u32 ctrl)
{
    int e = OS_DisableInterrupts();
    vu32 *p = DMA_REGS(dmaNo);
    *p = src;
    *(p + 1) = dest;
    *(p + 2) = ctrl;
    {
        u32 dummy = REG_DMA_SRC(0);
    }
    {
        u32 dummy = REG_DMA_SRC(0);
    }
    if (dmaNo == 0)
    {
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    (void)OS_RestoreInterrupts(e);
}

void func_01ff8174(u32 dmaNo, u32 src, u32 dest, u32 ctrl)
{
    vu32 *p = DMA_REGS(dmaNo);
    *p = src;
    *(p + 1) = dest;
    *(p + 2) = ctrl;
}

void func_01ff8114(u32 dmaNo, u32 src, u32 dest, u32 ctrl)
{
    vu32 *p = DMA_REGS(dmaNo);
    *p = src;
    *(p + 1) = dest;
    *(p + 2) = ctrl;
    {
        u32 dummy = REG_DMA_SRC(0);
    }
    {
        u32 dummy = REG_DMA_SRC(0);
    }
    if (dmaNo == 0)
    {
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    {
        u32 dummy = REG_DMA_SRC(0);
    }
    {
        u32 dummy = REG_DMA_SRC(0);
    }
}
