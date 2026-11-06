/* NitroSDK; written from the ROM. Sends 64 bytes to one fixed address (both stores
 * without write-back). File bounds and module are a hypothesis. */
#pragma force_active on

asm void func_020794b4(register const void *source, register volatile void *destination)
{
    stmfd   sp!, {r4-r8}
    ldmia   r0!, {r2-r8, r12}
    stmia   r1, {r2-r8, r12}
    ldmia   r0!, {r2-r8, r12}
    stmia   r1, {r2-r8, r12}
    ldmfd   sp!, {r4-r8}
    bx      lr
}
