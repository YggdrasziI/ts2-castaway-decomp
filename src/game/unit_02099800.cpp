/*
 * Unit 0x02099800-0x02099840: one static object and its class.
 *
 * Bounds: hypothesis. __sinit_020ae384 (.ctor entry 0x020B6EA8) builds the object
 * data_020c80b0 with func_02099800 and registers func_02099824 as its destructor
 * (func_02085b54, chain node data_020c80a4). The three empty functions after the
 * destructor are only called on that object, through func_02099834, which returns
 * its address. Whether 0x02099840-0x0209986C (tail calls to func_02099b44 and
 * func_02099b60) belongs to this file is unknown. Real file name unknown.
 */

class Unk020c80b0 {
public:
    Unk020c80b0();
    ~Unk020c80b0();
    void func_02099828();
    void func_0209982c(const char *name);
    void func_02099830();

    int unk0;
    int unk4;
    int unk8;
    int unkC;
    char unk10[0x200];
    int unk210;
};

Unk020c80b0 data_020c80b0;

Unk020c80b0::Unk020c80b0() {
    unk0 = 0;
    unk4 = 0;
    unk8 = 0;
    unkC = 0x2000;
    unk210 = -1;
}

Unk020c80b0::~Unk020c80b0() {}

void Unk020c80b0::func_02099828() {}

void Unk020c80b0::func_0209982c(const char *name) {}

void Unk020c80b0::func_02099830() {}

Unk020c80b0 *func_02099834() {
    return &data_020c80b0;
}
