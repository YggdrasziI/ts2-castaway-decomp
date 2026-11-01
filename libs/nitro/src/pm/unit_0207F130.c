/* NitroSDK PM: PXI reply handler; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned short u16;
typedef void (*Callback)(int result, void *arg);

typedef struct {
    int lock;
    Callback callback;
    void *arg;
    int pad;
    Callback alarm;
    void *alarmArg;
    u16 *status;
} Work;

extern Work data_020c7724;
static inline void func_finish(int result) {
    Callback callback;
    if (data_020c7724.lock) {
        data_020c7724.lock = 0;
    }
    callback = data_020c7724.callback;
    if (callback) {
        void *arg = data_020c7724.arg;
        data_020c7724.callback = 0;
        callback(result, arg);
    }
}

void func_0207f130(int tag, unsigned int data, int error) {
    int result;
    u16 code;
    u16 command;
    if (error) {
        func_finish(6);
    }
    code = data & 0xff;
    command = (data & 0x7f00) >> 8;
    switch (code) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 4;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 5;
        break;
    case 4:
        result = 1;
        break;
    default:
        result = 6;
        break;
    }
    if (command == 0x51) {
        if (data_020c7724.alarm) {
            data_020c7724.alarm(result, data_020c7724.alarmArg);
        }
        return;
    }
    if (command == 0x40) {
        if (data_020c7724.status) {
            *data_020c7724.status = *(u16 *)0x027fff94;
        }
    }
    func_finish(result);
}
