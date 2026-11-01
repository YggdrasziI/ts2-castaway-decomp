/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* func_02074700: backup sector size from the card context (+0x1c). */

extern int *data_020c4800;

int func_02074700(void) {
    return *(int *)((char *)data_020c4800 + 0x1c);
}
