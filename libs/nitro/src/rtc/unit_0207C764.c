/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* srand: stores the PRNG seed into data_020c5b6c. */

extern int data_020c5b6c[];

void func_0207c764(int seed) {
    data_020c5b6c[8] = seed;
}
