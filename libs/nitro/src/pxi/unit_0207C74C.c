/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern volatile int data_020c5b6c;
asm void func_0207c74c(void);

asm void func_0207c74c(void)
{
    ldr r12, =data_020c5b6c
loop:
    ldr r0, [r12, #0]
    cmp r0, #1
    beq loop
    bx lr
}
