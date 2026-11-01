/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207c3c8();
extern void func_0207c5d4(int fifoNo, void (*cb)(int, unsigned));
extern void func_0207553c(int, unsigned);
extern int data_020c5064[];

void func_020755bc(void) {
    func_0207c3c8();
    func_0207c5d4(0xe, func_0207553c);
    data_020c5064[0] = 0;
}
