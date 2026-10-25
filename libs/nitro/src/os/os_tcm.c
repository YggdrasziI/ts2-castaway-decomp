/* NitroSDK os_tcm.c: only OS_GetDTCMAddress is linked.
 *
 * Bounds 0x0207B8E4-0x0207B8F8: after the arena setup (func_0207b7cc), before
 * os_protectionUnit.c. Byte-identical to khdays-decomp's (CC0) version, see
 * notes/PROVENANCE.md; file name from khdays' citation of the NitroSDK source.
 */

#define OSi_TCM_REGION_BASE_MASK 0xfffff000

asm unsigned long OS_GetDTCMAddress(void)
{
    mrc p15, 0, r0, c9, c1, 0
    ldr r1, =OSi_TCM_REGION_BASE_MASK
    and r0, r0, r1
    bx lr
}
