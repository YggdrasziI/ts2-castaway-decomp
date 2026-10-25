/*
 * Unit 0x020973BC-0x02097434: one set-up function. It calls three other functions,
 * clears the five words of data_020c8034 and the two eight-entry u16 arrays
 * data_020c8048 / data_020c8058, and resets data_020bd56c to 0xFFFF (also its
 * initial value). No other code reads these objects directly.
 *
 * mwccarm sorts a file's .bss objects by increasing size, so the 20-byte
 * data_020c8034 could not precede the two 16-byte arrays if they were defined here:
 * the arrays belong to another file and stay in the original binary for now.
 *
 * Bounds: hypothesis. Before 0x020973BC lies unit_020970E0.cpp (button state);
 * 0x02097434 starts unit_02097434.cpp (touch screen state). The data lie between the
 * two neighbours' data. Real file name unknown.
 */

typedef unsigned short u16;

struct Unk020c8034 {
    int a;
    int b;
    int c;
    int d;
    int e;
};

extern "C" void func_0207f390();
extern "C" void func_0207ff64();
extern "C" void func_0207f968(int x);

extern u16 data_020c8048[8];
extern u16 data_020c8058[8];

int data_020bd56c = 0xffff;
Unk020c8034 data_020c8034;

void func_020973bc() {
    int i;

    func_0207f390();
    func_0207ff64();
    func_0207f968(1);
    data_020c8034.d = 0;
    data_020c8034.c = 0;
    data_020bd56c = 0xffff;
    data_020c8034.e = 0;
    data_020c8034.b = 0;
    data_020c8034.a = 0;
    for (i = 0; i < 8; i++) {
        data_020c8058[i] = 0;
        data_020c8048[i] = 0;
    }
}
