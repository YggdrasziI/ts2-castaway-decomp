/* NitroSDK power manager lists. Part of pm.c; rewritten from fingerprints of khdays (CC0). */

/* The link strips unused code; some of these have no caller in this ROM. */
#pragma force_active on
typedef struct PMSleepCallbackInfo {
    void (*callback)(void* arg);
    void* arg;
    struct PMSleepCallbackInfo* next;
} PMSleepCallbackInfo;

int PM_GetLCDPower(void) {
    return (*(volatile unsigned short*)0x04000304 & 1) ? 1 : 0;
}

void PMi_PrependList(PMSleepCallbackInfo** listp, PMSleepCallbackInfo* info) {
    if (!listp) {
        return;
    }
    info->next = *listp;
    *listp = info;
}

void PMi_AppendList(PMSleepCallbackInfo** listp, PMSleepCallbackInfo* info) {
    if (!listp) {
        return;
    }
    if (!*listp) {
        info->next = 0;
        *listp = info;
    } else {
        PMSleepCallbackInfo* p = *listp;
        while (p->next) {
            p = p->next;
        }
        info->next = p->next;
        p->next = info;
    }
}

void PMi_DeleteList(PMSleepCallbackInfo** listp, PMSleepCallbackInfo* info) {
    PMSleepCallbackInfo* p = *listp;
    PMSleepCallbackInfo* pre;

    if (!listp) {
        return;
    }
    pre = p = *listp;
    while (p) {
        if (p == info) {
            if (p == pre) {
                *listp = p->next;
            } else {
                pre->next = p->next;
            }
            break;
        }
        pre = p;
        p = p->next;
    }
}

void PMi_ExecuteList(PMSleepCallbackInfo* listp) {
    while (listp) {
        listp->callback(listp->arg);
        listp = listp->next;
    }
}
