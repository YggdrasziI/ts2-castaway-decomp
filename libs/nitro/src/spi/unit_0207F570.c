/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/spi.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
BOOL func_0207f590(PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);
BOOL PM_SetLCDPower (PMLCDPower sw);

BOOL PM_SetLCDPower (PMLCDPower sw)
{
    if (sw != PM_LCD_POWER_ON) {
        sw = PM_LCD_POWER_OFF;
    }

    return func_0207f590(sw, PM_LED_NONE, FALSE, TRUE);
}
