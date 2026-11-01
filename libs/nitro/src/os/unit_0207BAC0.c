/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern void func_0207b93c(void);
extern char data_020c5a18[];
extern unsigned int data_020c5a10;

void func_0207bac0(void)
{
    unsigned int v = *(volatile unsigned int *)0x027FFD9Cu;
    if (v >= 0x02600000u && v < 0x02800000u) {
        *(unsigned int *)data_020c5a18 = v;
    } else {
        *(unsigned int *)data_020c5a18 = 0;
    }
    if (*(unsigned int *)data_020c5a18 == 0) {
        *(volatile void **)0x027FFD9Cu = (void *)func_0207b93c;
        {
            volatile char *base = (volatile char *)0x027E3000u;
            *(volatile void **)(base + 0xFDC) = (void *)func_0207b93c;
        }
    }
    data_020c5a10 = 0;
}
