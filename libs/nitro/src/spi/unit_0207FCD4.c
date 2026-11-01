/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/spi.h"

extern int func_020800c4(void);
extern void PMi_SendPxiData(u32 command);
extern struct { char _0[4]; PMCallback callback; void *callbackArgument; } data_020c7758;
extern PMData16 data_020c7780[];
u32 func_0207fcd4(u16 channel, u16 *buffer,
                        PMCallback callback, void *callbackArgument);

u32 func_0207fcd4(u16 channel, u16 *buffer,
                        PMCallback callback, void *callbackArgument)
{
    if (func_020800c4() == 0) {
        return 1;
    }

    data_020c7758.callback = callback;
    data_020c7758.callbackArgument = callbackArgument;
    data_020c7780[channel].flag = 0;
    data_020c7780[channel].buffer = buffer;
    PMi_SendPxiData((channel & 0xff) | 0x03006500);
    return 0;
}
