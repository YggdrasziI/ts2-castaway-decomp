/* NitroSDK file system: commands, archives and files. Written from the ROM and from khdays (CC0)
 * per-function sources, retyped. File bounds are a hypothesis. Functions are emitted in reverse
 * source order. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/mi.h"
#include "sdk/os.h"
#include "sdk/fs.h"

typedef FSResult (*FSCommandFunc)(FSFile *);

FSResult FSi_ReadFileCommand(FSFile *p_file);
FSResult FSi_WriteFileCommand(FSFile *p_file);
FSResult FSi_SeekDirCommand(FSFile *p_file);
FSResult FSi_ReadDirCommand(FSFile *p_file);
FSResult FSi_FindPathCommand(FSFile *p_file);
FSResult FSi_GetPathCommand(FSFile *p_file);
FSResult FSi_OpenFileFastCommand(FSFile *p_file);
FSResult FSi_OpenFileDirectCommand(FSFile *p_file);
FSResult func_02076150(FSFile *p_file);

const FSCommandFunc data_020af1c4[9] = {
    FSi_ReadFileCommand,
    FSi_WriteFileCommand,
    FSi_SeekDirCommand,
    FSi_ReadDirCommand,
    FSi_FindPathCommand,
    FSi_GetPathCommand,
    FSi_OpenFileFastCommand,
    FSi_OpenFileDirectCommand,
    func_02076150,
};
extern const char data_020bcb68[];
extern const char data_020bcb6c[];
extern FSArchive *data_020c5670;
extern FSDirPos data_020c5674;
extern int data_020c5680;
extern u32 data_020c5684;
extern u32 data_020c5688;
extern u32 data_020c568c[2];
extern u32 data_020c5694[2];
extern FSArchive data_020c569c;

extern void func_0207a904(OSThreadQueue *queue); /* sleep */
extern void func_0207a884(OSThreadQueue *queue); /* wake up */
extern void func_02073f10(u16 lockId);
extern void func_02073ef0(u16 lockId);
extern void func_02074a30(void);
extern int func_02074ab4(u32 dma, u32 src, void *dst, u32 len, void *callback, void *arg, int async);
extern int func_0207552c(void);
extern u16 OS_GetLockID(void);

void FS_InitFile(FSFile *p_file);
void FS_InitArchive(FSArchive *p_arc);
BOOL FS_RegisterArchiveName(FSArchive *p_arc, const char *name, int name_len);
void FS_SetArchiveProc(FSArchive *p_arc, FS_ARCHIVE_PROC_FUNC proc, u32 flags);
BOOL FS_LoadArchive(FSArchive *p_arc, u32 base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size,
                    FS_ARCHIVE_READ_FUNC read_func, FS_ARCHIVE_WRITE_FUNC write_func);
FSResult FSi_ReadRomCallback(FSArchive *p_arc, void *dst, u32 src, u32 len);
FSResult FSi_RomArchiveProc(FSFile *p_file, FSCommandType cmd);
BOOL FS_WaitAsync(FSFile *p_file);
BOOL FSi_FindPath(FSFile *p_dir, const char *path, FSFileID *p_file_id, FSDirPos *p_dir_pos);
s32 FSi_ReadFileCore(FSFile *p_file, void *dst, s32 len, BOOL async);
FSFile *FSi_NextCommand(FSArchive *p_arc);
BOOL FSi_SendCommand(FSFile *p_file, FSCommandType command);
BOOL FSi_ExecuteSyncCommand(FSFile *p_file);
void FSi_ExecuteAsyncCommand(FSFile *p_file);
void FSi_ReleaseCommand(FSFile *p_file, FSResult ret);
FSResult FSi_TranslateCommand(FSFile *p_file, FSCommandType command);
FSArchive *FS_FindArchive(const char *name, int name_len);
void FS_NotifyArchiveAsyncEnd(FSArchive *p_arc, FSResult ret);
int FSi_ReadMemCallback(FSArchive *p_arc, void *dst, u32 pos, u32 size);
int FSi_WriteMemCallback(FSArchive *p_arc, const void *src, u32 pos, u32 size);
u32 FSi_GetPackedName(const char *name, int len);
void FSi_OnRomReadDone(void *p_arc);

static inline BOOL FS_IsBusy(volatile const FSFile *p_file)
{
    return p_file->stat & FS_FILE_STATUS_BUSY ? TRUE : FALSE;
}

static inline BOOL FS_IsCanceling(volatile const FSFile *p_file)
{
    return p_file->stat & FS_FILE_STATUS_CANCEL ? TRUE : FALSE;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile *p_file)
{
    return p_file->error == FS_RESULT_SUCCESS ? TRUE : FALSE;
}

static inline BOOL FS_IsDir(volatile const FSFile *p_file)
{
    return p_file->stat & FS_FILE_STATUS_IS_DIR ? TRUE : FALSE;
}

