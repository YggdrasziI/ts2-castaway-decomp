/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/hw.h"
#include "sdk/pxi.h"
#include "sdk/os.h"

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_ResetRequestIrqMask(unsigned int mask);
extern void func_0207a174(unsigned int mask, void *fn);
extern void OS_EnableIrqMask(unsigned int mask);
extern void func_0207c3d4(void);
extern unsigned short data_020c5ae4;
extern void *data_020c5ae8[];
void func_0207c640(void);
void func_0207c5d4(int tag, void *callback);
BOOL PXI_IsCallbackReady(int fifotag, PXIProc proc);

void func_0207c640(void) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned short *sync = (volatile unsigned short *)0x04000180;
    int *shared = (int *)0x027ffc00;
    int i;
    int timeout;
    int mark;
    int count;
    if (data_020c5ae4 == 0) {
        data_020c5ae4 = 1;
        shared[0xe2] = 0;
        for (i = 0; i < 0x20; i++) {
            data_020c5ae8[i] = 0;
        }
        *(volatile unsigned short *)0x04000184 = 0xc408;
        OS_ResetRequestIrqMask(0x40000);
        func_0207a174(0x40000, (void *)&func_0207c3d4);
        OS_EnableIrqMask(0x40000);
        count = 0;
        for (;;) {
            mark = *sync & 0xf;
            *sync = (unsigned short)(mark << 8);
            if (mark == 0 && count > 4) {
                break;
            }
            timeout = 1000;
            while ((*sync & 0xf) == mark) {
                if (timeout <= 0) {
                    count = 0;
                    break;
                }
                timeout--;
            }
            count++;
            }
    }
    OS_RestoreInterrupts(enabled);
}

void func_0207c5d4(int tag, void *callback) {
    int enabled = OS_DisableInterrupts();
    int *shared = (int *)0x027ffc00;
    data_020c5ae8[tag] = callback;
    if (callback != 0) {
        shared[0xe2] |= 1 << tag;
    } else {
        shared[0xe2] &= ~(1 << tag);
    }
    OS_RestoreInterrupts(enabled);
}

BOOL PXI_IsCallbackReady(int fifotag, PXIProc proc)
{
    OSSystemWork *p = OS_GetSystemWork();
    return (p->pxiHandleChecker[proc] & (1UL << fifotag)) ? TRUE : FALSE;
}
