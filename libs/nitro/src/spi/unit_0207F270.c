/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern int func_0207f2b4(int a, int b, void *c, int d);
extern void func_0207f0e8(void);
extern void func_0207f0d0(void);
extern int data_020c7724[];

int func_0207f270(int param_1, int b) {
    int r = func_0207f2b4(param_1, b, func_0207f0e8, 0);
    data_020c7724[3] = r;
    if (r == 0) func_0207f0d0();
    return data_020c7724[3];
}
