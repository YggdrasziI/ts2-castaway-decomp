/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
typedef struct {
    u16 field0;
    u16 field2;
    u16 field4;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u16 fieldC;
    u16 fieldE;
    u16 field10;
    u16 field12;
    u16 field14;
    u16 field16;
    u16 field18;
} VRAMState;
extern VRAMState data_020c5700;
void GX_InitGXState(void);

void GX_InitGXState(void) {
    VRAMState *state = &data_020c5700;
    state->field0 = 0;
    state->field2 = 0;
    state->field4 = 0;
    state->field6 = 0;
    state->field8 = 0;
    state->fieldA = 0;
    state->fieldC = 0;
    state->fieldE = 0;
    state->field10 = 0;
    state->field12 = 0;
    state->field14 = 0;
    state->field16 = 0;
    state->field18 = 0;

    /* VRAMCNT_A..D */
    *(volatile u32 *)0x04000240 = 0;
    /* VRAMCNT_E */
    *(volatile u8 *)0x04000244 = 0;
    /* VRAMCNT_F */
    *(volatile u8 *)0x04000245 = 0;
    /* VRAMCNT_G */
    *(volatile u8 *)0x04000246 = 0;
    /* VRAMCNT_H, VRAMCNT_I (WRAMCNT at 0x04000247 left untouched) */
    *(volatile u16 *)0x04000248 = 0;
}