static inline BOOL FS_IsFileSyncMode(volatile const FSFile *p_file)
{
    return p_file->stat & FS_FILE_STATUS_SYNC ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveLoaded(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_LOADED ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveSuspended(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_SUSPEND ? TRUE : FALSE;
}

static inline BOOL FSi_IsArchiveRunning(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_RUNNING ? TRUE : FALSE;
}

static inline BOOL FSi_IsArchiveBusy(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_RUNNING;
}

static inline BOOL FSi_IsArchiveCanceling(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_CANCELING;
}

static inline BOOL FSi_IsArchiveSuspending(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_SUSPENDING;
}

static inline BOOL FSi_IsArchiveAsync(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_IS_ASYNC;
}

static inline BOOL FSi_IsArchiveSync(volatile const FSArchive *p_arc)
{
    return p_arc->flag & FS_ARCHIVE_FLAG_IS_SYNC;
}

static inline BOOL FSi_IsSlash(u32 c)
{
    return c == '/' || c == '\\';
}

static inline void FSi_CutFromListCore(FSFileLink *trg)
{
    FSFile *const pr = trg->prev;
    FSFile *const nx = trg->next;

    if (pr) {
        pr->link.next = nx;
    }
    if (nx) {
        nx->link.prev = pr;
    }
}

static inline void FSi_CutFromList(FSFile *elem)
{
    FSFileLink *const trg = &elem->link;

    FSi_CutFromListCore(trg);
    trg->prev = NULL;
    trg->next = trg->prev;
}

static inline void FSi_AppendToList(FSFile *elem, FSFile *list)
{
    FSi_CutFromListCore(&elem->link);
    while (list->link.next != NULL) {
        list = list->link.next;
    }
    list->link.next = elem;
    elem->link.prev = list;
    elem->link.next = NULL;
}

void FSi_OnRomReadDone(void *p_arc)
{
    FS_NotifyArchiveAsyncEnd(p_arc, func_0207552c() ? FS_RESULT_ERROR : FS_RESULT_SUCCESS);
}

FSResult FSi_ReadRomCallback(FSArchive *p_arc, void *dst, u32 src, u32 len)
{
    func_02074ab4(data_020c5688, src, dst, len, FSi_OnRomReadDone, p_arc, TRUE);
    return FS_RESULT_PROC_ASYNC;
}

FSResult func_02077a68(FSArchive *p_arc, const void *src, u32 dst, u32 len)
{
    return FS_RESULT_FAILURE;
}

FSResult FSi_RomArchiveProc(FSFile *p_file, FSCommandType cmd)
{
    switch (cmd) {
    case FS_COMMAND_ACTIVATE:
        func_02073f10((u16)data_020c5684);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_IDLE:
        func_02073ef0((u16)data_020c5684);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_WRITEFILE:
        return FS_RESULT_UNSUPPORTED;
    default:
        return FS_RESULT_PROC_UNKNOWN;
    }
}

FSResult func_020779d0(FSArchive *p_arc, void *dst, u32 src, u32 len)
{
    return FS_RESULT_FAILURE;
}

FSResult func_020779c8(FSFile *p_file, FSCommandType cmd)
{
    return FS_RESULT_UNSUPPORTED;
}

static inline const u32 *FSi_GetRomRegion(u32 addr)
{
    return (const u32 *)addr;
}

void func_02077828(u32 dma)
{
    data_020c5688 = dma;
    data_020c5684 = OS_GetLockID();
    data_020c568c[0] = 0;
    data_020c568c[1] = 0;
    data_020c5694[0] = 0;
    data_020c5694[1] = 0;
    func_02074a30();
    FS_InitArchive(&data_020c569c);
    FS_RegisterArchiveName(&data_020c569c, data_020bcb6c, 3);
    if (*(vu16 *)0x027FFC40 == 2) {
        data_020c568c[0] = (u32)-1;
        data_020c568c[1] = 0;
        data_020c5694[0] = (u32)-1;
        data_020c5694[1] = 0;
        FS_SetArchiveProc(&data_020c569c, func_020779c8, FS_ARCHIVE_PROC_ALL);
        FS_LoadArchive(&data_020c569c, 0, 0, 0, 0, 0, func_020779d0, func_02077a68);
    } else {
        const u32 *const fnt = FSi_GetRomRegion(0x027FFE40);
        const u32 *const fat = FSi_GetRomRegion(0x027FFE48);

        FS_SetArchiveProc(&data_020c569c, FSi_RomArchiveProc, 0x602);
        if (fnt[0] != (u32)-1 && fnt[0] != 0 && fat[0] != (u32)-1 && fat[0] != 0) {
            FS_LoadArchive(&data_020c569c, 0, fat[0], fat[1], fnt[0], fnt[1], FSi_ReadRomCallback, func_02077a68);
        }
    }
}

void FS_Init(u32 dma)
{
    if (data_020c5680 == 0) {
        data_020c5680 = 1;
        func_02077828(dma);
    }
}

void FS_InitFile(FSFile *p_file)
{
    p_file->link.prev = NULL;
    p_file->link.next = p_file->link.prev;
    p_file->queue[0].tail = NULL;
    p_file->queue[0].head = p_file->queue[0].tail;
    p_file->arc = NULL;
    p_file->command = FS_COMMAND_INVALID;
    p_file->stat = 0;
}

BOOL FSi_FindPath(FSFile *p_dir, const char *path, FSFileID *p_file_id, FSDirPos *p_dir_pos)
{
    FSDirPos pos;

    if (FSi_IsSlash(*(const u8 *)path)) {
        pos.arc = data_020c5674.arc;
        pos.own_id = 0;
        pos.pos = 0;
        pos.index = 0;
        ++path;
    } else {
        int i;

        pos = data_020c5674;
        for (i = 0; i <= 3; ++i) {
            u32 c = *(const u8 *)(path + i);

            if (!c || FSi_IsSlash(c)) {
                break;
            } else if (c == ':') {
                FSArchive *const p_arc = FS_FindArchive(path, i);

                if (!p_arc) {
                    return FALSE;
                } else if (!FS_IsArchiveLoaded(p_arc)) {
                    return FALSE;
                }
                pos.arc = p_arc;
                pos.pos = 0;
                pos.index = 0;
                pos.own_id = 0;
                path += i + 1;
                if (FSi_IsSlash(*(const u8 *)path)) {
                    ++path;
                }
                break;
            }
        }
    }
    p_dir->arc = pos.arc;
    p_dir->arg.findpath.path = path;
    p_dir->arg.findpath.pos = pos;
    if (p_dir_pos) {
        p_dir->arg.findpath.find_directory = TRUE;
        p_dir->arg.findpath.result.dir = p_dir_pos;
    } else {
        p_dir->arg.findpath.find_directory = FALSE;
        p_dir->arg.findpath.result.file = p_file_id;
    }
    return FSi_SendCommand(p_dir, FS_COMMAND_FINDPATH);
}

s32 FSi_ReadFileCore(FSFile *p_file, void *dst, s32 len, BOOL async)
{
    {
        const s32 pos = (s32)p_file->prop.file.pos;
        const s32 rest = (s32)p_file->prop.file.bottom - pos;
        const u32 org = (u32)len;

        if (len > rest) {
            len = rest;
        }
        if (len < 0) {
            len = 0;
        }
        p_file->arg.readfile.dst = dst;
        p_file->arg.readfile.len_org = org;
        p_file->arg.readfile.len = (u32)len;
        if (!async) {
            p_file->stat |= FS_FILE_STATUS_SYNC;
        }
        (void)FSi_SendCommand(p_file, FS_COMMAND_READFILE);
        if (!async) {
            if (FS_WaitAsync(p_file)) {
                len = (s32)p_file->prop.file.pos - pos;
            } else {
                len = -1;
            }
        }
    }
    return len;
}

BOOL FS_ConvertPathToFileID(FSFileID *p_file_id, const char *path)
{
    FSFile file;

    FS_InitFile(&file);
    return FSi_FindPath(&file, path, p_file_id, NULL) != 0;
}

BOOL FS_OpenFileFast(FSFile *p_file, FSFileID file_id)
{
    if (!file_id.arc) {
        return FALSE;
    }
    p_file->arc = file_id.arc;
    p_file->arg.openfilefast.id = file_id;
    if (!FSi_SendCommand(p_file, FS_COMMAND_OPENFILEFAST)) {
        return FALSE;
    }
    p_file->stat |= FS_FILE_STATUS_IS_FILE;
    p_file->stat &= ~FS_FILE_STATUS_IS_DIR;
    return TRUE;
}

BOOL FS_CloseFile(FSFile *p_file)
{
    if (!FSi_SendCommand(p_file, FS_COMMAND_CLOSEFILE)) {
        return FALSE;
    }
    p_file->arc = NULL;
    p_file->command = FS_COMMAND_INVALID;
    p_file->stat &= ~(FS_FILE_STATUS_IS_FILE | FS_FILE_STATUS_IS_DIR);
    return TRUE;
}

BOOL FS_WaitAsync(FSFile *p_file)
{
    BOOL is_owner = FALSE;
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if (FS_IsBusy(p_file)) {
        is_owner = !(p_file->stat & (FS_FILE_STATUS_SYNC | FS_FILE_STATUS_OPERATING));
        if (is_owner) {
            p_file->stat |= FS_FILE_STATUS_SYNC;
            do {
                func_0207a904(p_file->queue);
            } while (!(p_file->stat & FS_FILE_STATUS_OPERATING));
        } else {
            do {
                func_0207a904(p_file->queue);
            } while (FS_IsBusy(p_file));
        }
    }
    (void)OS_RestoreInterrupts(bak_psr);
    if (is_owner) {
        return FSi_ExecuteSyncCommand(p_file);
    }
    return FS_IsSucceeded(p_file);
}

void FS_CancelFile(FSFile *p_file)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if (FS_IsBusy(p_file)) {
        p_file->stat |= FS_FILE_STATUS_CANCEL;
        p_file->arc->flag |= FS_ARCHIVE_FLAG_CANCELING;
    }
    (void)OS_RestoreInterrupts(bak_psr);
}

s32 FS_ReadFile(FSFile *p_file, void *dst, s32 len)
{
    return FSi_ReadFileCore(p_file, dst, len, FALSE);
}

BOOL FS_SeekFile(FSFile *p_file, s32 offset, FSSeekFileMode origin)
{
    switch (origin) {
    case FS_SEEK_SET:
        offset += p_file->prop.file.top;
        break;
    case FS_SEEK_CUR:
        offset += p_file->prop.file.pos;
        break;
    case FS_SEEK_END:
        offset += p_file->prop.file.bottom;
        break;
    default:
        return FALSE;
    }
    if (offset < (s32)p_file->prop.file.top) {
        offset = (s32)p_file->prop.file.top;
    }
    if (offset > (s32)p_file->prop.file.bottom) {
        offset = (s32)p_file->prop.file.bottom;
    }
    p_file->prop.file.pos = (u32)offset;
    return TRUE;
}

u32 FSi_GetPackedName(const char *name, int len)
{
    u32 packed = 0;

    if (len <= 3) {
        int i = 0;

        if (len > 0) {
            int shift = 0;

            do {
                u32 c = (u8)name[i];

                if (c == 0) {
                    break;
                }
                {
                    int d = (int)c - 0x41;

                    if ((u32)d <= 0x19) {
                        c = (u32)(d + 0x61);
                    } else {
                        c = (u32)(d + 0x41);
                    }
                }
                i++;
                packed |= c << shift;
                shift += 8;
            } while (i < len);
        }
    }
    return packed;
}

int FSi_ReadMemCallback(FSArchive *p_arc, void *dst, u32 pos, u32 size)
{
    MI_CpuCopy8((const void *)(p_arc->base + pos), dst, size);
    return 0;
}

int FSi_WriteMemCallback(FSArchive *p_arc, const void *src, u32 pos, u32 size)
{
    MI_CpuCopy8(src, (void *)(p_arc->base + pos), size);
    return 0;
}

FSFile *FSi_NextCommand(FSArchive *p_arc)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if (FSi_IsArchiveCanceling(p_arc)) {
        FSFile *p, *q;

        p_arc->flag &= ~FS_ARCHIVE_FLAG_CANCELING;
        for (p = p_arc->list.next; p; p = q) {
            q = p->link.next;
            if (FS_IsCanceling(p)) {
                if (p_arc->list.next == p) {
                    p_arc->list.next = q;
                }
                FSi_ReleaseCommand(p, FS_RESULT_CANCELED);
                if (!q) {
                    q = p_arc->list.next;
                }
            }
        }
    }
    if (!FSi_IsArchiveSuspending(p_arc) && !FS_IsArchiveSuspended(p_arc)) {
        FSFile *p_file = p_arc->list.next;

        if (p_file) {
            const BOOL is_start = !FSi_IsArchiveRunning(p_arc);

            if (is_start) {
                p_arc->flag |= FS_ARCHIVE_FLAG_RUNNING;
            }
            (void)OS_RestoreInterrupts(bak_psr);
            if (is_start) {
                if ((p_arc->proc_flag & FS_ARCHIVE_PROC_ACTIVATE) != 0) {
                    (void)(*p_arc->proc)(p_file, FS_COMMAND_ACTIVATE);
                }
            }
            bak_psr = OS_DisableInterrupts();
            p_file->stat |= FS_FILE_STATUS_OPERATING;
            if (FS_IsFileSyncMode(p_file)) {
                func_0207a884(p_file->queue);
                (void)OS_RestoreInterrupts(bak_psr);
                return NULL;
            } else {
                (void)OS_RestoreInterrupts(bak_psr);
                return p_file;
            }
        }
    }
    if (FSi_IsArchiveBusy(p_arc)) {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_RUNNING;
        if ((p_arc->proc_flag & FS_ARCHIVE_PROC_IDLE) != 0) {
            FSFile tmp;

            FS_InitFile(&tmp);
            tmp.arc = p_arc;
            (void)(*p_arc->proc)(&tmp, FS_COMMAND_IDLE);
        }
    }
    if (FSi_IsArchiveSuspending(p_arc)) {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_SUSPENDING;
        p_arc->flag |= FS_ARCHIVE_FLAG_SUSPEND;
        func_0207a884(&p_arc->stat_q);
    }
    (void)OS_RestoreInterrupts(bak_psr);
    return NULL;
}

