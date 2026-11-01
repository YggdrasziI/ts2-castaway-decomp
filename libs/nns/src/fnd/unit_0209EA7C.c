/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/mi.h"
#include "sdk/os.h"
#include "nnsys/fnd.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
typedef u32 NNSiUIntPtr;
inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}
inline void* AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}
static inline NNSiFndFrmHeapHead * GetFrmHeapHeadPtrFromHeapHead (NNSiFndHeapHead * pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}
extern void func_0209ed88 (NNSiFndHeapHead * pHeapHd);
extern void func_0209ed58 (NNSiFndHeapHead * pHeapHd);
extern void * func_0209ee14 (NNSiFndFrmHeapHead * pFrmHeapHd, u32 size, int alignment);
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern char data_020d60b0;
extern int data_020d60ac;
extern void NNS_FndInitList(NNSFndList *list, s32 linkOffset);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *heap);
void func_0209ec78 (NNSFndHeapHandle heap, int mode);
BOOL func_0209ec20 (NNSFndHeapHandle heap, u32 tagName);
BOOL NNS_FndFreeByStateToFrmHeap (NNSFndHeapHandle heap, u32 tagName);
void *func_0209eb54(void *list, char *p);
void *func_0209eb28(void *heap);
void func_0209ea98(
    struct NNSiFndHeapHead *head,
    u32 signature,
    void *heapStart,
    void *heapEnd,
    u16 optionFlag);
void func_0209ea7c(void *heap);

void func_0209ec78 (NNSFndHeapHandle heap, int mode)
{

    if (mode & NNS_FND_FRMHEAP_FREE_HEAD) {
        func_0209ed88(heap);
    }

    if (mode & NNS_FND_FRMHEAP_FREE_TAIL) {
        func_0209ed58(heap);
    }
}

BOOL func_0209ec20 (NNSFndHeapHandle heap, u32 tagName)
{

    {
        NNSiFndFrmHeapHead * pFrmHeapHd = GetFrmHeapHeadPtrFromHeapHead(heap);
        void * oldHeadAllocator = pFrmHeapHd->headAllocator;

        NNSiFndFrmHeapState * pState = func_0209ee14(pFrmHeapHd, sizeof(NNSiFndFrmHeapState), MIN_ALIGNMENT);
        if (!pState) {
            return FALSE;
        }

        pState->tagName = tagName;
        pState->headAllocator = oldHeadAllocator;
        pState->tailAllocator = pFrmHeapHd->tailAllocator;
        pState->pPrevState = pFrmHeapHd->pState;

        pFrmHeapHd->pState = pState;

        return TRUE;
    }
}

BOOL NNS_FndFreeByStateToFrmHeap (NNSFndHeapHandle heap, u32 tagName)
{

    {
        NNSiFndFrmHeapHead * pFrmHeapHd = GetFrmHeapHeadPtrFromHeapHead(heap);
        NNSiFndFrmHeapState * pState = pFrmHeapHd->pState;

        if (tagName != 0) {
            for (; pState; pState = pState->pPrevState)
            {
                if (pState->tagName == tagName)
                    break;
            }
        }

        if (!pState) {
            return FALSE;
        }

        pFrmHeapHd->headAllocator = pState->headAllocator;
        pFrmHeapHd->tailAllocator = pState->tailAllocator;

        pFrmHeapHd->pState = pState->pPrevState;

        return TRUE;
    }
}

void *func_0209eb54(void *list, char *p) {
    char *heap = NNS_FndGetNextListObject(list, 0);
    while (heap != 0) {
        if (*(char **)(heap + 0x18) <= p && p < *(char **)(heap + 0x1c)) {
            char *inner = func_0209eb54(heap + 0xc, p);
            if (inner == 0) {
                inner = heap;
            }
            return inner;
        }
        heap = NNS_FndGetNextListObject(list, heap);
    }
    return 0;
}

void *func_0209eb28(void *heap) {
    char *list = &data_020d60b0;
    void *found = func_0209eb54(list, heap);
    if (found != 0) {
        list = (char *)found + 0xc;
    }
    return list;
}

void func_0209ea98(
    struct NNSiFndHeapHead *head,
    u32 signature,
    void *heapStart,
    void *heapEnd,
    u16 optionFlag)
{
    head->signature = signature;
    head->heapStart = heapStart;
    head->heapEnd = heapEnd;
    head->attribute = 0;
    head->attribute &= ~0xff;
    head->attribute |= optionFlag & 0xff;
    NNS_FndInitList(&head->childList, 4);
    if (!data_020d60ac) {
        NNS_FndInitList((NNSFndList *)&data_020d60b0, 4);
        data_020d60ac = 1;
    }
    NNS_FndAppendListObject(func_0209eb28(head), head);
}

void func_0209ea7c(void *heap) {
    NNS_FndRemoveListObject(func_0209eb28(heap), heap);
}
