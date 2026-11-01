/* NitroSDK SND: reads the instrument of a program and key from a bank; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 values[5];
} Param;

typedef struct {
    u8 type;
    u8 pad;
    Param param;
} Inst;

typedef struct {
    u8 min;
    u8 max;
    Inst inst[1];
} Drums;

typedef struct {
    u8 keys[8];
    Inst inst[1];
} Split;

typedef struct {
    u8 pad[0x38];
    u32 count;
    u32 offsets[1];
} Bank;

extern void func_0207d5cc(void);
extern void func_0207d5e0(void);

int func_0207e2f4(const Bank *bank, int program, int key, Inst *inst) {
    u32 offset;
    if (program < 0) {
        return 0;
    }
    func_0207d5e0();
    if ((u32)program >= bank->count) {
        func_0207d5cc();
        return 0;
    }
    offset = bank->offsets[program];
    inst->type = offset;
    switch (inst->type) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        inst->param = *(const Param *)((const u8 *)bank + (offset >> 8));
        break;
    case 16: {
        const Drums *drums = (const Drums *)((const u8 *)bank + (offset >> 8));
        int max = drums->max;
        int min = drums->min;
        if (key < min || key > max) {
            func_0207d5cc();
            return 0;
        }
        *inst = drums->inst[key - min];
        break;
    }
    case 17: {
        int i = 0;
        const Split *split = (const Split *)((const u8 *)bank + (offset >> 8));
        while (key > split->keys[i]) {
            i++;
            if (i >= 8) {
                func_0207d5cc();
                return 0;
            }
        }
        *inst = split->inst[i];
        break;
    }
    case 0:
    default:
        func_0207d5cc();
        return 0;
    }
    func_0207d5cc();
    return 1;
}
