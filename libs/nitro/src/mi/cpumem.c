/* NitroSDK CPU memory copy and fill primitives (MI).
 *
 * Bounds 0x02079ABC-0x02079D70 (hypothesis: from twewy's cpumem.c layout; the
 * first and last functions here match twewy's file, which starts with a 16-bit
 * fill not linked in this game). Byte-identical sources: khdays-decomp (CC0),
 * except MI_CpuFillU32 and the body of MI_SwapWord (twewy, CC0); see
 * notes/PROVENANCE.md. Real file name unknown (twewy's name).
 */

typedef unsigned int u32;

asm void MIi_CpuCopy16(register const void *source,
                       register void *destination, register u32 size)
{
    mov     ip, #0
copyNextHalfword:
    cmp     ip, r2
    ldrlth  r3, [r0, ip]
    strlth  r3, [r1, ip]
    addlt   ip, ip, #2
    blt     copyNextHalfword
    bx      lr
}

asm void MI_CpuFillU32(register u32 value, register u32 *dest, register u32 count)
{
    add     ip, r1, r2
@1:
    cmp     r1, ip
    stmltia r1!, {r0}
    blt     @1
    bx      lr
}

asm void MIi_CpuCopy32(register const void *source,
                       register void *destination, register u32 size)
{
    add     ip, r1, r2
copyNextWord:
    cmp     r1, ip
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt     copyNextWord
    bx      lr
}

asm void MIi_CpuClearFast(register u32 value,
                          register void *destination, register u32 size)
{
    stmdb   sp!, {r4, r5, r6, r7, r8, r9}
    add     r9, r1, r2
    mov     ip, r2, lsr #5
    add     ip, r1, ip, lsl #5
    mov     r2, r0
    mov     r3, r2
    mov     r4, r2
    mov     r5, r2
    mov     r6, r2
    mov     r7, r2
    mov     r8, r2
clearNextBlock:
    cmp     r1, ip
    stmltia r1!, {r0, r2, r3, r4, r5, r6, r7, r8}
    blt     clearNextBlock
clearNextWord:
    cmp     r1, r9
    stmltia r1!, {r0}
    blt     clearNextWord
    ldmia   sp!, {r4, r5, r6, r7, r8, r9}
    bx      lr
}

asm void MIi_CpuCopyFast(register const void *source,
                         register void *destination, register u32 size)
{
    stmdb   sp!, {r4, r5, r6, r7, r8, r9, r10}
    add     r10, r1, r2
    mov     ip, r2, lsr #5
    add     ip, r1, ip, lsl #5
copyNextBlock:
    cmp     r1, ip
    ldmltia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
    stmltia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
    blt     copyNextBlock
copyNextWord:
    cmp     r1, r10
    ldmltia r0!, {r2}
    stmltia r1!, {r2}
    blt     copyNextWord
    ldmia   sp!, {r4, r5, r6, r7, r8, r9, r10}
    bx      lr
}
asm void MI_Copy36B(void *src, void *dst)
{
    ldmia r0!, {r2, r3, ip}
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    stmia r1!, {r2, r3, ip}
    ldmia r0!, {r2, r3, ip}
    stmia r1!, {r2, r3, ip}
    bx lr
}

asm void MI_CpuFill8(register void *destination, register u32 value,
                     register u32 size)
{
    cmp     r2, #0
    bxeq    lr
    tst     r0, #1
    beq     destinationHalfwordAligned
    ldrh    r12, [r0, #-1]
    and     r12, r12, #0xff
    orr     r3, r12, r1, lsl #8
    strh    r3, [r0, #-1]
    add     r0, r0, #1
    subs    r2, r2, #1
    bxeq    lr
destinationHalfwordAligned:
    cmp     r2, #2
    bcc     fillFinalByte
    orr     r1, r1, r1, lsl #8
    tst     r0, #2
    beq     destinationWordAligned
    strh    r1, [r0], #2
    subs    r2, r2, #2
    bxeq    lr
destinationWordAligned:
    orr     r1, r1, r1, lsl #16
    bics    r3, r2, #3
    beq     fillFinalHalfword
    sub     r2, r2, r3
    add     r12, r3, r0
fillNextWord:
    str     r1, [r0], #4
    cmp     r0, r12
    bcc     fillNextWord
fillFinalHalfword:
    tst     r2, #2
    strneh  r1, [r0], #2
fillFinalByte:
    tst     r2, #1
    bxeq    lr
    ldrh    r3, [r0]
    and     r3, r3, #0xff00
    and     r1, r1, #0xff
    orr     r1, r1, r3
    strh    r1, [r0]
    bx      lr
}

asm void MI_CpuCopy8(register const void *source, register void *destination,
                     register u32 size)
{
    cmp     r2, #0
    bxeq    lr
    tst     r1, #1
    beq     destinationHalfwordAligned
    ldrh    r12, [r1, #-1]
    and     r12, r12, #0xff
    tst     r0, #1
    ldrneh  r3, [r0, #-1]
    movne   r3, r3, lsr #8
    ldreqh  r3, [r0]
    orr     r3, r12, r3, lsl #8
    strh    r3, [r1, #-1]
    add     r0, r0, #1
    add     r1, r1, #1
    subs    r2, r2, #1
    bxeq    lr
destinationHalfwordAligned:
    eor     r12, r1, r0
    tst     r12, #1
    beq     equalHalfwordAlignment

    bic     r0, r0, #1
    ldrh    r12, [r0], #2
    mov     r3, r12, lsr #8
    subs    r2, r2, #2
    bcc     byteSkewTail
copyByteSkewHalfword:
    ldrh    r12, [r0], #2
    orr     r12, r3, r12, lsl #8
    strh    r12, [r1], #2
    mov     r3, r12, lsr #16
    subs    r2, r2, #2
    bcs     copyByteSkewHalfword
byteSkewTail:
    tst     r2, #1
    bxeq    lr
    ldrh    r12, [r1]
    and     r12, r12, #0xff00
    orr     r12, r12, r3
    strh    r12, [r1]
    bx      lr

equalHalfwordAlignment:
    tst     r12, #2
    beq     equalWordAlignment
    bics    r3, r2, #1
    beq     copyFinalByte
    sub     r2, r2, r3
    add     r12, r3, r1
copyHalfword:
    ldrh    r3, [r0], #2
    strh    r3, [r1], #2
    cmp     r1, r12
    bcc     copyHalfword
    b       copyFinalByte

equalWordAlignment:
    cmp     r2, #2
    bcc     copyFinalByte
    tst     r1, #2
    beq     destinationWordAligned
    ldrh    r3, [r0], #2
    strh    r3, [r1], #2
    subs    r2, r2, #2
    bxeq    lr
destinationWordAligned:
    bics    r3, r2, #3
    beq     copyFinalHalfword
    sub     r2, r2, r3
    add     r12, r3, r1
copyWord:
    ldr     r3, [r0], #4
    str     r3, [r1], #4
    cmp     r1, r12
    bcc     copyWord
copyFinalHalfword:
    tst     r2, #2
    ldrneh  r3, [r0], #2
    strneh  r3, [r1], #2
copyFinalByte:
    tst     r2, #1
    bxeq    lr
    ldrh    r2, [r1]
    ldrh    r0, [r0]
    and     r2, r2, #0xff00
    and     r0, r0, #0xff
    orr     r0, r2, r0
    strh    r0, [r1]
    bx      lr
}

asm u32 MI_SwapWord(register u32 value, register u32 *addr)
{
    swp     r0, r0, [r1]
    bx      lr
}
