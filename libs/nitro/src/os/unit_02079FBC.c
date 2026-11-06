/* NitroSDK; khdays' OSi_InitStackChecker (CC0), retyped for this ROM, after the empty
 * function before it (functions in reverse address order). File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;

extern unsigned char data_027e0000[];
extern void SDK_IRQ_STACKSIZE(void); /* link-time constant, 0x400 in this ROM */

#define HW_DTCM_IRQ_STACK_END ((u32)data_027e0000 + 0x3f80)
#define OSi_IRQ_STACK_BOTTOM HW_DTCM_IRQ_STACK_END
#define OSi_IRQ_STACK_TOP (OSi_IRQ_STACK_BOTTOM - (u32)SDK_IRQ_STACKSIZE)

void func_02079fc0(void) {
    *(u32 *)(OSi_IRQ_STACK_BOTTOM - 4) = 0xfddb597dUL;
    *(u32 *)(OSi_IRQ_STACK_TOP) = 0x7bf9dd5bUL;
}

void func_02079fbc(void) {}
