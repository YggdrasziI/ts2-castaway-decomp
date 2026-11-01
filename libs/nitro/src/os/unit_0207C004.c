/* NitroSDK: removes an alarm from the list; written from the ROM. File bounds are a hypothesis. */
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

void func_0207c004(Alarm *alarm) {
    Alarm *prev;
    Alarm *next;
    if (alarm == 0) {
        return;
    }
    next = alarm->next;
    prev = alarm->prev;
    if (next != 0) {
        next->prev = prev;
    } else {
        data_020c5abc.tail = prev;
    }
    if (prev != 0) {
        prev->next = next;
    } else {
        data_020c5abc.head = next;
    }
}
