/*
 * Unit 0x02099210-0x020997FC: the heap class Unk020c8440 (aligned first-fit
 * allocator over a free list of offset ranges) and its block headers.
 *
 * Bounds: hypothesis. Before 0x02099210 lie fixed-point vector helpers that
 * nothing here uses; 0x02099800 starts unit_02099800.cpp. Every function is
 * reached from unit_02099870.cpp or from this range. Real file name unknown.
 * Not complete: func_02099280 and func_02099678 do not match yet (comments above
 * them).
 */

#include "game/unk_heap.h"

extern "C" void *func_020993d8(Unk020c8440 *heap, u32 size, Unk02099210Header *header);
extern "C" void func_02099678(Unk020c8440 *heap, void *ptr, Unk02099210Header *header);
extern "C" Unk02099210Header *func_020997f8(void *ptr);

Unk020c8440::Unk020c8440() {
    list = 0;
    start = 0;
    size = 0;
    padding = 0;
    alignShift = 0;
    align = 0;
    id = 0;
    used = 0;
    unk20 = 0;
    unk24 = 0;
    flags = 0;
}

Unk020c8440::~Unk020c8440() {
    if (list != 0 && (flags & 2)) {
        delete list;
        list = 0;
    }
}

/* 94.06 %: the free-list loop differs. The original keeps one pointer for the
 * node it clears but computes the next-node address with a multiply from the
 * incremented index (`add r3, r3, #1; mla r1, r3, r0, lr`) and stores offset, size,
 * next in that order; every loop form tried strength-reduces both addresses. */
extern "C" void func_02099280(Unk020c8440 *heap, void *start, u32 size, u32 alignShift, int id, u8 inlineHeader, Unk020c8700 *list) {
    u32 aligned;
    Unk020c8700 *l;
    Unk02099210Node *node;
    u32 i;

    heap->start = (u32)start;
    heap->size = size;
    if (alignShift < 2) {
        alignShift = 2;
    }
    heap->alignShift = alignShift;
    heap->align = 1 << alignShift;
    heap->flags = inlineHeader ? 0 : 1;
    heap->id = id;
    heap->list = list;
    heap->used = 0;
    if (inlineHeader) {
        aligned = ((heap->start + (heap->align + 3)) & ~(heap->align - 1)) - 4;
    } else {
        aligned = (heap->start + (heap->align - 1)) & ~(heap->align - 1);
    }
    heap->padding = aligned - heap->start;
    heap->start = aligned;
    heap->size = heap->size - heap->padding;

    l = heap->list;
    if (l == 0) {
        return;
    }
    size = heap->size;
    l->total = size;
    l->nodes[0].offset = 0;
    l->nodes[0].size = size;
    l->nodes[0].next = 0;
    for (i = 1; i < 255; i++) {
        l->nodes[i].next = &l->nodes[i + 1];
        l->nodes[i].offset = 0;
        l->nodes[i].size = 0;
    }
    l->nodes[255].offset = 0;
    l->nodes[255].size = 0;
    l->nodes[255].next = 0;
    l->free = &l->nodes[0];
    l->spare = &l->nodes[1];
}

extern "C" void *func_02099390(Unk020c8440 *heap, u32 size) {
    if (heap->flags & 1) {
        return 0;
    }
    return func_020993d8(heap, size, 0);
}

extern "C" void *func_020993b0(Unk020c8440 *heap, u32 size, Unk02099210Handle *handle) {
    if (!(heap->flags & 1)) {
        return 0;
    }
    return handle->ptr = func_020993d8(heap, size, &handle->header);
}

static inline int AllocFromHint(Unk020c8700 *list, u32 size, u32 hint) {
    Unk02099210Node *node = list->free;
    u32 offset;
    int found;
    Unk02099210Node *spare;
    u32 rest;
    Unk02099210Node *prev = 0;

    if (size > list->total) {
        return -1;
    }
    while (node != 0) {
        if (hint >= node->offset && hint < node->offset + node->size &&
            size <= node->size - (hint - node->offset)) {
            break;
        }
        if (node->offset >= hint && node->size >= size) {
            break;
        }
        prev = node;
        node = node->next;
    }
    if (node == 0) {
        return -1;
    }
    offset = node->offset;
    found = offset > hint ? offset : hint;
    if (hint > offset) {
        if (list->spare != 0) {
            rest = offset + node->size - (hint + size);
            node->size = hint - offset;
            if (rest != 0) {
                spare = list->spare;
                list->spare = spare->next;
                spare->next = node->next;
                node->next = spare;
                spare->offset = found + size;
                spare->size = rest;
            }
        } else {
            return -1;
        }
    } else {
        node->size -= size;
        node->offset += size;
    }
    if (node->size == 0) {
        Unk02099210Node *next = node->next;
        if (prev != 0) {
            prev->next = next;
        } else {
            list->free = next;
        }
        node->next = list->spare;
        list->spare = node;
    }
    return found;
}

