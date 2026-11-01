/* NitroSDK: V-count alarm system initialisation; written from the ROM. File bounds are a hypothesis. */
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
extern u16 data_020c5ab0;
extern int data_020c5ab4;
extern int data_020c5ab8;
extern u32 OS_DisableIrqMask(u32 mask);

void func_0207c124(void) {
    if (data_020c5ab0) {
        return;
    }
    data_020c5ab0 = 1;
    data_020c5abc.head = 0;
    data_020c5abc.tail = 0;
    OS_DisableIrqMask(4);
    data_020c5ab8 = 0;
    data_020c5ab4 = 0;
}
