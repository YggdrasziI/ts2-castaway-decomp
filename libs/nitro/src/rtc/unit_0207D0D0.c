/* NitroSDK: seconds since 2000 from a date and a time; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef long long s64;

extern int func_0207d164(const void *date);
extern int func_0207d148(const void *time);

s64 func_0207d0d0(const void *date, const void *time) {
    int days = func_0207d164(date);
    int seconds;
    if (days == -1) {
        return -1;
    }
    seconds = func_0207d148(time);
    if (seconds == -1) {
        return -1;
    }
    return (s64)days * 86400 + seconds;
}
