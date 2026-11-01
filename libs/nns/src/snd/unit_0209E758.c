/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"


const NNSSndSeqArcSeqInfo * NNSi_SndSeqArcGetSeqInfo (const NNSSndSeqArc * seqArc, int index);

const NNSSndSeqArcSeqInfo * NNSi_SndSeqArcGetSeqInfo (const NNSSndSeqArc * seqArc, int index)
{

    if (index < 0) return NULL;
    if (index >= seqArc->count) return NULL;
    if (seqArc->info[ index ].offset == NNS_SND_SEQ_ARC_INVALID_OFFSET) return NULL;

    return &seqArc->info[ index ];
}
