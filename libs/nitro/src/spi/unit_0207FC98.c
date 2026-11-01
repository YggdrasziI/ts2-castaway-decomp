/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/mi.h"
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
u32 func_0207fcd4(u16 registerAddr, u16 * buffer, PMCallback callback, void * arg);
void func_02080084(void);
void func_0208007c(u32 result, void * arg);
u32 func_0207fc98 (u16 registerAddr, u16 * buffer);

u32 func_0207fc98 (u16 registerAddr, u16 * buffer)
{
    u32 commandResult;
    u32 sendResult =
        func_0207fcd4(registerAddr, buffer, func_0208007c, &commandResult);
    if (sendResult == PM_SUCCESS) {
        func_02080084();
        return commandResult;
    }
    return sendResult;
}
