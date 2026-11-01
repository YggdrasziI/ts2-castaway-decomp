/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/spi.h"
#include "sdk/rtc.h"
#include "sdk/wm.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
void PMi_PrependList(PMSleepCallbackInfo ** listp, PMSleepCallbackInfo * info);
extern PMSleepCallbackInfo * data_020c774c;
void PMi_AppendList(PMSleepCallbackInfo ** listp, PMSleepCallbackInfo * info);
extern PMSleepCallbackInfo * data_020c7754;
void PMi_DeleteList(PMSleepCallbackInfo ** listp, PMSleepCallbackInfo * info);
void func_0207f464 (PMSleepCallbackInfo * info);
void func_0207f44c (PMSleepCallbackInfo * info);
void func_0207f434 (PMSleepCallbackInfo * info);
void func_0207f41c (PMSleepCallbackInfo * info);

void func_0207f464 (PMSleepCallbackInfo * info)
{
    PMi_PrependList(&data_020c774c, info);
}

void func_0207f44c (PMSleepCallbackInfo * info)
{
    PMi_AppendList(&data_020c7754, info);
}

void func_0207f434 (PMSleepCallbackInfo * info)
{
    PMi_DeleteList(&data_020c774c, info);
}

void func_0207f41c (PMSleepCallbackInfo * info)
{
    PMi_DeleteList(&data_020c7754, info);
}
