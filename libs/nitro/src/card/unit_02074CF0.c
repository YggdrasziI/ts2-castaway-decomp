/* NitroSDK CARD: reads pages from the ROM through the card registers; written from the ROM. File bounds are a hypothesis. */
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

/* 94.00 %: registers of the addresses and the buffer, and the literal pool order (the
 * original loads data_020c4800 first); local orders and a local pointer to
 * data_020c4800 tried. The const view in the last test gives the reload of dst. */
void func_02074cf0(Task *task) {
    for (;;) {
        u32 *dst;
        u32 src = data_020c4800.src;
        u32 page = src & -0x200;
        if (page == src && !((dst = (u32 *)data_020c4800.dst, (u32)dst & 3)) && data_020c4800.len >= 0x200) {
        } else {
            dst = task->buffer;
            task->cached = page;
        }
        func_0207509c((page >> 8) | 0xb7000000, page << 24);
        REG_CTRL = task->ctrl;
        {
            u32 i = 0;
            u32 status;
            do {
                status = REG_CTRL;
                if (status & 0x800000) {
                    u32 value = REG_DATA;
                    if (i < 0x200) {
                        dst[i] = value;
                        i++;
                    }
                }
            } while (status & 0x80000000);
        }
        if ((u32)dst == ((const Common *)&data_020c4800)->dst) {
            data_020c4800.src += 0x200;
            data_020c4800.dst += 0x200;
            data_020c4800.len -= 0x200;
            if (data_020c4800.len == 0) {
                return;
            }
        } else if (!func_0207513c(task)) {
            return;
        }
    }
}
/* END */
