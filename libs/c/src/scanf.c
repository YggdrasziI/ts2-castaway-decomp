// Only __StringRead is linked into this ROM; the formatter and sscanf are not.
#include <critical_regions.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strtold.h>
#include <strtoul.h>

#define conversion_buff_size 512
#define conversion_max       509
#define bad_conversion       0xFF

enum argument_options {
    normal_argument,
    char_argument,
    short_argument,
    long_argument,
    intmax_argument,
    u32_argument,
    ptrdiff_argument,
    long_long_argument,
    double_argument,
    long_double_argument,
    wchar_argument
};

typedef unsigned char char_map[32];

typedef struct {
    unsigned char suppress_assignment;
    unsigned char field_width_specified;
    unsigned char argument_options;
    unsigned char conversion_char;
    int           field_width;
    char_map      char_set;
} scan_format;

#define set_char_map(map, ch) map[(unsigned char)ch >> 3] |= (1 << (ch & 7))
#define tst_char_map(map, ch) (map[(unsigned char)ch >> 3] & (1 << (ch & 7)))

int __StringRead(void* isc, int ch, int Action) {
    char         RetVal;
    __InStrCtrl* Iscp = (__InStrCtrl*)isc;
    switch (Action) {
        case __GetAChar:
            RetVal = *(Iscp->NextChar);
            if (RetVal == '\0') {
                Iscp->NullCharDetected = 1;
                return -1;
            } else {
                Iscp->NextChar++;
                return (u8)RetVal;
            }

        case __UngetAChar:
            if (!Iscp->NullCharDetected)
                Iscp->NextChar--;
            else
                Iscp->NullCharDetected = 0;
            return ch;

        case __TestForError:
            return Iscp->NullCharDetected;
    }
    return 0;
}
