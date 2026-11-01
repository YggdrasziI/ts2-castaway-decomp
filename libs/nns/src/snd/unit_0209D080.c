/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"

NNSSndArcLoadResult func_0209cdf4(int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);
BOOL NNS_SndArcLoadBank (int bankNo, NNSSndHeapHandle heap);

BOOL NNS_SndArcLoadBank (int bankNo, NNSSndHeapHandle heap)
{
    NNSSndArcLoadResult result;

    result = func_0209cdf4(bankNo, NNS_SND_ARC_LOAD_ALL, heap, TRUE, NULL);

    return result == NNS_SND_ARC_LOAD_SUCESS ? TRUE : FALSE;
}