static inline int AllocFirstFit(Unk020c8700 *list, u32 size) {
    Unk02099210Node *node = list->free;
    Unk02099210Node *prev = 0;
    int found;

    if (size > list->total) {
        return -1;
    }
    while (node != 0) {
        if (node->size >= size) {
            break;
        }
        prev = node;
        node = node->next;
    }
    if (node == 0) {
        return -1;
    }
    found = node->offset;
    node->size -= size;
    node->offset += size;
    if (node->size == 0) {
        Unk02099210Node *next = node->next;
        if (prev != 0) {
            prev->next = next;
        } else {
            list->free = next;
        }
        node->next = list->spare;
        list->spare = node;
    }
    return found;
}

extern "C" void *func_020993d8(Unk020c8440 *heap, u32 size, Unk02099210Header *header) {
    u32 result;
    int found;
    Unk020c8700 *list;

    if (header == 0) {
        size += 4;
    }
    size = (size + (heap->align - 1)) & ~(heap->align - 1);
    list = heap->list;
    result = 0;
    if (list != 0) {
        found = -1;
        if (size <= heap->unk20) {
            found = AllocFromHint(heap->list, size, heap->unk24);
        }
        if (found < 0) {
            found = AllocFirstFit(heap->list, size);
        }
        if (found >= 0) {
            result = heap->start + found;
        }
    }
    if (result != 0) {
        if (header == 0) {
            header = (Unk02099210Header *)result;
            result += 4;
        }
        header->size = size;
        header->used = 1;
        header->unk25 = 0;
        header->id = heap->id;
        heap->used += size;
    }
    return (void *)result;
}

extern "C" void func_02099638(Unk020c8440 *heap, void *ptr) {
    if (heap->flags & 1) {
        return;
    }
    func_02099678(heap, ptr, 0);
}

extern "C" void func_02099654(Unk020c8440 *heap, Unk02099210Handle *handle) {
    if (!(heap->flags & 1)) {
        return;
    }
    func_02099678(heap, handle->ptr, &handle->header);
}

/* 99.33 %: one register differs: the spare node taken from the list is in lr in the
 * original and in r12 here (declaration orders and block forms tried). */
extern "C" void func_02099678(Unk020c8440 *heap, void *ptr, Unk02099210Header *header) {
    Unk02099210Node *spare;
    Unk020c8700 *list;
    u32 size;
    u32 offset;
    Unk02099210Node *merged;
    Unk02099210Node *node;
    Unk02099210Node *prev;

    if (header == 0) {
        header = (Unk02099210Header *)((u32)ptr - 4);
        offset = (u32)header - heap->start;
    } else {
        offset = (u32)ptr - heap->start;
    }
    if (heap->list == 0) {
        return;
    }
    header->used = 0;
    heap->used -= header->size;
    size = header->size;
    list = heap->list;
    if (offset > list->total || size > list->total) {
        return;
    }
    prev = 0;
    for (node = list->free; node != 0; node = node->next) {
        if (offset + size <= node->offset) {
            break;
        }
        prev = node;
    }
    merged = 0;
    if (prev != 0 && offset == prev->offset + prev->size) {
        prev->size += size;
        merged = prev;
    }
    if (merged == 0) {
        spare = list->spare;
        if (spare != 0) {
            list->spare = spare->next;
            spare->next = node;
            if (prev != 0) {
                prev->next = spare;
            } else {
                list->free = spare;
            }
            spare->offset = offset;
            spare->size = size;
            merged = spare;
        }
    }
    if (node == 0) {
        return;
    }
    if (node->offset != offset + size) {
        return;
    }
    merged->size += node->size;
    merged->next = node->next;
    node->next = list->spare;
    list->spare = node;
}

extern "C" u32 func_020997a4(Unk020c8440 *heap) {
    return heap->start;
}

extern "C" int func_020997ac(Unk020c8440 *heap) {
    return heap->used == 0;
}

extern "C" void func_020997c0(Unk020c8440 *heap, u32 limit, u32 reserve) {
    heap->unk20 = limit;
    heap->unk24 = heap->size - reserve;
    if (heap->unk24 < heap->size >> 1) {
        heap->unk24 = heap->size >> 1;
    }
}

extern "C" int func_020997e4(void *ptr) {
    return func_020997f8(ptr)->id;
}

extern "C" Unk02099210Header *func_020997f8(void *ptr) {
    return (Unk02099210Header *)((u32)ptr - 4);
}
