/*
 * Unit 0x02011524-0x020116E0: the "Icon View utility" screen `Unk02011524`, a
 * microgame showing an animated icon.
 *
 * Bounds: hypothesis. The start is the factory called from 0x020A5A50, the end
 * follows the deleting destructor of its vtable at 0x020B7BC8. Real file name
 * unknown.
 */

#include "game/unk_microgame.h"

class Unk0208db14 {
public:
    void func_0208e224(void *data, u32 dst, u32 n);
};

extern "C" {
void func_020a69ac(Unk020a7c90 *s, int f);
int func_020a69cc(Unk020a7c90 *s);
int func_020a69d4(Unk020a7c90 *s);
void func_020a8048(Unk020a7c90 *s, u32 hash);
u32 func_020a805c(Unk020a7c90 *s);
Unk0208db14 *func_020aa410(Unk020a9d58 *l);
Unk020a5ccc *func_02011524(Unk02093648 *file, int a, int b);
}
int func_0209774c(int a);
int func_020972c0(int key);

class Unk02011524 : public Unk02013f8c {
public:
    Unk02011524(Unk02093648 *file, int a, int b) : Unk02013f8c("Icon View utility", 0xe0024c04, file, a, b) {
        delay = 0;
        for (int i = 0; i < 0x100; i++) {
            palette[i] = 0;
        }
    }

    virtual ~Unk02011524() {}

    virtual bool func_18() {
        Unk020a7c90 *s = func_020aa040(&layout, 2, 0);
        func_020a7c90(s, -0x4000);
        func_020a7cac(s, -0x4000);
        if (func_0209774c(0) != 0 && delay == 0) {
            int f = func_020a69cc(s);
            func_020a69ac(s, f == func_020a69d4(s) - 1 ? 0 : f + 1);
            delay = 10;
            func_020aa410(&layout)->func_0208e224(palette, 0, 0x100);
        }
        if (delay > 0) {
            delay--;
        } else {
            Unk020a7c90 *a = func_020aa040(&layout, 6, 0);
            Unk020a7c90 *b = func_020aa040(&layout, 6, 0);
            func_020a8048(b, func_020a805c(a));
        }
        func_020aa158(&layout);
        return func_020972c0(3) != 1;
    }

    u16 palette[0x100];
    int delay;
};

Unk020a5ccc *func_02011524(Unk02093648 *file, int a, int b) {
    return new Unk02011524(file, a, b);
}
