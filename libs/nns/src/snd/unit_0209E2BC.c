/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


struct S {
    char _0[0x110];
    int flags;
    char _114[0x164 - 0x114];
    void (*x168)(void *);
};
extern void FreeChannel(void *p);
extern void RemoveCommandByPlayer(void *list, void *node);
extern void FreePlayer(void *p);
extern char data_020d5ae0[];
extern char *data_020d5254[];
void func_0209e2bc(struct S *p);

void func_0209e2bc(struct S *p)
{
    char *q;
    if (((p->flags << 31) >> 31) == 0) return;
    FreeChannel(p);
    p->x168(p);
    RemoveCommandByPlayer(data_020d5ae0, p);
    q = data_020d5254[0];
    if (q != 0) {
        RemoveCommandByPlayer(q + 0x4e0, p);
    }
    FreePlayer(p);
}
