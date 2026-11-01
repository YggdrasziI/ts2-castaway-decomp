/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


#define ThreadInfo ThreadInfo
typedef struct Node {
    char pad[0x68];
    struct Node *next;  /* +0x68 */
    int pad2;           /* +0x6c */
    int value;          /* +0x70 */
} Node;
typedef struct {
    char pad[8];
    Node *head;         /* +0x2c */
} ListHead;
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);
extern void func_0207ae30(void *);
extern void func_0207acfc(void);
extern ListHead ThreadInfo;
extern Node data_020c57c0;
int func_0207a694(Node *target, int newval);

int func_0207a694(Node *target, int newval)
{
    Node *cur;
    Node *prev;
    int intr;

    prev = 0;
    cur = ThreadInfo.head;
    intr = OS_DisableInterrupts();
    while (cur != 0 && cur != target) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == 0 || cur == &data_020c57c0) {
        OS_RestoreInterrupts(intr);
        return 0;
    }
    if (cur->value != newval) {
        if (prev == 0) {
            ThreadInfo.head = target->next;
        } else {
            prev->next = target->next;
        }
        target->value = newval;
        func_0207ae30(target);
        func_0207acfc();
    }
    OS_RestoreInterrupts(intr);
    return 1;
}
