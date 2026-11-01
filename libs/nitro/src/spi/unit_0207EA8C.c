/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef struct { u16 x, y, touch, validity; } TPData;
extern struct { int cb; TPData buf; char a[0x28]; volatile u16 err; } data_020c76e8;
extern void func_0207e6cc(TPData *dst, TPData *src);
int func_0207ea8c(TPData *d) {
    if (data_020c76e8.err & 1) {
        return 1;
    }
    *d = data_020c76e8.buf;
    func_0207e6cc(d, d);
    return 0;
}
