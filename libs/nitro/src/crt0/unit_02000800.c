/* NitroSDK crt0, written from the ROM as asm functions (this SDK version differs from
 * Advance Wars' crt0, CC0, which gave the structure: it aligns the stacks on 8 bytes
 * and flushes the caches after clearing .bss, decompressing and autoloading), and the
 * module parameters BuildInfo with the backup library tag that follows them. File
 * bounds are a hypothesis. The asm functions are emitted in source order. */
#pragma force_active on

extern unsigned char data_027e0000[];
extern unsigned char data_020bfc9c[];
extern unsigned char data_020bdfcc[];
extern void func_01ff831c(void);
extern void main(void);
extern void func_02089780(void);
extern void func_02002124(void);
extern void __call_static_initializers(void);

void func_0200093c(unsigned int value, void *dest, unsigned int size);
void MIi_UncompressBackward(void *bottom);
void func_020009fc(void);
void AutoloadCallback(void);
void func_02000a78(void);
extern struct BuildInfo BuildInfo;

/* ARM9 entry point. */
asm void Entry(void)
{
    mov r12, #0x4000000
    str r12, [r12, #0x208]
wait_vcount:
    ldrh r0, [r12, #6]
    cmp r0, #0
    bne wait_vcount
    bl func_02000a78
    mov r0, #0x13
    msr CPSR_c, r0
    ldr r0, =data_027e0000
    add r0, r0, #0x3fc0
    mov sp, r0
    mov r0, #0x12
    msr CPSR_c, r0
    ldr r0, =data_027e0000
    add r0, r0, #0x3fc0
    sub r0, r0, #0x40
    sub sp, r0, #4
    tst sp, #4
    subeq sp, sp, #4
    ldr r1, =0x400
    sub r1, r0, r1
    mov r0, #0x1f
    msr CPSR_fsxc, r0
    sub sp, r1, #4
    mov r0, #0
    ldr r1, =data_027e0000
    mov r2, #0x4000
    bl func_0200093c
    mov r0, #0
    ldr r1, =0x05000000
    mov r2, #0x400
    bl func_0200093c
    mov r0, #0x200
    ldr r1, =0x07000000
    mov r2, #0x400
    bl func_0200093c
    ldr r1, =BuildInfo
    ldr r0, [r1, #0x14]
    bl MIi_UncompressBackward
    bl func_020009fc
    ldr r0, =BuildInfo
    ldr r1, [r0, #0xc]
    ldr r2, [r0, #0x10]
    mov r3, r1
    mov r0, #0
clear_bss:
    cmp r1, r2
    strcc r0, [r1], #4
    bcc clear_bss
    bic r1, r3, #31
flush_bss:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r1, c7, c5, 1
    mcr p15, 0, r1, c7, c14, 1
    add r1, r1, #32
    cmp r1, r2
    blt flush_bss
    ldr r1, =0x027fff9c
    str r0, [r1]
    ldr r1, =data_027e0000
    add r1, r1, #0x3fc0
    add r1, r1, #0x3c
    ldr r0, =func_01ff831c
    str r0, [r1]
    bl func_02089780
    bl func_02002124
    bl __call_static_initializers
    ldr r1, =main
    ldr lr, =0xffff0000
    tst sp, #4
    subne sp, sp, #4
    bx r1
}

asm void func_0200093c(register unsigned int value, register void *dest, register unsigned int size)
{
    add r12, r1, r2
loop:
    cmp r1, r12
    stmltia r1!, {r0}
    blt loop
    bx lr
}

asm void MIi_UncompressBackward(register void *bottom)
{
    cmp r0, #0
    beq exit
    stmfd sp!, {r4, r5, r6, r7}
    ldmdb r0, {r1, r2}
    add r2, r0, r2
    sub r3, r0, r1, lsr #24
    bic r1, r1, #0xff000000
    sub r1, r0, r1
    mov r4, r2
next_flags:
    cmp r3, r1
    ble flush_start
    ldrb r5, [r3, #-1]!
    mov r6, #8
next_item:
    subs r6, r6, #1
    blt next_flags
    tst r5, #0x80
    bne copy_ref
    ldrb r0, [r3, #-1]!
    strb r0, [r2, #-1]!
    b item_done
copy_ref:
    ldrb r12, [r3, #-1]!
    ldrb r7, [r3, #-1]!
    orr r7, r7, r12, lsl #8
    bic r7, r7, #0xf000
    add r7, r7, #2
    add r12, r12, #0x20
copy_byte:
    ldrb r0, [r2, r7]
    strb r0, [r2, #-1]!
    subs r12, r12, #0x10
    bge copy_byte
item_done:
    cmp r3, r1
    mov r5, r5, lsl #1
    bgt next_item
flush_start:
    mov r0, #0
    bic r3, r1, #31
flush_line:
    mcr p15, 0, r0, c7, c10, 4
    mcr p15, 0, r3, c7, c5, 1
    mcr p15, 0, r3, c7, c14, 1
    add r3, r3, #32
    cmp r3, r4
    blt flush_line
    ldmfd sp!, {r4, r5, r6, r7}
exit:
    bx lr
}

/* Copies the autoload blocks (destination, size, size to clear after it) and flushes
 * each block from the caches. */
asm void func_020009fc(void)
{
    ldr r0, =BuildInfo
    ldr r1, [r0]
    ldr r2, [r0, #4]
    ldr r3, [r0, #8]
next_block:
    cmp r1, r2
    beq done
    ldr r5, [r1], #4
    ldr r7, [r1], #4
    add r6, r5, r7
    mov r4, r5
copy:
    cmp r4, r6
    ldrmi r7, [r3], #4
    strmi r7, [r4], #4
    bmi copy
    ldr r7, [r1], #4
    add r6, r4, r7
    mov r7, #0
clear:
    cmp r4, r6
    strcc r7, [r4], #4
    bcc clear
    bic r4, r5, #31
flush:
    mcr p15, 0, r7, c7, c10, 4
    mcr p15, 0, r4, c7, c5, 1
    mcr p15, 0, r4, c7, c14, 1
    add r4, r4, #32
    cmp r4, r6
    blt flush
    b next_block
done:
    b AutoloadCallback
}

asm void AutoloadCallback(void)
{
    bx lr
}

/* Programs the CP15 protection regions, caches and TCMs. */
asm void func_02000a78(void)
{
    mrc p15, 0, r0, c1, c0, 0
    ldr r1, =0x000f9005
    bic r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0
    mcr p15, 0, r0, c7, c6, 0
    mcr p15, 0, r0, c7, c10, 4
    ldr r0, =0x04000033
    mcr p15, 0, r0, c6, c0, 0
    ldr r0, =0x0200002d
    mcr p15, 0, r0, c6, c1, 0
    ldr r0, =data_027e0000+0x21
    mcr p15, 0, r0, c6, c2, 0
    ldr r0, =0x08000035
    mcr p15, 0, r0, c6, c3, 0
    ldr r0, =data_027e0000
    orr r0, r0, #0x1a
    orr r0, r0, #1
    mcr p15, 0, r0, c6, c4, 0
    ldr r0, =0x0100002f
    mcr p15, 0, r0, c6, c5, 0
    ldr r0, =0xffff001d
    mcr p15, 0, r0, c6, c6, 0
    ldr r0, =0x027ff017
    mcr p15, 0, r0, c6, c7, 0
    mov r0, #0x20
    mcr p15, 0, r0, c9, c1, 1
    ldr r0, =data_027e0000
    orr r0, r0, #0xa
    mcr p15, 0, r0, c9, c1, 0
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 1
    mov r0, #0x42
    mcr p15, 0, r0, c2, c0, 0
    mov r0, #2
    mcr p15, 0, r0, c3, c0, 0
    ldr r0, =0x05100011
    mcr p15, 0, r0, c5, c0, 3
    ldr r0, =0x15111011
    mcr p15, 0, r0, c5, c0, 2
    mrc p15, 0, r0, c1, c0, 0
    ldr r1, =0x0005707d
    orr r0, r0, r1
    mcr p15, 0, r0, c1, c0, 0
    bx lr
}

asm void func_02000b60(void)
{
    bx lr
}

/* Module parameters: autoload list start and end, autoload data start, .bss start and
 * end (the end has no relocation: it lies past the module), compressed static end
 * (0: not compressed), SDK version and the two magic words, then the backup library
 * tag. Kept in .text, between the functions, as the original does: the pragma moves
 * initialized data only, so the object is not const (Advance Wars' text_data.h). */
#pragma define_section TEXT_DATA ".text" abs32 RWX
#pragma section TEXT_DATA begin

struct BuildInfo {
    void *autoloadListStart;
    void *autoloadListEnd;
    void *autoloadStart;
    void *bssStart;
    unsigned int bssEnd;
    unsigned int compressedStaticEnd;
    unsigned int version;
    unsigned int magic[2];
    char backupTag[24];
} BuildInfo = {
    data_020bfc9c + 0x1464,
    data_020bfc9c + 0x147c,
    data_020bdfcc + 0x14,
    data_020bdfcc + 0x14,
    0x020d7160,
    0,
    0x03027532,
    {0xdec00621, 0x2106c0de},
    "[SDK+NINTENDO:BACKUP]",
};

#pragma section TEXT_DATA end
