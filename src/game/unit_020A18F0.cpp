/*
 * Unit 0x020A18F0-0x020A1E68: the game clock (static object data_020d6298, 0xC bytes, with its
 * `__sinit`) and its date packed in one word: minute, hour, day and month from 0, year from
 * 1975. Fifteen updates make one game minute.
 *
 * Bounds: hypothesis (the static initializer 0x020AE494 builds the object; after the system
 * object; 0x020A1E68 starts small angle helpers). `.rodata` is the table of month lengths.
 * Layouts come from the code; all names are placeholders. Real file name unknown.
 */
typedef unsigned long u32;
typedef unsigned long long u64;

/* The date (Unk0202071c of include/game/unk_sim.h). */
struct Unk0202071c {
    Unk0202071c() {}
    Unk0202071c(u32 v) : value(v) {}

    int func_minute() const {
        return value & 0x3f;
    }
    int func_hour() const {
        return (value & 0x7c0) >> 6;
    }
    int func_day() const {
        return (value & 0xf800) >> 11;
    }
    int func_month() const {
        return (value & 0xf0000) >> 16;
    }
    int func_year() const {
        return (value & 0xfff00000) >> 20;
    }

    u32 value;
};

/* The part saved with the game (8 bytes). */
struct Unk020a18f0Time {
    /* Through a pointer: `__sinit` keeps the address of the sub-object in a register. */
    Unk020a18f0Time() {
        Unk020a18f0Time *self = this;
        self->date.value = -1;
        self->ticks = 0;
    }

    Unk0202071c date;
    int ticks;
};

class Unk020a18f0 {
public:
    ~Unk020a18f0();

    u32 epoch;
    Unk020a18f0Time time;
};

extern "C" {
void func_020a18f0(Unk020a18f0 *o);
void func_020a194c(Unk020a18f0 *o, int ticks);
void func_020a1994(Unk020a18f0 *o, void *save);
void func_020a19b0(Unk020a18f0 *o, void *save);
bool func_020a19cc(Unk020a18f0 *o, int ticks);
Unk0202071c func_020a1a4c(int hour, int minute, int day, int month, int year);
int func_020a1a88(Unk0202071c *date);
u32 func_020a1aa4(Unk0202071c *date);
bool func_020a1b80(int year);
int func_020a1bdc(int month, int year);
Unk0202071c func_020a1c08(Unk0202071c *date, int minutes);
void func_020a1cf4(Unk0202071c *date);
void func_020a1d24(Unk0202071c *date);
void func_020a1d58(Unk0202071c *date);
void func_020a1db8(Unk0202071c *date);
void func_020a1dec(Unk0202071c *date);
void func_020a4dc4(void *save, void *data, int size);
void func_020a4e14(void *save, void *data, int size);
extern Unk020a18f0 data_020d6298;
}

