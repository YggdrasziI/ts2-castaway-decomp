/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

void MI_CpuCopy8(const void * src, void * dest, u32 size);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
s32 ReadMemoryStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);

s32 ReadMemoryStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset)
{

    const u8 * src = (const u8 *)(player->fileOffset);

    MI_CpuCopy8(src + offset, dest, size);

    return (s32)size;
}
