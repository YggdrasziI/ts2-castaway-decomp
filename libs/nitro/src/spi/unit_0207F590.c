/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern int func_0207fb38(int led);
extern int func_0207fb74(int led, void *callback, void *arg);
extern int data_020c7750;
int func_0207f590(int mode, int led, int skip, int sync)
{
    if (mode != 0) {
        if (mode == 1) {
            if (skip == 0) {
                if ((u32)(*(int *)0x027ffc3c - data_020c7750) <= 7) {
                    return 0;
                }
            }
            if (led != 0) {
                if (sync != 0) {
                    func_0207fb38(led);
                } else {
                    func_0207fb74(led, 0, 0);
                }
            }
            *(volatile u16 *)0x04000304 |= 1;
        }
    } else {
        *(volatile u16 *)0x04000304 &= ~1;
        data_020c7750 = *(int *)0x027ffc3c;
        if (led != 0) {
            if (sync != 0) {
                func_0207fb38(led);
            } else {
                func_0207fb74(led, 0, 0);
            }
        }
    }
    return 1;
}
