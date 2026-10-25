/* NitroSDK os_cache.c: data and instruction cache maintenance (CP15 c7).
 *
 * Bounds 0x0207B3C4-0x0207B47C (hypothesis: the file's first functions, such as
 * DC_Enable or DC_StoreAll, may precede DC_FlushAll or be dead-stripped). Each
 * function is byte-identical to khdays-decomp's (CC0) version, see
 * notes/PROVENANCE.md. File name from khdays' citation of the NitroSDK source.
 */

#define HW_CACHE_LINE_SIZE 32
#define HW_DCACHE_SIZE 0x1000
#define HW_C7_CACHE_SET_NO_SHIFT 30

asm void DC_FlushAll(void)
{
    mov r12, #0
    mov r1, #0
@1:
    mov r0, #0
@2:
    orr r2, r1, r0
    mcr p15, 0, r12, c7, c10, 4
    mcr p15, 0, r2, c7, c14, 2
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, #HW_DCACHE_SIZE / 4
    blt @2
    add r1, r1, #1 << HW_C7_CACHE_SET_NO_SHIFT
    cmp r1, #0
    bne @1
    bx lr
}

asm void DC_InvalidateRange(register void *startAddr, register unsigned long nBytes)
{
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r0, c7, c6, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}

asm void DC_StoreRange(register const void *startAddr, register unsigned long nBytes)
{
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r0, c7, c10, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}

asm void DC_FlushRange(register const void *startAddr, register unsigned long nBytes)
{
    mov r12, #0
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r12, c7, c10, 4
    mcr p15, 0, r0, c7, c14, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}

asm void DC_WaitWriteBufferEmpty(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c10, 4
    bx lr
}

asm void IC_InvalidateRange(register void *startAddr, register unsigned long nBytes)
{
    add r1, r1, r0
    bic r0, r0, #HW_CACHE_LINE_SIZE - 1
@1:
    mcr p15, 0, r0, c7, c5, 1
    add r0, r0, #HW_CACHE_LINE_SIZE
    cmp r0, r1
    blt @1
    bx lr
}
