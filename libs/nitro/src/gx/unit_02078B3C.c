/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/fx.h"

extern void MI_Copy36B(const void *src, void *dst);
void func_02078b7c(const MtxFx33 *m);
void G2x_SetBlendAlpha_(unsigned int *r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int a5);
void G2x_SetBlendBrightness_(unsigned short *dst, unsigned int attr, int value);

void func_02078b7c(const MtxFx33 *m) {
    *(volatile unsigned int *)0x4000400 = 0x1a;
    MI_Copy36B(m, (void *)0x4000400);
}

void G2x_SetBlendAlpha_(unsigned int *r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int a5)
{
    *r0 = ((r1 | 0x40) | (r2 << 8)) | ((r3 | (a5 << 8)) << 16);
}

void G2x_SetBlendBrightness_(unsigned short *dst, unsigned int attr, int value)
{
    if (value < 0) {
        dst[0] = attr | 0xc0;
        dst[2] = -value;
    } else {
        dst[0] = attr | 0x80;
        dst[2] = value;
    }
}
