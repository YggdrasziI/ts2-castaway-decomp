/* NitroSDK CARD: writes a command to the card registers; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned char u8;
typedef unsigned int u32;

#define REG8(a) (*(volatile u8 *)(a))

void func_0207509c(u32 a, u32 b) {
    while (*(volatile u32 *)0x040001a4 & 0x80000000) {
    }
    REG8(0x040001a1) = 0xc0;
    REG8(0x040001a8) = a >> 24;
    REG8(0x040001a9) = a >> 16;
    REG8(0x040001aa) = a >> 8;
    REG8(0x040001ab) = a;
    REG8(0x040001ac) = b >> 24;
    REG8(0x040001ad) = b >> 16;
    REG8(0x040001ae) = b >> 8;
    REG8(0x040001af) = b;
}
