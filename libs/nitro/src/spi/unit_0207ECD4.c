/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/gx.h"
#include "sdk/spi.h"
typedef u32 REGType32;
typedef u64 REGType64;
#define reg_CP_DIVCNT (*(REGType16v *)REG_DIVCNT_ADDR)
typedef struct {
    u16 raw_x1;
    u16 raw_y1;
    u8 dx1;
    u8 dy1;
    u16 raw_x2;
    u16 raw_y2;
    u8 dx2;
    u8 dy2;
} NVRAMConfigTp;
typedef struct {
    u8 head[0x58];
    NVRAMConfigTp tp;             /* 0x58 */
} NVRAMConfigNcd;
typedef struct {
    NVRAMConfigNcd ncd;
} NVRAMConfig;
extern struct {
    u32 reserved0;                /* 0x00 */
    TPRecvCallback callback;      /* 0x04 */
    TPData buf;                   /* 0x08 */
    u16 index;                    /* 0x10 */
    u16 frequence;                /* 0x12 */
    TPData *samplingBufs;         /* 0x14 */
    u16 bufSize;                  /* 0x18 */
    u16 reserved1a;               /* 0x1a */
    TPiCalibrateParam calibrate;  /* 0x1c */
    u16 calibrate_flg;            /* 0x34 */
    vu16 state;                   /* 0x36 */
    vu16 err_flg;                 /* 0x38 */
    vu16 command_flg;             /* 0x3a */
} data_02046390;
#define tpState data_02046390
static inline void CP_SetDivImm32_32_NS_(u32 numer, u32 denom)
{
    *(REGType32 *)REG_DIV_NUMER_ADDR = numer;
    *(REGType64 *)REG_DIV_DENOM_ADDR = denom;
}
static inline void CP_SetDiv32_32(u32 numer, u32 denom)
{
    reg_CP_DIVCNT = CP_DIV_32_32BIT_MODE;
    CP_SetDivImm32_32_NS_(numer, denom);
}
static inline u32 CP_IsDivBusy(void)
{
    return (reg_CP_DIVCNT & REG_CP_DIVCNT_BUSY_MASK);
}
static inline void CP_WaitDiv(void)
{
    while (CP_IsDivBusy()) {
    }
}
static inline s32 CP_GetDivResultImm32(void)
{
    return (s32)(*(REGType32 *)REG_DIV_RESULT_ADDR);
}
static inline s32 CP_GetDivResult32(void)
{
    CP_WaitDiv();
    return CP_GetDivResultImm32();
}
static inline void TPi_CopyTpFromSystemWork(TPData *result)
{
    SPITpData spi_tp;

    spi_tp.halfs[0] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 0);
    spi_tp.halfs[1] = *(u16 *)((u8 *)HW_TOUCHPANEL_BUF + 2);

    result->x = (u16)spi_tp.e.x;
    result->y = (u16)spi_tp.e.y;
    result->touch = (u8)spi_tp.e.touch;
    result->validity = (u8)spi_tp.e.validity;
}
static inline void TPi_ErrorAtPxi(TPRequestCommand command)
{
    tpState.err_flg |= (1 << command);

    if (tpState.callback) {
        (tpState.callback)(command, TP_RESULT_PXI_BUSY, 0);
    }
}
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_Terminate(void);
extern u32 func_0207e7fc(TPCalibrateParam *calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2);
BOOL func_0207ecd4 (TPCalibrateParam * calibrate);

BOOL func_0207ecd4 (TPCalibrateParam * calibrate)
{
    NVRAMConfig * info = (NVRAMConfig *)OS_GetSystemWork_nvramUserInfo();

    u16 x1, y1, x2, y2, dx1, dy1, dx2, dy2;

    x1 = info->ncd.tp.raw_x1;
    y1 = info->ncd.tp.raw_y1;
    dx1 = (u16)(info->ncd.tp.dx1);
    dy1 = (u16)(info->ncd.tp.dy1);
    x2 = info->ncd.tp.raw_x2;
    y2 = info->ncd.tp.raw_y2;
    dx2 = (u16)(info->ncd.tp.dx2);
    dy2 = (u16)(info->ncd.tp.dy2);

    if ((x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) ||
        (func_0207e7fc(calibrate, x1, y1, dx1, dy1, x2, y2, dx2, dy2) != 0)) {
        calibrate->x0 = 0;
        calibrate->y0 = 0;
        calibrate->xDotSize = 0;
        calibrate->yDotSize = 0;

        return TRUE;
    }

    return TRUE;
}
