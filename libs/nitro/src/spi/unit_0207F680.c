/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef unsigned int vu32_;
extern void PMi_ExecuteList(void *list);
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 s);
extern u32 OS_DisableIrqMask(u32 m);
extern u32 OS_SetIrqMask(u32 m);
extern int func_0207584c(void);
extern int PM_GetLCDPower(void);
extern u32 PM_GetBackLight(int *top, int *bottom);
extern u32 func_0207fa6c(int target, int sw);
extern u32 func_0207fdc0(u16 trigger, u16 key);
extern void OS_Halt(void);
extern void OS_SpinWait(u32 cycles);
extern int func_0207f590(int mode, int led, int skip, int sync);
extern u32 func_0207fb38(int led);
extern void func_0207f980(void);
extern void *data_020c774c;
extern void *data_020c7754;
#define IME (*(volatile u16 *)0x04000208)
#define IF_ (*(volatile u32 *)0x04000214)
#define DISP (*(volatile u32 *)0x04000000)
#define DISPB (*(volatile u32 *)0x04001000)
static inline u32 VBf(void) { return *(volatile u32 *)0x027ffc3c; }
#define VB VBf()
static inline int disIrq(void) { u16 p = IME; IME = 0; return p; }
static inline int enIrq(void) { u16 p = IME; IME = 1; return p; }
static inline int resIrq(int e) { u16 p = IME; IME = (u16)e; return p; }
void func_0207f680(u32 trigger, u32 logic, u16 key)
{
    int prepIrq;
    u32 prepMode;
    u32 prepMask;
    int off = 0;
    int top, bottom;
    u32 gx, gxs;
    int lcd;

    PMi_ExecuteList(data_020c774c);
    prepIrq = disIrq();
    prepMode = OS_DisableInterrupts();
    prepMask = OS_DisableIrqMask(0x3fffff);
    OS_SetIrqMask(0x40000);
    OS_RestoreInterrupts(prepMode);
    enIrq();
    if (trigger & 8) {
        if (*(const u16 *)0x027ffc40 == 2) {
            trigger &= ~8;
        }
    }
    if (trigger & 0x10) {
        if (!func_0207584c()) {
            trigger &= ~0x10;
        }
    }
    gx = DISP;
    gxs = DISPB;
    lcd = PM_GetLCDPower();
    PM_GetBackLight(&top, &bottom);
    func_0207fa6c(2, 0);
    {
        volatile u32 v = VB;
        while (v == VB) {
        }
        v = VB;
        DISP = DISP & ~0x30000;
        DISPB &= ~0x10000;
        while (v == VB) {
        }
        v = VB;
        while (v == VB) {
        }
    }
    {
        u16 param = (u16)(trigger | top << 5 | bottom << 6);
        while (func_0207fdc0(param, (u16)(logic | key)) != 0) {
        }
    }
    OS_Halt();
    OS_SpinWait(0x996a00);
    if ((trigger & 8) && (IF_ & 0x100000)) {
        off = 1;
    }
    if (!off) {
        if (lcd == 1) {
            func_0207f590(1, 1, 1, 0);
        } else {
            func_0207fb38(1);
        }
        DISP = gx;
        DISPB = gxs;
    }
    OS_DisableInterrupts();
    OS_SetIrqMask(prepMask);
    OS_RestoreInterrupts(prepMode);
    resIrq(prepIrq);
    if (off) {
        func_0207f980();
    }
    PMi_ExecuteList(data_020c7754);
}
