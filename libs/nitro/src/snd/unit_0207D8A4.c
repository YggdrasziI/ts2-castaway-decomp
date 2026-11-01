/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int s);
extern int data_020c5bb4;
extern int data_020c5bb0;
extern int data_020c5bcc;
int func_0207d8a4(void) {
    int s = OS_DisableInterrupts();
    int r;
    if (data_020c5bb4 == 0) {
        r = data_020c5bb0;
    } else {
        r = data_020c5bcc;
    }
    OS_RestoreInterrupts(s);
    return r;
}
