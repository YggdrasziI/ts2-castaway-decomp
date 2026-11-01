/* NitroSDK RTC: days since 2000 from a date; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;

typedef struct {
    u32 year;
    u32 month;
    u32 day;
    int week;
} Date;

extern const u32 data_020bcb88[];

int func_0207d164(const Date *date) {
    u32 year = date->year;
    u32 month;
    u32 day;
    int days;
    if (year >= 100 || (month = date->month) < 1 || month > 12 || (day = date->day) < 1 || day > 31 || date->week >= 7 || month < 1 || month > 12) {
        return -1;
    }
    days = day - 1 + data_020bcb88[month];
    if (month >= 3 && (year & 3) == 0) {
        days++;
    }
    return year * 365 + days + ((year + 3) >> 2);
}
