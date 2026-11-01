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
u32 func_0207e7fc (TPCalibrateParam * calibrate,
                           u16 raw_x1, u16 raw_y1,
                           u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2);

u32 func_0207e7fc (TPCalibrateParam * calibrate,
                           u16 raw_x1, u16 raw_y1,
                           u16 dx1, u16 dy1, u16 raw_x2, u16 raw_y2, u16 dx2, u16 dy2)
{
    s32 rx_width, dx_width, ry_width, dy_width;
    s32 tmp32;
    OSIntrMode enabled;

#define IN_S16_RANGE(x) ((x) < 0x8000 && (x) >= -0x8000)

    if (raw_x1 >= TP_RAW_MAX || raw_y1 >= TP_RAW_MAX || raw_x2 >= TP_RAW_MAX
        || raw_y2 >= TP_RAW_MAX) {
        return 1;
    }
    if (dx1 >= GX_LCD_SIZE_X || dx2 >= GX_LCD_SIZE_X || dy1 >= GX_LCD_SIZE_Y
        || dy2 >= GX_LCD_SIZE_Y) {
        return 1;
    }
    if (dx1 == dx2 || dy1 == dy2 || raw_x1 == raw_x2 || raw_y1 == raw_y2) {
        return 1;
    }

    rx_width = raw_x1 - raw_x2;
    dx_width = dx1 - dx2;

    enabled = OS_DisableInterrupts();

    CP_SetDiv32_32(((u32)rx_width) << TP_CALIBRATE_DOT_SCALE_SHIFT, (u32)dx_width);

    ry_width = raw_y1 - raw_y2;
    dy_width = dy1 - dy2;

    tmp32 = CP_GetDivResult32();
    CP_SetDiv32_32(((u32)ry_width) << TP_CALIBRATE_DOT_SCALE_SHIFT, (u32)dy_width);

    if (!IN_S16_RANGE(tmp32)) {
        (void)OS_RestoreInterrupts(enabled);
        return 1;
    }
    calibrate->xDotSize = (s16)tmp32;
    tmp32 = (s16)((((s32)(raw_x1 + raw_x2) << TP_CALIBRATE_DOT_SCALE_SHIFT)
                   - ((s32)(dx1 + dx2) * calibrate->xDotSize)) >> (TP_CALIBRATE_DOT_SCALE_SHIFT -
                                                                   TP_CALIBRATE_ORIGIN_SCALE_SHIFT +
                                                                   1));
    if (!IN_S16_RANGE(tmp32)) {
        (void)OS_RestoreInterrupts(enabled);
        return 1;
    }
    calibrate->x0 = (s16)tmp32;

    tmp32 = CP_GetDivResult32();
    (void)OS_RestoreInterrupts(enabled);

    if (!IN_S16_RANGE(tmp32)) {
        return 1;
    }

    calibrate->yDotSize = (s16)tmp32;
    tmp32 = (s16)((((s32)(raw_y1 + raw_y2) << TP_CALIBRATE_DOT_SCALE_SHIFT)
                   - ((s32)(dy1 + dy2) * calibrate->yDotSize)) >> (TP_CALIBRATE_DOT_SCALE_SHIFT -
                                                                   TP_CALIBRATE_ORIGIN_SCALE_SHIFT +
                                                                   1));
    if (!IN_S16_RANGE(tmp32)) {
        return 1;
    }

    calibrate->y0 = (s16)tmp32;

    return 0;
}