void FSi_ExecuteAsyncCommand(FSFile *p_file)
{
    FSArchive *const p_arc = p_file->arc;

    while (p_file) {
        OSIntrMode bak_psr = OS_DisableInterrupts();

        p_file->stat |= FS_FILE_STATUS_OPERATING;
        if (FS_IsFileSyncMode(p_file)) {
            func_0207a884(p_file->queue);
            (void)OS_RestoreInterrupts(bak_psr);
            break;
        }
        p_file->stat |= FS_FILE_STATUS_ASYNC;
        (void)OS_RestoreInterrupts(bak_psr);
        if (FSi_TranslateCommand(p_file, p_file->command) == FS_RESULT_PROC_ASYNC) {
            break;
        }
        p_file = FSi_NextCommand(p_arc);
    }
}

BOOL FSi_ExecuteSyncCommand(FSFile *p_file)
{
    FSFile *p_target;
    FSResult ret = FSi_TranslateCommand(p_file, p_file->command);

    FSi_ReleaseCommand(p_file, ret);
    p_target = FSi_NextCommand(p_file->arc);
    if (p_target) {
        FSi_ExecuteAsyncCommand(p_target);
    }
    return FS_IsSucceeded(p_file);
}

BOOL FSi_SendCommand(FSFile *p_file, FSCommandType command)
{
    FSArchive *const p_arc = p_file->arc;
    const int bit = (1 << command);

    p_file->command = command;
    p_file->error = FS_RESULT_BUSY;
    p_file->stat |= FS_FILE_STATUS_BUSY;
    {
        OSIntrMode bak_psr = OS_DisableInterrupts();

        if (p_arc->flag & FS_ARCHIVE_FLAG_UNLOADING) {
            FSi_ReleaseCommand(p_file, FS_RESULT_CANCELED);
            (void)OS_RestoreInterrupts(bak_psr);
            return FALSE;
        }
        if ((bit & FS_ARCHIVE_PROC_SYNC) != 0) {
            p_file->stat |= FS_FILE_STATUS_SYNC;
        }
        FSi_AppendToList(p_file, (FSFile *)&p_arc->list);
        if (!FS_IsArchiveSuspended(p_arc) && !FSi_IsArchiveBusy(p_arc)) {
            p_arc->flag |= FS_ARCHIVE_FLAG_RUNNING;
            (void)OS_RestoreInterrupts(bak_psr);
            if ((p_arc->proc_flag & FS_ARCHIVE_PROC_ACTIVATE) != 0) {
                (void)(*p_arc->proc)(p_file, FS_COMMAND_ACTIVATE);
            }
            bak_psr = OS_DisableInterrupts();
            p_file->stat |= FS_FILE_STATUS_OPERATING;
            if (!FS_IsFileSyncMode(p_file)) {
                (void)OS_RestoreInterrupts(bak_psr);
                FSi_ExecuteAsyncCommand(p_file);
                return TRUE;
            }
            (void)OS_RestoreInterrupts(bak_psr);
        } else if (!FS_IsFileSyncMode(p_file)) {
            (void)OS_RestoreInterrupts(bak_psr);
            return TRUE;
        } else {
            do {
                func_0207a904(p_file->queue);
            } while (!(p_file->stat & FS_FILE_STATUS_OPERATING));
            (void)OS_RestoreInterrupts(bak_psr);
        }
    }
    return FSi_ExecuteSyncCommand(p_file);
}

