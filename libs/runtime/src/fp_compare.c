/* The link strips unused code; these entries have no caller in this ROM. */
#pragma force_active on

void func_02080430(void);
void func_020804c0(void);
void func_02085744(void);
asm void func_020876c8(void);
asm void func_02087710(void);
asm void func_02087744(void);
asm void func_02087784(void);
asm void func_020877c4(void);
asm void func_020878c8(void);
asm void func_02087978(void);
asm void func_020879a0(void);
asm void func_020879a8(void);
asm void func_020879b0(void);
asm void func_020879d8(void);
asm void func_020879e0(void);
asm void func_02087a64(void);
asm void func_02087a78(void);
asm void _dls(void);
asm void _deq(void);
asm void func_02087bc0(void);
asm void func_02087be4(void);
asm void func_02087c10(void);
asm void func_02087d18(void);
asm void func_02087d4c(void);
asm void func_02087dd8(void);
asm void func_02087dec(void);
asm void func_02087df8(void);
asm void func_02087e30(void);
asm void func_02087e68(void);
asm void _fgr(void);
asm void func_02087ed8(void);

/*
 * Compares of doubles and floats, written from this ROM (Advance Wars has the same
 * operations in another order). The invalid tails are duplicated by the original;
 * the code after some returns is unreachable. A label reached from another block is
 * its own function, as the assembler has no global labels. The word table at
 * func_02087a64 is read with explicit pc offsets for the same reason.
 */

asm void func_020876c8(void)
{
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bcs L_020876ec
    cmn ip, r3, lsl #0x1
    bcs L_02087700
L_020876dc:
    mov r0, #0x1
    bx lr
    mov r0, #0
    bx lr
L_020876ec:
    bne func_02087978
    cmp r0, #0
    bhi func_02087978
    cmn ip, r3, lsl #0x1
    bcc L_020876dc
L_02087700:
    bne func_020879a0
    cmp r2, #0
    bhi func_020879a0
    b L_020876dc
}

asm void func_02087710(void)
{
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    ldmfd sp!, {lr}
    bx lr
}

asm void func_02087744(void)
{
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
}

asm void func_02087784(void)
{
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
}

asm void func_020877c4(void)
{
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    orr r0, r0, #0x20000000
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    orr r0, r0, #0x20000000
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    and r0, r0, #0
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    ldmfd sp!, {r0}
    mrs r0, cpsr
    bic r0, r0, #0x20000000
    msr cpsr_f, r0
    ldmfd sp!, {lr}
    bx lr
}

