/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os_types.h"
#include "sdk/pxi.h"
#include "nnsys/snd.h"

BOOL FS_OpenFileFast(FSFile * p_file, FSFileID file_id);
s32 func_0209ba04(u32 fileId, void * buffer, s32 size, s32 offset);
FSFileID NNS_SndArcGetFileID(void);
u32 NNS_SndArcGetFileOffset(u32 fileId);
extern NNSSndStrmThread * sPrepareThread;
extern BOOL data_0204ad8c;
extern u8 * sDecodeBuffer;
void FS_CloseFile(FSFile * p_file);
s32 FS_ReadFile(FSFile * p_file, void * dst, s32 len);
BOOL FS_SeekFile(FSFile * p_file, s32 offset, FSSeekFileMode origin);
void FS_CancelFile(FSFile * p_file);
void MI_CpuCopy8(const void * src, void * dest, u32 size);
void * NNS_SndArcGetFileAddress(u32 fileId);
BOOL OpenFileStream (NNSSndStrmPlayer * player, u32 fileId);
void func_0209d550 (NNSSndStrmPlayer * player);
s32 ReadFileStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);
void func_0209d504 (NNSSndStrmPlayer * player);
BOOL OpenMemoryStream (NNSSndStrmPlayer * player, u32 fileId);

BOOL OpenFileStream (NNSSndStrmPlayer * player, u32 fileId)
{
    if (func_0209ba04(fileId, &player->info, sizeof(player->info), 0) != sizeof(player->info)) {
        return FALSE;
    }

    if (!FS_OpenFileFast(&player->file, NNS_SndArcGetFileID())) {
        return FALSE;
    }
    player->fileOffset = NNS_SndArcGetFileOffset(fileId);

    return TRUE;
}

void func_0209d550 (NNSSndStrmPlayer * player)
{
    FS_CloseFile(&player->file);
}

s32 ReadFileStream (NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset)
{
    BOOL result;

    result = FS_SeekFile(
        &player->file,
        (s32)(player->fileOffset + offset),
        FS_SEEK_SET
        );
    return FS_ReadFile(
        &player->file,
        dest,
        (s32)size
        );
}

void func_0209d504 (NNSSndStrmPlayer * player)
{
    FS_CancelFile(&player->file);
}

BOOL OpenMemoryStream (NNSSndStrmPlayer * player, u32 fileId)
{
    player->fileOffset = (u32)NNS_SndArcGetFileAddress(fileId);

    MI_CpuCopy8(
        (const void *)(player->fileOffset),
        &player->info,
        sizeof(player->info)
        );

    return TRUE;
}
