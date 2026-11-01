/* NitroSDK OS: starts a V-count alarm; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Alarm {
    void (*handler)(void *arg);
    void *arg;
    int pad8;
    u32 frame;
    short fire;
    short delay;
    struct Alarm *prev;
    struct Alarm *next;
    int period;
    int pad20;
    int canceled;
} Alarm;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void OS_Terminate(void);
extern u32 func_0207bc70(int count);
extern void func_0207c088(Alarm *alarm);

void func_0207bf58(Alarm *alarm, int count, int delay, void (*handler)(void *), void *arg) {
    int mask = OS_DisableInterrupts();
    int now;
    u32 frame;
    if (alarm == 0 || alarm->handler != 0) {
        OS_Terminate();
    }
    now = *(volatile u16 *)0x04000006;
    frame = func_0207bc70(now);
    alarm->period = 1;
    alarm->fire = count;
    if (count <= now) {
        frame++;
    }
    alarm->frame = frame;
    alarm->delay = delay;
    alarm->handler = handler;
    alarm->arg = arg;
    alarm->canceled = 0;
    func_0207c088(alarm);
    OS_RestoreInterrupts(mask);
}
