/*
 * ITCM unit 0x01FF8BEC-0x01FF8D84: functions of the model (Unk02089f38,
 * include/game/unk_model.h) placed in ITCM. func_01ff8bec reloads the data block
 * and size from the file and writes the first element set into the data;
 * func_01ff8c64 sends the data block to the geometry FIFO, either with
 * func_01ff8270 or with DMA 0 in geometry FIFO mode, and its interrupt handler
 * func_01ff8d4c calls the callback stored with it once the transfer is done.
 *
 * Bounds: hypothesis. 0x01FF8BEC follows the ITCM functions of the animation;
 * func_01ff8d4c shares the two globals of func_01ff8c64; the model functions
 * from 0x01FF8D84 (unit_01FF8D84.cpp) may belong to this file too. The callback
 * and its argument (data_020c7d20, data_020c7d1c) are in the main module's .bss
 * and stay there. The functions keep C linkage and their addresses as names. No
 * data. Real file name unknown.
 */

#include "game/unk_matrix.h"
#include "game/unk_model.h"

/* Source, destination and control registers of DMA 0. */
struct Unk01ff8becDma {
    u32 src;
    u32 dest;
    u32 ctrl;
};


extern "C" {
extern void (*data_020c7d20)(int);
extern int data_020c7d1c;

void func_01ff8270(int dma, const void *src, u32 size);
void func_02079748(int dma);
void func_0207a174(int mask, void (*handler)());
void OS_EnableIrqMask(int mask);
void func_01ff9404(Unk0208adc0 *set, void *data, Unk020bd014 *file);
void func_01ff8dac(Unk02089f38 *model, const Unk02098094 *mtx);

int func_01ff8d30(void);
void func_01ff8d4c(void);

void func_01ff8bec(Unk02089f38 *model) {
    if (model->file == 0) {
        return;
    }
    model->data = model->file->func_020954b4();
    model->size = model->file->func_020954dc();
    func_01ff9404(&model->setA, model->data, model->file);
}

void func_01ff8c38(Unk02089f38 *model, const Unk02098094 *mtx) {
    if (model->file == 0) {
        return;
    }
    func_01ff8bec(model);
    func_01ff8dac(model, mtx);
}

int func_01ff8c64(Unk02089f38 *model, int async, void (*callback)(int), int arg) {
    if (func_01ff8d30()) {
        return 0;
    }
    if (model->file == 0) {
        return 0;
    }
    data_020c7d20 = callback;
    data_020c7d1c = arg;
    if (model->size == 0) {
        return 0;
    }
    if (async == 0) {
        func_01ff8270(0, model->data, model->size);
        func_02079748(0);
        func_01ff8d4c();
    } else {
        func_02079748(0);
        volatile Unk01ff8becDma *dma = (volatile Unk01ff8becDma *)0x040000B0;
        dma->src = (u32)model->data;
        dma->dest = 0x04000400;
        func_0207a174(0x100, func_01ff8d4c);
        OS_EnableIrqMask(0x100);
        dma->ctrl = ((int)model->size >> 2) + 0xFC400000;
    }
    return 1;
}

int func_01ff8d30(void) {
    return data_020c7d20 != 0;
}

void func_01ff8d4c(void) {
    void (*callback)(int) = data_020c7d20;
    int arg = data_020c7d1c;
    data_020c7d20 = 0;
    data_020c7d1c = 0;
    if (callback != 0) {
        callback(arg);
    }
}
}
