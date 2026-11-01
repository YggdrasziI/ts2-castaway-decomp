/* NitroSDK: appends an alarm to the list; written from the ROM. File bounds are a hypothesis. */
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
extern void func_0207bf14(Alarm *alarm);

void func_0207c03c(Alarm *alarm) {
    Alarm *prev = data_020c5abc.tail;
    alarm->prev = prev;
    alarm->next = 0;
    data_020c5abc.tail = alarm;
    if (prev != 0) {
        prev->next = alarm;
        return;
    }
    data_020c5abc.head = alarm;
    func_0207bf14(alarm);
}
