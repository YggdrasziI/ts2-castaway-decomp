/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
typedef struct B { int a, b, c; struct B *next; } B;
typedef struct { int cur, end; B *top; } S;
typedef struct { char a[0x18]; int lo, hi; char b[4]; S s; } H;
void func_0209ed88(H *h) {
    S *s = &h->s;
    s->cur = h->lo;
    s->top = 0;
}
