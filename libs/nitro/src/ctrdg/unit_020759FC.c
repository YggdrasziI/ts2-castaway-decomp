/* NitroSDK; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

extern void CpuSet(const void *src, void *dst, unsigned int control);

/* Tail call of the BIOS copy (Thumb, through ip). */
void func_020759fc(const void *src, void *dst, unsigned int control) {
    CpuSet(src, dst, control);
}
