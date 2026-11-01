/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/hw.h"
#include "sdk/os.h"
#define func_0200302c func_0207ba54
#define OSi_ExContext                data_020c5a1c
#define OSi_DebuggerHandler          data_020c5a18
extern OSiExContext data_020c5a1c;
extern void func_0207ba54(void);
extern void *data_020c5a18;
asm void func_0207b9c4 (void);
asm void func_0207b9b0(void);
asm void func_0207b93c (void);

asm void func_0207b93c (void)
{
    ldr r12, = OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0
    movne lr, pc
    bxne r12
    ldr r12, = HW_ITCM_END
    stmfd r12 !, {r0 - r3, sp, lr}
    and r0, sp, #1
    mov sp, r12
    mrs r1, CPSR
    and r1, r1, #0x1f
    teq r1, #0x17
    bne @10
    bl func_0207b9b0
    b usr_return
@10:
    teq r1, #0x1b
    bne usr_return
    bl func_0207b9b0
usr_return:
    ldr r12, = OSi_DebuggerHandler
    ldr r12, [r12]
    cmp r12, #0
@1:
    beq @1
@2:
    mov r0, r0
    b @2
    ldmfd sp !, {r0 - r3, r12, lr}
    mov sp, r12
    bx lr
}

asm void func_0207b9b0(void)
{
    stmdb sp!, {r0, lr}
    bl func_0207b9c4
    bl func_0207ba54
    ldmia sp!, {r0, lr}
    bx lr
}

asm void func_0207b9c4 (void)
{
    ldr r1, = OSi_ExContext;
    mrs r2, CPSR
    str r2, [r1, #OSiExContext.debug[1]]
    str r0, [r1, #OSiExContext.exinfo]
    ldr r0, [r12, #0]
    str r0, [r1, #OS_CONTEXT_R0]
    ldr r0, [r12, #4]
    str r0, [r1, #OS_CONTEXT_R1]
    ldr r0, [r12, #8]
    str r0, [r1, #OS_CONTEXT_R2]
    ldr r0, [r12, #12]
    str r0, [r1, #OS_CONTEXT_R3]
    ldr r2, [r12, #16]
    bic r2, r2, #1
    add r0, r1, #OS_CONTEXT_R4
    stmia r0, {r4 - r11}
    str r12, [r1, #OSiExContext.debug[0]]
    ldr r0, [r2, #0]
    str r0, [r1, #OSiExContext.cp15]
    ldr r3, [r2, #4]
    str r3, [r1, #OS_CONTEXT_CPSR]
    ldr r0, [r2, #8]
    str r0, [r1, #OS_CONTEXT_R12]
    ldr r0, [r2, #12]
    str r0, [r1, #OS_CONTEXT_PC_PLUS4]
    mrs r0, CPSR
    orr r3, r3, #0x80
    bic r3, r3, #0x20
    msr CPSR_cxsf, r3
    str sp, [r1, #OS_CONTEXT_R13]
    str lr, [r1, #OS_CONTEXT_R14]
    mrs r2, SPSR
    str r2, [r1, #OSiExContext.debug[3]]
    msr CPSR_cxsf, r0
    bx lr
}
