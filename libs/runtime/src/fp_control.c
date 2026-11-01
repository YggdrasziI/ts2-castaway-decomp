/* Status word helpers. Hypothesis: the file name. */

/* The link strips unused code; this entry has no caller in this ROM's game data. */
#pragma force_active on

unsigned int* func_02085744(void);
unsigned int* func_02085750(void);

/* Clears `mask`, toggles `bits` and returns the old status word. */
asm unsigned int func_02089758(unsigned int mask, unsigned int bits)
{
    stmfd sp!, {r0, r1, r2, ip, lr}
    bl func_02085744
    mov r3, r0
    ldmfd sp!, {r0, r1, r2, ip, lr}
    ldr r2, [r3]
    bic ip, r2, r0
    eor ip, ip, r1
    str ip, [r3]
    mov r0, r2
    bx lr
}

/* Clears the status word and the trap handlers. */
asm void func_02089780(void)
{
    stmfd sp!, {lr}
    bl func_02085744
    mov r1, #0
    str r1, [r0]
    bl func_02085750
    mov r1, #0
    str r1, [r0, #4]
    str r1, [r0, #8]
    str r1, [r0, #0xc]
    str r1, [r0, #0x10]
    str r1, [r0, #0x14]
    ldmfd sp!, {lr}
    bx lr
}
