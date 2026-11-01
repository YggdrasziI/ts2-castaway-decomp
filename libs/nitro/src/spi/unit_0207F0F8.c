/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Sends one RTC command through PXI channel 5; true when the FIFO accepted it. */
extern int func_0207c4f8(int channel, int data, int flag);

int func_0207f0f8(int cmd) {
    return func_0207c4f8(9, cmd | 0x3004000, 0) >= 0;
}
