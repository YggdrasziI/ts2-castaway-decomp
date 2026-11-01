/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#define data_0204ad4c data_020d5210
#define data_02046468 data_020d5210
static inline
const void * GetPtrConst (const void * base, u32 offset)
{
    if (offset == 0) return NULL ;
    return (const u8 *)base + offset;
}
static inline
const NNSSndArcOffsetTable * GetOffsetTable (const NNSSndArcInfo * info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}
s32 FS_ReadFile(FSFile * p_file, void * dst, s32 len);
BOOL FS_SeekFile(FSFile * p_file, s32 offset, FSSeekFileMode origin);
void * func_0209c2d8(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
extern void InfoDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);
extern void FatDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);
extern void SymbolDisposeCallback(void * mem, u32 size, u32 data1, u32 data2);
extern NNSSndArc *data_020d5210;
extern const void * GetPtrConst(const void * base, u32 offset);
extern const NNSSndArcOffsetTable * GetOffsetTable(const NNSSndArcInfo * info, u32 offset);
BOOL func_0209be20 (NNSSndArc * arc, NNSSndHeapHandle heap, BOOL symbolLoadFlag);
int func_0209be08(int arg0);
int func_0209bdf8(void);
const NNSSndArcSeqInfo * func_0209bd94 (int seqNo);
const NNSSndArcSeqArcInfo * func_0209bd30 (int seqArcNo);
const NNSSndArcBankInfo * func_0209bccc (int bankNo);
const NNSSndArcWaveArcInfo * func_0209bc68 (int waveArcNo);
const NNSSndArcStrmInfo * func_0209bc04 (int strmNo);
const NNSSndArcPlayerInfo * func_0209bba0 (int playerNo);
const NNSSndArcStrmPlayerInfo * func_0209bb3c (int playerNo);

BOOL func_0209be20 (NNSSndArc * arc, NNSSndHeapHandle heap, BOOL symbolLoadFlag)
{
    BOOL result;
    s32 readSize;

    result = FS_SeekFile(&arc->file, 0, FS_SEEK_SET);
    if (!result) return FALSE;

    readSize = FS_ReadFile(
        &arc->file,
        &arc->header,
        sizeof(arc->header)
        );
    if (readSize != sizeof(arc->header)) return FALSE;

    if (heap != NNS_SND_HEAP_INVALID_HANDLE) {

        arc->info = (NNSSndArcInfo *)func_0209c2d8(heap, arc->header.infoSize, InfoDisposeCallback, (u32)arc, 0);
        if (arc->info == NULL) return FALSE;
        result = FS_SeekFile(&arc->file, (s32)(arc->header.infoOffset), FS_SEEK_SET);
        if (!result) return FALSE;
        readSize = FS_ReadFile(&arc->file, arc->info, (s32)(arc->header.infoSize));
        if (readSize != arc->header.infoSize) return FALSE;

        arc->fat = (NNSSndArcFat *)func_0209c2d8(heap, arc->header.fatSize, FatDisposeCallback, (u32)arc, 0);
        if (arc->fat == NULL) return FALSE;
        result = FS_SeekFile(&arc->file, (s32)(arc->header.fatOffset), FS_SEEK_SET);
        if (!result) return FALSE;
        readSize = FS_ReadFile(&arc->file, arc->fat, (s32)(arc->header.fatSize));
        if (readSize != arc->header.fatSize) return FALSE;

        if (symbolLoadFlag && arc->header.symbolDataSize > 0) {
            arc->symbol = (NNSSndArcSymbol *)func_0209c2d8(heap, arc->header.symbolDataSize, SymbolDisposeCallback, (u32)arc, 0);
            if (arc->symbol == NULL) return FALSE;
            result = FS_SeekFile(&arc->file, (s32)(arc->header.symbolDataOffset), FS_SEEK_SET);
            if (!result) return FALSE;

            readSize = FS_ReadFile(&arc->file, arc->symbol, (s32)(arc->header.symbolDataSize));
            if (readSize != arc->header.symbolDataSize) return FALSE;
        }
    }

    return TRUE;
}

int func_0209be08(int arg0)
{
    int old = (int)data_020d5210;
    data_020d5210 = (NNSSndArc *)arg0;
    return old;
}

int func_0209bdf8(void) {
    return (int)data_020d5210;
}

const NNSSndArcSeqInfo * func_0209bd94 (int seqNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->seqOffset);
    if (table == NULL) return NULL;

    if (seqNo < 0) return NULL;
    if (seqNo >= table->count) return NULL;

    return (const NNSSndArcSeqInfo *)GetPtrConst(arc->info, table->offset[ seqNo ]);
}

const NNSSndArcSeqArcInfo * func_0209bd30 (int seqArcNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->seqArcOffset);
    if (table == NULL) return NULL;

    if (seqArcNo < 0) return NULL;
    if (seqArcNo >= table->count) return NULL;

    return (const NNSSndArcSeqArcInfo *)GetPtrConst(arc->info, table->offset[ seqArcNo ]);
}

const NNSSndArcBankInfo * func_0209bccc (int bankNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->bankOffset);
    if (table == NULL) return NULL;

    if (bankNo < 0) return NULL;
    if (bankNo >= table->count) return NULL;

    return (const NNSSndArcBankInfo *)GetPtrConst(arc->info, table->offset[ bankNo ]);
}

const NNSSndArcWaveArcInfo * func_0209bc68 (int waveArcNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->waveArcOffset);
    if (table == NULL) return NULL;

    if (waveArcNo < 0) return NULL;
    if (waveArcNo >= table->count) return NULL;

    return (const NNSSndArcWaveArcInfo *)GetPtrConst(arc->info, table->offset[ waveArcNo ]);
}

const NNSSndArcStrmInfo * func_0209bc04 (int strmNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->strmOffset);
    if (table == NULL) return NULL;

    if (strmNo < 0) return NULL;
    if (strmNo >= table->count) return NULL;

    return (const NNSSndArcStrmInfo *)GetPtrConst(arc->info, table->offset[ strmNo ]);
}

const NNSSndArcPlayerInfo * func_0209bba0 (int playerNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->playerInfoOffset);
    if (table == NULL) return NULL;

    if (playerNo < 0) return NULL;
    if (playerNo >= table->count) return NULL;

    return (const NNSSndArcPlayerInfo *)GetPtrConst(arc->info, table->offset[ playerNo ]);
}

const NNSSndArcStrmPlayerInfo * func_0209bb3c (int playerNo)
{
    NNSSndArc * arc = data_020d5210;
    const NNSSndArcOffsetTable * table;

    table = GetOffsetTable(arc->info, arc->info->strmPlayerInfoOffset);
    if (table == NULL) return NULL;

    if (playerNo < 0) return NULL;
    if (playerNo >= table->count) return NULL;

    return (const NNSSndArcStrmPlayerInfo *)GetPtrConst(arc->info, table->offset[ playerNo ]);
}
