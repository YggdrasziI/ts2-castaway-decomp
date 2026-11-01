/* NitroSDK OS: tick timer interrupt; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned short u16;

extern volatile unsigned long long data_020c5aa8;
extern int data_020c5aa4;
extern void func_0207a0dc(int a, void (*func)(void), int b);

void func_0207bb4c(void) {
    data_020c5aa8++;
    if (data_020c5aa4) {
        *(volatile u16 *)0x04000102 = 0;
        *(volatile u16 *)0x04000100 = 0;
        *(volatile u16 *)0x04000102 = 0xc1;
        data_020c5aa4 = 0;
    }
    func_0207a0dc(0, func_0207bb4c, 0);
}
