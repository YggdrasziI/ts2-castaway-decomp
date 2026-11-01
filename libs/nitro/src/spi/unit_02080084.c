/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int OS_GetCpsrIrq(void);
extern void func_0207c3d4(void);

extern int data_020c7758;

void func_02080084(void) {
    int *p = &data_020c7758;
    if (*p == 0) return;
    do {
        if (OS_GetCpsrIrq() == 0x80) {
            func_0207c3d4();
        }
    } while (*p != 0);
}
