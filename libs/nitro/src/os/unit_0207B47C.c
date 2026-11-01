/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern void OS_InitArena(void);
extern void func_0207c3c8(void);
extern void func_0207a4e4(void);
extern void func_0207b74c(void);
extern void func_0207a204(void);
extern void func_02079fc0(void);
extern void func_0207bac0(void);
extern void MI_Init(void);
extern void func_0207c124(void);
extern void OSi_InitVramExclusive(void);
extern void func_0207aba0(void);
extern void func_0207c290(void);
extern void func_02075d10(void);
extern void func_02074a30(void);
extern void func_0207ff64(void);
void func_0207b47c(void) {
    OS_InitArena();
    func_0207c3c8();
    func_0207a4e4();
    func_0207b74c();
    func_0207a204();
    func_02079fc0();
    func_0207bac0();
    MI_Init();
    func_0207c124();
    OSi_InitVramExclusive();
    func_0207aba0();
    func_0207c290();
    func_02075d10();
    func_02074a30();
    func_0207ff64();
}
