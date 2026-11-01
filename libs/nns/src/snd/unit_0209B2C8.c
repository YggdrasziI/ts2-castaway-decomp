/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on


#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"

extern NNSSndPlayer data_020d4c68[ 32 ];

/* func_0209b2c8 -- NitroSystem player.c: func_0209b2c8. */
void func_0209b2c8 (int playerNo, u32 chBitFlag)
{

    *(u8 *)&data_020d4c68[ playerNo ] = chBitFlag;
}