void FS_InitArchive(FSArchive *p_arc)
{
    MI_CpuFill8(p_arc, 0, sizeof(FSArchive));
    p_arc->sync_q.tail = NULL;
    p_arc->sync_q.head = p_arc->sync_q.tail;
    p_arc->stat_q.tail = NULL;
    p_arc->stat_q.head = p_arc->stat_q.tail;
}

FSArchive *FS_FindArchive(const char *name, int name_len)
{
    const u32 pack = FSi_GetPackedName(name, name_len);
    OSIntrMode bak_psr = OS_DisableInterrupts();
    FSArchive *p_arc = data_020c5670;

    while (p_arc && p_arc->name.pack != pack) {
        p_arc = p_arc->next;
    }
    (void)OS_RestoreInterrupts(bak_psr);
    return p_arc;
}

BOOL FS_RegisterArchiveName(FSArchive *p_arc, const char *name, int name_len)
{
    BOOL ret = FALSE;
    OSIntrMode bak_psr = OS_DisableInterrupts();

    if (!FS_FindArchive(name, name_len)) {
        FSArchive *p_tail = data_020c5670;

        if (!p_tail) {
            data_020c5670 = p_arc;
            data_020c5674.arc = p_arc;
            data_020c5674.pos = 0;
            data_020c5674.index = 0;
            data_020c5674.own_id = 0;
        } else {
            while (p_tail->next) {
                p_tail = p_tail->next;
            }
            p_tail->next = p_arc;
            p_arc->prev = p_tail;
        }
        p_arc->name.pack = FSi_GetPackedName(name, name_len);
        p_arc->flag |= FS_ARCHIVE_FLAG_REGISTER;
        ret = TRUE;
    }
    (void)OS_RestoreInterrupts(bak_psr);
    return ret;
}

