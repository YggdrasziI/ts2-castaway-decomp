/* NitroSDK; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

extern void WaitByLoop(int count);

/* Tail call of the BIOS wait loop (Thumb, through ip). */
void func_02075438(int count) {
    WaitByLoop(count);
}
