/*
 * Unit 0x02000BA0-0x02000C68: `main`: it starts the systems, builds the file factory and
 * runs the main loop. Bounds: from the build info to the description of the next action.
 * The object that holds `main` is probably unit_02001FDC.cpp: its data and the inline
 * functions of the factory are there, and they follow an empty function exactly where
 * `main` would sit if the linker had moved it to the front (hypothesis, the mechanism is
 * unknown). Real file name unknown.
 */
#include "game/unk_sim.h"

class Unk020bd2d4 {
public:
    virtual ~Unk020bd2d4();
    virtual int func_02095c74(int id) = 0;
    virtual Unk0209487c *func_02095cd0(void *data, int kind) = 0;
};

class Unk02053204 : public Unk020bd2d4 {
public:
    ~Unk02053204();
    int func_02095c74(int id);
    Unk0209487c *func_02095cd0(void *data, int kind);
};

void func_02096b70();
void func_02096b8c();
void func_02096cb0();
void func_020947a4(Unk020bd2d4 *factory);

class Unk0208a0a8 {
public:
    void func_0208a0c4(unsigned long a);
};

extern "C" {
void *func_020999e8(int a);
void func_020997c0(void *a, int b, int c);
void func_0209f0ac(void *a);
void func_0209f2e8(void *a);
void func_020a2864(const char *path, int size);
void *func_020a2994();
void func_020a29a4(void *a);
extern Unk0208a0a8 *data_020c7d24;
extern u8 data_020d60c8[];
extern const char *data_020b7074;
}

extern "C" void main() {
    func_02096b70();
    func_02096b8c();
    func_02096cb0();
    func_0208c578()->func_0208ca84(0x60);
    func_0208c578()->func_0208ca9c(0x40);
    data_020c7d24->func_0208a0c4(0x40);
    data_020c7d38.func_0208b99c(0x40, 0x800);
    func_020a2864(data_020b7074, 0x87000);
    *(volatile u16 *)0x4000304 &= ~0x8000;
    func_020997c0(func_020999e8(0), 0x100, 0x4000);
    Unk02053204 factory;
    func_020947a4(&factory);
    func_0209f0ac(data_020d60c8);
    while (true) {
        func_0209f2e8(data_020d60c8);
        func_020a29a4(func_020a2994());
    }
}
