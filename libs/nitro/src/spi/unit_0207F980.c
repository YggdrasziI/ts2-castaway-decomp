/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/mi.h"
#include "sdk/spi.h"
#include "sdk/rtc.h"
#include "sdk/wm.h"
#include "sdk/pxi.h"
#include "sdk/snd.h"
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
typedef void (*MBCommPStateCallback) (u16 child_aid, u32 status, void * arg);
typedef void (*MBCommCStateCallbackFunc) (u32 status, void * arg);
typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);
extern struct {
    u32 reserved0;                /* 0x00 */
    volatile BOOL syncFlag;       /* 0x04: PMi_SyncFlag */
    volatile BOOL sleepEndFlag;   /* 0x08: PMi_SleepEndFlag */
    u32 reserved0c[4];            /* 0x0c */
    PMiWork work;                 /* 0x1c: PMi_Work */
} data_020463cc;
#define PMi_SyncFlag data_020463cc.syncFlag
#define PMi_SleepEndFlag data_020463cc.sleepEndFlag
#define PMi_Work data_020463cc.work
#define PMi_RegisterBuffer data_02046410
#define PM_LCD_ALL 2
#define PM_BACKLIGHT_OFF 0
#define PM_LCD_POWER_ON 1
#define PM_LED_ON 1
#define reg_OS_IME (*(vu16 *)REG_IME_ADDR)
#define reg_OS_IF (*(vu32 *)REG_IF_ADDR)
#define reg_GX_DISPCNT (*(vu32 *)REG_DISPCNT_ADDR)
#define reg_GXS_DB_DISPCNT (*(vu32 *)REG_DB_DISPCNT_ADDR)
#define MB_TYPE_MULTIBOOT 2
#define PMi_PreSleepCallbackList (*(PMSleepCallbackInfo **)&data_020463cc.reserved0c[0])
#define PMi_PostSleepCallbackList (*(PMSleepCallbackInfo **)&data_020463cc.reserved0c[3])
#define PM_LCD_TOP 0
#define PM_LCD_BOTTOM 1
#define PM_LCD_POWER_OFF 0
static inline BOOL OS_DisableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = OS_IME_DISABLE;
    return (BOOL)prep;
}
static inline BOOL OS_EnableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = OS_IME_ENABLE;
    return (BOOL)prep;
}
static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}
static inline OSIrqMask OS_GetRequestIrqMask(void)
{
    return reg_OS_IF;
}
static inline BOOL MB_IsMultiBootChild(void)
{
    return *(const u16 *)HW_WM_BOOT_BUF == MB_TYPE_MULTIBOOT;
}
static inline void GXS_DispOff(void)
{
    reg_GXS_DB_DISPCNT &= ~REG_GXS_DB_DISPCNT_MODE_MASK;
}
u32 func_0207fc18(u16 registerAddr, u16 * buffer, PMCallback callback, void * arg);
void func_02080084(void);
void func_0208007c(u32 result, void * arg);
extern int func_0207fd4c(int arg, void *arg1, void *arg2);
extern PMData16 data_02046410[PMIC_REG_NUMS];
extern void PMi_CallCallbackAndUnlock(u32 result);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern OSIrqMask OS_DisableIrqMask(OSIrqMask intr);
extern OSIrqMask OS_SetIrqMask(OSIrqMask intr);
extern BOOL OS_IsTickAvailable(void);
extern void OS_Halt(void);
extern void OS_SpinWait(u32 cycles);
extern BOOL CTRDG_IsExisting(void);
extern void PMi_ExecuteList(PMSleepCallbackInfo *listp);
extern PMLCDPower PM_GetLCDPower(void);
extern u32 PM_GetBackLight(PMBackLightSwitch *top, PMBackLightSwitch *bottom);
extern u32 PMi_SendSleepStart(unsigned int trigger, unsigned int keyIntrData);
extern BOOL PMi_SetLCDPower(PMLCDPower sw, PMLEDStatus led, BOOL skip, BOOL isSync);
extern BOOL func_0207f570(PMLCDPower sw);
u32 func_0207fbdc (u16 registerAddr, u16 * buffer);
int func_0207fb74(int arg0, void *arg1, void *arg2);
u32 func_0207fb38 (PMLEDStatus status);
u32 func_0207faa8 (PMLCDTarget target, PMBackLightSwitch sw, PMCallback callback, void * arg);
u32 func_0207fa6c (u16 registerAddr, u16 * buffer);
u32 func_0207f9bc (PMCallback callback, void * arg);
int func_0207f980(void);

