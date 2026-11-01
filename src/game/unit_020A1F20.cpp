/*
 * Unit 0x020A1F20-0x020A20BC: the random numbers of the game (static object data_020d62a4,
 * 0x9C4 bytes, with its `__sinit`): a Mersenne Twister (the constants of MT19937: 624 words,
 * shift 397, matrix 0x9908B0DF, seed multiplier 0x6C078965, default seed 5489). Bounds:
 * hypothesis (the static initializer 0x020AE4D0 sets its index; `.data` is the matrix table).
 * Layouts come from the code; all names are placeholders. Real file name unknown.
 */
typedef unsigned long u32;

class Unk020a20f0 {
public:
    Unk020a20f0() : index(625) {}

    u32 state[624];
    int index;
};

extern "C" void func_020a1f3c(Unk020a20f0 *o, u32 seed);

Unk020a20f0 data_020d62a4;

extern "C" void func_020a1f20() {
    func_020a1f3c(&data_020d62a4, 0xa47b92f1);
}

extern "C" void func_020a1f3c(Unk020a20f0 *o, u32 seed) {
    o->state[0] = seed;
    for (o->index = 1; o->index < 624; o->index++) {
        o->state[o->index] =
            0x6c078965 * (o->state[o->index - 1] ^ (o->state[o->index - 1] >> 30)) + o->index;
    }
}

extern "C" u32 func_020a1f84(Unk020a20f0 *o) {
    static u32 data_020bd898[2] = {0, 0x9908b0df};
    if (o->index >= 624) {
        if (o->index == 625) {
            func_020a1f3c(o, 5489);
        }
        int i;
        for (i = 0; i < 227; i++) {
            u32 y = (o->state[i] & 0x80000000) | (o->state[i + 1] & 0x7fffffff);
            u32 mag = data_020bd898[y & 1];
            o->state[i] = o->state[i + 397] ^ (y >> 1) ^ mag;
        }
        for (; i < 623; i++) {
            u32 y = (o->state[i] & 0x80000000) | (o->state[i + 1] & 0x7fffffff);
            u32 mag = data_020bd898[y & 1];
            o->state[i] = o->state[i - 227] ^ (y >> 1) ^ mag;
        }
        u32 y = (o->state[623] & 0x80000000) | (o->state[0] & 0x7fffffff);
        o->state[623] = o->state[396] ^ (y >> 1) ^ data_020bd898[y & 1];
        o->index = 0;
    }
    u32 y = o->state[o->index++];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= y >> 18;
    return y;
}
