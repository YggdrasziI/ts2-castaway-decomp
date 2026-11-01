/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
extern struct { int a, b; } data_020d47e8;

void func_0209a890(int bit) {
    data_020d47e8.a &= ~(1 << bit);
}
