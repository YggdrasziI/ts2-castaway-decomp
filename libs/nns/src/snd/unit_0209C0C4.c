/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#include "sdk/os.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))
extern void NNS_FndInitList(void *list, int offset);
void NNS_FndAppendListObject(NNSFndList * list, void * object);
void * NNS_FndAllocFromFrmHeapEx(NNSFndHeapHandle heap, u32 size, int alignment);
BOOL func_0207d974(u32 flags);
void SND_WaitForCommandProc(u32 tag);
u32 func_0207d8a4(void);
void func_0209c178(void *list);
BOOL InitHeap (NNSSndHeap * heap, NNSFndHeapHandle handle);
BOOL NewSection (NNSSndHeap * heap);
void EraseSync (void);

void func_0209c178(void *list)
{
    NNS_FndInitList(list, 0);
}

BOOL InitHeap (NNSSndHeap * heap, NNSFndHeapHandle handle)
{
    NNS_FND_INIT_LIST(&heap->sectionList, NNSSndHeapSection, link);
    heap->handle = handle;

    if (!NewSection(heap)) {
        return FALSE;
    }

    return TRUE;
}

BOOL NewSection (NNSSndHeap * heap)
{
    NNSSndHeapSection * section;

    section = (NNSSndHeapSection *)NNS_FndAllocFromFrmHeap(heap->handle, sizeof(NNSSndHeapSection));
    if (section == NULL) {
        return FALSE;
    }
    func_0209c178(section);

    NNS_FndAppendListObject(&heap->sectionList, section);

    return TRUE;
}

void EraseSync (void)
{
    u32 commandTag;

    commandTag = func_0207d8a4();
    (void)func_0207d974(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
