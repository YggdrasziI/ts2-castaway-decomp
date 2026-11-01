/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Spin while the masked bits of the halfword at data_020c76e8+0x3a stay set. */
extern char data_020c76e8;

void func_0207e6b4(unsigned int mask) {
    while (*(volatile unsigned short *)(&data_020c76e8 + 0x36) & mask) {
    }
}
