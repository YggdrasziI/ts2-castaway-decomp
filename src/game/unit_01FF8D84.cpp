/*
 * ITCM unit 0x01FF8D84-0x01FF9098: functions of the model (Unk02089f38,
 * include/game/unk_model.h) that write 4x4 matrices into its data at the offsets
 * of the file's matrix records. func_01ff8dac writes the given matrix (4x4) and,
 * when the model has a transform set (Unk0208be3c, include/game/unk_xform.h), the
 * record's matrix with its translation scaled (4x3) and the first element set's
 * scale; func_01ff8fd8 writes the identity (4x3) when the transform set is
 * dropped by func_01ff8d84.
 *
 * Bounds: hypothesis. Before 0x01FF8D84 lie the other ITCM model functions
 * (unit_01FF8BEC.cpp): no boundary is visible, the two may be one file;
 * 0x01FF9098 starts unit_01FF9098.cpp. The functions keep C linkage and their
 * addresses as names. No data. Real file name unknown.
 * Not complete: func_01ff8dac is at 93.53 % (comment above it).
 */

#include "game/unk_model.h"
#include "game/unk_xform.h"

typedef unsigned char u8;

/* A record of the file's matrix block (0x10 bytes): offsets into the data. */
struct Unk01ff8dacRecord {
    int offset0;
    int offset4;
    int offset8;
    int index;
};

extern "C" {
void func_01ff8fd8(Unk02089f38 *model);

void func_01ff8d84(Unk02089f38 *model, Unk0208be3c *xform) {
    if (xform == 0 && model->xform != 0) {
        func_01ff8fd8(model);
    }
    model->xform = xform;
}

/*
 * 93.53 %: register allocation. The original keeps the model in r10, the matrix
 * argument in r9 and the scale factor in r8 (ours: r9, r8, r10), and loads the
 * translation with one ldm before the three products. Tried: declaration orders,
 * a wrapper or pointer for the matrix copy, scaling helpers taking the vector by
 * value or by reference, the products in both orders, a data pointer local.
 */
void func_01ff8dac(Unk02089f38 *model, const Unk02098094 *mtx) {
    const Unk01ff8dacRecord *rec = (const Unk01ff8dacRecord *)model->file->func_02095558();
    if (rec == 0) {
        return;
    }
    int count = model->file->func_02095580();
    Unk0208be3cMtx *mtxs = 0;
    Unk0208adc0Scale scale = model->setA.scale;
    int mtxCount = 0;
    if (model->xform != 0) {
        mtxs = model->xform->func_0208c048();
        mtxCount = model->xform->func_0208c040();
    }
    while (count-- != 0) {
        int *dst0 = (int *)((u8 *)model->data + rec->offset0);
        int *dst4 = (int *)((u8 *)model->data + rec->offset4);
        int *dst8 = (int *)((u8 *)model->data + rec->offset8);
        if (model->xform != 0 && mtxs != 0 && rec->index < mtxCount) {
            Unk02098094 m = mtxs[rec->index].m;
            int s = model->unk18;
            Unk02098ff0 r;
            Unk02098ff0 t = m.func_020982a8();
            r.z = func_fxmul(t.z, s);
            r.y = func_fxmul(t.y, s);
            r.x = func_fxmul(t.x, s);
            m.func_020982bc(r);
            for (int i = 0, k = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    dst4[k] = m.m[i][j];
                    k++;
                }
            }
            dst8[0] = scale.v.x * model->unk14 >> 12;
            dst8[1] = scale.v.y * model->unk14 >> 12;
            dst8[2] = scale.v.z * model->unk14 >> 12;
        }
        for (int i = 0, k = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dst0[k] = mtx->m[i][j];
                k++;
            }
        }
        rec++;
    }
}

void func_01ff8fd8(Unk02089f38 *model) {
    int count = model->file->func_02095580();
    if (count == 0) {
        return;
    }
    const Unk01ff8dacRecord *rec = (const Unk01ff8dacRecord *)model->file->func_02095558();
    if (rec == 0) {
        return;
    }
    Unk02098094 m = Unk02098094::func_02098254();
    while (count-- != 0) {
        int *dst = (int *)((u8 *)model->data + rec->offset4);
        for (int i = 0, k = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                dst[k] = m.m[i][j];
                k++;
            }
        }
        rec++;
    }
}
}
