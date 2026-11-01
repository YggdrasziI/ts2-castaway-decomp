/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on


#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"


/* func_0209b154 -- NitroSystem sndarc_stream.c: func_0209b154. */
void func_0209b154 (NNSSndStrmHandle * handle)
{

    if (handle->player == NULL) return;

    *(int *)handle->player = 0;
    handle->player = NULL;
}
