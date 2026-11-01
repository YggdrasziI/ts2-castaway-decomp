/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern const short data_020b31e8[130];
extern void func_02077b94(int numer, int denom);
extern void func_02077bcc(int numer, int denom);
int FX_Atan2Idx(int x, int y);
int func_02077c60(int numer, int denom);
int func_02077c44(int numer, int denom);
int FX_GetDivResult(void);

int FX_Atan2Idx(int x, int y)
{
    int numer;
    int denom;
    int base;
    int add;

    if (x > 0) {
        if (y > 0) {
            if (y > x) {
                numer = x;
                denom = y;
                base = 0;
                add = 1;
            } else if (y < x) {
                numer = y;
                denom = x;
                base = 0x4000;
                add = 0;
            } else {
                return 0x2000;
            }
        } else if (y < 0) {
            int ny = -y;

            if (ny < x) {
                numer = ny;
                denom = x;
                base = 0x4000;
                add = 1;
            } else if (ny > x) {
                numer = x;
                denom = ny;
                base = 0x8000;
                add = 0;
            } else {
                return 0x6000;
            }
        } else {
            return 0x4000;
        }
    } else if (x < 0) {
        int nx = -x;

        if (y < 0) {
            int ny = -y;

            if (ny > nx) {
                numer = nx;
                denom = ny;
                base = -0x8000;
                add = 1;
            } else if (ny < nx) {
                numer = ny;
                denom = nx;
                base = -0x4000;
                add = 0;
            } else {
                return 0xa000;
            }
        } else if (y > 0) {
            if (y < nx) {
                numer = y;
                denom = nx;
                base = -0x4000;
                add = 1;
            } else if (y > nx) {
                numer = nx;
                denom = y;
                base = 0;
                add = 0;
            } else {
                return 0xe000;
            }
        } else {
            return 0xc000;
        }
    } else {
        if (y >= 0) {
            return 0;
        }
        return 0x8000;
    }

    if (denom == 0) {
        return 0;
    }
    if (add) {
        return (unsigned short)(base + data_020b31e8[func_02077c60(numer, denom) >> 5]);
    }
    return (unsigned short)(base - data_020b31e8[func_02077c60(numer, denom) >> 5]);
}

int func_02077c60(int numer, int denom) {
    func_02077b94(numer, denom);
    return FX_GetDivResult();
}

int func_02077c44(int numer, int denom) {
    func_02077bcc(numer, denom);
    return FX_GetDivResult();
}

int FX_GetDivResult(void) {
    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    return (int)((*(volatile long long *)0x040002a0 + 0x80000) >> 20);
}