BOOL FS_LoadArchive(FSArchive *p_arc, u32 base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size,
                    FS_ARCHIVE_READ_FUNC read_func, FS_ARCHIVE_WRITE_FUNC write_func)
{
    p_arc->base = base;
    p_arc->fat_size = fat_size;
    p_arc->fat = p_arc->fat_bak = fat;
    p_arc->fnt_size = fnt_size;
    p_arc->fnt = p_arc->fnt_bak = fnt;
    p_arc->read_func = read_func ? read_func : (FS_ARCHIVE_READ_FUNC)FSi_ReadMemCallback;
    p_arc->write_func = write_func ? write_func : (FS_ARCHIVE_WRITE_FUNC)FSi_WriteMemCallback;
    p_arc->table_func = p_arc->read_func;
    p_arc->load_mem = NULL;
    p_arc->flag |= FS_ARCHIVE_FLAG_LOADED;
    return TRUE;
}

void FS_SetArchiveProc(FSArchive *p_arc, FS_ARCHIVE_PROC_FUNC proc, u32 flags)
{
    if (flags == 0) {
        proc = NULL;
    } else if (proc == NULL) {
        flags = 0;
    }
    p_arc->proc = proc;
    p_arc->proc_flag = flags;
}

void FS_NotifyArchiveAsyncEnd(FSArchive *p_arc, FSResult ret)
{
    if (FSi_IsArchiveAsync(p_arc)) {
        FSFile *p_file = p_arc->list.next;

        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_ASYNC;
        FSi_ReleaseCommand(p_file, ret);
        p_file = FSi_NextCommand(p_arc);
        if (p_file) {
            FSi_ExecuteAsyncCommand(p_file);
        }
    } else {
        FSFile *p_file = p_arc->list.next;
        OSIntrMode bak_psr = OS_DisableInterrupts();

        p_file->error = ret;
        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_SYNC;
        func_0207a884(&p_arc->sync_q);
        (void)OS_RestoreInterrupts(bak_psr);
    }
}

