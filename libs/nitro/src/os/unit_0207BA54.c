/* NitroSDK; Advance Wars' Exception_RunUserHook (CC0), symbols renamed for this ROM.
 * Calls the user exception handler (if set) with the context record and its argument,
 * in system mode, with the protection unit on around the call. Written as an asm
 * function: it switches mode with msr and carries sp across the switch. File bounds
 * are a hypothesis. */
#pragma force_active on

extern unsigned int data_020c5a10;
extern unsigned int data_020c5a14;
extern unsigned int data_020c5a1c;
extern void OS_EnableProtectionUnit(void);
extern void OS_DisableProtectionUnit(void);

asm void func_0207ba54(void)
{
    stmdb sp!, {lr}
    sub sp, sp, #4
    ldr r0, =data_020c5a10
    ldr r0, [r0, #0]
    cmp r0, #0
    addeq sp, sp, #4
    ldmeqia sp!, {lr}
    bxeq lr
    mov r0, sp
    ldr r1, =0x9f
    msr CPSR_fsxc, r1
    mov sp, r0
    bl OS_EnableProtectionUnit
    ldr r1, =data_020c5a14
    ldr r0, =data_020c5a10
    ldr r1, [r1, #0]
    ldr r2, [r0, #0]
    ldr r0, =data_020c5a1c
    blx r2
    bl OS_DisableProtectionUnit
    add sp, sp, #4
    ldmia sp!, {lr}
    bx lr
}