u32 func_0207fbdc (u16 registerAddr, u16 * buffer)
{
    u32 commandResult;
    u32 sendResult =
        func_0207fc18(registerAddr, buffer, func_0208007c, &commandResult);
    if (sendResult == PM_SUCCESS) {
        func_02080084();
        return commandResult;
    }
    return sendResult;
}

int func_0207fb74(int arg0, void *arg1, void *arg2)
{
    int v;
    switch (arg0) {
    case 1: v = 1; break;
    case 3: v = 2; break;
    case 2: v = 3; break;
    default: v = 0; break;
    }
    if (v == 0) return 0xffff;
    return func_0207fd4c(v, arg1, arg2);
}

u32 func_0207fb38 (PMLEDStatus status)
{
    u32 commandResult;
    u32 sendResult = func_0207fb74(status, func_0208007c, &commandResult);

    if (sendResult == PM_SUCCESS) {
        func_02080084();
        return commandResult;
    }

    return sendResult;
}

u32 func_0207faa8 (PMLCDTarget target, PMBackLightSwitch sw, PMCallback callback, void * arg)
{
    u32 command = 0;

    if (target == PM_LCD_TOP) {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD2_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD2_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_BOTTOM)   {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD1_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD1_BACKLIGHT_OFF;
        }
    } else if (target == PM_LCD_ALL)   {
        if (sw == PM_BACKLIGHT_ON) {
            command = PM_UTIL_LCD12_BACKLIGHT_ON;
        }
        if (sw == PM_BACKLIGHT_OFF) {
            command = PM_UTIL_LCD12_BACKLIGHT_OFF;
        }
    }

    return (command) ? func_0207fd4c(command, callback, arg) : PM_INVALID_COMMAND;
}

u32 func_0207fa6c (u16 registerAddr, u16 * buffer)
{
    u32 commandResult;
    u32 sendResult =
        func_0207faa8((PMLCDTarget)registerAddr, (PMBackLightSwitch)(int)buffer, func_0208007c, &commandResult);
    if (sendResult == PM_SUCCESS) {
        func_02080084();
        return commandResult;
    }
    return sendResult;
}

u32 func_0207f9bc (PMCallback callback, void * arg)
{
    PMLCDPower LCDResult;
    PMBackLightSwitch top;
    PMBackLightSwitch bottom;

    OS_SpinWait(PMi_LCD_POWER_WAIT_TICK);
    LCDResult = PM_GetLCDPower();

    if (LCDResult != PM_LCD_POWER_ON) {
        (void)PM_GetBackLight(&top, &bottom);
        if (top != PM_BACKLIGHT_OFF)
            (void)func_0207fa6c(PM_LCD_TOP, PM_BACKLIGHT_OFF);
        if (bottom != PM_BACKLIGHT_OFF)
            (void)func_0207fa6c(PM_LCD_BOTTOM, PM_BACKLIGHT_OFF);

        while (!func_0207f570(PM_LCD_POWER_ON)) {
            OS_SpinWait(PMi_LCD_POWER_WAIT_TICK);
        }
    }

    return func_0207fd4c(PM_UTIL_FORCE_POWER_OFF, callback, arg);
}

int func_0207f980(void) {
    int local;
    int r = func_0207f9bc((void *)func_0208007c, &local);
    if (r != 0) return r;
    func_02080084();
    return local;
}
