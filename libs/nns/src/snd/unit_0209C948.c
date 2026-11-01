/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "nnsys/snd.h"
#define func_0201b3d8 func_0209bdf8
#define RESERVED_AREASIZE 32
const NNSSndArcSeqInfo * func_0209bd94(int seqNo);
void * NNS_SndArcGetFileAddress(u32 fileId);
const NNSSndArcSeqArcInfo * func_0209bd30(int seqNo);
void func_0207e5d8(struct SNDBankData * bank, int index, struct SNDWaveArc * waveArc);
const NNSSndArcBankInfo * func_0209bccc(int bankNo);
const NNSSndArcWaveArcInfo * func_0209bc68(int waveArcNo);
extern BOOL func_0209c4c0(SNDWaveArc * waveArc, const SNDBankData * bank, int waveArcNo, u32 fileId, NNSSndHeapHandle heap);
extern SNDWaveArc * func_0209c814(u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
void DC_StoreRange(const void * startAddr, u32 nBytes);
void * func_0209c2d8(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
s32 func_0209ba04(u32 fileId, void * buffer, s32 size, s32 offset);
u32 func_0209ba88(u32 fileId);
NNSSndArc * func_0209bdf8(void);
void func_0209b9a0(u32 fileId, void * address);
extern void func_0209c774(void * mem, u32 size, u32 data1, u32 data2);
extern void func_0209c738(void * mem, u32 size, u32 data1, u32 data2);
extern void func_0209c6fc(void * mem, u32 size, u32 data1, u32 data2);
NNSSndArcLoadResult func_0209ce64 (int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData);
NNSSndArcLoadResult func_0209cdf4 (int seqArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqArc ** pData);
NNSSndArcLoadResult func_0209cc94 (int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData);
NNSSndArcLoadResult func_0209cbec (int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData);
void * func_0209cb38 (u32 fileId, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2, NNSSndHeapHandle heap);
SNDBankData * func_0209cabc (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
SNDBankData * func_0209ca40 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
SNDBankData * func_0209c9c4 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);
SNDBankData * func_0209c948 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr);

NNSSndArcLoadResult func_0209ce64 (int seqNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqData ** pData)
{
    const NNSSndArcSeqInfo * seqInfo;
    NNSSndSeqData * seqData = NULL;
    SNDBankData * bank = NULL;
    NNSSndArcLoadResult result;

    seqInfo = func_0209bd94(seqNo);
    if (seqInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO;

    result = func_0209cc94(seqInfo->param.bankNo, loadFlag, heap, bSetAddr, NULL);
    if (result != NNS_SND_ARC_LOAD_SUCESS) return result;

    if (loadFlag & NNS_SND_ARC_LOAD_SEQ) {
        seqData = (NNSSndSeqData *)func_0209cabc(seqInfo->fileId, heap, bSetAddr);
        if (seqData == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ;
        }
    } else {
        seqData = (NNSSndSeqData *)NNS_SndArcGetFileAddress(seqInfo->fileId);
    }

    if (pData != NULL) *pData = seqData;

    return NNS_SND_ARC_LOAD_SUCESS;
}

NNSSndArcLoadResult func_0209cdf4 (int seqArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct NNSSndSeqArc ** pData)
{
    const NNSSndArcSeqArcInfo * seqArcInfo;
    NNSSndSeqArc * seqArc = NULL;

    seqArcInfo = func_0209bd30(seqArcNo);
    if (seqArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_SEQARC_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_SEQARC) {
        seqArc = (NNSSndSeqArc *)func_0209ca40(seqArcInfo->fileId, heap, bSetAddr);
        if (seqArc == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQARC;
        }
    } else {
        seqArc = (NNSSndSeqArc *)NNS_SndArcGetFileAddress(seqArcInfo->fileId);
    }

    if (pData != NULL) *pData = seqArc;

    return NNS_SND_ARC_LOAD_SUCESS;
}

NNSSndArcLoadResult func_0209cc94 (int bankNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDBankData ** pData)
{
    const NNSSndArcBankInfo * bankInfo;
    const NNSSndArcWaveArcInfo * waveArcInfo;
    SNDBankData * bank = NULL;
    SNDWaveArc * waveArc;
    NNSSndArcLoadResult result;
    int i;

    bankInfo = func_0209bccc(bankNo);
    if (bankInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_BANK) {
        bank = func_0209c9c4(bankInfo->fileId, heap, bSetAddr);
        if (bank == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK;
        }
    } else {
        bank = (SNDBankData *)NNS_SndArcGetFileAddress(bankInfo->fileId);
    }

    for (i = 0; i < NNS_SND_ARC_BANK_TO_WAVEARC_NUM; i++) {
        if (bankInfo->waveArcNo[i] == NNS_SND_ARC_INVALID_WAVEARC_NO) continue;

        waveArcInfo = func_0209bc68(bankInfo->waveArcNo[i]);
        if (waveArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;

        result = func_0209cbec(bankInfo->waveArcNo[i], loadFlag, heap, bSetAddr, &waveArc);
        if (result != NNS_SND_ARC_LOAD_SUCESS) return result;

        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {

            if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
                if (!func_0209c4c0(waveArc, bank, i, waveArcInfo->fileId, heap)) {
                    return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
                }
            }
        }

        if (bank != NULL && waveArc != NULL) {
            func_0207e5d8(bank, i, waveArc);
        }
    }

    if (pData != NULL) *pData = bank;

    return NNS_SND_ARC_LOAD_SUCESS;
}

NNSSndArcLoadResult func_0209cbec (int waveArcNo, u32 loadFlag, NNSSndHeapHandle heap, BOOL bSetAddr, struct SNDWaveArc ** pData)
{
    const NNSSndArcWaveArcInfo * waveArcInfo;
    SNDWaveArc * waveArc = NULL;

    waveArcInfo = func_0209bc68(waveArcNo);
    if (waveArcInfo == NULL) return NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO;

    if (loadFlag & NNS_SND_ARC_LOAD_WAVE) {
        if (waveArcInfo->flags & NNS_SND_ARC_WAVEARC_SINGLE_LOAD) {

            waveArc = func_0209c814(waveArcInfo->fileId, heap, bSetAddr);
        } else {

            waveArc = (SNDWaveArc *)func_0209c948(waveArcInfo->fileId, heap, bSetAddr);
        }

        if (waveArc == NULL) {
            return NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE;
        }
    } else {
        waveArc = (SNDWaveArc *)NNS_SndArcGetFileAddress(waveArcInfo->fileId);
    }

    if (pData != NULL) *pData = waveArc;

    return NNS_SND_ARC_LOAD_SUCESS;
}

void * func_0209cb38 (u32 fileId, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2, NNSSndHeapHandle heap)
{
    void * buffer;
    u32 len;

    len = func_0209ba88(fileId);
    if (len == 0) return NULL;

    if (heap == NNS_SND_HEAP_INVALID_HANDLE) return NULL;

    buffer = func_0209c2d8(heap, len + RESERVED_AREASIZE, callback, data1, data2);
    if (buffer == NULL) return NULL;

    if (func_0209ba04(fileId, buffer, (s32)len, 0) != len) {
        return NULL;
    }

    DC_StoreRange(buffer, len);

    return buffer;
}

SNDBankData * func_0209cabc (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr)
{
    void * buffer;

    buffer = NNS_SndArcGetFileAddress(fileId);
    if (buffer == NULL) {
        buffer = func_0209cb38(
            fileId,
            func_0209c774,
            bSetAddr ? (u32)func_0209bdf8() : 0,
            fileId,
            heap
            );

        if (bSetAddr && buffer != NULL) {
            func_0209b9a0(fileId, buffer);
        }
    }

    return (SNDBankData *)buffer;
}

SNDBankData * func_0209ca40 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr)
{
    void * buffer;

    buffer = NNS_SndArcGetFileAddress(fileId);
    if (buffer == NULL) {
        buffer = func_0209cb38(
            fileId,
            func_0209c774,
            bSetAddr ? (u32)func_0209bdf8() : 0,
            fileId,
            heap
            );

        if (bSetAddr && buffer != NULL) {
            func_0209b9a0(fileId, buffer);
        }
    }

    return (SNDBankData *)buffer;
}

SNDBankData * func_0209c9c4 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr)
{
    void * buffer;

    buffer = NNS_SndArcGetFileAddress(fileId);
    if (buffer == NULL) {
        buffer = func_0209cb38(
            fileId,
            func_0209c738,
            bSetAddr ? (u32)func_0209bdf8() : 0,
            fileId,
            heap
            );

        if (bSetAddr && buffer != NULL) {
            func_0209b9a0(fileId, buffer);
        }
    }

    return (SNDBankData *)buffer;
}

SNDBankData * func_0209c948 (u32 fileId, NNSSndHeapHandle heap, BOOL bSetAddr)
{
    void * buffer;

    buffer = NNS_SndArcGetFileAddress(fileId);
    if (buffer == NULL) {
        buffer = func_0209cb38(
            fileId,
            func_0209c6fc,
            bSetAddr ? (u32)func_0209bdf8() : 0,
            fileId,
            heap
            );

        if (bSetAddr && buffer != NULL) {
            func_0209b9a0(fileId, buffer);
        }
    }

    return (SNDBankData *)buffer;
}
