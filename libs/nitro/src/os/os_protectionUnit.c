/* NitroSDK os_protectionUnit.c: enable and disable the protection unit (CP15 c1).
 *
 * Bounds 0x0207B8F8-0x0207B918: between os_tcm.c and os_protectionRegion.c.
 * Byte-identical to khdays-decomp's (CC0) version, see notes/PROVENANCE.md; file
 * name from khdays' citation of the NitroSDK source.
 */

#define HW_C1_PROTECT_UNIT_ENABLE 0x1

asm void OS_EnableProtectionUnit(void)
{
    mrc p15, 0, r0, c1, c0, 0
    orr r0, r0, #HW_C1_PROTECT_UNIT_ENABLE
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm void OS_DisableProtectionUnit(void)
{
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #HW_C1_PROTECT_UNIT_ENABLE
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}
