/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern volatile int data_020c7724;

asm void func_0207f0d0(void)
{
    ldr r12, =data_020c7724
loop:
    ldr r0, [r12, #0]
    cmp r0, #1
    beq loop
    bx lr
}
