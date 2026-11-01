/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void func_0207aa98(void *thread, void (*func)(void *), void *arg, void *stack, unsigned stackSize, unsigned prio);
extern void OS_WakeupThreadDirect(void *thread);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02075de0(void *arg);
extern void *data_020c5248;
extern char data_020c524c;
extern char data_020c5670;
extern void MI_CpuFill8(void *dest, unsigned char val, unsigned int size);
void CTRDGi_InitTaskThread(char *p);
void func_02075ecc(void *dest);

void CTRDGi_InitTaskThread(char *p) {
    int state = OS_DisableInterrupts();
    if (data_020c5248 == 0) {
        data_020c5248 = p;
        func_02075ecc(p + 0xc4);
        func_02075ecc(&data_020c524c);
        *(int *)(p + 0xc0) = 0;
        func_0207aa98(p, func_02075de0, p, &data_020c5670, 0x400, 0x14);
        OS_WakeupThreadDirect(p);
    }
    OS_RestoreInterrupts(state);
}

void func_02075ecc(void *dest)
{
    MI_CpuFill8(dest, 0, 0x24);
}
