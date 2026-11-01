/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* srand: stores the PRNG seed into data_020c7724. */

extern int data_020c7724[];

void func_0207f0e8(int seed) {
    data_020c7724[3] = seed;
}
