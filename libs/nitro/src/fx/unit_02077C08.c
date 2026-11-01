/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



const short data_020b31e8[130] = {
    0, 81, 163, 244, 326, 407, 489, 570, 651, 732, 813, 894,
    975, 1056, 1136, 1217, 1297, 1377, 1457, 1537, 1617, 1696, 1775, 1854,
    1933, 2012, 2090, 2168, 2246, 2324, 2401, 2478, 2555, 2632, 2708, 2784,
    2860, 2935, 3010, 3085, 3159, 3233, 3307, 3380, 3453, 3526, 3599, 3670,
    3742, 3813, 3884, 3955, 4025, 4095, 4164, 4233, 4302, 4370, 4438, 4505,
    4572, 4639, 4705, 4771, 4836, 4901, 4966, 5030, 5094, 5157, 5220, 5282,
    5344, 5406, 5467, 5528, 5589, 5649, 5708, 5768, 5826, 5885, 5943, 6000,
    6058, 6114, 6171, 6227, 6282, 6337, 6392, 6446, 6500, 6554, 6607, 6660,
    6712, 6764, 6815, 6867, 6917, 6968, 7018, 7068, 7117, 7166, 7214, 7262,
    7310, 7358, 7405, 7451, 7498, 7544, 7589, 7635, 7679, 7724, 7768, 7812,
    7856, 7899, 7942, 7984, 8026, 8068, 8110, 8151, 8192, 0,
};
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
