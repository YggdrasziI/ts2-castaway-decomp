/* NitroSDK RTC: seconds of a time; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    int hour;
    int minute;
    int second;
} Time;

int func_0207d148(const Time *time) {
    return (time->hour * 60 + time->minute) * 60 + time->second;
}
