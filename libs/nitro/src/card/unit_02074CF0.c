/*
 * NitroSDK CARD: reads pages from the ROM through the card registers (CARDi_ReadCard). Structure
 * from khdays' CARDi_ReadCard.c (CC0), retyped for this ROM; the end returns early and jumps back
 * instead of jumping back from the tests. File bounds are a hypothesis.
 */
#pragma force_active on

typedef unsigned int u32;

typedef struct {
    unsigned char pad[0x1c];
    u32 src;
    u32 dst;
    u32 len;
} Common;

typedef struct {
    int pad0;
    u32 ctrl;
    u32 cached;
    int pad[5];
    u32 buffer[0x80];
} Task;

extern Common data_020c4800;
extern void func_0207509c(u32 a, u32 b);
extern int func_0207513c(Task *task);

#define REG_CTRL (*(volatile u32 *)0x040001a4)
#define REG_DATA (*(volatile u32 *)0x04100010)

static inline int func_advance(Task *task) {
    Common *common = &data_020c4800;
    common->src += 0x200;
    common->dst += 0x200;
    common->len -= 0x200;
    return common->len > 0;
}

void func_02074cf0(Task *task) {
    Common *const common = &data_020c4800;

read_page:
    {
        const u32 length = 0x200;
        u32 source = common->src & ~(0x200 - 1);
        u32 destination;

        if ((source != common->src) || ((common->dst & 3) != 0) || (common->len < length)) {
            destination = (u32)task->buffer;
            task->cached = source;
        } else {
            destination = common->dst;
        }

        func_0207509c(0xb7000000 | (source >> 8), source << 24);
        {
            u32 index = 0;

            REG_CTRL = task->ctrl;
            for (;;) {
                const u32 control = REG_CTRL;
                if ((control & 0x800000) != 0) {
                    u32 data = REG_DATA;
                    if (index < length) {
                        ((u32 *)destination)[index++] = data;
                    }
                }
                if ((control & 0x80000000) == 0) {
                    break;
                }
            }
        }

        if (destination == common->dst) {
            if (!func_advance(task)) {
                return;
            }
        } else if (!func_0207513c(task)) {
            return;
        }
        goto read_page;
    }
}