int FSi_StrNICmp(const char *str1, const char *str2, u32 len)
{
    u32 i = 0;

    while (i < len) {
        u32 c1 = (u32)(u8)str1[i] - 0x41;
        u32 c2 = (u32)(u8)str2[i] - 0x41;

        if (c1 <= 0x19) {
            c1 += 0x20;
        }
        if (c2 <= 0x19) {
            c2 += 0x20;
        }
        if (c1 != c2) {
            return (int)(c1 - c2);
        }
        i++;
    }
    return 0;
}

FSResult FSi_ReadTable(FSiSyncReadParam *p, void *dst, u32 len)
{
    FSResult ret;
    FSArchive *const p_arc = p->arc;

    p_arc->flag |= FS_ARCHIVE_FLAG_IS_SYNC;
    switch (ret = (*p_arc->table_func)(p_arc, dst, p->pos, len)) {
    case FS_RESULT_SUCCESS:
    case FS_RESULT_FAILURE:
        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_SYNC;
        break;
    case FS_RESULT_PROC_ASYNC: {
        OSIntrMode bak_psr = OS_DisableInterrupts();

        while (FSi_IsArchiveSync(p_arc)) {
            func_0207a904(&p_arc->sync_q);
        }
        (void)OS_RestoreInterrupts(bak_psr);
        ret = p_arc->list.next->error;
        break;
    }
    }
    p->pos += len;
    return ret;
}

FSResult FSi_SeekDirDirect(FSFile *p_dir, u32 id)
{
    p_dir->stat |= FS_FILE_STATUS_SYNC;
    p_dir->arg.seekdir.pos.arc = p_dir->arc;
    p_dir->arg.seekdir.pos.pos = 0;
    p_dir->arg.seekdir.pos.index = 0;
    p_dir->arg.seekdir.pos.own_id = (u16)id;
    return FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
}

FSResult FSi_ReadFileCommand(FSFile *p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.readfile.len;
    void *const dst = p_file->arg.readfile.dst;

    p_file->prop.file.pos = pos + len;
    return (*p_arc->read_func)(p_arc, dst, pos, len);
}

FSResult FSi_WriteFileCommand(FSFile *p_file)
{
    FSArchive *const p_arc = p_file->arc;
    const u32 pos = p_file->prop.file.pos;
    const u32 len = p_file->arg.writefile.len;
    const void *const src = p_file->arg.writefile.src;

    p_file->prop.file.pos = pos + len;
    return (*p_arc->write_func)(p_arc, src, pos, len);
}

FSResult FSi_SeekDirCommand(FSFile *p_dir)
{
    FSResult result;
    FSArchive *const p_arc = p_dir->arc;
    const FSDirPos *const arg = &p_dir->arg.seekdir.pos;
    FSArchiveFNT fnt_entry;
    FSiSyncReadParam param;

    param.arc = p_arc;
    param.pos = p_arc->fnt + arg->own_id * sizeof(fnt_entry);
    result = FSi_ReadTable(&param, &fnt_entry, sizeof(fnt_entry));
    if (result == FS_RESULT_SUCCESS) {
        p_dir->prop.dir.pos = *arg;
        if ((arg->index == 0) && (arg->pos == 0)) {
            p_dir->prop.dir.pos.index = fnt_entry.index;
            p_dir->prop.dir.pos.pos = p_arc->fnt + fnt_entry.start;
        }
        p_dir->prop.dir.parent = (u32)(fnt_entry.parent & 0xfff);
    }
    return result;
}

FSResult FSi_ReadDirCommand(FSFile *p_dir)
{
    FSResult result;
    FSDirEntry *p_entry = p_dir->arg.readdir.p_entry;
    u8 len;
    FSiSyncReadParam param;

    param.arc = p_dir->arc;
    param.pos = p_dir->prop.dir.pos.pos;
    result = FSi_ReadTable(&param, &len, sizeof(len));
    if (result != FS_RESULT_SUCCESS) {
        return result;
    }
    p_entry->name_len = (u32)(len & 0x7f);
    p_entry->is_directory = (u32)((len >> 7) & 1);
    if (p_entry->name_len == 0) {
        return FS_RESULT_FAILURE;
    }
    if (!p_dir->arg.readdir.skip_string) {
        result = FSi_ReadTable(&param, p_entry->name, p_entry->name_len);
        if (result != FS_RESULT_SUCCESS) {
            return result;
        }
        p_entry->name[p_entry->name_len] = '\0';
    } else {
        param.pos += p_entry->name_len;
    }
    if (p_entry->is_directory) {
        u16 id;

        result = FSi_ReadTable(&param, &id, sizeof(id));
        if (result != FS_RESULT_SUCCESS) {
            return result;
        }
        p_entry->dir_id.arc = p_dir->arc;
        p_entry->dir_id.own_id = (u16)(id & 0xfff);
        p_entry->dir_id.index = 0;
        p_entry->dir_id.pos = 0;
    } else {
        p_entry->file_id.arc = p_dir->arc;
        p_entry->file_id.file_id = p_dir->prop.dir.pos.index;
        ++p_dir->prop.dir.pos.index;
    }
    p_dir->prop.dir.pos.pos = param.pos;
    return result;
}

