/* NitroSDK OS: V-count alarm interrupt handler; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Alarm {
    void (*handler)(void *arg);
    void *arg;
    int pad8;
    int frame;
    short fire;
    short pad12;
    int pad14[2];
    int period;
    int pad20;
    int canceled;
} Alarm;

extern unsigned char data_027e0000[];
extern Alarm *data_020c5abc;
extern int data_020c5ab8;

extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_ResetRequestIrqMask(u32 mask);
extern int func_0207bc70(int count);
extern int func_0207bcbc(Alarm *alarm, int frame, int count);
extern void func_0207bf14(Alarm *alarm);
extern void func_0207c004(Alarm *alarm);
extern void func_0207c03c(Alarm *alarm);

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)
#define REG_VCOUNT (*(volatile u16 *)0x04000006)

static inline int func_eq(void) {
    u16 v = REG_DISPSTAT;
    return ((v >> 8) & 0xff) | ((v << 1) & 0x100);
}

void func_0207bd0c(void) {
    Alarm *alarm;
    OS_DisableIrqMask(4);
    REG_DISPSTAT &= ~0x20;
    *(volatile u32 *)((u32)data_027e0000 + 0x3ff8) |= 4;
    func_0207bc70(func_eq() - 1);
    while ((alarm = data_020c5abc) != 0) {
        u16 count = REG_VCOUNT;
        int frame = func_0207bc70(count);
        switch (func_0207bcbc(alarm, frame, count)) {
        case 0:
            func_0207bf14(alarm);
            count = REG_VCOUNT;
            if (alarm->fire != count) {
                return;
            }
            if (alarm->frame != frame) {
                return;
            }
            OS_DisableIrqMask(4);
            REG_DISPSTAT &= ~0x20;
            OS_ResetRequestIrqMask(4);
        case 1: {
            void (*handler)(void *) = alarm->handler;
            func_0207c004(alarm);
            alarm->handler = 0;
            if (handler) {
                handler(alarm->arg);
            }
            if (alarm->period && !alarm->canceled) {
                alarm->handler = handler;
                alarm->frame = data_020c5ab8 + 1;
                func_0207c03c(alarm);
            }
            break;
        }
        case 2:
            func_0207c004(alarm);
            func_0207c03c(alarm);
            alarm->frame = data_020c5ab8 + 1;
            break;
        }
    }
}
