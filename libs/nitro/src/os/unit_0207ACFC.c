/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"

typedef struct OSContext {
    char dummy[1];
} OSContext;

typedef void (*OSSwitchThreadCallback)(void *from, void *to);

extern BOOL OS_SaveContext(OSContext *context);
extern void OS_LoadContext(OSContext *context);
extern int OS_GetProcMode(void);
extern void *func_0207a824(void);

struct ThreadInfo2 {
    unsigned short isNeedRescheduling;
    unsigned short irqDepth;
    void *currentThread;
    void *list;
    OSSwitchThreadCallback switchCallback;
};
extern int data_020c579c;
extern void ***data_020c57a8;
extern OSSwitchThreadCallback data_020c57a4;
extern struct ThreadInfo2 ThreadInfo;
void func_0207acfc(void) {
    struct ThreadInfo2 *info;
    void **curPtr;
    void *cur;
    void *next;
    OSSwitchThreadCallback cb;
    if (data_020c579c != 0) return;
    info = &ThreadInfo;
    if (info->irqDepth != 0 || OS_GetProcMode() == 0x12) {
        info->isNeedRescheduling = 1;
        return;
    }
    curPtr = (void **)data_020c57a8;
    cur = *curPtr;
    next = func_0207a824();
    if (cur == next || next == 0) return;
    if (*(int *)((char *)cur + 0x64) != 2) {
        if (OS_SaveContext((OSContext *)cur)) return;
    }
    cb = data_020c57a4;
    if (cb != 0) {
        cb(cur, next);
    }
    cb = info->switchCallback;
    if (cb != 0) {
        cb(cur, next);
    }
    ThreadInfo.currentThread = next;
    OS_LoadContext((OSContext *)next);
}
