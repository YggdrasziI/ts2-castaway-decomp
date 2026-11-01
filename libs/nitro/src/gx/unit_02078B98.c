/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Geometry command 0x16 (MTX_LOAD_4x3) followed by the matrix's 48 bytes into the geometry FIFO. */
#include "sdk/fx.h"

extern void func_020794b4(const void *src, void *dst);

void func_02078b98(const MtxFx43 *m) {
    *(volatile unsigned int *)0x4000400 = 0x16;
    func_020794b4(m, (void *)0x4000400);
}
