/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
typedef struct {
    unsigned short field_00;
    unsigned short field_02;
    unsigned short field_04;
    unsigned short field_06;
} Rec;
typedef struct {
    u16 f0;
    u16 f1;
} Pair;
typedef struct {
    char pad_00[0x30];
    u16 field_34;
} Data_02046390;
typedef struct {
    s32 aX;
    s32 pad_04;
    s32 bX;
    s32 aY;
    s32 pad_10;
    s32 bY;
} Coef;
extern Data_02046390 data_020c76e8;
extern Coef data_020c7700;
void func_0207e6cc(Rec *out, Rec *in);

void func_0207e6cc(Rec *out, Rec *in) {
    if (data_020c76e8.field_34 == 0) {
        *(Pair *)&out->field_00 = *(Pair *)&in->field_00;
        *(Pair *)&out->field_04 = *(Pair *)&in->field_04;
        return;
    }

    {
        Coef *coef = &data_020c7700;

        out->field_04 = in->field_04;
        out->field_06 = in->field_06;

        if (in->field_04 == 0) {
            out->field_00 = 0;
            out->field_02 = 0;
            return;
        }

        {
            int x0 = in->field_00 << 2;
            s64 diff0 = (s64)x0 - coef->aX;
            s32 v0 = (s32)((coef->bX * diff0) >> 22);

            out->field_00 = (u16)v0;
            if ((short)out->field_00 < 0) {
                out->field_00 = 0;
            } else if ((short)out->field_00 > 0xff) {
                out->field_00 = 0xff;
            }

            {
                int x1 = in->field_02 << 2;
                s64 diff1 = (s64)x1 - coef->aY;
                s32 v1 = (s32)((coef->bY * diff1) >> 22);

                out->field_02 = (u16)v1;
                if ((short)out->field_02 < 0) {
                    out->field_02 = 0;
                    return;
                }
                if ((short)out->field_02 > 0xbf) {
                    out->field_02 = 0xbf;
                }
            }
        }
    }
}
