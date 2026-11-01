/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef struct { char a[0x34]; u16 kind; u16 pad; u16 x; u16 y; u8 no; char b[3]; u8 c40, c41; } P;
typedef struct { P *p; } H;
extern const short data_020b335c[];
extern void func_0207d4d0(int no, int m, int v);
void func_0209b0c4(H *h, int m, int v) {
    if (h->p == 0) {
        return;
    }
    func_0207d4d0(h->p->no, m, data_020b335c[v]);
}
