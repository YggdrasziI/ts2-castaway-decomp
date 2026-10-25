/*
 * Unit 0x02099C78-0x0209A11C: an abstract class (Unk02099c78) that runs bytecode
 * from a resource: each 12-byte instruction has an opcode in bits 12-15 of its
 * second word and runs only when the low 12 bits share a bit with the result of the
 * last test. Variables are read and written through virtual functions.
 *
 * Bounds: hypothesis. Before 0x02099C78 lies unit_02099C0C.cpp (another layout);
 * 0x0209A11C starts unit_0209A11C.cpp (a bit set). The vtable data_020bd584 holds
 * only the destructors, the other entries are zero (pure virtual), so the
 * implementations are in derived classes elsewhere. Real file name unknown.
 */

#include "game/unk_script.h"

class Unk02099c78;

struct Unk02099c78Call {
    Unk02099c78 *self;
    short result;
    Unk02099c78Value *value;
    int b;
};


class Unk02099c78 {
public:
    Unk02099c78(Unk020956f8 *res);
    virtual void vfunc_00() = 0;
    virtual short vfunc_04(int index) = 0;
    virtual void vfunc_08(int index, short value) = 0;
    virtual ~Unk02099c78();
    virtual int vfunc_14(int arg, Unk02099c78Call *call) = 0;

    void func_02099ce0(int key);
    int func_02099d04(Unk02099c78Block *block, int budget);
    int func_02099fd0(int index, int a, int b);
    bool func_0209a034(int index);
    bool func_0209a078(int index);
    void func_0209a0bc(int index);
    int func_0209a0f4(int key);

    Unk020956f8 *res;
    short unk8;
};

Unk02099c78::Unk02099c78(Unk020956f8 *res) {
    Unk020956f8Header *p;

    this->res = res;
    unk8 = 0;
    if (this->res->func_02094f88() == 0) {
        return;
    }
    p = this->res->func_0209576c();
    if (p == 0) {
        return;
    }
    if (this->res->func_0209585c() == 0) {
        return;
    }
    unk8 = p->varCount;
}

void Unk02099c78::func_02099ce0(int key) {
    func_02099d04(res->func_020957ec(key), 0x100);
}

int Unk02099c78::func_02099d04(Unk02099c78Block *block, int budget) {
    Unk02099c78Op *ops;
    Unk02099c78Value *values;
    Unk02099c78Op *op;
    int count;
    int i;
    int result;
    int type;

    if (block == 0) {
        return 0;
    }
    ops = res->func_02095794() + block->start;
    values = res->func_02095ab0();
    res->func_02095934();
    if (ops == 0 || values == 0) {
        return 0;
    }
    count = block->count;
    i = 0;
    result = 1;
    for (; i < count; i++, budget--) {
        if (budget == 0) {
            break;
        }
        op = &ops[i];
        type = (int)(op->code & 0xf000) >> 12;
        if ((result & (op->code & 0xfff)) == 0) {
            continue;
        }
        switch (type) {
        case 0: {
            Unk02099c78Call call;
            short a = op->a;
            short b = op->b;
            call.value = a == -1 ? 0 : &values[a];
            call.b = b;
            call.self = this;
            call.result = result;
            result = vfunc_14(op->arg, &call);
            break;
        }
        case 1:
            vfunc_08(op->a, op->b);
            break;
        case 2:
            vfunc_08(op->a, vfunc_04(op->b));
            break;
        case 3:
            func_0209a0bc(op->a);
            break;
        case 4:
            vfunc_08(op->a, op->b + vfunc_04(op->a));
            break;
        case 5:
            result = func_02099fd0(op->a, vfunc_04(op->a), 0);
            break;
        case 6:
            result = func_02099fd0(op->a, vfunc_04(op->a), op->b);
            break;
        case 7: {
            int a = vfunc_04(op->a);
            result = func_02099fd0(op->a, a, vfunc_04(op->b));
            break;
        }
        case 8:
            i += op->a - 1;
            break;
        case 9:
            func_02099d04(res->func_020957c0() + op->a, budget);
            break;
        case 10:
            return 1;
        }
    }
    return 1;
}

int Unk02099c78::func_02099fd0(int index, int a, int b) {
    int flags = 1;

    if (a == b) {
        flags |= 4;
    } else {
        flags |= 2;
    }
    if (a > b) {
        flags |= 0x10;
    }
    if (a < b) {
        flags |= 8;
    }
    if (func_0209a078(index)) {
        flags |= 0x40;
    } else {
        flags |= 0x100;
    }
    if (func_0209a034(index)) {
        flags |= 0x20;
    } else {
        flags |= 0x80;
    }
    return flags;
}

bool Unk02099c78::func_0209a034(int index) {
    Unk02099c78Var *var = &res->func_0209585c()[index];
    return var->min == vfunc_04(index);
}

bool Unk02099c78::func_0209a078(int index) {
    Unk02099c78Var *var = &res->func_0209585c()[index];
    return var->max == vfunc_04(index);
}

void Unk02099c78::func_0209a0bc(int index) {
    Unk02099c78Var *var = &res->func_0209585c()[index];
    vfunc_08(index, var->init);
}

int Unk02099c78::func_0209a0f4(int key) {
    return res->func_020958bc(key);
}

Unk02099c78::~Unk02099c78() {}
