/* NitroSDK os_context.c: thread context initialisation, save and load.
 *
 * Bounds 0x0207AFE0-0x0207B0DC: after the thread queue functions, before
 * func_0207b0dc. Sources: khdays-decomp (CC0), see notes/PROVENANCE.md; file name
 * from khdays' citation of the NitroSDK source.
 */

#define HW_PSR_SVC_MODE      0x13
#define HW_PSR_SYS_MODE      0x1f
#define HW_PSR_CPU_MODE_MASK 0x1f
#define HW_PSR_FIQ_DISABLE   0x40
#define HW_PSR_IRQ_DISABLE   0x80
#define HW_PSR_ARM_STATE     0x0
#define HW_PSR_THUMB_STATE   0x20
#define HW_SVC_STACK_SIZE    0x40

#define OS_CONTEXT_CPSR       0
#define OS_CONTEXT_R0         4
#define OS_CONTEXT_R1         8
#define OS_CONTEXT_R2         12
#define OS_CONTEXT_R3         16
#define OS_CONTEXT_R4         20
#define OS_CONTEXT_R5         24
#define OS_CONTEXT_R6         28
#define OS_CONTEXT_R7         32
#define OS_CONTEXT_R8         36
#define OS_CONTEXT_R9         40
#define OS_CONTEXT_R10        44
#define OS_CONTEXT_R11        48
#define OS_CONTEXT_R12        52
#define OS_CONTEXT_SP         56
#define OS_CONTEXT_LR         60
#define OS_CONTEXT_PC_PLUS4   64
#define OS_CONTEXT_SP_SVC     68
#define OS_CONTEXT_CP_CONTEXT 72

typedef struct OSContext OSContext;

extern void CP_SaveContext(void);
extern void CPi_RestoreContext(void);

asm void OS_InitContext(register OSContext *context, register unsigned long newpc, register unsigned long newsp)
{
    add r1, r1, #4
    str r1, [r0, #OS_CONTEXT_PC_PLUS4]
    str r2, [r0, #OS_CONTEXT_SP_SVC]
    sub r2, r2, #HW_SVC_STACK_SIZE
    tst r2, #4
    subne r2, r2, #4
    str r2, [r0, #OS_CONTEXT_SP]
    ands r1, r1, #1
    movne r1, #HW_PSR_SYS_MODE | HW_PSR_THUMB_STATE
    moveq r1, #HW_PSR_SYS_MODE | HW_PSR_ARM_STATE
    str r1, [r0, #OS_CONTEXT_CPSR]
    mov r1, #0
    str r1, [r0, #OS_CONTEXT_R0]
    str r1, [r0, #OS_CONTEXT_R1]
    str r1, [r0, #OS_CONTEXT_R2]
    str r1, [r0, #OS_CONTEXT_R3]
    str r1, [r0, #OS_CONTEXT_R4]
    str r1, [r0, #OS_CONTEXT_R5]
    str r1, [r0, #OS_CONTEXT_R6]
    str r1, [r0, #OS_CONTEXT_R7]
    str r1, [r0, #OS_CONTEXT_R8]
    str r1, [r0, #OS_CONTEXT_R9]
    str r1, [r0, #OS_CONTEXT_R10]
    str r1, [r0, #OS_CONTEXT_R11]
    str r1, [r0, #OS_CONTEXT_R12]
    str r1, [r0, #OS_CONTEXT_LR]
    bx lr
}

asm int OS_SaveContext(register OSContext *context)
{
    stmfd sp!, {r0, lr}
    add r0, r0, #OS_CONTEXT_CP_CONTEXT
    ldr r1, =CP_SaveContext
    blx r1
    ldmfd sp!, {r0, lr}
    add r1, r0, #OS_CONTEXT_CPSR
    mrs r2, cpsr
    str r2, [r1], #OS_CONTEXT_R0 - OS_CONTEXT_CPSR
    mov r0, #HW_PSR_SVC_MODE | HW_PSR_IRQ_DISABLE | HW_PSR_FIQ_DISABLE | HW_PSR_ARM_STATE
    msr cpsr_c, r0
    str sp, [r1, #OS_CONTEXT_SP_SVC - OS_CONTEXT_R0]
    msr cpsr_c, r2
    mov r0, #1
    stmia r1, {r0-r14}
    add r0, pc, #8
    str r0, [r1, #OS_CONTEXT_PC_PLUS4 - OS_CONTEXT_R0]
    mov r0, #0
    bx lr
}

asm void OS_LoadContext(register OSContext *context)
{
    stmfd sp!, {r0, lr}
    add r0, r0, #OS_CONTEXT_CP_CONTEXT
    ldr r1, =CPi_RestoreContext
    blx r1
    ldmfd sp!, {r0, lr}
    mrs r1, cpsr
    bic r1, r1, #HW_PSR_CPU_MODE_MASK
    orr r1, r1, #HW_PSR_SVC_MODE | HW_PSR_IRQ_DISABLE | HW_PSR_FIQ_DISABLE
    msr cpsr_c, r1
    ldr r1, [r0], #OS_CONTEXT_R0 - OS_CONTEXT_CPSR
    msr spsr_fsxc, r1
    ldr sp, [r0, #OS_CONTEXT_SP_SVC - OS_CONTEXT_R0]
    ldr lr, [r0, #OS_CONTEXT_PC_PLUS4 - OS_CONTEXT_R0]
    ldmia r0, {r0-r14}^
    nop
    subs pc, lr, #4
}
