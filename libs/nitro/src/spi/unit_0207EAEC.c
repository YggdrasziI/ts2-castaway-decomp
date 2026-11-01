/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 s);
extern int func_0207c4f8(u32 a, u32 b, u32 c);
typedef void (*Callback)(u32, u32, u32);
extern struct { Callback cb; char a[0x30]; volatile u16 err; volatile u16 cmd; } data_020c76e8;
void func_0207eaec(void) {
    u32 ie = OS_DisableInterrupts();
    int ok = func_0207c4f8(6, 0x3000000, 0) >= 0;
    if (!ok) {
        OS_RestoreInterrupts(ie);
        data_020c76e8.err |= 1;
        if (data_020c76e8.cb != 0) {
            data_020c76e8.cb(0, 4, 0);
        }
        return;
    }
    data_020c76e8.cmd |= 1;
    data_020c76e8.err &= ~1;
    OS_RestoreInterrupts(ie);
}
