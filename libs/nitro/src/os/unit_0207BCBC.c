/* NitroSDK: state of an alarm against the current frame and line; written from the ROM. File bounds are a hypothesis. */
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

int func_0207bcbc(Alarm *alarm, int frame, int count) {
    int frames = frame - alarm->frame;
    int lines = count - alarm->fire;
    if (frames < 0 || (frames == 0 && lines < 0)) {
        return 0;
    }
    if (lines < 0) {
        lines += 0x107;
    }
    return lines <= alarm->delay ? 1 : 2;
}
