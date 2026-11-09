/*
 * 20.12 fixed-point vectors of unit_02098E70.cpp, used by the units around it.
 * Layouts and helpers come from the code; all names are placeholders.
 */
#ifndef GAME_UNK_VECTOR_H
#define GAME_UNK_VECTOR_H

typedef long long s64;

extern "C" int func_02077c60(int a, int b);
extern "C" int func_02097a6c(s64 x);

static inline int func_fxmul(int a, int b) {
    return (int)(((s64)a * b) >> 12);
}

static inline int func_fxdiv(int a, int b) {
    if (b != 0) {
        return func_02077c60(a, b);
    }
    return a;
}

struct Unk02098e70Base {
    int x;
    int y;
};

class Unk02098e70 : public Unk02098e70Base {
public:
    Unk02098e70() {}
    Unk02098e70(int v);
    Unk02098e70(int x, int y);
    int func_02098e84() const;
    s64 func_02098e94() const;
    Unk02098e70 &func_02098ec0(int f);
    Unk02098e70 &func_02098eec();
    Unk02098e70 func_02098f38() const;
    Unk02098e70 &func_02098f74(int min, int max);
    Unk02098e70 func_02098fa8(const Unk02098e70 &o) const;
    Unk02098e70 func_02098fcc(const Unk02098e70 &o) const;
};

struct Unk02098ff0Base {
    int x;
    int y;
    int z;
};

class Unk02098ff0 : public Unk02098ff0Base {
public:
    Unk02098ff0() {}
    Unk02098ff0(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    int func_02098ff0() const;
    s64 func_02099000() const;
    void func_02099048(int f);
    Unk02098ff0 &func_02099088();
    Unk02098ff0 func_020990ec() const;
    Unk02098ff0 func_0209911c(const Unk02098ff0 &o) const;
    Unk02098ff0 func_02099150(const Unk02098ff0 &o) const;
    int func_02099184(const Unk02098ff0 &o) const;
    Unk02098ff0 func_020991b8(const Unk02098ff0 &o, int t) const;

    /*
     * The sum through an inline member: called on a returned vector, the receiver's
     * address is then taken before the result's (`add r1`, then `add r0`), as in
     * func_0200527c and func_02066f14; the direct call takes the result's first.
     * The inline and its name are a hypothesis.
     */
    Unk02098ff0 func_add(const Unk02098ff0 &o) const {
        return func_0209911c(o);
    }

    /* Clamps each component to [-0x1000, 0xFFF] (inline in the ITCM drawing code). */
    Unk02098ff0 &func_clamp() {
        if (x < -0x1000) {
            x = -0x1000;
        }
        if (x > 0xfff) {
            x = 0xfff;
        }
        if (y < -0x1000) {
            y = -0x1000;
        }
        if (y > 0xfff) {
            y = 0xfff;
        }
        if (z < -0x1000) {
            z = -0x1000;
        }
        if (z > 0xfff) {
            z = 0xfff;
        }
        return *this;
    }
};

#endif
