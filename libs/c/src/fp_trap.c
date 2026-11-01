/*
 * Soft-float trap dispatch. Hypotheses: the file name; the handler table layout, read
 * from the offsets. The operation word holds the exception in bits 26-30 and the
 * rounding mode in bits 22-23.
 */

typedef union Value {
    float f;
    double d;
    int i;
    struct {
        unsigned int lo;
        unsigned int hi;
    } words;
} Value;

typedef Value (*TrapHandler)(Value a, Value b, unsigned int op);

typedef struct TrapHandlers {
    unsigned int unk00;
    TrapHandler unk04;
    TrapHandler unk08;
    TrapHandler unk0c;
    TrapHandler unk10;
    TrapHandler unk14;
} TrapHandlers;

extern TrapHandlers* func_02085750(void);
extern unsigned int func_02089758(unsigned int mask, unsigned int bits);
extern int raise(int sig);

Value func_020802ac(Value a, Value b, unsigned int op) {
    TrapHandler handler;
    TrapHandlers* handlers = func_02085750();

    if ((op & 0xC00000) == 0) {
        op |= func_02089758(0, 0) & 0xC00000;
    }
    switch (op & 0x7C000000) {
        case 0x40000000:
            handler = handlers->unk14;
            break;
        case 0x04000000:
            handler = handlers->unk04;
            break;
        case 0x10000000:
            handler = handlers->unk0c;
            break;
        case 0x20000000:
            handler = handlers->unk10;
            break;
        case 0x08000000:
            handler = handlers->unk08;
            break;
        default:
            handler = 0;
            break;
    }
    if (handler == 0) {
        raise(2);
    }
    return handler(a, b, op);
}

float func_020803b4(float a, unsigned int op) {
    Value x;
    x.f = a;
    return func_020802ac(x, x, op).f;
}

double func_020803f0(double a, unsigned int op) {
    Value x;
    x.d = a;
    return func_020802ac(x, x, op).d;
}

float func_02080430(float a, float b, unsigned int op) {
    Value x, y;
    x.f = a;
    y.f = b;
    return func_020802ac(x, y, op).f;
}

double func_02080470(double a, double b, unsigned int op) {
    Value x, y;
    x.d = a;
    y.d = b;
    return func_020802ac(x, y, op).d;
}

int func_020804c0(double a, double b, unsigned int op) {
    Value x, y;
    x.d = a;
    y.d = b;
    return func_020802ac(x, y, op).i;
}
