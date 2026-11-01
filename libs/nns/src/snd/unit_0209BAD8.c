/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
static inline
const void * GetPtrConst (const void * base, u32 offset)
{
    if (offset == 0) return NULL ;
    return (const u8 *)base + offset;
}
static inline
const NNSSndArcOffsetTable * GetOffsetTable (const NNSSndArcInfo * info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}
extern const void * GetPtrConst(const void * base, u32 offset);
extern const NNSSndArcOffsetTable * GetOffsetTable(const NNSSndArcInfo * info, u32 offset);
extern NNSSndArc * data_020d5210;
const NNSSndArcBankInfo * func_0209bad8 (int bankNo);

const NNSSndArcBankInfo * func_0209bad8 (int bankNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->groupInfoOffset);
    if (table == NULL) return NULL;

    if (bankNo < 0) return NULL;
    if (bankNo >= table->count) return NULL;

    return (const NNSSndArcBankInfo *)GetPtrConst(arc->info, table->offset[ bankNo ]);
}
