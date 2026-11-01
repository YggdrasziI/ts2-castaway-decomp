/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int func_0207cdbc(int a, int b, void *c, int d);
extern void func_0207c764(void);
extern void func_0207c74c(void);
extern int data_020c5b6c[];

int func_0207cd78(int param_1, int b) {
    int r = func_0207cdbc(param_1, b, func_0207c764, 0);
    data_020c5b6c[8] = r;
    if (r == 0) func_0207c74c();
    return data_020c5b6c[8];
}
