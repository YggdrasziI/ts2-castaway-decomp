/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"

extern NNSSndArc * data_020d5210;
u32 NNS_SndArcGetFileOffset (u32 fileId);
u32 NNS_SndArcGetFileSize (u32 fileId);

u32 NNS_SndArcGetFileOffset (u32 fileId)
{
    NNSSndArc * arc = data_020d5210;

    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[ fileId ].offset;
}

u32 NNS_SndArcGetFileSize (u32 fileId)
{
    NNSSndArc * arc = data_020d5210;

    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[ fileId ].size;
}
