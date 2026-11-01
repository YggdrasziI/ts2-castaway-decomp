/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#define func_02010b88 func_0209ed0c
#define offsetof(type, member) ((u32)&(((type *)0)->member))
#define NNS_FndCreateFrmHeap(startAddress, size) func_02010b88(startAddress, size, 0)
#define ROUNDUP(value, align) (((u32)(value) + ((align) - 1)) & ~((align) - 1))
#define HEAP_ALIGN 32
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
NNSSndArc * func_0209be08(NNSSndArc * arc);
void * NNS_SndArcGetFileAddress(u32 fileId);
void func_0209b9a0(u32 fileId, void * address);
void SND_InvalidateSeqData(const void *start, const void *end);
void SND_InvalidateBankData(const void *start, const void *end);
void func_0207e538(struct SNDBankData * bank);
void SND_InvalidateWaveData(const void *start, const void *end);
void SND_DestroyWaveArc(struct SNDBankData * bank);
void func_0207e0bc(struct SNDWaveArc * waveArc, int index, const SNDWaveData * address);
const SNDWaveData * func_0207e074(const struct SNDWaveArc * waveArc, int index);
extern struct SNDWaveArc;
extern u32 func_0207e0f4(const SNDWaveArc *waveArc);
extern void DC_StoreRange(void *address, u32 size);
extern s32 func_0209ba04(u32 fileId, void *buffer, s32 size, s32 offset);
struct SNDInstPos SND_GetFirstInstDataPos(const struct SNDBankData * bank);
BOOL SND_GetNextInstData(const struct SNDBankData * bank, struct SNDInstData * inst, struct SNDInstPos * pos);
NNSFndHeapHandle func_0209ed0c(void * startAddress, u32 size, int optFlag);
void func_0209ed00(NNSFndHeapHandle heap);
extern BOOL InitHeap(NNSSndHeap * heap, NNSFndHeapHandle handle);
void NNS_FndRemoveListObject(NNSFndList * list, void * object);
void * NNS_FndGetPrevListObject(NNSFndList * list, void * object);
void func_0209ec78(NNSFndHeapHandle heap, int mode);
extern BOOL NewSection(NNSSndHeap * heap);
extern void EraseSync(void);
void NNS_FndAppendListObject(NNSFndList * list, void * object);
void * NNS_FndAllocFromFrmHeapEx(NNSFndHeapHandle heap, u32 size, int alignment);
BOOL func_0209ec20(NNSFndHeapHandle heap, u32 tagName);
BOOL NNS_FndFreeByStateToFrmHeap(NNSFndHeapHandle heap, u32 tagName);
void func_0209c7a8 (void * mem, NNSSndArc * arc, u32 fileId);
void func_0209c774 (void * mem, u32 size, u32 data1, u32 data2);
void func_0209c738 (void * mem, u32 size, u32 data1, u32 data2);
void func_0209c6fc (void * mem, u32 size, u32 data1, u32 data2);
void func_0209c6d8 (void * mem, u32 size, u32 data1, u32 data2);
void func_0209c684 (void * mem, u32 size, u32 data1, u32 data2);
BOOL func_0209c590(SNDWaveArc *waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap);
BOOL func_0209c4c0 (SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);
NNSSndHeapHandle func_0209c424 (void * startAddress, u32 size);
void func_0209c408 (NNSSndHeapHandle heap);
void func_0209c348 (NNSSndHeapHandle heap);
void * func_0209c2d8 (NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
int func_0209c280 (NNSSndHeapHandle heap);
void func_0209c194 (NNSSndHeapHandle heap, int level);

void func_0209c7a8 (void * mem, NNSSndArc * arc, u32 fileId)
{
    NNSSndArc * oldArc;
    OSIntrMode old;

    if (arc == NULL) return;

    old = OS_DisableInterrupts();
    oldArc = func_0209be08(arc);

    if (mem == NNS_SndArcGetFileAddress(fileId)) {
        func_0209b9a0(fileId, NULL);
    }

    (void)func_0209be08(oldArc);
    (void)OS_RestoreInterrupts(old);
}

void func_0209c774 (void * mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    func_0209c7a8(mem, arc, fileId);
    SND_InvalidateSeqData(mem, (u8 *)mem + size);
}

void func_0209c738 (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDBankData * bank = (SNDBankData *)mem;
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    func_0209c7a8(mem, arc, fileId);
    SND_InvalidateBankData(mem, (u8 *)mem + size);

    func_0207e538(bank);
}

void func_0209c6fc (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDBankData * bank = (SNDBankData *)mem;
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    func_0209c7a8(mem, arc, fileId);
    SND_InvalidateWaveData(mem, (u8 *)mem + size);

    SND_DestroyWaveArc(bank);
}

void func_0209c6d8 (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDWaveArc * waveArc = (SNDWaveArc *)mem;
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    (void)size;

    func_0209c7a8(mem, arc, fileId);
    SND_DestroyWaveArc((SNDBankData *)waveArc);
}

void func_0209c684 (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDWaveArc * waveArc = (SNDWaveArc *)data1;
    u32 waveNo = data2;

    if (mem == func_0207e074(waveArc, (int)waveNo)) {
        func_0207e0bc(waveArc, (int)waveNo, NULL);
    }

    SND_InvalidateWaveData(mem, (u8 *)mem + size);
}

BOOL func_0209c590(SNDWaveArc *waveArc, int waveNo, u32 fileId, NNSSndHeapHandle heap)
{
    SNDWaveData *buffer;
    u32 len;
    u32 begin;
    u32 end;
    u32 waveCount;

    if (func_0207e074(waveArc, waveNo) != 0) {
        return 1;
    }

    waveCount = func_0207e0f4(waveArc);

    {
        const SNDWaveArc *entry = (const SNDWaveArc *)((const char *)waveArc +
            (waveArc->waveCount + waveNo) * sizeof(u32));

        begin = entry->waveOffset[0];
        if (waveNo < waveCount - 1) {
            end = entry->waveOffset[1];
        } else {
            end = waveArc->fileHeader.fileSize;
        }
        len = end - begin;

        if (heap == 0) {
            return 0;
        }

        buffer = (SNDWaveData *)func_0209c2d8(
            heap,
            len + 32,
            func_0209c684,
            (u32)waveArc,
            (u32)waveNo
        );
        if (buffer == 0) {
            return 0;
        }

        if (func_0209ba04(fileId, buffer, (s32)len, (s32)begin) != len) {
            return 0;
        }

        DC_StoreRange(buffer, len);
        func_0207e0bc(waveArc, waveNo, buffer);

        return 1;
    }
}

BOOL func_0209c4c0 (SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap)
{
    SNDInstPos pos = SND_GetFirstInstDataPos(bank);
    SNDInstData inst;

    if (bank == NULL) {
        return FALSE;
    }

    while (SND_GetNextInstData(bank, &inst, &pos)) {
        if (inst.type == SND_INST_PCM && waveArcNo == inst.param.wave[1]) {
            if (!func_0209c590(waveArc, inst.param.wave[0], fileId, heap)) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

NNSSndHeapHandle func_0209c424 (void * startAddress, u32 size)
{
    NNSSndHeap * heap;
    void * endAddress;
    NNSFndHeapHandle handle;

    endAddress = (u8 *)startAddress + size;
    startAddress = (void *)ROUNDUP(startAddress, 4);

    if (startAddress > endAddress) return NNS_SND_HEAP_INVALID_HANDLE;

    size = (u32)((u8 *)endAddress - (u8 *)startAddress);
    if (size < sizeof(NNSSndHeap)) {
        return NNS_SND_HEAP_INVALID_HANDLE;
    }

    size -= sizeof(NNSSndHeap);

    heap = (NNSSndHeap *)startAddress;
    startAddress = heap + 1;

    handle = NNS_FndCreateFrmHeap(startAddress, size);
    if (handle == NNS_FND_HEAP_INVALID_HANDLE) {
        return NULL;
    }

    if (!InitHeap(heap, handle)) {
        func_0209ed00(handle);
        return NNS_SND_HEAP_INVALID_HANDLE;
    }

    return heap;
}

void func_0209c408 (NNSSndHeapHandle heap)
{

    func_0209c348(heap);
    func_0209ed00(heap->handle);
}

void func_0209c348 (NNSSndHeapHandle heap)
{
    NNSSndHeapSection * section = NULL;
    void * object;
    BOOL result;
    BOOL doCallback = FALSE;

    while ((section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL)) != NULL) {

        object = NULL;
        while ((object = NNS_FndGetPrevListObject(&section->blockList, object)) != NULL) {
            NNSSndHeapBlock * block = (NNSSndHeapBlock *)object;
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }

        NNS_FndRemoveListObject(&heap->sectionList, section);
    }

    func_0209ec78(heap->handle, NNS_FND_FRMHEAP_FREE_ALL);

    if (doCallback) EraseSync();

    result = NewSection(heap);
}

void * func_0209c2d8 (NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2)
{
    NNSSndHeapSection * section;
    NNSSndHeapBlock * block;

    block = (NNSSndHeapBlock *)NNS_FndAllocFromFrmHeapEx(
        heap->handle, sizeof(NNSSndHeapBlock) + ROUNDUP(size, HEAP_ALIGN), HEAP_ALIGN);
    if (block == NULL) return NULL;

    section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

    block->size = size;
    block->callback = callback;
    block->data1 = data1;
    block->data2 = data2;
    NNS_FndAppendListObject(&section->blockList, block);

    return block->buffer;
}

int func_0209c280 (NNSSndHeapHandle heap)
{
    BOOL result;

    if (!func_0209ec20(heap->handle, heap->sectionList.numObjects)) {
        return -1;
    }

    if (!NewSection(heap)) {
        result = NNS_FndFreeByStateToFrmHeap(heap->handle, 0);
        return -1;
    }

    return heap->sectionList.numObjects - 1;
}

void func_0209c194 (NNSSndHeapHandle heap, int level)
{
    NNSSndHeapSection * section;
    void * object = NULL;
    BOOL result;
    BOOL doCallback = FALSE;

    if (level == 0) {
        func_0209c348(heap);
        return;
    }

    while (level < heap->sectionList.numObjects) {
        section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

        while ((object = NNS_FndGetPrevListObject(&section->blockList, object)) != NULL) {
            NNSSndHeapBlock * block = (NNSSndHeapBlock *)object;
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }

        NNS_FndRemoveListObject(&heap->sectionList, section);
    }

    result = NNS_FndFreeByStateToFrmHeap(heap->handle, (u32)level);

    if (doCallback) EraseSync();

    result = func_0209ec20(heap->handle, heap->sectionList.numObjects);

    result = NewSection(heap);
}
