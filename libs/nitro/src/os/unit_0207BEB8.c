/* NitroSDK: cancels a V-count alarm; written from the ROM. File bounds are a hypothesis. */
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

typedef struct {
    Alarm *head;
    Alarm *tail;
} List;

extern List data_020c5abc;
extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void func_0207c004(Alarm *alarm);

void func_0207beb8(Alarm *alarm) {
    int mask = OS_DisableInterrupts();
    alarm->canceled = 1;
    if (alarm->handler == 0) {
        OS_RestoreInterrupts(mask);
        return;
    }
    func_0207c004(alarm);
    alarm->handler = 0;
    OS_RestoreInterrupts(mask);
}
