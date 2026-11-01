/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int func_0207ce90(int a, void *b, int c);
extern void func_0207c764(void);
extern void func_0207c74c(void);
extern int data_020c5b6c[];
int func_0207ce4c(int param_1);

int func_0207ce4c(int param_1) {
    int r = func_0207ce90(param_1, func_0207c764, 0);
    data_020c5b6c[8] = r;
    if (r == 0) func_0207c74c();
    return data_020c5b6c[8];
}
