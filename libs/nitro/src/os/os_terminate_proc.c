/* NitroSDK os_terminate_proc.c: halt and terminate.
 *
 * Bounds 0x0207C3A8-0x0207C3C8: after a data initializer (OSi_InitVramExclusive), before a
 * tail call (func_0207c3c8). Byte-identical to khdays-decomp's (CC0) versions, see
 * notes/PROVENANCE.md; file name from khdays' citation of the NitroSDK source.
 */

extern int OS_DisableInterrupts(void);

asm void OS_Halt(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
    bx lr
}

void OS_Terminate(void)
{
    for (;;) {
        OS_DisableInterrupts();
        OS_Halt();
    }
}
