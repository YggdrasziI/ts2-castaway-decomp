/* NitroSDK mutexes. Fields read from khdays' fingerprints and from this ROM. */

typedef struct OSMutex OSMutex;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
} OSMutexQueue;

typedef struct OSThread {
    unsigned char unk00[0x84];
    OSMutex* mutex;
    OSMutexQueue mutexQueue;
} OSThread;

typedef struct OSMutexLink {
    OSMutex* next;
    OSMutex* prev;
} OSMutexLink;

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    int count;
    OSMutexLink link;
};

typedef struct OSThreadInfo {
    unsigned int unk00;
    OSThread* current;
} OSThreadInfo;

extern OSThreadInfo ThreadInfo;

int OS_DisableInterrupts(void);
int OS_RestoreInterrupts(int state);
OSMutex* OSi_RemoveMutexLinkFromQueue(OSMutexQueue* queue);
void func_0207a884(OSThreadQueue* queue);
void func_0207a904(OSThreadQueue* queue);
void OSi_EnqueueTail(OSThread* thread, OSMutex* mutex);
void OSi_DequeueItem(OSThread* thread, OSMutex* mutex);

void OS_InitMutex(OSMutex* mutex) {
    mutex->queue.tail = 0;
    mutex->queue.head = mutex->queue.tail;
    mutex->thread = 0;
    mutex->count = 0;
}

void OS_LockMutex(OSMutex* mutex) {
    int state = OS_DisableInterrupts();
    OSThread* current = ThreadInfo.current;

    for (;;) {
        OSThread* owner = mutex->thread;
        if (owner == 0) {
            mutex->thread = current;
            mutex->count++;
            OSi_EnqueueTail(current, mutex);
            break;
        } else if (owner == current) {
            mutex->count++;
            break;
        } else {
            current->mutex = mutex;
            func_0207a904(&mutex->queue);
            current->mutex = 0;
        }
    }
    OS_RestoreInterrupts(state);
}

void OS_UnlockMutex(OSMutex* mutex) {
    int state = OS_DisableInterrupts();
    OSThread* current = ThreadInfo.current;

    if (mutex->thread == current && --mutex->count == 0) {
        OSi_DequeueItem(current, mutex);
        mutex->thread = 0;
        func_0207a884(&mutex->queue);
    }
    OS_RestoreInterrupts(state);
}

void OSi_UnlockAllMutex(OSThread* thread) {
    while (thread->mutexQueue.head != 0) {
        OSMutex* mutex = OSi_RemoveMutexLinkFromQueue(&thread->mutexQueue);
        mutex->count = 0;
        mutex->thread = 0;
        func_0207a884(&mutex->queue);
    }
}

int OS_TryLockMutex(OSMutex* mutex) {
    int state = OS_DisableInterrupts();
    OSThread* current = ThreadInfo.current;
    int locked;

    if (mutex->thread == 0) {
        mutex->thread = current;
        mutex->count++;
        OSi_EnqueueTail(current, mutex);
        locked = 1;
    } else if (mutex->thread == current) {
        mutex->count++;
        locked = 1;
    } else {
        locked = 0;
    }
    OS_RestoreInterrupts(state);
    return locked;
}

void OSi_EnqueueTail(OSThread* thread, OSMutex* mutex) {
    OSMutex* tail = thread->mutexQueue.tail;

    if (tail == 0) {
        thread->mutexQueue.head = mutex;
    } else {
        tail->link.next = mutex;
    }
    mutex->link.prev = tail;
    mutex->link.next = 0;
    thread->mutexQueue.tail = mutex;
}

void OSi_DequeueItem(OSThread* thread, OSMutex* mutex) {
    OSMutex* next = mutex->link.next;
    OSMutex* prev = mutex->link.prev;

    if (next == 0) {
        thread->mutexQueue.tail = prev;
    } else {
        next->link.prev = prev;
    }
    if (prev == 0) {
        thread->mutexQueue.head = next;
    } else {
        prev->link.next = next;
    }
}
