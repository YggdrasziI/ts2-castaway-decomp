/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#include "sdk/pxi.h"
#include "sdk/ctrdg.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
void OS_Terminate();
void CTRDGi_SendtoPxi(u32 data);
void CTRDG_TerminateForPulledOut (void);

void CTRDG_TerminateForPulledOut (void)
{
	CTRDGi_SendtoPxi(CTRDG_PXI_COMMAND_TERMINATE);
	OS_Terminate();
}
