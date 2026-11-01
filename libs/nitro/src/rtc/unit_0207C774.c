/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))

u32 RtcBCD2HEX (u32 bcd);

u32 RtcBCD2HEX (u32 bcd)
{
    u32 hex = 0;
    s32 i;
    s32 w;

    for (i = 0; i < 8; i++) {
        if (((bcd >> (i * 4)) & 0x0000000f) >= 0x0a) {
            return hex;
        }
    }

    for (i = 0, w = 1; i < 8; i++, w *= 10) {
        hex += (((bcd >> (i * 4)) & 0x0000000f) * w);
    }

    return hex;
}
