/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hdf_slist.h"
#include "hdf_log.h"

#define HDF_LOG_TAG utils_slist

void HdfSListInit(struct HdfSList *list)
{
    if (list != NULL) {
        list->root = NULL;
    }
}

bool HdfSListIsEmpty(struct HdfSList *list)
{
    return ((list == NULL) || (list->root == NULL));
}

struct HdfSListNode *HdfSListSearch(struct HdfSList *list, uint32_t keyValue, HdfSListSearchCompare compare)
{
    struct HdfSListIterator it;
    if (compare == NULL) {
        return NULL;
    }
    HdfSListIteratorInit(&it, list);
    while (HdfSListIteratorHasNext(&it)) {
        struct HdfSListNode *listNode = HdfSListIteratorNext(&it);
        if (compare(listNode, keyValue))  {
            return listNode;
        }
    }
    return NULL;
}

struct HdfSListNode *HdfSListGetLast(struct HdfSList *list)
{
    struct HdfSListNode *last = NULL;
    struct HdfSListNode *iterator = NULL;
    if (list == NULL) {
        return NULL;
    }

    for (iterator = list->root; iterator; iterator = iterator->next) {
        if (iterator != NULL) {
            last = iterator;
        }
    }
    return last;
}

void HdfSListAdd(struct HdfSList *list, struct HdfSListNode *link)
{
    struct HdfSListNode *iterator = NULL;
    if (list == NULL || link == NULL) {
        return;
    }

    for (iterator = list->root; iterator; iterator = iterator->next) {
        if (iterator == link) {
            return;
        }
    }

    link->next = list->root;
    list->root = link;
}

void HdfSListAddTail(struct HdfSList *list, struct HdfSListNode *link)
{
    struct HdfSListNode *iterator = NULL;
    if (list == NULL || link == NULL) {
        return;
    }

    for (iterator = (struct HdfSListNode *)list; iterator->next; iterator = iterator->next) {
        if (iterator->next == link) {
            return;
        }
    }

    link->next = NULL;
    iterator->next = link;
}

bool HdfSListAddOrder(struct HdfSList *list, struct HdfSListNode *link, HdfSListAddCompare compare)
{
    struct HdfSListNode *iterator = NULL;
    if (list == NULL || link == NULL || compare == NULL) {
        HDF_LOGE("input is invalid");
        return false;
    }
    for (iterator = list->root; iterator; iterator = iterator->next) {
        if (iterator == link) {
            HDF_LOGE("link is already in list");
            return false;
        }
    }
    if (compare(link, list->root)) {
        link->next = list->root;
        list->root = link;
        return true;
    }
    for (iterator = list->root; iterator && iterator->next; iterator = iterator->next) {
        if (compare(iterator, link) && compare(link, iterator->next)) {
            link->next = iterator->next;
            iterator->next = link;
            return true;
        }
    }
    if ((list->root == NULL) || (iterator == NULL)) {
        link->next = NULL;
        list->root = link;
    } else {
        link->next = NULL;
        iterator->next = link;
    }
    return true;
}

void HdfSListRemove(struct HdfSList *list, struct HdfSListNode *link)
{
    struct HdfSListNode *iterator = NULL;
    if (list == NULL || link == NULL) {
        return;
    }

    for (iterator = (struct HdfSListNode *)list; iterator; iterator = iterator->next) {
        if (iterator->next == link) {
            iterator->next = link->next;
            return;
        }
    }
}

void HdfSListFlush(struct HdfSList *list, HdfSListDeleter deleter)
{
    struct HdfSListIterator iterator;
    if (list == NULL) {
        return;
    }

    HdfSListIteratorInit(&iterator, list);
    while (HdfSListIteratorHasNext(&iterator)) {
        void *listNode = (void *)HdfSListIteratorNext(&iterator);
        HdfSListIteratorRemove(&iterator);
        if (deleter != NULL) {
            deleter(listNode);
        }
    }
}

int HdfSListCount(struct HdfSList *list)
{
    struct HdfSListNode *iterator = NULL;
    int counter = 0;
    if (list == NULL) {
        return counter;
    }

    for (iterator = (struct HdfSListNode *)list; iterator->next; iterator = iterator->next) {
        counter++;
    }
    return counter;
}

struct HdfSListNode *HdfSListPeek(struct HdfSList *list)
{
    if (list == NULL) {
        return NULL;
    }

    return list->root;
}

struct HdfSListNode *HdfSListNext(struct HdfSListNode *link)
{
    if (link == NULL) {
        return NULL;
    }

    return link->next;
}

struct HdfSListNode *HdfSListPop(struct HdfSList *list)
{
    if (list == NULL || list->root == NULL) {
        return NULL;
    }

    struct HdfSListNode *first = list->root;
    list->root = first->next;
    return first;
}

void HdfSListIteratorInit(struct HdfSListIterator *iterator, struct HdfSList *list)
{
    if (iterator == NULL || list == NULL) {
        if (iterator != NULL) {
            iterator->stepOnNext = 0;
            iterator->previous = NULL;
            iterator->current = NULL;
        }
        return;
    }
    iterator->stepOnNext = 0;
    iterator->previous = (struct HdfSListNode *)list;
    iterator->current = list->root;
}

bool HdfSListIteratorHasNext(struct HdfSListIterator *iterator)
{
    if ((iterator == NULL) || (iterator->current == NULL) || (iterator->previous == NULL)) {
        return false;
    }

    if (!iterator->stepOnNext) {
        return iterator->current != NULL;
    }

    if (iterator->previous->next != iterator->current) {
        // current item has been removed
        return iterator->previous->next != NULL;
    }

    // current items has not been removed
    return iterator->current->next != NULL;
}

struct HdfSListNode *HdfSListIteratorNext(struct HdfSListIterator *iterator)
{
    if ((iterator == NULL) || (iterator->current == NULL) || (iterator->previous == NULL)) {
        return NULL;
    }

    if (iterator->stepOnNext) {
        if (iterator->previous->next == iterator->current) {
            iterator->previous = iterator->current;
            iterator->current = iterator->current->next;
        } else {
            // curr was removed from the list, set it again but don't advance prev
            iterator->current = iterator->previous->next;
        }
    } else {
        iterator->stepOnNext = 1;
    }

    return iterator->current;
}

void HdfSListIteratorRemove(struct HdfSListIterator *iterator)
{
    if ((iterator == NULL) || (iterator->current == NULL) || (iterator->previous == NULL)) {
        return;
    }

    iterator->current = iterator->current->next;
    iterator->previous->next = iterator->current;
    iterator->stepOnNext = 0;
}

void HdfSListIteratorInsert(struct HdfSListIterator *iterator, struct HdfSListNode *link)
{
    if (iterator == NULL || link == NULL) {
        return;
    }

    link->next = iterator->current;
    iterator->previous->next = link;
    iterator->previous = link;
}

