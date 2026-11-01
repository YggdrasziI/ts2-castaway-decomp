/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/mi.h"
#include "sdk/spi.h"
#include "sdk/rtc.h"
#include "sdk/wm.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
u32 func_0207fc98(u16 registerAddr, u16 * buffer);
extern int func_0207c4f8(int a, int b, int c);
u32 PM_GetBackLight (PMBackLightSwitch * top, PMBackLightSwitch * bottom);
void PMi_SendPxiData(int arg0);

u32 PM_GetBackLight (PMBackLightSwitch * top, PMBackLightSwitch * bottom)
{
    u16 reg;
    u32 result;

    if ((result = func_0207fc98(REG_PMIC_CTL_ADDR, &reg)) == PM_SUCCESS) {
        if (top) {
            *top = (reg & PMIC_CTL_BKLT2) ? PM_BACKLIGHT_ON : PM_BACKLIGHT_OFF;
        }
        if (bottom) {
            *bottom = (reg & PMIC_CTL_BKLT1) ? PM_BACKLIGHT_ON : PM_BACKLIGHT_OFF;
        }
    }

    return result;
}

void PMi_SendPxiData(int arg0)
{
    while (func_0207c4f8(8, arg0, 0) != 0);
}
