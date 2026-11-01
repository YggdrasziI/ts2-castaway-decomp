/* NitroSDK SND: sends the reserved command list to the ARM7; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void OS_SpinWait(unsigned int cycles);
extern void DC_FlushRange(void *start, unsigned int size);
extern int func_0207c4f8(int tag, void *data, int err);
extern void func_0207d6e0(void);
extern void func_0207dc18(int flags);

extern void *data_020c5bb4;
extern void *data_020c5bb8;
extern int data_020c5bc4;
extern int data_020c5bc8;
extern int data_020c5bcc;
extern void *data_020c5bd0[];
extern unsigned char data_020c5e80[];

int func_0207d974(unsigned int flags) {
    int mask = OS_DisableInterrupts();
    if (data_020c5bb4 == 0) {
        OS_RestoreInterrupts(mask);
        return 1;
    }
    if (data_020c5bc8 >= 8) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(mask);
            return 0;
        }
        do {
            func_0207dc18(1);
        } while (data_020c5bc8 >= 8);
    }
    DC_FlushRange(data_020c5e80, 0x1800);
    if (func_0207c4f8(7, data_020c5bb4, 0) < 0) {
        if (!(flags & 1)) {
            OS_RestoreInterrupts(mask);
            return 0;
        }
        while (func_0207c4f8(7, data_020c5bb4, 0) < 0) {
            OS_RestoreInterrupts(mask);
            OS_SpinWait(100);
            mask = OS_DisableInterrupts();
        }
    }
    if (flags & 2) {
        func_0207d6e0();
    }
    data_020c5bd0[data_020c5bc4] = data_020c5bb4;
    data_020c5bc4++;
    if (data_020c5bc4 > 8) {
        data_020c5bc4 = 0;
    }
    data_020c5bb4 = 0;
    data_020c5bb8 = 0;
    data_020c5bc8++;
    data_020c5bcc++;
    OS_RestoreInterrupts(mask);
    return 1;
}
