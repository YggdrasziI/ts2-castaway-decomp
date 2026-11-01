/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* func_0207bb30: sets bit `n` in the reserved-timer mask and returns the new mask. */

extern unsigned short data_020c5a9c;

int func_0207bb30(int n) {
    int v = data_020c5a9c | (1 << n);
    data_020c5a9c = (unsigned short)v;
    return v;
}
