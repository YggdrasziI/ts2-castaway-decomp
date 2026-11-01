/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on


#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"

void FS_InitFile(FSFile * p_file);
BOOL FS_OpenFileFast(FSFile * p_file, FSFileID file_id);
BOOL FS_ConvertPathToFileID(FSFileID * p_file_id, const char * path);
BOOL func_0209be20(NNSSndArc * arc, NNSSndHeapHandle heap, BOOL symbolLoadFlag);
extern BOOL func_0209be20 (NNSSndArc * arc, NNSSndHeapHandle heap, BOOL symbolLoadFlag);

extern NNSSndArc * data_020d5210;
/* func_0209c03c -- NitroSystem sndarc.c: func_0209c03c. */
void func_0209c03c (NNSSndArc * arc, const char * filePath, NNSSndHeapHandle heap, BOOL symbolLoadFlag)
{
    BOOL result;

    arc->info = NULL;
    arc->fat = NULL;
    arc->symbol = NULL;

    result = FS_ConvertPathToFileID(&arc->fileId, filePath);
    if (!result) return;

    FS_InitFile(&arc->file);
    result = FS_OpenFileFast(&arc->file, arc->fileId);
    if (!result) return;

    arc->file_open = TRUE;

    result = func_0209be20(arc, heap, symbolLoadFlag);
    if (!result) return;

    data_020d5210 = arc;
}
