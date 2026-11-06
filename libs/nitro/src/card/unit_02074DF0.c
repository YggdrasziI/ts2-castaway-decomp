/* NitroSDK CARD: tries to start a ROM read by card DMA. Adapted from khdays'
 * CARDi_TryReadCardDma (CC0) to this ROM, which has no cache thresholds: the
 * instruction cache and data cache are always invalidated by range. File bounds
 * are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef int BOOL;

typedef struct {
    unsigned char pad[0x1c];
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
} Common;

typedef struct {
    void (*read_func)(void *state);
    u32 ctrl;
} RomStat;

extern Common data_020c4800;
extern u32 data_020bcb64;
extern void func_01ff8000(void);
extern void func_02074f64(void);
extern void func_02075044(void);
extern u32 OS_GetDTCMAddress(void);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void IC_InvalidateRange(void *address, u32 size);
extern void DC_StoreRange(void *address, u32 size);
extern void DC_InvalidateRange(void *address, u32 size);
extern void DC_WaitWriteBufferEmpty(void);
extern void *func_0207a174(u32 mask, void (*function)(void));
extern u32 OS_ResetRequestIrqMask(u32 mask);
extern u32 OS_EnableIrqMask(u32 mask);

static inline BOOL Card_IsInTcm(u32 buffer, u32 length) {
    const u32 instructionTcm = (u32)func_01ff8000;
    const u32 dataTcm = OS_GetDTCMAddress();
    return ((buffer + length > instructionTcm) && (buffer < 0x02000000)) ||
           ((dataTcm < buffer + length) && (dataTcm + 0x4000 > buffer));
}

static inline u32 Card_GetRomFlag(u32 flag) {
    const u32 control = *(volatile u32 *)(data_020bcb64 + 0x60);
    return (control & ~0x07000000) | flag | 0x80000000 | 0x20000000;
}

BOOL func_02074df0(RomStat *state) {
    Common *const common = &data_020c4800;
    const u32 destination = common->dst;
    u32 length = common->len;
    const BOOL asynchronous = !(destination & 0x1f) && (common->dma <= 3) &&
                              !Card_IsInTcm(destination, length) &&
                              !((common->src | length) & 0x1ff) && (length > 0);

    state->ctrl = Card_GetRomFlag(0x01000000);
    if (asynchronous) {
        int interruptState = OS_DisableInterrupts();
        IC_InvalidateRange((void *)destination, length);
        {
            u32 position = destination;
            u32 misalignment = destination & 0x1f;
            if (misalignment) {
                position -= misalignment;
                DC_StoreRange((void *)position, 0x20);
                DC_StoreRange((void *)(position + length), 0x20);
                length += 0x20;
            }
            DC_InvalidateRange((void *)position, length);
            DC_WaitWriteBufferEmpty();
        }
        func_0207a174(0x80000, func_02074f64);
        OS_ResetRequestIrqMask(0x80000);
        OS_EnableIrqMask(0x80000);
        OS_RestoreInterrupts(interruptState);
        func_02075044();
    }
    return asynchronous;
}
