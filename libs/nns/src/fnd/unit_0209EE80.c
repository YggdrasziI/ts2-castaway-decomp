/* NitroSystem: creates a frame heap in a block; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned int u32;

typedef struct {
    u32 pad[6];
    void *start;
    void *end;
    u32 pad20;
} Heap;

typedef struct {
    void *head;
    void *tail;
    void *state;
} Frame;

extern void func_0209ea98(void *heap, u32 signature, void *start, u32 size, int options);

void *func_0209ee80(Heap *heap, u32 size, int options) {
    Frame *frame = (Frame *)((char *)heap + 0x24);
    func_0209ea98(heap, 0x46524d48, frame + 1, size, options);
    frame->head = heap->start;
    frame->tail = heap->end;
    frame->state = 0;
    return heap;
}
