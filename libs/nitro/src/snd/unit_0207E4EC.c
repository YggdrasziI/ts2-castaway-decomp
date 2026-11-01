/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void func_0207d5e0(void);
extern void func_0207d5cc(void);
extern void DC_StoreRange(void *p, unsigned int len);
void SND_DestroyWaveArc(int **owner);

void SND_DestroyWaveArc(int **owner) {
    int *node;
    int zero;
    int len;
    int *next;
    func_0207d5e0();
    node = (int *)owner[6];
    if (node != 0) {
        zero = 0;
        len = 8;
        do {
            next = (int *)node[1];
            node[0] = zero;
            node[1] = zero;
            DC_StoreRange(node, len);
            node = next;
        } while (next != 0);
    }
    func_0207d5cc();
}