asm void func_020878c8(void)
{
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    add sp, sp, #0x4
    movs ip, #0x1
    ldmfd sp!, {lr}
    bx lr
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    add sp, sp, #0x4
    mov ip, #0xff000000
    adds ip, ip, #0x10000000
    ldmfd sp!, {lr}
    bx lr
    stmfd sp!, {ip, lr}
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr lr, [ip, #0]
    tst lr, #0x100
    bne func_02087a78
    orr lr, lr, #0x1
    str lr, [ip, #0]
    add sp, sp, #0x4
    mov ip, #0
    adds ip, ip, #0
    ldmfd sp!, {lr}
    bx lr
}

asm void func_02087978(void)
{
    tst r1, #0x80000
    beq func_02087710
    stmfd sp!, {ip}
    mov ip, #0x200000
    cmn ip, r3, lsl #0x1
    ldmfd sp!, {ip}
    bcc func_020879a8
    bne func_020879a0
    cmp r2, #0
    beq func_020879a8
}

asm void func_020879a0(void)
{
    tst r3, #0x80000
    beq func_02087710
}

asm void func_020879a8(void)
{
    mov r0, ip
    bx lr
}

asm void func_020879b0(void)
{
    tst r1, #0x80000
    beq func_02087744
    stmfd sp!, {ip}
    mov ip, #0x200000
    cmn ip, r3, lsl #0x1
    ldmfd sp!, {ip}
    bcc func_020879e0
    bne func_020879d8
    cmp r2, #0
    beq func_020879e0
}

asm void func_020879d8(void)
{
    tst r3, #0x80000
    beq func_02087744
}

asm void func_020879e0(void)
{
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    msr cpsr_f, r0
    bx lr
    tst r1, #0x80000
    beq func_02087784
    stmfd sp!, {ip}
    mov ip, #0x200000
    cmn ip, r3, lsl #0x1
    ldmfd sp!, {ip}
    bcc L_02087a20
    bne L_02087a18
    cmp r2, #0
    beq L_02087a20
L_02087a18:
    tst r3, #0x80000
    beq func_02087744
L_02087a20:
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    msr cpsr_f, r0
    bx lr
    tst r1, #0x80000
    beq func_020878c8
    stmfd sp!, {ip}
    mov ip, #0x200000
    cmn ip, r3, lsl #0x1
    ldmfd sp!, {ip}
    bcc L_02087a60
    bne L_02087a58
    cmp r2, #0
    beq L_02087a60
L_02087a58:
    tst r3, #0x80000
    beq func_020878c8
L_02087a60:
    bx lr
}

asm void func_02087a64(void)
{
    stmfd sp!, {lr}
    ldr r2, [pc, #0x20]
    bl func_02080430
    ldmfd sp!, {lr}
    bx lr
}

asm void func_02087a78(void)
{
    ldr ip, [pc, #0x14]
    stmfd sp!, {ip}
    bl func_020804c0
    add sp, sp, #0x8
    ldmfd sp!, {lr}
    bx lr
L_02087a90:
    dcd 0x4000049
L_02087a94:
    dcd 0x40000c9
}

asm void _dls(void)
{
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bcs L_02087b10
    cmn ip, r3, lsl #0x1
    bcs L_02087b24
L_02087aac:
    orrs ip, r3, r1
    bmi L_02087adc
    cmp r1, r3
    cmpeq r0, r2
    movcc r0, #0x1
    movcs r0, #0
    bx lr
    mov r0, #0
    mrs ip, cpsr
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
L_02087adc:
    orr ip, r0, ip, lsl #0x1
    orrs ip, ip, r2
    moveq r0, #0
    bne L_02087afc
    mrs ip, cpsr
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bxeq lr
L_02087afc:
    cmp r3, r1
    cmpeq r2, r0
    movcc r0, #0x1
    movcs r0, #0
    bx lr
L_02087b10:
    bne func_020877c4
    cmp r0, #0
    bhi func_020877c4
    cmn ip, r3, lsl #0x1
    bcc L_02087aac
L_02087b24:
    bne func_020877c4
    cmp r2, #0
    bhi func_020877c4
    b L_02087aac
}

asm void _deq(void)
{
    mov ip, #0x200000
    cmn ip, r1, lsl #0x1
    bcs L_02087b9c
    cmn ip, r3, lsl #0x1
    bcs L_02087bb0
L_02087b48:
    orrs ip, r3, r1
    bmi L_02087b78
    cmp r1, r3
    cmpeq r0, r2
    moveq r0, #0x1
    movne r0, #0
    bx lr
    mov r0, #0
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
L_02087b78:
    orr ip, r0, ip, lsl #0x1
    orrs ip, ip, r2
    moveq r0, #0x1
    bxeq lr
    cmp r3, r1
    cmpeq r2, r0
    moveq r0, #0x1
    movne r0, #0
    bx lr
L_02087b9c:
    bne func_020879b0
    cmp r0, #0
    bhi func_020879b0
    cmn ip, r3, lsl #0x1
    bcc L_02087b48
L_02087bb0:
    bne func_020879d8
    cmp r2, #0
    bhi func_020879d8
    b L_02087b48
}

asm void func_02087bc0(void)
{
    mov r3, #0xff000000
    cmp r3, r0, lsl #0x1
    bcc func_02087dd8
    cmp r3, r1, lsl #0x1
    bcc func_02087dec
    mov r0, #0x1
    bx lr
    mov r0, #0
    bx lr
}

asm void func_02087be4(void)
{
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mov r0, r2
    bx lr
}

asm void func_02087c10(void)
{
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs r0, cpsr
    bic r0, r0, #0x40000000
    msr cpsr_f, r0
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs ip, cpsr
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    orr ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs ip, cpsr
    bic ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
}

asm void func_02087d18(void)
{
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mrs ip, cpsr
    and ip, ip, #0
    msr cpsr_f, ip
    bx lr
}

asm void func_02087d4c(void)
{
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    movs r2, #0x1
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mov r2, #0xff000000
    adds r2, r2, #0x10000000
    bx lr
    stmfd sp!, {r0, r1, r2, r3, lr}
    bl func_02085744
    mov ip, r0
    ldmfd sp!, {r0, r1, r2, r3, lr}
    ldr r3, [ip, #0]
    tst r3, #0x100
    bne func_02087a64
    orr r3, r3, #0x1
    str r3, [ip, #0]
    mov r2, #0
    adds r2, r2, #0
    bx lr
}

asm void func_02087dd8(void)
{
    tst r0, #0x400000
    beq func_02087be4
    cmp r3, r1, lsl #0x1
    movcs r0, r2
    bxcs lr
}

asm void func_02087dec(void)
{
    tst r1, #0x400000
    beq func_02087be4
    bx lr
}

asm void func_02087df8(void)
{
    tst r0, #0x400000
    beq func_02087c10
    cmp r3, r1, lsl #0x1
    bcc L_02087e18
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
L_02087e18:
    tst r1, #0x400000
    beq func_02087c10
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
}

asm void func_02087e30(void)
{
    tst r0, #0x400000
    beq func_02087c10
    cmp r3, r1, lsl #0x1
    bcc L_02087e50
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
L_02087e50:
    tst r1, #0x400000
    beq func_02087c10
    mrs ip, cpsr
    bic ip, ip, #0x40000000
    msr cpsr_f, ip
    bx lr
}

asm void func_02087e68(void)
{
    tst r0, #0x400000
    beq func_02087d4c
    cmp r3, r1, lsl #0x1
    bcc L_02087e80
    movs r2, #0x1
    bx lr
L_02087e80:
    tst r1, #0x400000
    beq func_02087d4c
    movs r2, #0x1
    bx lr
}

asm void _fgr(void)
{
    mov r3, #0xff000000
    cmp r3, r0, lsl #0x1
    cmpcs r3, r1, lsl #0x1
    bcc func_02087d18
    cmp r0, #0
    bicmi r0, r0, #0x80000000
    rsbmi r0, r0, #0
    cmp r1, #0
    bicmi r1, r1, #0x80000000
    rsbmi r1, r1, #0
    cmp r0, r1
    movgt r0, #0x1
    movle r0, #0
    mrs ip, cpsr
    bicle ip, ip, #0x20000000
    orrgt ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
}

asm void func_02087ed8(void)
{
    mov r0, #0
    mrs ip, cpsr
    bic ip, ip, #0x20000000
    msr cpsr_f, ip
    bx lr
}
