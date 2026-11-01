/* NitroSDK hardware divider helpers. Written from the ROM. File bounds and role names are a
 * hypothesis; the names stay address based. Functions are emitted in reverse source order. */
#pragma force_active on

#include "sdk/types.h"

#define REG_DIVCNT (*(vu16 *)0x04000280)
#define REG_DIV_NUMER_L (*(vu32 *)0x04000290)
#define REG_DIV_NUMER (*(vu64 *)0x04000290)
#define REG_DIV_DENOM (*(vu64 *)0x04000298)
#define REG_DIV_RESULT_L (*(vs32 *)0x040002A0)
#define REG_DIV_REM_L (*(vs32 *)0x040002A8)

void func_02077bcc(s32 denom)
{
    REG_DIVCNT = 1;
    REG_DIV_NUMER = (u64)0x1000 << 32;
    REG_DIV_DENOM = (u32)denom;
}

void func_02077b94(s32 numer, s32 denom)
{
    REG_DIVCNT = 1;
    REG_DIV_NUMER = (u64)(u32)numer << 32;
    REG_DIV_DENOM = (u32)denom;
}

s32 func_02077b3c(s32 numer, s32 denom)
{
    REG_DIVCNT = 0;
    REG_DIV_NUMER_L = numer;
    REG_DIV_DENOM = (u32)denom;
    while (REG_DIVCNT & 0x8000) {
    }
    return REG_DIV_RESULT_L;
}

s32 func_02077ae4(s32 numer, s32 denom)
{
    REG_DIVCNT = 0;
    REG_DIV_NUMER_L = numer;
    REG_DIV_DENOM = (u32)denom;
    while (REG_DIVCNT & 0x8000) {
    }
    return REG_DIV_REM_L;
}
