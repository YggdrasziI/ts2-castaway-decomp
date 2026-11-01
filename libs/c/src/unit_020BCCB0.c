/* MSL C locale tables, data only. Word arrays: the field layout is not known. */
#pragma force_active on

extern unsigned long __mbtowc_noconv[];
extern unsigned long __wctomb_noconv[];
extern unsigned long data_020bcce8[];
extern unsigned long data_020bcda8[];
extern unsigned long data_020bcdc0[];
extern unsigned long data_020bcdcc[];
extern unsigned long data_020bcddc[];
extern unsigned long data_020bce34[];
extern unsigned long data_020bcca0[];
extern unsigned long data_020bcca8[];

unsigned long data_020bccb0[2] = {
    (unsigned long)&__mbtowc_noconv, (unsigned long)&__wctomb_noconv,
};

unsigned long data_020bccb8[4] = {
    0x00000020, 0x0000006E, 0x00000000, (unsigned long)&data_020bcce8,
};

unsigned long data_020bccc8[8] = {
    (unsigned long)&data_020bcca8, (unsigned long)&data_020bcdcc, (unsigned long)&data_020bcdc0, (unsigned long)&data_020bcda8,
    (unsigned long)&data_020bcca0[1], (unsigned long)&data_020bcddc, (unsigned long)&data_020bce34, (unsigned long)&data_020bcca0,
};
