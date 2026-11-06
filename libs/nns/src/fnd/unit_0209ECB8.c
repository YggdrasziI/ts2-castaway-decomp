/* NitroSystem FND frame heap: NNS_FndAllocFromFrmHeapEx. Heroes of Mana's source
 * (CC0), retyped for this ROM: the heap head follows the common header (+0x24). File
 * bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;

void *func_0209ee14(void *head, u32 size, s32 alignment); /* from the head */
void *func_0209eda0(void *head, u32 size, s32 alignment); /* from the tail */

void *NNS_FndAllocFromFrmHeapEx(u8 *heap, u32 size, s32 alignment) {
    u8 *head;

    head = heap + 0x24;
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3;
    if (alignment >= 0) {
        return func_0209ee14(head, size, alignment);
    }
    return func_0209eda0(head, size, -alignment);
}