FSResult FSi_FindPathCommand(FSFile *p_dir)
{
    const char *path = p_dir->arg.findpath.path;
    const BOOL is_dir = p_dir->arg.findpath.find_directory;

    p_dir->arg.seekdir.pos = p_dir->arg.findpath.pos;
    (void)FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
    for (; *(const u8 *)path; path += *(const u8 *)path ? 1 : 0) {
        u32 is_directory;
        int name_len = 0;

        while ((is_directory = *(const u8 *)(path + name_len)), (is_directory && !FSi_IsSlash(is_directory))) {
            ++name_len;
        }
        if (is_directory || is_dir) {
            is_directory = 1;
        }
        if (name_len == 0) {
            return FS_RESULT_FAILURE;
        } else if (*(const u8 *)path == '.') {
            if (name_len == 1) {
                path += 1;
                continue;
            } else if ((name_len == 2) & (*(const u8 *)(path + 1) == '.')) {
                if (p_dir->prop.dir.pos.own_id != 0) {
                    FSi_SeekDirDirect(p_dir, p_dir->prop.dir.parent);
                }
                path += 2;
                continue;
            }
        }
        if (name_len > FS_FILE_NAME_MAX) {
            return FS_RESULT_FAILURE;
        } else {
            FSDirEntry etr;

            p_dir->arg.readdir.p_entry = &etr;
            p_dir->arg.readdir.skip_string = FALSE;
            for (;;) {
                if (FSi_TranslateCommand(p_dir, FS_COMMAND_READDIR) != FS_RESULT_SUCCESS) {
                    return FS_RESULT_FAILURE;
                }
                if ((is_directory != etr.is_directory) || (name_len != etr.name_len)
                    || FSi_StrNICmp(path, etr.name, (u32)name_len)) {
                    continue;
                }
                if (is_directory) {
                    path += name_len;
                    p_dir->arg.seekdir.pos = etr.dir_id;
                    (void)FSi_TranslateCommand(p_dir, FS_COMMAND_SEEKDIR);
                    break;
                } else if (is_dir) {
                    return FS_RESULT_FAILURE;
                } else {
                    *p_dir->arg.findpath.result.file = etr.file_id;
                    return FS_RESULT_SUCCESS;
                }
            }
        }
    }
    if (!is_dir) {
        return FS_RESULT_FAILURE;
    }
    *p_dir->arg.findpath.result.dir = p_dir->prop.dir.pos;
    return FS_RESULT_SUCCESS;
}

FSResult FSi_GetPathCommand(FSFile *p_file)
{
    FSArchive *const p_arc = p_file->arc;
    FSGetPathInfo *p_info = &p_file->arg.getpath;
    FSDirEntry entry;
    FSFile tmp;
    u32 dir_id;
    u32 file_id;
    u32 id;
    u32 len;

    enum {
        INVALID_ID = 0x10000
    };

    FS_InitFile(&tmp);
    tmp.arc = p_file->arc;
    if (FS_IsDir(p_file)) {
        dir_id = p_file->prop.dir.pos.own_id;
        file_id = INVALID_ID;
    } else {
        file_id = p_file->prop.file.own_id;
        if (p_info->total_len != 0) {
            dir_id = p_info->dir_id;
        } else {
            u32 pos = 0;
            u32 num_dir = 0;

            dir_id = INVALID_ID;
            do {
                FSi_SeekDirDirect(&tmp, pos);
                if (!pos) {
                    num_dir = tmp.prop.dir.parent;
                }
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = TRUE;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
                    if (!entry.is_directory && (entry.file_id.file_id == file_id)) {
                        dir_id = tmp.prop.dir.pos.own_id;
                        break;
                    }
                }
            } while ((dir_id == INVALID_ID) && (++pos < num_dir));
        }
    }
    if (dir_id == INVALID_ID) {
        p_info->total_len = 0;
        return FS_RESULT_FAILURE;
    }
    if (p_info->total_len == 0) {
        len = 0;
        if (p_arc->name.pack <= 0x000000FF) {
            len += 1;
        } else if (p_arc->name.pack <= 0x0000FF00) {
            len += 2;
        } else {
            len += 3;
        }
        len += 1 + 1;
        if (file_id != INVALID_ID) {
            len += entry.name_len;
        }
        id = dir_id;
        if (id != 0) {
            FSi_SeekDirDirect(&tmp, id);
            do {
                FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = TRUE;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
                    if (entry.is_directory && (entry.dir_id.own_id == id)) {
                        len += entry.name_len + 1;
                        break;
                    }
                }
                id = tmp.prop.dir.pos.own_id;
            } while (id != 0);
        }
        p_info->total_len = (u16)(len + 1);
        p_info->dir_id = (u16)dir_id;
    }
    if (!p_info->buf) {
        return FS_RESULT_SUCCESS;
    }
    if (p_info->buf_len < p_info->total_len) {
        return FS_RESULT_FAILURE;
    } else {
        u8 *dst = p_info->buf;
        u32 total = p_info->total_len;
        u32 pos = 0;

        if (p_arc->name.pack <= 0x000000FF) {
            len = 1;
        } else if (p_arc->name.pack <= 0x0000FF00) {
            len = 2;
        } else {
            len = 3;
        }
        MI_CpuCopy8(p_arc->name.ptr, dst + pos, len);
        pos += len;
        MI_CpuCopy8(data_020bcb68, dst + pos, 2);
        pos += 2;
        id = dir_id;
        FSi_SeekDirDirect(&tmp, id);
        if (file_id != INVALID_ID) {
            tmp.arg.readdir.p_entry = &entry;
            tmp.arg.readdir.skip_string = FALSE;
            while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
                if (!entry.is_directory && (entry.file_id.file_id == file_id)) {
                    break;
                }
            }
            len = entry.name_len + 1;
            MI_CpuCopy8(entry.name, dst + total - len, len);
            total -= len;
        } else {
            *(dst + total - 1) = '\0';
            total -= 1;
        }
        if (id != 0) {
            do {
                FSi_SeekDirDirect(&tmp, tmp.prop.dir.parent);
                tmp.arg.readdir.p_entry = &entry;
                tmp.arg.readdir.skip_string = FALSE;
                *(dst + total - 1) = '/';
                total -= 1;
                while (FSi_TranslateCommand(&tmp, FS_COMMAND_READDIR) == FS_RESULT_SUCCESS) {
                    if (entry.is_directory && (entry.dir_id.own_id == id)) {
                        len = entry.name_len;
                        MI_CpuCopy8(entry.name, dst + total - len, len);
                        total -= len;
                        break;
                    }
                }
                id = tmp.prop.dir.pos.own_id;
            } while (id != 0);
        }
    }
    return FS_RESULT_SUCCESS;
}