static const int data_020b59c4[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

extern "C" void func_020a18f0(Unk020a18f0 *o) {
    o->time.date = func_020a1a4c(8, 0, 1, 1, 2007);
    o->epoch = 0;
    o->epoch = func_020a1aa4(&o->time.date);
    o->time.ticks = 0;
}

extern "C" void func_020a194c(Unk020a18f0 *o, int ticks) {
    if (ticks > 0) {
        o->time.ticks += ticks;
    }
    while (o->time.ticks >= 15) {
        o->time.ticks -= 15;
        func_020a1cf4(&o->time.date);
    }
}

extern "C" void func_020a1994(Unk020a18f0 *o, void *save) {
    func_020a4dc4(save, &o->time.date, 8);
}

extern "C" void func_020a19b0(Unk020a18f0 *o, void *save) {
    func_020a4e14(save, &o->time.date, 8);
}

extern "C" bool func_020a19cc(Unk020a18f0 *o, int ticks) {
    Unk0202071c later = func_020a1c08(&o->time.date, (o->time.ticks + ticks) / 15);
    return (o->time.date.func_hour() >= 6) != (later.func_hour() >= 6);
}

Unk020a18f0::~Unk020a18f0() {}

extern "C" Unk0202071c func_020a1a4c(int hour, int minute, int day, int month, int year) {
    return Unk0202071c(((year - 1975) << 20) + ((month - 1) << 16) + ((day - 1) << 11) +
                       (hour << 6) + minute);
}

extern "C" int func_020a1a88(Unk0202071c *date) {
    return date->func_hour() * 60 + date->func_minute();
}

extern "C" u32 func_020a1aa4(Unk0202071c *date) {
    int year = date->func_year();
    int day = date->func_day();
    int month = date->func_month();
    int days = day;
    for (int i = 0; i < month; i++) {
        days += data_020b59c4[i];
    }
    int fullYear = year + 1975;
    int leaps = fullYear / 4;
    leaps -= fullYear / 100;
    leaps += fullYear / 400;
    if (func_020a1b80(fullYear) && (month == 0 || (month == 1 && day < 28))) {
        leaps--;
    }
    int total = (fullYear - 1) * 365 + days;
    total += leaps;
    return total - data_020d6298.epoch;
}

extern "C" bool func_020a1b80(int year) {
    if ((year & 3) == 0) {
        if (year % 400 == 0) {
            return true;
        }
        return year % 100 != 0;
    }
    return false;
}

extern "C" int func_020a1bdc(int month, int year) {
    if (month != 1) {
        return data_020b59c4[month];
    }
    return func_020a1b80(year + 1975) + 28;
}

extern "C" Unk0202071c func_020a1c08(Unk0202071c *date, int minutes) {
    u32 value = date->value;
    int minute = value & 0x3f;
    int hour = (value & 0x7c0) >> 6;
    int day = (value & 0xf800) >> 11;
    int month = (value & 0xf0000) >> 16;
    int year = (value & 0xfff00000) >> 20;
    while (minutes > 0) {
        minute += minutes;
        if (minute >= 60) {
            hour++;
            minutes = minute - 60;
            minute = 0;
            if (hour >= 24) {
                day++;
                hour = 0;
                if (day >= func_020a1bdc(month, year)) {
                    month++;
                    day = 0;
                    if (month > 12) {
                        year++;
                        month = 0;
                        if (year > 6071) {
                            return Unk0202071c(-1);
                        }
                    }
                }
            }
        } else {
            minutes = 0;
        }
    }
    return Unk0202071c((year << 20) + (month << 16) + (day << 11) + (hour << 6) + minute);
}

extern "C" void func_020a1cf4(Unk0202071c *date) {
    if (date->func_minute() != 59) {
        date->value += 1;
    } else {
        date->value &= ~0x3f;
        func_020a1d24(date);
    }
}

extern "C" void func_020a1d24(Unk0202071c *date) {
    if (date->func_hour() != 23) {
        date->value += 0x40;
    } else {
        date->value &= ~0x7c0;
        func_020a1d58(date);
    }
}

extern "C" void func_020a1d58(Unk0202071c *date) {
    int last = func_020a1bdc(date->func_month(), date->func_year());
    int day = date->func_day();
    if (day == last - 1) {
        date->value &= ~0xf800;
        func_020a1db8(date);
    } else {
        date->value += 0x800;
    }
}

extern "C" void func_020a1db8(Unk0202071c *date) {
    if (date->func_month() != 11) {
        date->value += 0x10000;
    } else {
        date->value &= ~0xf0000;
        func_020a1dec(date);
    }
}

extern "C" void func_020a1dec(Unk0202071c *date) {
    if (date->func_year() != 6070) {
        date->value += 0x100000;
    }
}

extern "C" int func_020a1e1c(Unk0202071c *a, Unk0202071c *b) {
    u64 first = (u64)func_020a1aa4(b) * 1440;
    first += func_020a1a88(b);
    u64 second = (u64)func_020a1aa4(a) * 1440;
    second += func_020a1a88(a);
    return second - first;
}

Unk020a18f0 data_020d6298;
