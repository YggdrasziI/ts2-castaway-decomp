/* NitroSystem intrusive lists. Rewritten from fingerprints of khdays (CC0). */

/* The link strips unused code; some of these have no caller in this ROM. */
#pragma force_active on
typedef struct NNSFndList {
    void* head_object;
    void* tail_object;
    unsigned short num_objects;
    unsigned short offset;
} NNSFndList;

typedef struct NNSFndLink {
    void* prev_object;
    void* next_object;
} NNSFndLink;

#define LINK(list, object) ((NNSFndLink*)((char*)(object) + (list)->offset))

void NNS_FndInitList(NNSFndList* list, unsigned short offset) {
    list->head_object = 0;
    list->tail_object = 0;
    list->num_objects = 0;
    list->offset = offset;
}

void SetFirstObject(NNSFndList* list, void* object) {
    NNSFndLink* link = LINK(list, object);

    link->next_object = 0;
    link->prev_object = 0;
    list->head_object = object;
    list->tail_object = object;
    list->num_objects++;
}

void NNS_FndAppendListObject(NNSFndList* list, void* object) {
    if (list->head_object == 0) {
        SetFirstObject(list, object);
    } else {
        NNSFndLink* link = LINK(list, object);
        link->prev_object = list->tail_object;
        link->next_object = 0;
        LINK(list, list->tail_object)->next_object = object;
        list->tail_object = object;
        list->num_objects++;
    }
}

void NNS_FndPrependListObject(NNSFndList* list, void* object) {
    if (list->head_object == 0) {
        SetFirstObject(list, object);
    } else {
        NNSFndLink* link = LINK(list, object);
        link->prev_object = 0;
        link->next_object = list->head_object;
        LINK(list, list->head_object)->prev_object = object;
        list->head_object = object;
        list->num_objects++;
    }
}

void NNS_FndInsertListObject(NNSFndList* list, void* where, void* object) {
    if (where == 0) {
        NNS_FndAppendListObject(list, object);
    } else if (where == list->head_object) {
        NNS_FndPrependListObject(list, object);
    } else {
        NNSFndLink* link = LINK(list, object);
        void* previousObject = LINK(list, where)->prev_object;
        NNSFndLink* previousLink = LINK(list, previousObject);
        link->prev_object = previousObject;
        link->next_object = where;
        previousLink->next_object = object;
        LINK(list, where)->prev_object = object;
        list->num_objects++;
    }
}

void NNS_FndRemoveListObject(NNSFndList* list, void* object) {
    NNSFndLink* link = LINK(list, object);

    if (link->prev_object == 0) {
        list->head_object = link->next_object;
    } else {
        LINK(list, link->prev_object)->next_object = link->next_object;
    }
    if (link->next_object == 0) {
        list->tail_object = link->prev_object;
    } else {
        LINK(list, link->next_object)->prev_object = link->prev_object;
    }
    link->prev_object = 0;
    link->next_object = 0;
    list->num_objects--;
}

void* NNS_FndGetNextListObject(NNSFndList* list, void* object) {
    if (object == 0) {
        return list->head_object;
    }
    return LINK(list, object)->next_object;
}

void* NNS_FndGetPrevListObject(NNSFndList* list, void* object) {
    if (object == 0) {
        return list->tail_object;
    }
    return LINK(list, object)->prev_object;
}
