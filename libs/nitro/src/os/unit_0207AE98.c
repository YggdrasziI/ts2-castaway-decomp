/* NitroSDK thread queue links. Part of a file whose other functions are not written;
 * bounds from the functions found. Rewritten from fingerprints of khdays (CC0). */
/* The link strips unused code; some of these have no caller in this ROM. */
#pragma force_active on

typedef struct OSThread {
    unsigned char unk00[0x70];
    unsigned int priority;
    unsigned char unk74[0x4];
    void* queue;
    struct OSThread* prev;
    struct OSThread* next;
} OSThread;

typedef struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
} OSThreadQueue;

typedef struct OSMutex {
    unsigned char unk00[0x10];
    struct OSMutex* next;
    struct OSMutex* prev;
} OSMutex;

typedef struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
} OSMutexQueue;

void OSi_InsertLinkToQueue(OSThreadQueue* queue, OSThread* thread) {
    OSThread* after;
    OSThread* before;

    for (after = queue->head; after != 0 && after->priority <= thread->priority; after = after->next) {
        if (after == thread) {
            return;
        }
    }
    if (after == 0) {
        before = queue->tail;
        if (before == 0) {
            queue->head = thread;
        } else {
            before->next = thread;
        }
        thread->prev = before;
        thread->next = 0;
        queue->tail = thread;
        return;
    }
    before = after->prev;
    if (before == 0) {
        queue->head = thread;
    } else {
        before->next = thread;
    }
    thread->prev = before;
    thread->next = after;
    after->prev = thread;
}

OSThread* OSi_RemoveLinkFromQueue(OSThreadQueue* queue) {
    OSThread* head = queue->head;

    if (head != 0) {
        OSThread* next = head->next;
        queue->head = next;
        if (next != 0) {
            next->prev = 0;
        } else {
            queue->tail = 0;
            head->queue = 0;
        }
    }
    return head;
}

OSThread* OSi_RemoveSpecifiedLinkFromQueue(OSThreadQueue* queue, OSThread* thread) {
    OSThread* cur;
    OSThread* next;
    OSThread* prev;

    for (cur = queue->head; cur != 0; cur = next) {
        next = cur->next;
        if (cur == thread) {
            prev = cur->prev;
            if (queue->head == cur) {
                queue->head = next;
            } else {
                prev->next = next;
            }
            if (queue->tail == cur) {
                queue->tail = prev;
            } else {
                next->prev = prev;
            }
            break;
        }
    }
    return cur;
}

OSMutex* OSi_RemoveMutexLinkFromQueue(OSMutexQueue* queue) {
    OSMutex* head = queue->head;

    if (head != 0) {
        OSMutex* next = head->next;
        queue->head = next;
        if (next != 0) {
            next->prev = 0;
        } else {
            queue->tail = 0;
        }
    }
    return head;
}
