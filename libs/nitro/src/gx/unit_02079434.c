/* NitroSDK: applies the mode table entry; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned short u16;

typedef struct {
    u16 a;
    u16 b;
    u16 c;
} Entry;

extern const Entry data_020b32fc[];
extern const Entry data_020b32fe[];
extern const Entry data_020b3300[];
extern int data_020c5728;
extern int data_020c571c;
extern int data_020c572c;
extern int data_020c5730;
extern int func_020781f4(void);

void func_02079434(void) {
    int n = func_020781f4();
    data_020c5728 = n;
    data_020c571c = data_020b32fc[n].a << 12;
    data_020c572c = data_020b32fe[n].a << 12;
    data_020c5730 = data_020b3300[n].a << 12;
}
