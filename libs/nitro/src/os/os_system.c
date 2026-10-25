/* NitroSDK os_system.c: CPSR interrupt masks, processor mode, spin wait.
 *
 * Bounds 0x0207C194-0x0207C224 (hypothesis: the file may go on past OS_SpinWait;
 * OS_Halt at 0x0207C3A8 is in os_terminate_proc.c). Each function is
 * byte-identical to khdays-decomp's (CC0) version, see notes/PROVENANCE.md. File
 * name from khdays' citation of the NitroSDK source.
 */

#define HW_PSR_IRQ_DISABLE     0x80
#define HW_PSR_IRQ_FIQ_DISABLE 0xc0
#define HW_PSR_CPU_MODE_MASK   0x1f

typedef unsigned int OSIntrMode;
typedef unsigned int OSProcMode;

asm OSIntrMode OS_EnableInterrupts(void)
{
    mrs r0, cpsr
    bic r1, r0, #HW_PSR_IRQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_DISABLE
    bx lr
}

asm OSIntrMode OS_DisableInterrupts(void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_IRQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_DISABLE
    bx lr
}

asm OSIntrMode OS_RestoreInterrupts(register OSIntrMode state)
{
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_IRQ_DISABLE
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_IRQ_DISABLE
    bx lr
}

asm OSIntrMode OS_DisableInterrupts_IrqAndFiq(void)
{
    mrs r0, cpsr
    orr r1, r0, #HW_PSR_IRQ_FIQ_DISABLE
    msr cpsr_c, r1
    and r0, r0, #HW_PSR_IRQ_FIQ_DISABLE
    bx lr
}

asm OSIntrMode OS_RestoreInterrupts_IrqAndFiq(register OSIntrMode state)
{
    mrs r1, cpsr
    bic r2, r1, #HW_PSR_IRQ_FIQ_DISABLE
    orr r2, r2, r0
    msr cpsr_c, r2
    and r0, r1, #HW_PSR_IRQ_FIQ_DISABLE
    bx lr
}

asm OSIntrMode OS_GetCpsrIrq(void)
{
    mrs r0, cpsr
    and r0, r0, #HW_PSR_IRQ_DISABLE
    bx lr
}

asm OSProcMode OS_GetProcMode(void)
{
    mrs r0, cpsr
    and r0, r0, #HW_PSR_CPU_MODE_MASK
    bx lr
}

asm void OS_SpinWait(register unsigned int cycles)
{
@1:
    subs r0, r0, #4
    bhs @1
    bx lr
}
