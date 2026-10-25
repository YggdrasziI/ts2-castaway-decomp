/* NitroSDK os_protectionRegion.c: protection region permissions and bases (CP15
 * c5, c6).
 *
 * Bounds 0x0207B918-0x0207B93C: after os_protectionUnit.c, before the exception
 * handler (func_0207b93c). Byte-identical to khdays-decomp's (CC0) versions, see
 * notes/PROVENANCE.md; file name from khdays' citation of the NitroSDK source.
 */

asm void OS_SetDPermissionsForProtectionRegion(register unsigned long setMask, register unsigned long flags)
{
    mrc p15, 0, r2, c5, c0, 2
    bic r2, r2, r0
    orr r2, r2, r1
    mcr p15, 0, r2, c5, c0, 2
    bx lr
}

asm void OS_SetProtectionRegion1(register unsigned long param)
{
    mcr p15, 0, r0, c6, c1, 0
    bx lr
}

asm void OS_SetProtectionRegion2(register unsigned long param)
{
    mcr p15, 0, r0, c6, c2, 0
    bx lr
}
