/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int data_020c5acc[];
extern unsigned short data_020c5ad0[];
void OSi_InitVramExclusive(void);

void OSi_InitVramExclusive(void) {
    int i = 0;
    int z = i;
    data_020c5acc[0] = z;
    do {
        data_020c5ad0[i] = (unsigned short)z;
        i = i + 1;
    } while (i < 9);
}
