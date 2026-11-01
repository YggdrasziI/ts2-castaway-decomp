/* The link strips unused code; these entries have no caller in this ROM. */
#pragma force_active on

void _u32_div_not_0_f(void);
void func_020891e4(void);
asm void func_02089334(void);

/*
 * Unsigned 64-bit division and remainder. Both entries set r4 to choose the
 * result (0 for the quotient, 1 for the remainder) and continue in
 * func_02089334. The functions in this file run into each other, so they
 * must stay in this order.
 */
asm unsigned long long _ll_udiv(unsigned long long dividend, unsigned long long divisor)
{
    stmfd sp!, {r4, r5, r6, r7, r11, r12, lr}
    mov r4, #0
    b func_02089334
}

asm unsigned long long _ull_mod(unsigned long long dividend, unsigned long long divisor)
{
    stmfd sp!, {r4, r5, r6, r7, r11, r12, lr}
    mov r4, #1
}

/* Dividend in r0:r1, divisor in r2:r3. */
asm void func_02089334(void)
{
    orrs r5, r3, r2
    bne @divisor_not_0
    ldmfd sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx lr

@divisor_not_0:
    /* Both high words 0: one 32-bit division gives quotient and remainder. */
    orrs r5, r1, r3
    bne func_020891e4
    mov r1, r2
    bl _u32_div_not_0_f
    cmp r4, #0
    movne r0, r1
    mov r1, #0
    ldmfd sp!, {r4, r5, r6, r7, r11, r12, lr}
    bx lr
}