FSResult FSi_OpenFileFastCommand(FSFile *p_file)
{
    FSResult result;
    FSArchive *const p_arc = p_file->arc;
    const FSFileID *p_id = &p_file->arg.openfilefast.id;
    const u32 index = p_id->file_id;

    {
        u32 pos = (u32)(index * sizeof(FSArchiveFAT));

        if (pos >= p_arc->fat_size) {
            result = FS_RESULT_FAILURE;
        } else {
            FSArchiveFAT fat;
            FSiSyncReadParam param;

            param.arc = p_arc;
            param.pos = p_arc->fat + pos;
            result = FSi_ReadTable(&param, &fat, sizeof(fat));
            if (result == FS_RESULT_SUCCESS) {
                p_file->arg.openfiledirect.top = fat.top;
                p_file->arg.openfiledirect.bottom = fat.bottom;
                p_file->arg.openfiledirect.index = index;
                result = FSi_TranslateCommand(p_file, FS_COMMAND_OPENFILEDIRECT);
            }
        }
    }
    return result;
}

FSResult FSi_OpenFileDirectCommand(FSFile *p_file)
{
    p_file->prop.file.top = p_file->arg.openfiledirect.top;
    p_file->prop.file.pos = p_file->arg.openfiledirect.top;
    p_file->prop.file.bottom = p_file->arg.openfiledirect.bottom;
    p_file->prop.file.own_id = p_file->arg.openfiledirect.index;
    return FS_RESULT_SUCCESS;
}

FSResult func_02076150(FSFile *p_file)
{
    return FS_RESULT_SUCCESS;
}

void FSi_ReleaseCommand(FSFile *p_file, FSResult ret)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    FSi_CutFromList(p_file);
    p_file->stat &= ~(FS_FILE_STATUS_CANCEL | FS_FILE_STATUS_BUSY | FS_FILE_STATUS_SYNC | FS_FILE_STATUS_ASYNC
                      | FS_FILE_STATUS_OPERATING);
    p_file->error = ret;
    func_0207a884(p_file->queue);
    (void)OS_RestoreInterrupts(bak_psr);
}

FSResult FSi_TranslateCommand(FSFile *p_file, FSCommandType command)
{
    FSResult ret;
    FSArchive *const p_arc = p_file->arc;
    const int bit = (1 << command);

    if (FS_IsFileSyncMode(p_file)) {
        p_arc->flag |= FS_ARCHIVE_FLAG_IS_SYNC;
    } else {
        p_arc->flag |= FS_ARCHIVE_FLAG_IS_ASYNC;
    }
    if ((p_arc->proc_flag & bit) != 0) {
        switch (ret = (*p_arc->proc)(p_file, command)) {
        case FS_RESULT_SUCCESS:
        case FS_RESULT_FAILURE:
        case FS_RESULT_UNSUPPORTED:
            p_file->error = ret;
            break;
        case FS_RESULT_PROC_ASYNC:
            break;
        case FS_RESULT_PROC_UNKNOWN:
            ret = FS_RESULT_PROC_DEFAULT;
            p_arc->proc_flag &= ~bit;
            break;
        }
    } else {
        ret = FS_RESULT_PROC_DEFAULT;
    }
    if (ret == FS_RESULT_PROC_DEFAULT) {
        ret = (*data_020af1c4[command])(p_file);
    }
    if (ret == FS_RESULT_PROC_ASYNC) {
        if (FS_IsFileSyncMode(p_file)) {
            OSIntrMode bak_psr = OS_DisableInterrupts();

            while (FSi_IsArchiveSync(p_arc)) {
                func_0207a904(&p_arc->sync_q);
            }
            ret = p_file->error;
            (void)OS_RestoreInterrupts(bak_psr);
        }
    } else if (!FS_IsFileSyncMode(p_file)) {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_ASYNC;
        FSi_ReleaseCommand(p_file, ret);
    } else {
        p_arc->flag &= ~FS_ARCHIVE_FLAG_IS_SYNC;
        p_file->error = ret;
    }
    return ret;
}
