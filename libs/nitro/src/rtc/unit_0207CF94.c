/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Sends one RTC command through PXI channel 5; true when the FIFO accepted it. */
extern int func_0207c4f8(int channel, int data, int flag);

int func_0207cf94(int cmd) {
    return func_0207c4f8(5, (cmd << 8) & 0x7f00, 0) >= 0;
}
