/* NitroSDK OS: inserts a V-count alarm in its sorted list; written from the ROM. File bounds are a hypothesis. */
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
extern Alarm *data_020c5abc;
extern void func_0207bf14(Alarm *alarm);
extern void func_0207c03c(Alarm *alarm);

void func_0207c088(Alarm *alarm) {
    Alarm *t;
    for (t = data_020c5abc; t != 0; t = t->next) {
        if (t->frame < alarm->frame) {
            continue;
        }
        if (t->frame == alarm->frame && t->fire <= alarm->fire) {
            continue;
        }
        {
            Alarm *prev = t->prev;
            alarm->prev = prev;
            alarm->next = t;
            t->prev = alarm;
            if (prev != 0) {
                prev->next = alarm;
                return;
            }
            data_020c5abc = alarm;
            func_0207bf14(alarm);
            return;
        }
    }
    func_0207c03c(alarm);
}
