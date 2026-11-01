/* NitroSDK CARD: sets the backup device parameters from its type; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    int result;
    int type;
    int pad8[4];
    u32 total;
    u32 sector;
    u32 page;
    u32 addrWidth;
    u32 pageWait;
    u32 w2c;
    u32 w30;
    u32 w34;
    u32 w38;
    u32 w3c;
    u32 w40;
    u32 w44;
    u8 erased;
    u8 pad49[3];
    u32 caps;
} Arg;

extern Arg *data_020c4800;
extern void MI_CpuFill8(void *dst, int value, u32 size);

/* 98.69 %: the original schedules `mov r1, #3` between the two loads of the last statement. */
void func_02074290(int type) {
    Arg *p = data_020c4800;
    MI_CpuFill8(&p->total, 0, 0x48);
    p->type = type;
    p->caps = 0x3f;
    if (type != 0) {
        u32 size = 1 << ((type >> 8) & 0xff);
        u32 kind = type & 0xff;
        p->total = size;
        p->erased = 0xff;
        if (kind == 1) {
            switch (size) {
            case 0x200:
                p->page = 0x10;
                p->addrWidth = 1;
                p->pageWait = 5;
                p->erased = 0xf0;
                break;
            case 0x2000:
                p->page = 0x20;
                p->addrWidth = 2;
                p->pageWait = 5;
                p->erased = 0;
                break;
            case 0x10000:
                p->page = 0x80;
                p->addrWidth = 2;
                p->pageWait = 10;
                p->erased = 0;
                break;
            default:
                goto invalid;
            }
            p->sector = p->page;
            p->caps |= 0x40;
            p->caps |= 0x100;
            p->caps |= 0x200;
            return;
        }
        if (kind == 2) {
            switch (size) {
            case 0x40000:
            case 0x80000:
            case 0x100000:
                p->w2c = 0x19;
                p->w30 = 0x12c;
                p->w44 = 0x12c;
                p->w3c = 0x1388;
                p->caps |= 0x80;
                p->caps |= 0x400;
                break;
            case 0x200000:
                p->w3c = 0x3e8;
                p->w40 = 0xbb8;
                p->w34 = 0x4268;
                p->w38 = 0x9c40;
                p->erased = 0;
                p->caps |= 0x1000;
                break;
            case 0x800000:
                p->w3c = 0x3e8;
                p->w40 = 0xbb8;
                p->w34 = 0x109a0;
                p->w38 = 0x27100;
                p->erased = 0;
                p->caps |= 0x1000;
                break;
            default:
                goto invalid;
            }
            p->sector = 0x10000;
            p->page = 0x100;
            p->addrWidth = 3;
            p->pageWait = 5;
            p->caps |= 0x40;
            p->caps |= 0x100;
            p->caps |= 0x200;
            p->caps |= 0x800;
            return;
        }
        if (kind == 3) {
            if (size == 0x2000 || size == 0x8000) {
                p->page = size;
                p->sector = size;
                p->addrWidth = 2;
                p->erased = 0;
                p->caps |= 0x40;
                p->caps |= 0x100;
                p->caps |= 0x200;
                return;
            }
        }
    invalid:
        p->type = 0;
        p->total = 0;
        data_020c4800->result = 3;
    }
}
