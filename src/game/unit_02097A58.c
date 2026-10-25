/*
 * Unit 0x02097A58-0x02097B6C: 20.12 fixed-point helpers: a 16-bit wrapper, square
 * roots through the hardware divider/root unit (64-bit and 32-bit), a tail call and
 * an arc cosine read from a 2049-entry table (data_020b38e8, angle 0x8000 = pi)
 * with linear interpolation.
 *
 * Bounds: hypothesis. Before 0x02097A58 lies unit_02097434.cpp (touch screen
 * state); 0x02097B6C starts unit_02097B6C.cpp (3x3 matrix). The table is only used
 * here but stays in the original binary for now. Real file name unknown.
 */

typedef long long s64;
typedef unsigned short u16;
typedef unsigned long u32;

#define REG_SQRTCNT (*(volatile u16 *)0x040002B0)
#define REG_SQRT_RESULT (*(volatile u32 *)0x040002B4)
#define REG_SQRT_PARAM (*(volatile s64 *)0x040002B8)
#define REG_SQRT_PARAM_L (*(volatile u32 *)0x040002B8)

extern int func_02077c7c(int x);
extern int func_02077c44(int x);
extern const int data_020b38e8[];
extern const int data_020b38ec[];

short func_02097a58(int x) {
    return func_02077c7c(x);
}

int func_02097a6c(s64 x) {
    if (x <= 0) {
        return 0;
    }
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (x << 12) + 0x800;
    while (REG_SQRTCNT & 0x8000) {
    }
    return REG_SQRT_RESULT;
}

int func_02097acc(int x) {
    if (x <= 0) {
        return 0;
    }
    REG_SQRTCNT = 0;
    REG_SQRT_PARAM_L = x;
    while (REG_SQRTCNT & 0x8000) {
    }
    return REG_SQRT_RESULT;
}

int func_02097b08(int x) {
    return func_02077c44(x);
}

int func_02097b14(int x) {
    int i;
    int frac;
    int v;

    if (x < -0x1000 || x > 0x1000) {
        return 0;
    }
    i = (x + 0x1000) >> 2;
    frac = x & 3;
    v = data_020b38e8[i];
    if (frac == 0) {
        return v;
    }
    return v + (((data_020b38ec[i] - v) * frac) >> 2);
}
