/* NitroSDK IRQ handler and thread switch on IRQ return, placed in ITCM (OS).
 *
 * Bounds 0x01FF831C-0x01FF84D0 (hypothesis: the DMA functions of
 * unit_01FF8114.c before; the EA animation code of unit_01FF84D0.cpp after).
 * func_01ff831c finds the highest pending enabled interrupt, acknowledges it and
 * jumps to its handler in the DTCM table data_027e0000, returning to
 * func_01ff8374, which wakes the threads waiting for an interrupt and switches
 * to the thread to run, saving and restoring the coprocessor context
 * (CP_SaveContext / CPi_RestoreContext). Hand-written assembly. Written for this
 * project; no reference matches these functions, so their names and the file name
 * are unknown.
 */

extern unsigned long data_027e0000[];
extern unsigned long data_027e0060[];
extern unsigned short data_020c57b0[];
extern void CP_SaveContext(void *context);
extern void CPi_RestoreContext(void *context);
void func_01ff8374(void);

asm void func_01ff831c(void)
{
    stmdb   sp!, {lr}
    mov     ip, #0x4000000
    add     ip, ip, #0x210
    ldr     r1, [ip, #-8]
    cmp     r1, #0
    ldmeqia sp!, {pc}
    ldmia   ip, {r1, r2}
    ands    r1, r1, r2
    ldmeqia sp!, {pc}
    mov     r3, #0x80000000
@1:
    clz     r0, r1
    bics    r1, r1, r3, lsr r0
    bne     @1
    mov     r1, r3, lsr r0
    str     r1, [ip, #4]
    rsbs    r0, r0, #0x1f
    ldr     r1, =data_027e0000
    ldr     r0, [r1, r0, lsl #2]
    ldr     lr, =func_01ff8374
    bx      r0
}

asm void func_01ff8374(void)
{
    ldr     ip, =data_027e0060
    mov     r3, #0
    ldr     ip, [ip, #0]
    mov     r2, #1
    cmp     ip, #0
    beq     @2
@1:
    str     r2, [ip, #0x64]
    str     r3, [ip, #0x78]
    str     r3, [ip, #0x7c]
    ldr     r0, [ip, #0x80]
    str     r3, [ip, #0x80]
    mov     ip, r0
    cmp     ip, #0
    bne     @1
    ldr     ip, =data_027e0060
    str     r3, [ip, #0]
    str     r3, [ip, #4]
    ldr     ip, =data_020c57b0
    mov     r1, #1
    strh    r1, [ip, #0]
@2:
    ldr     ip, =data_020c57b0
    ldrh    r1, [ip, #0]
    cmp     r1, #0
    ldreq   pc, [sp], #4
    mov     r1, #0
    strh    r1, [ip, #0]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    add     r2, ip, #8
    ldr     r1, [r2, #0]
@3:
    cmp     r1, #0
    ldrneh  r0, [r1, #0x64]
    cmpne   r0, #1
    ldrne   r1, [r1, #0x68]
    bne     @3
    cmp     r1, #0
    bne     @5
@4:
    mov     r3, #0x92
    msr     cpsr_c, r3
    ldr     pc, [sp], #4
@5:
    ldr     r0, [ip, #4]
    cmp     r1, r0
    beq     @4
    ldr     r3, [ip, #0xc]
    cmp     r3, #0
    beq     @6
    stmdb   sp!, {r0, r1, ip}
    mov     lr, pc
    bx      r3
    ldmia   sp!, {r0, r1, ip}
@6:
    str     r1, [ip, #4]
    mrs     r2, spsr
    str     r2, [r0, #0]!
    stmdb   sp!, {r0, r1}
    add     r0, r0, #0
    add     r0, r0, #0x48
    ldr     r1, =CP_SaveContext
    blx     r1
    ldmia   sp!, {r0, r1}
    ldmib   sp!, {r2, r3}
    stmib   r0!, {r2, r3}
    ldmib   sp!, {r2, r3, ip, lr}
    stmib   r0!, {r2-r14}^
    stmib   r0!, {lr}
    mov     r3, #0xd3
    msr     cpsr_c, r3
    stmib   r0!, {sp}
    stmdb   sp!, {r1}
    add     r0, r1, #0
    add     r0, r0, #0x48
    ldr     r1, =CPi_RestoreContext
    blx     r1
    ldmia   sp!, {r1}
    ldr     sp, [r1, #0x44]
    mov     r3, #0xd2
    msr     cpsr_c, r3
    ldr     r2, [r1, #0]!
    msr     spsr_fc, r2
    ldr     lr, [r1, #0x40]
    ldmib   r1, {r0-r14}^
    nop
    stmda   sp!, {r0, r1, r2, r3, ip, lr}
    ldmia   sp!, {pc}
}
