/* NitroSDK; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

extern int func_02073f44(void);

/* Tail call through ip (interworking). */
int func_020745ac(void) {
    return func_02073f44();
}
